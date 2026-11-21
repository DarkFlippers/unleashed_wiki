---
title: Примеры
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Примеры скриптов Bad USB

Безобидные скрипты, чтобы освоить синтаксис и проверить, что набор на вашей машине работает. Они только открывают
текстовый редактор и печатают в него. Сохраните любой как `.txt` в `/ext/badusb/` и запустите, как описано в
[Работа с Bad USB](/ru/badusb/usage).

::: tip Встроенные демо
В прошивке уже есть демо в `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`, `demo_gnome.txt`,
`demo_chromeos.txt`, `test_mouse.txt`, а также `Install_qFlipper_windows.txt` / `_macOS.txt` / `_gnome.txt`, которые
скачивают и устанавливают qFlipper. Прочитайте их в редакторе перед запуском.
:::

::: warning Раскладка хоста
Все примеры печатают латиницей. Перед запуском переключите язык ввода на компьютере на английский (или на тот,
что выбран в Config / `DUCKY_LANG`), иначе вместо `notepad` наберётся `тщеузфв`.
:::

## Windows: «Hello World» в Блокноте

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

`GUI r` открывает окно «Выполнить», паузы дают Windows время открыть каждое окно.

## Windows: копирование-вставка и ALT-коды

На основе `demo_windows.txt`:

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

`GUI SPACE` открывает Spotlight. Строка `ID` должна быть первой в файле. Как и во встроенном `demo_macos.txt`,
замените ID-заглушки на ID своей клавиатуры Apple (их видно в «Информация о системе → USB»).

## Linux (GNOME): текстовый редактор

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

`ALT F2` открывает командную строку GNOME. Замените `gnome-text-editor` на `gedit`, `kate`, `mousepad` и т. п. под
своё окружение.

## Дождаться вас перед набором

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Сами откройте нужное окно, затем нажмите <kbd>OK</kbd> на Флиппере (**Press to continue**).

## Мультимедийные клавиши

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Мышь

На основе `test_mouse.txt`:

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

## Скрипт со своей раскладкой

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

С неправильной раскладкой на немецкой (QWERTZ) клавиатуре `y` и `z` поменялись бы местами. См.
[Раскладки клавиатуры](/ru/badusb/layouts).

## Связанные страницы

- [Формат скриптов](/ru/badusb/script-format)
- [Работа с Bad USB](/ru/badusb/usage)
- [Раскладки клавиатуры](/ru/badusb/layouts)
