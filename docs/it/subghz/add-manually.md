---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** crea un telecomando virtuale completamente nuovo e lo salva come file `.sub`. Non serve un
telecomando originale: il Flipper genera un numero di serie casuale (e un contatore, un seed ecc. dove il protocollo
li richiede). Il nuovo telecomando può poi essere **registrato in un ricevitore** come telecomando aggiuntivo, allo
stesso modo in cui registreresti un telecomando di scorta acquistato in negozio.

**Add Manually [Advanced]** fa la stessa cosa, ma chiede di digitare ogni valore in esadecimale invece di generarlo.

::: tip Unleashed
Il firmware di serie ha solo una manciata di protocolli statici in Add Manually. Unleashed elenca **più di 100
sistemi**, compresi quelli a codice rolling (produttori KeeLoq, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code, CAME Atomo,
Somfy, Security+ 2.0, …), permette di scegliere per ciascuno una qualsiasi delle 15 bande frequenza/modulazione e
aggiunge la voce **[Advanced]**.
:::

## Quando usarlo

| Situazione | Cosa usare |
|---|---|
| Hai un telecomando a codice **statico** (fisso) e vuoi solo una copia | [Read](/it/subghz/read) e salvalo — non serve Add Manually |
| Hai un telecomando a **codice rolling** e vuoi che il Flipper funzioni *insieme* a esso | **Add Manually** → registra il nuovo telecomando nel ricevitore ([come fare](/it/subghz/remote-prog)) |
| Ti serve un telecomando con valori noti (seed recuperato, codice installatore, un seriale specifico) | **Add Manually [Advanced]** |
| Hai perso il telecomando statico originale ma conosci i suoi DIP switch / il suo codice | **Add Manually [Advanced]** con la chiave digitata a mano |

Perché non clonare semplicemente un telecomando a codice rolling? Vedi [Codici rolling](/it/subghz/rolling-codes): il
clone e l'originale si contendono il contatore.

## Creare un telecomando

1. `Main Menu → Sub-GHz → Add Manually`.
2. Scorri l'elenco e scegli il sistema, per esempio `BFT Mitto` o `KL: DoorHan`. Le voci che iniziano con `KL:` sono
   produttori KeeLoq.

   ![Add Manually: elenco alfabetico dei sistemi con KL: Allmatic selezionato](/screens/subghz/add_manually.png)

3. Si apre un **selettore di banda**, con il nome del sistema come intestazione. Le bande sono indicate come
   `frequenza modulazione`, per esempio `433.92 AM650`. La banda predefinita del sistema è la prima, poi vengono le
   altre bande che quel sistema è noto usare e infine tutte le bande restanti (per installazioni su una frequenza
   inusuale). Premi <kbd>OK</kbd> sulla banda che ti serve.
