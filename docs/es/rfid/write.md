---
title: Escribir en chips vírgenes
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# Escribir llaves de 125 kHz en chips vírgenes

Las tarjetas y llaveros originales de 125 kHz son casi siempre de solo lectura. Para hacer una copia física necesitas
un **chip virgen escribible**: un chip «mágico» que se puede programar para comportarse como una tarjeta de otro
protocolo. Flipper Zero puede escribir en un chip así cualquier llave guardada, leída o añadida manualmente.

## Qué chips vírgenes se pueden escribir

| Chip (como aparece en pantalla) | Nombres habituales en el mercado | Escribe | Por defecto |
|---|---|---|---|
| **T5577** | T5577, ATA5577, tarjetas/llaveros/pegatinas «5577» | todos los protocolos | ON |
| **EM4305** | Chips vírgenes EM4305 / EM4205 | familia EM4100, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (clon de Hitag Micro, contraseña por defecto) | familia EM4100 | ON |
| **8210** | ID8210 (mismo chip, contraseña del clonador FURUI) | familia EM4100 | ON |
| **H5.5** | iKey H5.5 (mismo chip, contraseña de iKey) | familia EM4100 | ON |
| **8268** | ID8268 (chip mágico Hitag S) | EM4100 solo a RF/64 | **OFF** |

::: tip Unleashed
La documentación oficial solo habla del T5577. El soporte de Hitag Micro para **8265/H5, H5.5 y 8210** lo añadió a
Unleashed **@gromovyna** — los chips solo se diferencian por la contraseña de login, así que el Flipper prueba cada
contraseña conocida por turnos en lugar de preguntártela. Contexto e historia:
[T5577 y Hitag Micro](/es/rfid/t5577-hitag).
:::

::: warning 8268 hay que activarlo expresamente
El destino **8268** (Hitag S) está desactivado por defecto. A diferencia de los demás escritores, selecciona cualquier
tag Hitag S que responda, y en un Hitag S auténtico las páginas 4 y 5 contienen datos de aplicación — el Flipper no
puede distinguir un tag auténtico de un clon. Actívalo solo cuando sepas que hay un chip virgen 8268 sobre la bobina.
:::

## Escribir una llave

1. Lee un tag (`Read` → **More** → **Write**) o abre uno guardado (`Saved` → llave → **Write**).
2. Coloca el chip virgen contra la parte trasera del Flipper y **no lo muevas**. El LED parpadea en magenta.
3. La pantalla muestra **Writing**, el protocolo entre corchetes, el nombre del archivo (o *Unsaved Tag*) y, entre
   paréntesis, el **chip que se está probando en ese momento**, por ejemplo:

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Pantalla de escritura con el protocolo [EM4100], el nombre de la llave y el chip que se prueba, (T5577), entre paréntesis](/screens/lfrfid/write.png)

4. El Flipper escribe cada tipo de chip activado por turnos y **vuelve a leer el tag** después de cada intento. En
   cuanto la relectura coincide, se detiene.
5. Si todo va bien verás **Success!** con el nombre del chip que ha aceptado realmente los datos (por ejemplo
   `T5577`, `EM4305`, `H5.5`), y la app vuelve al menú de la llave.

![Escritura en curso, mostrando el chip que se está probando](/img/remote/34b72cbd8417d74e.png)

![Resultado de la escritura con el nombre del chip](/img/remote/3ca59457a78dad5b.png)

