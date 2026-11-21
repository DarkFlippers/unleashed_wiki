---
title: Añadir llaves manualmente
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Añadir llaves de 125 kHz manualmente

Puedes crear una llave sin tener el tag físico: elige el protocolo y escribe sus datos. El resultado se guarda igual
que una llave leída y se puede emular o [escribir en un chip virgen](/es/rfid/write).

**Úsalo cuando** conozcas el número impreso en una tarjeta o registrado en una base de datos de control de acceso,
quieras restaurar una llave a partir de tus notas o quieras probar un lector con un ID concreto.

## Pasos

1. Ve a `Main Menu → 125 kHz RFID → Add Manually`.
2. Elige el protocolo o formato de la lista (véase más abajo).

   ![Lista de tipos de tag de Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 y Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. En los formatos que tienen una estructura de facility code / número de tarjeta se te ofrece una elección:
   - **Enter FC/ID** — escribe los campos decimales uno a uno. El encabezado muestra el nombre del campo y su rango,
     por ejemplo `Facility Code (0-255)`. <kbd>Back</kbd> retrocede al campo anterior.
   - **Enter Hex Data** — escribe los bytes en bruto.

   Los demás protocolos pasan directamente al editor hexadecimal *Enter the data in hex*.

   ![El editor "Enter the data in hex" con los bytes del tag sobre un teclado hexadecimal en pantalla](/screens/lfrfid/add_manually_data.png)

4. Introduce un nombre y guarda. La llave se almacena como `/ext/lfrfid/<name>.rfid`.

Para cambiar una llave guardada más tarde: `Saved` → llave → **Edit** (editor hexadecimal, mismo nombre de archivo).

::: tip Unleashed
Introducir el **FC / número de tarjeta** en lugar de hexadecimal, los formatos **HID** adicionales y **Casi-Rusco**
son añadidos de Unleashed. El firmware de fábrica solo acepta hexadecimal. Las sumas de comprobación y la paridad
Wiegand se calculan por ti.
:::

## La lista, en el orden del dispositivo

| Etiqueta del menú | Guardado como (`Key type`) | Entrada | Bytes hex |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID o hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID o hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID o hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID o hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID o hex | 4 |
| AWID | AWID | FC/ID o hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID o hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID o hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Rangos de los campos de «Enter FC/ID»

| Formato | Campos (decimales) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (se guardan en los 3 últimos bytes; los 2 primeros a cero) |
| HID H10301 (Wiegand de 26 bits) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (formato de 26 bits, se añade la paridad) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 bits, se añaden paridad y CRC) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (se añade la suma de comprobación) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (tal como lo imprime el sistema de acceso; se guarda como EM4100/32) |
| HID H10304 (37 bits) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 bits) | Solo Card Number (35 bits) |
| HID S10401 (37 bits) | Facility Code 0–63, Card Number (29 bits) |
| HID H10306 (34 bits) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 bits) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Números de tarjeta grandes
La entrada numérica guarda un valor de 32 bits con signo, así que la parte más alta de un campo más ancho de 31 bits
(por ejemplo el número de tarjeta de 35 bits de H10302) solo se puede introducir mediante **Enter Hex Data** /
**Edit**.
:::

## Consejos

- Un número impreso de EM4100 como `0001234567` suele ser la forma **DEZ 10**; después de guardar, compáralo en la
  pantalla **Info** (muestra FC/Card, DEZ 8 y DEZ 10) para asegurarte de que has escrito lo correcto.

  ![Pantalla Info de un tag guardado: nombre de archivo, EM-Micro EM4100, datos hex, FC/Card, DEZ 8 y DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 y EM4100/16 son la misma trama a tasas de bits RF/32 y RF/16; elige la que corresponda a cómo se lee el
  original.
- En los protocolos que solo aceptan hexadecimal, la forma más sencilla de obtener los bytes correctos es leer una vez
  el tag real y copiar el valor de `Hex:`.

## Páginas relacionadas

- [Protocolos](/es/rfid/protocols) · [Formato de archivo](/es/rfid/file-format) ·
  [Escritura](/es/rfid/write) · [Lectura](/es/rfid/read)
