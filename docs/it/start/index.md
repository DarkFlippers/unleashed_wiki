---
title: Primi passi
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Primi passi

Questa sezione ti porta da un Flipper Zero appena acquistato a un dispositivo completamente configurato con
**Unleashed Firmware**. Copre le basi che tutte le altre sezioni della wiki danno per scontate: pulsanti, desktop,
alimentazione, scheda microSD, impostazioni e ripristino.

## Che cos'è il Flipper Zero?

Il Flipper Zero è un multi-tool da tasca per esplorare le tecnologie radio e di controllo accessi. A bordo trovi:

- un **transceiver Sub-GHz CC1101** per telecomandi di garage, barriere, sensori e altri dispositivi sotto 1 GHz;
- un modulo **NFC a 13,56 MHz** e un'antenna **RFID a 125 kHz** per card, portachiavi e tag;
- un trasmettitore e un ricevitore a **infrarossi** per TV, condizionatori e altri telecomandi;
- un contatto **1-Wire (iButton)** per chiavi Dallas, Cyfral e Metakom;
- **USB** e **Bluetooth LE**, così può funzionare come tastiera (Bad USB), token U2F o telecomando;
- pin **GPIO** per moduli esterni (CC1101 esterno, NRF24, ESP32, SIM800 e altri);
- uno schermo monocromatico 128×64, un pad a 5 direzioni con pulsante Back e una batteria da 2100 mAh.

Sul desktop vive un delfino digitale da accudire. Sale di livello man mano che usi il dispositivo.

## Che cos'è Unleashed Firmware?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) è un fork del firmware ufficiale (OFW). Rimane
**del tutto compatibile con le API e le app dell'OFW** e aggiunge funzioni in più. Le novità principali:

- **nessuna restrizione regionale sulla trasmissione Sub-GHz**, frequenze aggiuntive e un range esteso opzionale;
- **molti più protocolli Sub-GHz**, compresa la possibilità di salvare e inviare numerosi sistemi a rolling code,
  pulsanti personalizzati e `Add manually` per i telecomandi nuovi;
- supporto per il modulo **CC1101 esterno**;
- parser NFC aggiuntivi, un parser EMV, più chiavi MIFARE Classic nel dizionario di sistema;
- fuzzer RFID e iButton, uno strumento T5577 e altre app integrate;
- comodità d'uso: nome personalizzato del Flipper, orologio sul desktop, percentuale della batteria, Night Shift,
  più giochi in Dummy Mode, BadKB (Bad USB via Bluetooth) e altro.

L'elenco completo con i link è in [Cosa aggiunge Unleashed](/it/start/unleashed-features).

::: warning Solo fonti ufficiali
`DarkFlippers/unleashed-firmware` è l'unica casa ufficiale del progetto. Ogni build è gratuita e open source.
Non esistono versioni a pagamento, "premium" o closed source. Chi te ne offre una è un truffatore.
:::

## Build release e dev

| Build | Che cos'è | Dove si trova |
|---|---|---|
| **Release** (stabile) | Release testate, consigliate per l'uso quotidiano | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (instabile) | Compilata automaticamente a ogni nuovo commit sul branch `dev` | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), canale Discord `unleashed-development` |

Ogni nuova build dev sostituisce la precedente sul sito; le build dev vecchie sopravvivono solo come file nel canale
Telegram. Le build dev ricevono le novità per prime, ma **possono contenere bug**. Se ne trovi uno, segnalalo su
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

Ogni release esce in tre varianti: `e` (base più app extra), senza suffisso (app base) e `c` (senza app della
community). I dettagli sono in [Installare Unleashed](/it/start/install#which-file-to-download).

## Canali della community

- Chat Telegram: [inglese](https://t.me/flipperzero_unofficial), [russo](https://t.me/flipperzero_unofficial_ru), [ucraino](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Sito di Unleashed: [flipperunleashed.com](https://flipperunleashed.com)

## Pagine di questa sezione

**Primi passi**
- [Primo avvio](/it/start/first-start): accensione, inserimento della microSD, primo aggiornamento
- [Installare Unleashed](/it/start/install): Web Installer, qFlipper, app mobili, aggiornamento offline dalla scheda SD
- [Aggiornare](/it/start/updating): restare aggiornati, release o dev, cosa sopravvive a un aggiornamento
- [Cosa aggiunge Unleashed](/it/start/unleashed-features): tutte le funzioni di Unleashed a confronto con il firmware stock

**Usare il dispositivo**
- [Comandi](/it/start/controls): pulsanti, modalità per mancini, scorciatoie
- [Desktop](/it/start/desktop): barra di stato, scorciatoie, Lock Menu, Quick Settings, Dummy Mode, Archive
- [Il delfino](/it/start/dolphin): umore, livelli e XP
- [Alimentazione e batteria](/it/start/power): ricarica, spegnimento, Auto PowerOff, Limit Charge
- [Scheda microSD](/it/start/sd-card): scelta, formattazione, struttura delle cartelle
- [Impostazioni](/it/start/settings): tutte le voci del menu `Settings`, una per una
- [Nome personalizzato del Flipper](/it/start/custom-name)

**Quando qualcosa va storto**
- [Combinazioni di tasti](/it/start/key-combos): combinazioni per il reset e per il DFU
- [Ripristino](/it/start/recovery): ripristino del firmware, reset di fabbrica, reset del PIN
- [Impostazioni pericolose](/it/start/dangerous-settings): range Sub-GHz esteso (leggi prima di toccarlo)
- [FAQ](/it/start/faq)

::: tip Aspetti legali
Unleashed è pensato per la sperimentazione e la ricerca lecita. Usalo sui tuoi dispositivi o con il permesso del
proprietario.
:::
