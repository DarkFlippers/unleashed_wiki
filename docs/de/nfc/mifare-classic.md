---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic ist die verbreitetste Karte in Zutrittskontrolle, Türsprechanlagen, Hotels und älteren
Verkehrssystemen. Sie ist für den Flipper auch die „interessanteste": ihre Crypto-1-Verschlüsselung ist gebrochen,
mit genug Aufwand lassen sich also die Schlüssel fast jeder Karte zurückrechnen, und danach kann die Karte emuliert
oder auf einen [Magic-Rohling](/de/nfc/magic-cards) geschrieben werden.

## Speicheraufbau

| Typ | Sektoren | Blöcke | Zu findende Schlüssel | Typische SAK |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 Blöcke + 8 × 16 Blöcke) | 256 | 80 | `18` |

- Ein **Block** ist 16 Byte groß. **Block 0** (Herstellerblock) enthält die UID und Herstellerdaten; auf echten
  Karten ist er nur lesbar — genau dafür gibt es Magic Cards.
- Der letzte Block jedes Sektors ist der **Sektor-Trailer**:
  `Key A (6 Byte) | Access Bits (4 Byte) | Key B (6 Byte)`, z. B.
  `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` auf einer leeren Karte.
- Die Access Bits entscheiden, welcher Schlüssel welchen Block lesen/schreiben darf. Oft liest Key A und schreibt
  Key B; manchmal ist Key B selbst lesbar und kann dann nicht als Schlüssel genutzt werden.

## Schlüssel-Wörterbücher

Der Flipper „kennt" Schlüssel nie: er probiert Kandidaten aus Wörterbüchern. Alle sind reine Textdateien mit einem
Schlüssel aus 12 Hex-Ziffern pro Zeile, `#` für Kommentare (siehe [Dateiformat](/de/nfc/file-format)).

| Wörterbuch | Pfad | Wer es schreibt |
|---|---|---|
| **System** | `/ext/nfc/assets/mf_classic_dict.nfc` | Kommt mit der Firmware (wird beim Update überschrieben). In Unleashed enthält es **über 4000 Schlüssel**. |
| **Benutzer** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Du, MFKey, qUnleashed, *Save Keys to Dictionary*. Übersteht Updates. |
| **CUID** (pro Karte) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed für Karten mit *static encrypted* Nonces: eine große Liste von Schlüsselkandidaten für eine UID. |
| **Schlüsselcache** | `/ext/nfc/.cache/<UID>.keys` | Wird automatisch geschrieben, wenn du eine Karte **speicherst**; wird beim nächsten Lesen derselben UID zuerst genutzt. |

