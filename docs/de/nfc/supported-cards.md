---
title: Unterstützte Karten (Parser)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Unterstützte Karten (Parser)

Bei vielen Karten gibt der Flipper nicht einfach den Speicher aus, sondern **dekodiert** ihn: Kartennummer,
Guthaben, verbleibende Fahrten, Gültigkeit, Hotelzimmerdaten, Spielfigur … Das machen **Parser-Plugins**, kleine
`.fal`-Dateien, die die NFC-App nach einem erfolgreichen Lesen von der SD-Karte lädt. Erkennt ein Parser die Karte,
zeigt der Ergebnisbildschirm die dekodierten Daten statt der rohen Zusammenfassung; **More** führt zum gewohnten
Menü.

Manche Parser bringen außerdem die **Schlüssel** des Kartensystems mit (oder eine Funktion zur
Schlüsselableitung). Bei MIFARE-Classic-Karten heißt das, dass der Flipper die Karte **vollständig ohne
Wörterbuchangriff** liest: der Parser prüft erst, ob die Karte zum System gehört, und liest sie dann mit den
richtigen Schlüsseln.

::: tip Unleashed
Unleashed liefert viele Parser mit, die in der Stock-Firmware fehlen, besonders für russische und GUS-Systeme:
Umarsh, Zolotaya Korona (und Online), Kazan, Metromoney, Moscow Social Card, ein überarbeitetes Troika, Plantain,
Troika+Plantain, die PPK-Fahrkarten der Vorortbahn, dazu Bambu Lab Filament, Banapass-/Aime-/AIC-Arcade-Karten,
Sonicare-Köpfe und mehr (von @Leptopt1los, @assasinfil und vielen Beitragenden).
:::

## Parser-Liste

Eingebaute Schlüssel = der Parser kann die Karte mit eigenen Schlüsseln (oder per Schlüsselableitung) lesen, kein
Wörterbuch nötig.

### Verkehr

| Karte (wie angezeigt) | Protokoll | Region | Eingebaute Schlüssel | Zeigt |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Moskau, Russland | ja | Daten der Verkehrsanwendung |
| Plantain Card | MIFARE Classic | Sankt Petersburg, Russland | ja | Kartendaten, PPK-Vorortbahnfahrkarte |
| Troika+Plantain | MIFARE Classic | Russland | ja | beide Anwendungen auf einer Karte |
| Social card (Moscow Social Card) | MIFARE Classic | Moskau, Russland | ja | Kartennummer (OMC), Gültigkeit |
| Kazan transport card | MIFARE Classic | Kasan, Russland | ja | Fahrkartentyp, Guthaben |
| Umarsh | MIFARE Classic | Russland (regionale Systeme) | nein (Key B für die Sektoren 0, 8, 12 nötig) | Kartendaten |
| Zolotaya korona | MIFARE Classic | Russland | nein | Kartendaten |
| Zolotaya korona (Online) | MIFARE Classic | Russland | nein | Karten- und Tarifdaten |
| SZPPK Accompany Card | MIFARE Classic | Russland, Vorortbahn (SZPPK) | ja | Gültigkeit, Station, Ein-/Ausstieg, Durchgangszähler |
| SKPPK Transport Card | MIFARE Classic | Russland, Vorortbahn (SKPPK) | ja | Station, letzter Durchgang, Status, Durchgangszähler |
| SevPPK Transport Card | MIFARE Classic | Russland, Vorortbahn (SevPPK) | ja | Station, letzter Durchgang, Status, Durchgangszähler |
| Metromoney | MIFARE Classic | Tiflis, Georgien | ja | Fahrkartendaten |
| CharlieCard | MIFARE Classic | Boston (MBTA), USA | ja | Guthaben, Transaktionen |
| Clipper | MIFARE DESFire | San Francisco Bay Area, USA | — | Seriennummer, Guthaben, Fahrten (Verkehrsbetrieb, Fahrpreis, Datum) |
| Ventra | MIFARE Ultralight | Chicago (CTA), USA | — | verbleibende Fahrten, Ablaufdatum |
| Tarjeta Bip! | MIFARE Classic | Santiago, Chile | ja | Kartennummer, Guthaben |
| SmartRider | MIFARE Classic | Perth, Australien | ja | Guthaben, Ermäßigung, Seriennummer |
| Opal | MIFARE DESFire | Sydney, Australien | — | Guthaben, letztes Ein-/Auschecken |
| myki | MIFARE DESFire | Melbourne, Australien | — | Kartennummer |
| ITSO Card | MIFARE DESFire | Vereinigtes Königreich | — | Kartendaten |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, China | — | Guthaben, Verkaufsdatum |
| All-In-One | MIFARE Ultralight | Verkehrsfahrkarte | — | Nummer, verbleibende Fahrten |

