---
title: Externes CC1101-Modul
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# Externes CC1101-Modul

Das eingebaute Sub-GHz-Funkmodul des Flippers ist ein CC1101-Chip mit einer kleinen internen Antenne. Du kannst eine zweite CC1101-Platine auf die GPIO-Stiftleiste stecken und die Sub-GHz-App (und die Sub-GHz-Systemapps) stattdessen diese nutzen lassen. Externe Platinen haben meist eine richtige SMA-Antenne und oft einen Leistungsverstärker, reichen also deutlich weiter — beim Empfangen wie beim Senden.

**Wann du es brauchst:** die Fernbedienung oder der Empfänger ist weit weg, die interne Antenne fängt eine schwache Fernbedienung nicht, oder du brauchst mehr Sendereichweite. Um die Frequenz einer Fernbedienung zu finden, nimm weiterhin das interne Funkmodul (siehe [Frequency Analyzer](/de/subghz/frequency-analyzer)).

::: tip Läuft auf jeder Firmware
Externe Funkmodule laufen auf jeder Firmware, auch auf der Stock-Firmware. Die erste Umsetzung schrieb @quen0n für Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)); die heute verwendete stammt von **Skorp** aus der offiziellen Firmware, und Unleashed nutzt diese.
:::

## Verkabelung

Das Modul kommuniziert über den externen SPI-Bus des Flippers. Die Standardverkabelung ist:

| CC1101-Pin | Flipper-GPIO | Pin der Stiftleiste |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 oder 18 |
| Verstärker-/LED-Steuerung (E07-Module) | PC3 | 7 |

