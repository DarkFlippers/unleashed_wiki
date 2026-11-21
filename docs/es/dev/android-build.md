---
title: Compilar apps en Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Compilar apps en Android (Termux + uFBT)

Configura `ufbt` dentro de [Termux](https://termux.dev/) en un móvil Android normal, sin root, y compila apps
(`.fap`) de Flipper Zero directamente en el teléfono — sin PC, sin proot y sin máquina virtual.

::: info Créditos
Lo resolvió [@CamsShaft](https://github.com/CamsShaft) a base de mucha prueba y error en un Samsung Galaxy S22
(SM-S901W, aarch64). Guía original (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Forma parte de la
documentación de Unleashed.
:::

**Alcance:** esto compila **apps**, no el firmware. Para el firmware en sí consulta
[Compilar el firmware](/es/dev/build).

Las rutas que aparecen a continuación dan por supuesto un dispositivo **aarch64** y el prefijo por defecto de Termux
(`$PREFIX` = `/data/data/com.termux/files/usr`). Tu dispositivo puede ser distinto — los fallos típicos están
cubiertos en [Resolución de problemas](#troubleshooting).

## Por qué requiere trabajo extra

uFBT descarga un toolchain cruzado `arm-none-eabi-gcc` precompilado para un Linux normal con **glibc**. Termux se
ejecuta sobre la libc **Bionic** de Android, con una organización del sistema de archivos no estándar, y todos los
binarios ELF del toolchain piden `/lib/ld-linux-aarch64.so.1` como enlazador dinámico — y ese archivo no existe en
Android.

La solución: instalar la capa de compatibilidad glibc de Termux y después ejecutar cada binario del toolchain a
través del propio enlazador de glibc mediante un pequeño script envoltorio.

::: danger No ejecutes `patchelf` sobre los binarios del toolchain
Corrompe la organización de sus segmentos ELF y acabas con segfaults en `cc1`. Los envoltorios que se describen abajo
dejan los binarios intactos byte a byte.
:::

## Requisitos previos

- Un dispositivo Android aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/) instalado **desde F-Droid** — la versión de Google Play está
  obsoleta y no funciona.
- Conexión a internet y un par de GB libres para el toolchain, el SDK y glibc.

## 1. Paquetes básicos

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` **no** es opcional: el bucle de envoltorios del paso 6 lo usa para distinguir los binarios ELF de todo lo
demás.

## 2. Capa de compatibilidad glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Tienen que ser **dos comandos separados**: `glibc-repo` añade el repositorio del que viene `glibc-runner`. Juntos
instalan una glibc completa en `$PREFIX/glibc/`, incluido el enlazador dinámico. Compruébalo:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Nunca definas `LD_PRELOAD` globalmente apuntando al `libc.so.6` de glibc.** Rompe los propios binarios Bionic de
Termux, incluido Python, de formas poco evidentes. Los envoltorios del paso 6 hacen que no sea necesario.
:::

## 3. Instalar uFBT y las dependencias de compilación de Python

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Paquete | Para qué se necesita |
|---|---|
| `colorlog` | Registro de los scripts de compilación |
| `heatshrink2` | Compresión de iconos y recursos |
| `pyelftools` | El paso de posprocesado `FASTFAP` |
| `scons` | El sistema de compilación — debe ser una instalación independiente; la copia incluida en el toolchain es inservible aquí |
| `pillow` | Conversión de iconos; sin él, el único error es un simple `convert: No such file or directory` |

Si el wheel de `pillow` no se compila, usa el paquete de Termux: `pkg install python-pillow`.

## 4. Apuntar uFBT al SDK de Unleashed {#_4-point-ufbt-at-the-unleashed-sdk}

**uFBT usa por defecto el SDK del firmware oficial.** Para compilar contra Unleashed, pasa el índice de
actualizaciones de Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Canales: `dev` y `release`. **Cada `ufbt update` posterior necesita los mismos flags**, o volverás silenciosamente al
SDK oficial y compilarás contra la API equivocada.

Si `~/.ufbt/toolchain/` sigue vacío, cualquier llamada a uFBT inicializa el toolchain:

```sh
ufbt -h
```

Aquí es normal un error que mencione `python3` — el paso 5 lo arregla. Comprueba que el toolchain ha llegado:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Reapuntar el Python del toolchain

El toolchain trae su propio Python enlazado con glibc, que no puede ejecutarse aquí. Haz que todas las entradas
`python3*` apunten al Python de Termux:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Envolver los binarios del toolchain

Todo lo demás depende de este paso. Cada envoltorio ejecuta el binario real a través del enlazador dinámico de glibc
con un `--library-path` explícito, de modo que el binario en sí nunca se modifica.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

Los tres patrones son tres directorios distintos de binarios ELF. Olvidarse de uno da un error característico:

| Directorio | Contiene | Error si no se envuelve |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Por qué importan las salvaguardas (sobre todo al reejecutar):

- `*.so` se omite porque `liblto_plugin.so`, en `libexec/`, es una biblioteca compartida y no un ejecutable;
  envolverla da `invalid ELF header`.
- `*.real` y la comprobación de `$f.real` hacen la función idempotente: reejecutarla después de actualizar el
  toolchain no puede envolver un envoltorio.
- En `bin/` se envuelve solo `arm-none-eabi-*` a propósito: `bin/python3` apunta ahora al Python Bionic de Termux y
  **no** debe pasar por el enlazador de glibc.

::: warning
`ufbt update` puede reemplazar todo el toolchain — **vuelve a ejecutar los pasos 5 y 6 después de cada
actualización.**
:::

## 7. Compilar

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Una compilación correcta termina así:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

El `.fap` está en `dist/`. Compara la API indicada con el firmware de tu Flipper — si no coinciden, la app se negará
a cargar.

## 8. Pasar el .fap al Flipper

`ufbt launch` y `ufbt flash_usb` necesitan una conexión serie (`/dev/ttyACM*`). **En un Android de fábrica, sin root,
esto no funciona**: Android no expone los nodos de dispositivo USB CDC-ACM a Termux. Solo un dispositivo con root y un
controlador CDC-ACM funcional puede usar esos comandos.

En su lugar, copia el archivo fuera. Los FAP residen en `/ext/apps/<Category>/` en la tarjeta microSD:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

Desde `Downloads` el archivo es visible para otras apps, así que pásalo al Flipper por la vía habitual: con la app
móvil de Flipper o con un lector de tarjetas microSD USB-C.

## Resolución de problemas {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Uno de los tres directorios del paso 6 no se ha envuelto. Vuelve a ejecutar las llamadas a `wrap` — se pueden repetir
sin riesgo.

### `liblto_plugin.so: invalid ELF header`

Se ha envuelto una biblioteca compartida. Restáurala:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` en cc1

El binario se ha corrompido, casi siempre por `patchelf`. Vuelve a descargar el toolchain:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Después repite los pasos 5 y 6. **Nunca uses `patchelf` con estos binarios.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

Falta `pillow`: `pip install pillow`, o `pkg install python-pillow`.

### `python3: No such file or directory`

El enlace simbólico del Python del toolchain está roto o lo ha restaurado una actualización. Repite el paso 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` apunta al `libc.so.6` de glibc, lo que rompe los binarios Bionic de Termux. Límpialo:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Después revisa tus archivos de arranque del shell por si queda algún resto:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` dice que el SDK está actualizado, pero falta el toolchain

uFBT controla el SDK y el toolchain por separado. Fuerza los dos:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Después repite los pasos 5 y 6.

### La app compila pero declara una versión de API equivocada

Se ha ejecutado un `ufbt update` sin `--index-url`, así que uFBT ha vuelto al SDK oficial. Vuelve a ejecutar el
comando del [paso 4](#_4-point-ufbt-at-the-unleashed-sdk).

### Los envoltorios han desaparecido después de una actualización

Es lo esperado: `ufbt update` puede reemplazar todo el directorio del toolchain. Repite los pasos 5 y 6.

## Qué ocurre en realidad

Cada envoltorio ejecuta su binario real a través del enlazador dinámico de glibc, con `--library-path` apuntando a
las bibliotecas de glibc. Cuando `arm-none-eabi-gcc` hace exec de `cc1`, se encuentra con un script de shell que
encadena a través del enlazador hasta el binario `.real` intacto. La salida compilada no se ve afectada: va dirigida a
un Cortex-M bare-metal, no a Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Páginas relacionadas

- [Tu primera app en C](/es/dev/first-app-c)
- [Compilar el firmware](/es/dev/build)
- [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps)
- [App móvil de Flipper](/es/mobile/mobile-app)
