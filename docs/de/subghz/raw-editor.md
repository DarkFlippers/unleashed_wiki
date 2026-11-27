---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (von Lechnio) ist ein kleiner Kurveneditor für RAW-`.sub`-Aufnahmen direkt auf dem Gerät. Eine [Read RAW](/de/subghz/read-raw)-Aufnahme enthält meist sekundenlanges Rauschen rund um den kurzen Burst, der dich interessiert. Mit RAW Edit findest du das echte Signal, markierst es und speicherst nur diesen Teil — und du kannst mehrere Dateien zusammenfügen, Stücke herausschneiden und eine Auswahl mit den Sub-GHz-Dekodern der Firmware dekodieren.

::: tip Unleashed
RAW Edit wird mit Unleashed als Systemapp ausgeliefert, und die Sub-GHz-App öffnet sie direkt: `Sub-GHz → Read RAW` (oder `Saved`) → eine RAW-Datei öffnen → <kbd>→</kbd> `More` → `Edit`. Der Punkt `Edit` erscheint nur, wenn RAW Edit installiert ist. Verlässt du den Editor, landest du wieder in Sub-GHz.
:::

**Wann du es brauchst:** eine lange RAW-Aufnahme kürzen, bevor du sie teilst oder sendest, eine Aufnahme in einzelne Tasten aufteilen, mehrere Aufnahmen aneinanderkleben oder herausfinden, welches Protokoll in einer RAW-Datei steckt.

