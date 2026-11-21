---
title: Module und ihre Apps
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Module und ihre Apps

Was sich an den GPIO-Header anschließen lässt und welche App es ansteuert. Zuerst die Module mit eigener Seite,
danach die Community-Apps aus den App-Paketen, jeweils mit Link auf Quellcode und README.

Die Spalte **Paket** sagt, ob die App schon auf dem Flipper ist:

| Paket | In welchem Build |
|---|---|
| Base | im `e`-Build und im Build ohne Suffix |
| Extra | nur im `e`-Build |

Ein `c`-Build enthält keine Apps. Beide Pakete lassen sich von Hand aus den
[Paket-Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) nachinstallieren — siehe
[App-Katalog](/de/apps/catalog).

::: warning
Das sind Community-Apps. Der Inhalt der Pakete ändert sich von Release zu Release, und eine App fällt heraus, wenn
sie mit der aktuellen API nicht mehr baut. Der Build-Tag der Pakete steht oben in jedem Changelog.
:::

::: tip Bevor du etwas anschließt
In [GPIO-Pinbelegung](/de/gpio/pinout) steht, welche Spannung und welchen Strom ein Pin verträgt, und in
[Externe Module](/de/gpio/external-modules#pin-conflicts), welche Pins schon belegt sind. Zwei Module am selben Bus
funktionieren nicht gleichzeitig.
:::

## Module mit eigener Seite {#covered}

| Modul | Angesteuert von | Seite |
|---|---|---|
| Externes CC1101 (Sub-GHz) | der eingebauten Sub-GHz-App | [Externes CC1101](/de/subghz/external-cc1101) |
| ESP32- / ESP8266-WLAN-Boards | den Apps unten plus Board-Firmware | [ESP32 & WLAN](/de/gpio/esp32) |
| Wi-Fi Developer Board | Debug-Probe und Logs | [Dev Board](/de/gpio/devboard) |
| nRF24L01 | den Apps unten | [NRF24](/de/gpio/nrf24) |
| SIM800 GSM | der eingebauten SIM800-App | [SIM800](/de/gpio/sim800) |
| GPS (NMEA) | den Apps unten | [GPS](/de/gpio/gps) |
| Video Game Module | Firmware plus den Apps unten | [Video Game Module](/de/gpio/video-game-module) |
| Erweiterungsmodule | `Settings → Expansion Modules` | [Erweiterungsmodule](/de/gpio/expansion-modules) |

## WLAN und ESP-Boards {#esp}

| App | Paket | Was sie macht |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Oberfläche für die Marauder-Firmware: WLAN- und BLE-Scan, Paketmitschnitt, Wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Listet WLANs in der Umgebung auf, für die Scanner-Firmware auf dem ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Oberfläche für die DSTIKE-Deauther-Firmware |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Live-Bild einer ESP32-CAM auf dem Flipper-Display, mit Fotoaufnahme |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Zweite ESP32-CAM-App: Live-Bild und Fotos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Oberfläche für die Ghost-ESP-Firmware |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Betreibt auf dem ESP32 einen Access Point mit Captive Portal |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Für die Deauther-v2-Firmware von @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flasht Firmware auf ein ESP-Board, direkt vom Flipper über UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Löst einen IFTTT-Webhook über einen ESP8266 aus |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | WLAN-Kartierung mit einem ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Zeigt Gesicht und Status eines Pwnagotchi auf dem Flipper, über UART |

## 2,4 GHz: nRF24L01 {#nrf}

| App | Paket | Was sie macht |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Sammelt Adressen von Funktastaturen für den Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Schiebt Tastendrücke in einen angreifbaren Funktastatur- oder Maus-Empfänger |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Allgemeines Werkzeug für den nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Sucht und dekodiert nRF24-Pakete |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Zeigt, welche 2,4-GHz-Kanäle belegt sind |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Liest und schreibt benannte Felder eines nRF24-Geräts nach einer Konfigurationsdatei |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Andere Variante des Sniffers oben |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Andere Variante des Mouse Jackers oben |

## Sensoren {#sensors}

| App | Paket | Was sie macht |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: Temperatur-, Feuchte- und Drucksensoren (DHT, DS18B20, BMP/BME und weitere) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Belichtungsmesser für die Fotografie, BH1750 über I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Abstand von einem Ultraschallsensor HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Abstand von einem Parallax-PING)))-Ultraschallsensor (3 Adern) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Bewegung von einem Doppler-Radarmodul RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 von einem MH-Z19-Sensor |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Feinstaub von einem Plantower-PMSx003-Sensor |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Alkoholtester mit MQ-3-Sensor, mit Nullpunktkalibrierung |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Spannung und Strom von TI-INAxxx-Sensoren |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variometer für Gleitschirm und Wandern, Drucksensor BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Liest einen zweiachsigen Beschleunigungssensor Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Schrittzähler auf demselben Memsic-2125-Modul |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Maus über einen Bewegungssensor BMI160 oder LSM6DS |

