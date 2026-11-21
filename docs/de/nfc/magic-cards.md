---
title: MIFARE Classic Magic Cards
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# MIFARE Classic Magic Cards (Rohlinge)

Bei einem MIFARE-Classic-Tag lässt sich **Block 0**, der die UID und die Herstellerdaten enthält, nicht
überschreiben. Um eine vollständige Kopie eines solchen Tags zu machen, wurden besondere **Rohlinge** erfunden
(„Magic Cards", „Karten mit beschreibbarer UID"), bei denen Block 0 viele Male oder einmal beschrieben werden kann.

Diese Seite, nach dem Artikel von **@gromovyna**, erklärt kurz, was was ist: Gen1 bis Gen4, die internationalen
Bezeichnungen, die lokalen Marktbezeichnungen (Ex-UdSSR) und welches Verhalten für welches Lesegerät wichtig ist. Sie
nennt Tags, die ohne „Tanz mit dem Tamburin" in Richtung China zu bekommen sind und die der Autor selbst geprüft oder
gesehen hat. Zum Beschreiben mit dem Flipper siehe [NFC Magic 2.0](/de/nfc/nfc-magic).

> „Tag", „Chip", „Karte" und „Anhänger" sind im Folgenden Synonyme: wichtig ist der Chip darin und wie er sich
> verhält, nicht die Bauform.

Zum Weiterlesen:

