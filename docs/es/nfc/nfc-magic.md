---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0: escribir y borrar tarjetas mágicas

**NFC Magic** es la aplicación para escribir, clonar y borrar [tarjetas mágicas](/es/nfc/magic-cards) directamente
desde el Flipper. Empezó como una aplicación oficial del Flipper Zero; la versión que se describe aquí vive en el
paquete [all-the-plugins](https://github.com/xMasterX/all-the-plugins) de **xMasterX** y la mantiene el equipo de
**Unleashed** (hicieron un fork y siguen desarrollándola). La versión **2.0** la escribió **@gromovyna**: el ciclo
completo, desde la investigación del transporte hasta el último botón de la interfaz.

Antes de la 2.0 la aplicación manejaba las **MIFARE Classic** mágicas (Gen1a, Gen2) y la universal **Gen4**
(UMC/GTU), un chip configurable no atado a MFC. La 2.0 añade las tarjetas mágicas de **Ultralight/NTAG** y
resultados honestos.

![Versión nueva, icono nuevo](/img/remote/dafa43486592335f.png)

::: tip Dónde conseguirla
NFC Magic **no forma parte del binario del firmware**: es una aplicación externa del paquete de aplicaciones
adicionales. La 2.0 está disponible en las **compilaciones de desarrollo de Unleashed desde la 1307**. Actualiza la
aplicación desde el catálogo, o actualiza el firmware a una compilación de desarrollo reciente (con el paquete de
aplicaciones adicionales). Ruta en el aparato: `Main Menu → Apps → NFC → NFC Magic`.
:::

## Antes de empezar

1. [Lee](/es/nfc/read) la tarjeta original y **guárdala**. Asegúrate de que se han leído **todos** los sectores
   (MIFARE Classic) o todas las páginas (Ultralight/NTAG): un volcado parcial da una copia parcial.
2. Con las tarjetas en blanco MIFARE Classic, NFC Magic se autentica con claves de la **caché de claves** y de los
   **diccionarios de usuario y de sistema**, y de nada más. Si las claves de tu tarjeta venían de un diccionario
   CUID, ejecuta primero **Save Keys to Dictionary** en el volcado (véase
   [MIFARE Classic](/es/nfc/mifare-classic#save-keys-to-dictionary)).

## Paso 1. Detección

Todo empieza cuando pones la tarjeta en blanco sobre el Flipper (`Check Magic Tag`). El primer cambio importante: la
aplicación ya no está obsesionada con MIFARE Classic. El escáner trabaja **por familias primero**: antes averigua la
familia (**MFC** o **Ultralight/NTAG**) y solo después profundiza en la variante exacta.

En el caso de las **USCUID-UL** (tarjetas mágicas de la familia Ultralight) se reconoce todo el zoo principal,
además de un poco de circo local ruso: **UL11**, **UL21** (incluido lo que se vende como **«Ultra»** en el mercado
de la antigua URSS), **NTAG213/215/216**, **UL-C**, **UL-5** y etiquetas que ya están en modo **puerta trasera** (se
comprueban las dos secuencias de despertar).

![USCUID-UL detectada](/img/remote/557fa5d47ebeb0a6.png)

Si tienes un preajuste que la aplicación no conoce, no se rinde: muestra la **configuración en bruto**, para que
puedas verla y analizarla tú mismo. Práctico para investigadores.

![Configuración en bruto 1](/img/remote/7c3f38df0079d8fa.png)

![Configuración en bruto 2](/img/remote/c16eb844763ef4fa.png)

![Configuración en bruto 3](/img/remote/30f2a4b10d4be98a.png)

Para una tarjeta **Gen4** protegida por contraseña: `Gen4 Actions → Auth with password`, introduce la contraseña y
después comprueba la etiqueta.

## Paso 2. Escribir Ultralight / NTAG

Una vez reconocida la etiqueta puedes escribir y clonar por completo **UL/NTAG**. De lo que **no** tienes que
preocuparte es del transporte: la aplicación lo elige a partir del resultado de la detección.

- **Direct**: una escritura ISO14443-3 normal con el comando **`A2`**, para etiquetas que aceptan escrituras de
  frente (por ejemplo, las configuraciones de fábrica de **USCUID-UL**, las mismas **UL21**, también llamadas
  **«Ultra»**).
- **Backdoor**: si el chip tiene una puerta trasera expuesta, la aplicación la usa (despertar en bruto más comandos
  de puerta trasera). La lógica es sencilla: puerta trasera expuesta → se usa; ninguna → escritura directa.

Tus decisiones:

- **¿Escribir en una etiqueta sin puerta trasera pero con una contraseña conocida?** Facilítala mediante
  **PWD-AUTH**: la aplicación se autentica en la etiqueta antes de escribir o borrar.
- **¿La etiqueta no se ha confirmado como mágica pero tú sabes que lo es?** Pulsa **Write anyway** y asume la
  responsabilidad.

El proceso de escritura se diseñó para dar el menor miedo posible:

- **Progreso en vivo «Writing X/N»** en pantalla, para que no te quedes mirando una pantalla congelada
  preguntándote si está pasando algo.

  ![Progreso de la escritura (es rápido: hizo falta una NTAG216 para poder capturar la pantalla)](/img/remote/9914d55ba866082e.png)

- El **orden de las páginas** se ajusta según el tipo de etiqueta (por ejemplo, **UL-5**) y es **distinto para
  escribir y para borrar** por culpa de los bits de bloqueo. Al escribir, las páginas de servicio (incluido el UID)
  van **al final**: si escribes el bloqueo o la protección demasiado pronto, la etiqueta se bloquea antes de que el
  volcado esté completo. El borrado va en orden ascendente, para eliminar primero el bloqueo estático y solo
  después limpiar el resto.
- La escritura es **solo por ACK y continúa ante errores**: la aplicación no se detiene en la primera página
  fallida, sigue adelante con lo que puede.
- Si algo no ha llegado, obtienes **Partial Write** con una lista de **Details** con exactamente las páginas que
  fallaron, en lugar de un alegre «hecho». ¿Has apartado la etiqueta de la antena a media operación? Vuelve a
  ponerla y la escritura continúa desde el mismo punto.

![Escritura parcial](/img/remote/a50fa90dff60cdd8.png)

![Detalles](/img/remote/71b6fa77e1914b76.png)

Y **Wipe** devuelve la etiqueta a su estado de fábrica con una sola pulsación.

## Paso 3. Escribir MIFARE Classic

1. En NFC Magic selecciona **Check Magic Tag** y apoya la tarjeta en blanco en la parte trasera del Flipper.
2. Cuando se reconozca la tarjeta en blanco (Gen1a, Gen2, Gen4…), ve a **More** para ver las opciones de ese tipo de
   tarjeta.
3. **Write**: elige la tarjeta original en el explorador de ficheros y apoya la tarjeta en blanco en el Flipper.
4. **Wipe** formatea la tarjeta en blanco: el UID vuelve al valor por defecto y los datos de los sectores y páginas
   se borran.

### Información honesta: Success / Partial / Fail

Esto va de la buena y vieja **MIFARE Classic (Gen2)** y para el autor es igual de importante que las funciones
nuevas.

Antes, el borrado y el clonado de MFC informaban **siempre** de «Success». Siempre, incluso cuando no se había
escrito un solo byte. Eso no es solo un fallo, es una mentira: te vas convencido de que tu copia funciona, y no
funciona.

Ahora las operaciones se siguen **bloque a bloque** y obtienes un veredicto honesto:
**Success / Partial / Fail**. En **Partial** verás **Details**: qué bloques no se escribieron o no se borraron. El
bloque 0, de solo lectura, ya no hace fracasar todo el sector 0 en el informe (como ocurría en el diseño original),
lo que también resulta práctico cuando la etiqueta está cerrada por los **bits de acceso**.

![Resultado](/img/remote/9e9d84e664f7da06.png)

![Detalles de un resultado parcial](/img/remote/525faf18552333d1.png)

Cosas que hacen la vida más tranquila:

- Al borrar, el bloque 0 **conserva el SAK/ATQA real** de la etiqueta. Caso clásico: la **Perfect CUID** (responde a
  RATS y tiene ATS). El firmware la detectaba como 4K y el borrado estampaba el bloque 0 como 4K. Corregido: una 1K
  sigue siendo 1K, y el UID se pone a cero.
- ¿No hay ninguna clave válida para el borrado? En lugar de un intento de escritura condenado al fracaso, verás de
  inmediato **"No keys found"**.
- Todas las pantallas de fallo (Wipe / Write / Dump) tienen **Exit → menu**, para que no te sientas atrapado.
- Ha desaparecido un fallo desagradable: las claves de la etiqueta anterior **ya no se arrastran** a la operación
  siguiente. El ataque de diccionario vuelve a leer la etiqueta cada vez, en lugar de reutilizar las claves de la
  última etiqueta (lo que podía dar una falsa sensación de éxito y una rapidez ficticia).

## A prueba de descuidos

Ya en la versión anterior la aplicación recibió protección en torno a las etiquetas MFC mágicas y a las distintas
longitudes de **UID**. La 2.0 comprueba si el volcado se puede escribir realmente en la variante de **USCUID-UL**
dada:

![Comprobación de compatibilidad entre volcado y tarjeta en blanco](/img/remote/a4dc82f2b66b73b5.png)

y, para los especialmente dotados, bloquea los intentos de emparejar **familias distintas** (un volcado de MFC en
una tarjeta Ultralight y al contrario; esos casos aparecen en los foros y en los chats con regularidad):

![Familias que no coinciden](/img/remote/83e6e6cf1f0d9da6.png)

## Es menos trivial de lo que parece

Detrás de la lista de funciones hay casi **3000 líneas** de cambios: un poller de USCUID-UL escrito desde cero, la
lógica de Gen2 reescrita y un montón de fallos corregidos. Todo se **validó en hardware real** con una
**matriz de QA de casi 100 casos**:

- **unas 15 etiquetas de prueba**: variantes de USCUID-UL compradas o fabricadas (UL11, UL21 (NXP y la «Ultra» de
  Mikron), NTAG213/215/216, UL-C, UL-5, varias variantes UL-Y para casos límite), etiquetas en modo de puerta
  trasera (con los dos despertares), además de etiquetas genuinas no mágicas y completamente bloqueadas para
  obtener Fails honestos, y un montón de etiquetas para la regresión;
- **categorías**: detección (17 casos), transporte directo y por puerta trasera, integridad de los datos y orden de
  las páginas, escenarios de UX, PWD-AUTH, borrado, un bloque gordo para el borrado de Gen2/MFC (19 casos) y
  regresión de todos los protocolos antiguos (Gen1a de 4 y 7 bytes, Gen2, Gen4, MFC normal).

Esa tanda sacó a la luz y mató muchos fallos: falsos «Success», botones muertos, una fuga de memoria y un indicador
de carga que giraba eternamente en una Ultralight genuina. Las limitaciones conocidas (incluido un matiz de la
detección 1K/4K a nivel de firmware) están documentadas.

Siguiente en la lista: compatibilidad de escritura de **UL-C** para USCUID-UL y, posiblemente, exotismos propios de
alguna región.

## Resolución de problemas

- **La etiqueta no se reconoce**: puede que no sea una etiqueta mágica, o que sea un preajuste desconocido:
  comprueba la configuración en bruto. Con una Gen4 con contraseña, autentícate primero.
- **"No keys found"** en un borrado de MFC: las claves actuales de la tarjeta en blanco no están en tus
  diccionarios. Añádelas (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Escritura parcial**: vuelve a poner la etiqueta y continúa; consulta **Details**. Los bits de bloqueo o de
  acceso del volcado de origen pueden hacer que algunos bloques o páginas no se puedan escribir.
- **El lector rechaza la copia**: puede que el lector filtre tu tipo de tarjeta en blanco. Véase
  [Tarjetas mágicas](/es/nfc/magic-cards), [Iron Logic](/es/nfc/iron-logic),
  [Filtros de Vizit](/es/nfc/vizit-filters).

## Relacionado

[Tarjetas mágicas](/es/nfc/magic-cards) · [MIFARE Classic](/es/nfc/mifare-classic) · [qUnleashed](/es/nfc/qunleashed) ·
[Desbloquear tarjetas](/es/nfc/unlock-with-password)
