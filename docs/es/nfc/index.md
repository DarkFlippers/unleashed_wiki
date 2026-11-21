---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

El Flipper Zero lleva integrado un **módulo NFC de 13,56 MHz** capaz de **leer**, **guardar**, **emular** y, en
algunos tipos de tarjeta, **escribir** tarjetas de alta frecuencia: tarjetas y llaveros de acceso, tarjetas de
transporte, llaves de hotel, pegatinas NFC, juguetes de estilo amiibo y tarjetas bancarias (solo los datos
públicos). Los datos se guardan en la tarjeta microSD, en `/ext/nfc/`, como ficheros de texto `.nfc`.

::: warning Inserta una tarjeta microSD
La aplicación NFC guarda sus diccionarios, analizadores y tarjetas guardadas en la tarjeta microSD (`/ext/nfc/`).
Actualiza el firmware con la tarjeta SD puesta para que se instalen los recursos (diccionarios de claves,
`assets/*.nfc`, plugins de analizador).
:::

## Hardware

- Chip frontal NFC **ST25R3916**, responsable tanto de la lectura como de la emulación.
- Una **antena de 13,56 MHz** en la placa de antena RFID de doble banda de la parte trasera del aparato, junto a la
  antena de 125 kHz. Apoya las tarjetas contra el **centro de la parte trasera** del Flipper.

## Menú NFC

`Main Menu → NFC` abre este menú (las etiquetas son exactamente las del aparato en Unleashed):

