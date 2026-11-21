---
title: ESP32 y Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 y Wi-Fi

El Flipper Zero no tiene Wi-Fi propio. Las herramientas de Wi-Fi vienen de una placa **ESP32** (o ESP8266) en el
conector GPIO, que hace el trabajo de radio y se comunica con una aplicación del Flipper por el UART. Esta página
es un panorama de las opciones y de las herramientas web de Unleashed que las acompañan.

## Qué placa

| Placa | Uso habitual |
|---|---|
| **Wi-Fi Developer Board oficial** (ESP32-S2) | Viene con el firmware de sonda de depuración Black Magic para [depurar](/es/gpio/devboard). Se puede reflashear con Marauder |
| **Placas ESP32 Marauder** (varias placas ESP32 / ESP32-S2 / ESP32-S3, placas combo) | Escaneo de Wi-Fi y BLE, captura de paquetes, wardriving |
| **Placas ESP8266** | Firmware Wi-Fi Scanner y Deauther |
| **ESP32-CAM** | Camera Suite (imagen de la cámara en la pantalla del Flipper) |

## Apps

Cada una es solo la mitad que va en el Flipper: antes hay que grabar en la placa el firmware correspondiente.

| App | Paquete | Qué hace |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Interfaz para el firmware Marauder: escaneo de Wi-Fi y BLE, captura de paquetes, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Lista las redes Wi-Fi cercanas, para el firmware Scanner en ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Interfaz para el firmware DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Imagen en directo de una ESP32-CAM en la pantalla del Flipper, con captura de fotos |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Segunda app para ESP32-CAM: imagen en directo y fotos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Interfaz para el firmware Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Monta en el ESP32 un punto de acceso con portal cautivo |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Para el firmware Deauther v2 de @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Graba firmware en una placa ESP desde el Flipper, por UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Dispara un webhook de IFTTT a través de un ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Mapeo de redes Wi-Fi con un ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Muestra la cara y el estado de un Pwnagotchi en el Flipper, por UART |

Lista completa de apps para módulos: [Módulos y sus apps](/es/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder), de justcallmekoko, es un firmware para placas
ESP32. En el Flipper se usa a través de la aplicación **WiFi Marauder** de los paquetes de aplicaciones extra, que
envía comandos a la placa y muestra su salida.

Flujo de trabajo típico:

1. **Flashea Marauder** en la placa ESP32 (véase el flasher más abajo).
2. Apaga el Flipper, conecta la placa al conector GPIO y enciéndelo.
3. Abre la aplicación Marauder en `Apps → GPIO` y elige un comando (escanear puntos de acceso, hacer sniffing,
   wardriving, etc.).
4. Los resultados se muestran en la aplicación; las capturas y los registros de wardriving se guardan según los
   ajustes de la placa y de la aplicación (consulta la documentación de Marauder para tu placa).

Guía de uso completa de la Wi-Fi Devboard con Marauder (de UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Aspectos legales
El escaneo es pasivo, pero la desautenticación y otros ataques Wi-Fi activos son ilegales contra redes que no sean
tuyas o para las que no tengas permiso de prueba.
:::

## ESP32 Web Flasher

::: tip Unleashed
El equipo de Unleashed mantiene un flasher para navegador para los módulos ESP32 más habituales:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Funciona por completo en el navegador, así
que no hace falta instalar esptool. Usa un navegador compatible con Web Serial (los basados en Chromium).
:::

Pasos generales:

1. Desconecta la placa ESP32 del Flipper y conéctala al ordenador por USB.
2. Si la placa no entra en modo de flasheo por sí sola, mantén **BOOT**, pulsa **RESET** y suelta **BOOT**.
3. Abre el flasher, elige la placa y el firmware, pulsa conectar y selecciona el puerto serie de la placa.
4. Espera a que termine el flasheo, reinicia la placa y vuelve a conectarla al Flipper (con el Flipper apagado).

Otras formas de flashear una placa ESP:

- La aplicación **ESP flasher** para Flipper, que flashea un `.bin` desde la tarjeta SD del Flipper por el UART del
  GPIO: [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Guía para Windows de esptool / Flash Download Tool:
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- El [USB-UART Bridge de la aplicación GPIO](/es/gpio/gpio-app) con `RTS/DTR Pins` puede hacer de adaptador USB para
  placas que no tengan puerto USB propio.

::: tip Volver al firmware de depuración
Si has puesto Marauder en la Wi-Fi Devboard oficial y quieres recuperar el depurador Black Magic, reflashéala con
`ufbt devboard_flash` como se explica en [Devboard: actualizar el firmware](/es/gpio/devboard-firmware).
:::

## Wi-Fi Wardriving Map

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** combina y muestra en un solo mapa varias capturas de
wardriving en formato WiGLE procedentes de ESP32 Marauder y de otras herramientas.
:::

1. Haz una sesión de wardriving con Marauder (el wardriving necesita un módulo GPS conectado a la placa ESP32).
2. Copia los registros CSV en formato WiGLE a tu ordenador.
3. Abre el mapa y carga uno o varios archivos; las redes se dibujan todas juntas.

Para las capturas Sub-GHz y otros archivos con coordenadas hay un mapa aparte,
[map.unleashedflip.com](https://map.unleashedflip.com).

## Otros firmwares para ESP

| Firmware | Placa | Enlaces |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Cómo se usa](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Cómo se usa](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Cómo se usa](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Las aplicaciones de Flipper correspondientes están en los paquetes Base/Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Resolución de problemas

- **La aplicación no recibe respuesta de la placa:** la placa no tiene flasheado el firmware que espera la
  aplicación, TX/RX están en el UART equivocado o la placa no está insertada hasta el fondo.
- **Comportamiento raro en el UART:** otra función está escuchando en los mismos pines. Comprueba
  `Settings → Expansion Modules → Listen UART` (véase [Módulos de expansión](/es/gpio/expansion-modules)) y
  `Settings → System → Log Device`.
- **El flasher web no encuentra la placa:** usa un cable USB de datos, entra en modo bootloader a mano y prueba otro
  puerto USB u otro navegador.

## Relacionado

- [Wi-Fi Devboard](/es/gpio/devboard)
- [Módulos externos](/es/gpio/external-modules)
- [GPS](/es/gpio/gps)
