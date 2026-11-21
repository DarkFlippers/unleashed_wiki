---
title: "Devboard: отладка и логи"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: отладка и логи

Когда [Devboard настроена](/ru/gpio/devboard), можно отлаживать прошивку из VS Code и читать логи Flipper по UART.

## Как это работает

Devboard — отладочный пробник между отладчиком на компьютере (по USB или Wi-Fi) и микроконтроллером Flipper. С Flipper
она общается по **Serial Wire Debug**:

- **пин 10** — SWCLK (Serial Wire Clock);
- **пин 12** — SWDIO (Serial Wire Debug Data I/O).

![Железо Devboard](/img/remote/06e0a9eb98e4130d.jpg)

## Режимы отладки

| Подключение | Доступные режимы |
|---|---|
| Wi-Fi | Только Black Magic |
| USB | Black Magic (по умолчанию) или DAPLink |

Режим Black Magic не умеет показывать потоки RTOS; всё остальное работает.

### Переключение режима USB

Как ни странно, режим USB переключается по Wi-Fi:

1. Откройте веб-интерфейс платы (<http://192.168.4.1> в режиме точки доступа или <http://blackmagic.local> в режиме
   клиента, см. [подключение](/ru/gpio/devboard)).
2. На вкладке **WiFi** выберите в **USB mode** значение **BlackMagicProbe** или **DapLink**.
3. Нажмите **SAVE**, затем **REBOOT**.
4. В VS Code выберите соответствующий отладчик (ниже).

## Отладка прошивки в VS Code

### Подготовка

1. Установите [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Склонируйте и соберите прошивку. Для Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (С репозиторием стоковой прошивки `flipperdevices/flipperzero-firmware` шаги те же.) Подробнее о сборке:
   [Сборка прошивки](/ru/dev/build), [FBT](/ru/dev/fbt).

### Запуск сессии

1. Залейте собранную прошивку через Devboard:

   ```bash
   ./fbt flash
   ```

2. Откройте папку прошивки в **VS Code** и установите рекомендуемые расширения (по уведомлению или через поиск
   `@recommended` во вкладке Extensions).
3. Сгенерируйте конфигурацию VS Code:

   ```bash
   ./fbt vscode_dist
   ```

4. Во вкладке **Run and Debug** выберите:
   - **Attach FW (blackmagic)** — по Wi-Fi или USB;
   - **Attach FW (DAP)** — только USB, плата в режиме DAPLink.

   По USB отладчик должен совпадать с **USB mode** платы (проверьте в веб-интерфейсе).
5. Нажмите ▷ **Start Debugging**. При старте сессии прошивка останавливается; нажмите **Continue** на панели, чтобы она
   продолжила работу.

![Отладка в VS Code](/img/remote/92c6a616e2e5f86f.jpg)

См. также [руководство VS Code по отладке](https://code.visualstudio.com/docs/editor/debugging) и
[Отладка](/ru/dev/debugging).

## Чтение логов

Devboard читает вывод логов Flipper с его UART независимо от ОС Flipper. Поэтому видны логи при загрузке, обновлении и
падениях — то, что команда CLI `log` показать не может. Логи доступны **только по USB**.

### Уровень и устройство логов

1. Откройте `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: оставьте `USART` (пины 13/14) — именно их слушает Devboard. `LPUART` выводит логи на пины 15/16,
   `None` отключает логи по UART.

::: tip
Если пины 13/14 нужны другому модулю (Wi-Fi плата, SIM800, GPS), поставьте `Log Device` в `LPUART` или `None`, чтобы
логи ему не мешали.
:::

### macOS

1. Установите [Homebrew](https://brew.sh/), затем `brew install minicom`.
2. Выключите Flipper, вставьте Devboard, включите.
3. Выполните `ls /dev/cu.*`, подключите Devboard по USB, выполните ещё раз. Появятся два устройства, например
   `/dev/cu.usbmodemblackmagic1` и `/dev/cu.usbmodemblackmagic3`.
4. Откройте то, у которого **номер больше**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Логи пойдут в терминал. Выход — через меню minicom или закрыв окно.

### Linux

1. Установите minicom, например `sudo apt install minicom`.
2. Выключите Flipper, вставьте Devboard, включите.
3. Выполните `ls /dev/tty*`, подключите Devboard по USB, выполните ещё раз. Появятся два устройства, например
   `/dev/ttyACM0` и `/dev/ttyACM1`.
4. Откройте то, у которого номер больше:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Если ничего не выводится — попробуйте другое устройство.

### Windows

1. Установите [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Выключите Flipper, вставьте Devboard, включите, подключите Devboard по USB.
3. В **Диспетчере устройств → Порты (COM и LPT)** найдите новый COM-порт.
4. В PuTTY выберите **Serial**, впишите порт в **Serial line**, поставьте **Speed** = **230400**, нажмите **Open**.

![Настройки PuTTY](/img/remote/2bb43453a91a142e.jpg)

## См. также

- [Devboard: начало работы](/ru/gpio/devboard)
- [Devboard: обновление прошивки](/ru/gpio/devboard-firmware)
- [CLI](/ru/dev/cli)
