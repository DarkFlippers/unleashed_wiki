---
title: Examples
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Bad USB example scripts

Harmless scripts to learn the syntax and check that typing works on your machine. They only open a text editor and
type into it. Save any of them as a `.txt` file in `/ext/badusb/` and run it as described in
[Using Bad USB](/badusb/usage).

::: tip Built-in demos
The firmware already ships demos in `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`, `demo_gnome.txt`,
`demo_chromeos.txt`, `test_mouse.txt`, and `Install_qFlipper_windows.txt` / `_macOS.txt` / `_gnome.txt`, which download
and install qFlipper. Read them in a text editor before running.
:::

## Windows: Notepad "Hello World"

```text
REM Open Notepad and type a few lines
DEFAULT_STRING_DELAY 10
DELAY 1000
GUI r
DELAY 500
STRING notepad
ENTER
DELAY 1000
STRINGLN Hello World!
STRINGLN Typed by Flipper Zero.
```

`GUI r` opens the Run dialog, the delays give Windows time to open each window.

## Windows: copy-paste and ALT codes

Based on `demo_windows.txt`:

```text
DEFAULT_STRING_DELAY 10
DELAY 1000
GUI r
DELAY 500
STRING notepad
DELAY 500
ENTER
DELAY 750

STRING Hello World!
ENTER
DEFAULT_DELAY 50

REM Copy the previous line and paste it twice
UP
HOME
SHIFT DOWN
CTRL c
RIGHT
CTRL v
CTRL v

REM ALT+Numpad input works with any keyboard layout
ALTCHAR 7
ALTSTRING This line was typed using the Alt+Numpad method.
ENTER
```

## macOS: TextEdit

```text
ID 1234:5678 Apple:Keyboard
REM Replace 1234:5678 with the VID:PID of a real Apple keyboard to skip the Keyboard Setup Assistant
DELAY 1000
GUI SPACE
DELAY 500
STRING TextEdit
DELAY 500
ENTER
DELAY 1500
GUI n
DELAY 1000
STRINGLN Hello from Flipper Zero!
```

`GUI SPACE` opens Spotlight. The `ID` line must be the first line of the file. As in the built-in `demo_macos.txt`,
replace the placeholder IDs with those of an Apple keyboard you own (System Information → USB shows them).

## Linux (GNOME): text editor

```text
ID 1234:abcd Generic:USB Keyboard
ESC
DELAY 200
ALT F2
DELAY 1000
STRING gnome-text-editor
ENTER
DELAY 2000
STRINGLN Hello from Flipper Zero!
```

`ALT F2` opens GNOME's command prompt. Replace `gnome-text-editor` with `gedit`, `kate`, `mousepad` etc. for your
desktop.

## Wait for you before typing

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Open the target window yourself, then press <kbd>OK</kbd> on the Flipper (**Press to continue**).

## Media keys

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Mouse

Based on `test_mouse.txt`:

```text
DEFAULT_DELAY 200
DELAY 1000
REM Draw a square with the cursor
MOUSEMOVE -10 0
REPEAT 20
MOUSEMOVE 0 10
REPEAT 20
MOUSEMOVE 10 0
REPEAT 20
MOUSEMOVE 0 -10
REPEAT 20
MOUSESCROLL -50
MOUSESCROLL 50
```

## Script with its own layout

```text
REM The host uses a German keyboard
DUCKY_LANG de-DE
DELAY 1000
GUI r
DELAY 500
STRING notepad
ENTER
DELAY 1000
STRINGLN Zwei Yaks: y and z are typed correctly
```

With the wrong layout, `y` and `z` would be swapped on a German (QWERTZ) keyboard. See [Keyboard layouts](/badusb/layouts).

## Related pages

- [Script format](/badusb/script-format)
- [Using Bad USB](/badusb/usage)
- [Keyboard layouts](/badusb/layouts)
