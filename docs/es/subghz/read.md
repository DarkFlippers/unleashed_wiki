---
title: Read
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read

**Read** escucha en una frecuencia (o salta entre varias), **decodifica** las señales de protocolos conocidos y las
muestra en una lista. Una señal decodificada puede guardarse como fichero de clave y volverse a enviar. Es la forma
principal de copiar un mando con **código estático (fijo)** — cancelas, barreras, timbres, enchufes — y de
identificar qué protocolo usa un mando.

Para los mandos que Read no reconoce, usa [Read RAW](/es/subghz/read-raw). Para mandos de código rodante lee
[Códigos rodantes](/es/subghz/rolling-codes) **antes** de enviar nada.

::: tip Unleashed
Frente al firmware original, Unleashed añade: decenas de protocolos adicionales
([lista completa](/es/subghz/supported-systems)), el guardado y el envío de muchos protocolos de **código rodante**,
**botones personalizados** con las teclas de flecha al enviar, salto de frecuencia con umbral de RSSI, filtros
`Ignore …`, `Delete old signals when memory is full`, **mantener <kbd>→</kbd> para borrar** una señal de la lista,
la hora de recepción de cada señal y el recuerdo de los últimos ajustes.
:::

## Leer un mando

1. Averigua primero la frecuencia si no la conoces: [Frequency Analyzer](/es/subghz/frequency-analyzer)
   (una pulsación larga de <kbd>OK</kbd> allí salta directamente a Read en la frecuencia encontrada).
2. Abre `Main Menu → Sub-GHz → Read`. La pantalla muestra `Fixed scan...` (o `Hopper scan...` con el salto
   activado), y la frecuencia y la modulación actuales en la parte inferior.

   ![Pantalla de Read esperando una señal: Fixed scan en 433.92 MHz, AM650](/screens/subghz/read.png)

3. Sujeta el mando cerca del lado izquierdo del Flipper y pulsa su botón durante 1–2 segundos.
4. La señal decodificada aparece en la lista como `nombre del protocolo` + hora de recepción. El contador de la
   parte inferior indica cuántas señales hay en la lista.

   ![Lista de Read con tres señales recibidas: Princeton, CAME 12bit y KL: DoorHan](/screens/subghz/read_list.png)

5. Selecciónala con <kbd>↑</kbd> <kbd>↓</kbd> y pulsa <kbd>OK</kbd> para ver los detalles (clave, número de bits,
   serial, botón, contador, fabricante en el caso de KeeLoq, etc.).

   ![Detalles de la señal: Princeton 24bit con clave, serial y botón, y los botones Send y Save](/screens/subghz/signal_info.png)

6. Pulsa <kbd>→</kbd> **Save**, escribe un nombre y confirma. El fichero va a `/ext/subghz/`.
7. O pulsa <kbd>OK</kbd> **Send** para transmitirla de inmediato.

