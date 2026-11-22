---
title: Instalar Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Instalar Unleashed

Hay varias formas de instalar el firmware Unleashed. Todas instalan el mismo paquete de actualización, que contiene
el firmware, el actualizador y todos los recursos (aplicaciones, bibliotecas de IR, ajustes de Sub-GHz, etc.).

::: tip Antes de empezar
- **Sin actualizaciones intermedias:** instala Unleashed directamente sobre el firmware de serie o sobre una versión anterior de Unleashed.
- Asegúrate de que hay una **tarjeta microSD insertada**. La actualización se descomprime en la tarjeta, y las
  aplicaciones viven allí.
- Carga la batería. Una actualización completa tarda varios minutos.
:::

## Qué archivo descargar {#which-file-to-download}

Los archivos de las releases se llaman `flipper-z-f7-update-(version)(e / c).tgz`:

| Parte | Significado |
|---|---|
| `flipper-z` | Para el dispositivo Flipper Zero |
| `f7` | Objetivo de hardware. Es el mismo para todos los Flipper Zero |
| `update` | Paquete de autoactualización: actualizador, firmware y todos los recursos |
| `(version)` | Versión del firmware |
| sufijo | Variante del paquete de aplicaciones, véase más abajo |

| Sufijo | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(ninguno)* | ✅ | — |
| `c` | — | — |

- **`e`**: todo. El paquete base más el paquete extra de aplicaciones de la comunidad. Elige este si no lo tienes
  claro.
- **Sin sufijo**: solo el paquete base de aplicaciones de la comunidad.
- **`c`** («clean»): sin aplicaciones de la comunidad.

