---
title: Objetivos de hardware
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Objetivos de hardware

El firmware es modular: una sola base de código admite varias configuraciones de hardware. Todo lo que cambia de una
placa a otra — la implementación de `furi_hal`, el código de inicialización de la placa, los scripts del enlazador, las
tablas de símbolos del SDK — se agrupa en una **definición de objetivo**.

El repositorio de Unleashed incluye dos objetivos en `targets/`:

| Carpeta | Hardware |
|---|---|
| `targets/f7` | Flipper Zero — el objetivo por defecto (`TARGET_HW = 7`) |
| `targets/f18` | «Not Flipper Zero» — una placa sin los front-ends de radio; hereda de f7 |

Las cabeceras compartidas están en `targets/furi_hal_include`.

## Cómo se organiza un objetivo

Cada objetivo reside en su propia subcarpeta de `targets/`. Debe contener un `target.json` y puede contener cualquier
otro archivo al que esa definición haga referencia. Por defecto `fbt` compila **todos los archivos fuente** de la
carpeta del objetivo salvo los que se excluyan explícitamente. Los objetivos pueden **heredar** de otro objetivo para
no duplicar código.

## Campos de `target.json`

| Campo | Tipo | Significado |
|---|---|---|
| `include_paths` | lista de cadenas | Carpetas (relativas al objetivo) que se añaden a la ruta global de includes de C/C++ |
| `sdk_header_paths` | lista de cadenas | Carpetas cuyas cabeceras se incluyen en el SDK |
| `startup_script` | nombre de archivo | Script de arranque que realiza la inicialización inicial del hardware |
| `linker_script_flash` | nombre de archivo | Script del enlazador para la imagen principal del firmware |
| `linker_script_ram` | nombre de archivo | Script del enlazador para la configuración «updater» (se ejecuta desde la RAM) |
| `linker_script_app` | nombre de archivo | Script del enlazador para los archivos `.fap` |
| `sdk_symbols` | nombre de archivo | `.csv` con la definición actual del SDK (API) para este objetivo |
| `linker_dependencies` | lista | Bibliotecas con las que enlazar el firmware. Las bibliotecas que no se listan **no se compilan**. Varias pasadas de enlazado pueden requerir el mismo nombre dos veces |
| `inherit` | cadena | Objetivo del que se toma la configuración base. Los valores de lista se amplían y los demás se sobrescriben |
| `excluded_sources` | lista | Archivos de la configuración heredada que **no** hay que compilar |
| `excluded_headers` | lista | Cabeceras de la configuración heredada que **no** hay que poner en el SDK |
| `excluded_modules` | lista | Nombres de bibliotecas (módulos) de `fbt` que hay que excluir al configurar la compilación |

## Ejemplo: cómo hereda f18 de f7

El `targets/f18/target.json` (abreviado) muestra la herencia y las exclusiones en la práctica — toma todo de f7 y
elimina los controladores de Sub-GHz, NFC, RFID, iButton e infrarrojos:

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## Apps y hardware

No todas las apps están disponibles en todos los objetivos.

- **Apps integradas:** elige un conjunto de apps compatible con la opción `FIRMWARE_APP_SET=...`
  (consulta [fbt → conjuntos de apps del firmware](/es/dev/fbt#firmware-app-sets)).
- **Apps externas (FAP):** lista los objetivos compatibles en el `application.fam` de la app. Por ejemplo, para
  compilar una app solo para f7, añade:

```python
    targets=["f7"],
```

No se compilará para otros objetivos. Consulta [Manifiestos de app](/es/dev/app-manifests).

## Compilar para un objetivo concreto

Pasa `TARGET_HW` (y opcionalmente `FIRMWARE_APP_SET`) a `fbt`. Por ejemplo, para compilar y flashear el firmware para
f18 por USB:

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Páginas relacionadas

- [Flipper Build Tool (fbt)](/es/dev/fbt)
- [Manifiestos de app (.fam)](/es/dev/app-manifests)
- [API FuriHalBus](/es/dev/furi-hal-bus)
