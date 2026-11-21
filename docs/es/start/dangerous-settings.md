---
title: Ajustes peligrosos
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Ajustes peligrosos: rango Sub-GHz ampliado

Unleashed puede hacer que la radio CC1101 funcione **fuera de su rango oficial de frecuencias**. Esta página explica
qué hace el ajuste, por qué es casi seguro que no lo necesitas y cómo activarlo si de verdad lo necesitas.

::: danger Lee esto primero
1. No hagas esto a menos que sepas exactamente lo que haces.
2. No necesitas el rango ampliado para casi ningún caso de uso.
3. Transmitir fuera de las especificaciones del hardware **puede dañar tu hardware**.
4. Ni el equipo de Flipper Devices ni los desarrolladores de Unleashed se responsabilizan de ningún daño causado
   por un firmware personalizado ni por ampliar el rango de frecuencias.
:::

## Probablemente no lo necesitas: no hay bloqueo regional

::: tip Unleashed
En Unleashed, **todas las restricciones regionales de transmisión están eliminadas por defecto**. Cualquier
frecuencia dentro del rango que admite el chip transmite sin pasos adicionales. No uses el ajuste peligroso para
«desbloquear tu región». Para eso no hace falta.
:::

Si la transmisión está bloqueada en una frecuencia, comprueba primero que la frecuencia está dentro del rango normal
de transmisión que se indica más abajo. Fuera de él, el firmware registra
`Frequency blocked - outside default range`.

## Rangos de frecuencia

| | Rangos |
|---|---|
| Hoja de datos del CC1101 | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Rango de **transmisión** por defecto de Unleashed | ≈ 300–350 MHz, 387–467,75 MHz, 779–928 MHz (ampliado para incluir los 350 MHz y los 467 MHz) |
| Transmisión con `dangerous_settings` activado | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

El rango ampliado coincide con el rango ampliado del YARD Stick One (según el código fuente del firmware). Fuera de
los rangos de la hoja de datos, el chip funciona fuera de especificación y transmitir ahí puede dañarlo.

## Cómo activarlo

1. Saca la tarjeta microSD, o conéctate con qFlipper o con el gestor de archivos que prefieras.
2. Abre el archivo **`/ext/subghz/assets/dangerous_settings`**. Tiene este aspecto:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Lee los comentarios y después cambia `false` por `true`:
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Guarda el archivo y reinicia el Flipper. El ajuste se lee al arrancar.

Para volver atrás, pon el valor en `false` y reinicia.

::: warning Actualizaciones
El archivo forma parte de los recursos del firmware. Una actualización puede sobrescribirlo con el valor `false` por
defecto. Compruébalo después de actualizar si dependes de este ajuste.
:::

## Relacionado

- Frecuencias y presets de Sub-GHz, y cómo añadir tus propias frecuencias:
  [Frecuencias](/es/subghz/frequencies)
- Ajustes de Sub-GHz dentro de la aplicación: [Ajustes de Sub-GHz](/es/subghz/settings)
- Módulo CC1101 externo: [CC1101 externo](/es/subghz/external-cc1101)

Usa la radio solo con tus propios dispositivos y de acuerdo con la normativa de radiocomunicaciones de tu país.
