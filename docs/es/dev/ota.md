---
title: Actualizaciones OTA
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# Proceso de actualización OTA

Cómo instala el Flipper un paquete de actualización: qué ocurre en cada etapa, qué contiene el manifiesto de
actualización, qué significan los códigos de error `[XX-YY]` y cómo compilar tus propios paquetes.

Para la parte del usuario (instalar Unleashed con qFlipper, el instalador web o desde la tarjeta SD) consulta
[Actualizar](/es/start/updating). Si una actualización falla gravemente, consulta
[Recuperación](/es/start/recovery).

## Ejecutar código desde la RAM

El firmware tiene un modo de arranque especial que carga en la **RAM** una imagen de sistema preparada para ello y
salta a ella. El código que se ejecuta desde la RAM tiene acceso de escritura completo a toda la flash — algo
imposible mientras el firmware principal se ejecuta desde esa misma flash. El actualizador OTA usa este modo,
incluso para actualizar la pila de radio del segundo núcleo del MCU.

## Las tres etapas

### 1. Copia de seguridad del almacenamiento interno (`/int`)

`/int` es una partición de la flash del Flipper que ocupa todo el espacio que no usa el firmware. Un firmware nuevo
puede tener otro tamaño, así que instalarlo reparticionaría la flash y perdería los datos. Por eso, antes de nada, el
contenido actual de `/int` se guarda en un archivo `.tar` sin comprimir en la tarjeta SD.

### 2. Actualizar el dispositivo

El firmware principal carga el **actualizador** — una compilación adaptada del firmware — en la RAM y lo ejecuta. El
actualizador trabaja sobre la flash del sistema según lo que describa el manifiesto de actualización:

1. Si el paquete contiene una imagen de la **pila de radio**, su versión se compara con la instalada. Si no coinciden,
   la pila antigua se desinstala y la nueva se escribe e instala. La instalación la realiza el **FUS** propietario de
   ST ejecutándose en el Core2 e implica varios reinicios.
2. Se validan y corrigen los **Option Bytes** (la configuración de bajo nivel del MCU).
3. Se carga el archivo `.dfu` del firmware, se comprueba su integridad con CRC32, se escribe en la flash y se
   verifica.

### 3. Restaurar el almacenamiento interno y actualizar los recursos

El sistema se reinicia con el nuevo firmware, restaura el contenido de `/int` del que hizo copia y, si el paquete
contiene un archivo de recursos, lo extrae en la tarjeta SD.

## Manifiesto de actualización

Cada paquete viene con un manifiesto (el archivo `.fuf`) en Flipper File Format — un archivo de texto plano con pares
clave-valor.

### Campos obligatorios (en este orden)

| Clave | Significado |
|---|---|
| `Filetype` | La cadena constante `Flipper firmware upgrade configuration` |
| `Version` | Versión del manifiesto, actualmente `2` |
| `Info` | Descripción libre del paquete |
| `Target` | Revisión de hardware para la que está compilado el paquete |
| `Loader` | Nombre del archivo del cargador de segunda etapa que se ejecuta desde la RAM |
| `Loader CRC` | CRC32 del archivo del cargador, en hexadecimal **little-endian** |

### Campos opcionales

Pueden estar vacíos — el actualizador omite entonces las operaciones correspondientes.

