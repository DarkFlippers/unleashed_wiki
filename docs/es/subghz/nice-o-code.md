---
title: Aplicación Nice O-Code
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Aplicación Nice O-Code

**Nice O-Code** (de @xMasterX) recupera el **código de instalador (IC)** de 16 bits de un mando Nice O-Code y guarda el mando como fichero `.sub`, bien como clon sin más, bien como **mando nuevo** de la misma instalación que puedes registrar en el receptor.

## Contexto

Nice O-Code es Nice FloR-S cifrado con un código de instalador: un valor compartido por todos los mandos de una instalación. El receptor solo acepta un mando que lleve su código de instalador. Una sola pulsación capturada no basta para encontrarlo, pero **cuatro o más pulsaciones** del mismo mando sí: solo el código correcto hace que todas las pulsaciones se decodifiquen con el mismo serial. La aplicación recopila pulsaciones y aplica fuerza bruta a los 65 536 códigos posibles en el propio Flipper.

Algunos mandos O-Code llevan además el **certificado** del receptor (un paquete más largo, de 112 bits, que solo se envía durante los veinte primeros usos del mando). Cuando la aplicación detecta uno, lo desenmascara en cuanto conoce el IC y lo muestra como `Cert`.

::: tip Unleashed
Nice O-Code es una aplicación de sistema integrada de Unleashed, y la aplicación Sub-GHz puede decodificar y enviar mandos O-Code en cuanto un fichero lleva el IC. `Add Manually` tiene las entradas correspondientes `Nice O-Code`, `Nice O-Code One` y `Nice O-Code+Crt`; véase [Add Manually](/es/subghz/add-manually) y [Programar un mando nuevo](/es/subghz/remote-prog).
:::

::: warning
Úsala únicamente con tu propia instalación. Un clon comparte el contador con el mando original y los dos entrarán en conflicto (véase [Códigos rodantes](/es/subghz/rolling-codes)).
:::

## Requisitos

- El fichero de claves de Nice FloR-S `/ext/subghz/assets/nice_flor_s` en la tarjeta SD (viene con el firmware). Sin él la aplicación informa `No rainbow table`.
- Un mando O-Code de la instalación que funcione. La aplicación escucha en **433.92 MHz AM650**, con la radio interna o una [externa](/es/subghz/external-cc1101) (`Int` / `Ext` en el encabezado).

## Capturar un mando

1. Abre `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Elige `Capture remote`. El estado muestra `Listening 433.92`.
3. Pulsa el botón del mando **4 veces o más, con pulsaciones cortas y sin mantenerlo**. Cada pulsación nueva muestra `Press N: …`; la línea `Presses n/4  Xpkt` y la barra de progreso se van llenando. Si el mando tiene certificado, la línea termina con `+Crt`.
4. Cuando se han reunido 4 pulsaciones aparece `Solve`: pulsa <kbd>OK</kbd>.
5. La pantalla muestra `Trying installer codes` con un contador hasta 65536. <kbd>←</kbd> (`Cancel`) lo detiene.
6. Si tiene éxito verás `IC XXXX`, `Serial XXXXXXX` y, si existe, `Cert XXXXXX`.

Estados que pueden aparecer durante la captura:

| Estado | Significado |
|---|---|
| `Not O-Code, ignored` | un paquete que no es O-Code (por ejemplo, un mando FloR-S normal) |
| `Same press, ignored` | repetición de una pulsación ya almacenada |
| `Need 4+ packets` | no hay pulsaciones suficientes para resolver |
| `Ambiguous, capture more` | encajan varios códigos: pulsa el mando unas cuantas veces más y vuelve a resolver |
| `No code fits, not O-Code?` | ningún código de instalador coincide: probablemente no es un mando O-Code, o se han mezclado pulsaciones de mandos distintos |

## Guardar

En la pantalla de resultados:

- <kbd>OK</kbd> (`Save`): un **clon** del mando capturado (nombre por defecto `NiceO`). Útil para pruebas, pero entra en conflicto con tu original por el contador.
- <kbd>→</kbd> (`New`): un **mando nuevo**: el mismo código de instalador, botón y certificado, pero con serial y contador propios (nombre por defecto `NiceO_new`). Este es el que hay que registrar en el receptor. El contador se fija cerca del de tu mando en uso, y ligeramente por debajo.

Ambos se escriben en `/ext/subghz/` después de ponerles nombre (`Name the .sub file`). Ábrelos en `Sub-GHz → Saved`.

Para registrar el mando nuevo, sigue el procedimiento de Nice FloR-S en [Programar un mando nuevo](/es/subghz/remote-prog). Un mando con certificado se da de alta por sí mismo: pulsa su tecla aproximadamente una vez por segundo, **10–15 veces seguidas**; la cancela se abre en torno a la décima pulsación.

## Decode RAW file

`Decode RAW file` ejecuta la misma recuperación sobre un `.sub` RAW grabado previamente con [Read RAW](/es/subghz/read-raw) (graba 4 pulsaciones separadas o más). Un fichero de clave se rechaza con `Not a RAW capture`. La barra de progreso muestra por dónde va dentro del fichero.

## Resolución de problemas

- **`No rainbow table`**: falta `/ext/subghz/assets/nice_flor_s`; reinstala el firmware con la tarjeta SD puesta, o restaura la carpeta de recursos.
- **Las pulsaciones no cuentan**: haz pulsaciones cortas y separadas; mantener el botón repite la misma pulsación.
- **Un receptor recién salido de fábrica ignora el mando O-Code**: un receptor virgen no tiene código de instalador; registra en su lugar un mando `Nice One` / `Nice FloR-S` normal con el botón (véase [Programar un mando nuevo](/es/subghz/remote-prog)).
- **El receptor rechaza el mando nuevo**: mantén el contador cerca del de tu mando en uso; no lo pongas a cero.

## Páginas relacionadas

- [Programar un mando nuevo](/es/subghz/remote-prog) · [Add Manually](/es/subghz/add-manually)
- [Códigos rodantes](/es/subghz/rolling-codes) · [Sistemas compatibles](/es/subghz/supported-systems)
