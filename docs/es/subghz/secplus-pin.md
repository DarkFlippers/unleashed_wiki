---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (de @xMasterX) trabaja con una señal capturada de un **teclado Security+ 2.0**: el paquete de 86 bits que envían los teclados inalámbricos de Chamberlain / LiftMaster. El PIN del teclado reside dentro de ese paquete. La aplicación te permite fijar un PIN a mano o barrer de `0000` a `9999`, transmite cada candidato y escribe el PIN de vuelta en el fichero una vez has encontrado el correcto.

::: tip Unleashed
El teclado Security+ 2.0 (86 bits, 315 / 390 / 868 MHz) lo decodifica la aplicación Sub-GHz de Unleashed, y esta aplicación de sistema integrada edita su PIN. Los mandos Security+ 2.0 normales de 62 bits no son paquetes de teclado y se rechazan.
:::

::: warning
Solo para tu propio abrepuertas de garaje y tu propio teclado.
:::

## Antes de empezar

1. Captura tu teclado con `Sub-GHz → Read` en su frecuencia (véase [Read](/es/subghz/read)) y guárdalo. El fichero guardado debe mostrar `Security+ 2.0` con `Bit: 86`.
2. El fichero vive en `/ext/subghz/`.

## Uso de la aplicación

1. Abre `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Elige `Open .sub file` y selecciona la captura del teclado. Al cargarse, el estado muestra la frecuencia y `ready` (por ejemplo `315MHz  ready`). Si el fichero ya contiene un `Pin`, se muestra.
3. Los cuatro dígitos del PIN están en pantalla, con un marco alrededor del dígito activo:
   - <kbd>←</kbd> / <kbd>→</kbd>: moverse entre dígitos
   - <kbd>↑</kbd> / <kbd>↓</kbd>: cambiar el PIN
   - <kbd>OK</kbd> (`Send`): transmitir el PIN actual (`Sending 1234...` → `Sent 1234`)
   - mantener <kbd>OK</kbd>: **barrido**; envía todos los PIN a partir del actual, con una barra de progreso que muestra `N of 9999`. Una pulsación corta de <kbd>OK</kbd> o <kbd>←</kbd> (Back) lo detiene en `Stopped at NNNN`
   - mantener <kbd>←</kbd>: **guardar** el PIN actual en el fichero (`Saved PIN NNNN`)
   - <kbd>Back</kbd>: volver al menú

La línea de ayuda en pantalla lo resume: `hold OK sweep   < save`.

Al guardar se actualiza el fichero abierto sobre sí mismo: se escriben los campos `Pin`, `Key` y `Secplus_packet_1`. A partir de entonces el fichero se puede enviar normalmente desde `Sub-GHz → Saved`.

## Mensajes

| Mensaje | Significado |
|---|---|
| `Not Security+ 2.0: …` | el fichero es de otro protocolo |
| `Not an 86-bit keypad` | es un mando Security+ 2.0, no un paquete de teclado |
| `Missing packet 1` / `No Key value` | captura incompleta: vuelve a leer el teclado |
| `Unsupported preset …` / `Bad custom preset` | el preset del fichero no se puede usar |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | no se permite transmitir en esta frecuencia (véase [Frecuencias](/es/subghz/frequencies)) |
| `TX failed` | la radio no ha podido transmitir |

## Resolución de problemas

- **El barrido es lento**: cada PIN es una transmisión independiente con una pausa corta; un barrido completo tarda mucho. Empiézalo en un valor probable y detenlo en cuanto la puerta reaccione.
- **La puerta reaccionó pero se te pasó el PIN**: el barrido se detiene en el número mostrado; retrocede con <kbd>↓</kbd> y envía PIN individuales con <kbd>OK</kbd> para confirmarlo, y después mantén <kbd>←</kbd> para guardar.
- **Se rechaza un fichero equivocado**: captura el teclado en sí, no un mando de mano.

## Páginas relacionadas

- [Read](/es/subghz/read) · [Sistemas compatibles](/es/subghz/supported-systems)
- [Códigos rodantes](/es/subghz/rolling-codes)
