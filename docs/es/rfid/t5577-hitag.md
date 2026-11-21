---
title: T5577 y Hitag Micro (por @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Escritura de Hitag Micro, UX de escritura y borrado del T5577

Basado en el artículo de @gromovyna *«Preview of the LF (RFID) features I prepared for Unleashed»* (junio de 2026),
actualizado con el aspecto que tienen estas funciones en el firmware actual.

![](/img/remote/2e30c69f7eded901.png)

## Introducción

Después de una larga pausa, @gromovyna volvió a la investigación y se fijó en los chips vírgenes **H5.5** que vende
*iKey*. Por el Discord de Iceman ya se sabía que el H5.5 es el mismo clon chino de **Hitag Micro** sobre el que iKey
puso su propia contraseña. El panorama de nombres:

| Nombre | Qué es |
|---|---|
| **8265 / H5** | el chip con la contraseña por defecto |
| **H5.5** | el mismo chip con la contraseña de **iKey** |
| **8210** | el mismo chip con la contraseña del clonador chino **FURUI** |

Recuperó la contraseña de iKey (al segundo día de intentos), la compartió con la comunidad y
[actualizó las notas de magic cards de Proxmark3](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265).
Después implementó las funciones para el Flipper — como pull requests a **Unleashed**, con la esperanza de llevarlas
también al OFW cuando vuelva a estar en desarrollo activo.

Las contraseñas que usa el firmware para las tres variantes:

| Variante | Contraseña |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Soporte de Hitag Micro

El Flipper puede ahora **escribir** clones de Hitag Micro — **8265/H5**, **H5.5** y **8210** — como llaves EM4100 (el
chip se configura para enviar la trama EM4100 por sí mismo, «transponder talks first»).

Limitaciones de la arquitectura actual:
- el hardware LF del Flipper solo **transmite** mientras escribe, así que el éxito solo se puede comprobar
  **releyendo el tag**;
- se invirtió mucho tiempo en calibrar constantes, pero escribir estos chips sigue requiriendo una **buena
  colocación**.

### Por qué la escritura se volvió más lenta

Añadir el soporte empeoró la UX, porque la lógica de escritura es ahora un bucle que prueba, uno tras otro:

- **T5577**
- **EM4305**
- **Hitag Micro** — y aquí tres variantes, una por cada contraseña de fábrica conocida; además, estas operaciones son
  de por sí más lentas

Para Hitag Micro el Flipper prueba por turnos la contraseña de cada variante conocida, de modo que no tenga que
preguntar al usuario: preguntar echaría por tierra una de las ideas principales de Flipper Zero, la simplicidad. El
precio es la velocidad de escritura. Una contraseña incorrecta simplemente la rechaza el chip y deja el tag intacto;
la variante que se relee correctamente es la que está presente.

Para el usuario esto quedaba fatal — como si no pasara nada — y no quedaba claro con qué protocolo se había escrito el
tag. De ahí la siguiente función.

## UX: ¿con qué estamos escribiendo / qué hemos escrito?

Durante una escritura la pantalla muestra ahora **qué chip se está probando**:

![Escritura en curso](/img/remote/34b72cbd8417d74e.png)

Técnicamente no es un protocolo, sino el nombre comercial de la variante del chip virgen — pero se entiende la idea.
Después de escribir, el resultado se muestra con el mismo nivel de detalle:

![Resultado de la escritura](/img/remote/3ca59457a78dad5b.png)

::: tip En el firmware actual
- Los chips que se prueban son configurables: `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210 y
  H5.5 (todos en ON) y **8268** (chip mágico ID8268 / Hitag S, en OFF por defecto). Desactiva los que no uses para
  acelerar las escrituras.
- El destino 8268 solo escribe EM4100 a RF/64 y hay que activarlo expresamente, porque en un Hitag S auténtico
  sobrescribiría datos de usuario.
- El formato de la pantalla de escritura es `[Protocol]`, nombre del archivo, `(chip)`; **Success!** muestra el chip
  que ha aceptado los datos. Detalles: [Escribir en chips vírgenes](/es/rfid/write).
:::

## Devolver un T5577 a su estado de fábrica

Una función que @gromovyna echaba de menos desde hacía tiempo en el Flipper: devolver un T5577 al estado virgen. Un
intento anterior de añadirla a Unleashed había quedado bloqueado; más tarde se fusionaron funciones como *clear T5577
password* con los mismos problemas arquitectónicos, así que un arreglo adecuado tendría que ser global.

Comportamiento (igual que en Proxmark3):

- antes de empezar se te advierte de que **se borrarán todos los datos** y de que el tag **no será legible con Read**
  hasta que le escribas datos nuevos;
- el borrado **no elimina una contraseña** — si el tag está protegido, limpia primero la contraseña con la función
  específica;
- se muestra una barra de progreso. La mayor parte del tiempo no se va en el borrado en sí, sino en **verificarlo**:
  por la API de LF, el Flipper comprueba que el tag está limpio intentando leerlo y esperando que esa lectura falle;
- al final obtienes un mensaje de éxito o de fallo.

![Advertencia del borrado](/img/remote/f5ed0aa91bfcae98.png)

![Borrado en curso](/img/remote/153b85d1fede96d9.png)

![Verificación](/img/remote/0f2f4e240a35940d.png)

![Éxito](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — dónde está ahora
En el artículo el borrado estaba en `125 kHz RFID → Extra Actions`. En el firmware actual (junto con Clear Password)
se ha trasladado a la app **T5577** incluida: `Apps → RFID → T5577 → Wipe Tag`. La advertencia dice *Wipe T5577 —
Erases all data. The tag stops working as a key. Hold still while running*; el resultado es **Wiped!** o **Not wiped**
(por ejemplo *No answer. Protected? Try Clear Password*). El borrado escribe bloques de datos a cero y una
configuración por defecto, así que la app T5577 puede seguir leyendo el chip después. Consulta
[App T5577](/es/rfid/t5577-app).
:::

## «¡Esto lo has vibe-codeado!»

En palabras del autor, esto fue un experimento para ver si se puede escribir código correcto para estos sistemas con
un LLM. El proceso fue meticuloso: hojas de datos, el código del firmware Unleashed para entender la arquitectura, el
código de Proxmark3. Cada paso se validó, se probó en hardware real y se ajustó con precisión. Así que las funciones
fueron *escritas por Claude Code*, pero *creadas por @gromovyna*.

## Pull requests

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

Más artículos e investigación: [@gromovyna](https://t.me/gromovyna).

## Páginas relacionadas

- [Escribir en chips vírgenes](/es/rfid/write) · [App T5577](/es/rfid/t5577-app) ·
  [Protocolos](/es/rfid/protocols)
