---
title: Moduli i njihove aplikacije
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Moduli i njihove aplikacije

Što možete priključiti na GPIO priključak i koja aplikacija time upravlja. Prvo su navedeni moduli koji imaju vlastitu stranicu; sve nakon toga su aplikacije zajednice iz paketa aplikacija, s poveznicom na njihov izvorni kod i README.

**Paket (Pack)** govori nalazi li se aplikacija već na vašem Flipperu:

| Paket | Koji ga build sadrži |
|---|---|
| Base | `e` build i build bez sufiksa |
| Extra | samo `e` build |

Build `c` ne isporučuje aplikacije. Bilo koji paket možete dodati ručno iz
[izdanja paketa](https://github.com/xMasterX/all-the-plugins/releases/latest) — pogledajte [Katalog aplikacija](/hr/apps/catalog).

::: warning
Ovo su aplikacije zajednice. Sadržaj paketa mijenja se između izdanja i aplikacija može ispasti ako se prestane prevoditi
s trenutačnim API-jem. Oznaka builda paketa u vašem firmveru ispisana je na vrhu svakog zapisa promjena (changeloga).
:::

::: tip Prije nego što išta spojite
Provjerite [raspored GPIO pinova](/hr/gpio/pinout) za napon i struju koju pin može podnijeti te
[Vanjske module](/hr/gpio/external-modules#pin-conflicts) da vidite koji su pinovi već zauzeti. Dva modula na istoj
sabirnici neće raditi istovremeno.
:::

## Moduli s vlastitom stranicom {#covered}

| Modul | Upravlja | Stranica |
|---|---|---|
| Vanjski CC1101 (Sub-GHz) | ugrađena aplikacija Sub-GHz | [Vanjski CC1101](/hr/subghz/external-cc1101) |
| ESP32 / ESP8266 Wi-Fi ploče | aplikacije u nastavku + firmver ploče | [ESP32 & Wi-Fi](/hr/gpio/esp32) |
| Wi-Fi Developer Board | debug sonda i zapisnici | [Dev board](/hr/gpio/devboard) |
| nRF24L01 | aplikacije u nastavku | [NRF24](/hr/gpio/nrf24) |
| SIM800 GSM | ugrađena aplikacija SIM800 | [SIM800](/hr/gpio/sim800) |
| GPS (NMEA) | aplikacije u nastavku | [GPS](/hr/gpio/gps) |
| Video Game Module | firmver + aplikacije u nastavku | [Video Game Module](/hr/gpio/video-game-module) |
| Moduli proširenja (Expansion modules) | `Settings → Expansion Modules` | [Moduli proširenja](/hr/gpio/expansion-modules) |

## Wi-Fi i ESP ploče {#esp}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Sučelje za Marauder firmver: skeniranje Wi-Fi i BLE mreža, hvatanje paketa, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Popis obližnjih Wi-Fi mreža, za ESP8266 Scanner firmver |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Sučelje za DSTIKE Deauther firmver |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Slika uživo s ESP32-CAM modula na zaslonu Flippera, uz snimanje fotografija |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Druga ESP32-CAM aplikacija: prijenos uživo i snimanje fotografija |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Sučelje za Ghost ESP firmver |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Pokreće pristupnu točku s captive-portalom na ESP32 |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Za Deauther v2 firmver autora @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Snima firmver na ESP ploču s Flippera, preko UART-a |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Aktivira IFTTT webhook putem ESP8266 modula |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Mapiranje Wi-Fi mreža pomoću ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Prikazuje Pwnagotchi lice i status na Flipperu, preko UART-a |

## 2,4 GHz: nRF24L01 {#nrf}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Hvata adrese bežičnih tipkovnica za Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Ubrizgava pritiske tipki u ranjivi prijemnik bežične tipkovnice ili miša |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Opći alat za nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Skenira i dekodira nRF24 pakete |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Prikazuje koji su od kanala na 2,4 GHz zauzeti |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Čita i zapisuje imenovana polja na nRF24 uređaju iz konfiguracijske datoteke |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Varijanta builda gornjeg Sniffera |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Varijanta builda gornjeg Mouse Jackera |

## Senzori {#sensors}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp: senzori temperature, vlažnosti i tlaka (DHT, DS18B20, BMP/BME i drugi) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Svjetlomjer za fotografiju, BH1750 preko I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Udaljenost s ultrazvučnog senzora HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Udaljenost s ultrazvučnog senzora Parallax PING))) (3 žice) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Detekcija pokreta s Dopplerovog radarskog modula RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | Razina CO2 sa senzora MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Lebdeće čestice sa senzora Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Alkotest pomoću senzora MQ-3, s kalibracijom nule |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Napon i struja sa senzora TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variometar za paragliding i planinarenje, senzor tlaka BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Čita dvoosni akcelerometar Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Pedometar izgrađen na istom modulu Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Miš upravljan senzorom pokreta BMI160 ili LSM6DS |

## Zračenje {#rad}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Broji impulse s Geigerove cijevi J305 na vanjskoj ploči |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Bacanje kockica pomoću iste Geigerove ploče, za rad zahtijeva ploču |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Radi s modulom RadSens |

## Zasloni, LED-ice i radio {#disp}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Upravlja 7-segmentnim zaslonom s GPIO pinova |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Dijagnostički alat za I2C OLED zaslone SSD1306 |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Provjerava rade li adresabilne LED-ice WS2812B |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Upravlja FM radio modulom TEA5767 |

## Memorijski čipovi {#mem}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Čita i zapisuje SPI flash čipove serije 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Upravljanje zaključavanjem SD kartica preko SPI-ja |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | I2C EEPROM 24Cxx: čitanje, pisanje, brisanje, izvoz i vraćanje sadržaja |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Čita i zapisuje EEPROM unutar nekih aparata za kavu |

## Sonde za otklanjanje pogrešaka i programiranje {#probe}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Pretvara Flipper u CMSIS-DAP debug sondu za ARM ciljeve |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | ARM Single Wire Debug sonda |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Emulira FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Programira AVR mikrokontrolere preko ISP-a |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Program za otklanjanje pogrešaka i snimanje za WCH CH32V003 |

## Sabirnice, mreža i terminali {#bus}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Skenira I2C sabirnicu te čita ili zapisuje registre |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminal za komunikaciju sa SPI uređajem |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminal za bilo koji UART uređaj |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Alati za CAN sabirnicu, zahtijeva CAN dodatnu ploču |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Skup alata za Teslinu CAN sabirnicu, zahtijeva isti CAN dodatak |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Testira Ethernet vezu putem modula W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | LAN tester na istom modulu: ARP, ping, DHCP, skeniranje portova, SNMP i drugo |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminal za LoRa modul |

## Mjerenja i signali {#meas}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Flipper kao Openbench Logic Sniffer, za PulseView na računalu |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Osciloskop na pinu 16 (PC0), od 0 do 2,5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Generira digitalne signale na GPIO pinovima |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | Servo PWM na pinu A7, s ručnim, središnjim i automatskim načinom |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Drugi servo tester, također na pinu A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervalometar: okida fotoaparat putem GPIO pinova |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Dekodira dugovalne vremenske signale (DCF77 i slične) |

## Kontrola pristupa, magnetska traka i UHF RFID {#access}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Čita Wiegand formate od W4 do W48 s čitača ili tipkovnice, sprema ih i ponavlja |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Bežično odašilje podatke magnetske trake putem zavojnice |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID putem modula YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Za čitače M6E Nano, M7E Hecto i YRM1000; čita mnogo oznaka odjednom |

## GPS {#gps}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Pozicija s bilo kojeg NMEA GPS modula na UART-u |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Prikazuje i bilježi podatke s u-blox GPS modula preko I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA pratitelj s navigacijom po točkama traga |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Preglednik datoteka koji sortira vaše datoteke prema udaljenosti od trenutačne lokacije |

## Igre i retro hardver {#game}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Instalira i ažurira firmver Video Game Modulea |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Zračni miš pomoću senzora pokreta Video Game Modulea |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Prikaz igre i prosljeđivanje ulaza putem modula |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Razmjena Pokemona s Game Boyem, generacije I i II, ne-japanske verzije |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Flipper kao ColecoVision kontroler, s modulom RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analizira protokol Wii dodatnog kontrolera |

## Modul nije potreban: goli pinovi {#bare}

| Aplikacija | Paket | Što radi |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Vizualno upravljanje pinovima opće namjene |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Prikazuje stanje svakog pina na zaslonu |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Drugi čitač stanja pinova |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Pišti kada je žica neprekinuta (kontinuitet) |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Stavlja 3,3 V na pin 7 (C3) i ostavlja ga uključenim nakon izlaska |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Otvara elektroničke sefove Sentry Safe i Master Lock putem dviju žica |

## Povezano {#related}

- [Raspored GPIO pinova](/hr/gpio/pinout) — što svaki pin može raditi i koliko struje može dati
- [Vanjski moduli](/hr/gpio/external-modules) — sabirnice, sukobi pinova i vanjski IR
- [GPIO aplikacija](/hr/gpio/gpio-app) — ugrađeno upravljanje pinovima, UART most i `i2c` CLI
- [Katalog aplikacija](/hr/apps/catalog) — paketi i kako ih ručno instalirati
- [Aplikacije na SD kartici](/hr/apps/sd-card-apps) — instalacija pojedinačne `.fap` datoteke i usklađivanje verzija API-ja
