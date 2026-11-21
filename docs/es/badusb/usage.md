---
title: Uso de Bad USB
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Uso de Bad USB

Esta página recorre la ejecución de un script por USB y por Bluetooth, y explica cada elemento del menú **Config**.
Las etiquetas de menú y los mensajes se reproducen exactamente como aparecen en el firmware.

::: warning
Ejecuta scripts únicamente en ordenadores de tu propiedad o que tengas permiso para auditar. Lee el script antes de
ejecutarlo: hará exactamente lo que dice, con los permisos de tu usuario.
:::

## Antes de empezar

- Hace falta una tarjeta microSD con los recursos del firmware. Sin ella la aplicación muestra *"No SD card or app data found.
  This app will not work without required files."*
- Pon tu script (`.txt`) en `/ext/badusb/` (se admiten subcarpetas).
- **El modo USB se apodera del puerto USB del Flipper.** Si qFlipper o la [CLI](/es/dev/cli) están conectados por USB,
  la aplicación muestra *"Connection Is Active! Disconnect from PC or phone to use this function."* Cierra qFlipper primero.

## La pantalla principal

1. Abre `Main Menu → Bad USB`.
2. Elige un script en el explorador de ficheros. Se abre la pantalla del script.

La línea superior muestra el nombre del script; debajo, entre paréntesis, la distribución de teclado, `(default)` o
por ejemplo `(de-DE)`, y el tiempo transcurrido, o bien el PIN de emparejamiento en modo BLE. La imagen central
muestra un conector USB o un símbolo de Bluetooth.

![Pantalla del script en Bad USB: demo_windows cargado, 0/34 líneas, indicaciones Config / Run / BLE](/screens/badusb/script_ready.png)

| Estado | Texto en pantalla | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Inactivo / terminado / sin conexión | progreso o *Connect to device* | **Run** | **Config** | cambiar a **BLE** / **USB** |
| Esperando la conexión después de Run | *Will run on connect* | **Cancel** | | |
| En ejecución o dentro de un `DELAY` | `line/total`, porcentaje, `Delay Ns` | **Stop** | | **Pause** |
| En pausa | *Paused* | **End** | | **Resume** |
| Esperando en `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Error | *ERROR:* + `line N` + mensaje | | | |

Si pulsas **Run** antes de que el anfitrión haya reconocido el Flipper, la aplicación espera (*"Will run on connect"*)
y arranca el script automáticamente **1,5 s después de establecerse la conexión**, para que el anfitrión tenga
tiempo de instalar el teclado.

Mientras no haya ningún anfitrión conectado, el reloj de arena y *Connect to device* sustituyen al progreso:

![Bad USB esperando un anfitrión USB; la pantalla muestra Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> abandona la pantalla del script y vuelve al explorador de ficheros.

## Ejecutar por USB

1. Cierra qFlipper en el ordenador.
2. `Main Menu → Bad USB` → selecciona el script.
3. Comprueba que la pantalla muestre la imagen de **USB**; si no, pulsa <kbd>→</kbd> **USB**.
4. Opcional: <kbd>←</kbd> **Config → Keyboard Layout (global)** para que coincida con la distribución del ordenador
   (por defecto `en-US`).
5. Conecta el Flipper al ordenador con un cable USB.
6. Pulsa <kbd>OK</kbd> **Run**. El progreso `line/total` avanza hasta el 100 %.

![Bad USB ejecutando un script: 32 %, línea 12 de 34, indicaciones Stop y Pause](/screens/badusb/script_running.png)

![Bad USB en modo USB](/img/remote/d49323518c0b4b18.jpg)

## Ejecutar por Bluetooth (BLE)

1. Asegúrate de que el Bluetooth esté activado en el Flipper (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → selecciona el script.
3. Pulsa <kbd>→</kbd> **BLE**; aparece la imagen de Bluetooth. El Flipper empieza a anunciarse como teclado.
4. En el ordenador o el móvil abre los ajustes de Bluetooth y conéctate a **`BadUSB <nombre de tu Flipper>`** (el nombre por defecto).
5. Confirma el emparejamiento en los dos dispositivos. Con el modo de emparejamiento por defecto se muestra el mismo
   PIN en ambas pantallas; comprueba que coincida. El PIN aparece también en la pantalla del script.
6. Pulsa <kbd>OK</kbd> **Run**.
7. Para eliminar el emparejamiento más adelante: <kbd>←</kbd> **Config → Remove BLE Pairing**, y olvida también el
   dispositivo en el anfitrión.

![Bad USB en modo BLE](/img/remote/083420027c3f836c.jpg)

::: tip Identidad y emparejamiento independientes
En modo BLE el Flipper usa su **propia dirección MAC** (derivada de la MAC del Flipper) y su propio almacén de
emparejamientos, separado del perfil Bluetooth normal. Emparejar un ordenador con Bad USB no rompe por tanto el
emparejamiento con Flipper Mobile App. Al salir de la aplicación se restaura el perfil Bluetooth normal.
:::

## Scripts que cambian de modo por sí mismos

Si la **primera línea** de un script es un comando `ID` (USB) o `BLE_ID` / `BT_ID` (Bluetooth), la aplicación cambia
automáticamente a ese modo al abrir el script y aplica la identidad indicada. Aun así puedes cambiar a mano con
<kbd>→</kbd>. Véase [Formato de los scripts → Device ID](/es/badusb/script-format#device-id).

## Menú Config

<kbd>←</kbd> **Config** solo está disponible mientras el script no se está ejecutando. Su contenido depende del modo
de conexión activo.

### Común

| Elemento | Valores | Qué hace |
|---|---|---|
| **Keyboard Layout (global)** | explorador de ficheros | Selecciona un fichero `.kl` de `/ext/badusb/assets/layouts/`. Se aplica a todos los scripts que no fijen el suyo con `DUCKY_LANG`. Véase [Distribuciones de teclado](/es/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Lo mismo que <kbd>→</kbd> en la pantalla principal. La lista siguiente cambia en consecuencia. |

### Modo BLE

| Elemento | Valores | Qué hace |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | ON (por defecto): establece un vínculo con el anfitrión y lo recuerda, de modo que se reconecta sin emparejar de nuevo. OFF: emparejar cada vez. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo`: emparejar sin PIN. `PIN Type`: el Flipper muestra un PIN que tecleas en el anfitrión. `PIN Y/N` (por defecto): ambos muestran un PIN; confirma que coincide. |
| **Set Device Name** | texto | Nombre Bluetooth (*"Set BLE device name"*). Vacío = `BadUSB <nombre del Flipper>`. |
| **Set MAC Address** | 6 bytes | *"Set BLE MAC address"*. |
| **Randomize MAC Address** | acción | Genera una MAC estática aleatoria y muestra **Done**. Útil para presentarse como un teclado "nuevo". |
| **Restore BLE Defaults** | acción | Borra el nombre y la MAC, Persist Pairing ON, Pairing Mode `PIN Y/N`. |
| **Remove BLE Pairing** | acción | *"Unpair the Device?"* → **Unpair** olvida todos los anfitriones vinculados con Bad USB. |

