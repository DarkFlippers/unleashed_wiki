---
title: Il Flipper come nuovo telecomando
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Usare il Flipper come nuovo telecomando Sub-GHz

Trasforma il Flipper in un **telecomando completamente nuovo** e registralo nel ricevitore del tuo cancello, garage o tapparella, allo stesso modo in cui registreresti un telecomando di scorta acquistato in negozio. **Non** è clonazione.

::: warning
Usalo solo su ricevitori di tua proprietà o che sei autorizzato a gestire.
:::

## Clone o nuovo telecomando? {#clone-or-new}

- **Telecomandi a codice rolling (dinamico)**: BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq e tutto il resto di questa pagina. Ogni pressione invia un nuovo codice costruito da un contatore, e il ricevitore accetta solo un contatore che è andato avanti. Un clone condivide il contatore dell'originale, quindi i due se lo contendono: funziona quello premuto per ultimo, e l'altro ha bisogno di diverse pressioni per recuperare (vedi [Codici rolling](/it/subghz/rolling-codes)). Per questo si crea un telecomando **nuovo**. Ha un seriale e un contatore propri e convive con i tuoi telecomandi originali.
- **Telecomandi a codice statico (fisso)**: CAME 12/24 bit, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX e gli altri protocolli statici. Non c'è contatore, quindi **clonare va benissimo**: la copia è identica ed entrambi continuano a funzionare in qualsiasi ordine. Usa `Sub-GHz → Read` e salva (vedi [Read](/it/subghz/read)). Questa pagina ti serve solo se vuoi un telecomando con un codice separato tutto suo.

## Leggi prima questo {#read-first}

**Cosa fa Add Manually.** `Main Menu → Sub-GHz → Add Manually` costruisce un nuovo telecomando con un numero di serie generato casualmente e lo salva come file. Non viene inviato nulla finché non apri quel file e premi un tasto. I tuoi telecomandi originali non vengono toccati.

::: tip Unleashed: Add Manually in due passaggi
Nel firmware Unleashed attuale il menu è in due passaggi:
1. Scegli il **sistema** dall'elenco, per esempio `BFT Mitto`, `KL: DoorHan` o `Somfy Telis`.
2. Scegli la **banda** (frequenza + modulazione). Le bande proprie del sistema sono in cima, per esempio `433.92 AM650` oppure `868.35 AM650`. Tutte le altre bande sono elencate sotto, per le installazioni che ne usano una inusuale: `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Poi dai un nome al file e questo viene salvato in `/ext/subghz/`. Le guide più vecchie scrivono cose come "BFT Mitto 433MHz" come se fosse una sola voce di menu. Oggi è `BFT Mitto` → `433.92 AM650`.
:::

**Se il tuo sistema non è in questa pagina, il Flipper potrebbe comunque supportarlo.** Scorri l'elenco di `Add Manually`. Se la tua marca c'è, crea un telecomando e segui i passaggi di programmazione del *manuale del tuo ricevitore*. L'elenco completo dei protocolli è in [Sistemi supportati](/it/subghz/supported-systems), e ogni voce di menu è descritta in [Add Manually](/it/subghz/add-manually).

**Read e Add Manually fanno due lavori diversi.** `Read` acquisisce e riproduce un telecomando che hai già. `Add Manually` crea un nuovo telecomando che può essere registrato nel ricevitore. Molti protocolli supportano solo `Read`.

**I tasti del Flipper sono i tasti del telecomando originale.** Quando un file di telecomando è aperto (`Saved → file → Emulate`):

| Tasto del Flipper | Cosa invia |
|---|---|
| <kbd>OK</kbd> (mostrato come `Send`) | il tasto principale del telecomando |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | gli altri tasti del telecomando (tasti personalizzati) |

Quale freccia invii quale tasto dipende dal protocollo. Un tasto *nascosto* o di *programmazione* del telecomando originale (un foro per pin incassato, due tasti tenuti premuti insieme, piazzole da ponticellare all'interno del guscio) diventa **una singola pressione di tasto** sul Flipper. Ogni sezione qui sotto indica di quale tasto si tratta, e la [tabella di riferimento](#programming-hidden-button-reference) li elenca tutti.

L'app [Sub-GHz Remote](/it/subghz/remote) invia quegli stessi tasti: ogni slot di una mappa ha un'impostazione `Button` (`Default`, `Up`, `Down`, `Left`, `Right`), così un tasto nascosto può stare su un tasto tutto suo.

**Tieni premuto <kbd>OK</kbd> per 1–3 secondi**, se un passaggio non dice diversamente.

**La tempistica conta.** La maggior parte dei ricevitori apre una finestra di programmazione di 5, 10 o 30 secondi. Leggi tutta la procedura prima di iniziare.

::: danger
Su molti ricevitori, tenere premuto il tasto di programmazione **troppo a lungo** cancella tutti i telecomandi che conosce, non solo uno. Poi devi registrare di nuovo tutti i tuoi telecomandi originali. Quando un passaggio dice "circa 1 secondo", non tenerlo premuto per cinque.
:::

::: info Done! / Done?
Una procedura che termina con **Done!** è stata confermata funzionante. **Done?** significa che viene dal manuale del produttore ma nessuno ha ancora riferito l'esito. Dovrebbe funzionare. Se non funziona, segnalalo al team di Unleashed nelle issue di GitHub.
:::

**Add Manually [Advanced]** è la voce di menu immediatamente sotto `Add Manually`. Usala quando devi digitare i valori a mano invece di ottenere un seriale casuale. Dopo il sistema e la banda chiede, tutto in esadecimale, `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` e, sui protocolli che ne usano uno, `Enter SEED in hex`. Nice O-Code chiede invece `IC` (e `CERT`). FAAC FIX, Monarch, Phantom/Hiland e DEA Mio chiedono `DISC.` (discriminatore) al posto del SEED.

## Trova il tuo sistema {#find-your-system}

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

Non è in elenco? Vedi la [tabella di riferimento](#programming-hidden-button-reference). Copre tutte le altre voci del menu `Add Manually`.

---

## Alutech AT4N (AN-Motors) {#alutech-at4n-an-motors}

- **Crealo così:** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

Usa questa procedura per le schede con display e tasti `F`, `CL`, `+`, `-`. Se la tua scheda ha invece un tasto `Learn`, usa [AN-Motors AT4](#an-motors-at4).

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore, trova il tasto `F` e tienilo premuto per circa 3 s. Il display mostra `Pr`.
3. Premi `F` qualche altra volta finché il display mostra `Lr`.
4. Scegli un numero di telecomando libero con `+` / `-`. Un numero che ha già un telecomando mostra un punto rosso nell'angolo in basso a destra.
5. Premi <kbd>OK</kbd> (`Send`) sul Flipper una volta. Il display lampeggia e accanto a quel numero compare un punto rosso.
6. Tieni premuto `F` sulla scheda per circa 3 s per uscire dalla modalità di programmazione.
7. Done!

[Video dimostrativo, mostra anche altri tipi di scheda (in russo)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4 {#an-motors-at4}

- **Crealo così:** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xC`

