---
title: Read (Lesen)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read (Lesen)

**Read** hört auf einer Frequenz mit (oder springt zwischen mehreren), **dekodiert** Signale bekannter Protokolle
und zeigt sie als Liste. Ein dekodiertes Signal lässt sich als Schlüsseldatei speichern und wieder senden. Das ist
der Hauptweg, eine Fernbedienung mit **statischem (festem) Code** zu kopieren — Tore, Schranken, Türklingeln,
Funksteckdosen — und herauszufinden, welches Protokoll eine Fernbedienung nutzt.

Für Fernbedienungen, die Read nicht erkennt, nimm [Read RAW](/de/subghz/read-raw). Bei Fernbedienungen mit Rolling
Code lies **vor** dem Senden [Rolling Codes](/de/subghz/rolling-codes).

::: tip Unleashed
Gegenüber der Stock-Firmware ergänzt Unleashed: dutzende zusätzliche Protokolle
([vollständige Liste](/de/subghz/supported-systems)), Speichern und Senden vieler **Rolling-Code**-Protokolle,
**eigene Tasten** auf den Pfeiltasten beim Senden, Hopping mit RSSI-Schwelle, die Filter `Ignore …`,
`Delete old signals when memory is full`, **<kbd>→</kbd> halten löscht** ein Signal aus der Liste, die Empfangszeit
bei jedem Signal und das Merken der letzten Einstellungen.
:::

## Eine Fernbedienung lesen

1. Finde zuerst die Frequenz, falls du sie nicht kennst: [Frequency Analyzer](/de/subghz/frequency-analyzer)
   (langes <kbd>OK</kbd> dort springt direkt mit der gefundenen Frequenz in Read).
2. Öffne `Main Menu → Sub-GHz → Read`. Auf dem Display steht `Fixed scan...` (oder `Hopper scan...`, wenn Hopping
   aktiv ist), unten die aktuelle Frequenz und Modulation.

   ![Read-Bildschirm wartet auf ein Signal: Fixed scan auf 433.92 MHz, AM650](/screens/subghz/read.png)

3. Halte die Fernbedienung nah an die linke Seite des Flippers und drücke ihre Taste 1–2 Sekunden lang.
4. Das dekodierte Signal erscheint in der Liste als `Protokollname` + Empfangszeit. Der Zähler unten zeigt, wie
   viele Signale in der Liste stehen.

   ![Read-Liste mit drei empfangenen Signalen: Princeton, CAME 12bit und KL: DoorHan](/screens/subghz/read_list.png)

5. Wähle es mit <kbd>↑</kbd> <kbd>↓</kbd> aus und drücke <kbd>OK</kbd>, um die Details zu sehen (Key, Bitzahl,
   Seriennummer, Taste, Zähler, bei KeeLoq der Hersteller usw.).

   ![Signaldetails: Princeton 24bit mit Key, Seriennummer und Taste, Schaltflächen Send und Save](/screens/subghz/signal_info.png)

6. Drücke <kbd>→</kbd> **Save**, gib einen Namen ein und bestätige. Die Datei landet in `/ext/subghz/`.
7. Oder drücke <kbd>OK</kbd> **Send**, um es gleich zu senden.

