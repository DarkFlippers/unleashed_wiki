---
title: Formatos de archivo
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# Formatos de archivo del RFID de 125 kHz

En `/ext/lfrfid/` residen tres tipos de archivo:

| Extensión | Qué describe | Lo crea |
|---|---|---|
| `.rfid` | Una **tarjeta**: protocolo + ID | Read → Save, Add Manually |
| `.t5577` | Un **chip**: todos los bloques de un T5577 | [App T5577](/es/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | Una grabación de señal en bruto | [RAW](/es/rfid/raw) |

## `.rfid` — llave LF RFID

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

El archivo almacena una llave del tipo indicado por `Key type`.

| Campo | Descripción |
|---|---|
| `Key type` | Nombre del protocolo, exactamente como en la [tabla de protocolos](/es/rfid/protocols) |
| `Data` | Datos de la llave en hexadecimal; su longitud es fija para cada protocolo |

Valores válidos de `Key type` en este firmware: `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Historial de versiones: 1 — versión inicial. Los archivos antiguos con `Key type: I40134` (3 bytes) se convierten a
`Indala26` al cargarlos.

::: tip
Puedes crear una llave en el ordenador: escribe las cuatro líneas de arriba con el `Key type` adecuado y el número
correcto de bytes en `Data`, cópiala a `/ext/lfrfid/` y aparecerá en **Saved**.
:::

## `.t5577` — volcado de T5577

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

Un archivo `.t5577` describe el **silicio**; un archivo `.rfid` describe la **tarjeta**. Un T5577 configurado como un
EM4100 se puede guardar de las dos formas, y no son intercambiables: `.t5577` incluye la configuración que determina
cómo habla el chip y la contraseña que lo protege.

| Campo | Descripción |
|---|---|
| `Page 0 blocks read` | Bloques de la página 0 cuyos valores proceden del chip, separados por espacios |
| `Page 0 Block 0..7` | Contenido del bloque, 4 bytes hex, MSB primero. Bloque 0 = configuración, bloque 7 = almacén de la contraseña |
| `Page 1 blocks read` | Bloques de la página 1 que se han leído |
| `Page 1 Block 0..3` | El bloque 0 repite la configuración; los bloques 1–3 contienen los datos de trazabilidad de fábrica |
| `Password` | Opcional. Una contraseña que **se sabe que funciona** en el chip |

Reglas clave:

- **Todos los bloques tienen una clave**, leídos o no. Solo los bloques nombrados en `blocks read` son contenido real;
  el resto es relleno y nunca debe escribirse en un tag. Un archivo que no liste ningún bloque se rechaza.
- Un chip protegido rechaza la lectura del bloque 0 que necesita la detección, así que sin la contraseña no obtienes
  ningún volcado (ni siquiera parcial). Un volcado parcial significa que el tag se salió del campo.
- `Password` y `Page 0 Block 7` son hechos distintos y pueden no coincidir: el bloque 7 es lo que contenía el bloque
  al leerlo (almacenamiento normal si no hay contraseña activada), mientras que `Password` es una credencial que ha
  funcionado. Limpiar una contraseña solo borra el bit del bloque 0, así que el bloque 7 conserva el valor antiguo.
- La línea de comentario que decodifica el bloque 0 es solo para humanos.

### Orden de restauración

Al volver a escribir un volcado (app T5577 → **Write to Tag**), el orden coincide con el de Proxmark3:

1. Bloques 1–7 de la página 0. A partir del bloque 7, las escrituras deben usar la contraseña que ahora está
   almacenada en el bloque 7.
2. Bloques 1–3 de la página 1 (el bloque 0 de la página 1 nunca se escribe). Los chips auténticos se niegan a cambiar
   los bloques 1–2 — se informa como *unchanged*, no como un fallo.
3. El bloque 0 de la página 0 **al final** — cambia cómo habla el chip.
4. Solo se escriben los bloques listados en `blocks read`.
5. Un bloque 0 a cero **nunca** se escribe: un chip que lo contenga no responde absolutamente nada, y no hay vuelta
   atrás.

Las tramas de escritura no reciben respuesta, así que el éxito solo se conoce releyendo los bloques.

## `.raw` — grabaciones RAW

Archivos binarios que escribe la lectura RAW. Empiezan con una cabecera:

| Campo | Tipo | Valor |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | frecuencia de portadora, Hz (125000 o 134200) |
| duty_cycle | float | ciclo de trabajo de la portadora |
| max_buffer_size | uint32 | búfer más grande del archivo |

seguida de búferes, cada uno precedido por su tamaño, que contienen pares *(pulso, duración)* codificados como varint. Usa `rfid raw_analyze <filename>` en la CLI para
decodificarlos.

## Páginas relacionadas

- [Protocolos](/es/rfid/protocols) · [App T5577](/es/rfid/t5577-app) · [RAW](/es/rfid/raw)