![Menú principal de NFC: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Elemento | Qué hace |
|---|---|
| **Read** | Detecta el tipo de tarjeta y lee todo lo que puede, incluidos los ataques a claves de MIFARE Classic. Véase [Leer tarjetas](/es/nfc/read). |
| **Extract MFC Keys** | Emula una tarjeta MIFARE Classic para recopilar nonces de un lector (MFKey32). Véase [MFKey32](/es/nfc/mfkey). |
| **Saved** | Tus ficheros `.nfc` guardados: emular, escribir, desbloquear, renombrar, borrar. |
| **Extra Actions** | Leer un tipo de tarjeta concreto, gestionar diccionarios de claves, desbloquear NTAG/Ultralight y SLIX-L. |
| **Add Manually** | Genera una tarjeta virtual en blanco o una tarjeta NFC-A a partir de un UID/ATQA/SAK conocido. Véase [Añadir tarjetas a mano](/es/nfc/add-manually). |
| **Debug** | Solo visible con el modo depuración activado (`Settings → System → Debug`). |

`Extra Actions` contiene:

![Menú Extra Actions: Read Specific Card Type y los diccionarios de claves](/screens/nfc/extra_actions.png)

- **Read Specific Card Type**: salta la detección automática, útil para tarjetas híbridas.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys**: consulta los
  contadores del diccionario de sistema y de usuario, **Add** para añadir una clave, o **List** para listar (y
  borrar) las claves de usuario.
- **Unlock NTAG/Ultralight**: genera o introduce una contraseña antes de leer. Véase
  [Desbloquear tarjetas](/es/nfc/unlock-with-password).
- **Unlock SLIX-L**: desbloqueo por contraseña para etiquetas ICODE SLIX-L.

::: tip Unleashed
La app NFC viene del firmware oficial: su lector, su emulador y la mayoría de los analizadores de tarjetas.
Además, Unleashed añade, entre otras cosas: un diccionario de sistema de MIFARE Classic
ampliado (más de 4000 claves), lectura de **MIFARE Plus SL3** con diccionarios de claves AES, compatibilidad con
**MIFARE Ultralight AES**, llaves de portero automático **Texkom**, Add Manually para MIFARE Classic con UID
personalizado y para MIFARE Plus, **Save Keys to Dictionary** a partir de un volcado, el diccionario CUID (por
tarjeta) con barra de progreso de carga, y muchos analizadores de tarjeta adicionales (Troika, Plantain, Umarsh,
Zolotaya Korona, Kazan, Metromoney, la tarjeta social de Moscú, los billetes PPK y más).
:::

## Conceptos básicos

| Término | Significado |
|---|---|
| **UID** | Número de serie de la tarjeta, de 4 o 7 bytes (10 en algunas). Grabado de fábrica en las tarjetas genuinas. |
| **ATQA / SAK** | Bytes de respuesta durante la anticolisión que indican el tipo de tarjeta (por ejemplo, SAK `08` = MIFARE Classic 1K). |
| **Sector / bloque** | Unidad de memoria de MIFARE Classic: 16 bytes por bloque, 4 bloques por sector (sectores de 16 bloques al final de una 4K). |
| **Página** | Unidad de memoria de Ultralight/NTAG, de 4 bytes. |
| **Clave A / Clave B** | Claves Crypto-1 de 6 bytes que protegen cada sector de MIFARE Classic. |
| **Nonce** | Número aleatorio intercambiado durante la autenticación. Los nonces recopilados permiten calcular claves sin conexión. |
| **Tarjeta mágica** | Una tarjeta en blanco con el UID o el bloque 0 escribible. Véase [Tarjetas mágicas](/es/nfc/magic-cards). |

## Páginas de esta sección

### Uso cotidiano

- [Leer tarjetas](/es/nfc/read): leer, guardar y emular; qué tipos de tarjeta son compatibles y qué se obtiene de cada uno.
- [Añadir tarjetas a mano](/es/nfc/add-manually): generar tarjetas virtuales y crear una tarjeta NFC-A a partir de UID/ATQA/SAK.
- [Tarjetas compatibles (analizadores)](/es/nfc/supported-cards): tarjetas de transporte, de acceso y de juguetes que el Flipper puede decodificar.
- [Tarjetas bancarias (EMV)](/es/nfc/emv): qué se lee de una tarjeta bancaria y por qué no se puede clonar.
- [Desbloquear tarjetas con contraseña](/es/nfc/unlock-with-password): contraseñas de NTAG/Ultralight, claves de Ultralight C, SLIX-L.

### MIFARE Classic y recuperación de claves

- [MIFARE Classic](/es/nfc/mifare-classic): diccionarios, sectores, el flujo completo de lectura, emulación y escritura.
- [MFKey32: claves a partir del lector](/es/nfc/mfkey): recopilar nonces de un lector y recuperar claves.
- [Ataques anidados y puertas traseras de Fudan](/es/nfc/nested-fudan): ataques de solo tarjeta integrados en `Read`.
- [La aplicación MFKey](/es/nfc/mfkey-app): recuperar claves en el propio Flipper (MFKey 4.1).
- [Recuperación rápida de claves con qUnleashed](/es/nfc/qunleashed): todos los ataques en tu móvil o PC.

### Tarjetas en blanco y clonado

- [Tarjetas mágicas MIFARE Classic](/es/nfc/magic-cards): Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC y nombres locales.
- [NFC Magic 2.0](/es/nfc/nfc-magic): escribir y borrar tarjetas mágicas MIFARE Classic y Ultralight/NTAG.

### Otras familias de tarjetas

- [MIFARE Ultralight AES](/es/nfc/ultralight-aes): Ultralight protegido con AES (MF0AES20), claves, reescritura, mensajería segura.
- [MIFARE Plus](/es/nfc/mifare-plus): cómo se detectan S/X/SE/EV1/EV2 y los niveles de seguridad, claves AES de SL3.

### Sistemas de acceso (por @gromovyna)

- [Lectores Iron Logic](/es/nfc/iron-logic)
- [Alta dinámica en Iron Logic](/es/nfc/iron-logic-enrollment)
- [Filtros de los lectores Vizit](/es/nfc/vizit-filters)
- [Tarjetas Moskvyonok](/es/nfc/moskvyonok)

### Referencia

- [Formato de los ficheros NFC](/es/nfc/file-format): la estructura del fichero `.nfc` y los formatos de diccionario.

::: tip Aspectos legales
Trabaja con tus propias tarjetas o con permiso explícito. Copiar credenciales de acceso o billetes de transporte que
no te pertenecen puede ser ilegal.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG e ICODE son marcas registradas de
NXP B.V. FeliCa es una marca registrada de Sony Corporation.