| Clave | Significado |
|---|---|
| `Radio` | Nombre del archivo de la imagen de la pila de radio (lo proporciona ST) |
| `Radio address` | Dirección en la que instalar la pila de radio (según las notas de release de ST) |
| `Radio version` | Versión mayor, menor y de subnivel, rama, release y tipo de pila, empaquetados en 6 bytes hexadecimales |
| `Radio CRC` | CRC32 de la imagen de radio |
| `Resources` | Nombre del archivo con los recursos de la tarjeta SD — `resources.ths`, un tarball comprimido con heatshrink (consulta [Formato tarball heatshrink](/es/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Valores de referencia para validar y corregir los option bytes |

## Códigos de error

El proceso está diseñado para ser lo más tolerante a fallos posible: ninguna operación arriesgada empieza antes de
haber validado todos los datos relacionados, de modo que el dispositivo no se queda a medio actualizar ni se vuelve
inservible. Si algo va mal, el actualizador te permite volver a intentarlo y muestra un código de error `[XX-YY]`:
`XX` es la operación que ha fallado y `YY`, el progreso o el detalle en el que ha fallado.

| Etapa | XX | YY | Significado |
|---|--:|---|---|
| Carga del manifiesto de actualización | **1** | **13** | El actualizador informa de una versión de hardware incompatible |
| | | **20** | No se ha podido obtener la ruta del manifiesto guardado |
| | | **30** | No se ha podido cargar el manifiesto |
| | | **40** | Versión del paquete de actualización no compatible |
| | | **50** | El paquete tiene un objetivo de hardware distinto |
| | | **60** | Falta el archivo DFU |
| | | **80** | Falta el archivo de firmware de radio |
| Copia de seguridad de la configuración | **2** | **0-100** | Error de lectura/escritura del sistema de archivos |
| Comprobación del firmware de radio | **3** | **0-99** | Error al leer el archivo de firmware de radio |
| | | **100** | CRC incorrecto |
| Desinstalación del firmware de radio | **4** | **0** | Error del comando SHCI Delete |
| | | **80** | Error al esperar el estado del comando |
| Escritura del firmware de radio | **5** | **0-100** | Error de lectura/escritura de un bloque |
| Instalación del firmware de radio | **6** | **10** | Error del comando SHCI Install |
| | | **80** | Error al esperar el estado del comando |
| El Core2 está ocupado | **7** | **10** | No se ha podido arrancar el C2 |
| | | **20** | No se ha podido pasar el C2 al modo FUS |
| | | **30** | Error en una operación del FUS |
| | | **50** | No se ha podido pasar el C2 al modo de pila |
| Validación de los option bytes | **8** | **yy** | Código del option byte |
| Comprobación del archivo DFU | **9** | **0** | Error al abrir el archivo DFU |
| | | **1-98** | Error al leer el archivo DFU |
| | | **99-100** | Archivo DFU corrupto |
| Escritura de la flash | **10** | **0-100** | Error de lectura/escritura de un bloque |
| Validación de la flash | **11** | **0-100** | Error de lectura/escritura de un bloque |
| Restauración de la configuración | **12** | **0-100** | Error de lectura/escritura del sistema de archivos |
| Actualización de los recursos | **13-15** | **0-100** | Error de lectura/escritura de la tarjeta SD |

::: tip Qué hacer ante un error
- **1-50 / 1-13** — el paquete es para otro objetivo de hardware: descarga el correcto.
- **2, 12, 13-15** — problema con la tarjeta SD: revísala o reformatéala y vuelve a copiar el paquete.
- **3-100, 9-99/100** — archivos corruptos: vuelve a descargar el paquete.
- Reintenta primero — el actualizador está pensado para eso. Si el Flipper no arranca en absoluto, usa
  [Recuperación](/es/start/recovery).
:::

## Compilar paquetes de actualización

Asegúrate de pasar `DEBUG=0` — consulta [Compilar el firmware](/es/dev/build).

**Paquete completo** — firmware, pila de radio y recursos de la tarjeta SD:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Paquete mínimo** — solo el firmware:

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

El resultado queda en `dist/<target>-<cfg>/` como una carpeta `f7-update-<suffix>` y un
`flipper-z-f7-update-<suffix>.tgz`.

### Elegir otra pila de radio

Los paquetes usan por defecto la pila **Bluetooth Light**. Si tu firmware admite otra pila, pasa su tipo y su
binario:

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` debe apuntar a un archivo de `scripts/` con datos de referencia de los Option Bytes que correspondan
a ese tipo de pila. En algunos casos también hay que confirmarlo con `COPRO_DISCLAIMER=...` en la línea de comandos.

### Paquetes parciales

Llama directamente a `scripts/update.py` para contenidos personalizados. Por ejemplo, un paquete que solo instala la
pila BLE FULL:

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

Consulta `scripts/update.py generate --help` para ver todas las opciones.

## Instalar un paquete desde la CLI

Copia la carpeta del paquete descomprimido a la tarjeta SD y ejecuta:

```
update install /ext/update/f7-update-local/update.fuf
```

La [CLI](/es/dev/cli#update) ofrece también `update backup` y `update restore` para el almacenamiento interno.

## Páginas relacionadas

- [Actualizar el firmware](/es/start/updating)
- [Recuperación](/es/start/recovery)
- [Formato tarball heatshrink](/es/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/es/dev/fbt)
