---
title: Leer tarjetas
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Leer, guardar y emular tarjetas NFC

`Read` es el punto de entrada principal de la aplicación NFC. El Flipper detecta el protocolo por sí mismo, lee
todos los datos a los que puede llegar, ejecuta los ataques a claves cuando corresponde (MIFARE Classic,
Ultralight C, Ultralight AES, MIFARE Plus SL3) y después te permite guardar, emular o escribir el resultado.

## Leer una tarjeta

1. Ve a `Main Menu → NFC → Read`.
2. La pantalla dice **"Reading — Hold card next to Flipper's back"**. Pon la tarjeta plana contra el **centro de la
   parte trasera** del Flipper y mantenla quieta.

   ![Pantalla de lectura: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Cuando se encuentra la tarjeta verás **"Don't move"** mientras se leen los datos. Con las tarjetas protegidas
   puede aparecer una pantalla de ataque (ataque de diccionario, ataque anidado; véase
   [MIFARE Classic](/es/nfc/mifare-classic)).

   ![Ataque con el diccionario de sistema de MIFARE Classic: desbloqueando el sector 9, 19 de 32 claves encontradas](/screens/nfc/dict_attack.png)

4. La pantalla de resultados muestra el nombre de la tarjeta y un resumen. Si un
   [analizador](/es/nfc/supported-cards) ha reconocido la tarjeta, verás los datos decodificados (saldo, número de
   viajes, número de tarjeta…).

   ![Resultado de la lectura: MIFARE Classic 1K con UID, 32/32 claves encontradas y 16/16 sectores leídos](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: pregunta *"Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: abre el menú de la tarjeta.
5. En **More**, elige **Save**, escribe un nombre en **"Name the card"** y confirma. El fichero va a
   `/ext/nfc/<nombre>.nfc`.

El menú `More` después de leer siempre tiene **Save** e **Info**; según el tipo de tarjeta tiene además
**Emulate** / **Emulate UID**, elementos específicos del protocolo (por ejemplo **Unlock**, **Show Keys**,
**Extract MFC Keys**, o **Transactions** en EMV).

### Tarjetas multiprotocolo

Algunas tarjetas responden como más de un protocolo (por ejemplo, una tarjeta bancaria que además contiene un área
MIFARE Classic). El Flipper muestra entonces un menú **"Multi-protocol card"** con entradas como
**Read as MIFARE Classic**. Para saltarse la detección automática por completo, usa
`Main Menu → NFC → Extra Actions → Read Specific Card Type`, elige el tipo y pulsa <kbd>OK</kbd>.

## Tipos de tarjeta compatibles

| Familia | Tipos de tarjeta (con el nombre que les da el firmware) | Leer | Emular | Escribir |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Cualquier tarjeta NFC-A: UID, ATQA, SAK | sí | solo UID | — |
| MIFARE Classic | Mini, 1K, 4K (UID de 4 y de 7 bytes) | sectores con claves conocidas | completa | solo en la tarjeta de origen |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | páginas abiertas, más después del desbloqueo | completa | el mismo tipo (véase más abajo) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 como Classic, SL3 con claves AES | SL3 completa, el resto solo UID | SL3 en la tarjeta de origen |
| MIFARE DESFire | DESFire | aplicaciones y ficheros sin proteger | solo UID | — |
| ISO14443-4A | Tarjetas ISO-DEP desconocidas | UID, ATQA, SAK, ATS | solo UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; etiquetas NFC Forum Type 4 (NDEF) | sí | NTAG4xx: UID; T4T: completa | T4T: sí |
| EMV | Tarjetas bancarias | datos públicos | — | — |
| ISO14443-3B / -4B | Tarjetas NFC-B | UID, datos de aplicación, información de protocolo | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | sí | — | — |
| ISO15693-3 (NFC-V) | Etiquetas NFC-V desconocidas | UID + bloques legibles | completa | sí |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | sí, con desbloqueo por contraseña | completa | sí |
| FeliCa | FeliCa (Lite-S y otras) | IDm, PMm, bloques | completa | — |
| Texkom | Llaves de portero automático Texkom TK13, TK15, TK17, MMBIT | sí | completa | — |

::: tip Unleashed
Las llaves **Texkom** (llaveros de portero automático de 13,56 MHz habituales en Rusia que no implementan ningún
estándar ISO), los volcados de **MIFARE Plus SL3** con claves AES, **Ultralight AES** y la compatibilidad ampliada
de **Write** para Ultralight son aportaciones del firmware que no encontrarás en el original. MIFARE Classic recibe
además el diccionario CUID y **Save Keys to Dictionary**.
:::

### MIFARE Classic

Para leer sectores, el Flipper necesita las claves: hasta **10 claves para 5 sectores** (Mini), **32 claves para
16 sectores** (1K) u **80 claves para 40 sectores** (4K). Prueba la caché de claves por tarjeta, después los
diccionarios CUID, de usuario y de sistema, y por último los ataques anidados. Los detalles están en la página de
[MIFARE Classic](/es/nfc/mifare-classic); si siguen faltando claves, véase [MFKey32](/es/nfc/mfkey) y
[Ataques anidados](/es/nfc/nested-fudan).

### MIFARE Ultralight y NTAG

Las páginas abiertas se leen directamente. Las páginas protegidas por una contraseña (NTAG21x, Ultralight EV1), una
clave 3DES (Ultralight C) o una clave AES (Ultralight AES) permanecen bloqueadas hasta que las desbloqueas; véase
[Desbloquear tarjetas](/es/nfc/unlock-with-password) y [Ultralight AES](/es/nfc/ultralight-aes). Ultralight C y
Ultralight AES ejecutan un ataque de diccionario automáticamente.

**Write** se ofrece para un volcado completamente leído de **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** y **Ultralight AES**, sobre una tarjeta del mismo tipo. Ultralight C y AES tienen dos
entradas: **Write (Keep Key)** conserva la clave de la tarjeta de destino y **Write (Copy Key)** escribe también la
clave del volcado. Si el destino está protegido por una contraseña, por AUTH0 o por bits de bloqueo, obtendrás
*"Card protected by password, AUTH0 or lock bits"*.

### Tarjetas desconocidas

De una tarjeta NFC-A desconocida solo se guardan el UID, el ATQA y el SAK; de una etiqueta NFC-V desconocida, el UID
y los bloques legibles. Muchos lectores de acceso sencillos comprueban solo el UID, así que **Emulate UID** puede
funcionar igualmente.

## Tarjetas guardadas

`Main Menu → NFC → Saved` lista tus ficheros `.nfc`. El menú de una tarjeta guardada contiene (según el tipo):

- **Emulate** o **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- elementos de protocolo: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (solo cuando existe un fichero de sombra; véase más abajo)
- **Rename**, **Delete**, **Info**

## Emular una tarjeta

1. Ve a `Main Menu → NFC → Saved` y elige la tarjeta.
2. Selecciona **Emulate** (emulación completa) o **Emulate UID** (solo se envían UID/ATQA/SAK).
3. La pantalla muestra **Emulating** con el nombre de la tarjeta. Apoya la parte trasera del Flipper en el lector.
4. Si el lector ha dialogado con la tarjeta emulada, aparece un botón **Log** (<kbd>OK</kbd>) que muestra el
   intercambio.
5. Pulsa <kbd>←</kbd> para detenerlo.

### Ficheros de sombra {#shadow-files}

Cuando un lector escribe en una tarjeta emulada (por ejemplo, actualiza un saldo o un contador), el Flipper no
modifica tu fichero original. Escribe el nuevo estado en un **fichero de sombra** junto a él (`<nombre>.shd`). El
volcado original se mantiene intacto:

- **Restore to Original State** (`Saved → tarjeta`): pregunta *"Restore Card Data?"* y borra el fichero de sombra.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): vuelve a leer la tarjeta física con las claves
  guardadas y actualiza el volcado. Solo se acepta la tarjeta de origen; en caso contrario aparece
  *"Wrong Card! Data management is only possible with source card"*.

## Si la lectura falla

- **No se detecta nada**: puede que sea una tarjeta de 125 kHz. Prueba `Main Menu → 125 kHz RFID → Read`
  (véase la [sección de RFID](/es/rfid/read)).
- **Tipo detectado incorrecto / tarjeta híbrida**: usa `Extra Actions → Read Specific Card Type`.
- **"Lost the tag!"** durante un ataque largo: vuelve a poner la tarjeta en el mismo sitio y mantenla quieta. Las
  fundas gruesas y el metal detrás de la tarjeta perturban el campo.
- **No se leen todos los sectores o páginas**: la tarjeta está protegida. Continúa con
  [MIFARE Classic](/es/nfc/mifare-classic), [MFKey32](/es/nfc/mfkey) o
  [Desbloquear tarjetas](/es/nfc/unlock-with-password).
- **"Plugin Not Loaded — Plugin file missing or outdated"**: los ficheros `.fal` de analizador de la tarjeta SD no
  se corresponden con el firmware. Reinstala o actualiza el firmware con la tarjeta SD puesta.

## Relacionado

- [MIFARE Classic](/es/nfc/mifare-classic) · [Tarjetas compatibles](/es/nfc/supported-cards) · [Formato de los ficheros NFC](/es/nfc/file-format)
- [Tarjetas mágicas](/es/nfc/magic-cards) · [NFC Magic 2.0](/es/nfc/nfc-magic)
