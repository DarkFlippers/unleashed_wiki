---
title: Distribuciones de teclado
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Distribuciones de teclado para Bad USB

Un teclado USB no envía caracteres, envía **posiciones de tecla**. El ordenador las convierte en caracteres según
*su* distribución de teclado. Por eso, para escribir `z` en un PC alemán (QWERTZ), el Flipper tiene que pulsar la
tecla que en un teclado estadounidense es `y`. Un **fichero de distribución** (`.kl`) le indica a Bad USB qué tecla
(y qué modificador) produce cada carácter en la distribución de destino.

::: tip Unleashed
Las distribuciones de teclado para Bad USB provienen de [rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)
y forman parte de Unleashed. El comando `DUCKY_LANG` por script es una novedad de Unleashed (PR #1224).
:::

## Distribuciones disponibles

Ficheros en `/ext/badusb/assets/layouts/` (31 en la compilación actual):

| Fichero | Distribución |
|---|---|
| `en-US.kl` | Inglés (EE. UU.), la **predeterminada** y la de reserva integrada |
| `en-UK.kl` | Inglés (Reino Unido) |
| `de-DE.kl`, `de-DE-mac.kl` | Alemán (Alemania), PC y Mac |
| `de-CH.kl` | Alemán (Suiza) |
| `fr-FR.kl`, `fr-FR-mac.kl` | Francés (Francia), PC y Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | Francés (Bélgica, Canadá, Suiza) |
| `es-ES.kl`, `es-LA.kl` | Español (España, Latinoamérica) |
| `it-IT.kl`, `it-IT-mac.kl` | Italiano, PC y Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portugués (Portugal, Brasil) |
| `nl-NL.kl` | Neerlandés |
| `da-DA.kl` | Danés |
| `nb-NO.kl` | Noruego |
| `sv-SE.kl` | Sueco |
| `fi-FI.kl` | Finés |
| `cz_CS.kl` | Checo |
| `sk-SK.kl` | Eslovaco |
| `hu-HU.kl` | Húngaro |
| `hr-HR.kl` | Croata |
| `si-SI.kl` | Esloveno |
| `ba-BA.kl` | Bosnio |
| `tr-TR.kl` | Turco |
| `ja-JP.kl` | Japonés |
| `dvorak.kl` | Dvorak (EE. UU.) |
| `colemak.kl` | Colemak |

No hay distribución rusa ni cirílica: el formato solo puede describir caracteres ASCII (véase más abajo).

## Elegir una distribución

**De forma global** (para todos los scripts): en la pantalla del script pulsa <kbd>←</kbd> **Config → Keyboard Layout (global)**
y elige un fichero `.kl`. La elección se guarda en `/ext/badusb/.badusb.settings` y se muestra entre paréntesis en la
pantalla del script, por ejemplo `(de-DE)`. Si el fichero guardado falta o está corrupto, se usa `en-US`.

![Menú Config de Bad USB; Keyboard Layout (global) es el primer elemento](/screens/badusb/config.png)

**Por script**: pon `DUCKY_LANG <nombre>` al principio del script:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<nombre>` es el nombre del fichero sin `.kl`. Alias: `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Se aplica a partir de esa línea y se restablece a la distribución global al comienzo de cada ejecución.
- Un nombre desconocido o inválido recurre a la distribución integrada `en-US` sin detener el script.

## Lo que una distribución NO cambia

- Solo el texto de `STRING` / `STRINGLN` y las teclas de un solo carácter (`CTRL c`, `HOLD a`…) pasan por la
  distribución. Las teclas con nombre (`ENTER`, `F5`, flechas…) son iguales en todas partes.
- `ALTCHAR` / `ALTSTRING` no usan la distribución en absoluto; escriben los caracteres por su código mediante
  `ALT`+teclado numérico, y por eso funcionan con cualquier distribución en Windows.
- La distribución debe coincidir con el **idioma de entrada activo en el anfitrión**. En un PC con varios idiomas
  (por ejemplo inglés y ruso) cambia el anfitrión al idioma de la distribución antes de ejecutar, o `STRING`
  escribirá letras cirílicas.

## Formato del fichero (`.kl`)

Un fichero `.kl` es una tabla binaria de exactamente **256 bytes**: 128 entradas de 2 bytes (`uint16` little-endian),
una por cada código ASCII de 0 a 127.

- **Byte bajo**: el código de uso HID de la tecla que se debe pulsar (por ejemplo `0x1F` = la tecla `2`).
- **Byte alto**: los bits de modificador que deben mantenerse pulsados con ella:

| Bit (byte alto) | Modificador |
|---|---|
| `0x01` | Ctrl izquierdo |
| `0x02` | Shift izquierdo |
| `0x04` | Alt izquierdo |
| `0x08` | GUI izquierdo |
| `0x10` | Ctrl derecho |
| `0x20` | Shift derecho |
| `0x40` | Alt derecho (AltGr) |
| `0x80` | GUI derecho |

Ejemplo de `de-DE.kl`: la entrada de `"` (ASCII 34) es `1F 02`, es decir Shift + `2`, que es donde está la comilla
doble en un teclado alemán.

Como la tabla solo tiene 128 entradas, **únicamente se puede escribir ASCII**; un `STRING` con cualquier byte ≥ 128
(acentos UTF-8, cirílico, emoji) detiene el script con *"Native .kl supports ASCII, not UTF-8"*. Los nombres de
fichero pueden contener letras, dígitos, `-` y `_` (máximo 32 caracteres antes de `.kl`).

Para crear tu propia distribución, sigue las instrucciones de
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) y copia el fichero
resultante a `/ext/badusb/assets/layouts/`.

## Páginas relacionadas

- [Formato de los scripts](/es/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Uso de Bad USB](/es/badusb/usage)
- [Ejemplos](/es/badusb/examples)
