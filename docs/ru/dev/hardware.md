---
title: Железо
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Железо

Технические характеристики Flipper Zero и где найти его схемы, чертежи и 3D-модели — пригодится при разработке
внешних модулей и корпусов, а также для низкоуровневой отладки.

![Обзор характеристик Flipper Zero](/img/remote/629725f9f16a5946.png)

## Характеристики

### Корпус, размеры и вес

| | |
|---|---|
| Материалы | PC, ABS, PMMA |
| Высота | 40,1 мм (1,58 дюйма) |
| Ширина | 100,3 мм (3,95 дюйма) |
| Толщина | 25,6 мм (1,01 дюйма) |
| Вес | 102 г (3,6 унции) |

### Дисплей

| | |
|---|---|
| Тип | Монохромный LCD |
| Разрешение | 128×64 пикселя |
| Контроллер | ST7567 |
| Интерфейс | SPI |
| Диагональ | 1,4″ |

### Микроконтроллер

| | |
|---|---|
| Модель | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Прикладное ядро | Arm Cortex-M4, 32 бит, 64 МГц |
| Радиоядро | Arm Cortex-M0+, 32 бит, 32 МГц |
| Радио | Bluetooth LE 5.4, 802.15.4, проприетарные протоколы |
| Flash | 1024 КБ (общие для приложений и радио) |
| SRAM | 256 КБ (общие для приложений и радио) |

### Sub-1 GHz

