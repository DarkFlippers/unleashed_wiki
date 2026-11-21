---
title: Frequency Analyzer
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Frequency Analyzer

El Frequency Analyzer te dice **en qué frecuencia transmite un mando**. Barre las frecuencias de la lista de Sub-GHz,
mide la intensidad de señal (RSSI) y muestra la más fuerte. Úsalo antes de **Read** o **Read RAW** cuando no conozcas
la frecuencia de un mando.

::: tip Unleashed
Unleashed incluye un analizador rediseñado (originalmente de ClusterM) con un historial de 4 entradas, un disparador
ajustable, realimentación seleccionable (sonido / vibración / silencio) y un **salto directo a Read**: una pulsación
corta de <kbd>OK</kbd> guarda la frecuencia para Read / Read RAW, y una pulsación larga la guarda y abre Read de
inmediato.
:::

## La regla de oro

El analizador está pensado para funcionar **solo a unos centímetros de la antena del Flipper y con la radio
interna**. La antena está en el lado izquierdo, junto a la ventana negra de infrarrojos. Sus ajustes existen para
filtrar ruido, no para captar señales lejanas. Con un disparador muy bajo, el analizador no informa más que de
interferencias aleatorias y del propio ruido del Flipper en lugar de tu mando. Para *recibir* señales de verdad usa
[Read](/es/subghz/read) y [Read RAW](/es/subghz/read-raw).

::: warning
No se recomienda usar el analizador con un módulo externo: los módulos externos son más sensibles y recogen mucho
más ruido.
:::

## Pantalla

![Frequency Analyzer mostrando 433.920 MHz, las entradas del historial y la barra de RSSI](/screens/subghz/frequency_analyzer.png)

| Elemento | Significado |
|---|---|
| Icono arriba a la derecha | Realimentación al captar una señal: altavoz = vibración + sonido, altavoz pequeño = solo vibración, tachado = silencio |
| Número grande del centro | Frecuencia actual (principal). Mientras se recibe una señal por encima del disparador se muestra **invertida sobre un recuadro negro** |
| Cuatro entradas inferiores | Historial: frecuencia redondeada y cuántas veces se ha captado (`x3`). Ayuda con mandos débiles o que derivan |
| Barra `RSSI` abajo | Intensidad de señal en vivo con la marca del disparador |
| `T-` / `+T` | Botones del nivel de disparo |

## Botones

| Botón | Acción |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Mover el disparador (de −97 dBm a −60 dBm, en pasos de 1 dBm). Izquierda = más sensible, derecha = menos sensible |
| <kbd>↑</kbd> | Cambiar el modo de realimentación: vibración + sonido → silencio → vibración → … |
| <kbd>↓</kbd> | Seleccionar una entrada del historial (aparece un marco alrededor) |
| <kbd>OK</kbd> corta | Guardar la frecuencia seleccionada para Read / Read RAW |
| <kbd>OK</kbd> larga | Guardar la frecuencia y abrir **Read** de inmediato |
| <kbd>Back</kbd> | Salir (el disparador y el modo de realimentación se recuerdan) |

Qué frecuencia toma <kbd>OK</kbd>:

- si se está recibiendo una señal **en ese momento** (recuadro negro alrededor de la frecuencia principal), esa
  frecuencia, incluso si hay una entrada del historial seleccionada;
- si no se recibe nada y hay una entrada del historial seleccionada, la entrada seleccionada;
- en los demás casos, la última frecuencia que superó el disparador, para que no tengas que mantener el mando
  pulsado.

::: warning Redondeo
La frecuencia guardada se **redondea siempre a la frecuencia más cercana de la lista**
([Frecuencias](/es/subghz/frequencies)). Si tu mando queda lejos de todos los valores estándar, añade su frecuencia
a `setting_user`. El número principal mostrará entonces la frecuencia real, pero después de saltar a Read / Read RAW
tendrás que ajustarla a mano en `Config`.
:::

Guardar una frecuencia desde el analizador también **desactiva Hopping**, de modo que Read arranca exactamente en
esa frecuencia.

## Cómo encontrar la frecuencia de un mando

1. Aléjate de fuentes de alimentación conmutadas, cargadores y otros aparatos ruidosos.
2. Abre `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Sujeta el mando pegado al lado izquierdo del Flipper (cerca de la ventana negra).
4. Mantén pulsado un botón del mando. La frecuencia principal se invierte mientras se recibe la señal.
5. Suelta el botón y espera a que la frecuencia aparezca en el historial.
6. Pulsa <kbd>OK</kbd> para recordarla, o mantén <kbd>OK</kbd> para ir directamente a **Read**.

La mayoría de los mandos transmiten en torno a 315, 433.92 o 868.35 MHz. En Read, prueba aun así varias
modulaciones si no se decodifica nada (primero `AM650`, después `FM238`, `FM476`, `FM12K`).

## Ajustar el disparador

Por defecto el disparador está en −93 dBm, una posición que funciona en la mayoría de los casos, así que
normalmente no hay que tocarlo. Ajústalo solo cuando el mando no se capte ni a bocajarro, o cuando haya mucho ruido:

1. Sin pulsar ningún mando, mueve la marca con <kbd>←</kbd> / <kbd>→</kbd> hasta que el Flipper deje de captar nada
   (ni ruido ni aciertos aleatorios). La posición más a la izquierda es la más sensible: capta las señales *y* el
   ruido interno del Flipper y cualquier interferencia; la más a la derecha es la menos sensible a ambos.
2. Sujeta el mando contra el borde izquierdo del Flipper y pulsa su botón.
3. Si no se capta nada, mueve el disparador **a la izquierda** paso a paso hasta que aparezca la señal.
4. Pulsa y suelta el botón del mando repetidamente mientras ajustas: una señal intermitente facilita encontrar la
   posición correcta más que una continua.

## Resolución de problemas

- **Aparecen frecuencias aleatorias constantemente**: el disparador está demasiado bajo o hay ruido cerca. Muévelo
  a la derecha y aléjate de las fuentes de alimentación.
- **El mando nunca se capta**: acércalo más, comprueba la pila y mueve el disparador a la izquierda. Algunos mandos
  envían ráfagas muy cortas: pulsa repetidamente.
- **Read no muestra nada en la frecuencia encontrada**: modulación incorrecta. Cámbiala en `Read → Config`. Si no se
  decodifica nada, grábalo con [Read RAW](/es/subghz/read-raw).
- **La frecuencia no coincide con la etiqueta del mando**: es normal; los mandos baratos derivan. Usa los contadores
  del historial para elegir el valor más frecuente.

## Relacionado

- [Frecuencias](/es/subghz/frequencies) · [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw)
- [Remote Analyzer](/es/subghz/remote-analyzer) — una aplicación con su propio analizador y decodificación de un mando a la vez