- die hervorragenden [magic cards notes](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  in der Proxmark3-Dokumentation (englisch), von Forschern aktuell gehalten; sie deckt auch andere Protokolle ab und
  liefert technische Details und Befehle. Mit Erfahrung und einem Proxmark3 kannst du Geld sparen, indem du die
  günstigsten Rohlinge auf einem bestimmten Chip kaufst und sie umkonfigurierst (bei manchen Chips);
- die [Google-Sheets-Tabelle](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  des Autors mit den Tags unten, ihrer Generation, ihren Bezeichnungen und der Angabe, ob Flipper Zero sie
  beschreiben kann.

## Generationen

![Generationen von Magic Tags](/img/remote/f659ade923b6ca4f.png)

Die Aufteilung in Generationen („Gen") ist nicht formal: sie ist ein Versuch, Chips nach ihrem Verhalten zu
klassifizieren. Vier Generationen haben sich etabliert. Ein Chip kann zu mehreren gleichzeitig gehören (z. B.
**M1-4K**). Der Autor folgt der üblichen Klassifikation von Proxmark3, auch wenn er ihr bei manchen Chips nicht
vollständig zustimmt.

| Gen | Spitzname | Wie Block 0 geschrieben wird | Hinweise |
|---|---|---|---|
| **Gen1** | Backdoor | mit speziellen Backdoor-Befehlen | Die älteste. Backdoor-Befehle erlauben immer das Schreiben, Lesen (und bei Gen1a das Löschen) des Tags. Weil ein Filter dagegen trivial ist, **filtert jedes System, das sich selbst respektiert, sie weg**. |
| **Gen2** | Direct Write | Block 0 wird wie jeder andere Block geschrieben | Lässt sich von NFC-Telefonen (meist Android) mit passender Software beschreiben. |
| **Gen3** | APDU | mit einem speziellen APDU-Befehl | Manche erlauben, die UID getrennt von Block 0 zu ändern. Ein seltenes Tier. |
| **Gen4** | Configurable | Konfigurationsblock | Hat Konfiguration und Speicher, lässt sich als verschiedene MFC-Formate (und mehr) einrichten. Die flexibelste; kann das Verhalten von Gen1/Gen2 nachahmen. |

## Gen1 (Backdoor)

### Gen1a

Brauchen zum Schreiben die Backdoor-Befehle `40` (7 Bit) und `43`.

**UID** (russische Bezeichnung: *Zero*). International gibt es sie mit 4-Byte-ID; iKey LLC hat vermutlich auch eine
7-Byte-Variante hergestellt (Bestätigung, dass es derselbe Chip ist, steht aus). Unterstützt außerdem
Backdoor-Lesen (ohne Schlüssel) und Löschen.

**OTP 2.0** (RU; für den ukrainischen Markt auch als **MF** verkauft). Laut iKey LLC eine Eigenentwicklung.
**One time programmable**: nach dem ersten Schreiben (über die Backdoor) sperrt der Chip und verhält sich wie eine
echte MFC. Hat einen **harten PRNG**.

::: tip Anmerkung des Autors
Der Tag entspricht einer echten MFC nicht vollständig und verhält sich unter Stress anders, was es Iron Logic
erlaubte, einen Filter dagegen zu bauen. Wie dieser Filter funktioniert, war dem Autor zum Zeitpunkt des Schreibens
unbekannt.
:::

**MF-4** (RU). Eine verbesserte OTP 2.0. Ebenfalls **one time programmable** nach dem ersten Backdoor-Schreiben,
**harter PRNG**. Laut Beschreibung kann sie:

- die ID-Länge zwischen 4 und 7 Byte umschalten;
- beliebige ATQA/SAK und ATS setzen;
- den PPS-Befehl unterstützen (der, soweit der Autor weiß, überhaupt nicht Teil des MFC-Protokolls ist).

### Gen1b

Wie Gen1, funktioniert aber direkt nach dem Befehl `40` (7 Bit). Gen1b-UID-Chips für MFC 1K hat der Autor selbst
nicht gesehen.

**M1-4K**: ein Chip zum Kopieren von **MIFARE Classic 4K**. Verhält sich gleichzeitig wie **Gen1b und Gen2 CUID**.
Hat eine **statische Nonce `f17e64cd`**.

## Gen2 (Direct Write)

Block 0 lässt sich direkt schreiben. Sie können von Android aus mit der App *Mifare Classic Tool* beschrieben
werden.

### CUID

Russische Bezeichnungen: **MF-3**, **MF3-2**, **MF-8**.

Der wichtigste, (für die meisten Fälle) universelle und verbreitete Chip. Er umgeht einfache Gen1-Filter, ist viele
Male beschreibbar und lässt sich von einem Telefon aus beschreiben: das machte ihn zum Publikumsliebling.

::: tip Anmerkung des Autors
In der Ex-UdSSR sind das Interesse an diesem Chip und die Details seines Verhaltens für **Iron Logic**-Lesegeräte
wichtig, die Filter gegen Rohlinge haben. Diese Lesegeräte sind günstig und deshalb überall. Siehe
[Iron Logic Lesegeräte](/de/nfc/iron-logic).
:::

Viele Chips werden als „CUID" verkauft, und sie können sich im Verhalten in Randfällen unterscheiden. Die neuesten
sind **CUID mit statischer Nonce (MF-3.2)**: zum Zeitpunkt des Schreibens umgehen sie alle bekannten Filter der
Ex-UdSSR (einschließlich Iron Logic „4 Streifen").

Lokale Bezeichnungen:

- **MF-3**: CUID, die Iron-Logic-Filter mit „3 Streifen" umgeht.
- **MF-8**: CUID, die Iron-Logic-OTP-1.0-Filter **nicht** umgeht (eine „fehlerhafte Charge", deren Nummer, die Acht,
  aus einer einfachen Abwandlung der Drei entstand).
- **MF-3.2**: CUID mit statischer Nonce, umgeht alle Iron-Logic-Filter gegen MFC.

In China gibt es außerdem eine **„Perfect CUID"**, die den RATS-Befehl beantwortet (einen praktischen Nutzen dafür
fand der Autor nicht).

## Gen3 (APDU)

Tags, die über APDU-Befehle gesteuert werden. Derzeit die am wenigsten erforschte Kategorie. Potenziell nach Typ
konfigurierbar, nachgewiesen ist das aber nicht. Keine russische Bezeichnung.

Verkauft werden sie für verschiedene MFC-Varianten, in unterschiedlichen Kombinationen:

- nach Speicher: **MFC 1K**, **MFC 4K**, **MIFARE Mini**;
- nach ID-Länge: **4 Byte**, **7 Byte**.

Der Autor besitzt die Varianten MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b und MF Mini (S20) 7b (MFC 1K 4b
existiert höchstwahrscheinlich ebenfalls) und hat sie ein paarmal genutzt, um Hypothesen mit 7-Byte-IDs zu testen,
bevor er entdeckte, wie konfigurierbar USCUID-Chips sind. Diese Vielfalt (und Erfahrungen mit anderen Tags) brachte
ihn auf den Gedanken, dass diese Chips *vielleicht* nach Typ, ID-Länge und Speichergröße konfigurierbar sind.

## Gen4 (konfigurierbar)

Die fortschrittlichsten Chips: ein Konfigurationsblock steuert den Tag und sein Verhalten.

### USCUID (GDM in Proxmark3-Befehlen)

Ein leistungsfähiger, günstiger Chip mit MFC-1K-Speicher plus versteckten Blöcken, die manche Konfigurationen
nutzen. Je nach Konfiguration unterstützt er drei Arten von Backdoor-Befehlen und Direct Write. Er kann 4-Byte- oder
7-Byte-IDs tragen, kann eine MFC-EV1-Signatur zurückgeben, hat einen Shadow-Modus und viele weitere nützliche
Eigenschaften.

Backdoor-Varianten:

- **Gen1a** (`40`/`43`) Magic Wakeup;
- **GDM** (`20`/`23`) Magic Wakeup: genau wie Gen1, aber andere Befehle. Lesegeräte mit Filtern gegen diese Backdoor
  sind bisher nicht gesehen worden (anders als bei Gen1a);
- **Magic Authentication** (Tag auswählen, `8000` + CRC, Crypto-1-Authentisierung mit dem Schlüssel
  `000000000000`).

Kennt man die Konfigurationsprinzipien, lässt sich der Chip für bestimmte Zwecke feinjustieren. Mit aktivierten
Gen1a-/GDM-Backdoors und Befehlen im Gen1-Stil wurde beobachtet, dass Schreiben oder Löschen unzuverlässig ist.
Proxmark3-Nutzer sollten die oben verlinkte Dokumentation des Chips lesen: im Vergleich zur Ultimate Magic Card
kostet er wenig und bietet viel.

Marktkonfigurationen von USCUID:

| Bezeichnung | Russische Bezeichnung | Verhalten |
|---|---|---|
| **FUID** | *OTP* | **One time programmable**: Direct Write von Block 0, dann sperrt der Block. Wurde in der Ex-UdSSR als „OTP" von iKey LLC vermarktet, stellte sich aber als chinesischer Chip heraus. In der Standardkonfiguration hat er eine **GDM**-Backdoor, die ID lässt sich also mehr als einmal ändern und Daten ohne Schlüssel lesen. Anfang November 2024 berichteten Forscher von Versionen mit **gesperrter** Backdoor auf dem chinesischen Markt, was die Wiederverwendung ausschließt. |
| **UFUID** | — | Von den Chinesen als „versiegelbare UID" verkauft. Die Werkskonfiguration hat eine **Gen1a**-Backdoor, viele Male beschreibbar. „Versiegeln": chinesische Duplikatoren (CopyKey u. a.) prüfen nach dem Schreiben den Konfigurationsblock und senden dann einen Befehl, der ihn ändert und die Backdoor abschaltet, wodurch der Tag zu einer gewöhnlichen MFC wird. Ein beschnittener USCUID: er akzeptiert nur einen Teil der Konfiguration. |
| **ZUID** | — | Ein UID-Tag auf einem beschnittenen USCUID. Angesichts der Chippreise ist der Sinn dieser Variante unklar. Akzeptiert nur einen Teil der Konfiguration. |
| **GDM (GDMIC)** | — | Gab USCUID einen seiner ersten Namen. Hauptmerkmal: der **Shadow-Modus**: im Feld gehen alle Änderungen in einen temporären Speicher, der verloren geht, sobald das Feld verschwindet; beim nächsten Mal kommen die Daten aus dem dauerhaften Speicher. Die Chinesen bewerben ihn für Karten mit „verbleibenden Fahrten" (z. B. Liften). Gegen Lesegeräte mit dynamischen Daten (z. B. Eltis-Türsprechanlagen mit ihren Anhängern) hilft er **nicht**. |
| **GDCUID** | — | CUID, umgesetzt auf USCUID. Wird nicht separat verkauft, kann aber beim Kauf von CUID auftauchen. |
| **M1-7B** | — | Zum Schreiben von MIFARE Classic 1K mit **7-Byte**-ID. Hat eine **GDM**-Backdoor. Im 7-Byte-Modus liest er die ID aus einem **versteckten Block**: einen Dump einfach in den Hauptspeicher zu schreiben kann den Tag „bricken" (ist wiederherstellbar). |

Die Bezeichnungen **ZUID** und **GDCUID** hat der Autor selbst vorgeschlagen, während er die Proxmark3-Dokumentation
zu Magic-Chips schrieb.

### Ultimate Magic Card (GTU)

Der derzeit teuerste Chip: großer Speicher und Konfigurationen erlauben ihm, nicht nur als verschiedene MIFARE
Classic-/Mini-Formate zu wirken, sondern auch als MIFARE Ultralight, NTAG und andere (seine
Ultralight-Implementierung ist allerdings recht begrenzt). Die Konfiguration erlaubt:

- **ATQA/SAK** und **ATS** zu ändern;
- eine **ID**-Länge von 4, 7 oder 10 Byte;
- den **Shadow-Modus** und seine Einstellungen;
- **Direct Write** von Block 0 ein- und auszuschalten;
- das **Backdoor-Passwort** zu ändern (von allen Befehlen genutzt);
- **Version** und **Signature** zu setzen;
- in den **Ultralight-Modus** zu wechseln und ihn zu konfigurieren.

Bevor es CUID mit statischer Nonce gab, war die UMC der einzige Rohling, der Iron-Logic-Filter mit „4 Streifen"
umging.

## Übersichtstabelle

![Vergleichstabelle](/img/remote/a29bf09269c612bb.jpg)

Die vollständige, gepflegte Fassung steht in der
[Google-Sheets-Tabelle](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
des Autors.

Hast du Angst, in China den falschen Chip zu kaufen, empfiehlt der Autor den Shop
[FlipperMarket](https://flipper.market/catalog#services-3), wo die wichtigsten in der GUS benötigten Tags (und die
vom Flipper beschreibbaren) von einem erfahrenen Verkäufer ausgewählt und verkauft werden.

## Was der Flipper beschreiben kann

Laut der offiziellen Dokumentation beschreibt Flipper Zero (über die App **NFC Magic**) Magic Cards der Generationen
**Gen1**, **Gen2** und **Gen4** sowie **normale MIFARE Classic**-Karten (ohne die UID zu ändern):

| Rohling | Lässt sich einrichten als |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (eine kompatible Gen2-Karte ist erforderlich) |
| Gen4 (Ultimate) | jede MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
Der Unleashed-Build von **NFC Magic 2.0** erkennt und beschreibt zusätzlich **USCUID-UL**-Rohlinge der
Ultralight-/NTAG-Familie (UL11, UL21 / „Ultra", NTAG213/215/216, UL-C, UL-5) und meldet ehrliche Ergebnisse als
*Success / Partial / Fail*. Siehe [NFC Magic 2.0](/de/nfc/nfc-magic).
:::

### Eine Karte klonen, in Kurzform

1. [Lies](/de/nfc/read) das Original und speichere es. Stelle sicher, dass **alle** Sektoren/Pages gelesen wurden
   (rechne die Schlüssel bei Bedarf mit [MFKey32](/de/nfc/mfkey), [Nested-Angriffen](/de/nfc/nested-fudan) oder
   [qUnleashed](/de/nfc/qunleashed) zurück).
2. Wähle einen Rohling, den das Ziel-Lesegerät akzeptiert (siehe oben: Gen1 wird fast überall gefiltert).
3. Beschreibe ihn mit [NFC Magic](/de/nfc/nfc-magic).

::: tip Rechtliches
Kopiere nur deine eigenen Ausweise oder mit ausdrücklicher Erlaubnis.
:::

## Verwandte Seiten

[NFC Magic 2.0](/de/nfc/nfc-magic) · [MIFARE Classic](/de/nfc/mifare-classic) · [Iron Logic Lesegeräte](/de/nfc/iron-logic) ·
[Vizit Leser-Filter](/de/nfc/vizit-filters)
