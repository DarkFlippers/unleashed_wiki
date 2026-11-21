---
title: Tarjetas Moskvyonok
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Tarjetas, pulseras y llaveros Moskvyonok

Cómo están construidas las tarjetas escolares e infantiles «Moskvyonok» de Moscú y cómo copiar **tu propia** tarjeta a un formato más cómodo (pulsera, llavero). Basado en el artículo de @gromovyna (16-12-2024), con ayuda técnica de @Aleksei_Pashaev y de un miembro anónimo de la comunidad de Unleashed.

::: warning
Artículo técnico; la regulación legal varía. Usa únicamente tus propias tarjetas, recuerda que se parecen a un instrumento de pago y asume tú mismo las consecuencias.
:::

## Cómo se defienden estos sistemas del clonado

Apenas lo hacen. El sistema usa **MIFARE Classic** con claves estándar, sin diversificación, así que las claves se pueden encontrar con un diccionario corriente. Copiarlas es, por tanto, una [lectura de MIFARE Classic](/es/nfc/mifare-classic) normal más una escritura en una [tarjeta mágica](/es/nfc/magic-cards).

## Identifica tu tarjeta

| Tipo | UID | Bloque 0 | ATQA | SAK |
|---|---|---|---|---|
| UID de 4 bytes | 4 bytes | empieza por el UID | `00 04` | `08` |
| UID de 7 bytes | 7 bytes | empieza por el UID | `00 44` | `08` |
| 7 bytes, personalizada a 4 | 4 bytes | no empieza por el UID, parece un sinsentido | `00 44` | `08` |

### UID de 4 bytes

Etiquetas estándar, se escriben tal cual. Se recomiendan las tarjetas en blanco **Gen2 (CUID)**; las **Gen1 (UID/Zero)**, más baratas, también funcionan, aunque hay informes de que se filtraban.

### UID de 7 bytes

Etiquetas más nuevas, que se escriben tal cual en tarjetas en blanco **Zero 7 bytes** como si fueran etiquetas Gen1 corrientes, incluso con el Flipper Zero; o en etiquetas basadas en USCUID con duplicadores chinos o un Proxmark3 (hay que entender la estructura de memoria y de configuración, o puedes dejar la etiqueta inservible por software).

::: tip Unleashed
Escribir tarjetas en blanco Zero de 7 bytes en el Flipper Zero está disponible en Unleashed a partir de la versión 079, o con una aplicación NFC Magic compilada antes de la refactorización de NFC.
:::

### UID de 7 bytes personalizada a 4 bytes

Esto es MIFARE Classic EV1 en **modo de personalización**: un modo retrocompatible en el que la tarjeta tiene un identificador de 7 bytes pero responde a cada SELECT con un identificador de 4 bytes calculado a partir de él (hoja de datos MF1S50YYX_V1, sección 10.1.1; algoritmo en NXP AN10927, página 14). Escribirla tal cual produce basura. Un bloque 0 típico de Moskvyonok empieza por `34 00...`, pero eso depende del lote. En Proxmark3 el cálculo es `analyse nuid`.

Copiar a una tarjeta en blanco de 4 bytes (CUID):

1. Haz una copia del volcado original.
2. Calcula el UID nuevo (por ejemplo, `3400060000DBDC` pasa a ser `2FEDA2F1`).
3. Calcula el byte de suma de comprobación BCC (`2FEDA2F1` pasa a ser `0x91`).
4. Reescribe el bloque 0 de la copia así: el identificador de 4 bytes calculado, el BCC, `08`, `04`, `00` y el resto sin cambios (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Cambia el ATQA de la cabecera del fichero `.nfc` a `00 04` (la mayoría de las tarjetas en blanco tienen un ATQA fijo, pero hazlo por corrección).
6. Escribe el volcado en la tarjeta en blanco.

Las etiquetas basadas en USCUID pueden escribir el volcado tal cual y emular este comportamiento, pero eso requiere conocer la configuración del chip y no se trata aquí.

## Cosas que no funcionaron

El equipo probó a truncar los bytes altos, bajos y medios del UID, el orden de bytes invertido y el NUID a partir de los 7 bytes contra sistemas de 7 bytes; ninguna de esas vías funcionó.

## Relacionado

- [MIFARE Classic](/es/nfc/mifare-classic) · [Tarjetas mágicas](/es/nfc/magic-cards) · [Leer tarjetas](/es/nfc/read)
