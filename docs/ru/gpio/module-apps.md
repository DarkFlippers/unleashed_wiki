---
title: Модули и приложения для них
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Модули и приложения для них

Что можно подключить к GPIO и какое приложение этим управляет. Сначала перечислены модули, у которых есть
отдельная страница; дальше — приложения из паков с ссылкой на исходники и README.

Колонка **Пак** говорит, есть ли приложение на вашем Flipper:

| Пак | В какой сборке есть |
|---|---|
| Base | в сборке `e` и в сборке без суффикса |
| Extra | только в сборке `e` |

В сборке `c` приложений нет. Любой пак можно добавить вручную из
[релизов паков](https://github.com/xMasterX/all-the-plugins/releases/latest) — см. [Каталог приложений](/ru/apps/catalog).

::: warning
Это приложения от сообщества. Состав паков меняется от релиза к релизу, и приложение может выпасть, если перестанет
собираться с текущим API. Тег сборки паков указан в начале каждого чейнджлога.
:::

::: tip Перед тем как что-то подключать
Посмотрите [Распиновка GPIO](/ru/gpio/pinout) — какое напряжение и ток выдерживает пин, и
[Внешние модули](/ru/gpio/external-modules#pin-conflicts) — какие пины уже заняты. Два модуля на одной шине
одновременно работать не будут.
:::

## Модули, у которых есть отдельная страница {#covered}

| Модуль | Чем управляется | Страница |
|---|---|---|
| Внешний CC1101 (Sub-GHz) | встроенное приложение Sub-GHz | [Внешний CC1101](/ru/subghz/external-cc1101) |
| Платы Wi-Fi на ESP32 / ESP8266 | приложения ниже плюс прошивка платы | [ESP32 и Wi-Fi](/ru/gpio/esp32) |
| Wi-Fi Developer Board | отладчик и логи | [Dev board](/ru/gpio/devboard) |
| nRF24L01 | приложения ниже | [NRF24](/ru/gpio/nrf24) |
| SIM800 GSM | встроенное приложение SIM800 | [SIM800](/ru/gpio/sim800) |
| GPS (NMEA) | приложения ниже | [GPS](/ru/gpio/gps) |
| Video Game Module | прошивка плюс приложения ниже | [Video Game Module](/ru/gpio/video-game-module) |
| Модули расширения | `Settings → Expansion Modules` | [Модули расширения](/ru/gpio/expansion-modules) |

## Wi-Fi и платы на ESP {#esp}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Интерфейс для прошивки Marauder: сканирование Wi-Fi и BLE, захват пакетов, вардрайвинг |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Список Wi-Fi сетей рядом, для прошивки Scanner на ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Интерфейс для прошивки DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Картинка с ESP32-CAM на экране Flipper и съёмка фото |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Второе приложение для ESP32-CAM: живое видео и фото |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Интерфейс для прошивки Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Поднимает на ESP32 точку доступа с captive-порталом |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Для прошивки Deauther v2 от @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Прошивает плату ESP прямо с Flipper, по UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Запускает веб-хук IFTTT через ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Картирование Wi-Fi сетей с ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Показывает лицо и статус Pwnagotchi на экране Flipper, по UART |

## 2,4 ГГц: nRF24L01 {#nrf}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Собирает адреса беспроводных клавиатур для Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Вставляет нажатия клавиш в уязвимый приёмник беспроводной клавиатуры или мыши |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Универсальная утилита для nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Ищет и декодирует пакеты nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Показывает, какие каналы 2,4 ГГц заняты |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Читает и пишет именованные поля устройства nRF24 по файлу конфигурации |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Другая сборка Sniffer выше |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Другая сборка Mouse Jacker выше |

## Датчики {#sensors}

| Приложение | Пак | Что делает |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: датчики температуры, влажности и давления (DHT, DS18B20, BMP/BME и другие) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Экспонометр для фотографии, BH1750 по I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Расстояние с УЗ-датчика HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Расстояние с УЗ-датчика Parallax PING))) (3 провода) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Движение с доплеровского радара RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 с датчика MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Частицы в воздухе с датчика Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Алкотестер на датчике MQ-3, с калибровкой нуля |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Напряжение и ток с датчиков TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Вариометр для парапланеризма и походов, датчик давления BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Читает двухосевой акселерометр Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Шагомер на том же модуле Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Мышь на датчике движения BMI160 или LSM6DS |

