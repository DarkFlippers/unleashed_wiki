---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic es la tarjeta más habitual en control de acceso, porteros automáticos, hoteles y sistemas de
transporte antiguos. Es también la más «interesante» para el Flipper: su cifrado Crypto-1 está roto, así que con
suficiente esfuerzo se pueden recuperar las claves de casi cualquier tarjeta, y después emularla o escribirla en una
[tarjeta mágica](/es/nfc/magic-cards).

## Estructura de memoria

| Tipo | Sectores | Bloques | Claves a encontrar | SAK habitual |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 bloques + 8 × 16 bloques) | 256 | 80 | `18` |

- Un **bloque** son 16 bytes. El **bloque 0** (bloque de fabricante) contiene el UID y los datos del fabricante; en
  las tarjetas genuinas es de solo lectura, que es precisamente la razón de que existan las tarjetas mágicas.
- El último bloque de cada sector es el **sector trailer**:
  `Clave A (6 bytes) | bits de acceso (4 bytes) | Clave B (6 bytes)`, por ejemplo
  `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` en una tarjeta virgen.
- Los bits de acceso deciden qué clave puede leer o escribir cada bloque. A menudo la clave A lee y la clave B
  escribe; a veces la clave B es legible, y entonces no se puede usar como clave.

## Diccionarios de claves

El Flipper nunca «conoce» las claves: prueba claves candidatas de los diccionarios. Todos son ficheros de texto con
una clave de 12 dígitos hexadecimales por línea y `#` para los comentarios (véase el
[formato de fichero](/es/nfc/file-format)).

| Diccionario | Ruta | Quién lo escribe |
|---|---|---|
| **Sistema** | `/ext/nfc/assets/mf_classic_dict.nfc` | Viene con el firmware (se sobrescribe al actualizar). En Unleashed tiene **más de 4000 claves**. |
| **Usuario** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Tú, MFKey, qUnleashed, *Save Keys to Dictionary*. Sobrevive a las actualizaciones. |
| **CUID** (por tarjeta) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey y qUnleashed, para tarjetas con nonces *cifrados estáticos*: una lista larga de claves candidatas para un solo UID. |
| **Caché de claves** | `/ext/nfc/.cache/<UID>.keys` | Se escribe automáticamente cuando **guardas** una tarjeta; se usa en primer lugar en la siguiente lectura del mismo UID. |

::: tip Unleashed
El diccionario de sistema de Unleashed contiene un gran conjunto de claves adicionales recopiladas por la comunidad
(«Extra Mifare Classic keys in system dict» en el ReadMe). La pantalla de carga del diccionario CUID con barra de
progreso (*"CUID dictionary is loading"*) apareció en la compilación de desarrollo 1437 y en la versión 094.
:::

### Gestionar el diccionario de usuario en el aparato

