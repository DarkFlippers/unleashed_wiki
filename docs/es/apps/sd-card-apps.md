---
title: Aplicaciones en la tarjeta SD (.fap)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md, https://docs.flipper.net/zero/apps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Aplicaciones en la tarjeta SD (.fap)

Casi todas las apps que lanzas desde `Main Menu → Apps` son un **FAP** (Flipper App Package): un ejecutable `.elf` con
metadatos adicionales (nombre, icono, categoría, versión de API requerida) y, opcionalmente, recursos empaquetados.
Los FAP residen en la tarjeta microSD, así que **las apps necesitan una tarjeta SD** para funcionar.

## Dónde residen las apps

| Ruta | Qué hay ahí |
|---|---|
| `/ext/apps/<Category>/*.fap` | apps instaladas, una carpeta por categoría (`Sub-GHz`, `NFC`, `RFID`, `GPIO`, `USB`, `Bluetooth`, `Games`, `Tools`, ...) |
| `/ext/apps_data/<appid>/` | datos y ajustes que cada app guarda para sí misma |
| `/ext/apps_data/loader/plugins/` | plugins del cargador, por ejemplo los [estilos del menú principal](/es/apps/menu-styles) |

`Main Menu → Apps` simplemente muestra las carpetas que hay bajo `/ext/apps`. La pestaña **Apps** del
[Archive](/es/apps/archive) lista la misma carpeta y muestra además los scripts `.js`.

## Cómo ejecuta el Flipper un FAP

El MCU no puede ejecutar código directamente desde el almacenamiento externo. Cuando inicias una app, el **App
Loader**:

1. lee el FAP de la tarjeta SD y comprueba su integridad y su manifiesto;
2. verifica que la **versión mayor de la API** de la app coincide con la versión mayor de la API del firmware;
3. copia las secciones de código y de datos a la RAM y corrige las direcciones para la nueva ubicación
   (relocalización);
4. resuelve todas las funciones que la app importa a través de la **tabla de símbolos** del firmware;
5. inicia la app.

Como la app se ejecuta desde la RAM, una app grande deja menos heap para todo lo demás. Solo se cargan el código y los
datos, así que la RAM utilizada es menor que el tamaño del archivo `.fap`.

::: tip Unleashed
Unleashed mantiene la API oficial (la versión de API actual se imprime al principio de cada changelog, por ejemplo
`Current API: 88.27`), así que la mayoría de las apps del catálogo oficial funcionan tal cual. Si la versión mayor de
la API difiere, Unleashed no se niega directamente: muestra **App Too Old** o **App Too New** con las dos versiones
(por ejemplo `APP:86 < FW:88`) y un botón **Continue**, de modo que puedes intentar ejecutarla igualmente. Consulta
[Resolución de problemas de apps](/es/apps/troubleshoot).
:::

## Instalar aplicaciones

### Desde los packs de apps

Lo más sencillo es elegir una compilación de firmware que ya incluya un pack (la compilación por defecto o la `e`);
consulta [Aplicaciones incluidas en Unleashed](/es/apps/catalog).

