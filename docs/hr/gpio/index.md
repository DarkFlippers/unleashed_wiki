---
title: GPIO i moduli
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO i moduli

18-pinski konektor na vrhu Flipper Zera pretvara ga u hardverski alat: može napajati vanjske module i komunicirati s njima,
djelovati kao USB-UART adapter, ručno mijenjati stanja pinova za testiranje i služiti kao cilj za hardverski debugger.

![GPIO konektor na Flipper Zeru](/img/remote/f9f4fe12522d6f9d.png)

## Osnove

| Stranica | Što je unutra |
|---|---|
| [GPIO raspored pinova](/hr/gpio/pinout) | Svih 18 pinova, naponi, ograničenja struje, 5 V na pinu 1, tolerancija 3,3 V / 5 V |
| [GPIO aplikacija](/hr/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; CLI `gpio` i `i2c` |
| [Vanjski moduli](/hr/gpio/external-modules) | Pregled vrsta modula i koje pinove svaki koristi |
| [Moduli za proširenje](/hr/gpio/expansion-modules) | `Settings → Expansion Modules` i Expansion Module Protocol |
| [Moduli i njihove aplikacije](/hr/gpio/module-apps) | Svaki modul koji paketi aplikacija podržavaju i što svaka aplikacija radi |

## Moduli

| Stranica | Modul |
|---|---|
| [Vanjski CC1101](/hr/subghz/external-cc1101) | Sub-GHz radio sa snažnijim ulaznim stupnjem (obrađeno u odjeljku Sub-GHz) |
| [ESP32 / Wi-Fi](/hr/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, Unleashed web flasher i wardriving karta |
| [NRF24](/hr/gpio/nrf24) | 2,4 GHz nRF24L01 sniffer i MouseJack |
| [SIM800](/hr/gpio/sim800) | GSM modul: pozivi, SMS, imenik, USSD (ugrađena Unleashed aplikacija) |
| [GPS](/hr/gpio/gps) | Lokacija s popratnog telefona (GPS servis) i NMEA GPS moduli na UART-u |
| [Video Game Module](/hr/gpio/video-game-module) | RP2040 modul s video izlazom i senzorom pokreta |

## Wi-Fi Developer Board

| Stranica | Što je unutra |
|---|---|
| [Devboard: početak rada](/hr/gpio/devboard) | Priprema Flippera, priključivanje, USB i Wi-Fi povezivanje |
| [Devboard: otklanjanje pogrešaka i zapisnici](/hr/gpio/devboard-debug) | Black Magic / DAPLink, VS Code debugging, čitanje UART zapisnika |
| [Devboard: ažuriranje firmvera](/hr/gpio/devboard-firmware) | Flashanje vlastitog firmvera ploče pomoću uFBT-a |

::: tip Unleashed
Unleashed odmah po instalaciji donosi dodatne GPIO alate: aplikaciju [SIM800](/hr/gpio/sim800) (`Apps → GPIO → SIM800`), podršku za vanjski
CC1101 s upravljanjem pojačalom u Sub-GHz aplikaciji, izlaz za vanjski IR modul u `Infrared → GPIO Settings` te velik
broj GPIO dodataka u dodatnim paketima aplikacija. Pogledajte [Vanjski moduli](/hr/gpio/external-modules).
:::

::: warning Prije priključivanja bilo čega
Isključite Flipper prije povezivanja modula i gurnite modul do kraja u konektor. Priključivanje modula s velikim kapacitivnim
opterećenjem dok je uređaj uključen može oštetiti microSD karticu, jer kartica i pin 9 dijele istu 3,3 V naponsku liniju.
:::
