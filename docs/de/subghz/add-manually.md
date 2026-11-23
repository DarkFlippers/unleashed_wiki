---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** erzeugt eine völlig neue virtuelle Fernbedienung und speichert sie als `.sub`-Datei. Eine
Originalfernbedienung brauchst du dafür nicht: der Flipper erzeugt eine zufällige Seriennummer (und einen Zähler,
Seed usw., wo das Protokoll sie braucht). Die neue Fernbedienung lässt sich dann **in einem Empfänger anlernen** wie
eine zusätzliche Fernbedienung — genauso, wie du eine im Laden gekaufte Ersatzfernbedienung anlernen würdest.

**Add Manually [Advanced]** macht dasselbe, verlangt aber, dass du jeden Wert selbst in Hex eingibst, statt ihn
erzeugen zu lassen.

::: tip Unleashed
Die Stock-Firmware hat in Add Manually nur eine Handvoll statischer Protokolle. Unleashed listet
**über 100 Systeme** auf, darunter Rolling-Code-Systeme (KeeLoq-Hersteller, FAAC SLH, BFT Mitto,
Nice FloR-S / O-Code, CAME Atomo, Somfy, Security+ 2.0, …), erlaubt für jedes die Wahl aus 15
Frequenz-/Modulationsbändern und ergänzt den Punkt **[Advanced]**.
:::

## Wann du es brauchst

| Situation | Vorgehen |
|---|---|
| Du hast eine **statische** Fernbedienung (fester Code) und willst nur eine Kopie | [Read](/de/subghz/read) und speichern — Add Manually ist nicht nötig |
| Du hast eine **Rolling-Code**-Fernbedienung und willst, dass der Flipper *neben* ihr funktioniert | **Add Manually** → die neue Fernbedienung im Empfänger anlernen ([wie](/de/subghz/remote-prog)) |
| Du brauchst eine Fernbedienung mit bekannten Werten (zurückgerechneter Seed, Installationscode, eine bestimmte Seriennummer) | **Add Manually [Advanced]** |
| Du hast die originale statische Fernbedienung verloren, kennst aber ihre DIP-Schalter / ihren Code | **Add Manually [Advanced]** mit eingetipptem Key |

Warum eine Rolling-Code-Fernbedienung nicht einfach klonen? Siehe [Rolling Codes](/de/subghz/rolling-codes): Klon
und Original streiten sich um den Zähler.

## Eine Fernbedienung anlegen

1. `Main Menu → Sub-GHz → Add Manually`.
2. Scrolle durch die Liste und wähle das System, z. B. `BFT Mitto` oder `KL: DoorHan`. Einträge, die mit `KL:`
   beginnen, sind KeeLoq-Hersteller.

   ![Add Manually: alphabetische Systemliste mit ausgewähltem KL: Allmatic](/screens/subghz/add_manually.png)

3. Es öffnet sich eine **Bandauswahl** mit dem Systemnamen als Kopfzeile. Die Bänder sind als
   `Frequenz Modulation` bezeichnet, z. B. `433.92 AM650`. Das Standardband des Systems steht zuerst, dann die
   anderen Bänder, die dieses System bekanntlich nutzt, dann alle übrigen Bänder (für Anlagen auf einer
   ungewöhnlichen Frequenz). Drücke <kbd>OK</kbd> auf dem Band, das du brauchst.
