---
title: Módulos de expansión
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Módulos de expansión

Un **módulo de expansión** es una placa de terceros en el conector GPIO que el Flipper detecta automáticamente y a
la que permite controlarlo por **RPC** (el mismo protocolo que usan qFlipper y la aplicación móvil). El
[Video Game Module](/es/gpio/video-game-module) es el ejemplo más conocido. De la detección y del enlace se
encargan el servicio `expansion` del firmware y el **Expansion Module Protocol** que se describe más abajo.

## Ajuste: en qué UART escuchar

1. Abre `Main Menu → Settings → Expansion Modules`.
2. Pon `Listen UART` en:
   - `USART`: pines 13 (TX) / 14 (RX). Obligatorio para el Video Game Module.
   - `LPUART`: pines 15 (TX) / 16 (RX).
   - `None`: detección desactivada; el Flipper ignora los módulos.
3. Pulsa <kbd>BACK</kbd>. La elección se guarda y se aplica de inmediato.

| UART | Pin TX | Pin RX |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Cuándo elegir None
Si usas el mismo UART para otra cosa (una placa Wi-Fi, GSM, GPS, el puente USB-UART) y notas un comportamiento
raro, pon `Listen UART` en `None` o en el otro UART. Las aplicaciones que se adueñan del puerto serie pausan la
detección mientras están en marcha.
:::

## Expansion Module Protocol (para desarrolladores de módulos)

Un protocolo orientado a bytes, síncrono y de petición-respuesta sobre el UART, con detección del módulo,
negociación de la velocidad en baudios, una suma de comprobación XOR y reenvío transparente del tráfico RPC.

### Términos

- **Host**: el Flipper. **Device / module**: el módulo de expansión.
- **Intervalo de tiempo de espera, Tto = 250 ms**: la inactividad se trata como una conexión perdida.
- **Tiempo muerto tras cambiar de velocidad, Tdt = 25 ms**: no se permite tráfico justo después de un cambio de
  velocidad.

### Estructura de la trama

| Cabecera (1 byte) | Contenido (0 o más bytes) | Suma de comprobación (1 byte) |
|---|---|---|
| Tipo de trama | Carga útil | XOR de todos los bytes anteriores, valor inicial 0 |

| Tipo | Cabecera | Contenido | Propósito |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Mantiene viva una conexión inactiva |
| STATUS | `0x02` | código de error (1 byte) | Confirma cada trama recibida |
| BAUD RATE | `0x03` | velocidad en baudios (4 bytes) | Negocia la velocidad |
| CONTROL | `0x04` | comando (1 byte) | Inicia o detiene RPC, controla los 5 V |
| DATA | `0x05` | tamaño (1 byte, `0x00`–`0x40`) + hasta 64 bytes de datos | Transporta datos RPC |

Códigos de error de STATUS: `0x00` correcto, `0x01` error desconocido, `0x02` velocidad en baudios no admitida.

Comandos CONTROL:

| Comando | Significado | Permitido cuando |
|---|---|---|
| `0x00` | Iniciar la sesión RPC | RPC no activo |
| `0x01` | Detener la sesión RPC | RPC activo |
| `0x02` | Activar OTG (5 V) en el GPIO | RPC no activo (si no, usa mensajes RPC) |
| `0x03` | Desactivar OTG (5 V) en el GPIO | RPC no activo (si no, usa mensajes RPC) |

### Flujo de la conexión

1. **El módulo la inicia** poniendo brevemente a nivel bajo el pin RX del Flipper.
2. El Flipper responde con un **HEARTBEAT**: está listo.
3. Dentro de Tto, el módulo debe enviar una trama **BAUD RATE**, siempre la primera, incluso si 9600 le vale. La
   velocidad inicial es siempre de **9600 baudios**. El Flipper responde con STATUS correcto o `0x02`; si lo
   rechaza, el módulo puede ofrecer otras velocidades. No se permite nada más hasta que la negociación tenga éxito.
4. Los dos lados cambian de velocidad; el módulo espera Tdt.
5. El módulo envía **CONTROL → Start RPC** y el Flipper lo confirma con STATUS.
6. Las peticiones RPC van en tramas **DATA** (partidas en bloques de 64 bytes; cada bloque se confirma con STATUS).
   Las respuestas RPC vuelven como tramas DATA, que el módulo debe confirmar con STATUS.
7. Cuando no hay actividad, el módulo envía **HEARTBEAT** con más frecuencia que cada Tto; el Flipper responde con
   un HEARTBEAT.
8. **CONTROL → Stop RPC** termina la sesión. Tras Tto de silencio, el Flipper vuelve al estado de espera.

```text
        MODULE               |            FLIPPER
-----------------------------+---------------------------
Pull down RX                -->
                            <--       Heartbeat
Baud Rate                   -->
                            <--       Status [OK | Error]
(both change baud rate, module waits Tdt)
Control [Start RPC]         -->
                            <--       Status [OK | Error]
Data [RPC Request]          -->
                            <--       Status [OK | Error]
                            <--       Data [RPC Response]
Status [OK | Error]         -->
Heartbeat                   -->
                            <--       Heartbeat
Control [Stop RPC]          -->
                            <--       Status [OK | Error]
```

### Errores

Ante cualquier error detectado (suma de comprobación errónea, trama inesperada), el lado que lo ha advertido
**detiene toda la comunicación y se reinicia**. El otro lado agota Tto y la conexión se vuelve a establecer desde
el paso 1.

### Control desde el programa

Las aplicaciones del firmware pueden llamar a `expansion_enable()` / `expansion_disable()` (y a
`expansion_set_listen_serial()`) del servicio `expansion` en lugar de usar la pantalla de ajustes. En el árbol de
código fuente se incluye una aplicación de depuración, `expansion_test`, como implementación de referencia de un
módulo.

## Relacionado

- [Video Game Module](/es/gpio/video-game-module)
- [Patillaje GPIO](/es/gpio/pinout)
- [Módulos externos](/es/gpio/external-modules)
