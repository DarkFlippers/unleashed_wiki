---
title: Aprender y enviar señales
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Aprender y enviar señales IR

El Flipper Zero puede copiar los botones de un mando IR uno por uno y conservarlos como un **mando virtual**: un
fichero `.ir` en `/ext/infrared/`. Resulta útil cuando el mando original se ha perdido, está roto o simplemente está
en otra habitación, o cuando un mando universal no encuentra tu aparato.

Las señales de [protocolos conocidos](/es/infrared/protocols) se decodifican y se guardan en forma *parsed* compacta
(protocolo + dirección + comando). Todo lo demás se guarda como temporizaciones **RAW**, que también sirven para la
reproducción.

## Aprender un mando nuevo

1. Ve a `Main Menu → Infrared → Learn New Remote`.
2. La pantalla dice **"Point the remote at IR port and push the button"**. Sujeta el mando a unos centímetros del
   borde superior del Flipper, con la ventana IR a la vista.

   ![Learn New Remote esperando una señal: "Point the remote at IR port and push the button"](/screens/infrared/learn.png)

3. Pulsa el botón del mando **brevemente**. No lo mantengas: un botón mantenido produce una captura larga llena de
   repeticiones.
4. Aparece la pantalla de captura:
   - una señal decodificada muestra el nombre del protocolo y la dirección/comando, por ejemplo `NECext`, `A: 0x87EE`, `C: 0xA05D`;
   - una señal desconocida muestra **Unknown** y el número de muestras, por ejemplo `150 samples`.

   ![Pantalla de captura: el protocolo decodificado NEC con su dirección y comando, y Retry, Send y Save abajo](/screens/infrared/learn_success.png)

5. Elige qué hacer:
   - <kbd>OK</kbd> **Send**: reproduce la señal capturada mientras mantengas el botón, para probarla al instante;
   - <kbd>←</kbd> **Retry**: pregunta *"Retry Reading? All unsaved data will be lost!"*; después <kbd>←</kbd> Exit
     descarta la captura y vuelve a escuchar, y <kbd>→</kbd> Stay regresa;
   - <kbd>→</kbd> **Save**: continúa hasta el nombre.
6. Escribe un nombre de botón en **"Name the button"** (máximo 23 caracteres) y confirma. El nombre por defecto se
   genera a partir de la señal: las 4 primeras letras del protocolo y el comando (por ejemplo `NECe_A05D`), o
   `RAW_<samples>` para RAW.
7. Se muestra **"Success!"** y se abre el mando nuevo. El primer mando se guarda como `/ext/infrared/Remote.ir`; si
   ese nombre está ocupado, `Remote1.ir`, `Remote2.ir`, etc.

![Señal capturada en la pantalla](/img/remote/a62fc8f9d738534b.png)

::: tip Renombra el mando
Un mando nuevo siempre se llama `Remote`. Renómbralo cuanto antes con `Edit → Rename Remote` (véase más abajo), o
acabarás con `Remote`, `Remote1`, `Remote2`…
:::

### Añadir más botones

En la lista de botones del mando, baja hasta el final y selecciona **`+`**. Se abre de nuevo la pantalla de
aprendizaje. Captura, **Save**, pon nombre al botón y obtendrás **"Saved"**: el botón se añade al mismo fichero.

Pulsar <kbd>Back</kbd> en la pantalla de captura pregunta *"Exit to Infrared Menu?"* (o *"Exit to Remote Menu?"* al
añadir a un mando existente): los datos sin guardar se pierden si eliges Exit.

## Enviar un botón guardado {#send-a-saved-button}

1. Ve a `Main Menu → Infrared → Saved Remotes` y elige un fichero `.ir`.
2. Apunta con el borde superior del Flipper hacia el aparato.
3. Selecciona un botón con <kbd>↑</kbd> / <kbd>↓</kbd> y pulsa <kbd>OK</kbd>.

La señal se envía **mientras mantengas** <kbd>OK</kbd>: una pulsación para un comando simple, mantenido para
acciones de «pulsar y mantener» como subir el volumen progresivamente. El LED parpadea durante la transmisión.

![Envío de una señal guardada](/img/remote/d20ed673954c3711.png)

