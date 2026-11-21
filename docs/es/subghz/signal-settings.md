---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** edita una señal que ya has guardado: su modo de contador, su contador rodante actual y su código
de botón. Es una pantalla pequeña para usuarios avanzados, oculta mientras Debug esté desactivado, y casi todo lo que
hace funciona solo con los pocos protocolos que admiten [modos de contador](/es/subghz/counter-mode).

## Dónde está {#where}

Es un elemento del menú de una señal guardada, no una entrada del menú principal de Sub-GHz. Abre un fichero desde
`Sub-GHz → Saved` (o desde el [Archive](/es/apps/archive)) y el menú es:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Cómo hacer que aparezca {#enable}

`Signal Settings` se añade a ese menú solo mientras **Debug** está activado. Con Debug desactivado no aparece.

- Vía rápida: mantén <kbd>↓</kbd> en el escritorio y después mantén <kbd>OK</kbd> en la pantalla informativa
  ([Escritorio → Pantalla de información del dispositivo](/es/start/desktop#info-screen)).
- O bien `Settings → System → Debug` = `ON` ([Ajustes](/es/start/settings)).

## Los tres elementos {#items}

![Signal Settings: Counter Mode, Edit Counter y Edit Button](/screens/subghz/signal_settings.png)

| Elemento | Qué hace |
|---|---|
| `Counter Mode` | con <kbd>←</kbd>/<kbd>→</kbd> eliges `System` (modo 0) o `Mode 1` … hasta el límite del protocolo. La elección se escribe de inmediato en el fichero `.sub` como una línea `CounterMode:` y el fichero se recarga; no se transmite nada |
| `Edit Counter` | <kbd>OK</kbd> abre una entrada hexadecimal del contador actual, encabezada `Enter <N>-bits counter in HEX` con la longitud de contador del protocolo: 4 dígitos hexadecimales (2 bytes) hasta 16 bits, 8 dígitos (4 bytes) por encima |
| `Edit Button` | <kbd>OK</kbd> abre una entrada hexadecimal del código de botón, encabezada `Enter <N>-bits button in HEX`: siempre un byte, 2 dígitos hexadecimales |

El valor que tiene cada elemento en ese momento se muestra en su fila, en hexadecimal. Lo que los modos de contador
le hacen al contador, y cómo fijar uno editando el fichero en un PC en su lugar, está en
[Modos de contador](/es/subghz/counter-mode#modes-by-protocol).

::: warning Confirmar una edición de contador o de botón transmite
`Edit Counter` y `Edit Button` escriben el fichero ejecutando la ruta de transmisión: el firmware inicia un envío
con el valor nuevo y lo detiene de inmediato, y el fichero se reescribe cuando ese envío se detiene. La radio se
activa un instante, así que hazlo lejos del receptor que no quieras accionar.

El contador que escribes se guarda exactamente tal y como lo escribes: para esa reescritura se omiten el modo de
contador y el paso de [Counter Incr.](/es/subghz/settings). Una edición de botón, en cambio, pone el paso a 0 para
la reescritura, así que cambiar el botón deja el contador donde estaba.

Si el envío se rechaza (una frecuencia en la que este firmware no transmite), el fichero no se escribe en absoluto.
:::

## Protocolos con modos de contador {#protocols}

`Counter Mode` está disponible en cinco protocolos. `System` es el modo 0, el normal:

| Protocolo | Opciones |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

La comparación se hace con la línea `Protocol:` del fichero. En cualquier otro protocolo el elemento está bloqueado.

## Elementos bloqueados {#locked}

Un elemento bloqueado no se puede abrir ni cambiar; al pulsarlo aparece `Not available for this protocol !`

- `Counter Mode`: el protocolo del fichero no es ninguno de los cinco de arriba.
- `Edit Counter`: el protocolo no tiene contador. También puede depender del fabricante: en KeeLoq el elemento está
  bloqueado para `AN-Motors`, que solo tiene un pseudocontador, y para `Unknown`.
- `Edit Button`: el protocolo no tiene código de botón en su trama.

`Edit Button` también está desbloqueado en los protocolos estáticos que llevan código de botón — Princeton, Dooya,
GangQi, Hollarm, Nord ICE, Proteco y Roger — y ahí funciona igual que en una señal de código rodante.

## Relacionado {#related}

- [Modos de contador](/es/subghz/counter-mode): qué hace cada modo y la línea `CounterMode:` del fichero
- [Códigos rodantes](/es/subghz/rolling-codes) · [Formato de fichero .sub](/es/subghz/file-format)
- [Escritorio](/es/start/desktop#info-screen): el atajo de Debug · [Ajustes](/es/start/settings): Debug en los menús
