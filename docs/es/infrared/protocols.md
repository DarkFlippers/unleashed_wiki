---
title: Protocolos
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Protocolos IR compatibles

La biblioteca de infrarrojos (`lib/infrared/encoder_decoder/`) contiene un decodificador y un codificador para cada
protocolo de la lista. Una señal que encaja con uno de ellos se guarda como `type: parsed` (protocolo + dirección +
comando); todo lo demás se guarda como `type: raw` y se reproduce como temporizaciones. La lista y los valores de
esta página están tomados del código fuente del firmware.

::: tip Unleashed
**RCA** es una aportación de Unleashed. Los demás protocolos son comunes con el firmware oficial.
:::

## Tabla de protocolos

| Protocolo (valor de `protocol:`) | Familia | Bits de dirección | Bits de comando | Portadora |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (extendido, sin bytes invertidos) | 16 | 16 | 38 kHz |
| `NEC42` | NEC de 42 bits | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC de 42 bits extendido | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 extendido | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC de 12 bits | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC de 15 bits | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC de 20 bits | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon…) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

El ciclo de trabajo de todos los codificadores integrados es del 33 %. El comando de la CLI `ir tx` acepta estos
mismos nombres (por ejemplo `ir tx NEC 0x04 0x08`) y son también lo que debe contener `protocol:` en un fichero `.ir`.

::: info Pioneer
El protocolo `Pioneer` está implementado en el firmware (y se usa en las bibliotecas de audio y de televisores)
aunque la lista del documento oficial *InfraredFileFormats* todavía no lo mencione.
:::

## Referencia de temporizaciones

Temporizaciones de pulso y silencio de los protocolos principales, tal como se definen en los codificadores (µs). La
tolerancia de decodificación es de ±200 µs en el preámbulo y de ±120 µs en los bits.

| Protocolo | Marca / silencio del preámbulo | Marca / silencio del bit 1 | Marca / silencio del bit 0 |
|---|---|---|---|
| NEC (todas las variantes) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 unidades de 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | ninguno (Manchester) | medio bit de 888 µs | |
| RC6 | 2666 / 889 | medio bit de 444 µs (Manchester) | |

## Qué significan estos números en la práctica

- **Aprendizaje:** el receptor integrado está ajustado a 38 kHz, pero los decodificadores de los protocolos de
  36 kHz (RC5, RC6) y 40 kHz (Sony SIRC, Pioneer) también están presentes, así que esos mandos se aprenden igualmente
  como señales decodificadas.
- **Guardado:** una señal decodificada es diminuta y robusta. Si una señal decodificada no funciona en tu aparato,
  apréndela como RAW (en modo depuración, `Learn New Remote RAW`; véase
  [Aprendizaje](/es/infrared/read#debug-mode-extras)).
- **Mandos desconocidos** (la mayoría de los de aire acondicionado: 181 de las 182 señales de `ac.ir` son RAW) no se
  decodifican en absoluto y se almacenan siempre como RAW. Las señales RAW pueden contener hasta 1024
  temporizaciones; las capturas RAW aprendidas se almacenan normalmente con `frequency: 38000` y
  `duty_cycle: 0.330000`.

## Páginas relacionadas

- [Formato de los ficheros IR](/es/infrared/file-format)
- [Aprender y enviar señales](/es/infrared/read)
- [Mandos universales](/es/infrared/universal-remotes)
