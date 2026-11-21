---
title: Formato de archivo
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Formato de archivo de llave iButton (`.ibtn`)

Las llaves guardadas se almacenan en `/ext/ibutton/` con la extensión `.ibtn`. Un archivo contiene una llave con todos
los datos que necesita su protocolo.

## Ejemplo

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Una llave DS1990 (los bytes son un ejemplo; una ROM real termina con un CRC válido):

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Una llave Cyfral:

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Versión 2 (actual)

Los campos posteriores a `Protocol` dependen del protocolo.

| Campo | Tipo | Descripción |
|---|---|---|
| `Protocol` | cadena | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | ROM de 8 bytes (solo protocolos Dallas) |
| `Sram Data` | hex | Contenido de la SRAM (DS1992: 128 bytes, DS1996: 8192 bytes) |
| `Eeprom Data` | hex | Contenido de la EEPROM (DS1971: 32 bytes) |
| `Data` | hex | Código de la llave (Cyfral: 2 bytes, Metakom: 4 bytes) |

Notas:
- **(non-specific)** es el cajón de sastre para dispositivos 1-Wire desconocidos (etiqueta del menú *Dallas
  (non-specific)*). Contiene solo la ROM y no realiza ninguna comprobación — úsalo para llaves con un family code o un
  CRC deliberadamente inválidos. El firmware lo guarda como `Protocol: (non-specific)`; el nombre `DSGeneric` que usan
  la documentación oficial y los archivos antiguos se sigue aceptando.
- **DS1420** es totalmente compatible con DS1990; solo cambia el family code (`0x81` frente a `0x01`).
- Los protocolos nuevos no exigen subir la versión del formato — cada protocolo define sus propios campos.

## Versión 1 (obsoleta)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Campo | Tipo | Descripción |
|---|---|---|
| `Key type` | cadena | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Datos de la llave |

Los archivos de la versión 1 se siguen cargando (`Dallas` se interpreta como DS1990) y se convierten a la versión 2 al
guardarlos.

## Páginas relacionadas

- [Protocolos](/es/ibutton/protocols) · [Añadir manualmente](/es/ibutton/add-manually) ·
  [Lectura](/es/ibutton/read)