Gespeicherte Signale findest du unter `Main Menu → Sub-GHz → Saved` (siehe [unten](#saved-signals)).

## Tasten im Read-Bildschirm

| Taste | Aktion |
|---|---|
| <kbd>←</kbd> | **Config** — Empfängereinstellungen |
| <kbd>↑</kbd> / <kbd>↓</kbd> | In der Liste der empfangenen Signale bewegen |
| <kbd>OK</kbd> | Das ausgewählte Signal öffnen |
| <kbd>→</kbd> halten | Das ausgewählte Signal aus der Liste löschen |
| <kbd>Back</kbd> | Read verlassen. Gibt es ungespeicherte Signale, erscheint **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

Die Liste fasst bis zu 128 Signale (weniger bei großen BinRAW-Aufnahmen, je nach freiem Speicher).

## Config {#config}

Drücke im Read-Bildschirm <kbd>←</kbd> **Config**:

![Menü Read Config: Frequency, Modulation, Hopping und Bin RAW](/screens/subghz/read_config.png)

| Punkt | Werte | Funktion |
|---|---|---|
| `Frequency` | Liste aus [Frequenzen](/de/subghz/frequencies) | Feste Empfangsfrequenz. Zeigt ` -----`, solange Hopping aktiv ist |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + eigene Presets | Demodulations-Preset. `AM650` passt zu den meisten Fernbedienungen |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Durchläuft die Hopper-Liste (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). Der Wert ist der RSSI-Pegel, bei dem das Hopping auf einer Frequenz stehen bleibt |
| `Bin RAW` | `OFF` / `ON` | Sammelt unbekannte statische Signale zusätzlich als **BinRAW** (sich wiederholendes Muster mit rekonstruierter Bitrate). Halte die Taste der Fernbedienung etwas länger, damit genug Daten zusammenkommen |
| `Ignore ReversRB2` | `OFF` / `ON` | Signale von Revers RB-2(M) ausblenden |
| `Ignore Alarms` | `OFF` / `ON` | Protokolle von Fahrrad- und Motorradalarmen ausblenden (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Sensoren und ähnliches Geplapper ausblenden: Magellan, Honeywell, Honeywell WDB und Legrand Türklingeln, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Princeton (PT2262 und Klone) ausblenden — praktisch dort, wo billige Fernbedienungen den Äther überfluten |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Nice Flor-S / Nice One ausblenden |
| `Delete old signals when memory is full` | `OFF` / `ON` | Ist die Liste voll, werden die ältesten Signale verworfen statt abzubrechen. Der Zähler zeigt dann `!` |
| `Sound` | `OFF` / `ON` | Alles, was das Funkmodul empfängt, über den Lautsprecher ausgeben |
| `Reset to default` | — | Zurück auf 433,92 MHz AM650, Hopping aus, alle Filter aus, Bin RAW aus, Sendeleistung `Preset` |
| `Lock Keyboard` | — | Sperrt die Tasten während des Scannens (in der Tasche). **Entsperren: dreimal <kbd>Back</kbd> drücken** |

Alle Read-Einstellungen werden gespeichert und beim nächsten Start der App wiederhergestellt.

::: tip Welchen Hopping-Wert nehmen
Mit aktivem `Hopping` bleibt der Empfänger nur dann auf einer Frequenz, wenn das Signal über dem gewählten Pegel
liegt. `-90dBm` ist der empfindlichste Wert; erhöhe ihn, wenn Rauschen den Hopper immer wieder anhält. Für
zuverlässigen Empfang nimm lieber eine **feste Frequenz**, die du mit dem Analyzer gefunden hast — Signale, die
während eines Frequenzwechsels gesendet werden, gehen verloren.
:::

## Ein Signal senden

Öffne das Signal (aus der Read-Liste oder über `Saved → <Datei> → Emulate`). Der Sendebildschirm zeigt die
Schlüsseldaten, Frequenz, Modulation und `R: Int` / `R: Ext` (welches Funkmodul sendet).

- <kbd>OK</kbd> (**Send**) **halten** — der Flipper sendet **nur, solange die Taste gehalten wird**. Ein kurzer
  Tipp kann einen unvollständigen Code senden; halte 1–2 s (CAME Atomo braucht mindestens 2 s).
- <kbd>Back</kbd> — verlassen.

### Eigene Tasten (Unleashed)

::: tip Unleashed
Bei vielen Protokollen senden die Pfeiltasten **dieselbe Fernbedienung mit einem anderen Tastencode** — so wirkt
eine gespeicherte Datei wie die ganze Fernbedienung. Unterstützt werden unter anderem: KeeLoq, Alutech AT-4N,
Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0, CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift,
KingGates Stylo 4k, V2 Phoenix, Prastel, Roger, Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm.
Solange eine Pfeiltaste gehalten wird, steht der gesendete Tastencode am rechten Bildschirmrand. Welche Pfeiltaste
welche Taste bedeutet, hängt vom Protokoll ab — siehe [Rolling Codes](/de/subghz/rolling-codes) und
[Neue Fernbedienung anlernen](/de/subghz/remote-prog).
:::

## Gespeicherte Signale {#saved-signals}

`Main Menu → Sub-GHz → Saved` listet die Dateien in `/ext/subghz/`. Wähle eine aus, und du bekommst:

- `Emulate` — den Sendebildschirm öffnen;
- `Rename`;
- `Delete`;
- `Signal Settings` — **nur im Debug-Modus** (`Settings → System → Debug`): `Counter Mode`, `Edit Counter`,
  `Edit Button` einer Rolling-Code-Datei ändern. Siehe [Zählermodi](/de/subghz/counter-mode).

RAW-Dateien öffnen sich stattdessen im Read-RAW-Bildschirm — siehe [Read RAW](/de/subghz/read-raw#playback).

Dateinamen werden automatisch erzeugt (Datum-Uhrzeit), außer `Protocol Names` ist in den
[Radio Settings](/de/subghz/settings) aktiv — dann steht der Protokollname vor dem Zeitstempel.

## Statische gegen rollierende Codes

- **Statischer Code** (Princeton, CAME 12/24 Bit, Nice Flo, Marantec, Roger, Gate TX …): jeder Tastendruck sendet
  denselben Code. Eine gespeicherte Kopie funktioniert dauerhaft neben dem Original.
- **Rolling Code (dynamischer Code)** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+ …): jeder
  Tastendruck trägt einen neuen Zählerwert. Unleashed kann viele davon speichern und senden, **aber das Senden
  einer Kopie desynchronisiert die Originalfernbedienung**. Lies [Rolling Codes](/de/subghz/rolling-codes) und lege
  besser mit [Add Manually](/de/subghz/add-manually) eine *neue* Fernbedienung an.

::: danger Autoschlüssel
Experimentiere nicht mit deinem Autoschlüssel. Das Wiederabspielen eines Autoschlüssels (Read oder Read RAW) kann
den Originalschlüssel desynchronisieren oder sperren, und das erneute Anlernen braucht oft Werkstattwerkzeug. Nutze
den Flipper nur mit deiner eigenen Technik und für legale Forschung.
:::

## Fehlersuche

- **Es erscheint nichts** — falsche Frequenz oder Modulation. Nimm den Analyzer, probiere `AM650`, dann
  `FM238`/`FM476`/`FM12K`. Prüfe, ob ein `Ignore …`-Filter das Protokoll ausblendet.
- **Signal empfangen, aber nicht dekodiert** — das Protokoll ist unbekannt: schalte `Bin RAW` ein (statische
  Fernbedienungen) oder nimm es mit [Read RAW](/de/subghz/read-raw) auf. Probiere auch die App
  [Remote Analyzer](/de/subghz/remote-analyzer).
- **KeeLoq zeigt Hersteller `Unknown`** — der Herstellerschlüssel steht nicht in der Datenbank, oder die
  Fernbedienung braucht einen Seed (BFT, Erreka, FAAC SLH). Siehe [KeeLoq](/de/subghz/keeloq) und
  [Seed Capturer](/de/subghz/seed-capturer).
- **Keine Schaltfläche `Send`** — das Protokoll kann nur dekodiert werden (z. B. iDo), oder es ist ein
  Nice-O-Code-Paket ohne Installationscode (nimm die App [Nice O-Code](/de/subghz/nice-o-code)).
- **Die Liste füllt sich mit Rauschen** — aktiviere die passenden `Ignore`-Optionen oder
  `Delete old signals when memory is full`.

## Verwandte Seiten

- [Read RAW](/de/subghz/read-raw) · [Frequency Analyzer](/de/subghz/frequency-analyzer) · [Unterstützte Systeme](/de/subghz/supported-systems)
- [Rolling Codes](/de/subghz/rolling-codes) · [Add Manually](/de/subghz/add-manually) · [Radio Settings](/de/subghz/settings) · [Dateiformate](/de/subghz/file-format)
