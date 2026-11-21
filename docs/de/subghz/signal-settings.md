---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** bearbeitet ein Signal, das du schon gespeichert hast: seinen Zählermodus, seinen aktuellen
rollierenden Zähler und seinen Tastencode. Es ist ein kleiner Bildschirm für Fortgeschrittene, versteckt solange
Debug aus ist, und das meiste darin funktioniert nur bei den wenigen Protokollen, die
[Zählermodi](/de/subghz/counter-mode) unterstützen.

## Wo er liegt {#where}

Er ist ein Punkt im Menü eines gespeicherten Signals, kein Eintrag im Sub-GHz-Hauptmenü. Öffne eine Datei über
`Sub-GHz → Saved` (oder aus dem [Archive](/de/apps/archive)), dann lautet das Menü:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## So wird er sichtbar {#enable}

`Signal Settings` kommt nur in dieses Menü, solange **Debug** eingeschaltet ist. Mit ausgeschaltetem Debug fehlt
der Punkt.

- Schneller Weg: halte <kbd>↓</kbd> auf dem Desktop gedrückt, danach <kbd>OK</kbd> auf dem Infobildschirm
  ([Desktop → Geräte-Infobildschirm](/de/start/desktop#info-screen)).
- Oder `Settings → System → Debug` = `ON` ([Einstellungen](/de/start/settings)).

## Die drei Punkte {#items}

![Signal Settings: Counter Mode, Edit Counter und Edit Button](/screens/subghz/signal_settings.png)

| Punkt | Funktion |
|---|---|
| `Counter Mode` | Mit <kbd>←</kbd>/<kbd>→</kbd> wählst du `System` (Modus 0) oder `Mode 1` … bis zur Grenze des Protokolls. Die Wahl landet sofort als Zeile `CounterMode:` in der `.sub`-Datei und die Datei wird neu geladen; gesendet wird nichts |
| `Edit Counter` | <kbd>OK</kbd> öffnet eine Hex-Eingabe für den aktuellen Zähler, überschrieben mit `Enter <N>-bits counter in HEX` und der Zählerlänge des Protokolls: 4 Hex-Ziffern (2 Byte) bis 16 Bit, darüber 8 Ziffern (4 Byte) |
| `Edit Button` | <kbd>OK</kbd> öffnet eine Hex-Eingabe für den Tastencode, überschrieben mit `Enter <N>-bits button in HEX` — immer ein Byte, also 2 Hex-Ziffern |

Welchen Wert ein Punkt gerade enthält, steht hexadezimal in seiner Zeile. Was die Zählermodi selbst mit dem Zähler
machen und wie du einen davon stattdessen durch Bearbeiten der Datei am PC setzt, steht unter
[Zählermodi](/de/subghz/counter-mode#modes-by-protocol).

::: warning Eine bestätigte Zähler- oder Tastenänderung sendet
`Edit Counter` und `Edit Button` schreiben die Datei über den Sendeweg: die Firmware startet einen Sendevorgang mit
dem neuen Wert und stoppt ihn sofort, und beim Stoppen wird die Datei neu geschrieben. Der Sender ist dabei einen
Augenblick aktiv — mach das also abseits des Empfängers, den du nicht bedienen willst.

Der Zähler, den du eingibst, wird genau so gespeichert, wie du ihn getippt hast: für dieses eine Neuschreiben
werden der Zählermodus und die Schrittweite [Counter Incr.](/de/subghz/settings) übersprungen. Bei einer
Tastenänderung setzt die Firmware die Schrittweite stattdessen auf 0, sodass eine geänderte Taste den Zähler dort
lässt, wo er war.

Wird der Sendevorgang abgelehnt — bei einer Frequenz, auf der diese Firmware nicht sendet —, wird die Datei gar
nicht geschrieben.
:::

## Protokolle mit Zählermodi {#protocols}

`Counter Mode` ist bei fünf Protokollen freigeschaltet. `System` ist Modus 0, der normale:

| Protokoll | Auswahl |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

Verglichen wird die Zeile `Protocol:` der Datei. Bei jedem anderen Protokoll ist der Punkt gesperrt.

## Gesperrte Punkte {#locked}

Ein gesperrter Punkt lässt sich nicht öffnen und nicht ändern; beim Drücken erscheint
`Not available for this protocol !`

- `Counter Mode` — das Protokoll der Datei ist keines der fünf oben.
- `Edit Counter` — das Protokoll hat keinen Zähler. Es kann auch am Hersteller hängen: bei KeeLoq ist der Punkt
  für `AN-Motors` gesperrt, das nur einen Pseudo-Zähler hat, und für `Unknown`.
- `Edit Button` — das Protokoll hat in seinem Frame keinen Tastencode.

`Edit Button` ist auch bei den statischen Protokollen mit Tastencode entsperrt — Princeton, Dooya, GangQi,
Hollarm, Nord ICE, Proteco und Roger — und verhält sich dort genauso wie bei einem Rolling-Code-Signal.

## Verwandte Seiten {#related}

- [Zählermodi](/de/subghz/counter-mode) — was jeder Modus macht, und die Dateizeile `CounterMode:`
- [Rolling Codes](/de/subghz/rolling-codes) · [Das `.sub`-Dateiformat](/de/subghz/file-format)
- [Desktop](/de/start/desktop#info-screen) — die Abkürzung zu Debug · [Einstellungen](/de/start/settings) — Debug
  in den Menüs
