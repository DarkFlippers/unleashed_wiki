---
title: "Devboard: actualizar el firmware"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: actualizar el firmware

Cómo actualizar (o restaurar) el firmware de la propia Wi-Fi Developer Board con **uFBT**. Esto no es el firmware
del Flipper: para eso, véase [Actualizar](/es/start/updating).

## Paso 1. Instala uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) compila y depura aplicaciones, flashea firmware,
crea configuraciones de VS Code y flashea la Wi-Fi Devboard.

**Linux y macOS**

1. Instala `pipx` ([instrucciones](https://pipx.pypa.io/stable/installation/)) y reinicia el terminal.
2. Instala uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Instala el [Python](https://www.python.org/downloads/windows/) más reciente.
2. En PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Reinicia PowerShell y después:

   ```powershell
   pipx install ufbt
   ```

## Paso 2. Pon la placa en modo bootloader

1. Lista los dispositivos serie: en macOS `ls /dev/cu.*`, en Linux `ls /dev/tty*`, en Windows Administrador de
   dispositivos → **Ports (COM & LPT)**.
2. Conecta la Devboard al ordenador con un cable USB-C.
3. Entra en modo bootloader:
   1. mantén pulsado **BOOT**;
   2. pulsa y suelta **RESET** sin dejar de mantener **BOOT**;
   3. suelta **BOOT**.
4. Vuelve a listar los dispositivos y apunta el nuevo.

![Botones de bootloader de la Devboard](/img/remote/060af5decf4b567c.jpg)

## Paso 3. Flashea

Linux y macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Mensaje de éxito: `WiFi board flashed successfully`.

### Si el flasheo falla

Errores como

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

o

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

se suelen arreglar:

- desconectando y volviendo a conectar la placa, y entrando otra vez en modo bootloader;
- con otro puerto USB;
- con otro cable USB-C.

## Paso 4. Para terminar

1. Pulsa **RESET** en la placa.
2. Desconecta y vuelve a conectar el cable USB-C.

La placa ejecuta ya el firmware Black Magic oficial más reciente. Así es también como se restaura después de
flashear otro firmware (por ejemplo, [Marauder](/es/gpio/esp32)). Continúa con
[conectarla al Flipper](/es/gpio/devboard).
