---
title: "Devboard: Firmware-Update"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: Firmware-Update

So aktualisierst (oder stellst du wieder her) die Firmware des Wi-Fi Developer Board selbst, mit **uFBT**. Das ist
nicht die Firmware des Flippers: dazu siehe [Aktualisieren](/de/start/updating).

## Schritt 1. uFBT installieren

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) baut und debuggt Apps, flasht Firmware, erzeugt
VS-Code-Konfigurationen und flasht das Wi-Fi Devboard.

**Linux & macOS**

1. Installiere `pipx` ([Anleitung](https://pipx.pypa.io/stable/installation/)) und starte das Terminal neu.
2. Installiere uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Installiere das aktuelle [Python](https://www.python.org/downloads/windows/).
2. In PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Starte PowerShell neu, dann:

   ```powershell
   pipx install ufbt
   ```

## Schritt 2. Das Board in den Bootloader-Modus versetzen

1. Liste die seriellen Geräte auf: macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows Geräte-Manager →
   **Anschlüsse (COM & LPT)**.
2. Verbinde das Devboard per USB-C-Kabel mit dem Computer.
3. Geh in den Bootloader-Modus:
   1. **BOOT** drücken und halten;
   2. **RESET** drücken und loslassen, während **BOOT** gehalten wird;
   3. **BOOT** loslassen.
4. Liste die Geräte erneut auf und merke dir das neue.

![Bootloader-Taster des Devboards](/img/remote/060af5decf4b567c.jpg)

## Schritt 3. Flashen

Linux & macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Erfolgsmeldung: `WiFi board flashed successfully`.

### Wenn das Flashen fehlschlägt

Fehler wie

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

oder

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

lassen sich meist so beheben:

- Board abziehen und wieder anschließen, dann erneut in den Bootloader-Modus gehen;
- ein anderer USB-Port;
- ein anderes USB-C-Kabel.

## Schritt 4. Abschluss

1. Drücke **RESET** auf dem Board.
2. Zieh das USB-C-Kabel ab und steck es wieder ein.

Auf dem Board läuft jetzt die neueste offizielle Black-Magic-Firmware. So stellst du es auch wieder her, nachdem du
andere Firmware geflasht hast (z. B. [Marauder](/de/gpio/esp32)). Weiter geht es mit
[dem Einstecken in den Flipper](/de/gpio/devboard).
