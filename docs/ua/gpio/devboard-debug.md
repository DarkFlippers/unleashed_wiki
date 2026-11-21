---
title: "Devboard: відлагодження й логи"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: відлагодження й логи

Коли [Devboard налаштована](/ua/gpio/devboard), ви можете відлагоджувати прошивку з VS Code й читати логи Flipper
через UART.

## Як це працює

Devboard — це відлагоджувальний зонд між відлагоджувачем на вашому комп'ютері (через USB або Wi-Fi) і
мікроконтролером Flipper. З Flipper вона спілкується через **Serial Wire Debug**:

- **пін 10** — SWCLK (Serial Wire Clock);
- **пін 12** — SWDIO (Serial Wire Debug Data I/O).

![Апаратна частина Devboard](/img/remote/06e0a9eb98e4130d.jpg)

## Режими відлагодження

| З'єднання | Доступні режими |
|---|---|
| Wi-Fi | лише Black Magic |
| USB | Black Magic (типово) або DAPLink |

Режим Black Magic не підтримує розпізнавання потоків RTOS; усе інше працює.

### Перемикання режиму USB

Як не дивно, режим USB перемикається через Wi-Fi:

1. Відкрийте вебінтерфейс плати (<http://192.168.4.1> у режимі точки доступу або <http://blackmagic.local> у
   режимі клієнта, див. [підключення](/ua/gpio/devboard)).
2. На вкладці **WiFi** встановіть **USB mode** у **BlackMagicProbe** або **DapLink**.
3. Натисніть **SAVE**, а потім **REBOOT**.
4. У VS Code виберіть відповідний відлагоджувач (див. нижче).

## Відлагодження прошивки у VS Code

### Попередні вимоги

1. Встановіть [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Клонуйте й зберіть прошивку. Для Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Ті самі кроки працюють із офіційним репозиторієм `flipperdevices/flipperzero-firmware`.) Докладніше про
   збірку: [Збірка прошивки](/ua/dev/build), [FBT](/ua/dev/fbt).

### Запуск сесії

1. Прошийте щойно зібрану прошивку через Devboard:

   ```bash
   ./fbt flash
   ```

2. Відкрийте теку прошивки у **VS Code** і встановіть рекомендовані розширення (з повідомлення або через
   `@recommended` на вкладці Extensions).
3. Згенеруйте конфігурацію VS Code:

   ```bash
   ./fbt vscode_dist
   ```

4. У **Run and Debug** виберіть:
   - **Attach FW (blackmagic)** — через Wi-Fi або USB;
   - **Attach FW (DAP)** — лише USB, плата в режимі DAPLink.

   Через USB відлагоджувач мусить відповідати **USB mode** плати (перевірте його у вебінтерфейсі).
5. Натисніть ▷ **Start Debugging**. На початку сесії прошивка зупиняється; натисніть **Continue** на панелі
   інструментів, щоб вона продовжила роботу.

![Відлагодження у VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Див. також [посібник із відлагодження у VS Code](https://code.visualstudio.com/docs/editor/debugging) і
[Налагодження застосунків](/ua/dev/debugging).

## Читання логів

Devboard читає вивід логів Flipper із його UART незалежно від ОС Flipper. Тому ви бачите логи під час
завантаження, оновлень і збоїв — тобто те, чого команда CLI `log` показати не може. Логи доступні **лише через
USB**.

### Задайте рівень і пристрій логування

1. Відкрийте `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: залиште `USART` (піни 13/14) — саме там слухає Devboard. `LPUART` надсилає логи на піни 15/16,
   `None` вимикає логування через UART.

::: tip
Якщо піни 13/14 потрібні іншому модулю (Wi-Fi-плата, SIM800, GPS), встановіть `Log Device` у `LPUART` або `None`,
щоб вивід логів йому не перешкоджав.
:::

### macOS

1. Встановіть [Homebrew](https://brew.sh/), а потім `brew install minicom`.
2. Вимкніть Flipper, вставте Devboard, увімкніть пристрій.
3. Виконайте `ls /dev/cu.*`, підключіть Devboard по USB, виконайте команду знову. З'являться два нові пристрої,
   наприклад `/dev/cu.usbmodemblackmagic1` і `/dev/cu.usbmodemblackmagic3`.
4. Відкрийте той, у якого **більший номер**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Логи почнуть іти в терміналі. Виходьте через меню minicom або закрийте вікно.

### Linux

1. Встановіть minicom, наприклад `sudo apt install minicom`.
2. Вимкніть Flipper, вставте Devboard, увімкніть пристрій.
3. Виконайте `ls /dev/tty*`, підключіть Devboard по USB, виконайте команду знову. З'являться два нові пристрої,
   наприклад `/dev/ttyACM0` і `/dev/ttyACM1`.
4. Відкрийте той, у якого більший номер:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Якщо нічого не з'являється, спробуйте інший пристрій.

### Windows

1. Встановіть [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Вимкніть Flipper, вставте Devboard, увімкніть пристрій, підключіть Devboard по USB.
3. У **Диспетчері пристроїв → Ports (COM & LPT)** запам'ятайте новий COM-порт.
4. У PuTTY виберіть **Serial**, введіть порт у **Serial line**, встановіть **Speed** у **230400** і натисніть
   **Open**.

![Налаштування PuTTY](/img/remote/2bb43453a91a142e.jpg)

## Пов'язані сторінки

- [Devboard: перші кроки](/ua/gpio/devboard)
- [Devboard: оновлення прошивки](/ua/gpio/devboard-firmware)
- [CLI](/ua/dev/cli)
