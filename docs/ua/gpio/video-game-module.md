---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

**Video Game Module** (VGM) — офіційний додатковий модуль на базі **Raspberry Pi RP2040**. Він вставляється у
гребінку GPIO й додає:

- **Video Out** — дублює екран Flipper на телевізор чи монітор (сигнал DVI-D, 640×480);
- **6-осьовий датчик руху** (TDK ICM-42688-P: 3-осьовий гіроскоп + акселерометр) для керування жестами;
- **порт USB-C**, підключений до RP2040 (для прошивання або для власних прошивок);
- **гребінку на 14 пінів** із виведеними GPIO RP2040;
- **кнопки BOOT / RESET** (натискаються скріпкою) для режиму прошивання UF2 і скидання;
- RGB-світлодіод на верхній частині.

Він також може працювати як самостійна плата на RP2040, сумісна з проєктами для Raspberry Pi Pico.

![Кнопки та рознімання Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Встановлення й підключення до телевізора

1. **Встановіть модуль.** Він постачається з силіконовим бампером, розрахованим на Flipper *без* чохла. Якщо ваш
   Flipper у силіконовому чохлі, зніміть бампер із модуля (або чохол із Flipper).
2. **Прошивка.** Модулю потрібна прошивка Flipper 0.98.3 або новіша; актуальні релізи Unleashed підходять.
3. **Перевірте налаштування UART:** `Main Menu → Settings → Expansion Modules → Listen UART` мусить мати значення
   **`USART`**. За будь-якого іншого значення модуль не визначається. (Див.
   [Модулі розширення](/ua/gpio/expansion-modules).)
4. Вставте модуль (із вимкненим Flipper) й увімкніть пристрій. Flipper виявить модуль і підготує його
   автоматично.
5. Підключіть кабель телевізора до порту **Video Out** модуля й виберіть на телевізорі відповідний вхід.

### «Video Game Module not initialized»

Цей текст на телевізорі означає, що модуль не спілкується з Flipper: прошивка надто стара, `Listen UART` не має
значення `USART`, або модуль має живлення (наприклад, від USB) без приєднаного Flipper.

## Ігри та застосунки

Датчик руху використовують застосунки з Flipper Apps Catalog — наприклад,
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) і
[Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse) (гіроскопічна миша для комп'ютера).

::: tip Unleashed
Рушій JavaScript в Unleashed містить модуль `vgm` (можливість JS `vgm`): `getPitch()`, `getRoll()`, `getYaw()` і
`deltaYaw(angle, timeout)` зчитують орієнтацію модуля зі скрипта й повертають `undefined`, якщо VGM не
підключений. Про застосунки на JavaScript див. розділ [Розробка](/ua/dev/).
:::

## Оновлення прошивки модуля

Оновлення встановлюються застосунком **Video Game Module Tool** (із Flipper Apps Catalog). Його меню:

- `Install Official Firmware` — найновіша офіційна прошивка модуля, що постачається разом із застосунком;
- `Install Firmware from File` — власний файл `.uf2` із SD-картки.

Щоб оновити:

1. Встановіть (або **спочатку оновіть**) Video Game Module Tool: у мобільному застосунку Flipper перейдіть до
   **Apps**, знайдіть *Video Game Module Tool* і натисніть **INSTALL** / **UPDATE**. Нова прошивка модуля
   надходить разом із новою версією застосунку, тому завжди оновлюйте застосунок перед оновленням модуля.
2. Підключіть модуль до Flipper.
3. Відкрийте `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Виберіть `Install Official Firmware` і підтвердьте через `Install` (<kbd>→</kbd>).
5. Дочекайтеся повідомлення **Video Game Module Updated**.

## Власна прошивка

Модуль може працювати з вашою власною прошивкою для RP2040.

### З Flipper Zero

Дає змогу тримати кілька прошивок модуля на SD-картці й перемикатися між ними без комп'ютера.

1. Скопіюйте файл `.uf2` на SD-картку Flipper (наприклад, через [qFlipper](/ua/mobile/qflipper):
   `File manager → SD Card`, створіть теку, завантажте файл).
2. Підключіть модуль і відкрийте
   `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Виберіть файл і підтвердьте через `Install` (<kbd>→</kbd>). Дочекайтеся **Video Game Module Updated**.

::: warning Обмеження UF2 під час встановлення через Flipper
- Блоки не для флеш-пам'яті не підтримуються.
- Корисне навантаження блоку мусить мати розмір рівно 256 байтів.
- Цільові адреси корисного навантаження мусять бути вирівняні по 256 байтів, без пропусків.
- Файлові контейнери та теги розширень не підтримуються.
:::

### З комп'ютера

1. Відключіть модуль від Flipper і від USB.
2. Затисніть скріпкою кнопку **BOOT** на модулі.
3. Підключіть модуль до комп'ютера кабелем USB-C. Він змонтується як USB-накопичувач з іменем **RPI-RP2**.
   Відпустіть **BOOT**.
4. Перетягніть файл `.uf2` на **RPI-RP2**. Модуль перезавантажиться й сам від'єднається.

## Подробиці про апаратну частину (для самостійного використання)

### GPIO RP2040

- GPIO **8–15** і **18–20** використовуються для відеовиходу й на рознімання не виведені.
- GPIO **0–7, 16, 17, 21, 22, 26–28** виведені на рознімання (як у Raspberry Pi Pico). GPIO **2–7** також
  підключені до датчика руху.
- GPIO **23–25 і 29** (які в Pico використовуються внутрішньо) на VGM вільні й виведені на 14-контактну гребінку.

![Розпіновка 14-контактної гребінки Video Game Module](/img/remote/b030c6a0375c6254.png)

![Розпіновки Video Game Module і Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Периферія, доступна RP2040

- **Video Out:** відео й звук на телевізор/монітор, а також обмін даними через
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** USB-пристрій або хост (без USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **Гребінка GPIO:** 11 пінів GPIO із захистом від електростатичних розрядів.
- **Рознімання до Flipper Zero:** піни 13 і 14 Flipper повністю функційні; піни 2–7 з обмеженою функційністю
  (спільні з IMU). Із захистом від електростатичних розрядів.
- **RGB-світлодіод**, керований із GPIO RP2040.

### Живлення

- 5 В через USB-C у самостійному режимі;
- 3,3 В (пін 9) або 5 В (пін 1) від Flipper.

Живлення одночасно від USB-C і від Flipper безпечне і для модуля, і для обох джерел.

Схеми, складальні креслення плати та PDF-файли розпіновок є на офіційній сторінці
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Пов'язані сторінки

- [Модулі розширення](/ua/gpio/expansion-modules)
- [Розпіновка GPIO](/ua/gpio/pinout)
- [Зовнішні модулі](/ua/gpio/external-modules)
