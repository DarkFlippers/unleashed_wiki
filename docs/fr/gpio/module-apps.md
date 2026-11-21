---
title: Les modules et leurs apps
order: 35
original: [https://github.com/xMasterX/all-the-plugins/tree/dev]
sources: [all-the-plugins, unleashed-src]
---
# Les modules et leurs apps

Ce que l'on peut brancher sur le connecteur GPIO, et l'app qui le pilote. D'abord les modules qui ont leur propre
page, ensuite les apps de la communauté livrées dans les packs, chacune avec un lien vers ses sources et son README.

La colonne **Pack** indique si l'app est déjà sur votre Flipper :

| Pack | Dans quel build |
|---|---|
| Base | dans le build `e` et dans celui sans suffixe |
| Extra | seulement dans le build `e` |

Le build `c` ne contient aucune app. Les deux packs peuvent être ajoutés à la main depuis les
[releases des packs](https://github.com/xMasterX/all-the-plugins/releases/latest) — voir
[Catalogue d'apps](/fr/apps/catalog).

::: warning
Ce sont des apps de la communauté. Le contenu des packs change d'une release à l'autre, et une app peut disparaître
si elle ne compile plus avec l'API actuelle. Le build tag des packs est indiqué en haut de chaque changelog.
:::

::: tip Avant de brancher quoi que ce soit
[Brochage GPIO](/fr/gpio/pinout) donne la tension et le courant que supporte chaque broche, et
[Modules externes](/fr/gpio/external-modules#pin-conflicts) indique quelles broches sont déjà prises. Deux modules sur
le même bus ne fonctionnent pas en même temps.
:::

## Modules qui ont leur propre page {#covered}

| Module | Piloté par | Page |
|---|---|---|
| CC1101 externe (Sub-GHz) | l'app Sub-GHz intégrée | [CC1101 externe](/fr/subghz/external-cc1101) |
| Cartes Wi-Fi ESP32 / ESP8266 | les apps ci-dessous plus le firmware de la carte | [ESP32 et Wi-Fi](/fr/gpio/esp32) |
| Wi-Fi Developer Board | sonde de débogage et logs | [Dev board](/fr/gpio/devboard) |
| nRF24L01 | les apps ci-dessous | [NRF24](/fr/gpio/nrf24) |
| SIM800 GSM | l'app SIM800 intégrée | [SIM800](/fr/gpio/sim800) |
| GPS (NMEA) | les apps ci-dessous | [GPS](/fr/gpio/gps) |
| Video Game Module | le firmware plus les apps ci-dessous | [Video Game Module](/fr/gpio/video-game-module) |
| Modules d'extension | `Settings → Expansion Modules` | [Modules d'extension](/fr/gpio/expansion-modules) |

## Wi-Fi et cartes ESP {#esp}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Interface pour le firmware Marauder : scan Wi-Fi et BLE, capture de paquets, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Liste les réseaux Wi-Fi proches, pour le firmware Scanner sur ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Interface pour le firmware DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Image en direct d'une ESP32-CAM sur l'écran du Flipper, avec prise de photo |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Une deuxième app ESP32-CAM : image en direct et photos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Interface pour le firmware Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Monte sur l'ESP32 un point d'accès avec portail captif |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Pour le firmware Deauther v2 de @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flashe un firmware sur une carte ESP depuis le Flipper, par UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Déclenche un webhook IFTTT via un ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Cartographie des réseaux Wi-Fi avec un ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Affiche le visage et l'état d'un Pwnagotchi sur le Flipper, par UART |

## 2,4 GHz : nRF24L01 {#nrf}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Collecte les adresses de claviers sans fil pour Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Injecte des touches dans le récepteur vulnérable d'un clavier ou d'une souris sans fil |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Utilitaire général pour le nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Cherche et décode les paquets nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Montre quels canaux 2,4 GHz sont occupés |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Lit et écrit des champs nommés d'un appareil nRF24 à partir d'un fichier de configuration |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Autre version du Sniffer ci-dessus |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Autre version du Mouse Jacker ci-dessus |

## Capteurs {#sensors}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [Temp sensors reader](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uni_temp) | Base | Unitemp : capteurs de température, d'humidité et de pression (DHT, DS18B20, BMP/BME et d'autres) |
| [Lightmeter](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/lightmeter) | Base | Posemètre pour la photo, BH1750 en I2C |
| [\[HC-SR\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/hc_sr04) | Base | Distance avec un capteur à ultrasons HC-SR04 |
| [\[USPING\] Dist. Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/usping) | Extra | Distance avec un capteur à ultrasons Parallax PING))) (3 fils) |
| [\[RCWL-0516\] Motion Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rcwl_0516) | Extra | Mouvement avec un module radar doppler RCWL-0516 |
| [\[MH-Z19\] CO2 sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mh_z19) | Extra | CO2 avec un capteur MH-Z19 |
| [\[PMSx003\] Airmon](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/airmon) | Extra | Particules fines avec un capteur Plantower PMSx003 |
| [MQ-3 Alcometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mq3_alcometer) | Extra | Éthylotest avec un capteur MQ-3, avec calibrage du zéro |
| [INA Meter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper-tina) | Extra | Tension et courant des capteurs TI INAxxx |
| [\[BME280\] Vario](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vario) | Extra | Variomètre pour le parapente et la randonnée, capteur de pression BME280 |
| [\[Mx2125\] Accelerometer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/memsic_2125) | Extra | Lit un accéléromètre deux axes Memsic 2125 |
| [\[Mx2125\] Step Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/step_counter) | Extra | Compteur de pas sur le même module Memsic 2125 |
| [\[BMI/LSM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/airmouse) | Extra | Souris pilotée par un capteur de mouvement BMI160 ou LSM6DS |

## Radioactivité {#rad}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[J305\] Geiger Counter](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper_geiger) | Extra | Comptage avec un tube Geiger J305 sur une carte externe |
| [\[J305\] Atomic Dice Roller](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_atomicdiceroller) | Extra | Dés lancés avec la même carte Geiger ; sans la carte, cela ne marche pas |
| [Radiation Sensor](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_radsens) | Extra | Fonctionne avec le module RadSens |

## Écrans, LED et radio {#disp}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [7-Segment Output](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_7segment) | Extra | Pilote un afficheur 7 segments depuis les broches GPIO |
| [SSD1306 Test](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ssd1306_test) | Extra | Outil de diagnostic pour les écrans OLED SSD1306 en I2C |
| [\[WS2812B\] LED Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/ws2812b_tester) | Extra | Vérifie que des LED adressables WS2812B fonctionnent |
| [\[TEA5767\] FM Radio](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/fm_radio_controller) | Extra | Commande un module radio FM TEA5767 |

## Puces mémoire {#mem}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [SPI Mem Manager](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/spi_mem_manager) | Base | Lit et écrit les puces de flash SPI de la série 25 |
| [SD SPI](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/sd_spi) | Extra | Gestion du verrouillage des cartes SD en SPI |
| [24Cxx Programmer](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/24cxxprog) | Extra | EEPROM 24Cxx en I2C : lecture, écriture, effacement, dump et restauration |
| [Coffee EEPROM](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/coffee_eeprom) | Extra | Lit et écrit l'EEPROM de certaines machines à café |

## Débogage et programmation {#probe}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [DAP Link](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/dap_link) | Base | Transforme le Flipper en sonde de débogage CMSIS-DAP pour cibles ARM |
| [SWD Probe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/swd_probe) | Base | Sonde ARM Single Wire Debug |
| [FlipTDI](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flip_tdi) | Base | Émule un FTDI FT232H |
| [AVR Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/avr_isp_programmer) | Base | Flashe des microcontrôleurs AVR en ISP |
| [WHC SWIO Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wch_swio_flasher) | Extra | Débogueur et programmateur pour le WCH CH32V003 |

## Bus, réseau et terminaux {#bus}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[GPIO\] i2c Tools](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/flipper_i2ctools) | Base | Scanne le bus I2C et lit ou écrit les registres |
| [\[SPI\] Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/spi_terminal) | Extra | Terminal pour dialoguer avec un appareil SPI |
| [UART Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/uart_terminal) | Base | Terminal pour n'importe quel appareil en UART |
| [CAN Commander](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/can_commander) | Extra | Outils pour le bus CAN, nécessite une carte CAN |
| [Tesla Mod](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_tesla_mod) | Extra | Boîte à outils pour le bus CAN des Tesla, nécessite la même carte CAN |
| [\[W5500\] Ethernet](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/eth_troubleshooter) | Extra | Teste une connexion Ethernet via un module W5500 |
| [\[W5500\] LAN Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/w5500_lan_analyse) | Extra | Testeur LAN sur le même module : ARP, ping, DHCP, scan de ports, SNMP et plus |
| [LoRA_Terminal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/LORA_term) | Extra | Terminal pour un module LoRa |

## Mesure et signaux {#meas}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [Logic Analyzer](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/logic_analyzer) | Extra | Le Flipper en Openbench Logic Sniffer, pour PulseView sur un ordinateur |
| [Scope](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperscope) | Extra | Oscilloscope sur la broche 16 (PC0), de 0 à 2,5 V |
| [Signal Generator](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/signal_generator) | Base | Génère des signaux numériques sur les broches GPIO |
| [ServoTester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/servotester) | Extra | PWM de servo sur la broche A7, modes Manual, Center et Auto |
| [Servo Tester 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ServoTesterApp) | Extra | Un deuxième testeur de servos, également sur la broche A7 |
| [\[GPIO\] Timelapse](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/timelapse) | Extra | Intervallomètre : déclenche un appareil photo via les broches GPIO |
| [Longwave Clock](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_longwave_clock) | Extra | Décode les signaux horaires en ondes longues (DCF77 et similaires) |

## Contrôle d'accès, piste magnétique et UHF RFID {#access}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [Wiegand Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wiegand) | Extra | Lit les formats Wiegand de W4 à W48 depuis un lecteur ou un clavier, les enregistre et les rejoue |
| [MagSpoof](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/magspoof_flipper) | Extra | Transmet des données de piste magnétique sans fil, par une bobine |
| [\[YRM100\] UHF RFID](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/uhf_rfid) | Extra | UHF RFID via un module YRM100 |
| [Simultaneous UHF RFID Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/simultaneous_rfid_reader) | Extra | Pour les lecteurs M6E Nano, M7E Hecto et YRM1000 ; lit beaucoup de tags d'un coup |

## GPS {#gps}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position depuis n'importe quel module GPS NMEA en UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Affiche et enregistre les données des modules GPS u-blox en I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Traceur NMEA avec navigation par points |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Explorateur qui trie vos fichiers par distance depuis l'endroit où vous êtes |

## Matériel de jeu et rétro {#game}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[VGM\] Video Game Module Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/video_game_module_tool) | Base | Installe et met à jour le firmware du Video Game Module |
| [\[VGM\] Air Mouse](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/air_mouse_ofw) | Base | Souris en l'air avec le capteur de mouvement du Video Game Module |
| [Video Game Module Console](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/vgm_console) | Extra | Image du jeu et renvoi des commandes à travers le module |
| [Pokemon Trade Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gb-pokemon-trading) | Extra | Échange des Pokémon avec une Game Boy, générations I et II, jeux non japonais |
| [RC2014 ColecoVision](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/rc2014_coleco) | Extra | Le Flipper en manette ColecoVision, avec un module RC2014 |
| [Wii EC Analyser](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wii_ec_anal) | Extra | Analyse le protocole des manettes d'extension Wii |

## Sans module : juste les broches {#bare}

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [GPIO Controller](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_controller) | Extra | Contrôle visuel des broches à usage général |
| [\[GPIO\] Reader](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/gpio_pins_reader) | Extra | Affiche à l'écran l'état de chaque broche |
| [\[GPIO\] Input Reader 2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero_gpioreader) | Extra | Une deuxième app pour lire l'état des broches |
| [\[GPIO\] Wire Tester](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/wire_tester) | Extra | Bipe quand un fil est continu |
| [Flashlight](https://github.com/xMasterX/all-the-plugins/tree/dev/apps_source_code/flipper-flashlight) | Extra | Met 3,3 V sur la broche 7 (C3) et les y laisse en quittant l'app |
| [\[GPIO\] Sentry Safe](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/sentry_safe) | Base | Ouvre les coffres électroniques Sentry Safe et Master Lock avec deux fils |

## Voir aussi {#related}

- [Brochage GPIO](/fr/gpio/pinout) — ce que peut faire chaque broche et le courant qu'elle fournit
- [Modules externes](/fr/gpio/external-modules) — bus, conflits de broches et IR externe
- [App GPIO](/fr/gpio/gpio-app) — le contrôle des broches intégré, le pont UART et la commande `i2c`
- [Catalogue d'apps](/fr/apps/catalog) — les packs et comment en installer un à la main
- [Apps sur la carte SD](/fr/apps/sd-card-apps) — installer un `.fap` seul et faire correspondre les versions d'API
