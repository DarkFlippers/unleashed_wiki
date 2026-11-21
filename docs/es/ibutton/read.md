---
title: Leer llaves
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Leer, guardar y emular llaves iButton

Flipper Zero lee llaves Dallas 1-Wire (el ID y, en las llaves con memoria, su memoria), llaves Cyfral y Metakom, y
después puede guardarlas y emularlas.

| Llave | Qué se lee |
|---|---|
| Dallas **DS1990** / **DS1420** | Solo la ROM de 8 bytes (el ID) — la llave no tiene memoria |
| Dallas **DS1992** | ROM + 128 bytes de SRAM |
| Dallas **DS1996** | ROM + 8192 bytes de SRAM |
| Dallas **DS1971** | ROM + 32 bytes de EEPROM |
| Otros dispositivos 1-Wire | Solo la ROM, mostrada como **Dallas (non-specific)** |
| **Cyfral** | Código de 2 bytes |
| **Metakom** | Código de 4 bytes |

## Leer una llave

1. Ve a `Main Menu → iButton → Read`. La pantalla muestra **Reading — Connect key with pogo pins**.

   ![Pantalla de lectura con el mensaje "Connect key with pogo pins"](/screens/ibutton/read.png)

2. Apoya la llave sobre la **parte plana** del contacto iButton de forma que su centro toque el **pin de datos
   izquierdo** y su borde el **pin central de masa**. Mantenla quieta.
3. Cuando la llave se lee, el Flipper pita y muestra el protocolo (por ejemplo **Dallas DS1990**) y su ID.

   ![Resultado de la lectura: Dallas DS1990 con su ID de ocho bytes y el family code, con Retry y More abajo](/screens/ibutton/read_success.png)

4. Botones: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> pregunta *Exit to iButton Menu? All unsaved
   data will be lost!*

**More** ofrece (los elementos dependen del protocolo):

| Elemento | Cuándo aparece | Acción |
|---|---|---|
| **Save** | siempre | Dar nombre a la llave; se guarda en `/ext/ibutton/<name>.ibtn` |
| **Emulate** | siempre | Emular de inmediato |
| **Write ID** | protocolos escribibles | Escribir el ID en una llave virgen — [Escritura](/es/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Copiar la memoria a una llave del mismo tipo |
| **Data Info** | DS1992, DS1996, DS1971 | Mostrar el volcado de memoria |

## Errores de lectura

Si los datos no pasan la comprobación del protocolo, la pantalla de error explica el motivo y sigue ofreciendo
**Retry** y **More**:

- **CRC Error** (Dallas) — el octavo byte de la ROM es un CRC de los siete primeros; la pantalla muestra la ROM con el
  byte incorrecto resaltado y el *Expected CRC*. Normalmente es un mal contacto: limpia la llave y vuelve a leerla. Si
  se repite, aún puedes guardarla e intentar emularla — algunos lectores ignoran el CRC. Si la emulación falla, el
  error no se puede arreglar.
- **Invalid Metakom key: odd parity in byte N** — un byte Metakom no ha pasado su comprobación de paridad; vuelve a
  leer la llave.

## Llaves guardadas

`Main Menu → iButton → Saved` abre `/ext/ibutton/`. El menú de una llave:

| Elemento | Acción |
|---|---|
| **Emulate** | Emular ante un lector |
| **Write ID** | Escribir el ID en una llave virgen |
| **Full Write on Same Type** | Solo DS1992/DS1996/DS1971 — copiar la memoria |
| **Edit** | Cambiar el ID en hexadecimal y guardar con un nombre |
| **Rename** / **Delete** | Gestionar el archivo |
| **Info** | Nombre, protocolo, ID; <kbd>→</kbd> **More** muestra los datos de memoria en las llaves con memoria |

## Emular

1. Abre una llave guardada → **Emulate** (o **More → Emulate** justo después de leerla). La pantalla muestra
   **Emulating**, `[Protocol]` y el nombre de la llave (o *Unsaved Key*).

   ![Pantalla de emulación con "Emulating", el protocolo [DS1990] y el nombre de la llave](/screens/ibutton/emulate.png)

2. Presiona la **parte saliente** del contacto contra el lector: el **pin de datos derecho** debe tocar el centro del
   lector y el **pin central de masa**, su borde.
3. Si el pin de masa no alcanza el borde, conecta dos cables: GPIO **17** → centro del lector, GPIO **8 / 11 / 18**
   (GND) → borde.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Resolución de problemas

- **No pasa nada.** La llave no está tocando los dos pines — inclínala para que el borde toque el pin de masa.
- **Llave no compatible.** Puede usar un protocolo no soportado (o ser un llavero RFID — prueba con
  [RFID de 125 kHz](/es/rfid/read)).
- **El lector rechaza la emulación.** Comprueba el contacto de los pines; algunos lectores detectan emuladores o
  verifican cosas que el Flipper no puede falsear. Si has editado o añadido la llave a mano, revisa el ID.

## Páginas relacionadas

- [Escritura](/es/ibutton/write) · [Añadir manualmente](/es/ibutton/add-manually) ·
  [Protocolos](/es/ibutton/protocols) · [Formato de archivo](/es/ibutton/file-format)
