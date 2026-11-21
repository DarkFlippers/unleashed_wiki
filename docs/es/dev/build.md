---
title: Compilar el firmware
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Compilar el firmware

Compila el firmware Unleashed desde el código fuente cuando quieras modificar el propio firmware, incluir tus apps en
la compilación o probar el código más reciente de `dev` antes de una release oficial.

Si solo quieres escribir una app (`.fap`), no necesitas todo el firmware: usa [uFBT](/es/dev/first-app-c) y salta a
[compilar apps contra el SDK de Unleashed](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Qué necesitas

- **Git** — [descarga](https://git-scm.com/downloads) para Windows; en Linux/macOS instálalo con tu gestor de
  paquetes (`brew`, `apt`, …).
- **VS Code** (recomendado para desarrollar, opcional si solo vas a compilar).
- Unos pocos GB de espacio en disco. Nada más: `fbt` descarga su propio toolchain de ARM en la primera ejecución y no
  toca el `PATH` de tu sistema (consulta [fbt → Entorno](/es/dev/fbt#environment)).

## 1. Clonar el repositorio

Clona siempre **con submódulos**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Si ya lo has clonado sin `--recursive`, inicializa los submódulos:

```shell
git submodule update --init --recursive
```

## 2. Compilar en Linux / macOS

Compila todo y genera un paquete de actualización que puedas instalar desde la tarjeta microSD:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Compila una sola app de `applications_user/` y lánzala en un Flipper conectado por USB:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Compilar en Windows

Usa `fbt.cmd` en PowerShell o `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
En Windows puede que tengas que escribir `.\fbt.cmd` (con barra invertida) en lugar de `./fbt.cmd`, según el intérprete
de comandos que uses.
:::

## 4. Encontrar el resultado y flashearlo

Todos los resultados de la compilación van a `dist/`. El archivo que hay que instalar es el paquete de actualización:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

El patrón del nombre es `flipper-z-{target}-update-{suffix}.tgz`. El sufijo por defecto es `local` (lo define
`DIST_SUFFIX` en `fbt_options.py`, o la variable de entorno `DIST_SUFFIX`).

Formas de instalarlo:

- abre el `.tgz` en **qFlipper** (*Install from file*) o en el instalador web de Unleashed;
- o deja que `fbt` lo haga por USB: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (compila, sube e instala);
- o flashéalo por SWD con una sonda de depuración: `./fbt flash` (consulta
  [targets de fbt](/es/dev/fbt#high-level-targets)).

::: tip ¿Por qué `DEBUG=0`?
El `fbt_options.py` de Unleashed usa por defecto `COMPACT=1` y **`DEBUG=1`**. Una imagen de depuración es más grande y
puede no caber por debajo de la pila de radio en la flash — el empaquetado se detiene entonces con
`Firmware image overlaps C2 region and is not programmable!`. Para cualquier cosa que vayas a instalar, pasa
`DEBUG=0` explícitamente. Ten en cuenta que `DEBUG=0` también elimina en compilación las llamadas a `furi_assert()`.
:::

## Integración con VS Code

`fbt` incluye una configuración lista para VS Code:

```sh
./fbt vscode_dist
```

Esto copia la configuración en `.vscode/`. Después abre la raíz del firmware en VS Code con
**File → Open Folder**, acepta las extensiones recomendadas y usa <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> para
las tareas de compilación. Más información en [fbt → VS Code](/es/dev/fbt#vs-code-integration).

## Compilar apps contra el SDK de Unleashed con uFBT {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) compila apps individuales contra un SDK descargado en lugar del árbol de fuentes completo. **Por
defecto descarga el SDK del firmware oficial.** Para compilar para Unleashed, apúntalo al índice de actualizaciones de
Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Los canales son `dev` y `release`. Usa los mismos flags en **cada** `ufbt update` posterior; de lo contrario, uFBT
vuelve silenciosamente al SDK oficial y la app compilada declara una versión de API incorrecta.

::: tip Unleashed
Unleashed mantiene la API oficial, así que la mayoría de las apps oficiales funcionan tal cual. Una app solo se niega a
cargar cuando su versión mayor de API no coincide con la del firmware — recompilarla contra el SDK correspondiente lo
soluciona.
:::

## Compilar apps en Android

Las apps (no el firmware) también se pueden compilar directamente en un móvil Android con uFBT dentro de Termux —
consulta [Compilar apps en Android](/es/dev/android-build).

## Resolución de problemas

| Problema | Solución |
|---|---|
| La compilación falla por archivos que faltan o errores de submódulos | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Añade `DEBUG=0` al comando |
| `./fbt` no se encuentra en Windows | Usa `fbt.cmd` / `.\fbt.cmd` |
| Una app compilada con uFBT no arranca: API incompatible | Vuelve a ejecutar `ufbt update` con el `--index-url` de Unleashed y recompila |
| Quieres una recompilación limpia | Añade `-c` para limpiar los targets indicados, por ejemplo `./fbt -c fw_dist` |

## Páginas relacionadas

- [Flipper Build Tool (fbt)](/es/dev/fbt) — todos los targets y opciones
- [Tu primera app en C](/es/dev/first-app-c)
- [Actualizaciones OTA](/es/dev/ota) — qué hay dentro de un paquete de actualización
- [Objetivos de hardware](/es/dev/hardware-targets)
