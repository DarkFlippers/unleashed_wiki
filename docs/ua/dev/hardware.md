---
title: Апаратна частина
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Апаратна частина

Технічні характеристики Flipper Zero, а також де знайти його схеми, креслення та 3D-моделі — усе це потрібно,
якщо ви робите зовнішні модулі, корпуси або займаєтеся низькорівневим налагодженням.

![Огляд технічних характеристик Flipper Zero](/img/remote/629725f9f16a5946.png)

## Технічні характеристики

### Корпус, розміри та вага

| | |
|---|---|
| Матеріали | PC, ABS, PMMA |
| Висота | 40,1 мм (1,58 дюйма) |
| Ширина | 100,3 мм (3,95 дюйма) |
| Глибина | 25,6 мм (1,01 дюйма) |
| Вага | 102 г (3,6 унції) |

### Дисплей

| | |
|---|---|
| Тип | Монохромний LCD |
| Роздільна здатність | 128×64 пікселі |
| Контролер | ST7567 |
| Інтерфейс | SPI |
| Діагональ | 1,4″ |

### Мікроконтролер

| | |
|---|---|
| Модель | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Прикладне ядро | Arm Cortex-M4, 32-бітне, 64 МГц |
| Радіоядро | Arm Cortex-M0+, 32-бітне, 32 МГц |
| Радіо | Bluetooth LE 5.4, 802.15.4, власні протоколи |
| Флеш-пам’ять | 1024 КБ (спільна для прикладної частини та радіо) |
| SRAM | 256 КБ (спільна для прикладної частини та радіо) |

### Sub-1 GHz

