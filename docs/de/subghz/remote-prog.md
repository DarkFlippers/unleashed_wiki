---
title: Flipper als neue Fernbedienung
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Den Flipper als neue Sub-GHz-Fernbedienung nutzen

Diese Seite handelt davon, den Flipper in eine **ganz neue Fernbedienung** zu verwandeln und ihn im Empfänger deines Tores, deiner Garage oder deiner Jalousie anzulernen — genauso, wie du eine im Laden gekaufte Ersatzfernbedienung anlernen würdest. Es geht **nicht** um das Klonen.

::: warning
Nutze das nur an Empfängern, die dir gehören oder die du verwalten darfst.
:::

## Klon oder neue Fernbedienung? {#clone-or-new}

- **Fernbedienungen mit Rolling Code (dynamisch)**: BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq und der Rest dieser Seite. Jeder Tastendruck sendet einen neuen Code, gebildet aus einem Zähler, und der Empfänger akzeptiert nur einen Zähler, der sich vorwärts bewegt hat. Ein Klon teilt den Zähler des Originals, beide streiten sich also darum: diejenige, die du zuletzt gedrückt hast, funktioniert, und die andere braucht mehrere Tastendrücke, um aufzuholen (siehe [Rolling Codes](/de/subghz/rolling-codes)). Deshalb legst du eine **neue** Fernbedienung an. Sie bekommt ihre eigene Seriennummer und ihren eigenen Zähler und lebt neben deinen Originalfernbedienungen.
- **Fernbedienungen mit statischem (festem) Code**: CAME 12/24 Bit, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX und die übrigen statischen Protokolle. Es gibt keinen Zähler, **Klonen ist also in Ordnung**: die Kopie ist identisch und beide funktionieren weiter, in beliebiger Reihenfolge. Nimm einfach `Sub-GHz → Read` und speichere sie (siehe [Signale lesen](/de/subghz/read)). Diese Seite brauchst du nur, wenn du eine Fernbedienung mit eigenem, separatem Code willst.

## Lies das zuerst {#read-first}

**Was Add Manually macht.** `Main Menu → Sub-GHz → Add Manually` baut eine neue Fernbedienung mit einer zufällig erzeugten Seriennummer und speichert sie als Datei. Es wird nichts gesendet, bevor du diese Datei öffnest und eine Taste drückst. Deine Originalfernbedienungen bleiben unangetastet.

::: tip Unleashed: Add Manually in zwei Schritten
In der aktuellen Unleashed-Firmware besteht das Menü aus zwei Schritten:
1. Wähle das **System** aus der Liste, zum Beispiel `BFT Mitto`, `KL: DoorHan` oder `Somfy Telis`.
2. Wähle das **Band** (Frequenz + Modulation). Die eigenen Bänder des Systems stehen oben, zum Beispiel `433.92 AM650` oder `868.35 AM650`. Alle übrigen Bänder sind darunter aufgeführt, für Anlagen, die ein ungewöhnliches nutzen: `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Dann benennst du die Datei und sie wird in `/ext/subghz/` gespeichert. Ältere Anleitungen schreiben Dinge wie „BFT Mitto 433MHz" als einen Menüpunkt. Heute ist das `BFT Mitto` → `433.92 AM650`.
:::

**Steht dein System nicht auf dieser Seite, unterstützt der Flipper es möglicherweise trotzdem.** Scrolle durch die Liste von `Add Manually`. Ist deine Marke dabei, lege eine Fernbedienung an und folge den Programmierschritten aus der *Anleitung deines Empfängers*. Die vollständige Protokollliste steht unter [Unterstützte Systeme](/de/subghz/supported-systems), und jeder Menüeintrag ist unter [Add Manually](/de/subghz/add-manually) beschrieben.

**Read und Add Manually sind verschiedene Aufgaben.** `Read` schneidet eine Fernbedienung mit, die du schon hast, und spielt sie wieder ab. `Add Manually` legt eine neue Fernbedienung an, die sich im Empfänger anlernen lässt. Viele Protokolle unterstützen nur `Read`.

**Die Tasten des Flippers sind die Tasten der Originalfernbedienung.** Ist eine Fernbedienungsdatei geöffnet (`Saved → Datei → Emulate`):

| Flipper-Taste | Was sie sendet |
|---|---|
| <kbd>OK</kbd> (als `Send` angezeigt) | die Haupttaste der Fernbedienung |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | die anderen Tasten der Fernbedienung (eigene Tasten) |

Welche Pfeiltaste welche Taste sendet, hängt vom Protokoll ab. Eine *versteckte* oder *Programmier*-Taste auf der Originalfernbedienung (eine versenkte Nadelöffnung, zwei gleichzeitig gehaltene Tasten, Kontaktflächen, die du im Gehäuse überbrückst) wird auf dem Flipper zu **einem Tastendruck**. Jeder Abschnitt unten nennt die zugehörige Taste, und die [Referenztabelle](#programming-hidden-button-reference) listet sie alle auf.

Die App [Sub-GHz Remote](/de/subghz/remote) sendet genau dieselben Tasten: jeder Slot einer Map hat eine Einstellung `Button` (`Default`, `Up`, `Down`, `Left`, `Right`), eine versteckte Taste kann also auf einer eigenen Taste liegen.

**Halte die Taste gedrückt.** Der Flipper sendet nur, solange eine Taste gehalten wird. Ein kurzer Tipp sendet oft einen unvollständigen Code. Halte sie 1–3 Sekunden, sofern ein Schritt nichts anderes sagt.

**Das Timing ist entscheidend.** Die meisten Empfänger öffnen ein Programmierfenster von 5, 10 oder 30 Sekunden. Lies das ganze Vorgehen durch, bevor du anfängst.

::: danger
An vielen Empfängern löscht das **zu lange** Halten der Programmiertaste jede Fernbedienung, die er kennt, nicht nur eine. Dann musst du alle deine Originalfernbedienungen neu anlernen. Wenn ein Schritt „etwa 1 Sekunde" sagt, halte sie nicht fünf.
:::

::: info Done! / Done?
Ein Vorgehen, das mit **Done!** endet, ist bestätigt funktionierend. **Done?** bedeutet, dass es aus der Herstelleranleitung stammt, aber noch niemand Rückmeldung gegeben hat. Es sollte funktionieren. Falls nicht, sag es dem Unleashed-Team in den GitHub-Issues.
:::

**Add Manually [Advanced]** ist der Menüeintrag direkt unter `Add Manually`. Nimm ihn, wenn du Werte von Hand eingeben willst statt eine zufällige Seriennummer zu bekommen. Nach System und Band fragt er, alles in Hex, nach `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` und, bei Protokollen, die einen nutzen, nach `Enter SEED in hex`. Nice O-Code fragt stattdessen nach `IC` (und `CERT`). FAAC FIX, Monarch, Phantom/Hiland und DEA Mio fragen nach `DISC.` (Diskriminator) statt nach SEED.

## Finde dein System {#find-your-system}

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

Nicht dabei? Siehe die [Referenztabelle](#programming-hidden-button-reference). Sie deckt jeden weiteren Eintrag im Menü `Add Manually` ab.

---

## Alutech AT4N (AN-Motors) {#alutech-at4n-an-motors}

- **Anlegen:** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

Nimm das für Platinen mit Display und den Tasten `F`, `CL`, `+`, `-`. Hat deine Platine stattdessen eine `Learn`-Taste, nimm [AN-Motors AT4](#an-motors-at4).

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse, finde die Taste `F` und halte sie etwa 3 s. Das Display zeigt `Pr`.
3. Drücke `F` noch ein paar Mal, bis das Display `Lr` zeigt.
4. Wähle mit `+` / `-` eine freie Fernbedienungsnummer. Eine Nummer, auf der schon eine Fernbedienung liegt, zeigt unten rechts einen roten Punkt.
5. Drücke am Flipper einmal <kbd>OK</kbd> (`Send`). Das Display blinkt und neben dieser Nummer erscheint ein roter Punkt.
6. Halte `F` auf der Platine etwa 3 s, um den Programmiermodus zu verlassen.
7. Done!

[Video-Anleitung, zeigt auch andere Platinentypen (russisch)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4 {#an-motors-at4}

- **Anlegen:** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xC`

