---
title: Tu primera app en C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Tu primera app en C

En este tutorial montarás un entorno de desarrollo con **uFBT**, generarás una plantilla de app, añadirás una GUI
sencilla y compilarás y ejecutarás la app en tu Flipper Zero.

Las apps creadas así son archivos `.fap` (Flipper App Package) — residen en la tarjeta microSD y se cargan cuando se
necesitan, así que no hace falta recompilar el firmware.

## 1. Preparar el entorno

Necesitas un Flipper Zero, un cable USB y, en Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) («micro Flipper Build Tool») — una versión de
  [fbt](/es/dev/fbt) con todo lo necesario para desarrollar apps. Instálalo con `pip install ufbt` (consulta el README
  de uFBT para más detalles).
- [**Visual Studio Code**](https://code.visualstudio.com/) — el IDE recomendado. Otros también funcionan, pero
  requieren configuración manual para integrarse con uFBT.

::: tip Unleashed
uFBT descarga por defecto el SDK **oficial**. Para compilar para Unleashed, ejecuta una vez (y usa los mismos flags en
todas las actualizaciones posteriores):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Usa `--channel=release` si tu Flipper lleva una compilación de release. La versión del SDK debe coincidir con el
firmware del dispositivo — consulta el [paso 5](#_5-build-and-run-the-app).
:::

## 2. Generar una plantilla de app

1. Crea una carpeta para la app, por ejemplo `test_app`.
2. Abre un terminal en esa carpeta y ejecuta:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT genera la estructura de archivos.
3. Ejecuta:

   ```sh
   ufbt vscode_dist
   ```

   Esto configura VS Code para compilar y depurar la app directamente desde el IDE.

::: warning
`APPID` solo puede contener letras minúsculas `a-z`, dígitos `0-9` y `_`.
:::

La estructura resultante:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| Archivo | Finalidad |
|---|---|
| `application.fam` | El manifiesto de la app que uFBT lee para saber cómo compilarla — consulta [Manifiestos de app](/es/dev/app-manifests) |
| `test_app.c` | Archivo fuente principal con el punto de entrada |
| `test_app.png` | Icono de la app (10×10, 1 bit) |
| `.github/workflows/build.yml` | Configuración de GitHub Actions — [más información](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Tus recursos de imagen |
| `images/.gitkeep` | Marcador para que Git controle la carpeta `images/` vacía |

## 3. El código de la plantilla

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Qué hace cada parte:

- `#include <furi.h>` — la cabecera principal de **Furi**, el núcleo del firmware del Flipper
  ([API Furi](/es/dev/furi-api)).
- `#include <test_app_icons.h>` — necesaria si la app usa imágenes. uFBT convierte los PNG de `images/` al formato
  interno del Flipper y genera esta cabecera automáticamente.
- `int32_t` — el tipo de retorno habitual de la función principal de una app.
- `UNUSED(p);` — una macro que silencia el aviso de «parámetro no utilizado».
- `FURI_LOG_I` — escribe un mensaje de nivel `info` en el log del Flipper. Puedes verlo con `ufbt cli` → `log info`.
- `return 0;` — éxito, por convención de C.

## 4. Añadir una GUI

Abre la carpeta de la app en VS Code (**File → Open Folder…**). Instala las extensiones sugeridas cuando se te
pregunte.

Vamos a mostrar dos líneas en la pantalla: `Hello world` e `I'm test_app!`. Sustituye el contenido de `test_app.c`
por:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Esto usa el servicio de GUI **Dialogs**, la API gráfica más sencilla. Otros enfoques se describen en
[GUI en las apps](/es/dev/gui).

## 5. Compilar y ejecutar la app {#_5-build-and-run-the-app}

**La forma rápida:**

1. Conecta el Flipper al ordenador con el cable USB.
2. Cierra qFlipper y cualquier otro programa que use el puerto serie del Flipper.
3. Ejecuta:

   ```sh
   ufbt launch
   ```

   Compila la app, la sube y la inicia en el Flipper.

**La forma manual:**

1. Compila con <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) o
   <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (macOS), o ejecuta `ufbt` en el terminal. El `.fap` autocontenido (con
   todos sus recursos) aparece en `dist/`.
2. En qFlipper abre **File Manager → SD Card → apps → Examples** (crea la carpeta si no existe) y arrastra ahí el
   `.fap`.
3. En el Flipper: `Main Menu → Apps → Examples → tu app`.

**Resultado esperado:** una pantalla con «Hello world» como encabezado e «I'm test_app!» debajo. Pulsa cualquier botón
para cerrarla.

::: warning La versión del SDK debe coincidir
La versión del SDK (API) del firmware del dispositivo debe coincidir con el SDK con el que uFBT ha compilado. Si al
iniciar la app obtienes un error de incompatibilidad de API, actualiza el SDK de uFBT para que coincida con tu
firmware, o flashea el firmware correspondiente con `ufbt flash_usb`. En Unleashed, asegúrate de que uFBT usa el
índice de Unleashed (consulta el aviso del paso 1) — de lo contrario `ufbt flash_usb` instalaría el firmware
**oficial**.
:::

Para ver la salida de `FURI_LOG_I`: ejecuta `ufbt cli` y después `log` (o `log info` si has cambiado el nivel de log
por defecto).

## Resolución de problemas

| Problema | Solución |
|---|---|
| `ufbt create` rechaza el APPID | Usa solo `a-z`, `0-9`, `_` |
| Incompatibilidad de API / SDK al lanzarla | Actualiza el SDK de uFBT para tu firmware (¡con el índice de Unleashed!) y recompila |
| `ufbt launch` no encuentra el dispositivo | Cierra qFlipper / Lab / cualquier terminal serie; vuelve a conectar el cable |
| La app no está en el menú | Debe estar en una carpeta de categoría bajo `/ext/apps/`, por ejemplo `/ext/apps/Examples/` |
| No aparece nada en `log` | Arranca `log` **antes** de lanzar la app; comprueba el nivel de log |

## ¿Y ahora qué?

- Si tienes el C algo oxidado, *El lenguaje de programación C* de B. Kernighan y D. Ritchie es la referencia clásica.
- [Depurar apps](/es/dev/debugging) — recorre tu app paso a paso con un depurador.
- [GUI en las apps](/es/dev/gui) — ViewPort, Views y Scenes.
- [Manifiestos de app](/es/dev/app-manifests) — todas las opciones de `application.fam`.
- ¿Sin PC? [Compila apps en Android](/es/dev/android-build).
- ¿Prefieres scripting? [JavaScript en el Flipper](/es/dev/js-about).
