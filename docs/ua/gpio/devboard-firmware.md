---
title: "Devboard: оновлення прошивки"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: оновлення прошивки

Як оновити (або відновити) прошивку самої Wi-Fi Developer Board за допомогою **uFBT**. Це не прошивка Flipper —
про неї див. [Оновлення](/ua/start/updating).

## Крок 1. Встановіть uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) збирає й відлагоджує застосунки, прошиває
прошивку, створює конфігурації для VS Code і прошиває Wi-Fi Devboard.

**Linux і macOS**

1. Встановіть `pipx` ([інструкція](https://pipx.pypa.io/stable/installation/)) і перезапустіть термінал.
2. Встановіть uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Встановіть найновіший [Python](https://www.python.org/downloads/windows/).
2. У PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Перезапустіть PowerShell, а потім:

   ```powershell
   pipx install ufbt
   ```

## Крок 2. Переведіть плату в режим завантажувача

1. Виведіть перелік послідовних пристроїв: macOS — `ls /dev/cu.*`, Linux — `ls /dev/tty*`, Windows — Диспетчер
   пристроїв → **Ports (COM & LPT)**.
2. Підключіть Devboard до комп'ютера кабелем USB-C.
3. Увійдіть у режим завантажувача:
   1. натисніть і тримайте **BOOT**;
   2. натисніть і відпустіть **RESET**, тримаючи **BOOT**;
   3. відпустіть **BOOT**.
4. Виведіть перелік пристроїв знову й запам'ятайте новий.

![Кнопки завантажувача на Devboard](/img/remote/060af5decf4b567c.jpg)

## Крок 3. Прошивання

Linux і macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Повідомлення про успіх: `WiFi board flashed successfully`.

### Якщо прошивання не вдалося

Помилки на кшталт

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

або

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

зазвичай зникають, якщо:

- відключити й знову підключити плату, а потім ще раз увійти в режим завантажувача;
- скористатися іншим USB-портом;
- скористатися іншим кабелем USB-C.

## Крок 4. Завершення

1. Натисніть **RESET** на платі.
2. Відключіть і знову підключіть кабель USB-C.

Тепер плата працює з найновішою офіційною прошивкою Black Magic. Так само її відновлюють після прошивання іншої
прошивки (наприклад, [Marauder](/ua/gpio/esp32)). Далі перейдіть до
[підключення плати до Flipper](/ua/gpio/devboard).
