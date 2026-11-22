---
title: Primjeri
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Primjeri skripti za Bad USB

Bezopasne skripte za učenje sintakse i provjeru radi li tipkanje na vašem računalu. One samo otvaraju uređivač teksta i
upisuju tekst u njega. Spremite bilo koju od njih kao `.txt` datoteku u `/ext/badusb/` i pokrenite je kako je opisano u
[Korištenje Bad USB-a](/hr/badusb/usage).

::: tip Ugrađeni primjeri
Firmver već sadrži pokazne skripte u `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`, `demo_gnome.txt`,
`demo_chromeos.txt`, `test_mouse.txt` te `Install_qFlipper_windows.txt` / `_macOS.txt` / `_gnome.txt`, koje preuzimaju
i instaliraju qFlipper. Pročitajte ih u uređivaču teksta prije pokretanja.
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

`GUI r` otvara dijaloški okvir Run, a pauze daju sustavu Windows vremena da otvori svaki prozor.

## Windows: kopiranje, lijepljenje i ALT kodovi

Na temelju `demo_windows.txt`:

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

`GUI SPACE` otvara Spotlight. Redak `ID` mora biti prvi redak datoteke. Kao i u ugrađenom `demo_macos.txt`,
zamijenite zamjenske ID-ove s onima Apple tipkovnice koju posjedujete (prikazani su pod System Information → USB).

## Linux (GNOME): uređivač teksta

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

`ALT F2` otvara naredbeni upit u GNOME-u. Zamijenite `gnome-text-editor` s `gedit`, `kate`, `mousepad` itd. za svoje
radno okruženje.

## Čekanje prije tipkanja

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Sami otvorite ciljni prozor, zatim pritisnite <kbd>OK</kbd> na Flipperu (**Press to continue**).

## Medijske tipke

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Miš

Na temelju `test_mouse.txt`:

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

## Skripta s vlastitim rasporedom tipkovnice

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

S pogrešnim rasporedom tipkovnice `y` i `z` bili bi zamijenjeni na njemačkoj (QWERTZ) tipkovnici. Pogledajte [Rasporedi tipkovnice](/hr/badusb/layouts).

## Povezane stranice

- [Format skripte](/hr/badusb/script-format)
- [Korištenje Bad USB-a](/hr/badusb/usage)
- [Rasporedi tipkovnice](/hr/badusb/layouts)