4. Gib einen Dateinamen ein (einer wird vorgeschlagen) und bestätige.
5. Die Fernbedienung wird in `/ext/subghz/` gespeichert und erscheint unter `Sub-GHz → Saved`.

   ![Menü eines gespeicherten Signals: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Öffne sie: `Sub-GHz → Saved → <deine Datei> → Emulate`. Halte <kbd>OK</kbd> (`Send`) zum Senden; bei
   Protokollen mit [eigenen Tasten](/de/subghz/rolling-codes#custom-buttons) senden die Pfeiltasten die anderen
   Tasten.

   ![Sendebildschirm eines gespeicherten Signals mit R: Int und der Schaltfläche Send](/screens/subghz/emulate.png)


Es wird nichts gesendet, bevor du die Datei öffnest und eine Taste drückst.

::: warning Veraltete Bezeichnungen
Ältere Anleitungen (auch ältere Fassungen von `SubGHzRemoteProg.md`) nennen Einträge wie `BFT Mitto 433MHz`
oder `KL: DoorHan 315MHz`. Die aktuelle Firmware teilt das in zwei Schritte: System (`BFT Mitto`) → Band
(`433.92 AM650`).
:::

### Die 15 Bänder

Alle werden für jedes System angeboten:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → System → Band, dann eine Reihe von Hex-Eingabebildschirmen.
Welche Bildschirme du bekommst, hängt von der Protokollfamilie ab:

| Familie | Bildschirme (in dieser Reihenfolge) |
|---|---|
| Statische Protokolle (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; Protokolle, die eine Zeitdauer speichern, fragen außerdem `Enter TE in us` (und `Enter GT in TE`) |
| KeeLoq (`KL:`-Einträge, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq mit Seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (Hop-Diskriminator, im Feld `Seed` gespeichert) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 Bit) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (Installationscode) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (wird auch im einfachen Add Manually gefragt) |
| Security+1.0 | nichts einzugeben, wird direkt erzeugt |

Die Werte sind Hex in Big-Endian. `BUTTON` und `SERIAL` bilden zusammen den `Fix`, den du nach einem
[Read](/de/subghz/read) siehst: bei KeeLoq ist die Taste die **erste** Hex-Ziffer von `Fix` (Seriennummer = `Fix`
mit dieser Ziffer durch `0` ersetzt), bei FAAC SLH / Genius ist es die **letzte** Ziffer.

::: tip Byte-Eingabe
Die Byte-Eingabe in Unleashed hat einen kleinen Nibble-Editor: drücke <kbd>↑</kbd> mehrmals, bis er erscheint.
:::

## Jeder Eintrag der Liste

Reihenfolge und Bezeichnungen genau wie im Firmware-Menü. „Standard" ist das zuerst gelistete Band; „Außerdem"
sind die alternativen Bänder des Systems, die direkt danach aufgeführt werden.

| Menüeintrag | Standard | Außerdem | Typ |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (Beninca-Schlüssel) |
| `Alutech AT4N` | 433.92 AM650 | | Dynamisch (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dynamisch (einfacher Zähler) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dynamisch (AES-128) |
| `BETT` | 433.92 AM650 | | Statisch |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Statisch |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Statisch |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dynamisch |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Statisch (pseudodynamisch) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + Diskriminator |
| `Ditec GOL4` | 433.92 AM650 | | Dynamisch |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + Diskriminator |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Statisch (12 DIP-Schalter) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Statisch (Fahrradalarm) |
| `Gate TX` | 433.92 AM650 | | Statisch |
| `Genius` | 433.92 AM650 | 868.35 AM650 | FAAC-SLH-Paket, Genius-Schlüssel |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | KeeLoq-artig |
| `Hollarm` | 433.92 AM650 | | Statisch (Fahrradalarm) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dynamisch (auf KeeLoq-Basis) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dynamisch (auf KeeLoq-Basis) |
| `Linear` | **300.00 AM650** | | Statisch (10 Bit) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Statisch |
| `Marantec24` | **868.35 AM650** | | Statisch |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + Diskriminator |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Statisch |
| `Nice Flo 24bit` | 433.92 AM650 | | Statisch |
| `Nice FloR-S` | 433.92 AM650 | | Dynamisch |
| `Nice O-Code` | 433.92 AM650 | | Dynamisch, Installationscode |
| `Nice O-Code One` | 433.92 AM650 | | Dynamisch, Installationscode (Nice-One-Paket) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dynamisch, Installationscode + Zertifikat |
| `Nice One` | 433.92 AM650 | | Dynamisch |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Statisch |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + Diskriminator |
| `Prastel` | 433.92 AM650 | | Dynamisch (42 Bit) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Statisch (24 Bit) |
| `Proteco` | 433.92 AM650 | | Statisch |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Statisch |
| `Roger` | 433.92 AM650 | | Statisch |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dynamisch |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dynamisch |
| `Somfy Keytis` | **433.42 AM650** | | Dynamisch |
| `Somfy Telis` | **433.42 AM650** | | Dynamisch (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Statisch |
| `V2 Phoenix` | 433.92 AM650 | | Dynamisch |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Statisch (Princeton, siehe [ZKTeco CMP200](/de/subghz/zkteco-cmp200)) |

Bei `KL: Sommer` erzeugen die FM476-Bänder die Fernbedienung mit Sommers anderer Modulationsvariante, eine
Menüzeile deckt also beide Sorten von Sommer-Fernbedienungen ab.

## Die neue Fernbedienung in einem Empfänger anlernen

Eine frisch angelegte Rolling-Code-Fernbedienung ist dem Empfänger unbekannt. Lerne sie an wie jede
Ersatzfernbedienung — mit der Lerntaste des Empfängers oder von einer bereits funktionierenden Fernbedienung aus.
Versteckte bzw. Programmiertasten der Originalfernbedienung sendet der Flipper mit einer einzelnen Pfeiltaste.
Vorgehen Schritt für Schritt je Hersteller:
**[Flipper als neue Fernbedienung](/de/subghz/remote-prog)**.

## Fehlersuche

- **`Function requires an SD card with fresh databases.`** — die Datenbanken der Herstellerschlüssel in
  `/ext/subghz/assets/` fehlen oder sind veraltet. Installiere bzw. aktualisiere die Firmware mit eingelegter
  SD-Karte.
- **Der Empfänger reagiert überhaupt nicht** — falsches Band. Lies erst deine Originalfernbedienung
  (`Sub-GHz → Read`) und wähle dieselbe Frequenz und Modulation. DoorHan gibt es auf 315 und 433.92 MHz; FAAC,
  Genius, Erreka auf 433.92 und 868.35.
- **Der Empfänger reagiert, speichert die Fernbedienung aber nie** — das Lernfenster wurde verpasst oder der Empfänger
  hat aus einem anderen Grund (zum Beispiel durch Störungen) kein sauberes Signal vom Flipper erhalten.
- **Neue Erreka-/BFT-Fernbedienung wird abgewiesen** — manche Anlagen teilen einen Seed über alle
  Fernbedienungen; rechne ihn zurück ([Seed Capturer](/de/subghz/seed-capturer)) und nimm Add Manually [Advanced].
  Siehe [KeeLoq](/de/subghz/keeloq).
- **Nice-O-Code-Fernbedienung wird ignoriert** — ein Empfänger im Werkszustand hat keinen Installationscode; nimm
  dort `Nice One` oder `Nice FloR-S`. Für eine installierte Anlage siehe [Nice O-Code](/de/subghz/nice-o-code).

::: warning
Lerne Fernbedienungen nur in Empfängern an, die dir gehören oder die du verwalten darfst.
:::

## Verwandte Seiten

- [Rolling Codes und eigene Tasten](/de/subghz/rolling-codes)
- [Eine neue Fernbedienung im Empfänger anlernen](/de/subghz/remote-prog)
- [KeeLoq](/de/subghz/keeloq) · [Unterstützte Systeme](/de/subghz/supported-systems)
- [Zählermodi](/de/subghz/counter-mode) · [Das `.sub`-Dateiformat](/de/subghz/file-format)
