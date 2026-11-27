---
title: Sub-GHz RAW Edit
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/subghz_raw_editor, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/Lechnio/SubGHz-RAW-Edit]
sources: [unleashed-src, unleashed-readme]
---
# Sub-GHz RAW Edit

**Sub-GHz RAW Edit** (de Lechnio) es un pequeño editor de formas de onda, en el propio aparato, para capturas RAW `.sub`. Una grabación de [Read RAW](/es/subghz/read-raw) suele contener segundos de ruido alrededor de la ráfaga corta que te interesa. Con RAW Edit localizas la señal real, la marcas y guardas solo esa parte; además puedes unir varios ficheros, cortar trozos y decodificar una selección con los decodificadores Sub-GHz del firmware.

::: tip Unleashed
RAW Edit viene con Unleashed como aplicación de sistema, y la aplicación Sub-GHz la abre directamente: `Sub-GHz → Read RAW` (o `Saved`) → abre un fichero RAW → <kbd>→</kbd> `More` → `Edit`. El elemento `Edit` solo se muestra cuando RAW Edit está instalado. Al salir del editor vuelves a Sub-GHz.
:::

**Cuándo usarlo:** recortar una captura RAW larga antes de compartirla o enviarla, separar una grabación en botones individuales, pegar varias capturas, o averiguar qué protocolo se esconde dentro de un fichero RAW.

## Menú principal

`Main Menu → Apps → Sub-GHz → Sub-GHz RAW Edit`:

- `Select .sub file`: abrir en el editor un fichero de `/ext/subghz`
- `Merge .sub files`: unir varios ficheros en uno
- `Config`: opciones de carga y de unión
- `About`: versión y enlace al proyecto

Además de ficheros RAW, la aplicación puede cargar cualquier señal que el firmware sea capaz de codificar (se convierte a RAW mediante el codificador interno). Para los protocolos con botones personalizados ofrece primero un selector de botón.

## El editor

La pantalla muestra la forma de onda con una barra de vista general en la parte superior, y dos líneas debajo: `View:` (zoom) y `Marked:` (longitud de la selección A..B). El rango seleccionado se resalta con una línea de puntos; unas pequeñas marcas indican que hay más señal más allá del borde de la pantalla.

| Botón | Acción |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | mover el marcador activo (A o B); mantener para moverlo más rápido |
| <kbd>↑</kbd> / <kbd>↓</kbd> | acercar / alejar el zoom |
| <kbd>OK</kbd> | cambiar el marcador activo entre A y B |
| mantener <kbd>OK</kbd> | abrir el menú de acciones |
| <kbd>Back</kbd> | cerrar el editor |

El menú de acciones (<kbd>↑</kbd> / <kbd>↓</kbd>, <kbd>OK</kbd> para ejecutar, <kbd>Back</kbd> para cerrar) aparece a la izquierda, con un panel informativo de solo lectura al lado que muestra el número de muestras de A..B, `TE` y la codificación de línea detectada (`PWM`, `PPM`, `Manchester`, `NRZ` o `1:1`):

- **Save**: escribe solo el rango A..B en un fichero RAW nuevo. El nombre se propone como `<nombre>_edit1`, `_edit2`, … Guardar con un nombre existente pregunta `Name exists, overwrite?`; el fichero abierto nunca se sobrescribe.
- **Decode**: decodifica el rango A..B con los decodificadores Sub-GHz del firmware (probando cada fabricante en cada trama KeeLoq; omite BinRAW), agrupa las tramas idénticas (`Decoded: N`) y guarda la elegida como fichero de clave, nombrado por defecto según el protocolo y el fabricante (por ejemplo `KeeLoq_Verex`). Cada entrada decodificada tiene también un botón **Locate** que ajusta A..B sobre su trama (la primera si se repite). `No known protocol` significa que no se ha decodificado nada.
- **Cut** / **Copy** / **Paste**: pulsa <kbd>←</kbd> / <kbd>→</kbd> sobre `Cut` para alternar entre **Cut** (elimina A..B y lo coloca en el portapapeles; se rechaza si dejaría la señal vacía), **Copy** (copia A..B al fichero del portapapeles) y **Paste** (inserta el portapapeles en el marcador activo y lo selecciona).
- **Undo**: historial respaldado en la SD de los últimos **32** cortes y pegados (no consume RAM). Cuando hay más de una edición, las lista de la más reciente a la más antigua con el número de muestras y las posiciones, y revierte hasta antes de la que elijas. Aparece tachado cuando no hay nada que deshacer.

## Recortar una captura, paso a paso

1. Graba el mando en [Read RAW](/es/subghz/read-raw) y guárdalo.
2. Ábrelo en RAW Edit (mediante `More → Edit` o `Select .sub file`).
3. Aleja el zoom con <kbd>↓</kbd> para ver dónde están las ráfagas.
4. Mueve el marcador **A** hasta justo antes de la ráfaga con <kbd>←</kbd>/<kbd>→</kbd>, pulsa <kbd>OK</kbd> y mueve el marcador **B** hasta justo después de ella.
5. Mantén <kbd>OK</kbd> → `Save`, y acepta o edita el nombre.
6. Prueba el fichero guardado desde `Sub-GHz → Saved`.

## Unir ficheros

1. `Merge .sub files` → elige un fichero; el diálogo muestra `Added N file(s)` y el número de muestras. Elige `Add more` o `Done`.
2. Todos los ficheros deben estar en la misma frecuencia; si no, obtendrás `Frequency mismatch`.
3. El resultado se abre en el editor como `merged`; guárdalo desde el menú de acciones.

## Config

| Elemento | Qué hace |
|---|---|
| Normalize jitter | `OFF`/`ON`: limpia la fluctuación y la deriva de las temporizaciones al cargar |
| Merge gap | silencio insertado entre los ficheros unidos, 0–1000 ms (por defecto 100); <kbd>OK</kbd> abre un campo numérico |
| Repeat | repite cada señal cargada o unida de 1 a 64 veces |

Una línea de solo lectura al final de `Config` muestra también si los botones personalizados y la conservación del contador rodante están disponibles en la compilación actual del firmware.

## Límites y resolución de problemas

- **Sin límite de longitud (v2.0):** las señales y las uniones se mantienen en un fichero de trabajo en la tarjeta SD, mientras que la RAM guarda una ventana deslizante de la captura (hasta ~38 000 muestras tras reiniciar), dejando espacio para Decode y Save. Empujar el marcador A o B más allá del borde de la ventana la desliza un cuarto más allá; alejar el zoom se detiene en el límite de la ventana con `No RAM to zoom out`.
- **Aviso `Low RAM`**: se muestra cuando en la RAM libre caben menos de 15 000 muestras de una señal más grande; ofrece `Reboot` o `Continue`. `Decode` también comprueba si hay ~8 KB de RAM libre e informa `Low memory` en lugar de colgarse.
- `Unsupported protocol or file is empty`: el fichero no es una señal que el firmware pueda codificar.
- `Nothing in A..B` / `Range too small`: separa más los marcadores.
- Los silencios largos se conservan con su longitud real en el fichero guardado.

## Páginas relacionadas

- [Read RAW](/es/subghz/read-raw) · [Formato de fichero](/es/subghz/file-format)
- [Remote Analyzer](/es/subghz/remote-analyzer)
