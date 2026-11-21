# Flipper screen renderer

Generates the Flipper Zero screenshots in `docs/public/screens/` from the real
Unleashed firmware GUI code. The output matches a qFlipper screenshot
pixel for pixel. Every PNG is rendered, not drawn by hand. Change the firmware
or a spec, run the script again, and the screenshots follow.

```sh
npm run screens                                 # all screens -> docs/public/screens/
bash scripts/screens/build.sh --only nfc/       # only files whose path contains "nfc/"
FW_SRC=~/src/unleashed bash scripts/screens/build.sh
```

Requirements: `clang`, zlib (part of macOS and of most Linux dev setups),
`python3`. Pillow is installed into `.build/venv` automatically when
`python3` lacks it.

## 1. Fetch the firmware

The renderer compiles firmware sources, so it needs a checkout of the
Unleashed firmware. Only three small submodules are needed; the full
`fbt` toolchain is not.

```sh
git clone --filter=blob:none --branch dev \
    https://github.com/DarkFlippers/unleashed-firmware.git ~/src/unleashed
git -C ~/src/unleashed submodule update --init --depth 50 \
    lib/mlib lib/heatshrink lib/libusb_stm32
export FW_SRC=~/src/unleashed
```

`FW_SRC` points at that checkout. When it is unset, `build.sh` looks for
`.firmware/` in the repository root, so cloning there needs no environment
variable at all. The current screenshots were rendered from `dev` at commit
`7f31d0cca513` (2026-11-20).

The Sub-GHz Remote app lives in its own submodule. Add it if you want to
render that app's screens:

```sh
git -C "$FW_SRC" submodule update --init applications/main/subghz_remote
```

## 2. How it works

```
build.sh
 ├─ tools/icons.py      assets/icons/**  -> .build/icons/assets_icons.{c,h}
 │                      assets/dolphin/external/<anim>/frame_N.png
 │                                       -> .build/icons/assets_dolphin.{c,h}
 ├─ clang               firmware GUI sources + stubs + harness + specs
 │                      -> .build/flipper_screens
 └─ flipper_screens     renders every spec -> <section>/<name>.png + manifest.json
```

**Firmware code, unmodified.** These are compiled straight from `FW_SRC`:

- `canvas.c`, `elements.c`, `icon*.c`, `view.c`, `view_port.c`
- every `gui/modules/*.c`, including `widget_elements/`
- all of `u8g2`, `furi_string`, and the heatshrink and toolbox helpers
- the app views listed in `fw_sources.txt` (for example
  `subghz/views/receiver.c`, `lfrfid/views/lfrfid_view_read.c`,
  `bad_usb/views/bad_usb_view.c`)

`harness/desktop_host.c` includes `gui/gui.c` and `power/power_service/power.c`.
That way the real status-bar compositor and the real battery icon callback
draw the desktop.

There is one host patch. `gui/modules/menu.c` is copied to `.build/patched/`
with its `static_assert`s removed. Those asserts pin the 32-bit plugin ABI,
which a 64-bit host cannot satisfy. The drawing code is not changed.

**Stubs** (`stubs/`) replace the HAL and RTOS:

- The display reset pin, SPI and random-number generator are stubs.
- Mutexes are no-ops and the tick counter stays at 0. A spec that shows an
  uptime sets `screen_host_tick` for its own draw and resets it afterwards.
- The device identity is a placeholder, never a real Flipper: name `Flipper`,
  hardware `13.F7B9C6 R00`, firmware `unlshd-080 [21-11-2026]`, commit
  `7f31d0cc` on `dev`, API `88.27`, copro `1.20.0:L`. `lib/toolbox/version.c`
  is generated from git at build time, so the stubs provide its accessors.
  `-DSRV_BT` is set because `desktop_view_debug.c` is the only compiled source
  that reads it, and with it the info screen prints the copro version.
- The RTC always returns 2026-11-21 12:34:56 with 24h, D/M/Y and metric
  locale settings.
- Timers only fire when a spec calls `screen_fire_oneshot_timers()`.
- Threads never run, so workers stay idle.
- `-DNDEBUG -DFURI_NDEBUG` disables asserts, as in a release build.

