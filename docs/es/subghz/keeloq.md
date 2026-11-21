---
title: KeeLoq
order: 70
author: gromovyna
original: [https://blog.li0ard.rest/wtfiskeeloq, https://t.me/gromovyna/24, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [li0ard, gromovyna, unleashed-docs, unleashed-src]
---
# KeeLoq

KeeLoq es el cifrado que hay detrás de un enorme número de mandos de cancela, puerta de garaje y barrera (DoorHan,
Nice Smilo, FAAC RC, BFT, Came Space, Beninca, Hormann EcoStar…) y de alarmas de coche antiguas. Esta página explica
cómo funciona, qué son las «claves de fabricante» y las «semillas», y cómo los maneja Unleashed.

La parte teórica se basa en el artículo **«KeeLoq и с чем его едят»** de
[@li0ard](https://blog.li0ard.rest/wtfiskeeloq), miembro del equipo de investigación de @gromovyna y recomendado en
[su canal](https://t.me/gromovyna/24) a todo el que quiera entender este cifrado.

## Qué es KeeLoq

KeeLoq es un cifrado por bloques basado en un NLFSR (registro de desplazamiento con realimentación no lineal),
diseñado por Nanoteq Pty Ltd. y vendido a Microchip Technology Inc. Cifra **bloques de 32 bits** con una **clave de
64 bits** en **528 rondas**. Implementa *code hopping*: cada transmisión es un paquete único.

### Estructura del paquete

Un paquete KeeLoq de 64 bits, por ejemplo `239B3DEBF16C47A6`, consta de:

- **Fix** (los 4 primeros bytes, `239B3DEB`), enviado en claro: el identificador de botón (`2`) y el número de serie
  de 28 bits del mando (`39B3DEB`).
- **Hop** (los 4 últimos bytes, `F16C47A6`), cifrado con la clave de fabricante. Descifrado tiene el aspecto
  `21EB000A`: de nuevo el identificador de botón (`2`), 12 bits de datos de discriminación (a menudo
  `serial & 0x3FF`) y el **contador de 16 bits** (`000A`).

![Estructura del paquete KeeLoq](/img/remote/167cc7293a53adb1.png)

Eso es lo que muestra el Flipper después de un [Read](/es/subghz/read): `Fix`, `Hop`, `Btn`, `Cnt` y el nombre del
fabricante.

### Lógica del contador

- El contador coincide con el valor que espera el receptor → el comando se ejecuta.
- El contador es **mayor** que el almacenado → el receptor se resincroniza con él y funciona con normalidad a partir
  de la siguiente pulsación.
- El contador es **menor** → se ignora; algunos receptores desemparejan el mando después de varios valores
  «caducados». *Ese es el verdadero peligro al experimentar con KeeLoq.* Véase
  [Códigos rodantes](/es/subghz/rolling-codes).

## Modos de aprendizaje (derivación de clave)

La clave que realmente cifra el hop se deriva de una **clave de fabricante** (64 bits, la misma para todos los
mandos de una marca o línea de modelos). El estándar define tres modos:

| Modo | Cómo se obtiene la clave por mando |
|---|---|
| **Simple learning** | la clave de fabricante se usa tal cual (el más débil) |
| **Normal learning** | la clave de fabricante se mezcla con el número de serie del mando |
| **Secure learning** | usa un valor adicional, la **semilla**, única por mando y transmitida solo al emparejar (el modo estándar más fuerte) |

Los fabricantes se inventan también los suyos propios, por ejemplo **Magic XOR Type-1** (Beninca: serial XOR clave
de fabricante) o **FAAC SLH (SPA)**, una serie de operaciones de bits y cifrados, el más elaborado de todos ellos en
opinión de li0ard.

::: tip Unleashed
Unleashed implementa todos los modos estándar más muchos de fabricante (`lib/subghz/protocols/keeloq_common.h`):
Simple, Normal, Secure, Magic XOR type 1, FAAC, Magic Serial types 1–3, KingGates, Jarolift, Erreka, Pujol, AERF,
JCM, JCM Gen2, Stagnoli y el aprendizaje Telcoma basado en tablas. Hay más de 100 fabricantes listados en
[Sistemas compatibles](/es/subghz/supported-systems).
:::

## Claves de fabricante en Unleashed

Para decodificar una señal KeeLoq el Flipper debe conocer la clave de fabricante. Unleashed las incluye en un
almacén de claves **cifrado** en la tarjeta SD:

| Fichero | Finalidad |
|---|---|
| `/ext/subghz/assets/keeloq_mfcodes` | claves integradas, cifradas (`Encryption: 1`), se actualizan con el firmware |
| `/ext/subghz/assets/keeloq_mfcodes_user` | **tus propias** claves, en texto plano (créalo a partir de `keeloq_mfcodes_user.example`) |

Al decodificar una señal se prueban todas las claves; si alguna encaja, el nombre aparece como `KL: DoorHan`,
`KL: Nice_Smilo`, etc. Si no encaja ninguna, la señal se muestra como **`KL: Unknown`**: se puede guardar, pero no
enviar ni usar para generar el código siguiente. Los comandos `subghz` de la CLI que decodifican señales imprimen al
arrancar `Load_keystore keeloq_mfcodes OK` y `Load_keystore keeloq_mfcodes_user OK` / `Absent`, una forma rápida de
comprobar que los almacenes se cargan.

### Formato del fichero de claves de usuario

```text
# AABBCCDDEEFFAABB:X:NAME
# AABBCCDDEEFFAABB - manufacture key, 64 bit
# X - learning type: 1 - Simple, 2 - Normal, 3 - Secure, 4 - Magic_xor_type1,
#     5 - FAAC SLH, 6 - Magic Serial typ1, 7 - Magic Serial typ2, 8 - Magic Serial typ3,
#     0 - iterates over both previous and man in direct and reverse byte sequence
# NAME - name (no spaces), max 64 characters
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:1:Test2
```

Deja una línea vacía al final del fichero. El fichero `_user` no se sobrescribe con las actualizaciones.

### Los campos `Manufacture` y `Seed`

Un `.sub` de KeeLoq guardado almacena el fabricante por su nombre:

```text
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: DoorHan
```

Los sistemas de secure learning almacenan también `Seed: XX XX XX XX`. Añadir a mano las líneas `Seed` +
`Manufacture` a un fichero que se lee como `KL: Unknown` lo hace decodificable (véase BFT/Erreka más abajo).

## Semillas: BFT Mitto, Erreka, FAAC SLH, Genius

Estos sistemas usan una **semilla** por mando (o por instalación); sin ella la señal se lee como `KL: Unknown` (o no
se decodifica) y no se puede construir ningún mando que sea aceptado.

- **BFT Mitto**: los mandos más nuevos derivan la semilla del número de serie y se decodifican directamente en Read
  (`KL: BFT`). Los más antiguos tienen una semilla única. Pon el original en modo de programación (el orificio de la
  parte de atrás o los botones 1+2): envía un paquete cuyo `Fix` empieza por `F`; el **`Hop` de ese paquete es la
  semilla** en claro.
- **Erreka IRIS**: puentea los pines `1` y `5` del conector de 5 vías del costado; de nuevo el `Fix` empieza por `F`
  y el `Hop` es la semilla. Algunas instalaciones dan la misma semilla a **todos** los mandos; entonces un mando
  nuevo debe reutilizarla.
- **FAAC SLH / Genius**: lee la semilla de un mando **maestro** en modo de programación; la semilla es distinta
  **para cada botón**.
- ¿No hay botón de programación disponible? Usa la aplicación **[Seed Capturer](/es/subghz/seed-capturer)**:
  recopila parejas Fix/Hop consecutivas y la semilla se recupera en la aplicación acompañante qUnleashed.

Con la semilla, crea el mando en `Sub-GHz → Add Manually [Advanced]` (SERIAL → BUTTON → COUNTER → SEED); véase
[Add Manually](/es/subghz/add-manually) y [programación de mandos](/es/subghz/remote-prog).

## Ataques conocidos (panorama)

Del artículo de li0ard, a modo de comprensión y no de instrucciones.

**Teóricos:** ataque de deslizamiento (unos 2³² pares de texto claro y cifrado, que proporciona los 32 primeros bits
de la clave), enfoque por correlación (aprovecha un sesgo de 5/8 del NLFSR) y paso lineal (los 16 últimos bits de la
clave una vez conocidos los demás). Complejidad total ≈ 2⁵².

**Prácticos** (gracias a los materiales de Derek Jamison, «SubGHz Rolling Flaws»):

| Ataque | Idea |
|---|---|
| Replay | reenviar un paquete capturado; funciona con códigos estáticos y con receptores que no comprueban el contador |
| Clonado del mando | con la clave de fabricante se puede hacer una copia funcional, pero entra en conflicto con el contador del original y puede provocar su desemparejamiento |
| Future | enviar un contador muy adelantado (`0001` → `3E91`); el receptor se resincroniza y el original queda desincronizado |
| Rollback | retroceder el contador después de algunos usos; algunos receptores poco frecuentes se resincronizan con valores antiguos |
| RollJam | grabar mientras se interfiere el receptor y usarlo después. **La interferencia es ilegal** en casi todos los países |
| Clave de fabricante (KGB) | el receptor puede aceptar varias claves de fabricante; se envía el fix original con un contador cifrado con otra clave |
| Enc00 | sustituir el fix por el de otro mando emparejado y usar el hop original; el otro mando queda desincronizado |
| Unknown | cuando un receptor no puede decodificar el hop usa 0; los receptores universales pueden abrir con 0 |

Pese a todo esto, KeeLoq —como MIFARE Classic con su Crypto-1 roto— sigue siendo popular en sistemas de acceso
económicos; algunos fabricantes (Beninca, Hormann) han pasado a AES.

::: warning
Experimenta únicamente con tus propios mandos y receptores. Un mando desincronizado o desemparejado puede necesitar
volver a registrarse en el receptor.
:::

## Resolución de problemas

- **`KL: Unknown`**: no hay clave coincidente. Comprueba la modulación, actualiza el firmware (claves nuevas) o añade
  una clave a `keeloq_mfcodes_user` si legítimamente te pertenece. En los sistemas con semilla, recupera la semilla.
- **Se decodifica pero el receptor ignora al Flipper**: estás enviando un clon; véase
  [Códigos rodantes](/es/subghz/rolling-codes) y [Modos de contador](/es/subghz/counter-mode).
- **`Function requires an SD card with fresh databases.`** en Add Manually: falta el almacén de claves; reinstala el
  firmware con la tarjeta SD puesta.

## Relacionado

- [Sistemas compatibles](/es/subghz/supported-systems) · [Add Manually](/es/subghz/add-manually)
- [Seed Capturer](/es/subghz/seed-capturer) · [Programación de mandos](/es/subghz/remote-prog)
- [Modos de contador](/es/subghz/counter-mode) · [Formato de fichero .sub](/es/subghz/file-format)