### Modo USB

| Elemento | Valores | Qué hace |
|---|---|---|
| **Set Manufacturer Name** | texto | Cadena de fabricante USB (*"Set USB manufacturer name"*). |
| **Set Product Name** | texto | Cadena de producto USB (*"Set USB product name"*). |
| **Set VID and PID** | 4 bytes | *"Set USB VID:PID"*. Permite que el Flipper se presente con un identificador de fabricante/producto concreto. |
| **Randomize VID and PID** | acción | VID y PID aleatorios; muestra **Done**. |
| **Restore USB Defaults** | acción | Borra el VID/PID y los nombres: se usa la identidad de teclado por defecto del Flipper. |

Todo esto, junto con la distribución y el modo elegidos, se guarda en `/ext/badusb/.badusb.settings`. Una línea
`ID` / `BLE_ID` en un script sobrescribe la identidad solo para ese script.

## Resolución de problemas

| Problema | Qué probar |
|---|---|
| El texto escrito sale mal (`z` e `y` intercambiadas, símbolos erróneos) | La distribución de teclado del anfitrión no coincide con la de la aplicación. Elige la correcta en Config, o añade `DUCKY_LANG` al script. En un PC con varios idiomas de entrada, cambia el anfitrión al idioma de la distribución antes de ejecutar (por ejemplo inglés, no ruso). |
| Faltan caracteres | El anfitrión es demasiado lento. Añade `DEFAULT_STRING_DELAY 10` (o más) y `DELAY`s más largos después de abrir ventanas. |
| El script empieza antes de que la ventana esté abierta | Aumenta el `DELAY` después de `GUI r`, `ENTER` y similares. |
| *ERROR: line N* | La línea tiene un comando desconocido, una errata, un número mal formado o texto no ASCII. Los comandos **distinguen mayúsculas y minúsculas** (`STRING`, no `string`). Véase [Formato de los scripts](/es/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` contiene caracteres no ASCII (acentos, cirílico…). Usa `ALTSTRING`/`ALTCHAR` en Windows, o escribe ese texto de otra manera. |
| *Connection Is Active!* | Desconecta qFlipper / la CLI del puerto USB. |
| macOS abre el *Asistente de configuración del teclado* | Usa una línea `ID` con el VID/PID de un teclado de Apple (véase el ejemplo `demo_macos.txt`) o simplemente cierra el asistente. |
| El anfitrión BLE no encuentra el Flipper | Activa el Bluetooth en el Flipper, permanece en la pantalla del script en modo BLE y elimina los emparejamientos antiguos en ambos lados (`Remove BLE Pairing`). |

## Páginas relacionadas

- [Formato de los scripts](/es/badusb/script-format)
- [Ejemplos](/es/badusb/examples)
- [Distribuciones de teclado](/es/badusb/layouts)
