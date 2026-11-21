---
title: Hardware-Targets
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Hardware-Targets

Die Firmware ist modular: eine Codebasis unterstützt mehrere Hardwarekonfigurationen. Alles, was sich zwischen
Boards unterscheidet — die `furi_hal`-Implementierung, der Board-Init-Code, die Linker-Skripte, die
SDK-Symboltabellen — ist in einer **Target-Definition** zusammengefasst.

Das Unleashed-Repository liefert zwei Targets in `targets/` mit:

| Ordner | Hardware |
|---|---|
| `targets/f7` | Flipper Zero — der Standard (`TARGET_HW = 7`) |
| `targets/f18` | "Not Flipper Zero" — ein Board ohne die Funk-Frontends; erbt von f7 |

Gemeinsame Header liegen in `targets/furi_hal_include`.

## Wie ein Target aufgebaut ist

Jedes Target liegt in seinem eigenen Unterordner von `targets/`. Es muss eine `target.json` enthalten und darf
beliebige weitere Dateien enthalten, auf die diese Definition verweist. Standardmäßig kompiliert `fbt` **jede
Quelldatei** im Target-Ordner, sofern sie nicht ausdrücklich ausgeschlossen ist. Targets können von einem anderen
Target **erben**, um Code nicht doppelt zu pflegen.

## Felder von `target.json`

| Feld | Typ | Bedeutung |
|---|---|---|
| `include_paths` | Liste von Strings | Ordner (relativ zum Target), die dem globalen C/C++-Include-Pfad hinzugefügt werden |
| `sdk_header_paths` | Liste von Strings | Ordner, deren Header im SDK enthalten sind |
| `startup_script` | Dateiname | Startskript, das die anfängliche Hardwareinitialisierung durchführt |
| `linker_script_flash` | Dateiname | Linker-Skript für das Haupt-Firmware-Image |
| `linker_script_ram` | Dateiname | Linker-Skript für die "updater"-Konfiguration (läuft aus dem RAM) |
| `linker_script_app` | Dateiname | Linker-Skript für `.fap`-Dateien |
| `sdk_symbols` | Dateiname | `.csv` mit der aktuellen SDK-(API-)Definition für dieses Target |
| `linker_dependencies` | Liste | Bibliotheken, mit denen die Firmware gelinkt wird. Nicht aufgeführte Bibliotheken werden **nicht gebaut**. Mehrere Link-Durchläufe brauchen denselben Namen möglicherweise zweimal |
| `inherit` | String | Target, von dem die Basiskonfiguration übernommen wird. Listenwerte werden erweitert, andere Werte überschrieben |
| `excluded_sources` | Liste | Dateien aus geerbten Konfiguration(en), die **nicht** gebaut werden |
| `excluded_headers` | Liste | Header aus geerbten Konfiguration(en), die **nicht** in das SDK aufgenommen werden |
| `excluded_modules` | Liste | Namen von `fbt`-Bibliotheken (Modulen), die beim Konfigurieren des Builds ausgeschlossen werden |

## Beispiel: wie f18 von f7 erbt

`targets/f18/target.json` (gekürzt) zeigt Vererbung und Ausschlüsse in der Praxis — es übernimmt alles von f7 und
lässt die Treiber für Sub-GHz, NFC, RFID, iButton und Infrarot weg:

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## Apps und Hardware

Nicht jede App ist auf jedem Target verfügbar.

- **Eingebaute Apps:** wähle mit der Option `FIRMWARE_APP_SET=...` ein kompatibles App-Set
  (siehe [fbt → Firmware-App-Sets](/de/dev/fbt#firmware-app-sets)).
- **Externe Apps (FAPs):** führe die kompatiblen Targets in der `application.fam` der App auf. Um eine App zum
  Beispiel nur für f7 zu bauen, ergänze:

```python
    targets=["f7"],
```

Sie wird dann für andere Targets nicht gebaut. Siehe [App-Manifeste](/de/dev/app-manifests).

## Für ein bestimmtes Target bauen

Übergib `TARGET_HW` (und optional `FIRMWARE_APP_SET`) an `fbt`. Um zum Beispiel die Firmware für f18 zu bauen und
über USB zu flashen:

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Verwandte Seiten

- [Flipper Build Tool (fbt)](/de/dev/fbt)
- [App-Manifeste (.fam)](/de/dev/app-manifests)
- [FuriHalBus-API](/de/dev/furi-hal-bus)