::: tip Unleashed
Das Systemwörterbuch von Unleashed enthält eine große Menge zusätzlicher Schlüssel, die die Community gesammelt hat
(„Extra Mifare Classic keys in system dict" im ReadMe). Der Ladebildschirm des CUID-Wörterbuchs mit
Fortschrittsbalken (*„CUID dictionary is loading"*) kam mit Dev-Build 1437 / Release 094.
:::

### Das Benutzerwörterbuch auf dem Gerät verwalten

1. Geh zu `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Menü Extra Actions mit MIFARE Classic Keys unter den Wörterbucheinträgen](/screens/nfc/extra_actions.png)

2. Der Bildschirm zeigt **System dict: N** und **User dict: N**.
3. <kbd>OK</kbd> **Add**: einen 6 Byte langen Schlüssel in Hex eingeben und speichern. Ein doppelter Schlüssel löst
   eine Warnung aus.
4. <kbd>→</kbd> **List** (nur, wenn das Benutzerwörterbuch nicht leer ist): einen Schlüssel zum Löschen auswählen
   (*„Select key to delete:"*).

Du kannst `mf_classic_dict_user.nfc` auch an einem Rechner bearbeiten (qFlipper, qUnleashed oder direkt auf der
SD-Karte).

### Save Keys to Dictionary {#save-keys-to-dictionary}

Jeder gespeicherte oder frisch gelesene MIFARE-Classic-Dump mit mindestens einem bekannten Schlüssel hat
**Save Keys to Dictionary** in seinem Menü. Es kopiert alle Schlüssel dieses Dumps ins Benutzerwörterbuch,
überspringt Duplikate und meldet *„New keys: N, Already known: M"*. Am wichtigsten ist das bei Karten, deren
Schlüssel aus einem CUID-Wörterbuch zurückgerechnet wurden: diese Schlüssel leben sonst nur in dieser Datei pro UID
und im Dump, während [NFC Magic](/de/nfc/nfc-magic) nur in den Schlüsselcache und in das Benutzer- bzw.
Systemwörterbuch schaut (das ist das „automatische Speichern von Schlüsseln mit Duplikatsprüfung", das @gromovyna
in seinem [qUnleashed-Artikel](/de/nfc/qunleashed) erwähnt).

## Was beim Lesen einer MIFARE-Classic-Karte passiert

`Main Menu → NFC → Read`, Karte still halten. Die Firmware durchläuft diese Stufen; die Kopfzeile des
Angriffsbildschirms zeigt, welche läuft.

1. **Schlüsselcache.** Hast du diese UID schon einmal gespeichert, werden die gecachten Schlüssel genutzt und die
   Karte sofort gelesen.
2. **Wörterbuchangriff**, in dieser Reihenfolge:
   - **MF Classic CUID Dictionary**: nur, wenn eine Datei für diese UID existiert (davor *„CUID dictionary is
     loading"* mit Fortschrittsbalken; eine große Datei braucht Minuten zum Laden).
   - **MF Classic User Dictionary**: wenn die Benutzerdatei existiert und nicht leer ist.
   - **MF Classic System Dictionary**.

   Der Bildschirm zeigt `Keys found: X/Y`, `Sectors Read: X/Y`, die aktuelle Schlüsselnummer und
   *„Unlocking sector: N"* / *„Reuse key check for sector: N"*.

   ![Wörterbuchangriff mit dem Systemwörterbuch: Sektor 9 wird entsperrt, Schlüssel 1244 von 2271, 19 von 32 Schlüsseln gefunden](/screens/nfc/dict_attack.png)

3. **Backdoor-Lesen.** Hat der Chip einen bekannten **Backdoor-Schlüssel** (Fudan und einige andere), zeigt die
   Kopfzeile **Backdoor Read** / **(Backdoor)** und die Sektoren werden ohne echte Schlüssel gelesen. Gleichzeitig
   werden Nonces gesammelt.
4. **Nested-Angriffe** (sobald mindestens ein Schlüssel bekannt ist): **PRNG Analysis**, **Nested Dictionary**,
   **Calibration**, **Nonce Collection** (*„Collecting from sector: N"*). Der Zusatz **(Hard)** bedeutet, dass die
   Karte einen harten PRNG hat. Gesammelte Nonces werden an `/ext/nfc/.nested.log` angehängt.
5. Der Ergebnisbildschirm öffnet sich. Eine grüne LED / ein Erfolgston bedeutet, dass die Karte vollständig gelesen
   ist, ein kurzer „Teilerfolg" bedeutet, dass noch Sektoren fehlen.

Drücke <kbd>OK</kbd> **Skip**, um zur nächsten Stufe zu springen (CUID → Benutzer → System → Ergebnis).
<kbd>←</kbd> fragt *„Exit to NFC Menu? All unsaved data will be lost"*. Wird die Karte weggezogen, bekommst du
**„Lost the tag! Make sure the tag is positioned correctly."**; lege sie zurück und der Angriff läuft weiter.

Eine ausführliche Begleitung mit Screenshots zu jeder Phase steht auf
[Nested-Angriffe und Fudan-Backdoors](/de/nfc/nested-fudan).

### Nach dem Lesen

Das Lesemenü (`More`) einer MIFARE-Classic-Karte enthält:

| Punkt | Wann | Funktion |
|---|---|---|
| **Save** | immer | Den Dump in `/ext/nfc/` speichern. Füllt außerdem den Schlüsselcache. |
| **Emulate** | immer | Vollständige Emulation des Dumps. |
| **Extract MFC Keys** | Karte nicht vollständig gelesen | Fragt *„Save the Key?"* (Save/Skip) und sammelt dann Nonces von einem Lesegerät. Siehe [MFKey32](/de/nfc/mfkey). |
| **Unlock with Dictionary** | Karte nicht vollständig gelesen | Führt den Wörterbuch-/Nested-Angriff erneut aus (z. B. nachdem du Schlüssel ergänzt hast). |
| **Crack nonces in MFKey32** | Karte nicht vollständig gelesen | Bietet an, die Karte zu speichern, und startet dann die [MFKey-App](/de/nfc/mfkey-app) (**Run**). |
| **Show Keys** | immer | *„Found MFC Keys"*: Access Bits, Key A, Key B pro Sektor und die Summen. |
| **Save Keys to Dictionary** | mindestens ein Schlüssel bekannt | Siehe oben. |
| **Info** | immer | UID, ATQA, SAK, Übersicht über Schlüssel/Sektoren; **More** zeigt den Hex-Dump (`??` = unbekannte Bytes). |

Bei einer **gespeicherten** Karte bekommst du zusätzlich **Write to Initial Card**, **Update from Initial Card**,
**Restore to Original State** (wenn eine Schattendatei existiert), **Rename** und **Delete**.

## Die fehlenden Schlüssel bekommen

Wurden nicht alle Sektoren gelesen, wähle die Methode, die zu deiner Situation passt:

| Situation | Methode |
|---|---|
| Du hast die Karte **und** Zugang zum Lesegerät | [MFKey32](/de/nfc/mfkey): der Flipper emuliert die Karte, das Lesegerät gibt seine Schlüssel preis. |
| Du hast die Karte, mindestens ein Schlüssel ist bekannt oder der Chip hat eine Backdoor | Nested-Angriffe laufen in `Read` automatisch; berechne die Schlüssel dann mit der [MFKey-App](/de/nfc/mfkey-app) oder, viel schneller, mit [qUnleashed](/de/nfc/qunleashed). |
| Die Karte hat einen **harten PRNG** | HardNested: berechnet von qUnleashed oder an einem PC, siehe [Nested-Angriffe](/de/nfc/nested-fudan). |
| Keine Karte, nur das Lesegerät | [MFKey32](/de/nfc/mfkey) über `Extract MFC Keys` aus dem NFC-Hauptmenü: die Schlüssel landen für später im Benutzerwörterbuch. |
| Die Schlüssel sind pro Karte diversifiziert (z. B. [Iron Logic](/de/nfc/iron-logic)) | Jede Karte hat eigene Schlüssel: rechne sie für jede Karte einzeln zurück. |

Nachdem neue Schlüssel ergänzt sind, lies die Karte erneut (oder öffne die gespeicherte Datei →
**Unlock with Dictionary**).

## Emulation

1. `Main Menu → NFC → Saved → <Karte> → Emulate`.
2. Halte den Flipper an das Lesegerät.

Sektoren, die nie gelesen wurden, werden als unbekannt emuliert: ein Lesegerät, das sie braucht, weist die Karte
ab. Schreibt das Lesegerät auf die Karte (Guthaben, Zähler, „dynamische" Systeme), landen die Änderungen in der
[Schattendatei](/de/nfc/read#shadow-files).

::: warning Dynamische Systeme
Manche Systeme schreiben bei jedem Durchgang Daten auf die Karte um (z. B.
[Iron Logic im dynamischen Modus](/de/nfc/iron-logic-enrollment)). Eine emulierte Kopie und das Original laufen
dann auseinander; beide zu nutzen kann das Original sperren.
:::

## Schreiben

- **Write to Initial Card** schreibt den Dump **auf dieselbe Karte** zurück (die UID muss übereinstimmen). Jede
  andere Karte ergibt *„Use source card! To write blanks use NFC Magic app"*. Konnte nicht jeder Block geschrieben
  werden: *„Not all sectors were written correctly"*.
- Um auf einen Rohling zu klonen, nimm die App [NFC Magic](/de/nfc/nfc-magic) und eine passende
  [Magic Card](/de/nfc/magic-cards). Wähle den Rohling mit Bedacht: viele Lesegeräte filtern Gen1-Karten.

## Fehlersuche

- **Schlüssel gefunden, aber manche Sektoren weiterhin nicht gelesen**: die Access Bits verbieten vielleicht das
  Lesen mit dem gefundenen Schlüsseltyp; rechne den anderen Schlüssel (A oder B) zurück.
- **Das Lesen beginnt mit einem langen „CUID dictionary is loading"**: für diese Karte existiert eine große
  Kandidatenliste pro UID. Das ist nach einem Angriff auf static encrypted Nonces zu erwarten. Lösche
  `/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, sobald die Karte vollständig zurückgewonnen ist und ihre Schlüssel im
  Benutzerwörterbuch stehen.
- **MFKey sagt „Nonces already cracked" / es kommt nichts Neues**: räume `/ext/nfc/.nested.log` und
  `/ext/nfc/.mfkey32.log` nach erfolgreicher Rückrechnung auf; alte Nonces bremsen alles.
- **Zurückgerechnete Schlüssel scheinen nicht genutzt zu werden**: prüfe, ob sie wirklich in
  `mf_classic_dict_user.nfc` gelandet sind (`Extra Actions → MIFARE Classic Keys → List`). Schlüssel, die
  HardNested an einem PC gefunden hat, musst du von Hand ergänzen.

## Verwandte Seiten

[Karten lesen](/de/nfc/read) · [MFKey32](/de/nfc/mfkey) · [Nested-Angriffe](/de/nfc/nested-fudan) ·
[MFKey-App](/de/nfc/mfkey-app) · [qUnleashed](/de/nfc/qunleashed) · [Magic Cards](/de/nfc/magic-cards) ·
[MIFARE Plus](/de/nfc/mifare-plus)
