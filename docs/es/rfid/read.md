---
title: Leer tags
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# Leer, guardar y emular tags de 125 kHz

Un tag de 125 kHz es un transpondedor que, alimentado por el campo de un lector, envía un ID fijo. Si el tag usa uno
de los [protocolos compatibles](/es/rfid/protocols), Flipper Zero decodifica el ID, lo muestra y puede guardarlo en la
tarjeta SD, emularlo ante un lector o [escribirlo en un chip virgen](/es/rfid/write).

**Úsalo cuando** quieras una copia de tu propia tarjeta o llavero de acceso en el Flipper, quieras identificar qué
tipo de tag tienes o necesites el ID para un sistema de control de acceso que administras.

::: tip Inserta una tarjeta SD
Las llaves guardadas, los diccionarios y los ajustes residen en la tarjeta microSD (`/ext/lfrfid/`). Instala el
firmware con la tarjeta SD puesta para que los recursos de la app estén presentes.
:::

## Leer un tag

1. Ve a `Main Menu → 125 kHz RFID → Read`.
2. Coloca el tag contra la **parte trasera** del Flipper, cerca del centro, y mantenlo quieto. La pantalla indica
   *Don't move card*.
3. El Flipper recorre tres pasadas de lectura de unos 2 segundos cada una y muestra la activa como
   **Reading 1/3 … 3/3**: **ASK** (125 kHz), **PSK** (125 kHz) y **134kHz** (ASK a 134,2 kHz, para chips de animales).

   ![Reading 1/3 con la pasada ASK activa, PSK y 134 kHz debajo, y "Don't move card" al pie](/screens/lfrfid/read.png)

4. Fíjate en el LED: parpadea en **cian** mientras lee, cambia a **amarillo** cuando oye algo y a **verde** cuando
   empiezan a decodificarse las tramas de un tag — resulta útil para encontrar el punto justo.
5. Cuando se decodifica un tag, el Flipper pita y muestra la pantalla de resultado:
   - encabezado: fabricante y protocolo, por ejemplo **EM-Micro EM4100**;
   - `Hex:` — los datos en bruto de la llave (los 7 primeros bytes; las llaves más largas terminan con `...`);
   - campos decodificados (facility code, número de tarjeta, etc. — consulta [protocolos](/es/rfid/protocols)).

   ![Resultado de la lectura: EM-Micro EM4100 con sus datos en hex, facility code, número de tarjeta, DEZ 8 y DEZ 10, con Retry y More al pie](/screens/lfrfid/read_success.png)