Nimm das für ältere Platinen mit einer `Learn`-Taste. Hat deine Platine stattdessen `F`, `CL`, `+`, `-`, nimm [Alutech AT4N](#alutech-at4n-an-motors).

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse und drücke einmal `Learn`. Die LED leuchtet.
3. Drücke am Flipper einmal `Send`. Die LED auf der Platine geht aus.
4. Drücke erneut `Send`. Die LED beginnt zu blinken. Warte ein paar Sekunden, bis sie ausgeht.
5. Done!

[Video-Anleitung (russisch)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR {#aprimatic-tr}

- **Anlegen:** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xF` (am Original alle 4 Tasten gleichzeitig gehalten)

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke an einer bestehenden Fernbedienung, die schon mit dem Empfänger funktioniert, alle 4 Tasten gleichzeitig.
3. Der Empfänger gibt einen Dauerton.
4. Drücke am Flipper `Send` und halte etwa 2 s.
5. Warte, bis der Empfänger aufhört zu piepen.
6. Done?

## Beninca ARC (TO.GO) {#beninca-arc-to-go}

- **Auch verkauft als:** TO.GO 2VA / 4VA (früher TO.GO 2WV / 4WV). Empfänger WB, WI und in das Steuergerät eingebaute Empfänger.
- **Anlegen:** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Programmiertaste:** **<kbd>↓</kbd>** = `0x0`, die versteckte Taste

Bei einem Original mit zwei Tasten bedeutet die versteckte Taste, beide gleichzeitig zu halten, was sich schwer zuverlässig hinbekommen lässt. Am Flipper ist es einfach <kbd>↓</kbd>.

### Mit einer funktionierenden Fernbedienung: Empfänger WB / WI {#beninca-wb-wi}

1. Stelle dich nah an den Empfänger.
2. Öffne die Datei der Fernbedienung, die schon funktioniert. Drücke <kbd>↓</kbd> und halte etwa 3 s. Die versteckte Funktion ist nun aktiv (an einer Originalfernbedienung blinkt hier die LED).
3. Drücke innerhalb von 5 s an derselben Fernbedienung `Send` für den Kanal, den du teilen willst.
4. Öffne innerhalb von 5 s deine neue Fernbedienungsdatei und drücke `Send`. Diese Taste steuert dann diesen Kanal.
5. Der Empfänger verlässt den Programmiermodus. Teste die neue Fernbedienung.
6. Done?

### Mit einer funktionierenden Fernbedienung: in das Steuergerät eingebauter Empfänger {#beninca-panel}

Hier muss die versteckte Taste von **beiden** Fernbedienungen gesendet werden:

1. Funktionierende Fernbedienung: <kbd>↓</kbd>, dann innerhalb von 5 s `Send`.
2. Neue Fernbedienung: <kbd>↓</kbd>, dann innerhalb von 5 s `Send`.
3. Done?

::: info
ARC- und HCS-Fernbedienungen (Rolling Code) können sich keinen Empfänger teilen. Die erste Fernbedienung, die du speicherst, entscheidet, welchen Typ der Empfänger von dann an akzeptiert. Das zu ändern braucht ein vollständiges Zurücksetzen des Empfängers.
:::

## BFT Mitto {#bft-mitto}

- **Anlegen:** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xF` (am Original die Nadelöffnung auf der Rückseite oder die Tasten 1+2 gleichzeitig gehalten)

::: info Seed
**Neuere BFT-Mitto-Fernbedienungen leiten ihren Seed aus der Seriennummer ab**, ein normales `Sub-GHz → Read` dekodiert sie also direkt. Sie erscheinen sofort als `KL: BFT`.
**Ältere Modelle haben einen einmaligen Seed** und werden als `KL: Unknown` gelesen, bis du ihn hast. Es gibt zwei Wege, ihn zurückzuholen:
- 2 Tasten halten und den `Hop`-Wert lesen. Die Fernbedienung sendet ihren Seed im Klartext (siehe [Einen vollständigen Klon anlegen](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/de/subghz/seed-capturer) + qUnleashed.
:::

### Mit einer funktionierenden Fernbedienung {#bft-with-remote}

1. Öffne deine neue Fernbedienungsdatei.
2. Stelle dich mindestens 3 m vom Empfänger weg.
3. **Originalfernbedienung:** drücke mit einer Nadel die versteckte Taste auf der Rückseite oder die Tasten 1 und 2 gleichzeitig, bis die LED der Fernbedienung leuchtet.
4. **Originalfernbedienung:** drücke kurz die Taste, die das Gerät öffnet.
5. Drücke am Flipper <kbd>→</kbd> lange (`0xF`, angezeigt als `Btn:F`) für 3–5 s.
6. Drücke am Flipper die Taste, mit der du das Gerät öffnen willst.
7. Drücke erneut <kbd>→</kbd>.
8. Done?

### Mit Zugang zum Empfängergehäuse {#bft-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Gehäuse der Empfängerplatine.
3. [Schau dir zuerst dieses Video an](https://www.youtube.com/watch?v=5QXMBKI_-Ls). Es zeigt die Platinenseite des Vorgehens.
4. Drücke am Flipper <kbd>→</kbd> lange (`0xF`) für 3–5 s. Das macht genau das, was im Video das Halten der Tasten 1 und 2 auf der Originalfernbedienung macht.
5. Done?

### Einen vollständigen Klon anlegen (liest den Seed vom Original) {#making-a-full-clone-reads-the-seed-off-your-original}

::: danger
Das erzeugt eine Kopie, die sich mit deiner Originalfernbedienung um den Zähler **streitet**. Dein Original kann sogar aufhören zu funktionieren, bis es neu angelernt ist. Mache das nur, wenn das Original defekt oder verschlissen ist und der Flipper es ersetzen soll.
:::

1. Öffne `Sub-GHz → Read`.
2. **Nur an der Originalfernbedienung:** halte alle Tasten gleichzeitig (bei einer Zweitastenfernbedienung beide, bei einer Viertastenfernbedienung die zwei in der oberen Reihe) oder drücke die versteckte Taste mit einer Nadel.
3. Du empfängst ein Signal. Öffne es und schau auf `Fix:`. Es beginnt mit `F`, zum Beispiel `F00F1C9B`. Das führende `F` ist der Tastencode für „Programmiertaste gedrückt".
4. Der `Hop:`-Wert genau dieses Signals ist dein Seed.
5. Schreibe den `Hop`-Wert auf und ersetze seine erste Ziffer `F` durch `0`.
6. Drücke nun an deiner Fernbedienung die Taste, die du tatsächlich klonen willst, und lies dieses Signal.
7. Schreibe dessen `Fix:` auf. Die erste Ziffer entspricht dem `Btn:`, das für das Signal angezeigt wird.
8. Lege die Fernbedienung mit `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` an und gib ein:
   - `SERIAL`: der `Fix` aus Schritt 7, dessen **erste** Ziffer durch `0` ersetzt ist
   - `BUTTON`: die erste Ziffer dieses `Fix`
   - `COUNTER`: `FF F9`
   - `SEED`: der Wert aus Schritt 5
9. Ein hoher Zähler wie `FF F9` springt über den Zähler deines Originals hinaus. Das lässt den Klon sofort funktionieren — und genau das desynchronisiert auch das Original.

**Oder bearbeite stattdessen eine gespeicherte Datei.** Speichere das Signal deiner Originalfernbedienung (eine ältere wird als `KL: Unknown` aufgeführt), kopiere die Datei auf einen PC und füge diese beiden Zeilen nach der Zeile `Key: ...` ein:

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Ersetze die `X` durch die Seed-Ziffern aus Schritt 4 und kopiere die Datei zurück. Du hast nun einen exakten Klon mit demselben Zähler.

### Keine versteckte Taste, oder sie sendet den Seed nicht {#bft-no-hidden-button}

Das gilt nur für Fernbedienungen mit einmaligem Seed. Bei einer Fernbedienung, die schon als `KL: BFT` gelesen wird, gibt es nichts zurückzuholen. Kannst du das Original nicht in den Programmiermodus versetzen, nimm die App [Seed Capturer](/de/subghz/seed-capturer): wähle `BFT Mitto` auf 433.92 MHz, drücke eine Taste immer wieder und rechne den Seed dann in qUnleashed zurück.

## CAME Atomo {#came-atomo}

- **Auch verkauft als:** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Anlegen:** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (oder `868.35 AM650`)

::: warning
Halte bei CAME Atomo `Send` immer **mindestens 2 Sekunden**. Das Protokoll braucht so lange, um den ganzen Code hinauszubekommen.
:::

### Mit einer funktionierenden Fernbedienung (oder ihrer Kopie auf dem Flipper) {#atomo-with-remote}

1. Öffne deine neue Fernbedienungsdatei.
2. Stelle dich mindestens 3 m vom Empfänger weg.
3. **Originalfernbedienung:** drücke und halte die Taste, die diesem Empfänger zugeordnet ist, etwa 10 s.
4. Du hast nun etwa 20 s, um die neue Fernbedienung hinzuzufügen.
5. Drücke `Send` in der neuen Fernbedienungsdatei 3–4 s lang und lass los. Damit ist sie angelernt.
6. Warte 20 s, dann drücke und halte `Send` erneut. Jetzt sollte sie den Empfänger betätigen.
7. Done!

### Mit Zugang zum Empfängergehäuse {#atomo-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse und finde die Programmiertaste für den Kanal, den du brauchst. Manche Empfänger haben mehrere Kanäle. Ein RE432M / RE862M zum Beispiel hat zwei, jeder mit eigenen Fernbedienungen und Tasten. Drücke `1` oder `2` auf der Platine, um den Programmiermodus für diesen Kanal zu starten.
3. Drücke am Flipper `Send` 3–4 s lang und lass los.
4. Drücke einmal `CLEAR`, um den Programmiermodus zu verlassen, oder warte etwa 20 s.
5. Done!

::: info
Statische CAME-Fernbedienungen mit 12/24 Bit und CAME TWEE können den Programmiermodus nicht starten, und sie lassen sich nicht in ein Fenster anlernen, das eine Atomo-Fernbedienung geöffnet hat. Das können nur Atomo-Fernbedienungen.
:::

[Video-Anleitung (russisch)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449 {#cardin-s449}

- **Auch verkauft als:** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Empfänger RCQ449.
- **Lesen mit:** Modulation `FM12K`, **nicht** AM650
- **Anlegen:** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Programmiertaste:** <kbd>→</kbd> = `0xD` (am Original die Taste im kleinen Loch unter den Tasten)

1. Öffne deine neue Fernbedienungsdatei.
2. Stelle dich 1–2 m vom Empfänger weg.
3. Öffne die Datei der Fernbedienung, die schon funktioniert. Drücke <kbd>→</kbd> und lass los, wenn der Empfänger einen kurzen Piepton gibt.
4. Drücke an derselben Fernbedienung einmal `Send`. Der Empfänger gibt einen weiteren kurzen Piepton.
5. Öffne deine neue Fernbedienungsdatei und drücke `Send`. Der Empfänger piept zweimal hintereinander.
6. Lass die Taste los. Der Empfänger gibt einen längeren Piepton.
7. Warte mindestens 10 s, dann probiere die neue Fernbedienung.
8. Done?

**Falls es nicht klappt** oder du vor Schritt 5 einen langen Piepton hörst, warte 20 s und fang ab Schritt 3 neu an.

## DEA Mio {#dea-mio}

- **Anlegen:** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xF`, die versteckte Taste

1. Öffne deine neue Fernbedienungsdatei.
2. `Send` wirkt wie eine der normalen Tasten. Diese lernst du an.
3. <kbd>→</kbd> wirkt wie die versteckte Taste der Originalfernbedienung.
4. Folge der Anleitung deines Herstellers zum Hinzufügen einer Fernbedienung und nutze diese beiden Tasten anstelle der Tasten des Originals.

## Ditec GOL4 {#ditec-gol4}

- **Auch verkauft als:** GOL4 / GOL4C. Empfänger BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Anlegen:** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0x0`, die versteckte Taste

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse. Drücke `PRG` und lass los. Die LED `SIG` leuchtet und bleibt an.
3. Drücke am Flipper `Send` für den Kanal, den du speichern willst.
4. `SIG` blinkt während des Speicherns. Leuchtet sie wieder dauerhaft, kannst du eine weitere Fernbedienung hinzufügen.
5. Das Speichern endet 10 s nach der letzten Fernbedienung, oder drücke `PRG` erneut, um es sofort zu verlassen.
6. Done?

::: info
An manchen Platinen muss am Empfänger erst ein Jumper gesetzt werden, damit die Programmierung überhaupt funktioniert. Prüfe die Anleitung deines Empfängers.
:::

## DoorHan {#doorhan}

- **Anlegen:** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (oder `315.00 AM650`)

### Zuerst die Frequenz finden {#doorhan-frequency}

DoorHan nutzt entweder 315.00 oder 433.92 MHz. Lege eine Fernbedienung auf einer davon an, öffne sie und drücke `Send`, während du den Empfänger beobachtest. Hast du richtig geraten, leuchtet die Lampe am Empfänger, solange du die Taste hältst, und geht beim Loslassen aus. Passiert nichts, probiere das andere Band. Du kannst auch einfach deine bestehende Fernbedienung mit `Sub-GHz → Read` lesen.

### Mit Zugang zum Empfängergehäuse {#doorhan-with-receiver}

Nimm die Schutzabdeckung ab und schau auf die Tasten:

- **4 Tasten (`Radio`, `Reverse`, `Auto`, …):** halte `Radio`, bis die LED leuchtet, dann drücke am Flipper 2-mal `Send`. Die LED geht aus.
- **4 Tasten (`R`, `P`, `+`, `-`) und ein Display:** drücke `R`, drücke 2-mal `Send`, warte etwa 10 s.
- **4 Tasten (`+`, `-`, `F`, `TR`) und ein Display:** drücke `TR`, drücke 2-mal `Send`, warte etwa 10 s.
- **Alles andere:** halte `P` etwa 2 s, bis die LED blinkt, dann drücke 2-mal `Send`. Die LED geht aus.

Warte in allen Fällen, bis der Empfänger in den Normalbetrieb zurückkehrt, bevor du testest.

### Mit einer Originalfernbedienung in der Hand {#doorhan-with-original}

1. Öffne deine neue Fernbedienungsdatei.
2. Stelle dich 1–2 m von der Empfängerplatine weg.
3. Drücke an der alten Fernbedienung die zweite (untere) Taste und halte sie, dann drücke zusätzlich die erste (obere). Halte beide 1 s und lass los.
4. Drücke an der alten Fernbedienung die funktionierende Taste (die, die das Tor öffnet). Halte sie 1 s und lass los.
5. Schritt 3 und 4 müssen innerhalb von 5 s aufeinander folgen. Halte nicht zu lange, aber hetze auch nicht.
6. Der Empfänger piept. Du hast nun 10 s: drücke an der neuen Fernbedienung 2-mal `Send` und halte jedes Mal mindestens 1 s.
7. Der Empfänger piept erneut. Die neue Fernbedienung ist angelernt.
8. Done!

### Mit einer Kopie deiner Originalfernbedienung auf dem Flipper {#doorhan-with-copy}

1. Öffne die Datei deiner **bestehenden (originalen)** Fernbedienung.
2. Stelle dich 1–2 m von der Empfängerplatine weg.
3. Drücke <kbd>←</kbd> (`0x8`), halte 1 s, lass los. Dann drücke <kbd>→</kbd> (`0xA`), halte 1 s, lass los.
4. Drücke die funktionierende Taste (<kbd>OK</kbd>, `Send`), halte 1 s, lass los.
5. Schritt 3 und 4 müssen innerhalb von 5 s aufeinander folgen.
6. Der Empfänger piept. Drücke <kbd>Back</kbd> und öffne deine **neue** Fernbedienungsdatei. Drücke innerhalb von 10 s 2-mal `Send` und halte jedes Mal mindestens 1 s.
7. Der Empfänger piept erneut. Die neue Fernbedienung ist angelernt.
8. Done!

[Video-Anleitung (russisch)](https://www.youtube.com/watch?v=wZ5121HYv50) und [eine zweite](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
Ist ein DoorHan-Empfänger gegenüber deiner Datei aus dem Takt geraten, hat Unleashed Zählermodi zur erzwungenen Resynchronisation für DoorHan. Siehe [Zählermodi](/de/subghz/counter-mode).
:::

## Erreka IRIS {#erreka-iris}

- **Auch verkauft als:** IRIS IR02 / IR04 auf 433.92 MHz, IR02/868 / IR04/868 auf 868.35 MHz
- **Anlegen:** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` für IR02 / IR04, oder `868.35 AM650` für die /868-Modelle
- **Programmiertaste:** <kbd>→</kbd> = `0xF` (am Original das Überbrücken der Pins `1` und `5` des fünfpoligen Steckers, der an der Seite der Fernbedienung freiliegt)

Erreka IRIS ist eine Rolling-Code-Fernbedienung: KeeLoq mit geheimem Seed. Beide Anlernverfahren des Herstellers funktionieren vom Flipper aus.

### Mit Zugang zum Empfängergehäuse {#erreka-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Aktiviere den Programmiermodus am Empfänger, normalerweise mit einer Taste auf der Platine.
3. Drücke am Flipper einmal `Send`. Der Empfänger piept **zweimal**, wenn die Fernbedienung gespeichert wurde.
4. Wiederhole Schritt 3 für weitere Fernbedienungen.
5. Schalte den Programmiermodus aus.
6. Done!

### Mit einer funktionierenden Fernbedienung {#erreka-with-remote}

Die originale IRIS öffnet das Programmierfenster, wenn du die Pins `1` und `5` überbrückst. Sie sendet dann ihren Seed im Klartext, und der Empfänger antwortet mit einem Piepton. Am Flipper ist das einfach <kbd>→</kbd>.

Die Fernbedienung, die das Fenster öffnet, muss eine sein, die der Empfänger schon kennt: entweder die erste Flipper-Fernbedienung, die du an der Empfängertaste angelernt hast, oder deine Originalfernbedienung mit zurückgerechnetem Seed (siehe unten).

1. Öffne die Datei der angelernten Erreka-Fernbedienung.
2. Drücke <kbd>→</kbd> (`0xF`) lange, etwa 2 s. Der Empfänger piept **einmal** und ist bereit, Codes zu speichern.
3. Drücke innerhalb von 10 s <kbd>Back</kbd> und öffne deine neue Fernbedienungsdatei.
4. Drücke `Send`. Der Empfänger piept **zweimal**, wenn die Fernbedienung gespeichert wurde.
5. Vergehen 10 s, ohne dass etwas gespeichert wird, verlässt der Empfänger den Programmiermodus. Fang ab Schritt 2 neu an.
6. Done?

### Wenn sich die neue Fernbedienung nicht anlernen lässt {#erreka-shared-seed}

Manche Anlagen geben **jeder Fernbedienung denselben Seed**, weil der Installateur sie als Satz programmiert hat. Dort wird eine Fernbedienung mit zufälligem Seed nie akzeptiert. Die Lösung ist, den bestehenden Seed zu behalten und nur die Seriennummer zu ändern:

1. Hole den Seed von einer Fernbedienung, die schon funktioniert (siehe unten).
2. Lege eine Fernbedienung mit `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (oder `868.35 AM650`) an und gib ein:
   - `SERIAL`: `0X XX XX XX`, ein beliebiger Wert, der keiner deiner bestehenden Fernbedienungen entspricht. **Behalte die führende `0`.** Dieses Nibble ist die Taste, die separat gefragt wird.
   - `BUTTON`: `02`
   - `COUNTER`: `00 02`
   - `SEED`: der Seed aus Schritt 1
3. Führe eines der beiden Anlernverfahren erneut durch.

::: tip Behalte die führenden Nullen
Manche Systeme nutzen nur die letzten 3 oder 4 Stellen der Seriennummer, ihre Fernbedienungen sehen also aus wie `00 00 0A BC`. Dort wird eine lange zufällige Seriennummer womöglich abgewiesen. Lies eine deiner funktionierenden Fernbedienungen, übernimm die Form ihrer Seriennummer (gleiche Zahl signifikanter Stellen, führende Nullen behalten) und ändere nur die letzten Stellen. Zeigen zwei deiner Originalfernbedienungen nach dem Zurückrechnen denselben Seed, hast du so eine Anlage, und den Seed wiederzuverwenden ist der richtige Schritt.
:::

### So holst du den Seed von deiner originalen IRIS {#erreka-get-seed}

Eine Erreka-Fernbedienung wird als `KL: Unknown` gelesen, bis der Seed bekannt ist.

**Möglichkeit 1: die Pins kurzschließen und ihn lesen.** Das ist der schnelle Weg. Die Pins liegen außen am Gehäuse.

1. Öffne `Sub-GHz → Read`. Setze in `Config` die Frequenz auf 433.92 oder 868.35 und die Modulation auf `AM650`.
2. Überbrücke die Pins `1` und `5` des fünfpoligen Steckers an der Originalfernbedienung.
3. Du empfängst ein Signal. Als Hersteller erscheint **Unknown**. Das ist zu erwarten, weil der Flipper den Seed noch nicht kennt.
4. Öffne das Signal. `Fix:` beginnt mit `F`, dem Code für „Programmiertaste gedrückt".
5. **Der `Hop:`-Wert dieses Signals ist dein Seed**, im Klartext.
6. Tippe ihn entweder wie oben in `Add Manually [Advanced]` ein oder speichere das Signal, kopiere es auf einen PC und füge diese Zeilen nach `Key: ...` ein:

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

Die Datei lässt sich nun dekodieren, und du kannst damit das Programmierfenster für neue Fernbedienungen öffnen.

**Möglichkeit 2: [Seed Capturer](/de/subghz/seed-capturer)**, wenn du die Pins nicht überbrücken kannst. Wähle `Erreka` und deine Frequenz, drücke eine Taste immer wieder und rechne den Seed dann in qUnleashed zurück.

## FAAC RC, XT {#faac-rc-xt}

- **Auch verkauft als:** XT2 / XT4 433 RC / 868 RC, sowie die ältere RC-Kodierung
- **Anlegen:** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (oder `868.35 AM650`)
- **Programmiertaste:** <kbd>→</kbd> = `0xB` (am Original die Tasten 1+2 gleichzeitig gehalten, der „Master"-Druck)

::: warning
Das ist KeeLoq, nicht SLH. Lies deine Fernbedienung zuerst. Nennt der Flipper sie `KL: FAAC_RC,XT`, bist du hier richtig. Sagt er `FAAC SLH`, geh zu [FAAC SLH](#faac-slh).
:::

1. Öffne deine neue Fernbedienungsdatei.
2. Stelle dich nah an den Empfänger.
3. Öffne die Datei der Fernbedienung, die schon funktioniert. Drücke <kbd>→</kbd> und halte etwa 1–2 s (bis die LED des Originals anfangen würde zu blinken), dann lass los.
4. Drücke, solange das Fenster offen ist, an derselben Fernbedienung `Send` für die Taste, die du kopieren willst.
5. Öffne deine neue Fernbedienungsdatei und drücke `Send`.
6. Wiederhole Schritt 3–5 für jede weitere Taste.
7. Done?

::: info
Nur eine **Master**-Fernbedienung kann ihren Systemcode weitergeben. Beobachte an einer Originalfernbedienung die LED, wenn du eine Taste drückst. Ein kurzes Blinken, bevor sie dauerhaft leuchtet, bedeutet Master. Leuchtet sie sofort dauerhaft, ist es ein Slave. Bei einem Slave lernst du die neue Fernbedienung stattdessen am Empfänger an.
:::

## FAAC SLH {#faac-slh}

- **Anlegen:** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (oder `868.35 AM650`)
- **Programmiertaste:** **<kbd>↑</kbd>** sendet das Programmiersignal

### Mit Zugang zum Empfängergehäuse {#faac-slh-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse und finde die Programmiertaste auf der Platine.
3. Halte am Flipper <kbd>↑</kbd> und drücke und halte gleichzeitig die Programmiertaste auf der Platine.
4. Die LED der Platine geht an, aus, an, aus und dann wieder an.
5. Lass alles los.
6. Drücke am Flipper ein paarmal `Send` und halte jeden Druck 1–3 s.
7. Done!

[Video-Anleitung](https://www.youtube.com/watch?v=NfZmMy37XUs)

### Mit einer Master-Fernbedienung, ohne das Gehäuse zu öffnen {#faac-slh-with-master}

FAAC kann neue Fernbedienungen von einer bestehenden Master-Fernbedienung aus anlernen, und der Flipper kann dabei mitmachen. Lies zuerst den Seed vom Master:

1. Öffne `Sub-GHz → Read`. Setze die Frequenz auf 868.35 oder 433.92 und die Modulation auf `AM650`.
2. Halte zwei Tasten an der originalen Master-Fernbedienung, bis ihre LED leuchtet.
3. Drücke die eine Taste, für die du den Seed willst. **Der Seed ist für jede Taste anders.**
4. Du empfängst ein Signal. Öffne es und notiere den Seed.
5. Lege die Fernbedienung mit `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (oder 868.35) an und gib ein:
   - `SERIAL`: `0A 0R RR RR`, wobei du jedes `R` durch eine beliebige Ziffer ersetzt
   - `BUTTON`: `06`
   - `COUNTER`: `00 00 00 02`
   - `SEED`: der Seed aus Schritt 4
6. Der Flipper wirkt nun als neue Fernbedienung. Drücke ein paarmal `Send` in der Nähe des Empfängers, um ihn anzulernen.
7. Done!

### Wenn keines von beiden möglich ist {#if-neither-of-those-is-possible}

- **Die Funkprogrammierung des Empfängers ist deaktiviert.** Manche Installateure schalten sie ab, und dann lässt sich nichts anlernen.
- **Deine Fernbedienung ist ein Slave, kein Master.** Nur ein Master kann den Programmiercode senden.

In beiden Fällen bleibt nur der Weg über einen **Klon** einer Fernbedienung, die der Empfänger schon kennt — und der braucht den Seed. Hol ihn mit dem [Seed Capturer](/de/subghz/seed-capturer) und baue den Klon dann mit `SERIAL` und `BUTTON` der **Originalfernbedienung**.

::: tip Wo SERIAL und BUTTON im Fix stecken
- **FAAC SLH und Genius:** `BUTTON` ist die **letzte** Ziffer von `Fix`. `SERIAL` ist der Rest, mit einer `0` davor.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin und die anderen `KL:`-Einträge): `BUTTON` ist die **erste** Ziffer von `Fix`. `SERIAL` ist derselbe `Fix` mit der ersten Ziffer durch `0` ersetzt.
:::

## Genius (SLH) {#genius-slh}

- **Auch verkauft als:** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Anlegen:** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (oder `868.35 AM650`)
- **Programmiertaste:** **<kbd>↑</kbd>** sendet das Programmiersignal

Genius SLH ist dasselbe Paket wie FAAC SLH mit eigenem Herstellerschlüssel (eine Zeile `Manufacture: Genius` in der Datei), **[die FAAC-SLH-Verfahren](#faac-slh) gelten also genau so, wie sie dort stehen**. Ist die Programmierung deaktiviert oder deine Fernbedienung ein Slave, schneide den Seed mit dem [Seed Capturer](/de/subghz/seed-capturer) mit (wähle `Genius`) und baue einen Klon wie unter FAAC SLH beschrieben.

::: warning
Verwechsle das nicht mit `KL: Genius TX4RC`. Die RC-Modelle sind KeeLoq, nicht SLH, und haben [ihren eigenen Abschnitt](#genius-tx4rc-bravo-echo). Bei Unsicherheit lies die Fernbedienung zuerst.
:::

## Genius TX4RC (Bravo / Echo) {#genius-tx4rc-bravo-echo}

- **Auch verkauft als:** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Anlegen:** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xB`

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse und drücke `SW1` für Kanal 1 oder `SW2` für Kanal 2. `LED1` / `LED2` leuchtet und bleibt an. Das ist der Anlernmodus.
3. Drücke innerhalb von 10 s am Flipper `Send` und halte mindestens 1 s.
4. Die LED blinkt zweimal. Die Fernbedienung ist gespeichert.
5. Der Empfänger bleibt im Anlernmodus, du kannst also weitere Fernbedienungen hinzufügen, indem du Schritt 3 wiederholst. Drücke `SW1` / `SW2` erneut zum Verlassen, oder er verlässt ihn selbst 10 s nach der letzten Fernbedienung.
6. Done?

## Hormann EcoStar {#hormann-ecostar}

- **Auch verkauft als:** RSC2 / RSE2 / RSZ1 auf 433.92 MHz. Antriebe EcoStar Liftronic / Portronic.
- **Anlegen:** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Programmiertaste:** **<kbd>↓</kbd>** = `0x6` (diese liegt auf Runter, nicht auf Rechts)

1. Öffne deine neue Fernbedienungsdatei.
2. Finde die transparente Programmiertaste am Antrieb, meist unterhalb des Motors, und halte sie etwa 1 s. Die Motor-LED beginnt langsam zu blinken.
3. Drücke `Send` und halte etwa 2 s. Die Motor-LED blinkt schneller.
4. Drücke `Send` erneut und halte etwa 2 s. Die LED blinkt sehr schnell und geht dann aus. Die Fernbedienung ist programmiert.
5. Done?

::: danger
Diese transparente Taste etwa 5 s zu halten löscht **jede** Fernbedienung, die der Antrieb kennt.
:::

## Jarolift {#jarolift}

- **Auch verkauft als:** TDEF-Funk-Rohrmotoren mit TDRC- / TDRCE-Fernbedienungen
- **Anlegen:** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

Die Tasten sind bereits auf die Tasten der Originalfernbedienung gelegt:

| Flipper-Taste | Jarolift-Taste |
|---|---|
| <kbd>OK</kbd> (`Send`) | Down |
| <kbd>←</kbd> | Up |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

Am Original bedeutet `Learn`, Up + Down gleichzeitig zu halten und dann Stop zu drücken. Am Flipper ist es ein Tastendruck.

### Mit Zugang zum Motorkopf {#jarolift-motor}

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke die Lerntaste am Motorkopf. Der Motor vibriert kurz und bleibt 5 s im Anlernmodus.
3. Kommst du an diese Taste nicht heran, trenne den Motor vom Netz und schließe ihn wieder an. Er geht von selbst für 5 s in den Anlernmodus.
4. Drücke innerhalb dieser 5 s <kbd>↑</kbd> (`Learn`).
5. Der Motor vibriert erneut. Der Code wurde gelernt.
6. Done!

### Mit einer funktionierenden Fernbedienung {#jarolift-with-remote}

1. Öffne deine neue Fernbedienungsdatei.
2. Halte an der funktionierenden Fernbedienung Up + Down gleichzeitig, dann drücke 8-mal Stop. Der Motor vibriert kurz.
3. Drücke innerhalb von 5 s am Flipper <kbd>↑</kbd> (`Learn`).
4. Der Motor vibriert erneut.
5. Done?

::: tip
Liegt die funktionierende Fernbedienung ebenfalls auf deinem Flipper, ist Schritt 2 einfach <kbd>↑</kbd> (`Learn`) in der Datei dieser Fernbedienung.
:::

## KingGates Stylo 4k {#kinggates-stylo-4k}

- **Auch verkauft als:** Stylo 2K / Stylo 4K (10S001). Empfänger Fred, Myo.
- **Anlegen:** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

Es gibt keine separate Programmiertaste. Die vier Tasten sind die vier Kanäle des Originals:

| Flipper-Taste | Kanalcode |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne das Empfängergehäuse. Bei einem zweikanaligen `Fred` zeigt die LED-Farbe den Kanal: grün ist Kanal 1, rot ist Kanal 2.
3. Drücke die Empfängertaste einmal für Kanal 1 (grün) oder zweimal für Kanal 2 (rot). Damit startet der Anlernmodus.
4. Drücke innerhalb von 5 s am Flipper `Send` für etwa 1 s.
5. Die LED geht aus und dann wieder an. Die Fernbedienung wurde gelernt.
6. Das Anlernen endet nach 5 s ohne Signal, oder drücke die Empfängertaste erneut.
7. Done?

## Mhouse {#mhouse}

- **Auch verkauft als:** GTX4 / GTX4C / TX3 / TX4, außerdem Moovo und Nice Home ECCO
- **Anlegen:** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xF`, die zusätzliche (versteckte) Taste

### Mit Zugang zum Empfängergehäuse {#mhouse-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke und halte `P1` am Empfänger, bis die `P1`-LED dauerhaft leuchtet, dann lass los.
3. Drücke `Send` und halte, bis die `P1`-LED dreimal blinkt.
4. Lass los. Damit sind alle Tasten der Fernbedienung in einem Zug angelernt (Nice-„Modus 1").
5. Warte 10 s, bevor du testest.
6. Done?

### Mit einer funktionierenden Fernbedienung {#mhouse-with-remote}

Mhouse gehört zur selben Nice-Empfängerfamilie wie [Nice Smilo](#nice-smilo):

1. Stelle dich nah an den Empfänger.
2. Öffne deine neue Fernbedienungsdatei. Drücke und halte `Send` mindestens 5 s, dann lass los.
3. Drücke an der funktionierenden Fernbedienung ihre Taste und lass sie 3-mal langsam los.
4. Öffne die neue Fernbedienungsdatei erneut, drücke `Send` 1 s und lass los.
5. Warte 10 s, bevor du testest.
6. Done?

## Nice Flor S {#nice-flor-s}

- **Anlegen:** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### Mit einer funktionierenden Fernbedienung {#nice-flor-s-with-remote}

Du brauchst das Empfängergehäuse nicht, **die allererste Fernbedienung muss aber immer mit der Empfängertaste angelernt werden**. Unten ist `OLD` die berechtigte Fernbedienung und `NEW` der Flipper. Stelle dich in 3 m Umgebung des Empfängers.

1. Öffne deine neue Fernbedienungsdatei. Drücke und halte `Send` mindestens 5 s (7 s bei einem OXIBD-Empfänger), dann lass los.
2. Drücke an `OLD` ihre Taste 3-mal langsam.
3. Drücke am Flipper langsam `Send` und lass dann los.
4. Warte 10 s, dann drücke `Send` zum Testen.
5. Done?

### Mit Zugang zum Empfängergehäuse {#nice-flor-s-with-receiver}

Lerne sie so an, wie es die Anleitung deiner Originalfernbedienung beschreibt. Für einen typischen NICE-FLOX2R-Empfänger:

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke die Lerntaste am Empfänger 1–2 s. Die LED leuchtet 5 s. Mache den nächsten Schritt innerhalb dieser 5 s.
3. Drücke `Send`, bis die LED am Empfänger ausgeht.
4. Lass los und warte 2 s.
5. Drücke `Send` erneut. Die LED blinkt dreimal und die Fernbedienung ist angelernt. Falls nicht, fang ab Schritt 2 neu an.
6. Warte 5 s, dann drücke `Send` zum Testen.
7. Done!

::: tip
Zählervarianten von Nice Flor-S für bestimmte Empfänger (floxi2r, ox2) gibt es als [Zählermodi](/de/subghz/counter-mode).
:::

## Nice One {#nice-one}

- **Anlegen:** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One ist die Nice-FloR-S-Familie mit anderer Verschlüsselung, und die Empfängerseite ist identisch. **[Beide Nice-Flor-S-Verfahren](#nice-flor-s) gelten genau so, wie sie dort stehen.** Wird deine Fernbedienung als FloR-S gelesen, der Zähler sieht aber falsch aus, könnte es stattdessen Nice O-Code sein.

## Nice O-Code {#nice-o-code}

- **Anlegen:** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (oder `Nice O-Code One` für die Nice-One-Verschlüsselung)
- **Für eine installierte Anlage anlegen:** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, wo nach `SERIAL`, `BUTTON`, `COUNTER` und dem Installationscode (`Enter IC in hex`) gefragt wird
- **Mit Zertifikat anlegen:** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, wo immer nach Seriennummer, Taste, Zähler, Installationscode **und** dem Empfängerzertifikat (`Enter CERT in hex`) gefragt wird

O-Code ist Nice FloR-S, verschlüsselt mit einem 16-Bit-**Installationscode (IC)**, den alle Fernbedienungen einer Anlage teilen. Die Empfängerseite ist dieselbe wie bei FloR-S, es gelten also [beide Nice-Flor-S-Verfahren](#nice-flor-s) — eine Fernbedienung erreicht aber nur einen Empfänger, der mit demselben Installationscode eingerichtet ist.

- **Für eine eigene Anlage** erfindet das einfache `Nice O-Code` einen Installationscode zusammen mit der Seriennummer. Ein Empfänger im Werkszustand nimmt sie an der Taste nicht an, lerne also zuerst eine einfache [Nice One](#nice-one)-Fernbedienung an.
- **Für eine installierte Anlage** rechne den Installationscode mit der [Nice-O-Code-App](/de/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`) von einer funktionierenden Fernbedienung zurück. Drücke die Taste der Fernbedienung 4-mal oder öfter (nicht halten). Auf dem Ergebnisbildschirm schreibt <kbd>→</kbd> (`New`) eine neue Fernbedienung mit demselben Installationscode und derselben Taste, aber mit eigener Seriennummer und eigenem Zähler. Diese lernst du an. `Save` schreibt einen einfachen Klon zum Testen.

::: info Getestet an einem OXIBD im Werkszustand
Im Modus I **ignoriert der Empfänger O-Code-Pakete vollständig**, welchen Installationscode sie auch tragen, während eine einfache `Nice One`-Fernbedienung sofort gespeichert wird. Nur eine O-Box schreibt den Installationscode in den Empfänger. An einem unangetasteten Empfänger nimm die einfachen Einträge Nice Flor S / Nice One.
:::

::: tip COUNTER
Lass `COUNTER` **nicht** nahe null. Der Empfänger weist einen Zählerstand ab, der hinter dem gespeicherten liegt, und ebenso einen, der unplausibel weit hinter den Fernbedienungen liegt, die er kennt — auch bei einer neuen Seriennummer. Setze ihn etwas unter den Stand deiner funktionierenden Fernbedienung (das `New` der App macht das für dich). Hast du von dieser Seriennummer schon Pakete gesendet, nimm einen Wert etwas über dem höchsten, den du gesendet hast.
:::

**Anlernen per Zertifikat.** Eine Fernbedienung, die das Zertifikat des Empfängers trägt, sendet während ihrer ersten **zwanzig** Nutzungen 112-Bit-Pakete, und der Empfänger lernt sie von selbst an. Öffne die Datei in Reichweite des Tores und drücke die Taste etwa einmal pro Sekunde, **zehn bis fünfzehn Mal in einem Durchgang**. Das Tor öffnet um den zehnten Druck herum, und danach ist die Fernbedienung dauerhaft angelernt. Vergehen alle zwanzig Nutzungen, ohne dass das Tor öffnet, lösche die Datei und lege eine neue an. Zertifikate, die fünf Nice-Anlernwege, die LED-Codes des Empfängers und das Zählerfenster sind ausführlich auf der Seite [Nice O-Code](/de/subghz/nice-o-code) beschrieben.

## Nice Smilo {#nice-smilo}

- **Auch verkauft als:** SM2 / SM4. Empfänger SMXI, SMXIS und OXI mit Smilo-Kodierung.
- **Anlegen:** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0xB`, die zusätzliche (versteckte) Taste

Nice-Empfänger speichern eine Fernbedienung in einem von zwei Modi. **Modus I** gibt jeder Taste der Fernbedienung den passenden Empfängerausgang. **Modus II** lässt dich wählen, welchen Ausgang eine einzelne Taste steuert.

### Mit Zugang zum Empfängergehäuse: Modus I {#smilo-mode-1}

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke und halte die Empfängertaste mindestens 3 s.
3. Lass sie los, wenn die LED leuchtet.
4. Drücke innerhalb von 10 s `Send` und halte mindestens 2 s.
5. Die LED des Empfängers blinkt dreimal. Die Fernbedienung ist gespeichert.
6. Um weitere hinzuzufügen, wiederhole Schritt 4 innerhalb der nächsten 10 s.
7. Done!

### Mit Zugang zum Empfängergehäuse: Modus II {#smilo-mode-2}

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke die Empfängertaste so oft, wie die Ausgangsnummer lautet (zweimal für Ausgang 2).
3. Prüfe, dass die LED genauso oft blinkt.
4. Drücke innerhalb von 10 s die Flipper-Taste, die du für diesen Ausgang willst, und halte mindestens 2 s.
5. Die LED blinkt dreimal. Die Fernbedienung ist gespeichert.
6. Done!

### Mit einer funktionierenden Fernbedienung {#smilo-with-remote}

Die erste Fernbedienung muss immer mit der Empfängertaste angelernt werden. Die neue Fernbedienung **erbt den Modus** der alten, bei Modus II drückst du also an beiden die passenden Tasten.

1. Stelle dich nah an den Empfänger.
2. Öffne deine neue Fernbedienungsdatei. Drücke und halte `Send` mindestens 5 s, dann lass los.
3. Drücke an der funktionierenden Fernbedienung ihre Taste und lass sie 3-mal langsam los.
4. Öffne die neue Datei erneut und drücke `Send` einmal, dann langsam loslassen.
5. Done?

::: info
Diese Empfänger können keine einzelne Fernbedienung löschen, nur alle auf einmal.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman) {#security-1-0-2-0-chamberlain-liftmaster-craftsman}

- **Anlegen:** `Sub-GHz → Add Manually → Security+2.0` oder `Security+1.0`, dann das Band. Standard ist `433.92 AM650`. Security+ 1.0 bietet außerdem `315.00 AM650` und `390.00 AM650`. Security+ 2.0 bietet `310.00`, `315.00` und `390.00 AM650`.

**Welches hast du?** Schau auf die Farbe der `Learn`-Taste am Motorkopf:

| Learn-Taste | Lege das an |
|---|---|
| Gelb | `Security+2.0` |
| Violett | `Security+1.0` → `315.00 AM650` |
| Grün | `Security+1.0` → `390.00 AM650` |
| Rot / orange | Billion Code, nicht Security+ |
| Grau / weiß | Fernbedienung mit DIP-Schaltern, nicht Security+ |

1. Öffne deine neue Fernbedienungsdatei.
2. Finde `Learn` am Motorkopf: meist auf der Rückseite oder der Seitenblende, manchmal hinter der Lampenabdeckung.
3. Drücke sie einmal und lass los. Die Lern-LED leuchtet 30 s dauerhaft.
4. Drücke und halte innerhalb dieser 30 s am Flipper `Send`.
5. Lass los, wenn die Lampen des Antriebs blinken oder du zwei Klicks hörst. Die Fernbedienung ist programmiert.
6. Drücke `Send` erneut, um zu prüfen, ob sich das Tor bewegt.
7. Done?

::: tip
Macht die Taste am Motorkopf nicht mit, lassen manche Anlagen das Programmieren stattdessen von der Wandkonsole aus zu. Zu Keypad-Paketen von Security+ 2.0 siehe [Security+ PIN](/de/subghz/secplus-pin).
:::

## Somfy Keytis {#somfy-keytis}

- **Auch verkauft als:** Keytis NS 2 RTS / KeyGo 4 RTS
- **Anlegen:** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (das sind **433.42 MHz**, nicht 433.92)
- **Programmiertaste:** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` ist `Key_1`)

Eine originale Keytis hat vorne keine `Prog`-Taste. Du überbrückst die beiden `PROG`-Kontaktflächen auf der Rückseite der Platine mit einem Schraubendreher. Der Flipper braucht nur <kbd>↑</kbd>.

### Mit Zugang zum Empfänger {#keytis-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke und halte `PROG` am Empfänger etwa 3 s, bis es blinkt.
3. Drücke am Flipper <kbd>↑</kbd> (`Prog`).
4. Die Jalousie oder das Tor fährt kurz auf und ab. Die Fernbedienung ist angelernt.
5. Done?

### Mit einer funktionierenden Fernbedienung {#keytis-with-remote}

1. Öffne deine neue Fernbedienungsdatei.
2. Versetze die angelernte Fernbedienung in den Programmiermodus, bis sich Jalousie oder Tor kurz bewegen. Bei einer originalen Keytis überbrücke die `PROG`-Kontaktflächen. Am Flipper drückst du <kbd>↑</kbd> in der Datei dieser Fernbedienung.
3. Öffne deine neue Fernbedienungsdatei und drücke <kbd>↑</kbd> (`Prog`), bis sich Jalousie oder Tor erneut kurz bewegen.
4. Done?

::: danger
An vielen Somfy-Empfängern löscht das Halten der Programmiertaste über etwa 7 s hinaus jede Fernbedienung und jeden Sensor, die der Empfänger kennt.
:::

::: info
Keytis nutzt das neuere `NS`-Funkprotokoll. Ein älterer RTS-Empfänger ohne NS akzeptiert sie nicht, bis das Protokoll der Fernbedienung umgestellt ist. Siehe die Dokumentation von Somfy zu deinem Empfänger.
:::

## Somfy Telis {#somfy-telis}

- **Anlegen:** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (das sind **433.42 MHz**, nicht 433.92)
- **Programmiertaste:** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Öffne deine neue Fernbedienungsdatei.
2. Drücke `Prog` an einer Fernbedienung, die am Gerät schon angelernt ist, lange, bis die Jalousien kurz auf und ab fahren.
3. Drücke und halte am Flipper <kbd>←</kbd> (`Prog`), bis die Jalousien erneut kurz auf und ab fahren.
4. Done?

## Sommer {#sommer}

- **Auch verkauft als:** TX03-868-4 / TX03-868-2 (SOMloq). Antriebe Pearl, Duo, Sprint, Marathon.
- **Lesen mit:** Modulation `FM12K` oder `FM476`, je nachdem, welche deine Fernbedienung dekodiert
- **Anlegen:** `Sub-GHz → Add Manually → KL: Sommer`, dann das Band wählen, das dazu passt, wie deine Fernbedienung gelesen wurde: `434.42 FM12K` (Standard), `868.80 FM12K`, `434.42 FM476` oder `868.80 FM476`
- **Programmiertaste:** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Ältere Anleitungen führen vier getrennte Sommer-Einträge auf (`fm2` und einfach). Die aktuelle Firmware hat eine Zeile `KL: Sommer`, und die Bandauswahl wählt sowohl die Frequenz als auch die Modulationsvariante.
:::

### Mit Zugang zum Empfänger {#sommer-with-receiver}

1. Öffne deine neue Fernbedienungsdatei.
2. Finde die Taste `learn` / `code` am Empfänger. Bei einem Duo liegt sie unter der Lampenabdeckung, bei einem Sprint hinter der Abdeckung des Schaltkastens und bei einem Marathon unter einer transparenten Kunststoffabdeckung neben der Code-Taste.
3. Drücke sie kurz. Die LED des Empfängers leuchtet.
4. Drücke und halte `Send`. Lass los, sobald die LED des Empfängers schnell zu blinken beginnt.
5. Die LED des Empfängers geht aus. Die Fernbedienung ist programmiert.
6. Done?

### An einem Schiebetorantrieb {#sommer-sliding-gate}

Drücke stattdessen die Taste `Radio` am Steuergerät. Eine rote LED bestätigt den Programmiermodus. Drücke sie erneut, um den Kanal zu wählen, dann halte `Send`, bis die Kanal-LED blinkt und dunkel wird. Der Empfänger verlässt den Programmiermodus nach etwa 30 s ohne Signal von selbst.

## V2 Phoenix (Phox) {#v2-phoenix-phox}

- **Auch verkauft als:** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Empfänger RXP, MR2.
- **Anlegen:** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Programmiertaste:** <kbd>→</kbd> = `0x3` (am Original die Tasten 1+2 oder 1+3 gleichzeitig gehalten)

::: warning
Diese Zuordnung ist **noch nicht bestätigt**. Falls sie nicht funktioniert, lerne an der Empfängertaste an und melde es in den Unleashed-Issues.
:::

1. Öffne deine neue Fernbedienungsdatei.
2. Öffne die Datei der angelernten Fernbedienung. Drücke <kbd>→</kbd> und halte mindestens 5 s, dann lass los.
3. Öffne innerhalb von 5 s die neue Fernbedienungsdatei und drücke `Send`.
4. Lass los. Wiederhole das für weitere Tasten.
5. Done?

Die Fernbedienung, die das Fenster öffnet, muss im Empfänger schon gespeichert sein, und alles, was so gespeichert wird, erbt ihre Logik. War bei ihr nur Taste 1 gespeichert, lassen sich neue Fernbedienungen nur auf Taste 1 speichern. Manche V2-Empfänger lassen sich in den Modus `Static` umschalten, der den rollierenden Teil des Keys ignoriert.

---

## So holst du einen Seed {#recovering-a-seed}

**FAAC SLH**, **Genius**, **Erreka** und **BFT Mitto** bauen ihren Rolling Code aus einem geheimen **Seed**. Ohne ihn kann der Flipper diese Fernbedienungen nicht dekodieren (sie werden als `KL: Unknown` oder gar nicht gelesen) und keine Fernbedienung bauen, die der Empfänger akzeptiert. Du brauchst den Seed, wenn:

- die Funkprogrammierung des Empfängers abgeschaltet ist, sodass nur ein Klon funktioniert;
- deine FAAC-/Genius-Fernbedienung ein Slave ist und den Programmiercode nicht senden kann;
- du nicht an den Empfänger herankommst;
- eine Erreka-Anlage einen Seed über alle Fernbedienungen teilt;
- eine ältere BFT Mitto nicht in den Programmiermodus geht.

Die App [Seed Capturer](/de/subghz/seed-capturer) (`Apps → Sub-GHz → Seed Capturer`) sammelt aufeinanderfolgende `Fix`-+-`Hop`-Paare einer Taste. Sie sendet nie und speichert sie in `/ext/apps_data/subghz_seed_captures/`. Die Begleit-App qUnleashed (siehe [Die qUnleashed-App](/de/mobile/qunleashed-app)) rechnet den Seed dann per Brute Force zurück und kann die fertige Klon-Datei für dich schreiben.

Sobald du den Seed hast:

- **Neue Fernbedienung** (der Empfänger muss neue Fernbedienungen akzeptieren): `Add Manually [Advanced]` → dein System → Band, deine eigene `SERIAL` und der zurückgerechnete `SEED`.
- **Klon** (funktioniert ohne Programmierung, weil der Empfänger diese Seriennummer schon kennt): lass qUnleashed ihn speichern, oder gib `SERIAL` und `BUTTON` des **Originals**, den `SEED` und einen `COUNTER` etwas über dem aktuellen Wert des Originals ein.

::: danger
Ein Klon teilt den Zähler mit dem Original und beide streiten sich darum. Klone nur, wenn eine neue Fernbedienung unmöglich ist.
:::

## Referenz der Programmier- und versteckten Tasten {#programming-hidden-button-reference}

Suche in der Anleitung deines Herstellers den Schritt „den Empfänger in den Programmiermodus versetzen". Wo immer dort steht, dass du etwas an der Originalfernbedienung drücken sollst, drücke stattdessen die Taste aus dieser Tabelle.

::: info
Das sind die Tasten einer Fernbedienung, wie `Add Manually` sie anlegt. Änderst du den Tastencode von Hand, wandern die Tasten mit.
:::

| System (Eintrag in Add Manually) | Code | Taste am Flipper | An der Originalfernbedienung |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | das Programmiersignal |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | Nadelöffnung auf der Rückseite oder Tasten 1+2 gehalten |
| `Erreka` | `0xF` | <kbd>→</kbd> | Pins 1 und 5 des fünfpoligen Steckers überbrückt |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | versteckte Taste |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | alle 4 Tasten gleichzeitig gehalten |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | Tasten 1+2 gehalten (Master-Druck) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | Taste für den Programmiermodus |
| `KL: Monarch` | `0xB` | *keine Pfeiltaste sendet ihn* | den Tastencode von Hand in den Signal Settings setzen |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | zusätzliche / versteckte Taste *(unbestätigt)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `KL: Sommer` (alle Bänder) | `0x6` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | zusätzliche / versteckte Taste |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | Taste im Loch unter den Tasten |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | zusätzliche / versteckte Taste |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | versteckte Taste (Tasten 1+2 gehalten) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | versteckte Taste |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn`: Up+Down gehalten, dann Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | Taste `Prog` |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | `PROG`-Kontaktflächen auf der Rückseite der Platine |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | Tasten 1+2 oder 1+3 gehalten *(unbestätigt)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | Taste 3 *(als Programmiertaste unbestätigt)* |

### Alles Übrige im Menü {#everything-else}

Jeder Eintrag, der nicht in dieser Tabelle steht und oben keinen Abschnitt hat, wird auf dem einfachen Weg angelernt: **versetze den Empfänger mit seiner eigenen Taste in den Anlernmodus und drücke dann am Flipper `Send` innerhalb des Zeitfensters, das dein Hersteller angibt.**

Das deckt die meisten KeeLoq-Systeme ab (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) sowie jedes statische Protokoll, etwa CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero und [ZKTeco](/de/subghz/zkteco-cmp200).

## Wenn es nicht funktioniert {#troubleshooting}

- **Es passiert überhaupt nichts.** Prüfe zuerst die Frequenz. Das ist der häufigste Fehler. Lies deine Originalfernbedienung mit `Sub-GHz → Read` und vergleiche. Manche Marken verkaufen dieselbe Fernbedienung auf zwei Frequenzen: DoorHan auf 315 und 433.92, FAAC und Genius auf 433.92 und 868.35. Nimm den [Frequency Analyzer](/de/subghz/frequency-analyzer), wenn du unsicher bist.
- **Falsche Modulation.** Die meisten Systeme hier nutzen `AM650`, aber Cardin S449 nutzt `FM12K` und Sommer `FM12K` oder `FM476`. Setze sie in `Sub-GHz → Read → Config` und wähle in Add Manually das passende Band.
- **Der Empfänger reagiert, speichert die Fernbedienung aber nie.** Wahrscheinlich verpasst du das Zeitfenster. Lies die Schritte erneut und habe die Fernbedienungsdatei geöffnet, bevor du die Empfängertaste anfasst.
- **Die Fernbedienung wurde gespeichert, aber nichts öffnet.** Halte `Send` länger. Mehrere Protokolle brauchen 1–3 s, um einen vollständigen Code hinauszubekommen, und CAME Atomo braucht jedes Mal mindestens 2 s.
- **Es hat einmal funktioniert und dann nicht mehr.** An einem Rolling-Code-System ist das ein Zählerproblem: du hast eine Fernbedienung geklont statt eine neue anzulegen. Drücke `Send` noch ein paarmal hintereinander, denn der Empfänger akzeptiert einen Zähler, der innerhalb eines Fensters vorausgelaufen ist. Damit beide Fernbedienungen funktionieren, lege stattdessen eine neue an (siehe [Rolling Codes](/de/subghz/rolling-codes)). Eine statische Fernbedienung hat keinen Zähler — hört sie auf zu funktionieren, prüfe Batterie, Frequenz oder Empfänger.
- **Alle deine Fernbedienungen funktionieren nicht mehr.** Höchstwahrscheinlich hast du eine Programmiertaste lange genug gehalten, um die Löschfunktion des Empfängers auszulösen. Lerne jede Fernbedienung neu an, die Originale eingeschlossen.

## Quellen und Anleitungen {#sources}

- [FAAC SLH: Video-Anleitung](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Beschreibung des Somfy-RTS-Protokolls](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS: Installationsanleitung](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Somfy Keytis NS 2 RTS anlernen (Somfy-Forum)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [BFT-Mitto-Anleitung](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [Programmierung des Empfängers NICE FLOX2R](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Nice Flor S programmieren](https://motepro.com.au/Instructions/Nice.pdf)
- [Anleitung zu Nice Smilo SM2/SM4 und dem Empfänger SMXI](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code: Installateursanleitungen von [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, Empfänger FLOR `IS0063A00MM`, Era-One-Sender `IS0102A01MM`)
- [Programmierung von Mhouse GTX4 / TX4 / Nice Home ECCO5](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS: `Guia rapida mando IRIS` (MSR-044/03), von [erreka.com](https://www.erreka.com/)
- [Anleitung zum Jarolift-TDEF-Motor](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Programmierung der Beninca-TO.GO-Sender](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Anleitung zu den Empfängern Ditec BIX L / BIX A](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Programmieranleitung Cardin S449 QZ2](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Anleitung zum Empfänger Cardin RCQ449](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Anleitung zum Hormann-Handsender RSC2](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer: einen Sender an einem Schiebetorantrieb anlernen](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [Anleitung zum Empfänger V2 RXP4: Funk anlernen](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [Programmierung des KingGates-Empfängers Fred](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Verwandte Seiten {#related}

- [Add Manually](/de/subghz/add-manually)
- [Rolling Codes](/de/subghz/rolling-codes)
- [KeeLoq](/de/subghz/keeloq)
- [Zählermodi](/de/subghz/counter-mode)
- [Unterstützte Systeme](/de/subghz/supported-systems)
- [Seed Capturer](/de/subghz/seed-capturer) · [Nice O-Code](/de/subghz/nice-o-code)
