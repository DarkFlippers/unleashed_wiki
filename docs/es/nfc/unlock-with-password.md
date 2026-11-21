---
title: Desbloquear tarjetas con contraseña
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Desbloquear tarjetas con contraseñas y claves

Las tarjetas organizadas en **páginas** (MIFARE Ultralight, NTAG) pueden proteger parte de su memoria. Si `Read`
muestra **"Some Pages Are Locked!"** / **"Password-protected pages!"** y `Pages Read: X/Y` con X menor que Y, la
tarjeta necesita una contraseña o una clave. Según la tarjeta:

| Tarjeta | Protección | Cómo la desbloquea el Flipper |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | contraseña (PWD) de 4 bytes + PACK de 2 bytes | capturarla del lector, generarla a partir del UID (amiibo, Xiaomi) o introducirla a mano |
| Ultralight C | clave 3DES de 16 bytes | ataque de diccionario (automático) o introducir la clave a mano |
| Ultralight AES | clave AES de 16 bytes | ataque de diccionario (automático) o introducir la clave a mano; véase [Ultralight AES](/es/nfc/ultralight-aes) |
| ICODE SLIX-L | contraseña de 4 bytes | `Extra Actions → Unlock SLIX-L` |

::: danger Las contraseñas incorrectas pueden bloquear la tarjeta
Muchas tarjetas cuentan las autenticaciones fallidas (`AUTHLIM`) y se bloquean de forma permanente después de
demasiadas. El Flipper avisa con **"Risky action! Wrong password can block your card."** antes de probar una
contraseña. No hagas fuerza bruta.
:::

## Capturar la contraseña del lector

Si tienes la tarjeta y el lector que la acepta: emula la tarjeta, deja que el lector envíe su contraseña, captúrala y
después lee la tarjeta con ella.

1. [Lee y guarda](/es/nfc/read) la tarjeta.
2. Ve a `Main Menu → NFC → Saved → <tarjeta> → Unlock`.
3. Selecciona **Unlock With Reader**. La pantalla dice *"Touch the reader to get password..."*. Toca el lector con
   el Flipper.
4. Cuando se captura la contraseña verás **Password Captured!** con su valor. Pulsa **Continue**.
5. Apoya la tarjeta en la parte trasera del Flipper (*"Hold card next to Flipper's back"* y después
   *"Don't move"*).
6. Cuando las páginas estén desbloqueadas (**"All Pages Are Unlocked!"**), ve a **More → Save**, pon nombre a la
   tarjeta y guárdala.

Si no se captura nada (*"Password not captured."*), puede que el lector no use contraseña, o que la tarjeta
pertenezca a otro lector.

`Unlock With Reader` no se ofrece en Ultralight C (usa autenticación mutua 3DES y no se envía ninguna contraseña en
claro).

## Generar la contraseña a partir del UID

En las figuras de **toys-to-life** (NTAG215 de estilo amiibo) y en los filtros del **purificador de aire de
Xiaomi**, la contraseña se deriva del UID de la tarjeta.

1. Ve a `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (o, en una tarjeta guardada, a `Saved → <tarjeta> → Unlock`).
2. Selecciona **Auth As Ameebo** o **Auth As Xiaomi Air Purifier**.
3. Confirma el aviso y apoya la tarjeta en el Flipper.
4. Cuando las páginas estén desbloqueadas, usa **Save** para guardar la tarjeta.

## Introducir la contraseña a mano

1. `Main Menu → NFC → Saved → <tarjeta> → Unlock` (o `Extra Actions → Unlock NTAG/Ultralight` antes de leer).
2. Selecciona **Enter Password Manually**.
3. **"Enter the password in hex"**: escribe los 4 bytes y confirma.
4. Confirma el aviso *"Try to unlock the card with password: …"* y apoya la tarjeta en el Flipper.
5. Usa **Save** para guardar la tarjeta desbloqueada.

## Ultralight C: claves 3DES

Las tarjetas Ultralight C usan una clave 3DES de 16 bytes. El Flipper tiene un diccionario integrado de claves
conocidas (`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 claves, incluida la clave de muestra de NXP
`BREAKMEIFYOUCAN!`) y un diccionario de usuario (`mf_ultralight_c_dict_user.nfc`).

- En `Read`, si la tarjeta no se puede leer por completo, el ataque de diccionario se ejecuta por sí solo:
  cabeceras **"MFUL C User Dictionary"** y después **"MFUL C System Dictionary"**, con `Key found: Yes/No` y
  `Pages read: X/Y`.
- En una tarjeta guardada e incompleta: **Unlock with Dictionary** vuelve a ejecutar el ataque; **Unlock** pide
  **"Enter key in hex"** (16 bytes) y después muestra **"Risky Action! Unlock with key: … ?"** con **Unlock** /
  **Cancel**.
- Añadir tus propias claves: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Un volcado de Ultralight C completamente leído ofrece **Write (Keep Key)** (conserva la clave 3DES de la tarjeta de
destino) y **Write (Copy Key)** (escribe también las páginas de clave del volcado) en una tarjeta del mismo tipo.

::: tip Unleashed
La introducción manual de claves 3DES y AES, la reescritura de Ultralight C y AES con Keep Key o Copy Key, y el
diccionario de Ultralight AES (`Extra Actions → MIFARE UL AES Keys`) son funciones de Unleashed.
:::

## ICODE SLIX-L

1. Ve a `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Elige **Enter Password Manually** (4 bytes en hexadecimal) o **Auth As TommyBox** (la contraseña conocida de las
   etiquetas TommyBox).
3. Apoya la etiqueta en el Flipper (*"Unlocking — Hold card next to Flipper's back"*).
4. En **SLIX Unlocked!** pulsa **More** para continuar hasta el resultado de la lectura y guardarlo, o **Retry**.

## Si el desbloqueo ha fallado

- Puede que la tarjeta esté emparejada con otro lector, o que use una clave derivada por tarjeta.
- La contraseña es correcta pero algunas páginas siguen bloqueadas: los bits de bloqueo o los ajustes de
  `AUTH0`/`PROT` pueden hacer que algunas páginas sean de solo lectura o ilegibles sin autenticación de forma
  permanente.
- Para Ultralight AES, consulta la nota sobre el orden de los bytes en
  [Ultralight AES](/es/nfc/ultralight-aes).

## Relacionado

[Leer tarjetas](/es/nfc/read) · [Ultralight AES](/es/nfc/ultralight-aes) ·
[Filtros de los lectores Vizit](/es/nfc/vizit-filters) · [Formato de los ficheros NFC](/es/nfc/file-format)
