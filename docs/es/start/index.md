---
title: Primeros pasos
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-readme, unleashed-docs, unleashed-src, flipper-docs]
---
# Primeros pasos

Esta sección te lleva de un Flipper Zero recién sacado de la caja a un dispositivo completamente configurado con el
**firmware Unleashed**. Cubre lo básico que da por supuesto cualquier otra sección de la wiki: botones, escritorio,
energía, tarjeta microSD, ajustes y recuperación.

## ¿Qué es el Flipper Zero?

El Flipper Zero es una multiherramienta de bolsillo para explorar la tecnología de radio y de control de accesos. Su
hardware incluye:

- un **transceptor Sub-GHz CC1101** para mandos de garaje, barreras, sensores y otros dispositivos por debajo de
  1 GHz;
- un módulo **NFC de 13,56 MHz** y una antena **RFID de 125 kHz** para tarjetas, llaveros y etiquetas;
- un emisor y un receptor de **infrarrojos** para televisores, aires acondicionados y otros mandos;
- un contacto **1-Wire (iButton)** para llaves Dallas, Cyfral y Metakom;
- **USB** y **Bluetooth LE**, de modo que puede actuar como teclado (Bad USB), como token U2F o como mando;
- pines **GPIO** para módulos externos (CC1101 externo, NRF24, ESP32, SIM800 y más);
- una pantalla monocroma de 128×64, un pad de 5 direcciones con botón Back y una batería de 2100 mAh.

En el escritorio vive un delfín mascota digital que sube de nivel según usas el dispositivo.

## ¿Qué es el firmware Unleashed?

[Unleashed](https://github.com/DarkFlippers/unleashed-firmware) es un fork del firmware oficial (OFW). Se mantiene
**totalmente compatible con la API y las aplicaciones del OFW** y añade funciones por encima. Lo principal que
incorpora:

- **ninguna restricción regional de transmisión en Sub-GHz**, frecuencias adicionales y un rango ampliado opcional;
- **muchos más protocolos Sub-GHz**, con la posibilidad de guardar y enviar numerosos sistemas de código rodante,
  botones personalizados y `Add manually` para mandos nuevos;
- soporte de módulos **CC1101 externos**;
- parsers NFC adicionales, un parser EMV y más claves de MIFARE Classic en el diccionario del sistema;
- fuzzers de RFID e iButton, una herramienta para T5577 y otras aplicaciones integradas;
- comodidades de uso: nombre personalizado del Flipper, reloj en el escritorio, porcentaje de batería, Night Shift,
  más juegos en el Dummy Mode, BadKB (Bad USB por Bluetooth) y más.

En [Qué añade Unleashed](/es/start/unleashed-features) está la lista completa con enlaces.

::: warning Solo fuentes oficiales
`DarkFlippers/unleashed-firmware` es el único hogar oficial del proyecto. Todas las compilaciones son gratuitas y de
código abierto. No existen versiones de pago, «premium» ni de código cerrado. Quien te ofrezca una es un estafador.
:::

## Builds release y dev

| Build | Qué es | Dónde conseguirlo |
|---|---|---|
| **Release** (estable) | Versiones probadas, recomendadas para el uso diario | [Web Installer](https://web.unleashedflip.com), [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), Telegram [@unleashed_fw](https://t.me/unleashed_fw) |
| **Dev** (pruebas) | Compilaciones automáticas de la rama `dev` para probar nuevas funciones | [dev.unleashedflip.com](https://dev.unleashedflip.com), Telegram [@kotnehleb](https://t.me/kotnehleb), canal de Discord `unleashed-development` |

Cada build dev nuevo sustituye al anterior en la web; los builds dev antiguos solo sobreviven como archivos en el
canal de Telegram. Los builds dev reciben las novedades primero, pero **pueden contener fallos**. Si encuentras uno,
comunícalo en las [issues de GitHub](https://github.com/DarkFlippers/unleashed-firmware/issues).

Cada release llega en tres variantes: `e` (base + aplicaciones extra), sin sufijo (aplicaciones base) y `c` (sin
aplicaciones de la comunidad). Los detalles están en
[Instalar Unleashed](/es/start/install#which-file-to-download).

## Canales de la comunidad

- Chats de Telegram: [inglés](https://t.me/flipperzero_unofficial), [ruso](https://t.me/flipperzero_unofficial_ru), [ucraniano](https://t.me/flipperzero_unofficial_ua)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Web de Unleashed: [flipperunleashed.com](https://flipperunleashed.com)

## Páginas de esta sección

**Primeros pasos**
- [Primer arranque](/es/start/first-start): encender, insertar una tarjeta microSD, instalar Unleashed
- [Instalar Unleashed](/es/start/install): Web Installer, qFlipper, aplicaciones móviles, actualización sin conexión desde la tarjeta SD
- [Actualizar](/es/start/updating): mantenerse al día, release frente a dev, qué sobrevive a una actualización
- [Qué añade Unleashed](/es/start/unleashed-features): todas las funciones de Unleashed comparadas con el firmware de serie

**Usar el dispositivo**
- [Controles](/es/start/controls): botones, modo para zurdos, atajos
- [Escritorio](/es/start/desktop): barra de estado, accesos directos, Lock Menu, Quick Settings, Dummy Mode, Archive
- [El delfín mascota](/es/start/dolphin): humor, niveles y XP
- [Energía y batería](/es/start/power): carga, apagado, Auto PowerOff, Limit Charge
- [Tarjeta microSD](/es/start/sd-card): elección, formateo, estructura de carpetas
- [Ajustes](/es/start/settings): todos los elementos del menú Settings, uno por uno
- [Nombre personalizado del Flipper](/es/start/custom-name)

**Cuando algo va mal**
- [Combinaciones de teclas](/es/start/key-combos): combinaciones de reinicio y de DFU
- [Recuperación](/es/start/recovery): recuperar el firmware, reinicio de fábrica, restablecer el PIN
- [Ajustes peligrosos](/es/start/dangerous-settings): rango Sub-GHz ampliado (léelo antes de tocarlo)
- [Preguntas frecuentes](/es/start/faq)

::: tip Aspectos legales
Unleashed está pensado para experimentar y para investigación lícita. Úsalo en tus propios dispositivos o con
permiso.
:::
