---
title: Hardver
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Hardver

Tehničke specifikacije uređaja Flipper Zero te gdje pronaći njegove sheme, nacrte i 3D modele — korisno za izradu vanjskih modula, kućišta i za niskorazinsko otklanjanje pogrešaka.

![Pregled tehničkih specifikacija Flipper Zera](/img/remote/629725f9f16a5946.png)

## Tehničke specifikacije

### Kućište, dimenzije i masa

| | |
|---|---|
| Materijali | PC, ABS, PMMA |
| Visina | 40,1 mm (1,58 in) |
| Širina | 100,3 mm (3,95 in) |
| Dubina | 25,6 mm (1,01 in) |
| Masa | 102 g (3,6 oz) |

### Zaslon

| | |
|---|---|
| Vrsta | Monokromatski LCD |
| Razlučivost | 128×64 piksela |
| Kontroler | ST7567 |
| Sučelje | SPI |
| Dijagonala | 1,4″ |

### Mikrokontroler

| | |
|---|---|
| Model | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Aplikacijska jezgra | Arm Cortex-M4, 32-bitna, 64 MHz |
| Radijska jezgra | Arm Cortex-M0+, 32-bitna, 32 MHz |
| Radio | Bluetooth LE 5.4, 802.15.4, vlasnički |
| Flash | 1024 KB (dijeljeno između aplikacije i radija) |
| SRAM | 256 KB (dijeljeno između aplikacije i radija) |

### Sub-1 GHz

