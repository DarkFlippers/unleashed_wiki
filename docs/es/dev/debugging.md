---
title: Depurar apps
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Depurar apps

La depuración en tiempo real (in-circuit) permite iniciar una app, pausarla en cualquier punto, recorrer el código
línea a línea y observar las variables y la pila de llamadas. Encuentra muchos más fallos que «añade una línea de log
y vuelve a intentarlo».

::: info
La depuración in-circuit es opcional. Siempre puedes depurar cargando las apps por USB y leyendo el
[log](/es/dev/cli#reading-logs).
:::

## Qué necesitas

- Un Flipper Zero (el *objetivo*).
- Un ordenador con Windows, Linux o macOS con [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (para apps)
  o el árbol completo del firmware con [fbt](/es/dev/fbt).
- Una **sonda SWD** compatible.

### Sondas SWD compatibles

| Sonda | Notas |
|---|---|
| Un **segundo Flipper Zero** | Ejecuta la [app DAP Link](https://lab.flipper.net/apps/dap_link) en él para convertirlo en una sonda SWD |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Con su firmware de fábrica (Blackmagic); se conecta por USB o por Wi-Fi — consulta [Dev Board](/es/gpio/devboard) |
| Sondas CMSIS-DAP | Por ejemplo la [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), la [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/) o la [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Sondas compatibles con Blackmagic](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), la [devboard ST-Link V3](/es/dev/hardware#st-link-v3-developer-board) |
| J-Link | Flasheo y depuración solo desde VS Code; instala las herramientas de SEGGER por tu cuenta |

## Preparar el Flipper

Activa el modo de depuración en el dispositivo objetivo: `Main Menu → Settings → System → Debug` → **ON**.

## Paso a paso (VS Code)

1. **Conecta la sonda al conector GPIO del Flipper.** Las sondas hechas para el Flipper se conectan directamente. Para
   una sonda genérica conecta tres cables:

   | Señal | Pin del Flipper |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 o 18 |

   Si la sonda tiene también un UART, conéctalo al USART del Flipper (pines **13** TX y **14** RX). Ese puerto imprime
   los logs y la información de los fallos, lo que ayuda mucho.
2. **Conecta la sonda al ordenador** — normalmente por USB; la Wi-Fi Devboard también funciona por Wi-Fi.
3. **Prepara el proyecto:** ejecuta `ufbt vscode_dist` (app) o `./fbt vscode_dist` (firmware) una vez y abre la
   carpeta en VS Code.
4. **Cambia VS Code a Run and Debug:** pulsa el icono de depuración de la barra lateral o
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> en macOS). Elige la
   configuración de tu sonda y pulsa **Play**.

   ::: info
   Iniciar una sesión de depuración **detiene** el firmware. Pulsa **Continue** en la barra de depuración para
   reanudarlo.
   :::
5. **Usa los controles de depuración:** reset, pausa, continuar, entrar en la función, salir de la función,
   desconectar.
6. **Pon breakpoints** haciendo clic a la izquierda de un número de línea. La ejecución se detiene cuando llega a esa
   línea.
7. **Examina la pila de llamadas** en el panel *Call Stack* mientras está pausada.
8. **Examina las variables** en los paneles *Variables*, *Watch* o *Live Watch*.

Un vídeo de demostración de Flipper Devices:
[Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Depurar desde la línea de comandos con fbt

Con el árbol completo del firmware puedes depurar sin VS Code:

| Comando | Qué hace |
|---|---|
| `./fbt debug` | Compila y flashea el firmware, después conecta GDB con el `.elf` del firmware cargado |
| `./fbt blackmagic` | Depura con una sonda Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Conecta GDB sin cargar ningún `.elf`; añade el `.elf` de tu app con `add-symbol-file` |
| `./fbt updater_debug` | Conecta GDB con el `.elf` del actualizador |
| `./fbt openocd ARGS="..."` | Solo arranca OpenOCD |
| `./fbt get_stlink` | Lista los números de serie de las ST-Link, para `SWD_TRANSPORT_SERIAL=...` |

## Señales de depuración del Furi HAL

Algunos subsistemas de Furi pueden exponer su estado interno en pines GPIO para seguirlo con un analizador lógico o un
osciloscopio. Se activan añadiendo un define en tiempo de compilación, por ejemplo:

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — planificador y modo de reposo

Expone el tick, la supresión del tick, la inactividad y el paso del tiempo:

| Señal | Pin | Significado |
|---|---|---|
| `AWAKE` | `PA7` | Alta mientras el sistema está calculando, baja mientras duerme — permite seguir las transiciones al reposo |
| `TICK` | `PA6` | Conmuta en cada tick del sistema (solo cuando no hay supresión de tick en curso) — revela desviaciones del tick y planificaciones anómalas |
| `SECOND` | `PA4` | Conmuta cada segundo — las alteraciones de su cadencia indican que el sistema no cumple el tiempo real estricto |

### `FURI_HAL_POWER_DEBUG` — modos de energía

Sigue las transiciones entre modos de energía:

| Señal | Pin | Significado |
|---|---|---|
| `WFI` | `PB2` | Reposo ligero (wait for interrupt). El modo de ahorro más suave y no invasivo — todo, incluida la depuración, funciona |
| `STOP` | `PC3` | Modo STOP, el reposo profundo de la plataforma. La mayor parte del silicio está apagada o inutilizable; depurar el MCU en este modo es casi imposible |

### `FURI_HAL_SD_SPI_DEBUG` — tarjeta SD

Registra el tráfico del bus SPI de la tarjeta SD.

## Resolución de problemas

| Problema | Solución |
|---|---|
| La sonda conecta pero no pasa nada | El firmware está detenido — pulsa **Continue** |
| Se ignoran los breakpoints de tu app | Asegúrate de que los símbolos del `.elf` de la app están cargados (la configuración de VS Code de `vscode_dist` lo hace; con `debug_other` usa `add-symbol-file`) |
| El depurador pierde el objetivo | El MCU puede estar en modo STOP; consulta `FURI_HAL_POWER_DEBUG`. El modo Debug del Flipper debe estar en **ON** |
| Las variables aparecen como optimizadas | Compila con `DEBUG=1` (ojo: ese firmware puede ser demasiado grande para empaquetarlo — consulta [Compilar](/es/dev/build)) |

## Páginas relacionadas

- [Tu primera app en C](/es/dev/first-app-c)
- [Flipper Build Tool (fbt)](/es/dev/fbt)
- [Dev Board](/es/gpio/devboard)
- [Hardware](/es/dev/hardware) — esquemas de patillaje y de las devboards
