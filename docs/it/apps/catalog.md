---
title: App incluse in Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# App incluse in Unleashed

Un'installazione di Unleashed comprende tre livelli di app:

1. **App di sistema (integrate).** Sono compilate dal repository del firmware e installate a ogni aggiornamento del
   firmware, qualunque build si scelga.
2. **Il pacchetto Base Apps.** Un insieme di app della comunità, preinstallato nella build predefinita.
3. **Il pacchetto Extra Apps.** Molte altre app della comunità, preinstallate solo nella build `e`.

A questo si aggiunge tutto ciò che installi tu, vedi [App sulla scheda SD](/it/apps/sd-card-apps).

## Varianti di build {#build-variants}

I file di release si chiamano `flipper-z-f7-update-(version)(e / c).tgz`:

| Parte | Significato |
|---|---|
| `flipper-z` | per Flipper Zero |
| `f7` | target hardware, lo stesso per ogni Flipper Zero |
| `update` | pacchetto di aggiornamento: updater, asset (app, librerie IR e così via) e il firmware stesso |
| `(version)` | versione del firmware |
| suffisso | quali pacchetti di app sono inclusi (vedi sotto) |

| Suffisso | Base Apps | Extra Apps |
|---|:---:|:---:|
| nessuno (` `) | sì | no |
| `c` | no | no |
| `e` | sì | sì |

- **` ` (nessuna lettera)** è la scelta predefinita: firmware, app di sistema e pacchetto Base.
- **`c`**: solo firmware e app di sistema, nessun pacchetto di app. Sceglila se vuoi comporre tu il tuo set di app.
- **`e`**: firmware, app di sistema, pacchetto Base e pacchetto Extra.

Il modo consigliato per installare qualunque di queste build è il [Web Installer](/it/mobile/web-tools), vedi anche
[Installare Unleashed](/it/start/install).

::: tip Unleashed
Le app integrate **non** fanno parte dei pacchetti Base o Extra. Un aggiornamento del firmware le scrive nella
cartella `apps/` della scheda SD, quindi l'installazione di un pacchetto di app non può mai sovrascrivere o
retrocedere un'app di sistema.
:::

## App di sistema: visibili nel menu principale

| App | Funzione | Autore / origine |
|---|---|---|
| GPIO | controllo dei pin GPIO, ponte USB-UART e gli strumenti 1-Wire/iButton | OFW |
| iButton | leggere, salvare ed emulare chiavi Dallas / Cyfral / Metakom | OFW |
| Infrared | apprendere, salvare e inviare segnali IR, telecomandi universali | OFW |
| NFC | leggere, salvare, emulare e analizzare tessere NFC | OFW |
| 125 kHz RFID | leggere, salvare, emulare e scrivere tag RFID LF | OFW |
| Bad USB | payload Ducky Script su USB, e BadKB su Bluetooth | OFW + BadKB di Willy-JL, ClaraCrazy e collaboratori XFW |
| U2F | token di sicurezza FIDO U2F su USB, vedi [U2F](/it/apps/u2f) | OFW |
| Clock | orologio con regolazione della luminosità dello schermo, sveglia e timer essenziale, vedi [Clock](/it/apps/clock) | @nymda, con @Willy-JL, @mishamyte e @xMasterX |
| Sub-GHz Remote | associa fino a 5 file `.sub` salvati ai pulsanti e li invia, vedi [Sub-GHz Remote](/it/subghz/remote) | @gid9798 e @xMasterX |

Sub-GHz, Archive, Settings e i servizi di sistema sono compilati direttamente nel binario del firmware.

## App di sistema: nella cartella Apps

Sono file `.fap` sotto `Main Menu → Apps`, ordinati in cartelle per categoria.