### Zutritt, Hotels, Zahlung und Service

| Karte (wie angezeigt) | Protokoll | Was | Eingebaute Schlüssel | Zeigt |
|---|---|---|---|---|
| HID Card | MIFARE Classic | HID-Berechtigung, auf einer Classic gespeichert | ja | Bitlänge und Wert der Berechtigung |
| Gallagher NZ | MIFARE Classic | Gallagher-Zutrittskontrolle (Neuseeland) | — | Berechtigungen (eine Karte kann mehrere halten) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | Saflok-Hotelschlösser | ja (KDF) | Objektnummer, Schlüssel-ID, Schlüsseldatensatz, Zutrittsstufe |
| H World Card | MIFARE Classic | H-World-Hotelschlüssel (Festlandchina) | ja | Zimmernummer, Check-in- und Ablaufdatum |
| CSC Service Works | MIFARE Classic | aufladbare Wäscherei-Geldkarte (USA) | — | Guthaben, letzte Aufladung, verbleibende Nutzungen |
| WashCity | MIFARE Classic | WashCity-/MarkItaly-Wäschereikarte (Europa) | ja | Guthaben in EUR |
| MiZIP Card | MIFARE Classic | MiZIP-Automatenschlüssel | ja | UID, Guthaben, vorheriges Guthaben |
| Microel Card | MIFARE Classic | Microel-Automatenschlüssel | ja (aus der UID abgeleitet) | UID, Guthaben, vorheriges Guthaben |
| HI! Card | MIFARE Classic | HI!-Karte | ja | UID |
| MyKey | ST25TB | MyKey-Automatenschlüssel | — | Seriennummer, Zustand leer/gesperrt, LockID |
| EMV | EMV | Bankkarten | — | siehe [Bankkarten (EMV)](/de/nfc/emv) |

### Spiele, Spielzeug und Sonstiges

| Karte (wie angezeigt) | Protokoll | Was | Eingebaute Schlüssel |
|---|---|---|---|
| Aime Card | MIFARE Classic | SEGA-Aime-Arcade-Karte (Access Code) | ja |
| Banapass | MIFARE Classic | Bandai Namco Passport (Access Code, Wert) | ja |
| Amusement IC Card | FeliCa | Arcade-Karten (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | Skylanders-Figuren (Figurenname) | ja |
| Disney Infinity | MIFARE Classic | Disney-Infinity-Figuren | ja (abgeleitet) |
| Bambu Lab Filament | MIFARE Classic 1K | Tags der Bambu-Lab-Filamentspulen (Typ, Filamentcode, Material, Farbe …) | ja (abgeleitet) |
| Philips Sonicare head | MIFARE Ultralight | Sonicare-Zahnbürstenköpfe | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | NDEF-Nachrichten: URI (auch Telefon, E-Mail), Text, Bluetooth-MAC, Kontakt, Wi-Fi, SmartPoster | — |

Der Quellcode jedes Parsers liegt in
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Manche Parser nutzen Nachschlagetabellen aus `/ext/nfc/assets/` (zum Beispiel `skylanders.nfc`, `vendors.nfc`,
`sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` für Stationsnamen, `aid.nfc`/`country_code.nfc`/`currency_code.nfc` für EMV).

## Hinweise

- Ein Parser für eine Karte mit „eingebauten Schlüsseln" prüft die Karte zuerst; scheitert die Prüfung (andere
  Schlüssel, anderes System), läuft der normale Wörterbuchangriff.
- Manche Parser sagen, was fehlt, z. B. *„Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A DICTIONARY ATTACK TO
  READ THE TICKET SECTORS"*.
- **„Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources."**: die `.fal`-Dateien auf
  der SD-Karte passen nicht zur Firmware. Installiere die Firmware mit eingelegter SD-Karte neu.
- Ein Parser zeigt nur Daten an. Ein Guthaben in einem Dump zu ändern und ihn zu emulieren ist in Verkehrs- und
  Zahlungssystemen Betrug.

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [Bankkarten (EMV)](/de/nfc/emv) · [MIFARE Classic](/de/nfc/mifare-classic) ·
[Moskwjonok-Karten](/de/nfc/moskvyonok)
