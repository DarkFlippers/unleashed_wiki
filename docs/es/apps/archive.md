---
title: Archive (explorador de archivos)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (explorador de archivos)

**Archive** es el explorador de archivos del Flipper. Lista las llaves, tarjetas, mandos y scripts que has guardado,
permite ejecutarlos al instante y se encarga de la gestión básica de archivos: fijar a favoritos, renombrar, copiar,
mover, crear carpetas y borrar.

**Para abrirlo:** en el escritorio pulsa <kbd>↓</kbd>.

![Archive en la pestaña Sub-GHz: una carpeta Garage y señales .sub guardadas, con Barrier seleccionado](/screens/apps/archive.png)

## Pestañas

Pulsa <kbd>←</kbd> / <kbd>→</kbd> para cambiar de pestaña. Cada pestaña muestra una carpeta, filtrada por tipo de
archivo:

| Pestaña | Carpeta | Archivos que muestra |
|---|---|---|
| Favorites | tus archivos fijados | todo lo que hayas fijado (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` (mapas de [Sub-GHz Remote](/es/subghz/remote)) |
| RFID LF | `/ext/lfrfid` | `.rfid` y volcados de T5577 |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` (agenda de [SIM800](/es/gpio/sim800)) |
| U2F | interna | la entrada de la app U2F |
| Apps | `/ext/apps` | `.fap` y `.js` |
| Internal | memoria flash interna | todo (solo con el modo Debug activado) |
| Browser | toda la tarjeta SD | todo |

El Archive se abre en **Favorites**.

::: tip Unleashed
Unleashed añade la pestaña **SubRem** para los mapas de Sub-GHz Remote, la pestaña **Phone** para la agenda de SIM800
(una entrada `.phone` se abre directamente en la app SIM800), muestra los volcados de T5577 junto a las llaves en
**RFID LF** y lista los scripts `.js` en **Apps**.
:::

## Botones en la lista

| Botón | Acción |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | moverse por la lista (mantén pulsado para desplazarte más rápido) |
| <kbd>←</kbd> / <kbd>→</kbd> | pestaña anterior / siguiente |
| <kbd>OK</kbd> sobre un archivo | abrir su menú |
| <kbd>OK</kbd> sobre una carpeta | entrar en la carpeta |
| mantener <kbd>OK</kbd> sobre una carpeta | abrir el menú de la carpeta |
| <kbd>OK</kbd> en Favorites | ejecutar el archivo al instante |
| mantener <kbd>OK</kbd> en Favorites | abrir el menú |
| mantener <kbd>OK</kbd> en una carpeta vacía | abrir el menú (Paste / NewDir) |
| <kbd>Back</kbd> | subir una carpeta, o salir |

## El menú del archivo: Actions y Manage

El menú tiene dos páginas. Su título indica cuál está abierta: **Actions** o **Manage**. Pulsa <kbd>←</kbd> o
<kbd>→</kbd> dentro del menú para alternar entre ellas (no en la pestaña Favorites). <kbd>↑</kbd> / <kbd>↓</kbd>
seleccionan un elemento, <kbd>OK</kbd> lo ejecuta y <kbd>Back</kbd> cierra el menú.

**Actions** (un archivo que el firmware sabe abrir):

- **Run**: abrir el archivo en su app (emular una llave, enviar una señal, ejecutar un script...).
- **Pin** / **Unpin**: añadir a Favorites o quitarlo de ahí.
- **Info**: nombre y tamaño del archivo.
- **Show**: ver el archivo como texto (en los formatos de texto).

Para un tipo de archivo desconocido, Actions solo ofrece **Info** y, en los archivos de texto, **Show**.

**Manage:**

- **Cut** / **Copy**, y después **Paste** en la carpeta de destino.
- **NewDir**: crear una carpeta.
- **Rename**: escribir un nombre nuevo.
- **Delete**: pide confirmación antes.

En la pestaña **Favorites** el menú es **Run**, **Unpin**, **Show** (si procede) y **Move**. Move permite reordenar los
favoritos: pulsa <kbd>↑</kbd> / <kbd>↓</kbd> para desplazar el elemento y <kbd>OK</kbd> para guardar la nueva posición
(<kbd>Back</kbd> cancela).

## Tareas habituales

### Fijar un archivo a Favorites

1. Escritorio → <kbd>↓</kbd> para abrir el Archive.
2. Ve a la pestaña correspondiente con <kbd>←</kbd> / <kbd>→</kbd> y selecciona el archivo.
3. Pulsa <kbd>OK</kbd> → **Pin**. El archivo aparece ahora en la pestaña Favorites.

### Renombrar una llave o señal guardada

1. Selecciona el archivo y pulsa <kbd>OK</kbd>.
2. Pulsa <kbd>→</kbd> para cambiar el menú a **Manage**.
3. Elige **Rename**, escribe el nombre y confirma.

### Borrar archivos para liberar espacio

1. Selecciona el archivo, <kbd>OK</kbd>, <kbd>→</kbd> para ir a **Manage**.
2. Elige **Delete** y confirma.

Para limpiar una carpeta entera, usa la pestaña **Browser**: selecciona la carpeta, mantén <kbd>OK</kbd>,
**Manage → Delete**.

### Mover un archivo a otra carpeta

1. Selecciona el archivo, <kbd>OK</kbd>, **Manage → Cut**.
2. Ve a la carpeta de destino (la pestaña **Browser** llega a todas las carpetas de la tarjeta).
3. Pulsa <kbd>OK</kbd> sobre cualquier archivo (o mantén <kbd>OK</kbd> en una carpeta vacía) → **Paste**.

## Resolución de problemas

- **«Empty»** significa que la carpeta no tiene archivos del tipo de esa pestaña. Comprueba la extensión: un archivo
  `.ir` dentro de `/ext/nfc` no aparecerá en ninguna de las dos pestañas, pero sí en la pestaña Browser.
- **Falta la pestaña Internal**: solo es visible cuando `Settings → System → Debug` está en ON.
- **Ha desaparecido un favorito**: los favoritos cuyo archivo ya no existe (movido, renombrado o borrado fuera del
  Archive) se eliminan de la lista. Vuelve a fijar el archivo en su nueva ubicación.
- **Delete** siempre pregunta `Delete <name>?` con los botones **Cancel** / **Delete**, así que nada se borra por una
  pulsación descuidada.

## Páginas relacionadas

- [Tarjeta microSD](/es/start/sd-card)
- [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps)
- [Escritorio](/es/start/desktop)
