---
title: Ataques anidados y puertas traseras de Fudan
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Ataques anidados y puertas traseras de Fudan

Una guía práctica de **@gromovyna** sobre «qué hay que pulsar» en los ataques de solo tarjeta a MIFARE Classic que
están integrados en `NFC → Read`. Llegaron al firmware oficial **1.1.2** (trabajo de
[@noproto](https://github.com/noproto)) y forman parte de Unleashed. Mientras se desarrollaban, un investigador de
la comunidad hizo dos descubrimientos importantes: un ataque a los **nonces cifrados estáticos** y unas **claves de
puerta trasera** en chips fabricados por **Fudan** (y otros) que permiten leer los sectores de una etiqueta MIFARE
Classic sin conocer sus claves. Los dos llegaron al firmware y a **MFKey 3** (hoy
[MFKey 4.1](/es/nfc/mfkey-app)). El artículo de investigación:
[eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Vía más rápida (actualización de septiembre de 2026)
Si solo quieres recuperar claves de MIFARE Classic rápidamente, usa la aplicación acompañante **qUnleashed**, que
ejecuta todos estos ataques, HardNested incluido, en tu móvil o en tu PC: véase
[Recuperación rápida de claves con qUnleashed](/es/nfc/qunleashed).
:::

## La idea en breve

Los **ataques anidados** son ataques *de solo tarjeta* (no hace falta lector): conociendo al menos una clave de una
tarjeta, recuperan las desconocidas. Conceptualmente, las etiquetas se dividen en cuatro grupos (hablando con
propiedad existen Nested y HardNested, pero esta división es más fácil de entender):

| La etiqueta es vulnerable a | Tipo de nonce | Dónde se calcula la clave |
|---|---|---|
| **Nested** | PRNG débil | MFKey en el Flipper, qUnleashed |
| **HardNested** | PRNG difícil | qUnleashed o un PC (no en el Flipper) |
| **Static Nested** | nonce estático | MFKey en el Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | nonce cifrado estático | MFKey en el Flipper (lo más lento), qUnleashed |

Las **claves de puerta trasera** son claves que abren los datos de una etiqueta **sin** sus claves reales.

Para los ejemplos el autor usó etiquetas de cada tipo, con el sector 0 cifrado por una pareja de claves generada:
clave A `A3F92C8E7D3A`, clave B `4F6D91C5BA7E` (bits de acceso en sus valores por defecto). En un Proxmark3, la
comprobación de claves por defecto mostraba esas claves como desconocidas:

![Comprobación de claves por defecto en Proxmark3](/img/remote/86130b06142278a1.png)

## Paso 1. Leer la etiqueta

Ve a `Main Menu → NFC → Read` y mantén la etiqueta quieta.

### 1.1 La etiqueta tiene puerta trasera

Verás pantallas con **Backdoor Read** y después unas cuantas más con **(Backdoor)** en la cabecera:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Leyendo por la puerta trasera](/img/remote/e9be977d84486794.png)

Eso significa que el chip tiene una puerta trasera: el Flipper lee por ella los datos de los sectores y recopila
nonces para poder recuperar las claves. El resultado típico es **todos los sectores leídos, pero menos claves de las
necesarias**:

![Todos los sectores, pero solo 30 claves](/img/remote/9e7db33e51594779.png)

### 1.2 La etiqueta no tiene puerta trasera

Entonces se ejecuta la búsqueda clásica de claves: primero el diccionario de **usuario**, después el de
**sistema**.

![Diccionario de usuario](/img/remote/fff8f5662df941b9.png)

![Diccionario de sistema](/img/remote/0da64f609fc2c770.png)

Si se ha encontrado al menos una clave, el Flipper pasa a **PRNG Analysis** y después recorre el
**Nested Dictionary**:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

luego **Calibration** y **Nonce Collection**:

![Calibración y recopilación de nonces](/img/remote/f5b036a96f5a0869.png)

Si la etiqueta es vulnerable **solo a HardNested**, la recopilación de nonces lleva más tiempo y la cabecera recibe
el sufijo **(Hard)**:

![Recopilación de nonces en una etiqueta con PRNG difícil](/img/remote/fca9f1b2e4475631.png)

> En ese caso, ve directamente al [paso 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Aquí el resultado tiene un aspecto más familiar: el número de claves encontradas se acerca al número de sectores
leídos (según los bits de acceso).

![Resultado después de la fase anidada](/img/remote/d15656101dfafcc4.png)

Todos los nonces recopilados se añaden a `/ext/nfc/.nested.log`.

## Paso 2. Recuperar las claves

Ve a `Main Menu → Apps → NFC → MFKey`.

::: warning Comprueba la versión de la aplicación
Asegúrate de que la aplicación MFKey es la que corresponde a tu firmware y de que no la ha sobrescrito una copia
antigua si instalaste aplicaciones por separado. Unleashed incluye **MFKey 4.1**.
:::

![Pantalla de inicio de MFKey](/img/remote/195a1b6a411e7bf3.png)

Pulsa <kbd>OK</kbd> **Start** y…

### 2.1 La etiqueta es vulnerable a Nested, Static Nested o Static Encrypted Nested

Empieza el proceso de descifrado. Puedes dejar el Flipper solo y hacer otra cosa:

![Descifrado en curso](/img/remote/a514db67a986ae2c.png)

Solo queda esperar. Con el hardware del Flipper esto no es rápido (hola, SPI) y depende de:

- el tipo de ataque: Nested < Static Nested < Static Encrypted Nested (SEN es el más lento);
- el número de claves desconocidas (cuantas menos, más rápido);
- lo únicas que sean las claves: una clave reutilizada en todas partes se encuentra antes que una etiqueta
  parcialmente diversificada (por ejemplo, Iron Logic), que a su vez es más rápida que una etiqueta totalmente
  diversificada (por ejemplo, las bobinas de filamento de Bambu Lab).

La interfaz no siempre responde y a veces se queda «pensando». De cuando en cuando el Flipper puede parecer
colgado; no te precipites a reiniciarlo. La línea **RAM** de arriba sigue cambiando mientras el trabajo avanza.

::: warning Nonces cifrados estáticos
Con los nonces cifrados estáticos, por cómo funciona el ataque, los nonces no se marcan como «resueltos»; MFKey solo
construye **candidatas** (claves que después hay que comprobar en la etiqueta), y la aplicación puede parecer
atascada en el último paso (o en uno anterior). Si ha pasado tiempo suficiente, sal y comprueba el resultado
(paso 3). Desde MFKey 4.x las candidatas se guardan en un **diccionario CUID** por tarjeta,
`/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, que `Read` prueba en primer lugar.
:::

Cuando el descifrado termina, obtienes un resumen con el número de claves añadidas al diccionario de usuario
(**Keys added to user dict: N**, y en las etiquetas SEN **SEN key candidates: N**):

![MFKey completado](/img/remote/c9ef77139b74cc89.png)

Continúa con el paso 3.

### 2.2 La etiqueta es vulnerable a HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

Lo habrás notado por la pantalla **(Hard)** durante la recopilación de nonces, o MFKey mostrará un error indicando
que no se han encontrado nonces:

![MFKey: no se han encontrado nonces](/img/remote/2519c7dce0b881c9.png)

HardNested es el único ataque que no se puede ejecutar en el Flipper. Opciones:

- **qUnleashed** (recomendado, en móvil o PC): `Tools → Recover MIFARE Keys`; véase
  [qUnleashed](/es/nfc/qunleashed). Las claves van directamente al diccionario de usuario.
- **Un PC con HardnestedRecovery**, como en la guía original:
  1. Copia `/ext/nfc/.nested.log` de la tarjeta SD del Flipper al ordenador.
  2. Clona y compila [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) con
     `make build` (en Windows usa WSL o Docker).
  3. Ejecútalo con el registro como argumento:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. La clave aparece en la salida:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Añade las claves a mano
A diferencia del caso 2.1, las claves encontradas por HardnestedRecovery en un PC **no** se añaden
automáticamente. Añádelas tú mismo al diccionario de usuario:
`NFC → Extra Actions → MIFARE Classic Keys → Add`, o escríbelas al final de
`/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Paso 3. Volver a leer la etiqueta

Una vez recuperadas las claves, vuelve a leer la etiqueta con `NFC → Read`.

::: tip Consejo avanzado
Si guardaste la etiqueta después de la primera lectura, puedes desbloquearla directamente desde el menú de la
tarjeta guardada: `Saved → <tarjeta> → Unlock with Dictionary`.
:::

![Unlock with Dictionary desde una tarjeta guardada](/img/remote/8232d690446c70b6.png)

::: tip Consejo avanzado
Para obtener mejor rendimiento la próxima vez, limpia `/ext/nfc/.nested.log` después de haber descifrado las claves
de una etiqueta.
:::

## Relacionado

[MIFARE Classic](/es/nfc/mifare-classic) · [Aplicación MFKey](/es/nfc/mfkey-app) · [qUnleashed](/es/nfc/qunleashed) ·
[MFKey32](/es/nfc/mfkey) · [Lectores Iron Logic](/es/nfc/iron-logic) · más artículos en el canal del autor
[@gromovyna](https://t.me/gromovyna)
