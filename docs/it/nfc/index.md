---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Il Flipper Zero integra un **modulo NFC a 13.56 MHz** in grado di **leggere**, **salvare**, **emulare** e, per alcuni
tipi di carte, **scrivere** carte ad alta frequenza: tessere e portachiavi di accesso, carte dei trasporti, chiavi
d'albergo, adesivi NFC, giocattoli in stile amiibo e carte bancarie (solo dati pubblici). I dati vengono salvati sulla
scheda microSD in `/ext/nfc/` come file di testo `.nfc`.

::: warning Inserisci una scheda microSD
L'app NFC conserva i suoi dizionari, i parser e le carte salvate sulla scheda microSD (`/ext/nfc/`). Aggiorna il
firmware con la scheda SD inserita, così le risorse (dizionari di chiavi, `assets/*.nfc`, plugin dei parser) vengono
installate.
:::

## Hardware

- Chip front-end NFC **ST25R3916**, responsabile sia della lettura sia dell'emulazione.
- Un'**antenna a 13.56 MHz** sulla scheda antenna RFID dual-band nella parte posteriore del dispositivo, accanto
  all'antenna a 125 kHz. Appoggia le carte contro il **centro del retro** del Flipper.

## Il menu NFC

`Main Menu → NFC` apre questo menu (le etichette sono esattamente quelle sul dispositivo in Unleashed):

