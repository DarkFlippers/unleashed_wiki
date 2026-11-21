---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Il Flipper Zero integra un transceiver **CC1101** e un'antenna per le bande sotto 1 GHz. Con essi puoi
leggere, salvare e riprodurre i segnali di telecomandi per garage e cancelli, sbarre, tapparelle, campanelli,
sensori wireless e altri dispositivi che lavorano negli intervalli
**300–348 MHz, 387–464 MHz e 779–928 MHz**.
La maggior parte dei telecomandi che incontrerai usa **315 MHz**, **433.92 MHz** o **868.35 MHz**.

L'app si trova in `Main Menu → Sub-GHz`. Il suo menu principale in Unleashed:

![Menu principale Sub-GHz: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Voce di menu | Cosa fa | Pagina |
|---|---|---|
| `Read` | Decodifica, salva e invia telecomandi di protocolli noti | [Read](/it/subghz/read) |
| `Read RAW` | Registra il segnale grezzo di qualsiasi telecomando e lo riproduce | [Read RAW](/it/subghz/read-raw) |
| `Saved` | File `.sub` salvati: Emulate, Rename, Delete e Signal Settings con Debug attivo | [Read](/it/subghz/read) |
| `Add Manually` | Crea un telecomando nuovo di zecca con numero di serie casuale | [Add Manually](/it/subghz/add-manually) |
| `Add Manually [Advanced]` | Lo stesso, ma seriale / tasto / contatore / seed li digiti tu | [Add Manually](/it/subghz/add-manually) |
| `Frequency Analyzer` | Scoprire su quale frequenza trasmette un telecomando | [Frequency Analyzer](/it/subghz/frequency-analyzer) |
| `Radio Settings` | Modulo interno / esterno, potenza TX, nomi dei file, passo del contatore | [Radio Settings](/it/subghz/settings) |

::: tip Unleashed
L'app Sub-GHz, la sua libreria di protocolli e il Frequency Analyzer vengono dal firmware ufficiale. Unleashed
rimuove le restrizioni TX regionali, aggiunge frequenze extra e altri protocolli, permette di salvare e inviare numerosi protocolli a codice rolling, crea nuovi telecomandi a codice
rolling che puoi registrare nel tuo ricevitore (`Add Manually`), usa i tasti freccia come tasti aggiuntivi del
telecomando, supporta un modulo CC1101 esterno e include app Sub-GHz aggiuntive (Remote Analyzer, Seed Capturer,
Nice O-Code, Security+ PIN, Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Usa queste funzioni solo con apparecchiature di tua proprietà o per ricerca lecita.
:::

## Per iniziare

1. Trova la frequenza del tuo telecomando — [Frequency Analyzer](/it/subghz/frequency-analyzer).
2. Prova a decodificarlo — [Read](/it/subghz/read). Se viene decodificato e il protocollo è **statico**, salvalo e hai finito.
3. Se è un telecomando a **codice rolling**, non clonarlo — leggi [Codici rolling](/it/subghz/rolling-codes) e crea un
   nuovo telecomando con [Add Manually](/it/subghz/add-manually) + [Il Flipper come nuovo telecomando](/it/subghz/remote-prog).
4. Se nulla viene decodificato, registralo con [Read RAW](/it/subghz/read-raw).

## Tutte le pagine

**Basi**
- [Frequenze e portata](/it/subghz/frequencies) — bande, elenchi predefiniti, blocchi regionali e portata estesa
- [Frequency Analyzer](/it/subghz/frequency-analyzer) — trovare la frequenza di un telecomando
- [Read](/it/subghz/read) — decodificare, salvare e inviare segnali
- [Read RAW](/it/subghz/read-raw) — registrare segnali grezzi

**Codici rolling e nuovi telecomandi**
- [Add Manually](/it/subghz/add-manually) — tutti i protocolli presenti nel menu
- [Codici rolling](/it/subghz/rolling-codes) — conflitti di contatore, tasti personalizzati
- [KeeLoq](/it/subghz/keeloq) — come funziona KeeLoq, chiavi del produttore e seed
- [Il Flipper come nuovo telecomando](/it/subghz/remote-prog) — passo per passo per ogni sistema
- [Modalità contatore](/it/subghz/counter-mode) — il `CounterMode` sperimentale per i cloni
- [Signal Settings](/it/subghz/signal-settings) — modalità contatore, contatore e tasto di un segnale salvato
- [Sistemi supportati](/it/subghz/supported-systems) — tabella completa dei protocolli

**Configurazione e hardware**
- [Radio Settings](/it/subghz/settings) — Radio Settings, configurazione di Read, frequenze personalizzate
- [Formati dei file](/it/subghz/file-format) — `.sub`, preset, file di impostazioni personalizzate
- [Modulo CC1101 esterno](/it/subghz/external-cc1101) — moduli esterni e amplificatori

**App**
- [App Sub-GHz Remote](/it/subghz/remote) — fino a 5 segnali sul D-pad
- [Sub-GHz Bruteforce](/it/subghz/bruteforce) — brute-force di codici statici
- [Remote Analyzer](/it/subghz/remote-analyzer) — decodificare un telecomando, protocolli aggiuntivi
- [App Nice O-Code](/it/subghz/nice-o-code) — recuperare il codice dell'installatore
- [Security+ PIN](/it/subghz/secplus-pin) — PIN della tastiera di Security+ 2.0
- [Seed Capturer](/it/subghz/seed-capturer) — raccogliere hop per il recupero del seed
- [Sub-GHz RAW Edit](/it/subghz/raw-editor) — tagliare, unire e decodificare file RAW

**Note dal campo**
- [ZKTeco CMP200](/it/subghz/zkteco-cmp200) — un telecomando Princeton travestito

## Dove sono salvati i file

| Percorso | Contenuto |
|---|---|
| `/ext/subghz/` | Segnali salvati (`.sub`), registrazioni RAW |
| `/ext/subghz/assets/setting_user` | Frequenze personalizzate, elenco dell'hopper, preset personalizzati |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Chiavi del produttore KeeLoq personalizzate |
| `/ext/subghz/assets/dangerous_settings` | Interruttore della gamma di frequenze estesa |
| `/ext/subghz_remote/` | File di mappa dell'app Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Acquisizioni del Seed Capturer |
