---
title: GPIO-App
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# GPIO-App

Die eingebaute App **GPIO** (`Main Menu → GPIO`) hat drei Einträge:

| Eintrag | Funktion |
|---|---|
| `USB-UART Bridge` | Macht den Flipper zum USB-Seriell-Adapter an den Pins 13/14 oder 15/16 |
| `GPIO Manual Control` | Zieht die Benutzer-Pins auf High, solange du <kbd>OK</kbd> hältst |
| `5V on GPIO` | `OFF` / `ON`: der 5-V-Ausgang an Pin 1 |

![Menü der GPIO-App: USB-UART Bridge, GPIO Manual Control, 5V on GPIO auf OFF](/screens/gpio/menu.png)

Pin-Nummern und Spannungen stehen auf der Seite [Pinbelegung](/de/gpio/pinout).

## USB-UART Bridge

Damit sprichst du vom Computer aus mit einer Router-Konsole, einem ESP32-/ESP8266-Board, einem GSM- oder GPS-Modul oder
jedem anderen seriellen 3,3-V-Gerät — der Flipper ist dabei der Adapter.

1. Verdrahte das Gerät: **Flipper TX → RX des Geräts**, **Flipper RX → TX des Geräts**, dazu eine gemeinsame Masse
   (Pin 8, 11 oder 18). Standardmäßig liegt TX auf Pin 13 und RX auf Pin 14.
2. Verbinde den Flipper per USB mit dem Computer.
3. Öffne `Main Menu → GPIO → USB-UART Bridge`. Das Display zeigt `USB Serial`, die Nummer von `COM PORT`, die
   TX-/RX-Pins, Byte-Zähler und die aktuelle Baudrate.
4. Drücke <kbd>←</kbd> (`Config`) zum Einrichten (Tabelle unten), dann <kbd>BACK</kbd>, um zur Statusanzeige
   zurückzukehren.
5. Öffne den Port in einem Terminalprogramm (PuTTY, minicom, screen, der serielle Monitor der Arduino-IDE …).
6. Zum Beenden drücke <kbd>BACK</kbd> und bestätige `Exit USB-UART?` mit `Exit` (oder wähle `Stay`).

![Statusanzeige der USB-UART Bridge: USB Serial, COM PORT 0, TX Pin 13, RX Pin 14, Byte-Zähler, Baud 115200](/screens/gpio/usb_uart.png)

Während Daten fließen, blinkt die LED **blau bei TX** und **grün bei RX**, und die Beleuchtung bleibt an.

### Config-Bildschirm

