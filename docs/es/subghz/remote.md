---
title: Aplicación Sub-GHz Remote
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** convierte el Flipper en un mando de cinco botones. Asignas hasta cinco ficheros `.sub` guardados a <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> y <kbd>OK</kbd>, le pones una etiqueta a cada uno y los envías con una pulsación, sin pasar por `Sub-GHz → Saved`.

::: tip Unleashed
Sub-GHz Remote viene integrada en Unleashed y está en el **menú principal**: `Main Menu → Sub-GHz Remote`. La escribieron @gid9798 y @xMasterX, y su código vive en un repositorio aparte, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), incluido en el firmware como submódulo. El firmware de serie no la tiene en el menú; para el firmware oficial hay una build aparte en el catálogo de aplicaciones.
:::

## Cuándo usarla {#when-to-use}

- Usas unas pocas señales constantemente, por ejemplo una cancela, una puerta de garaje y una barrera, y las quieres a una pulsación.
- Controlas varios aparatos (ventilador, luces, timbre) y los quieres en una pantalla con etiquetas legibles.

Cada botón envía un fichero `.sub` normal, así que todo lo que funciona desde `Sub-GHz → Saved → Emulate` funciona aquí: claves estáticas, mandos de código rodante creados con [Add Manually](/es/subghz/add-manually), grabaciones RAW y BinRAW. Los protocolos que el Flipper solo sabe recibir no se pueden asignar.

## El menú {#menu}

La aplicación abre directamente el explorador de ficheros de mapa. Pulsa <kbd>Back</kbd> para llegar al menú:

| Opción | Qué hace |
|---|---|
| `Open Map File` | elige un mapa y va a la pantalla del mando |
| `Edit Map File` | elige un mapa y lo abre en el editor |
| `New Map File` | escribe un nombre y crea un mapa nuevo |
| `Set Default` | elige el mapa que la aplicación abrirá sola a partir de ahora |
| `Clear Default` | olvida ese mapa (solo aparece si hay uno fijado) |

Los mapas son ficheros `.txt` en la carpeta `subghz_remote` de la tarjeta SD. El nombre del fichero da igual y puedes guardar tantos mapas como quieras. Si tienes una carpeta `unirf` antigua de versiones anteriores, la aplicación la mueve a `subghz_remote` la primera vez que arranca.

## Crear un mapa en el Flipper {#builtin-editor}

La aplicación trae un editor, así que no necesitas un PC.

1. Guarda primero las señales que quieras, con [Read](/es/subghz/read), [Read RAW](/es/subghz/read-raw) o [Add Manually](/es/subghz/add-manually).
2. Abre `Main Menu → Sub-GHz Remote`, pulsa <kbd>Back</kbd> y elige `New Map File`.
3. Escribe un nombre, hasta 25 caracteres. El mapa se guarda como `/ext/subghz_remote/<nombre>.txt`.
4. El editor se abre en la ranura `UP`.

| Tecla en el editor | Qué hace |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | moverse entre las cinco ranuras: `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — abre el menú de la ranura |
| <kbd>→</kbd> | `Save` — pasa a la vista previa |
| <kbd>←</kbd> o <kbd>Back</kbd> | `Back` |

La barra de arriba muestra el nombre de la ranura y su etiqueta. Debajo ves la ruta del fichero asignado, o `Button not set` si la ranura está vacía, o `ERR:` con el motivo: `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

El menú de la ranura tiene cuatro opciones:

