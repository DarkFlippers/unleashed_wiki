---
title: ESP32 & Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 & Wi-Fi

Der Flipper Zero hat kein eigenes Wi-Fi. Wi-Fi-Werkzeuge kommen von einem **ESP32**- (oder ESP8266-) Board an der
GPIO-Stiftleiste, das die Funkarbeit übernimmt und über den UART mit einer Flipper-App spricht. Diese Seite gibt einen
Überblick über die Möglichkeiten und die passenden Unleashed-Webwerkzeuge.

## Welches Board

| Board | Typischer Einsatz |
|---|---|
| **Offizielles Wi-Fi Developer Board** (ESP32-S2) | Wird mit der Debug-Probe-Firmware Black Magic ausgeliefert, zum [Debuggen](/de/gpio/devboard). Kann mit Marauder neu geflasht werden |
| **ESP32-Marauder-Boards** (verschiedene ESP32-, ESP32-S2- und ESP32-S3-Boards, Combo-Boards) | Wi-Fi- und BLE-Scans, Paketmitschnitte, Wardriving |
| **ESP8266-Boards** | Firmware Wi-Fi Scanner und Deauther |
| **ESP32-CAM** | Camera Suite (Kamerabild auf dem Flipper-Display) |

## Apps

Jede davon ist nur die Flipper-Seite: auf dem Board muss zuerst die passende Firmware liegen.

| App | Paket | Was sie macht |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Oberfläche für die Marauder-Firmware: WLAN- und BLE-Scan, Paketmitschnitt, Wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Listet WLANs in der Umgebung auf, für die Scanner-Firmware auf dem ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Oberfläche für die DSTIKE-Deauther-Firmware |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Live-Bild einer ESP32-CAM auf dem Flipper-Display, mit Fotoaufnahme |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Zweite ESP32-CAM-App: Live-Bild und Fotos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Oberfläche für die Ghost-ESP-Firmware |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Betreibt auf dem ESP32 einen Access Point mit Captive Portal |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Für die Deauther-v2-Firmware von @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flasht Firmware auf ein ESP-Board, direkt vom Flipper über UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Löst einen IFTTT-Webhook über einen ESP8266 aus |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | WLAN-Kartierung mit einem ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Zeigt Gesicht und Status eines Pwnagotchi auf dem Flipper, über UART |

Vollständige Liste der Modul-Apps: [Module und ihre Apps](/de/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) von justcallmekoko ist Firmware für ESP32-Boards. Auf
dem Flipper wird sie über die App **WiFi Marauder** aus den zusätzlichen App-Paketen genutzt, die Befehle an das Board
schickt und dessen Ausgabe anzeigt.

Typischer Ablauf:

1. **Marauder flashen** — auf das ESP32-Board (siehe Flasher unten).
2. Flipper ausschalten, Board in die GPIO-Stiftleiste stecken, einschalten.
3. Die Marauder-App unter `Apps → GPIO` öffnen und einen Befehl wählen (Access Points scannen, sniffen, wardriven usw.).
4. Ergebnisse zeigt die App an; Mitschnitte und Wardriving-Logs werden entsprechend den Board- und App-Einstellungen
   gespeichert (siehe die Marauder-Dokumentation zu deinem Board).

Eine vollständige Anleitung zum Wi-Fi Devboard mit Marauder (von UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Rechtliches
Scannen ist passiv, aber Deauthentication und andere aktive Wi-Fi-Angriffe sind illegal, wenn sie sich gegen Netze
richten, die dir nicht gehören oder für die du keine Testfreigabe hast.
:::

## ESP32 Web Flasher

::: tip Unleashed
Das Unleashed-Team betreibt einen browserbasierten Flasher für verbreitete ESP32-Module:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Er läuft vollständig im Browser, du musst
also kein esptool installieren. Verwende einen Browser mit Web-Serial-Unterstützung (Chromium-basierte Browser).
:::

Grundsätzliches Vorgehen:

1. Zieh das ESP32-Board vom Flipper ab und verbinde es per USB mit dem Computer.
2. Geht das Board nicht von selbst in den Flash-Modus, halte **BOOT**, tippe **RESET** an und lass **BOOT** los.
3. Öffne den Flasher, wähle Board und Firmware, klicke auf Verbinden und wähle den seriellen Port des Boards.
4. Warte, bis das Flashen abgeschlossen ist, setze das Board zurück und stecke es wieder in den Flipper (Flipper
   ausgeschaltet).

Weitere Wege, ein ESP-Board zu flashen:

- Die Flipper-App **ESP flasher** — flasht eine `.bin` von der SD-Karte des Flippers über den GPIO-UART:
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Windows-Anleitung für esptool / Flash Download Tool:
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- Die [USB-UART Bridge der GPIO-App](/de/gpio/gpio-app) mit `RTS/DTR Pins` kann als USB-Adapter für Boards ohne eigenen
  USB-Port dienen.

::: tip Zurück zur Debug-Firmware
Wenn du Marauder auf das offizielle Wi-Fi Devboard gelegt hast und den Black-Magic-Debugger zurückwillst, flashe es mit
`ufbt devboard_flash` neu, wie unter [Devboard: Firmware-Update](/de/gpio/devboard-firmware) beschrieben.
:::

## Wi-Fi Wardriving Map

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** fasst mehrere Wardriving-Mitschnitte im WiGLE-Format aus
ESP32 Marauder und anderen Werkzeugen zusammen und zeigt sie auf einer Karte.
:::

1. Fahre ein Wardrive mit Marauder (Wardriving braucht ein GPS-Modul am ESP32-Board).
2. Kopiere die CSV-Logs im WiGLE-Format auf deinen Computer.
3. Öffne die Karte und lade eine oder mehrere Dateien; die Netze werden gemeinsam eingezeichnet.

Für Sub-GHz-Mitschnitte und andere Dateien mit Koordinaten gibt es eine eigene Karte:
[map.unleashedflip.com](https://map.unleashedflip.com).

## Weitere ESP-Firmware

| Firmware | Board | Links |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Anleitung](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Anleitung](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Anleitung](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Die passenden Flipper-Apps stecken in den Paketen Base/Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Fehlerbehebung

- **Die App meldet keine Antwort vom Board:** Auf dem Board läuft nicht die Firmware, die die App erwartet, TX/RX
  liegen am falschen UART, oder das Board ist nicht vollständig eingesteckt.
- **Seltsames Verhalten am UART:** Eine andere Funktion lauscht auf denselben Pins. Prüfe
  `Settings → Expansion Modules → Listen UART` (siehe [Expansion-Module](/de/gpio/expansion-modules)) und
  `Settings → System → Log Device`.
- **Der Web-Flasher findet das Board nicht:** Verwende ein USB-Kabel mit Datenleitungen, gehe manuell in den
  Bootloader-Modus, probiere einen anderen USB-Port oder Browser.

## Siehe auch

- [Wi-Fi Devboard](/de/gpio/devboard)
- [Externe Module](/de/gpio/external-modules)
- [GPS](/de/gpio/gps)
