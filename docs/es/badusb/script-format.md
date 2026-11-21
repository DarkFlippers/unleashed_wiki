---
title: Formato de los scripts
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Formato de los scripts de Bad USB (DuckyScript)

Bad USB ejecuta scripts de texto plano con una sintaxis de **DuckyScript ampliado**. Los scripts clásicos de
USB Rubber Ducky 1.0 funcionan tal cual; además de eso, el Flipper añade identidad USB/BLE personalizada, entrada
con `ALT`+teclado numérico, `SYSRQ`, teclas multimedia, control del ratón, espera por pulsación de botón y más. Esta
referencia está verificada contra la tabla de comandos del firmware (`helpers/ducky_script_commands.c`,
`ducky_script_keycodes.c`).

## Reglas del fichero

- Texto plano, extensión **`.txt`**, sin compilación. Fin de línea `\n` o `\r\n`.
- Un comando por línea. Las líneas vacías se omiten; las líneas pueden sangrarse con espacios o tabuladores.
- Los comandos van en **MAYÚSCULAS y distinguen mayúsculas de minúsculas**: `STRING`, no `string`.
- El comando y su argumento se separan con un único espacio.
- Los comentarios son líneas completas que empiezan por `REM`. No hay comentarios al final de línea.
- El texto escrito (`STRING`, `STRINGLN`) debe ser **ASCII**. Los caracteres no ASCII detienen el script con
  *"Native .kl supports ASCII, not UTF-8"*.
- Ante un error el script se detiene y la pantalla muestra *ERROR:*, el número de línea y el motivo.

## Referencia rápida

