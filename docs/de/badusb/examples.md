---
title: Beispiele
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Bad-USB-Beispielskripte

Harmlose Skripte, um die Syntax kennenzulernen und zu prüfen, ob das Tippen auf deinem Rechner funktioniert. Sie
öffnen nur einen Texteditor und schreiben dort hinein. Speichere eines davon als `.txt`-Datei in `/ext/badusb/` und
starte es wie unter [Bad USB verwenden](/de/badusb/usage) beschrieben.

::: tip Mitgelieferte Demos
Die Firmware bringt bereits Demos in `/ext/badusb/examples/` mit: `demo_windows.txt`, `demo_macos.txt`,
`demo_gnome.txt`, `demo_chromeos.txt`, `test_mouse.txt` sowie `Install_qFlipper_windows.txt` / `_macOS.txt` /
`_gnome.txt`, die qFlipper herunterladen und installieren. Lies sie vor dem Start in einem Texteditor durch.
:::

## Windows: Notepad „Hello World"

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

`GUI r` öffnet den Ausführen-Dialog, die Verzögerungen geben Windows Zeit, jedes Fenster zu öffnen.

## Windows: Kopieren/Einfügen und ALT-Codes

Nach `demo_windows.txt`:

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

`GUI SPACE` öffnet Spotlight. Die `ID`-Zeile muss die erste Zeile der Datei sein. Ersetze die Platzhalter-IDs — wie
im mitgelieferten `demo_macos.txt` — durch die einer Apple-Tastatur, die du besitzt (System Information → USB zeigt
sie an).

## Linux (GNOME): Texteditor

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

`ALT F2` öffnet die Befehlszeile von GNOME. Ersetze `gnome-text-editor` passend zu deinem Desktop durch `gedit`,
`kate`, `mousepad` usw.

## Erst auf dich warten, dann tippen

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Öffne das Zielfenster selbst und drücke dann am Flipper <kbd>OK</kbd> (**Press to continue**).

## Medientasten

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Maus

Nach `test_mouse.txt`:

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

## Skript mit eigenem Layout

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

Mit dem falschen Layout wären `y` und `z` auf einer deutschen (QWERTZ-)Tastatur vertauscht. Siehe
[Tastaturlayouts](/de/badusb/layouts).

## Verwandte Seiten

- [Skriptformat](/de/badusb/script-format)
- [Bad USB verwenden](/de/badusb/usage)
- [Tastaturlayouts](/de/badusb/layouts)
