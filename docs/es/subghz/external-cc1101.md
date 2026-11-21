---
title: Módulo CC1101 externo
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# Módulo CC1101 externo

La radio Sub-GHz propia del Flipper es un chip CC1101 con una antena interna pequeña. Puedes conectar una segunda placa CC1101 al conector GPIO y hacer que la aplicación Sub-GHz (y las aplicaciones de sistema Sub-GHz) la usen en su lugar. Las placas externas suelen llevar una antena SMA en condiciones y, a menudo, un amplificador de potencia, de modo que alcanzan mucho más lejos, tanto al recibir como al transmitir.

**Cuándo usarlo:** el mando o el receptor están lejos, la antena interna no capta un mando débil, o necesitas más alcance de transmisión. Para localizar la frecuencia de un mando, sigue usando la radio interna (véase [Frequency Analyzer](/es/subghz/frequency-analyzer)).

::: tip Funciona en cualquier firmware
Los módulos de radio externos funcionan en cualquier firmware, también en el de serie. La primera implementación la escribió @quen0n para Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)); la que se usa hoy la escribió **Skorp** en el firmware oficial, y es la que usa Unleashed.
:::

## Conexiones

El módulo se comunica a través del bus SPI externo del Flipper. El cableado estándar es:

| Pin del CC1101 | GPIO del Flipper | Pin del conector |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 o 18 |
| Control del amplificador / LED (módulos E07) | PC3 | 7 |

Para placas ya montadas, esquemas y fotos, consulta la guía de quen0n: [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (enlazada desde el FAQ de Unleashed). La numeración del conector está en la página del [pinout del GPIO](/es/gpio/pinout); otras placas de expansión están en [Módulos externos](/es/gpio/external-modules).

::: warning
Alimenta el módulo únicamente con **3,3 V**. El CC1101 no es un chip de 5 V.
:::

## Cambiar al módulo externo

1. Conecta el módulo con el Flipper apagado o, al menos, sin ninguna aplicación Sub-GHz en marcha.
2. Abre `Main Menu → Sub-GHz → Radio Settings`.
3. En la línea **Module** pulsa <kbd>→</kbd> para cambiar `Internal` por `External`.
4. Pulsa <kbd>←</kbd> (Back) y usa `Read`, `Read RAW`, `Saved`, etc., como de costumbre.

Qué esperar:

- La línea **Module** ofrece `External` solo cuando se detecta realmente un módulo. Si no hay nada conectado, la línea tiene un único valor, `Internal`.
- El firmware sondea el módulo al seleccionarlo. Si el sondeo falla, vuelve a la radio interna y la línea muestra `Internal` de nuevo, así que lo que ves es lo que está realmente en uso.
- En la pantalla de transmisión de una señal guardada, la línea inferior muestra `R: Int` o `R: Ext`: la radio que va a transmitir.
- Las aplicaciones de sistema Sub-GHz ([Nice O-Code](/es/subghz/nice-o-code), [Seed Capturer](/es/subghz/seed-capturer), [Security+ PIN](/es/subghz/secplus-pin)) muestran `Int` o `Ext` en su encabezado y usan automáticamente un módulo externo cuando hay uno conectado.

## Otros Radio Settings

`Sub-GHz → Radio Settings` contiene:

| Elemento | Valores | Qué hace |
|---|---|---|
| Module | `Internal` / `External` | radio usada por la aplicación Sub-GHz |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | sobrescribe la potencia de transmisión del preset; `Preset` mantiene la potencia del preset de modulación |
| Protocol Names | `OFF` / `ON` | véase [Ajustes](/es/subghz/settings) |
| Counter Incr. | `+1`… | véase [Ajustes](/es/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **solo en modo depuración**: controla el pin del amplificador y de los LED (PC3, pin 7 del conector) de los módulos de estilo E07 |
| Debug Pin | `OFF` / `17(1W)` | **solo en modo depuración**: replica la señal en el pin 17 para desarrollar protocolos |

`Ext Amp & LEDs` está **en ON por defecto**. Con él activado, el firmware activa el amplificador del módulo en PC3 solo mientras el chip está transmitiendo de verdad. Desactívalo únicamente si tu módulo usa el pin 7 para otra cosa; el elemento del menú aparece cuando el modo depuración está activado en `Settings → System`.

## Módulo de alta potencia de 1 W (en pruebas)

A principios de 2025 @gromovyna compartió sus pruebas de un nuevo módulo Sub-GHz mucho más potente fabricado por quen0n (miembro del equipo de Unleashed):

- En el momento de las publicaciones era el único que existía, con una potencia de transmisión de **hasta 1 W**.
- Está construido sobre un chip distinto del CC1101, un chip sobre el que nadie había construido nada antes.
- La compatibilidad en el firmware **aún no estaba terminada**; se estaba desarrollando para Unleashed junto con Flipper Market, y gromovyna actuó como probador.

![Módulo de alta potencia junto a una placa CC1101](/img/remote/29279ff04df77e30.jpg)

Sus resultados empíricos (sin mediciones de potencia):

- El módulo es mucho más potente que cualquier cosa que hubiera visto basada en el CC1101.
- En ciudad, transmitiendo desde un piso con otro edificio de por medio, envió una señal **Hollarm** a **600 m** en horizontal.
- Alcanzó la misma distancia tanto con la antena incluida como con una antena de walkie-talkie recomendada por MMX y quen0n, aunque con la antena de walkie-talkie el conjunto es «absolutamente no portátil».
- Todavía no estaba claro si existía alguna ventaja para la *recepción* frente al CC1101.

![El módulo con una antena de walkie-talkie](/img/remote/0998ad639bb38e82.jpg)

Esto describe un aparato en pruebas; consulta las notas de la versión actual de Unleashed para conocer su estado de compatibilidad.

::: warning
Transmite solo en frecuencias y con potencias que sean legales donde te encuentres, y únicamente hacia tus propios equipos.
:::

## Resolución de problemas

- **No se puede seleccionar `External`**: el módulo no se detecta; comprueba los 3,3 V, GND y las cuatro líneas SPI (CSN, SCK, MOSI, MISO). Un cable CSN o MISO equivocado es el error más habitual.
- **Vuelve a `Internal` por sí solo**: el sondeo falló al seleccionar el módulo; recolócalo y vuelve a intentarlo.
- **Recibe bien pero el alcance al transmitir es malo**: en los módulos E07 el amplificador necesita el pin 7 (PC3) conectado y `Ext Amp & LEDs` en ON.
- **El Frequency Analyzer muestra aciertos aleatorios**: el módulo externo es mucho más sensible al ruido; usa la radio interna para el análisis de frecuencia.
- **Transmisión bloqueada**: la frecuencia está fuera del rango del CC1101; véase [Frecuencias](/es/subghz/frequencies).

## Páginas relacionadas

- [Ajustes de Sub-GHz](/es/subghz/settings)
- [Frecuencias](/es/subghz/frequencies)
- [Pinout del GPIO](/es/gpio/pinout) · [Módulos externos](/es/gpio/external-modules)
