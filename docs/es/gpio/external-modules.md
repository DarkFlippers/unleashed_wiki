---
title: Módulos externos
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Módulos externos

La mayoría de las placas accesorias del Flipper Zero se conectan directamente al conector GPIO y se comunican con
él a través de uno de tres buses: **SPI** (pines 2–5), **UART** (pines 13/14 o 15/16) o **I2C** (pines 15/16). Esta
página es un mapa: qué tipos de módulo existen, qué firmware o aplicación los controla y qué pines ocupan, para que
sepas cuáles se pueden usar juntos.

## Tipos de módulo

| Módulo | Bus / pines | Lo controla | Página |
|---|---|---|---|
| CC1101 externo (Sub-GHz) | SPI 2–5, GDO0 en el 6, control del amplificador en el 7 | Aplicación Sub-GHz integrada (`Radio Settings → Module → External`) | [CC1101 externo](/es/subghz/external-cc1101) |
| NRF24L01 (2,4 GHz) | SPI 2–5, CE en el 6 | Plugins NRF24 Sniffer / Mouse Jacker | [NRF24](/es/gpio/nrf24) |
| Placas Wi-Fi ESP32 / ESP8266, Wi-Fi Devboard | UART 13/14 (SWD 10/12 para depurar) | Plugins Marauder, Wi-Fi Scanner, Deauther; firmware Black Magic | [ESP32](/es/gpio/esp32), [Devboard](/es/gpio/devboard) |
| GSM SIM800C / SIM800L | UART 13/14 o 15/16, alimentación del pin 1 | Aplicación SIM800 integrada | [SIM800](/es/gpio/sim800) |
| GPS (NMEA) | UART | Plugin `[NMEA] GPS` | [GPS](/es/gpio/gps) |
| Video Game Module | UART 13/14, pines 2–7, alimentación | Firmware del Flipper + firmware del módulo | [Video Game Module](/es/gpio/video-game-module) |
| Módulos de expansión (protocolo) | UART 13/14 o 15/16 | `Settings → Expansion Modules` | [Módulos de expansión](/es/gpio/expansion-modules) |
| LED IR externo / amplificador IR | Pin 2 (PA7), 5 V en el pin 1 | Aplicación Infrared integrada (`GPIO Settings`) | véase más abajo |
| Sensores de temperatura / humedad / presión | depende del sensor (véase su README) | Plugin `Unitemp` | [README de Unitemp](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Cualquier dispositivo I2C | I2C 15/16 | Plugin `i2c Tools`, comando `i2c` de la CLI | [Aplicación GPIO](/es/gpio/gpio-app) |
| ESP32-CAM | UART | Plugin Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Cajas fuertes Sentry Safe / Master Lock (dos hilos) | Pin 15 (C1) + GND 8 | Plugin SentrySafe | [SentrySafe](/es/apps/sentry-safe) |

::: tip Unleashed
Unleashed añade soporte directamente en el firmware para:
- **CC1101 externo** por SPI por hardware, con control de amplificador y LED externos (`Ext Amp & LEDs`, activado
  por defecto) en `Sub-GHz → Radio Settings`.
- **Módulos IR externos** en `Infrared → GPIO Settings` (con detección automática, igual que en el firmware de
  serie).
- La aplicación GSM **SIM800** (`Apps → GPIO → SIM800`).

Los módulos de radio externos funcionan en cualquier firmware, no solo en Unleashed. La primera implementación del
CC1101 la escribió @quen0n para Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); la que se usa hoy la escribió **Skorp** en el firmware
oficial, y es la que usa Unleashed.

Los plugins para el resto (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) están en los paquetes Base y
Extra: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Véase
[Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps).
:::

## Conflictos de pines

Los módulos que comparten un bus no pueden funcionar al mismo tiempo sin tomar precauciones. Los choques
habituales:

| Pines | Ocupados por |
|---|---|
| 2, 3, 4, 5 | SPI: CC1101 externo, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | GDO0 del CC1101 / CE del NRF24 |
| 7 | Control del amplificador del CC1101 (módulos E07) |
| 13, 14 | USART: placas Wi-Fi, SIM800, módulos de expansión, Video Game Module, puente USB-UART, salida de registros |
| 15, 16 | LPUART o I2C (no los dos a la vez) |
| 10, 12 | Depuración SWD (Devboard) |

Si usas una placa «combo» que lleva varias radios (por ejemplo, CC1101 + NRF24 + ESP32 en un mismo PCB), sigue la
documentación de esa placa para saber qué pines y qué ajustes de plugin usa cada radio.

## Módulos IR externos

1. Conecta la entrada del driver del LED IR al **pin 2 (A7)**, GND a GND y la alimentación al pin 1 (5 V) si el
   módulo la necesita.
2. Abre `Main Menu → Infrared → GPIO Settings`.
3. Pon `Signal Output` en:
   - `Flipper`: el LED IR integrado;
   - `2 (A7)`: el módulo externo en el pin 2;
   - `Detect`: el firmware detecta automáticamente el módulo conectado.
4. Con `2 (A7)` seleccionado puedes conmutar aquí también `5V on GPIO`. Con `Detect`, el elemento de 5 V muestra
   `Auto`.

Consulta la sección [Infrarrojos](/es/infrared/) para el uso de los mandos.

## Reglas generales

1. **Apaga el Flipper antes de conectar.** Conectar en caliente condensadores grandes puede corromper la tarjeta
   SD.
2. **Lógica de 3,3 V.** No metas las salidas del Flipper en lógica de 5 V; las entradas solo toleran 5 V mientras
   estén configuradas como entradas.
3. **Respeta los límites de corriente:** 1,2 A en el pin 1 y en el pin 9, 20 mA por pin de E/S. Véase
   [patillaje](/es/gpio/pinout).
4. **Cruza TX y RX** en los módulos UART: el TX del Flipper va al RX del módulo.
5. **Insértalo hasta el fondo.** Un módulo a medio insertar hace un contacto intermitente.

## Relacionado

- [Patillaje GPIO](/es/gpio/pinout)
- [Aplicación GPIO](/es/gpio/gpio-app)
- [Módulos de expansión](/es/gpio/expansion-modules)
- [Módulos y sus apps](/es/gpio/module-apps)
