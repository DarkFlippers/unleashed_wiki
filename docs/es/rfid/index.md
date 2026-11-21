---
title: RFID de 125 kHz
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# RFID de 125 kHz

El RFID de baja frecuencia (LF) es la tecnología de «proximidad» que usan las tarjetas y llaveros de acceso baratos,
los tags de porteros automáticos, algunos sistemas de aparcamiento y de gimnasios, y los microchips de animales. Estos
tags normalmente solo emiten un ID fijo, sin criptografía, y por eso son fáciles de leer, emular y clonar.

Flipper Zero tiene una antena de 125 kHz en su parte trasera (en la antena de doble banda, junto a la bobina NFC de
13,56 MHz), controlada por el MCU STM32WB55. Con ella el Flipper puede **leer**, **guardar**, **emular** y
**escribir** tags LF.

::: tip Unleashed
La app de RFID de 125 kHz es del firmware oficial. Además, la versión de Unleashed tiene:
- un menú **Settings → Write Chips**: además de T5577 puede escribir **EM4305** y clones de Hitag Micro (**8265**,
  **8210**, **H5.5**), más un destino **8268** (Hitag S) que hay que activar expresamente. La pantalla de escritura
  muestra qué chip se está probando y cuál ha aceptado la escritura;
- **Write and set password** para llaves vírgenes T5577;
- formatos adicionales en **Add Manually** (introducir facility code / número de tarjeta en lugar de hex, HID
  H10304/H10302/S10401/H10306/Corp1000-35, Casi-Rusco) y visualización DEZ 8 / DEZ 10 para EM4100;
- una tercera pasada de lectura a **134,2 kHz** para tags de animales, y un modo específico **Read FDX-B (Animals)**;
- la app **T5577** incluida (leer/editar/restaurar bloques, probar, borrar por completo, limpiar y esnifar
  contraseñas).
:::

## Menú principal

`Main Menu → 125 kHz RFID` abre un menú con estos elementos (etiquetas exactas del firmware):

![El menú de RFID de 125 kHz con Read, Saved, Add Manually y Extra Actions](/screens/lfrfid/menu.png)

| Elemento | Qué hace | Página |
|---|---|---|
| **Read** | Detectar y leer un tag automáticamente (ciclo ASK → PSK → 134 kHz) | [Leer tags](/es/rfid/read) |
| **Saved** | Explorar `/ext/lfrfid/` — emular, escribir, editar, renombrar y borrar llaves guardadas | [Leer tags](/es/rfid/read), [Escritura](/es/rfid/write) |
| **Add Manually** | Crear una llave a partir de su protocolo e ID | [Añadir manualmente](/es/rfid/add-manually) |
| **Extra Actions** | Leer con una modulación fija (ASK, PSK, FDX-B); lectura/emulación RAW en modo Debug | [Leer tags](/es/rfid/read), [RAW](/es/rfid/raw) |
| **Settings** | **Write Chips** — a qué tipos de chip virgen puede dirigirse una escritura | [Escritura](/es/rfid/write) |

## Páginas de esta sección

- [Leer tags](/es/rfid/read) — leer, guardar y emular tags LF; lectura con una modulación fija.
- [Escribir en chips vírgenes](/es/rfid/write) — qué chips vírgenes funcionan (T5577, EM4305, Hitag Micro, 8268), el
  ajuste de write chips, escritura con contraseña y mensajes de error.
- [Añadir manualmente](/es/rfid/add-manually) — todos los protocolos de Add Manually y los formatos de entrada FC/ID.
- [Protocolos compatibles](/es/rfid/protocols) — tabla completa de protocolos: modulación, tamaño de los datos,
  campos decodificados y soporte de escritura.
- [Microchips de animales](/es/rfid/animal-microchips) — chips de mascotas FDX-B / FDX-A.
- [T5577 y Hitag Micro (por @gromovyna)](/es/rfid/t5577-hitag) — la historia de H5.5 / 8265 / 8210, la UX de
  escritura y el borrado del T5577.
- [App T5577](/es/rfid/t5577-app) — lectura, edición, restauración, prueba, borrado completo, limpieza de contraseña y
  esnifado de contraseña a nivel de bloque.
- [Grabación RAW](/es/rfid/raw) — grabar la señal ASK/PSK en bruto para investigar protocolos.
- [Fuzzer](/es/rfid/fuzzer) — qué incluye el firmware para la app de fuzzing de RFID.
- [Formatos de archivo](/es/rfid/file-format) — archivos `.rfid`, `.t5577` y `.raw`.

## Dónde están los archivos

| Ruta | Contenido |
|---|---|
| `/ext/lfrfid/*.rfid` | Llaves guardadas |
| `/ext/lfrfid/*.t5577` | Volcados de bloques T5577 (los abre la app T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | Grabaciones RAW |
| `/ext/lfrfid/.lfrfid.settings` | Ajuste Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Diccionario de contraseñas T5577 (se sobrescribe al actualizar) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Tus propias contraseñas T5577 |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Nombres de países para los chips FDX-B |

::: warning
Clona y emula únicamente tags que sean tuyos o que tengas autorización para probar.
:::
