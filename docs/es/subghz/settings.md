---
title: Radio Settings
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings

`Main Menu → Sub-GHz → Radio Settings` contiene los ajustes que afectan a toda la aplicación Sub-GHz: qué radio se
usa, la potencia de transmisión, el nombrado de ficheros y el comportamiento del contador rodante. Los ajustes de
recepción (frecuencia, modulación, salto, filtros) están en `Read → Config`; véase [Read](/es/subghz/read#config).

::: tip Unleashed
En el firmware original este menú solo permite cambiar entre el módulo interno y el externo. Unleashed añade
**TX Power**, **Protocol Names**, **Counter Incr.** y, en modo depuración, **Ext Amp & LEDs** y **Debug Pin**.
:::

## Elementos del menú

![Radio Settings: Module, TX Power, Protocol Names y Counter Incr.](/screens/subghz/radio_settings.png)

| Elemento | Valores | Qué hace |
|---|---|---|
| `Module` | `Internal`, `External` | Radio usada para recibir y transmitir. `External` solo se ofrece cuando se detecta un CC1101 externo en el GPIO; si no responde, el Flipper vuelve a `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Potencia de transmisión. `Preset` = lo que defina el preset de modulación (por defecto). Los valores bajos resultan prácticos para pruebas a corta distancia |
| `Protocol Names` | `OFF` / `ON` | Con `ON`, los nombres de fichero generados automáticamente contienen el nombre del protocolo + la marca de tiempo, en lugar de solo una marca de tiempo o un nombre aleatorio |
| `Counter Incr.` | `+1`, `+2`, `+3` (normal) | Cuánto se incrementa el contador rodante por transmisión en los protocolos dinámicos. Por defecto `+1` |

Elementos adicionales en **modo depuración** (`Settings → System → Debug → ON`):

| Elemento | Valores | Qué hace |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Lista completa de pasos del contador para experimentar: saltos grandes, `OVFL` (paso 65535), `OFEX` (modo especial), `No` (el contador no cambia) y pasos negativos |
| `Ext Amp & LEDs` | `ON` / `OFF` | Controla el pin del amplificador y de los LED de los módulos externos (GPIO PC3, como en los módulos E07). Por defecto `ON`. Desactívalo si tu módulo usa ese pin para otra cosa |
| `Debug Pin` | `OFF` / `17(1W)` | Replica la señal de datos de la radio en el pin 17 del GPIO (1-Wire), para desarrollar protocolos con un analizador lógico |

`TX Power`, `Protocol Names` y `Ext Amp & LEDs` se guardan de inmediato (en
`/ext/subghz/assets/last_subghz.settings`). `Counter Incr.` no se guarda: se mantiene hasta que el Flipper se
reinicia y entonces vuelve a `+1`.

::: warning Incremento del contador
Los pasos de contador grandes o negativos son para experimentar **en tus propios receptores**. Adelantar mucho un
contador mueve de forma permanente el contador almacenado en el receptor más allá del de tu mando original;
retroceder hace que el receptor te ignore. Para convivir con el mando original usa los
[modos de contador](/es/subghz/counter-mode) o crea un mando nuevo con
[Add Manually](/es/subghz/add-manually). Contexto: [Códigos rodantes](/es/subghz/rolling-codes).
:::

## Otros ajustes que viven en la tarjeta SD

| Fichero | Finalidad | Detalles |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Frecuencias adicionales, lista del hopper, frecuencia por defecto, presets de modulación personalizados | [Frecuencias](/es/subghz/frequencies#adding-frequencies), [Formatos de fichero](/es/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Rango de frecuencias ampliado (fuera de especificación) | [Frecuencias](/es/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Tus propias claves de fabricante KeeLoq | [Formatos de fichero](/es/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/es/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Última frecuencia, modulación, filtros y disparador del analizador usados; lo escribe la aplicación | no lo edites a mano |

Los ficheros que terminan en `.example` son plantillas: renómbralos a `…_user` para activarlos. Los ficheros
`_user` no se sobrescriben con las actualizaciones de firmware.

## Resolución de problemas

- **`Module` solo muestra `Internal`**: no se ha detectado ningún CC1101 externo. Comprueba el cableado y la
  alimentación y vuelve a entrar en el menú. Véase [CC1101 externo](/es/subghz/external-cc1101).
- **Las señales salen débiles al enviar**: comprueba que `TX Power` no esté puesto en un valor negativo.
- **Los nombres de fichero son solo fechas**: activa `Protocol Names`.
- **No aparecen `Ext Amp & LEDs` ni `Debug Pin`**: solo se muestran en modo depuración.

## Relacionado

- [Read → Config](/es/subghz/read#config) · [Frecuencias](/es/subghz/frequencies) · [CC1101 externo](/es/subghz/external-cc1101)
- [Modos de contador](/es/subghz/counter-mode) · [Formatos de fichero](/es/subghz/file-format) · [Ajustes peligrosos](/es/start/dangerous-settings)
