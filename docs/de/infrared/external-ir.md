---
title: Externe IR-Module
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Externe IR-Module (GPIO)

Die drei eingebauten IR-LEDs reichen fürs Wohnzimmer, die Reichweite ist aber begrenzt. Für mehr Leistung kannst du
einen **externen IR-Sender** (eine Platine mit stärkeren LEDs und einem Treibertransistor) an die GPIO-Stiftleiste
anschließen. Die Infrared-App sendet dann darüber statt über die eingebauten LEDs. Universalfernbedienungen,
gespeicherte Fernbedienungen, die Mobile-App und die Taste „Send" auf dem Aufnahmebildschirm benutzen alle den
gewählten Ausgang.

::: tip Unleashed
Die Unterstützung für externe IR-Module mit automatischer Erkennung steht in der Funktionsliste von Unleashed; die
Erkennungslogik selbst stammt aus der offiziellen Firmware, das hier beschriebene Verhalten ist also auf beiden
gleich.
:::

## Verdrahtung

| Pin am Modul | GPIO-Pin des Flippers |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, versorgt, wenn „5V on GPIO" ON ist, oder 9 (3V3) für 3,3-V-Module |
| GND | 8, 11 oder 18 (GND) |

Pin 2 führt **dasselbe modulierte Signal** (inklusive Träger, typisch 38 kHz), das normalerweise die internen LEDs
ansteuert. Das Modul braucht daher nur eine Treiberstufe und LEDs, keinen eigenen Modulator. Die Belegung der
Stiftleiste zeigt [GPIO-Pinbelegung](/de/gpio/pinout).

::: warning
Das Anlernen (Empfangen) läuft immer über den eingebauten Empfänger. Das externe Modul kann nur senden.
:::

## GPIO Settings

Gehe zu `Main Menu → Infrared → GPIO Settings`. Es gibt zwei Optionen:

| Option | Werte | Bedeutung |
|---|---|---|
| **Signal Output** | `Flipper` | Eingebaute IR-LEDs (Standard). |
| | `2 (A7)` | Immer über GPIO-Pin 2 senden. |
| | `Detect` | Bei jedem Start der Infrared-App ein externes Modul an Pin 2 automatisch erkennen. |
| **5V on GPIO** | `OFF` / `ON` | Schaltet 5 V auf GPIO-Pin 1, um das Modul zu versorgen. Mit `Detect` zeigt es **`Auto`** und wird automatisch gesteuert. |

Die Einstellungen werden beim Verlassen des Bildschirms in `/ext/infrared/.infrared.settings` gespeichert und bei
jedem Start der Infrared-App angewandt. Verlässt du die Infrared-App, geht der Ausgang auf die eingebauten LEDs
zurück und 5 V wird wieder abgeschaltet, damit das Modul in anderen Apps nicht am Akku zieht.

### Schritt für Schritt

1. Schließe das Modul an (Signal → Pin 2, VCC → Pin 1, GND → Pin 8/11/18).
2. Öffne `Infrared → GPIO Settings`.
3. Stelle **Signal Output** auf `Detect` (oder auf `2 (A7)`, wenn die Erkennung mit deinem Modul nicht klappt).
4. Bei `2 (A7)` setze **5V on GPIO** auf `ON`, wenn das Modul aus Pin 1 versorgt wird.
5. Drücke <kbd>Back</kbd>. Sende eine beliebige gespeicherte Taste oder eine Universalfernbedienung; die LEDs des
   Moduls sollten jetzt senden.

## Wie die automatische Erkennung funktioniert

Ist `Detect` gewählt, aktiviert die Firmware an Pin 2 kurz einen **schwachen Pull-up** und liest den Pin zurück:

- bleibt der Pin **low**, hängt etwas mit einem Pull-down daran, es wird also ein externes Modul angenommen. Die
  Ausgabe geht auf Pin 2 und **5 V am GPIO wird automatisch eingeschaltet**;
- liest der Pin **high**, ist nichts angeschlossen und die eingebauten LEDs werden benutzt.

Das funktioniert am besten mit Modulen, deren LED-Treiber ein **MOSFET mit kräftigem Pull-down** am Gate oder ein
**BJT** zum Ansteuern der IR-LEDs ist. Das Modul **muss den Pin auf 0,9 V oder weniger ziehen**, damit es erkannt
wird. Hat dein Modul keinen Pull-down, wähle `2 (A7)` von Hand und schalte 5 V selbst ein.

Die Erkennung läuft beim Start der Infrared-App (und wenn du `Detect` auswählst). Steckst du das Modul an, während
die App offen ist, wähle `Detect` erneut aus oder starte die App neu.

## Fehlersuche

| Problem | Was du versuchen kannst |
|---|---|
| `Detect` nutzt immer die eingebauten LEDs | Das Modul zieht Pin 2 nicht tief genug (≤ 0,9 V). Nutze `2 (A7)` und schalte `5V on GPIO` von Hand auf ON. |
| Die LED des Moduls leuchtet nicht | Prüfe VCC: bei `2 (A7)` muss 5 V ON sein. Prüfe GND. Schau während des Sendens mit einer Handykamera auf die LEDs. |
| Der Akku ist schnell leer | Ein starkes Modul zieht viel aus den 5 V. Trenne es, wenn du es nicht brauchst. |

## Verwandte Seiten

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [GPIO-Module](/de/gpio/external-modules)
- [Signale anlernen und senden](/de/infrared/read)
- [Universalfernbedienungen](/de/infrared/universal-remotes)
