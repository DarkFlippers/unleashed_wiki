---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (de @xMasterX) decodifica un mando a la vez con el CC1101 interno y muestra todos los campos que consigue deducir. A diferencia de `Sub-GHz → Read`, no guarda **ningún historial** —solo la última señal está en pantalla— y **nunca guarda** un fichero `.sub`. Es una herramienta para responder a la pregunta «¿qué es este mando?».

::: tip Unleashed
Remote Analyzer es una aplicación de sistema integrada de Unleashed. Además de todos los protocolos que conoce la aplicación Sub-GHz, tiene sus propios protocolos solo de decodificación: **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** y **PC4**.
:::

**Cuándo usarla:** quieres identificar rápidamente un mando desconocido, ver si es de código fijo o rodante, o examinar un mando que la aplicación principal no puede decodificar. Para capturar y reproducir, usa [Read](/es/subghz/read) o [Read RAW](/es/subghz/read-raw).

## Menú principal

`Main Menu → Apps → Sub-GHz → Remote Analyzer`:

- `Read`: decodificación en vivo
- `Decode RAW File`: pasa una captura RAW guardada por los mismos decodificadores
- `Frequency Analyzer`: localiza la frecuencia del mando
- `How to use`: el manual integrado

## Leer un mando

1. Abre `Read`. La pantalla muestra `Waiting for a signal`.
2. Pulsa <kbd>←</kbd> (`Config`) y ajusta **Frequency** y **Modulation** (o activa **Hopping**).
3. Sujeta el mando cerca del Flipper y pulsa su botón.
4. Aparece la lectura:
   - el icono de arriba a la izquierda indica código **fixed** o **rolling**;
   - la línea situada bajo el nombre del protocolo y el número de bits indica si la aplicación Sub-GHz conoce también este protocolo, o si es **analyzer only**;
   - `xN` arriba a la derecha cuenta cuántas veces se ha recibido este código;
   - la barra inferior es la intensidad de la señal.
5. <kbd>↑</kbd> / <kbd>↓</kbd> desplazan una lectura que no cabe, y <kbd>→</kbd> (`Reset`) la borra.

**El LED:** morado, escuchando; amarillo, hay algo en el aire que nada ha decodificado; verde, se ha recibido un código.

## Config

| Elemento | Qué hace |
|---|---|
| Frequency | frecuencia de recepción (se ignora mientras Hopping está activado) |
| Modulation | preset: AM270, AM650, FM238, FM476, FM12K y cualquier preset personalizado |
| Hopping | `OFF` o un nivel de `-90dB` a `-40dB` |
| Sound | reproduce la señal demodulada por el altavoz |
| Mod. sweep | prueba otras modulaciones cuando no se decodifica nada |
| Notify | vibra una vez ante un código distinto del último |
| Reset to default | restaura los valores por defecto |

**Hopping.** Con un nivel fijado, la aplicación recorre **315, 390, 430.5, 433.92, 434.42 y 868.35 MHz** mientras el aire está tranquilo y se detiene en la primera banda donde la portadora alcanza ese nivel. Una decodificación mantiene la banda durante dos segundos antes de reanudar el salto. Elegir una frecuencia en el Frequency Analyzer desactiva el salto. El nivel es también lo que el barrido y el LED consideran «una señal», así que sigue importando con Hopping en `OFF`.

**Mod. sweep.** Cuando un mando está transmitiendo claramente pero nada lo decodifica, la aplicación recorre las demás modulaciones, aproximadamente un segundo cada una. Un `~` junto a la modulación significa que sigue intentándolo: **mantén pulsado el botón del mando**. La primera decodificación con éxito fija la modulación y el `~` desaparece; tras dos segundos sin decodificar nada, el barrido vuelve a empezar desde ahí. `Unknown remote` significa que una ronda completa no ha encontrado nada; vuelve a dar otra ronda mientras el botón esté pulsado.

**Notify.** Un mando mantenido repite un mismo código, así que eso solo hace parpadear el LED; un código nuevo y distinto además vibra.

## Decode RAW File

1. Elige `Decode RAW File` y selecciona un `.sub` RAW de `/ext/subghz`.
2. Una barra de progreso muestra por dónde va dentro del fichero.
3. Se listan todos los códigos distintos encontrados; pulsa <kbd>OK</kbd> sobre uno para ver la lectura completa.

Solo una captura RAW contiene muestras: un fichero de clave guardado se rechaza. Si no se decodifica nada (o si el fichero se rechaza) suena un error y el LED se queda en rojo.

## Frequency Analyzer

Mantén pulsado el botón del mando cerca del Flipper y después **mantén** <kbd>OK</kbd> para llevar la frecuencia detectada a `Read`. <kbd>←</kbd> / <kbd>→</kbd> mueven el nivel de disparo. Funciona como el [analizador de la aplicación principal](/es/subghz/frequency-analyzer).

## Resolución de problemas

- **Siempre `Waiting for a signal`**: frecuencia incorrecta; ejecuta el Frequency Analyzer o activa Hopping.
- **LED amarillo pero sin decodificación**: activa `Mod. sweep` y mantén el botón pulsado, o grábalo con [Read RAW](/es/subghz/read-raw) y prueba `Decode RAW File`.
- **Protocolo solo de analizador**: la aplicación Sub-GHz principal no puede guardarlo ni enviarlo; Remote Analyzer únicamente lo identifica.
- **Quieres guardar la señal**: usa [Read](/es/subghz/read); esta aplicación no escribe ficheros.

## Páginas relacionadas

- [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw) · [Frequency Analyzer](/es/subghz/frequency-analyzer)
- [Sistemas compatibles](/es/subghz/supported-systems)
