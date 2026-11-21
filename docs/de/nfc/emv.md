---
title: Bankkarten (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Bankkarten (EMV)

Kontaktlose Bankkarten und Telefon-Wallets nutzen **EMV** auf Basis von ISO14443-4. Der Flipper kann die
**öffentlichen** Informationen lesen, die eine Karte jedem Terminal gibt, und sie lesbar anzeigen. Geheime Schlüssel
kann er nicht lesen, und er kann eine Bankkarte **nicht emulieren oder klonen**: jede Zahlung wird mit einem
Schlüssel signiert, der den Chip nie verlässt.

::: tip Unleashed
Das EMV-Protokoll und der Parser für die öffentlichen Daten kommen von Unleashed (von @Leptopt1los und @wosk).
:::

## Eine Bankkarte lesen

1. `Main Menu → NFC → Read`, die Karte (oder ein entsperrtes Telefon mit geöffneter Wallet) an die Rückseite des
   Flippers halten.
2. Das ausgewertete Ergebnis zeigt, was die Karte preisgegeben hat, zum Beispiel:
   - die Bezeichnung oder den Namen der Anwendung (z. B. das Zahlungssystem) oder nur `EMV`;
   - die Kartennummer (PAN), in Vierergruppen;
   - `Cardholder name:` (die meisten modernen Karten senden ihn nicht mehr);
   - die Daten `Effective:` / `Expires:` (im Datumsformat deiner Spracheinstellung);
   - `Country:` und `Currency:` der Ausgabe;
   - `PIN attempts left:`;
   - `Mobile: yes` bei Wallets auf Telefon oder Uhr;
   - *„No data was parsed"*, wenn nichts Nützliches zurückkam.
3. <kbd>→</kbd> **More** öffnet das Menü: **Save**, **Transactions** (nur, wenn die Karte ein Transaktionsprotokoll
   geliefert hat), **Info**.

Der Bildschirm **Info** zeigt die technische Sicht: UID, `AID`, `Interchange profile`, `Currency code`,
`Country code`, `Transactions count` und, falls verfügbar, `Last Online ATC`.

## Transaktionen

Manche Karten führen ein kurzes Protokoll der letzten Transaktionen und geben es ohne PIN heraus.
`More → Transactions` listet jeden Eintrag mit Zähler (ATC), Betrag, Währung, Land und, wo vorhanden, Datum und
Uhrzeit (`???` / `UNK` bei unbekannten Werten).

## Namen von Ländern, Währungen und Anwendungen

Der EMV-Parser übersetzt Codes mithilfe von Nachschlagedateien auf der SD-Karte:

- `/ext/nfc/assets/aid.nfc`: Anwendungs-IDs → Namen;
- `/ext/nfc/assets/country_code.nfc`: ISO-Ländercodes;
- `/ext/nfc/assets/currency_code.nfc`: ISO-Währungscodes.

Jede Datei hat den Kopf `Filetype: Flipper EMV resources`, `Version: 1`, dann Zeilen der Form `<code>: <name>`,
z. B. `0985: PLN`. Siehe [Dateiformat](/de/nfc/file-format#emv-resources).

## Was nicht funktioniert und warum

- **Emulation / Zahlungen**: nicht möglich. Die Karte berechnet für jede Transaktion mit ihren privaten Schlüsseln
  ein Kryptogramm.
- **Kartennummer fehlt**: manche Karten und die meisten Telefon-Wallets geben eine tokenisierte Nummer heraus oder
  ohne Terminaldialog gar nichts.
- **Hybridkarten** (Bankkarte + Verkehrs-/Zutrittschip): nimm `Extra Actions → Read Specific Card Type`, um den
  anderen Teil zu lesen.

::: warning Datenschutz
Ein gespeicherter EMV-Dump kann deine Kartennummer und das Ablaufdatum enthalten. Teile ihn nicht.
:::

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [Unterstützte Karten](/de/nfc/supported-cards) · [NFC-Dateiformat](/de/nfc/file-format)
