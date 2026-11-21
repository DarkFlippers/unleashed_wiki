---
title: Mando de barrera ZKTeco CMP200
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — Princeton en envoltorio chino

*Una breve reseña de @gromovyna sobre el mando de las barreras ZKTeco, además de cómo manejarlo en Unleashed.*

![Mando ZKTeco CMP200](/img/remote/a2cb668ab24d6625.png)

## Introducción

Hace algún tiempo abrió una clínica privada cerca de casa de gromovyna y se instaló una **barrera ZKTeco**. Tenía curiosidad, pero había poco tráfico y no demasiadas razones para investigar, así que la cosa quedó en la lista mental de pendientes.

![Barrera ZKTeco (foto de internet)](/img/remote/4cfaf6cbf4b21db6.png)

Después, al salir de una consulta, vio el mando sobre el mostrador de recepción desde un piso superior, lo fotografió, identificó el modelo con Google Lens y lo puso en su lista de «comprar». Antes de comprarlo preguntó a MMX (xMasterX), y resultó que el misterio ya estaba resuelto.

## Cómo envolvieron los chinos a Princeton

Todo es bastante prosaico, y lleva más de un año siendo compatible con **Unleashed** (gracias a MMX). Por dentro es un **Princeton** corriente con un código de botón de 8 bits, y los códigos de botón son bien conocidos, **los mismos en todos los mandos**:

| Parámetro | Valor |
|---|---|
| Frecuencia | **430.50 MHz** |
| Modulación | **AM650** |
| Botón UP | `0x30` |
| Botón STOP | `0x03` |
| Botón DOWN | `0x0C` |

Y lo mejor: en Unleashed esos códigos de botón **ya están asignados a las teclas de flecha**, así que una única señal guardada funciona enseguida como el mando completo.

::: tip Unleashed
ZKTeco aparece en la lista de sistemas compatibles de Unleashed como `ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` y tiene su propia entrada en `Add Manually`. 430.50 MHz está en la lista de frecuencias por defecto.
:::

## Cómo usarlo con el Flipper

Como el código es estático, una copia es idéntica al original: ambos siguen funcionando en cualquier orden.

### Opción 1 — leer tu mando

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Back.
3. Pulsa un botón del CMP200 cerca del Flipper. Aparece una señal `Princeton`.
4. <kbd>OK</kbd> → `Save`, pon nombre al fichero.
5. Ábrelo en `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> envía el botón capturado; las teclas de flecha envían los demás botones (UP / STOP / DOWN).

### Opción 2 — crear un mando

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Elige la banda `430.50 AM650` (aparece primera en esta entrada).
3. Pon nombre y guarda. El Flipper crea una clave Princeton de 24 bits con un código aleatorio, TE de 357 µs y botón `0x30` (UP).

Un mando creado así tiene su propio código: la barrera solo reaccionará después de registrarlo en su receptor (sigue el manual de la barrera). Para actuar como un mando existente, lee ese mando en su lugar (opción 1).

::: warning
Solo para barreras de tu propiedad o que administres.
:::

## ¿Eso es todo?

Por ahora, sí. Como señala gromovyna, esta compatibilidad llegó sin hacer ruido, así que la mayor parte de la comunidad nunca se dio cuenta; él la probó y compartió los resultados.

## Resolución de problemas

- **No se recibe nada**: asegúrate de que la frecuencia sea 430.50 y no 433.92; compruébalo con el [Frequency Analyzer](/es/subghz/frequency-analyzer).
- **`Ignore Princeton` está en ON** en el `Config` de Read: los mandos basados en Princeton como este quedan entonces ocultos; desactívalo.
- **Las flechas no envían nada**: abre la señal desde `Saved → Emulate`; los botones personalizados funcionan en la pantalla de transmisión.

## Páginas relacionadas

- [Read](/es/subghz/read) · [Add Manually](/es/subghz/add-manually) · [Sistemas compatibles](/es/subghz/supported-systems)
- [Códigos rodantes](/es/subghz/rolling-codes) — los botones personalizados explicados
