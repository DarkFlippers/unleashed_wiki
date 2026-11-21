---
title: Exemples
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Scripts Bad USB d'exemple

Des scripts sans danger pour apprendre la syntaxe et vérifier que la saisie fonctionne sur votre machine. Ils se
contentent d'ouvrir un éditeur de texte et d'y taper du texte. Enregistrez n'importe lequel d'entre eux dans un
fichier `.txt` placé dans `/ext/badusb/` et lancez-le comme décrit sur
[Utiliser le Bad USB](/fr/badusb/usage).

::: tip Démonstrations intégrées
Le firmware livre déjà des démonstrations dans `/ext/badusb/examples/` : `demo_windows.txt`, `demo_macos.txt`,
`demo_gnome.txt`, `demo_chromeos.txt`, `test_mouse.txt`, ainsi que `Install_qFlipper_windows.txt` / `_macOS.txt` /
`_gnome.txt`, qui téléchargent et installent qFlipper. Lisez-les dans un éditeur de texte avant de les exécuter.
:::

## Windows : « Hello World » dans le Bloc-notes

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

`GUI r` ouvre la boîte de dialogue Exécuter, et les délais laissent à Windows le temps d'ouvrir chaque fenêtre.

## Windows : copier-coller et codes ALT

D'après `demo_windows.txt` :

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

## macOS : TextEdit

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

`GUI SPACE` ouvre Spotlight. La ligne `ID` doit être la première ligne du fichier. Comme dans le `demo_macos.txt`
intégré, remplacez les identifiants d'exemple par ceux d'un clavier Apple que vous possédez (Informations système →
USB les affiche).

## Linux (GNOME) : éditeur de texte

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

`ALT F2` ouvre l'invite de commande de GNOME. Remplacez `gnome-text-editor` par `gedit`, `kate`, `mousepad`, etc.
selon votre bureau.

## Attendre votre signal avant de taper

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Ouvrez vous-même la fenêtre cible, puis appuyez sur <kbd>OK</kbd> sur le Flipper (**Press to continue**).

## Touches multimédia

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Souris

D'après `test_mouse.txt` :

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

## Script avec sa propre disposition

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

Avec la mauvaise disposition, `y` et `z` seraient inversés sur un clavier allemand (QWERTZ). Voir
[Dispositions de clavier](/fr/badusb/layouts).

## Voir aussi

- [Format des scripts](/fr/badusb/script-format)
- [Utiliser le Bad USB](/fr/badusb/usage)
- [Dispositions de clavier](/fr/badusb/layouts)
