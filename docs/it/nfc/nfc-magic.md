---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0: scrivere e azzerare carte magic

**NFC Magic** è l'app per scrivere, clonare e azzerare le [carte magic vuote](/it/nfc/magic-cards) direttamente dal
Flipper. È nata come app ufficiale del Flipper Zero; la versione descritta qui vive nel pacchetto
[all-the-plugins](https://github.com/xMasterX/all-the-plugins) di **xMasterX** ed è mantenuta dal team **Unleashed**
(che l'ha forkata e continua a svilupparla). La versione **2.0** è stata scritta da **@gromovyna**: l'intero ciclo,
dalla ricerca sul transport fino all'ultimo pulsante dell'interfaccia.

Prima della 2.0 l'app gestiva le **MIFARE Classic** magic (Gen1a, Gen2) e le universali **Gen4** (UMC/GTU), un chip
configurabile non legato a MFC. La 2.0 aggiunge le carte magic **Ultralight/NTAG** e risultati onesti.

![Nuova versione, nuova icona](/img/remote/dafa43486592335f.png)

::: tip Dove ottenerla
NFC Magic **non fa parte del binario del firmware**: è un'app esterna del pacchetto di app aggiuntive. La 2.0 è
disponibile nelle **build dev di Unleashed dalla 1307**. Aggiorna l'app dal catalogo, oppure aggiorna il firmware a una
build dev recente (con il pacchetto di app aggiuntive). Percorso sul dispositivo:
`Main Menu → Apps → NFC → NFC Magic`.
:::

## Prima di iniziare

1. [Leggi](/it/nfc/read) la carta originale e **salvala**. Assicurati che **tutti** i settori (MIFARE Classic) o tutte
   le pagine (Ultralight/NTAG) siano stati letti: un dump parziale dà una copia parziale.
2. Per le carte vuote MIFARE Classic, NFC Magic si autentica con le chiavi provenienti dalla **cache di chiavi** e dai
   **dizionari utente e di sistema**, nient'altro. Se le chiavi della tua carta provenivano da un dizionario CUID,
   esegui prima **Save Keys to Dictionary** sul dump (vedi
   [MIFARE Classic](/it/nfc/mifare-classic#save-keys-to-dictionary)).

## Passo 1. Rilevamento

Tutto inizia quando appoggi la carta vuota al Flipper (`Check Magic Tag`). La prima grande novità: l'app non è più
fissata su MIFARE Classic. Lo scanner lavora **prima per famiglia**: capisce innanzitutto la famiglia (**MFC** oppure
**Ultralight/NTAG**) e solo dopo scava fino alla variante esatta.

Per gli **USCUID-UL** (carte magic della famiglia Ultralight) viene riconosciuto tutto lo zoo principale, più un po' di
circo locale russo: **UL11**, **UL21** (compreso quello venduto come **"Ultra"** nel mercato dell'ex URSS),
**NTAG213/215/216**, **UL-C**, **UL-5** e i tag già in modalità **backdoor** (vengono verificate entrambe le sequenze
di wakeup).

![USCUID-UL rilevato](/img/remote/557fa5d47ebeb0a6.png)

Se hai un preset che l'app non conosce, non si arrende: mostra la **configurazione grezza**, così puoi vederla e
analizzarla tu stesso. Comodo per i ricercatori.

![Configurazione grezza 1](/img/remote/7c3f38df0079d8fa.png)

![Configurazione grezza 2](/img/remote/c16eb844763ef4fa.png)

![Configurazione grezza 3](/img/remote/30f2a4b10d4be98a.png)

Per una carta **Gen4** protetta da password: `Gen4 Actions → Auth with password`, inserisci la password, poi verifica
il tag.

## Passo 2. Scrivere Ultralight / NTAG

Una volta riconosciuto il tag puoi scrivere e clonare completamente **UL/NTAG**. Quello a cui **non** devi pensare è il
transport: l'app lo sceglie in base al risultato del rilevamento.

- **Direct**: una normale scrittura ISO14443-3 con il comando **`A2`**, per i tag che accettano la scrittura diretta
  (per esempio le configurazioni di fabbrica **USCUID-UL**, lo stesso **UL21**, alias **"Ultra"**).
- **Backdoor**: se il chip ha una backdoor esposta, l'app la usa (wakeup raw più comandi di backdoor). Logica semplice:
  backdoor esposta → usala; nessuna → scrivi direttamente.

Le tue decisioni:

- **Scrivere su un tag senza backdoor ma di cui conosci la password?** Fornisci la password tramite **PWD-AUTH**:
  l'app si autentica sul tag prima di scrivere o azzerare.
- **Il tag non è stato confermato come magic ma tu sai che lo è?** Premi **Write anyway** e assumiti la responsabilità.

Il processo di scrittura è stato reso il meno spaventoso possibile:

- **Avanzamento in tempo reale "Writing X/N"** a schermo, così non resti a fissare una schermata immobile chiedendoti
  se stia succedendo qualcosa.

  ![Avanzamento della scrittura (rapida: è servito un NTAG216 per catturare lo screenshot)](/img/remote/9914d55ba866082e.png)

- L'**ordine delle pagine** è calibrato per tipo di tag (per esempio **UL-5**) ed è **diverso tra scrittura e
  azzeramento** a causa dei lock bit. Durante la scrittura le pagine di servizio (compreso l'UID) vanno **per ultime**:
  scrivere troppo presto il lock/la protezione blocca il tag prima che il dump sia completo. L'azzeramento procede in
  ordine crescente, per rimuovere prima il lock statico e solo dopo ripulire il resto.
- La scrittura è **ACK-only con continue-on-error**: l'app non si ferma alla prima pagina fallita, porta avanti ciò che
  può.
- Se qualcosa non è andato a buon fine ottieni **Partial Write** con un elenco **Details** delle pagine esattamente
  fallite, non un allegro "fatto". Hai staccato il tag dall'antenna a metà? Riappoggialo e la scrittura continua dallo
  stesso punto.

![Scrittura parziale](/img/remote/a50fa90dff60cdd8.png)

![Details](/img/remote/71b6fa77e1914b76.png)

E **Wipe** riporta il tag allo stato di fabbrica con una sola pressione.

## Passo 3. Scrivere MIFARE Classic

1. In NFC Magic seleziona **Check Magic Tag** e appoggia la carta vuota al retro del Flipper.
2. Quando la carta vuota viene riconosciuta (Gen1a, Gen2, Gen4…), vai in **More** per le opzioni di quel tipo di carta.
3. **Write**: scegli la carta originale nel file browser e appoggia la carta vuota al Flipper.
4. **Wipe** formatta la carta vuota: UID riportato al valore predefinito, dati nei settori/nelle pagine cancellati.

### Risposte oneste: Success / Partial / Fail

Questa parte riguarda il buon vecchio **MIFARE Classic (Gen2)** ed è per l'autore importante quanto le nuove funzioni.

Prima, l'azzeramento e la clonazione MFC riportavano **sempre** "Success". Sempre, anche quando non era stato scritto
nemmeno un byte. Non è solo un bug, è una bugia: te ne vai convinto che la tua copia funzioni, e invece no.

Ora le operazioni vengono tracciate **blocco per blocco** e ottieni un verdetto onesto: **Success / Partial / Fail**.
Con **Partial** vedi i **Details**: quali blocchi non sono stati scritti o azzerati. Il blocco 0 di sola lettura non fa
più fallire tutto il settore 0 nel resoconto (come nel progetto originale), cosa comoda anche quando il tag è chiuso dai
**bit di accesso**.

![Risultato](/img/remote/9e9d84e664f7da06.png)

![Dettagli di un risultato parziale](/img/remote/525faf18552333d1.png)

Cose che rendono la vita più serena:

- Durante l'azzeramento, il blocco 0 **mantiene il SAK/ATQA reale** del tag. Caso classico: **Perfect CUID** (risponde
  a RATS / ha un ATS). Il firmware lo rilevava come 4K e l'azzeramento marchiava il blocco 0 come 4K. Corretto: una 1K
  resta 1K, e l'UID viene azzerato.
- Nessuna chiave funzionante per l'azzeramento? Invece di un tentativo di scrittura condannato in partenza vedi subito
  **"No keys found"**.
- Ogni schermata di errore (Wipe / Write / Dump) ha **Exit → menu**, così non ti senti in trappola.
- Un bug fastidioso è scomparso: le chiavi del tag precedente **non vengono più riportate** all'operazione successiva.
  L'attacco a dizionario ora rilegge il tag ogni volta invece di riutilizzare le chiavi dell'ultimo tag (cosa che
  poteva dare una falsa sensazione di successo e una velocità finta).

## A prova di errore

Già nella release precedente l'app aveva ottenuto protezioni riguardo ai tag MFC magic e alle diverse lunghezze di
**UID**. La 2.0 verifica se il dump può realmente essere scritto sulla variante **USCUID-UL** data:

![Verifica di compatibilità dump/carta vuota](/img/remote/a4dc82f2b66b73b5.png)

e, per i più ingegnosi, blocca i tentativi di accoppiare **famiglie diverse** (un dump MFC su una carta vuota
Ultralight e viceversa; casi che compaiono regolarmente nei forum e nelle chat):

![Famiglia non corrispondente](/img/remote/83e6e6cf1f0d9da6.png)

## È meno banale di quanto sembri

Dietro l'elenco delle funzioni ci sono quasi **3.000 righe** di modifiche: un poller USCUID-UL scritto da zero, la
logica Gen2 riscritta e un mucchio di bug corretti. Tutto è stato **validato su hardware reale** con una **matrice di
QA di quasi 100 casi**:

- **~15 tag di prova**: varianti USCUID-UL acquistate o costruite (UL11, UL21 (NXP e Mikron "Ultra"),
  NTAG213/215/216, UL-C, UL-5, diverse varianti UL-Y per i casi limite), tag in modalità backdoor (entrambi i wakeup),
  più tag originali non magic e completamente bloccati per ottenere dei Fail onesti, e un mucchio di tag per la
  regressione;
- **categorie**: rilevamento (17 casi), transport diretto/backdoor, integrità dei dati e ordine delle pagine, scenari
  di UX, PWD-AUTH, azzeramento, un blocco corposo per l'azzeramento Gen2/MFC (19 casi) e la regressione di tutti i
  vecchi protocolli (Gen1a 4/7 byte, Gen2, Gen4, MFC semplice).

Quel ciclo ha fatto emergere e ha eliminato molti bug: falsi "Success", pulsanti morti, una perdita di memoria, uno
spinner che girava all'infinito su un Ultralight originale. Le limitazioni note (compresa una sfumatura nel rilevamento
1K/4K a livello di firmware) sono documentate.

Prossimo in lista: il supporto alla scrittura **UL-C** per USCUID-UL e forse qualche esotismo specifico di certe
regioni.

## Risoluzione dei problemi

- **Tag non riconosciuto**: potrebbe non essere un tag magic, oppure è un preset sconosciuto: controlla la
  configurazione grezza. Per un Gen4 con password, autenticati prima.
- **"No keys found"** durante un azzeramento MFC: le chiavi attuali della carta vuota non sono nei tuoi dizionari.
  Aggiungile (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Scrittura parziale**: riappoggia il tag e continua; controlla i **Details**. I lock bit / bit di accesso presenti
  nel dump di origine possono rendere alcuni blocchi/pagine non scrivibili.
- **Il lettore rifiuta la copia**: il lettore potrebbe filtrare il tuo tipo di carta vuota. Vedi
  [Magic card](/it/nfc/magic-cards), [Iron Logic](/it/nfc/iron-logic),
  [Filtri Vizit](/it/nfc/vizit-filters).

## Pagine correlate

[Magic card](/it/nfc/magic-cards) · [MIFARE Classic](/it/nfc/mifare-classic) · [qUnleashed](/it/nfc/qunleashed) ·
[Sbloccare le carte con password](/it/nfc/unlock-with-password)
