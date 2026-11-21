---
title: Modules and their apps
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Modules and their apps

What you can plug into the GPIO header, and the app that drives it. The modules with a page of their own are
listed first; everything after that is a community app from the app packs, with a link to its source and README.

**Pack** tells you whether the app is already on your Flipper:

| Pack | Which build has it |
|---|---|
| Base | the `e` build and the one with no suffix |
| Extra | the `e` build only |

A `c` build ships no apps. You can add either pack by hand from the
[pack releases](https://github.com/xMasterX/all-the-plugins/releases/latest) — see [App catalog](/apps/catalog).

::: warning
These are community apps. Pack contents change between releases, and an app can drop out if it stops building
against the current API. The build tag of the packs in your firmware is printed at the top of every changelog.
:::

::: tip Before you wire anything up
Check [GPIO pinout](/gpio/pinout) for the voltage and current a pin can take, and
[External modules](/gpio/external-modules#pin-conflicts) for which pins are already taken. Two modules on the same
bus will not work at the same time.
:::

## Modules with a page of their own {#covered}

| Module | Driven by | Page |
|---|---|---|
| External CC1101 (Sub-GHz) | the built-in Sub-GHz app | [External CC1101](/subghz/external-cc1101) |
| ESP32 / ESP8266 Wi-Fi boards | the apps below, plus board firmware | [ESP32 & Wi-Fi](/gpio/esp32) |
| Wi-Fi Developer Board | debug probe and logs | [Dev board](/gpio/devboard) |
| nRF24L01 | the apps below | [NRF24](/gpio/nrf24) |
| SIM800 GSM | the built-in SIM800 app | [SIM800](/gpio/sim800) |
| GPS (NMEA) | the apps below | [GPS](/gpio/gps) |
| Video Game Module | firmware plus the apps below | [Video Game Module](/gpio/video-game-module) |
| Expansion modules | `Settings → Expansion Modules` | [Expansion modules](/gpio/expansion-modules) |

## Wi-Fi and ESP boards {#esp}

| App | Pack | What it does |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Front end for Marauder firmware: Wi-Fi and BLE scanning, packet capture, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Lists nearby Wi-Fi networks, for the ESP8266 Scanner firmware |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Front end for the DSTIKE Deauther firmware |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Live image from an ESP32-CAM on the Flipper screen, with photo capture |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | A second ESP32-CAM app: live feed and photo capture |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Front end for the Ghost ESP firmware |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Runs a captive-portal access point on the ESP32 |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | For Deauther v2 firmware by @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flashes firmware onto an ESP board from the Flipper, over UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Fires an IFTTT webhook through an ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Wi-Fi mapping with an ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Shows a Pwnagotchi face and status on the Flipper, over UART |

## 2.4 GHz: nRF24L01 {#nrf}

| App | Pack | What it does |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Captures wireless-keyboard addresses for Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Injects keystrokes into a vulnerable wireless keyboard or mouse receiver |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | General nRF24L01 utility |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Scans for and decodes nRF24 packets |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Shows which of the 2.4 GHz channels are busy |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Reads and writes named fields on an nRF24 device from a config file |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Variant build of the Sniffer above |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Variant build of the Mouse Jacker above |

## Sensors {#sensors}

| App | Pack | What it does |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: temperature, humidity and pressure sensors (DHT, DS18B20, BMP/BME and more) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Light meter for photography, BH1750 over I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Distance from an HC-SR04 ultrasonic sensor |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Distance from a Parallax PING))) ultrasonic sensor (3 wires) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Motion from an RCWL-0516 doppler radar module |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 from an MH-Z19 sensor |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Particulate matter from a Plantower PMSx003 sensor |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Breathalyzer using an MQ-3 sensor, with zero calibration |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Voltage and current from TI INAxxx sensors |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variometer for paragliding and hiking, BME280 pressure sensor |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Reads a Memsic 2125 dual-axis accelerometer |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Pedometer built on the same Memsic 2125 module |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Mouse driven by a BMI160 or LSM6DS motion sensor |

## Radiation {#rad}

| App | Pack | What it does |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Counts from a J305 geiger tube on an external board |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Dice rolled from the same geiger board, needs the board to work |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Works with the RadSens module |

## Displays, LEDs and radio {#disp}

| App | Pack | What it does |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Drives a 7-segment display from the GPIO pins |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Diagnostic tool for SSD1306 I2C OLED displays |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Checks that WS2812B addressable LEDs work |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Controls a TEA5767 FM radio module |

## Memory chips {#mem}

| App | Pack | What it does |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Reads and writes 25-series SPI flash chips |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Lock management for SD cards over SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | 24Cxx I2C EEPROM: read, write, erase, dump and restore |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Reads and writes the EEPROM inside some coffee machines |

## Debug and programming probes {#probe}

| App | Pack | What it does |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Turns the Flipper into a CMSIS-DAP debug probe for ARM targets |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | ARM Single Wire Debug probe |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Emulates an FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Flashes AVR microcontrollers over ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Debugger and flasher for WCH CH32V003 |

## Buses, networking and terminals {#bus}

| App | Pack | What it does |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Scans the I2C bus and reads or writes registers |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminal for talking to an SPI device |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminal for any UART device |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | CAN bus tools, needs a CAN add-on board |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Tesla CAN bus toolkit, needs the same CAN add-on |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Tests an Ethernet connection through a W5500 module |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | LAN tester on the same module: ARP, ping, DHCP, port scan, SNMP and more |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminal for a LoRa module |

## Measurement and signals {#meas}

| App | Pack | What it does |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper as an Openbench Logic Sniffer, for PulseView on a PC |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Oscilloscope on pin 16 (PC0), 0 to 2.5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Generates digital signals on the GPIO pins |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | Servo PWM on pin A7, with manual, center and auto modes |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | A second servo tester, also on pin A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervalometer: triggers a camera through the GPIO pins |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Decodes long-wave time signals (DCF77 and the like) |

## Access control, magstripe and UHF RFID {#access}

| App | Pack | What it does |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Reads W4 to W48 Wiegand formats from a reader or keypad, saves and replays them |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Transmits magstripe data wirelessly through a coil |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID through a YRM100 module |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | For M6E Nano, M7E Hecto and YRM1000 readers; reads many tags at once |

## GPS {#gps}

| App | Pack | What it does |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position from any NMEA GPS module on UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Shows and logs data from u-blox GPS modules over I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA tracker with breadcrumb navigation |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | File browser that sorts your files by distance from where you are |

## Game and retro hardware {#game}

| App | Pack | What it does |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Installs and updates the Video Game Module firmware |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Air mouse using the Video Game Module motion sensor |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Game display and input forwarding through the module |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Trades Pokemon with a Game Boy, generations I and II, non-Japanese |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper as a ColecoVision controller, with an RC2014 module |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analyses the Wii extension controller protocol |

## No module needed: bare pins {#bare}

| App | Pack | What it does |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Visual control of the general-purpose pins |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Shows the state of each pin on screen |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | A second pin-state reader |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Beeps when a wire is continuous |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Puts 3.3 V on pin 7 (C3) and leaves it on when you exit |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Opens Sentry Safe and Master Lock electronic safes through two wires |

## Related {#related}

- [GPIO pinout](/gpio/pinout) — what each pin can do, and how much current it can give
- [External modules](/gpio/external-modules) — buses, pin conflicts and external IR
- [GPIO app](/gpio/gpio-app) — the built-in pin control, UART bridge and `i2c` CLI
- [App catalog](/apps/catalog) — the packs, and how to install one by hand
- [Apps on the SD card](/apps/sd-card-apps) — installing a single `.fap` and matching API versions
