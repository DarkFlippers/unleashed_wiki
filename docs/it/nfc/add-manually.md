---
title: Aggiungere carte manualmente
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Aggiungere carte NFC manualmente

`Add Manually` crea una carta virtuale senza leggerne una. Due casi d'uso:

- **Generare una carta di un tipo standard** con UID casuale e contenuto predefinito (vuoto), come se avessi una carta
  fisica nuova. Poi la emuli per "registrarla" in un sistema di accesso, oppure lasci che un telefono le scriva dati
  NDEF (un link, una vCard).
- **Creare una carta NFC-A da valori noti**: UID, ATQA e SAK. Sufficiente per i sistemi semplici che controllano solo
  l'UID.

## Generare una carta di un tipo standard

1. Vai in `Main Menu → NFC → Add Manually`.
2. Scegli il tipo di carta (elenco più sotto).

   ![Add Manually: elenco dei tipi di carta con NFC-A 7-bytes UID selezionato](/screens/nfc/add_manually.png)

3. Si apre una schermata con l'**UID** generato. Premi <kbd>→</kbd> **More**.
4. Nel menu scegli **Save** (puoi anche fare prima **Change UID**, oppure **Emulate** subito).
5. Inserisci un nome e conferma. La carta viene salvata in `/ext/nfc/`.

Tipi disponibili (nomi esatti come nel menu):

| Gruppo | Tipi |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Il firmware di serie genera solo Ultralight/NTAG e MIFARE Classic. Unleashed aggiunge **Mifare Ultralight C** (con la
chiave 3DES predefinita `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, tutte le varianti **MIFARE Plus**, le chiavi
per citofoni **Texkom** e **Change UID** subito dopo la generazione, così è possibile creare una MIFARE Classic con UID
personalizzato ("NFC Add manually → Mifare Classic with custom UID" nel ReadMe).
:::

::: tip Quale tipo per un telefono?
Per scrivere un link o un biglietto da visita da un telefono, **NTAG216** va bene nella maggior parte dei casi.
Verifica cosa si aspetta la tua app o il tuo sistema.
:::

## Creare una carta NFC-A da UID, ATQA e SAK

Alcuni sistemi di accesso concedono l'accesso in base all'UID (a volte con ATQA/SAK). Se conosci questi valori:

1. Vai in `Main Menu → NFC → Add Manually`.
2. Seleziona **NFC-A 7-bytes UID** oppure **NFC-A 4-bytes UID**.
3. **"Enter SAK in hex"**: digita il SAK (1 byte), conferma.
4. **"Enter ATQA in hex"**: digita l'ATQA (2 byte), conferma.
5. **"Enter UID in hex"**: digita l'UID, conferma.
6. Dai un nome alla carta e salvala.

Valori tipici: MIFARE Classic 1K: ATQA `00 04` (UID a 4 byte) oppure `00 44` (a 7 byte), SAK `08`; Ultralight/NTAG:
ATQA `00 44`, SAK `00`. Suggerimento per l'inserimento dei byte: premi <kbd>↑</kbd> ripetutamente finché compare
l'editor di nibble (Unleashed).

## Usare la carta

- **Emulate**: `Main Menu → NFC → Saved → <carta> → Emulate` (oppure **Emulate UID** per una carta NFC-A) e appoggia
  il Flipper al lettore. Per "programmare" una chiave virtuale in un sistema di accesso, metti il sistema in modalità
  di registrazione secondo il suo manuale e presenta la carta emulata.
- **Edit UID** in un secondo momento: `Saved → <carta> → Edit UID` (carte NFC-A).

::: warning
Sistemi di accesso e app diversi registrano le carte in modi diversi; controlla la loro documentazione per i tipi di
carta supportati. Una carta virtuale non può aiutare con i sistemi che verificano la crittografia della carta
(DESFire, Plus SL3 con chiavi sconosciute, EMV).
:::

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [Formato dei file NFC](/it/nfc/file-format) · [Magic card](/it/nfc/magic-cards)
