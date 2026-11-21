---
title: Модулі та застосунки для них
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Модулі та застосунки для них

Що можна підключити до GPIO і який застосунок цим керує. Спершу перелічені модулі, які мають окрему сторінку;
далі — застосунки з паків із посиланням на джерела та README.

Колонка **Пак** каже, чи застосунок уже є на вашому Flipper:

| Пак | У якій збірці є |
|---|---|
| Base | у збірці `e` та у збірці без суфікса |
| Extra | лише у збірці `e` |

У збірці `c` застосунків немає. Будь-який пак можна додати вручну з
[релізів паків](https://github.com/xMasterX/all-the-plugins/releases/latest) — див. [Каталог застосунків](/ua/apps/catalog).

::: warning
Це застосунки від спільноти. Склад паків змінюється від релізу до релізу, і застосунок може зникнути, якщо
перестане збиратися з поточним API. Тег збірки паків указано на початку кожного чейнджлогу.
:::

::: tip Перед тим як щось підключати
Подивіться [Розпіновка GPIO](/ua/gpio/pinout) — яку напругу і струм витримує пін, та
[Зовнішні модулі](/ua/gpio/external-modules#pin-conflicts) — які піни вже зайняті. Два модулі на одній шині
одночасно не працюватимуть.
:::

## Модулі, які мають окрему сторінку {#covered}

| Модуль | Чим керується | Сторінка |
|---|---|---|
| Зовнішній CC1101 (Sub-GHz) | вбудований застосунок Sub-GHz | [Зовнішній CC1101](/ua/subghz/external-cc1101) |
| Плати Wi-Fi на ESP32 / ESP8266 | застосунки нижче плюс прошивка плати | [ESP32 та Wi-Fi](/ua/gpio/esp32) |
| Wi-Fi Developer Board | відладчик і логи | [Dev board](/ua/gpio/devboard) |
| nRF24L01 | застосунки нижче | [NRF24](/ua/gpio/nrf24) |
| SIM800 GSM | вбудований застосунок SIM800 | [SIM800](/ua/gpio/sim800) |
| GPS (NMEA) | застосунки нижче | [GPS](/ua/gpio/gps) |
| Video Game Module | прошивка плюс застосунки нижче | [Video Game Module](/ua/gpio/video-game-module) |
| Модулі розширення | `Settings → Expansion Modules` | [Модулі розширення](/ua/gpio/expansion-modules) |

## Wi-Fi і плати на ESP {#esp}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Інтерфейс для прошивки Marauder: сканування Wi-Fi і BLE, захоплення пакетів, вардрайвінг |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Список Wi-Fi мереж поблизу, для прошивки Scanner на ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Інтерфейс для прошивки DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Картинка з ESP32-CAM на екрані Flipper і зйомка фото |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Другий застосунок для ESP32-CAM: живе відео та фото |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Інтерфейс для прошивки Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Піднімає на ESP32 точку доступу з captive-порталом |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Для прошивки Deauther v2 від @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Прошиває плату ESP просто з Flipper, через UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Запускає вебхук IFTTT через ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Картування Wi-Fi мереж з ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Показує обличчя та статус Pwnagotchi на екрані Flipper, через UART |

## 2,4 ГГц: nRF24L01 {#nrf}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Збирає адреси безпровідних клавіатур для Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Вставляє натискання клавіш у вразливий приймач безпровідної клавіатури або мишки |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Універсальна утиліта для nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Шукає та декодує пакети nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Показує, які канали 2,4 ГГц зайняті |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Читає і пише іменовані поля пристрою nRF24 за файлом конфігурації |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Інша збірка Sniffer вище |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Інша збірка Mouse Jacker вище |

## Датчики {#sensors}

| Застосунок | Пак | Що робить |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: датчики температури, вологості та тиску (DHT, DS18B20, BMP/BME та інші) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Експонометр для фотографії, BH1750 через I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Відстань з УЗ-датчика HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Відстань з УЗ-датчика Parallax PING))) (3 дроти) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Рух з доплерівського радара RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 з датчика MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Частки в повітрі з датчика Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Алкотестер на датчику MQ-3, з калібруванням нуля |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Напруга і струм з датчиків TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Варіометр для парапланеризму та походів, датчик тиску BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Читає двовісний акселерометр Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Крокомір на тому ж модулі Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Мишка на датчику руху BMI160 або LSM6DS |