Las señales guardadas están en `Main Menu → Sub-GHz → Saved` (véase [más abajo](#saved-signals)).

## Botones en la pantalla de Read

| Botón | Acción |
|---|---|
| <kbd>←</kbd> | **Config** — ajustes del receptor |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Moverse por la lista de señales recibidas |
| <kbd>OK</kbd> | Abrir la señal seleccionada |
| mantener <kbd>→</kbd> | Borrar de la lista la señal seleccionada |
| <kbd>Back</kbd> | Salir de Read. Si hay señales sin guardar aparece **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

La lista admite hasta 128 señales (menos con capturas BinRAW grandes, según la memoria libre).

## Config {#config}

Pulsa <kbd>←</kbd> **Config** en la pantalla de Read:

![Menú Config de Read: Frequency, Modulation, Hopping y Bin RAW](/screens/subghz/read_config.png)

| Elemento | Valores | Qué hace |
|---|---|---|
| `Frequency` | lista de [Frecuencias](/es/subghz/frequencies) | Frecuencia fija de recepción. Muestra ` -----` mientras el salto está activado |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + presets personalizados | Preset de demodulación. `AM650` encaja con la mayoría de los mandos |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Recorre la lista del hopper (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). El valor es el nivel de RSSI que detiene el salto en una frecuencia |
| `Bin RAW` | `OFF` / `ON` | Recoge también las señales estáticas desconocidas como **BinRAW** (patrón repetitivo con la tasa de bits restaurada). Mantén el botón del mando algo más de tiempo para acumular datos suficientes |
| `Ignore ReversRB2` | `OFF` / `ON` | Oculta las señales Revers RB-2(M) |
| `Ignore Alarms` | `OFF` / `ON` | Oculta los protocolos de alarmas de bicicleta y moto (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Oculta sensores y parloteo similar: Magellan, Honeywell, Honeywell WDB y los timbres Legrand, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Oculta Princeton (PT2262 y clones); útil donde los mandos baratos saturan el aire |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Oculta Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | Cuando la lista se llena, descarta las señales más antiguas en lugar de detenerse. El contador muestra entonces `!` |
| `Sound` | `OFF` / `ON` | Reproduce por el altavoz todo lo que recibe la radio |
| `Reset to default` | — | Vuelve a 433.92 MHz AM650, salto desactivado, todos los filtros desactivados, Bin RAW desactivado, potencia de TX en `Preset` |
| `Lock Keyboard` | — | Bloquea los botones mientras escanea (en un bolsillo). **Desbloqueo: pulsa <kbd>Back</kbd> tres veces** |

Todos los ajustes de Read se guardan y se restauran la próxima vez que abres la aplicación.

::: tip Qué valor de salto elegir
Con `Hopping` activado, el receptor se queda en una frecuencia solo cuando la señal supera el nivel elegido.
`-90dBm` es el más sensible; súbelo si el ruido detiene el salto constantemente. Para una recepción fiable es
preferible una **frecuencia fija** localizada con el analizador: las señales enviadas durante un cambio de
frecuencia se pierden.
:::

## Enviar una señal

Abre la señal (desde la lista de Read o desde `Saved → <fichero> → Emulate`). La pantalla de transmisión muestra los
datos de la clave, la frecuencia, la modulación y `R: Int` / `R: Ext` (qué radio va a transmitir).

- **Mantén** <kbd>OK</kbd> (**Send**): el Flipper transmite **solo mientras el botón esté pulsado**. Un toque rápido
  puede enviar un código incompleto; mantenlo 1–2 s (CAME Atomo necesita al menos 2 s).
- <kbd>Back</kbd>: salir.

### Botones personalizados (Unleashed)

::: tip Unleashed
En muchos protocolos las teclas de flecha envían el **mismo mando con otro código de botón**, así que un único
fichero guardado se comporta como el mando completo. Entre los protocolos compatibles están: KeeLoq, Alutech AT-4N,
Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0, CAME Atomo, FAAC SLH, BelKorn, Beninca ARC, Ditec GOL4, Jarolift,
KingGates Stylo 4k, V2 Phoenix, Prastel, Roger, Nord ICE, Princeton, Proteco, Dooya, Hay21, GangQi, Hollarm.
Mientras se mantiene una flecha, el código de botón enviado se muestra en el borde derecho de la pantalla. Qué
flecha corresponde a qué botón depende del protocolo; véase
[Códigos rodantes](/es/subghz/rolling-codes) y [Programar un mando nuevo](/es/subghz/remote-prog).
:::

## Señales guardadas {#saved-signals}

`Main Menu → Sub-GHz → Saved` lista los ficheros de `/ext/subghz/`. Elige uno y obtendrás:

- `Emulate`: abre la pantalla de transmisión;
- `Rename`;
- `Delete`;
- `Signal Settings`: **solo en modo depuración** (`Settings → System → Debug`); cambia `Counter Mode`,
  `Edit Counter` y `Edit Button` de un fichero de código rodante. Véase
  [Modos de contador](/es/subghz/counter-mode).

Los ficheros RAW se abren en la pantalla de Read RAW; véase [Read RAW](/es/subghz/read-raw#playback).

Los nombres de fichero se generan automáticamente (fecha y hora) a menos que `Protocol Names` esté activado en
[Radio Settings](/es/subghz/settings); entonces el nombre del protocolo se coloca delante de la marca de tiempo.

## Códigos estáticos frente a rodantes

- **Código estático** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…): cada pulsación envía el
  mismo código. Una copia guardada funciona indefinidamente junto al original.
- **Código rodante (dinámico)** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…): cada pulsación lleva
  un valor de contador nuevo. Unleashed puede guardar y enviar muchos de ellos, **pero enviar una copia
  desincroniza el mando original**. Lee [Códigos rodantes](/es/subghz/rolling-codes) y usa preferentemente
  [Add Manually](/es/subghz/add-manually) para crear un mando *nuevo*.

::: danger Llaves de coche
No experimentes con la llave de tu coche. Reproducir un mando de coche (Read o Read RAW) puede desincronizarlo o
dejarlo en lista negra, y volver a emparejarlo suele requerir herramientas de concesionario. Usa el Flipper
únicamente con tus propios equipos y para investigación lícita.
:::

## Resolución de problemas

- **No aparece nada**: frecuencia o modulación equivocadas. Usa el analizador, prueba `AM650` y después
  `FM238`/`FM476`/`FM12K`. Comprueba que ningún filtro `Ignore …` esté ocultando el protocolo.
- **La señal se recibe pero no se decodifica**: el protocolo es desconocido; activa `Bin RAW` (mandos estáticos) o
  grábala con [Read RAW](/es/subghz/read-raw). Prueba también la aplicación
  [Remote Analyzer](/es/subghz/remote-analyzer).
- **KeeLoq muestra el fabricante `Unknown`**: la clave de fabricante no está en la base de datos, o el mando
  necesita una semilla (BFT, Erreka, FAAC SLH). Véase [KeeLoq](/es/subghz/keeloq) y
  [Seed Capturer](/es/subghz/seed-capturer).
- **No hay botón `Send`**: el protocolo es solo de decodificación (por ejemplo iDo), o se trata de un paquete Nice
  O-Code sin código de instalador (usa la aplicación [Nice O-Code](/es/subghz/nice-o-code)).
- **La lista se llena de ruido**: activa las opciones `Ignore` pertinentes o
  `Delete old signals when memory is full`.

## Relacionado

- [Read RAW](/es/subghz/read-raw) · [Frequency Analyzer](/es/subghz/frequency-analyzer) · [Sistemas compatibles](/es/subghz/supported-systems)
- [Códigos rodantes](/es/subghz/rolling-codes) · [Add Manually](/es/subghz/add-manually) · [Radio Settings](/es/subghz/settings) · [Formatos de fichero](/es/subghz/file-format)
