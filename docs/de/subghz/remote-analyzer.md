---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (von @xMasterX) dekodiert immer eine Fernbedienung auf dem internen CC1101 und zeigt jedes Feld, das er ermitteln kann. Anders als `Sub-GHz → Read` führt er **keine Historie** — nur das letzte Signal steht auf dem Bildschirm — und er **speichert nie** eine `.sub`-Datei. Er ist ein Werkzeug für die Frage „was ist das für eine Fernbedienung?".

::: tip Unleashed
Remote Analyzer ist eine eingebaute Unleashed-Systemapp. Zusätzlich zu allen Protokollen, die die Sub-GHz-App kennt, hat er eigene, nur dekodierbare Protokolle: **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** und **PC4**.
:::

**Wann du ihn brauchst:** du willst eine unbekannte Fernbedienung schnell identifizieren, sehen, ob sie einen festen oder rollierenden Code nutzt, oder eine Fernbedienung prüfen, die die Haupt-App nicht dekodieren kann. Zum Mitschneiden und Wiederabspielen nimm [Read](/de/subghz/read) oder [Read RAW](/de/subghz/read-raw).

## Hauptmenü

`Main Menu → Apps → Sub-GHz → Remote Analyzer`:

- `Read` — Dekodieren in Echtzeit
- `Decode RAW File` — eine gespeicherte RAW-Aufnahme durch dieselben Dekoder laufen lassen
- `Frequency Analyzer` — die Frequenz der Fernbedienung finden
- `How to use` — die eingebaute Anleitung

## Eine Fernbedienung lesen

1. Öffne `Read`. Auf dem Bildschirm steht `Waiting for a signal`.
2. Drücke <kbd>←</kbd> (`Config`) und setze **Frequency** und **Modulation** (oder schalte **Hopping** ein).
3. Halte die Fernbedienung nah an den Flipper und drücke ihre Taste.
4. Das Ergebnis erscheint:
   - das Symbol oben links sagt **fester** oder **rollierender** Code;
   - die Zeile unter dem Protokollnamen und der Bitzahl sagt, ob die Sub-GHz-App dieses Protokoll ebenfalls kennt oder ob es **nur im Analyzer** verfügbar ist;
   - `xN` oben rechts zählt, wie oft dieser Code empfangen wurde;
   - der Balken unter der Zeile ist die Signalstärke.
5. <kbd>↑</kbd> / <kbd>↓</kbd> scrollen ein Ergebnis, das nicht ganz passt, <kbd>→</kbd> (`Reset`) löscht es.

**Die LED:** violett — hört zu; gelb — es liegt etwas auf dem Äther, das nichts dekodiert hat; grün — ein Code ist durchgekommen.

## Config

| Punkt | Funktion |
|---|---|
| Frequency | Empfangsfrequenz (wird bei aktivem Hopping ignoriert) |
| Modulation | Preset: AM270, AM650, FM238, FM476, FM12K und alle eigenen Presets |
| Hopping | `OFF` oder ein Pegel von `-90dB` bis `-40dB` |
| Sound | das demodulierte Signal über den Lautsprecher ausgeben |
| Mod. sweep | andere Modulationen probieren, wenn nichts dekodiert wird |
| Notify | einmal vibrieren bei einem Code, der sich vom letzten unterscheidet |
| Reset to default | Standardwerte wiederherstellen |

**Hopping.** Ist ein Pegel gesetzt, durchläuft die App **315, 390, 430.5, 433.92, 434.42 und 868.35 MHz**, solange der Äther still ist, und bleibt auf dem ersten Band stehen, auf dem der Träger diesen Pegel erreicht. Eine Dekodierung hält das Band zwei Sekunden, bevor das Hopping weitergeht. Eine Frequenz im Frequency Analyzer zu wählen schaltet das Hopping aus. Der Pegel ist außerdem das, was Sweep und LED als „ein Signal" betrachten — er ist also auch mit Hopping `OFF` wichtig.

**Mod. sweep.** Sendet eine Fernbedienung offensichtlich, aber nichts dekodiert sie, durchläuft die App die anderen Modulationen, jeweils etwa eine Sekunde. Ein `~` neben der Modulation bedeutet, dass sie noch probiert — **halte die Taste der Fernbedienung gedrückt**. Die erste erfolgreiche Dekodierung legt die Modulation fest und das `~` verschwindet; nach zwei Sekunden ohne Dekodierung beginnt der Sweep von dort erneut. `Unknown remote` bedeutet, dass eine ganze Runde nichts gefunden hat; es geht erneut rundherum, solange die Taste gehalten wird.

**Notify.** Eine gehaltene Fernbedienung wiederholt einen Code, das lässt also nur die LED blinken; ein neuer, anderer Code vibriert zusätzlich.

## Decode RAW File

1. Wähle `Decode RAW File` und nimm eine RAW-`.sub` aus `/ext/subghz`.
2. Ein Fortschrittsbalken zeigt, wie weit sie in der Datei ist.
3. Jeder gefundene unterschiedliche Code wird aufgelistet; drücke auf einem <kbd>OK</kbd> für das vollständige Ergebnis.

Nur eine RAW-Aufnahme enthält Samples — eine gespeicherte Schlüsseldatei wird abgewiesen. Wird nichts dekodiert (oder die Datei abgewiesen), piept ein Fehler und die LED bleibt rot.

## Frequency Analyzer

Halte die Taste der Fernbedienung nah am Flipper gedrückt, dann **halte** <kbd>OK</kbd>, um die erkannte Frequenz nach `Read` zu übernehmen. <kbd>←</kbd> / <kbd>→</kbd> verschieben den Triggerpegel. Er funktioniert wie der [Analyzer der Haupt-App](/de/subghz/frequency-analyzer).

## Fehlersuche

- **Immer `Waiting for a signal`** — falsche Frequenz; nimm den Frequency Analyzer oder aktiviere Hopping.
- **Gelbe LED, aber keine Dekodierung** — aktiviere `Mod. sweep` und halte die Taste, oder nimm es mit [Read RAW](/de/subghz/read-raw) auf und probiere `Decode RAW File`.
- **Nur im Analyzer verfügbares Protokoll** — die Haupt-App Sub-GHz kann es nicht speichern oder senden; Remote Analyzer identifiziert es nur.
- **Du willst das Signal speichern** — nimm [Read](/de/subghz/read); diese App schreibt keine Dateien.

## Verwandte Seiten

- [Read](/de/subghz/read) · [Read RAW](/de/subghz/read-raw) · [Frequency Analyzer](/de/subghz/frequency-analyzer)
- [Unterstützte Systeme](/de/subghz/supported-systems)
