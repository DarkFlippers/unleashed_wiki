---
title: Nice O-Code app
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Nice O-Code app

**Nice O-Code** (by @xMasterX) recovers the 16-bit **installer code (IC)** of a Nice O-Code remote and saves the remote as a `.sub` file — either as a plain clone, or as a **new remote** of the same installation that you can register in the receiver.

## Background

Nice O-Code is Nice FloR-S keyed with an installer code — one value shared by every remote of an installation. The receiver only accepts a remote that carries its installer code. One captured press is not enough to find it, but **four or more presses** of the same remote are: only the right code makes every press decode to the same serial. The app collects presses and brute-forces all 65 536 codes on the Flipper.

Some O-Code remotes also carry the receiver's **certificate** (a longer 112-bit frame, sent only during the remote's first twenty uses). When the app sees one, it un-masks it once the IC is known and shows it as `Cert`.

::: tip Unleashed
Nice O-Code is a built-in Unleashed system app, and the Sub-GHz app can decode and send O-Code remotes once a file carries the IC. `Add Manually` has matching `Nice O-Code`, `Nice O-Code One` and `Nice O-Code+Crt` entries — see [Add manually](/subghz/add-manually) and [Programming a new remote](/subghz/remote-prog).
:::

::: warning
Use it only with your own installation. A clone shares the counter with the original remote and the two will fight (see [Rolling codes](/subghz/rolling-codes)).
:::

## Requirements

- The Nice FloR-S key file `/ext/subghz/assets/nice_flor_s` on the SD card (it ships with the firmware). Without it the app reports `No rainbow table`.
- A working O-Code remote of the installation. The app listens on **433.92 MHz AM650**, with the internal or an [external](/subghz/external-cc1101) radio (`Int` / `Ext` in the header).

## Capturing a remote

1. Open `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Choose `Capture remote`. The status shows `Listening 433.92`.
3. Press the remote's button **4 or more times — short presses, do not hold it**. Each new press shows `Press N: …`; the line `Presses n/4  Xpkt` and the progress bar fill up. If the remote has a certificate, the line ends with `+Crt`.
4. When 4 presses are collected, `Solve` appears — press <kbd>OK</kbd>.
5. The screen shows `Trying installer codes` with a counter up to 65536. <kbd>←</kbd> (`Cancel`) stops it.
6. On success you see `IC XXXX`, `Serial XXXXXXX` and, if present, `Cert XXXXXX`.

Statuses you may see while capturing:

| Status | Meaning |
|---|---|
| `Not O-Code, ignored` | a frame that is not O-Code (e.g. a plain FloR-S remote) |
| `Same press, ignored` | a repeat of a press already stored |
| `Need 4+ packets` | not enough presses to solve |
| `Ambiguous, capture more` | several codes fit — press the remote a few more times and solve again |
| `No code fits, not O-Code?` | no installer code matches — probably not an O-Code remote, or presses from different remotes were mixed |

## Saving

On the result screen:

- <kbd>OK</kbd> (`Save`) — a **clone** of the captured remote (default name `NiceO`). Useful for testing, but it fights your original over the counter.
- <kbd>→</kbd> (`New`) — a **new remote**: the same installer code, button and certificate, but a serial and counter of its own (default name `NiceO_new`). This is the one to register in the receiver. The counter is set close to, and a little below, the count of your working remote.

Both are written to `/ext/subghz/` after you name them (`Name the .sub file`). Open them in `Sub-GHz → Saved`.

To register the new remote, follow the Nice FloR-S procedure on [Programming a new remote](/subghz/remote-prog). A remote with a certificate enrols itself: press its key about once a second, **10–15 times in one go** — the gate opens around the tenth press.

## Decode RAW file

`Decode RAW file` runs the same recovery on a RAW `.sub` you recorded earlier with [Read RAW](/subghz/read-raw) (record 4+ separate presses). A key file is refused with `Not a RAW capture`. The progress bar shows how far into the file it is.

## Troubleshooting

- **`No rainbow table`** — `/ext/subghz/assets/nice_flor_s` is missing; reinstall the firmware with the SD card in, or restore the assets folder.
- **Presses do not count** — make separate short presses; holding the button repeats the same press.
- **Factory-fresh receiver ignores the O-Code remote** — an untouched receiver has no installer code; register a plain `Nice One` / `Nice FloR-S` remote at the button instead (see [Programming a new remote](/subghz/remote-prog)).
- **Receiver refuses the new remote** — keep the counter near your working remote's; do not reset it to zero.

## Related pages

- [Programming a new remote](/subghz/remote-prog) · [Add manually](/subghz/add-manually)
- [Rolling codes](/subghz/rolling-codes) · [Supported systems](/subghz/supported-systems)
