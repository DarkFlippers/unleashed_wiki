---
title: Manifiestos de app (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# Manifiestos de app (.fam)

Cada componente del firmware — servicios, apps de usuario, páginas de ajustes — se desarrolla de forma independiente y
se describe en un archivo de manifiesto llamado `application.fam`. Ahí se declaran las propiedades básicas del
componente y su relación con el resto del sistema.

Al compilar, `fbt` recopila todos los manifiestos, resuelve sus dependencias y compila **solo** los componentes a los
que hace referencia la configuración de compilación actual (consulta
[fbt → conjuntos de apps del firmware](/es/dev/fbt#firmware-app-sets)).

## Definición de una app

Un manifiesto es un fragmento de Python que llama a `App()` con argumentos con nombre. Solo **`appid`** y
**`apptype`** son obligatorios; el resto son opcionales y algunos solo tienen sentido para ciertos tipos de app.

### Tipos de app (`apptype`)

`apptype` es un miembro de `FlipperAppType`:

| Valor | Tipo de componente |
|---|---|
| `SERVICE` | Servicio del sistema, creado en el arranque temprano |
| `SYSTEM` | No aparece en los menús; lo inician otras apps o la CLI |
| `APP` | App normal del menú principal |
| `PLUGIN` | Se compila como parte del firmware y se coloca en el menú Plugins |
| `DEBUG` | Visible solo en el menú Debug, con el modo de depuración activado |
| `ARCHIVE` | La única app Archive |
| `SETTINGS` | Se coloca en el menú Settings del sistema |
| `STARTUP` | Callback que se ejecuta al arrancar el sistema; no define una app aparte |
| `EXTERNAL` | Se compila como una app `.fap` |
| `METAPACKAGE` | Sin código; sirve para declarar dependencias y conjuntos de apps |

### Parámetros comunes

| Parámetro | Significado |
|---|---|
| `appid` | ID de la app en forma de cadena dentro del sistema de compilación. Se usa en las configuraciones de compilación y para resolver dependencias y conflictos |
| `apptype` | Véase la tabla anterior |
| `name` | Nombre que se muestra en los menús |
| `entry_point` | Función de C que se usa como punto de entrada. Los nombres de C++ se decoran — envuelve la función en `extern "C"` |
| `flags` | Flags internos para las apps de sistema. **No los uses** |
| `cdefines` | Definiciones del preprocesador de C declaradas globalmente para otras apps cuando esta app está en la compilación. En las apps externas se usan al compilar la propia app |
| `requires` | ID de apps que se añaden a la compilación siempre que se compile esta app |
| `conflicts` | ID de apps con las que esta app entra en conflicto; si alguna está presente, `fbt` aborta la compilación |
| `provides` | Funcionalmente idéntico a `requires` |
| `stack_size` | Tamaño de la pila en bytes que se reserva al arrancar la app. Demasiado pequeño → fallo por desbordamiento de pila; demasiado grande → menos heap para la app |
| `icon` | Icono animado de los recursos integrados, usado cuando la app se compila dentro del firmware |
| `order` | Orden dentro de su grupo (menor = antes). Se usa en los ganchos de arranque y en las entradas de menú |
| `sdk_headers` | Cabeceras de C de esta app que se incluyen en la API para las apps externas |
| `targets` | [Objetivos de hardware](/es/dev/hardware-targets) compatibles. Por defecto `["all"]` |
| `resources` | Carpeta dentro de las fuentes de la app que se empaqueta como recursos de la tarjeta SD (solo si la app está en la compilación). Por defecto `""` — ninguna |

::: tip
Usa los [comandos de la CLI](/es/dev/cli) `top` y `free` para perfilar el uso de memoria de tu app al elegir el
`stack_size`.
:::

### Parámetros para apps externas (FAP)

| Parámetro | Significado |
|---|---|
| `sources` | Máscaras de archivo para recopilar las fuentes en la carpeta de la app. Por defecto `["*.c*"]` (C y C++). La carpeta `lib` está reservada para `fap_private_libs`. Las máscaras que empiezan por `!` excluyen archivos; las máscaras sin comodines (`*`, `?`) son rutas literales. Ejemplo: `["*.c*", "!plugins"]` |
| `fap_version` | Cadena con la versión de la app, por defecto `"0.1"`. También se admite una tupla `(x, y)`. Se permiten más partes separadas por puntos, pero en el `.fap` solo se guardan la mayor y la menor |
| `fap_icon` | Archivo `.png`, color de 1 bit, 10×10 px, incrustado en el `.fap` |
| `fap_libs` | Bibliotecas adicionales con las que enlazar — da acceso a funciones que el firmware no exporta, a cambio de un `.fap` más grande y más RAM |
| `fap_category` | Subcategoría de la app; también determina la carpeta bajo `apps/` en la tarjeta SD |
| `fap_description` | Descripción breve (puede estar vacía) |
| `fap_author` | Autor (puede estar vacío) |
| `fap_weburl` | Página web (puede estar vacía) |
| `fap_icon_assets` | Carpeta con recursos de imagen que se preprocesan y compilan junto con la app |
| `fap_extbuild` | Partes de las fuentes compiladas por herramientas externas: una lista de `ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Booleano, por defecto `False`. Solo para el tipo `PLUGIN`: incrusta el plugin en el `.fap` de la app anfitriona como recurso; se extrae a `apps_assets/APPID` al arrancar |
| `fap_private_libs` | Bibliotecas que se distribuyen como fuentes junto con la app — véase más abajo |

#### Comandos de compilación externa (`fap_extbuild`)

Los comandos se ejecutan desde la raíz del firmware. Los archivos intermedios deben ir a la carpeta temporal de
compilación de la app. `fbt` expande estas variables (y otras internas):

- `${FAP_WORK_DIR}` — la carpeta temporal de compilación de la app
- `${FAP_SRC_DIR}` — la carpeta de fuentes de la app

Ejemplo: compilar una app a partir de fuentes en Rust:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Bibliotecas privadas (`fap_private_libs`)

Las fuentes de las bibliotecas van en una subcarpeta de `lib/` dentro de la carpeta de la app. Cada biblioteca es una
llamada a `Lib()`:

| Parámetro de `Lib()` | Significado | Por defecto |
|---|---|---|
| `name` | Nombre de la carpeta de la biblioteca (**obligatorio**) | — |
| `fap_include_paths` | Rutas (relativas a la biblioteca) que se añaden a la ruta de includes de la app | `["."]` |
| `sources` | Máscaras de archivo para las fuentes de la biblioteca, relativas a su raíz | `["*.c*"]` |
| `cflags` | Flags adicionales del compilador | `[]` |
| `cdefines` | Definiciones adicionales del preprocesador | `[]` |
| `cincludes` | Rutas de includes adicionales, relativas a la raíz de la **app** (por ejemplo, para cabeceras de configuración) | `[]` |

Ejemplo:

```python
    fap_private_libs=[
            Lib(
                name="mbedtls",
                fap_include_paths=["include"],
                sources=[
                    "library/des.c",
                    "library/sha1.c",
                    "library/platform_util.c",
                ],
                cdefines=["MBEDTLS_ERROR_C"],
            ),
            Lib(
                name="loclass",
                cflags=["-Wno-error"],
            ),
        ],
```

Qué hace `fbt` con esto:

- **mbedtls** — se compila desde `lib/mbedtls`; `lib/mbedtls/include` se añade a la ruta de includes de la app; solo
  se compilan los tres archivos listados; se define `MBEDTLS_ERROR_C` para sus fuentes.
- **loclass** — se compila con todas las fuentes de `lib/loclass`; `lib/loclass` se añade a la ruta de includes; los
  avisos **no** se tratan como errores (`-Wno-error`), lo que resulta práctico con código de terceros extenso.

Ambas bibliotecas se enlazan dentro de la app.

## Un archivo `.fam` completo

Un mismo archivo puede definir varias apps. Este es un fragmento de `applications/services/bt/application.fam`:

```python
App(
    appid="bt_start",
    apptype=FlipperAppType.STARTUP,
    entry_point="bt_on_system_start",
    order=70,
)

App(
    appid="bt_settings",
    name="Bluetooth",
    apptype=FlipperAppType.SETTINGS,
    entry_point="bt_settings_app",
    stack_size=1 * 1024,
    requires=[
        "bt",
        "gui",
    ],
    order=10,
)
```

Un manifiesto para tu propia app externa, tal como lo genera `ufbt create APPID=test_app` (desde
`scripts/ufbt/project_template/app_template/application.fam`):

```python
# For details & more options, see documentation/AppManifests.md in firmware repo

App(
    appid="test_app",  # Must be unique
    name="App test_app",  # Displayed in menus
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Optional values
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bit PNG
    # fap_description="A simple app",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Image assets to compile for this application
)
```

Para ver más ejemplos, echa un vistazo a los archivos `.fam` repartidos por el firmware — por ejemplo
`applications/system/*/application.fam` para las apps añadidas por Unleashed.

## Páginas relacionadas

- [Tu primera app en C](/es/dev/first-app-c)
- [Flipper Build Tool (fbt)](/es/dev/fbt)
- [Objetivos de hardware](/es/dev/hardware-targets)