4. Inserisci un nome di file (ne viene suggerito uno) e confermalo.
5. Il telecomando viene salvato in `/ext/subghz/` e compare in `Sub-GHz → Saved`.

   ![Menu di un segnale salvato: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Aprilo: `Sub-GHz → Saved → <il tuo file> → Emulate`. Tieni premuto <kbd>OK</kbd> (`Send`) per trasmettere; sui
   protocolli con [tasti personalizzati](/it/subghz/rolling-codes#custom-buttons) le frecce inviano gli altri tasti.

   ![Schermata di trasmissione di un segnale salvato con R: Int e il pulsante Send](/screens/subghz/emulate.png)


Nulla viene trasmesso finché non apri il file e premi un tasto.

::: warning Nomi obsoleti
Le guide più vecchie (comprese le versioni precedenti di `SubGHzRemoteProg.md`) citano voci come `BFT Mitto 433MHz`
oppure `KL: DoorHan 315MHz`. Il firmware attuale divide tutto in due passaggi: sistema (`BFT Mitto`) → banda
(`433.92 AM650`).
:::

### Le 15 bande

Vengono proposte tutte per ogni sistema:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → sistema → banda, poi una serie di schermate di inserimento
esadecimale. Quali schermate ottieni dipende dalla famiglia di protocolli:

| Famiglia | Schermate (in ordine) |
|---|---|
| Protocolli statici (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; i protocolli che memorizzano una temporizzazione chiedono anche `Enter TE in us` (e `Enter GT in TE`) |
| KeeLoq (voci `KL:`, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq con seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (discriminatore di hop, memorizzato nel campo `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 bit) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N / AT4L, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (codice installatore) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (richiesto anche dal normale Add Manually) |
| Security+1.0 | niente da inserire, viene generato direttamente |

I valori sono in esadecimale big-endian. `BUTTON` e `SERIAL` insieme formano il `Fix` che vedi dopo una
[lettura](/it/subghz/read): su KeeLoq il tasto è la **prima** cifra esadecimale di `Fix` (seriale = `Fix` con quella
cifra sostituita da `0`), su FAAC SLH / Genius è l'**ultima** cifra.

::: tip Inserimento dei byte
L'inserimento dei byte di Unleashed ha un mini editor di nibble: premi <kbd>↑</kbd> ripetutamente finché compare.
:::

## Tutte le voci dell'elenco

Ordine ed etichette esattamente come nel menu del firmware. "Predefinita" è la banda elencata per prima; "Anche" sono
le bande alternative del sistema, elencate subito dopo.

| Voce di menu | Predefinita | Anche | Tipo |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (chiave Beninca) |
| `Alutech AT4L` | 433.92 AM650 | | Dinamico (Alutech AT-4N, prefisso `0x1Dxxxxxx`) |
| `Alutech AT4N` | 433.92 AM650 | | Dinamico (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dinamico (contatore semplice) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dinamico (AES-128) |
| `BETT` | 433.92 AM650 | | Statico |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Statico |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Statico |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dinamico |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Statico (pseudo-dinamico) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + discriminatore |
| `Ditec GOL4` | 433.92 AM650 | | Dinamico |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + discriminatore |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Statico (12 DIP switch) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Statico (antifurto per bici) |
| `Gate TX` | 433.92 AM650 | | Statico |
| `Genius` | 433.92 AM650 | 868.35 AM650 | Pacchetto FAAC SLH, chiave Genius |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | Simile a KeeLoq |
| `Hollarm` | 433.92 AM650 | | Statico (antifurto per bici) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dinamico (basato su KeeLoq) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dinamico (basato su KeeLoq) |
| `Linear` | **300.00 AM650** | | Statico (10 bit) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Statico |
| `Marantec24` | **868.35 AM650** | | Statico |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + discriminatore |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Statico |
| `Nice Flo 24bit` | 433.92 AM650 | | Statico |
| `Nice FloR-S` | 433.92 AM650 | | Dinamico |
| `Nice O-Code` | 433.92 AM650 | | Dinamico, codice installatore |
| `Nice O-Code One` | 433.92 AM650 | | Dinamico, codice installatore (pacchetto Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dinamico, codice installatore + certificato |
| `Nice One` | 433.92 AM650 | | Dinamico |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Statico |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + discriminatore |
| `Prastel` | 433.92 AM650 | | Dinamico (42 bit) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Statico (24 bit) |
| `Proteco` | 433.92 AM650 | | Statico |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Statico |
| `Roger` | 433.92 AM650 | | Statico |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dinamico |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dinamico |
| `Somfy Keytis` | **433.42 AM650** | | Dinamico |
| `Somfy Telis` | **433.42 AM650** | | Dinamico (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Statico |
| `V2 Phoenix` | 433.92 AM650 | | Dinamico |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Statico (Princeton, vedi [ZKTeco CMP200](/it/subghz/zkteco-cmp200)) |

Per `KL: Sommer`, le bande FM476 generano il telecomando con l'altra variante di modulazione di Sommer, così una sola
riga di menu copre entrambi i tipi di telecomando Sommer.

## Programmare il nuovo telecomando in un ricevitore

Un telecomando a codice rolling appena creato è sconosciuto al ricevitore. Registralo come qualsiasi telecomando di
scorta — con il tasto di apprendimento del ricevitore oppure da un telecomando già funzionante. I tasti nascosti / di
programmazione del telecomando originale si inviano con un singolo tasto freccia sul Flipper. Procedure passo per
passo per ogni produttore: **[Il Flipper come nuovo telecomando](/it/subghz/remote-prog)**.

## Risoluzione dei problemi

- **`Function requires an SD card with fresh databases.`** — i database delle chiavi dei produttori in
  `/ext/subghz/assets/` sono assenti o obsoleti. Reinstalla/aggiorna il firmware con la scheda SD inserita.
- **Il ricevitore non reagisce affatto** — banda sbagliata. Leggi prima il tuo telecomando originale
  (`Sub-GHz → Read`) e scegli la stessa frequenza e modulazione. DoorHan esiste a 315 e 433.92 MHz; FAAC, Genius,
  Erreka a 433.92 e 868.35.
- **Il ricevitore reagisce ma non memorizza mai il telecomando** — hai mancato la finestra di apprendimento oppure, per
  un altro motivo (per esempio interferenze), il ricevitore non ha ricevuto un segnale corretto dal Flipper.
- **Il nuovo telecomando Erreka/BFT viene rifiutato** — alcune installazioni condividono un solo Seed tra tutti i
  telecomandi; recuperalo ([Seed Capturer](/it/subghz/seed-capturer)) e usa Add Manually [Advanced]. Vedi
  [KeeLoq](/it/subghz/keeloq).
- **Il telecomando Nice O-Code viene ignorato** — un ricevitore di fabbrica non ha codice installatore; lì usa
  `Nice One` o `Nice FloR-S`. Per un sistema già installato vedi [Nice O-Code](/it/subghz/nice-o-code).

::: warning
Registra telecomandi solo in ricevitori di tua proprietà o che sei autorizzato a gestire.
:::

## Pagine correlate

- [Codici rolling e tasti personalizzati](/it/subghz/rolling-codes)
- [Programmare un nuovo telecomando in un ricevitore](/it/subghz/remote-prog)
- [KeeLoq](/it/subghz/keeloq) · [Sistemi supportati](/it/subghz/supported-systems)
- [Modalità contatore](/it/subghz/counter-mode) · [Formato dei file .sub](/it/subghz/file-format)
