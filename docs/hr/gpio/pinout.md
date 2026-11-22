---
title: Raspored GPIO pinova
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# Raspored GPIO pinova

Flipper Zero ima 18-pinski priključak razmaka 2,54 mm na gornjem rubu. Sadrži naponske izlaze, masu, 13 I/O pinova povezanih s mikrokontrolerom STM32WB55, SWD linije za otklanjanje pogrešaka i 1-Wire liniju koju dijeli s iButtonom.

![Funkcije GPIO pinova Flipper Zera](/img/remote/b75cf29833cf8de8.jpg)

## Tablica pinova

Brojevi pinova broje se od **pina 1 (+5 V)**. Nazivi priključaka (`PA7`, `PC0`, …) nazivi su koje firmver koristi na zaslonu i u CLI-ju.

| Pin | Naziv | Glavne funkcije | Napomene |
|---|---|---|---|
| 1 | +5V | Izlaz napajanja 5 V | Isključeno na bateriji dok se ne omogući, pogledajte niže |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | Vanjski CC1101 / NRF24 MOSI |
| 3 | PA6 | SPI MISO, ADC | Vanjski CC1101 / NRF24 MISO |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | Vanjski CC1101 / NRF24 CS; USB-UART DE/RE pin |
| 5 | PB3 | SPI SCK | Vanjski CC1101 / NRF24 SCK |
| 6 | PB2 | GPIO | Vanjski CC1101 GDO0, NRF24 CE |
| 7 | PC3 | GPIO, ADC | Upravljanje pojačalom vanjskog CC1101 |
| 8 | GND | Masa | |
| 9 | 3V3 | Izlaz napajanja 3.3 V | Zadano uključeno |
| 10 | PA14 | SWCLK | Otklanjanje pogrešaka (SWD) |
| 11 | GND | Masa | |
| 12 | PA13 | SWDIO | Otklanjanje pogrešaka (SWD) |
| 13 | PB6 | USART TX | Zadani UART za USB-UART most, zapisnike, module za proširenje |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Drugi UART; vanjski I2C podatci |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Drugi UART; vanjski I2C takt |
| 17 | PB14 | 1-Wire | iButton linija |
| 18 | GND | Masa | |

Firmver označava pinove 10, 12, 13, 14 i 17 kao **debug pinove**: skriveni su u `GPIO Manual Control`, a CLI naredba `gpio` prikazuje ih samo kada je uključen Debug način (i traži potvrdu prije njihove izmjene).

![Detaljni raspored GPIO pinova Flipper Zera](/img/remote/e77df2d4499cbbbc.jpg)

PDF verzija rasporeda pinova spremna za ispis dostupna je na [službenoj GPIO stranici](https://docs.flipper.net/zero/gpio-and-modules).

## Električna ograničenja

- **Logička razina:** 3,3 V CMOS. Svaki I/O pin spojen je na MCU preko otpornika od 51 Ω i ima ESD zaštitu.
- **Struja po pinu:** do 20 mA.
- **Ukupno s I/O pinova:** držite ispod 5 W, inače se može aktivirati zaštita baterije i Flipper će se isključiti.
- **Tolerancija na 5 V:** samo za pin konfiguriran kao **ulaz**. Pin postavljen kao izlaz nije tolerantan na 5 V. Izbjegavajte periferiju s 5 V logikom osim ako ne koristite pretvarač logičkih razina. Pojedinosti: ST aplikacijska bilješka [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3.3 V (pin 9)

- Zadano omogućeno, maksimalno opterećenje **1,2 A**.
- microSD kartica napaja se s iste naponske linije. Pin 9 nakratko se isključuje tijekom ažuriranja firmvera i prilikom montiranja kartice.

::: warning
Module s velikim kapacitivnim opterećenjem priključujte samo dok je Flipper isključen, inače riskirate oštećenje podataka na microSD kartici.
:::

### +5 V (pin 1)

- Preko USB-a: kada je kabel priključen, pin 1 napaja se izravno s USB-a. Nikada nemojte povlačiti više od **1,2 A**.
- S baterije: izlaz je **zadano isključen**. Podizni pretvarač (OTG) daje do **1,2 A** kada je omogućen.

Za uključivanje 5 V dok uređaj radi na bateriji:

1. Otvorite `Main Menu → GPIO`.
2. Odaberite `5V on GPIO` i prebacite na `ON` tipkom <kbd>→</kbd>.

Drugi načini uključivanja:

- CLI: `power 5v 1` / `power 5v 0` (pogledajte [CLI](/hr/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` za vanjske IR module.
- Aplikacije poput Sub-GHz (vanjski CC1101) i [SIM800](/hr/gpio/sim800) automatski ga traže, a [modul za proširenje](/hr/gpio/expansion-modules) može ga zatražiti putem svog protokola.

::: tip Kako firmver upravlja naponom od 5 V
Ako zatražite 5 V dok je prisutno USB napajanje, servis za napajanje odgađa uključivanje podiznog pretvarača i sam ga uključuje čim se USB odspoji. Ako punjač javi OTG pogrešku (preopterećenje ili kratki spoj), 5 V se isključuje i zahtjev se briše, pa ga morate ponovno omogućiti.
:::

## Pinovi u DFU načinu

U DFU načinu (bootloader) I/O pinovi, osim pina 17, mijenjaju stanje prema dokumentu tvrtke STMicroelectronics [AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf) (tablica "STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode"). Imajte to na umu ako neki modul reagira na stanja pinova dok [oporavljate](/hr/start/recovery) Flipper.

## Umetanje modula

- **Bez silikonske maske:** gurnite modul do kraja tako da se između Flippera i modula ne vide pinovi. Možda će biti potrebno malo sile.
- **U silikonskoj maski:** gurajte ga dok u sredini ne nestane razmak između maske i modula.

![Modul umetnut do kraja](/img/remote/52e7045a797ed1c4.png)

## Povezano

- [GPIO aplikacija](/hr/gpio/gpio-app)
- [Vanjski moduli](/hr/gpio/external-modules)
- [Sheme Flipper Zera](https://docs.flipper.net/zero/development/hardware/schematic)
