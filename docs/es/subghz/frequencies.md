---
title: Frecuencias y alcance
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Frecuencias y alcance

El Flipper Zero se comunica con el mundo por debajo de 1 GHz mediante un transceptor **TI CC1101**. Esta página
cubre las bandas que admite el chip, la lista de frecuencias que incluye Unleashed, cómo funcionan los límites de
transmisión en Unleashed y cómo añadir tus propias frecuencias.

## Bandas del hardware

La hoja de datos del CC1101 especifica tres bandas:

| Banda | Uso habitual |
|---|---|
| 300–348 MHz | Puertas de garaje y cancelas estadounidenses (familia de 300, 310, 315, 318, 390 MHz), mandos de coche |
| 387–464 MHz | Mandos LPD433 de 433.92 MHz, barreras, sensores, timbres (la mayor parte de Europa y la CEI) |
| 779–928 MHz | Aparatos de 868 MHz (SRD de la UE) y 915 MHz (ISM de EE. UU.) |

Unleashed amplía ligeramente la ventana de transmisión por defecto para que funcionen las frecuencias habituales de
350 MHz y 467.75 MHz.

## Límites de transmisión en Unleashed

::: tip Unleashed
El firmware original restringe la transmisión a las frecuencias permitidas en la **región** detectada durante la
actualización (por ejemplo, solo 433.05–434.79 y 868.15–868.55 MHz en la UE y Rusia). **Unleashed elimina por
completo el bloqueo regional.** Puedes transmitir en cualquier frecuencia que admita el chip, sin pasos adicionales.
:::

Lo que sigue aplicándose es un límite de seguridad del hardware (de `furi_hal_subghz.c`):

| Modo | Rangos de TX permitidos |
|---|---|
| Por defecto | 300–350 MHz, 387–467.75 MHz, 779–928 MHz |
| Ampliado («peligroso») | 281–361 MHz, 378–481 MHz, 749–962 MHz |

Si intentas transmitir fuera del rango permitido, el Flipper se niega a hacerlo.

### Ampliar el rango (peligroso) {#extended-range}

::: danger
Transmitir fuera de las especificaciones del CC1101 puede **dañar el chip de radio**. Ni el equipo de Flipper ni los
desarrolladores de Unleashed se responsabilizan de los daños. Casi nadie necesita esto: el rango por defecto cubre
ya prácticamente cualquier mando real.
:::

1. Conecta la tarjeta SD a un PC (o usa qFlipper o el gestor de ficheros de la aplicación móvil).
2. Abre `/ext/subghz/assets/dangerous_settings`. Su contenido tiene este aspecto:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Cambia `false` por `true`, guarda el fichero y reinicia el Flipper (el ajuste se lee al arrancar).

Véase también [Ajustes peligrosos](/es/start/dangerous-settings).

## Lista de frecuencias por defecto

Estas son las frecuencias que puedes recorrer con <kbd>←</kbd> <kbd>→</kbd> en **Read**, en **Read RAW** → `Config`,
y a las que redondea el Frequency Analyzer. **433.92 MHz** es la frecuencia por defecto.

| 300–350 MHz | 387–467.75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (primera de LPD433), 433.220, 433.420, 433.657070, 433.889, **433.920** (central de LPD433, por defecto), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (última de LPD433), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Lista del hopper

Cuando **Hopping** está activado, el receptor recorre solo una lista corta (una lista larga perdería señales):

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulaciones (presets)

La frecuencia sola no basta: el Flipper no es un SDR y hay que indicarle la modulación por adelantado. Presets
integrados:

| Nombre en el menú | Preset en el fichero `.sub` | Significado |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, ancho de banda de 270 kHz |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, ancho de banda de 650 kHz — **por defecto, el que usan la mayoría de los mandos** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, desviación de 2,38 kHz |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, desviación de 47,6 kHz |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, desviación de 12 kHz (por ejemplo Cardin S449, Sommer) |

Puedes añadir tus propios presets (por ejemplo `FM15k`, `Pagers`); véase
[Formatos de fichero](/es/subghz/file-format#setting-user).

## Añadir tus propias frecuencias {#adding-frequencies}

1. En la tarjeta SD, ve a `/ext/subghz/assets/`.
2. Renombra `setting_user.example` a `setting_user` (los ficheros `_user` sobreviven a las actualizaciones de
   firmware).
3. Añade líneas con este formato, siempre con 9 dígitos, en Hz:
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Reinicia la aplicación Sub-GHz.

Reglas que conviene conocer:

- Las frecuencias de usuario se **añaden detrás** de la lista por defecto: desplázate hasta el final de la lista
  para encontrarlas.
- `Hopper_frequency` añade una frecuencia al salto. Mantén la lista del hopper corta. Repetir una frecuencia hace
  que el Flipper la escuche más a menudo.
- Para usar **solo** tus propias frecuencias, cambia `#Add_standard_frequencies: true` por
  `Add_standard_frequencies: false`. Entonces tendrás que rellenar **ambas** listas (`Frequency:` y
  `Hopper_frequency:`), o la lista principal quedará vacía.
- `Default_frequency: 433920000` fija la frecuencia con la que arrancan Read y Read RAW.

## Resolución de problemas

- **No se recibe nada**: la frecuencia o la modulación son incorrectas. Localiza la frecuencia con el
  [Frequency Analyzer](/es/subghz/frequency-analyzer) y después prueba `AM650` y luego los presets FM.
- **Mi frecuencia no está en la lista**: añádela a `setting_user` (más arriba). El analizador seguirá redondeando a
  la entrada más cercana de la lista, así que fija el valor exacto a mano en `Config`.
- **Transmisión rechazada**: la frecuencia está fuera de la ventana de TX por defecto; consulta la tabla anterior.
  No actives el rango ampliado solo por «probar».

## Relacionado

- [Frequency Analyzer](/es/subghz/frequency-analyzer) · [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw)
- [Ajustes de radio](/es/subghz/settings) · [Formatos de fichero](/es/subghz/file-format) · [CC1101 externo](/es/subghz/external-cc1101)
