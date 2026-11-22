---
title: Aplicación móvil de Flipper
order: 20
original: [https://docs.flipper.net/zero/mobile-app, https://docs.flipper.net/zero/mobile-app/bug-report, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# Aplicación móvil de Flipper

La **Flipper Mobile App** oficial ([App Store](https://apps.apple.com/us/app/flipper-mobile-app/id1534655259),
[Google Play](https://play.google.com/store/apps/details?id=com.flipperdevices.app)) se conecta al Flipper por
Bluetooth. Con ella puedes actualizar el firmware, consultar y compartir las llaves guardadas, instalar
aplicaciones del catálogo, controlar el Flipper a distancia y respaldar tus datos.

::: tip Unleashed
La aplicación móvil oficial funciona con Unleashed. Puede instalar un `.tgz` de Unleashed como actualización
**Custom** (más abajo). Si la aplicación deja de conectarse después de instalar Unleashed o de cambiar el nombre
del Flipper, vuelve a emparejarlo; consulta [Problemas de conexión](#connection-problems).
:::

## Conectar con el Flipper

1. En el Flipper: `Main Menu → Settings → Bluetooth`, pon **Bluetooth** en **ON**.
2. En la aplicación, toca **Connect** y después **Connect** junto al nombre de tu Flipper.
3. Introduce el **código de emparejamiento** que aparece en la pantalla del Flipper y toca **Pair**.
4. Espera a que la aplicación termine de sincronizar.

## Qué hay en la aplicación

- **Main Menu** (pestaña del dispositivo): actualizar por Bluetooth, **Device Info** (datos del hardware y del
  firmware), **Options** (copia de seguridad, registros, gestor de archivos, reinicio, informe de fallos; el
  conjunto depende de iOS/Android), sincronización manual y reproducir un sonido para encontrar el Flipper.
- **Archive**: todos los archivos guardados de Sub-GHz, RFID 125, NFC, infrarrojos e iButton. Favoritos, búsqueda y
  restauración de elementos borrados. Toca una llave para ver **Key Info**: emular o enviar, añadir a favoritos,
  renombrar, añadir una nota, ver detalles, borrar y compartir.
- **Apps**: el catálogo oficial de aplicaciones, instaladas por Bluetooth LE; véase
  [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps).
- **Tools**: **Mfkey32** (Extract MF Keys) para calcular claves de MIFARE Classic a partir de los nonces
  recopilados, y la **Remotes Library** de mandos de infrarrojos (véase
  [Infrarrojos desde el móvil](/es/infrared/mobile)).
- **Widget**: emula mandos y tarjetas guardados desde la pantalla de inicio del móvil sin abrir la aplicación (en
  iOS, Today View → Edit → Add Widget → Flipper; en Android, añádelo como cualquier widget y tócalo para
  configurarlo).

## Instalar Unleashed desde el móvil

::: tip Antes de empezar
Asegúrate de que la tarjeta SD está puesta. Puedes instalar Unleashed directamente sobre el firmware de serie o sobre
una versión anterior de Unleashed.
:::

### iOS

1. Abre la [última release de Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) y
   descarga `flipper-z-f7-update-(version).tgz`.
2. En la aplicación **Archivos**, selecciona el `.tgz` descargado, toca **Compartir** y elige la aplicación
   **Flipper**.
3. En la aplicación de Flipper, comprueba que el Update Channel muestra `Custom flipper-z-f7-update...` y toca el
   botón verde **Update**.
4. Espera a que termine la actualización. La aplicación de iOS puede mostrar un error al final, pero el Flipper
   queda actualizado.

### Android, con el archivo `.tgz`

1. Descarga `flipper-z-f7-update-(version).tgz` de la página de la release.
2. En la aplicación de Flipper, toca **Update channel** → **Custom** y elige el archivo descargado.
3. Toca **Update** y espera.

### Android, con el enlace del web updater

1. En la página de la release, toca **Install via Web Updater**.
2. Cuando Android pregunte con qué abrirlo, elige la aplicación **Flipper**.
3. Continúa con la instalación y espera.

Una actualización por Bluetooth puede tardar unos 10 minutos. Otras vías:
[Instalar Unleashed](/es/start/install).

### Si la actualización falla

- Comprueba que el Flipper está encendido y sigue conectado por Bluetooth.
- Reinicia el Flipper (<kbd>←</kbd> + <kbd>Back</kbd>) y vuelve a lanzar la actualización.
- Si sigue fallando, puede que el almacenamiento interno esté lleno o dañado: instala con
  [qFlipper](/es/mobile/qflipper) o con el
  [Web Installer](/es/mobile/web-tools#unleashed-web-installer) y consulta
  [Recuperación](/es/start/recovery).

## Respaldar tus llaves

1. En la pestaña del dispositivo, toca **Options → Backup Keys**.
2. Elige dónde guardar o con quién compartir el `.zip` con tus llaves, tarjetas y mandos.

Para restaurarlo, descomprime el archivo y sube los ficheros con [qFlipper](/es/mobile/qflipper). Para una copia
completa de la tarjeta SD, descarga toda la tarjeta desde el **File manager** de qFlipper.

## Problemas de conexión {#connection-problems}

**Después de instalar Unleashed o de renombrar el Flipper, la aplicación no se conecta:**

1. En la aplicación, toca **Forget flipper**.
2. En los ajustes de Bluetooth del móvil, busca el Flipper, abre sus opciones y elige **Olvidar dispositivo**.
3. En el Flipper: `Settings → Bluetooth → Unpair All Devices` y confirma con **Unpair**.
4. Asegúrate de que el Bluetooth del Flipper está en ON y vuelve a emparejarlo desde la aplicación.

**No se encuentra el Flipper:** comprueba que el Bluetooth está activado en los dos, desconecta el Flipper de otros
dispositivos (por ejemplo, de un anfitrión de [mando Bluetooth](/es/apps/controllers)), actualiza la aplicación y
el firmware y reinicia el Flipper.

**La sincronización falla:** desemparéjalo y vuelve a emparejarlo, reinicia los dos dispositivos y prueba
`Settings → System → Sleep Method → Legacy` en el Flipper.

## Informar de fallos de la aplicación

Para fallos de la aplicación oficial: **Options → Report Bug**, rellena un título y los pasos para reproducirlo,
deja los registros adjuntos, toca **Submit** y, si quieres, publica el ID de la issue en
[forum.flipperzero.one](https://forum.flipperzero.one/) (sección Mobile App). Para capturar los registros del
Flipper para un informe: pon `Settings → System → Log Level` en **Debug**, conéctalo por USB, abre un terminal
serie a **230400** baudios (o [lab.flipper.net/cli](https://lab.flipper.net/cli)), ejecuta `info device` y luego
`log`, reproduce el fallo y elimina las líneas `hardware.uid` y `hardware.name` antes de publicarlo.

## Páginas relacionadas

- [qFlipper](/es/mobile/qflipper)
- [Aplicación complementaria qUnleashed](/es/mobile/qunleashed-app)
- [Instalar Unleashed](/es/start/install)
