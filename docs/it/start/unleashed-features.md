---
title: Cosa aggiunge Unleashed
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Cosa aggiunge Unleashed

Unleashed è costruito sul firmware ufficiale (OFW) e rimane **del tutto compatibile con le sue API e le sue app**.
Tutto quello che fa il firmware stock continua a funzionare. Qui sotto sono elencate le modifiche e le aggiunte rispetto al firmware ufficiale (OFW), raggruppate per area,
con i link alle pagine della wiki che trattano ogni funzione in dettaglio.

## Sub-GHz: libreria radio e hardware

- **Restrizioni regionali sulla trasmissione rimosse.** Ogni frequenza supportata dal chip CC1101 può trasmettere
  senza passaggi aggiuntivi.
- **Frequenze aggiuntive** nell'elenco predefinito e un elenco di frequenze modificabile dall'utente: [Frequenze e preset](/it/subghz/frequencies).
- **Range di frequenza esteso opzionale**, oltre le specifiche del chip. Può danneggiare l'hardware:
  [Impostazioni pericolose](/it/start/dangerous-settings).
- **Ampia raccolta di protocolli aggiuntivi**, con la possibilità di **salvare e inviare numerosi sistemi a rolling code**:
  [Sistemi supportati](/it/subghz/supported-systems), [Rolling code](/it/subghz/rolling-codes),
  [KeeLoq](/it/subghz/keeloq).
- Supporto per il **modulo CC1101 esterno** su SPI hardware, con controllo di amplificatore e LED:
  [CC1101 esterno](/it/subghz/external-cc1101).
- **Modalità speciali del contatore** per i rolling code, per evitare la desincronizzazione:
  [Modalità contatore](/it/subghz/counter-mode).

## Sub-GHz: app principale

- **Le ultime impostazioni usate vengono ricordate** (frequenza, modulazione…).
- **Miglioramenti al Frequency Analyzer**: le funzioni di base sono le stesse del firmware ufficiale; in più, in
  Unleashed <kbd>OK</kbd> invia la frequenza rilevata a Read e una pressione lunga di <kbd>OK</kbd> porta direttamente a Read: [Frequency Analyzer](/it/subghz/frequency-analyzer).
- **Miglioramenti a Read**: mostra quando è stato ricevuto ogni segnale. Tieni premuto <kbd>→</kbd> nell'elenco per
  eliminare un segnale. I protocolli multi-sistema mostrano il nome del sistema decodificato (CAME, Nice FloR-S,
  FAAC SLH, KeeLoq): [Read](/it/subghz/read).
- **Nomi dei protocolli nei nomi dei file**: con `Radio Settings → Protocol Names = ON` i file salvati prendono il
  nome da un timestamp più il protocollo.
- **Pulsanti personalizzati** per KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn
  e altri. Usa i tasti freccia del pad direzionale per inviare il codice di un altro pulsante:
  [Usare il Flipper come telecomando](/it/subghz/remote).
- **`Add manually` esteso**: una voce per ogni sistema, selettore di banda, modalità avanzata con TE, guard time e
  altri campi. Crea telecomandi FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo e altri e accoppiali con un
  ricevitore: [Add manually](/it/subghz/add-manually),
  [Programmare un telecomando nuovo](/it/subghz/remote-prog).
- **Read RAW → More → Edit** apre un file RAW direttamente in Sub-GHz RAW Edit:
  [Editor RAW](/it/subghz/raw-editor).
- **Filtri Ignore** per i protocolli rumorosi (allarmi, sensori, campanelli, cercachiavi, luci Feron…) e opzioni di
  debug (passo di incremento del contatore, uscita sui pin di debug):
  [Impostazioni Sub-GHz](/it/subghz/settings).

## App Sub-GHz

