---
title: Read RAW
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** graba la señal demodulada «tal cual», sin decodificarla, como una grabadora de voz. La grabación se
puede reproducir, guardar, decodificar más tarde o editar. Úsalo cuando:

- **Read** no reconozca el mando (protocolo desconocido);
- quieras capturar una señal para analizarla o para comunicar un protocolo nuevo a los desarrolladores;
- necesites reproducir con exactitud una señal estática cuyo protocolo el Flipper no conoce.

La grabación se sigue haciendo con la **frecuencia y la modulación** seleccionadas: el Flipper no es un SDR. Una
modulación equivocada te da una grabación de ruido.

::: warning Códigos rodantes
Reproducir en RAW un mando de código rodante es exactamente igual que clonarlo: adelanta el contador del receptor y
puede desincronizar tu original. **No lo hagas nunca con la llave de un coche**, porque puede acabar en lista negra.
Detalles: [Códigos rodantes](/es/subghz/rolling-codes).
:::

## Grabar

1. Localiza la frecuencia con el [Frequency Analyzer](/es/subghz/frequency-analyzer) si no la conoces.
2. Abre `Main Menu → Sub-GHz → Read RAW`.
3. Pulsa <kbd>←</kbd> **Config** y ajusta `Frequency`, `Modulation` y `RSSI Threshold:` (véase más abajo). Pulsa
   <kbd>Back</kbd> para volver.

   ![Read RAW listo para grabar: forma de onda vacía, botones Config y REC](/screens/subghz/read_raw.png)

4. Pulsa <kbd>OK</kbd> **REC**. La forma de onda empieza a desplazarse y el RSSI se muestra a la derecha.
5. Pulsa el botón del mando (manténlo 1–2 s).

   ![Read RAW grabando: dos ráfagas de señal en la forma de onda, contador de muestras y botón Stop](/screens/subghz/read_raw_recording.png)

6. Pulsa <kbd>OK</kbd> **Stop**.
7. Ahora tienes tres opciones:
   - <kbd>←</kbd> **Erase**: descartar y empezar de nuevo;
   - <kbd>OK</kbd> **Send**: reproducir la grabación (manténlo pulsado para repetirla);
   - <kbd>→</kbd> **Save**: escribir un nombre (por defecto `RAW_<fecha-hora>`) y guardarla en `/ext/subghz/`.

## Config en Read RAW

El menú de configuración de RAW es más corto que el de Read:

| Elemento | Valores | Significado |
|---|---|---|
| `Frequency` | lista de frecuencias | Frecuencia de recepción |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + personalizados | Preset de demodulación |
| `Sound` | `OFF` / `ON` | Reproduce la señal recibida por el altavoz |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | Graba solo mientras la señal esté por encima de este nivel. `-----` = grabar todo |

::: tip Cuándo usar el umbral
Con un umbral, el fichero contiene solo las ráfagas de tu mando y no segundos de ruido entre pulsaciones: los
ficheros son mucho más pequeños y limpios. Para capturas que vayas a enviar a los desarrolladores, déjalo en
`-----` (grabación completa).
:::

## Reproducir un RAW guardado {#playback}

1. `Main Menu → Sub-GHz → Saved` y selecciona el fichero RAW. Se abre en la pantalla de Read RAW.
2. <kbd>OK</kbd> **Send**: envía la grabación completa una vez; mantén <kbd>OK</kbd> pulsado para repetirla
   (**Hold to repeat**).
3. <kbd>←</kbd> **New**: iniciar una grabación nueva.
4. <kbd>→</kbd> **More**:
   - `Decode`: pasa la grabación por todos los decodificadores de la aplicación Sub-GHz; las señales encontradas se
     pueden guardar como ficheros de clave normales;
   - `Edit`: abre el fichero en la aplicación [Sub-GHz RAW Edit](/es/subghz/raw-editor) (solo se muestra cuando esa
     aplicación está instalada en una versión compatible); Sub-GHz se vuelve a abrir al salir del editor;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` y `More → Edit` son aportaciones de Unleashed. Con `Edit` puedes localizar la señal real en una
captura ruidosa, recortarla, unir ficheros y decodificar solo una selección.
:::

Los ficheros RAW largos y densos se transmiten en streaming desde la tarjeta SD mientras se envían. Si intervienen
pulsos muy cortos (por debajo de 10 µs) y la tarjeta es lenta, la transmisión puede detenerse antes del final del
fichero: usa una tarjeta buena.

## Grabar un mando para solicitar un protocolo

Este es el procedimiento que piden los desarrolladores de Unleashed cuando quieres que se admita un protocolo nuevo:

1. Localiza la frecuencia con el analizador. En Read prueba `AM650`, `FM238`, `FM476`, `FM12K`; si no se decodifica
   nada, continúa.
2. En Read RAW fija esa frecuencia y **`RSSI Threshold: -----`**.
3. Haz **un RAW por modulación**: `AM650`, `FM238`, `FM476`, `FM12K`.
4. Para cada uno: pulsa **REC**, después pulsa un botón del mando **5 veces manteniéndolo 1–2 s** y luego **5 veces
   manteniéndolo unos 5 s**. Detén y guarda.
5. Si el mando tiene varios botones, graba cada botón de la misma forma. Nombra cada fichero según el botón.
6. Copia los ficheros a un PC, comprímelos en un zip y abre una issue en el repositorio del firmware. Añade buenas
   fotos del mando (también por dentro, si es posible), el modelo y el fabricante.

## Resolución de problemas

- **La grabación está plana o solo tiene ruido**: frecuencia o modulación incorrectas, o el mando está demasiado
  lejos. Sujétalo cerca.
- **Ficheros enormes**: fija un `RSSI Threshold`.
- **La reproducción no funciona**: el mando usa código rodante (el receptor rechaza los contadores antiguos), la
  modulación era incorrecta, o la grabación contiene solo parte de la señal. Graba pulsaciones más largas.
- **La transmisión se detiene a mitad**: tarjeta SD lenta con un fichero largo y denso. Recorta el fichero con
  [RAW Edit](/es/subghz/raw-editor) o usa una tarjeta más rápida.
- **Falta `Edit` en `More`**: la aplicación Sub-GHz RAW Edit no está instalada o es demasiado antigua.

## Relacionado

- [Read](/es/subghz/read) · [Sub-GHz RAW Edit](/es/subghz/raw-editor) · [Remote Analyzer](/es/subghz/remote-analyzer)
- [Formatos de fichero (RAW, BinRAW)](/es/subghz/file-format) · [Códigos rodantes](/es/subghz/rolling-codes)
