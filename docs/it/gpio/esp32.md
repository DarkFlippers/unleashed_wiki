---
title: ESP32 e Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 e Wi-Fi

Il Flipper Zero non ha un Wi-Fi proprio. Gli strumenti Wi-Fi arrivano da una scheda **ESP32** (o ESP8266) collegata al
connettore GPIO, che si occupa della parte radio e dialoga con un'app del Flipper via UART. Questa pagina è una
panoramica delle opzioni disponibili e degli strumenti web di Unleashed che le accompagnano.

## Quale scheda

| Scheda | Uso tipico |
|---|---|
| **Wi-Fi Developer Board ufficiale** (ESP32-S2) | Arriva con il firmware della sonda di debug Black Magic per il [debug](/it/gpio/devboard). Può essere riprogrammata con Marauder |
| **Schede ESP32 Marauder** (varie schede ESP32 / ESP32-S2 / ESP32-S3, schede combo) | Scansione Wi-Fi e BLE, cattura di pacchetti, wardriving |
| **Schede ESP8266** | Firmware Wi-Fi Scanner e Deauther |
| **ESP32-CAM** | Camera Suite (immagine della fotocamera sullo schermo del Flipper) |

## App

Ognuna di queste è solo il lato Flipper: sulla scheda va prima scritto il firmware corrispondente.

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

Elenco completo delle app per i moduli: [Moduli e le loro app](/it/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) di justcallmekoko è un firmware per schede ESP32. Sul
Flipper si usa tramite l'app **WiFi Marauder** dei pacchetti di app extra, che invia comandi alla scheda e ne mostra
l'output.

Flusso di lavoro tipico:

1. **Programma Marauder** sulla scheda ESP32 (vedi il flasher qui sotto).
2. Spegni il Flipper, inserisci la scheda nel connettore GPIO, riaccendi.
3. Apri l'app Marauder in `Apps → GPIO` e scegli un comando (scansione degli access point, sniffing, wardriving e
   così via).
4. I risultati sono mostrati nell'app; le catture e i log di wardriving vengono salvati in base alle impostazioni
   della scheda e dell'app (consulta la documentazione di Marauder per la tua scheda).

Guida completa all'uso del Wi-Fi Devboard con Marauder (di UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Aspetti legali
La scansione è passiva, ma la deautenticazione e gli altri attacchi Wi-Fi attivi sono illegali contro reti che non ti
appartengono o per le quali non hai autorizzazione a fare test.
:::

## ESP32 Web Flasher

::: tip Unleashed
Il team di Unleashed gestisce un flasher basato su browser per i moduli ESP32 più diffusi:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Funziona interamente nel browser, quindi non
serve installare esptool. Usa un browser con supporto per Web Serial (quelli basati su Chromium).
:::

Passaggi generali:

1. Scollega la scheda ESP32 dal Flipper e collegala al computer via USB.
2. Se la scheda non entra da sé in modalità di programmazione, tieni premuto **BOOT**, premi brevemente **RESET** e
   rilascia **BOOT**.
3. Apri il flasher, scegli la scheda e il firmware, clicca per connettere e seleziona la porta seriale della scheda.
4. Attendi la fine della programmazione, resetta la scheda e ricollegala al Flipper (con il Flipper spento).

Altri modi per programmare una scheda ESP:

- L'app Flipper **ESP flasher** — scrive un `.bin` dalla scheda SD del Flipper attraverso la UART del GPIO:
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Guida per Windows a esptool / Flash Download Tool:
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- L'[USB-UART Bridge dell'app GPIO](/it/gpio/gpio-app) con `RTS/DTR Pins` può fare da adattatore USB per le schede
  senza porta USB propria.

::: tip Tornare al firmware di debug
Se hai messo Marauder sulla Wi-Fi Devboard ufficiale e vuoi riavere il debugger Black Magic, riprogrammala con
`ufbt devboard_flash` come descritto in
[Devboard: aggiornamento del firmware](/it/gpio/devboard-firmware).
:::

## Mappa di wardriving Wi-Fi

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** unisce e mostra su un'unica mappa diverse acquisizioni
di wardriving in formato WiGLE da ESP32 Marauder e da altri strumenti.
:::

1. Esegui una sessione di wardriving con Marauder (il wardriving richiede un modulo GPS collegato alla scheda ESP32).
2. Copia i log CSV in formato WiGLE sul tuo computer.
3. Apri la mappa e carica uno o più file; le reti vengono tracciate insieme.

Per le acquisizioni Sub-GHz e altri file con coordinate esiste una mappa separata,
[map.unleashedflip.com](https://map.unleashedflip.com).

## Altri firmware per ESP

| Firmware | Scheda | Link |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Come si usa](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Come si usa](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Come si usa](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Le app Flipper corrispondenti sono nei pacchetti Base/Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Risoluzione dei problemi

- **L'app non riceve risposta dalla scheda:** la scheda non ha il firmware che l'app si aspetta, TX/RX sono sulla UART
  sbagliata, oppure la scheda non è inserita a fondo.
- **Comportamenti strani sulla UART:** un'altra funzione sta ascoltando sugli stessi pin. Controlla
  `Settings → Expansion Modules → Listen UART` (vedi [Moduli di espansione](/it/gpio/expansion-modules)) e
  `Settings → System → Log Device`.
- **Il flasher web non trova la scheda:** usa un cavo USB che trasporti dati, entra manualmente in modalità
  bootloader, prova un'altra porta USB o un altro browser.

## Argomenti correlati

- [Wi-Fi Devboard](/it/gpio/devboard)
- [Moduli esterni](/it/gpio/external-modules)
- [GPS](/it/gpio/gps)