| App | Cosa fa | Pagina |
|---|---|---|
| Sub-GHz Remote | Associa fino a 5 file `.sub` ai pulsanti, con configuratore integrato | [Telecomando](/it/subghz/remote) |
| Sub-GHz Bruteforcer | Brute force su codici statici, file personalizzati, ritardo e ripetizioni | [Bruteforce](/it/subghz/bruteforce) |
| Remote Analyzer | Decodifica un telecomando alla volta, con analizzatore di frequenze integrato | [Remote Analyzer](/it/subghz/remote-analyzer) |
| Nice O-Code | Recupera il codice installatore di un telecomando Nice O-Code | [Nice O-Code](/it/subghz/nice-o-code) |
| Security+ PIN | Trova il PIN della tastiera a partire da un segnale Security+ 2.0 | [Security+ PIN](/it/subghz/secplus-pin) |
| Seed Capturer | Raccoglie coppie Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) per recuperare il seed | [Seed Capturer](/it/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Taglia, unisce e decodifica le acquisizioni RAW | [Editor RAW](/it/subghz/raw-editor) |

## NFC, RFID e iButton

- **Chiavi MIFARE Classic aggiuntive** nel dizionario di sistema: [MIFARE Classic](/it/nfc/mifare-classic). Guide al
  recupero delle chiavi: [Nested e Fudan](/it/nfc/nested-fudan), [MFKey](/it/nfc/mfkey).
- **MFKey** direttamente sul dispositivo: [App MFKey](/it/nfc/mfkey-app).
- **Protocollo EMV e parser dei dati pubblici**: [Carte bancarie (EMV)](/it/nfc/emv).
- **NFC `Add manually` → MIFARE Classic con UID personalizzato**: [Add manually](/it/nfc/add-manually).
- **Molti parser di card aggiuntivi** (card per i trasporti e card cittadine: Troika, Umarsh, Zolotaya Korona, Kazan,
  Metromoney, Moscow Social Card e altre): [Card supportate](/it/nfc/supported-cards).
- **NFC Magic 2.0** per le card magic, Ultralight comprese: [NFC Magic](/it/nfc/nfc-magic).
- **App T5577**: legge, modifica e scrive i blocchi, cancella o azzera la password, sniffer di password (`Sniff Password`):
  [App T5577](/it/rfid/t5577-app).
- Formato di visualizzazione **EM4100 DEZ 8**: [Leggere RFID](/it/rfid/read).
- **Fuzzer RFID e iButton**: [RFID Fuzzer](/it/rfid/fuzzer), [iButton Fuzzer](/it/ibutton/fuzzer).

## Infrarossi

- Il telecomando universale per le TV è stato ricostruito per coprire **tutti i pulsanti**.
- **Ampia raccolta di telecomandi universali per proiettori, ventilatori, condizionatori e audio** (soundbar…),
  aggiornata, verificata e ampliata regolarmente dal team.
- Protocollo **RCA** e supporto per i moduli IR esterni (rilevati automaticamente):
  [Telecomandi universali](/it/infrared/universal-remotes).
- Come realizzare acquisizioni valide da includere nel database dei telecomandi universali:
  [Acquisizioni IR](/it/infrared/captures).

## Bad USB e USB/Bluetooth

- **BadKB**: esegue gli script Bad USB via **Bluetooth**, integrato nell'app Bad USB: [Bad USB](/it/badusb/usage).
- **Layout di tastiera** e il comando `DUCKY_LANG`, che permette a uno script di scegliere il proprio layout:
  [Formato degli script](/it/badusb/script-format).

## Desktop, impostazioni e comodità d'uso

- **Nome personalizzato del Flipper** in **Settings → Desktop → Change Flipper Name**:
  [Nome personalizzato](/it/start/custom-name).
- **Orologio sul desktop** (`Settings → Desktop → Show Clock`) e **stili della batteria** (`Battery View`: Bar, %,
  Inv. %, Retro 3, Retro 5, Bar %): [Desktop](/it/start/desktop).
- **Blocco tenendo premuto <kbd>↑</kbd>** sul desktop: con il PIN se ne è impostato uno, altrimenti blocco normale.
- **Più giochi in Dummy Mode**: ogni freccia (pressione breve e lunga) e <kbd>OK</kbd> possono avviare la propria app.
- Supporto per la **[mod di retroilluminazione RGB](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** in **LCD and Notifications → RGB Mod Settings** (solo per i Flipper
  modificati a livello hardware).
- **Cursore nell'inserimento di testo** e un **mini-editor per l'inserimento dei byte** (premi <kbd>↑</kbd> più volte
  finché non compare l'editor dei nibble).
- **Archive** con schede aggiuntive (SubRem per le mappature di Sub-GHz Remote, Phone per la rubrica del SIM800).

Tutte le voci di Settings sono descritte in [Impostazioni](/it/start/settings).

## App integrate {#built-in-apps}

Queste app sono compilate dal repository del firmware e installate in `/ext/apps/` da ogni aggiornamento, in **tutte**
le varianti di build (`e`, senza suffisso, `c`). I pacchetti di app non le contengono, quindi un pacchetto non può mai
sovrascriverle o riportarle a una versione precedente.

**Nel menu principale:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (con BadKB), U2F, **Clock** (controlli
della luminosità, sveglia, timer), **Sub-GHz Remote**. Sub-GHz, Archive e Settings fanno parte del binario del
firmware.

**In Apps:**

| App | Categoria | Pagina |
|---|---|---|
| MFKey | NFC | [App MFKey](/it/nfc/mfkey-app) |
| T5577 | RFID | [App T5577](/it/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | vedi la tabella sopra |
| SIM800 (chiamate, SMS, rubrica, USSD, terminale AT) | GPIO | [SIM800](/it/gpio/sim800) |
| FindMy Flipper (beacon Apple FindMy / Google Find My Device) | Bluetooth | [Catalogo delle app](/it/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Controller](/it/apps/controllers) |
| Snake Game | Giochi | — |

## Pacchetti di app della community

- **Pacchetto base** (nelle build senza suffisso e in quelle `e`) e **pacchetto extra** (solo `e`): sorgenti ed elenco
  completo su [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). I pacchetti più
  recenti sono nelle [release GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Funziona anche il catalogo ufficiale: [lab.flipper.net/apps](https://lab.flipper.net/apps) o l'app mobile.
- Altro: [Catalogo delle app](/it/apps/catalog), [App sulla scheda SD](/it/apps/sd-card-apps).

## App companion e strumenti web

- **qUnleashed**: app companion per telefono e PC: [qUnleashed](/it/mobile/qunleashed-app).
- **Strumenti web**: [Web Installer](https://web.unleashedflip.com), mappa Sub-GHz
  ([map.unleashedflip.com](https://map.unleashedflip.com)), mappa di wardriving Wi-Fi
  ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), flasher web per ESP32
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)):
  [Strumenti web](/it/mobile/web-tools).
