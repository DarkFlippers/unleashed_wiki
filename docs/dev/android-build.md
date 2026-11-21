---
title: Building apps on Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Building apps on Android (Termux + uFBT)

Set up `ufbt` inside [Termux](https://termux.dev/) on an ordinary, non-rooted Android phone and compile Flipper Zero
apps (`.fap`) right on the phone — no PC, no proot, no virtual machine.

::: info Credits
Worked out by [@CamsShaft](https://github.com/CamsShaft) through a lot of trial and error on a Samsung Galaxy S22
(SM-S901W, aarch64). Original guide (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). It is part of the
Unleashed documentation.
:::

**Scope:** this builds **apps**, not the firmware. For the firmware itself see [Building the firmware](/dev/build).

Paths below assume an **aarch64** device and the default Termux prefix
(`$PREFIX` = `/data/data/com.termux/files/usr`). Your device may differ — the typical failures are covered in
[Troubleshooting](#troubleshooting).

## Why it needs extra work

uFBT downloads a prebuilt `arm-none-eabi-gcc` cross-toolchain built for ordinary Linux with **glibc**. Termux runs on
Android's **Bionic** libc with a non-standard filesystem layout, and every ELF binary in the toolchain asks for
`/lib/ld-linux-aarch64.so.1` as its dynamic linker — which doesn't exist on Android.

The fix: install Termux's glibc compatibility layer, then run each toolchain binary through glibc's own linker via
a small wrapper script.

::: danger Do not run `patchelf` on the toolchain binaries
It corrupts their ELF segment layout and you get segfaults out of `cc1`. The wrappers below leave the binaries
byte-for-byte untouched.
:::

## Prerequisites

- An aarch64 Android device.
- [Termux](https://f-droid.org/en/packages/com.termux/) installed **from F-Droid** — the Google Play build is
  obsolete and won't work.
- Internet and a couple of GB free for the toolchain, SDK and glibc.

## 1. Base packages

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` is **not** optional — the wrapper loop in step 6 uses it to tell ELF binaries from everything else.

## 2. glibc compatibility layer

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

These must be **two separate commands**: `glibc-repo` adds the repository that `glibc-runner` comes from. Together
they install a full glibc under `$PREFIX/glibc/`, including the dynamic linker. Check it:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Never set `LD_PRELOAD` to glibc's `libc.so.6` globally.** It breaks Termux's own Bionic binaries, Python included,
in non-obvious ways. The wrappers in step 6 make it unnecessary.
:::

## 3. Install uFBT and Python build dependencies

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Package | Needed for |
|---|---|
| `colorlog` | Build script logging |
| `heatshrink2` | Icon and asset compression |
| `pyelftools` | The `FASTFAP` post-processing step |
| `scons` | The build system — must be a standalone install; the toolchain's bundled copy is unusable here |
| `pillow` | Icon conversion; without it the only error is a bare `convert: No such file or directory` |

If the `pillow` wheel fails to build, use the Termux package: `pkg install python-pillow`.

## 4. Point uFBT at the Unleashed SDK

**uFBT defaults to the official firmware SDK.** To build against Unleashed, pass the Unleashed update index:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Channels: `dev` and `release`. **Every later `ufbt update` needs the same flags**, or you silently fall back to the
official SDK and build against the wrong API.

If `~/.ufbt/toolchain/` is still empty, any uFBT call bootstraps the toolchain:

```sh
ufbt -h
```

An error mentioning `python3` here is expected — step 5 fixes it. Check that the toolchain arrived:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Repoint the toolchain's Python

The toolchain ships its own glibc-linked Python, which can't run here. Point every `python3*` entry at Termux's
Python:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Wrap the toolchain binaries

Everything else depends on this step. Each wrapper runs the real binary through glibc's dynamic linker with an
explicit `--library-path`, so the binary itself is never modified.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

The three globs are three separate directories of ELF binaries. Missing one gives a distinct error:

| Directory | Contains | Error if not wrapped |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Why the guards matter (especially when re-running):

- `*.so` is skipped because `liblto_plugin.so` in `libexec/` is a shared library, not an executable — wrapping it
  gives `invalid ELF header`.
- `*.real` and the `$f.real` check make the function idempotent: re-running after a toolchain update can't wrap a
  wrapper.
- In `bin/` only `arm-none-eabi-*` is wrapped on purpose: `bin/python3` now points at Termux's Bionic Python and must
  **not** go through glibc's linker.

::: warning
`ufbt update` can replace the whole toolchain — **re-run steps 5 and 6 after every update.**
:::

## 7. Build

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

A successful build ends like this:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

The `.fap` is in `dist/`. Compare the reported API with your Flipper's firmware — a mismatch means the app will
refuse to load.

## 8. Get the .fap onto the Flipper

`ufbt launch` and `ufbt flash_usb` need a serial connection (`/dev/ttyACM*`). **On a stock, non-rooted Android this
doesn't work** — Android doesn't expose USB CDC-ACM device nodes to Termux. Only a rooted device with a working
CDC-ACM driver can use those commands.

Copy the file out instead. FAPs live in `/ext/apps/<Category>/` on the microSD card:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

From `Downloads` the file is visible to other apps, so move it to the Flipper the usual way — with the Flipper mobile
app, or a USB-C microSD card reader.

## Troubleshooting

### `cannot execute cc1` / `cannot execute as`

One of the three directories in step 6 wasn't wrapped. Re-run the `wrap` calls — they're safe to repeat.

### `liblto_plugin.so: invalid ELF header`

A shared library got wrapped. Restore it:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` from cc1

The binary was corrupted, almost always by `patchelf`. Re-download the toolchain:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Then redo steps 5 and 6. **Never use `patchelf` on these binaries.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

`pillow` is missing: `pip install pillow`, or `pkg install python-pillow`.

### `python3: No such file or directory`

The toolchain's Python symlink is broken or was restored by an update. Re-run step 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` points at glibc's `libc.so.6`, which breaks Termux's Bionic binaries. Clear it:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Then check your shell startup files for leftovers:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` says the SDK is up to date, but the toolchain is missing

uFBT tracks SDK and toolchain separately. Force both:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Then redo steps 5 and 6.

### The app builds but reports the wrong API version

A `ufbt update` ran without `--index-url`, so uFBT switched back to the official SDK. Re-run the command from
[step 4](#_4-point-ufbt-at-the-unleashed-sdk).

### The wrappers disappeared after an update

Expected — `ufbt update` can replace the whole toolchain directory. Re-run steps 5 and 6.

## What actually happens

Each wrapper runs its real binary through glibc's dynamic linker with `--library-path` pointing at glibc's libraries.
When `arm-none-eabi-gcc` execs `cc1`, it hits a shell script that chains through the linker to the untouched
`.real` binary. The cross-compiled output is unaffected — it targets bare-metal Cortex-M, not Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Related pages

- [Your first app in C](/dev/first-app-c)
- [Building the firmware](/dev/build)
- [Apps on the SD card](/apps/sd-card-apps)
- [Flipper mobile app](/mobile/mobile-app)