## Hauptmenü

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit`:

- `Select .sub file` — eine Datei aus `/ext/subghz` im Editor öffnen
- `Merge .sub files` — mehrere Dateien zu einer zusammenfügen
- `Config` — Optionen für das Laden und Zusammenfügen
- `About` — Version und Projektlink

Außer RAW-Dateien kann die App jedes Signal laden, das die Firmware kodieren kann (es wird über den internen Encoder in RAW umgewandelt). Bei Protokollen mit eigenen Tasten erscheint zuerst eine Tastenauswahl.

## Der Editor

Der Bildschirm zeigt die Kurve mit einer Übersichtsleiste oben und zwei Zeilen darunter: `View:` (Zoom) und `Marked:` (Länge der Auswahl A..B). Der ausgewählte Bereich ist mit einer gepunkteten Linie hervorgehoben; kleine Markierungen zeigen, dass jenseits des Bildschirmrands noch Signal folgt.

| Taste | Aktion |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | die aktive Marke (A oder B) verschieben; halten verschiebt schneller |
| <kbd>↑</kbd> / <kbd>↓</kbd> | hinein- / herauszoomen |
| <kbd>OK</kbd> | die aktive Marke zwischen A und B umschalten |
| <kbd>OK</kbd> halten | das Aktionsmenü öffnen |
| <kbd>Back</kbd> | den Editor schließen |

Das Aktionsmenü (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> zum Ausführen, <kbd>Back</kbd> zum Schließen) sitzt links, daneben zeigt ein schreibgeschütztes Infofeld die Sample-Anzahl von A..B, `TE` und die erkannte Leitungskodierung (`PWM`, `PPM`, `Manchester`, `NRZ` oder `1:1`):

- **Save** — nur den Bereich A..B in eine neue RAW-Datei schreiben. Der Name wird als `<Name>_edit1`, `_edit2`, … vorgeschlagen. Unter einem bestehenden Namen zu speichern fragt `Name exists, overwrite?`; die geöffnete Datei selbst wird nie überschrieben.
- **Decode** — den Bereich A..B mit den Sub-GHz-Dekodern der Firmware dekodieren (probiert bei jedem KeeLoq-Frame jeden Hersteller durch; überspringt BinRAW), identische Pakete gruppieren (`Decoded: N`) und das ausgewählte als Schlüsseldatei speichern, standardmäßig nach Protokoll und Hersteller benannt (z. B. `KeeLoq_Verex`). Jeder dekodierte Eintrag hat außerdem eine **Locate**-Taste, die A..B auf seinen Frame einrasten lässt (bei Wiederholungen auf den ersten). `No known protocol` bedeutet, dass nichts dekodiert wurde.
- **Cut** / **Copy** / **Paste** — drücke auf `Cut` <kbd>←</kbd> / <kbd>→</kbd>, um zwischen **Cut** (A..B entfernen und in die Zwischenablage legen; wird abgelehnt, wenn das Signal dadurch leer würde), **Copy** (A..B in die Zwischenablage-Datei kopieren) und **Paste** (die Zwischenablage an der aktiven Marke einfügen und markieren) zu wechseln.
- **Undo** — SD-gestützter Verlauf der letzten **32** Schnitte und Einfügungen (belegt keinen RAM). Bei mehr als einer Bearbeitung listet er sie – neueste zuerst – mit Sample-Anzahl und Position auf und setzt auf den Stand vor dem gewählten Eintrag zurück. Durchgestrichen, wenn es nichts rückgängig zu machen gibt.

## Eine Aufnahme kürzen — Schritt für Schritt

1. Nimm die Fernbedienung in [Read RAW](/de/subghz/read-raw) auf und speichere sie.
2. Öffne sie in RAW Edit (über `More → Edit` oder `Select .sub file`).
3. Zoome mit <kbd>↓</kbd> heraus, um zu sehen, wo die Bursts liegen.
4. Verschiebe die Marke **A** mit <kbd>←</kbd>/<kbd>→</kbd> bis knapp vor den Burst, drücke <kbd>OK</kbd> und verschiebe die Marke **B** bis knapp dahinter.
5. Halte <kbd>OK</kbd> → `Save`, übernimm den Namen oder passe ihn an.
6. Teste die gespeicherte Datei aus `Sub-GHz → Saved`.

## Dateien zusammenfügen

1. `Merge .sub files` → eine Datei wählen; der Dialog zeigt `Added N file(s)` und die Zahl der Samples. Wähle `Add more` oder `Done`.
2. Alle Dateien müssen auf derselben Frequenz liegen, sonst bekommst du `Frequency mismatch`.
3. Das Ergebnis öffnet sich im Editor als `merged`; speichere es über das Aktionsmenü.

## Config

| Punkt | Funktion |
|---|---|
| Normalize jitter | `OFF`/`ON` — Zeitjitter und Drift beim Laden bereinigen |
| Merge gap | Stille, die zwischen zusammengefügten Dateien eingefügt wird, 0–1000 ms (Standard 100); <kbd>OK</kbd> öffnet eine Zahleneingabe |
| Repeat | jedes geladene / zusammengefügte Signal 1- bis 64-mal wiederholen |

Eine schreibgeschützte Zeile unten in `Config` zeigt außerdem an, ob eigene Tasten und das Beibehalten des Rolling-Counters im aktuellen Firmware-Build verfügbar sind.

## Grenzen und Fehlersuche

- **Kein Längenlimit (v2.0):** Signale und Zusammenführungen liegen in einer Arbeitsdatei auf der SD-Karte, während der RAM ein gleitendes Fenster der Aufnahme hält (bis zu ~38 000 Samples nach einem frischen Neustart), sodass genug Platz für Decode und Save bleibt. Schiebst du Marke A oder B über den Rand des Fensters hinaus, wandert es um ein Viertel weiter; das Herauszoomen stoppt am Fenster mit `No RAM to zoom out`.
- **Abfrage `Low RAM`** — erscheint, wenn der freie RAM weniger als 15 000 Samples eines größeren Signals fasst; bietet `Reboot` oder `Continue` an. `Decode` prüft außerdem auf ~8 KB freien RAM und meldet `Low memory`, statt abzustürzen.
- `Unsupported protocol or file is empty` — die Datei ist kein Signal, das die Firmware kodieren kann.
- `Nothing in A..B` / `Range too small` — schiebe die Marken weiter auseinander.
- Lange Lücken behalten in der gespeicherten Datei ihre echte Länge.

## Verwandte Seiten

- [Read RAW](/de/subghz/read-raw) · [Dateiformate](/de/subghz/file-format)
- [Remote Analyzer](/de/subghz/remote-analyzer)
