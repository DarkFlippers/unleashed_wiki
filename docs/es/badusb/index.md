---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

La aplicación **Bad USB** convierte el Flipper en un teclado (y ratón) que escribe un script preparado en un
ordenador. El ordenador ve un dispositivo de interfaz humana (HID) corriente, así que no hacen falta controladores.
Los scripts se escriben en una versión ampliada de **DuckyScript** (el lenguaje del USB Rubber Ducky) y se guardan
como ficheros `.txt` en la tarjeta microSD.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Usos legítimos habituales: automatizar tareas de configuración repetitivas en tus propios equipos, escribir
contraseñas o ficheros de configuración largos, instalar software en un PC recién montado, demostraciones y
formación en concienciación sobre seguridad.

::: danger Aspectos legales
Un dispositivo de inyección de pulsaciones puede hacer todo lo que haría una persona sentada al teclado. Ejecuta
scripts únicamente en ordenadores de tu propiedad o que tengas permiso explícito para auditar.
:::

La aplicación funciona por cable **USB** o por **Bluetooth (BLE)**; en el segundo caso el anfitrión la ve como un
teclado Bluetooth.

::: tip Unleashed
Unleashed integra **BadKB** (de Willy-JL, ClaraCrazy y los colaboradores de XFW) directamente en la aplicación Bad USB:
- **modo BLE** con nombre de dispositivo, dirección MAC, modo de emparejamiento y emparejamiento persistente
  configurables, además de los comandos de script `BLE_ID` / `BT_ID`;
- ajustes de **identidad USB**: nombre de fabricante y de producto, VID/PID, aleatorización;
- **distribuciones de teclado** para muchos idiomas ([de rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- el comando **`DUCKY_LANG`**, con el que un script puede elegir su propia distribución de teclado (nuevo en la versión actual, PR #1224 de @ANTONiO-eagle).
:::

## Ficheros

| Ruta | Contenido |
|---|---|
| `/ext/badusb/` | Tus scripts (`.txt`). El explorador de ficheros de la aplicación se abre aquí. |
| `/ext/badusb/examples/` | Scripts de demostración incluidos en el firmware (Windows, macOS, GNOME, ChromeOS, prueba de ratón, instaladores de qFlipper). |
| `/ext/badusb/assets/layouts/` | Ficheros de distribución de teclado (`.kl`). Véase [Distribuciones de teclado](/es/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Ajustes de la aplicación: distribución global, modo USB/BLE, identidad USB y BLE. |

Sube los scripts con [qFlipper](/es/mobile/qflipper), la [aplicación móvil](/es/mobile/mobile-app) o copiándolos
directamente a la tarjeta SD. Un fichero con el mismo nombre se sobrescribe sin avisar.

## Páginas de esta sección

| Página | Qué aprenderás |
|---|---|
| [Uso de Bad USB](/es/badusb/usage) | Ejecutar scripts por USB y BLE, el menú `Config`, todos los ajustes |
| [Formato de los scripts](/es/badusb/script-format) | Referencia completa de comandos: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, ratón, ID, DUCKY_LANG… |
| [Ejemplos](/es/badusb/examples) | Scripts de ejemplo inofensivos para empezar |
| [Distribuciones de teclado](/es/badusb/layouts) | Qué distribuciones existen, cómo funcionan y cómo elegir una por script |
