---
title: "Devboard: перші кроки"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: перші кроки

Офіційна **Wi-Fi Developer Board** — це модуль на ESP32-S2 (ESP32-S2-WROVER-N4R2) для гребінки GPIO. «З коробки»
на ній працює прошивка **Black Magic Probe**, і вона виконує роль **відлагоджувального зонда**: з'єднує
відлагоджувач на вашому комп'ютері зі STM32 у Flipper через SWD — по USB або Wi-Fi. Вона також може перенаправляти
логи UART із Flipper.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Для прошивання вона не потрібна
Оновлення, збірка й завантаження власної прошивки працюють через звичайний USB. Devboard потрібна лише для
живого відлагодження (GDB, точки зупинки) і для читання логів незалежно від ОС Flipper. Про використання цієї ж
плати як Wi-Fi-інструмента (Marauder) див. [ESP32 і Wi-Fi](/ua/gpio/esp32).
:::

## Крок 1. Увімкніть режим Debug на Flipper

1. Відкрийте `Main Menu → Settings → System`.
2. Переведіть `Debug` у `ON`.

Режим Debug потрібен для відлагодження застосунків і відкриває відлагоджувальні параметри в застосунках та
[CLI](/ua/dev/cli). Увімкнюйте його знову після кожного оновлення прошивки.

## Крок 2. Оновіть прошивку плати

Плата постачається зі старішою прошивкою. Спочатку оновіть її:
[Devboard: оновлення прошивки](/ua/gpio/devboard-firmware).

## Крок 3. Вставте Devboard у Flipper

1. **Спочатку вимкніть Flipper.** Плата й картка microSD живляться від однієї лінії 3,3 В Flipper; гаряче
   підключення великого ємнісного навантаження може пошкодити дані на картці.
2. **Вставляйте до кінця.** Без чохла: між Flipper і платою не має бути проміжку (може знадобитися певне
   зусилля). У силіконовому чохлі: не має бути проміжку в середині між чохлом і платою.
3. Увімкніть Flipper, затиснувши <kbd>BACK</kbd>.

![Вставлена Devboard, Flipper без чохла](/img/remote/4eb1e40120ff42bb.jpg)

## Крок 4. Підключення до комп'ютера

### Через USB

USB використовують для відлагодження в режимах **Black Magic** або **DAPLink** і для читання логів.

1. Виведіть перелік послідовних пристроїв на комп'ютері:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Диспетчер пристроїв → **Ports (COM & LPT)**
2. Підключіть порт USB-C **Devboard** до комп'ютера.
3. Виведіть перелік пристроїв знову: з'являться **два нові порти**, і обидва належать Devboard.

Якщо нічого не з'явилося, спробуйте інший кабель (він мусить передавати дані), інший USB-порт або інший
комп'ютер.

### Через Wi-Fi: режим точки доступу (типово)

Плата створює власну мережу. Поки ваш комп'ютер підключений до неї, він втрачає звичайне з'єднання Wi-Fi.

1. На комп'ютері чи смартфоні підключіться до мережі Wi-Fi:
   - Назва: `blackmagic`
   - Пароль: `iamwitcher`
2. Відкрийте <http://192.168.4.1> або <http://blackmagic.local>, щоб побачити вебінтерфейс плати.

Якщо мережа `blackmagic` не з'являється:

- скиньте з'єднання Wi-Fi на комп'ютері;
- плата може бути налаштована як клієнт (STA). Затисніть кнопку **BOOT** на платі на **10 секунд**, щоб скинути
  її налаштування; після перезавантаження вона знову стане точкою доступу.

### Через Wi-Fi: режим клієнта (STA)

Плата приєднується до вашої наявної мережі на 2,4 ГГц, тому доступ до інтернету залишається.

1. Підключіться до плати в режимі точки доступу (див. вище) і відкрийте <http://192.168.4.1>.
2. Виберіть режим **STA**, введіть **SSID** і **пароль** своєї мережі. Кнопка **+** показує перелік мереж на
   2,4 ГГц поблизу (5 ГГц не підтримується).
3. Збережіть налаштування й перезавантажте плату.
4. Далі відкривайте <http://blackmagic.local> через свою звичайну мережу.

Через Wi-Fi доступне лише відлагодження в режимі **Black Magic**.

## Апаратна частина

- Мікроконтролер: ESP32-S2-WROVER-N4R2.
- SWD до Flipper на **піні 10 (SWCLK)** і **піні 12 (SWDIO)**; логи UART — на пінах USART 13/14 Flipper.
- Схеми (друкована плата, ESP32-S2, живлення, рознімання) та складальне креслення:
  [схеми Wi-Fi Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Що далі

- [Devboard: відлагодження й логи](/ua/gpio/devboard-debug)
- [Devboard: оновлення прошивки](/ua/gpio/devboard-firmware)
- Спільнота: [Discord](https://discord.com/invite/flipper) (канал #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
