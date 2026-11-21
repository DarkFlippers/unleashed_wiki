---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** es una Ultralight con autenticación mutua **AES-128** en lugar de una contraseña (NTAG21x)
o 3DES (Ultralight C). Tiene 60 páginas, tres contadores unidireccionales, una firma de originalidad ECC de
48 bytes, un modo **Random ID** opcional y **mensajería segura** opcional (cada comando y cada respuesta protegidos
por un CMAC).

::: tip Unleashed
La compatibilidad con Ultralight AES (lectura, ataque de diccionario, introducción manual de clave, emulación,
reescritura, decodificación de la configuración, Random ID y mensajería segura) es una función de Unleashed,
validada en una tarjeta MF0AES20 real contra los datos de referencia de un Proxmark3.
:::

## Qué hace el Flipper con ella

| Función | Detalles |
|---|---|
| Identificar y leer | Se detecta como `Mifare Ultralight AES`, ATQA `0044`, SAK `00`, `60/60` páginas en una tarjeta abierta, y contadores. |
| Firma de originalidad | Se guarda en el fichero `.nfc` como una línea `AES signature:` (48 bytes) y se reproduce durante la emulación, así que la comprobación de firma de un lector pasa. |
| Autenticación AES | Desafío-respuesta AES de 3 pasos y después se leen las páginas protegidas. |
| Ataque de diccionario | Se ejecuta automáticamente en una lectura incompleta: **MFUL AES User Dictionary** y después **MFUL AES System Dictionary**. |
| Clave manual | `Saved → <tarjeta> → Unlock` → **"Enter key in hex"** (16 bytes) → confirmar con **Unlock**. |
| Gestión de claves | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Reescritura | **Write (Keep Key)** / **Write (Copy Key)** en un volcado completamente leído. |
| Emulación | Completa, incluida la autenticación AES como tarjeta, la barrera AUTH0 y la mensajería segura. |
| Decodificación de la configuración | `Info` muestra un bloque **UL-AES Config** (véase más abajo). |
| Random ID | Se detecta y se muestra (`Random ID: on`); **Reveal Real UID** intenta recuperar el UID real. |

Diccionarios: sistema `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (la clave de fábrica de todo ceros,
`BREAKMEIFYOUCAN!` reutilizada como AES, y otros valores por defecto habituales de Proxmark3), usuario
`/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. Una tarjeta de fábrica usa la clave de todo ceros
`00000000000000000000000000000000` tanto para la DataProtKey como para la UIDRetrKey.

## Leer una tarjeta protegida

1. `Main Menu → NFC → Read`, y apoya la tarjeta.
2. Se leen las páginas abiertas; si la tarjeta tiene una región protegida por AES, el ataque de diccionario empieza
   por sí solo (primero el diccionario de usuario y después el de sistema).
3. Si una clave funciona, se leen todas las páginas y la clave se muestra y se guarda con el volcado. Si no,
   obtienes una lectura parcial (por ejemplo, `42/60` páginas) y **"AES-protected pages!"**, sin colgarse ni gastar
   intentos en una tarjeta sin límite.
4. Guarda la tarjeta. Más adelante puedes volver a intentarlo con **Unlock with Dictionary** (después de añadir
   claves) o con **Unlock** (clave manual).

::: warning Orden de los bytes de la clave
Las escrituras de página en bruto (por ejemplo, `hf mfu wrbl` de Proxmark3) guardan la clave en el **orden de la
memoria de la etiqueta**; el motor AES, la introducción manual del Flipper y `hf mfu aesauth --key` de PM3 usan el
orden **inverso**. Una tarjeta cuyas páginas `0x30–0x33` se leen como
`A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` se autentica con `AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Introduce una clave
recuperada a mano **en orden AES**. En el `.nfc` guardado, las páginas de clave (`Page 48`–`51`) se almacenan en el
orden de la memoria de la etiqueta para poder reescribirlas literalmente; la línea `DataProtKey:` de la pantalla es
solo una representación.
:::

## Memoria y configuración

| Elemento | Ubicación |
|---|---|
| DataProtKey | páginas `0x30`–`0x33` |
| UIDRetrKey | páginas `0x34`–`0x37` |
| CFG | página `0x29`: byte 0 bit 0 = `RID_ACT`, bit 1 = `SEC_MSG_ACT`; byte 3 = `AUTH0` |
| ACCESS | página `0x2A`: byte 0 bit 2 = `CNT_RD_EN`, bit 3 = `CNT_INC_EN`, bit 6 = `CFGLCK`, bit 7 = `PROT`; bytes 2–3 = `AUTH_LIM` |
| LOCK_KEYS | página `0x2D`: byte 0 = bits de bloqueo por clave |

El bloque **UL-AES Config** de `Info` decodifica todo esto, por ejemplo:

- `Auth from: off (open)` o `Auth from: page 0x10 (r+w)` / `(write)`: `AUTH0` y `PROT`;
- `Auth limit: unlimited` o `Auth limit: N (locks!)`;
- `Counter 2: rd open / inc auth` y similares;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N`;
- `Real UID:` una vez revelado.

