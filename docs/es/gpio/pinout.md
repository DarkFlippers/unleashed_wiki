---
title: Patillaje GPIO
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# Patillaje GPIO

El Flipper Zero tiene un conector de 18 pines con paso de 2,54 mm en su borde superior. Lleva salidas de
alimentación, masa, 13 pines de E/S conectados al microcontrolador STM32WB55, las líneas de depuración SWD y la
línea 1-Wire compartida con iButton.

![Funciones de los pines GPIO del Flipper Zero](/img/remote/b75cf29833cf8de8.jpg)

## Tabla de pines

Los números de pin se cuentan desde el **pin 1 (+5 V)**. Los nombres de puerto (`PA7`, `PC0`, …) son los que usa el
firmware en pantalla y en la CLI.

| Pin | Nombre | Funciones principales | Notas |
|---|---|---|---|
| 1 | +5V | Salida de alimentación de 5 V | Apagada con batería hasta que se activa, véase más abajo |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | MOSI del CC1101 / NRF24 externo |
| 3 | PA6 | SPI MISO, ADC | MISO del CC1101 / NRF24 externo |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | CS del CC1101 / NRF24 externo; pin DE/RE del USB-UART |
| 5 | PB3 | SPI SCK | SCK del CC1101 / NRF24 externo |
| 6 | PB2 | GPIO | GDO0 del CC1101 externo, CE del NRF24 |
| 7 | PC3 | GPIO, ADC | Control del amplificador del CC1101 externo |
| 8 | GND | Masa | |
| 9 | 3V3 | Salida de alimentación de 3,3 V | Activada por defecto |
| 10 | PA14 | SWCLK | Depuración (SWD) |
| 11 | GND | Masa | |
| 12 | PA13 | SWDIO | Depuración (SWD) |
| 13 | PB6 | USART TX | UART por defecto para el puente USB-UART, los registros y los módulos de expansión |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Segundo UART; datos del I2C externo |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Segundo UART; reloj del I2C externo |
| 17 | PB14 | 1-Wire | Línea de iButton |
| 18 | GND | Masa | |

El firmware marca los pines 10, 12, 13, 14 y 17 como **pines de depuración**: quedan ocultos en
`GPIO Manual Control`, y el comando `gpio` de la CLI solo los lista con el modo Debug activado (y pide confirmación
antes de cambiarlos).

![Patillaje GPIO detallado del Flipper Zero](/img/remote/e77df2d4499cbbbc.jpg)

En la [página oficial de GPIO](https://docs.flipper.net/zero/gpio-and-modules) hay un PDF imprimible del patillaje.

## Límites eléctricos

- **Nivel lógico:** CMOS de 3,3 V. Cada pin de E/S llega al MCU a través de una resistencia de 51 Ω y está
  protegido contra ESD.
- **Corriente por pin:** hasta 20 mA.
- **Total desde los pines de E/S:** mantenlo por debajo de 5 W; de lo contrario, la protección de la batería puede
  saltar y el Flipper se apaga.
- **Tolerancia a 5 V:** solo para un pin configurado como **entrada**. Un pin puesto como salida no tolera 5 V.
  Evita periféricos con lógica de 5 V a menos que uses un conversor de niveles. Detalles en la nota de aplicación
  de ST
  [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3,3 V (pin 9)

- Activado por defecto, carga máxima **1,2 A**.
- La tarjeta microSD se alimenta del mismo raíl. El pin 9 se desactiva brevemente durante las actualizaciones de
  firmware y cuando se monta la tarjeta.

::: warning
Conecta módulos con una carga capacitiva grande solo con el Flipper apagado, o te arriesgas a corromper los datos
de la tarjeta microSD.
:::

### +5 V (pin 1)

- Desde USB: cuando hay un cable conectado, el pin 1 se alimenta directamente del USB. Nunca consumas más de
  **1,2 A**.
- Desde la batería: la salida está **desactivada por defecto**. El convertidor elevador (OTG) da hasta **1,2 A**
  cuando se activa.

Para activar los 5 V funcionando con batería:

1. Abre `Main Menu → GPIO`.
2. Selecciona `5V on GPIO` y ponlo en `ON` con <kbd>→</kbd>.

Otras formas de conmutarlo:

- CLI: `power 5v 1` / `power 5v 0` (véase [CLI](/es/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` para los módulos IR externos.
- Aplicaciones como Sub-GHz (CC1101 externo) y [SIM800](/es/gpio/sim800) lo piden automáticamente, y un
  [módulo de expansión](/es/gpio/expansion-modules) puede solicitarlo a través de su protocolo.

::: tip Cómo gestiona el firmware los 5 V
Si pides 5 V mientras hay alimentación por USB, el servicio de energía aplaza la activación del convertidor
elevador y lo enciende él mismo en cuanto se desconecta el USB. Si el cargador informa de un fallo OTG
(sobrecarga o cortocircuito), los 5 V se apagan y la petición se cancela, así que tendrás que activarlos de nuevo.
:::

## Los pines en modo DFU

En modo DFU (bootloader), los pines de E/S, salvo el pin 17, cambian de estado según la nota
[AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf)
de STMicroelectronics (tabla «STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode»). Tenlo en
cuenta si un módulo reacciona a los niveles de los pines mientras [recuperas](/es/start/recovery) el Flipper.

## Insertar un módulo

- **Sin funda de silicona:** empuja el módulo hasta el fondo para que no quede ningún pin visible entre el Flipper
  y el módulo. Puede hacer falta algo de fuerza.
- **Con funda de silicona:** empújalo hasta que no quede hueco en la parte central entre la funda y el módulo.

![Módulo insertado hasta el fondo](/img/remote/52e7045a797ed1c4.png)

## Relacionado

- [Aplicación GPIO](/es/gpio/gpio-app)
- [Módulos externos](/es/gpio/external-modules)
- [Esquemas del Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)
