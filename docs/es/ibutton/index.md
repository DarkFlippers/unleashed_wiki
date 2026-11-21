---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

iButton («touch memory», en los países de la CEI se le llama a menudo *таблетка*) es una llave alojada en una pequeña
cápsula de acero que se lee apoyándola sobre un lector. La mayoría hablan Dallas **1-Wire**; los porteros automáticos
usan además llaves **Cyfral** y **Metakom**. Flipper Zero puede leer, guardar, emular y escribir estas llaves.

## Hardware

El módulo iButton es un contacto con tres pines pogo con resorte situado en la placa iButton.

- Los dos pines exteriores son de datos (conectados al **pin GPIO 17**), el pin central es **masa**.
- **Leer / escribir una llave**: la llave toca la **parte plana** del contacto — pin de datos izquierdo + pin central
  de masa.
- **Emular ante un lector**: la **parte saliente** del contacto toca el lector — pin de datos derecho + masa central.
- Si la masa no alcanza el borde del lector, usa dos cables: GPIO **17** (datos) y GPIO **8, 11 o 18** (masa).

## Menú principal

`Main Menu → iButton`:

![El menú iButton con Read, Saved, Add Manually y Settings](/screens/ibutton/menu.png)

| Elemento | Qué hace | Página |
|---|---|---|
| **Read** | Detectar el tipo de llave y leer su ID (y la memoria en DS1992/1996/1971) | [Lectura](/es/ibutton/read) |
| **Saved** | Explorar `/ext/ibutton/` — emular, escribir, editar, renombrar, borrar | [Lectura](/es/ibutton/read), [Escritura](/es/ibutton/write) |
| **Add Manually** | Crear una llave a partir del protocolo + ID en hex | [Añadir manualmente](/es/ibutton/add-manually) |
| **Settings** | **Write Blanks** — a qué tipos de llave virgen puede dirigirse una escritura | [Escritura](/es/ibutton/write) |

::: tip Unleashed
Frente a la documentación oficial, Unleashed añade una página **Settings → Write Blanks** (RW1990.1, RW1990.2,
TM2004, TM01x), muestra qué llave virgen se está probando durante una escritura y cuál la ha aceptado, escribe llaves
**Cyfral y Metakom** en llaves vírgenes **TM01x** y admite **DS1420**. El ReadMe menciona además un plugin iButton
Fuzzer.
:::

## Páginas de esta sección

- [Leer llaves](/es/ibutton/read) — leer, guardar, emular, errores de CRC.
- [Escribir en llaves vírgenes](/es/ibutton/write) — RW1990, TM2004, TM01x; Write ID frente a Full Write on Same Type.
- [Añadir manualmente](/es/ibutton/add-manually) — crear llaves a partir de un ID.
- [Protocolos compatibles](/es/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, 1-Wire genérico, Cyfral,
  Metakom.
- [Fuzzer](/es/ibutton/fuzzer) — qué incluye el firmware para la app de fuzzing de iButton.
- [Formato de archivo](/es/ibutton/file-format) — archivos `.ibtn`.

## Archivos

| Ruta | Contenido |
|---|---|
| `/ext/ibutton/*.ibtn` | Llaves guardadas (prefijo de nombre por defecto `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Ajuste Write Blanks |

::: warning
Copia y emula únicamente llaves que sean tuyas o que tengas autorización para probar.
:::
