---
title: Fuzzer de RFID
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer de RFID

Un **fuzzer** emula una larga serie de ID uno tras otro para probar cómo reacciona un lector — por ejemplo, si acepta
un ID por defecto, si se cuelga con datos mal formados, o para comprobar el rango de tarjetas válidas de tu propio
sistema.

::: tip Unleashed
El ReadMe de Unleashed menciona los **plugins LFRFID e iButton Fuzzer** entre sus funciones de NFC/RFID/iButton. El
fuzzer es una app externa, no forma parte del árbol de fuentes del firmware: a las compilaciones de release se añaden
packs de apps precompiladas, y el **extra apps pack** publicado con cada release contiene todas las apps conocidas que
funcionan. Sus menús dependen de la versión de la app, así que no se describen aquí.
:::

## Qué incluye el firmware: listas de UID de ejemplo

El firmware instala listas de ID de ejemplo para el fuzzer en **`/ext/rfidfuzzer/`**:

| Archivo | Protocolo | Longitud del ID (caracteres hex) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 bytes) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 bytes) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 bytes) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 bytes) |

Formato: un ID en hexadecimal por línea, `#` para comentarios y una **línea vacía al final** del archivo:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Crea tu propia lista copiando uno de los ejemplos y sustituyendo los ID; la longitud del ID debe coincidir con el
tamaño de clave del protocolo (consulta [protocolos](/es/rfid/protocols), columna *Bytes*).

El FAQ de Unleashed enlaza archivos de diccionario ya preparados compartidos por la comunidad:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) y
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Usa el fuzzer solo con lectores que sean tuyos o que tengas autorización para probar.
:::

## Páginas relacionadas

- [Protocolos](/es/rfid/protocols) · [Lectura](/es/rfid/read) · [Fuzzer de iButton](/es/ibutton/fuzzer)