## Радіація {#rad}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Лік з трубки Гейгера J305 на зовнішній платі |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Кості, кинуті тією ж гейгерівською платою; без плати не працює |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Працює з модулем RadSens |

## Дисплеї, світлодіоди та радіо {#disp}

| Застосунок | Пак | Що робить |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Керує семисегментним індикатором з пінів GPIO |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Діагностика OLED-дисплеїв SSD1306 через I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Перевіряє адресні світлодіоди WS2812B |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Керує FM-модулем TEA5767 |

## Чипи пам’яті {#mem}

| Застосунок | Пак | Що робить |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Читає і пише SPI-флеш серії 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Керування блокуванням SD-карт через SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | EEPROM 24Cxx через I2C: читання, запис, стирання, дамп і відновлення |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Читає і пише EEPROM усередині деяких кавомашин |

## Відладка та програматори {#probe}

| Застосунок | Пак | Що робить |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Перетворює Flipper на відладчик CMSIS-DAP для ARM |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | Відладчик ARM Single Wire Debug |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Емулює FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Прошиває мікроконтролери AVR через ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Відладчик і програматор для WCH CH32V003 |

## Шини, мережа та термінали {#bus}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Сканує шину I2C, читає і пише регістри |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Термінал для спілкування з пристроєм через SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Термінал для будь-якого пристрою на UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Інструменти для шини CAN, потрібна плата CAN |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Набір інструментів для CAN-шини Tesla, потрібна та ж плата CAN |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Перевіряє Ethernet-підключення через модуль W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | LAN-тестер на тому ж модулі: ARP, ping, DHCP, скан портів, SNMP та інше |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Термінал для модуля LoRa |

## Вимірювання та сигнали {#meas}

| Застосунок | Пак | Що робить |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper як Openbench Logic Sniffer, для PulseView на комп’ютері |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Осцилограф на піні 16 (PC0), від 0 до 2,5 В |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Генерує цифрові сигнали на пінах GPIO |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | ШІМ для сервоприводу на піні A7, режими Manual, Center і Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Другий тестер сервоприводів, теж на піні A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Інтервалометр: спускає затвор камери через піни GPIO |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Декодує довгохвильові сигнали часу (DCF77 і подібні) |

## СКУД, магнітна смуга та UHF RFID {#access}

| Застосунок | Пак | Що робить |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Читає формати Wiegand від W4 до W48 зі зчитувача або клавіатури, зберігає та відтворює |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Передає дані магнітної смуги повітрям через котушку |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID через модуль YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Для зчитувачів M6E Nano, M7E Hecto та YRM1000; читає багато міток одразу |

## GPS {#gps}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Координати з будь-якого GPS-модуля NMEA на UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Показує та логує дані GPS-модулів u-blox через I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Трекер NMEA з навігацією за точками |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Файловий браузер, який сортує файли за відстанню від вас |

## Ігрове та ретро-залізо {#game}

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Встановлює та оновлює прошивку Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Повітряна мишка на датчику руху Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Вивід картинки гри та передача натискань через модуль |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Обмін покемонами з Game Boy, покоління I та II, неяпонські версії |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper як джойстик ColecoVision, з модулем RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Розбирає протокол контролерів-розширень Wii |

## Без модуля: лише піни {#bare}

| Застосунок | Пак | Що робить |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Візуальне керування пінами загального призначення |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Показує стан кожного піна на екрані |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Другий переглядач стану пінів |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Пищить, коли дріт цілий |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Подає 3,3 В на пін 7 (C3) і залишає його увімкненим після виходу |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Відкриває електронні сейфи Sentry Safe і Master Lock через два дроти |

## Дивіться також {#related}

- [Розпіновка GPIO](/ua/gpio/pinout) — що вміє кожен пін і який струм він може дати
- [Зовнішні модулі](/ua/gpio/external-modules) — шини, конфлікти пінів і зовнішній ІЧ
- [Застосунок GPIO](/ua/gpio/gpio-app) — вбудоване керування пінами, мост UART і команда `i2c`
- [Каталог застосунків](/ua/apps/catalog) — паки і як поставити пак вручну
- [Застосунки на SD-карті](/ua/apps/sd-card-apps) — встановлення одного `.fap` і відповідність версій API
