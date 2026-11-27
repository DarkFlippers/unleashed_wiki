---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (by Lechnio) is a small on-device waveform editor for RAW `.sub` captures. A [Read RAW](/subghz/read-raw) recording usually contains seconds of noise around a short burst you care about. With RAW Edit you find the real signal, mark it, and save just that part.

::: tip Unleashed
RAW Edit ships with Unleashed as a system app, and the Sub-GHz app opens it directly: `Sub-GHz → Read RAW` (or `Saved`) → open a RAW file → <kbd>→</kbd> `More` → `Edit`. The `Edit` item is shown only when RAW Edit is installed. When you leave the editor you are returned to Sub-GHz.
:::

**When to use it:** trim a long RAW capture before sharing or sending it, split one recording into separate buttons, glue several captures together, or find out which protocol hides inside a RAW file.

## Main menu

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit`:

- `Select .sub file` — open a file from `/ext/subghz` in the editor
- `Merge .sub files` — join several files into one
- `Config` — options for loading and merging
- `About` — version and project link

Besides RAW files, the app can load any signal the firmware can encode (it is converted to RAW through the internal encoder). For protocols with custom buttons it first offers a button picker.

## The editor

The screen shows the waveform with an overview bar at the top, and two lines below: `View:` (zoom) and `Marked:` (length of the A..B selection). The selected range is highlighted with a dotted line; little marks show there is more signal beyond the screen edge.

| Button | Action |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | move the active marker (A or B); hold to move faster |
| <kbd>↑</kbd> / <kbd>↓</kbd> | zoom in / out |
| <kbd>OK</kbd> | switch the active marker between A and B |
| hold <kbd>OK</kbd> | open the action menu |
| <kbd>Back</kbd> | close the editor |

The action menu (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> to run, <kbd>Back</kbd> to close) sits on the left, with a read-only info panel beside it showing A..B's sample count, `TE` and detected line coding (`PWM`, `PPM`, `Manchester`, `NRZ` or `1:1`):

- **Save** — write only the A..B range to a new RAW file. The name is proposed as `<name>_edit1`, `_edit2`, … Saving under an existing name asks `Name exists, overwrite?`; the open file itself is never overwritten.
- **Decode** — decode the A..B range with the firmware's Sub-GHz decoders (trying every manufacturer on each KeeLoq frame; skips BinRAW), group identical frames (`Decoded: N`) and save the chosen one as a key file, named by protocol and manufacturer by default (e.g. `KeeLoq_Verex`). Each decoded entry also has a **Locate** button that snaps A..B onto its frame (the first one when it repeats). `No known protocol` means nothing decoded.
- **Cut** / **Copy** / **Paste** — press <kbd>←</kbd> / <kbd>→</kbd> on `Cut` to switch between **Cut** (remove A..B and place it on the clipboard; refused if it would leave the signal empty), **Copy** (copy A..B to the clipboard file) and **Paste** (insert the clipboard at the active marker and select it).
- **Undo** — SD-backed history of the last **32** cuts and pastes (takes no RAM). With more than one edit, it lists them newest first with sample counts and positions and rolls back to before the one you pick. Crossed out when there is nothing to undo.

## Trimming a capture — step by step

1. Record the remote in [Read RAW](/subghz/read-raw) and save it.
2. Open it in RAW Edit (via `More → Edit` or `Select .sub file`).
3. Zoom out with <kbd>↓</kbd> to see where the bursts are.
4. Move marker **A** to just before the burst with <kbd>←</kbd>/<kbd>→</kbd>, press <kbd>OK</kbd>, move marker **B** to just after it.
5. Hold <kbd>OK</kbd> → `Save`, accept or edit the name.
6. Test the saved file from `Sub-GHz → Saved`.

## Merging files

1. `Merge .sub files` → pick a file; the dialog shows `Added N file(s)` and the sample count. Choose `Add more` or `Done`.
2. All files must be on the same frequency, otherwise you get `Frequency mismatch`.
3. The result opens in the editor as `merged`; save it from the action menu.

## Config

| Item | What it does |
|---|---|
| Normalize jitter | `OFF`/`ON` — clean up timing jitter and drift when loading |
| Merge gap | silence inserted between merged files, 0–1000 ms (default 100); <kbd>OK</kbd> opens a number input |
| Repeat | repeat each loaded / merged signal 1–64 times |

A read-only line at the bottom of `Config` also shows whether custom buttons and preserving the rolling counter are available in the current firmware build.

## Limits and troubleshooting

- **No length limit (v2.0):** signals and merges are kept in a working file on the SD card, while RAM holds a sliding window of the capture (up to ~38 000 samples on a fresh boot), leaving room for Decode and Save. Pushing marker A or B past the window edge slides it a quarter further; zooming out stops at the window with `No RAM to zoom out`.
- **`Low RAM` prompt** — shown when free RAM fits fewer than 15 000 samples of a larger signal; offers `Reboot` or `Continue`. `Decode` also checks for ~8 KB of free RAM and reports `Low memory` instead of crashing.
- `Unsupported protocol or file is empty` — the file is not a signal the firmware can encode.
- `Nothing in A..B` / `Range too small` — move the markers further apart.
- Long gaps are kept at their real length in the saved file.

## Related pages

- [Read RAW](/subghz/read-raw) · [File format](/subghz/file-format)
- [Remote Analyzer](/subghz/remote-analyzer)
