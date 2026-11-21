---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

El plugin **Sentry Safe** de [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) abre cajas
fuertes electrónicas Sentry Safe y Master Lock **sin el código PIN**, aprovechando una vulnerabilidad conocida en la
conexión de su teclado. La vulnerabilidad y una demostración se describen en
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Úsalo solo en una caja fuerte que sea tuya. Abrir la caja fuerte de otra persona es ilegal.
:::

::: tip Unleashed
Sentry Safe es un plugin de GPIO de los [packs de apps](/es/apps/catalog#base-and-extra-packs) de la comunidad; no
forma parte del firmware en sí.
:::

## Conexiones

El Flipper se conecta a dos cables de la caja fuerte (el negro y el verde). El
[análisis de la vulnerabilidad](https://github.com/H4ckd4ddy/bypass-sentry-safe) muestra dónde encontrarlos.

| Pin GPIO del Flipper | Cable de la caja fuerte |
|---|---|
| 8 (GND) | negro |
| 15 (C1) | verde |

Los números de pin son los impresos en el conector GPIO del Flipper; consulta [Patillaje GPIO](/es/gpio/pinout).

## Uso

1. Abre la app **Sentry Safe** desde `Main Menu → Apps` (es un plugin de GPIO, búscalo en la carpeta GPIO).
2. Conecta los cables como se indica en la pantalla de la app y en la tabla de arriba.
3. Pulsa <kbd>OK</kbd> (enter).
4. Abre la caja fuerte.

## Resolución de problemas

- No pasa nada: comprueba que GND va realmente al cable negro y C1 (pin 15) al cable verde, y que el contacto es
  firme.

## Páginas relacionadas

- [Patillaje GPIO](/es/gpio/pinout)
- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
