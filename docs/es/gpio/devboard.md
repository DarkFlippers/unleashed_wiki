---
title: "Devboard: primeros pasos"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: primeros pasos

La **Wi-Fi Developer Board** oficial es un módulo ESP32-S2 (ESP32-S2-WROVER-N4R2) para el conector GPIO. De fábrica
lleva el firmware **Black Magic Probe** y funciona como **sonda de depuración**: conecta el depurador de tu
ordenador con el STM32 del Flipper por SWD, a través de USB o Wi-Fi. También puede reenviar los registros UART del
Flipper.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip No hace falta para flashear firmware
Actualizar, compilar y subir tu propio firmware funciona todo por USB normal. La Devboard solo hace falta para
depurar en vivo (GDB, puntos de interrupción) y para leer registros con independencia del sistema operativo del
Flipper. Para usar la misma placa como herramienta Wi-Fi (Marauder), véase [ESP32 y Wi-Fi](/es/gpio/esp32).
:::

## Paso 1. Activa el modo Debug en el Flipper

1. Abre `Main Menu → Settings → System`.
2. Pon `Debug` en `ON`.

El modo Debug es necesario para depurar aplicaciones y desbloquea opciones de depuración en las aplicaciones y en la
[CLI](/es/dev/cli). Vuelve a activarlo después de cada actualización de firmware.

## Paso 2. Actualiza el firmware de la placa

La placa viene con un firmware antiguo. Actualízalo primero:
[Devboard: actualizar el firmware](/es/gpio/devboard-firmware).

## Paso 3. Conecta la Devboard al Flipper

1. **Apaga el Flipper antes.** La placa y la tarjeta microSD comparten el raíl de 3,3 V del Flipper; conectar en
   caliente una carga capacitiva grande puede corromper la tarjeta.
2. **Insértala hasta el fondo.** Sin funda: que no quede hueco entre el Flipper y la placa (puede hacer falta algo
   de fuerza). Con funda de silicona: que no quede hueco en la parte central entre la funda y la placa.
3. Mantén <kbd>BACK</kbd> para encender el Flipper.

![Devboard insertada, Flipper sin funda](/img/remote/4eb1e40120ff42bb.jpg)

## Paso 4. Conéctala a un ordenador

### Por USB

Usa el USB para depurar en modo **Black Magic** o **DAPLink** y para leer registros.

1. Lista los dispositivos serie del ordenador:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Administrador de dispositivos → **Ports (COM & LPT)**
2. Conecta el puerto USB-C **de la Devboard** al ordenador.
3. Vuelve a listar los dispositivos: aparecen **dos puertos nuevos**, los dos de la Devboard.

Si no aparece nada, prueba otro cable (tiene que llevar datos), otro puerto USB u otro ordenador.

### Por Wi-Fi: modo punto de acceso (por defecto)

La placa crea su propia red. Tu ordenador pierde su conexión Wi-Fi habitual mientras esté conectado a ella.

1. En el ordenador o el móvil, conéctate a la red Wi-Fi:
   - Nombre: `blackmagic`
   - Contraseña: `iamwitcher`
2. Abre <http://192.168.4.1> o <http://blackmagic.local> para acceder a la interfaz web de la placa.

Si la red `blackmagic` no aparece:

- reinicia la conexión Wi-Fi del ordenador;
- puede que la placa esté configurada como cliente (STA). Mantén el botón **BOOT** de la placa durante **10
  segundos** para restablecer su configuración; tras reiniciarse vuelve a ser un punto de acceso.

### Por Wi-Fi: modo cliente (STA)

La placa se une a tu red de 2,4 GHz, así que no pierdes el acceso a internet.

1. Conéctate a la placa en modo punto de acceso (más arriba) y abre <http://192.168.4.1>.
2. Selecciona el modo **STA** e introduce el **SSID** y la **contraseña** de tu red. El botón **+** lista las redes
   de 2,4 GHz cercanas (no se admiten las de 5 GHz).
3. Guarda y reinicia la placa.
4. A partir de ahí, abre <http://blackmagic.local> por tu red habitual.

Por Wi-Fi solo está disponible la depuración con **Black Magic**.

## Hardware

- MCU: ESP32-S2-WROVER-N4R2.
- SWD al Flipper en el **pin 10 (SWCLK)** y el **pin 12 (SWDIO)**; registros UART en los pines 13/14 del USART del
  Flipper.
- Esquemas (PCB, ESP32-S2, alimentación, conectores) y plano de montaje:
  [esquemas de la Wi-Fi Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Siguientes pasos

- [Devboard: depuración y registros](/es/gpio/devboard-debug)
- [Devboard: actualizar el firmware](/es/gpio/devboard-firmware)
- Comunidad: [Discord](https://discord.com/invite/flipper) (canal #wifi-devboard), [Reddit](https://www.reddit.com/r/flipperzero/)
