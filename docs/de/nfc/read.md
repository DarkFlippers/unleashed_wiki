---
title: Karten lesen
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# NFC-Karten lesen, speichern und emulieren

`Read` ist der Haupteinstieg der NFC-App. Der Flipper erkennt das Protokoll selbst, liest alle Daten, an die er
herankommt, führt die Schlüsselangriffe aus, wo sie greifen (MIFARE Classic, Ultralight C, Ultralight AES,
MIFARE Plus SL3), und lässt dich das Ergebnis dann speichern, emulieren oder schreiben.

## Eine Karte lesen

1. Geh zu `Main Menu → NFC → Read`.
2. Auf dem Bildschirm steht **„Reading — Hold card next to Flipper's back"**. Lege die Karte flach gegen die
   **Mitte der Rückseite** des Flippers und halte sie still.

   ![Lesebildschirm: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Ist die Karte gefunden, erscheint **„Don't move"**, während die Daten gelesen werden. Bei geschützten Karten kann
   ein Angriffsbildschirm auftauchen (Wörterbuchangriff, Nested-Angriff, siehe
   [MIFARE Classic](/de/nfc/mifare-classic)).

   ![Wörterbuchangriff mit dem MIFARE-Classic-Systemwörterbuch: Sektor 9 wird entsperrt, 19 von 32 Schlüsseln gefunden](/screens/nfc/dict_attack.png)

4. Der Ergebnisbildschirm zeigt den Kartennamen und eine Zusammenfassung. Hat ein
   [Parser](/de/nfc/supported-cards) die Karte erkannt, siehst du die dekodierten Daten (Guthaben, Anzahl der
   Fahrten, Kartennummer …).

   ![Leseergebnis: MIFARE Classic 1K mit UID, 32/32 Schlüsseln gefunden und 16/16 gelesenen Sektoren](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: fragt *„Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: öffnet das Kartenmenü.
5. Wähle in **More** den Punkt **Save**, gib einen Namen unter **„Name the card"** ein und bestätige. Die Datei
   landet in `/ext/nfc/<name>.nfc`.

Das Menü `More` nach dem Lesen enthält immer **Save** und **Info**; je nach Kartentyp außerdem
**Emulate** / **Emulate UID** sowie protokollspezifische Punkte (z. B. **Unlock**, **Show Keys**,
**Extract MFC Keys**, **Transactions** bei EMV).

### Karten mit mehreren Protokollen

Manche Karten antworten als mehr als ein Protokoll (zum Beispiel eine Bankkarte, die auch einen
MIFARE-Classic-Bereich enthält). Der Flipper zeigt dann ein Menü **„Multi-protocol card"** mit Einträgen wie
**Read as MIFARE Classic**. Um die automatische Erkennung ganz zu überspringen, nimm
`Main Menu → NFC → Extra Actions → Read Specific Card Type`, wähle den Typ und drücke <kbd>OK</kbd>.

## Unterstützte Kartentypen

| Familie | Kartentypen (wie von der Firmware benannt) | Lesen | Emulieren | Schreiben |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | jede NFC-A-Karte: UID, ATQA, SAK | ja | nur UID | — |
| MIFARE Classic | Mini, 1K, 4K (4- und 7-Byte-UID) | Sektoren mit bekannten Schlüsseln | vollständig | nur auf die Ursprungskarte |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | offene Pages, mehr nach dem Entsperren | vollständig | gleicher Typ (siehe unten) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 wie Classic, SL3 mit AES-Schlüsseln | SL3 vollständig, sonst UID | SL3 auf die Ursprungskarte |
| MIFARE DESFire | DESFire | ungeschützte Anwendungen und Dateien | nur UID | — |
| ISO14443-4A | unbekannte ISO-DEP-Karten | UID, ATQA, SAK, ATS | nur UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; NFC Forum Type 4 Tags (NDEF) | ja | NTAG4xx: UID; T4T: vollständig | T4T: ja |
| EMV | Bankkarten | öffentliche Daten | — | — |
| ISO14443-3B / -4B | NFC-B-Karten | UID, Anwendungsdaten, Protokollinfos | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | ja | — | — |
| ISO15693-3 (NFC-V) | unbekannte NFC-V-Tags | UID + lesbare Blöcke | vollständig | ja |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | ja, Entsperren per Passwort | vollständig | ja |
| FeliCa | FeliCa (Lite-S und andere) | IDm, PMm, Blöcke | vollständig | — |
| Texkom | Türsprechanlagen-Schlüssel Texkom TK13, TK15, TK17, MMBIT | ja | vollständig | — |

::: tip Unleashed
**Texkom**-Schlüssel (13,56-MHz-Anhänger für Türsprechanlagen, in Russland verbreitet, die keinem ISO-Standard
folgen), **MIFARE Plus SL3**-Dumps mit AES-Schlüsseln, **Ultralight AES** und die erweiterte **Write**-Unterstützung
für Ultralight sind Ergänzungen der Firmware, die du in der Stock-Firmware nicht findest. MIFARE Classic bekommt
außerdem das CUID-Wörterbuch und **Save Keys to Dictionary**.
:::

### MIFARE Classic

Um Sektoren zu lesen, braucht der Flipper die Schlüssel: bis zu **10 Schlüssel für 5 Sektoren** (Mini),
**32 Schlüssel für 16 Sektoren** (1K) oder **80 Schlüssel für 40 Sektoren** (4K). Er probiert den Schlüsselcache
pro Karte, dann das CUID-, das Benutzer- und das Systemwörterbuch, dann Nested-Angriffe. Die Details stehen auf der
Seite [MIFARE Classic](/de/nfc/mifare-classic); fehlen danach noch Schlüssel, siehe [MFKey32](/de/nfc/mfkey) und
[Nested-Angriffe](/de/nfc/nested-fudan).

### MIFARE Ultralight und NTAG

Offene Pages werden direkt gelesen. Pages, die durch ein Passwort (NTAG21x, Ultralight EV1), einen 3DES-Schlüssel
(Ultralight C) oder einen AES-Schlüssel (Ultralight AES) geschützt sind, bleiben gesperrt, bis du sie entsperrst —
siehe [Karten mit Passwort entsperren](/de/nfc/unlock-with-password) und
[Ultralight AES](/de/nfc/ultralight-aes). Bei Ultralight C und Ultralight AES läuft automatisch ein
Wörterbuchangriff.

**Write** wird für einen vollständig gelesenen Dump von **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** und **Ultralight AES** angeboten, auf eine Karte desselben Typs. Ultralight C und AES
haben zwei Einträge: **Write (Keep Key)** behält den Schlüssel der Zielkarte, **Write (Copy Key)** schreibt auch den
Schlüssel aus dem Dump. Ist das Ziel durch ein Passwort, AUTH0 oder Lock-Bits geschützt, bekommst du
*„Card protected by password, AUTH0 or lock bits"*.

### Unbekannte Karten

Bei einer unbekannten NFC-A-Karte werden nur UID, ATQA und SAK gespeichert; bei einem unbekannten NFC-V-Tag die UID
und die lesbaren Blöcke. Viele einfache Zutrittsleser prüfen nur die UID, **Emulate UID** kann also trotzdem
funktionieren.

## Gespeicherte Karten

`Main Menu → NFC → Saved` listet deine `.nfc`-Dateien. Das Menü einer gespeicherten Karte enthält (je nach Typ):

- **Emulate** oder **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- Protokollpunkte: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID** …
- **Restore to Original State** (nur, wenn eine Schattendatei existiert, siehe unten)
- **Rename**, **Delete**, **Info**

## Eine Karte emulieren

1. Geh zu `Main Menu → NFC → Saved` und wähle die Karte.
2. Wähle **Emulate** (vollständige Emulation) oder **Emulate UID** (nur UID/ATQA/SAK werden gesendet).
3. Der Bildschirm zeigt **Emulating** mit dem Kartennamen. Halte die Rückseite des Flippers an das Lesegerät.
4. Hat das Lesegerät mit der emulierten Karte gesprochen, erscheint eine Schaltfläche **Log** (<kbd>OK</kbd>), die
   den Austausch zeigt.
5. Drücke <kbd>←</kbd> zum Beenden.

### Schattendateien {#shadow-files}

Schreibt ein Lesegerät auf eine emulierte Karte (aktualisiert es zum Beispiel ein Guthaben oder einen Zähler),
ändert der Flipper deine Originaldatei nicht. Er schreibt den neuen Zustand in eine **Schattendatei** daneben
(`<name>.shd`). Der ursprüngliche Dump bleibt unversehrt:

- **Restore to Original State** (`Saved → Karte`): fragt *„Restore Card Data?"* und löscht die Schattendatei.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): liest die physische Karte mit den gespeicherten
  Schlüsseln erneut und frischt den Dump auf. Nur die Ursprungskarte wird akzeptiert, sonst *„Wrong Card! Data
  management is only possible with source card"*.

## Wenn das Lesen scheitert

- **Es wird nichts erkannt**: die Karte könnte eine 125-kHz-Karte sein. Probiere
  `Main Menu → 125 kHz RFID → Read` (siehe [RFID-Abschnitt](/de/rfid/read)).
- **Falscher Typ erkannt / Hybridkarte**: nimm `Extra Actions → Read Specific Card Type`.
- **„Lost the tag!"** während eines langen Angriffs: lege die Karte an dieselbe Stelle zurück und halte sie still.
  Dicke Hüllen und Metall hinter der Karte stören das Feld.
- **Nicht alle Sektoren / Pages gelesen**: die Karte ist geschützt. Mach weiter mit
  [MIFARE Classic](/de/nfc/mifare-classic), [MFKey32](/de/nfc/mfkey) oder
  [Karten mit Passwort entsperren](/de/nfc/unlock-with-password).
- **„Plugin Not Loaded — Plugin file missing or outdated"**: die `.fal`-Parserdateien auf der SD-Karte passen nicht
  zur Firmware. Installiere bzw. aktualisiere die Firmware mit eingelegter SD-Karte.

## Verwandte Seiten

- [MIFARE Classic](/de/nfc/mifare-classic) · [Unterstützte Karten](/de/nfc/supported-cards) · [NFC-Dateiformat](/de/nfc/file-format)
- [Magic Cards](/de/nfc/magic-cards) · [NFC Magic 2.0](/de/nfc/nfc-magic)
