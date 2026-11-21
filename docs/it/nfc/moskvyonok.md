---
title: Carte Moskvyonok
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Carte, bracciali e portachiavi Moskvyonok

Come sono costruite le carte "Moskvyonok" per studenti e bambini di Mosca e come copiare la **tua** carta su un formato più comodo (bracciale, portachiavi). Basato sull'articolo di @gromovyna (16/12/2024), con l'aiuto tecnico di @Aleksei_Pashaev e di un membro anonimo della comunità Unleashed.

::: warning
Articolo tecnico; la regolamentazione legale varia. Usa solo le tue carte, ricorda che assomigliano a uno strumento di pagamento e assumiti tu le conseguenze.
:::

## Come questi sistemi si difendono dalla clonazione

Quasi per nulla. Il sistema usa **MIFARE Classic** con chiavi standard, senza diversificazione, quindi le chiavi si trovano con un normale dizionario. Copiare è perciò una normale [lettura MIFARE Classic](/it/nfc/mifare-classic) più una scrittura su una [magic card](/it/nfc/magic-cards).

## Identifica la tua carta

| Tipo | UID | Blocco 0 | ATQA | SAK |
|---|---|---|---|---|
| UID a 4 byte | 4 byte | inizia con l'UID | `00 04` | `08` |
| UID a 7 byte | 7 byte | inizia con l'UID | `00 44` | `08` |
| 7 byte, personalizzata a 4 | 4 byte | non inizia con l'UID, sembra incomprensibile | `00 44` | `08` |

### UID a 4 byte

Tag standard, scritti così come sono. Si consigliano le carte vuote **Gen2 (CUID)**; funzionano anche le più economiche **Gen1 (UID/Zero)**, sebbene alcune segnalazioni dicano che venivano filtrate.

### UID a 7 byte

Tag più recenti, scritti così come sono su carte vuote **Zero 7 bytes** come i normali tag Gen1, anche con il Flipper Zero; oppure su tag basati su USCUID con i duplicatori cinesi o con Proxmark3 (bisogna capire la struttura della memoria e della configurazione, altrimenti puoi rendere il tag temporaneamente inutilizzabile).

::: tip Unleashed
La scrittura delle carte vuote Zero a 7 byte sul Flipper Zero è disponibile su Unleashed a partire dalla versione 079, oppure con un'app NFC Magic compilata prima del refactor dell'NFC.
:::

### UID a 7 byte personalizzato a 4 byte

Si tratta di MIFARE Classic EV1 in **modalità personalizzazione**: una modalità retrocompatibile in cui la carta ha un ID da 7 byte ma risponde a ogni SELECT con un ID da 4 byte calcolato da quello (datasheet MF1S50YYX_V1, sezione 10.1.1; algoritmo in NXP AN10927, pagina 14). Scriverla così come è dà risultati senza senso. Un tipico blocco 0 Moskvyonok inizia con `34 00...`, ma dipende dal lotto. Su Proxmark3 il calcolo è `analyse nuid`.

Copiare su una carta vuota a 4 byte (CUID):

1. Fai una copia del dump originale.
2. Calcola il nuovo UID (per esempio `3400060000DBDC` diventa `2FEDA2F1`).
3. Calcola il byte di checksum BCC (`2FEDA2F1` diventa `0x91`).
4. Riscrivi il blocco 0 della copia come: ID calcolato da 4 byte, BCC, `08`, `04`, `00`, il resto invariato (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Cambia l'ATQA nell'intestazione del file `.nfc` in `00 04` (la maggior parte delle carte vuote ha un ATQA fisso, ma fallo per correttezza).
6. Scrivi il dump sulla carta vuota.

I tag basati su USCUID possono scrivere il dump così come è ed emulare questo comportamento, ma serve conoscere la configurazione del chip e la cosa non è trattata qui.

## Cose che non hanno funzionato

Il team ha provato a troncare i byte alti, bassi e centrali dell'UID, l'ordine dei byte invertito e il NUID ricavato dai 7 byte contro i sistemi a 7 byte; nessuna di queste strade ha funzionato.

## Pagine correlate

- [MIFARE Classic](/it/nfc/mifare-classic) · [Magic card](/it/nfc/magic-cards) · [Leggere le carte](/it/nfc/read)