| Comando | Argumento | Efecto |
|---|---|---|
| `REM` | texto | Comentario, se ignora. |
| `ID` | `VID:PID [Fabricante:Producto]` | Identidad USB, **solo en la primera línea**. |
| `BLE_ID` / `BT_ID` | `MAC Nombre` | Identidad Bluetooth, **solo en la primera línea**. |
| `DELAY` | ms | Espera una vez. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Espera antes de cada comando siguiente. |
| `STRING` | texto | Escribe el texto. |
| `STRINGLN` | texto | Escribe el texto y pulsa Enter. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Retardo entre pulsaciones solo para el **siguiente** `STRING`. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Retardo entre pulsaciones para **todos** los `STRING`. |
| `REPEAT` | n | Repite el comando anterior n veces más. |
| `DUCKY_LANG` | nombre de distribución | Cambia la distribución de teclado para el resto del script (Unleashed). |
| `HOLD` | tecla / botón del ratón | Pulsa y mantiene pulsado. |
| `RELEASE` | tecla / botón del ratón | Suelta una tecla mantenida. |
| `ALTCHAR` | código | Escribe un carácter con `ALT`+teclado numérico. |
| `ALTSTRING` / `ALTCODE` | texto | Escribe texto con `ALT`+teclado numérico. |
| `SYSRQ` | carácter | Combinación Magic SysRq. |
| `MEDIA` | tecla multimedia | Tecla de control de consumo (volumen, reproducción…). |
| `GLOBE` | tecla | Fn/Globo + tecla (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | ninguno | Pausa hasta que se pulse <kbd>OK</kbd> en el Flipper. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | ninguno | Clics de ratón. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Mueve el ratón. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Gira la rueda. |
| combinación de teclas | p. ej. `CTRL-ALT DELETE` | Pulsa y suelta varias teclas a la vez. |

## Comentarios

```text
REM This line is ignored
```

## Retardos

| Comando | Parámetro | Notas |
|---|---|---|
| `DELAY` | ms | Pausa única. |
| `DEFAULT_DELAY` | ms | Se añade antes de cada comando siguiente. Igual que `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Los retardos son tu principal herramienta de fiabilidad: el anfitrión necesita tiempo para abrir ventanas, así que
añade un `DELAY` después de `GUI r`, de `ENTER` en un lanzador, etc. Los retardos largos se muestran en la pantalla
como `Delay Ns`.

## Escribir texto

| Comando | Parámetro | Notas |
|---|---|---|
| `STRING` | texto | Escribe el texto literalmente, usando la distribución de teclado activa. |
| `STRINGLN` | texto | Lo mismo y luego pulsa Enter. |
| `STRING_DELAY` | ms | Pausa entre pulsaciones solo para el siguiente `STRING`/`STRINGLN`. Igual que `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pausa entre pulsaciones para todas las cadenas siguientes. Igual que `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Sin un retardo de cadena el texto se envía lo más rápido posible; algunos anfitriones o aplicaciones pierden
caracteres en ese caso. Los scripts de demostración incluidos usan `DEFAULT_STRING_DELAY 10`.

::: warning La distribución importa
`STRING` envía *posiciones de tecla*, traducidas a través de la [distribución de teclado](/es/badusb/layouts)
seleccionada. Si el anfitrión usa una distribución distinta a la de la aplicación, obtendrás caracteres erróneos.
El texto debe ser ASCII.
:::

## Teclas y combinaciones

Una línea que no es un comando se interpreta como una pulsación de teclas: cero o más **modificadores** y después
una **tecla**. Los modificadores se unen con espacios o guiones. La tecla es un nombre de tecla especial o un único
carácter.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modificadores

| Nombre | Notas |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Tecla Windows / Command / Super |

### Teclas especiales

| Nombre | Notas |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Flechas |
| `ENTER` | |
| `DELETE` | Borrado hacia delante |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pausa/Inter |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Tecla de menú contextual |
| `F1` … `F24` | Teclas de función (el firmware conoce también F13-F24) |

## Repetición

```text
DOWN
REPEAT 9
```

`REPEAT n` ejecuta el **comando anterior** n veces más (el ejemplo pulsa Abajo 10 veces). `n` debe ser ≥ 1.

## Mantener y soltar

| Comando | Parámetro | Notas |
|---|---|---|
| `HOLD` | tecla especial, modificador, un solo carácter o botón del ratón | Pulsa y mantiene hasta `RELEASE`. |
| `RELEASE` | lo mismo | Suelta esa tecla. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Se pueden mantener como máximo **6** teclas o botones a la vez (el tamaño del informe HID de teclas); más produce
*"Too many keys are held"*. Un `RELEASE` sin nada mantenido produce *"No keys are held"*. El documento oficial dice
5; la comprobación del firmware permite 6.

## Entrada con ALT + teclado numérico

En Windows (y en algunas configuraciones de Linux) se puede escribir cualquier carácter manteniendo `ALT` e
introduciendo su código en el teclado numérico. Esto **no depende de la distribución de teclado**, lo que resulta
muy práctico en equipos desconocidos.

| Comando | Parámetro | Notas |
|---|---|---|
| `ALTCHAR` | código de carácter | Escribe un carácter: mantiene ALT y teclea los dígitos en el numérico. |
| `ALTSTRING` | texto | Escribe cada carácter ASCII imprimible (32-126) del texto mediante su código ALT. |
| `ALTCODE` | texto | Igual que `ALTSTRING` (nombre usado por algunas implementaciones de DuckyScript). |

NumLock se activa automáticamente antes de la entrada con ALT.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Envía `ALT`+`PRINTSCREEN`+tecla, la combinación [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key) de Linux.
Ten cuidado: algunas teclas de SysRq reinician o detienen el sistema de inmediato.

## Teclas multimedia

`MEDIA <tecla>` pulsa una tecla de control de consumo:

| Tecla | Notas |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | Sistema |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Navegación del navegador o de la aplicación |
| `SNAPSHOT` | Hacer una foto en una aplicación de cámara |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Reproducción |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Volumen |
| `FN` | Tecla Fn/Globo de los teclados Mac |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Brillo de la pantalla |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Tecla Fn / Globo (Mac, iPad)

```text
GLOBE e
```

`GLOBE <tecla>` mantiene Fn/Globo, pulsa la tecla y suelta ambas (tecla especial o un solo carácter).

## Esperar una pulsación de botón

```text
WAIT_FOR_BUTTON_PRESS
```

El script se detiene indefinidamente; el Flipper muestra **Press to continue**. Pulsa <kbd>OK</kbd> para continuar.
Útil para sincronizarse con algo que haces a mano (iniciar sesión, desbloquear la pantalla…).

## Ratón

| Comando | Parámetro | Notas |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | ninguno | Clic izquierdo |
| `RIGHTCLICK` / `RIGHT_CLICK` | ninguno | Clic derecho |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | ninguno | Clic central (rueda) |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (enteros) | Movimiento relativo; negativo = izquierda / arriba |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (entero) | Rueda de desplazamiento; el signo indica la dirección |

Los botones del ratón funcionan con `HOLD`/`RELEASE`, por ejemplo para arrastrar y soltar:

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## Device ID {#device-id}

Puedes fijar la identidad con la que el Flipper se presenta al anfitrión. El comando debe estar en la **primera
línea**; se aplica al abrir el script, antes de ejecutarlo, y la aplicación **cambia al modo de conexión
correspondiente** (aun así puedes volver a cambiarlo a mano). En otras líneas estos comandos se ignoran.

| Comando | Parámetros | Ejemplo | Modo |
|---|---|---|---|
| `ID` | `VID:PID Fabricante:Producto` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Nombre de dispositivo` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Nombre de dispositivo` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | igual que `BLE_ID` |

- `ID`: el VID y el PID (en hexadecimal) son obligatorios; las cadenas de fabricante y producto son opcionales
  (máximo 31 caracteres cada una).
- `BLE_ID` / `BT_ID`: tanto la MAC de 6 bytes como el nombre del dispositivo son obligatorios.

## Distribución de teclado por script: `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` es una novedad de Unleashed (PR #1224 de @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Carga `/ext/badusb/assets/layouts/<nombre>.kl` y lo usa a partir de esa línea, en lugar de la distribución global
  fijada en Config. Alias cortos: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- El nombre puede contener letras, dígitos, `-` y `_`, y nada más puede seguirlo en la línea.
- Un fichero inexistente o un nombre inválido **no detienen el script**: se recurre silenciosamente a la
  distribución integrada `en-US`.
- Cada ejecución nueva vuelve a empezar con la distribución global, así que pon `DUCKY_LANG` cerca del principio.

La lista de nombres de distribución está en [Distribuciones de teclado](/es/badusb/layouts).

## Páginas relacionadas

- [Ejemplos](/es/badusb/examples)
- [Distribuciones de teclado](/es/badusb/layouts)
- [Uso de Bad USB](/es/badusb/usage)
