---
title: Script format
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Bad USB script format (DuckyScript)

Bad USB executes plain-text scripts in an **extended DuckyScript** syntax. Classic USB Rubber Ducky 1.0 scripts run
as-is; on top of that the Flipper adds custom USB/BLE identity, `ALT`+Numpad input, `SYSRQ`, media keys, mouse
control, waiting for a button press and more. This reference is checked against the command table in the firmware
(`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## File rules

- Plain text, extension **`.txt`**, no compilation. Line endings `\n` or `\r\n`.
- One command per line. Empty lines are skipped; lines may be indented with spaces or tabs.
- Commands are **UPPERCASE and case-sensitive**: `STRING`, not `string`.
- Command and argument are separated by a single space.
- Comments are whole lines starting with `REM`. There are no end-of-line comments.
- Typed text (`STRING`, `STRINGLN`) must be **ASCII**. Non-ASCII characters stop the script with
  *"Native .kl supports ASCII, not UTF-8"*.
- On an error the script stops and the screen shows *ERROR:*, the line number and the reason.

## Quick reference

| Command | Argument | Effect |
|---|---|---|
| `REM` | text | Comment, ignored. |
| `ID` | `VID:PID [Manufacturer:Product]` | USB identity, **first line only**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Bluetooth identity, **first line only**. |
| `DELAY` | ms | Wait once. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Wait before every following command. |
| `STRING` | text | Type text. |
| `STRINGLN` | text | Type text and press Enter. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Delay between keystrokes for the **next** `STRING` only. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Delay between keystrokes for **every** `STRING`. |
| `REPEAT` | n | Repeat the previous command n more times. |
| `DUCKY_LANG` | layout name | Switch the keyboard layout for the rest of the script (Unleashed). |
| `HOLD` | key / mouse button | Press and keep holding. |
| `RELEASE` | key / mouse button | Release a held key. |
| `ALTCHAR` | code | Type one character with `ALT`+Numpad. |
| `ALTSTRING` / `ALTCODE` | text | Type text with `ALT`+Numpad. |
| `SYSRQ` | character | Magic SysRq key combo. |
| `MEDIA` | media key | Consumer-control key (volume, play…). |
| `GLOBE` | key | Fn/Globe + key (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | none | Pause until <kbd>OK</kbd> is pressed on the Flipper. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | none | Mouse clicks. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Move the mouse. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Scroll the wheel. |
| key combo | e.g. `CTRL-ALT DELETE` | Press and release keys together. |

## Comments

```text
REM This line is ignored
```

## Delays

| Command | Parameter | Notes |
|---|---|---|
| `DELAY` | ms | Single pause. |
| `DEFAULT_DELAY` | ms | Added before every next command. Same as `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Delays are your main tool for reliability: the host needs time to open windows, so add a `DELAY` after `GUI r`,
`ENTER` in a launcher, etc. Long delays are shown on the screen as `Delay Ns`.

## Typing text

| Command | Parameter | Notes |
|---|---|---|
| `STRING` | text | Types the text exactly, using the active keyboard layout. |
| `STRINGLN` | text | Same, then presses Enter. |
| `STRING_DELAY` | ms | Pause between keystrokes for the next `STRING`/`STRINGLN` only. Same as `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pause between keystrokes for all following strings. Same as `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Without a string delay text is sent as fast as possible; some hosts/apps drop characters then. The
built-in demo scripts use `DEFAULT_STRING_DELAY 10`.

::: warning Layout matters
`STRING` sends *key positions*, translated through the selected [keyboard layout](/badusb/layouts). If the host uses
another layout than the app, you get wrong characters. Text must be ASCII.
:::

## Keys and combos

A line that is not a command is read as a key press: zero or more **modifiers**, then one **key**. Modifiers are
joined with spaces or hyphens. The key is a special key name or a single character.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modifiers

| Name | Notes |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Windows / Command / Super key |

### Special keys

| Name | Notes |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Arrows |
| `ENTER` | |
| `DELETE` | Forward delete |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Break |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Context-menu key |
| `F1` … `F24` | Function keys (the firmware knows F13-F24 too) |

## Repeat

```text
DOWN
REPEAT 9
```

`REPEAT n` runs the **previous command** n more times (the example presses Down 10 times). `n` must be ≥ 1.

## Hold and release

| Command | Parameter | Notes |
|---|---|---|
| `HOLD` | special key, modifier, single character, or mouse button | Press and keep holding until `RELEASE`. |
| `RELEASE` | the same | Release that key. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

At most **6** keys/buttons can be held at once (the size of the HID key report); more gives *"Too many keys are
held"*. `RELEASE` without anything held gives *"No keys are held"*. The official document says 5; the firmware
check allows 6.

## ALT + Numpad input

On Windows (and some Linux setups) any character can be typed by holding `ALT` and entering its code on the numeric
keypad. This **doesn't depend on the keyboard layout**, which makes it handy on unknown machines.

| Command | Parameter | Notes |
|---|---|---|
| `ALTCHAR` | character code | Types one character: holds ALT, types the digits on the numpad. |
| `ALTSTRING` | text | Types every printable ASCII character (32-126) of the text via its ALT code. |
| `ALTCODE` | text | Same as `ALTSTRING` (name used by some DuckyScript implementations). |

NumLock is switched on automatically before ALT input.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Sends `ALT`+`PRINTSCREEN`+key, the Linux [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key) combo. Be careful:
some SysRq keys reboot or halt the system immediately.

## Media keys

`MEDIA <key>` presses a consumer-control key:

| Key | Notes |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | System |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Browser / app navigation |
| `SNAPSHOT` | Take a photo in a camera app |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Playback |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Volume |
| `FN` | Fn/Globe key on Mac keyboards |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Display brightness |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Fn / Globe key (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` holds Fn/Globe, presses the key, and releases both (special key or single character).

## Wait for a button press

```text
WAIT_FOR_BUTTON_PRESS
```

The script pauses indefinitely; the Flipper shows **Press to continue**. Press <kbd>OK</kbd> to go on. Useful to
synchronise with something you do by hand (log in, unlock the screen…).

## Mouse

| Command | Parameter | Notes |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | none | Left click |
| `RIGHTCLICK` / `RIGHT_CLICK` | none | Right click |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | none | Middle (wheel) click |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (integers) | Relative movement; negative = left / up |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (integer) | Scroll wheel; sign gives direction |

Mouse buttons work with `HOLD`/`RELEASE`, e.g. for drag and drop:

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## Device ID

You can set the identity the Flipper presents to the host. The command must be on the **very first line**; it is
applied when the script is opened, before it runs, and the app **switches to the matching connection mode** (you
can still switch back manually). On other lines these commands are ignored.

| Command | Parameters | Example | Mode |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | same as `BLE_ID` |

- `ID`: VID and PID (hex) are mandatory; manufacturer and product strings are optional (max. 31 characters each).
- `BLE_ID` / `BT_ID`: the 6-byte MAC and the device name are both mandatory.

## Keyboard layout per script: `DUCKY_LANG`

::: tip Unleashed
`DUCKY_LANG` is new in Unleashed (PR #1224 by @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Loads `/ext/badusb/assets/layouts/<name>.kl` and uses it from that line on, instead of the global layout set in
  Config. Short aliases: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- The name may contain letters, digits, `-` and `_`, and nothing may follow it on the line.
- A missing file or an invalid name **doesn't stop the script**: it silently falls back to the built-in `en-US`.
- Every new run starts again with the global layout, so put `DUCKY_LANG` near the top.

The list of layout names is on [Keyboard layouts](/badusb/layouts).

## Related pages

- [Examples](/badusb/examples)
- [Keyboard layouts](/badusb/layouts)
- [Using Bad USB](/badusb/usage)
