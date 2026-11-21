---
title: Leggere le carte
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Leggere, salvare ed emulare carte NFC

`Read` è il punto di accesso principale dell'app NFC. Il Flipper rileva il protocollo da sé, legge tutti i dati che
riesce a raggiungere, esegue gli attacchi alle chiavi dove sono applicabili (MIFARE Classic, Ultralight C,
Ultralight AES, MIFARE Plus SL3) e poi ti permette di salvare, emulare o scrivere il risultato.

## Leggere una carta

1. Vai in `Main Menu → NFC → Read`.
2. La schermata dice **"Reading — Hold card next to Flipper's back"**. Appoggia la carta piatta contro il **centro del
   retro** del Flipper e tienila immobile.

   ![Schermata di lettura: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Quando la carta viene trovata vedrai **"Don't move"** mentre i dati vengono letti. Per le carte protette può
   comparire una schermata di attacco (attacco a dizionario, attacco nested, vedi
   [MIFARE Classic](/it/nfc/mifare-classic)).

   ![Attacco al dizionario di sistema MIFARE Classic: sblocco del settore 9, trovate 19 chiavi su 32](/screens/nfc/dict_attack.png)

4. La schermata del risultato mostra il nome della carta e un riepilogo. Se un
   [parser](/it/nfc/supported-cards) ha riconosciuto la carta, vedi i dati decodificati (saldo, numero di corse, numero
   della carta…).

   ![Risultato della lettura: MIFARE Classic 1K con UID, 32/32 chiavi trovate e 16/16 settori letti](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: chiede *"Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: apre il menu della carta.
5. In **More**, scegli **Save**, digita un nome in **"Name the card"** e conferma. Il file finisce in
   `/ext/nfc/<nome>.nfc`.

Il menu `More` dopo la lettura contiene sempre **Save** e **Info**; a seconda del tipo di carta contiene anche
**Emulate** / **Emulate UID** e voci specifiche del protocollo (per esempio **Unlock**, **Show Keys**,
**Extract MFC Keys**, **Transactions** per EMV).

### Carte multi-protocollo

Alcune carte rispondono con più di un protocollo (per esempio una carta bancaria che contiene anche un'area MIFARE
Classic). Il Flipper mostra allora un menu **"Multi-protocol card"** con voci come **Read as MIFARE Classic**. Per
saltare del tutto il rilevamento automatico usa `Main Menu → NFC → Extra Actions → Read Specific Card Type`, scegli il
tipo e premi <kbd>OK</kbd>.

## Tipi di carta supportati

| Famiglia | Tipi di carta (con i nomi usati dal firmware) | Lettura | Emulazione | Scrittura |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Qualsiasi carta NFC-A: UID, ATQA, SAK | sì | solo UID | — |
| MIFARE Classic | Mini, 1K, 4K (UID a 4 e 7 byte) | settori con chiavi note | completa | solo sulla carta di origine |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | pagine aperte, altre dopo lo sblocco | completa | stesso tipo (vedi sotto) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 come Classic, SL3 con chiavi AES | SL3 completa, le altre solo UID | SL3 sulla carta di origine |
| MIFARE DESFire | DESFire | applicazioni e file non protetti | solo UID | — |
| ISO14443-4A | Carte ISO-DEP sconosciute | UID, ATQA, SAK, ATS | solo UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; tag NFC Forum Type 4 (NDEF) | sì | NTAG4xx: UID; T4T: completa | T4T: sì |
| EMV | Carte bancarie | dati pubblici | — | — |
| ISO14443-3B / -4B | Carte NFC-B | UID, dati applicativi, informazioni di protocollo | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | sì | — | — |
| ISO15693-3 (NFC-V) | Tag NFC-V sconosciuti | UID + blocchi leggibili | completa | sì |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | sì, sblocco con password | completa | sì |
| FeliCa | FeliCa (Lite-S e altre) | IDm, PMm, blocchi | completa | — |
| Texkom | Chiavi per citofoni Texkom TK13, TK15, TK17, MMBIT | sì | completa | — |

::: tip Unleashed
Le chiavi **Texkom** (portachiavi per citofoni a 13.56 MHz diffusi in Russia che non implementano alcuno standard ISO),
i dump **MIFARE Plus SL3** con chiavi AES, **Ultralight AES** e il supporto esteso alla **scrittura** di Ultralight
sono aggiunte del firmware che non trovi nel firmware di serie. MIFARE Classic ottiene anche il dizionario CUID e
**Save Keys to Dictionary**.
:::

### MIFARE Classic

Per leggere i settori il Flipper ha bisogno delle chiavi: fino a **10 chiavi per 5 settori** (Mini), **32 chiavi per
16 settori** (1K) oppure **80 chiavi per 40 settori** (4K). Prova la cache di chiavi della singola carta, poi i
dizionari CUID, utente e di sistema, poi gli attacchi nested. I dettagli sono nella pagina
[MIFARE Classic](/it/nfc/mifare-classic); se mancano ancora delle chiavi, vedi [MFKey32](/it/nfc/mfkey) e
[Attacchi nested](/it/nfc/nested-fudan).

### MIFARE Ultralight e NTAG

Le pagine aperte vengono lette direttamente. Le pagine protette da una password (NTAG21x, Ultralight EV1), da una
chiave 3DES (Ultralight C) o da una chiave AES (Ultralight AES) restano bloccate finché non le sblocchi, vedi
[Sbloccare le carte con password](/it/nfc/unlock-with-password) e [Ultralight AES](/it/nfc/ultralight-aes).
Ultralight C e Ultralight AES eseguono automaticamente un attacco a dizionario.

La **scrittura** è proposta per un dump completo di **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** e **Ultralight AES**, su una carta dello stesso tipo. Ultralight C e AES hanno due voci:
**Write (Keep Key)** mantiene la chiave della carta di destinazione, **Write (Copy Key)** scrive anche la chiave presa
dal dump. Se la destinazione è protetta da password, AUTH0 o lock bit, ottieni *"Card protected by password, AUTH0 or
lock bits"*.

### Carte sconosciute

Per una carta NFC-A sconosciuta vengono salvati solo UID, ATQA e SAK; per un tag NFC-V sconosciuto l'UID e i blocchi
leggibili. Molti lettori di accesso semplici controllano solo l'UID, quindi **Emulate UID** potrebbe comunque
funzionare.

## Carte salvate

`Main Menu → NFC → Saved` elenca i tuoi file `.nfc`. Il menu di una carta salvata contiene (a seconda del tipo):

- **Emulate** oppure **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- voci di protocollo: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (solo quando esiste un file shadow, vedi sotto)
- **Rename**, **Delete**, **Info**

## Emulare una carta

1. Vai in `Main Menu → NFC → Saved` e scegli la carta.
2. Seleziona **Emulate** (emulazione completa) oppure **Emulate UID** (vengono inviati solo UID/ATQA/SAK).
3. La schermata mostra **Emulating** con il nome della carta. Appoggia il retro del Flipper al lettore.
4. Se il lettore ha dialogato con la carta emulata, compare un pulsante **Log** (<kbd>OK</kbd>) che mostra lo scambio.
5. Premi <kbd>←</kbd> per fermare l'emulazione.

### File shadow {#shadow-files}

Quando un lettore scrive su una carta emulata (per esempio aggiorna un saldo o un contatore), il Flipper non modifica
il tuo file originale. Scrive il nuovo stato in un **file shadow** accanto a esso (`<nome>.shd`). Il dump originale
resta intatto:

- **Restore to Original State** (`Saved → carta`): chiede *"Restore Card Data?"* ed elimina il file shadow.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): rilegge la carta fisica con le chiavi salvate e
  aggiorna il dump. Viene accettata solo la carta di origine, altrimenti compare *"Wrong Card! Data management is only
  possible with source card"*.

## Se la lettura non riesce

- **Non viene rilevato nulla**: la carta potrebbe essere a 125 kHz. Prova `Main Menu → 125 kHz RFID → Read`
  (vedi la [sezione RFID](/it/rfid/read)).
- **Tipo rilevato sbagliato / carta ibrida**: usa `Extra Actions → Read Specific Card Type`.
- **"Lost the tag!"** durante un attacco lungo: riappoggia la carta nella stessa posizione e tienila immobile. Custodie
  spesse e metallo dietro la carta disturbano il campo.
- **Non tutti i settori / le pagine vengono letti**: la carta è protetta. Continua con
  [MIFARE Classic](/it/nfc/mifare-classic), [MFKey32](/it/nfc/mfkey) oppure
  [Sbloccare le carte con password](/it/nfc/unlock-with-password).
- **"Plugin Not Loaded — Plugin file missing or outdated"**: i file `.fal` dei parser sulla scheda SD non corrispondono
  al firmware. Reinstalla/aggiorna il firmware con la scheda SD inserita.

## Pagine correlate

- [MIFARE Classic](/it/nfc/mifare-classic) · [Carte supportate](/it/nfc/supported-cards) · [Formato dei file NFC](/it/nfc/file-format)
- [Magic card](/it/nfc/magic-cards) · [NFC Magic 2.0](/it/nfc/nfc-magic)
