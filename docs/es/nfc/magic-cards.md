---
title: Tarjetas mágicas MIFARE Classic
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# Tarjetas mágicas MIFARE Classic (tarjetas en blanco)

En una etiqueta MIFARE Classic el **bloque 0**, que contiene el UID y los datos del fabricante, no se puede
reescribir. Para poder hacer una copia completa de una etiqueta así se inventaron unas **tarjetas en blanco**
especiales («tarjetas mágicas», «tarjetas con UID reescribible»), en las que el bloque 0 se puede escribir muchas
veces, o una sola.

Esta página, basada en el artículo de **@gromovyna**, explica brevemente qué es qué: de Gen1 a Gen4, los nombres
internacionales, los nombres del mercado local (de la antigua URSS) y qué comportamiento importa frente a cada
lector. Menciona etiquetas que se consiguen sin «bailes con pandereta» hacia China y que el autor ha comprobado o
visto en persona. Para escribirlas con el Flipper, véase [NFC Magic 2.0](/es/nfc/nfc-magic).

> Más abajo, «etiqueta», «chip», «tarjeta» y «llavero» son sinónimos: lo que importa es el chip de dentro y cómo se
> comporta, no el formato.

Lecturas adicionales:

- las excelentes [notas sobre tarjetas mágicas](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  de la documentación de Proxmark3 (en inglés), mantenidas al día por investigadores, que cubren también otros
  protocolos y dan detalles técnicos y comandos. Con experiencia y un Proxmark3 puedes ahorrar dinero comprando las
  tarjetas en blanco más baratas de un chip determinado y reconfigurándolas (en algunos chips);
- la [tabla de Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  del autor con las etiquetas de más abajo, su generación, sus nombres y si el Flipper Zero puede escribirlas.

## Generaciones

![Generaciones de etiquetas mágicas](/img/remote/f659ade923b6ca4f.png)

La división en generaciones («Gen») no es formal: es un intento de clasificar los chips por su comportamiento. Se
han consolidado cuatro generaciones. Un chip puede pertenecer a varias a la vez (por ejemplo, el **M1-4K**). El autor
sigue la clasificación estándar que usa Proxmark3, aunque no está del todo de acuerdo con ella en algunos chips.

| Gen | Apodo | Cómo se escribe el bloque 0 | Notas |
|---|---|---|---|
| **Gen1** | Backdoor | con comandos especiales de puerta trasera | Las más antiguas. Los comandos de puerta trasera permiten siempre escribir, leer (y borrar, en las Gen1a) la etiqueta. Como un filtro contra ellos es trivial, **todos los sistemas que se respetan los filtran**. |
| **Gen2** | Direct Write | el bloque 0 se escribe como cualquier otro bloque | Se pueden escribir desde móviles con NFC (sobre todo Android) con el software adecuado. |
| **Gen3** | APDU | con un comando APDU especial | Algunas permiten cambiar el UID por separado del bloque 0. Un bicho raro. |
| **Gen4** | Configurable | bloque de configuración | Tienen configuración y memoria, y se pueden preparar como distintos formatos de MFC (y más). Las más flexibles; pueden imitar el comportamiento de Gen1 y Gen2. |

## Gen1 (puerta trasera)

### Gen1a

Necesitan los comandos de puerta trasera `40` (7 bits) y `43` para escribir.

**UID** (nombre ruso: *Zero*). A nivel internacional existe con un identificador de 4 bytes; iKey LLC hizo
presumiblemente también una variante de 7 bytes (pendiente de confirmar que sea el mismo chip). Admite además la
lectura por puerta trasera (sin necesidad de claves) y el borrado.

**OTP 2.0** (ruso; se vende también como **MF** para el mercado ucraniano). Según iKey LLC, un diseño propio.
**Programable una sola vez**: después de la primera escritura (por la puerta trasera) el chip se bloquea y se
comporta como una MFC genuina. Tiene un **PRNG difícil**.

::: tip Nota del autor
La etiqueta no coincide del todo con una MFC genuina y se comporta de forma distinta bajo estrés, lo que permitió a
Iron Logic construir un filtro contra ella. Cómo funciona ese filtro era desconocido para el autor en el momento de
escribir esto.
:::

**MF-4** (ruso). Una OTP 2.0 mejorada. También **programable una sola vez** después de la primera escritura por la
puerta trasera, y con **PRNG difícil**. Según la descripción puede:

- cambiar la longitud del UID entre 4 y 7 bytes;
- fijar ATQA/SAK y ATS arbitrarios;
- admitir el comando PPS (que, por lo que el autor sabe, no forma parte del protocolo MFC en absoluto).

### Gen1b

Como las Gen1, pero funcionan justo después del comando `40` (7 bits). El autor no ha visto personalmente chips
Gen1b UID para MFC 1K.

**M1-4K**: un chip para copiar **MIFARE Classic 4K**. Se comporta como **Gen1b y Gen2 CUID** al mismo tiempo. Tiene
un **nonce estático `f17e64cd`**.

## Gen2 (escritura directa)

El bloque 0 se puede escribir directamente. Se pueden escribir desde Android con la aplicación
*Mifare Classic Tool*.

### CUID

Nombres rusos: **MF-3**, **MF3-2**, **MF-8**.

El chip principal, universal (en la mayoría de los casos) y más extendido. Esquiva los filtros Gen1 sencillos, es
reescribible muchas veces y se puede escribir desde un móvil: eso es lo que lo convirtió en el favorito del público.

::: tip Nota del autor
En la antigua URSS el interés por este chip, y los detalles de su comportamiento, importan por los lectores
**Iron Logic**, que tienen filtros contra las tarjetas en blanco. Esos lectores son baratos y, por tanto, están en
todas partes. Véase [Lectores Iron Logic](/es/nfc/iron-logic).
:::

Se venden muchos chips como «CUID», y pueden diferir en su comportamiento en casos límite. Los más nuevos son las
**CUID con nonce estático (MF-3.2)**: en el momento de escribir esto esquivan todos los filtros conocidos de la
antigua URSS (incluido el Iron Logic de «4 franjas»).

Nombres locales:

- **MF-3**: CUID que esquiva los filtros de Iron Logic de «3 franjas».
- **MF-8**: CUID que **no** esquiva los filtros OTP 1.0 de Iron Logic (un «lote defectuoso» cuyo número, el ocho,
  salió de una modificación sencilla del tres).
- **MF-3.2**: CUID con nonce estático, esquiva todos los filtros de Iron Logic contra MFC.

En China existe además una **«Perfect CUID»** que responde al comando RATS (el autor no le encontró ninguna
utilidad práctica).

## Gen3 (APDU)

Etiquetas que se controlan con comandos APDU. Actualmente es la categoría menos investigada. Potencialmente son
configurables por tipo, pero eso no se ha demostrado. No tienen nombre ruso.

Se venden para distintas variantes de MFC, en varias combinaciones:

- por memoria: **MFC 1K**, **MFC 4K**, **MIFARE Mini**;
- por longitud del identificador: **4 bytes**, **7 bytes**.

El autor posee las variantes MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b y MF Mini (S20) 7b (lo más probable
es que exista también la MFC 1K 4b) y las usó un par de veces para probar hipótesis con identificadores de 7 bytes,
antes de descubrir lo configurables que son los chips USCUID. Esa variedad (y la experiencia con otras etiquetas) le
hizo pensar que estos chips *podrían* ser configurables por tipo, longitud de UID y tamaño de memoria.

## Gen4 (configurable)

Los chips más avanzados: un bloque de configuración controla la etiqueta y su comportamiento.

### USCUID (GDM en los comandos de Proxmark3)

Un chip potente y barato con memoria de MFC 1K más bloques ocultos que usan algunas configuraciones. Según la
configuración admite tres clases de comandos de puerta trasera y Direct Write. Puede llevar identificadores de
4 o de 7 bytes, puede devolver una firma de MFC EV1, tiene modo de sombra y muchas otras funciones útiles.

Variantes de puerta trasera:

- despertar mágico **Gen1a** (`40`/`43`);
- despertar mágico **GDM** (`20`/`23`): exactamente como Gen1, pero con otros comandos. Hasta ahora no se han visto
  lectores con filtros contra esta puerta trasera (a diferencia de la Gen1a);
- **Magic Authentication** (seleccionar la etiqueta, `8000` + CRC, autenticación Crypto-1 con la clave
  `000000000000`).

Conociendo los principios de configuración puedes ajustar el chip al detalle para necesidades concretas. Con las
puertas traseras Gen1a/GDM activadas y comandos de estilo Gen1, se ha visto que la escritura y el borrado son poco
fiables. Los usuarios de Proxmark3 deberían leer la documentación del chip enlazada más arriba: comparado con la
Ultimate Magic Card cuesta poco y da mucho.

Configuraciones de mercado de USCUID:

| Nombre | Nombre ruso | Comportamiento |
|---|---|---|
| **FUID** | *OTP* | **Programable una sola vez**: Direct Write del bloque 0 y después el bloque se bloquea. Se comercializó en la antigua URSS como la «OTP» de iKey LLC, pero resultó ser un chip chino. En la configuración por defecto tiene una puerta trasera **GDM**, así que el identificador se puede cambiar más de una vez y los datos se pueden leer sin claves. A principios de noviembre de 2024 los investigadores informaron de versiones con la puerta trasera **bloqueada** en el mercado chino, lo que elimina la reutilización. |
| **UFUID** | — | Los chinos la venden como una «UID precintable». La configuración de fábrica tiene una puerta trasera **Gen1a** y es reescribible muchas veces. El «precintado»: los duplicadores chinos (CopyKey y similares) comprueban el bloque de configuración después de escribir y envían entonces un comando que lo cambia y desactiva la puerta trasera, convirtiendo la etiqueta en una MFC corriente. Es una USCUID recortada: solo acepta parte de la configuración. |
| **ZUID** | — | Una etiqueta UID sobre una USCUID recortada. Dados los precios de los chips, el sentido de esta variante no queda claro. Solo acepta parte de la configuración. |
| **GDM (GDMIC)** | — | Dio a USCUID uno de sus primeros nombres. Su característica clave es el **modo de sombra**: dentro del campo todos los cambios van a una memoria temporal que se pierde cuando el campo desaparece; la siguiente vez los datos vienen de la memoria permanente. Los chinos la anuncian para tarjetas de «viajes restantes» (por ejemplo, remontes). **No** sirve de nada frente a lectores que usan datos dinámicos (por ejemplo, los porteros Eltis con sus llaveros). |
| **GDCUID** | — | Una CUID implementada sobre USCUID. No se vende por separado, pero puede aparecer al comprar CUID. |
| **M1-7B** | — | Para escribir MIFARE Classic 1K con un identificador de **7 bytes**. Tiene una puerta trasera **GDM**. En modo de 7 bytes lee el identificador de un **bloque oculto**: escribir sin más un volcado en la memoria principal puede dejar la etiqueta «inservible» (recuperable). |

Los nombres **ZUID** y **GDCUID** los propuso el propio autor mientras escribía la documentación de chips mágicos de
Proxmark3.

### Ultimate Magic Card (GTU)

El chip más caro del momento: su gran memoria y sus configuraciones le permiten actuar no solo como distintos
formatos de MIFARE Classic y Mini, sino también como MIFARE Ultralight, NTAG y otros (aunque su implementación de
Ultralight es bastante limitada). La configuración permite:

- cambiar **ATQA/SAK** y **ATS**;
- longitudes de **identificador** de 4, 7 o 10 bytes;
- el **modo de sombra** y sus ajustes;
- activar y desactivar el **Direct Write** del bloque 0;
- cambiar la **contraseña de la puerta trasera** (que usan todos los comandos);
- fijar **Version** y **Signature**;
- pasar al **modo Ultralight** y configurarlo.

Antes de que aparecieran las CUID con nonce estático, la UMC era la única tarjeta en blanco que esquivaba los
filtros de Iron Logic de «4 franjas».

## Tabla resumen

![Tabla comparativa](/img/remote/a29bf09269c612bb.jpg)

La versión completa y mantenida está en la
[tabla de Google Sheets](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
del autor.

Si te da miedo comprar el chip equivocado en China, el autor recomienda la tienda
[FlipperMarket](https://flipper.market/catalog#services-3), donde un vendedor con experiencia selecciona y vende las
etiquetas principales que se necesitan en la CEI (y que el Flipper puede escribir).

## Qué puede escribir el Flipper

Según la documentación oficial, el Flipper Zero (mediante la aplicación **NFC Magic**) escribe tarjetas mágicas
**Gen1**, **Gen2** y **Gen4**, además de tarjetas **MIFARE Classic normales** (sin cambiar el UID):

| Tarjeta en blanco | Se puede configurar como |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (hace falta una tarjeta Gen2 compatible) |
| Gen4 (Ultimate) | cualquier MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
La compilación de Unleashed de **NFC Magic 2.0** detecta y escribe además tarjetas en blanco **USCUID-UL** de
Ultralight/NTAG (UL11, UL21 / «Ultra», NTAG213/215/216, UL-C, UL-5) e informa de resultados honestos
*Success / Partial / Fail*. Véase [NFC Magic 2.0](/es/nfc/nfc-magic).
:::

### Clonar una tarjeta en breve

1. [Lee](/es/nfc/read) y guarda el original. Asegúrate de que se han leído **todos** los sectores y páginas
   (recupera claves con [MFKey32](/es/nfc/mfkey), [ataques anidados](/es/nfc/nested-fudan) o
   [qUnleashed](/es/nfc/qunleashed) si hace falta).
2. Elige una tarjeta en blanco que el lector de destino acepte (véase más arriba: las Gen1 están filtradas casi en
   todas partes).
3. Escríbela con [NFC Magic](/es/nfc/nfc-magic).

::: tip Aspectos legales
Copia solo tus propias credenciales, o con permiso explícito.
:::

## Relacionado

[NFC Magic 2.0](/es/nfc/nfc-magic) · [MIFARE Classic](/es/nfc/mifare-classic) · [Lectores Iron Logic](/es/nfc/iron-logic) ·
[Filtros de los lectores Vizit](/es/nfc/vizit-filters)
