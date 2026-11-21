---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (by @xMasterX) works with a captured **Security+ 2.0 keypad** signal — the 86-bit frame sent by Chamberlain / LiftMaster wireless keypads. The keypad PIN lives inside that frame. The app lets you set a PIN by hand or sweep `0000`–`9999`, transmits each candidate, and writes the PIN back into the file once you have found the right one.

::: tip Unleashed
Security+ 2.0 Keypad (86 bits, 315 / 390 / 868 MHz) is decoded by the Unleashed Sub-GHz app, and this built-in system app edits its PIN. Regular 62-bit Security+ 2.0 remotes are not keypad frames and are refused.
:::

::: warning
Only for your own garage door opener and keypad.
:::

## Before you start

1. Capture your keypad with `Sub-GHz → Read` on its frequency (see [Read](/subghz/read)) and save it. The saved file must show `Security+ 2.0` with `Bit: 86`.
2. The file lives in `/ext/subghz/`.

## Using the app

1. Open `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Choose `Open .sub file` and pick the keypad capture. When it loads, the status shows the frequency and `ready` (e.g. `315MHz  ready`). If the file already contains a `Pin`, it is shown.
3. The four PIN digits are on screen, with a frame around the active digit:
   - <kbd>←</kbd> / <kbd>→</kbd> — move between digits
   - <kbd>↑</kbd> / <kbd>↓</kbd> — change the PIN
   - <kbd>OK</kbd> (`Send`) — transmit the current PIN (`Sending 1234...` → `Sent 1234`)
   - hold <kbd>OK</kbd> — **sweep**: send every PIN from the current one onwards; a progress bar shows `N of 9999`. Short <kbd>OK</kbd> or <kbd>←</kbd> (Back) stops it at `Stopped at NNNN`
   - hold <kbd>←</kbd> — **save** the current PIN into the file (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — back to the menu

The hint line on screen sums it up: `hold OK sweep   < save`.

Saving updates the opened file in place: it writes the `Pin`, `Key` and `Secplus_packet_1` fields. Afterwards the file can be sent normally from `Sub-GHz → Saved`.

## Messages

| Message | Meaning |
|---|---|
| `Not Security+ 2.0: …` | the file is another protocol |
| `Not an 86-bit keypad` | a Security+ 2.0 remote, not a keypad frame |
| `Missing packet 1` / `No Key value` | incomplete capture — read the keypad again |
| `Unsupported preset …` / `Bad custom preset` | the file's preset cannot be used |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | transmission on this frequency is not allowed (see [Frequencies](/subghz/frequencies)) |
| `TX failed` | the radio could not transmit |

## Troubleshooting

- **Sweep is slow** — each PIN is a separate transmission with a short pause; a full sweep takes a long time. Start it from a likely value and stop as soon as the door reacts.
- **Door reacted but you missed the PIN** — the sweep stops on the number shown; step back with <kbd>↓</kbd> and send single PINs with <kbd>OK</kbd> to confirm, then hold <kbd>←</kbd> to save.
- **Wrong file refused** — capture the keypad itself, not a handheld remote.

## Related pages

- [Read](/subghz/read) · [Supported systems](/subghz/supported-systems)
- [Rolling codes](/subghz/rolling-codes)