![Menu principale NFC: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Voce | Cosa fa |
|---|---|
| **Read** | Rileva il tipo di carta e legge tutto quello che può, compresi gli attacchi alle chiavi MIFARE Classic. Vedi [Leggere le carte](/it/nfc/read). |
| **Extract MFC Keys** | Emula una carta MIFARE Classic per raccogliere nonce da un lettore (MFKey32). Vedi [MFKey32](/it/nfc/mfkey). |
| **Saved** | I tuoi file `.nfc` salvati: emulare, scrivere, sbloccare, rinominare, eliminare. |
| **Extra Actions** | Leggere un tipo di carta specifico, gestire i dizionari di chiavi, sbloccare NTAG/Ultralight e SLIX-L. |
| **Add Manually** | Genera una carta virtuale vuota oppure una carta NFC-A a partire da UID/ATQA/SAK noti. Vedi [Aggiungere carte manualmente](/it/nfc/add-manually). |
| **Debug** | Visibile solo con la modalità Debug attiva (`Settings → System → Debug`). |

`Extra Actions` contiene:

![Menu Extra Actions: Read Specific Card Type e i dizionari di chiavi](/screens/nfc/extra_actions.png)

- **Read Specific Card Type**: salta il rilevamento automatico, utile per le carte ibride.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys**: mostrano i
  contatori del dizionario di sistema/utente, permettono di aggiungere una chiave (**Add**) oppure di elencarle
  (**List**) ed eliminare le chiavi utente.
- **Unlock NTAG/Ultralight**: generare o inserire una password prima della lettura. Vedi
  [Sbloccare le carte con password](/it/nfc/unlock-with-password).
- **Unlock SLIX-L**: sbloccare con password i tag ICODE SLIX-L.

::: tip Unleashed
L'app NFC viene dal firmware ufficiale: il suo lettore, l'emulatore e la maggior parte dei parser di carte.
Inoltre Unleashed aggiunge, tra le altre cose: un dizionario di sistema MIFARE Classic esteso
(oltre 4000 chiavi), la lettura di **MIFARE Plus SL3** con dizionari di chiavi AES, il supporto di **MIFARE Ultralight
AES**, le chiavi per citofoni **Texkom**, Add Manually per MIFARE Classic con UID personalizzato e per MIFARE Plus,
**Save Keys to Dictionary** da un dump, il dizionario CUID (per singola carta) con barra di avanzamento del caricamento
e molti parser di carte aggiuntivi (Troika, Plantain, Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow Social Card,
biglietti PPK e altri).
:::

## Concetti di base

| Termine | Significato |
|---|---|
| **UID** | Numero di serie della carta, 4 o 7 byte (10 su alcune). Scritto in fabbrica sulle carte originali. |
| **ATQA / SAK** | Byte di risposta durante l'anticollisione che suggeriscono il tipo di carta (per esempio SAK `08` = MIFARE Classic 1K). |
| **Settore / blocco** | Unità di memoria MIFARE Classic: 16 byte per blocco, 4 blocchi per settore (settori da 16 blocchi in coda a una 4K). |
| **Pagina** | Unità di memoria Ultralight/NTAG, 4 byte. |
| **Key A / Key B** | Chiavi Crypto-1 da 6 byte che proteggono ciascun settore MIFARE Classic. |
| **Nonce** | Numero casuale scambiato durante l'autenticazione. I nonce raccolti permettono di calcolare le chiavi offline. |
| **Magic card** | Una carta vuota con UID/blocco 0 scrivibile. Vedi [Magic card](/it/nfc/magic-cards). |

## Pagine di questa sezione

### Uso quotidiano

- [Leggere le carte](/it/nfc/read): leggere, salvare, emulare; quali tipi di carta sono supportati e cosa si ottiene da
  ciascuno.
- [Aggiungere carte manualmente](/it/nfc/add-manually): generare carte virtuali, creare una carta NFC-A da
  UID/ATQA/SAK.
- [Carte supportate (parser)](/it/nfc/supported-cards): carte dei trasporti, di accesso e dei giocattoli che il Flipper
  è in grado di decodificare.
- [Carte bancarie (EMV)](/it/nfc/emv): cosa si legge da una carta bancaria e perché non può essere clonata.
- [Sbloccare le carte con password](/it/nfc/unlock-with-password): password NTAG/Ultralight, chiavi Ultralight C,
  SLIX-L.

### MIFARE Classic e recupero delle chiavi

- [MIFARE Classic](/it/nfc/mifare-classic): dizionari, settori, l'intero flusso di lettura, emulazione e scrittura.
- [MFKey32: chiavi dal lettore](/it/nfc/mfkey): raccogliere nonce da un lettore, recuperare le chiavi.
- [Attacchi nested e backdoor Fudan](/it/nfc/nested-fudan): attacchi card-only integrati in `Read`.
- [L'app MFKey](/it/nfc/mfkey-app): recuperare le chiavi direttamente sul Flipper (MFKey 4.1).
- [Recupero rapido delle chiavi con qUnleashed](/it/nfc/qunleashed): tutti gli attacchi sul telefono o sul PC.

### Carte vuote e clonazione

- [Magic card MIFARE Classic](/it/nfc/magic-cards): Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC e i nomi commerciali
  locali.
- [NFC Magic 2.0](/it/nfc/nfc-magic): scrivere e azzerare carte magic MIFARE Classic e Ultralight/NTAG vuote.

### Altre famiglie di carte

- [MIFARE Ultralight AES](/it/nfc/ultralight-aes): Ultralight protetto da AES (MF0AES20), chiavi, riscrittura,
  secure messaging.
- [MIFARE Plus](/it/nfc/mifare-plus): come vengono rilevati S/X/SE/EV1/EV2 e i livelli di sicurezza, chiavi AES SL3.

### Sistemi di accesso (di @gromovyna)

- [Lettori Iron Logic](/it/nfc/iron-logic)
- [Enrollment dinamico Iron Logic](/it/nfc/iron-logic-enrollment)
- [Filtri dei lettori Vizit](/it/nfc/vizit-filters)
- [Carte Moskvyonok](/it/nfc/moskvyonok)

### Riferimento

- [Formato dei file NFC](/it/nfc/file-format): la struttura del file `.nfc` e i formati dei dizionari.

::: tip Aspetti legali
Lavora con carte di tua proprietà oppure con un permesso esplicito. Copiare credenziali di accesso o biglietti dei
trasporti che non ti appartengono può essere illegale.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG e ICODE sono marchi di NXP B.V.
FeliCa è un marchio di Sony Corporation.