| App | Cartella | Funzione | Autore / origine |
|---|---|---|---|
| MFKey | NFC | recupera le chiavi MIFARE Classic dai nonce raccolti da Detect Reader, vedi [App MFKey](/it/nfc/mfkey-app) | @noproto |
| T5577 | RFID | legge, modifica e scrive i blocchi del T5577, esegue il wipe o cancella la password, intercetta una password, vedi [App T5577](/it/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | recupera il codice dell'installatore di un telecomando Nice O-Code e lo salva come `.sub`, vedi [Nice O-Code](/it/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | trova il PIN della tastiera in un segnale Security+ 2.0 catturato, vedi [Security+ PIN](/it/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | raccoglie coppie Fix + Hop dai telecomandi FAAC SLH, Genius, Erreka e BFT Mitto per il recupero offline del Seed, vedi [Seed Capturer](/it/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | decodifica un telecomando alla volta sul CC1101 interno, con analizzatore di frequenza integrato, vedi [Remote Analyzer](/it/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | apre una cattura RAW `.sub`, individua il segnale, lo ritaglia, unisce e decodifica, vedi [Editor RAW](/it/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | pilota un modulo GSM SIM800C/SIM800L: chiamate, SMS, rubrica, USSD, DTMF, terminale AT, vedi [SIM800](/it/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | beacon BLE di localizzazione per Apple Find My / Google Find My Device e altri, vedi [FindMy Flipper](/it/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | il telecomando HID su USB, vedi [Telecomando HID](/it/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | il telecomando HID su Bluetooth, vedi [Telecomando HID](/it/apps/hid-remote) | OFW |
| Snake Game | Games | Snake, vedi [Snake](/it/apps/snake) | OFW |

Il firmware comprende anche gli **stili del menu principale**, piccoli plugin che si selezionano in
`Settings → Desktop → Menu Style`, vedi [Stili del menu principale](/it/apps/menu-styles), e il runner JavaScript
usato per gli script `.js` (vedi [JavaScript](/it/dev/js-about)).

::: info Modifiche recenti
A partire dalla build del 20 novembre 2026, Sub-GHz RAW Edit viene distribuito con il firmware e non fa più parte del
pacchetto Extra, e SIM800 è una nuova app integrata (`Apps → GPIO → SIM800`).
:::

## Pacchetti Base ed Extra {#base-and-extra-packs}

Le app della comunità sono raccolte da @xMasterX in
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): quel repository contiene l'elenco
completo e il codice sorgente, e la sua pagina
[Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) offre i pacchetti Base ed Extra come download
separati, nel caso tu voglia aggiungere un pacchetto a una build `c` o aggiornare le app tra due release del firmware.

Per installare un pacchetto a mano: scarica lo `.zip` dalla [pagina delle release](https://github.com/xMasterX/all-the-plugins/releases/latest), estrailo e copia le cartelle
delle app nella cartella `apps` della scheda SD (`/ext/apps/`). La versione di API del pacchetto deve corrispondere a
quella del firmware (`Current API:` in cima a ogni changelog).

App a cui rimanda il ReadMe di Unleashed (ciascuna è presente in uno dei pacchetti):

| App | Dove approfondire |
|---|---|
| TOTP (Authenticator) | [descrizione del file di configurazione](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/it/apps/barcode) |
| Multi Converter | [Multi Converter](/it/apps/multi-converter) |
| WAV Player | [file di esempio e come convertirli](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [script generatore](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Bruteforce Sub-GHz](/it/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [Fuzzer RFID](/it/rfid/fuzzer), [Fuzzer iButton](/it/ibutton/fuzzer) |
| Unitemp (sensori di temperatura) | [come si usa e sensori supportati](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [come si usa](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [come si usa](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| App NRF24 | [NRF24](/it/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 e moduli Wi-Fi](/it/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/it/apps/sentry-safe) |

::: warning
Il contenuto dei pacchetti cambia da una release all'altra. Il build tag dei pacchetti correnti è indicato in cima a
ogni changelog di Unleashed (per esempio `Apps: Build tag (20nov2026)`), con un link ai commit più recenti delle app.
:::

## Catalogo ufficiale

L'Apps Catalog ufficiale di Flipper Zero è disponibile in [Flipper Lab](https://lab.flipper.net/apps) e nell'
[app mobile Flipper](/it/mobile/mobile-app). L'installazione a partire dal catalogo è descritta in
[App sulla scheda SD](/it/apps/sd-card-apps#installing-from-the-official-catalog).

## Pagine correlate

- [App sulla scheda SD (.fap)](/it/apps/sd-card-apps)
- [Risoluzione dei problemi con le app](/it/apps/troubleshoot)
- [Installare Unleashed](/it/start/install)
