---
title: Karten manuell anlegen
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# NFC-Karten manuell anlegen

`Add Manually` erzeugt eine virtuelle Karte, ohne eine zu lesen. Zwei Anwendungsfälle:

- **Eine Karte eines Standardtyps erzeugen** mit zufälliger UID und leerem Standardinhalt, so als hättest du eine
  frische physische Karte. Emuliere sie dann, um sie in einem Zutrittssystem „anzulernen", oder lass ein Telefon
  NDEF-Daten (einen Link, eine vCard) darauf schreiben.
- **Eine NFC-A-Karte aus bekannten Werten anlegen**: UID, ATQA und SAK. Genug für einfache Systeme, die nur die UID
  prüfen.

## Eine Karte eines Standardtyps erzeugen

1. Geh zu `Main Menu → NFC → Add Manually`.
2. Wähle den Kartentyp (Liste unten).

   ![Add Manually: Liste der Kartentypen mit ausgewähltem NFC-A 7-bytes UID](/screens/nfc/add_manually.png)

3. Es öffnet sich ein Bildschirm mit der erzeugten **UID**. Drücke <kbd>→</kbd> **More**.
4. Wähle im Menü **Save** (du kannst vorher auch **Change UID** nutzen oder gleich **Emulate**).
5. Gib einen Namen ein und bestätige. Die Karte wird in `/ext/nfc/` gespeichert.

Verfügbare Typen (die Namen genau wie im Menü):

| Gruppe | Typen |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Die Stock-Firmware erzeugt nur Ultralight/NTAG und MIFARE Classic. Unleashed ergänzt **Mifare Ultralight C** (mit dem
Standard-3DES-Schlüssel `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, alle **MIFARE Plus**-Varianten, die
**Texkom**-Türsprechanlagen-Schlüssel und **Change UID** direkt nach dem Erzeugen, sodass sich eine MIFARE Classic
mit eigener UID anlegen lässt („NFC Add manually → Mifare Classic with custom UID" im ReadMe).
:::

::: tip Welcher Typ für ein Telefon?
Um einen Link oder eine Visitenkarte von einem Telefon zu schreiben, passt in den meisten Fällen **NTAG216**. Prüfe,
was deine App oder dein System erwartet.
:::

## Eine NFC-A-Karte aus UID, ATQA und SAK anlegen

Manche Zutrittssysteme gewähren den Zutritt anhand der UID (manchmal mit ATQA/SAK). Wenn du diese Werte kennst:

1. Geh zu `Main Menu → NFC → Add Manually`.
2. Wähle **NFC-A 7-bytes UID** oder **NFC-A 4-bytes UID**.
3. **„Enter SAK in hex"**: die SAK eingeben (1 Byte), bestätigen.
4. **„Enter ATQA in hex"**: die ATQA eingeben (2 Byte), bestätigen.
5. **„Enter UID in hex"**: die UID eingeben, bestätigen.
6. Die Karte benennen und speichern.

Typische Werte: MIFARE Classic 1K: ATQA `00 04` (4-Byte-UID) oder `00 44` (7-Byte), SAK `08`; Ultralight/NTAG:
ATQA `00 44`, SAK `00`. Tipp zur Byte-Eingabe: drücke <kbd>↑</kbd> mehrmals, bis der Nibble-Editor erscheint
(Unleashed).

## Die Karte nutzen

- **Emulate**: `Main Menu → NFC → Saved → <Karte> → Emulate` (oder **Emulate UID** bei einer NFC-A-Karte) und den
  Flipper an das Lesegerät halten. Um einen virtuellen Schlüssel in ein Zutrittssystem zu „programmieren", versetze
  das System gemäß seiner Anleitung in den Anlernmodus und präsentiere die emulierte Karte.
- **Edit UID** später: `Saved → <Karte> → Edit UID` (NFC-A-Karten).

::: warning
Verschiedene Zutrittssysteme und Apps lernen Karten auf unterschiedliche Weise an; prüfe ihre Dokumentation, welche
Kartentypen unterstützt werden. Bei Systemen, die die Kryptografie der Karte überprüfen (DESFire, Plus SL3 mit
unbekannten Schlüsseln, EMV), hilft eine virtuelle Karte nicht.
:::

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [NFC-Dateiformat](/de/nfc/file-format) · [Magic Cards](/de/nfc/magic-cards)
