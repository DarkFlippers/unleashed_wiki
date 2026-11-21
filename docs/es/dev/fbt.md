---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` es el único punto de entrada para compilar, flashear, depurar y revisar el estilo del firmware. Se ejecuta como
`./fbt` (o `fbt.cmd` en Windows) desde la raíz del repositorio. Internamente es un envoltorio sobre el sistema de
compilación [SCons](https://scons.org/).

Si solo quieres compilar y depurar **una app**, no necesitas el árbol completo del firmware: usa
[uFBT](https://pypi.org/project/ufbt/) (consulta [Tu primera app en C](/es/dev/first-app-c)).

## Entorno {#environment}

Lo único que debes tener instalado es `git`. En la primera ejecución, `fbt` descarga y descomprime un toolchain
precompilado y ajusta las variables de entorno **solo para sí mismo** — tu `PATH` global no se modifica.

Para usar el toolchain incluido fuera de `fbt` (por ejemplo, para llamar a `arm-none-eabi-gdb` a mano), abre un
*fbt shell*:

- Windows: ejecuta `scripts/toolchain/fbtenv.cmd`
- Linux / macOS: ejecuta `source scripts/toolchain/fbtenv.sh` en un shell nuevo
- o escribe `` . `./fbt -s env` `` en tu shell (conserva el `.` inicial)

Variables de entorno que modifican el comportamiento de `fbt`:

| Variable | Efecto |
|---|---|
| `FBT_NOENV=1` | Omite la descarga y configuración del toolchain; todas las herramientas deben estar ya en el `PATH` (no disponible en Windows) |
| `FBT_TOOLCHAIN_PATH=…` | Directorio donde descomprimir el toolchain (por defecto: `toolchain/` en la raíz del repositorio) |
| `FBT_VERBOSE=1` | Salida de depuración adicional de `fbt` y de los scripts del toolchain |
| `FBT_NO_SYNC=1` | No ejecutar `git submodule update --init` en cada arranque |

Definir una variable para una sola ejecución:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

Hay más variables documentadas en el código de los scripts `fbt` y `fbtenv`.

## Invocar fbt

Pasa las opciones de configuración y los targets que quieras:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Para limpiar (como `make clean`) los targets indicados, añade `-c`.

`fbt` controla las dependencias, así que solo tienes que nombrar el target de nivel más alto que necesites — todo
aquello de lo que depende se recompila automáticamente.

## Directorios de compilación

El firmware y el actualizador se compilan en subdirectorios distintos de `build/`, nombrados según los ajustes de
optimización (`COMPACT`, `DEBUG`). Para los IDE, la variante compilada más recientemente siempre se enlaza como
`build/latest`, junto con un `compile_commands.json` que se usa para el autocompletado de código.

::: info
`build/latest` y la base de datos de compilación solo se actualizan con los **targets de compilación del firmware**.
Flashear, o compilar paquetes de actualización para una configuración *distinta* de debug/release o para otro objetivo
de hardware, no mueve `build/latest`.
:::

## Integración con VS Code {#vs-code-integration}

```sh
./fbt vscode_dist
```

copia en `.vscode/` una configuración de entorno lista para usar. Abre la raíz del firmware con
**File → Open Folder**.

- Para usar un servidor de lenguaje distinto del `cpptools` por defecto, ejecuta
  `./fbt vscode_dist LANG_SERVER=<language-server>`. Se admiten `cpptools` (por defecto) y `clangd`.
- En el primer arranque se te ofrecerán las extensiones recomendadas (listadas en `.vscode/extensions.json`) —
  instálalas.
- Las tareas de compilación están en <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- La depuración necesita una sonda compatible: la Wi-Fi Devboard con su firmware de fábrica (Blackmagic), ST-Link y
  compatibles, o J-Link (solo en VS Code; las herramientas de J-Link no vienen incluidas —
  [descárgalas](https://www.segger.com/downloads/jlink/) y ponlas en el `PATH`).
- Sin sonda puedes instalar el firmware por USB igualmente.

## Targets de alto nivel {#high-level-targets}

Estos son los targets que usarás con más frecuencia.

| Target | Qué hace |
|---|---|
| `fw_dist` | Compila el firmware y lo publica en `dist/`. **Target por defecto** cuando no se indica ninguno |
| `fap_dist` | Compila las apps externas (FAP) y las publica en `dist/` |
| `updater_package` | Paquete completo de autoactualización: DFU del firmware + pila de radio + recursos de la tarjeta SD |
| `updater_minpackage` | Paquete de actualización mínimo: solo el DFU del firmware |
| `copro_dist` | Empaqueta los binarios del FUS y la pila de radio del Core2 para qFlipper |
| `flash` | Flashea por SWD con una sonda compatible (se detecta automáticamente; fuérzala con `SWD_TRANSPORT=...` y elige entre varias sondas con `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Compila, sube e instala el paquete de actualización por USB (paquete mínimo / completo) |
| `debug` | Compila y flashea el firmware, después conecta GDB con el `.elf` del firmware cargado |
| `debug_other`, `debug_other_blackmagic` | Conecta GDB sin cargar ningún `.elf`; añade archivos `.elf` externos con `add-symbol-file` |
| `updater_debug` | Conecta GDB con el `.elf` del actualizador cargado |
| `devboard_flash` | Actualiza la Wi-Fi Devboard; argumentos adicionales con `ARGS="..."`, por ejemplo `ARGS="-c dev"` |
| `blackmagic` | Depura el firmware con una sonda Blackmagic (Wi-Fi Devboard) |
| `openocd` | Solo arranca OpenOCD; argumentos adicionales con `ARGS="..."` |
| `get_blackmagic` | Imprime la dirección de Blackmagic en formato remoto de GDB (para la integración con el IDE) |
| `get_stlink` | Imprime los números de serie de las sondas ST-Link conectadas (para `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Comprueba / reformatea el código C con clang-format (`.clang-format`); argumentos adicionales con `ARGS="..."` |
| `lint_py`, `format_py` | Comprueba / reformatea el código Python, los archivos de compilación y los manifiestos con [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Comprueba / corrige los recursos de imagen (profundidad de color, eliminación de metadatos) |
| `lint_all`, `format_all` | Ejecuta todos los linters / formateadores |
| `firmware_pvs` | Informe de PVS-Studio (PVS-Studio debe estar en el `PATH`) |
| `doxygen` | Genera la documentación Doxygen; `doxy` además la abre en el navegador |
| `cli` | Abre una sesión de la [CLI](/es/dev/cli) del Flipper por USB |

## Targets del firmware

| Target | Qué hace |
|---|---|
| `faps` | Compila todas las apps externas y los plugins como `.fap` |
| `fap_<appid>` | Compila una app como `.fap` por su ID de app, por ejemplo `fap_snake_game` |
| `fap_<appid>_list` | Genera el listado de fuentes y ensamblador del `.fap` de esa app |
| `flash`, `firmware_flash` | Flashea la compilación actual por SWD |
| `jflash` | Flashea con JFlash usando una sonda J-Link (JFlash debe estar en el `PATH`) |
| `firmware_all`, `updater_all` | Compila un conjunto básico de binarios |
| `firmware_list`, `updater_list` | Genera listados de fuentes y ensamblador |
| `firmware_cdb`, `updater_cdb` | Genera `compilation_database.json` para los IDE — funciona sin una compilación completa |

Usa `--extra-ext-apps` (más abajo) para forzar que apps adicionales entren en la compilación externa.

## Targets de recursos

| Target | Qué hace |
|---|---|
| `resources` | Compila los recursos de la tarjeta SD y sus archivos de manifiesto |
| `dolphin_ext` | Procesa las animaciones del delfín para la tarjeta SD |
| `icons` | Genera los `.c` y `.h` de los iconos a partir de los recursos PNG |
| `proto` | Genera los `.pb.c` y `.pb.h` a partir de las fuentes `.proto` |
| `proto_ver` | Genera un `.h` con la versión de protobuf |
| `dolphin_internal`, `dolphin_blocking` | Generan los `.c` y `.h` de los recursos del delfín correspondientes |

## Parámetros de línea de comandos

| Parámetro | Significado |
|---|---|
| `--options optionfile.py` | Carga un archivo con valores de configuración (por defecto `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Fuerza que las apps indicadas se compilen **dentro** del firmware (target `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Fuerza que las apps indicadas se compilen como **externas** (target `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Defines globales adicionales de C/C++; se puede repetir |
| `--proxy-env=VAR1,VAR2` | Variables de entorno adicionales que se pasan a los subprocesos. Por defecto `fbt` sanea el entorno; la lista de las que siempre se reenvían está en `environ.scons` |

## Configuración

Los valores por defecto están en `fbt_options.py`. Los valores de la línea de comandos tienen prioridad. Para
**sobrescrituras personales permanentes**, crea un `fbt_options_local.py` junto a él — se evalúa al cargar las
opciones por defecto, así que nunca necesitas editar el archivo versionado. Ejecuta `./fbt -h` para listar todas las
opciones.

Valores por defecto destacados de Unleashed en `fbt_options.py`:

| Opción | Por defecto | Notas |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Se indica en la información del dispositivo |
| `TARGET_HW` | `7` | Flipper Zero (f7); consulta [objetivos de hardware](/es/dev/hardware-targets) |
| `COMPACT` | `1` | Optimizar para tamaño |
| `DEBUG` | `1` | Pasa `DEBUG=0` para compilaciones instalables |
| `DIST_SUFFIX` | `"local"` | Sufijo en los nombres de los archivos de salida |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` está soportado pero puede no caber en las compilaciones de depuración |
| `FIRMWARE_APP_SET` | `"default"` | Véase más abajo |

### Conjuntos de apps del firmware {#firmware-app-sets}

Qué apps entran en el firmware lo controla `FIRMWARE_APPS` — un mapa de *nombre de configuración → tupla de ID de
apps*. Elige uno con `FIRMWARE_APP_SET`. Unleashed define dos conjuntos:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Por ejemplo, para compilar una imagen con las pruebas unitarias:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Consulta [Pruebas unitarias](/es/dev/unit-tests) para saber por qué esa compilación necesita `DEBUG=0`.

## Páginas relacionadas

- [Compilar el firmware](/es/dev/build)
- [Manifiestos de app (.fam)](/es/dev/app-manifests)
- [Depurar apps](/es/dev/debugging)
- [Actualizaciones OTA](/es/dev/ota)
