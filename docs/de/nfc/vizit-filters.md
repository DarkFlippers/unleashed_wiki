---
title: Vizit Leser-Filter
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# Vizit Leser-Filter gegen Klone der Vizit RF 3.1

Wie Vizit-Lesegeräte versuchen, geklonte **Vizit RF 3.1**-Schlüssel (MIFARE Ultralight EV1) zu erkennen, und worauf jeder Filter achtet. Nach dem Artikel von @gromovyna (15.05.2025).

::: tip Geltungsbereich
Nur für deine eigenen Ausweise und für rechtmäßige Forschung.
:::

## Hintergrund

Vizit ist ein russischer Hersteller von Zutrittstechnik (nach eigenen Angaben seit 1996). Alte Lesegeräte nutzten **Dallas**-Schlüssel, dann **EM Marine**; neuere nutzen **Vizit RF 3.1** (= MIFARE Ultralight, UID beginnt mit `34`); die neuesten Schlüssel **Vizit RF 7.1** sind **MIFARE Ultralight C** (3DES-Authentisierung). Die Mindest-Firmware für RF 7.1 ist auf der Herstellerseite angegeben. Der Autor weist darauf hin, dass die Schlüsselableitung der 7.1-Schlüssel iKey bekannt ist und westliche Forscher an der Rückrechnung der 3DES-Schlüssel arbeiten (keine Details veröffentlicht).

## Wie sich diese Systeme gegen Klonen wehren

Anders als bei Iron Logic sind die Vizit-Filter, die der Autor kennt, **Software** und keine Hardware, sie sind also im mit einem Proxmark3 mitgeschnittenen Datenverkehr sichtbar. Gefunden wurden sie im Lesegerät **RD-5F, Firmware 212**; andere Panels tragen sie ebenfalls, aber in welcher Version jeder Filter auftauchte, ist unbekannt.

### Filter 1: Gen1-Backdoor

Das Lesegerät sendet den bekannten Backdoor-Befehl `40(7)` und wartet auf eine Antwort. Ein echter Tag antwortet nicht. Er richtet sich gegen die frühesten Rohlinge (UL-0116 / UL-0416), die über die Backdoor einschließlich der UID beschrieben wurden.

### Filter 2: EV1 VERSION

Das Lesegerät sendet `EV1 VERSION` und vergleicht das **zweite Byte des Ergebnisses** mit dem **ersten Byte der Tag-UID**. Vizit-RF-3.1-Tags melden als Hersteller **Micron Russia** (Byte `34`), und ihre UIDs beginnen mit `34`. Das erledigt USCUID-UL-Varianten (chinesische „UL-21", auf dem russischen Markt „UL-2"). Die Antwort des Marktes waren „ULtra"-Tags, USCUID-UL mit derselben Version wie 3.1 (die sich mit zwei Proxmark3-Befehlen von Hand setzen lässt, wenn die Konfiguration offen ist). Nach 2022 nutzt in der Ukraine Vizit-kompatible Technik (Grazhda-Lesegeräte, Mriya-Panels) Original-NXP-Chips mit der korrekten Version, ULtra-Kopien funktionieren dort also möglicherweise nicht.

### Filter 3: OTP

Page 3 eines Ultralight ist OTP: ab Werk Nullen, Bits lassen sich nur auf 1 setzen, nie zurück (siehe Abschnitt 8.5.4 des Datenblatts MF0ULX1). In normalen USCUID-UL-Tags ist sie frei überschreibbar. Das Lesegerät versucht, Nullen in diese Page zu schreiben, und liest sie zurück; hat sie sich geändert, ist der Tag eine Kopie, das Lesegerät stellt den „Original"-Wert wieder her und weist ihn ab. Ein echter Tag antwortet mit **NACK** und reagiert bis zum nächsten SELECT nicht mehr, was der korrekte Zustandsautomat ist.

Andere Implementierungen hatten denselben Fehler: Flipper Zero verhält sich seit dem NFC-Refactor korrekt, und die Proxmark3-Emulation hatte ihn, bis der Autor ihn meldete ([Issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) und er behoben wurde.

iKeys Antwort war der Rohling **UL-5**, einmal beschreibbar; nachdem Page 0 geändert wurde, sperrt er und verhält sich wie ein Original. Er kommt aus China mit einer Version, die nicht Micron Russia ist. Der Autor vermutet, es handelt sich um einen besonders konfigurierten USCUID-UL. Derselbe Filter lässt sich auch mit regulären USCUID-UL (zum Beispiel in ULtra-Konfiguration) passieren, indem man den Konfigurationsblock richtig ändert, sofern er offen ist.

## Fazit für Besitzer

Vizit RF 7.1 (Ultralight C) erfüllt moderne Sicherheitsstandards und beendet dieses Katz-und-Maus-Spiel.

## Verwandte Seiten

- [Iron Logic Lesegeräte](/de/nfc/iron-logic) · [Magic Cards](/de/nfc/magic-cards) · [Karten lesen](/de/nfc/read)
