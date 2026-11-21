---
title: Hardware
order: 140
original: [https://docs.flipper.net/zero/development/hardware, https://docs.flipper.net/zero/development/hardware/tech-specs, https://docs.flipper.net/zero/development/hardware/schematic, https://docs.flipper.net/zero/development/hardware/flipper-blueprints, https://docs.flipper.net/zero/development/hardware/modules-blueprints, https://docs.flipper.net/zero/development/hardware/vgm-blueprints, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Hardware

Especificaciones técnicas de Flipper Zero, además de dónde encontrar sus esquemas, planos y modelos 3D — útil para
construir módulos externos y carcasas, y para la depuración de bajo nivel.

![Resumen de las especificaciones técnicas de Flipper Zero](/img/remote/629725f9f16a5946.png)

## Especificaciones técnicas

### Carcasa, tamaño y peso

| | |
|---|---|
| Materiales | PC, ABS, PMMA |
| Altura | 40,1 mm (1,58 in) |
| Anchura | 100,3 mm (3,95 in) |
| Profundidad | 25,6 mm (1,01 in) |
| Peso | 102 g (3,6 oz) |

### Pantalla

| | |
|---|---|
| Tipo | LCD monocromo |
| Resolución | 128×64 píxeles |
| Controlador | ST7567 |
| Interfaz | SPI |
| Diagonal | 1,4″ |

### Microcontrolador

| | |
|---|---|
| Modelo | [STM32WB55RG](https://www.st.com/en/microcontrollers-microprocessors/stm32wb55rg.html) |
| Núcleo de aplicación | Arm Cortex-M4, 32 bits, 64 MHz |
| Núcleo de radio | Arm Cortex-M0+, 32 bits, 32 MHz |
| Radio | Bluetooth LE 5.4, 802.15.4, propietaria |
| Flash | 1024 KB (compartida entre la aplicación y la radio) |
| SRAM | 256 KB (compartida entre la aplicación y la radio) |

### Sub-1 GHz

| | |
|---|---|
| Transceptor | [CC1101](https://www.ti.com/product/CC1101) |
| Potencia de TX | −20 dBm máx. (según las especificaciones oficiales) |
| Bandas de frecuencia | 315 MHz, 433 MHz, 868 MHz, 915 MHz (según la región) |

El CC1101 sintoniza en los rangos 299,999755–348 MHz, 386,999938–464 MHz y 778,999847–928 MHz.

::: tip Unleashed
Unleashed elimina las restricciones regionales de TX y añade frecuencias adicionales (350 MHz y 467 MHz se añaden al
rango por defecto). El rango se puede ampliar más todavía a 281–361, 378–481 y 749–962 MHz mediante el archivo
`subghz/assets/dangerous_settings` — eso queda fuera de las especificaciones del CC1101 y **puede dañar el
hardware** ([ajustes peligrosos](/es/start/dangerous-settings)). También se admite un
[módulo CC1101 externo](/es/subghz/external-cc1101). Respeta la normativa de radio de tu país.
:::

### NFC

| | |
|---|---|
| Transceptor | [ST25R3916](https://www.st.com/en/nfc/st25r3916.html) |
| Frecuencia | 13,56 MHz |
| Tarjetas | ISO-14443A/B; NXP MIFARE Classic®, Ultralight®, DESFire®, etc.; FeliCa™; HID iClass (Picopass); protocolos del NFC Forum |

### RFID de 125 kHz

| | |
|---|---|
| Frecuencia | 125 kHz |
| Modulación | AM, OOK |
| Codificación | ASK, PSK |
| Tarjetas (lista oficial) | EM-Micro EM4100, HID H10301, IDTECK Idteck, Motorola Indala 26, Kantech IoProx XSF, AWID, FECAVA FDX-A, ISO FDX-B, Generic HID Prox, Generic HID Ext, Farpointe Pyramid, Viking, Jablotron, Paradox, PAC Stanley, Keri, Gallagher, Honeywell Nexwatch, Electra, Securakey |

Consulta [RFID → Lectura](/es/rfid/read) para ver los protocolos que admite realmente el firmware Unleashed.

### Infrarrojos

| | |
|---|---|
| Longitud de onda de RX | 950 nm (±100 nm) |
| Portadora de RX | 38 kHz (±5 %) |
| Longitud de onda de TX | 940 nm |
| Portadora de TX | 0–2 MHz |
| Potencia de TX | 300 mW |
| Protocolos | Familia NEC, Kaseikyo, RCA, RC5, RC6, Samsung, SIRC |

### iButton (1-Wire)

Dallas DS199x, DS1971, CYFRAL, Metakom, TM2004, RW1990.

### GPIO

- 13 pines de E/S disponibles en conectores externos de 2,54 mm
- Niveles CMOS de 3,3 V
- Entradas tolerantes a 5 V (consulta la [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf) de ST)
- Hasta 20 mA por pin digital

Mapa de pines: [Patillaje GPIO](/es/gpio/pinout).

### Batería y alimentación

| | |
|---|---|
| Tipo | Polímero de litio (LiPo) |
| Capacidad | 2100 mAh |
| Autonomía | Hasta 28 días |
| Temperatura de funcionamiento | 0…40 °C (32…104 °F) |

### Tarjeta microSD

| | |
|---|---|
| Capacidad máxima | Hasta 256 GB |
| Capacidad recomendada | 2–32 GB |
| Interfaz | SPI |
| Velocidad de lectura/escritura | Hasta 5 Mbps |

El Flipper no incluye tarjeta microSD — cómprala por separado. Consulta [Tarjeta SD](/es/start/sd-card).

### USB

| | |
|---|---|
| Conector | Type-C |
| Estándar | USB 2.0 |
| Tasa de datos | 12 Mbps |
| Corriente máxima de carga | 1 A |

### Bluetooth LE 5.4

| | |
|---|---|
| Potencia de TX | 4 dBm máx. |
| Sensibilidad de RX | −96 dBm |
| Tasa de datos | 2 Mbps |

### Zumbador y vibración

| | |
|---|---|
| Frecuencia del zumbador | 100–2500 Hz |
| Salida del zumbador | 87 dB |
| Tipo de zumbador | De moneda |
| Fuerza de vibración | 30 N |
| Velocidad del motor de vibración | 13500 rpm |

### Contenido de la caja

Flipper Zero, cable USB-C a USB-A, documentación y una pegatina.

## Esquemas

Flipper Devices publica los esquemas de todas las PCB de Flipper Zero «con fines educativos» — son útiles para
desarrollar módulos de hardware y para la depuración de bajo nivel. Los visores interactivos de Altium y las descargas
en PDF están en la página oficial:
**[Schematics of Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)**.

![PCB de Flipper Zero](/img/remote/db285947a71be613.png)

| PCB | Documentos disponibles |
|---|---|
| **Main PCB** (rev. 12.1.F7B9C6) | Plano de montaje; resumen de los bloques principales; Power; Peripherals; MCU STM32WB55; LCD display; Sub-1 GHz CC1101; Buttons |
| **iButton PCB** (rev. 12.F7B9C6) — también lleva el altavoz piezoeléctrico y el IR | Plano de montaje; esquema de iButton |
| **NFC RFID PCB** (rev. 12.F7B9C6) — RFID de 125 kHz y NFC | Plano de montaje; resumen de los bloques de NFC; NFC; Power and vibro; RFID |
| **Antenna PCB** | Imagen de la placa |

::: info
En la revisión 13.F7B9C6 de la PCB de iButton cambiaron las huellas de los pines pogo: los pines pogo pasantes
sustituyeron a los SMD. Los diámetros de las huellas son los mismos que en la 12.F7B9C6.
:::

## Planos y modelos 3D

Todos los archivos se pueden descargar desde las páginas oficiales:

| Qué | Archivos | Página |
|---|---|---|
| Carcasa de Flipper Zero | Plano 2D (`.pdf`, `.dwg`), modelo 3D (`.stl`) | [Blueprints of Flipper Zero](https://docs.flipper.net/zero/development/hardware/flipper-blueprints) |
| Módulo externo normal | Plano (`.pdf`), modelo 3D de la PCB (`.stp`, suelta y montada), contorno de la PCB (`.dwg`, `.dxf`) | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Módulo externo pequeño | El mismo conjunto que el módulo normal | [External modules blueprints](https://docs.flipper.net/zero/development/hardware/modules-blueprints) |
| Video Game Module | Plano (`.pdf`, `.dwg.zip`), modelo 3D (`.stp`) | [Blueprints of Video Game Module](https://docs.flipper.net/zero/development/hardware/vgm-blueprints) |

![Plano de Flipper Zero](/img/remote/c91e01d61829df8e.png)

Los planos del módulo externo dan la geometría recomendada para las placas que se conectan al conector GPIO — empieza
por ahí si diseñas tu propio módulo (consulta también [Módulos de expansión](/es/gpio/expansion-modules)).

## Placas de desarrollo

### Wi-Fi Developer Board

Basada en el **ESP32-S2-WROVER-N4R2**. Documentos publicados: vista de la PCB, plano de montaje
(`Wi-Fi Module_V1_Assembly.pdf`), esquema del ESP32-S2, esquema de alimentación y esquema de conectores —
[Wi-Fi Developer Board schematics](https://docs.flipper.net/zero/development/hardware/devboard-schematics).
Uso: [Dev Board](/es/gpio/devboard), [Depurar apps](/es/dev/debugging).

### Placa de desarrollo ST-Link V3 {#st-link-v3-developer-board}

Para desarrolladores avanzados que necesitan depuración in-circuit. Está basada en el módulo
[ST-Link V3 Mods](https://www.st.com/en/development-tools/stlink-v3mods.html) y solo se diferencia en el factor de
forma y en la facilidad de conexión.

- ST-Link V3 Mods para flashear y depurar in-circuit.
- UART a USB integrado, conectado al UART del Flipper (pines GPIO 13 y 14).
- Pines sin usar de Flipper Zero y del ST-Link expuestos para depurar y prototipar.

Proyecto de Altium Designer:
[github.com/Flipper-Zero/flipperzero-devboard-stlinkv3](https://github.com/Flipper-Zero/flipperzero-devboard-stlinkv3).
Esquema y BOM: [ST-Link V3 Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3).

::: info No la necesitas para actualizar ni para desarrollar
Las actualizaciones de firmware, el desarrollo y la carga de tu propio firmware funcionan todos por USB normal. Una
placa de depuración solo es necesaria para depurar el firmware mientras se ejecuta (GDB, OpenOCD, …).
:::

## Páginas relacionadas

- [Patillaje GPIO](/es/gpio/pinout)
- [API Furi](/es/dev/furi-api) — diagrama de bloques del hardware
- [Depurar apps](/es/dev/debugging)
- [Actualizaciones OTA](/es/dev/ota)

MIFARE, MIFARE Ultralight, MIFARE Classic y DESFire son marcas registradas de NXP B.V. FeliCa es una marca comercial
de Sony Corporation.
