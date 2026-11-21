---
title: Hardware
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Hardware

Specifiche tecniche del Flipper Zero, più l'indicazione di dove trovare schemi, disegni e modelli 3D — utili per
costruire moduli esterni e custodie, e per il debug di basso livello.

![Panoramica delle specifiche tecniche del Flipper Zero](/img/remote/629725f9f16a5946.png)

## Specifiche tecniche

### Scocca, dimensioni e peso

| | |
|---|---|
| Materiali | PC, ABS, PMMA |
| Altezza | 40,1 mm (1,58 in) |
| Larghezza | 100,3 mm (3,95 in) |
| Profondità | 25,6 mm (1,01 in) |
| Peso | 102 g (3,6 oz) |

### Display

| | |
|---|---|
| Tipo | LCD monocromatico |
| Risoluzione | 128×64 pixel |
| Controller | ST7567 |
| Interfaccia | SPI |
| Diagonale | 1,4″ |

### Microcontrollore

| | |
|---|---|
| Modello | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Core applicativo | Arm Cortex-M4, 32 bit, 64 MHz |
| Core radio | Arm Cortex-M0+, 32 bit, 32 MHz |
| Radio | Bluetooth LE 5.4, 802.15.4, proprietaria |
| Flash | 1024 KB (condivisa tra applicazione e radio) |
| SRAM | 256 KB (condivisa tra applicazione e radio) |

### Sub-1 GHz