Los dos packs salen de [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Para añadir uno a mano:

1. Descarga el `.zip` de la [página de releases](https://github.com/xMasterX/all-the-plugins/releases/latest).
2. Descomprímelo.
3. Copia las carpetas de las apps en la carpeta `apps` de la tarjeta SD (`/ext/apps/`), conservando sus carpetas de
   categoría.
4. Comprueba que la versión de API del pack coincide con la de tu firmware (`Current API:` al principio del changelog).

### Desde el catálogo oficial {#installing-from-the-official-catalog}

El catálogo oficial de aplicaciones está en [Flipper Lab](https://lab.flipper.net/apps) (Chrome, Edge y otros
navegadores basados en Chromium con Web Serial) y en la pestaña **Apps** de la
[app móvil de Flipper](/es/mobile/mobile-app).

1. Cierra qFlipper y cualquier otra pestaña de Flipper Lab (solo un programa puede ocupar el puerto serie USB).
2. Conecta el Flipper por USB (Flipper Lab) o Bluetooth (app móvil).
3. Abre **Apps** y busca la app por categoría o con el buscador.
4. Pulsa **Install** en la tarjeta de la app o en su página y espera a que se suba.
5. En el Flipper abre `Main Menu → Apps → <category> → <app>`.

Para actualizar o borrar apps del catálogo, abre **Apps → Installed** y pulsa **Update** o el icono de borrar
(papelera).

Si la instalación falla: comprueba la conexión, libera espacio en la tarjeta SD (borra archivos desde el
[Archive](/es/apps/archive)) y asegúrate de que el firmware está actualizado.

### A mano (cualquier `.fap`)

1. Descarga el `.fap` compilado para tu firmware (una compilación de Unleashed, o una del OFW con una versión de API
   compatible).
2. Cópialo a `/ext/apps/<Category>/` con [qFlipper](/es/mobile/qflipper), el gestor de archivos de la app móvil o un
   lector de tarjetas.
3. Inícialo desde `Main Menu → Apps`, o abre el archivo en el [Archive](/es/apps/archive) y elige **Run**.

::: warning
Las apps compiladas para otro fork del firmware pueden importar funciones que Unleashed no exporta, y entonces fallan
con **Missing Imports**. Toma las apps de los packs de Unleashed o recompílalas contra el SDK de Unleashed.
:::

## Compilar tu propio FAP

Los FAP se desarrollan exactamente igual que las apps integradas. En resumen:

1. Coloca la carpeta de tu app en `applications_user/` de una copia local del firmware.
2. En su `application.fam` pon `apptype=FlipperAppType.EXTERNAL` (consulta
   [Manifiestos de app](/es/dev/app-manifests)).
3. Compila con uno de estos comandos:

```bash
./fbt fap_{APPID}                                     # build one app
./fbt launch APPSRC=applications_user/path/to/app     # build, upload over USB and run
./fbt build APPSRC=applications_user/path/to/app      # build without uploading
./fbt faps                                            # build all FAPs (or ./fbt fap_dist)
```

En el perfil por defecto de VS Code, `launch` es la acción **Launch App on Flipper**
(<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>).

**Recursos.** Pon las imágenes en una subcarpeta de la app e indícala en `fap_icon_assets`; después haz
`#include "{APPID}_icons.h"` y úsalas igual que los iconos de `assets_icons.h`.

**Versionado de la API.** No todas las funciones del firmware están disponibles para las apps: el conjunto exportado
se lista en el `api_symbols.csv` del objetivo de hardware. La versión mayor aumenta con los cambios incompatibles (una
función o variable eliminada, una firma modificada) y la menor con las adiciones. `fbt` gestiona esto
automáticamente: los símbolos nuevos aparecen con `?`, y debes marcar cada uno como `+` (exportado) o `-` (oculto)
antes de que el firmware compile.

**Depuración.** `fbt` carga `debug/flipperapps.py` en gdb, así que puedes depurar un FAP igual que el código del
firmware. Compila y flashea el firmware (`./fbt`, `./fbt flash`), ejecuta tu FAP y después conéctate con
`./fbt debug`. El firmware se detiene en un breakpoint justo después de cargar el FAP, de modo que puedes poner
breakpoints en él. El tipo de compilación del firmware y de la app (debug/release) debe coincidir, y la compilación
correspondiente debe estar enlazada como `build/latest`.

Más información en [Compilar el firmware](/es/dev/build), [fbt](/es/dev/fbt) y
[Tu primera app en C](/es/dev/first-app-c).

## Páginas relacionadas

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
- [Resolución de problemas de apps](/es/apps/troubleshoot)
- [Archive (explorador de archivos)](/es/apps/archive)
