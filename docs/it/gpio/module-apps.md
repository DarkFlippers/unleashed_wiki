---
title: Moduli e le loro app
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Moduli e le loro app

Cosa si può collegare al connettore GPIO e quale app lo pilota. Prima i moduli che hanno una pagina propria, poi le
app della comunità presenti nei pacchetti, ognuna con il link ai sorgenti e al README.

La colonna **Pacchetto** dice se l'app è già sul tuo Flipper:

| Pacchetto | In quale build |
|---|---|
| Base | nella build `e` e in quella senza suffisso |
| Extra | solo nella build `e` |

La build `c` non contiene app. Entrambi i pacchetti si possono aggiungere a mano dalle
[release dei pacchetti](https://github.com/xMasterX/all-the-plugins/releases/latest) — vedi
[Catalogo delle app](/it/apps/catalog).

::: warning
Sono app della comunità. Il contenuto dei pacchetti cambia da una release all'altra e un'app può sparire se non
compila più con l'API attuale. Il build tag dei pacchetti è indicato in cima a ogni changelog.
:::

::: tip Prima di collegare qualcosa
In [Pinout GPIO](/it/gpio/pinout) trovi la tensione e la corrente che un pin regge, e in
[Moduli esterni](/it/gpio/external-modules#pin-conflicts) quali pin sono già occupati. Due moduli sullo stesso bus non
funzionano contemporaneamente.
:::

## Moduli che hanno una pagina propria {#covered}

| Modulo | Pilotato da | Pagina |
|---|---|---|
| CC1101 esterno (Sub-GHz) | l'app Sub-GHz integrata | [CC1101 esterno](/it/subghz/external-cc1101) |
| Schede Wi-Fi ESP32 / ESP8266 | le app qui sotto più il firmware della scheda | [ESP32 e Wi-Fi](/it/gpio/esp32) |
| Wi-Fi Developer Board | sonda di debug e log | [Dev board](/it/gpio/devboard) |
| nRF24L01 | le app qui sotto | [NRF24](/it/gpio/nrf24) |
| SIM800 GSM | l'app SIM800 integrata | [SIM800](/it/gpio/sim800) |
| GPS (NMEA) | le app qui sotto | [GPS](/it/gpio/gps) |
| Video Game Module | il firmware più le app qui sotto | [Video Game Module](/it/gpio/video-game-module) |
| Moduli di espansione | `Settings → Expansion Modules` | [Moduli di espansione](/it/gpio/expansion-modules) |

## Wi-Fi e schede ESP {#esp}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Interfaccia per il firmware Marauder: scansione Wi-Fi e BLE, cattura pacchetti, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Elenca le reti Wi-Fi vicine, per il firmware Scanner su ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Interfaccia per il firmware DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Immagine dal vivo di una ESP32-CAM sullo schermo del Flipper, con scatto foto |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Seconda app per ESP32-CAM: immagine dal vivo e foto |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Interfaccia per il firmware Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Crea sull'ESP32 un access point con captive portal |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Per il firmware Deauther v2 di @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Scrive il firmware su una scheda ESP dal Flipper, via UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Lancia un webhook IFTTT tramite un ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Mappatura delle reti Wi-Fi con un ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Mostra faccia e stato di un Pwnagotchi sul Flipper, via UART |

## 2,4 GHz: nRF24L01 {#nrf}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Raccoglie gli indirizzi delle tastiere wireless per Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Inietta tasti nel ricevitore vulnerabile di una tastiera o di un mouse wireless |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Utility generica per nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Cerca e decodifica i pacchetti nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Mostra quali canali a 2,4 GHz sono occupati |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Legge e scrive campi con nome di un dispositivo nRF24 da un file di configurazione |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Variante dello Sniffer qui sopra |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Variante del Mouse Jacker qui sopra |

## Sensori {#sensors}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: sensori di temperatura, umidità e pressione (DHT, DS18B20, BMP/BME e altri) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Esposimetro per la fotografia, BH1750 su I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Distanza da un sensore a ultrasuoni HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Distanza da un sensore a ultrasuoni Parallax PING))) (3 fili) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Movimento da un modulo radar doppler RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 da un sensore MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Particolato da un sensore Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Etilometro con sensore MQ-3, con calibrazione dello zero |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Tensione e corrente dai sensori TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variometro per parapendio ed escursioni, sensore di pressione BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Legge un accelerometro a due assi Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Contapassi sullo stesso modulo Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Mouse pilotato da un sensore di movimento BMI160 o LSM6DS |

## Radiazioni {#rad}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Conteggi da un tubo Geiger J305 su scheda esterna |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Dadi tirati con la stessa scheda Geiger; senza la scheda non funziona |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Funziona con il modulo RadSens |

## Display, LED e radio {#disp}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Pilota un display a 7 segmenti dai pin GPIO |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Strumento di diagnosi per display OLED SSD1306 su I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Verifica che i LED indirizzabili WS2812B funzionino |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Controlla un modulo radio FM TEA5767 |

## Chip di memoria {#mem}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Legge e scrive i chip di flash SPI della serie 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Gestione del blocco delle schede SD via SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | EEPROM 24Cxx su I2C: lettura, scrittura, cancellazione, dump e ripristino |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Legge e scrive la EEPROM dentro alcune macchine da caffè |

## Debug e programmazione {#probe}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Trasforma il Flipper in una sonda di debug CMSIS-DAP per target ARM |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | Sonda ARM Single Wire Debug |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Emula un FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Programma microcontrollori AVR via ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Debugger e programmatore per WCH CH32V003 |

## Bus, rete e terminali {#bus}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Scansiona il bus I2C e legge o scrive i registri |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminale per dialogare con un dispositivo SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminale per qualsiasi dispositivo su UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Strumenti per il bus CAN, serve una scheda CAN |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Set di strumenti per il bus CAN delle Tesla, serve la stessa scheda CAN |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Verifica una connessione Ethernet tramite un modulo W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | Tester LAN sullo stesso modulo: ARP, ping, DHCP, scansione porte, SNMP e altro |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminale per un modulo LoRa |

## Misure e segnali {#meas}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper come Openbench Logic Sniffer, per PulseView sul computer |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Oscilloscopio sul pin 16 (PC0), da 0 a 2,5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Genera segnali digitali sui pin GPIO |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | PWM per servo sul pin A7, modalità Manual, Center e Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Secondo tester per servo, anch'esso sul pin A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervallometro: fa scattare una fotocamera tramite i pin GPIO |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Decodifica i segnali orari a onde lunghe (DCF77 e simili) |

## Controllo accessi, banda magnetica e UHF RFID {#access}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Legge i formati Wiegand da W4 a W48 da un lettore o da una tastiera, li salva e li riproduce |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Trasmette i dati di una banda magnetica via radio attraverso una bobina |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID tramite un modulo YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Per lettori M6E Nano, M7E Hecto e YRM1000; legge molti tag in una volta |

## GPS {#gps}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Posizione da qualsiasi modulo GPS NMEA su UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Mostra e registra i dati dei moduli GPS u-blox via I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Tracker NMEA con navigazione a breadcrumb |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Browser di file che ordina i file per distanza dal punto in cui ti trovi |

## Hardware da gioco e retro {#game}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Installa e aggiorna il firmware del Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Air mouse con il sensore di movimento del Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Immagine di gioco e inoltro dei comandi attraverso il modulo |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Scambia Pokémon con un Game Boy, generazioni I e II, giochi non giapponesi |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper come controller ColecoVision, con un modulo RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analizza il protocollo dei controller di espansione Wii |

## Senza modulo: solo pin {#bare}

| App | Pacchetto | Cosa fa |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Controllo visuale dei pin general purpose |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Mostra sullo schermo lo stato di ogni pin |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Seconda app per leggere lo stato dei pin |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Suona quando un filo è continuo |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Mette 3,3 V sul pin 7 (C3) e li lascia attivi all'uscita |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Apre le casseforti elettroniche Sentry Safe e Master Lock con due fili |

## Vedi anche {#related}

- [Pinout GPIO](/it/gpio/pinout) — cosa può fare ogni pin e quanta corrente può dare
- [Moduli esterni](/it/gpio/external-modules) — bus, conflitti di pin e IR esterno
- [App GPIO](/it/gpio/gpio-app) — controllo dei pin integrato, ponte UART e il comando `i2c`
- [Catalogo delle app](/it/apps/catalog) — i pacchetti e come installarne uno a mano
- [App sulla scheda SD](/it/apps/sd-card-apps) — installare un singolo `.fap` e far combaciare le versioni API
