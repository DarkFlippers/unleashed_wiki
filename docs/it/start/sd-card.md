---
title: Scheda microSD
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Scheda microSD

La scheda microSD non è un accessorio opzionale. Contiene le chiavi, le card e i telecomandi che salvi, tutte le app
`.fap` (comprese le app integrate di Unleashed), i database, il pacchetto di aggiornamento e, nei firmware attuali,
anche la **memoria interna**.

## Scegliere una scheda

- **Capacità:** 16–32 GB sono più che sufficienti. Sono supportate schede fino a 256 GB, ma quelle grandi richiedono
  più tempo per il montaggio.
- **File system:** FAT12, FAT16, FAT32 o exFAT.
- **Qualità:** usa una scheda **di marca** (SanDisk, Kingston…). Il Flipper comunica con la scheda via **SPI**, non
  con la modalità SDIO veloce usata da telefoni e PC. Non tutte le schede gestiscono bene l'SPI, anche se funzionano
  perfettamente in altri dispositivi. Una scheda scadente rende il Flipper lento, può far scaricare la batteria più in
  fretta (fino a ~50 mA invece di ~30 mA) e può corrompere i dati.
- In lettura l'SPI raggiunge quasi 600 KiB/s, più che sufficienti per tutto ciò che fa il Flipper.

## Inserimento

1. Lo slot si trova sul lato inferiore del Flipper.
2. Tieni la scheda **con i contatti verso l'alto** e spingila dentro fino allo scatto.
3. Nella barra di stato compare l'icona della SD.

## Se la scheda non viene riconosciuta

Compare un messaggio sulla scheda SD, oppure l'icona nella barra di stato è barrata. Possibili cause:

| Causa | Soluzione |
|---|---|
| File system errato o assente | Formatta la scheda (vedi sotto) |
| Polvere nello slot | Pulisci con cautela con aria compressa |
| La scheda non supporta l'SPI | Usa un'altra scheda |
| La scheda è danneggiata | Usa un'altra scheda |

## Settings → Storage

**Main Menu → Settings → Storage**

| Voce | Cosa fa |
|---|---|
| **About Internal Storage** | Nome, tipo `Virtual (/.int on SD)`, spazio totale e libero, flash libera |
| **About SD Card** | Etichetta, tipo di file system, spazio totale e libero, produttore e numero di serie |
| **Unmount SD Card** / **Mount SD Card** | Smonta in sicurezza prima di rimuovere la scheda, o la rimonta. Il montaggio può interrompere brevemente l'alimentazione ai moduli esterni |
| **Format SD Card** | Formatta la scheda. **Tutti i dati andranno perduti!** |
| **Benchmark SD Card** | Misura la velocità di scrittura/lettura in modalità SPI |
| **Factory Reset** | Cancella la memoria interna (impostazioni, accoppiamenti, delfino). Vedi [Ripristino](/it/start/recovery#factory-reset) |

### Formattazione

1. **Settings → Storage → Format SD Card**.
2. Confermi con <kbd>→</kbd> **Format**.
3. Attendi `Formatted`, poi premi **Finish**.

Se la formattazione dal Flipper fallisce (`Cannot Format SD Card`), formatta la scheda da PC in FAT32/exFAT oppure
prova un'altra scheda.

### Rimozione sicura

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. Quando vedi `SD Card Unmounted` / `You can remove SD card now.`, spingi la scheda per sbloccarla ed estraila.

Rimuovere la scheda mentre il Flipper vi sta scrivendo può corrompere i file o il file system.

### Benchmark

Il benchmark scrive un file di prova `/ext/rwfiletest.bin` e mostra righe come `4096b : W 300K R 600K`: dimensione del
blocco, poi velocità di scrittura e di lettura in KiB/s. Per un funzionamento normale una scheda dovrebbe scrivere ad
**almeno ~260 KiB/s**. I risultati sono diversi da quelli dei benchmark su PC perché il test gira in modalità SPI.
Eseguilo più volte per avere un quadro attendibile.

## Struttura delle cartelle

`/ext` è la radice della scheda. Le cartelle principali:

| Cartella | Contenuto |
|---|---|
| `/ext/subghz/` | File `.sub` Sub-GHz. In `assets/` ci sono `dangerous_settings`, `setting_user.example` (modello per il tuo elenco di frequenze) e il keystore KeeLoq `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Mappature di Sub-GHz Remote |
| `/ext/nfc/` | File `.nfc`. In `assets/` ci sono i dizionari di chiavi |
| `/ext/lfrfid/` | File `.rfid` per l'RFID a 125 kHz |
| `/ext/ibutton/` | File `.ibtn` per iButton |
| `/ext/infrared/` | Telecomandi `.ir`. In `assets/` ci sono le librerie dei telecomandi universali |
| `/ext/badusb/` | Script Bad USB (`.txt`). In `assets/layouts/` ci sono i layout di tastiera (`.kl`) |
| `/ext/apps/` | App `.fap` per categoria (app integrate e pacchetti di app) |
| `/ext/apps_data/` | Dati e impostazioni delle app |
| `/ext/dolphin/` | `name.settings` (nome personalizzato) e animazioni |
| `/ext/update/` | Pacchetti di aggiornamento scompattati |
| `/ext/.int/` | Archivio di appoggio per la memoria interna (`/int`). Non modificarlo a mano |

::: tip
Fai di tanto in tanto un backup dell'intera scheda (qFlipper può scaricare i file, oppure copiali da PC). Le tue
chiavi e i tuoi telecomandi esistono solo sulla scheda.
:::

## macOS: file nascosti e ordinamento {#macos-hidden-files-and-sorting}

macOS lascia sulla scheda file `._*` e `.DS_Store`. Per ripulirli:

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Sostituisci `Flipper\ SD` con il nome della tua scheda.

Il browser dei file elenca i file più rapidamente quando la directory FAT è ordinata. Su macOS (con
[Homebrew](https://brew.sh)):

```bash
brew install fatsort
diskutil list                         # find the card, e.g. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # use your own disk id
```

`fatsort` è disponibile anche su Linux.

## Argomenti correlati

- Cosa sopravvive a un aggiornamento: [Aggiornare](/it/start/updating)
- Formati dei file: [Sub-GHz](/it/subghz/file-format), [NFC](/it/nfc/file-format), [RFID](/it/rfid/file-format),
  [Infrarossi](/it/infrared/file-format), [iButton](/it/ibutton/file-format)
