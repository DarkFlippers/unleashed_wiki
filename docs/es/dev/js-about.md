---
title: "JavaScript: visión general"
sidebarTitle: "JS: visión general"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript en Flipper Zero

Escribir una app para Flipper Zero significaba antes usar C, un toolchain completo y leer mucho código fuente de otras apps. El firmware incluye ahora un **motor de JavaScript integrado**, así que puedes escribir un simple archivo `.js`, copiarlo a la tarjeta SD y ejecutarlo directamente desde el dispositivo. No hace falta compilar en un PC y los scripts son fáciles de compartir.

- Los scripts residen en `/ext/apps/Scripts/` y se lanzan desde `Main Menu → Apps → Scripts`, o desde la CLI con `js <path>`.
- El motor se basa en [mJS](https://github.com/cesanta/mjs), un intérprete de JavaScript diseñado para microcontroladores: necesita menos de 50 KB de flash y unos 2 KB de RAM. El Flipper mantiene el núcleo de mJS y añade extras como arrays binarios compactos (`ArrayBuffer`, typed arrays).
- Los scripts pueden usar la GUI, los botones, el HID USB (BadUSB), el GPIO, el UART, el sistema de archivos y más, a través de **módulos** cargados con `require()`.

::: warning mJS no es un motor de navegador
mJS admite un subconjunto de JavaScript. Lo más destacado: **no hay closures** (una función no puede usar variables del ámbito que la rodea; consulta [Bucle de eventos](/es/dev/js-event-loop) para la solución alternativa), las cadenas son de un solo byte sin soporte de UTF-8, y faltan muchos objetos de la biblioteca estándar. Consulta el [README de mJS](https://github.com/cesanta/mjs) para ver la lista completa de limitaciones.
:::

## Primeros pasos

1. [Tu primera app en JS](/es/dev/js-first-app): escribe un script, cópialo al Flipper y ejecútalo desde el menú o la CLI.
2. [SDK de JavaScript](/es/dev/js-sdk): TypeScript, autocompletado y subida con un solo comando mediante `npm start`.
3. [Usar módulos de JS](/es/dev/js-modules): cómo funciona `require()`.

## Referencia del lenguaje

- [Tipos de datos](/es/dev/js-data-types)
- [Funciones integradas](/es/dev/js-builtin): `print`, `delay`, `require`, `load`, métodos de cadenas y arrays, comprobaciones de compatibilidad del SDK.

## Referencia de módulos

| Módulo | Nombre en `require()` | Página |
|---|---|---|
| Bucle de eventos | `event_loop` | [Bucle de eventos](/es/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/es/dev/js-gui), [Vistas de la GUI](/es/dev/js-gui-views) |
| BadUSB (teclado HID USB) | `badusb` | [BadUSB](/es/dev/js-badusb) |
| Información del dispositivo | `flipper` | [Flipper](/es/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/es/dev/js-gpio) |
| Matemáticas | `math` | [Math](/es/dev/js-math) |
| Notificaciones de LED / vibración / sonido | `notification` | [Notification](/es/dev/js-notification) |
| UART | `serial` | [Serial](/es/dev/js-serial) |
| Archivos y carpetas | `storage` | [Storage](/es/dev/js-storage) |

Los scripts de ejemplo de cada módulo se instalan con el firmware en `/ext/apps/Scripts/js_examples/` (por ejemplo `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Leerlos es la forma más rápida de aprender la API.

## Extras de Unleashed: módulos sin documentación oficial {#unleashed-extras}

::: tip Unleashed
Unleashed declara `flipper.firmwareVendor === "unleashed"` e incluye **módulos de JS adicionales** que el firmware de fábrica no tiene. La documentación oficial de JS no los cubre, así que las páginas de abajo se han escrito a partir del código del firmware (`applications/system/js_app/modules/`) y de las declaraciones de TypeScript de `packages/fz-sdk/`. Cada módulo es además una «característica» del SDK, así que compruébala con `doesSdkSupport([...])` o `checkSdkFeatures([...])` (consulta [Funciones integradas](/es/dev/js-builtin#sdk-compatibility)) para que tu script siga funcionando en otros firmwares.
:::

La lista completa de características adicionales que declara Unleashed es: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Módulo | Nombre de la característica | Qué hace | Página |
|---|---|---|---|
| `subghz` | `subghz` | Controla la radio Sub-GHz (CC1101 interno o externo): RX, RSSI, frecuencia, transmisión de ficheros `.sub` | [JS: subghz](/es/dev/js-subghz) |
| `infrared` | `infrared-send` | Envía señales de IR por protocolo o como temporizaciones en bruto | [JS: infrared](/es/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Emite paquetes de anuncio BLE personalizados (baliza adicional) | [JS: blebeacon](/es/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Emula un dispositivo de almacenamiento masivo USB a partir de una imagen de disco | [JS: usbdisk](/es/dev/js-usbdisk) |
| `i2c` | `i2c` | Habla con dispositivos I2C del conector GPIO | [JS: i2c](/es/dev/js-i2c) |
| `spi` | `spi` | Habla con dispositivos SPI del bus SPI externo | [JS: spi](/es/dev/js-spi) |
| `vgm` | `vgm` | Lee la IMU (pitch/roll/yaw) del Video Game Module | [JS: vgm](/es/dev/js-vgm) |

El módulo GUI tiene también vistas que faltan en la documentación oficial: `button_menu`, `button_panel`, `menu`, `number_input`, `popup` y `vi_list`. Se describen en [Vistas de la GUI](/es/dev/js-gui-views).

Las APIs del firmware que esta wiki no cubre están en la [referencia de la API en Doxygen](https://developer.flipper.net/flipperzero/doxygen/) oficial.

## Páginas relacionadas

- [Escribir apps en C](/es/dev/first-app-c), para cuando JS no es lo bastante rápido o flexible.
- [Formato de script de BadUSB](/es/badusb/script-format), la alternativa clásica en DuckyScript al módulo `badusb` de JS.
