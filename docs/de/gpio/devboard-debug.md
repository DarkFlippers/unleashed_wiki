---
title: "Devboard: Debugging und Logs"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: Debugging und Logs

Ist das [Devboard eingerichtet](/de/gpio/devboard), kannst du die Firmware aus VS Code debuggen und die Logs des
Flippers über UART mitlesen.

## Funktionsweise

Das Devboard ist die Debug-Probe zwischen dem Debugger auf deinem Computer (über USB oder Wi-Fi) und dem MCU des
Flippers. Mit dem Flipper spricht es über **Serial Wire Debug**:

- **Pin 10** — SWCLK (Serial Wire Clock);
- **Pin 12** — SWDIO (Serial Wire Debug Data I/O).

![Hardware des Devboards](/img/remote/06e0a9eb98e4130d.jpg)

## Debug-Modi

| Verbindung | Verfügbare Modi |
|---|---|
| Wi-Fi | nur Black Magic |
| USB | Black Magic (Standard) oder DAPLink |

Der Black-Magic-Modus unterstützt keine RTOS-Thread-Awareness; alles andere funktioniert.

### Den USB-Modus umschalten

Kurioserweise wird der USB-Modus über Wi-Fi umgeschaltet:

1. Öffne die Weboberfläche des Boards (<http://192.168.4.1> im Access-Point-Modus oder <http://blackmagic.local> im
   Client-Modus, siehe [Verbindung](/de/gpio/devboard)).
2. Setze im Reiter **WiFi** den **USB mode** auf **BlackMagicProbe** oder **DapLink**.
3. Klicke auf **SAVE**, dann auf **REBOOT**.
4. Wähle in VS Code den passenden Debugger (siehe unten).

## Die Firmware in VS Code debuggen

### Voraussetzungen

1. Installiere [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Klone und baue die Firmware. Für Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Dieselben Schritte funktionieren mit dem Stock-Repository `flipperdevices/flipperzero-firmware`.) Mehr zum Bauen:
   [Firmware bauen](/de/dev/build), [FBT](/de/dev/fbt).

### Eine Sitzung starten

1. Flashe die eben gebaute Firmware über das Devboard:

   ```bash
   ./fbt flash
   ```

2. Öffne den Firmware-Ordner in **VS Code** und installiere die empfohlenen Erweiterungen (per Benachrichtigung oder
   mit `@recommended` im Erweiterungen-Reiter).
3. Erzeuge die VS-Code-Konfiguration:

   ```bash
   ./fbt vscode_dist
   ```

4. Wähle unter **Run and Debug**:
   - **Attach FW (blackmagic)** — über Wi-Fi oder USB;
   - **Attach FW (DAP)** — nur USB, Board im DAPLink-Modus.

   Über USB muss der Debugger zum **USB mode** des Boards passen (prüfe ihn in der Weboberfläche).
5. Klicke auf ▷ **Start Debugging**. Die Firmware hält beim Start der Sitzung an; klicke in der Werkzeugleiste auf
   **Continue**, um sie laufen zu lassen.

![Debuggen in VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Siehe auch die [Anleitung zum Debuggen in VS Code](https://code.visualstudio.com/docs/editor/debugging) und
[Debugging](/de/dev/debugging).

## Logs lesen

Das Devboard liest die Log-Ausgabe des Flippers von seinem UART, unabhängig vom Betriebssystem des Flippers. So siehst
du Logs beim Booten, bei Updates und bei Abstürzen, die der CLI-Befehl `log` nicht zeigen kann. Logs sind **nur über
USB** verfügbar.

### Log-Level und Log-Gerät einstellen

1. Öffne `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: Lass `USART` (Pins 13/14) stehen, denn dort lauscht das Devboard. `LPUART` schickt die Logs an die
   Pins 15/16, `None` schaltet das Logging über UART ab.

::: tip
Wenn ein anderes Modul die Pins 13/14 braucht (Wi-Fi-Board, SIM800, GPS), setze `Log Device` auf `LPUART` oder `None`,
damit die Log-Ausgabe es nicht stört.
:::

### macOS

1. Installiere [Homebrew](https://brew.sh/), dann `brew install minicom`.
2. Flipper ausschalten, Devboard einstecken, einschalten.
3. Führe `ls /dev/cu.*` aus, verbinde das Devboard per USB und führe es erneut aus. Zwei neue Geräte erscheinen, z. B.
   `/dev/cu.usbmodemblackmagic1` und `/dev/cu.usbmodemblackmagic3`.
4. Öffne das mit der **höheren Nummer**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Die Logs laufen im Terminal durch. Beende über das minicom-Menü oder schließe das Fenster.

### Linux

1. Installiere minicom, z. B. mit `sudo apt install minicom`.
2. Flipper ausschalten, Devboard einstecken, einschalten.
3. Führe `ls /dev/tty*` aus, verbinde das Devboard per USB und führe es erneut aus. Zwei neue Geräte erscheinen, z. B.
   `/dev/ttyACM0` und `/dev/ttyACM1`.
4. Öffne das mit der höheren Nummer:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Erscheint nichts, probiere das andere Gerät.

### Windows

1. Installiere [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Flipper ausschalten, Devboard einstecken, einschalten, Devboard per USB verbinden.
3. Notiere im **Geräte-Manager → Anschlüsse (COM & LPT)** den neuen COM-Port.
4. Wähle in PuTTY **Serial**, trage den Port unter **Serial line** ein, setze **Speed** auf **230400** und klicke auf
   **Open**.

![PuTTY-Einstellungen](/img/remote/2bb43453a91a142e.jpg)

## Siehe auch

- [Devboard: erste Schritte](/de/gpio/devboard)
- [Devboard: Firmware-Update](/de/gpio/devboard-firmware)
- [CLI](/de/dev/cli)
