---
title: Añadir tarjetas a mano
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Añadir tarjetas NFC a mano

`Add Manually` crea una tarjeta virtual sin leer ninguna. Hay dos casos de uso:

- **Generar una tarjeta de un tipo estándar** con un UID aleatorio y un contenido por defecto (en blanco), como si
  tuvieras una tarjeta física recién sacada del paquete. Después la emulas para darla de alta en un sistema de
  acceso, o dejas que un móvil escriba datos NDEF (un enlace, una vCard) en ella.
- **Crear una tarjeta NFC-A a partir de valores conocidos**: UID, ATQA y SAK. Es suficiente para sistemas sencillos
  que solo comprueban el UID.

## Generar una tarjeta de un tipo estándar

1. Ve a `Main Menu → NFC → Add Manually`.
2. Elige el tipo de tarjeta (lista más abajo).

   ![Add Manually: lista de tipos de tarjeta con NFC-A 7-bytes UID seleccionado](/screens/nfc/add_manually.png)

3. Se abre una pantalla con el **UID** generado. Pulsa <kbd>→</kbd> **More**.
4. En el menú elige **Save** (también puedes usar antes **Change UID**, o **Emulate** directamente).
5. Escribe un nombre y confirma. La tarjeta se guarda en `/ext/nfc/`.

Tipos disponibles (con los nombres exactos del menú):

| Grupo | Tipos |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
El firmware original solo genera Ultralight/NTAG y MIFARE Classic. Unleashed añade **Mifare Ultralight C** (con la
clave 3DES por defecto `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, todas las variantes de **MIFARE Plus**, las
llaves de portero automático **Texkom** y **Change UID** justo después de generar, de modo que se puede crear una
MIFARE Classic con un UID personalizado («NFC Add manually → Mifare Classic with custom UID» en el ReadMe).
:::

::: tip ¿Qué tipo para un móvil?
Para escribir un enlace o una tarjeta de visita desde un móvil, **NTAG216** funciona en la mayoría de los casos.
Comprueba qué espera tu aplicación o tu sistema.
:::

## Crear una tarjeta NFC-A a partir de UID, ATQA y SAK

Algunos sistemas de acceso conceden el paso según el UID (a veces junto con ATQA/SAK). Si conoces esos valores:

1. Ve a `Main Menu → NFC → Add Manually`.
2. Selecciona **NFC-A 7-bytes UID** o **NFC-A 4-bytes UID**.
3. **"Enter SAK in hex"**: escribe el SAK (1 byte) y confirma.
4. **"Enter ATQA in hex"**: escribe el ATQA (2 bytes) y confirma.
5. **"Enter UID in hex"**: escribe el UID y confirma.
6. Pon nombre a la tarjeta y guárdala.

Valores habituales: MIFARE Classic 1K: ATQA `00 04` (UID de 4 bytes) o `00 44` (de 7 bytes), SAK `08`;
Ultralight/NTAG: ATQA `00 44`, SAK `00`. Truco para la entrada de bytes: pulsa <kbd>↑</kbd> repetidamente hasta que
aparezca el editor de nibbles (Unleashed).

## Usar la tarjeta

- **Emulate**: `Main Menu → NFC → Saved → <tarjeta> → Emulate` (o **Emulate UID** para una tarjeta NFC-A) y apoya el
  Flipper en el lector. Para «programar» una llave virtual en un sistema de acceso, pon el sistema en modo de alta
  según su manual y presenta la tarjeta emulada.
- **Edit UID** más adelante: `Saved → <tarjeta> → Edit UID` (tarjetas NFC-A).

::: warning
Cada sistema de acceso y cada aplicación da de alta las tarjetas de forma distinta; consulta su documentación para
saber qué tipos de tarjeta admite. Una tarjeta virtual no sirve de nada con sistemas que verifican la criptografía
de la tarjeta (DESFire, Plus SL3 con claves desconocidas, EMV).
:::

## Relacionado

[Leer tarjetas](/es/nfc/read) · [Formato de los ficheros NFC](/es/nfc/file-format) · [Tarjetas mágicas](/es/nfc/magic-cards)