Fertige Platinen, Schaltpläne und Fotos findest du in quen0ns Anleitung: [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (aus der Unleashed-FAQ verlinkt). Die Nummerierung der Stiftleiste steht auf der Seite [GPIO-Pinbelegung](/de/gpio/pinout); andere Erweiterungsplatinen findest du unter [Externe Module](/de/gpio/external-modules).

::: warning
Versorge das Modul ausschließlich mit **3,3 V**. CC1101 ist kein 5-V-Chip.
:::

## Auf das externe Modul umschalten

1. Schließe das Modul an, während der Flipper ausgeschaltet ist — mindestens aber, ohne dass eine Sub-GHz-App läuft.
2. Öffne `Main Menu → Sub-GHz → Radio Settings`.
3. Drücke in der Zeile **Module** <kbd>→</kbd>, um `Internal` auf `External` zu ändern.
4. Drücke <kbd>←</kbd> (Back) und nutze `Read`, `Read RAW`, `Saved` usw. wie gewohnt.

Was du erwarten kannst:

- Die Zeile **Module** bietet `External` nur an, wenn tatsächlich ein Modul erkannt wurde. Ist nichts angeschlossen, hat die Zeile nur einen Wert: `Internal`.
- Die Firmware prüft das Modul, wenn du es auswählst. Scheitert die Prüfung, fällt sie auf das interne Funkmodul zurück und die Zeile zeigt wieder `Internal` — was du siehst, ist also das, was wirklich genutzt wird.
- Im Sendebildschirm eines gespeicherten Signals zeigt die untere Zeile `R: Int` oder `R: Ext` — das Funkmodul, das senden wird.
- Die Sub-GHz-Systemapps ([Nice O-Code](/de/subghz/nice-o-code), [Seed Capturer](/de/subghz/seed-capturer), [Security+ PIN](/de/subghz/secplus-pin)) zeigen `Int` oder `Ext` in ihrer Kopfzeile und nutzen ein externes Modul automatisch, wenn eines angeschlossen ist.

## Weitere Radio Settings

`Sub-GHz → Radio Settings` enthält:

| Punkt | Werte | Funktion |
|---|---|---|
| Module | `Internal` / `External` | Funkmodul, das die Sub-GHz-App nutzt |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | überschreibt die Sendeleistung des Presets; `Preset` behält die Leistung aus dem Modulations-Preset |
| Protocol Names | `OFF` / `ON` | siehe [Einstellungen](/de/subghz/settings) |
| Counter Incr. | `+1` … | siehe [Einstellungen](/de/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **nur im Debug-Modus** — den Pin für die Verstärker-/LED-Steuerung (PC3, Pin 7 der Stiftleiste) von E07-artigen Modulen ansteuern |
| Debug Pin | `OFF` / `17(1W)` | **nur im Debug-Modus** — das Signal auf Pin 17 spiegeln, für die Protokollentwicklung |

`Ext Amp & LEDs` ist **standardmäßig ON**. Damit tastet die Firmware den Verstärker des Moduls an PC3 nur dann an, wenn der Chip wirklich sendet. Schalte es nur aus, wenn dein Modul Pin 7 anders nutzt; der Menüpunkt erscheint, wenn der Debug-Modus unter `Settings → System` aktiviert ist.

## Leistungsstarkes 1-W-Modul (im Test)

Anfang 2025 hat @gromovyna seine Tests mit einem neuen, viel leistungsstärkeren Sub-GHz-Modul von quen0n (einem Mitglied des Unleashed-Teams) geteilt:

- Zum Zeitpunkt der Beiträge war es das einzige Exemplar überhaupt, mit einer Sendeleistung von **bis zu 1 W**.
- Es basiert auf einem anderen Chip als dem CC1101 — auf diesem Chip hatte vorher noch niemand etwas gebaut.
- Die Firmware-Unterstützung war **noch nicht fertig**; sie wurde für Unleashed gemeinsam mit Flipper Market entwickelt, und gromovyna war als Tester dabei.

![Das leistungsstarke Modul neben einer CC1101-Platine](/img/remote/29279ff04df77e30.jpg)

Seine empirischen Ergebnisse (ohne Leistungsmessungen):

- Das Modul ist weit leistungsstärker als alles, was er auf CC1101-Basis gesehen hat.
- In der Stadt, aus einer Wohnung heraus und mit einem anderen Gebäude im Weg, hat er ein **Hollarm**-Signal
  **600 m** horizontal gesendet.
- Dieselbe Entfernung erreichte er sowohl mit der beiliegenden Antenne als auch mit einer Funkgerätantenne, die MMX und quen0n empfohlen hatten — mit der Funkgerätantenne ist der Aufbau allerdings „absolut nicht tragbar".
- Ob das Modul beim *Empfangen* gegenüber dem CC1101 Vorteile bringt, war noch nicht klar.

![Das Modul mit einer Funkgerätantenne](/img/remote/0998ad639bb38e82.jpg)

Das beschreibt ein Gerät im Teststadium; prüfe in den aktuellen Unleashed-Release-Notes, wie es um die Unterstützung steht.

::: warning
Sende nur auf Frequenzen und mit Leistungen, die bei dir legal sind, und nur an deine eigene Technik.
:::

## Fehlersuche

- **`External` lässt sich nicht auswählen** — das Modul wird nicht erkannt: prüfe 3,3 V, GND und die vier SPI-Leitungen (CSN, SCK, MOSI, MISO). Eine falsch angeschlossene CSN- oder MISO-Leitung ist der häufigste Fehler.
- **Schaltet von selbst auf `Internal` zurück** — die Prüfung ist beim Auswählen des Moduls gescheitert; stecke das Modul neu und versuche es erneut.
- **Empfängt, aber die Reichweite beim Senden ist schlecht** — bei E07-Modulen braucht der Verstärker Pin 7 (PC3) angeschlossen und `Ext Amp & LEDs` auf ON.
- **Der Frequency Analyzer zeigt Zufallstreffer** — das externe Modul ist viel empfindlicher für Rauschen; nimm für die Frequenzanalyse das interne Funkmodul.
- **Senden wird blockiert** — die Frequenz liegt außerhalb des CC1101-Bereichs; siehe [Frequenzen](/de/subghz/frequencies).

## Verwandte Seiten

- [Sub-GHz-Einstellungen](/de/subghz/settings)
- [Frequenzen](/de/subghz/frequencies)
- [GPIO-Pinbelegung](/de/gpio/pinout) · [Externe Module](/de/gpio/external-modules)