Las **aplicaciones de sistema integradas** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote
Analyzer, Sub-GHz RAW Edit, SIM800, FindMy Flipper, mandos USB/BT, Snake…) vienen **con el propio firmware** y están
en **todas** las variantes, incluida la `c`. Véase
[Qué añade Unleashed](/es/start/unleashed-features#built-in-apps).

Otros archivos de las releases:
- `flipper-z-any-scripts-(version).tgz`: la carpeta `scripts` para el desarrollo del firmware y de aplicaciones;
- `flipper-z-f7-sdk-(version).zip`: SDK para el desarrollo de aplicaciones y para uFBT.

## Método 1: qUnleashed (recomendado)

[qUnleashed](/es/mobile/qunleashed-app) es la aplicación complementaria del propio equipo de Unleashed. Descarga e
instala el firmware ella misma, así que no hay ningún archivo que elegir. Funciona en **Android, iOS, Windows, macOS
y Linux**: por USB en todos ellos excepto en iOS, que se conecta por Bluetooth.

1. Instala qUnleashed para tu sistema desde su
   [página de releases](https://github.com/DarkFlippers/qUnleashed/releases).
2. Conecta el Flipper por USB, o empareja por Bluetooth (en iOS, Bluetooth es la única vía).
3. Abre el **actualizador de firmware** de la aplicación.
4. Elige el canal **Unleashed**, **Release** o **Dev**.
5. Elige la variante: **base**, **extra apps** o **compact** ([qué contiene cada una](#which-file-to-download)).
6. Inicia la instalación y espera. El Flipper se reinicia en el actualizador y recorre todas las fases.

Si el Flipper ya no arranca, usa **Repair from DFU mode** en la misma aplicación para volver a flashearlo por USB.
Véase [Recuperación](/es/start/recovery#firmware-recovery).

Los métodos de abajo son alternativas. Usa uno si qUnleashed no encaja con tu equipo.

## Método 2: Unleashed Web Installer

Necesitas un **navegador basado en Chromium** (Chrome, Edge, Opera, Brave, Vivaldi) y un cable USB.

1. Cierra **qFlipper** y cualquier otra página web de Flipper. Tienen tomado el puerto serie.
2. Conecta el Flipper por USB.
3. Abre **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Pulsa **Connect** y elige tu Flipper en la ventana emergente del navegador.
5. Selecciona la rama **Release** o **Dev**.
6. Pulsa **Install** y espera. El Flipper se reinicia en el actualizador y recorre todas las fases.
7. Listo. Todos los recursos quedan instalados.

## Método 3: el web updater de Flipper Lab

1. Abre la [página de la última release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Conecta el Flipper y pulsa el enlace **Install via Web Updater**.
3. En la página del web updater, pulsa **Connect** y después **Install**.
4. Espera a que termine la actualización.

![Web updater](/img/remote/b803c9d8ec0350d6.png)

## Método 4: qFlipper (1.2.0 o posterior)

1. Instala [qFlipper](https://flipperzero.one/update) 1.2.0 o posterior (las versiones anteriores no pueden
   instalar archivos `.tgz`).
2. Descarga `flipper-z-f7-update-(version).tgz` de las
   [releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Arranca qFlipper y conecta el Flipper.
4. Pulsa **Install from file** y selecciona el `.tgz` descargado.
5. La actualización arranca. Espera a que termine.

![Install from file en qFlipper](/img/remote/f1a3ede83085d040.png)

::: warning
**No** uses el botón **Update** de qFlipper después de instalar Unleashed. Instala el firmware **oficial** encima de
Unleashed. Usa **Install from file** en su lugar.
:::

## Método 5: la aplicación móvil de Flipper

### Android, con un archivo `.tgz`
1. Descarga `flipper-z-f7-update-(version).tgz` al móvil.
2. En la aplicación de Flipper, toca **Update channel** y selecciona **Custom**.
3. Selecciona el `.tgz` descargado y toca **Update**.
4. Espera a que termine la actualización.

### Android, con el enlace del web updater
1. En la página de la release, toca **Install via Web Updater**.
2. Cuando te pregunte si abrirlo con un navegador o con la aplicación de Flipper, elige la **Flipper App**.
3. Continúa con la instalación y espera.

### iOS
1. Descarga `flipper-z-f7-update-(version).tgz`.
2. Ábrelo en la aplicación **Archivos**. Toca **Compartir** y elige la **Flipper App**.
3. En la aplicación de Flipper, toca el botón verde **Update**. Comprueba que el canal de actualización muestra
   `Custom flipper-z-f7-update...`.
4. Espera. **La aplicación de iOS puede mostrar un error al final, pero el Flipper se actualiza correctamente.**

## Método 6: actualización sin conexión desde la tarjeta microSD

No hace falta ningún programa de ordenador. Funciona desde un PC o desde un móvil.

1. Descomprime `flipper-z-f7-update-(version).tgz` (o `.zip`). Dentro hay una carpeta `f7-update-(version)` que
   contiene `update.fuf`, `resources.tar` y otros archivos.
2. Pon la tarjeta en un PC o en un móvil, o sube los archivos con qFlipper.
3. Crea una carpeta `update` en la **raíz** de la tarjeta y mueve `f7-update-(version)` dentro:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Comprueba que están **todos** los archivos. La aplicación Archivos de iOS puede mostrar solo 3 de los 6 archivos.
   Usa otra aplicación de descompresión, un PC o Android.
5. Vuelve a insertar la tarjeta en el Flipper.
6. Abre **Archive** (<kbd>↓</kbd> en el escritorio), ve a la pestaña **Browser**, navega a
   `update/f7-update-(version)/` y abre `update.fuf`.
7. La actualización arranca. Espera a que terminen todas las fases.

![Actualización sin conexión](/img/remote/92717373349f3b7c.png)

## Después de instalar

- La pantalla About (**Settings → About**) muestra la información del firmware Unleashed y su versión.
- En el primer arranque después de una actualización, el Flipper descomprime los recursos en la tarjeta. Es normal.
- Lee [Qué añade Unleashed](/es/start/unleashed-features) y configura el dispositivo en
  [Ajustes](/es/start/settings).

## Resolución de problemas

| Problema | Solución |
|---|---|
| El navegador no puede conectarse | Cierra qFlipper y las demás pestañas de Flipper Lab. Usa un navegador basado en Chromium. Prueba otro cable u otro puerto |
| La actualización falla o se queda colgada | Reinicia con <kbd>←</kbd> + <kbd>BACK</kbd>, comprueba la tarjeta SD, prueba otro método |
| La aplicación móvil no se conecta después de instalar | Olvida el Flipper en la aplicación y en los ajustes de Bluetooth del móvil. Después, **Settings → Bluetooth → Unpair All Devices** en el Flipper y vuelve a emparejarlo |
| La retroiluminación está apagada después de instalar | Véase las [preguntas frecuentes](/es/start/faq#backlight-does-not-work) (ajuste del mod RGB) |
| El dispositivo está muerto o «briqueado» | [Recuperación](/es/start/recovery) |