| | |
|---|---|
| Трансивер | [CC1101](https://www.ti.com/product/CC1101) |
| Потужність передавання | не більше −20 дБм (за офіційними характеристиками) |
| Частотні діапазони | 315 МГц, 433 МГц, 868 МГц, 915 МГц (залежно від регіону) |

CC1101 налаштовується в діапазонах 299,999755–348 МГц, 386,999938–464 МГц і 778,999847–928 МГц.

::: tip Unleashed
Unleashed знімає регіональні обмеження на передавання й додає додаткові частоти (350 МГц і 467 МГц додані до типового
діапазону). Діапазон можна розширити й далі — до 281–361, 378–481 і 749–962 МГц — через файл
`subghz/assets/dangerous_settings`. Це вже поза характеристиками CC1101 і **може пошкодити апаратну частину**
([небезпечні налаштування](/ua/start/dangerous-settings)). Також підтримується
[зовнішній модуль CC1101](/ua/subghz/external-cc1101). Дотримуйтеся радіочастотного законодавства своєї країни.
:::

### NFC

| | |
|---|---|
| Трансивер | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Частота | 13,56 МГц |
| Карти | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® тощо; FeliCa™; HID iClass (Picopass); протоколи NFC Forum |

### 125 кГц RFID

| | |
|---|---|
| Частота | 125 кГц |
| Модуляція | AM, OOK |
| Кодування | ASK, PSK |
| Карти (офіційний список) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Які протоколи насправді підтримує прошивка Unleashed, описано на сторінці [RFID → Читання](/ua/rfid/read).

### Інфрачервоний порт

| | |
|---|---|
| Довжина хвилі приймання | 950 нм (±100 нм) |
| Несуча приймання | 38 кГц (±5 %) |
| Довжина хвилі передавання | 940 нм |
| Несуча передавання | 0–2 МГц |
| Потужність передавання | 300 мВт |
| Протоколи | родина NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 виводів введення/виведення на зовнішніх гребінках із кроком 2,54 мм
- Рівні 3,3 В CMOS
- Входи витримують 5 В (див. ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- До 20 мА на кожен цифровий вивід

Карта виводів: [розпіновка GPIO](/ua/gpio/pinout).

### Акумулятор і живлення

| | |
|---|---|
| Тип | Літій-полімерний (LiPo) |
| Ємність | 2100 мА·год |
| Час роботи | до 28 днів |
| Робоча температура | 0…40 °C (32…104 °F) |

### Картка microSD

| | |
|---|---|
| Максимальний обсяг | до 256 ГБ |
| Рекомендований обсяг | 2–32 ГБ |
| Інтерфейс | SPI |
| Швидкість читання/запису | до 5 Мбіт/с |

Картка microSD у комплект не входить — її потрібно купити окремо. Див. [Картка microSD](/ua/start/sd-card).

### USB

| | |
|---|---|
| Роз’єм | Type-C |
| Стандарт | USB 2.0 |
| Швидкість передавання даних | 12 Мбіт/с |
| Максимальний струм заряджання | 1 А |

### Bluetooth LE 5.4

| | |
|---|---|
| Потужність передавання | не більше 4 дБм |
| Чутливість приймання | −96 дБм |
| Швидкість передавання даних | 2 Мбіт/с |

### Динамік і вібрація

| | |
|---|---|
| Частота динаміка | 100–2500 Гц |
| Звуковий тиск | 87 дБ |
| Тип динаміка | монетний (coin) |
| Сила вібрації | 30 Н |
| Обороти вібромотора | 13500 об/хв |

### Комплектація

Flipper Zero, кабель USB-C — USB-A, документація, наліпка.

## Схеми

Схеми всіх друкованих плат Flipper Zero опубліковані Flipper Devices «в освітніх цілях» — вони корисні для
розробки апаратних модулів і низькорівневого налагодження. Інтерактивні переглядачі Altium і файли PDF для
завантаження лежать на офіційній сторінці:
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Друковані плати Flipper Zero](/img/remote/db285947a71be613.png)

| Плата | Доступні документи |
|---|---|
| **Main PCB** (рев. 12.1.F7B9C6) | Збірне креслення; огляд основних блоків; Power; Peripherals; MCU STM32WB55; LCD display; Sub-1 GHz CC1101; Buttons |
| **iButton PCB** (рев. 12.F7B9C6) — на ній також п’єзодинамік та ІЧ-порт | Збірне креслення; схема iButton |
| **NFC RFID PCB** (рев. 12.F7B9C6) — 125 кГц RFID і NFC | Збірне креслення; огляд блоків NFC; NFC; Power and vibro; RFID |
| **Antenna PCB** | Зображення плати |

::: info
У ревізії 13.F7B9C6 плати iButton PCB змінилися посадкові місця pogo-пінів: замість SMD-варіанта використано
pogo-піни з монтажем в отвори. Діаметри посадкових місць такі самі, як у 12.F7B9C6.
:::

## Креслення та 3D-моделі

Усі файли можна завантажити з офіційних сторінок:

| Що | Файли | Сторінка |
|---|---|---|
| Корпус Flipper Zero | 2D-креслення (`.pdf`, `.dwg`), 3D-модель (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Звичайний зовнішній модуль | Креслення (`.pdf`), 3D-модель плати (`.stp`, окремо й у зборі), контур плати (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Малий зовнішній модуль | Той самий набір, що й для звичайного модуля | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Креслення (`.pdf`, `.dwg.zip`), 3D-модель (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Креслення Flipper Zero](/img/remote/c91e01d61829df8e.png)

Креслення зовнішніх модулів задають рекомендовану геометрію плат, які вставляються в гребінку GPIO, — починайте
з них, якщо проєктуєте власний модуль (див. також [Модулі розширення](/ua/gpio/expansion-modules)).

## Плати для розробників

### Wi-Fi Developer Board

Побудована на **ESP32-S2-WROVER-N4R2**. Опубліковані документи: вигляд плати, збірне креслення
(`Wi-Fi Module_V1_Assembly.pdf`), схема ESP32-S2, схема живлення, схема роз’ємів —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Як користуватися: [Dev Board](/ua/gpio/devboard), [Налагодження застосунків](/ua/dev/debugging).

### ST-Link V3 Developer Board {#st-link-v3-developer-board}

Для досвідчених розробників, яким потрібне внутрішньосхемне налагодження. Плата побудована на модулі
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) і відрізняється від нього лише
форм-фактором та зручністю під’єднання.

- ST-Link V3 Mods для прошивання та внутрішньосхемного налагодження.
- Вбудований перетворювач UART — USB, під’єднаний до UART Flipper (виводи GPIO 13 і 14).
- Невикористані виводи Flipper Zero та ST-Link виведені назовні для налагодження й прототипування.

Проєкт Altium Designer: [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Схема та BOM: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Для оновлення та розробки вона не потрібна
Оновлення прошивки, розробка й завантаження власної прошивки працюють через звичайний USB. Плата для
налагодження потрібна лише для того, щоб налагоджувати прошивку під час її роботи (GDB, OpenOCD, …).
:::

## Пов’язані сторінки

- [Розпіновка GPIO](/ua/gpio/pinout)
- [Furi API](/ua/dev/furi-api) — блок-схема апаратної частини
- [Налагодження застосунків](/ua/dev/debugging)
- [OTA-оновлення](/ua/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic і DESFire — зареєстровані торгові марки NXP B.V. FeliCa — торгова марка
Sony Corporation.