| | |
|---|---|
| Трансивер | [CC1101](https://www.ti.com/product/CC1101) |
| Мощность передачи | до −20 дБм (по официальным характеристикам) |
| Диапазоны | 315 МГц, 433 МГц, 868 МГц, 915 МГц (зависит от региона) |

CC1101 перестраивается в диапазонах 299,999755–348 МГц, 386,999938–464 МГц и 778,999847–928 МГц.

::: tip Unleashed
Unleashed снимает региональные ограничения на передачу и добавляет частоты (в стандартный диапазон добавлены 350 МГц
и 467 МГц). Диапазон можно расширить до 281–361, 378–481 и 749–962 МГц через файл
`subghz/assets/dangerous_settings` — это выходит за спецификацию CC1101 и **может повредить железо**
([опасные настройки](/ru/start/dangerous-settings)). Также поддерживается
[внешний модуль CC1101](/ru/subghz/external-cc1101). Соблюдайте законодательство о радиочастотах в своей стране.
:::

### NFC

| | |
|---|---|
| Трансивер | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Частота | 13,56 МГц |
| Карты | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® и др.; FeliCa™; HID iClass (Picopass); протоколы NFC Forum |

### RFID 125 кГц

| | |
|---|---|
| Частота | 125 кГц |
| Модуляция | AM, OOK |
| Кодирование | ASK, PSK |
| Карты (официальный список) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Протоколы, которые реально поддерживает прошивка Unleashed, — см. [RFID → Чтение](/ru/rfid/read).

### Инфракрасный порт

| | |
|---|---|
| Длина волны приёма | 950 нм (±100 нм) |
| Несущая приёма | 38 кГц (±5%) |
| Длина волны передачи | 940 нм |
| Несущая передачи | 0–2 МГц |
| Мощность передачи | 300 мВт |
| Протоколы | Семейство NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 линий ввода-вывода на внешних разъёмах с шагом 2,54 мм
- Уровни 3,3 В CMOS
- Входы толерантны к 5 В (см. ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- До 20 мА на цифровой пин

Распиновка: [GPIO pinout](/ru/gpio/pinout).

### Аккумулятор и питание

| | |
|---|---|
| Тип | Литий-полимерный (LiPo) |
| Ёмкость | 2100 мА·ч |
| Время работы | До 28 дней |
| Рабочая температура | 0…40 °C |

### Карта microSD

| | |
|---|---|
| Максимальный объём | До 256 ГБ |
| Рекомендуемый объём | 2–32 ГБ |
| Интерфейс | SPI |
| Скорость чтения/записи | До 5 Мбит/с |

Флиппер поставляется без microSD-карты — купите её отдельно. См. [SD-карта](/ru/start/sd-card).

### USB

| | |
|---|---|
| Разъём | Type-C |
| Стандарт | USB 2.0 |
| Скорость передачи | 12 Мбит/с |
| Максимальный ток зарядки | 1 А |

### Bluetooth LE 5.4

| | |
|---|---|
| Мощность передачи | до 4 дБм |
| Чувствительность приёма | −96 дБм |
| Скорость | 2 Мбит/с |

### Пищалка и вибромотор

| | |
|---|---|
| Частота пищалки | 100–2500 Гц |
| Громкость пищалки | 87 дБ |
| Тип пищалки | Таблеточный (coin) |
| Сила вибрации | 30 Н |
| Скорость вибромотора | 13500 об/мин |

### Комплектация

Flipper Zero, кабель USB-C — USB-A, документация, наклейка.

## Схемы

Схемы всех плат Flipper Zero опубликованы Flipper Devices «в образовательных целях» — пригодятся для разработки
модулей и низкоуровневой отладки. Интерактивные просмотрщики Altium и PDF для скачивания — на официальной странице:
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Платы Flipper Zero](/img/remote/db285947a71be613.png)

| Плата | Доступные документы |
|---|---|
| **Main PCB** (ред. 12.1.F7B9C6) | Сборочный чертёж; обзор основных блоков; Power; Peripherals; MCU STM32WB55; LCD display; Sub-1 GHz CC1101; Buttons |
| **iButton PCB** (ред. 12.F7B9C6) — на ней же пьезодинамик и ИК | Сборочный чертёж; схема iButton |
| **NFC RFID PCB** (ред. 12.F7B9C6) — RFID 125 кГц и NFC | Сборочный чертёж; обзор блоков NFC; NFC; Power and vibro; RFID |
| **Antenna PCB** | Изображение платы |

::: info
В ревизии 13.F7B9C6 платы iButton изменились посадочные места pogo-пинов: вместо SMD-пинов стоят выводные. Диаметры
посадочных мест те же, что в 12.F7B9C6.
:::

## Чертежи и 3D-модели

Все файлы можно скачать на официальных страницах:

| Что | Файлы | Страница |
|---|---|---|
| Корпус Flipper Zero | 2D-чертёж (`.pdf`, `.dwg`), 3D-модель (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Обычный внешний модуль | Чертёж (`.pdf`), 3D-модель платы (`.stp`, без деталей и в сборе), контур платы (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Малый внешний модуль | Тот же набор, что и для обычного | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Чертёж (`.pdf`, `.dwg.zip`), 3D-модель (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Чертёж Flipper Zero](/img/remote/c91e01d61829df8e.png)

Чертежи внешних модулей задают рекомендуемую геометрию плат, которые вставляются в GPIO-разъём, — начинайте с них,
если проектируете свой модуль (см. также [Модули расширения](/ru/gpio/expansion-modules)).

## Платы разработчика

### Wi-Fi Developer Board

Построена на **ESP32-S2-WROVER-N4R2**. Опубликованы: вид платы, сборочный чертёж (`Wi-Fi Module_V1_Assembly.pdf`),
схема ESP32-S2, схема питания, схема разъёмов —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Использование: [Dev Board](/ru/gpio/devboard), [Отладка приложений](/ru/dev/debugging).

### ST-Link V3 Developer Board

Для продвинутых разработчиков, которым нужна внутрисхемная отладка. Основана на модуле
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) и отличается от него только
форм-фактором и удобством подключения.

- ST-Link V3 Mods для прошивки и внутрисхемной отладки.
- Встроенный UART-USB, подключённый к UART Флиппера (пины GPIO 13 и 14).
- Неиспользуемые пины Flipper Zero и ST-Link выведены наружу для отладки и прототипирования.

Проект Altium Designer: [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Схема и BOM: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Для обновления и разработки она не нужна
Обновление прошивки, разработка и загрузка своей прошивки работают по обычному USB. Отладочная плата нужна только
для отладки прошивки во время работы (GDB, OpenOCD, …).
:::

## Связанные страницы

- [Распиновка GPIO](/ru/gpio/pinout)
- [Furi API](/ru/dev/furi-api) — блок-схема железа
- [Отладка приложений](/ru/dev/debugging)
- [OTA-обновления](/ru/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic и DESFire — зарегистрированные товарные знаки NXP B.V. FeliCa — товарный
знак Sony Corporation.
