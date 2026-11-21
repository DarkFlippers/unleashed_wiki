---
title: Protocolos compatibles
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Protocolos de 125 kHz compatibles

La tabla está elaborada a partir de `lib/lfrfid/protocols/` del firmware Unleashed. Todos los protocolos se pueden
**leer**, **guardar**, **emular** y **añadir manualmente**; las últimas columnas indican qué chips vírgenes pueden
albergarlos (consulta [Escritura](/es/rfid/write)).

- **Nombre** — tal como aparece en pantalla y se almacena en los archivos `.rfid` como `Key type`.
- **Lectura** — qué pasada de lectura lo decodifica: ASK, PSK o ambas.
- **Bytes** — longitud del campo `Data:`.

| Nombre | Fabricante | Lectura | Bytes | Campos mostrados | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | los mismos (tasa de bits RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | los mismos (tasa de bits RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (Wiegand de 26 bits) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, país, temperatura, indicador de animal… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | longitud en bits; formatos HID coincidentes | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, comprobación de CRC | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT de n bits (FC, Card) o RKKTH en claro (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = los destinos 8265/H5, 8210 y H5.5. ² El 8268 (Hitag S) solo acepta EM4100 a la tasa RF/64 y está
desactivado por defecto.

::: tip Unleashed
Frente a la lista de la documentación oficial, este firmware añade **Indala224** y una pasada de lectura a
**134,2 kHz** para FDX-A/FDX-B. La documentación oficial del formato de archivo tampoco incluye EM4100/32, EM4100/16,
Electra, Nexwatch, Radio Key, Noralsy ni Indala224 — aquí son valores válidos de `Key type`.
:::

## Notas sobre algunos protocolos

- **EM4100 / EM-Marin** — el tipo de llavero más habitual en la CEI («ЕМ-Марин»). ID de 40 bits; el FC es el 3.er byte
  y el número de tarjeta, los dos últimos. DEZ 8 / DEZ 10 son las formas decimales impresas en los llaveros.
- **Casi-Rusco C10106** — no es un protocolo aparte; es una trama EM4100 (normalmente RF/32). Cuando los datos
  encajan, la pantalla de información añade una línea `or C10106: credential card`, y Add Manually lo ofrece como
  formato de entrada.
- **HIDProx** — contenedor HID Prox genérico de 26 a 37 bits. El Flipper prueba las estructuras conocidas (H10304,
  H10302, S10401, H10306, Corp1000-35) e imprime el FC y el número de tarjeta de cada coincidencia.
- **Paradox** — la pantalla de información muestra el CRC y *CRC Mismatch, Invalid Card!* si no coincide.
- **Nombre antiguo de Indala26** — los archivos muy antiguos con `Key type: I40134` se convierten a Indala26 al
  cargarlos.

## Páginas relacionadas

- [Lectura](/es/rfid/read) · [Añadir manualmente](/es/rfid/add-manually) · [Escritura](/es/rfid/write) ·
  [Microchips de animales](/es/rfid/animal-microchips) · [Formato de archivo](/es/rfid/file-format)
