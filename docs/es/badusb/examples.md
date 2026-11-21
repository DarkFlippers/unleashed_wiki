---
title: Ejemplos
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Scripts de ejemplo para Bad USB

Scripts inofensivos para aprender la sintaxis y comprobar que la escritura funciona en tu equipo. Solo abren un
editor de texto y escriben en él. Guarda cualquiera de ellos como fichero `.txt` en `/ext/badusb/` y ejecútalo como
se describe en [Uso de Bad USB](/es/badusb/usage).

::: tip Demostraciones incluidas
El firmware ya trae demostraciones en `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`, `demo_gnome.txt`,
`demo_chromeos.txt`, `test_mouse.txt`, e `Install_qFlipper_windows.txt` / `_macOS.txt` / `_gnome.txt`, que descargan
e instalan qFlipper. Léelos en un editor de texto antes de ejecutarlos.
:::

## Windows: «Hello World» en el Bloc de notas

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

`GUI r` abre el diálogo Ejecutar; los retardos dan a Windows tiempo para abrir cada ventana.

## Windows: copiar y pegar y códigos ALT

Basado en `demo_windows.txt`:

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

`GUI SPACE` abre Spotlight. La línea `ID` debe ser la primera del fichero. Igual que en el `demo_macos.txt`
integrado, sustituye los identificadores de ejemplo por los de un teclado de Apple que tengas (Información del
Sistema → USB los muestra).

## Linux (GNOME): editor de texto

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

`ALT F2` abre el cuadro de comandos de GNOME. Sustituye `gnome-text-editor` por `gedit`, `kate`, `mousepad`, etc.,
según tu escritorio.

## Esperarte antes de escribir

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Abre tú mismo la ventana de destino y después pulsa <kbd>OK</kbd> en el Flipper (**Press to continue**).

## Teclas multimedia

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Ratón

Basado en `test_mouse.txt`:

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

## Script con su propia distribución

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

Con la distribución equivocada, `y` y `z` saldrían intercambiadas en un teclado alemán (QWERTZ). Véase
[Distribuciones de teclado](/es/badusb/layouts).

## Páginas relacionadas

- [Formato de los scripts](/es/badusb/script-format)
- [Uso de Bad USB](/es/badusb/usage)
- [Distribuciones de teclado](/es/badusb/layouts)
