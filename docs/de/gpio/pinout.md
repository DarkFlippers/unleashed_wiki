---
title: GPIO-Pinbelegung
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# GPIO-Pinbelegung

Am oberen Rand des Flipper Zero sitzt eine 18-polige Stiftleiste im Raster 2,54 mm. Sie führt Versorgungsspannungen,
Masse, 13 I/O-Pins des Mikrocontrollers STM32WB55, die SWD-Debug-Leitungen und die 1-Wire-Leitung, die mit iButton
gemeinsam genutzt wird.

![Pin-Funktionen des Flipper Zero GPIO](/img/remote/b75cf29833cf8de8.jpg)

## Pin-Tabelle

Gezählt wird ab **Pin 1 (+5 V)**. Die Portnamen (`PA7`, `PC0`, …) sind die Namen, die die Firmware auf dem Display und
in der CLI verwendet.

| Pin | Name | Hauptfunktionen | Hinweise |
|---|---|---|---|
| 1 | +5V | Ausgang 5 V | Im Akkubetrieb aus, bis er aktiviert wird, siehe unten |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | MOSI für externes CC1101 / NRF24 |
| 3 | PA6 | SPI MISO, ADC | MISO für externes CC1101 / NRF24 |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | CS für externes CC1101 / NRF24; DE/RE-Pin bei USB-UART |
| 5 | PB3 | SPI SCK | SCK für externes CC1101 / NRF24 |
| 6 | PB2 | GPIO | GDO0 des externen CC1101, CE des NRF24 |
| 7 | PC3 | GPIO, ADC | Verstärkersteuerung des externen CC1101 |
| 8 | GND | Masse | |
| 9 | 3V3 | Ausgang 3,3 V | Standardmäßig an |
| 10 | PA14 | SWCLK | Debug (SWD) |
| 11 | GND | Masse | |
| 12 | PA13 | SWDIO | Debug (SWD) |
| 13 | PB6 | USART TX | Standard-UART für USB-UART-Bridge, Logs, Expansion-Module |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Zweiter UART; Daten des externen I2C |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Zweiter UART; Takt des externen I2C |
| 17 | PB14 | 1-Wire | iButton-Leitung |
| 18 | GND | Masse | |

Die Firmware kennzeichnet die Pins 10, 12, 13, 14 und 17 als **Debug-Pins**: In `GPIO Manual Control` werden sie
ausgeblendet, und der CLI-Befehl `gpio` listet sie nur bei aktiviertem Debug-Modus auf (und fragt vor einer Änderung
nach einer Bestätigung).

![Detaillierte GPIO-Pinbelegung des Flipper Zero](/img/remote/e77df2d4499cbbbc.jpg)

Ein druckbares PDF der Pinbelegung gibt es auf der
[offiziellen GPIO-Seite](https://docs.flipper.net/zero/gpio-and-modules).

## Elektrische Grenzwerte

- **Logikpegel:** 3,3 V CMOS. Jeder I/O-Pin führt über einen 51-Ω-Widerstand zum MCU und ist ESD-geschützt.
- **Strom pro Pin:** bis zu 20 mA.
- **Summe über alle I/O-Pins:** unter 5 W halten, sonst kann der Akkuschutz auslösen und der Flipper schaltet ab.
- **5-V-Toleranz:** nur für einen Pin, der als **Eingang** konfiguriert ist. Ein als Ausgang geschalteter Pin ist nicht
  5-V-tolerant. Verzichte auf Peripherie mit 5-V-Logik, solange du keinen Pegelwandler verwendest. Details in der
  ST-Application-Note
  [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3,3 V (Pin 9)

- Standardmäßig aktiv, maximale Last **1,2 A**.
- Die microSD-Karte wird von derselben Schiene versorgt. Während eines Firmware-Updates und beim Einbinden der Karte
  wird Pin 9 kurz abgeschaltet.

::: warning
Module mit großer kapazitiver Last nur bei ausgeschaltetem Flipper anschließen, sonst riskierst du beschädigte Daten
auf der microSD-Karte.
:::

### +5 V (Pin 1)

- Über USB: Bei eingestecktem Kabel wird Pin 1 direkt aus USB versorgt. Niemals mehr als **1,2 A** ziehen.
- Über den Akku: Der Ausgang ist **standardmäßig aus**. Der Aufwärtswandler (OTG) liefert aktiviert bis zu **1,2 A**.

So schaltest du 5 V im Akkubetrieb ein:

1. Öffne `Main Menu → GPIO`.
2. Wähle `5V on GPIO` und schalte mit <kbd>→</kbd> auf `ON`.

Weitere Wege zum Umschalten:

- CLI: `power 5v 1` / `power 5v 0` (siehe [CLI](/de/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` für externe IR-Module.
- Apps wie Sub-GHz (externes CC1101) und [SIM800](/de/gpio/sim800) fordern es automatisch an, und ein
  [Expansion-Modul](/de/gpio/expansion-modules) kann es über sein Protokoll anfordern.

::: tip Wie die Firmware mit 5 V umgeht
Wird 5 V angefordert, während USB-Strom anliegt, verschiebt der Power-Dienst das Einschalten des Aufwärtswandlers und
aktiviert ihn selbst, sobald USB abgezogen wird. Meldet der Ladecontroller einen OTG-Fehler (Überlast oder Kurzschluss),
wird 5 V abgeschaltet und die Anforderung verworfen — du musst sie erneut aktivieren.
:::

## Pins im DFU-Modus

Im DFU-Modus (Bootloader) wechseln die I/O-Pins außer Pin 17 ihren Zustand gemäß der Application-Note
[AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf)
von STMicroelectronics (Tabelle „STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode“). Denk daran,
wenn ein Modul auf Pin-Pegel reagiert, während du den Flipper [wiederherstellst](/de/start/recovery).

## Modul einstecken

- **Ohne Silikonhülle:** Schiebe das Modul bis zum Anschlag hinein, sodass zwischen Flipper und Modul keine Pins mehr
  zu sehen sind. Das kann etwas Kraft brauchen.
- **Mit Silikonhülle:** Schiebe es hinein, bis in der Mitte kein Spalt zwischen Hülle und Modul mehr bleibt.

![Modul bis zum Anschlag eingesteckt](/img/remote/52e7045a797ed1c4.png)

## Siehe auch

- [GPIO-App](/de/gpio/gpio-app)
- [Externe Module](/de/gpio/external-modules)
- [Schaltpläne des Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)
