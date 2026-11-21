---
title: Aplicaciones
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, flipper-docs, unleashed-src]
---
# Aplicaciones

Además de las grandes herramientas integradas (Sub-GHz, NFC, RFID, Infrarrojos, iButton, Bad USB, GPIO), Flipper Zero
ejecuta **aplicaciones**: pequeños programas empaquetados como archivos `.fap` que residen en la tarjeta microSD.
Unleashed incluye un conjunto de apps de sistema propias en cada compilación, ofrece dos packs de apps opcionales
(Base y Extra) y se mantiene compatible con el catálogo oficial de aplicaciones.

::: tip Unleashed
Unleashed mantiene la compatibilidad de API con el firmware oficial, así que las apps del catálogo oficial (Flipper
Lab o la app móvil) normalmente también funcionan. Además, cada release de Unleashed tiene una compilación `e` que
preinstala el pack **Extra Apps** de apps de la comunidad. Consulta
[Aplicaciones incluidas en Unleashed](/es/apps/catalog).
:::

## Obtener y ejecutar aplicaciones

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog): apps integradas, los packs Base y Extra, y qué significan las letras de compilación `e`, ` ` y `c`.
- [Aplicaciones en la tarjeta SD (.fap)](/es/apps/sd-card-apps): dónde residen las apps, cómo instalarlas a mano o desde el catálogo, y cómo comprueba el cargador la versión de la API.
- [Archive (explorador de archivos)](/es/apps/archive): explorar, ejecutar, fijar, renombrar, mover y borrar archivos guardados.
- [Resolución de problemas de apps](/es/apps/troubleshoot): qué significa cada error del cargador y cómo solucionarlo.

## Aplicaciones integradas

- [Llave de seguridad U2F](/es/apps/u2f): usar el Flipper como segundo factor FIDO U2F.
- [Reloj](/es/apps/clock): reloj nocturno con control de brillo, cronómetro y alarma diaria.
- [Mando por USB / Bluetooth (HID)](/es/apps/hid-remote): todos los modos de la app de mando HID, botón a botón.
- [Emparejar el mando HID](/es/apps/controllers): conectar el mando por Bluetooth o USB y resolver problemas de emparejamiento.
- [FindMy Flipper](/es/apps/find-my-flipper): hacer que el Flipper sea visible en Apple Find My, Samsung SmartThings, Tile o Google Find My Device.
- [Estilos del menú principal](/es/apps/menu-styles): cambiar el aspecto del menú principal (PS4, Wii, DSi, C64, CoverFlow, Grid y otros).
- [Snake](/es/apps/snake): el juego clásico.

## Aplicaciones de los packs

- [Barcode Generator](/es/apps/barcode)
- [Multi Converter](/es/apps/multi-converter)
- [Sentry Safe](/es/apps/sentry-safe)

Las apps auxiliares de Sub-GHz, NFC y RFID (Seed Capturer, Remote Analyzer, MFKey, T5577 y otras) se tratan en sus
propias secciones, por ejemplo [Seed Capturer](/es/subghz/seed-capturer), [App MFKey](/es/nfc/mfkey-app) y
[App T5577](/es/rfid/t5577-app).
