---
title: Modos de contador
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Modos de contador (experimental)

**Counter Mode** cambia la forma en que avanza el contador rodante cuando el Flipper transmite una señal de código
rodante guardada. El objetivo: un clon de tu mando original que **no entre en conflicto** con él, de modo que tanto
el Flipper como el original puedan usarse con el mismo receptor sin desincronizarse. (Contexto:
[Códigos rodantes](/es/subghz/rolling-codes).)

::: tip Unleashed
Los modos de contador son una característica exclusiva de Unleashed. Protocolos compatibles: **Nice FloR-S,
CAME Atomo, Alutech AT-4N, KeeLoq y V2 Phoenix**.
:::

::: danger Léelo antes de usarlo
No experimentes con equipos a los que no tengas acceso. Si no estás seguro de qué modo funciona con tu sistema y
**no puedes volver a programar tu mando original** en el receptor, no uses estos modos. Pueden desincronizar o
bloquear tu mando. Si puedes probar en tu propio receptor, cuéntale al equipo de Unleashed qué funciona (issues de
GitHub o chats de la comunidad).
:::

## Cómo fijar un modo

### Opción 1 — editar el fichero `.sub`

1. Copia el fichero de `/ext/subghz/` a un PC (qFlipper, aplicación móvil o lector de tarjetas).
2. Añade una línea al final:
   ```text
   CounterMode: X
   ```
   donde `X` es el número de modo. Fíjate en el espacio después de los dos puntos.
3. Copia el fichero de vuelta.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### Opción 2 — Signal Settings en el Flipper

Con **Debug** activado, el menú de una señal guardada incorpora un elemento más:
`Sub-GHz → Saved → <fichero> → Signal Settings`. En su fila `Counter Mode` puedes elegir `System` (modo 0) y
`Mode 1` … hasta el último modo que tenga el protocolo, y la elección se escribe en el fichero de inmediato. En la
misma pantalla también se editan el contador y el código de botón:
véase [Signal Settings](/es/subghz/signal-settings).

## Modos por protocolo {#modes-by-protocol}

El modo 0 es siempre el predeterminado: se comporta como un mando normal, el contador crece con el valor global de
[Counter Incr.](/es/subghz/settings) (por defecto +1) y vuelve a 0 después de `0xFFFF`.

### Nice FloR-S

| Modo | Contador | Notas |
|---|---|---|
| 0 | +multiplicador | por defecto |
| 1 | `0x0001 / 0xFFFE` | receptor **floxi2r** |
| 2 | `0x0000 / 0x0001` | receptor **ox2** |

### CAME Atomo

| Modo | Contador | Notas |
|---|---|---|
| 0 | +multiplicador | por defecto |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | funciona con el CAME externo **RE432**, puede que con otros |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | funciona con el CAME externo **RE432**, puede que con otros |
| 3 | congelado | el contador no se incrementa |

### Alutech AT-4N

| Modo | Contador | Notas |
|---|---|---|
| 0 | +multiplicador | por defecto |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | receptor **MCSW-3.3M** |
| 2 | `0x0000 … 0x0005` | otras placas receptoras |

### KeeLoq

| Modo | Contador | Notas |
|---|---|---|
| 0 | +multiplicador | por defecto |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | puede que funcione con algunos sistemas |
| 2 | `+0x3333` por transmisión (13107) | por ejemplo DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | por ejemplo Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | por ejemplo Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | alterna 0 y 65535 |
| 6 | congelado | el contador no se incrementa |
| 7–10 | paquetes de resincronización forzada | DoorHan, Phantom / Hiland; véase más abajo |

#### Modos 7–10: paquetes de resincronización forzada (DoorHan, Phantom / Hiland)

Estos modos no avanzan el contador; cada pulsación envía un **paquete fijo** de códigos. Un receptor solo se
resincroniza cuando oye dos transmisiones con contadores **consecutivos**, así que el paquete se construye con
parejas consecutivas, espaciadas de modo que cada salto se mantenga dentro de la ventana de resincronización del
receptor y las parejas, en conjunto, cubran todo el espacio de contadores. Eso recupera al receptor desde cualquier
estado. El contador de tu fichero no cambia, así que cada pulsación envía el mismo paquete y el fichero sigue
siendo utilizable.

