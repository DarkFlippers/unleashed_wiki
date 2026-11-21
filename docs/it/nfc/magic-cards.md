---
title: Magic card MIFARE Classic
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# Magic card MIFARE Classic (carte vuote)

Su un tag MIFARE Classic il **blocco 0**, che contiene l'UID e i dati del produttore, non può essere riscritto. Per
poter fare una copia completa di un tag di questo tipo sono state inventate speciali **carte vuote** ("magic card",
"carte con UID riscrivibile"), in cui il blocco 0 può essere scritto molte volte oppure una sola volta.

Questa pagina, basata sull'articolo di **@gromovyna**, spiega in breve come stanno le cose: da Gen1 a Gen4, i nomi
internazionali, i nomi commerciali locali (ex URSS) e quale comportamento conta per quale lettore. Cita i tag
reperibili senza "danze rituali" verso la Cina e che l'autore ha verificato o visto di persona. Per scriverli con il
Flipper vedi [NFC Magic 2.0](/it/nfc/nfc-magic).

> Qui sotto "tag", "chip", "carta" e "portachiavi" sono sinonimi: quello che conta è il chip all'interno e come si
> comporta, non il formato fisico.

Per approfondire:

- le eccellenti [note sulle magic card](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  nella documentazione di Proxmark3 (in inglese), tenute aggiornate dai ricercatori, che coprono anche altri protocolli
  e danno dettagli tecnici e comandi. Con un po' di esperienza e un Proxmark3 puoi risparmiare acquistando le carte
  vuote più economiche su un dato chip e riconfigurandole (per alcuni chip);
- la [tabella Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  dell'autore con i tag elencati qui sotto, la loro generazione, i nomi e l'indicazione se il Flipper Zero è in grado di
  scriverli.

## Generazioni

![Generazioni dei tag magic](/img/remote/f659ade923b6ca4f.png)

La suddivisione in generazioni ("Gen") non è formale: è un tentativo di classificare i chip in base al comportamento.
Si sono affermate quattro generazioni. Un chip può appartenere a più di una contemporaneamente (per esempio
**M1-4K**). L'autore segue la classificazione standard usata da Proxmark3, pur non condividendola del tutto per alcuni
chip.

| Gen | Soprannome | Come si scrive il blocco 0 | Note |
|---|---|---|---|
| **Gen1** | Backdoor | comandi di backdoor speciali | I più vecchi. I comandi di backdoor permettono sempre di scrivere, leggere (e azzerare, per Gen1a) il tag. Poiché filtrarli è banale, **ogni sistema che si rispetti li filtra**. |
| **Gen2** | Direct Write | il blocco 0 si scrive come qualsiasi altro blocco | Possono essere scritti da telefoni NFC (soprattutto Android) con il software adatto. |
| **Gen3** | APDU | un comando APDU speciale | Alcuni permettono di cambiare l'UID separatamente dal blocco 0. Bestia rara. |
| **Gen4** | Configurabile | blocco di configurazione | Ha configurazione e memoria, può essere impostato come formati MFC diversi (e non solo). Il più flessibile; può imitare il comportamento di Gen1/Gen2. |

## Gen1 (backdoor)

### Gen1a

Per scrivere servono i comandi di backdoor `40` (a 7 bit) e `43`.

**UID** (nome RU: *Zero*). A livello internazionale esiste con ID a 4 byte; iKey LLC ha presumibilmente prodotto anche
una variante a 7 byte (in attesa di conferma che sia lo stesso chip). Supporta anche la lettura tramite backdoor
(senza chiavi) e l'azzeramento.

**OTP 2.0** (RU; venduto anche come **MF** per il mercato ucraino). Secondo iKey LLC, progetto proprio.
**Programmabile una sola volta**: dopo la prima scrittura (tramite la backdoor) il chip si blocca e si comporta come un
MFC originale. Ha un **PRNG difficile**.

::: tip Nota dell'autore
Il tag non corrisponde del tutto a un MFC originale e si comporta diversamente sotto stress, cosa che ha permesso a
Iron Logic di costruire un filtro contro di esso. Come funzioni quel filtro era ignoto all'autore al momento della
stesura.
:::

**MF-4** (RU). Un OTP 2.0 migliorato. Anch'esso **programmabile una sola volta** dopo la prima scrittura tramite
backdoor, **PRNG difficile**. Secondo la descrizione può:

- commutare la lunghezza dell'UID tra 4 e 7 byte;
- impostare ATQA/SAK e ATS arbitrari;
- supportare il comando PPS (che, per quanto sa l'autore, non fa parte affatto del protocollo MFC).

### Gen1b

Come Gen1, ma funziona subito dopo il comando `40` (a 7 bit). L'autore non ha visto personalmente chip Gen1b UID per
MFC 1K.

**M1-4K**: un chip per copiare **MIFARE Classic 4K**. Si comporta contemporaneamente come **Gen1b e Gen2 CUID**. Ha un
**nonce statico `f17e64cd`**.

## Gen2 (direct write)

Il blocco 0 può essere scritto direttamente. Possono essere scritti da Android con l'app *Mifare Classic Tool*.

### CUID

Nomi RU: **MF-3**, **MF3-2**, **MF-8**.

Il chip principale, universale (nella maggior parte dei casi) e più diffuso. Supera i filtri Gen1 semplici, è
riscrivibile molte volte e si può scrivere da telefono: è questo che l'ha reso il preferito di tutti.

::: tip Nota dell'autore
Nell'ex URSS l'interesse per questo chip, e i dettagli del suo comportamento, contano per i lettori **Iron Logic**, che
hanno filtri contro le carte vuote. Quei lettori costano poco e perciò sono dappertutto. Vedi
[Lettori Iron Logic](/it/nfc/iron-logic).
:::

Molti chip vengono venduti come "CUID", e possono differire nel comportamento nei casi limite. I più recenti sono i
**CUID con nonce statico (MF-3.2)**: al momento della stesura superano tutti i filtri noti dell'ex URSS (compresi gli
Iron Logic "4 strisce").

Nomi locali:

- **MF-3**: CUID che supera i filtri Iron Logic "3 strisce".
- **MF-8**: CUID che **non** supera i filtri Iron Logic OTP 1.0 (un "lotto difettoso" il cui numero, otto, è nato da una
  semplice modifica del tre).
- **MF-3.2**: CUID con nonce statico, supera tutti i filtri Iron Logic contro MFC.

In Cina esiste anche un **"Perfect CUID"** che risponde al comando RATS (l'autore non ne ha trovato un uso pratico).

## Gen3 (APDU)

Tag pilotati da comandi APDU. Attualmente la categoria meno studiata. Potenzialmente configurabili per tipo, ma la
cosa non è stata dimostrata. Nessun nome RU.

Venduti per diverse varianti di MFC, in varie combinazioni:

- per memoria: **MFC 1K**, **MFC 4K**, **MIFARE Mini**;
- per lunghezza dell'ID: **4 byte**, **7 byte**.

L'autore possiede le varianti MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b e MF Mini (S20) 7b (molto
probabilmente esiste anche MFC 1K 4b) e le ha usate un paio di volte per verificare ipotesi con ID a 7 byte, prima di
scoprire quanto sono configurabili i chip USCUID. Quella varietà (e l'esperienza con altri tag) gli ha fatto pensare che
questi chip *potrebbero* essere configurabili per tipo, lunghezza dell'UID e dimensione della memoria.

## Gen4 (configurabili)

I chip più avanzati: un blocco di configurazione controlla il tag e il suo comportamento.

### USCUID (GDM nei comandi di Proxmark3)

Un chip potente ed economico con memoria MFC 1K più blocchi nascosti usati da alcune configurazioni. A seconda della
configurazione supporta tre tipi di comandi di backdoor e il Direct Write. Può avere ID a 4 o 7 byte, può restituire
una firma MFC EV1, ha una modalità shadow e molte altre funzioni utili.

Varianti di backdoor:

- magic wakeup **Gen1a** (`40`/`43`);
- magic wakeup **GDM** (`20`/`23`): esattamente come Gen1, ma con altri comandi. Finora non sono stati visti lettori
  con filtri contro questa backdoor (a differenza di Gen1a);
- **Magic Authentication** (selezione del tag, `8000` + CRC, autenticazione Crypto-1 con chiave `000000000000`).

Conoscendo i principi di configurazione si può mettere a punto il chip per esigenze specifiche. Con le backdoor
Gen1a/GDM abilitate e i comandi in stile Gen1, si è visto che la scrittura o l'azzeramento sono inaffidabili. Chi usa
Proxmark3 dovrebbe leggere la documentazione del chip linkata sopra: rispetto all'Ultimate Magic Card costa poco e dà
molto.

Configurazioni commerciali di USCUID:

| Nome | Nome RU | Comportamento |
|---|---|---|
| **FUID** | *OTP* | **Programmabile una sola volta**: Direct Write del blocco 0, poi il blocco si blocca. Nell'ex URSS era commercializzato come "OTP" di iKey LLC ma si è rivelato un chip cinese. Nella configurazione predefinita ha una backdoor **GDM**, quindi l'ID può essere cambiato più di una volta e i dati letti senza chiavi. All'inizio di novembre 2024 i ricercatori hanno segnalato sul mercato cinese versioni con la backdoor **bloccata**, cosa che elimina il riutilizzo. |
| **UFUID** | — | Venduto dai cinesi come "UID sigillabile". La configurazione di fabbrica ha una backdoor **Gen1a**, riscrivibile molte volte. "Sigillatura": i duplicatori cinesi (CopyKey ecc.) controllano il blocco di configurazione dopo la scrittura e poi inviano un comando che lo modifica e disabilita la backdoor, trasformando il tag in un normale MFC. Un USCUID ridotto: accetta solo parte della configurazione. |
| **ZUID** | — | Un tag UID su un USCUID ridotto. Visti i prezzi dei chip, il senso di questa variante non è chiaro. Accetta solo parte della configurazione. |
| **GDM (GDMIC)** | — | Ha dato a USCUID uno dei suoi primi nomi. Caratteristica chiave: la **modalità shadow**: nel campo tutte le modifiche vanno in una memoria temporanea che si perde quando il campo scompare; la volta successiva i dati provengono dalla memoria permanente. I cinesi la pubblicizzano per le carte a "corse residue" (per esempio skipass). **Non** aiuta contro i lettori che usano dati dinamici (per esempio i citofoni Eltis con i loro portachiavi). |
| **GDCUID** | — | CUID implementato su USCUID. Non venduto separatamente, ma può capitare acquistando un CUID. |
| **M1-7B** | — | Per scrivere MIFARE Classic 1K con ID a **7 byte**. Ha una backdoor **GDM**. In modalità a 7 byte legge l'ID da un **blocco nascosto**: scrivere semplicemente un dump nella memoria principale può "brickare" il tag (recuperabile). |

I nomi **ZUID** e **GDCUID** sono stati proposti dall'autore stesso mentre scriveva la documentazione dei chip magic
per Proxmark3.

### Ultimate Magic Card (GTU)

Il chip più costoso al momento: la grande memoria e le configurazioni gli permettono di comportarsi non solo come
diversi formati MIFARE Classic / Mini, ma anche come MIFARE Ultralight, NTAG e altri (anche se la sua implementazione
di Ultralight è piuttosto limitata). La configurazione permette di:

- cambiare **ATQA/SAK** e **ATS**;
- usare un **ID** di 4, 7 o 10 byte;
- impostare la **modalità shadow** e le sue opzioni;
- abilitare/disabilitare il **Direct Write** del blocco 0;
- cambiare la **password della backdoor** (usata da tutti i comandi);
- impostare **Version** e **Signature**;
- passare in **modalità Ultralight** e configurarla.

Prima della comparsa dei CUID con nonce statico, l'UMC era l'unica carta vuota che superasse i filtri Iron Logic
"4 strisce".

## Tabella riassuntiva

![Tabella di confronto](/img/remote/a29bf09269c612bb.jpg)

La versione completa e aggiornata è nella
[tabella Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
dell'autore.

Se hai paura di acquistare il chip sbagliato in Cina, l'autore consiglia il negozio
[FlipperMarket](https://flipper.market/catalog#services-3), dove i tag principali necessari nella CSI (e scrivibili dal
Flipper) sono selezionati e venduti da un venditore esperto.

## Cosa può scrivere il Flipper

Secondo la documentazione ufficiale, il Flipper Zero (tramite l'app **NFC Magic**) scrive magic card **Gen1**, **Gen2**
e **Gen4**, oltre alle normali carte **MIFARE Classic** (senza cambiarne l'UID):

| Carta vuota | Può essere configurata come |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (serve una carta Gen2 compatibile) |
| Gen4 (Ultimate) | qualsiasi MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
La build Unleashed di **NFC Magic 2.0** rileva e scrive in più le carte vuote Ultralight/NTAG **USCUID-UL**
(UL11, UL21 / "Ultra", NTAG213/215/216, UL-C, UL-5) e riporta risultati onesti *Success / Partial / Fail*.
Vedi [NFC Magic 2.0](/it/nfc/nfc-magic).
:::

### Clonare una carta, in breve

1. [Leggi](/it/nfc/read) e salva l'originale. Assicurati che **tutti** i settori/le pagine siano stati letti (se
   necessario recupera le chiavi con [MFKey32](/it/nfc/mfkey), gli [attacchi nested](/it/nfc/nested-fudan) oppure
   [qUnleashed](/it/nfc/qunleashed)).
2. Scegli una carta vuota che il lettore bersaglio accetti (vedi sopra: Gen1 è filtrato quasi dappertutto).
3. Scrivila con [NFC Magic](/it/nfc/nfc-magic).

::: tip Aspetti legali
Copia solo le tue credenziali oppure agisci con un permesso esplicito.
:::

## Pagine correlate

[NFC Magic 2.0](/it/nfc/nfc-magic) · [MIFARE Classic](/it/nfc/mifare-classic) · [Lettori Iron Logic](/it/nfc/iron-logic) ·
[Filtri dei lettori Vizit](/it/nfc/vizit-filters)