::: tip Favoritos y Archive
Los mandos guardados aparecen también en el **Archive** (`Main Menu → Archive → Infrared`) y desde allí se pueden
añadir a favoritos. En Flipper Mobile App aparecen en **Archive → Infrared**; véase
[Mandos en la aplicación móvil](/es/infrared/mobile).
:::

## Editar un mando

Abre un mando y selecciona **Edit** al final de la lista de botones. El menú Edit contiene:

| Elemento | Qué hace |
|---|---|
| **Add Button** | Aprende un botón más (igual que `+`). |
| **Rename Button** | Elige un botón y escribe un nombre nuevo. |
| **Move Button** | Pantalla *"Select a Button to Move"*: selecciona un botón, pulsa <kbd>OK</kbd> para cogerlo (se desplaza a la derecha), muévelo con <kbd>↑</kbd> / <kbd>↓</kbd> y pulsa <kbd>OK</kbd> otra vez para soltarlo. |
| **Delete Button** | Elige un botón. La confirmación *"Delete Button?"* muestra su nombre y protocolo / dirección / comando (o `RAW` y el número de muestras). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Renombra el mando y el fichero. Si el nombre ya existe, se añade un número. |
| **Delete Remote** | Confirmación *"Delete Remote?"* con el número de botones. Borra el fichero `.ir`. |

Los nombres están limitados a **23 caracteres**, tanto para botones como para mandos. Las ediciones más grandes
(fusionar ficheros, quitar muchos botones) son más fáciles en un PC: descarga el fichero con
[qFlipper](/es/mobile/qflipper) y edítalo como texto; véase el
[formato de los ficheros IR](/es/infrared/file-format).

::: warning Los ficheros de biblioteca no son mandos
Si intentas abrir un fichero de `/ext/infrared/assets/` mediante Saved Remotes, obtendrás
*"Library file … can't be opened as a remote"*. Los ficheros de biblioteca (`Filetype: IR library file`) solo los
usan los [mandos universales](/es/infrared/universal-remotes).
:::

## Extras en modo depuración {#debug-mode-extras}

Con `Settings → System → Debug` activado, el menú Infrared muestra dos elementos más:

- **Learn New Remote RAW**: el mismo procedimiento que Learn, pero con el decodificador desactivado y cada señal
  almacenada como RAW. Útil cuando el decodificador reconoce un protocolo pero la reproducción decodificada no
  funciona en tu aparato.
- **Debug RX**: la pantalla *"INFRARED monitor"*, que muestra en tiempo real lo que recibe el receptor.

## Resolución de problemas

| Problema | Qué probar |
|---|---|
| No pasa nada al pulsar el mando | Comprueba las pilas del mando (mira su LED a través de la cámara de un móvil). Acércate y apunta recto al borde superior. Evita la luz solar directa y las lámparas fluorescentes o LED cercanas. |
| La señal se captura como **Unknown / RAW** aunque el mando sea corriente | Las interferencias pueden forzar RAW. Usa **Retry** varias veces hasta conseguir una señal decodificada. Si de verdad es un protocolo desconocido, RAW está bien. |
| Capturas RAW enormes (cientos de muestras) | Has mantenido el botón. Haz una pulsación corta; unas 100 muestras es lo normal para una pulsación simple. Las capturas muy largas se reproducen despacio. Una señal RAW puede contener como máximo 1024 temporizaciones. |
| El aparato no reacciona al botón guardado | Acércate y apunta directamente a la ventana IR del aparato. Prueba a enviarlo varias veces o a mantener <kbd>OK</kbd> más tiempo. Para distancias largas usa un [módulo IR externo](/es/infrared/external-ir). |
| El aire acondicionado reacciona mal | Los mandos de aire acondicionado envían el estado completo (modo, temperatura, ventilador) en cada pulsación. Graba cada estado que necesites como un botón propio; véase [Contribuir con capturas](/es/infrared/captures#air-conditioners). |
| "Failed to load …" al enviar | El fichero `.ir` está dañado o se editó a mano de forma incorrecta. Compruébalo contra el [formato del fichero](/es/infrared/file-format). |

## Páginas relacionadas

- [Mandos universales](/es/infrared/universal-remotes)
- [Mandos en la aplicación móvil](/es/infrared/mobile)
- [Formato de los ficheros IR](/es/infrared/file-format)
- [Módulos IR externos](/es/infrared/external-ir)