Usa questa procedura per le schede più vecchie con un tasto `Learn`. Se la tua scheda ha invece `F`, `CL`, `+`, `-`, usa [Alutech AT4N](#alutech-at4n-an-motors).

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore e premi `Learn` una volta. Il LED si accende.
3. Premi `Send` sul Flipper una volta. Il LED sulla scheda si spegne.
4. Premi `Send` di nuovo. Il LED inizia a lampeggiare. Attendi un paio di secondi finché si spegne.
5. Done!

[Video dimostrativo (in russo)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR {#aprimatic-tr}

- **Crealo così:** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xF` (sull'originale, tutti e 4 i tasti tenuti premuti insieme)

1. Apri il file del tuo nuovo telecomando.
2. Su un telecomando esistente che già funziona con il ricevitore, premi tutti e 4 i tasti contemporaneamente.
3. Il ricevitore emette un segnale acustico continuo.
4. Premi `Send` sul Flipper e tienilo premuto per circa 2 s.
5. Attendi che il ricevitore smetta di suonare.
6. Done?

## Beninca ARC (TO.GO) {#beninca-arc-to-go}

- **Venduto anche come:** TO.GO 2VA / 4VA (prima TO.GO 2WV / 4WV). Ricevitori WB, WI e ricevitori integrati nella centrale.
- **Crealo così:** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Tasto di programmazione:** **<kbd>↓</kbd>** = `0x0`, il tasto nascosto

Su un originale a 2 tasti, il tasto nascosto significa tenere premuti entrambi i tasti insieme, cosa difficile da fare in modo affidabile. Sul Flipper è un tasto solo: <kbd>↓</kbd>.

### Con un telecomando funzionante: ricevitori WB / WI {#beninca-wb-wi}

1. Mettiti vicino al ricevitore.
2. Apri il file del telecomando che già funziona. Premi <kbd>↓</kbd> e tieni premuto per circa 3 s. La funzione nascosta è ora attiva (qui il LED di un telecomando originale lampeggia).
3. Entro 5 s, premi `Send` su quello stesso telecomando per il canale che vuoi condividere.
4. Entro 5 s, apri il file del tuo nuovo telecomando e premi `Send`. Questo tasto controllerà quel canale.
5. Il ricevitore esce dalla modalità di programmazione. Prova il nuovo telecomando.
6. Done?

### Con un telecomando funzionante: ricevitore integrato nella centrale {#beninca-panel}

Qui il tasto nascosto deve essere inviato da **entrambi** i telecomandi:

1. Telecomando funzionante: <kbd>↓</kbd>, poi `Send` entro 5 s.
2. Nuovo telecomando: <kbd>↓</kbd>, poi `Send` entro 5 s.
3. Done?

::: info
I telecomandi ARC e HCS (codice rolling) non possono condividere lo stesso ricevitore. Il primo telecomando che memorizzi decide quale tipo il ricevitore accetterà da quel momento in poi. Cambiarlo richiede un reset completo del ricevitore.
:::

## BFT Mitto {#bft-mitto}

- **Crealo così:** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xF` (sull'originale, il foro per pin sul retro oppure i tasti 1+2 tenuti premuti insieme)

::: info Seed
**I telecomandi BFT Mitto più recenti derivano il loro Seed dal seriale**, quindi un normale `Sub-GHz → Read` li decodifica al volo. Compaiono subito come `KL: BFT`.
**I modelli più vecchi hanno un Seed unico** e vengono letti come `KL: Unknown` finché non lo possiedi. Ci sono due modi per recuperarlo:
- Tieni premuti 2 tasti e leggi il valore `Hop`. Il telecomando invia il suo Seed in chiaro (vedi [Creare un clone completo](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/it/subghz/seed-capturer) + qUnleashed.
:::

### Con un telecomando funzionante {#bft-with-remote}

1. Apri il file del tuo nuovo telecomando.
2. Mettiti ad almeno 3 m dal ricevitore.
3. **Telecomando originale:** premi il tasto nascosto sul retro con uno spillo, oppure premi i tasti 1 e 2 insieme, finché il LED del telecomando si accende.
4. **Telecomando originale:** premi brevemente il tasto che apre il dispositivo.
5. Sul Flipper, tieni premuto a lungo <kbd>→</kbd> (`0xF`, mostrato come `Btn:F`) per 3–5 s.
6. Premi il tasto del Flipper che vuoi usare per aprire il dispositivo.
7. Premi di nuovo <kbd>→</kbd>.
8. Done?

### Con accesso alla scatola del ricevitore {#bft-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola della scheda ricevitore.
3. [Guarda prima questo video](https://www.youtube.com/watch?v=5QXMBKI_-Ls). Mostra il lato scheda della procedura.
4. Sul Flipper, tieni premuto a lungo <kbd>→</kbd> (`0xF`) per 3–5 s. Fa esattamente ciò che nel video fa tenere premuti i tasti 1 e 2 sul telecomando originale.
5. Done?

### Creare un clone completo (legge il Seed dal tuo originale) {#making-a-full-clone-reads-the-seed-off-your-original}

::: danger
Questo crea una copia che **entra in conflitto con il tuo telecomando originale** per il contatore. Il tuo originale potrebbe anche smettere di funzionare finché non viene registrato di nuovo. Fallo solo se l'originale è rotto o consumato e il Flipper deve sostituirlo.
:::

1. Apri `Sub-GHz → Read`.
2. **Solo sul telecomando originale:** tieni premuti tutti i tasti insieme (entrambi su un telecomando a 2 tasti, i due della fila superiore su uno a 4 tasti), oppure premi il tasto nascosto con uno spillo.
3. Ricevi un segnale. Aprilo e guarda `Fix:`. Inizia con `F`, per esempio `F00F1C9B`. La `F` iniziale è il codice tasto per "tasto di programmazione premuto".
4. Il valore `Hop:` di quello stesso segnale è il tuo Seed.
5. Annota il valore `Hop` e sostituisci la sua prima cifra `F` con `0`.
6. Ora premi sul telecomando il tasto che vuoi davvero clonare, e leggi quel segnale.
7. Annota il suo `Fix:`. La sua prima cifra corrisponde al `Btn:` mostrato per quel segnale.
8. Crea il telecomando con `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` e inserisci:
   - `SERIAL`: il `Fix` del passaggio 7 con la sua **prima** cifra sostituita da `0`
   - `BUTTON`: la prima cifra di quel `Fix`
   - `COUNTER`: `FF F9`
   - `SEED`: il valore del passaggio 5
9. Un contatore alto come `FF F9` supera il contatore del tuo originale. Questo fa funzionare subito il clone, ed è anche ciò che desincronizza l'originale.

**Oppure modifica un file salvato.** Salva il segnale del tuo telecomando originale (uno più vecchio viene elencato come `KL: Unknown`), copia il file su un PC e aggiungi queste due righe dopo la riga `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Sostituisci le `X` con le cifre del Seed del passaggio 4 e ricopia il file sul dispositivo. Ora hai un clone esatto con lo stesso contatore.

### Nessun tasto nascosto, o non invia il Seed {#bft-no-hidden-button}

Questo vale solo per i telecomandi con un Seed unico. Un telecomando che viene già letto come `KL: BFT` non ha nulla da recuperare. Se non riesci a portare l'originale in modalità di programmazione, usa l'app [Seed Capturer](/it/subghz/seed-capturer): scegli `BFT Mitto` a 433.92 MHz, premi un tasto ripetutamente e poi recupera il Seed in qUnleashed.

## CAME Atomo {#came-atomo}

- **Venduto anche come:** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Crealo così:** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (oppure `868.35 AM650`)

::: warning
Con CAME Atomo tieni sempre premuto `Send` per **almeno 2 secondi**. Al protocollo serve tutto quel tempo per far uscire l'intero codice.
:::

### Con un telecomando funzionante (o la sua copia sul Flipper) {#atomo-with-remote}

1. Apri il file del tuo nuovo telecomando.
2. Mettiti ad almeno 3 m dal ricevitore.
3. **Telecomando originale:** premi e tieni premuto per circa 10 s il tasto associato a quel ricevitore.
4. Ora hai circa 20 s per aggiungere il nuovo telecomando.
5. Tieni premuto `Send` nel file del nuovo telecomando per 3–4 s e rilascia. Questo lo registra.
6. Attendi 20 s, poi premi e tieni premuto `Send` di nuovo. Ora dovrebbe comandare il ricevitore.
7. Done!

### Con accesso alla scatola del ricevitore {#atomo-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore e trova il tasto di programmazione del canale che ti serve. Alcuni ricevitori hanno più canali. Un RE432M / RE862M, per esempio, ne ha due, ciascuno con i propri telecomandi e tasti. Premi `1` o `2` sulla scheda per entrare in modalità di programmazione per quel canale.
3. Tieni premuto `Send` sul Flipper per 3–4 s e rilascia.
4. Premi `CLEAR` una volta per uscire dalla modalità di programmazione, oppure attendi circa 20 s.
5. Done!

::: info
I telecomandi CAME statici da 12/24 bit e i CAME TWEE non possono aprire la modalità di programmazione, e non possono essere registrati in una finestra aperta da un telecomando Atomo. Solo i telecomandi Atomo possono farlo.
:::

[Video dimostrativo (in russo)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449 {#cardin-s449}

- **Venduto anche come:** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Ricevitori RCQ449.
- **Leggilo con:** modulazione `FM12K`, **non** AM650
- **Crealo così:** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xD` (sull'originale, il tasto nel piccolo foro sotto i tasti)

1. Apri il file del tuo nuovo telecomando.
2. Mettiti a 1–2 m dal ricevitore.
3. Apri il file del telecomando che già funziona. Premi <kbd>→</kbd> e rilascialo quando il ricevitore emette un breve segnale acustico.
4. Premi `Send` su quello stesso telecomando una volta. Il ricevitore emette un altro breve segnale acustico.
5. Apri il file del tuo nuovo telecomando e premi `Send`. Il ricevitore emette due segnali acustici di seguito.
6. Rilascia il tasto. Il ricevitore emette un segnale acustico più lungo.
7. Attendi almeno 10 s, poi prova il nuovo telecomando.
8. Done?

**Se non funziona**, oppure se senti un segnale acustico lungo prima del passaggio 5, attendi 20 s e ricomincia dal passaggio 3.

## DEA Mio {#dea-mio}

- **Crealo così:** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xF`, il tasto nascosto

1. Apri il file del tuo nuovo telecomando.
2. `Send` funziona come uno dei tasti normali. È questo quello da registrare.
3. <kbd>→</kbd> funziona come il tasto nascosto del telecomando originale.
4. Segui le istruzioni del tuo produttore per aggiungere un telecomando, usando questi due tasti al posto di quelli dell'originale.

## Ditec GOL4 {#ditec-gol4}

- **Venduto anche come:** GOL4 / GOL4C. Ricevitori BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Crealo così:** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0x0`, il tasto nascosto

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore. Premi e rilascia `PRG`. Il LED `SIG` si accende e resta acceso.
3. Premi `Send` sul Flipper per il canale che vuoi memorizzare.
4. `SIG` lampeggia durante la memorizzazione. Quando torna fisso puoi aggiungere un altro telecomando.
5. La memorizzazione termina 10 s dopo l'ultimo telecomando, oppure premi di nuovo `PRG` per uscire subito.
6. Done?

::: info
Su alcune schede va impostato un ponticello sul ricevitore perché la programmazione funzioni. Controlla il manuale del tuo ricevitore.
:::

## DoorHan {#doorhan}

- **Crealo così:** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (oppure `315.00 AM650`)

### Trovare prima la frequenza {#doorhan-frequency}

DoorHan usa 315.00 oppure 433.92 MHz. Crea un telecomando su una delle due, aprilo e premi `Send` osservando il ricevitore. Se hai indovinato, la spia sul ricevitore si accende mentre tieni premuto il tasto e si spegne quando lo rilasci. Se non succede nulla, prova l'altra banda. Puoi anche leggere il tuo telecomando esistente con `Sub-GHz → Read`.

### Con accesso alla scatola del ricevitore {#doorhan-with-receiver}

Togli il coperchio di protezione e guarda i tasti:

- **4 tasti (`Radio`, `Reverse`, `Auto`, …):** tieni premuto `Radio` finché il LED si accende, poi premi `Send` sul Flipper 2 volte. Il LED si spegne.
- **4 tasti (`R`, `P`, `+`, `-`) e un display:** premi `R`, premi `Send` 2 volte, attendi circa 10 s.
- **4 tasti (`+`, `-`, `F`, `TR`) e un display:** premi `TR`, premi `Send` 2 volte, attendi circa 10 s.
- **Qualsiasi altra cosa:** tieni premuto `P` per circa 2 s finché il LED lampeggia, poi premi `Send` 2 volte. Il LED si spegne.

In tutti i casi, attendi che il ricevitore torni in modalità normale prima di provare.

### Con un telecomando originale in mano {#doorhan-with-original}

1. Apri il file del tuo nuovo telecomando.
2. Mettiti a 1–2 m dalla scheda ricevitore.
3. Sul vecchio telecomando, premi e mantieni premuto il secondo tasto (quello in basso), poi premi anche il primo (quello in alto). Tieni premuti entrambi per 1 s e rilascia.
4. Premi il tasto funzionante del vecchio telecomando (quello che apre il cancello). Tienilo premuto per 1 s e rilascia.
5. I passaggi 3 e 4 vanno eseguiti entro 5 s l'uno dall'altro. Non tenere premuto troppo a lungo e non avere fretta.
6. Il ricevitore emette un segnale acustico. Ora hai 10 s: premi `Send` sul nuovo telecomando 2 volte, tenendolo premuto almeno 1 s ogni volta.
7. Il ricevitore emette di nuovo un segnale acustico. Il nuovo telecomando è registrato.
8. Done!

### Con una copia del tuo telecomando originale sul Flipper {#doorhan-with-copy}

1. Apri il file del tuo telecomando **esistente (originale)**.
2. Mettiti a 1–2 m dalla scheda ricevitore.
3. Premi <kbd>←</kbd> (`0x8`), tieni premuto 1 s, rilascia. Poi premi <kbd>→</kbd> (`0xA`), tieni premuto 1 s, rilascia.
4. Premi il tasto funzionante (<kbd>OK</kbd>, `Send`), tieni premuto 1 s, rilascia.
5. I passaggi 3 e 4 vanno eseguiti entro 5 s l'uno dall'altro.
6. Il ricevitore emette un segnale acustico. Premi <kbd>Back</kbd> e apri il file del tuo **nuovo** telecomando. Entro 10 s, premi `Send` 2 volte, tenendolo premuto almeno 1 s ogni volta.
7. Il ricevitore emette di nuovo un segnale acustico. Il nuovo telecomando è registrato.
8. Done!

[Video dimostrativo (in russo)](https://www.youtube.com/watch?v=wZ5121HYv50) e [un secondo](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
Se un ricevitore DoorHan si è desincronizzato rispetto al tuo file, Unleashed ha modalità contatore di risincronizzazione forzata per DoorHan. Vedi [Modalità contatore](/it/subghz/counter-mode).
:::

## Erreka IRIS {#erreka-iris}

- **Venduto anche come:** IRIS IR02 / IR04 a 433.92 MHz, IR02/868 / IR04/868 a 868.35 MHz
- **Crealo così:** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` per IR02 / IR04, oppure `868.35 AM650` per i modelli /868
- **Tasto di programmazione:** <kbd>→</kbd> = `0xF` (sull'originale, ponticellando i pin `1` e `5` del connettore a 5 vie esposto sul fianco del telecomando)

Erreka IRIS è un telecomando a codice rolling: KeeLoq con un Seed segreto. Entrambi i metodi di registrazione del produttore funzionano dal Flipper.

### Con accesso alla scatola del ricevitore {#erreka-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Attiva la modalità di programmazione sul ricevitore, di solito con un tasto sulla scheda.
3. Premi `Send` sul Flipper una volta. Il ricevitore emette **due** segnali acustici se il telecomando è stato memorizzato.
4. Ripeti il passaggio 3 per eventuali altri telecomandi.
5. Disattiva la modalità di programmazione.
6. Done!

### Con un telecomando funzionante {#erreka-with-remote}

L'IRIS originale apre la finestra di programmazione quando ponticelli i pin `1` e `5`. Invia allora il suo Seed in chiaro, e il ricevitore risponde con un segnale acustico. Sul Flipper lo fa <kbd>→</kbd>.

Il telecomando che apre la finestra deve essere uno che il ricevitore conosce già: il primo telecomando Flipper che hai registrato tramite il tasto del ricevitore, oppure il tuo telecomando originale con il Seed recuperato (vedi sotto).

1. Apri il file del telecomando Erreka registrato.
2. Tieni premuto a lungo <kbd>→</kbd> (`0xF`) per circa 2 s. Il ricevitore emette **un** segnale acustico ed è pronto a memorizzare codici.
3. Entro 10 s, premi <kbd>Back</kbd> e apri il file del tuo nuovo telecomando.
4. Premi `Send`. Il ricevitore emette **due** segnali acustici se il telecomando è stato memorizzato.
5. Se passano 10 s senza che nulla venga memorizzato, il ricevitore esce dalla modalità di programmazione. Ricomincia dal passaggio 2.
6. Done?

### Se il nuovo telecomando non si registra {#erreka-shared-seed}

Alcune installazioni assegnano **lo stesso Seed a tutti i telecomandi**, perché l'installatore li ha programmati come un insieme. In quelle, un telecomando con Seed casuale non viene mai accettato. La soluzione è mantenere il Seed esistente e cambiare solo il seriale:

1. Ricava il Seed da un telecomando che già funziona (vedi sotto).
2. Crea un telecomando con `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (oppure `868.35 AM650`) e inserisci:
   - `SERIAL`: `0X XX XX XX`, qualsiasi valore che non sia uno dei tuoi telecomandi esistenti. **Mantieni lo `0` iniziale.** Quel nibble è il tasto, che viene richiesto separatamente.
   - `BUTTON`: `02`
   - `COUNTER`: `00 02`
   - `SEED`: il Seed del passaggio 1
3. Esegui di nuovo una delle due procedure di registrazione.

::: tip Mantieni gli zeri iniziali
Alcuni sistemi usano solo le ultime 3 o 4 cifre del seriale, quindi i loro telecomandi hanno un aspetto come `00 00 0A BC`. Su quelli, un seriale casuale lungo può essere rifiutato. Leggi uno dei tuoi telecomandi funzionanti, copia la forma del suo seriale (stesso numero di cifre significative, zeri iniziali mantenuti) e cambia solo le ultime cifre. Se due dei tuoi telecomandi originali mostrano lo stesso Seed dopo il recupero, hai un'installazione di questo tipo, e riutilizzare il Seed è la scelta giusta.
:::

### Come ricavare il Seed dal tuo telecomando IRIS originale {#erreka-get-seed}

Un telecomando Erreka viene letto come `KL: Unknown` finché il Seed non è noto.

**Opzione 1: cortocircuitare i pin e leggerlo.** È la via rapida. I pin sono all'esterno del guscio.

1. Apri `Sub-GHz → Read`. In `Config`, imposta la frequenza su 433.92 o 868.35 e la modulazione su `AM650`.
2. Ponticella i pin `1` e `5` del connettore a 5 vie sul telecomando originale.
3. Ricevi un segnale. Il produttore viene mostrato come **Unknown**. È normale, perché il Flipper non conosce ancora il Seed.
4. Apri il segnale. `Fix:` inizia con `F`, il codice di "tasto di programmazione premuto".
5. **Il valore `Hop:` di quel segnale è il tuo Seed**, in chiaro.
6. Puoi digitarlo in `Add Manually [Advanced]` come sopra, oppure salvare il segnale, copiarlo su un PC e aggiungere queste righe dopo `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

Il file ora si decodifica, e puoi usarlo per aprire la finestra di programmazione per nuovi telecomandi.

**Opzione 2: [Seed Capturer](/it/subghz/seed-capturer)**, quando non puoi ponticellare i pin. Scegli `Erreka` e la tua frequenza, premi un tasto ripetutamente, poi recupera il Seed in qUnleashed.

## FAAC RC, XT {#faac-rc-xt}

- **Venduto anche come:** XT2 / XT4 433 RC / 868 RC, e la vecchia codifica RC
- **Crealo così:** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (oppure `868.35 AM650`)
- **Tasto di programmazione:** <kbd>→</kbd> = `0xB` (sull'originale, i tasti 1+2 tenuti premuti insieme, la pressione "master")

::: warning
Questi sono KeeLoq, non SLH. Leggi prima il tuo telecomando. Se il Flipper lo chiama `KL: FAAC_RC,XT`, sei nel posto giusto. Se dice `FAAC SLH`, vai a [FAAC SLH](#faac-slh).
:::

1. Apri il file del tuo nuovo telecomando.
2. Mettiti vicino al ricevitore.
3. Apri il file del telecomando che già funziona. Premi <kbd>→</kbd> e tieni premuto per circa 1–2 s (fino a quando il LED dell'originale inizierebbe a lampeggiare), poi rilascia.
4. Mentre la finestra è aperta, premi `Send` su quello stesso telecomando per il tasto che vuoi copiare.
5. Apri il file del tuo nuovo telecomando e premi `Send`.
6. Ripeti i passaggi 3–5 per ogni altro tasto.
7. Done?

::: info
Solo un telecomando **master** può trasmettere il proprio codice di sistema. Su un telecomando originale, osserva il LED quando premi un tasto. Un breve lampeggio prima che diventi fisso significa master. Fisso subito significa slave. Con uno slave, registra invece il nuovo telecomando dal ricevitore.
:::

## FAAC SLH {#faac-slh}

- **Crealo così:** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (oppure `868.35 AM650`)
- **Tasto di programmazione:** **<kbd>↑</kbd>** invia il segnale di programmazione

### Con accesso alla scatola del ricevitore {#faac-slh-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore e trova il tasto di programmazione sulla scheda.
3. Tieni premuto <kbd>↑</kbd> sul Flipper e, contemporaneamente, premi e tieni premuto il tasto di programmazione sulla scheda.
4. Il LED della scheda si accende, si spegne, si accende, si spegne e poi si accende di nuovo.
5. Rilascia tutto.
6. Premi `Send` sul Flipper un paio di volte, tenendo premuto ogni volta per 1–3 s.
7. Done!

[Video dimostrativo](https://www.youtube.com/watch?v=NfZmMy37XUs)

### Con un telecomando master, senza aprire la scatola {#faac-slh-with-master}

FAAC può registrare nuovi telecomandi a partire da un telecomando master esistente, e il Flipper può partecipare. Prima ricava il Seed dal master:

1. Apri `Sub-GHz → Read`. Imposta la frequenza su 868.35 o 433.92 e la modulazione su `AM650`.
2. Tieni premuti due tasti sul telecomando master originale finché il suo LED si accende.
3. Premi il singolo tasto di cui vuoi il Seed. **Il Seed è diverso per ogni tasto.**
4. Ricevi un segnale. Aprilo e annota il Seed.
5. Crea il telecomando con `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (oppure 868.35) e inserisci:
   - `SERIAL`: `0A 0R RR RR`, sostituendo ogni `R` con una cifra qualsiasi
   - `BUTTON`: `06`
   - `COUNTER`: `00 00 00 02`
   - `SEED`: il Seed del passaggio 4
6. Il Flipper si comporta ora come un nuovo telecomando. Premi `Send` un paio di volte vicino al ricevitore per registrarlo.
7. Done!

### Se nessuna delle due cose è possibile {#if-neither-of-those-is-possible}

- **La programmazione radio del ricevitore è disabilitata.** Alcuni installatori la disattivano, e allora non si registra nulla.
- **Il tuo telecomando è uno slave, non un master.** Solo un master può inviare il codice di programmazione.

In entrambi i casi l'unica strada che resta è un **clone** di un telecomando che il ricevitore conosce già, e questo richiede il Seed. Ricavalo con [Seed Capturer](/it/subghz/seed-capturer), poi costruisci il clone con il `SERIAL` e il `BUTTON` del **telecomando originale**.

::: tip Dove si trovano SERIAL e BUTTON all'interno di Fix
- **FAAC SLH e Genius:** `BUTTON` è l'**ultima** cifra di `Fix`. `SERIAL` è il resto, con uno `0` davanti.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin e le altre voci `KL:`): `BUTTON` è la **prima** cifra di `Fix`. `SERIAL` è lo stesso `Fix` con la sua prima cifra sostituita da `0`.
:::

## Genius (SLH) {#genius-slh}

- **Venduto anche come:** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Crealo così:** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (oppure `868.35 AM650`)
- **Tasto di programmazione:** **<kbd>↑</kbd>** invia il segnale di programmazione

Genius SLH usa lo stesso pacchetto di FAAC SLH con una chiave del produttore propria (una riga `Manufacture: Genius` nel file), quindi **[le procedure FAAC SLH](#faac-slh) si applicano esattamente come sono scritte**. Se la programmazione è disabilitata o il tuo telecomando è uno slave, acquisisci il Seed con [Seed Capturer](/it/subghz/seed-capturer) (scegli `Genius`) e costruisci un clone come descritto sotto FAAC SLH.

::: warning
Non confonderlo con `KL: Genius TX4RC`. I modelli RC sono KeeLoq, non SLH, e hanno [una sezione propria](#genius-tx4rc-bravo-echo). Se non sei sicuro, leggi prima il telecomando.
:::

## Genius TX4RC (Bravo / Echo) {#genius-tx4rc-bravo-echo}

- **Venduto anche come:** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Crealo così:** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xB`

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore e premi `SW1` per il canale 1 o `SW2` per il canale 2. `LED1` / `LED2` si accende e resta acceso. È la modalità di apprendimento.
3. Entro 10 s, premi `Send` sul Flipper e tieni premuto almeno 1 s.
4. Il LED lampeggia due volte. Il telecomando è memorizzato.
5. Il ricevitore resta in modalità di apprendimento, quindi puoi aggiungere altri telecomandi ripetendo il passaggio 3. Premi di nuovo `SW1` / `SW2` per uscire, oppure esce da sé 10 s dopo l'ultimo telecomando.
6. Done?

## Hormann EcoStar {#hormann-ecostar}

- **Venduto anche come:** RSC2 / RSE2 / RSZ1 a 433.92 MHz. Motorizzazioni EcoStar Liftronic / Portronic.
- **Crealo così:** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Tasto di programmazione:** **<kbd>↓</kbd>** = `0x6` (questo è su Giù, non su Destra)

1. Apri il file del tuo nuovo telecomando.
2. Trova il tasto di cancellazione/programmazione sulla motorizzazione, di solito sotto il motore, e tienilo premuto per circa 1 s. Il LED del motore inizia a lampeggiare lentamente.
3. Premi `Send` e tieni premuto per circa 2 s. Il LED del motore accelera.
4. Premi `Send` di nuovo e tieni premuto per circa 2 s. Il LED lampeggia molto rapidamente, poi si spegne. Il telecomando è programmato.
5. Done?

::: danger
Tenere premuto quel tasto di cancellazione per circa 5 s cancella **tutti** i telecomandi che la motorizzazione conosce.
:::

## Jarolift {#jarolift}

- **Venduto anche come:** motori tubolari radio TDEF con telecomandi TDRC / TDRCE
- **Crealo così:** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

I tasti sono già mappati sui tasti del telecomando originale:

| Tasto del Flipper | Tasto Jarolift |
|---|---|
| <kbd>OK</kbd> (`Send`) | Down |
| <kbd>←</kbd> | Up |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

Sull'originale, `Learn` significa tenere premuti Up + Down insieme e poi premere Stop. Sul Flipper è una sola pressione di tasto.

### Con accesso alla testa motore {#jarolift-motor}

1. Apri il file del tuo nuovo telecomando.
2. Premi il tasto di apprendimento sulla testa motore. Il motore vibra brevemente e resta in modalità di apprendimento per 5 s.
3. Se non riesci a raggiungere quel tasto, scollega il motore dalla rete e ricollegalo. Entra da sé in modalità di apprendimento per 5 s.
4. Entro quei 5 s, premi <kbd>↑</kbd> (`Learn`).
5. Il motore vibra di nuovo. Il codice è stato appreso.
6. Done!

### Con un telecomando funzionante {#jarolift-with-remote}

1. Apri il file del tuo nuovo telecomando.
2. Sul telecomando funzionante, tieni premuti Up + Down insieme, poi premi Stop 8 volte. Il motore vibra brevemente.
3. Entro 5 s, premi <kbd>↑</kbd> (`Learn`) sul Flipper.
4. Il motore vibra di nuovo.
5. Done?

::: tip
Se il telecomando funzionante è anche sul tuo Flipper, il passaggio 2 è <kbd>↑</kbd> (`Learn`) nel file di quel telecomando.
:::

## KingGates Stylo 4k {#kinggates-stylo-4k}

- **Venduto anche come:** Stylo 2K / Stylo 4K (10S001). Ricevitori Fred, Myo.
- **Crealo così:** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

Non c'è un tasto di programmazione separato. I quattro tasti sono i quattro canali dell'originale:

| Tasto del Flipper | Codice canale |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Apri il file del tuo nuovo telecomando.
2. Apri la scatola del ricevitore. Su un `Fred` a 2 canali, il colore del LED indica il canale: verde è il canale 1, rosso il canale 2.
3. Premi il tasto del ricevitore una volta per il canale 1 (verde) oppure due volte per il canale 2 (rosso). Questo avvia la modalità di apprendimento.
4. Entro 5 s, premi `Send` sul Flipper per circa 1 s.
5. Il LED si spegne e poi si riaccende. Il telecomando è stato appreso.
6. L'apprendimento termina dopo 5 s senza segnale, oppure premi di nuovo il tasto del ricevitore.
7. Done?

## Mhouse {#mhouse}

- **Venduto anche come:** GTX4 / GTX4C / TX3 / TX4, e anche Moovo e Nice Home ECCO
- **Crealo così:** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xF`, il tasto aggiuntivo (nascosto)

### Con accesso alla scatola del ricevitore {#mhouse-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Premi e tieni premuto `P1` sul ricevitore finché il LED `P1` resta acceso, poi rilascia.
3. Premi `Send` e tieni premuto finché il LED `P1` lampeggia 3 volte.
4. Rilascia. Questo registra tutti i tasti del telecomando in una volta (Nice "modo 1").
5. Attendi 10 s prima di provare.
6. Done?

### Con un telecomando funzionante {#mhouse-with-remote}

Mhouse appartiene alla stessa famiglia di ricevitori Nice di [Nice Smilo](#nice-smilo):

1. Mettiti vicino al ricevitore.
2. Apri il file del tuo nuovo telecomando. Premi e tieni premuto `Send` per almeno 5 s, poi rilascia.
3. Sul telecomando funzionante, premi e rilascia lentamente il suo tasto 3 volte.
4. Apri di nuovo il file del nuovo telecomando, premi `Send` per 1 s e rilascia.
5. Attendi 10 s prima di provare.
6. Done?

## Nice Flor S {#nice-flor-s}

- **Crealo così:** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### Con un telecomando funzionante {#nice-flor-s-with-remote}

Non ti serve la scatola del ricevitore, ma **il primissimo telecomando va sempre registrato con il tasto del ricevitore**. Qui sotto, `OLD` è il telecomando autorizzato e `NEW` è il Flipper. Mettiti entro 3 m dal ricevitore.

1. Apri il file del tuo nuovo telecomando. Premi e tieni premuto `Send` per almeno 5 s (7 s su un ricevitore OXIBD), poi rilascia.
2. Su `OLD`, premi il suo tasto 3 volte lentamente.
3. Premi `Send` sul Flipper lentamente, poi rilascia.
4. Attendi 10 s, poi premi `Send` per provare.
5. Done?

### Con accesso alla scatola del ricevitore {#nice-flor-s-with-receiver}

Registralo come descrive il manuale del tuo telecomando originale. Per un tipico ricevitore NICE FLOX2R:

1. Apri il file del tuo nuovo telecomando.
2. Premi il tasto di apprendimento sul ricevitore per 1–2 s. Il LED si accende per 5 s. Esegui il passaggio successivo entro quei 5 s.
3. Premi `Send` finché il LED sul ricevitore si spegne.
4. Rilascia e attendi 2 s.
5. Premi `Send` di nuovo. Il LED lampeggia 3 volte e il telecomando è registrato. Se non succede, ricomincia dal passaggio 2.
6. Attendi 5 s, poi premi `Send` per provare.
7. Done!

::: tip
Le varianti di contatore Nice Flor-S per ricevitori specifici (floxi2r, ox2) sono disponibili come
[modalità contatore](/it/subghz/counter-mode).
:::

## Nice One {#nice-one}

- **Crealo così:** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One appartiene alla famiglia Nice FloR-S con una cifratura diversa, e il lato ricevitore è identico. **[Entrambe le procedure Nice Flor S](#nice-flor-s) si applicano esattamente come sono scritte.** Se il tuo telecomando viene letto come FloR-S ma il contatore sembra sbagliato, potrebbe trattarsi invece di Nice O-Code.

## Nice O-Code {#nice-o-code}

- **Crealo così:** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (oppure `Nice O-Code One` per la cifratura Nice One)
- **Crealo per un sistema già installato:** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, che chiede `SERIAL`, `BUTTON`, `COUNTER` e il codice installatore (`Enter IC in hex`)
- **Crealo con un certificato:** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, che chiede sempre seriale, tasto, contatore, codice installatore **e** il certificato del ricevitore (`Enter CERT in hex`)

O-Code è Nice FloR-S cifrato con un **codice installatore (IC)** a 16 bit condiviso da tutti i telecomandi di un'installazione. Il lato ricevitore è lo stesso di FloR-S, quindi si applicano [entrambe le procedure Nice Flor S](#nice-flor-s), ma un telecomando raggiunge solo un ricevitore configurato con lo stesso codice installatore.

- **Per un sistema tutto tuo**, il semplice `Nice O-Code` inventa un codice installatore insieme al seriale. Un ricevitore di fabbrica non lo accetterà tramite il tasto, quindi registra prima un normale telecomando [Nice One](#nice-one).
- **Per un sistema già installato**, recupera il codice installatore da un telecomando funzionante con l'[app Nice O-Code](/it/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`). Premi il tasto del telecomando 4 o più volte (non tenerlo premuto). Nella schermata del risultato, <kbd>→</kbd> (`New`) scrive un nuovo telecomando con lo stesso codice installatore e tasto ma con seriale e contatore propri. È quello da registrare. `Save` scrive un semplice clone per i test.

::: info Provato su un OXIBD appena uscito di fabbrica
In modo I il ricevitore **ignora completamente i pacchetti O-Code**, qualunque codice installatore portino, mentre un normale telecomando `Nice One` viene memorizzato subito. Solo un O-Box scrive il codice installatore nel ricevitore. Su un ricevitore intonso usa le voci semplici Nice Flor S / Nice One.
:::

::: tip COUNTER
**Non** lasciare `COUNTER` vicino a zero. Il ricevitore rifiuta un conteggio più basso di quello che ha memorizzato, e anche uno che risulti implausibilmente indietro rispetto ai telecomandi che conosce, perfino per un seriale nuovo. Impostalo un po' sotto il conteggio del tuo telecomando funzionante (il `New` dell'app lo fa per te). Se hai già inviato pacchetti da quel seriale, usa un valore un po' sopra il più alto che hai inviato.
:::

**Registrazione con certificato.** Un telecomando che porta il certificato del ricevitore invia pacchetti da 112 bit durante i suoi primi **venti** utilizzi, e il ricevitore lo registra da sé. Apri il file a portata del cancello e premi il tasto circa una volta al secondo, **da dieci a quindici volte di seguito**. Il cancello si apre intorno alla decima pressione, e da quel momento il telecomando è registrato definitivamente. Se passano tutti e venti gli utilizzi senza che il cancello si apra, elimina il file e creane uno nuovo. Certificati, i cinque percorsi di registrazione Nice, i codici LED del ricevitore e la finestra del contatore sono trattati in dettaglio nella pagina [Nice O-Code](/it/subghz/nice-o-code).

## Nice Smilo {#nice-smilo}

- **Venduto anche come:** SM2 / SM4. Ricevitori SMXI, SMXIS e OXI impostati sulla codifica Smilo.
- **Crealo così:** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0xB`, il tasto aggiuntivo (nascosto)

I ricevitori Nice memorizzano un telecomando in uno di due modi. Il **modo I** assegna a ogni tasto del telecomando l'uscita corrispondente del ricevitore. Il **modo II** permette di scegliere quale uscita controlla un singolo tasto.

### Con accesso alla scatola del ricevitore: modo I {#smilo-mode-1}

1. Apri il file del tuo nuovo telecomando.
2. Premi e tieni premuto il tasto del ricevitore per almeno 3 s.
3. Rilascialo quando il LED si accende.
4. Entro 10 s, premi `Send` e tieni premuto per almeno 2 s.
5. Il LED del ricevitore lampeggia 3 volte. Il telecomando è memorizzato.
6. Per aggiungerne altri, ripeti il passaggio 4 entro altri 10 s.
7. Done!

### Con accesso alla scatola del ricevitore: modo II {#smilo-mode-2}

1. Apri il file del tuo nuovo telecomando.
2. Premi il tasto del ricevitore tante volte quanto il numero dell'uscita (due volte per l'uscita 2).
3. Verifica che il LED lampeggi lo stesso numero di volte.
4. Entro 10 s, premi il tasto del Flipper che vuoi per quell'uscita e tieni premuto per almeno 2 s.
5. Il LED lampeggia 3 volte. Il telecomando è memorizzato.
6. Done!

### Con un telecomando funzionante {#smilo-with-remote}

Il primo telecomando va sempre registrato con il tasto del ricevitore. Il nuovo telecomando **eredita il modo** di quello vecchio, quindi con il modo II premi i tasti corrispondenti su entrambi.

1. Mettiti vicino al ricevitore.
2. Apri il file del tuo nuovo telecomando. Premi e tieni premuto `Send` per almeno 5 s, poi rilascia.
3. Sul telecomando funzionante, premi e rilascia lentamente il suo tasto 3 volte.
4. Apri di nuovo il nuovo file e premi e rilascia lentamente `Send` una volta.
5. Done?

::: info
Questi ricevitori non possono eliminare un singolo telecomando, solo tutti insieme.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman) {#security-1-0-2-0-chamberlain-liftmaster-craftsman}

- **Crealo così:** `Sub-GHz → Add Manually → Security+2.0` oppure `Security+1.0`, poi la banda. Il valore predefinito è `433.92 AM650`. Security+ 1.0 propone anche `315.00 AM650` e `390.00 AM650`. Security+ 2.0 propone `310.00`, `315.00` e `390.00 AM650`.

**Quale dei due hai?** Guarda il colore del tasto `Learn` sulla testa motore:

| Tasto Learn | Crea questo |
|---|---|
| Giallo | `Security+2.0` |
| Viola | `Security+1.0` → `315.00 AM650` |
| Verde | `Security+1.0` → `390.00 AM650` |
| Rosso / arancione | Billion Code, non Security+ |
| Grigio / bianco | telecomando a dip switch, non Security+ |

1. Apri il file del tuo nuovo telecomando.
2. Trova `Learn` sulla testa motore: di solito sul retro o sul pannello laterale, a volte dietro la lente della luce.
3. Premilo e rilascialo una volta. Il LED di apprendimento resta acceso fisso per 30 s.
4. Entro quei 30 s, premi e tieni premuto `Send` sul Flipper.
5. Rilascia quando le luci del motore lampeggiano o senti due clic. Il telecomando è programmato.
6. Premi `Send` di nuovo per verificare che la porta si muova.
7. Done?

::: tip
Se il tasto sulla testa motore non collabora, alcuni sistemi permettono di programmare dalla pulsantiera a muro. Per i pacchetti di tastiera Security+ 2.0, vedi [Security+ PIN](/it/subghz/secplus-pin).
:::

## Somfy Keytis {#somfy-keytis}

- **Venduto anche come:** Keytis NS 2 RTS / KeyGo 4 RTS
- **Crealo così:** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (questa è **433.42 MHz**, non 433.92)
- **Tasto di programmazione:** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` è `Key_1`)

Un Keytis originale non ha un tasto `Prog` sul fronte. Si ponticellano le due piazzole `PROG` sul retro della scheda con un cacciavite. Al Flipper serve solo <kbd>↑</kbd>.

### Con accesso al ricevitore {#keytis-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Premi e tieni premuto `PROG` sul ricevitore per circa 3 s, finché lampeggia.
3. Premi <kbd>↑</kbd> (`Prog`) sul Flipper.
4. La tapparella o il cancello si muove brevemente su e giù. Il telecomando è registrato.
5. Done?

### Con un telecomando funzionante {#keytis-with-remote}

1. Apri il file del tuo nuovo telecomando.
2. Porta il telecomando registrato in modalità di programmazione finché la tapparella o il cancello si muove brevemente. Su un Keytis originale, ponticella le piazzole `PROG`. Sul Flipper, premi <kbd>↑</kbd> nel file di quel telecomando.
3. Apri il file del tuo nuovo telecomando e premi <kbd>↑</kbd> (`Prog`) finché la tapparella o il cancello si muove brevemente di nuovo.
4. Done?

::: danger
Su molti ricevitori Somfy, tenere premuto il tasto di programmazione per più di circa 7 s cancella tutti i telecomandi e i sensori che conosce.
:::

::: info
Keytis usa il più recente protocollo radio `NS`. Un vecchio ricevitore RTS non-NS non lo accetterà finché il protocollo del telecomando non viene commutato. Vedi la documentazione Somfy del tuo ricevitore.
:::

## Somfy Telis {#somfy-telis}

- **Crealo così:** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (questa è **433.42 MHz**, non 433.92)
- **Tasto di programmazione:** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Apri il file del tuo nuovo telecomando.
2. Tieni premuto a lungo `Prog` su un telecomando già registrato nel dispositivo, finché le tapparelle si muovono brevemente su e giù.
3. Premi e tieni premuto <kbd>←</kbd> (`Prog`) sul Flipper finché le tapparelle si muovono brevemente su e giù di nuovo.
4. Done?

## Sommer {#sommer}

- **Venduto anche come:** TX03-868-4 / TX03-868-2 (SOMloq). Motorizzazioni Pearl, Duo, Sprint, Marathon.
- **Leggilo con:** modulazione `FM12K` o `FM476`, quella che decodifica il tuo telecomando
- **Crealo così:** `Sub-GHz → Add Manually → KL: Sommer`, poi scegli la banda corrispondente a come è stato letto il tuo telecomando: `434.42 FM12K` (predefinita), `868.80 FM12K`, `434.42 FM476` oppure `868.80 FM476`
- **Tasto di programmazione:** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Le guide più vecchie elencano quattro voci Sommer separate (`fm2` e semplice). Il firmware attuale ha una sola riga `KL: Sommer`, e il selettore di banda sceglie sia la frequenza sia la variante di modulazione.
:::

### Con accesso al ricevitore {#sommer-with-receiver}

1. Apri il file del tuo nuovo telecomando.
2. Trova il tasto `learn` / `code` sul ricevitore. Su un Duo è sotto il coperchio della luce, su uno Sprint dietro il coperchio della scatola dell'interruttore, e su un Marathon sotto un coperchio di plastica trasparente accanto al tasto del codice.
3. Premilo brevemente. Il LED del ricevitore si accende.
4. Premi e tieni premuto `Send`. Quando il LED del ricevitore inizia a lampeggiare rapidamente, rilascia.
5. Il LED del ricevitore si spegne. Il telecomando è programmato.
6. Done?

### Su una motorizzazione per cancello scorrevole {#sommer-sliding-gate}

Premi invece il tasto `Radio` sulla centrale. Un LED rosso conferma la modalità di programmazione. Premilo di nuovo per scegliere il canale, poi tieni premuto `Send` finché il LED del canale lampeggia e si spegne. Il ricevitore esce da sé dalla modalità di programmazione dopo circa 30 s senza segnale.

## V2 Phoenix (Phox) {#v2-phoenix-phox}

- **Venduto anche come:** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Ricevitori RXP, MR2.
- **Crealo così:** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Tasto di programmazione:** <kbd>→</kbd> = `0x3` (sull'originale, i tasti 1+2 o 1+3 tenuti premuti insieme)

::: warning
Questa mappatura **non è ancora confermata**. Se non funziona, registra dal tasto del ricevitore e segnalalo nelle issue di Unleashed.
:::

1. Apri il file del tuo nuovo telecomando.
2. Apri il file del telecomando registrato. Premi <kbd>→</kbd> e tieni premuto per almeno 5 s, poi rilascia.
3. Entro 5 s, apri il file del nuovo telecomando e premi `Send`.
4. Rilascia. Ripeti per eventuali altri tasti.
5. Done?

Il telecomando che apre la finestra deve essere già memorizzato nel ricevitore, e tutto ciò che viene memorizzato in questo modo erediterà la sua logica. Se aveva memorizzato solo il tasto 1, i nuovi telecomandi potranno essere memorizzati solo sul tasto 1. Alcuni ricevitori V2 possono essere commutati in modalità `Static`, che ignora la parte rolling della chiave.

---

## Recuperare un Seed {#recovering-a-seed}

**FAAC SLH**, **Genius**, **Erreka** e **BFT Mitto** costruiscono il loro codice rolling a partire da un **Seed** segreto. Senza di esso il Flipper non può decodificare quei telecomandi (vengono letti come `KL: Unknown` oppure non vengono letti affatto) e non può costruire un telecomando che il ricevitore accetti. Ti serve il Seed quando:

- la programmazione radio del ricevitore è disattivata, quindi funziona solo un clone;
- il tuo telecomando FAAC/Genius è uno slave e non può inviare il codice di programmazione;
- non riesci ad arrivare al ricevitore;
- un'installazione Erreka condivide un solo Seed tra tutti i telecomandi;
- un BFT Mitto più vecchio non entra in modalità di programmazione.

L'app [Seed Capturer](/it/subghz/seed-capturer) (`Apps → Sub-GHz → Seed Capturer`) raccoglie coppie `Fix` + `Hop` consecutive da un solo tasto. Non trasmette mai, e le salva in `/ext/apps_data/subghz_seed_captures/`. L'app companion qUnleashed (vedi [App qUnleashed](/it/mobile/qunleashed-app)) ricava poi il Seed in forza bruta e può scrivere al posto tuo il file del clone già pronto.

Una volta che hai il Seed:

- **Nuovo telecomando** (il ricevitore deve accettare nuovi telecomandi): `Add Manually [Advanced]` → il tuo sistema →
  banda, il tuo `SERIAL` e il `SEED` recuperato.
- **Clone** (funziona senza programmazione, perché il ricevitore conosce già quel seriale): lascia che lo salvi
  qUnleashed, oppure inserisci il `SERIAL` e il `BUTTON` dell'**originale**, il `SEED` e un `COUNTER` un po' sopra il
  valore attuale dell'originale.

::: danger
Un clone condivide il contatore con l'originale e i due se lo contenderanno. Clona solo quando creare un nuovo telecomando è impossibile.
:::

## Riferimento dei tasti di programmazione / nascosti {#programming-hidden-button-reference}

Trova il passaggio "porta il ricevitore in modalità di programmazione" nel manuale del tuo produttore. Dove ti dice di premere qualcosa sul telecomando originale, premi invece il tasto di questa tabella.

::: info
Questi sono i tasti di un telecomando come lo crea `Add Manually`. Se cambi il codice tasto a mano, i tasti si spostano di conseguenza.
:::

| Sistema (voce di Add Manually) | Codice | Tasto sul Flipper | Sul telecomando originale |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | il segnale di programmazione |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | foro per pin sul retro, oppure tasti 1+2 tenuti premuti |
| `Erreka` | `0xF` | <kbd>→</kbd> | pin 1 e 5 del connettore a 5 vie ponticellati |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | tasto nascosto |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | tutti e 4 i tasti tenuti premuti insieme |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | tasti 1+2 tenuti premuti (pressione master) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | tasto della modalità di programmazione |
| `KL: Monarch` | `0xB` | *nessuna freccia lo invia* | imposta il codice tasto a mano nelle impostazioni del segnale |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | tasto aggiuntivo / nascosto *(non confermato)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `KL: Sommer` (tutte le bande) | `0x6` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | tasto aggiuntivo / nascosto |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | tasto nel foro sotto i tasti |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | tasto aggiuntivo / nascosto |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | tasto nascosto (tasti 1+2 tenuti premuti) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | tasto nascosto |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn`: Up+Down tenuti premuti, poi Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | tasto `Prog` |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | piazzole `Prog` sul retro della scheda |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | tasti 1+2 o 1+3 tenuti premuti *(non confermato)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | tasto 3 *(non confermato come tasto di programmazione)* |

### Tutto il resto nel menu {#everything-else}

Qualsiasi voce che non sia in questa tabella e non abbia una sezione sopra si registra nel modo semplice: **porta il ricevitore in modalità di apprendimento con il suo stesso tasto, poi premi `Send` sul Flipper entro la finestra temporale indicata dal produttore.**

Questo copre la maggior parte dei sistemi KeeLoq (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) e tutti i protocolli statici, come CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero e [ZKTeco](/it/subghz/zkteco-cmp200).

## Quando non funziona {#troubleshooting}

- **Non succede assolutamente nulla.** Controlla prima la frequenza. È l'errore più comune. Leggi il tuo telecomando originale con `Sub-GHz → Read` e confronta. Alcune marche vendono lo stesso telecomando su due frequenze: DoorHan su 315 e 433.92, FAAC e Genius su 433.92 e 868.35. Usa il [Frequency Analyzer](/it/subghz/frequency-analyzer) se non sei sicuro.
- **Modulazione sbagliata.** La maggior parte dei sistemi qui usa `AM650`, ma Cardin S449 usa `FM12K` e Sommer `FM12K` o `FM476`. Impostala in `Sub-GHz → Read → Config` e scegli la banda corrispondente in Add Manually.
- **Il ricevitore reagisce ma non memorizza mai il telecomando.** Probabilmente stai mancando la finestra temporale. Rileggi i passaggi e tieni il file del telecomando già aperto prima di toccare il tasto del ricevitore.
- **Ha memorizzato il telecomando ma non apre niente.** Tieni premuto `Send` più a lungo. Diversi protocolli hanno bisogno di 1–3 s per far uscire un codice completo, e CAME Atomo richiede almeno 2 s ogni volta.
- **Ha funzionato una volta e poi ha smesso.** Su un sistema a codice rolling è un problema di contatore: hai clonato un telecomando invece di crearne uno nuovo. Premi `Send` qualche altra volta di fila, perché il ricevitore accetta un contatore andato avanti entro una certa finestra. Per mantenere funzionanti entrambi i telecomandi, crea invece un nuovo telecomando (vedi [Codici rolling](/it/subghz/rolling-codes)). Un telecomando statico non ha contatore, quindi se smette di funzionare controlla la batteria, la frequenza o il ricevitore.
- **Tutti i tuoi telecomandi hanno smesso di funzionare.** Molto probabilmente hai tenuto premuto un tasto di programmazione abbastanza a lungo da attivare la funzione di cancellazione del ricevitore. Registra di nuovo tutti i telecomandi, originali compresi.

## Fonti e manuali {#sources}

- [FAAC SLH: video dimostrativo](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Analisi del protocollo Somfy RTS](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS: istruzioni di installazione](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Registrazione Somfy Keytis NS 2 RTS (forum Somfy)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [Manuale BFT Mitto](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [Programmazione del ricevitore NICE FLOX2R](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Programmazione Nice Flor S](https://motepro.com.au/Instructions/Nice.pdf)
- [Manuale Nice Smilo SM2/SM4 e del ricevitore SMXI](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code: manuali per installatori da [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, ricevitore FLOR `IS0063A00MM`, trasmettitori Era One `IS0102A01MM`)
- [Programmazione Mhouse GTX4 / TX4 / Nice Home ECCO5](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS: `Guia rapida mando IRIS` (MSR-044/03), da [erreka.com](https://www.erreka.com/)
- [Manuale del motore Jarolift TDEF](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Programmazione dei trasmettitori Beninca TO.GO](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Manuale dei ricevitori Ditec BIX L / BIX A](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Istruzioni di programmazione Cardin S449 QZ2](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Manuale del ricevitore Cardin RCQ449](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Manuale del telecomando Hormann RSC2](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer: come programmare un trasmettitore su una motorizzazione per cancello scorrevole](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [Manuale del ricevitore V2 RXP4: apprendimento radio](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [Programmazione del ricevitore KingGates Fred](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Pagine correlate {#related}

- [Add Manually](/it/subghz/add-manually)
- [Codici rolling](/it/subghz/rolling-codes)
- [KeeLoq](/it/subghz/keeloq)
- [Modalità contatore](/it/subghz/counter-mode)
- [Sistemi supportati](/it/subghz/supported-systems)
- [Seed Capturer](/it/subghz/seed-capturer) · [Nice O-Code](/it/subghz/nice-o-code)
