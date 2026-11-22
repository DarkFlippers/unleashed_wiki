---
title: Vanjski moduli
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Vanjski moduli

Većina dodatnih pločica za Flipper Zero spaja se izravno u GPIO priključak i komunicira s njim putem jedne od triju
sabirnica: **SPI** (pinovi 2–5), **UART** (pinovi 13/14 ili 15/16) ili **I2C** (pinovi 15/16). Tablice u nastavku
pokazuju što upravlja kojim modulom i koje pinove zauzima, kako biste mogli znati koji se moduli mogu koristiti zajedno.

## Vrste modula

| Modul | Sabirnica / pinovi | Upravlja | Stranica |
|---|---|---|---|
| Vanjski CC1101 (Sub-GHz) | SPI 2–5, GDO0 na 6, upravljanje pojačalom na 7 | Ugrađena Sub-GHz aplikacija (`Radio Settings → Module → External`) | [Vanjski CC1101](/hr/subghz/external-cc1101) |
| NRF24L01 (2.4 GHz) | SPI 2–5, CE na 6 | Dodaci NRF24 Sniffer / Mouse Jacker | [NRF24](/hr/gpio/nrf24) |
| ESP32 / ESP8266 Wi-Fi pločice, Wi-Fi Devboard | UART 13/14 (SWD 10/12 za debugiranje) | Dodaci Marauder, Wi-Fi Scanner, Deauther; firmver Black Magic | [ESP32](/hr/gpio/esp32), [Devboard](/hr/gpio/devboard) |
| SIM800C / SIM800L GSM | UART 13/14 ili 15/16, napajanje s pina 1 | Ugrađena aplikacija SIM800 | [SIM800](/hr/gpio/sim800) |
| GPS (NMEA) | UART | Dodatak `[NMEA] GPS` | [GPS](/hr/gpio/gps) |
| Video Game Module | UART 13/14, pinovi 2–7, napajanje | Firmver Flippera + firmver modula | [Video Game Module](/hr/gpio/video-game-module) |
| Moduli za proširenje (protokol) | UART 13/14 ili 15/16 | `Settings → Expansion Modules` | [Moduli za proširenje](/hr/gpio/expansion-modules) |
| Vanjska IR LED dioda / IR pojačivač | Pin 2 (PA7), 5 V na pinu 1 | Ugrađena aplikacija Infrared (`GPIO Settings`) | pogledajte ispod |
| Senzori temperature / vlažnosti / tlaka | ovisi o senzoru (pogledajte README) | Dodatak `Unitemp` | [Unitemp README](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Bilo koji I2C uređaj | I2C 15/16 | Dodatak `i2c Tools`, CLI `i2c` | [Aplikacija GPIO](/hr/gpio/gpio-app) |
| ESP32-CAM | UART | Dodatak Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Sefovi Sentry Safe / Master Lock (dvije žice) | Pin 15 (C1) + GND 8 | Dodatak SentrySafe | [SentrySafe](/hr/apps/sentry-safe) |

::: tip Unleashed
Unleashed izravno u firmver dodaje podršku za:
- **Vanjski CC1101** putem hardverskog SPI-ja, s upravljanjem vanjskim pojačalom / LED diodama (`Ext Amp & LEDs`, zadano uključeno) u
  `Sub-GHz → Radio Settings`.
- **Vanjske IR module** u `Infrared → GPIO Settings` (automatsko prepoznavanje kao u tvorničkom firmveru).
- GSM aplikaciju **SIM800** (`Apps → GPIO → SIM800`).

Vanjski radiomoduli rade na svakom firmveru, ne samo na firmveru Unleashed. @quen0n je napisao prvu implementaciju za
CC1101, za Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); onu koja se danas koristi
napisao je **Skorp** u službenom firmveru, a Unleashed koristi upravo nju.

Dodaci za ostale module (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) nalaze se u paketima Base i Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Pogledajte
[Aplikacije na SD kartici](/hr/apps/sd-card-apps).
:::

## Sukobi pinova {#pin-conflicts}

Moduli koji dijele sabirnicu ne mogu raditi istovremeno bez dodatne pažnje. Najčešći sukobi:

| Pinovi | Zauzima ih |
|---|---|
| 2, 3, 4, 5 | SPI: vanjski CC1101, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | CC1101 GDO0 / NRF24 CE |
| 7 | Upravljanje pojačalom za CC1101 (moduli E07) |
| 13, 14 | USART: Wi-Fi pločice, SIM800, moduli za proširenje, Video Game Module, USB-UART most, ispis zapisnika |
| 15, 16 | LPUART ili I2C (ne oboje istovremeno) |
| 10, 12 | SWD debugiranje (Devboard) |

Ako koristite kombiniranu („combo”) pločicu koja na jednom PCB-u nosi više radija (na primjer CC1101 + NRF24 + ESP32),
slijedite dokumentaciju te pločice za točne pinove i postavke dodataka koje svaki radio koristi.

## Vanjski IR moduli

1. Spojite ulaz upravljačkog sklopa IR LED diode na **pin 2 (A7)**, GND na GND, a napajanje s pina 1 (5 V) ako ga modul treba.
2. Otvorite `Main Menu → Infrared → GPIO Settings`.
3. Postavite `Signal Output`:
   - `Flipper` — ugrađena IR LED dioda;
   - `2 (A7)` — vanjski modul na pinu 2;
   - `Detect` — firmver automatski prepoznaje spojeni modul.
4. Kada je odabrano `2 (A7)`, ovdje možete uključiti ili isključiti i `5V on GPIO`. Uz `Detect` stavka za 5 V prikazuje `Auto`.

Pogledajte odjeljak [Infrared](/hr/infrared/) za korištenje daljinskih upravljača.

## Opća pravila

1. **Isključite uređaj prije spajanja.** Spajanje velikih kondenzatora pod naponom može oštetiti SD karticu.
2. **Logika od 3.3 V.** Nemojte spajati Flipperove izlaze na logiku od 5 V; ulazi podnose 5 V samo dok su konfigurirani kao ulazi.
3. **Poštujte ograničenja struje:** 1.2 A na pinu 1 i pinu 9, 20 mA po I/O pinu. Pogledajte [raspored pinova](/hr/gpio/pinout).
4. **Ukrižite TX i RX** na UART modulima: Flipperov TX ide na RX modula.
5. **Umetnite do kraja.** Djelomično umetnut modul stvara povremeni kontakt.

## Povezano

- [GPIO raspored pinova](/hr/gpio/pinout)
- [Aplikacija GPIO](/hr/gpio/gpio-app)
- [Moduli za proširenje](/hr/gpio/expansion-modules)
- [Moduli i njihove aplikacije](/hr/gpio/module-apps)
