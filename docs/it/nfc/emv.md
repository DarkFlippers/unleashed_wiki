---
title: Carte bancarie (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Carte bancarie (EMV)

Le carte bancarie contactless e i wallet dei telefoni usano **EMV** sopra ISO14443-4. Il Flipper può leggere le
informazioni **pubbliche** che una carta fornisce a qualsiasi terminale e mostrarle in forma leggibile. Non può leggere
le chiavi segrete e **non può emulare né clonare** una carta bancaria: ogni pagamento è firmato da una chiave che non
lascia mai il chip.

::: tip Unleashed
Il protocollo EMV e il parser dei dati pubblici arrivano da Unleashed (opera di @Leptopt1los e @wosk).
:::

## Leggere una carta bancaria

1. `Main Menu → NFC → Read`, appoggia la carta (o un telefono sbloccato con il wallet aperto) al retro del Flipper.
2. Il risultato interpretato mostra ciò che la carta ha divulgato, per esempio:
   - l'etichetta o il nome dell'applicazione (per esempio il circuito di pagamento), oppure semplicemente `EMV`;
   - il numero della carta (PAN), raggruppato a 4 cifre;
   - `Cardholder name:` (la maggior parte delle carte moderne non lo invia più);
   - le date `Effective:` / `Expires:` (nel formato data della tua lingua);
   - `Country:` e `Currency:` di emissione;
   - `PIN attempts left:`;
   - `Mobile: yes` per i wallet su telefono/orologio;
   - *"No data was parsed"* se non è tornato nulla di utile.
3. <kbd>→</kbd> **More** apre il menu: **Save**, **Transactions** (solo se la carta ha restituito un registro delle
   transazioni), **Info**.

La schermata **Info** mostra la vista tecnica: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` e `Last Online ATC` se disponibile.

## Transazioni

Alcune carte conservano un breve registro delle transazioni recenti e lo forniscono senza PIN.
`More → Transactions` elenca ogni voce con il suo contatore (ATC), l'importo, la valuta, il paese e la data/ora dove
presenti (`???` / `UNK` per i valori sconosciuti).

## Nomi di paesi, valute e applicazioni

Il parser EMV traduce i codici usando dei file di consultazione sulla scheda SD:

- `/ext/nfc/assets/aid.nfc`: ID applicazione → nomi;
- `/ext/nfc/assets/country_code.nfc`: codici paese ISO;
- `/ext/nfc/assets/currency_code.nfc`: codici valuta ISO.

Ogni file ha l'intestazione `Filetype: Flipper EMV resources`, `Version: 1`, poi righe `<code>: <name>`, per esempio
`0985: PLN`. Vedi il [formato dei file](/it/nfc/file-format#emv-resources).

## Cosa non funziona e perché

- **Emulazione / pagamenti**: non è possibile. La carta calcola un criptogramma per ogni transazione con le sue chiavi
  private.
- **Numero della carta assente**: alcune carte e la maggior parte dei wallet su telefono forniscono un numero
  tokenizzato, oppure nulla senza un dialogo con il terminale.
- **Carte ibride** (carta bancaria + chip trasporti/accessi): usa
  `Extra Actions → Read Specific Card Type` per leggere l'altra parte.

::: warning Privacy
Un dump EMV salvato può contenere il numero della tua carta e la data di scadenza. Non condividerlo.
:::

## Pagine correlate

[Leggere le carte](/it/nfc/read) · [Carte supportate](/it/nfc/supported-cards) ·
[Formato dei file NFC](/it/nfc/file-format)
