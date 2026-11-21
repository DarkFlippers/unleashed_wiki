---
title: Añadir llaves manualmente
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Añadir llaves iButton manualmente

Puedes crear una llave virtual a partir de su ID sin tener la llave física — por ejemplo con un número grabado en la
llave o apuntado previamente. Se puede emular y, en los protocolos escribibles,
[escribir en una llave virgen](/es/ibutton/write).

## Pasos

1. Ve a `Main Menu → iButton → Add Manually`.
2. Elige el protocolo:

   | Etiqueta del menú | ID a introducir |
   |---|---|
   | **Dallas DS1990** | ROM de 8 bytes |
   | **Dallas DS1992** | ROM de 8 bytes |
   | **Dallas DS1996** | ROM de 8 bytes |
   | **Dallas DS1971** | ROM de 8 bytes |
   | **Dallas DS1420** | ROM de 8 bytes |
   | **Dallas (non-specific)** | ROM de 8 bytes — cualquier dispositivo 1-Wire, sin comprobaciones |
   | **Cyfral** | 2 bytes |
   | **Metakom** | 4 bytes (cada byte debe tener la paridad correcta) |

   ![Lista de tipos de llave de Add Manually: Dallas DS1990, DS1992, DS1996 y DS1971](/screens/ibutton/add_manually.png)

3. La pantalla **Enter the key** abre un editor hexadecimal. Escribe los bytes y pulsa **Save**.
4. Introduce un nombre (prefijo por defecto `iBtn`) y guarda. La llave se almacena en `/ext/ibutton/<name>.ibtn`.

## Editar una llave guardada

`Main Menu → iButton → Saved` → llave → **Edit** → cambia el hexadecimal → **Save** → nombre → **Save**.

## Notas sobre los ID de Dallas

Una ROM Dallas es `family code` (1 byte) + `serial` (6 bytes) + `CRC` (1 byte):

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- La mayoría de las llaves de portero automático son DS1990 con family code `01`.
- Si el CRC es incorrecto, un lector puede rechazar la llave, y el Flipper informa de un error de CRC al volver a
  leerla.
- ¿Necesitas una llave con un family code o un CRC deliberadamente inválidos? Usa **Dallas (non-specific)** — no
  realiza ninguna comprobación.
- Una llave añadida manualmente **no tiene datos de memoria**; Full Write on Same Type requiere una lectura real.

::: tip Editor de bytes
En Unleashed, pulsar <kbd>↑</kbd> repetidamente en la entrada de bytes abre un mini editor de nibbles — muy práctico
para ID largos.
:::

## Páginas relacionadas

- [Lectura](/es/ibutton/read) · [Escritura](/es/ibutton/write) · [Protocolos](/es/ibutton/protocols) ·
  [Formato de archivo](/es/ibutton/file-format)