## Радиация {#rad}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Счёт с трубки Гейгера J305 на внешней плате |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Кости, брошенные той же гейгеровской платой; без платы не работает |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Работает с модулем RadSens |

## Дисплеи, светодиоды и радио {#disp}

| Приложение | Пак | Что делает |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Управляет семисегментным индикатором с пинов GPIO |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Диагностика OLED-дисплеев SSD1306 по I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Проверяет адресные светодиоды WS2812B |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Управляет FM-модулем TEA5767 |

## Чипы памяти {#mem}

| Приложение | Пак | Что делает |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Читает и пишет SPI-флеш серии 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Управление блокировкой SD-карт по SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | EEPROM 24Cxx по I2C: чтение, запись, стирание, дамп и восстановление |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Читает и пишет EEPROM внутри некоторых кофемашин |

## Отладка и программаторы {#probe}

| Приложение | Пак | Что делает |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Превращает Flipper в отладчик CMSIS-DAP для ARM |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | Отладчик ARM Single Wire Debug |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Эмулирует FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Прошивает микроконтроллеры AVR по ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Отладчик и программатор для WCH CH32V003 |

## Шины, сеть и терминалы {#bus}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Сканирует шину I2C, читает и пишет регистры |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Терминал для общения с устройством по SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Терминал для любого устройства на UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Инструменты для шины CAN, нужна плата CAN |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Набор инструментов для CAN-шины Tesla, нужна та же плата CAN |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Проверяет Ethernet-подключение через модуль W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | LAN-тестер на том же модуле: ARP, ping, DHCP, скан портов, SNMP и другое |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Терминал для модуля LoRa |

## Измерения и сигналы {#meas}

| Приложение | Пак | Что делает |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper как Openbench Logic Sniffer, для PulseView на компьютере |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Осциллограф на пине 16 (PC0), от 0 до 2,5 В |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Генерирует цифровые сигналы на пинах GPIO |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | ШИМ для сервопривода на пине A7, режимы Manual, Center и Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Второй тестер сервоприводов, тоже на пине A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Интервалометр: спускает затвор камеры через пины GPIO |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Декодирует длинноволновые сигналы времени (DCF77 и подобные) |

## СКУД, магнитная полоса и UHF RFID {#access}

| Приложение | Пак | Что делает |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Читает форматы Wiegand от W4 до W48 со считывателя или клавиатуры, сохраняет и воспроизводит |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Передаёт данные магнитной полосы по воздуху через катушку |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID через модуль YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Для считывателей M6E Nano, M7E Hecto и YRM1000; читает много меток сразу |

## GPS {#gps}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Координаты с любого GPS-модуля NMEA на UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Показывает и логирует данные GPS-модулей u-blox по I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Трекер NMEA с навигацией по точкам |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Файловый браузер, который сортирует файлы по расстоянию от вас |

## Игровое и ретро-железо {#game}

| Приложение | Пак | Что делает |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Ставит и обновляет прошивку Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Воздушная мышь на датчике движения Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Вывод картинки игры и передача нажатий через модуль |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Обмен покемонами с Game Boy, поколения I и II, не японские версии |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper как джойстик ColecoVision, с модулем RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Разбирает протокол контроллеров-расширений Wii |

## Без модуля: только пины {#bare}

| Приложение | Пак | Что делает |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Визуальное управление пинами общего назначения |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Показывает состояние каждого пина на экране |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Второй просмотрщик состояния пинов |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Пищит, когда провод цел |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Подаёт 3,3 В на пин 7 (C3) и оставляет его включённым после выхода |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Открывает электронные сейфы Sentry Safe и Master Lock через два провода |

## Смотрите также {#related}

- [Распиновка GPIO](/ru/gpio/pinout) — что умеет каждый пин и какой ток он может дать
- [Внешние модули](/ru/gpio/external-modules) — шины, конфликты пинов и внешний ИК
- [Приложение GPIO](/ru/gpio/gpio-app) — встроенное управление пинами, мост UART и команда `i2c`
- [Каталог приложений](/ru/apps/catalog) — паки и как поставить пак вручную
- [Приложения на SD-карте](/ru/apps/sd-card-apps) — установка одного `.fap` и соответствие версий API
