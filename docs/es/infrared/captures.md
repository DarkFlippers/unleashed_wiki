---
title: Contribuir con capturas
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Contribuir con capturas IR a los mandos universales

Si un [mando universal](/es/infrared/universal-remotes) no funciona con tu aparato, puedes grabar tu mando original
y añadirlo a la biblioteca, para que funcione para todo el mundo. Esta página explica cómo hacer capturas
**limpias**: cortas, decodificadas siempre que sea posible y con el nombre exacto que espera el mando universal.

El método es la guía de Unleashed de **@amec0e** (quien mantiene los recursos IR de Unleashed), basada en la
documentación original *UniversalRemotes* de @gsurkov, @skotopes, @knrn-ai, @DrZlo13 y @ahumeniy.

## Nombres de botón por biblioteca {#button-names-per-library}

El mando universal solo usa señales cuyo `name:` coincide exactamente con uno de sus botones (las mayúsculas
cuentan). Cualquiera de ellos puede omitirse si tu aparato no lo tiene.

| Biblioteca | Fichero | Nombres de señal |
|---|---|---|
| TVs | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projectors | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LEDs | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Fans | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| ACs | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

En muchos mandos de audio `Play` y `Pause` son el mismo botón: grábalo como `Play` y omite `Pause`.

## Televisores, audio, proyectores, ventiladores y LED

1. Apunta con el mando al receptor IR del Flipper.
2. Inicia `Infrared → Learn New Remote` para el primer botón, o selecciona `+` dentro del mando para los siguientes.
3. Haz una **pulsación corta** del botón del mando y guárdalo con el nombre correspondiente de la tabla anterior.
4. Repite los pasos 2-3 para todos los botones.
5. Prueba cada botón guardado con el aparato real: cada uno debe hacer lo que dice su nombre.

::: warning No mantengas el botón
Mantener pulsado el botón del mando produce capturas largas con muchas repeticiones. Tardan más en enviarse y
ralentizan todo el mando universal para todo el mundo.
:::

### Parsed frente a RAW

**Parsed** es el mejor resultado: el protocolo se ha reconocido y solo se almacenan protocolo, dirección y comando.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Las interferencias de otros aparatos a tu alrededor (lámparas, retroiluminación de televisores, otros mandos) pueden
empujar una captura a **RAW** aunque el protocolo sea conocido. Si has obtenido RAW con un mando corriente, pulsa
**Retry** en el Flipper varias veces hasta conseguir una captura decodificada limpia.

**RAW** está bien cuando el mando usa realmente un protocolo desconocido. Procura obtener el *menor número de
muestras* que siga funcionando en el aparato: una pulsación corta, normalmente **alrededor de 100 muestras**. Una
captura ideal de una sola pulsación tiene este aspecto:

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Aires acondicionados {#air-conditioners}

Los mandos de aire acondicionado son distintos: el mando mantiene el estado (modo, temperatura, ventilador,
lamas) en su pantalla, y cada pulsación envía **el estado completo** de una vez. Así que cada «botón» de aire
acondicionado es en realidad un estado completo que hay que capturar entero.

Para cada señal **excepto `Off`**:

1. Pulsa **Power** en el mando para que su pantalla muestre el aire acondicionado encendido.
2. Ajusta el modo y la temperatura según la tabla siguiente. Deja todo lo demás (velocidad del ventilador, lamas) en
   **AUTO** si es posible.
3. Pulsa **Power** en el mando para apagarlo.
4. En el Flipper inicia el aprendizaje (`Learn New Remote` para el primero, `+` para el resto).
5. Apunta con el mando al Flipper y pulsa **Power** una vez más (esta es la trama de «encender en este modo»).
6. Guarda la señal con el nombre de la tabla.
7. Repítelo para cada fila.

| Señal | Modo | Temperatura | Nota |
|:---:|:---:|:---:|---|
| `Dh` | Deshumidificador | N/D | |
| `Cool_hi` | Refrigeración | la más baja | la temperatura más baja disponible en modo refrigeración |
| `Cool_lo` | Refrigeración | 23 °C | |
| `Heat_hi` | Calefacción | la más alta | la temperatura más alta disponible en modo calefacción |
| `Heat_lo` | Calefacción | 23 °C | |

Después graba **`Off`**:

1. Comprueba que la pantalla del mando muestre el aire acondicionado encendido.
2. Inicia el aprendizaje en el Flipper y apunta el mando hacia él.
3. Pulsa **Power** para que el mando muestre OFF.
4. Guarda la señal como `Off`.

Acabarás con hasta 6 señales. Pruébalas todas con el aire acondicionado real.

## Preparar el fichero y enviarlo

1. Copia el fichero `.ir` de `/ext/infrared/` a tu ordenador con [qFlipper](/es/mobile/qflipper) (o con la aplicación
   móvil) y ábrelo en un editor de texto.
2. Precede tus señales con un comentario de modelo para que la biblioteca siga ordenada:
   ```text
   # Model: <your brand and model>
   ```
   El orden de las señales dentro del bloque no importa.
3. Haz un fork del [repositorio de Unleashed](https://github.com/DarkFlippers/unleashed-firmware) y **añade** tu
   bloque **al final** del fichero correspondiente en
   `applications/main/infrared/resources/infrared/assets/`.
4. Abre un pull request con el fichero modificado. Tras la revisión se incluirá en la siguiente compilación para
   todo el mundo.

El formato del fichero se describe en [Formato de los ficheros IR](/es/infrared/file-format#library-files). Grandes
colecciones comunitarias de mandos ya preparados: [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) y la
oficial [flipperdevices/IRDB](https://github.com/flipperdevices/IRDB), que usa la
[aplicación móvil](/es/infrared/mobile).

## Páginas relacionadas

- [Mandos universales](/es/infrared/universal-remotes)
- [Aprender y enviar señales](/es/infrared/read)
- [Formato de los ficheros IR](/es/infrared/file-format)
