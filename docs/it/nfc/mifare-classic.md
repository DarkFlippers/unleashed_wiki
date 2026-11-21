---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic è la carta più diffusa nel controllo accessi, nei citofoni, negli alberghi e nei sistemi di trasporto
più vecchi. È anche la più "interessante" per il Flipper: il suo cifrario Crypto-1 è compromesso, quindi con
abbastanza impegno si possono recuperare le chiavi di quasi qualsiasi carta, per poi emularla o scriverla su una
[carta magic vuota](/it/nfc/magic-cards).

## Organizzazione della memoria

| Tipo | Settori | Blocchi | Chiavi da trovare | SAK tipico |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 blocchi + 8 × 16 blocchi) | 256 | 80 | `18` |

- Un **blocco** è di 16 byte. Il **blocco 0** (blocco del produttore) contiene l'UID e i dati del produttore; sulle
  carte originali è di sola lettura, ed è proprio per questo che esistono le magic card.
- L'ultimo blocco di ogni settore è il **sector trailer**:
  `Key A (6 byte) | bit di accesso (4 byte) | Key B (6 byte)`, per esempio
  `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` su una carta vuota.
- I bit di accesso decidono quale chiave può leggere/scrivere quale blocco. Spesso la Key A legge e la Key B scrive; a
  volte la Key B è essa stessa leggibile e allora non può essere usata come chiave.

## Dizionari di chiavi

Il Flipper non "conosce" mai le chiavi: prova chiavi candidate prese dai dizionari. Sono tutti file di testo semplice
con una chiave di 12 cifre esadecimali per riga e `#` per i commenti (vedi
[formato dei file](/it/nfc/file-format)).

| Dizionario | Percorso | Chi lo scrive |
|---|---|---|
| **Di sistema** | `/ext/nfc/assets/mf_classic_dict.nfc` | Distribuito con il firmware (sovrascritto a ogni aggiornamento). In Unleashed contiene **oltre 4000 chiavi**. |
| **Utente** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Tu, MFKey, qUnleashed, *Save Keys to Dictionary*. Sopravvive agli aggiornamenti. |
| **CUID** (per singola carta) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed per le carte con nonce *static encrypted*: un lungo elenco di chiavi candidate per un solo UID. |
| **Cache di chiavi** | `/ext/nfc/.cache/<UID>.keys` | Scritta automaticamente quando **salvi** una carta; viene usata per prima alla lettura successiva dello stesso UID. |

