---
title: Infrarrojos
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Infrarrojos

El Flipper Zero lleva un módulo de infrarrojos (IR) integrado. Puede **aprender** los botones de casi cualquier mando
IR, **guardarlos** como mando virtual en la tarjeta microSD, **reenviarlos** y funcionar como **mando universal** que
recorre una biblioteca de códigos conocidos para televisores, equipos de audio, proyectores, tiras LED, ventiladores
y aires acondicionados.

![Infrarrojos en el Flipper Zero](/img/remote/133011d2bd3dc44c.png)

## Hardware

- Una ventana de plástico transparente al infrarrojo en el borde superior del Flipper.
- **Tres LED IR** para transmitir.
- Un **receptor IR** que demodula la portadora (está ajustado a la portadora habitual de 38 kHz). El aprendizaje
  siempre usa este receptor integrado.
- Opcionalmente un **transmisor IR externo** en el pin 2 (A7) del GPIO para mayor alcance; véase
  [Módulos IR externos](/es/infrared/external-ir).

## El menú Infrared

Abre `Main Menu → Infrared`. Los elementos del menú vienen directamente del firmware:

![El menú Infrared con Universal Remotes, Learn New Remote, Saved Remotes y GPIO Settings](/screens/infrared/menu.png)

| Elemento | Qué hace |
|---|---|
| **Universal Remotes** | Envía una biblioteca completa de códigos para un botón (Power, Vol+…) hasta que tu aparato reacciona. Véase [Mandos universales](/es/infrared/universal-remotes). |
| **Learn New Remote** | Captura botones de un mando físico y los guarda como un mando nuevo. Véase [Aprender y enviar señales](/es/infrared/read). |
| **Saved Remotes** | Abre el explorador de ficheros en `/ext/infrared/` para enviar, editar, renombrar o borrar tus mandos. |
| **GPIO Settings** | Elige el transmisor (integrado, pin 2 (A7) o detección automática) y los 5 V del GPIO. Véase [Módulos IR externos](/es/infrared/external-ir). |
| **Learn New Remote RAW** | Solo con `Settings → System → Debug` activado. Como Learn, pero con el decodificador desactivado: cada señal se guarda como RAW. |
| **Debug RX** | Solo con Debug activado. Un «INFRARED monitor» en vivo de lo que recibe el receptor. |

::: tip Unleashed
La app Infrared, sus decodificadores de protocolos y el mecanismo de los mandos universales son del firmware
oficial. Unleashed añade:
- el protocolo IR **RCA** (véase [Protocolos](/es/infrared/protocols));
- bibliotecas de mandos universales adicionales (**LEDs**, **Fans**) y bibliotecas mucho más grandes y revisadas con
  regularidad para televisores, audio, proyectores y aires acondicionados, mantenidas por el equipo de Unleashed
  (recursos IR de @amec0e). La biblioteca de televisores se recompila para que funcionen **todos** sus botones;
- compatibilidad con módulos IR externos con detección automática (heredada del firmware oficial).
:::

## Dónde están los ficheros

| Ruta | Contenido |
|---|---|
| `/ext/infrared/*.ir` | Tus mandos guardados (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Bibliotecas de mandos universales: `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Se instalan y se actualizan junto con el firmware. |
| `/ext/infrared/.infrared.settings` | Ajustes del GPIO (pin de salida, 5 V). |

El formato de los ficheros `.ir` se describe en [Formato de los ficheros IR](/es/infrared/file-format).

## Línea de comandos

El comando `ir` está disponible en la [CLI](/es/dev/cli) (por ejemplo a través de qFlipper o de un terminal serie):

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Páginas de esta sección

| Página | Qué aprenderás |
|---|---|
| [Aprender y enviar señales](/es/infrared/read) | Aprender un mando, guardarlo, enviar botones, editar / mover / renombrar / borrar botones |
| [Mandos universales](/es/infrared/universal-remotes) | Todas las categorías de mandos universales, botones, controles y cómo guardar un código que funciona |
| [Mandos en la aplicación móvil](/es/infrared/mobile) | La Remotes Library en Flipper Mobile App |
| [Contribuir con capturas](/es/infrared/captures) | Cómo grabar señales limpias para las bibliotecas universales |
| [Módulos IR externos](/es/infrared/external-ir) | Salida por GPIO, detección automática, alimentación de 5 V |
| [Protocolos](/es/infrared/protocols) | Todos los protocolos que conoce el decodificador, incluido RCA |
| [Formato de los ficheros IR](/es/infrared/file-format) | Formatos de fichero `.ir` de mando, de biblioteca y de prueba |
