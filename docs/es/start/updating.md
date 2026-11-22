---
title: Actualizar
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Actualizar

Unleashed se actualiza a menudo. Actualizar funciona exactamente igual que instalar: pon la versión nueva **encima**
de la actual. No hace falta volver al firmware oficial ni instalar nada por el medio.

## Cómo actualizar

**Recomendado: [qUnleashed](/es/mobile/qunleashed-app)**, la aplicación complementaria de Unleashed para
**Android, iOS, Windows, macOS y Linux** (USB en todos ellos excepto en iOS, que usa Bluetooth). Descarga ella misma
el firmware nuevo.

1. Instala o actualiza qUnleashed desde su
   [página de releases](https://github.com/DarkFlippers/qUnleashed/releases).
2. Conecta el Flipper por USB o por Bluetooth.
3. Abre el **actualizador de firmware**, elige el canal **Unleashed** (**Release** o **Dev**) y la variante que
   usas: **base**, **extra apps** o **compact**.
4. Inicia la instalación y espera hasta que el Flipper haya terminado todas las fases.

Si el Flipper ha dejado de arrancar, **Repair from DFU mode** en la misma aplicación lo vuelve a flashear por USB
([Recuperación](/es/start/recovery#firmware-recovery)).

Alternativas, todas descritas en los [métodos de instalación](/es/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → elige Release o Dev → Install.
2. **qFlipper**: **Install from file** con el nuevo `flipper-z-f7-update-(version).tgz`.
3. **Aplicación móvil**: canal de actualización personalizado con el `.tgz`.
4. **Sin conexión**: copia `f7-update-(version)` en `/ext/update/` y abre `update.fuf` desde el Archive.

::: warning No pulses «Update» en qFlipper ni en la aplicación oficial
El botón **Update** integrado de qFlipper y de la Flipper Mobile App usa el servidor de actualización **oficial**.
Sustituye Unleashed por el firmware de serie. Para Unleashed, usa el actualizador de qUnleashed, **Install from
file**, el canal personalizado o el Web Installer.
:::

## ¿Release o dev?

| | Release | Dev |
|---|---|---|
| Estabilidad | Probada | Puede tener fallos |
| Funciones nuevas | Con cada release | En cuanto se integran |
| Dónde conseguirlo | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Los builds dev se compilan automáticamente a partir de los últimos commits. El build dev anterior se borra del sitio
cuando se sube uno nuevo. Informa de los fallos en las
[issues de GitHub](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Qué sobrevive a una actualización

- **Tus archivos de la tarjeta microSD**: las llaves, tarjetas, mandos y scripts guardados permanecen intactos.
- **Tu nombre personalizado**: se guarda en la tarjeta, en `/ext/dolphin/name.settings`
  ([Nombre personalizado del Flipper](/es/start/custom-name)).
- **Los ajustes**: normalmente se conservan. **Excepción:** cuando una release cambia la estructura de un archivo de
  ajustes, ese archivo se restablece a los valores por defecto una vez. Esto solo pasa en releases concretas. Si
  después de una actualización se restablecen tus ajustes de escritorio (PIN, favoritos…), vuelve a configurarlos y
  consulta el changelog.
- **Las aplicaciones integradas** de `/ext/apps/` se sustituyen únicamente por las versiones del firmware nuevo. Los
  paquetes de aplicaciones adicionales nunca pueden sobrescribirlas ni dejarlas en una versión anterior.

## Comprobar tu versión

- **Main Menu → Settings → About**: versión del firmware, fecha de compilación, rama y commit;
- o mantén <kbd>↓</kbd> en el escritorio para abrir la pantalla de depuración e información.

## Dónde leer qué ha cambiado

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases): el changelog de cada release;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) en la rama dev: lo que
  viene en la próxima release;
- actualizaciones de aplicaciones:
  [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## El servidor de actualizaciones de Unleashed

Unleashed tiene su propio servidor de actualizaciones con el mismo formato que el oficial:
`https://up.unleashedflip.com/directory.json`. Las aplicaciones oficiales no pueden apuntarse a él sin
recompilarlas. **uFBT** acepta esta URL como argumento para compilar aplicaciones contra el SDK de Unleashed (véase
[Compilar el firmware](/es/dev/build)).

## Si una actualización falla

1. Reinicia con <kbd>←</kbd> + <kbd>BACK</kbd> e inténtalo de nuevo.
2. Prueba otro método (qUnleashed ↔ Web Installer ↔ qFlipper ↔ sin conexión).
3. Comprueba la tarjeta SD (**Settings → Storage → About SD Card**), o formatéala después de hacer una copia de
   seguridad.
4. Si sigue fallando: [Recuperación](/es/start/recovery).
