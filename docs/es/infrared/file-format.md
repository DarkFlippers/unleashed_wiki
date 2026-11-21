---
title: Formato de los ficheros IR
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Formato de los ficheros de infrarrojos (`.ir`)

Todos los datos IR del Flipper se guardan como texto plano en el Flipper Format (líneas `key: value`). La extensión
es siempre `.ir`. Hay tres variantes que se diferencian únicamente en la cabecera `Filetype` y en su finalidad.

| Filetype | Para qué sirve | Ubicación |
|---|---|---|
| `IR signals file` | Tus mandos (aprendidos, guardados desde un mando universal, descargados de la aplicación) | `/ext/infrared/` |
| `IR library file` | Bibliotecas de mandos universales | `/ext/infrared/assets/` |
| fichero de prueba (`.irtest`) | Pruebas unitarias de los decodificadores y codificadores | solo en el repositorio del firmware |

## Fichero de mando

### Ejemplo

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

El fichero contiene cualquier número de botones. Cada botón empieza por `name:`; una línea de comentario `#` entre
botones es solo para mejorar la legibilidad.

### Campos

| Campo | Se usa en | Tipo | Descripción |
|---|---|---|---|
| `name` | ambos | cadena | Nombre del botón. Solo ASCII imprimible. La interfaz del Flipper limita los nombres a 23 caracteres. |
| `type` | ambos | cadena | `parsed` o `raw`. |
| `protocol` | parsed | cadena | Nombre del protocolo, exactamente como en la [lista de protocolos](/es/infrared/protocols) (el comando `ir` de la CLI también lo imprime). |
| `address` | parsed | hex | Dirección, siempre de **4 bytes**, byte menos significativo primero: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Comando, siempre de **4 bytes**, byte menos significativo primero. |
| `frequency` | raw | uint32 | Frecuencia de la portadora en Hz, normalmente `38000`. Rango válido 10000-1000000. |
| `duty_cycle` | raw | float | Ciclo de trabajo de la portadora, normalmente `0.33`. Debe ser > 0 y ≤ 1. |
| `data` | raw | lista de uint32 | Temporizaciones en microsegundos entre cambios de nivel (marca, silencio, marca, …), separadas por espacios. **Máximo 1024** valores. |

### Valores válidos de `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` es una aportación de Unleashed. `Pioneer` existe en el firmware aunque el documento oficial del formato
todavía no lo recoja.
:::

### Edición a mano

- Mantén las dos líneas de cabecera (`Filetype`, `Version`) al principio.
- Cada botón necesita `name` y `type`, y después `protocol`/`address`/`command` o bien
  `frequency`/`duty_cycle`/`data`.
- Para fusionar dos mandos, copia los bloques de botones de un fichero al final del otro.
- Los bytes de dirección y comando deben seguir ocupando 4 bytes aunque el protocolo use menos bits; los bytes no
  utilizados son `00`.
- Si el Flipper dice *"Failed to load …"*, alguno de los campos está mal formado (por ejemplo una línea `data` RAW
  con más de 1024 valores o una frecuencia fuera de rango).

## Ficheros de biblioteca {#library-files}

Los ficheros de biblioteca usan exactamente la misma estructura; solo cambia la cabecera:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

El mando universal busca las señales **por nombre**, así que los nombres deben coincidir exactamente con los botones
de la biblioteca (véase la tabla de
[Contribuir con capturas](/es/infrared/captures#button-names-per-library)). Los modelos nuevos se añaden al final,
precedidos de un comentario `# Model: …`.

Un fichero de biblioteca no se puede abrir mediante `Saved Remotes`: la aplicación informa
*"Library file … can't be opened as a remote"*.

## Ficheros de prueba (`.irtest`)

Los usan únicamente las pruebas unitarias del firmware
(`applications/debug/unit_tests/resources/unit_tests/infrared` en el repositorio). Tienen el aspecto de un fichero de
mando, más un tipo `parsed_array` para secuencias completas de mensajes decodificados:

| Campo | Se usa en | Tipo | Descripción |
|---|---|---|---|
| `name` | ambos | cadena | Nombre de la señal; véase la nomenclatura más abajo. |
| `type` | ambos | cadena | `parsed_array` o `raw`. |
| `count` | parsed_array | uint32 | Número de mensajes del array, al menos 1. |
| `protocol`, `address`, `command` | parsed_array | | Como arriba, uno por mensaje. |
| `repeat` | parsed_array | bool | Si el mensaje es una repetición (botón mantenido). |
| `frequency`, `duty_cycle`, `data` | raw | | Como arriba. |

Los nombres siguen el patrón `<name><test_number>`: `decoder_input1` (entrada en bruto para el decodificador, que es
también la salida esperada del codificador), `decoder_expected1` (salida esperada del decodificador, que es también
la entrada del codificador) y `encoder_decoder_input1` (array decodificado que debe sobrevivir a un ciclo
codificar → decodificar). Cada protocolo debe tener un fichero de prueba de este tipo.

## Páginas relacionadas

- [Protocolos](/es/infrared/protocols)
- [Contribuir con capturas](/es/infrared/captures)
- [Aprender y enviar señales](/es/infrared/read)
