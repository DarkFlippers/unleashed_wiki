---
title: "JavaScript: Übersicht"
sidebarTitle: "JS: Übersicht"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript auf dem Flipper Zero

Eine App für den Flipper Zero zu schreiben bedeutete früher C, eine komplette Toolchain und viel Lesen im Quellcode
anderer Apps. Die Firmware bringt inzwischen eine **eingebaute JavaScript-Engine** mit, du kannst also eine einfache
`.js`-Datei schreiben, auf die SD-Karte kopieren und direkt auf dem Gerät ausführen. Es muss nichts auf einem PC
kompiliert werden, und Skripte lassen sich leicht weitergeben.

- Skripte liegen in `/ext/apps/Scripts/` und werden über `Main Menu → Apps → Scripts` oder über die CLI mit
  `js <path>` gestartet.
- Die Engine basiert auf [mJS](https://github.com/cesanta/mjs), einem JavaScript-Interpreter für Mikrocontroller:
  er braucht weniger als 50 KB Flash und etwa 2 KB RAM. Flipper behält den mJS-Kern und ergänzt Extras wie kompakte
  Binärarrays (`ArrayBuffer`, typisierte Arrays).
- Skripte können über **Module**, die mit `require()` geladen werden, die GUI, die Tasten, USB HID (BadUSB), GPIO,
  UART, das Dateisystem und mehr nutzen.

::: warning mJS ist keine Browser-Engine
mJS unterstützt eine Teilmenge von JavaScript. Vor allem gibt es **keine Closures** (eine Funktion kann keine
Variablen aus dem umgebenden Scope nutzen; der Umweg dazu steht unter [Event loop](/de/dev/js-event-loop)), Strings
sind Einzelbyte-Strings ohne UTF-8-Unterstützung, und viele Objekte der Standardbibliothek fehlen. Die vollständige
Liste der Einschränkungen steht in der [mJS-README](https://github.com/cesanta/mjs).
:::

## Erste Schritte

1. [Deine erste JS-App](/de/dev/js-first-app): ein Skript schreiben, auf den Flipper kopieren, aus dem Menü oder
   über die CLI ausführen.
2. [JavaScript-SDK](/de/dev/js-sdk): TypeScript, Code-Vervollständigung und Upload mit einem Befehl per
   `npm start`.
3. [JS-Module verwenden](/de/dev/js-modules): wie `require()` funktioniert.

## Sprachreferenz

- [Datentypen](/de/dev/js-data-types)
- [Eingebaute Funktionen](/de/dev/js-builtin): `print`, `delay`, `require`, `load`, String-/Array-Methoden,
  SDK-Kompatibilitätsprüfungen.

## Modulreferenz

| Modul | Name für `require()` | Seite |
|---|---|---|
| Event loop | `event_loop` | [Event loop](/de/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/de/dev/js-gui), [GUI-Views](/de/dev/js-gui-views) |
| BadUSB (USB-HID-Tastatur) | `badusb` | [BadUSB](/de/dev/js-badusb) |
| Geräteinformationen | `flipper` | [Flipper](/de/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/de/dev/js-gpio) |
| Mathematik | `math` | [Math](/de/dev/js-math) |
| LED-/Vibro-/Ton-Benachrichtigungen | `notification` | [Notification](/de/dev/js-notification) |
| UART | `serial` | [Serial](/de/dev/js-serial) |
| Dateien und Ordner | `storage` | [Storage](/de/dev/js-storage) |

Beispielskripte für jedes Modul werden mit der Firmware in `/ext/apps/Scripts/js_examples/` installiert (zum
Beispiel `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Sie zu lesen ist der schnellste Weg, die API zu
lernen.

## Unleashed-Extras: Module ohne eigene Dokumentation {#unleashed-extras}

::: tip Unleashed
Unleashed meldet `flipper.firmwareVendor === "unleashed"` und bringt **zusätzliche JS-Module** mit, die die
Original-Firmware nicht hat. Sie sind in der offiziellen JS-Dokumentation nicht beschrieben; die Seiten unten
entstanden aus dem Firmware-Quellcode (`applications/system/js_app/modules/`) und den TypeScript-Typdefinitionen in
`packages/fz-sdk/`. Jedes Modul ist außerdem ein SDK-"Feature", prüfe es daher mit `doesSdkSupport([...])` oder
`checkSdkFeatures([...])` (siehe [Eingebaute Funktionen](/de/dev/js-builtin#sdk-compatibility)), damit dein Skript
auch auf anderen Firmwares funktioniert.
:::

Die vollständige Liste der von Unleashed gemeldeten Extra-Features lautet: `baseline`, `gpio-pwm`, `gui-widget`,
`serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Modul | Feature-Name | Funktion | Seite |
|---|---|---|---|
| `subghz` | `subghz` | Das Sub-GHz-Funkmodul steuern (internes oder externes CC1101): RX, RSSI, Frequenz, `.sub`-Dateien senden | [JS: subghz](/de/dev/js-subghz) |
| `infrared` | `infrared-send` | IR-Signale per Protokoll oder als rohe Timings senden | [JS: infrared](/de/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Eigene BLE-Advertisement-Pakete senden (zusätzliches Beacon) | [JS: blebeacon](/de/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Ein USB-Massenspeichergerät aus einem Disk-Image emulieren | [JS: usbdisk](/de/dev/js-usbdisk) |
| `i2c` | `i2c` | Mit I2C-Geräten an der GPIO-Stiftleiste kommunizieren | [JS: i2c](/de/dev/js-i2c) |
| `spi` | `spi` | Mit SPI-Geräten am externen SPI-Bus kommunizieren | [JS: spi](/de/dev/js-spi) |
| `vgm` | `vgm` | Die IMU (pitch/roll/yaw) des Video Game Module auslesen | [JS: vgm](/de/dev/js-vgm) |

Das GUI-Modul hat außerdem Views, die in der offiziellen Dokumentation fehlen: `button_menu`, `button_panel`,
`menu`, `number_input`, `popup`, `vi_list`. Sie sind unter [GUI-Views](/de/dev/js-gui-views) beschrieben.

Firmware-APIs, die dieses Wiki nicht abdeckt, stehen in der offiziellen
[Doxygen-API-Referenz](https://developer.flipper.net/flipperzero/doxygen/).

## Verwandte Themen

- [Apps in C schreiben](/de/dev/first-app-c), wenn JS nicht schnell oder flexibel genug ist.
- [BadUSB-Skriptformat](/de/badusb/script-format), die klassische DuckyScript-Alternative zum JS-Modul `badusb`.
