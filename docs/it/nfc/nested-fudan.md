---
title: Attacchi nested e backdoor Fudan
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Attacchi nested e backdoor Fudan

Una guida pratica "cosa premere" di **@gromovyna** agli attacchi card-only su MIFARE Classic integrati in
`NFC → Read`. Sono arrivati nel firmware ufficiale **1.1.2** (lavoro di [@noproto](https://github.com/noproto)) e
fanno parte di Unleashed. Mentre venivano sviluppati, un ricercatore della comunità ha fatto due scoperte importanti:
un attacco ai **nonce static encrypted** e delle **chiavi di backdoor** nei chip prodotti da **Fudan** (e da altri) che
permettono di leggere i settori di un tag MIFARE Classic senza conoscerne le chiavi. Entrambe sono finite nel firmware
e in **MFKey 3** (oggi [MFKey 4.1](/it/nfc/mfkey-app)). Il paper di ricerca:
[eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Via più rapida (aggiornamento, settembre 2026)
Se vuoi soltanto recuperare rapidamente le chiavi MIFARE Classic, usa l'app companion **qUnleashed**, che esegue tutti
questi attacchi, HardNested compreso, sul telefono o sul PC: vedi
[Recupero rapido delle chiavi con qUnleashed](/it/nfc/qunleashed).
:::

## L'idea in breve

Gli **attacchi nested** sono attacchi *card-only* (non serve un lettore): conoscendo almeno una chiave di una carta,
recuperano quelle sconosciute. Concettualmente i tag si dividono in quattro gruppi (a rigore esistono Nested e
HardNested, ma questa suddivisione è più facile da capire):

| Il tag è vulnerabile a | Tipo di nonce | Dove viene calcolata la chiave |
|---|---|---|
| **Nested** | PRNG debole | MFKey sul Flipper, qUnleashed |
| **HardNested** | PRNG difficile | qUnleashed o un PC (non sul Flipper) |
| **Static Nested** | nonce statico | MFKey sul Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | nonce statico cifrato | MFKey sul Flipper (il più lento), qUnleashed |

Le **chiavi di backdoor** sono chiavi che aprono i dati di un tag **senza** le sue chiavi reali.

Per gli esempi l'autore ha usato tag di ciascun tipo, con il settore 0 cifrato da una coppia di chiavi generata:
Key A `A3F92C8E7D3A`, Key B `4F6D91C5BA7E` (bit di accesso lasciati ai valori predefiniti). Su un Proxmark3 la verifica
delle chiavi predefinite mostrava quelle chiavi come sconosciute:

![Verifica delle chiavi predefinite su Proxmark3](/img/remote/86130b06142278a1.png)

## Passo 1. Leggere il tag

Vai in `Main Menu → NFC → Read` e tieni il tag immobile.

### 1.1 Il tag ha una backdoor

Vedrai schermate con **Backdoor Read** e poi qualche altra con **(Backdoor)** nell'intestazione:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Lettura tramite la backdoor](/img/remote/e9be977d84486794.png)

Significa che il chip ha una backdoor: il Flipper legge i dati dei settori attraverso di essa e raccoglie i nonce, così
le chiavi possono essere recuperate. Il risultato tipico è **tutti i settori letti, ma meno chiavi di quelle
necessarie**:

![Tutti i settori, ma solo 30 chiavi](/img/remote/9e7db33e51594779.png)

### 1.2 Il tag non ha una backdoor

Parte allora la ricerca classica delle chiavi: prima il dizionario **utente**, poi il dizionario **di sistema**.

![Dizionario utente](/img/remote/fff8f5662df941b9.png)

![Dizionario di sistema](/img/remote/0da64f609fc2c770.png)

Se è stata trovata almeno una chiave, il Flipper passa alla **PRNG Analysis**, poi percorre il **Nested Dictionary**:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

poi **Calibration** e **Nonce Collection**:

![Calibration e raccolta dei nonce](/img/remote/f5b036a96f5a0869.png)

Se il tag è vulnerabile **soltanto a HardNested**, la raccolta dei nonce richiede più tempo e l'intestazione riceve un
suffisso **(Hard)**:

![Raccolta dei nonce per un tag con PRNG difficile](/img/remote/fca9f1b2e4475631.png)

> In quel caso vai direttamente al [passo 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Qui il risultato ha un aspetto più familiare: il numero di chiavi trovate è vicino al numero di settori letti (a
seconda dei bit di accesso).

![Risultato dopo la fase nested](/img/remote/d15656101dfafcc4.png)

Tutti i nonce raccolti vengono aggiunti a `/ext/nfc/.nested.log`.

## Passo 2. Recuperare le chiavi

Vai in `Main Menu → Apps → NFC → MFKey`.

::: warning Controlla la versione dell'app
Assicurati che l'app MFKey sia quella corrispondente al tuo firmware e che non sia stata sovrascritta da una copia
vecchia, se hai installato le app separatamente. Unleashed include **MFKey 4.1**.
:::

![Schermata iniziale di MFKey](/img/remote/195a1b6a411e7bf3.png)

Premi <kbd>OK</kbd> **Start** e…

### 2.1 Il tag è vulnerabile a Nested, Static Nested o Static Encrypted Nested

Il processo di cracking parte. Puoi lasciare il Flipper da solo e fare altro:

![Cracking in corso](/img/remote/a514db67a986ae2c.png)

Non resta che aspettare. Sull'hardware del Flipper non è veloce (ciao, SPI) e dipende da:

- il tipo di attacco: Nested < Static Nested < Static Encrypted Nested (SEN è il più lento);
- il numero di chiavi sconosciute (meno sono, più è rapido);
- quanto sono univoche le chiavi: una chiave riutilizzata ovunque si trova più in fretta di un tag parzialmente
  diversificato (per esempio Iron Logic), che a sua volta è più rapido di un tag completamente diversificato (per
  esempio le bobine di filamento Bambu Lab).

L'interfaccia non è sempre reattiva e a volte "ci pensa". A tratti il Flipper può sembrare bloccato; non affrettarti a
riavviarlo. La riga **RAM** in alto continua a cambiare mentre il lavoro procede.

::: warning Nonce static encrypted
Con i nonce static encrypted, per come funziona l'attacco, i nonce non vengono contrassegnati come "risolti"; MFKey
costruisce soltanto delle **candidate** (chiavi che andranno verificate sul tag più tardi), e l'app può sembrare
bloccata all'ultimo passaggio (o a uno precedente). Se è passato abbastanza tempo, esci e controlla il risultato
(passo 3). Da MFKey 4.x le candidate vengono salvate in un **dizionario CUID** per singola carta
`/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, che `Read` prova per primo.
:::

Quando la decifratura è terminata ottieni un riepilogo con il numero di chiavi aggiunte al dizionario utente
(**Keys added to user dict: N** e, per i tag SEN, **SEN key candidates: N**):

![MFKey completato](/img/remote/c9ef77139b74cc89.png)

Continua con il passo 3.

### 2.2 Il tag è vulnerabile a HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

Lo si capiva già dalla schermata **(Hard)** durante la raccolta dei nonce, oppure MFKey mostrerà un errore indicando
che non sono stati trovati nonce:

![MFKey: nessun nonce trovato](/img/remote/2519c7dce0b881c9.png)

HardNested è l'unico attacco che non si può eseguire sul Flipper. Opzioni:

- **qUnleashed** (consigliato, telefono o PC): `Tools → Recover MIFARE Keys`, vedi
  [qUnleashed](/it/nfc/qunleashed). Le chiavi finiscono direttamente nel dizionario utente.
- **Un PC con HardnestedRecovery**, come nella guida originale:
  1. Copia `/ext/nfc/.nested.log` dalla scheda SD del Flipper al computer.
  2. Clona e compila [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) con
     `make build` (su Windows usa WSL o Docker).
  3. Eseguilo passando il log come argomento:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. La chiave compare nell'output:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Aggiungi le chiavi a mano
A differenza del punto 2.1, le chiavi trovate da HardnestedRecovery su un PC **non** vengono aggiunte
automaticamente. Aggiungile tu al dizionario utente: `NFC → Extra Actions → MIFARE Classic Keys → Add`, oppure
accodale a `/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Passo 3. Leggere di nuovo il tag

Una volta recuperate le chiavi, rileggi il tag tramite `NFC → Read`.

::: tip Consiglio da esperti
Se hai salvato il tag dopo la prima lettura, puoi sbloccarlo direttamente dal menu della carta salvata:
`Saved → <carta> → Unlock with Dictionary`.
:::

![Unlock with Dictionary da una carta salvata](/img/remote/8232d690446c70b6.png)

::: tip Consiglio da esperti
Per prestazioni migliori la volta successiva, ripulisci `/ext/nfc/.nested.log` dopo aver ricavato le chiavi di un tag.
:::

## Pagine correlate

[MIFARE Classic](/it/nfc/mifare-classic) · [App MFKey](/it/nfc/mfkey-app) · [qUnleashed](/it/nfc/qunleashed) ·
[MFKey32](/it/nfc/mfkey) · [Lettori Iron Logic](/it/nfc/iron-logic) · altri articoli nel canale dell'autore
[@gromovyna](https://t.me/gromovyna)
