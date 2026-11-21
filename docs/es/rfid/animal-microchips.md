---
title: Microchips de animales
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Microchips de animales (FDX-B, FDX-A)

Los microchips de mascotas son transpondedores RFID del tamaño de un grano de arroz implantados bajo la piel. Cuando un
lector los alimenta, envían un ID que se puede consultar en las bases de datos de recuperación de mascotas. Flipper
Zero lee los dos tipos LF más habituales:

| Tipo | Nombre en el Flipper | Descripción |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, ID de 15 dígitos; el tipo más habitual; algunos chips informan también de la temperatura corporal |
| **FDX-A** | `FDX-A` (FECAVA) | Chips antiguos de 10 dígitos, no ISO |

La mayoría de los chips de animales funcionan a **134,2 kHz**, mientras que la antena del Flipper está sintonizada a
125 kHz, por lo que la distancia de lectura es corta: alrededor de **1 cm**. Los microchips en el rango de
110–140 kHz se pueden leer, pero hay que acercarse más.

::: tip Unleashed
La documentación oficial te indica usar *Read ASK*. Unleashed genera un campo real de **134,2 kHz** para estos chips:
- **Read** ejecuta ahora una tercera pasada, **134kHz**, después de ASK y PSK;
- `Extra Actions → Read FDX-B (Animals)` se mantiene a 134,2 kHz todo el tiempo — la mejor opción para chips débiles;
- el nombre del país para FDX-B se busca en `/ext/lfrfid/assets/iso3166.lfrfid`.
:::

## Leer el chip de una mascota

1. Ve a `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. La pantalla muestra *Reading FDX-B*.
2. Localiza el chip:
   - perros y gatos: normalmente bajo la piel **entre los omóplatos**; en Europa continental, a menudo **a media
     altura del lado izquierdo del cuello**. Los chips pueden migrar ligeramente;
   - palpa con suavidad con la punta de los dedos buscando un objeto firme con forma de grano de arroz y después
     coloca el centro de la parte trasera del Flipper justo encima.
3. Mantén el Flipper quieto unos **3 segundos** en cada punto. Si no pasa nada, desplázalo a pequeños pasos por la
   zona, después gíralo 90° y repite.
4. Fíjate en el LED: amarillo/verde significa que se está captando señal — quédate ahí.
5. Una vez decodificado aparece la pantalla de resultado. <kbd>→</kbd> **More → Save** para conservarlo.

## Qué muestra el Flipper para FDX-B

| Campo | Significado |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | Código de país de 3 dígitos (ISO 3166-1 numérico) o del fabricante + ID nacional de 12 dígitos — el número de 15 dígitos que hay que consultar |
| Country Code / Country | El código y su nombre según la tabla ISO 3166 |
| Temperature | En los chips con termómetro, en °C y °F; `---` si no está presente |
| Animal | Indicador de aplicación animal |
| Visual Start Digit, Replacement Number, User Info, RFU | Campos de cabecera de la trama ISO |
| Data Block | Present / Absent — bloque de datos adicional (por ejemplo, la temperatura) |
| RUDI Bit | Yes / No |

FDX-A muestra un `ID` de 10 dígitos hexadecimales y `Parity`.

::: warning
La temperatura del chip no sustituye a un termómetro adecuado.
:::

## Consultar el ID

Introduce el ID de 15 dígitos en una base de datos de recuperación de mascotas, por ejemplo:
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — EE. UU. y Canadá
- [Europetnet](https://www.europetnet.com/) — Europa
- [PETMAXX](http://www.petmaxx.com/) — ámbito mundial

O pregunta a tu veterinario o al registro de mascotas local.

## Si no se encuentra el chip

- Está fuera de alcance — usa pasos más pequeños y mantén el Flipper más tiempo en cada punto.
- El chip ha migrado — explora una zona más amplia.
- Hay metal o electrónica cerca — aléjate de ellos.
- El animal puede llevar un chip de 13,56 MHz — prueba con [NFC](/es/nfc/read).
- Chip no compatible — pide a un veterinario que lo escanee.

Las llaves FDX-B también se pueden [emular o escribir](/es/rfid/write) (chips vírgenes T5577 y EM4305, que existen
también como tags de cristal), por ejemplo para probar una puerta para mascotas.

## Páginas relacionadas

- [Lectura](/es/rfid/read) · [Protocolos](/es/rfid/protocols) · [Escritura](/es/rfid/write)
