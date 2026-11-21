---
title: GPIO y módulos
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO y módulos

El conector de 18 pines del borde superior del Flipper Zero lo convierte en una herramienta de hardware: puede
alimentar módulos externos y comunicarse con ellos, hacer de adaptador USB-UART, conmutar pines a mano para hacer
pruebas y servir de objetivo para un depurador por hardware.

![Conector GPIO del Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Conceptos básicos

| Página | Qué contiene |
|---|---|
| [Patillaje GPIO](/es/gpio/pinout) | Los 18 pines, voltajes, límites de corriente, 5 V en el pin 1, tolerancia a 3,3 V / 5 V |
| [Aplicación GPIO](/es/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; comandos `gpio` e `i2c` de la CLI |
| [Módulos externos](/es/gpio/external-modules) | Panorama de los tipos de módulo y de los pines que usa cada uno |
| [Módulos de expansión](/es/gpio/expansion-modules) | `Settings → Expansion Modules` y el Expansion Module Protocol |
| [Módulos y sus apps](/es/gpio/module-apps) | Todos los módulos que soportan los paquetes de apps, y qué hace cada app |

## Módulos

| Página | Módulo |
|---|---|
| [CC1101 externo](/es/subghz/external-cc1101) | Radio Sub-GHz con un front end más potente (se trata en la sección de Sub-GHz) |
| [ESP32 / Wi-Fi](/es/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, el web flasher de Unleashed y el mapa de wardriving |
| [NRF24](/es/gpio/nrf24) | Sniffer nRF24L01 de 2,4 GHz y MouseJack |
| [SIM800](/es/gpio/sim800) | Módulo GSM: llamadas, SMS, agenda, USSD (aplicación integrada en Unleashed) |
| [GPS](/es/gpio/gps) | Ubicación desde el móvil emparejado (servicio GPS) y módulos GPS NMEA por UART |
| [Video Game Module](/es/gpio/video-game-module) | Módulo RP2040 con salida de vídeo y un sensor de movimiento |

## Wi-Fi Developer Board

| Página | Qué contiene |
|---|---|
| [Devboard: primeros pasos](/es/gpio/devboard) | Preparar el Flipper, conectarla, conexión por USB y por Wi-Fi |
| [Devboard: depuración y registros](/es/gpio/devboard-debug) | Black Magic / DAPLink, depuración en VS Code, leer los registros UART |
| [Devboard: actualizar el firmware](/es/gpio/devboard-firmware) | Flashear el firmware propio de la placa con uFBT |

::: tip Unleashed
Unleashed incluye herramientas GPIO adicionales de serie: la aplicación [SIM800](/es/gpio/sim800)
(`Apps → GPIO → SIM800`), soporte de CC1101 externo con control del amplificador en Sub-GHz, salida para módulo IR
externo en `Infrared → GPIO Settings` y un buen conjunto de plugins de GPIO en los paquetes de aplicaciones extra.
Véase [Módulos externos](/es/gpio/external-modules).
:::

::: warning Antes de conectar cualquier cosa
Apaga el Flipper antes de conectar un módulo, y encaja el módulo hasta el fondo del conector. Conectar en caliente
un módulo con una carga capacitiva grande puede corromper la tarjeta microSD, porque la tarjeta y el pin 9
comparten el mismo raíl de 3,3 V.
:::