Cada paquete reproduce, código a código, lo que envía un mando clónico para esa familia de placas. Los modos 7–9 =
clon DoorHan Smart, el modo 10 = clon Phantom / Hiland. `X` = el contador de tu fichero.

| Modo | Para | Paquete | Tiempo por pulsación |
|---|---|---|---|
| 7 | las placas DoorHan más antiguas | 12 códigos: `X / X+1`, cuatro parejas que avanzan en pasos de 15998 (botón 0) y después `X-2 / X-1`; la primera y la última pareja llevan tu botón | ~1,3 s |
| 8 | DHRE, la mayoría de las placas más nuevas, clones de cancelas batientes | 12 códigos: `X / X+1`, cuatro parejas separadas `+0x3334` y después vuelta a tu contador, donde cae `X+1` con tu botón | ~1,3 s |
| 9 | placas de persiana CV01 y otras placas antiguas | 3 códigos con tu botón: `X + 0x8000`, `X-1`, `X+1`, cada uno enviado dos veces | ~0,65 s |
| 10 | Phantom / Hiland | 2 códigos con tu botón: los absolutos `0xFFFE` y `0xFFFF`, cada uno enviado tres veces | ~0,4 s |

::: warning El modo 7 ha cambiado
El modo 8 es exactamente lo que hacía `CounterMode: 7` en versiones anteriores. Si tienes un fichero con
`CounterMode: 7` que funcionaba, cámbialo a `CounterMode: 8`.
:::

Detalles:

- En los paquetes largos (7 y 8) cada código sale **una vez** (el clon original envía cada uno dos o tres veces):
  el paquete completo se construye en memoria, y triplicarlo necesitaría 20 KB en lugar de 8 KB. Reenviar el
  paquete no es un sustituto: un receptor que ya se ha resincronizado interpreta una segunda pasada como un nuevo
  recorrido y vuelve a accionar la cancela, mientras que una repetición inmediata de un mismo código se ignora como
  duplicado.
- El modo 10 ignora el contador de tu fichero. Al no haber recorrido, una sola pulsación resincroniza un receptor
  que tenga cualquier valor en los 32768 inferiores a `0xFFFE`, que es donde se sitúa un receptor que se ha
  adelantado a tu mando. Si no funciona, envíalo una vez más.
- **Mantener** Send repite el paquete mientras lo sostengas; un receptor que se resincronizó en la primera pasada
  lo interpreta como otra pulsación. Volver a pulsar Send mientras se está enviando un paquete lo **aborta**.

### V2 Phoenix (Phox)

| Modo | Contador | Notas |
|---|---|---|
| 0 | +multiplicador | por defecto |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` («estilo ofex») | verificado como funcional |
| 2 | `0x0000 … 0x0004` | puede que funcione |

## Ejemplo: KeeLoq DoorHan con +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Resolución de problemas y preguntas frecuentes

- **El fichero no funciona después de añadir `CounterMode`**: comprueba la sintaxis `CounterMode: X` (espacio
  después de los dos puntos) y que el número sea válido para el protocolo.
- **¿Número de modo inválido?** Se usa el último modo de la lista del protocolo.
- **¿Hace falta en todos los ficheros?** No. Sin `CounterMode` se usa el modo 0.
- **¿Puede dañar mi mando o mi receptor?** Puede desincronizar tu mando, según el receptor. No lo uses si no puedes
  volver a emparejar el original.
- **¿Qué modo debo usar?** Si no estás seguro, ninguno. Es preferible crear un [mando nuevo](/es/subghz/add-manually).

## Relacionado

- [Signal Settings](/es/subghz/signal-settings) — fijar un modo, el contador y el botón en el Flipper
- [Códigos rodantes](/es/subghz/rolling-codes) · [KeeLoq](/es/subghz/keeloq)
- [Radio Settings: Counter Incr.](/es/subghz/settings) · [Formato de fichero .sub](/es/subghz/file-format)
