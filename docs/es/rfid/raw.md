---
title: Grabación RAW
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Leer datos RAW de 125 kHz

El modo RAW graba la señal del tag tal cual — las duraciones de pulso y de periodo — en lugar de decodificarla, un
poco como una grabadora de voz. Está pensado para la **investigación de protocolos**: si tu tag no se reconoce,
grábalo y envía los archivos (y una foto de la tarjeta) a los desarrolladores en una issue de GitHub.

## Activar el modo Debug

Los elementos RAW están ocultos a menos que Debug esté activado:

1. `Main Menu → Settings → System`.
2. Pon **Debug** en **ON**.

## Grabar

1. Ve a `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Dale nombre a la grabación (por defecto `RfidRecord`).
3. Lee las instrucciones (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) y pulsa <kbd>OK</kbd>.
4. Mantén la tarjeta sobre la parte trasera del Flipper. El Flipper graba tres pasadas de **5 segundos** cada una —
   *Reading ASK*, *ASK 134kHz*, *Reading PSK* — y pide *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Pulsa <kbd>OK</kbd>.

Se crean tres archivos en `/ext/lfrfid/`:

| Archivo | Pasada |
|---|---|
| `<name>.ask.raw` | ASK, portadora de 125 kHz |
| `<name>.ask134.raw` | ASK, portadora de 134,2 kHz |
| `<name>.psk.raw` | PSK, portadora de 125 kHz |

::: tip Unleashed
La documentación de Unleashed y el firmware de fábrica mencionan dos archivos (ASK y PSK). El firmware actual graba una
tercera pasada, **ASK 134kHz**, para los tags de animales.
:::

Si ves *RAW Reading error! This may be caused by SD card issues*, revisa la tarjeta (espacio libre, errores). Sin
tarjeta SD la app muestra *No SD Card!*.

## Reproducir

`Extra Actions → Emulate RAW RFID data` abre el explorador de archivos para los archivos `.raw` y reproduce el
seleccionado (*Emulating RAW RFID*). Resulta útil sobre todo para depurar protocolos, no como sustituto de la
emulación normal.

## CLI

Lo mismo está disponible desde la CLI y resulta práctico para el desarrollo:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` imprime cada par pulso/duración, marca dónde se ha decodificado un protocolo y termina con la frecuencia,
el ciclo de trabajo, las medias y el protocolo detectado (o `not found`).

## App LF-RFID Debug

El código fuente del firmware incluye también una herramienta para desarrolladores, **LF-RFID Debug**
(`applications/debug/lfrfid_debug`), cuya pantalla **Tune** ajusta en vivo el temporizador de la portadora (ARR/CCR —
frecuencia y ciclo de trabajo). Es una app de depuración para el desarrollo de protocolos, no necesaria para el uso
normal.

## Páginas relacionadas

- [Formatos de archivo](/es/rfid/file-format) · [Lectura](/es/rfid/read) · [Protocolos](/es/rfid/protocols)
