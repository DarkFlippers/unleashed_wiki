---
title: "Devboard: erste Schritte"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: erste Schritte

Das offizielle **Wi-Fi Developer Board** ist ein ESP32-S2-Modul (ESP32-S2-WROVER-N4R2) für die GPIO-Stiftleiste. Ab
Werk läuft darauf die Firmware **Black Magic Probe**, und es arbeitet als **Debug-Probe**: Es verbindet den Debugger
auf deinem Computer über SWD mit dem STM32 des Flippers, per USB oder Wi-Fi. Außerdem kann es die UART-Logs des
Flippers weiterleiten.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Zum Flashen von Firmware brauchst du es nicht
Aktualisieren, Bauen und Hochladen eigener Firmware funktioniert alles über einfaches USB. Das Devboard wird nur zum
Live-Debugging (GDB, Breakpoints) und zum Lesen von Logs unabhängig vom Betriebssystem des Flippers gebraucht. Wie du
dasselbe Board als Wi-Fi-Werkzeug (Marauder) nutzt, steht unter [ESP32 & Wi-Fi](/de/gpio/esp32).
:::

## Schritt 1. Debug-Modus auf dem Flipper aktivieren

1. Öffne `Main Menu → Settings → System`.
2. Setze `Debug` auf `ON`.

Der Debug-Modus ist zum Debuggen von Apps nötig und schaltet Debug-Optionen in Apps und in der [CLI](/de/dev/cli) frei.
Aktiviere ihn nach jedem Firmware-Update erneut.

## Schritt 2. Die Firmware des Boards aktualisieren

Das Board wird mit älterer Firmware ausgeliefert. Aktualisiere sie zuerst:
[Devboard: Firmware-Update](/de/gpio/devboard-firmware).

## Schritt 3. Das Devboard in den Flipper stecken

1. **Schalte den Flipper zuerst aus.** Board und microSD-Karte teilen sich die 3,3-V-Schiene des Flippers; wird eine
   große kapazitive Last im Betrieb eingesteckt, kann die Karte beschädigt werden.
2. **Steck es vollständig ein.** Ohne Hülle: kein Spalt zwischen Flipper und Board (kann etwas Kraft brauchen). In
   einer Silikonhülle: kein Spalt in der Mitte zwischen Hülle und Board.
3. Halte <kbd>BACK</kbd>, um den Flipper einzuschalten.

![Eingestecktes Devboard, Flipper ohne Hülle](/img/remote/4eb1e40120ff42bb.jpg)

## Schritt 4. Mit einem Computer verbinden

### Über USB

USB nutzt du zum Debuggen im **Black Magic**- oder **DAPLink**-Modus und zum Lesen von Logs.

1. Liste die seriellen Geräte auf dem Computer auf:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Geräte-Manager → **Anschlüsse (COM & LPT)**
2. Verbinde den USB-C-Port des **Devboards** mit dem Computer.
3. Liste die Geräte erneut auf: Es erscheinen **zwei neue Ports**, beide gehören zum Devboard.

Erscheint nichts, probiere ein anderes Kabel (es muss Daten übertragen), einen anderen USB-Port oder einen anderen
Computer.

### Über Wi-Fi: Access-Point-Modus (Standard)

Das Board eröffnet sein eigenes Netz. Dein Computer verliert seine normale Wi-Fi-Verbindung, solange er damit verbunden
ist.

1. Verbinde dich auf dem Computer oder Telefon mit dem Wi-Fi-Netz:
   - Name: `blackmagic`
   - Passwort: `iamwitcher`
2. Öffne <http://192.168.4.1> oder <http://blackmagic.local> für die Weboberfläche des Boards.

Wenn das Netz `blackmagic` nicht auftaucht:

- setze die Wi-Fi-Verbindung auf dem Computer zurück;
- das Board ist möglicherweise als Client (STA) konfiguriert. Halte den **BOOT**-Taster des Boards **10 Sekunden**
  lang, um seine Einstellungen zurückzusetzen; nach dem Neustart ist es wieder ein Access Point.

### Über Wi-Fi: Client-Modus (STA)

Das Board tritt deinem bestehenden 2,4-GHz-Netz bei, du behältst also den Internetzugang.

1. Verbinde dich mit dem Board im Access-Point-Modus (siehe oben) und öffne <http://192.168.4.1>.
2. Wähle den Modus **STA** und gib **SSID** und **Passwort** deines Netzes ein. Die Schaltfläche **+** listet
   2,4-GHz-Netze in der Nähe auf (5 GHz wird nicht unterstützt).
3. Speichern und das Board neu starten.
4. Ab jetzt öffnest du <http://blackmagic.local> über dein normales Netz.

Über Wi-Fi steht nur das Debuggen mit **Black Magic** zur Verfügung.

## Hardware

- MCU: ESP32-S2-WROVER-N4R2.
- SWD zum Flipper an **Pin 10 (SWCLK)** und **Pin 12 (SWDIO)**; UART-Logs an den USART-Pins 13/14 des Flippers.
- Schaltpläne (Platine, ESP32-S2, Stromversorgung, Steckverbinder) und die Bestückungszeichnung:
  [Schaltpläne des Wi-Fi Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Nächste Schritte

- [Devboard: Debugging und Logs](/de/gpio/devboard-debug)
- [Devboard: Firmware-Update](/de/gpio/devboard-firmware)
- Community: [Discord](https://discord.com/invite/flipper) (Kanal #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
