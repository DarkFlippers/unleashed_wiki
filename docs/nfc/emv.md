---
title: Bank cards (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Bank cards (EMV)

Contactless bank cards and phone wallets use **EMV** on top of ISO14443-4. Flipper can read the **public**
information a card gives to any terminal and show it in a readable form. It can't read secret keys and **can't
emulate or clone** a bank card: every payment is signed by a key that never leaves the chip.

::: tip Unleashed
The EMV protocol and the public data parser come from Unleashed (by @Leptopt1los and @wosk).
:::

## Read a bank card

1. `Main Menu → NFC → Read`, hold the card (or an unlocked phone with the wallet open) to the back of the Flipper.
2. The parsed result shows what the card disclosed, for example:
   - the application label or name (e.g. the payment system), or just `EMV`;
   - the card number (PAN), grouped by 4 digits;
   - `Cardholder name:` (most modern cards no longer send it);
   - `Effective:` / `Expires:` dates (in your locale's date format);
   - `Country:` and `Currency:` of issue;
   - `PIN attempts left:`;
   - `Mobile: yes` for phone/watch wallets;
   - *"No data was parsed"* if nothing useful came back.
3. <kbd>→</kbd> **More** opens the menu: **Save**, **Transactions** (only if the card returned a transaction log),
   **Info**.

The **Info** screen shows the technical view: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` and `Last Online ATC` if available.

## Transactions

Some cards keep a short log of recent transactions and give it out without a PIN. `More → Transactions` lists each
entry with its counter (ATC), amount, currency, country and date/time where present (`???` / `UNK` for unknown
values).

## Names of countries, currencies and applications

The EMV parser translates codes using lookup files on the SD card:

- `/ext/nfc/assets/aid.nfc`: application IDs → names;
- `/ext/nfc/assets/country_code.nfc`: ISO country codes;
- `/ext/nfc/assets/currency_code.nfc`: ISO currency codes.

Each file has the header `Filetype: Flipper EMV resources`, `Version: 1`, then lines `<code>: <name>`, e.g.
`0985: PLN`. See [file format](/nfc/file-format#emv-resources).

## What doesn't work and why

- **Emulation / payments**: not possible. The card computes a cryptogram for each transaction with its private keys.
- **Card number missing**: some cards and most phone wallets give a tokenised number, or nothing without a terminal
  dialog.
- **Hybrid cards** (bank card + transport/access chip): use `Extra Actions → Read Specific Card Type` to read the other
  part.

::: warning Privacy
A saved EMV dump can contain your card number and expiry date. Don't share it.
:::

## Related

[Reading cards](/nfc/read) · [Supported cards](/nfc/supported-cards) · [NFC file format](/nfc/file-format)
