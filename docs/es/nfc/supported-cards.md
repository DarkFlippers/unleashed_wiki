---
title: Tarjetas compatibles (analizadores)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Tarjetas compatibles (analizadores)

Con muchas tarjetas el Flipper no se limita a volcar la memoria, sino que la **decodifica**: número de tarjeta,
saldo, viajes restantes, validez, datos de la habitación de hotel, figura de juguete… De eso se encargan los
**plugins de analizador**, pequeños ficheros `.fal` que la aplicación NFC carga de la tarjeta SD después de una
lectura correcta. Cuando un analizador reconoce la tarjeta, la pantalla de resultados muestra los datos
decodificados en lugar del resumen en bruto; **More** lleva al menú habitual.

Algunos analizadores llevan además las **claves** del sistema de la tarjeta (o una función de derivación de claves).
En las tarjetas MIFARE Classic eso significa que el Flipper lee la tarjeta **por completo sin ningún ataque de
diccionario**: el analizador comprueba primero que la tarjeta pertenece al sistema y después la lee con las claves
correctas.

::: tip Unleashed
Unleashed incluye muchos analizadores que no están en el firmware original, en particular para sistemas rusos y de
la CEI: Umarsh, Zolotaya Korona (y su versión Online), Kazan, Metromoney, la tarjeta social de Moscú, un Troika
rediseñado, Plantain, Troika+Plantain, los billetes de cercanías PPK, además de filamento de Bambu Lab, tarjetas de
salón recreativo Banapass/Aime/AIC, cabezales Sonicare y más (de @Leptopt1los, @assasinfil y muchos
colaboradores).
:::

## Lista de analizadores

Claves integradas = el analizador puede leer la tarjeta con sus propias claves (o con derivación de claves), sin
necesidad de diccionario.

### Transporte

| Tarjeta (tal como se muestra) | Protocolo | Región | Claves integradas | Qué muestra |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Moscú, Rusia | sí | datos de la aplicación de transporte |
| Plantain Card | MIFARE Classic | San Petersburgo, Rusia | sí | datos de la tarjeta, billete de cercanías PPK |
| Troika+Plantain | MIFARE Classic | Rusia | sí | ambas aplicaciones en una tarjeta |
| Social card (tarjeta social de Moscú) | MIFARE Classic | Moscú, Rusia | sí | número de tarjeta (OMC), validez |
| Kazan transport card | MIFARE Classic | Kazán, Rusia | sí | tipo de billete, saldo |
| Umarsh | MIFARE Classic | Rusia (sistemas regionales) | no (hace falta la clave B para los sectores 0, 8 y 12) | datos de la tarjeta |
| Zolotaya korona | MIFARE Classic | Rusia | no | datos de la tarjeta |
| Zolotaya korona (Online) | MIFARE Classic | Rusia | no | datos de la tarjeta y de la tarifa |
| SZPPK Accompany Card | MIFARE Classic | Rusia, cercanías (SZPPK) | sí | validez, estación, entrada/salida, contador de pasos |
| SKPPK Transport Card | MIFARE Classic | Rusia, cercanías (SKPPK) | sí | estación, último paso, estado, contador de pasos |
| SevPPK Transport Card | MIFARE Classic | Rusia, cercanías (SevPPK) | sí | estación, último paso, estado, contador de pasos |
| Metromoney | MIFARE Classic | Tiflis, Georgia | sí | datos del billete |
| CharlieCard | MIFARE Classic | Boston (MBTA), EE. UU. | sí | saldo, transacciones |
| Clipper | MIFARE DESFire | área de la bahía de San Francisco, EE. UU. | — | número de serie, saldo, viajes (operador, tarifa, fecha) |
| Ventra | MIFARE Ultralight | Chicago (CTA), EE. UU. | — | viajes restantes, caducidad |
| Tarjeta Bip! | MIFARE Classic | Santiago, Chile | sí | número de tarjeta, saldo |
| SmartRider | MIFARE Classic | Perth, Australia | sí | saldo, bonificación, número de serie |
| Opal | MIFARE DESFire | Sídney, Australia | — | saldo, última entrada y salida |
| myki | MIFARE DESFire | Melbourne, Australia | — | número de tarjeta |
| ITSO Card | MIFARE DESFire | Reino Unido | — | datos de la tarjeta |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, China | — | saldo, fecha de venta |
| All-In-One | MIFARE Ultralight | billete de transporte | — | número, viajes restantes |

