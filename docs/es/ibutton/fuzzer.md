---
title: Fuzzer de iButton
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer de iButton

Un **fuzzer** emula una serie de ID de llave uno tras otro para ver cómo reacciona un lector — por ejemplo, para
comprobar si tu propio portero automático acepta ID por defecto o mal formados.

::: tip Unleashed
El ReadMe de Unleashed menciona los **plugins LFRFID e iButton Fuzzer**. El fuzzer es una app externa, no forma parte
del árbol de fuentes del firmware: a las compilaciones de release se añaden packs de apps precompiladas, y el **extra
apps pack** publicado con cada release contiene todas las apps conocidas que funcionan. Sus menús dependen de la
versión de la app, así que no se describen aquí.
:::

## Qué incluye el firmware: listas de UID de ejemplo

El firmware instala listas de ID de ejemplo en **`/ext/ibtnfuzzer/`**:

| Archivo | Protocolo | Longitud del ID (caracteres hex) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 bytes) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 bytes) |
| `example_uids_metakom.txt` | Metakom | 8 (4 bytes) |

Formato: un ID en hexadecimal por línea, `#` para comentarios y una **línea vacía al final**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Para crear tu propia lista, copia un ejemplo y sustituye los ID; la longitud debe coincidir con la del protocolo.

Diccionarios de la comunidad enlazados desde el FAQ de Unleashed:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Usa el fuzzer solo con lectores que sean tuyos o que tengas autorización para probar.
:::

## Páginas relacionadas

- [Protocolos](/es/ibutton/protocols) · [Emular llaves](/es/ibutton/read) · [Fuzzer de RFID](/es/rfid/fuzzer)
