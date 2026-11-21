---
title: Aplicaciones incluidas en Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Aplicaciones incluidas en Unleashed

Una instalación de Unleashed tiene tres capas de aplicaciones:

1. **Apps de sistema (integradas).** Se compilan desde el repositorio del firmware y se instalan con cada
   actualización del firmware, sea cual sea la compilación que elijas.
2. **El pack Base Apps.** Un conjunto de apps de la comunidad, preinstalado en la compilación por defecto.
3. **El pack Extra Apps.** Muchas más apps de la comunidad, preinstaladas solo en la compilación `e`.

Además puedes instalar cualquier otra cosa por tu cuenta; consulta
[Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps).

## Variantes de compilación {#build-variants}

Los archivos de release se llaman `flipper-z-f7-update-(version)(e / c).tgz`:

| Parte | Significado |
|---|---|
| `flipper-z` | para Flipper Zero |
| `f7` | objetivo de hardware, el mismo en todos los Flipper Zero |
| `update` | paquete de actualización: actualizador, recursos (apps, bibliotecas de IR, etc.) y el propio firmware |
| `(version)` | versión del firmware |
| sufijo | qué packs de apps se incluyen (más abajo) |

| Sufijo | Base Apps | Extra Apps |
|---|:---:|:---:|
| ninguno (` `) | sí | no |
| `c` | no | no |
| `e` | sí | sí |

- **` ` (sin letra)** es la opción por defecto: firmware, apps de sistema y el pack Base.
- **`c`**: solo firmware y apps de sistema, sin pack de apps. Elígela si quieres montar tu propio conjunto de apps.
- **`e`**: firmware, apps de sistema, pack Base y pack Extra.

La forma recomendada de instalar cualquiera de ellas es el [instalador web](/es/mobile/web-tools); consulta también
[Instalar Unleashed](/es/start/install).

::: tip Unleashed
Las apps integradas **no** forman parte de los packs Base ni Extra. Una actualización de firmware las escribe en la
carpeta `apps/` de la tarjeta SD, así que instalar un pack de apps nunca puede sobrescribir ni degradar una app de
sistema.
:::

## Apps de sistema: visibles en el menú principal

| App | Qué hace | Autor / origen |
|---|---|---|
| GPIO | control de los pines GPIO, puente USB-UART y las herramientas 1-Wire/iButton | OFW |
| iButton | leer, guardar y emular llaves Dallas / Cyfral / Metakom | OFW |
| Infrared | aprender, guardar y enviar señales IR, mandos universales | OFW |
| NFC | leer, guardar, emular e interpretar tarjetas NFC | OFW |
| 125 kHz RFID | leer, guardar, emular y escribir tags LF RFID | OFW |
| Bad USB | payloads de Ducky Script por USB, y BadKB por Bluetooth | OFW + BadKB de Willy-JL, ClaraCrazy y colaboradores de XFW |
| U2F | token de seguridad FIDO U2F por USB, consulta [U2F](/es/apps/u2f) | OFW |
| Clock | reloj con control del brillo de pantalla, alarma y un temporizador básico, consulta [Reloj](/es/apps/clock) | @nymda, con @Willy-JL, @mishamyte y @xMasterX |
| Sub-GHz Remote | asignar hasta 5 archivos `.sub` guardados a los botones y enviarlos, consulta [Sub-GHz Remote](/es/subghz/remote) | @gid9798 y @xMasterX |

Sub-GHz, Archive, Settings y los servicios del sistema se compilan dentro del propio binario del firmware.

## Apps de sistema: en la carpeta Apps

Son archivos `.fap` bajo `Main Menu → Apps`, organizados en carpetas por categoría.