| | |
|---|---|
| Transceiver | [CC1101](https://www.ti.com/product/CC1101) |
| Potenza TX | −20 dBm max (secondo le specifiche ufficiali) |
| Bande di frequenza | 315 MHz, 433 MHz, 868 MHz, 915 MHz (dipende dalla regione) |

Il CC1101 si sintonizza negli intervalli 299,999755–348 MHz, 386,999938–464 MHz e 778,999847–928 MHz.

::: tip Unleashed
Unleashed rimuove le restrizioni regionali sulla trasmissione e aggiunge frequenze extra (350 MHz e 467 MHz vengono
aggiunte all'intervallo predefinito). L'intervallo può essere esteso ulteriormente a 281–361, 378–481 e 749–962 MHz
tramite il file `subghz/assets/dangerous_settings` — questo è fuori dalle specifiche del CC1101 e **può danneggiare
l'hardware** ([impostazioni pericolose](/it/start/dangerous-settings)). È supportato anche un
[modulo CC1101 esterno](/it/subghz/external-cc1101). Rispetta le normative radio del tuo paese.
:::

### NFC

| | |
|---|---|
| Transceiver | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Frequenza | 13,56 MHz |
| Tessere | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire® ecc.; FeliCa™; HID iClass (Picopass); protocolli NFC Forum |

### RFID 125 kHz

| | |
|---|---|
| Frequenza | 125 kHz |
| Modulazione | AM, OOK |
| Codifica | ASK, PSK |
| Tessere (elenco ufficiale) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Vedi [RFID → Lettura](/it/rfid/read) per i protocolli effettivamente supportati dal firmware Unleashed.

### Infrarossi

| | |
|---|---|
| Lunghezza d'onda RX | 950 nm (±100 nm) |
| Portante RX | 38 kHz (±5%) |
| Lunghezza d'onda TX | 940 nm |
| Portante TX | 0–2 MHz |
| Potenza TX | 300 mW |
| Protocolli | famiglia NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 pin di I/O disponibili su header esterni da 2,54 mm
- Livelli CMOS a 3,3 V
- Ingressi tolleranti ai 5 V (vedi la nota ST [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf))
- Fino a 20 mA per pin digitale

Mappa dei pin: [pinout GPIO](/it/gpio/pinout).

### Batteria e alimentazione

| | |
|---|---|
| Tipo | Litio-polimeri (LiPo) |
| Capacità | 2100 mAh |
| Autonomia | Fino a 28 giorni |
| Temperatura di esercizio | 0…40 °C (32…104 °F) |

### Scheda microSD

| | |
|---|---|
| Capacità massima | Fino a 256 GB |
| Capacità consigliata | 2–32 GB |
| Interfaccia | SPI |
| Velocità di lettura/scrittura | Fino a 5 Mbps |

Il Flipper non include una scheda microSD — acquistane una a parte. Vedi [Scheda SD](/it/start/sd-card).

### USB

| | |
|---|---|
| Connettore | Type-C |
| Standard | USB 2.0 |
| Velocità dati | 12 Mbps |
| Corrente di carica massima | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| Potenza TX | 4 dBm max |
| Sensibilità RX | −96 dBm |
| Velocità dati | 2 Mbps |

### Cicalino e vibrazione

| | |
|---|---|
| Frequenza del cicalino | 100–2500 Hz |
| Uscita del cicalino | 87 dB |
| Tipo di cicalino | A moneta |
| Forza di vibrazione | 30 N |
| Velocità del motore di vibrazione | 13500 rpm |

### Nella confezione

Flipper Zero, cavo da USB-C a USB-A, documentazione, adesivo.

## Schemi elettrici

Gli schemi di tutti i PCB del Flipper Zero sono pubblicati da Flipper Devices "per scopi didattici" — sono utili per
lo sviluppo di moduli hardware e per il debug di basso livello. I visualizzatori Altium interattivi e i PDF
scaricabili si trovano nella pagina ufficiale:
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![I PCB del Flipper Zero](/img/remote/db285947a71be613.png)

| PCB | Documenti disponibili |
|---|---|
| **PCB principale** (rev. 12.1.F7B9C6) | Disegno di assemblaggio; panoramica dei blocchi principali; Power; Peripherals; MCU STM32WB55; display LCD; Sub-1 GHz CC1101; pulsanti |
| **PCB iButton** (rev. 12.F7B9C6) — porta anche l'altoparlante piezo e l'IR | Disegno di assemblaggio; schema iButton |
| **PCB NFC RFID** (rev. 12.F7B9C6) — RFID 125 kHz e NFC | Disegno di assemblaggio; panoramica dei blocchi NFC; NFC; alimentazione e vibrazione; RFID |
| **PCB dell'antenna** | Immagine della scheda |

::: info
Nella revisione 13.F7B9C6 del PCB iButton le piazzole dei pogo pin sono cambiate: i pogo pin passanti hanno
sostituito quelli SMD. I diametri delle piazzole sono gli stessi della 12.F7B9C6.
:::

## Disegni e modelli 3D

Tutti i file sono scaricabili dalle pagine ufficiali:

| Che cosa | File | Pagina |
|---|---|---|
| Scocca del Flipper Zero | Disegno 2D (`.pdf`, `.dwg`), modello 3D (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Modulo esterno standard | Disegno (`.pdf`), modello 3D del PCB (`.stp`, nudo e assemblato), profilo del PCB (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Modulo esterno piccolo | Lo stesso insieme del modulo standard | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Disegno (`.pdf`, `.dwg.zip`), modello 3D (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Disegno del Flipper Zero](/img/remote/c91e01d61829df8e.png)

I disegni dei moduli esterni indicano la geometria consigliata per le schede che si innestano sull'header GPIO —
parti da lì se progetti un modulo tuo (vedi anche [Moduli di espansione](/it/gpio/expansion-modules)).

## Devboard per sviluppatori

### Wi-Fi Developer Board

Basata su **ESP32-S2-WROVER-N4R2**. Documenti pubblicati: vista del PCB, disegno di assemblaggio
(`Wi-Fi Module_V1_Assembly.pdf`), schema dell'ESP32-S2, schema di alimentazione, schema dei connettori —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Utilizzo: [Dev Board](/it/gpio/devboard), [Debug delle app](/it/dev/debugging).

### ST-Link V3 Developer Board {#st-link-v3-developer-board}

Per sviluppatori avanzati che hanno bisogno del debug in-circuit. È basata sul modulo
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) e se ne differenzia solo per il fattore
di forma e la facilità di collegamento.

- ST-Link V3 Mods per il flashing e il debug in-circuit.
- UART-to-USB integrata, collegata alla UART del Flipper (pin GPIO 13 e 14).
- Pin non utilizzati del Flipper Zero e dell'ST-Link esposti per debug e prototipazione.

Progetto Altium Designer: [github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Schema e BOM: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info Non ti serve per aggiornare o sviluppare
Aggiornamenti del firmware, sviluppo e caricamento di un firmware proprio funzionano tutti via semplice USB. Una
scheda di debug serve soltanto per eseguire il debug del firmware mentre è in esecuzione (GDB, OpenOCD, …).
:::

## Pagine correlate

- [Pinout GPIO](/it/gpio/pinout)
- [API Furi](/it/dev/furi-api) — diagramma a blocchi dell'hardware
- [Debug delle app](/it/dev/debugging)
- [Aggiornamenti OTA](/it/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic e DESFire sono marchi registrati di NXP B.V. FeliCa è un marchio di Sony
Corporation.