6. Botones: <kbd>←</kbd> **Retry** (pregunta *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More**;
   <kbd>Back</kbd> pregunta si quieres salir y perder la lectura sin guardar.

::: tip Unleashed
La documentación de fábrica solo describe el cambio entre ASK y PSK. Unleashed añade la tercera pasada de **134 kHz**
(los tags FDX-A/FDX-B están sintonizados a 134,2 kHz y los más débiles solo responden ahí) y, para EM4100, muestra
además **DEZ 8** y **DEZ 10** — las formas decimales impresas en muchos llaveros. Un EM4100 que se decodifica como una
credencial Casi-Rusco C10106 obtiene una línea adicional `or C10106: …`, y una llave Generic HIDProx se compara con
los formatos HID conocidos (H10304, H10302, S10401, H10306, Corp1000-35) y muestra su FC y número de tarjeta.
:::

## Después de leer: More

<kbd>→</kbd> **More** abre:

| Elemento | Acción |
|---|---|
| **Save** | Introduce un nombre (prefijo por defecto `RFID`); se guarda como `/ext/lfrfid/<name>.rfid` |
| **Emulate** | Emular la llave de inmediato, sin guardarla |
| **Write** | Escribir la llave en un chip virgen — consulta [Escritura](/es/rfid/write) |

## Leer con una modulación fija

Algunos tags necesitan más tiempo que una pasada de 2 segundos para decodificarse, o solo se encuentran de forma
fiable con un demodulador concreto. `Main Menu → 125 kHz RFID → Extra Actions` ofrece:

| Elemento | Qué lee |
|---|---|
| **Read ASK (Regular)** | Solo ASK a 125 kHz, hasta encontrar un tag: EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | Solo PSK: Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | Solo ASK a 134,2 kHz — chips de animales, consulta [Microchips de animales](/es/rfid/animal-microchips) |

En modo Debug el mismo menú incluye también **Read RAW RFID data** y **Emulate RAW RFID data** — consulta
[RAW](/es/rfid/raw).

## Llaves guardadas

`Main Menu → 125 kHz RFID → Saved` abre el explorador de archivos en `/ext/lfrfid/`. Al elegir una llave `.rfid` se
abre:

![Menú de un tag guardado con Emulate, Write, Write and set password y Edit](/screens/lfrfid/saved_menu.png)

| Elemento | Acción |
|---|---|
| **Emulate** | Actuar como esta llave ante un lector |
| **Write** | Escribirla en un chip virgen ([Escritura](/es/rfid/write)) |
| **Write and set password** | Escribir en un T5577 y protegerlo con contraseña ([Escritura](/es/rfid/write#write-and-set-password)) |
| **Edit** | Cambiar los datos de la llave en hexadecimal; se guarda con el mismo nombre |
| **Rename** | Cambiar el nombre del archivo |
| **Delete** | Borrar el archivo (con confirmación) |
| **Info** | Nombre, protocolo, datos hex completos y todos los campos decodificados |

::: tip Unleashed
El explorador también lista volcados de bloques **`.t5577`** (marcados con el icono de T5577). Al seleccionar uno se
abre la [app T5577](/es/rfid/t5577-app) con ese volcado. Si la app no está instalada verás *No T5577 app — It comes
with the firmware - install its resources to get it*.
:::

## Emular

1. Abre una llave guardada (o una lectura reciente desde **More**) y elige **Emulate**.
2. La pantalla muestra *Emulating*, `[Protocol]` y el nombre de la llave (o *Unsaved Tag*); el LED parpadea en
   magenta.

   ![Pantalla de emulación con "Emulating", el protocolo [EM4100] y el nombre de la llave](/screens/lfrfid/emulate.png)

3. Mantén la parte trasera del Flipper plana contra el lector. Pulsa <kbd>Back</kbd> para detenerlo.

## CLI

Desde la CLI por USB/serie (comando `rfid`):

```text
rfid read <optional: normal | indala | ask134>   - read in ASK/PSK mode
rfid <write | emulate> <key_type> <key_data>      - write or emulate a card
rfid raw_read <ask | ask134 | psk> <filename>     - read and save raw data to a file
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` es el nombre del protocolo tal como se almacena en los archivos `.rfid` (por ejemplo `EM4100`, `H10301`) y
`key_data` es hexadecimal.

## Resolución de problemas

- **No se encuentra nada.** La tarjeta puede ser de 13,56 MHz — prueba con [NFC](/es/nfc/read). Muchas tarjetas
  «duales» llevan ambas tecnologías.
- **La lectura no deja de ciclar.** Prueba un modo fijo en **Extra Actions** — una pasada de 2 s puede ser demasiado
  corta para algunos tags.
- **Tags débiles / llaveros pequeños.** Desplaza el tag lentamente por la parte trasera y vigila el LED
  amarillo/verde. No lo sujetes en la mano sobre superficies metálicas.
- **Protocolo desconocido.** Graba una captura [RAW](/es/rfid/raw) e infórmala a los desarrolladores.
- **El lector no acepta la emulación.** Algunos lectores son quisquillosos con la distancia y la orientación —
  mantén el Flipper plano y prueba varias posiciones. Los lectores que comprueban algo más que el ID (por ejemplo
  tarjetas con criptografía) no se pueden engañar con emulación.

## Páginas relacionadas

- [Escribir en chips vírgenes](/es/rfid/write) · [Añadir manualmente](/es/rfid/add-manually) ·
  [Protocolos](/es/rfid/protocols) · [Formato de archivo](/es/rfid/file-format)