| | |
|---|---|
| Primopredajnik | [CC1101](https://www.ti.com/product/CC1101) |
| TX snaga | maks. −20 dBm (prema službenim specifikacijama) |
| Frekvencijski pojasevi | 315 MHz, 433 MHz, 868 MHz, 915 MHz (ovisno o regiji) |

Čip CC1101 radi u rasponima 299,999755–348 MHz, 386,999938–464 MHz i 778,999847–928 MHz.

::: tip Unleashed
Unleashed uklanja regionalna TX ograničenja i dodaje dodatne frekvencije (350 MHz i 467 MHz dodane su zadanom rasponu). Raspon se može dodatno proširiti na 281–361, 378–481 i 749–962 MHz putem datoteke `subghz/assets/dangerous_settings` — to je izvan specifikacija čipa CC1101 i **može oštetiti hardver** ([opasne postavke](/hr/start/dangerous-settings)). Podržan je i [vanjski modul CC1101](/hr/subghz/external-cc1101). Poštujte radijske propise svoje države.
:::

### NFC

| | |
|---|---|
| Primopredajnik | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Frekvencija | 13,56 MHz |
| Kartice | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® itd.; FeliCa™; HID iClass (Picopass); protokoli NFC Forum |

### 125 kHz RFID

| | |
|---|---|
| Frekvencija | 125 kHz |
| Modulacija | AM, OOK |
| Kodiranje | ASK, PSK |
| Kartice (službeni popis) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Pogledajte [RFID → Čitanje](/hr/rfid/read) za protokole koje firmver Unleashed doista podržava.

### Infracrveno (IR)

| | |
|---|---|
| RX valna duljina | 950 nm (±100 nm) |
| RX nositelj | 38 kHz (±5%) |
| TX valna duljina | 940 nm |
| TX nositelj | 0–2 MHz |
| TX snaga | 300 mW |
| Protokoli | obitelj NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 I/O pinova dostupnih na vanjskim letvicama od 2,54 mm
- 3,3 V CMOS razine
- Ulazi podnose 5 V (pogledajte ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- Do 20 mA po digitalnom pinu

Raspored pinova: [GPIO raspored pinova](/hr/gpio/pinout).

### Baterija i napajanje

| | |
|---|---|
| Vrsta | Litij-polimerna (LiPo) |
| Kapacitet | 2100 mAh |
| Trajanje baterije | Do 28 dana |
| Radna temperatura | 0…40 °C (32…104 °F) |

### microSD kartica

| | |
|---|---|
| Najveći kapacitet | Do 256 GB |
| Preporučeni kapacitet | 2–32 GB |
| Sučelje | SPI |
| Brzina čitanja/pisanja | Do 5 Mbps |

Flipper ne dolazi s microSD karticom — kupuje se zasebno. Pogledajte [SD kartica](/hr/start/sd-card).

### USB

| | |
|---|---|
| Priključak | Type-C |
| Standard | USB 2.0 |
| Brzina prijenosa podataka | 12 Mbps |
| Najveća struja punjenja | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| TX snaga | maks. 4 dBm |
| RX osjetljivost | −96 dBm |
| Brzina prijenosa podataka | 2 Mbps |

### Zujalica i vibracija

| | |
|---|---|
| Frekvencija zujalice | 100–2500 Hz |
| Izlaz zujalice | 87 dB |
| Vrsta zujalice | Coin |
| Sila vibracije | 30 N |
| Brzina vibracijskog motora | 13500 okr/min |

### U kutiji

Flipper Zero, USB-C na USB-A kabel, dokumentacija, naljepnica.

## Sheme

Sheme svih tiskanih pločica (PCB) uređaja Flipper Zero objavila je tvrtka Flipper Devices „u obrazovne svrhe” — korisne su za razvoj hardverskih modula i niskorazinsko otklanjanje pogrešaka. Interaktivni Altium preglednici i PDF preuzimanja nalaze se na službenoj stranici: **[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![Tiskane pločice uređaja Flipper Zero](/img/remote/db285947a71be613.png)

| PCB | Dostupni dokumenti |
|---|---|
| **Main PCB** (rev. 12.1.F7B9C6) | Montažni crtež; pregled glavnih blokova; Napajanje; Periferija; MCU STM32WB55; LCD zaslon; Sub-1 GHz CC1101; Tipke |
| **iButton PCB** (rev. 12.F7B9C6) — nosi i piezo zvučnik te IR | Montažni crtež; shema iButton |
| **NFC RFID PCB** (rev. 12.F7B9C6) — 125 kHz RFID i NFC | Montažni crtež; pregled NFC blokova; NFC; Napajanje i vibro; RFID |
| **Antenna PCB** | Slika pločice |

::: info
U reviziji 13.F7B9C6 pločice iButton PCB promijenjeni su otisci (footprints) pogo pinova: SMD pogo pinovi zamijenjeni su pinovima za provlačenje (through-hole). Promjeri otisaka isti su kao u reviziji 12.F7B9C6.
:::

## Nacrti i 3D modeli

Sve datoteke mogu se preuzeti sa službenih stranica:

| Što | Datoteke | Stranica |
|---|---|---|
| Kućište uređaja Flipper Zero | 2D crtež (`.pdf`, `.dwg`), 3D model (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Standardni vanjski modul | Crtež (`.pdf`), 3D model PCB-a (`.stp`, obični i sastavljeni), obris PCB-a (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Mali vanjski modul | Isti skup kao za standardni modul | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Crtež (`.pdf`, `.dwg.zip`), 3D model (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Crtež uređaja Flipper Zero](/img/remote/c91e01d61829df8e.png)

Nacrti vanjskih modula daju preporučenu geometriju za pločice koje se priključuju u GPIO letvicu — započnite ondje ako dizajnirate vlastiti modul (pogledajte i [Moduli proširenja](/hr/gpio/expansion-modules)).

## Razvojne ploče

### Wi-Fi Developer Board

Temeljena na modulu **ESP32-S2-WROVER-N4R2**. Objavljeni dokumenti: prikaz PCB-a, montažni crtež (`Wi-Fi Module_V1_Assembly.pdf`), shema ESP32-S2, shema napajanja, shema priključaka — [Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Korištenje: [Razvojna ploča](/hr/gpio/devboard), [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging).

### Razvojna ploča ST-Link V3 {#st-link-v3-developer-board}

Za napredne programere kojima je potrebno otklanjanje pogrešaka u krugu (in-circuit debugging). Temelji se na modulu [ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) i razlikuje se samo po obliku i jednostavnosti povezivanja.

- ST-Link V3 Mods za učitavanje firmvera i otklanjanje pogrešaka u krugu.
- Ugrađeni UART-na-USB pretvarač, spojen na Flipperov UART (GPIO pinovi 13 i 14).
- Neiskorišteni pinovi uređaja Flipper Zero i modula ST-Link izvedeni su za otklanjanje pogrešaka i izradu prototipova.

Altium Designer projekt: [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Shema i popis komponenti (BOM): [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Nije potrebna za ažuriranje ni razvoj
Ažuriranje firmvera, razvoj i učitavanje vlastitog firmvera rade putem običnog USB-a. Ploča za otklanjanje pogrešaka potrebna je samo za otklanjanje pogrešaka firmvera dok se izvršava (GDB, OpenOCD, …).
:::

## Povezane stranice

- [GPIO raspored pinova](/hr/gpio/pinout)
- [Furi API](/hr/dev/furi-api) — blok-dijagram hardvera
- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging)
- [OTA ažuriranja](/hr/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic i DESFire registrirani su zaštitni znakovi tvrtke NXP B.V. FeliCa je zaštitni znak tvrtke Sony Corporation.
