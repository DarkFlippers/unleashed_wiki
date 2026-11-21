---
title: MIFARE Plus
order: 75
author: gromovyna
original: ["https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/nfc/MIFARE%20Plus%20Detection.md", https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_plus, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [unleashed-docs, unleashed-src, gromovyna]
---
# MIFARE Plus

**MIFARE Plus** ist NXPs Nachfolger von MIFARE Classic. Es kann in mehreren **Sicherheitsstufen** laufen:

| Stufe | Verhalten | Was der Flipper macht |
|---|---|---|
| **SL0** | Werks-/Personalisierungszustand | Erkennt die Karte, UID-Emulation |
| **SL1** | **MIFARE-Classic-kompatibel** (Crypto-1) | Lesen **als MIFARE Classic**: Wörterbücher, Nested-Angriffe, MFKey, qUnleashed gelten alle |
| **SL2** | Daten im Classic-Stil mit AES (nicht bei EV-Teilen) | Erkennt die Karte, UID-Emulation |
| **SL3** | ISO14443-4, AES-128-Authentisierung und Secure Messaging | AES-Wörterbuchangriff, vollständiger Dump, vollständige Emulation, Zurückschreiben auf die Quellkarte |

Produktvarianten: **Plus S**, **Plus X**, **Plus SE**, **Plus EV1**, **Plus EV2** (und ein allgemeines „Plus");
Größen 1K (SE), 2K und 4K.

::: tip Unleashed
Die Erkennung von MIFARE Plus nach Produkt/Stufe/Größe, das **SL3-Lesen mit AES-Wörterbüchern**, *Show Keys*, die
Emulation, *Write to Initial Card* / *Update from Initial Card*, ein Schlüsselcache pro UID und die
MIFARE-Plus-Generatoren in *Add Manually* sind Unleashed-Funktionen.
:::

## Lesen

1. `Main Menu → NFC → Read`, Karte anhalten.
2. **SL1**-Karten werden als MIFARE Classic gelesen (siehe [MIFARE Classic](/de/nfc/mifare-classic)). Die
   Schlüsselrückrechnung für SL1 funktioniert genau wie bei Classic; @gromovynas
   [qUnleashed-Anleitung](/de/nfc/qunleashed) weist darauf hin, dass sie bei MIFARE Plus **nur für SL1** gilt.
3. **SL3**-Karten: der AES-Wörterbuchangriff startet automatisch (Kopfzeile **„MF Plus Dictionary"**). Zuerst werden
   die Benutzerschlüssel probiert, dann das Systemwörterbuch; ein Schlüssel, der von einem früheren Speichern
   derselben UID im Cache liegt, wird vor beiden probiert. Der Bildschirm zeigt *Keys Found* / *Sectors Read*. Es
   gibt keinen eigenen Eintrag „Unlock with Dictionary": der Angriff ist Teil von `Read`.
4. Speichere die Karte. Die Schlüssel werden in `/ext/nfc/.cache/<UID>.mfpkeys` zwischengespeichert, sodass sich das
   nächste Lesen derselben Karte beim ersten Versuch authentisiert.

Wörterbücher: System `/ext/nfc/assets/mf_plus_dict.nfc` (33 AES-128-Schlüssel aus den Proxmark3-Standardwerten),
Benutzer `/ext/nfc/assets/mf_plus_dict_user.nfc`. Verwalte sie in
`NFC → Extra Actions → MIFARE Plus Keys` (**Add** für einen 16-Byte-Schlüssel, **List** zum Löschen).

### Menüs für eine SL3-Karte

- Nach dem Lesen: **Save**, **Emulate**, **Show Keys** (*„Found MFP Keys"*: A-/B-Schlüssel pro Sektor und
  Admin-Schlüssel wie der Card Master Key, plus Summen), **Info**.
- Gespeicherte Karte: **Emulate**, **Write to Initial Card** (schreibt den Dump auf dieselbe Karte zurück),
  **Update from Initial Card** (liest die Quellkarte mit den gespeicherten Schlüsseln erneut; *„Use the source card
  only"* bei anderen), **Show Keys**, **Rename**, **Delete**, **Info**.
- `Info → More` öffnet einen Knotenpunkt mit **View Dump** (Blöcke, Admin-Schlüssel, Konfigurationsblöcke,
  Signatur) und **ISO14443-4 Data** (ATS usw.) → **More** (GetVersion-Felder: Hardware-/Software-Hersteller, Typ,
  Version, Größe, Charge, Produktionswoche/-jahr).

Für andere Stufen wird nur die Identität behalten, und es wird **Emulate UID** angeboten.

## Wie eine MIFARE Plus erkannt wird

Die Firmware kombiniert drei Signale:

1. **SAK**: `08` = 2K SL1, `18` = 4K SL1, `10` / `11` = 2K / 4K SL2, `20` = ISO14443-4 (SL3, aber auch SL0 und
   DESFire).
2. **ATS-Historical-Bytes** der Form `C1 05 …`: identifizieren Plus S / X / SE ohne jeden Schlüssel.
3. **GetVersion** und eine Abfrage der Sicherheitsstufe bei EV1-/EV2-Teilen, die den verbindlichen Typ und die Größe
   liefern.

Weil SAK `20` auch von DESFire genutzt wird, wird eine Karte nur dann als Plus ausgegeben, wenn die Abfrage oder der
ATS-Fingerabdruck es bestätigt.

### Referenz: wie NXP TagInfo es macht

Die Unleashed-Dokumentation enthält eine Analyse von NXPs eigener App **NFC TagInfo** (v6.2.0), die als Referenz
diente. Ihr Entscheidungsverfahren:

```text
NFC tag presented
├─ SAK ∈ {01,08,09,18,19,28,38,88,98,B8} → "Classic lane" (MifareClassic, SL1)
│   ├─ RATS (E0 80) → ATS, then DESELECT (C2)
│   │   match ATS historical bytes → S | X | SE | Engineering
│   ├─ Read-Signature (3C 00), status 90 → EV generation → EV1
│   ├─ security level = SL1 (answers Classic block auth)
│   └─ size = Plus AES First-Auth probe to increasing key-block addresses
└─ SAK == 20 → "ISO-DEP lane" (IsoDep, SL3/EV)
    ├─ SELECT VCA applet (00 A4 04 00 10 A0 00 00 03 96 56 43 41 …) succeeds → SL3
    ├─ GET_VERSION (60 … AF) → EV1 | EV2 (+ storage size)
    └─ size = GET_VERSION storage byte (22 = 2K, 42 = 4K)
```

ATS-Fingerabdrücke (Historical Bytes, byte-genau):

| ATS-Historical-Bytes | Untertyp | Produktcode |
|---|---|---|
| `C1 05 2F 2F 00 35 C7` | Plus **S** | `MF1SPLUS` |
| `C1 05 2F 2F 01 BC D6` | Plus **X** | `MF1PLUS` |
| `C1 05 21 30 00 77 C1` | Plus **SE** | `MF1SEP10` |
| `C1 05 20 30 00 AB 9B` | Plus **SE** (alternativ) | `MF1SEP10` |
| `4D 46 50 5F 45 4E 47` (`"MFP_ENG"`) | Engineering Sample | — |
| keine Übereinstimmung | Plus **X** (Standard) | `MF1PLUS` |

Innerhalb der Familie `C1 05 2F 2F …` unterscheidet Byte 4 S (`00`) von X (`01`). EV1-/EV2-Teile antworten auf
**Read-Signature** (`3C`), Plus S/X nicht. In GetVersion ist das Hersteller-Byte `04` (NXP) und das Speicher-Byte
`22` = 2K, `42` = 4K.

SAK-Auslegung, wie TagInfo sie nutzt:

| SAK | Bedeutung |
|---|---|
| `08` | Classic 1K / Plus 2K SL1 |
| `18` | Classic 4K / Plus 4K SL1 |
| `09` | MIFARE Mini |
| `19` | Classic 2K / Plus 2K-Variante |
| `28`, `38` | SmartMX mit Classic 1K / 4K |
| `88` | NXP Classic 1K (Bit 0x80) |
| `98`, `B8` | SmartMX-/Pro-Varianten |
| `01` | alte / TNP-Markierung |
| `20` | ISO14443-4 → Plus SL3 / EV, DESFire |

Die Speichergröße bei SL1 wird mit Plus-AES-**First-Auth**-Frames `70 XX 40 01 00` an die Schlüsselblöcke `0x4010`,
`0x4020`, `0x4040`, `0x4064` abgefragt: der höchste, der antwortet, begrenzt die Sektorzahl (Basis / 2K / 4K /
erweitert). Ausgegebene Produktcodes: `MF1SPLUS60`/`80` (S 2K/4K), `MF1PLUS60`/`80` (X 2K/4K), `MF1SEP10xx` (SE),
`MF1P2101` (EV1 2K).

## Eine MIFARE Plus von Hand anlegen

`NFC → Add Manually` bietet Plus SE (4-/7-Byte-UID), Plus S, X, EV1 und EV2 in 2K/4K mit 4- oder 7-Byte-UID. Die
erzeugte Karte bekommt die passenden ATS-Historical-Bytes, siehe
[Karten manuell anlegen](/de/nfc/add-manually).

## Verwandte Seiten

[MIFARE Classic](/de/nfc/mifare-classic) · [Karten lesen](/de/nfc/read) · [qUnleashed](/de/nfc/qunleashed) ·
[NFC-Dateiformat](/de/nfc/file-format)