::: danger No experimentes con estos bits
`CFGLCK` bloquea la configuración de forma **permanente**, `AUTH_LIM` arma un bloqueo tras varias autenticaciones
fallidas, y los bits de `LOCK_KEYS` y de bloqueo estático pueden dejar la tarjeta inservible. No los cambies nunca
en una tarjeta que te importe. Ten en cuenta también que `hf mfu info` de PM3 etiqueta las páginas `0x34`–`0x37` de
la MF0AES20 con una plantilla heredada de Ultralight (`cfg0/cfg1/PWD/PACK`); fíate de la tabla de arriba.
:::

## Reescribir un volcado

Solo se ofrece en un volcado de Ultralight AES **completamente leído**, como dos elementos:

- **Write (Keep Key)**: escribe las páginas de datos `0x04`–`0x27`; la clave del destino se mantiene.
- **Write (Copy Key)**: las páginas de datos más la **DataProtKey** (`0x30`–`0x33`) del volcado.

Reglas integradas en el firmware:

- La escritura **se autentica primero en el destino** con una clave de diccionario, así que la clave *actual* del
  destino debe estar en un diccionario (la clave de fábrica de todo ceros lo está).
- Las páginas de configuración y bloqueo `0x28`–`0x2F` **nunca** se escriben; la UIDRetrKey (`0x34`–`0x37`) tampoco
  se escribe nunca.
- El destino debe ser del mismo **tipo**; el UID no tiene por qué coincidir.

## Emulación

`Saved → <tarjeta> → Emulate`. La tarjeta emulada responde a GET_VERSION, a la firma, a los contadores y a la
configuración igual que la real, realiza la autenticación AES como tarjeta usando `reverse(páginas 0x30–0x33)` como
clave, rechaza las claves incorrectas y aplica `AUTH0`. Nota: las lecturas restringidas sin autenticación devuelven
datos de las primeras páginas por desbordamiento en lugar de un NAK.

## Random ID

Con `RID_ACT` activado, la tarjeta presenta un **UID aleatorio de 4 bytes que empieza por `08`** en cada selección;
el UID real de 7 bytes queda oculto hasta una lectura autenticada. El Flipper muestra el UID aleatorio y
`Random ID: on`. En esas tarjetas el menú tiene **Reveal Real UID**: confirma con un aviso, vuelve a leer la tarjeta
e intenta autenticarse (con la UIDRetrKey de todo ceros por defecto) para revelar el UID estático, que se muestra
como `Real UID:` en la vista de configuración.

## Mensajería segura (CMAC)

Con `SEC_MSG_ACT` activado, una vez autenticado **cada** comando y cada respuesta deben llevar un CMAC. El Flipper
lo gestiona de forma adaptativa: después de la autenticación, el primer `READ`/`WRITE` en claro falla (el silicio
real simplemente se calla, lo que el lector percibe como un tiempo de espera agotado), el firmware se vuelve a
autenticar y pasa a `READ`, `READ_CNT` y `WRITE` envueltos en MAC. El contador de comandos avanza de 2 en 2 por
intercambio (el comando usa `CmdCtr` y la respuesta `CmdCtr+1`). Validado en hardware: una lectura completa de 60/60
sobre CMAC sin discordancias de MAC, contadores sobre CMAC, páginas de clave `0x30`–`0x37` enmascaradas a cero en el
volcado, y una reescritura de páginas de datos con CMAC.

El emulador también habla mensajería segura: verifica el MAC del comando, envuelve en MAC todas las respuestas,
sustituye el ACK de `WRITE` por un MAC y descarta la sesión ante un MAC incorrecto.

::: warning Recuperabilidad
Una vez activado `SEC_MSG_ACT`, las escrituras de configuración en una región protegida requieren una escritura
autenticada con CMAC, algo que Proxmark3 no puede hacer y que la escritura del Flipper se salta (las páginas de
configuración nunca se escriben). No pongas `AUTH0 ≤ 0x29` en una tarjeta con mensajería segura, o puede que no
puedas volver a desactivarla.
:::

### Marcadores de depuración

Con `Settings → System → Log Level → Debug` puedes seguir lo que ocurre en el registro, por ejemplo
`UL-AES: plain read failed post-auth, switching to secure messaging`,
`UL-AES response MAC mismatch (ctr N)` (no debería aparecer en una ejecución sana) o
`UL-AES command MAC mismatch, dropping session` (del lado del emulador).

## Relacionado

[Desbloquear tarjetas](/es/nfc/unlock-with-password) · [Leer tarjetas](/es/nfc/read) ·
[Formato de los ficheros NFC](/es/nfc/file-format) · [Añadir tarjetas a mano](/es/nfc/add-manually)
