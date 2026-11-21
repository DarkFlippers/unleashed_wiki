---
title: Emparejar el mando HID
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Emparejar el mando HID

La app de mando HID permite al Flipper controlar presentaciones, escribir texto, mover el ratón y manejar la
reproducción multimedia en un ordenador o un móvil. Esta página trata la **conexión**; qué hace cada modo está en
[Mando por USB / Bluetooth (HID)](/es/apps/hid-remote).

Puedes conectarlo de dos formas:

| | USB | Bluetooth LE |
|---|---|---|
| App | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Emparejamiento | ninguno, basta con conectarlo | una vez por host |
| Funciona con | ordenadores y móviles con USB-C/OTG | ordenadores, Android, iPhone/iPad |

::: tip Unleashed
En Unleashed las dos variantes se llaman **USB Keyboard & Mouse** y **Bluetooth Remote**, y están en las carpetas de
apps `USB` y `Bluetooth` (la documentación oficial llama «Remote» a las dos).
:::

## Por USB

1. Conecta el Flipper al ordenador con un cable de datos USB. Cierra qFlipper primero: el mando necesita el puerto
   USB.
2. Abre `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Elige un modo (Keynote, Keyboard, Mouse...). El ordenador ve un teclado o ratón nuevo; no hace falta ningún
   controlador.

Al salir de la app, el USB del Flipper vuelve al modo normal (serie).

## Por Bluetooth

1. Activa el Bluetooth en el ordenador o el móvil.
2. En el Flipper: `Main Menu → Settings → Bluetooth` y pon **Bluetooth** en **ON**.
3. Abre `Main Menu → Apps → Bluetooth → Bluetooth Remote` y elige un modo.
4. En el ordenador o el móvil abre los ajustes de Bluetooth y conéctate a **Control &lt;Flipper name&gt;** (en un
   móvil, toca **Pair**).
5. Si el Flipper muestra una confirmación de emparejamiento, pulsa <kbd>OK</kbd>.

La próxima vez el host se reconecta automáticamente cuando abras Bluetooth Remote.

::: tip Nombre personalizado
`Bluetooth Remote → Bluetooth Remote Name` cambia el nombre anunciado, lo que resulta práctico si tienes varios mandos
Flipper o quieres que parezca un teclado normal.
:::

### Si el emparejamiento falla

- Asegúrate de que el Bluetooth está en ON en `Settings → Bluetooth`.
- Elimina la entrada antigua «Control ...» de los ajustes de Bluetooth del host y después, en el Flipper, ejecuta
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` y vuelve a emparejar.
- Desconecta el Flipper de otros dispositivos (por ejemplo de la app móvil).
- Reinicia el Flipper: mantén <kbd>←</kbd> + <kbd>Back</kbd> unos 5 segundos.
- Actualiza el firmware.

El mando conserva sus propios emparejamientos (`/ext/apps_data/hid_ble/.bt_hid.keys`), separados del Bluetooth
principal del Flipper que usa la app móvil. **Bluetooth Unpairing** dentro del mando solo borra los hosts del mando.
El `Settings → Bluetooth → Unpair All Devices` global borra todo: el emparejamiento de la app móvil y también los del
mando (y de BadKB).

### iPhone / iPad: el modo TikTok no reacciona

1. En el iPhone abre `Settings → Accessibility → Touch → AssistiveTouch`.
2. Activa **AssistiveTouch**.
3. En **Pointer Devices** ve a **Devices → Bluetooth Devices** y selecciona tu Flipper.

## Páginas relacionadas

- [Mando por USB / Bluetooth (HID)](/es/apps/hid-remote)
- [Ajustes](/es/start/settings)
- [App móvil de Flipper](/es/mobile/mobile-app)