The binary links with `-undefined dynamic_lookup`. Firmware code that never
runs while drawing (radio workers, storage, notifications) may therefore stay
unresolved.

**Specs** (`specs/*.c`) build a module the same way the app scene does
(`submenu_add_item`, `widget_add_*`, `popup_set_*`, a view's public setters)
with realistic placeholder data, then draw it:

```c
SCREEN(nfc_reading,
       .file = "nfc/reading",              /* -> docs/public/screens/nfc/reading.png */
       .section = "nfc",
       .title = "Reading a card",
       .menu_path = "NFC → Read",
       .scene = "applications/main/nfc/scenes/nfc_scene_detect.c") {
    Popup* popup = popup_alloc();
    popup_set_header(popup, "Reading", 97, 15, AlignCenter, AlignTop);
    popup_set_text(popup, "Hold card next\nto Flipper's back", 94, 27, AlignCenter, AlignTop);
    popup_set_icon(popup, 0, 8, &I_NFC_manual_60x50);
    screen_draw_view(canvas, popup_get_view(popup));
}
```

`screen_draw_view()` reproduces `gui_redraw_fs()` followed by
`view_port_draw()`:

- It resets the canvas, sets a 128x64 frame and applies the view's
  orientation.
- It calls the draw callback.
- It does not call `enter` callbacks, so no worker starts.

`screen_draw_desktop()` draws on the desktop layer, then adds the status bar
(SD card icon and battery icon). `screen_draw_desktop_view()` does the same for
a View of the desktop's own view dispatcher (the lock menu, the PIN input and
the device info screen, which is why they leave `STATUS_BAR_Y_SHIFT` at the
top). `screen_draw_fullscreen()` draws a ViewPort the app put on
`GuiLayerFullscreen`, which covers the status bar (Passport, Snake).

When a view keeps its model private, include the firmware `.c` in the spec
(see `specs/subghz.c` and the frequency analyzer). When a state can only be
reached by input, call `view_input()` the way the user would (see Read RAW
REC in `specs/subghz.c`).

To add a screen:

1. Write a `SCREEN(...)` block in the matching `specs/*.c`.
2. If the screen uses a new app view, add its `.c` to `fw_sources.txt`.
3. Run `bash scripts/screens/build.sh --only <file>`.

## 3. Output format (what qFlipper does)

The format comes from qFlipper's own code:

- `application/screencanvas.cpp`: `ScreenCanvas::setFrame()`,
  `canvas()`, `canvasTransform()`.
- `application/components/StreamOverlay.qml`.
- `application/Theme.qml`.

| | |
|---|---|
| Frame decode | pixel (x, y) = bit `y % 8` of byte `(y / 8) * 128 + x` (u8g2 buffer as sent by RPC) |
| Foreground | `"black"` → `#000000` |
| Background | `Theme.color.lightorange2` → `#FE8A2C` |
| Size | `saveImage(url, 4)`: 128x64 scaled ×4 with nearest neighbour → **512x256** RGB PNG |
| Orientation | vertical views (e.g. universal remotes) are rotated like `canvasTransform()` → 256x512 |

`manifest.json` lists every screen with these fields:

- `file`
- `section`
- `title`
- `menuPath`
- `scene`: the firmware source the placeholder state comes from

## 4. Verifying against a real screenshot

```sh
.build/venv/bin/python tools/verify.py <reference.png> <x0,y0,x1,y1|full> <ours.png> [diff.png]
```

The reference can be a raw qFlipper PNG. It can also be a screenshot pasted
into a documentation illustration at any scale or colour.

The script:

1. searches for the 128x64 pixel grid inside the crop box;
2. samples each cell;
3. prints the number of differing pixels;
4. writes a diff image (red = only ours, blue = only the reference).

## Known limits

- Placeholder data is written into the specs by hand. Each spec reproduces
  the format strings of the matching scene or protocol (for example
  `protocol_em4100_render_data`, `nfc_render_mf_classic_info`), but those
  functions are not called.
- Animated icons are drawn at frame 0. The desktop shows passive frame 0 with
  no speech bubble.
- The status bar on the desktop uses default settings: SD card mounted,
  battery 100 % not charging, Bluetooth off, clock off.
