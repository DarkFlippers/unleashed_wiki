---
title: Interfaz de línea de comandos (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Interfaz de línea de comandos (CLI)

El Flipper expone una consola de texto por USB serie. Desde ella puedes leer y enviar señales, ejecutar apps,
gestionar archivos, ver los logs, controlar el GPIO y los LED, chatear con otros Flippers por Sub-GHz y mucho más —
muy práctico para hacer scripts, depurar y desarrollar apps.

## Conectarse a la CLI

::: warning Cierra qFlipper primero
Solo un programa puede usar el puerto serie del Flipper a la vez. Cierra **qFlipper** (y también Flipper Lab u otros
terminales) antes de conectarte.
:::

La velocidad del puerto serie es de **230400** baudios (en USB CDC el valor se ignora casi siempre, pero algunos
terminales exigen indicarlo).

### Opción 1: Flipper Lab (navegador)

Funciona en Chrome, Edge u otro navegador basado en Chromium con soporte de Web Serial.

1. Conecta el Flipper por USB.
2. Abre [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Opción 2: terminal serie web (navegador)

1. Conecta el Flipper por USB y abre un navegador basado en Chromium.
2. Ve al [terminal serie web](https://googlechromelabs.github.io/serial-terminal/).
3. Pon **Baud rate** en **230400**, pulsa **Connect**, selecciona tu Flipper y pulsa **Connect**.

### Opción 3: terminal serie — macOS

1. Localiza el puerto:

   ```sh
   ls /dev/cu.*
   ```

   El Flipper aparece como `/dev/cu.usbmodemflip_NAME`, donde `NAME` es el nombre de tu Flipper.
2. Conéctate con **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Para salir: <kbd>Ctrl</kbd>+<kbd>A</kbd>, después <kbd>K</kbd> y después <kbd>Y</kbd>.
3. …o con **minicom** (instálalo con [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Para salir: <kbd>Esc</kbd>+<kbd>Z</kbd>, después <kbd>X</kbd> y después <kbd>Return</kbd>.

### Opción 3: terminal serie — Linux

1. Localiza el puerto:

   ```sh
   ls /dev/serial/by-id/
   ```

   Busca `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Si solo tienes un dispositivo serie, normalmente es
   también `/dev/ttyACM0`; qFlipper también muestra el nombre del puerto.
2. Conéctate:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   Para salir de screen: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Para salir de minicom:
   <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Si obtienes «permission denied» en Linux, añádete al grupo `dialout` (o `uucp` en algunas distribuciones) y vuelve a
iniciar sesión.
:::

### Opción 3: terminal serie — Windows

1. Instala [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Conecta el Flipper; en **Administrador de dispositivos → Puertos (COM y LPT)** anota su puerto COM
   (desconéctalo y vuelve a conectarlo para ver cuál aparece).
3. En PuTTY elige **Connection type: Serial**, en **Serial line** pon por ejemplo `COM3`, en **Speed** `230400`, y
   pulsa **Open**.

### Desde el árbol del firmware

Si tienes el código fuente del firmware, `./fbt cli` abre una sesión de CLI directamente; con uFBT usa `ufbt cli`.

**Resultado esperado:** un banner en ASCII art del Flipper, «Welcome to Flipper Zero Command Line Interface!», la
línea con la versión del firmware y un prompt `>:`.

## Comandos integrados y externos

Ejecuta `help` o `?` para listar los comandos disponibles en tu dispositivo.

::: tip Unleashed / nueva arquitectura de la CLI
La mayoría de los comandos de radio y de periféricos (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`,
`crypto`, `js`, `gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) son **plugins externos de la CLI** que se
cargan desde la carpeta `/ext/apps_data/cli/plugins` de la tarjeta SD (archivos con el prefijo `cli_`). Sin tarjeta
SD — o con una dañada — solo quedan los comandos del núcleo. Después de copiar o actualizar plugins, ejecuta
`reload_ext_cmds` en lugar de reiniciar.
:::

### Resumen de comandos

| Comando | Descripción |
|---|---|
| `!` | Alias de `info device` |
| `?`, `help` | Lista los comandos disponibles |
| `bt` | Herramienta de pruebas del núcleo de radio (BLE) — versión de HCI y, en modo de depuración, pruebas de portadora y de paquetes |
| `buzzer` | Reproduce un tono o una nota en el altavoz piezoeléctrico |
| `crypto` | Aprovisionamiento de claves en el secure enclave y cifrado/descifrado AES |
| `date` | Muestra o ajusta la fecha y la hora |
| `device_info` | Alias de `info device` (obsoleto) |
| `echo` | Devuelve tal cual los bytes recibidos (se usa para pruebas de rendimiento); se detiene con <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Sale del shell (útil en subshells como `nfc`) |
| `factory_reset` | Restablece los ajustes de fábrica; los datos de la tarjeta microSD se conservan |
| `free` | Información del asignador de heap — perfilado general de memoria |
| `free_blocks` | Bloques libres del heap y sus tamaños — para estimar la fragmentación |
| `gpio` | Fija el modo, escribe o lee pines GPIO |
| `i2c` | Escanea el bus I2C en busca de dispositivos |
| `ikey` | Lee, emula y escribe llaves iButton |
| `info` | Información detallada del dispositivo y de la alimentación |
| `input` | Muestra eventos de botón e inyecta pulsaciones |
| `ir` | Recibe, envía y decodifica señales de infrarrojos; mandos universales |
| `js` | Ejecuta un archivo JavaScript; la salida de la consola va a la CLI |
| `led` | Controla el LED RGB y la retroiluminación de la pantalla |
| `loader` | Lista, abre y cierra apps |
| `log` | Muestra el log del sistema |
| `neofetch` | Información del sistema, como `neofetch` en Linux |
| `nfc` | Subshell de NFC: dump, emulate, raw, APDU, scanner |
| `onewire` | Escanea el bus 1-Wire (pines de iButton) |
| `power` | Apaga, reinicia, reinicia en DFU, activa los 5 V / 3,3 V del GPIO |
| `reload_ext_cmds` | Recarga la lista de comandos externos desde la tarjeta SD |
| `rfid` | Lee, escribe y emula tarjetas de 125 kHz; herramientas RAW |
| `sleep` | Espera un tiempo dado, por ejemplo `sleep 5s` (útil en scripts) |
| `start_rpc_session` | Pasa la CLI al modo RPC con protobuf (lo usan qFlipper y las apps; normalmente no es necesario) |
| `storage` | Comandos del sistema de archivos |
| `subghz` | Herramientas de Sub-GHz: rx/tx, RAW, decodificación, chat |
| `sysctl` | Ajustes del sistema: modo de depuración, seguimiento del heap |
| `top` | Lista en vivo de los hilos (como el `top` de Linux); <kbd>Ctrl</kbd>+<kbd>C</kbd> para salir |
| `update` | Instala un paquete de actualización, hace copia de seguridad o restaura el almacenamiento interno |
| `uptime` | Tiempo desde el último arranque |
| `vibro` | Activa o desactiva el motor de vibración |
| `unit_tests` | Solo en la compilación de firmware `unit_tests` — consulta [Pruebas unitarias](/es/dev/unit-tests) |

## Leer los logs {#reading-logs}

1. Conéctate a la CLI.
2. Inicia el registro en el nivel que necesites:

   | Comando | Qué muestra |
   |---|---|
   | `log` | El nivel actual según los ajustes del sistema |
   | `log error` | Solo errores críticos y mensajes importantes |
   | `log warn` | Avisos y errores no críticos, más `error` |
   | `log info` | Información no crítica, más `warn` |
   | `log default` | El nivel por defecto del sistema (= `info`) |
   | `log debug` | Información de depuración, más `info` (afecta al rendimiento) |
   | `log trace` | Trazas del sistema, más `debug` (afecta al rendimiento) |

   `log ?` imprime esta lista en el dispositivo.
3. Usa el Flipper — los mensajes aparecen en el terminal.
4. Detenlo con <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Chatear por Sub-GHz

Varios Flippers en la misma frecuencia pueden chatear a través de la CLI.

1. Cada participante se conecta a la CLI de su Flipper.
2. Ejecuta `subghz chat <frequency_in_hz> <device>`, por ejemplo:

   ```
   subghz chat 868150000 0
   ```

   - la frecuencia en Hz dentro de 299999755–348000000, 386999938–464000000 o 778999847–928000000;
   - dispositivo `0` = CC1101 interno, `1` = módulo CC1101 externo.
3. Escribe un mensaje y pulsa <kbd>Enter</kbd>.
4. Sal con <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
El firmware de fábrica solo transmite en las frecuencias permitidas en tu región; Unleashed elimina las restricciones
regionales de TX. Respeta la normativa de radio local.
:::

## Referencia de comandos

### bt

| Comando | Descripción |
|---|---|
| `bt hci_info` | Información HCI de Bluetooth |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Solo en modo de depuración.* Inicia la prueba de portadora de TX |
| `bt rx_carrier <channel:0-39>` | *Solo en modo de depuración.* Inicia la prueba de portadora de RX |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Solo en modo de depuración.* Inicia la prueba de paquetes de TX |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Solo en modo de depuración.* Inicia la prueba de paquetes de RX |

### buzzer

| Comando | Descripción |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Reproduce un tono |
| `buzzer note <note> <duration>` | Reproduce una nota; `s` significa sostenido, por ejemplo `cs3` = Do♯3; los bemoles no se admiten |

La duración acepta `ms`, `s`, `m`, `h`, por ejemplo `buzzer note cs3 500ms`.

### crypto

Cifra y descifra con claves almacenadas en el secure enclave del MCU.

| Comando | Descripción |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Cifra texto con AES256-CBC y lo imprime en hexadecimal |
| `crypto decrypt <key_slot> <iv_hex>` | Descifra el hexadecimal de vuelta a texto |
| `crypto has_key <key_slot>` | Comprueba si una ranura (1–100) contiene una clave |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **¡Irreversible!** Almacena una clave — no se puede eliminar |

- `key_slot`: las ranuras 1–11 vienen rellenas con las claves que usa el firmware.
- `iv_hex`: vector de inicialización de 16 bytes en hexadecimal.
- `key_type`: `master`, `simple` o `encrypted`; `key_size`: `128` o `256`.

### gpio

| Comando | Descripción |
|---|---|
| `gpio mode <pin_name> <0/1>` | Pone el pin como entrada (0) o salida (1) |
| `gpio set <pin_name> <0/1>` | Fija el valor del pin |
| `gpio read <pin_name>` | Lee el valor del pin |

Nombres de pin: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — consulta
[Patillaje GPIO](/es/gpio/pinout).

### ikey

| Comando | Descripción |
|---|---|
| `ikey read` | Lee una llave iButton |
| `ikey emulate <key_type> <key_data>` | Emula una llave |
| `ikey write Dallas <key_data>` | Escribe 8 bytes en una llave virgen compatible con Dallas |

Tipos de llave y longitud de los datos (hex): `Dallas` — 8 bytes, `Cyfral` — 2 bytes, `Metakom` — 4 bytes (debe
contener la paridad correcta).

### info

| Comando | Descripción |
|---|---|
| `info device` | Información del dispositivo (firmware, hardware, pila de radio, …) |
| `info power` | Información del sistema de alimentación |
| `info power_debug` | Información detallada de la alimentación |

### input

| Comando | Descripción |
|---|---|
| `input dump` | Imprime los eventos de botón |
| `input send <key> <type>` | Inyecta un evento; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

Una pulsación corta completa son tres comandos; si no, la entrada se descarta:

```
input send ok press
input send ok short
input send ok release
```

Para una pulsación larga usa `long` en lugar de `short`.

### ir

| Comando | Descripción |
|---|---|
| `ir rx` | Recibe y decodifica señales de IR |
| `ir rx raw` | Recibe en formato RAW |
| `ir tx <protocol> <address> <command>` | Envía un comando; dirección y comando en hexadecimal |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Envía datos RAW: frecuencia 10000–56000, ciclo de trabajo 0–100, máximo 512 muestras |
| `ir decode <input_file> [<output_file>]` | Decodifica un archivo con señales RAW |
| `ir universal list <remote_name>` | Lista las señales de un mando universal |
| `ir universal <remote_name> <signal_name>` | Envía una señal de un mando universal |

Protocolos: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Los nombres de los mandos universales se toman de los archivos de `/ext/infrared/assets/`. Unleashed incluye `tv`,
`audio`, `ac`, `projectors`, `fans` y `leds` (el firmware de fábrica tiene menos). Ejecuta `ir universal list tv`
para ver los nombres de señal válidos.
:::

### js

| Comando | Descripción |
|---|---|
| `js <path>` | Ejecuta un archivo JavaScript e imprime su salida de consola — consulta [JavaScript](/es/dev/js-about) |

### led

| Comando | Descripción |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Brillo de la componente roja / verde / azul del LED |
| `led bl <0-255>` | Brillo de la retroiluminación de la pantalla (`128` ≈ 50 %) |

Para un rojo puro: `led r 255`, `led g 0`, `led b 0`.

### loader

| Comando | Descripción |
|---|---|
| `loader list` | Lista las apps disponibles |
| `loader open <Application Name> [args]` | Abre una app por su nombre, opcionalmente con argumentos |
| `loader info` | Muestra el estado del cargador |
| `loader close` | Cierra la app en ejecución |
| `loader signal <signal> [arg_hex]` | Envía una señal con un argumento hexadecimal opcional |

Los argumentos que contienen espacios se pueden poner entre comillas:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` abre un **subshell**. Dentro: `help` / `?` lista los comandos, `<command> -h` muestra los detalles y `exit`
sale.

| Comando | Descripción |
|---|---|
| `dump -f <path>` | Volcar una tarjeta física a un archivo `.nfc`. Opciones: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Emular un archivo `.nfc` |
| `field` | Activa el campo de 13,56 MHz; <kbd>Ctrl</kbd>+<kbd>C</kbd> para detenerlo |
| `scanner` | Lista todos los protocolos que admite un tag; `-t` muestra el árbol de protocolos |
| `raw -p <protocol> -d <data>` | Envía bytes en bruto. Opciones: `-t <timeout>` (ciclos de portadora), `-k` mantiene el campo activo, `-c` añade el CRC, `-s` hace primero la activación y la anticolisión |
| `apdu -d <data> [<data2> ...]` | Envía APDU a tags ISO14443-4A/4B o ISO15693-3; `-p 4a`/`4b`/`15` fuerza el protocolo |
| `mfu info` | Información básica de un tag MIFARE Ultralight |
| `mfu rdbl -b <block>` | Lee un bloque |
| `mfu wrbl -b <block> -d <data>` | Escribe un bloque de 4 bytes |

Protocolos de `dump -p`: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`,
`des`, `slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Protocolos de `raw -p`: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Comando | Descripción |
|---|---|
| `onewire search` | Busca dispositivos 1-Wire |

### power

| Comando | Descripción |
|---|---|
| `power off` | Apagar |
| `power reboot` | Reiniciar |
| `power reboot2dfu` | Reiniciar en modo DFU |
| `power 5v <1/0>` | Activa o desactiva los 5 V en el pin 1 del GPIO |
| `power 3v3 <1/0>` | Activa o desactiva los 3,3 V en el pin 9 del GPIO (solo en modo de depuración) |

### rfid

| Comando | Descripción |
|---|---|
| `rfid read [normal/indala/ask134]` | Lee una tarjeta en modo ASK/PSK; el argumento opcional selecciona un modo de lectura (`ask134` — tags de animales a 134 kHz) |
| `rfid write <key_type> <key_data>` | Escribe en un T5577 |
| `rfid emulate <key_type> <key_data>` | Emula |
| `rfid raw_read <ask/ask134/psk> <filename>` | Guarda la señal en bruto en un archivo |
| `rfid raw_emulate <filename>` | Emula un archivo en bruto (depuración de protocolos) |
| `rfid raw_analyze <filename>` | Imprime un archivo en bruto e intenta decodificarlo (desarrollo de protocolos) |

Tipos de llave y longitud de los datos (bytes hex):

| Tipo | Bytes | Tipo | Bytes | Tipo | Bytes |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

Las rutas empiezan por `/int` (flash interna) o `/ext` (tarjeta SD).

| Comando | Descripción |
|---|---|
| `storage info /ext` | Información del sistema de archivos y espacio libre |
| `storage format /ext` | Formatea la tarjeta SD (pide confirmación) |
| `storage list <path>` | Lista un directorio |
| `storage tree <path>` | Lista recursivamente |
| `storage remove <path>` | Borra un archivo o un directorio **vacío** |
| `storage read <file>` | Imprime el tamaño y el contenido de texto |
| `storage read_chunks <file> <1-512>` | Imprime el contenido en bloques del tamaño indicado |
| `storage write <file>` | Añade al final el texto escrito en la CLI; <kbd>Ctrl</kbd>+<kbd>C</kbd> para terminar |
| `storage write_chunk <file> <1-512>` | Añade exactamente N bytes desde la CLI (la entrada no se muestra) |
| `storage copy <src> <dst>` | Copia un archivo |
| `storage rename <old> <new>` | Renombra o mueve |
| `storage mkdir <path>` | Crea un directorio |
| `storage md5 <file>` | Hash MD5 |
| `storage stat <path>` | Información de un archivo o directorio |
| `storage timestamp <file>` | Hora de la última modificación |
| `storage extract <archive.tar> <dir>` | Extrae un archivo `.tar` |

### subghz

| Comando | Descripción |
|---|---|
| `subghz chat <frequency> <device>` | Chatea con otros Flippers |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Transmite una llave (Princeton) |
| `subghz rx <frequency> <device>` | Recibe y decodifica |
| `subghz rx_raw <frequency>` | Recibe en RAW |
| `subghz decode_raw <path_to_raw_file>` | Decodifica un archivo RAW `.sub` e imprime los resultados |
| `subghz tx_from_file <path> <repeat> <device>` | Transmite un archivo `.sub` guardado |

Solo en modo de depuración:

| Comando | Descripción |
|---|---|
| `subghz tx_carrier <frequency>` | Transmite una portadora sin modular |
| `subghz rx_carrier <frequency>` | Recibe portadora (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Cifra un archivo de claves de fabricante de KeeLoq |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Cifra datos RAW |

`device`: `0` — CC1101 interno, `1` — CC1101 externo ([módulo externo](/es/subghz/external-cc1101)).
`te_us` — la duración base del pulso en µs.

Ejemplo: transmitir un archivo guardado 3 veces por la radio interna:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Comando | Descripción |
|---|---|
| `sysctl debug <0/1>` | Desactiva o activa el modo de depuración del sistema |
| `sysctl heap_track <none/main>` | Seguimiento de las asignaciones de heap del hilo principal de la app; las compilaciones de depuración (`DEBUG=1`) aceptan también `tree` (hilo principal + hilos hijos) y `all` |

### update

| Comando | Descripción |
|---|---|
| `update install /ext/path/to/update.fuf` | Verifica e instala un paquete de actualización (el manifiesto `.fuf` dentro de la carpeta del paquete descomprimido) |
| `update backup /ext/backup.tar` | Hace copia de seguridad del almacenamiento interno |
| `update restore /ext/backup.tar` | Restaura el almacenamiento interno desde una copia de seguridad |

Consulta [Actualizaciones OTA](/es/dev/ota).

### vibro

| Comando | Descripción |
|---|---|
| `vibro <1/0>` | Activa o desactiva el motor de vibración |

## Páginas relacionadas

- [Depurar apps](/es/dev/debugging)
- [Actualizaciones OTA](/es/dev/ota)
- [Pruebas unitarias](/es/dev/unit-tests)
- [qFlipper](/es/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire e ICODE son marcas registradas de NXP B.V. FeliCa es una marca
comercial de Sony Corporation.