::: tip Unleashed
Il dizionario di sistema di Unleashed contiene un vasto insieme di chiavi aggiuntive raccolte dalla comunità ("Extra
Mifare Classic keys in system dict" nel ReadMe). La schermata di caricamento del dizionario CUID con barra di
avanzamento (*"CUID dictionary is loading"*) è comparsa nella build dev 1437 / release 094.
:::

### Gestire il dizionario utente sul dispositivo

1. Vai in `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Menu Extra Actions con MIFARE Classic Keys tra le voci dei dizionari](/screens/nfc/extra_actions.png)

2. La schermata mostra **System dict: N** e **User dict: N**.
3. <kbd>OK</kbd> **Add**: inserisci una chiave da 6 byte in esadecimale e salva. Una chiave duplicata genera un avviso.
4. <kbd>→</kbd> **List** (solo se il dizionario utente non è vuoto): scegli una chiave per eliminarla
   (*"Select key to delete:"*).

Puoi anche modificare `mf_classic_dict_user.nfc` su un computer (qFlipper, qUnleashed, oppure direttamente la scheda
SD).

### Save Keys to Dictionary {#save-keys-to-dictionary}

Ogni dump MIFARE Classic salvato o appena letto con almeno una chiave nota ha **Save Keys to Dictionary** nel proprio
menu. Copia tutte le chiavi di quel dump nel dizionario utente, saltando i duplicati, e riporta *"New keys: N,
Already known: M"*. Questo conta soprattutto per le carte le cui chiavi sono state recuperate da un dizionario CUID:
altrimenti quelle chiavi vivono solo in quel file per singolo UID e nel dump, mentre
[NFC Magic](/it/nfc/nfc-magic) guarda soltanto nella cache di chiavi e nei dizionari utente/di sistema (è il
"salvataggio automatico delle chiavi con controllo dei duplicati" di cui parla @gromovyna nel suo
[articolo su qUnleashed](/it/nfc/qunleashed)).

## Cosa succede quando leggi una carta MIFARE Classic

`Main Menu → NFC → Read`, tieni la carta immobile. Il firmware passa attraverso queste fasi; l'intestazione della
schermata di attacco mostra quale è in corso.

1. **Cache di chiavi.** Se hai già salvato questo UID, vengono usate le chiavi in cache e la carta viene letta subito.
2. **Attacco a dizionario**, in questo ordine:
   - **MF Classic CUID Dictionary**: solo se esiste un file per quell'UID (prima compare *"CUID dictionary is
     loading"* con una barra di avanzamento; un file grande richiede minuti per caricarsi).
   - **MF Classic User Dictionary**: se il file utente esiste e non è vuoto.
   - **MF Classic System Dictionary**.

   La schermata mostra `Keys found: X/Y`, `Sectors Read: X/Y`, il numero della chiave corrente e *"Unlocking
   sector: N"* / *"Reuse key check for sector: N"*.

   ![Attacco al dizionario di sistema: sblocco del settore 9, chiave 1244 su 2271, 19 chiavi trovate su 32](/screens/nfc/dict_attack.png)

3. **Lettura tramite backdoor.** Se il chip ha una **chiave di backdoor** nota (Fudan e alcuni altri), l'intestazione
   mostra **Backdoor Read** / **(Backdoor)** e i settori vengono letti senza chiavi reali. Nello stesso momento
   vengono raccolti i nonce.
4. **Attacchi nested** (una volta nota almeno una chiave): **PRNG Analysis**, **Nested Dictionary**, **Calibration**,
   **Nonce Collection** (*"Collecting from sector: N"*). Un suffisso **(Hard)** significa che la carta ha un PRNG
   difficile. I nonce raccolti vengono aggiunti a `/ext/nfc/.nested.log`.
5. Si apre la schermata del risultato. Un LED verde / un suono di successo significa che la carta è stata letta
   completamente, un breve "mezzo successo" significa che mancano ancora alcuni settori.

Premi <kbd>OK</kbd> **Skip** per passare alla fase successiva (CUID → Utente → Sistema → risultato). <kbd>←</kbd>
chiede *"Exit to NFC Menu? All unsaved data will be lost"*. Se la carta viene allontanata ottieni **"Lost the tag!
Make sure the tag is positioned correctly."**; riappoggiala e l'attacco continua.

Una descrizione dettagliata con schermate di ogni fase è in
[Attacchi nested e backdoor Fudan](/it/nfc/nested-fudan).

### Dopo la lettura

Il menu di lettura (`More`) per una carta MIFARE Classic contiene:

| Voce | Quando | Cosa fa |
|---|---|---|
| **Save** | sempre | Salva il dump in `/ext/nfc/`. Riempie anche la cache di chiavi. |
| **Emulate** | sempre | Emulazione completa del dump. |
| **Extract MFC Keys** | carta non letta completamente | Chiede *"Save the Key?"* (Save/Skip), poi raccoglie i nonce da un lettore. Vedi [MFKey32](/it/nfc/mfkey). |
| **Unlock with Dictionary** | carta non letta completamente | Esegue di nuovo l'attacco a dizionario/nested (per esempio dopo aver aggiunto chiavi). |
| **Crack nonces in MFKey32** | carta non letta completamente | Propone di salvare la carta, poi avvia l'[app MFKey](/it/nfc/mfkey-app) (**Run**). |
| **Show Keys** | sempre | *"Found MFC Keys"*: bit di accesso per settore, Key A, Key B e totali. |
| **Save Keys to Dictionary** | almeno una chiave nota | Vedi sopra. |
| **Info** | sempre | UID, ATQA, SAK, riepilogo di chiavi/settori; **More** mostra il dump esadecimale (`??` = byte sconosciuti). |

Su una carta **salvata** ottieni in più **Write to Initial Card**, **Update from Initial Card**, **Restore to Original
State** (se esiste un file shadow), **Rename** e **Delete**.

## Ottenere le chiavi mancanti

Se non tutti i settori sono stati letti, scegli il metodo che corrisponde alla tua situazione:

| Situazione | Metodo |
|---|---|
| Hai la carta **e** accesso al lettore | [MFKey32](/it/nfc/mfkey): il Flipper emula la carta, il lettore rivela le sue chiavi. |
| Hai la carta e almeno una chiave è nota, oppure il chip ha una backdoor | Gli attacchi nested vengono eseguiti automaticamente in `Read`; poi calcola le chiavi con l'[app MFKey](/it/nfc/mfkey-app) oppure, molto più rapidamente, con [qUnleashed](/it/nfc/qunleashed). |
| La carta ha un **PRNG difficile** | HardNested: calcolato da qUnleashed o su un PC, vedi [Attacchi nested](/it/nfc/nested-fudan). |
| Nessuna carta, solo il lettore | [MFKey32](/it/nfc/mfkey) tramite `Extract MFC Keys` dal menu NFC principale: le chiavi finiscono nel dizionario utente per un uso successivo. |
| Le chiavi sono diversificate per carta (per esempio [Iron Logic](/it/nfc/iron-logic)) | Ogni carta ha chiavi proprie: recuperale per ogni carta singolarmente. |

Dopo aver aggiunto nuove chiavi, rileggi la carta (oppure apri il file salvato → **Unlock with Dictionary**).

## Emulazione

1. `Main Menu → NFC → Saved → <carta> → Emulate`.
2. Appoggia il Flipper al lettore.

I settori che non sono mai stati letti vengono emulati come sconosciuti: un lettore che ne ha bisogno rifiuterà la
carta. Se il lettore scrive sulla carta (saldo, contatori, sistemi "dinamici"), le modifiche finiscono nel
[file shadow](/it/nfc/read#shadow-files).

::: warning Sistemi dinamici
Alcuni sistemi riscrivono i dati sulla carta a ogni passaggio (per esempio
[Iron Logic in modalità dinamica](/it/nfc/iron-logic-enrollment)). Una copia emulata e l'originale si
desincronizzano, e usarli entrambi può bloccare l'originale.
:::

## Scrittura

- **Write to Initial Card** riscrive il dump **sulla stessa carta** (l'UID deve corrispondere). Qualsiasi altra carta
  dà *"Use source card! To write blanks use NFC Magic app"*. Se non tutti i blocchi sono stati scritti: *"Not all
  sectors were written correctly"*.
- Per clonare su una carta vuota usa l'app [NFC Magic](/it/nfc/nfc-magic) e una
  [magic card](/it/nfc/magic-cards) adatta. Scegli la carta vuota con attenzione: molti lettori filtrano le carte Gen1.

## Risoluzione dei problemi

- **Chiavi trovate ma alcuni settori ancora non letti**: i bit di accesso possono vietare la lettura con il tipo di
  chiave trovato; recupera l'altra chiave (A o B).
- **La lettura inizia con un lungo "CUID dictionary is loading"**: per questa carta esiste un grande elenco di
  candidate per quell'UID. È normale dopo un attacco a nonce static encrypted. Elimina
  `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` quando la carta è completamente recuperata e le sue chiavi sono salvate
  nel dizionario utente.
- **MFKey dice "Nonces already cracked" / niente di nuovo**: pulisci `/ext/nfc/.nested.log` e `/ext/nfc/.mfkey32.log`
  dopo un recupero riuscito; i nonce vecchi rallentano tutto.
- **Le chiavi recuperate non sembrano venire usate**: verifica che siano davvero finite in
  `mf_classic_dict_user.nfc` (`Extra Actions → MIFARE Classic Keys → List`). Le chiavi trovate con HardNested su un PC
  vanno aggiunte a mano.

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [MFKey32](/it/nfc/mfkey) · [Attacchi nested](/it/nfc/nested-fudan) ·
[App MFKey](/it/nfc/mfkey-app) · [qUnleashed](/it/nfc/qunleashed) · [Magic card](/it/nfc/magic-cards) ·
[MIFARE Plus](/it/nfc/mifare-plus)
