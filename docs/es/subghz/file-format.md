---
title: Formatos de fichero
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/resources/subghz/assets, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md]
sources: [unleashed-docs, unleashed-src]
---
# Formatos de fichero de Sub-GHz

Todos los ficheros de Sub-GHz son texto plano en el *Flipper File Format* (líneas `Key: value`), así que puedes
verlos y editarlos en un PC. Esta página describe los ficheros de señal (`.sub`) y los ficheros de configuración de
`/ext/subghz/assets/`.

| Ruta | Qué es |
|---|---|
| `/ext/subghz/*.sub` | Señales guardadas: claves, RAW y BinRAW |
| `/ext/subghz/assets/setting_user` | Tus frecuencias, lista del hopper y presets personalizados |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Tus claves de fabricante KeeLoq |
| `/ext/subghz/assets/keeloq_mfcodes` | Claves de fabricante KeeLoq integradas (cifradas, incluidas con el firmware) |
| `/ext/subghz/assets/nice_flor_s`, `alutech_at_4n` | Tablas integradas de esos protocolos |
| `/ext/subghz/assets/dangerous_settings` | Interruptor del rango de frecuencias ampliado; véase [Frecuencias](/es/subghz/frequencies#extended-range) |

## Estructura de un fichero `.sub`

Un fichero `.sub` tiene tres partes:

1. **Cabecera**: tipo de fichero, versión y frecuencia.
2. **Preset**: preset de modulación, o una configuración completa personalizada del CC1101.
3. **Datos**: nombre del protocolo y sus campos, o temporizaciones RAW.

### Cabecera

| Campo | Tipo | Descripción |
|---|---|---|
| `Filetype` | cadena | `Flipper SubGhz Key File` para claves, `Flipper SubGhz RAW File` para grabaciones RAW |
| `Version` | uint | Versión del formato de fichero, actualmente `1` |
| `Frequency` | uint | Frecuencia en Hz, por ejemplo `433920000` |

### Preset

| Campo | Descripción |
|---|---|
| `Preset` | Nombre del preset. Para un preset personalizado debe ser `FuriHalSubGhzPresetCustom` |
| `Custom_preset_module` | Transceptor, `CC1101` en el Flipper Zero (solo en presets personalizados) |
| `Custom_preset_data` | Configuración del transceptor (solo en presets personalizados) |

Presets integrados:

| Valor de `Preset` | Nombre en el menú | Significado |
|---|---|---|
| `FuriHalSubGhzPresetOok270Async` | `AM270` | OOK, ancho de banda de 270 kHz |
| `FuriHalSubGhzPresetOok650Async` | `AM650` | OOK, ancho de banda de 650 kHz |
| `FuriHalSubGhzPreset2FSKDev238Async` | `FM238` | 2-FSK, desviación de 2,38 kHz, ancho de banda de 270 kHz |
| `FuriHalSubGhzPreset2FSKDev12KAsync` | `FM12K` | 2-FSK, desviación de 12 kHz |
| `FuriHalSubGhzPreset2FSKDev476Async` | `FM476` | 2-FSK, desviación de 47,6 kHz, ancho de banda de 270 kHz |

Un preset personalizado va incrustado en el fichero, así que otro Flipper puede enviarlo incluso sin tener ese
preset en sus ajustes.

#### Datos de un preset personalizado {#custom-preset-data}

Bytes hexadecimales separados por espacios: `XX YY XX YY … 00 00 ZZ ZZ ZZ ZZ ZZ ZZ ZZ ZZ`

- `XX`: dirección de registro del CC1101; `YY`: valor del registro (tantos pares como sean necesarios);
- `00 00`: fin del bloque de registros;
- `ZZ ×8`: la tabla PA de 8 bytes (rampa del amplificador de potencia).

Consulta la [hoja de datos del CC1101](https://www.ti.com/lit/ds/symlink/cc1101.pdf) para el significado de los
registros.

### Ficheros de clave

Las señales decodificadas almacenan el nombre del protocolo y sus campos:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

| Campo | Descripción |
|---|---|
| `Protocol` | Nombre del protocolo exactamente como aparece en el registro de protocolos (por ejemplo `Princeton`, `KeeLoq`, `Nice FloR-S`, `CAME Atomo`, `Security+ 2.0`) |
| `Bit` | Longitud de la carga útil en bits |
| `Key` | Carga útil, en hexadecimal, 8 bytes |
| `TE` | Duración del pulso base (intervalo de cuantización) en µs, en los protocolos que la almacenan |

Los protocolos pueden añadir sus propios campos. Los que te encontrarás en Unleashed:

| Campo | Lo usan | Significado |
|---|---|---|
| `Manufacture` | KeeLoq, FAAC SLH / Genius | Fabricante cuya clave decodifica la señal (por ejemplo `DoorHan`, `BFT`, `Genius`) |
| `Seed` | BFT Mitto, Erreka, FAAC SLH, Genius, algunos KeeLoq | Secreto por mando para secure learning |
| `CounterMode` | Nice Flor-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix | Comportamiento experimental del contador; véase [Modos de contador](/es/subghz/counter-mode) |
| `Secplus_packet_1`, `Pin` | Security+ 2.0 | Segundo paquete; PIN del teclado en los paquetes de 86 bits ([Security+ PIN](/es/subghz/secplus-pin)) |
| `Cert` | Nice O-Code | Certificado del receptor ([Nice O-Code](/es/subghz/nice-o-code)) |

Ejemplo de preset personalizado:

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetCustom
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
Protocol: Princeton
Bit: 24
Key: 00 00 00 00 00 95 D5 D4
TE: 400
```

::: warning Editar ficheros de código rodante
Cambiar a mano la `Key` de un protocolo dinámico rara vez produce un código válido. Para cambiar el serial, el botón
o el contador usa [Add Manually [Advanced]](/es/subghz/add-manually) o, en modo depuración,
`Saved → fichero → Signal Settings`.
:::

### Ficheros RAW

Grabaciones de [Read RAW](/es/subghz/read-raw):

```text
Filetype: Flipper SubGhz RAW File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: RAW
RAW_Data: 29262 361 -68 2635 -66 24113 -66 11 ...
RAW_Data: -424 205 -412 159 -412 381 -240 181 ...
```

- `Protocol` debe ser `RAW`.
- `RAW_Data`: duraciones en µs; positivo = portadora activa, negativo = portadora inactiva. Los valores no pueden
  ser cero, deben empezar con un número positivo y alternar de signo. Hasta 512 valores por línea; la línea puede
  repetirse tantas veces como sea necesario.

Las cargas útiles largas se leen de la tarjeta SD durante la transmisión. Con temporizaciones muy cortas (por
debajo de 10 µs) una tarjeta lenta puede no dar abasto y la transmisión se detiene antes del final.

### Ficheros BinRAW

`Bin RAW` en `Read → Config` produce ficheros **BinRAW**. A diferencia de RAW, almacenan solo la secuencia
repetitiva útil, con la tasa de bits restaurada y sin el ruido, de modo que pueden reproducir casi cualquier
protocolo **estático**, conocido o no. Mantén el botón del mando algo más de tiempo al leer para acumular datos
suficientes.

| Campo | Descripción |
|---|---|
| `Protocol` | `BinRAW` |
| `Bit` | Longitud de la carga útil del fichero completo en bits (máximo 4096) |
| `TE` | Intervalo de cuantización, en µs |
| `Bit_RAW` | Longitud del bloque `Data_RAW` siguiente, en bits |
| `Data_RAW` | Duraciones codificadas: cada bit = un `TE`; `1` = portadora, `0` = sin portadora |

Ejemplo: `TE: 100`, `Bit_RAW: 8`, `Data_RAW: 37` → `0b00110111` → envía `-200 200 -100 300`.
Las parejas `Bit_RAW` + `Data_RAW` forman bloques repetidos; varios bloques se envían uno tras otro.

```text
Protocol: BinRAW
Bit: 1572
TE: 597
Bit_RAW: 260
Data_RAW: 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 00 0F 4A B5 55 4C B3 52 AC D5 2D 53 52 AD 4A D5 35 00
```

## `setting_user` {#setting-user}

Frecuencias y presets adicionales, cargados al arrancar la aplicación Sub-GHz. Renombra `setting_user.example` a
`setting_user`.

```text
Filetype: Flipper SubGhz Setting File
Version: 1

# Add standard frequencies included with firmware and place user frequencies after them
Add_standard_frequencies: true

# Default frequency for "Read" and "Read Raw"
Default_frequency: 433920000

# Frequencies for "Read", "Read Raw" and "Frequency Analyzer"
Frequency: 300000000
Frequency: 310000000

# Frequencies for hopping mode (keep this list small)
Hopper_frequency: 300000000
Hopper_frequency: 310000000

# Custom preset
Custom_preset_name: AM_1
Custom_preset_module: CC1101
Custom_preset_data: 02 0D 03 07 08 32 0B 06 14 00 13 00 12 30 11 32 10 17 18 18 19 18 1D 91 1C 00 1B 07 20 FB 22 11 21 B6 00 00 00 C0 00 00 00 00 00 00
```

| Clave | Significado |
|---|---|
| `Add_standard_frequencies` | `true`: lista del firmware + las tuyas (añadidas detrás); `false`: solo las tuyas (entonces rellena tanto `Frequency` como `Hopper_frequency`) |
| `Default_frequency` | Frecuencia con la que arrancan Read / Read RAW |
| `Frequency` | Añade una frecuencia a la lista principal (9 dígitos, en Hz). Se puede repetir |
| `Hopper_frequency` | Añade una frecuencia al salto. Repetir una hace que el Flipper la escuche más a menudo |
| `Custom_preset_name` / `_module` / `_data` | Un preset de modulación personalizado, que se muestra en la lista `Modulation` con ese nombre. Formato de los datos: [más arriba](#custom-preset-data) |

El fichero `.example` incluye presets comentados que puedes activar: `FM95`, `FM15k` (2-FSK, 200 kHz de ancho de
banda / filtro de 135 kHz, desviación de 15,86 kHz), `Pagers`, `AM_1` y `AM_2`.

## `keeloq_mfcodes_user` {#keeloq-mfcodes-user}

Tus propias claves de fabricante KeeLoq, cargadas al arrancar la aplicación además de la base de datos integrada
(cifrada). Créalo a partir de `keeloq_mfcodes_user.example`, elimina las claves de ejemplo y **deja una línea vacía
al final**.

```text
Filetype: Flipper SubGhz Keystore File
Version: 0
Encryption: 0
AABBCCDDEEFFAABB:1:Test1
AABBCCDDEEFFAABB:2:Test2
```

Cada línea es `KEY:METHOD:NAME`:

- `KEY`: clave de fabricante de 64 bits, 16 dígitos hexadecimales;
- `NAME`: nombre sin espacios, hasta 64 caracteres (se muestra como fabricante en Read);
- `METHOD`: tipo de aprendizaje:

| Valor | Aprendizaje |
|---|---|
| `0` | probar todos: itera sobre la clave anterior y la de fabricante en orden de bytes directo e invertido |
| `1` | Simple Learning |
| `2` | Normal Learning |
| `3` | Secure Learning (necesita Seed) |
| `4` | Magic XOR type 1 |
| `5` | FAAC SLH |
| `6` | Magic Serial type 1 |
| `7` | Magic Serial type 2 |
| `8` | Magic Serial type 3 |

`Encryption: 0` significa que el fichero es texto plano: los ficheros de usuario no deben estar cifrados. Más sobre
los tipos de aprendizaje: [KeeLoq](/es/subghz/keeloq).

## Relacionado

- [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw) · [Frecuencias](/es/subghz/frequencies) · [Radio Settings](/es/subghz/settings)
- [KeeLoq](/es/subghz/keeloq) · [Modos de contador](/es/subghz/counter-mode) · [Ficheros de mapa de Sub-GHz Remote](/es/subghz/remote)
