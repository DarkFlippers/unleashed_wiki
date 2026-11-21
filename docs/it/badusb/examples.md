---
title: Esempi
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Script di esempio per Bad USB

Script innocui per imparare la sintassi e verificare che la digitazione funzioni sulla tua macchina. Si limitano ad
aprire un editor di testo e a scriverci dentro. Salva uno qualsiasi di essi come file `.txt` in `/ext/badusb/` ed
eseguilo come descritto in [Usare Bad USB](/it/badusb/usage).

::: tip Demo integrate
Il firmware include già delle demo in `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`,
`demo_gnome.txt`, `demo_chromeos.txt`, `test_mouse.txt` e `Install_qFlipper_windows.txt` / `_macOS.txt` /
`_gnome.txt`, che scaricano e installano qFlipper. Leggile in un editor di testo prima di eseguirle.
:::

## Windows: "Hello World" nel Notepad

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

`GUI r` apre la finestra Esegui, i ritardi danno a Windows il tempo di aprire ciascuna finestra.

## Windows: copia-incolla e codici ALT

Basato su `demo_windows.txt`:

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

`GUI SPACE` apre Spotlight. La riga `ID` deve essere la prima riga del file. Come nella demo integrata
`demo_macos.txt`, sostituisci gli ID segnaposto con quelli di una tastiera Apple che possiedi (li mostra
Informazioni di sistema → USB).

## Linux (GNOME): editor di testo

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

`ALT F2` apre il prompt dei comandi di GNOME. Sostituisci `gnome-text-editor` con `gedit`, `kate`, `mousepad` ecc. a
seconda del tuo desktop.

## Attendere te prima di digitare

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Apri tu la finestra di destinazione, poi premi <kbd>OK</kbd> sul Flipper (**Press to continue**).

## Tasti multimediali

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

Basato su `test_mouse.txt`:

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

## Script con un layout proprio

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

Con il layout sbagliato, su una tastiera tedesca (QWERTZ) `y` e `z` risulterebbero scambiate. Vedi
[Layout di tastiera](/it/badusb/layouts).

## Pagine correlate

- [Formato degli script](/it/badusb/script-format)
- [Usare Bad USB](/it/badusb/usage)
- [Layout di tastiera](/it/badusb/layouts)
