---
title: Furi-API
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# Furi-API

Um die Hardware des Flipper zu nutzen — Display, Lautsprecher, Funk, USB, NFC — spricht deine App mit **Furi**, der
Sammlung von Bibliotheken, die zwischen der nackten Hardware und dem Anwendungscode sitzt. Diese Seite gibt einen
Überblick über die Hardware- und Softwarearchitektur und erklärt die Laufzeitprüfungen von Furi.

## Hardware

Das Herz des Flipper Zero ist ein Mikrocontroller (MCU) **STM32WB55**: zwei Kerne, RAM, Flash und Dutzende
Peripherieblöcke (Timer, RTC, BLE, GPIO, …). Ihre Funktionsweise ist im Reference Manual des Mikrocontrollers
beschrieben. Rund um die MCU sitzen mehrere externe Chips (CC1101, ST25R3916, Display-Controller usw.) mit ihren
eigenen Datenblättern.

![Hardwarestruktur des Flipper Zero](/img/dev/flipper_zero_hardware.png)

Farblegende:

- **Violett** — Blöcke innerhalb der MCU
- **Blau** — Chips außerhalb der MCU
- **Orange** — weitere Peripheriekomponenten, die keine komplexe Interaktion brauchen

Da die Firmware Open Source ist, *kannst* du direkt auf die Hardware zugreifen und eigene Low-Level-Treiber
schreiben — normalerweise ist das aber nicht nötig.

## Software: Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) ist die Abstraktionsschicht, die in der
Firmware enthalten ist. Sie bietet eine direkte API für die Hardware und für gängige Systemaufgaben: Threads,
dynamischen Speicher, Zugriffssteuerung auf Ressourcen (Records), Timer, Nachrichtenwarteschlangen, Logging und so
weiter.

Mit Furi musst du keine hunderte Seiten Datenblätter lesen oder Treiber schreiben — die Furi-API zu lernen genügt.
Außerdem verhindert sie, dass jeder Entwickler dieselben Dinge erneut implementiert.

![Hardware- und Softwarestruktur des Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi spannt sich über die gesamte Breite des Diagramms: es trennt den Code auf Anwendungsebene (Dienste und Apps)
von der darunterliegenden Hardware.

Furi besteht aus zwei Teilen:

| Teil | Wo | Was |
|---|---|---|
| Furi Core | `furi/` | Betriebssystem-Primitive: Threads, Mutexe, Nachrichtenwarteschlangen, Records, Timer, Event Loop, Logging, Prüfungen |
| Furi HAL | `targets/` (z. B. `targets/f7/furi_hal/`) | Hardwareabstraktion: GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, Energie, … — siehe [FuriHalBus](/de/dev/furi-hal-bus) |

Quellcode:

- Furi Core: [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (offiziell: [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL: [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (offiziell: [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Beispiele finden

Jede Flipper-App verwendet Furi, deshalb gibt es Beispiele für jeden Hardwareblock:

- Beispiel-Apps in [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …);
- eingebaute Apps in `applications/main/` und die zusätzlichen Unleashed-Apps in `applications/system/`;
- Community-Apps im [Apps Catalog](https://lab.flipper.net/apps) — der Link zum Quellcode steht unten auf jeder
  App-Seite. Wähle Apps, deren Funktionalität dem nahekommt, was du bauen willst.

Jede Furi-Funktion, jede Struktur und jeder Header steht in der offiziellen
[Doxygen-API-Referenz](https://developer.flipper.net/flipperzero/doxygen/) — nimm sie, wenn dieses Wiki den Aufruf
nicht beschreibt, den du brauchst.

## Laufzeitprüfungen und erzwungene Abstürze

Der beste Weg, die Systemintegrität zu schützen, besteht darin, weniger unmögliche Fälle zu behandeln und
**so früh wie möglich abzustürzen**, wenn etwas nicht stimmt. Die `check.h` von Furi Core stellt dafür
Hilfsfunktionen bereit.

Begriffe:

- **Crash** — das Ereignis protokollieren, Absturzinformationen im RTC speichern, neu starten.
- **Halt** — das Ereignis protokollieren, das System anhalten.

Hinweise:

- Debug- und Release-Builds verhalten sich unterschiedlich: ein **Debug-Build setzt das System nie zurück**, um den
  Zustand für den Debugger zu erhalten.
- Mit angeschlossenem Debugger stoppt die Ausführung automatisch vor dem Neustart.
- Alle Hilfsmakros akzeptieren ein optionales `MESSAGE_CSTR`. Es darf im RAM oder im Flash liegen, aber **nur im
  Flash gespeicherte Meldungen** werden nach dem Neustart angezeigt (verwende also String-Literale).
- `MESSAGE_CSTR` darf `NULL` sein, die Makros behandeln den Fall ohne Meldung aber schon selbst — lass es einfach
  weg.

| Makro | Verhalten | Wann zu verwenden |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Crash, wenn `CONDITION` falsch ist — **nur in Entwicklungs-Builds** | Prüfungen in der Entwicklungsphase in Apps und Diensten |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | **Immer** Crash, wenn `CONDITION` falsch ist | Bedingungen, die in jedem Build gelten müssen |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Crash ohne Bedingung | Es wurde ein anormaler Zustand erkannt |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Hält das System an | Intern verwendet, z. B. zum Anhalten, wenn ein Ausschalten nicht möglich ist |

::: warning Fallstricke bei furi_assert
- Release-Builds (`DEBUG=0`) enthalten niemals `furi_assert`-Prüfungen.
- Bibliotheken enthalten sie standardmäßig nicht; baue mit `LIB_DEBUG=1`, wenn du sie brauchst.
- Setze keine Funktionsaufrufe (Nebenwirkungen) in die `CONDITION` — der gesamte Ausdruck kann herauskompiliert
  werden.
:::

Beispiel:

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Verwandte Seiten

- [GUI in Apps](/de/dev/gui)
- [FuriHalBus-API](/de/dev/furi-hal-bus)
- [Apps debuggen](/de/dev/debugging) — enthält die Debug-Signale des Furi HAL