1. Ve a `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Menú Extra Actions con MIFARE Classic Keys entre las entradas de diccionario](/screens/nfc/extra_actions.png)

2. La pantalla muestra **System dict: N** y **User dict: N**.
3. <kbd>OK</kbd> **Add**: introduce una clave de 6 bytes en hexadecimal y guárdala. Una clave duplicada provoca un
   aviso.
4. <kbd>→</kbd> **List** (solo si el diccionario de usuario no está vacío): elige una clave para borrarla
   (*"Select key to delete:"*).

También puedes editar `mf_classic_dict_user.nfc` en un ordenador (con qFlipper, con qUnleashed o directamente en la
tarjeta SD).

### Save Keys to Dictionary {#save-keys-to-dictionary}

Todo volcado de MIFARE Classic guardado o recién leído con al menos una clave conocida tiene
**Save Keys to Dictionary** en su menú. Copia todas las claves de ese volcado al diccionario de usuario, salta los
duplicados e informa con *"New keys: N, Already known: M"*. Esto importa sobre todo en las tarjetas cuyas claves se
recuperaron de un diccionario CUID: de otro modo esas claves viven únicamente en ese fichero por UID y en el
volcado, mientras que [NFC Magic](/es/nfc/nfc-magic) solo mira la caché de claves y los diccionarios de usuario y de
sistema (es el «guardado automático de claves con comprobación de duplicados» que menciona @gromovyna en su
[artículo sobre qUnleashed](/es/nfc/qunleashed)).

## Qué ocurre cuando lees una tarjeta MIFARE Classic

`Main Menu → NFC → Read`, y mantén la tarjeta quieta. El firmware recorre estas etapas; la cabecera de la pantalla
de ataque indica cuál se está ejecutando.

1. **Caché de claves.** Si has guardado este UID antes, se usan las claves en caché y la tarjeta se lee de
   inmediato.
2. **Ataque de diccionario**, en este orden:
   - **MF Classic CUID Dictionary**: solo si existe un fichero por UID (antes de él, *"CUID dictionary is loading"*
     con una barra de progreso; un fichero grande tarda minutos en cargarse).
   - **MF Classic User Dictionary**: si el fichero de usuario existe y no está vacío.
   - **MF Classic System Dictionary**.

   La pantalla muestra `Keys found: X/Y`, `Sectors Read: X/Y`, el número de clave actual y *"Unlocking sector: N"* /
   *"Reuse key check for sector: N"*.

   ![Ataque con el diccionario de sistema: desbloqueando el sector 9, clave 1244 de 2271, 19 de 32 claves encontradas](/screens/nfc/dict_attack.png)

3. **Lectura por puerta trasera.** Si el chip tiene una **clave de puerta trasera** conocida (Fudan y algunos
   otros), la cabecera muestra **Backdoor Read** / **(Backdoor)** y los sectores se leen sin claves reales. Al mismo
   tiempo se recopilan nonces.
4. **Ataques anidados** (una vez que se conoce al menos una clave): **PRNG Analysis**, **Nested Dictionary**,
   **Calibration**, **Nonce Collection** (*"Collecting from sector: N"*). El sufijo **(Hard)** significa que la
   tarjeta tiene un PRNG difícil. Los nonces recopilados se añaden a `/ext/nfc/.nested.log`.
5. Se abre la pantalla de resultados. Un LED verde o un sonido de éxito significa que la tarjeta se ha leído por
   completo; un «semiéxito» corto significa que siguen faltando sectores.

Pulsa <kbd>OK</kbd> **Skip** para saltar a la etapa siguiente (CUID → usuario → sistema → resultado). <kbd>←</kbd>
pregunta *"Exit to NFC Menu? All unsaved data will be lost"*. Si se retira la tarjeta aparece
**"Lost the tag! Make sure the tag is positioned correctly."**; vuelve a ponerla y el ataque continúa.

Hay un recorrido detallado con capturas de cada fase en
[Ataques anidados y puertas traseras de Fudan](/es/nfc/nested-fudan).

### Después de leer

El menú de lectura (`More`) de una tarjeta MIFARE Classic contiene:

| Elemento | Cuándo | Qué hace |
|---|---|---|
| **Save** | siempre | Guarda el volcado en `/ext/nfc/`. También rellena la caché de claves. |
| **Emulate** | siempre | Emulación completa del volcado. |
| **Extract MFC Keys** | tarjeta no leída por completo | Pregunta *"Save the Key?"* (Save/Skip) y después recopila nonces de un lector. Véase [MFKey32](/es/nfc/mfkey). |
| **Unlock with Dictionary** | tarjeta no leída por completo | Vuelve a ejecutar el ataque de diccionario y anidado (por ejemplo, después de añadir claves). |
| **Crack nonces in MFKey32** | tarjeta no leída por completo | Ofrece guardar la tarjeta y después lanza la [aplicación MFKey](/es/nfc/mfkey-app) (**Run**). |
| **Show Keys** | siempre | *"Found MFC Keys"*: bits de acceso, clave A, clave B y totales por sector. |
| **Save Keys to Dictionary** | al menos una clave conocida | Véase más arriba. |
| **Info** | siempre | UID, ATQA, SAK y resumen de claves y sectores; **More** muestra el volcado hexadecimal (`??` = bytes desconocidos). |

En una tarjeta **guardada** tienes además **Write to Initial Card**, **Update from Initial Card**,
**Restore to Original State** (si existe un fichero de sombra), **Rename** y **Delete**.

## Conseguir las claves que faltan

Si no se han leído todos los sectores, elige el método que se ajuste a tu situación:

| Situación | Método |
|---|---|
| Tienes la tarjeta **y** acceso al lector | [MFKey32](/es/nfc/mfkey): el Flipper emula la tarjeta y el lector revela sus claves. |
| Tienes la tarjeta y se conoce al menos una clave, o el chip tiene una puerta trasera | Los ataques anidados se ejecutan automáticamente en `Read`; después calcula las claves con la [aplicación MFKey](/es/nfc/mfkey-app) o, mucho más rápido, con [qUnleashed](/es/nfc/qunleashed). |
| La tarjeta tiene un **PRNG difícil** | HardNested: lo calcula qUnleashed o un PC; véase [Ataques anidados](/es/nfc/nested-fudan). |
| No tienes la tarjeta, solo el lector | [MFKey32](/es/nfc/mfkey) mediante `Extract MFC Keys` desde el menú principal de NFC: las claves van al diccionario de usuario para más adelante. |
| Las claves están diversificadas por tarjeta (por ejemplo, [Iron Logic](/es/nfc/iron-logic)) | Cada tarjeta tiene sus propias claves: hay que recuperarlas una por una. |

Después de añadir claves nuevas, vuelve a leer la tarjeta (o abre el fichero guardado →
**Unlock with Dictionary**).

## Emulación

1. `Main Menu → NFC → Saved → <tarjeta> → Emulate`.
2. Apoya el Flipper en el lector.

Los sectores que nunca se leyeron se emulan como desconocidos: un lector que los necesite rechazará la tarjeta. Si
el lector escribe en la tarjeta (saldo, contadores, sistemas «dinámicos»), los cambios van al
[fichero de sombra](/es/nfc/read#shadow-files).

::: warning Sistemas dinámicos
Algunos sistemas reescriben datos en la tarjeta en cada paso (por ejemplo,
[Iron Logic en modo dinámico](/es/nfc/iron-logic-enrollment)). Una copia emulada y el original se desincronizan
entonces; usar los dos puede bloquear el original.
:::

## Escritura

- **Write to Initial Card** escribe el volcado de vuelta **en la misma tarjeta** (el UID debe coincidir). Cualquier
  otra tarjeta da *"Use source card! To write blanks use NFC Magic app"*. Si no se han podido escribir todos los
  bloques: *"Not all sectors were written correctly"*.
- Para clonar en una tarjeta en blanco usa la aplicación [NFC Magic](/es/nfc/nfc-magic) y una
  [tarjeta mágica](/es/nfc/magic-cards) adecuada. Elige la tarjeta en blanco con cuidado: muchos lectores filtran
  las tarjetas Gen1.

## Resolución de problemas

- **Se encuentran claves pero algunos sectores siguen sin leerse**: puede que los bits de acceso prohíban la lectura
  con el tipo de clave encontrado; recupera la otra clave (A o B).
- **La lectura empieza con un largo "CUID dictionary is loading"**: existe una lista larga de candidatas por UID para
  esta tarjeta. Es lo esperado después de un ataque a nonces cifrados estáticos. Borra
  `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` cuando la tarjeta esté completamente recuperada y sus claves estén
  guardadas en el diccionario de usuario.
- **MFKey dice "Nonces already cracked" o no aporta nada nuevo**: limpia `/ext/nfc/.nested.log` y
  `/ext/nfc/.mfkey32.log` después de una recuperación correcta; los nonces antiguos ralentizan todo.
- **Parece que las claves recuperadas no se usan**: comprueba que realmente han llegado a
  `mf_classic_dict_user.nfc` (`Extra Actions → MIFARE Classic Keys → List`). Las claves encontradas por HardNested
  en un PC hay que añadirlas a mano.

## Relacionado

[Leer tarjetas](/es/nfc/read) · [MFKey32](/es/nfc/mfkey) · [Ataques anidados](/es/nfc/nested-fudan) ·
[Aplicación MFKey](/es/nfc/mfkey-app) · [qUnleashed](/es/nfc/qunleashed) · [Tarjetas mágicas](/es/nfc/magic-cards) ·
[MIFARE Plus](/es/nfc/mifare-plus)
