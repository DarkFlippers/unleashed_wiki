---
title: Protocolos compatibles
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks, https://docs.flipper.net/zero/ibutton/read, https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Protocolos iButton compatibles

Elaborado a partir de `lib/ibutton/protocols/` del firmware Unleashed. El firmware agrupa los protocolos en **Dallas**
(1-Wire) y **misc** (Cyfral, Metakom).

| Protocolo (nombre de archivo) | Etiqueta del menú | Family code | Memoria | Emulación | Write ID a | Full Write on Same Type |
|---|---|---|---|---|---|---|
| `DS1990` | Dallas DS1990 | `01` | — | ✓ | RW1990.1, RW1990.2, TM2004, TM01x | — |
| `DS1420` | Dallas DS1420 | `81` | — | ✓ | RW1990.1, RW1990.2, TM2004 | — |
| `DS1992` | Dallas DS1992 | `08` | 128 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1996` | Dallas DS1996 | `0C` | 8192 B SRAM (`Sram Data`) | ✓ | TM2004 | ✓ |
| `DS1971` | Dallas DS1971 | `14` | 32 B EEPROM (`Eeprom Data`) | ✓ | TM2004 | ✓ |
| `(non-specific)` | Dallas (non-specific) | cualquiera | — (solo ROM) | ✓ | TM2004 | — |
| `Cyfral` | Cyfral | — | Código de 2 bytes | ✓ | TM01x | — |
| `Metakom` | Metakom | — | Código de 4 bytes | ✓ | TM01x | — |

## Dallas 1-Wire

La «touch memory» de Dallas Semiconductor (hoy Analog Devices). Cada dispositivo tiene una ROM de 8 bytes: family
code, número de serie de 48 bits y CRC-8. El Flipper comprueba el CRC e identifica el tipo por el family code.

- **DS1990 (DS1990A)** — la llave clásica, solo con ID, que usan la mayoría de los porteros automáticos.
- **DS1420** — totalmente compatible con DS1990, solo cambia el family code (`81` en lugar de `01`).
- **DS1992 / DS1996** — llaves con memoria SRAM; DS1971 — con EEPROM. El Flipper lee la memoria, puede mostrarla
  (**Data Info**), emularla y copiarla a una llave del mismo tipo.
- **Dallas (non-specific)** — cajón de sastre para cualquier otro dispositivo 1-Wire: solo se lee la ROM y no se
  comprueba nada. También sirve para crear una llave con un family code o un CRC intencionadamente incorrectos.

## Cyfral

Un protocolo de llaves de portero automático habitual en Rusia y la CEI; no es 1-Wire. El código se almacena en 2 bytes. Se puede emular y escribir en una llave virgen TM01x.

## Metakom

Otro protocolo de porteros automáticos de la CEI. El código ocupa 4 bytes y cada byte lleva un bit de paridad — una
llave con paridad incorrecta se marca como inválida y no se escribe. Se puede emular y escribir en una llave virgen
TM01x.

## Llaves vírgenes

| Llave virgen | Acepta | Comportamiento |
|---|---|---|
| **RW1990.1** | ROM Dallas (8 bytes) | Desbloquear, escribir (bits invertidos), bloquear |
| **RW1990.2** | ROM Dallas (8 bytes) | Desbloquear, escribir, bloquear |
| **TM2004** | ROM Dallas (8 bytes) | Escribe desde la dirección 0 con relectura de comprobación de cada byte |
| **TM01x** | ROM Dallas, Cyfral, Metakom | Cyfral/Metakom se escriben como una trama de 36 bits (prefijo de 4 bits + 32 bits de código), se verifican y después se **finalizan** (irreversible). Los ID Dallas no se finalizan |

Consulta [Escritura](/es/ibutton/write) para ver su uso.

::: tip Unleashed
La documentación oficial no menciona DS1420, el ajuste Write Blanks ni la escritura en TM01x para Cyfral/Metakom.
:::

## Páginas relacionadas

- [Lectura](/es/ibutton/read) · [Escritura](/es/ibutton/write) ·
  [Formato de archivo](/es/ibutton/file-format)