| App | Carpeta | Qué hace | Autor / origen |
|---|---|---|---|
| MFKey | NFC | recuperar claves de MIFARE Classic a partir de los nonces recogidos con Detect Reader, consulta [App MFKey](/es/nfc/mfkey-app) | @noproto |
| T5577 | RFID | leer, editar y escribir bloques T5577, borrar el tag o limpiar la contraseña, esnifar una contraseña, consulta [App T5577](/es/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | recuperar el código de instalador de un mando Nice O-Code y guardarlo como `.sub`, consulta [Nice O-Code](/es/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | encontrar el PIN del teclado en una señal Security+ 2.0 capturada, consulta [Security+ PIN](/es/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | recoger pares Fix + Hop de mandos FAAC SLH, Genius, Erreka y BFT Mitto para recuperar la Seed sin conexión, consulta [Seed Capturer](/es/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | decodificar un mando a la vez con el CC1101 interno, con analizador de frecuencias integrado, consulta [Remote Analyzer](/es/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | abrir una captura RAW `.sub`, localizar la señal, recortar, combinar y decodificar, consulta [Editor RAW](/es/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | manejar un módulo GSM SIM800C/SIM800L: llamadas, SMS, agenda, USSD, DTMF, terminal AT, consulta [SIM800](/es/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | baliza de localización BLE para Apple Find My / Google Find My Device y otros, consulta [FindMy Flipper](/es/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | el mando HID por USB, consulta [Mando HID](/es/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | el mando HID por Bluetooth, consulta [Mando HID](/es/apps/hid-remote) | OFW |
| Snake Game | Games | Snake, consulta [Snake](/es/apps/snake) | OFW |

El firmware incluye también los **estilos del menú principal**, pequeños plugins que se cambian en
`Settings → Desktop → Menu Style`, consulta [Estilos del menú principal](/es/apps/menu-styles), y el intérprete de
JavaScript que ejecuta los scripts `.js` (consulta [JavaScript](/es/dev/js-about)).

::: info Cambios recientes
A partir de la compilación del 20 de noviembre de 2026, Sub-GHz RAW Edit se incluye con el firmware y ya no forma
parte del pack Extra, y SIM800 es una nueva app integrada (`Apps → GPIO → SIM800`).
:::

## Packs Base y Extra {#base-and-extra-packs}

Las apps de la comunidad las recopila @xMasterX en
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): ese repositorio contiene la lista
completa y el código fuente, y su página de [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest)
ofrece los packs Base y Extra como descargas separadas, por si quieres añadir un pack a una compilación `c` o
actualizar apps entre releases del firmware.

Para instalar un pack a mano: descarga el `.zip` de la [página de releases](https://github.com/xMasterX/all-the-plugins/releases/latest), descomprímelo y copia las carpetas
de las apps en la carpeta `apps` de la tarjeta SD (`/ext/apps/`). La versión de API del pack tiene que coincidir con
la del firmware (`Current API:` al principio de cada changelog).

Apps a las que apunta el ReadMe de Unleashed (cada una está en uno de los packs):

| App | Dónde leer más |
|---|---|
| TOTP (Authenticator) | [descripción del archivo de configuración](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/es/apps/barcode) |
| Multi Converter | [Multi Converter](/es/apps/multi-converter) |
| WAV Player | [archivos de muestra y cómo convertirlos](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [script generador](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Fuerza bruta en Sub-GHz](/es/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [Fuzzer de RFID](/es/rfid/fuzzer), [Fuzzer de iButton](/es/ibutton/fuzzer) |
| Unitemp (sensores de temperatura) | [cómo usarlo y sensores compatibles](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [cómo usarlo](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [cómo usarlo](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| Apps NRF24 | [NRF24](/es/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 y módulos Wi-Fi](/es/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/es/apps/sentry-safe) |

::: warning
El contenido de los packs cambia entre releases. La etiqueta de compilación de los packs actuales se imprime al
principio de cada changelog de Unleashed (por ejemplo `Apps: Build tag (20nov2026)`), con un enlace a los últimos
commits de las apps.
:::

## Catálogo oficial

El catálogo oficial de aplicaciones de Flipper Zero está disponible en [Flipper Lab](https://lab.flipper.net/apps) y
en la [app móvil de Flipper](/es/mobile/mobile-app). La instalación desde él se describe en
[Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps#installing-from-the-official-catalog).

## Páginas relacionadas

- [Aplicaciones en la tarjeta SD (.fap)](/es/apps/sd-card-apps)
- [Resolución de problemas de apps](/es/apps/troubleshoot)
- [Instalar Unleashed](/es/start/install)
