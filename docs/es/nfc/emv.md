---
title: Tarjetas bancarias (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Tarjetas bancarias (EMV)

Las tarjetas bancarias sin contacto y los monederos de móvil usan **EMV** por encima de ISO14443-4. El Flipper puede
leer la información **pública** que la tarjeta entrega a cualquier terminal y mostrarla de forma legible. No puede
leer claves secretas y **no puede emular ni clonar** una tarjeta bancaria: cada pago lo firma una clave que nunca
sale del chip.

::: tip Unleashed
El protocolo EMV y el analizador de datos públicos provienen de Unleashed (de @Leptopt1los y @wosk).
:::

## Leer una tarjeta bancaria

1. `Main Menu → NFC → Read`, y apoya la tarjeta (o un móvil desbloqueado con el monedero abierto) en la parte
   trasera del Flipper.
2. El resultado analizado muestra lo que la tarjeta ha revelado, por ejemplo:
   - la etiqueta o el nombre de la aplicación (por ejemplo, el sistema de pago), o simplemente `EMV`;
   - el número de tarjeta (PAN), agrupado de 4 en 4 dígitos;
   - `Cardholder name:` (la mayoría de las tarjetas modernas ya no lo envían);
   - las fechas `Effective:` / `Expires:` (en el formato de fecha de tu configuración regional);
   - `Country:` y `Currency:` de emisión;
   - `PIN attempts left:`;
   - `Mobile: yes` en los monederos de móvil o reloj;
   - *"No data was parsed"* si no ha llegado nada útil.
3. <kbd>→</kbd> **More** abre el menú: **Save**, **Transactions** (solo si la tarjeta ha devuelto un registro de
   transacciones) e **Info**.

La pantalla **Info** muestra la vista técnica: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` y `Last Online ATC` si está disponible.

## Transacciones

Algunas tarjetas conservan un registro breve de las transacciones recientes y lo entregan sin PIN.
`More → Transactions` lista cada entrada con su contador (ATC), importe, moneda, país y fecha y hora cuando
existen (`???` / `UNK` para los valores desconocidos).

## Nombres de países, monedas y aplicaciones

El analizador EMV traduce los códigos usando ficheros de consulta de la tarjeta SD:

- `/ext/nfc/assets/aid.nfc`: identificadores de aplicación → nombres;
- `/ext/nfc/assets/country_code.nfc`: códigos de país ISO;
- `/ext/nfc/assets/currency_code.nfc`: códigos de moneda ISO.

Cada fichero lleva la cabecera `Filetype: Flipper EMV resources`, `Version: 1`, y después líneas
`<código>: <nombre>`, por ejemplo `0985: PLN`. Véase el
[formato de fichero](/es/nfc/file-format#emv-resources).

## Qué no funciona y por qué

- **Emulación y pagos**: no es posible. La tarjeta calcula un criptograma para cada transacción con sus claves
  privadas.
- **Falta el número de tarjeta**: algunas tarjetas y la mayoría de los monederos de móvil entregan un número
  tokenizado, o nada sin un diálogo de terminal.
- **Tarjetas híbridas** (tarjeta bancaria + chip de transporte o de acceso): usa
  `Extra Actions → Read Specific Card Type` para leer la otra parte.

::: warning Privacidad
Un volcado EMV guardado puede contener el número de tu tarjeta y su fecha de caducidad. No lo compartas.
:::

## Relacionado

[Leer tarjetas](/es/nfc/read) · [Tarjetas compatibles](/es/nfc/supported-cards) · [Formato de los ficheros NFC](/es/nfc/file-format)