### Acceso, hoteles, pago y servicios

| Tarjeta (tal como se muestra) | Protocolo | Qué es | Claves integradas | Qué muestra |
|---|---|---|---|---|
| HID Card | MIFARE Classic | credencial HID almacenada en una tarjeta Classic | sí | longitud en bits y valor de la credencial |
| Gallagher NZ | MIFARE Classic | control de acceso Gallagher (Nueva Zelanda) | — | credenciales (una tarjeta puede llevar varias) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | cerraduras de hotel Saflok | sí (KDF) | número de propiedad, ID de llave, registro de llave, nivel de acceso |
| H World Card | MIFARE Classic | llaves de hotel H World (China continental) | sí | número de habitación, fecha de entrada y de caducidad |
| CSC Service Works | MIFARE Classic | tarjeta monedero recargable de lavandería (EE. UU.) | — | saldo, última recarga, usos restantes |
| WashCity | MIFARE Classic | tarjeta de lavandería WashCity / MarkItaly (Europa) | sí | saldo en EUR |
| MiZIP Card | MIFARE Classic | llaves de máquinas expendedoras MiZIP | sí | UID, crédito, crédito anterior |
| Microel Card | MIFARE Classic | llaves de máquinas expendedoras Microel | sí (derivadas del UID) | UID, crédito, crédito anterior |
| HI! Card | MIFARE Classic | tarjeta HI! | sí | UID |
| MyKey | ST25TB | llaves de máquinas expendedoras MyKey | — | número de serie, estado virgen/bloqueado, LockID |
| EMV | EMV | tarjetas bancarias | — | véase [Tarjetas bancarias (EMV)](/es/nfc/emv) |

### Juegos, juguetes y otros

| Tarjeta (tal como se muestra) | Protocolo | Qué es | Claves integradas |
|---|---|---|---|
| Aime Card | MIFARE Classic | tarjeta de recreativos SEGA Aime (código de acceso) | sí |
| Banapass | MIFARE Classic | Bandai Namco Passport (código de acceso, valor) | sí |
| Amusement IC Card | FeliCa | tarjetas de recreativos (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | figuras de Skylanders (nombre del personaje) | sí |
| Disney Infinity | MIFARE Classic | figuras de Disney Infinity | sí (derivadas) |
| Bambu Lab Filament | MIFARE Classic 1K | etiquetas de bobinas de filamento de Bambu Lab (tipo, código de filamento, material, color…) | sí (derivadas) |
| Philips Sonicare head | MIFARE Ultralight | cabezales de cepillo de dientes Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | mensajes NDEF: URI (incluidos teléfono y correo), texto, MAC Bluetooth, contacto, Wi-Fi, SmartPoster | — |

El código fuente de todos los analizadores está en
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Algunos analizadores usan tablas de consulta de `/ext/nfc/assets/` (por ejemplo `skylanders.nfc`, `vendors.nfc`,
`sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` para los nombres de estación, y
`aid.nfc`/`country_code.nfc`/`currency_code.nfc` para EMV).

## Notas

- Un analizador de una tarjeta con «claves integradas» comprueba primero la tarjeta; si la comprobación falla
  (otras claves, sistema distinto) se ejecuta el ataque de diccionario normal.
- Algunos analizadores indican qué falta, por ejemplo *"Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A
  DICTIONARY ATTACK TO READ THE TICKET SECTORS"*.
- **"Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources."**: los ficheros `.fal` de
  la tarjeta SD no se corresponden con el firmware. Reinstala el firmware con la tarjeta SD puesta.
- Un analizador solo muestra datos. Cambiar un saldo en un volcado y emularlo es fraude en los sistemas de
  transporte y de pago.

## Relacionado

[Leer tarjetas](/es/nfc/read) · [Tarjetas bancarias (EMV)](/es/nfc/emv) · [MIFARE Classic](/es/nfc/mifare-classic) ·
[Tarjetas Moskvyonok](/es/nfc/moskvyonok)
