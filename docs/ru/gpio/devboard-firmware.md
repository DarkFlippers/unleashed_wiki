---
title: "Devboard: обновление прошивки"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: обновление прошивки

Как обновить (или восстановить) прошивку самой Wi-Fi Developer Board с помощью **uFBT**. Это не прошивка Flipper — о
ней см. [Обновление](/ru/start/updating).

## Шаг 1. Установите uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) собирает и отлаживает приложения, прошивает
прошивку, создаёт конфигурации VS Code и прошивает Wi-Fi Devboard.

**Linux и macOS**

1. Установите `pipx` ([инструкция](https://pipx.pypa.io/stable/installation/)) и перезапустите терминал.
2. Установите uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Установите последний [Python](https://www.python.org/downloads/windows/).
2. В PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Перезапустите PowerShell, затем:

   ```powershell
   pipx install ufbt
   ```

## Шаг 2. Переведите плату в режим загрузчика

1. Посмотрите список последовательных устройств: macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows — Диспетчер
   устройств → **Порты (COM и LPT)**.
2. Подключите Devboard к компьютеру кабелем USB-C.
3. Войдите в режим загрузчика:
   1. нажмите и держите **BOOT**;
   2. не отпуская **BOOT**, нажмите и отпустите **RESET**;
   3. отпустите **BOOT**.
4. Снова посмотрите список и найдите новое устройство.

![Кнопки загрузчика Devboard](/img/remote/060af5decf4b567c.jpg)

## Шаг 3. Прошейте

Linux и macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Сообщение об успехе: `WiFi board flashed successfully`.

### Если прошивка не удалась

Ошибки вроде

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

или

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

обычно лечатся так:

- отключите и снова подключите плату, затем ещё раз войдите в режим загрузчика;
- другой USB-порт;
- другой кабель USB-C.

## Шаг 4. Завершение

1. Нажмите **RESET** на плате.
2. Отключите и снова подключите кабель USB-C.

Теперь на плате последняя официальная прошивка Black Magic. Этим же способом её восстанавливают после другой прошивки
(например, [Marauder](/ru/gpio/esp32)). Дальше — [подключение к Flipper](/ru/gpio/devboard).