::: tip ¿Por qué el nombre del chip?
Con varios tipos de chip que probar (y tres contraseñas para Hitag Micro), una escritura puede tardar bastante más y
no quedaba claro qué se había escrito. Mostrar el chip que se intenta y el chip final fue el arreglo de UX de
@gromovyna: técnicamente es el nombre comercial de la variante del chip virgen, no un protocolo.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` lista todos los destinos: **T5577**, **EM4305**, **8265**,
**8210**, **H5.5** y **8268**, cada uno en **ON** / **OFF**.

- <kbd>OK</kbd>, <kbd>←</kbd> o <kbd>→</kbd> conmuta el chip resaltado.
- La elección se guarda al salir de la página (<kbd>Back</kbd>) en `/ext/lfrfid/.lfrfid.settings`.
- Desactivar los chips que nunca usas acelera las escrituras (cada chip activado que no coincide cuesta una escritura
  más una verificación).
- El comando `rfid write` de la CLI respeta el mismo ajuste.

Si la página no se abre, verás *Settings plugin failed to load* — actualiza los recursos de la SD (la página es un
archivo de plugin aparte). Las escrituras siguen usando lo que esté almacenado en el archivo de ajustes.

## Write and set password

`Saved` → llave → **Write and set password** escribe la llave en un **T5577** y activa su protección por contraseña,
de modo que nadie pueda reescribir el tag sin la contraseña.

1. Introduce la contraseña de 4 bytes en hexadecimal. Si todavía no había ninguna, el campo se rellena previamente con
   una palabra aleatoria del diccionario T5577.
2. Mantén el chip virgen quieto. La pantalla muestra **Writing with password**, `[Protocol]` y el paso actual.
3. Primero se escribe la llave y se vuelve a leer, después la contraseña va al bloque 7 y se relee, y solo entonces se
   activa el bit de contraseña del bloque 0. **Apunta la contraseña** — un T5577 bloqueado con una contraseña
   desconocida no se puede reutilizar.

Resultados posibles:

| Pantalla | Significado |
|---|---|
| **Success!** | Llave escrita, contraseña almacenada y protección activada |
| **Error** — *This protocol cannot be written with a password* | El protocolo necesita los 7 bloques de datos, así que el bloque 7 no puede albergar una contraseña |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | El tag ya está protegido |
| **Cannot read it** | Hay algo sobre la bobina pero sus bloques no se pueden leer — bórralo por completo o limpia primero su contraseña |
| **Not written** | Un bloque rechazó la llave; el tag contiene parte de ella y ninguna contraseña |
| **Not protected** | La contraseña no llegó al bloque 7, o el tag se negó a activar la protección |
| **Not confirmed** | La contraseña está en el tag, pero no se pudo releer si la protección está activa |
| **Still trying to write...** | Ningún tag responde — comprueba que sea un T5577 escribible |

## Mensajes de error de una escritura normal

| Mensaje | Qué hacer |
|---|---|
| *This protocol cannot be written* | No existe ninguna codificación de chip para él |
| *No write chips enabled. Enable one in Settings* | Todos los destinos están en OFF |
| *No enabled chip can write this protocol* | Por ejemplo, solo EM4305 activado para una llave HID — activa T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Aparece tras unos 10 s o varias verificaciones fallidas. El tag es de solo lectura, está protegido con contraseña, es un chip no compatible o está mal colocado. El Flipper sigue intentándolo hasta que pulses <kbd>Back</kbd>. |

## Resolución de problemas

- **El chip virgen tiene contraseña.** Muchos clonadores baratos bloquean los chips vírgenes T5577. Usa la
  [app T5577](/es/rfid/t5577-app) → **Clear Password** (prueba tu contraseña y después el diccionario).
- **Un T5577 ha quedado con una configuración corrupta** (no se lee como nada). Usa la app T5577 → **Wipe Tag**.
- **Hitag Micro (8265/8210/H5.5) exige una buena colocación.** Escribir estos chips tarda más y es sensible a la
  posición; el Flipper solo tiene TX en LF, así que el éxito se confirma únicamente releyendo el tag.
- **«Success» en una tarjeta de solo lectura.** Si un tag no escribible ya lleva el mismo ID, la relectura coincide y
  la escritura se da por correcta.
- **Llaveros con metal o carcasas gruesas.** Prueba distintos puntos; los llaveros suelen tener la bobina
  descentrada.

## Páginas relacionadas

- [T5577 y Hitag Micro](/es/rfid/t5577-hitag) · [App T5577](/es/rfid/t5577-app) ·
  [Protocolos](/es/rfid/protocols) · [Lectura](/es/rfid/read)
