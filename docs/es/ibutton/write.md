---
title: Escribir en llaves vírgenes
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# Escribir llaves iButton en llaves vírgenes

Las llaves iButton originales tienen un ID de fábrica que no se puede cambiar. Para copiar una necesitas una **llave
virgen**: una llave reescribible cuyo ID se puede programar. Flipper Zero tiene dos modos de escritura:

- **Write ID** — escribe el ID (ROM / código) en una llave virgen. Es el típico «hacer una copia de la llave del
  portero automático».
- **Full Write on Same Type** — solo para DS1992, DS1996 y DS1971: copia el contenido de la **memoria** a otra llave
  auténtica del mismo tipo (DS1992 → DS1992). La llave de destino conserva su propio ID.

## Llaves vírgenes compatibles

| Llave virgen (como en Settings) | Escribe | Notas |
|---|---|---|
| **RW1990.1** | IDs de DS1990, DS1420 | Llaves vírgenes tipo RW1990; esta variante escribe los bits invertidos |
| **RW1990.2** | IDs de DS1990, DS1420 | Llaves vírgenes tipo RW1990, variante no invertida |
| **TM2004** | IDs de DS1990, DS1420, DS1992, DS1996, DS1971 y 1-Wire genérico | Llaves vírgenes RW2004/TM2004; solo se escribe el ID, aunque la llave tenga memoria |
| **TM01x** | ID de DS1990, **Cyfral**, **Metakom** | Llaves vírgenes TM01/TM01x |

Las llaves vírgenes que se venden como RW1990, TM1990 o TM08v2 las gestionan las variantes RW1990; el Flipper prueba
ambas, así que no necesitas saber cuál tienes.

::: tip Unleashed
- **Settings → Write Blanks** permite activar y desactivar tipos de llave virgen (todos están en ON por defecto).
- La pantalla de escritura muestra qué llave virgen se está probando, y la pantalla de éxito indica *Written to
  TM2004!*, etc.
- **Cyfral y Metakom** se pueden escribir en llaves vírgenes **TM01x**.
:::

::: warning TM01x para Cyfral / Metakom no tiene vuelta atrás
Para Cyfral y Metakom la llave virgen TM01x se escribe, se vuelve a leer y se compara, y después se **finaliza** en
modo Cyfral o Metakom. La finalización es irreversible: la llave virgen deja de responder como dispositivo 1-Wire y no
se puede reescribir — ni siquiera como llave Dallas. Si la verificación falla, la llave virgen no se finaliza y sigue
siendo escribible. Un ID Dallas escrito en una TM01x no se finaliza.

Las llaves Metakom con paridad incorrecta se rechazan (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Abre la llave: `Saved` → llave → **Write ID** (o **More → Write ID** después de leerla).

   ![Menú de una llave guardada con Emulate, Write ID, Edit y Rename](/screens/ibutton/saved_menu.png)

2. La pantalla muestra **Writing ID**, `[Protocol]`, el nombre de la llave (o *Unsaved Key*) y, entre paréntesis, el
   tipo de llave virgen que se está probando — por ejemplo `(RW1990.1)`.

   ![Pantalla Writing ID con el protocolo [DS1990], el nombre de la llave y la llave virgen que se prueba, (RW1990.1)](/screens/ibutton/write.png)

3. Apoya la llave virgen sobre la **parte plana** del contacto (pin de datos izquierdo + pin central de masa), igual
   que al leer. Mantenla quieta.
4. El Flipper prueba todas las llaves vírgenes activadas que puedan albergar este protocolo y vuelve a leer el
   resultado para comprobarlo.
5. **Written to RW1990.2!** (o *Successfully written!*) — listo.

## Full Write on Same Type

1. `Saved` → llave DS1992 / DS1996 / DS1971 → **Full Write on Same Type**.
2. La pantalla muestra **Full Writing**. Apoya una llave auténtica del **mismo** tipo.
3. Se escribe la memoria; el ID propio de la llave de destino se mantiene. Este modo no usa el ajuste Write Blanks.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` lista **RW1990.1**, **RW1990.2**, **TM2004** y **TM01x** con
**ON**/**OFF**. Cambia el valor con <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd>; se guarda al salir, en
`/ext/ibutton/.ibutton.settings`. El comando `ikey write` de la CLI usa el mismo ajuste.

Si la página indica *Settings page missing. Update the SD resources*, reinstala el firmware con la tarjeta SD puesta.

## Errores

| Pantalla | Significado |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | Todos los tipos de llave virgen están en OFF |
| **Cannot Write** — *No enabled blank can write this key* | Por ejemplo, solo RW1990 activado para una llave Metakom |
| **Cannot Write** — *This key cannot be written* (o el motivo del protocolo) | Los datos de la llave no son válidos para escribir |
| La pantalla de escritura se queda fija, el LED parpadea | Todavía no se detecta ninguna llave virgen — revisa el contacto, o el tipo de llave virgen no es compatible |

## Resolución de problemas

- **Contacto.** El centro de la llave virgen debe tocar el pin de datos y su borde, el pin de masa.
- **Tipo de llave virgen desconocido.** Prueba activando todos los tipos. Algunas llaves vírgenes baratas son de
  tipos que el Flipper no puede programar.
- **«Éxito» pero el lector rechaza la copia.** Algunos lectores filtran llaves vírgenes (comprueban comportamientos
  propios de llaves escribibles) — ahí el Flipper no puede hacer nada.
- **TM01x gastada.** Una TM01x finalizada como Cyfral/Metakom no se puede reutilizar.

## Páginas relacionadas

- [Lectura](/es/ibutton/read) · [Protocolos](/es/ibutton/protocols) ·
  [Añadir manualmente](/es/ibutton/add-manually)
