---
title: Приклади
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/examples, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md]
sources: [unleashed-src, unleashed-docs]
---
# Приклади скриптів Bad USB

Безневинні скрипти, щоб вивчити синтаксис і переконатися, що введення працює на вашій машині. Вони лише
відкривають текстовий редактор і друкують у ньому. Збережіть будь-який із них як файл `.txt` у `/ext/badusb/` і
запустіть так, як описано у [Використанні Bad USB](/ua/badusb/usage).

::: tip Вбудовані демонстрації
Прошивка вже містить демонстрації у `/ext/badusb/examples/`: `demo_windows.txt`, `demo_macos.txt`,
`demo_gnome.txt`, `demo_chromeos.txt`, `test_mouse.txt`, а також `Install_qFlipper_windows.txt` / `_macOS.txt` /
`_gnome.txt`, які завантажують і встановлюють qFlipper. Перед запуском прочитайте їх у текстовому редакторі.
:::

## Windows: «Hello World» у Notepad

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

`GUI r` відкриває діалог «Виконати», а затримки дають Windows час відкрити кожне вікно.

## Windows: копіювання-вставлення та ALT-коди

На основі `demo_windows.txt`:

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

`GUI SPACE` відкриває Spotlight. Рядок `ID` має бути першим рядком файлу. Як і у вбудованому `demo_macos.txt`,
замініть тестові ID на ID клавіатури Apple, яка вам належить (System Information → USB показує їх).

## Linux (GNOME): текстовий редактор

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

`ALT F2` відкриває командний рядок GNOME. Замініть `gnome-text-editor` на `gedit`, `kate`, `mousepad` тощо —
відповідно до вашого робочого середовища.

## Зачекати на вас перед введенням

```text
REM Type a long text only when you are ready
WAIT_FOR_BUTTON_PRESS
DEFAULT_STRING_DELAY 5
STRINGLN The quick brown fox jumps over the lazy dog.
```

Відкрийте потрібне вікно самостійно, а потім натисніть <kbd>OK</kbd> на Flipper (**Press to continue**).

## Мультимедійні клавіші

```text
REM Turn the volume down 10 steps, then mute and unmute
MEDIA VOLUME_DOWN
REPEAT 9
DELAY 500
MEDIA MUTE
DELAY 1000
MEDIA MUTE
```

## Миша

На основі `test_mouse.txt`:

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

## Скрипт із власною розкладкою

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

З хибною розкладкою на німецькій клавіатурі (QWERTZ) `y` і `z` помінялися б місцями. Див.
[Розкладки клавіатури](/ua/badusb/layouts).

## Пов'язані сторінки

- [Формат скриптів](/ua/badusb/script-format)
- [Використання Bad USB](/ua/badusb/usage)
- [Розкладки клавіатури](/ua/badusb/layouts)
