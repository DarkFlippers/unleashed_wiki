---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 GHz)

Der **nRF24L01(+)** von Nordic Semiconductor ist ein günstiger 2,4-GHz-Transceiver, der in vielen Funkmäusen,
Funktastaturen und Hobbyprojekten steckt. Er wird über SPI mit dem Flipper verbunden.

## Apps

Im Base-Paket stecken der Sniffer und der Mouse Jacker, die die Anleitung unten benutzt. Das Extra-Paket bringt sechs weitere:

| App | Paket | Was sie macht |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Sammelt Adressen von Funktastaturen für den Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Schiebt Tastendrücke in einen angreifbaren Funktastatur- oder Maus-Empfänger |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Allgemeines Werkzeug für den nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Sucht und dekodiert nRF24-Pakete |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Zeigt, welche 2,4-GHz-Kanäle belegt sind |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Liest und schreibt benannte Felder eines nRF24-Geräts nach einer Konfigurationsdatei |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Andere Variante des Sniffers oben |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Andere Variante des Mouse Jackers oben |

Treiber, Sniffer und Mouse Jacker von [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Alle diese Apps liegen in den
[App-Paketen](https://github.com/xMasterX/all-the-plugins/releases/latest) — siehe [Module und ihre Apps](/de/gpio/module-apps).

::: warning Rechtliches
Nur zu Bildungszwecken und an eigener Ausrüstung. Tastenanschläge in den Computer einer anderen Person einzuspeisen ist
illegal.
:::

## Verdrahtung

| Flipper-Pin | nRF24L01-Pin |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — unverbunden lassen |

![Verdrahtung des nRF24L01 mit dem Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Pinbelegung von UberGuidoZ.*

Der nRF24 nutzt dieselben SPI-Pins (2–5) wie ein [externes CC1101](/de/subghz/external-cc1101). Schließe immer nur
eines von beiden an, es sei denn, du verwendest ein Combo-Board, das für beide ausgelegt ist (dann richte dich nach
seiner Dokumentation).

## Verwendung

1. Flipper ausschalten, Modul anschließen, einschalten.
2. Öffne **NRF24: Sniffer** (`Apps → GPIO`). Starte den Scan; mit den Tasten wechselst du Modi und Kanäle, wie auf dem
   Display angezeigt.
3. Warte, bis der Sniffer eine **Adresse** findet.
4. Öffne **NRF24: Mouse Jacker**.
5. Wähle die Adresse und öffne dann das zu sendende Bad-USB-Skript.
6. Die Tastenanschläge werden an den Ziel-Dongle übertragen.

Demo-Video: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). Die Skriptsyntax ist dieselbe wie bei
[Bad USB](/de/badusb/script-format).

## Wenn das Modul zickt

Der nRF24 zieht Strom in kurzen Spitzen. Wenn er nur manchmal funktioniert, setze einen Kondensator direkt am Modul
zwischen **VCC und GND**:

- 3,3 µF bis 10 µF Elektrolyt (Polarität beachten: Minus an GND). Ein einzelner 10 µF reicht meist.
- Optional ein 0,1-µF-Keramikkondensator parallel dazu: Der große Kondensator deckt langsame Änderungen ab, der kleine
  schnelle Schaltspitzen.

Die „Plus“-Varianten (nRF24L01+PA+LNA) mit Verstärker brauchen das noch dringender.

![Kondensator am nRF24-Modul](/img/remote/218b238eb91c9e38.jpg)

## Credits

- Sniffing-Technik: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- MouseJack-Schwachstellen: Marc Newlin, [Bastille Research](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Der Treiber ist von [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html) inspiriert, der
  MouseJack-Code von [JackIt](https://github.com/insecurityofthings/jackit).

## Siehe auch

- [Externe Module](/de/gpio/external-modules)
- [Bad USB](/de/badusb/usage)
- [GPIO-Pinbelegung](/de/gpio/pinout)
