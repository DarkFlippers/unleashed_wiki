---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Flipper Zero hat ein eingebautes **13,56-MHz-NFC-Modul**, das Hochfrequenzkarten **lesen**, **speichern**,
**emulieren** und bei manchen Kartentypen auch **schreiben** kann: Zutrittskarten und Schlüsselanhänger,
Verkehrskarten, Hotelkarten, NFC-Aufkleber, Amiibo-artiges Spielzeug und Bankkarten (nur öffentliche Daten). Die
Daten liegen auf der microSD-Karte in `/ext/nfc/` als `.nfc`-Textdateien.

::: warning Lege eine microSD-Karte ein
Die NFC-App hält ihre Wörterbücher, Parser und gespeicherten Karten auf der microSD-Karte (`/ext/nfc/`).
Aktualisiere die Firmware mit eingelegter SD-Karte, damit die Ressourcen (Schlüssel-Wörterbücher, `assets/*.nfc`,
Parser-Plugins) mit installiert werden.
:::

## Hardware

- **ST25R3916** als NFC-Frontend-Chip, zuständig sowohl für das Lesen als auch für die Emulation.
- Eine **13,56-MHz-Antenne** auf der Zweiband-RFID-Antennenplatine an der Rückseite des Geräts, neben der
  125-kHz-Antenne. Halte Karten gegen die **Mitte der Rückseite** des Flippers.

## Das NFC-Menü

`Main Menu → NFC` öffnet dieses Menü (die Bezeichnungen genau wie auf dem Gerät unter Unleashed):

