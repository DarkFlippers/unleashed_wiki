---
title: "Devboard: depuración y registros"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: depuración y registros

Con la [Devboard ya configurada](/es/gpio/devboard), puedes depurar el firmware desde VS Code y leer los registros
del Flipper por el UART.

## Cómo funciona

La Devboard es la sonda de depuración entre el depurador de tu ordenador (por USB o Wi-Fi) y el MCU del Flipper.
Habla con el Flipper por **Serial Wire Debug**:

- **pin 10**: SWCLK (Serial Wire Clock);
- **pin 12**: SWDIO (Serial Wire Debug Data I/O).

![Hardware de la Devboard](/img/remote/06e0a9eb98e4130d.jpg)

## Modos de depuración

| Conexión | Modos disponibles |
|---|---|
| Wi-Fi | Solo Black Magic |
| USB | Black Magic (por defecto) o DAPLink |

El modo Black Magic no admite el reconocimiento de hilos del RTOS; todo lo demás funciona.

### Cambiar el modo USB

Curiosamente, el modo USB se cambia por Wi-Fi:

1. Abre la interfaz web de la placa (<http://192.168.4.1> en modo punto de acceso o <http://blackmagic.local> en
   modo cliente, véase la [conexión](/es/gpio/devboard)).
2. En la pestaña **WiFi**, pon **USB mode** en **BlackMagicProbe** o en **DapLink**.
3. Pulsa **SAVE** y después **REBOOT**.
4. En VS Code, selecciona el depurador correspondiente (más abajo).

## Depurar el firmware en VS Code

### Requisitos previos

1. Instala [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Clona y compila el firmware. Para Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Los mismos pasos valen con el repositorio de serie `flipperdevices/flipperzero-firmware`.) Más sobre la
   compilación: [Compilar el firmware](/es/dev/build), [FBT](/es/dev/fbt).

### Iniciar una sesión

1. Flashea el firmware que acabas de compilar a través de la Devboard:

   ```bash
   ./fbt flash
   ```

2. Abre la carpeta del firmware en **VS Code** e instala las extensiones recomendadas (en la notificación, o con
   `@recommended` en la pestaña de extensiones).
3. Genera la configuración de VS Code:

   ```bash
   ./fbt vscode_dist
   ```

4. En **Run and Debug**, elige:
   - **Attach FW (blackmagic)**: por Wi-Fi o por USB;
   - **Attach FW (DAP)**: solo por USB, con la placa en modo DAPLink.

   Por USB, el depurador debe coincidir con el **USB mode** de la placa (compruébalo en la interfaz web).
5. Pulsa ▷ **Start Debugging**. El firmware se detiene al arrancar la sesión; pulsa **Continue** en la barra de
   herramientas para dejarlo correr.

![Depuración en VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Véase también la [guía de depuración de VS Code](https://code.visualstudio.com/docs/editor/debugging) y
[Depuración](/es/dev/debugging).

## Leer los registros

La Devboard lee la salida de registro del Flipper desde su UART, con independencia del sistema operativo del
Flipper. Así ves los registros durante el arranque, las actualizaciones y los cuelgues, que el comando `log` de la
CLI no puede mostrar. Los registros están disponibles **solo por USB**.

### Fija el nivel y el dispositivo de registro

1. Abre `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: déjalo en `USART` (pines 13/14), que es donde escucha la Devboard. `LPUART` envía los registros a
   los pines 15/16 y `None` desactiva el registro por UART.

::: tip
Si otro módulo necesita los pines 13/14 (placa Wi-Fi, SIM800, GPS), pon `Log Device` en `LPUART` o en `None` para
que la salida de registros no le moleste.
:::

### macOS

1. Instala [Homebrew](https://brew.sh/) y después `brew install minicom`.
2. Apaga el Flipper, conecta la Devboard y enciéndelo.
3. Ejecuta `ls /dev/cu.*`, conecta la Devboard por USB y vuelve a ejecutarlo. Aparecen dos dispositivos nuevos, por
   ejemplo `/dev/cu.usbmodemblackmagic1` y `/dev/cu.usbmodemblackmagic3`.
4. Abre el que tenga el **número más alto**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Los registros van apareciendo en el terminal. Sal por el menú de minicom o cierra la ventana.

### Linux

1. Instala minicom, por ejemplo con `sudo apt install minicom`.
2. Apaga el Flipper, conecta la Devboard y enciéndelo.
3. Ejecuta `ls /dev/tty*`, conecta la Devboard por USB y vuelve a ejecutarlo. Aparecen dos dispositivos nuevos, por
   ejemplo `/dev/ttyACM0` y `/dev/ttyACM1`.
4. Abre el que tenga el número más alto:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Si no aparece nada, prueba con el otro dispositivo.

### Windows

1. Instala [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Apaga el Flipper, conecta la Devboard, enciéndelo y conecta la Devboard por USB.
3. En **Administrador de dispositivos → Ports (COM & LPT)**, apunta el puerto COM nuevo.
4. En PuTTY, elige **Serial**, escribe el puerto en **Serial line**, pon **Speed** en **230400** y pulsa **Open**.

![Ajustes de PuTTY](/img/remote/2bb43453a91a142e.jpg)

## Relacionado

- [Devboard: primeros pasos](/es/gpio/devboard)
- [Devboard: actualizar el firmware](/es/gpio/devboard-firmware)
- [CLI](/es/dev/cli)