## Radioaktivität {#rad}

| App | Paket | Was sie macht |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Zählt mit einem J305-Geigerrohr auf einer externen Platine |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Würfelt mit derselben Geiger-Platine; ohne Platine läuft es nicht |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Arbeitet mit dem RadSens-Modul |

## Displays, LEDs und Radio {#disp}

| App | Paket | Was sie macht |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Steuert eine 7-Segment-Anzeige über die GPIO-Pins |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Diagnose für SSD1306-OLED-Displays am I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Prüft, ob WS2812B-LEDs funktionieren |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Steuert ein TEA5767-FM-Radiomodul |

## Speicherchips {#mem}

| App | Paket | Was sie macht |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Liest und schreibt SPI-Flash-Chips der 25er-Serie |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Sperrverwaltung für SD-Karten über SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | 24Cxx-EEPROM am I2C: lesen, schreiben, löschen, Dump und Restore |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Liest und schreibt das EEPROM in manchen Kaffeemaschinen |

## Debugging und Programmieren {#probe}

| App | Paket | Was sie macht |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Macht den Flipper zur CMSIS-DAP-Debug-Probe für ARM-Ziele |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | ARM-Single-Wire-Debug-Probe |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Emuliert einen FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Flasht AVR-Mikrocontroller über ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Debugger und Flasher für den WCH CH32V003 |

## Busse, Netzwerk und Terminals {#bus}

| App | Paket | Was sie macht |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Scannt den I2C-Bus und liest oder schreibt Register |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminal für ein Gerät am SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminal für jedes Gerät am UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Werkzeuge für den CAN-Bus, braucht ein CAN-Zusatzboard |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Werkzeugkasten für den CAN-Bus von Tesla, braucht dasselbe CAN-Board |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Prüft eine Ethernet-Verbindung über ein W5500-Modul |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | LAN-Tester auf demselben Modul: ARP, Ping, DHCP, Portscan, SNMP und mehr |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminal für ein LoRa-Modul |

## Messen und Signale {#meas}

| App | Paket | Was sie macht |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper als Openbench Logic Sniffer, für PulseView am PC |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Oszilloskop an Pin 16 (PC0), 0 bis 2,5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Erzeugt digitale Signale an den GPIO-Pins |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | Servo-PWM an Pin A7, Modi Manual, Center und Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Zweiter Servotester, ebenfalls an Pin A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervallauslöser: löst eine Kamera über die GPIO-Pins aus |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Dekodiert Langwellen-Zeitsignale (DCF77 und ähnliche) |

## Zutritt, Magnetstreifen und UHF-RFID {#access}

| App | Paket | Was sie macht |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Liest Wiegand-Formate von W4 bis W48 von Leser oder Tastatur, speichert und spielt sie zurück |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Überträgt Magnetstreifendaten drahtlos über eine Spule |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF-RFID über ein YRM100-Modul |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Für M6E Nano, M7E Hecto und YRM1000; liest viele Tags gleichzeitig |

## GPS {#gps}

| App | Paket | Was sie macht |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position von jedem NMEA-GPS-Modul am UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Zeigt und protokolliert Daten von u-blox-GPS-Modulen über I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA-Tracker mit Breadcrumb-Navigation |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Dateibrowser, der die Dateien nach Entfernung vom aktuellen Standort sortiert |

## Spiele- und Retro-Hardware {#game}

| App | Paket | Was sie macht |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Installiert und aktualisiert die Firmware des Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Air Mouse über den Bewegungssensor des Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Spielbild und Eingabeweiterleitung über das Modul |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Tauscht Pokémon mit einem Game Boy, Generation I und II, nicht-japanische Spiele |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper als ColecoVision-Controller, mit einem RC2014-Modul |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analysiert das Protokoll der Wii-Erweiterungscontroller |

## Ohne Modul: nur Pins {#bare}

| App | Paket | Was sie macht |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Visuelle Steuerung der General-Purpose-Pins |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Zeigt den Zustand jedes Pins auf dem Display |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Zweite App zum Anzeigen der Pin-Zustände |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Piept, wenn eine Leitung durchgeht |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Legt 3,3 V an Pin 7 (C3) und lässt sie nach dem Verlassen der App an |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Öffnet elektronische Safes von Sentry Safe und Master Lock über zwei Adern |

## Siehe auch {#related}

- [GPIO-Pinbelegung](/de/gpio/pinout) — was jeder Pin kann und wie viel Strom er liefert
- [Externe Module](/de/gpio/external-modules) — Busse, Pin-Konflikte und externes IR
- [GPIO-App](/de/gpio/gpio-app) — eingebaute Pin-Steuerung, UART-Bridge und der `i2c`-Befehl
- [App-Katalog](/de/apps/catalog) — die Pakete und wie man eines von Hand installiert
- [Apps auf der SD-Karte](/de/apps/sd-card-apps) — eine einzelne `.fap` installieren und API-Versionen abgleichen