- `Edit Label` — el texto que se muestra para este botón. Hasta 25 caracteres, de los que en la pantalla del mando entran unos 16. Se admite una etiqueta vacía, la aplicación pregunta antes `Empty Label Name / Continue?`; sin etiqueta se muestra el nombre del fichero.
- `Edit File` — un explorador de ficheros `.sub` que empieza en `/ext/subghz`. Si el fichero no sirve, sale un aviso `ERROR` con `Bad frequency`, `Bad modulation` o `Unsupported protocol`, y la ranura se queda con lo que tenía.
- `Button` — qué botón del mando envía esta ranura: `Default`, `Up`, `Down`, `Left`, `Right`. Mira [Botones del mando](#custom-buttons).
- `Clear Slot` — vacía la ranura.

Cuando termines pulsa <kbd>→</kbd>. La vista previa enseña el mando montado, con `Back` a la izquierda y `Save` a la derecha; <kbd>→</kbd> u <kbd>OK</kbd> escribe el fichero y aparece una pantalla `Saved!`. Si sales del editor con cambios sin guardar, primero te pregunta `Changes are not saved / do you want to exit?`.

No pasa nada por dejar ranuras vacías. Un mapa con un solo botón funciona.

## Enviar {#sending}

Elige `Open Map File` y tu mapa. Esta pantalla está dibujada de lado, así que sujeta el Flipper en vertical.

- **Mantén pulsada** una tecla para transmitir. Esa fila se pone en negro y el LED parpadea en magenta.
- Al soltarla, el protocolo manda las repeticiones que le quedan y para. Un fichero RAW se reproduce hasta el final de la grabación y vuelve a empezar si sigues con la tecla pulsada.
- Debajo de las cinco filas la aplicación muestra lo que está enviando: nombre del protocolo, frecuencia y modulación, `Key:` (solo para claves de 32 bits o menos), `Sn:` o `Fix:`, `Cnt:`, `MF:`. Caben cinco líneas como mucho.
- El icono de la esquina superior izquierda indica si se usa la radio interna o un [módulo externo](/es/subghz/external-cc1101).
- <kbd>Back</kbd> corta una transmisión en marcha. Púlsalo otra vez para salir de la aplicación.

Una ranura cuyo fichero no se ha podido cargar muestra `[X] Can't open file` o `[X] Error in .sub file` en vez de su etiqueta. Las ranuras vacías se quedan en blanco, y al pulsarlas el LED parpadea en rojo.

## Botones del mando {#custom-buttons}

Un mando de código rodante tiene varios botones, y un fichero `.sub` guarda uno de ellos. `Button`, en el menú de la ranura, elige cuál envía esta ranura. `Default` deja el botón del fichero; `Up`, `Down`, `Left` y `Right` envían los otros botones del mismo mando, los mismos que salen con esas teclas en `Sub-GHz → Saved → Emulate`. El editor añade entonces `(Btn. Up)` después de la ruta.

El contador avanza una pulsación, y la aplicación devuelve el botón original al terminar la transmisión.

Así es como le das su propia ranura a un botón oculto o de programación. Qué flecha corresponde a cada botón depende del protocolo, mira [El Flipper como mando nuevo](/es/subghz/remote-prog).

## El fichero de mapa {#map-file}

El editor escribe un fichero de texto plano en el formato de Flipper:

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` son las rutas completas de los ficheros `.sub` asignados a cada dirección del pad.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` son los textos que se ven en pantalla para esos botones.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` son el botón personalizado, en hexadecimal: `00` por defecto, `01` arriba, `02` abajo, `03` izquierda, `04` derecha. El editor omite la línea cuando la ranura usa `Default`.

También puedes escribir un mapa en el PC. Si lo haces:

- Separa la clave del valor con dos puntos y **un** espacio, exactamente como arriba.
- El orden de las líneas da igual, la aplicación busca cada clave por su nombre. Una clave que falte cuenta como vacía.
- El **nombre de fichero** de un `.sub` tiene que ser ASCII imprimible y no puede llevar `\ < > * | " : ?`. Un nombre en cirílico o un emoji hace que esa ranura no cargue.
- Deja las etiquetas en unos 16 caracteres. Las más largas se cortan en la pantalla estrecha del mando.

El editor integrado no puede generar un mapa roto, así que mejor úsalo a él.

## Abrir un mapa al arrancar {#default-map}

`Set Default` guarda el mapa elegido en `/ext/subghz_remote/.config`. A partir de ahí la aplicación va directa a la pantalla del mando al abrirla, y <kbd>Back</kbd> te lleva al menú. `Clear Default` borra ese fichero.

La aplicación también acepta la ruta de un fichero de mapa como argumento de arranque, así que otra aplicación puede abrir un mando concreto.

## Si no funciona {#troubleshooting}

- **`[X] Can't open file`**: el fichero `.sub` al que apunta esa ranura se movió, se renombró o se borró. Vuelve a elegirlo con `Edit File`, o corrige la ruta en el mapa.
- **`[X] Error in .sub file`**: el fichero carga pero no se puede enviar. El editor dice por qué: `Bad frequency` (la radio que tienes seleccionada no admite esa frecuencia, mira [Frecuencias y alcance](/es/subghz/frequencies)), `Bad modulation`, o `Unsupported protocol` (el protocolo es solo de recepción).
- **Un botón no hace nada** y el LED parpadea en rojo: esa ranura está vacía o su fichero no se cargó.
- **Un mando de código rodante ha dejado de funcionar** después de usar el Flipper y el original: es un conflicto de contadores, no un fallo de la aplicación. Mira [Códigos rodantes](/es/subghz/rolling-codes) y crea un mando nuevo con [El Flipper como mando nuevo](/es/subghz/remote-prog).
- **Aviso `Not official FW` al arrancar**: has instalado la build del catálogo pensada para el firmware oficial. Usa la Sub-GHz Remote que ya está en el menú principal de Unleashed.
- Las guías antiguas hablan de una pantalla `Config is incorrect. Please configure map.`. La aplicación actual no la muestra: marca los botones rotos en la pantalla del mando.

## Páginas relacionadas {#related}

- [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw) · [Add Manually](/es/subghz/add-manually)
- [El Flipper como mando nuevo](/es/subghz/remote-prog)
- [Formato de fichero .sub](/es/subghz/file-format)
