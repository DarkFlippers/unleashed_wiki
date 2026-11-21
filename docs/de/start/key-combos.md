---
title: Tastenkombinationen
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Tastenkombinationen

Manchmal reagiert der Flipper wegen eines Software-Problems nicht mehr. Diese Tastenkombinationen setzen ihn auf
Hardware-Ebene zurück oder starten ihn im DFU-Modus (Firmware-Update) — ohne Mithilfe der hängenden Firmware.

## Kurzübersicht

| Ziel | Kombination | USB |
|---|---|---|
| Hängenden Flipper neu starten | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | beliebig |
| Power-Reset | <kbd>BACK</kbd>, 30 s | **abgezogen** |
| DFU über den Flipper-Bootloader (mit Anzeige) | <kbd>←</kbd> + <kbd>BACK</kbd>, <kbd>BACK</kbd> loslassen, <kbd>←</kbd> halten, bis die LED blau leuchtet | beliebig |
| DFU über den ST-Bootloader (ohne Anzeige) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, <kbd>BACK</kbd> und <kbd>←</kbd> loslassen | beliebig |
| Bildschirm zum Zurücksetzen von PIN / Einstellungen | <kbd>↑</kbd> halten, während der Flipper startet | — |

## Grundkombinationen

### Hardware-Reset

1. Halte <kbd>←</kbd> und <kbd>BACK</kbd> ein paar Sekunden gedrückt.
2. Lass beide los.

Das zieht die Reset-Leitung des MCU nach unten. Weg: Tasten → DD8 (NC7SZ32M5X, OR-Gatter) → DD1 (STM32WB55, MCU).

**Funktioniert nicht, wenn:** der Debug-Block des MCU aktiv ist und die Reset-Leitung von innen hält.

### Hardware-Power-Reset

1. Zieh das USB-Kabel und jede externe Stromversorgung ab. Prüfe doppelt, dass USB wirklich abgezogen ist.
2. Halte <kbd>BACK</kbd> **30 Sekunden** gedrückt. Das funktioniert nur bei abgezogenem USB.
3. Lass <kbd>BACK</kbd> los.

Das schaltet die SYS-Versorgungsleitung über den Lade-IC DD6 (bq25896) aus und wieder ein.

**Funktioniert nicht, wenn:** Spannung an USB oder 5V_ext anliegt.

### Software-DFU

Halte <kbd>←</kbd> gedrückt, während der Flipper startet. Er geht über den **Flipper-Bootloader** in den DFU-Modus.

**Funktioniert nicht, wenn:** der Flipper-Bootloader beschädigt ist oder fehlt.

### Hardware-DFU

Halte <kbd>OK</kbd> gedrückt, während der Flipper startet. Er geht über den **ST-Bootloader** im MCU in den DFU-Modus.

**Funktioniert nicht, wenn:** die Option Bytes beschädigt sind oder so gesetzt sind, dass die Taste <kbd>OK</kbd>
ignoriert wird.

## DFU-Kombinationen

### Hardware-Reset + Software-DFU

1. Halte <kbd>←</kbd> + <kbd>BACK</kbd> ein paar Sekunden gedrückt.
2. Lass <kbd>BACK</kbd> los.
3. Das Gerät geht **mit Anzeige** in den DFU-Modus: blaue LED und DFU-Bildschirm.
4. Lass <kbd>←</kbd> los.

**Funktioniert nicht, wenn:** der Debug-Block des MCU die Reset-Leitung hält oder der Flipper-Bootloader beschädigt ist
oder fehlt.

### Hardware-Reset + Hardware-DFU

1. Halte <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> ein paar Sekunden gedrückt.
2. Lass <kbd>BACK</kbd> und <kbd>←</kbd> los.
3. Das Gerät geht **ohne Anzeige** in den DFU-Modus. Der Bildschirm bleibt leer. Das ist normal.

**Funktioniert nicht, wenn:** der Debug-Block des MCU die Reset-Leitung hält oder die Option Bytes beschädigt sind oder
so gesetzt sind, dass <kbd>OK</kbd> ignoriert wird.

### Hardware-Power-Reset + Software-DFU

1. Zieh USB und jede externe Stromversorgung ab.
2. Halte <kbd>BACK</kbd> + <kbd>←</kbd> 30 Sekunden gedrückt.
3. Lass <kbd>BACK</kbd> los.
4. Das Gerät geht mit Anzeige in den DFU-Modus (blaue LED + DFU-Bildschirm).
5. Lass <kbd>←</kbd> los.
6. Steck USB an.

**Funktioniert nicht, wenn:** Spannung an USB oder 5V_ext anliegt oder der Flipper-Bootloader beschädigt ist oder fehlt.

### Hardware-Power-Reset + Hardware-DFU

1. Zieh USB und jede externe Stromversorgung ab.
2. Halte <kbd>BACK</kbd> + <kbd>OK</kbd> 30 Sekunden gedrückt.
3. Lass <kbd>BACK</kbd> und <kbd>OK</kbd> los.
4. Das Gerät geht ohne Anzeige in den DFU-Modus.
5. Steck USB an.

**Funktioniert nicht, wenn:** Spannung an USB oder 5V_ext anliegt oder die Option Bytes beschädigt sind oder so gesetzt
sind, dass <kbd>OK</kbd> ignoriert wird.

## Was im DFU-Modus zu tun ist

Verbinde den Flipper mit einem Computer. Er erscheint als **DFU in FS Mode** (Windows/macOS) bzw. als
**STMicroelectronics STM Device in DFU Mode** (`lsusb` unter Linux). Reparier die Firmware dann mit qFlipper:
[Wiederherstellung](/de/start/recovery#firmware-recovery).

## Wenn nichts hilft {#if-nothing-helps}

- Stell sicher, dass der Akku geladen ist: häng das Gerät eine Stunde ans Ladegerät.
- Trenn den Akku ab und schließ ihn wieder an (dazu muss das Gehäuse geöffnet werden).
- Flash das Gerät mit einem ST-Link oder einem anderen SWD-Programmer.

Wenn das Gerät auch danach nicht funktioniert, liegt das Problem **nicht an der Software**.
