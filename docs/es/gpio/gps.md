---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Hay dos formas de darle una ubicación al Flipper:

| Opción | Hardware | Cómo funciona |
|---|---|---|
| **Servicio GPS (ubicación del dispositivo emparejado)** | Ninguno: un móvil u ordenador conectado por USB o Bluetooth | Las aplicaciones piden su ubicación a la aplicación complementaria conectada por RPC |
| **Módulo GPS NMEA** | Un receptor GPS serie en el UART del GPIO | El plugin `[NMEA] GPS` lee las sentencias NMEA del módulo |

## Servicio GPS (ubicación del dispositivo emparejado)

::: tip Unleashed
El firmware Unleashed incluye un servicio de sistema `gps` (registro `gps`, arrancado al inicio). No usa ningún pin
del GPIO: reenvía las peticiones de ubicación por la **sesión RPC** activa (USB o Bluetooth) a la aplicación
complementaria, que responde con la posición del móvil o del ordenador.
:::

Lo que obtiene una aplicación:

| Campo | Unidad |
|---|---|
| Latitud, longitud | grados × 10⁷ |
| Rumbo | grados × 100 (0…36000) |
| Velocidad | mm/s |
| Altitud | cm |
| Precisión | mm |
| Satélites | cantidad |

Las aplicaciones pueden pedir una sola posición (`gps_request_location()`), un flujo continuo a **1–10 Hz**
(`gps_request_stream()` / `gps_stop_stream()`) y también enviar una ubicación de vuelta al dispositivo emparejado
(`gps_report_location()`). El dispositivo emparejado puede responder con un error: no admitido, sin permiso,
ubicación desactivada o error desconocido.

### Probarlo

El árbol de código fuente incluye dos aplicaciones de ejemplo de @apfxtech (categoría `Examples`, compiladas como
FAP):

- **`[RPC] GPS Click`**: petición puntual; pulsa <kbd>OK</kbd> para obtener la ubicación. Muestra latitud, longitud,
  rumbo, velocidad, altitud, satélites y precisión. <kbd>BACK</kbd> sale.
- **`[RPC] GPS Stream`**: flujo continuo con los mismos datos.

Mensajes que puedes ver:

| Mensaje | Significado |
|---|---|
| `No USB/BLE connection` | No hay sesión RPC: conecta la aplicación complementaria por USB o Bluetooth |
| `GPS not available` | La aplicación complementaria no admite la ubicación |
| `Permission denied` | No se ha concedido el permiso de ubicación a la aplicación complementaria |
| `Location disabled` | Los servicios de ubicación están desactivados en el móvil o el ordenador |
| `No response` | La aplicación complementaria no ha respondido a tiempo |
| `Waiting for data...` | El flujo ha arrancado, pero todavía no hay posición |

La aplicación complementaria debe admitir estas peticiones GPS por RPC; comprueba la tuya (véase
[Móvil](/es/mobile/)).

Para quien desarrolla aplicaciones: incluye `<gps/gps.h>` y abre el registro con `furi_record_open(RECORD_GPS)`; la
cabecera trae además utilidades para formatear coordenadas, rumbo, velocidad, altitud y precisión.

## Módulo GPS NMEA en el UART

Para obtener una ubicación sin móvil, conecta un receptor GPS serie (la mayoría de los módulos que emiten
sentencias NMEA con lógica de 3,3 V).

Cableado (USART):

| Pin del Flipper | Módulo GPS |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) o 1 (5V) | VCC (comprueba el rango de alimentación del módulo) |
| 8, 11 o 18 (GND) | GND |

Después abre el plugin `[NMEA] GPS` de los paquetes de aplicaciones extra. La configuración, la velocidad en
baudios y los módulos admitidos están en su
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
El módulo GPS y los demás usuarios del UART (placas Wi-Fi, SIM800, módulos de expansión, salida de registros)
comparten los pines 13/14. Si el plugin no recibe datos, comprueba
`Settings → Expansion Modules → Listen UART` y `Settings → System → Log Device`.
:::

## Apps

Apps que funcionan con un módulo GPS, todas de los paquetes:

| App | Paquete | Qué hace |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Posición de cualquier módulo GPS NMEA en UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Muestra y registra datos de módulos GPS u-blox por I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Rastreador NMEA con navegación por puntos |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Explorador que ordena tus archivos por distancia desde donde estás |

Lista completa de apps para módulos: [Módulos y sus apps](/es/gpio/module-apps).

## Relacionado

- [ESP32 y Wi-Fi](/es/gpio/esp32) — mapa de wardriving
- [Módulos externos](/es/gpio/external-modules)
- [Patillaje GPIO](/es/gpio/pinout)
