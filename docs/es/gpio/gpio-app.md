---
title: Aplicación GPIO
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# Aplicación GPIO

La aplicación **GPIO** integrada (`Main Menu → GPIO`) tiene tres elementos:

| Elemento | Qué hace |
|---|---|
| `USB-UART Bridge` | Convierte el Flipper en un adaptador USB a serie en los pines 13/14 o 15/16 |
| `GPIO Manual Control` | Pone los pines de usuario a nivel alto mientras mantienes <kbd>OK</kbd> |
| `5V on GPIO` | `OFF` / `ON`: la salida de 5 V del pin 1 |

![Menú de la aplicación GPIO: USB-UART Bridge, GPIO Manual Control y 5V on GPIO en OFF](/screens/gpio/menu.png)

Los números de pin y los voltajes están en la página de [patillaje](/es/gpio/pinout).

## USB-UART Bridge

Úsalo para hablar desde un ordenador con la consola de un router, una placa ESP32/ESP8266, un módulo GSM o GPS o
cualquier dispositivo serie de 3,3 V, usando el Flipper como adaptador.

1. Conecta el dispositivo: **TX del Flipper → RX del dispositivo**, **RX del Flipper → TX del dispositivo** y una
   masa común (pin 8, 11 o 18). Por defecto, TX es el pin 13 y RX el pin 14.
2. Conecta el Flipper al ordenador por USB.
3. Abre `Main Menu → GPIO → USB-UART Bridge`. La pantalla muestra `USB Serial`, el número de `COM PORT`, los pines
   TX/RX, los contadores de bytes y la velocidad en baudios actual.
4. Pulsa <kbd>←</kbd> (`Config`) para configurarlo (tabla más abajo) y luego <kbd>BACK</kbd> para volver a la
   pantalla de estado.
5. Abre el puerto en un programa de terminal (PuTTY, minicom, screen, el monitor serie de Arduino…).
6. Para terminar, pulsa <kbd>BACK</kbd> y confirma `Exit USB-UART?` con `Exit` (o elige `Stay`).

![Pantalla de estado del USB-UART Bridge: USB Serial, COM PORT 0, TX pin 13, RX pin 14, contadores de bytes, Baud 115200](/screens/gpio/usb_uart.png)

Mientras circulan datos, el LED parpadea en **azul al transmitir (TX)** y en **verde al recibir (RX)**, y la
retroiluminación se queda encendida.

### Pantalla de configuración

![Config del USB-UART Bridge: USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Ajuste | Valores | Significado |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)`: el puente toma el puerto serie USB principal y la CLI queda desactivada mientras funciona. `1`: el Flipper expone dos puertos serie; la CLI se queda en el primero y el puente usa el segundo |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` sigue la velocidad que fije el programa de terminal en el puerto. Un número fuerza una velocidad fija (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART en los pines 13 (TX) / 14 (RX), o LPUART en los pines 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Saca las líneas RTS y DTR del host (el primer pin es RTS y el segundo DTR, activas a nivel bajo). `16,15` no se ofrece cuando `UART Pins` está en `15,16` |
| `DE/RE Pin` | `None`, `4` | Usa el pin 4 como señal de dirección (driver enable) para un transceptor RS-485 |

::: tip Flashear placas ESP
La salida RTS/DTR es justo lo que esperan los circuitos de autorreinicio y arranque de las placas ESP8266/ESP32 y
Arduino. Conecta los dos pines a la lógica de EN/RST y BOOT/GPIO0 de la placa (con la pareja de transistores
habitual) y esptool podrá ponerla en el bootloader sin pulsar botones.
:::

### Si aparece «Connection Is Active!»

El puente no puede arrancar mientras qFlipper, la aplicación móvil u otra sesión RPC tengan tomada la conexión USB.
La pantalla muestra `Connection Is Active! Disconnect from PC or phone to use this function.` Cierra qFlipper o
desconecta la aplicación y vuelve a intentarlo.

## GPIO Manual Control

Una forma rápida de comprobar un cableado o un LED / relé en un pin.

1. Abre `Main Menu → GPIO → GPIO Manual Control`. La pantalla muestra `GPIO Output Mode Test`.
2. Elige el pin con <kbd>←</kbd> / <kbd>→</kbd>: `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6), `PC3` (7),
   `PC1` (15), `PC0` (16) o `ALL`.
3. **Mantén** <kbd>OK</kbd>: el pin (o todos ellos) pasa a nivel alto, 3,3 V, y se enciende el LED verde. Al
   soltarlo, el pin vuelve a nivel bajo.

Todos los pines de la lista son salidas push-pull mientras esta pantalla esté abierta; al salir vuelven al modo de
alta impedancia (analógico). No conectes nada que accione esos pines por sí mismo mientras haces pruebas.

## 5V on GPIO

Conmuta la salida de 5 V del pin 1. Selecciona el elemento y cámbialo con <kbd>←</kbd> / <kbd>→</kbd>. El ajuste no
es un modo de la aplicación: los 5 V siguen activos después de salir de la aplicación GPIO, hasta que los
desactives, apagues el Flipper o se produzca un fallo por sobrecarga. Consulta el [patillaje](/es/gpio/pinout) para
los límites de corriente.

## Herramientas de la CLI

En la [CLI](/es/dev/cli) del Flipper hay dos comandos relacionados:

```text
gpio mode <pin_name> <0|1>   # 0 - input, 1 - output
gpio set <pin_name> <0|1>    # set output low/high
gpio read <pin_name>         # read input level
power 5v <0|1>               # 5 V on pin 1 off/on
i2c                          # scan the external I2C bus
```

- Los nombres de pin son los nombres de puerto (`PA7`, `PC0`, …). Los pines de depuración (`PA13`, `PA14`, `PB6`,
  `PB7`, `PB14`) solo se aceptan con el modo Debug activado, y la CLI avisa primero con
  `Changing this pin mode may damage hardware...`.
- `i2c` escanea direcciones en **PC0 (SCL, pin 16) / PC1 (SDA, pin 15)** a 100 kHz, con direccionamiento de 7 bits,
  e imprime una tabla donde `#` marca un dispositivo que ha respondido. La mayoría de las placas de desarrollo I2C
  ya llevan resistencias de pull-up; si no aparece nada, comprueba que la tuya las tenga.

::: tip Unleashed
Para más trabajo con I2C (sniffer, lectura y escritura de registros) y sensores, mira los plugins `i2c Tools` y
`Unitemp` de los paquetes de aplicaciones extra, listados en [Módulos externos](/es/gpio/external-modules).
:::

## Resolución de problemas

- **Caracteres basura en el terminal:** la velocidad en baudios no coincide. Pon `Baudrate` en la velocidad del
  dispositivo, o déjalo en `Host` y fija la velocidad en el programa de terminal.
- **No llegan datos:** intercambia TX y RX, comprueba que la masa es común y que `UART Pins` coincide con tu
  cableado.
- **Ha desaparecido la CLI:** `USB Channel` está en `0 (CLI)`. Sal del puente o usa el canal `1`.
- **5V on GPIO no se queda activado:** la carga consume demasiado (apagado por fallo) o un condensador grande del
  módulo hace saltar el convertidor elevador al arrancar. Apaga el Flipper, conecta el módulo y enciéndelo después.

## Relacionado

- [Patillaje GPIO](/es/gpio/pinout)
- [Módulos externos](/es/gpio/external-modules)
- [Devboard: depuración y registros](/es/gpio/devboard-debug)
