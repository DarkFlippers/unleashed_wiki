---
title: Moskwjonok-Karten
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Moskwjonok-Karten, -Armbänder und -Anhänger

Wie die Moskauer Schüler-/Kinderkarten „Moskwjonok" aufgebaut sind und wie du **deine eigene** Karte in eine bequemere Bauform (Armband, Anhänger) kopierst. Nach dem Artikel von @gromovyna (16.12.2024), mit technischer Hilfe von @Aleksei_Pashaev und einem anonymen Mitglied der Unleashed-Community.

::: warning
Technischer Artikel; die rechtliche Regelung ist unterschiedlich. Nutze nur deine eigenen Karten, bedenke, dass sie einem Zahlungsmittel ähneln, und trage die Folgen selbst.
:::

## Wie sich diese Systeme gegen Klonen wehren

Kaum. Das System nutzt **MIFARE Classic** mit Standardschlüsseln, ohne Diversifizierung, die Schlüssel lassen sich also mit einem gewöhnlichen Wörterbuch finden. Kopieren ist deshalb ein normales [MIFARE-Classic-Lesen](/de/nfc/mifare-classic) plus ein Schreiben auf eine [Magic Card](/de/nfc/magic-cards).

## Bestimme deine Karte

| Typ | UID | Block 0 | ATQA | SAK |
|---|---|---|---|---|
| 4-Byte-UID | 4 Byte | beginnt mit der UID | `00 04` | `08` |
| 7-Byte-UID | 7 Byte | beginnt mit der UID | `00 44` | `08` |
| 7 Byte, auf 4 personalisiert | 4 Byte | beginnt nicht mit der UID, sieht nach Unsinn aus | `00 44` | `08` |

### 4-Byte-UID

Standard-Tags, werden unverändert geschrieben. Empfohlen sind **Gen2 (CUID)**-Rohlinge; günstigere **Gen1 (UID/Zero)** funktionieren ebenfalls, auch wenn es Berichte gibt, dass sie gefiltert wurden.

### 7-Byte-UID

Neuere Tags, werden unverändert auf **Zero 7 Byte**-Rohlinge geschrieben wie gewöhnliche Gen1-Tags, auch mit dem Flipper Zero; oder auf USCUID-basierte Tags mit chinesischen Duplikatoren oder einem Proxmark3 (versteh die Speicher- und Konfigurationsstruktur, sonst kannst du den Tag soft-bricken).

::: tip Unleashed
Das Beschreiben von Zero-7-Byte-Rohlingen auf dem Flipper Zero gibt es in Unleashed ab Version 079, oder mit einer NFC-Magic-App, die vor dem NFC-Refactor gebaut wurde.
:::

### 7-Byte-UID, auf 4 Byte personalisiert

Das ist MIFARE Classic EV1 im **Personalisierungsmodus**: ein rückwärtskompatibler Modus, in dem die Karte eine 7-Byte-ID hat, aber auf jedes SELECT mit einer daraus berechneten 4-Byte-ID antwortet (Datenblatt MF1S50YYX_V1, Abschnitt 10.1.1; Algorithmus in NXP AN10927, Seite 14). Schreibt man sie unverändert, kommt Müll heraus. Ein typischer Moskwjonok-Block 0 beginnt mit `34 00...`, das hängt aber von der Charge ab. Auf dem Proxmark3 lautet die Berechnung `analyse nuid`.

Auf einen 4-Byte-(CUID-)Rohling kopieren:

1. Mach eine Kopie des Original-Dumps.
2. Berechne die neue UID (aus `3400060000DBDC` wird zum Beispiel `2FEDA2F1`).
3. Berechne das BCC-Prüfbyte (aus `2FEDA2F1` wird `0x91`).
4. Schreibe Block 0 der Kopie neu als: berechnete 4-Byte-ID, BCC, `08`, `04`, `00`, Rest unverändert (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Ändere ATQA im Kopf der `.nfc`-Datei auf `00 04` (die meisten Rohlinge haben ein festes ATQA, aber mach es der Korrektheit zuliebe).
6. Schreibe den Dump auf den Rohling.

USCUID-basierte Tags können den Dump unverändert schreiben und dieses Verhalten emulieren, dafür braucht es aber Wissen über die Chipkonfiguration, und das wird hier nicht behandelt.

## Was nicht funktioniert hat

Das Team hat versucht, hohe, niedrige und mittlere UID-Bytes abzuschneiden, die Bytefolge umzudrehen und die NUID aus den 7 Byte gegen 7-Byte-Systeme einzusetzen; nichts davon war erfolgreich.

## Verwandte Seiten

- [MIFARE Classic](/de/nfc/mifare-classic) · [Magic Cards](/de/nfc/magic-cards) · [Karten lesen](/de/nfc/read)