![USB-UART Bridge Config: USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Einstellung | Werte | Bedeutung |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)`: Die Bridge übernimmt den seriellen Haupt-USB-Port, die CLI ist während des Betriebs deaktiviert. `1`: Der Flipper stellt zwei serielle Ports bereit; die CLI bleibt auf dem ersten, die Bridge nutzt den zweiten |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` übernimmt die Baudrate, die das Terminalprogramm am Port einstellt. Eine Zahl erzwingt eine feste Rate (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART an Pin 13 (TX) / 14 (RX) oder LPUART an Pin 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Gibt die RTS- und DTR-Leitungen des Hosts aus (erster Pin RTS, zweiter DTR, Low-aktiv). `16,15` wird nicht angeboten, wenn `UART Pins` auf `15,16` steht |
| `DE/RE Pin` | `None`, `4` | Schaltet Pin 4 als Richtungssignal (Driver Enable) für einen RS-485-Transceiver |

::: tip ESP-Boards flashen
Die RTS-/DTR-Ausgabe ist genau das, was die Auto-Reset-/Boot-Schaltungen auf ESP8266-, ESP32- und Arduino-Boards
erwarten. Verbinde die beiden Pins mit der EN/RST- und BOOT/GPIO0-Logik des Boards (über das üblicherweise verwendete
Transistorpaar), dann kann esptool es ohne Tastendruck in den Bootloader versetzen.
:::

### Wenn „Connection Is Active!“ erscheint

Die Bridge kann nicht starten, solange qFlipper, die mobile App oder eine andere RPC-Sitzung die USB-Verbindung belegt.
Auf dem Display steht `Connection Is Active! Disconnect from PC or phone to use this function.` Schließe qFlipper bzw.
trenne die App und versuche es erneut.

## GPIO Manual Control

Ein schneller Weg, eine Verdrahtung oder eine LED bzw. ein Relais an einem Pin zu prüfen.

1. Öffne `Main Menu → GPIO → GPIO Manual Control`. Das Display zeigt `GPIO Output Mode Test`.
2. Wähle den Pin mit <kbd>←</kbd> / <kbd>→</kbd>: `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6), `PC3` (7),
   `PC1` (15), `PC0` (16) oder `ALL`.
3. **Halte** <kbd>OK</kbd>: Der Pin (oder alle) geht auf High, 3,3 V, und die grüne LED leuchtet. Beim Loslassen geht
   der Pin wieder auf Low.

Alle aufgeführten Pins sind Push-Pull-Ausgänge, solange dieser Bildschirm offen ist; beim Verlassen gehen sie zurück in
den hochohmigen (analogen) Modus. Schließe während des Tests nichts an, was diese Pins selbst treibt.

## 5V on GPIO

Schaltet den 5-V-Ausgang an Pin 1. Wähle den Eintrag und ändere ihn mit <kbd>←</kbd> / <kbd>→</kbd>. Die Einstellung ist
kein Modus der App: 5 V bleibt nach dem Verlassen der GPIO-App an, bis du es abschaltest, den Flipper ausschaltest oder
ein Überlastfehler auftritt. Die Strombegrenzungen stehen unter [Pinbelegung](/de/gpio/pinout).

## CLI-Werkzeuge

In der [CLI](/de/dev/cli) des Flippers gibt es zwei passende Befehle:

```text
gpio mode <pin_name> <0|1>   # 0 - input, 1 - output
gpio set <pin_name> <0|1>    # set output low/high
gpio read <pin_name>         # read input level
power 5v <0|1>               # 5 V on pin 1 off/on
i2c                          # scan the external I2C bus
```

- Pin-Namen sind die Portnamen (`PA7`, `PC0`, …). Debug-Pins (`PA13`, `PA14`, `PB6`, `PB7`, `PB14`) werden nur bei
  aktiviertem Debug-Modus akzeptiert, und die CLI fragt vorher `Changing this pin mode may damage hardware...`.
- `i2c` scannt Adressen an **PC0 (SCL, Pin 16) / PC1 (SDA, Pin 15)** mit 100 kHz und 7-Bit-Adressierung und gibt eine
  Tabelle aus, in der `#` ein Gerät markiert, das geantwortet hat. Die meisten I2C-Breakout-Boards haben bereits
  Pull-ups; wenn nichts erscheint, prüfe, ob deines welche hat.

::: tip Unleashed
Für mehr I2C-Arbeit (Sniffer, Register lesen und schreiben) und Sensoren siehe die Plugins `i2c Tools` und `Unitemp` in
den zusätzlichen App-Paketen, aufgeführt unter [Externe Module](/de/gpio/external-modules).
:::

## Fehlerbehebung

- **Wirre Zeichen im Terminal:** Die Baudrate passt nicht. Setze `Baudrate` auf die Rate des Geräts, oder belasse es
  bei `Host` und stelle die Rate im Terminalprogramm ein.
- **Überhaupt keine Daten:** Tausche TX und RX, prüfe die gemeinsame Masse und ob `UART Pins` zu deiner Verdrahtung
  passt.
- **CLI verschwunden:** `USB Channel` steht auf `0 (CLI)`. Verlasse die Bridge oder nutze Kanal `1`.
- **5V on GPIO bleibt nicht an:** Die Last zieht zu viel (Abschaltung wegen Fehler), oder ein großer Kondensator auf
  dem Modul bringt den Aufwärtswandler beim Start zum Auslösen. Schalte den Flipper aus, schließe das Modul an und
  schalte dann ein.

## Siehe auch

- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Externe Module](/de/gpio/external-modules)
- [Devboard: Debugging und Logs](/de/gpio/devboard-debug)
