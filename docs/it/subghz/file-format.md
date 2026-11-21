---
title: Formati dei file
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Formati dei file Sub-GHz

Tutti i file Sub-GHz sono testo semplice nel *Flipper File Format* (righe `Key: value`), quindi puoi visualizzarli e
modificarli su un PC. Questa pagina descrive i file di segnale (`.sub`) e i file di configurazione in
`/ext/subghz/assets/`.

| Percorso | Cosa contiene |
|---|---|
| `/ext/subghz/*.sub` | Segnali salvati: chiavi, RAW e BinRAW |
| `/ext/subghz/assets/setting_user` | Le tue frequenze, l'elenco dell'hopper, i preset personalizzati |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Le tue chiavi del produttore KeeLoq |
| `/ext/subghz/assets/keeloq_mfcodes` | Chiavi del produttore KeeLoq integrate (cifrate, distribuite con il firmware) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Tabelle integrate per quei protocolli |
| `/ext/subghz/assets/dangerous_settings` | Interruttore della gamma di frequenze estesa, vedi [Frequenze e portata](/it/subghz/frequencies#extended-range) |

## Struttura di un file `.sub`

Un file `.sub` ha tre parti:

1. **Intestazione** — tipo di file, versione, frequenza.
2. **Preset** — preset di modulazione, oppure una configurazione CC1101 personalizzata completa.
3. **Dati** — nome del protocollo e i suoi campi, oppure temporizzazioni RAW.

### Intestazione

| Campo | Tipo | Descrizione |
|---|---|---|
| `Filetype` | stringa | `Flipper SubGhz Key File` per le chiavi, `Flipper SubGhz RAW File` per le registrazioni RAW |
| `Version` | uint | Versione del formato di file, attualmente `1` |
| `Frequency` | uint | Frequenza in Hz, per esempio `433920000` |

### Preset

| Campo | Descrizione |
|---|---|
| `Preset` | Nome del preset. Per un preset personalizzato deve essere `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Transceiver, `CC1101` per il Flipper Zero (solo preset personalizzato) |
| `Custom_preset_data` | Configurazione del transceiver (solo preset personalizzato) |

Preset integrati:

| Valore di `Preset` | Nome nel menu | Significato |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, banda 270 kHz |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, banda 650 kHz |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, deviazione 2.38 kHz, banda 270 kHz |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, deviazione 12 kHz |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, deviazione 47.6 kHz, banda 270 kHz |

Un preset personalizzato è incorporato nel file, così un altro Flipper può inviarlo anche senza avere quel preset
nelle proprie impostazioni.

#### Dati di un preset personalizzato {#custom-preset-data}

Byte esadecimali separati da spazi: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX` — indirizzo del registro CC1101, `YY` — valore del registro (tante coppie quante servono);
- `00 00` — fine del blocco dei registri;
- `ZZ ×8` — la tabella PA da 8 byte (rampa dell'amplificatore di potenza).

Per il significato dei registri vedi il [datasheet del CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf).

### File chiave

I segnali decodificati memorizzano il nome del protocollo e i suoi campi:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Campo | Descrizione |
|---|---|
| `Protocol` | Nome del protocollo esattamente come nel registro dei protocolli (per esempio `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Lunghezza del payload in bit |
| `Key` | Payload, esadecimale, 8 byte |
| `TE` | Durata dell'impulso base (intervallo di quantizzazione) in µs, per i protocolli che la memorizzano |

I protocolli possono aggiungere campi propri. Quelli che incontrerai in Unleashed:

| Campo | Usato da | Significato |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Produttore la cui chiave decodifica il segnale (per esempio `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, alcuni KeeLoq | Segreto per singolo telecomando per il secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Comportamento sperimentale del contatore, vedi [Modalità contatore](/it/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Secondo pacchetto; PIN della tastiera per i pacchetti a 86 bit ([Security+ PIN](/it/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Certificato del ricevitore ([Nice O-Code](/it/subghz/nice-o-code)) |

Esempio con preset personalizzato:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Modificare i file a codice rolling
Cambiare a mano la `Key` di un protocollo dinamico produce raramente un codice valido. Per cambiare seriale, tasto o
contatore usa [Add Manually [Advanced]](/it/subghz/add-manually) oppure, in modalità Debug,
`Saved → file → Signal Settings`.
:::

### File RAW

Registrazioni da [Read RAW](/it/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` deve essere `RAW`.
- `RAW_Data` — durate in µs: positive = portante attiva, negative = portante assente. I valori devono essere diversi
  da zero, iniziare con un numero positivo e alternarsi di segno. Fino a 512 valori per riga; la riga può ripetersi
  quante volte serve.

I payload lunghi vengono letti dalla scheda SD durante la trasmissione. Con temporizzazioni molto brevi (sotto i
10 µs) una scheda lenta può non stare al passo e la trasmissione si interrompe prima della fine.

### File BinRAW

`Bin RAW` in `Read → Config` produce file **BinRAW**. A differenza dei RAW, memorizzano solo la sequenza ripetuta utile,
con il bit rate ricostruito e senza rumore, così possono riprodurre quasi qualsiasi protocollo **statico**, noto o
meno. Durante la lettura tieni premuto il tasto del telecomando un po' più a lungo, così si accumulano dati sufficienti.

| Campo | Descrizione |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Lunghezza del payload dell'intero file in bit (massimo 4096) |
| `TE` | Intervallo di quantizzazione, µs |
| `Bit_RAW` | Lunghezza del blocco `Data_RAW` che segue, in bit |
| `Data_RAW` | Durate codificate: ogni bit = un `TE`; `1` = portante, `0` = nessuna portante |

Esempio: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → invia `-200 200 -100 300`.
Le coppie `Bit_RAW` + `Data_RAW` formano blocchi ripetuti; più blocchi vengono inviati uno dopo l'altro.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Frequenze e preset aggiuntivi, caricati all'avvio dell'app Sub-GHz. Rinomina `setting_user.example` in
`setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Chiave | Significato |
|---|---|
| `Add_standard_frequencies` | `true` — elenco del firmware + le tue (aggiunte dopo); `false` — solo le tue (allora compila sia `Frequency` sia `Hopper_frequency`) |
| `Default_frequency` | Frequenza con cui partono Read / Read RAW |
| `Frequency` | Aggiunge una frequenza all'elenco principale (9 cifre, Hz). Ripetibile |
| `Hopper_frequency` | Aggiunge una frequenza all'hopping. Ripeterne una fa sì che il Flipper la ascolti più spesso |
| `Custom_preset_name` / `_module` / `_data` | Un preset di modulazione personalizzato, mostrato nell'elenco `Modulation` con quel nome. Formato dei dati: [sopra](#custom-preset-data) |

Il file `.example` include preset commentati che puoi abilitare: `FM95`, `FM15k` (2-FSK, 200 kHz di banda / filtro a
135 kHz, deviazione 15.86 kHz), `Pagers`, `AM_1`, `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Le tue chiavi del produttore KeeLoq, caricate all'avvio dell'app in aggiunta al database integrato (cifrato). Crealo
da `keeloq_mfcodes_user.example`, rimuovi le chiavi di esempio e **lascia una riga vuota alla fine**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Ogni riga è `KEY:METHOD:NAME`:

- `KEY` — chiave del produttore a 64 bit, 16 cifre esadecimali;
- `NAME` — nome senza spazi, fino a 64 caratteri (mostrato come produttore in Read);
- `METHOD` — tipo di apprendimento:

| Valore | Apprendimento |
|---|---|
| `0` | prova tutto: itera sulla chiave precedente e su quella del produttore in ordine di byte diretto e inverso |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (richiede il Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` significa che il file è testo semplice: i file dell'utente non devono essere cifrati. Altro sui tipi
di apprendimento: [KeeLoq](/it/subghz/keeloq).

## Pagine correlate

- [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw) · [Frequenze e portata](/it/subghz/frequencies) · [Radio Settings](/it/subghz/settings)
- [KeeLoq](/it/subghz/keeloq) · [Modalità contatore](/it/subghz/counter-mode) · [File di mappa di Sub-GHz Remote](/it/subghz/remote)