![NFC-Hauptmenü: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Punkt | Funktion |
|---|---|
| **Read** | Erkennt den Kartentyp und liest alles, was möglich ist — einschließlich der Schlüsselangriffe auf MIFARE Classic. Siehe [Karten lesen](/de/nfc/read). |
| **Extract MFC Keys** | Emuliert eine MIFARE Classic Karte, um Nonces von einem Lesegerät zu sammeln (MFKey32). Siehe [MFKey32](/de/nfc/mfkey). |
| **Saved** | Deine gespeicherten `.nfc`-Dateien: emulieren, schreiben, entsperren, umbenennen, löschen. |
| **Extra Actions** | Einen bestimmten Kartentyp lesen, Schlüssel-Wörterbücher verwalten, NTAG/Ultralight und SLIX-L entsperren. |
| **Add Manually** | Erzeugt eine leere virtuelle Karte oder eine NFC-A-Karte aus bekannten UID/ATQA/SAK-Werten. Siehe [Karten manuell anlegen](/de/nfc/add-manually). |
| **Debug** | Nur sichtbar, wenn der Debug-Modus aktiv ist (`Settings → System → Debug`). |

`Extra Actions` enthält:

![Menü Extra Actions: Read Specific Card Type und die Schlüssel-Wörterbücher](/screens/nfc/extra_actions.png)

- **Read Specific Card Type**: überspringt die automatische Erkennung, praktisch bei Hybridkarten.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys**: zeigt die
  Zähler des System- bzw. Benutzer-Wörterbuchs, erlaubt **Add** für einen Schlüssel oder **List** (und das Löschen)
  der Benutzerschlüssel.
- **Unlock NTAG/Ultralight**: ein Passwort erzeugen oder eingeben, bevor gelesen wird. Siehe
  [Karten mit Passwort entsperren](/de/nfc/unlock-with-password).
- **Unlock SLIX-L**: Passwort-Entsperrung für ICODE-SLIX-L-Tags.

::: tip Unleashed
Die NFC-App stammt aus der offiziellen Firmware — Leser, Emulator und die meisten Kartenparser. Darüber hinaus
ergänzt Unleashed unter anderem: ein erweitertes MIFARE-Classic-System-Wörterbuch
(über 4000 Schlüssel), das Lesen von **MIFARE Plus SL3** mit AES-Schlüssel-Wörterbüchern, Unterstützung für
**MIFARE Ultralight AES**, **Texkom**-Türsprechanlagen-Schlüssel, `Add Manually` für MIFARE Classic mit eigener UID
und für MIFARE Plus, **Save Keys to Dictionary** aus einem Dump, das CUID-Wörterbuch (pro Karte) mit
Ladefortschrittsbalken und viele zusätzliche Kartenparser (Troika, Plantain, Umarsh, Zolotaya Korona, Kazan,
Metromoney, Moscow Social Card, PPK-Tickets und mehr).
:::

## Grundlagen

| Begriff | Bedeutung |
|---|---|
| **UID** | Seriennummer der Karte, 4 oder 7 Byte (bei manchen 10). Auf echten Karten werkseitig eingebrannt. |
| **ATQA / SAK** | Antwortbytes während der Antikollision, die auf den Kartentyp hinweisen (z. B. SAK `08` = MIFARE Classic 1K). |
| **Sektor / Block** | Speichereinheit bei MIFARE Classic: 16 Byte pro Block, 4 Blöcke pro Sektor (am Ende einer 4K liegen Sektoren mit 16 Blöcken). |
| **Page** | Speichereinheit bei Ultralight/NTAG, 4 Byte. |
| **Key A / Key B** | 6 Byte lange Crypto-1-Schlüssel, die jeden Sektor einer MIFARE Classic schützen. |
| **Nonce** | Zufallszahl, die bei der Authentisierung ausgetauscht wird. Aus gesammelten Nonces lassen sich Schlüssel offline berechnen. |
| **Magic Card** | Ein Rohling mit beschreibbarer UID bzw. beschreibbarem Block 0. Siehe [Magic Cards](/de/nfc/magic-cards). |

## Seiten in diesem Abschnitt

### Alltag

- [Karten lesen](/de/nfc/read): lesen, speichern, emulieren; welche Kartentypen unterstützt werden und was jeder davon hergibt.
- [Karten manuell anlegen](/de/nfc/add-manually): virtuelle Karten erzeugen, eine NFC-A-Karte aus UID/ATQA/SAK bauen.
- [Unterstützte Karten (Parser)](/de/nfc/supported-cards): Verkehrs-, Zutritts- und Spielzeugkarten, die der Flipper dekodieren kann.
- [Bankkarten (EMV)](/de/nfc/emv): was von einer Bankkarte gelesen wird und warum sie sich nicht klonen lässt.
- [Karten mit Passwort entsperren](/de/nfc/unlock-with-password): NTAG/Ultralight-Passwörter, Ultralight-C-Schlüssel, SLIX-L.

### MIFARE Classic und Schlüsselsuche

- [MIFARE Classic](/de/nfc/mifare-classic): Wörterbücher, Sektoren, der komplette Leseablauf, Emulation und Schreiben.
- [MFKey32: Schlüssel vom Lesegerät](/de/nfc/mfkey): Nonces von einem Lesegerät sammeln, Schlüssel zurückrechnen.
- [Nested-Angriffe und Fudan-Backdoors](/de/nfc/nested-fudan): Angriffe ohne Lesegerät, direkt in `Read` eingebaut.
- [Die MFKey-App](/de/nfc/mfkey-app): Schlüssel auf dem Flipper selbst zurückrechnen (MFKey 4.1).
- [Schnelle Schlüsselsuche mit qUnleashed](/de/nfc/qunleashed): alle Angriffe auf dem Telefon oder PC.

### Rohlinge und Klonen

- [MIFARE Classic Magic Cards](/de/nfc/magic-cards): Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC und die lokalen Bezeichnungen.
- [NFC Magic 2.0](/de/nfc/nfc-magic): Magic-Rohlinge für MIFARE Classic und Ultralight/NTAG beschreiben und löschen.

### Weitere Kartenfamilien

- [MIFARE Ultralight AES](/de/nfc/ultralight-aes): AES-geschützte Ultralight (MF0AES20), Schlüssel, Rückschreiben, Secure Messaging.
- [MIFARE Plus](/de/nfc/mifare-plus): wie S/X/SE/EV1/EV2 und die Sicherheitsstufen erkannt werden, SL3-AES-Schlüssel.

### Zutrittssysteme (von @gromovyna)

- [Iron Logic Lesegeräte](/de/nfc/iron-logic)
- [Iron Logic dynamische Anlernung](/de/nfc/iron-logic-enrollment)
- [Vizit Leser-Filter](/de/nfc/vizit-filters)
- [Moskwjonok-Karten](/de/nfc/moskvyonok)

### Referenz

- [NFC-Dateiformat](/de/nfc/file-format): der Aufbau der `.nfc`-Dateien und die Wörterbuchformate.

::: tip Rechtliches
Arbeite mit deinen eigenen Karten oder mit ausdrücklicher Erlaubnis. Das Kopieren fremder Zutrittsausweise oder
Fahrkarten kann strafbar sein.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG und ICODE sind Marken der NXP B.V.
FeliCa ist eine Marke der Sony Corporation.
