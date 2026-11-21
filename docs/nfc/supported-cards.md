---
title: Supported cards (parsers)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Supported cards (parsers)

For many cards Flipper doesn't just dump the memory but **decodes** it: card number, balance, trips left, validity,
hotel room data, toy figure… This is done by **parser plugins**, small `.fal` files the NFC app loads from the SD card
after a successful read. When a parser recognises the card, the read result screen shows the decoded data instead of
the raw summary; **More** leads to the usual menu.

Some parsers also carry the card system's **keys** (or a key derivation function). For MIFARE Classic cards this means
Flipper reads the card **completely without a dictionary attack**: the parser first checks that the card belongs to
the system, then reads it with the right keys.

::: tip Unleashed
Unleashed ships many parsers that are not in stock firmware, notably for Russian and CIS systems: Umarsh, Zolotaya
Korona (and Online), Kazan, Metromoney, Moscow Social Card, a reworked Troika, Plantain, Troika+Plantain, the PPK
suburban rail tickets, plus Bambu Lab filament, Banapass/Aime/AIC arcade cards, Sonicare heads and more (by
@Leptopt1los, @assasinfil and many contributors).
:::

## Parser list

Built-in keys = the parser can read the card with its own keys (or key derivation), no dictionary needed.

### Transport

| Card (as shown) | Protocol | Region | Built-in keys | Shows |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Moscow, Russia | yes | transport application data |
| Plantain Card | MIFARE Classic | St Petersburg, Russia | yes | card data, PPK suburban ticket |
| Troika+Plantain | MIFARE Classic | Russia | yes | both applications on one card |
| Social card (Moscow Social Card) | MIFARE Classic | Moscow, Russia | yes | card number (OMC), validity |
| Kazan transport card | MIFARE Classic | Kazan, Russia | yes | ticket type, balance |
| Umarsh | MIFARE Classic | Russia (regional systems) | no (key B needed for sectors 0, 8, 12) | card data |
| Zolotaya korona | MIFARE Classic | Russia | no | card data |
| Zolotaya korona (Online) | MIFARE Classic | Russia | no | card and tariff data |
| SZPPK Accompany Card | MIFARE Classic | Russia, suburban rail (SZPPK) | yes | validity, station, entered/exited, pass counter |
| SKPPK Transport Card | MIFARE Classic | Russia, suburban rail (SKPPK) | yes | station, last pass, status, pass counter |
| SevPPK Transport Card | MIFARE Classic | Russia, suburban rail (SevPPK) | yes | station, last pass, status, pass counter |
| Metromoney | MIFARE Classic | Tbilisi, Georgia | yes | ticket data |
| CharlieCard | MIFARE Classic | Boston (MBTA), USA | yes | balance, transactions |
| Clipper | MIFARE DESFire | San Francisco Bay Area, USA | — | serial, balance, trips (agency, fare, date) |
| Ventra | MIFARE Ultralight | Chicago (CTA), USA | — | rides left, expiry |
| Tarjeta Bip! | MIFARE Classic | Santiago, Chile | yes | card number, balance |
| SmartRider | MIFARE Classic | Perth, Australia | yes | balance, concession, serial |
| Opal | MIFARE DESFire | Sydney, Australia | — | balance, last tap on/off |
| myki | MIFARE DESFire | Melbourne, Australia | — | card number |
| ITSO Card | MIFARE DESFire | United Kingdom | — | card data |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, China | — | balance, sale date |
| All-In-One | MIFARE Ultralight | transit ticket | — | number, rides left |

### Access, hotels, payment and service

| Card (as shown) | Protocol | What | Built-in keys | Shows |
|---|---|---|---|---|
| HID Card | MIFARE Classic | HID credential stored on a Classic card | yes | bit length and credential value |
| Gallagher NZ | MIFARE Classic | Gallagher access control (New Zealand) | — | credentials (a card may hold several) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | Saflok hotel locks | yes (KDF) | property number, key ID, key record, pass level |
| H World Card | MIFARE Classic | H World hotel keys (mainland China) | yes | room number, check-in and expiration date |
| CSC Service Works | MIFARE Classic | reloadable laundry cash card (US) | — | balance, last top-up, usages left |
| WashCity | MIFARE Classic | WashCity / MarkItaly laundry card (Europe) | yes | balance in EUR |
| MiZIP Card | MIFARE Classic | MiZIP vending keys | yes | UID, credit, previous credit |
| Microel Card | MIFARE Classic | Microel vending keys | yes (derived from UID) | UID, credit, previous credit |
| HI! Card | MIFARE Classic | HI! card | yes | UID |
| MyKey | ST25TB | MyKey vending keys | — | serial, blank/locked state, LockID |
| EMV | EMV | bank cards | — | see [Bank cards (EMV)](/nfc/emv) |

### Games, toys and other

| Card (as shown) | Protocol | What | Built-in keys |
|---|---|---|---|
| Aime Card | MIFARE Classic | SEGA Aime arcade card (access code) | yes |
| Banapass | MIFARE Classic | Bandai Namco Passport (access code, value) | yes |
| Amusement IC Card | FeliCa | arcade cards (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | Skylanders figures (character name) | yes |
| Disney Infinity | MIFARE Classic | Disney Infinity figures | yes (derived) |
| Bambu Lab Filament | MIFARE Classic 1K | Bambu Lab filament spool tags (type, filament code, material, colour…) | yes (derived) |
| Philips Sonicare head | MIFARE Ultralight | Sonicare toothbrush heads | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | NDEF messages: URI (incl. phone, mail), Text, Bluetooth MAC, Contact, Wi-Fi, SmartPoster | — |

The source of every parser is in
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Some parsers use lookup tables from `/ext/nfc/assets/` (for example `skylanders.nfc`, `vendors.nfc`, `sk_id.nfc`,
`sz_id.nfc`, `sev_id.nfc` for station names, `aid.nfc`/`country_code.nfc`/`currency_code.nfc` for EMV).

## Notes

- A parser for a "keys built in" card checks the card first; if the check fails (other keys, different system) the
  normal dictionary attack runs.
- Some parsers say what's missing, e.g. *"Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A DICTIONARY ATTACK TO
  READ THE TICKET SECTORS"*.
- **"Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources."**: the `.fal` files on the
  SD card don't match the firmware. Reinstall the firmware with the SD card inserted.
- A parser only displays data. Changing a balance in a dump and emulating it is fraud in transport and payment
  systems.

## Related

[Reading cards](/nfc/read) · [Bank cards (EMV)](/nfc/emv) · [MIFARE Classic](/nfc/mifare-classic) ·
[Moskvyonok cards](/nfc/moskvyonok)
