---
title: Sub-GHz Remote app
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** turns the Flipper into a five-button remote control. You bind up to five saved `.sub` files to <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> and <kbd>OK</kbd>, give each one a label, and then send them with one press without browsing through `Sub-GHz → Saved`.

::: tip Unleashed
Sub-GHz Remote is built into Unleashed and sits in the **main menu**: `Main Menu → Sub-GHz Remote`. It was written by @gid9798 and @xMasterX, and its source lives in a separate repository, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), included in the firmware as a submodule. Stock firmware does not have it in the menu; for official firmware there is a separate build in the app catalog.
:::

## When to use it

- You use a few signals all the time, for example a gate, a garage door and a barrier, and want them one press away.
- You control several devices (fan, lights, doorbell) and want them on a single screen with readable labels.

Each button sends a normal `.sub` file, so anything that works from `Sub-GHz → Saved → Emulate` works here too: static keys, rolling-code remotes you made with [Add Manually](/subghz/add-manually), RAW and BinRAW recordings. Protocols that the Flipper can only receive cannot be bound.

## The menu

The app opens the map file browser straight away. Press <kbd>Back</kbd> to reach the menu:

| Item | What it does |
|---|---|
| `Open Map File` | pick a map and go to the remote screen |
| `Edit Map File` | pick a map and open it in the editor |
| `New Map File` | type a name and build a new map |
| `Set Default` | pick the map the app opens by itself from now on |
| `Clear Default` | forget that map again (shown only when one is set) |

Maps are `.txt` files in the `subghz_remote` folder on the SD card. The file name does not matter and you can keep as many maps as you like. If you have an old `unirf` folder from earlier versions, the app moves it to `subghz_remote` the first time it starts.

## Build a map on the Flipper

The app has a built-in editor, so you do not need a PC.

1. Save the signals you want first, using [Read](/subghz/read), [Read RAW](/subghz/read-raw) or [Add Manually](/subghz/add-manually).
2. Open `Main Menu → Sub-GHz Remote`, press <kbd>Back</kbd> and pick `New Map File`.
3. Type a name, up to 25 characters. The map becomes `/ext/subghz_remote/<name>.txt`.
4. The editor opens on the `UP` slot.

| Key in the editor | What it does |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | move between the five slots: `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — open the slot's menu |
| <kbd>→</kbd> | `Save` — go to the preview |
| <kbd>←</kbd> or <kbd>Back</kbd> | `Back` |

The bar at the top shows the slot name and its label. Under it you see the path of the file bound to that slot, or `Button not set` when the slot is empty, or `ERR:` with the reason: `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

The slot menu has four items:

- `Edit Label` — the text shown for this button. Up to 25 characters, of which about 16 fit on the remote screen. An empty label is allowed, the app asks `Empty Label Name / Continue?` first; with no label it shows the file name instead.
- `Edit File` — a `.sub` file browser that starts in `/ext/subghz`. If the file cannot be used you get an `ERROR` popup saying `Bad frequency`, `Bad modulation` or `Unsupported protocol`, and the slot keeps what it had.
- `Button` — which button of the remote this slot sends: `Default`, `Up`, `Down`, `Left`, `Right`. See [Custom buttons](#custom-buttons).
- `Clear Slot` — empty the slot.

Press <kbd>→</kbd> when you are done. The preview shows the finished remote with `Back` on the left and `Save` on the right; <kbd>→</kbd> or <kbd>OK</kbd> writes the file and a `Saved!` screen appears. Leaving the editor with changes you have not saved asks `Changes are not saved / do you want to exit?` first.

Leaving a slot empty is fine. A map with one button works.

## Sending

Pick `Open Map File` and choose your map. This screen is drawn sideways, so hold the Flipper upright.

- **Hold** a key to transmit. That row turns black and the LED blinks magenta.
- Release it and the protocol sends its own remaining repeats, then stops. A RAW file plays to the end of the recording and starts again if you are still holding the key.
- Under the five rows the app shows what it is sending: protocol name, frequency and modulation, `Key:` (only for keys of 32 bits or less), `Sn:` or `Fix:`, `Cnt:`, `MF:`. Five lines fit at most.
- The icon in the top left corner tells you whether the internal radio or an [external module](/subghz/external-cc1101) is in use.
- <kbd>Back</kbd> stops a transmission that is running. Press it again to leave the app.

A slot whose file could not be loaded shows `[X] Can't open file` or `[X] Error in .sub file` instead of its label. Empty slots stay blank, and pressing them blinks the LED red.

## Custom buttons

A rolling-code remote has several buttons, and a `.sub` file stores one of them. `Button` in the slot menu picks which one this slot sends. `Default` keeps the button from the file; `Up`, `Down`, `Left` and `Right` send the same remote's other buttons, the same ones you get from those keys in `Sub-GHz → Saved → Emulate`. The editor then adds `(Btn. Up)` after the path.

The counter moves once per press, and the app puts the original button back when the transmission ends.

This is how you give a hidden or programming button its own slot. Which arrow is which button depends on the protocol, see [Flipper as a new remote](/subghz/remote-prog).

## The map file

The editor writes a plain text file in the Flipper format:

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` are the full paths of the `.sub` files bound to each D-pad direction.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` are the texts shown on screen for those buttons.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` are the custom button, in hex: `00` default, `01` up, `02` down, `03` left, `04` right. The editor leaves the line out when the slot uses `Default`.

You can also write a map on a PC. If you do:

- Separate the key from the value with a colon and **one** space, exactly as above.
- The order of the lines does not matter, the app looks every key up by name. A key you leave out counts as empty.
- The **file name** of a `.sub` has to be plain printable ASCII and must not contain `\ < > * | " : ?`. A Cyrillic name or an emoji makes that slot fail to load.
- Keep labels to about 16 characters. Longer ones are cut off on the narrow remote screen.

The built-in editor cannot produce a broken map, so prefer it.

## Open a map on startup

`Set Default` stores the chosen map in `/ext/subghz_remote/.config`. From then on the app goes straight to the remote screen when you open it, and <kbd>Back</kbd> takes you to the menu. `Clear Default` deletes that file.

The app also accepts a map file path as a launch argument, so another app can open a specific remote directly.

## Troubleshooting

- **`[X] Can't open file`**: the `.sub` file that slot points to was moved, renamed or deleted. Pick it again with `Edit File`, or fix the path in the map.
- **`[X] Error in .sub file`**: the file loads but cannot be sent. The editor says why: `Bad frequency` (the signal's frequency is not supported by the radio you have selected, see [Frequencies](/subghz/frequencies)), `Bad modulation`, or `Unsupported protocol` (the protocol is receive-only).
- **A button does nothing** and the LED blinks red: that slot is empty or its file failed to load.
- **A rolling-code remote stopped working** after you used both the Flipper and the original: that is a counter conflict, not a bug in the app. See [Rolling codes](/subghz/rolling-codes) and make a new remote with [Flipper as a new remote](/subghz/remote-prog).
- **`Not official FW` warning on startup**: you installed the app-catalog build meant for official firmware. Use the Sub-GHz Remote that is already in Unleashed's main menu.
- Older guides mention a `Config is incorrect. Please configure map.` screen. The current app does not show it; it marks the broken buttons on the remote screen instead.

## Related pages

- [Reading signals](/subghz/read) · [Read RAW](/subghz/read-raw) · [Add Manually](/subghz/add-manually)
- [Flipper as a new remote](/subghz/remote-prog)
- [.sub file format](/subghz/file-format)
