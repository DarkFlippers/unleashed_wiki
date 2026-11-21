---
title: Apps debuggen
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Apps debuggen

Echtzeit-Debugging (In-Circuit) erlaubt es dir, eine App zu starten, sie an jeder Stelle anzuhalten, Zeile für
Zeile durch den Code zu gehen und Variablen und den Aufrufstapel zu beobachten. Es findet weit mehr Fehler als
"eine Log-Zeile ergänzen und es nochmal versuchen".

::: info
In-Circuit-Debugging ist optional. Du kannst immer debuggen, indem du Apps über USB lädst und das
[Log](/de/dev/cli#reading-logs) liest.
:::

## Was du brauchst

- Einen Flipper Zero (das *Target*).
- Einen Windows-, Linux- oder macOS-Computer mit [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (für
  Apps) oder dem vollständigen Firmware-Baum mit [fbt](/de/dev/fbt).
- Eine unterstützte **SWD-Probe**.

### Unterstützte SWD-Probes

| Probe | Hinweise |
|---|---|
| Ein **zweiter Flipper Zero** | Starte darauf die [DAP-Link-App](https://lab.flipper.net/apps/dap_link), um ihn in eine SWD-Probe zu verwandeln |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Mit der Original-Firmware (Blackmagic); verbindet sich über USB oder Wi-Fi — siehe [Dev Board](/de/gpio/devboard) |
| CMSIS-DAP-Probes | z. B. [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Blackmagic-kompatible Probes](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), das [ST-Link-V3-Devboard](/de/dev/hardware#st-link-v3-developer-board) |
| J-Link | Flashen und Debuggen nur aus VS Code; die SEGGER-Werkzeuge musst du selbst installieren |

## Den Flipper vorbereiten

Aktiviere den Debug-Modus auf dem Target: `Main Menu → Settings → System → Debug` → **ON**.

## Schritt für Schritt (VS Code)

1. **Verbinde die Probe mit der GPIO-Stiftleiste des Flipper.** Für den Flipper gemachte Probes werden einfach
   aufgesteckt. Bei einer allgemeinen Probe verbinde drei Leitungen:

   | Signal | Pin des Flipper |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 oder 18 |

   Hat die Probe außerdem ein UART, verbinde es mit dem USART des Flipper (Pins **13** TX und **14** RX). Dieser
   Port gibt Logs und Absturzinformationen aus, was sehr hilfreich ist.
2. **Verbinde die Probe mit dem Computer** — üblicherweise über USB; das Wi-Fi Devboard funktioniert auch über
   Wi-Fi.
3. **Projekt vorbereiten:** führe einmal `ufbt vscode_dist` (App) oder `./fbt vscode_dist` (Firmware) aus und
   öffne den Ordner in VS Code.
4. **Wechsle in VS Code zu Run and Debug:** klicke auf das Debug-Symbol in der Seitenleiste oder drücke
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> unter macOS). Wähle
   die Konfiguration für deine Probe und drücke **Play**.

   ::: info
   Das Starten einer Debug-Sitzung **hält** die Firmware an. Klicke in der Debug-Werkzeugleiste auf **Continue**, um
   sie fortzusetzen.
   :::
5. **Nutze die Debug-Steuerelemente:** Reset, Pause, Continue, Step In, Step Out, Disconnect.
6. **Setze Breakpoints**, indem du links neben eine Zeilennummer klickst. Die Ausführung stoppt, wenn sie diese
   Zeile erreicht.
7. **Untersuche den Aufrufstapel** im Panel *Call Stack*, während die Ausführung angehalten ist.
8. **Untersuche Variablen** in den Panels *Variables*, *Watch* oder *Live Watch*.

Eine Videodemo von Flipper Devices:
[Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Debuggen über die Kommandozeile mit fbt

Mit dem vollständigen Firmware-Baum kannst du ohne VS Code debuggen:

| Befehl | Funktion |
|---|---|
| `./fbt debug` | Baut und flasht die Firmware, hängt dann GDB mit geladener Firmware-`.elf` an |
| `./fbt blackmagic` | Debuggt mit einer Blackmagic-Probe (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Hängt GDB an, ohne eine `.elf` zu laden; die `.elf` deiner App mit `add-symbol-file` ergänzen |
| `./fbt updater_debug` | Hängt GDB mit der Updater-`.elf` an |
| `./fbt openocd ARGS="..."` | Startet nur OpenOCD |
| `./fbt get_stlink` | Listet die ST-Link-Seriennummern auf, für `SWD_TRANSPORT_SERIAL=...` |

## Debug-Signale des Furi HAL

Manche Furi-Subsysteme können internen Zustand auf GPIO-Pins ausgeben, um ihn mit einem Logikanalysator oder
Oszilloskop zu verfolgen. Aktiviere sie, indem du beim Bauen ein Define ergänzt, zum Beispiel:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — Scheduler und Schlafmodus

Legt Tick, Tick-Unterdrückung, Leerlauf und Zeitfluss offen:

| Signal | Pin | Bedeutung |
|---|---|---|
| `AWAKE` | `PA7` | High, solange das System rechnet, low im Schlafmodus — verfolgt die Übergänge in den Schlafmodus |
| `TICK` | `PA6` | Wechselt bei jedem System-Tick (nur wenn keine Tick-Unterdrückung läuft) — zeigt Tick-Abweichungen und ungewöhnliches Scheduling |
| `SECOND` | `PA4` | Wechselt jede Sekunde — Störungen in seinem Timing bedeuten, dass das System die harte Echtzeit nicht einhält |

### `FURI_HAL_POWER_DEBUG` — Energiemodi

Verfolgt die Übergänge zwischen Energiemodi:

| Signal | Pin | Bedeutung |
|---|---|---|
| `WFI` | `PB2` | Leichter Schlaf (Wait For Interrupt). Der leichteste, nicht störende Energiesparmodus — alles einschließlich Debugging funktioniert |
| `STOP` | `PC3` | STOP-Modus, der Tiefschlaf der Plattform. Der größte Teil des Chips ist abgeschaltet oder unbenutzbar; den Mikrocontroller in diesem Modus zu debuggen ist nahezu unmöglich |

### `FURI_HAL_SD_SPI_DEBUG` — SD-Karte

Protokolliert den SPI-Busverkehr der SD-Karte.

## Fehlerbehebung

| Problem | Lösung |
|---|---|
| Die Probe verbindet sich, aber es passiert nichts | Die Firmware ist angehalten — drücke **Continue** |
| Breakpoints in deiner App werden ignoriert | Stelle sicher, dass die Symbole der `.elf` deiner App geladen sind (die VS-Code-Konfiguration aus `vscode_dist` erledigt das; bei `debug_other` nutze `add-symbol-file`) |
| Der Debugger verliert das Target | Der Mikrocontroller ist möglicherweise im STOP-Modus; siehe `FURI_HAL_POWER_DEBUG`. Der Debug-Modus auf dem Flipper muss **ON** sein |
| Variablen erscheinen als wegoptimiert | Baue mit `DEBUG=1` (Achtung: eine solche Firmware ist möglicherweise zu groß zum Verpacken — siehe [Bauen](/de/dev/build)) |

## Verwandte Seiten

- [Deine erste App in C](/de/dev/first-app-c)
- [Flipper Build Tool (fbt)](/de/dev/fbt)
- [Dev Board](/de/gpio/devboard)
- [Hardware](/de/dev/hardware) — Pinbelegungszeichnungen und Devboard-Schaltpläne
