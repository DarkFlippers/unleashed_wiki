---
title: Aplikacija GPIO
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# Aplikacija GPIO

Ugrađena aplikacija **GPIO** (`Main Menu → GPIO`) sadrži tri stavke:

| Stavka | Što radi |
|---|---|
| `USB-UART Bridge` | Pretvara Flipper u USB-na-serijski prilagodnik na pinovima 13/14 ili 15/16 |
| `GPIO Manual Control` | Postavlja korisničke pinove u visoko stanje dok držite <kbd>OK</kbd> |
| `5V on GPIO` | `OFF` / `ON`: 5 V izlaz na pinu 1 |

![Izbornik aplikacije GPIO: USB-UART Bridge, GPIO Manual Control, 5V on GPIO postavljen na OFF](/screens/gpio/menu.png)

Brojevi pinova i naponi nalaze se na stranici [raspored pinova](/hr/gpio/pinout).

## USB-UART Bridge

Koristite ga za komunikaciju s konzolom usmjerivača, ESP32/ESP8266 pločicom, GSM ili GPS modulom ili bilo kojim 3,3 V serijskim uređajem s računala, pri čemu Flipper služi kao prilagodnik.

1. Spojite uređaj: **Flipper TX → RX uređaja**, **Flipper RX → TX uređaja** i zajednički GND (pin 8, 11 ili 18). Zadano je TX pin 13, a RX pin 14.
2. Povežite Flipper s računalom putem USB-a.
3. Otvorite `Main Menu → GPIO → USB-UART Bridge`. Zaslon prikazuje `USB Serial`, broj `COM PORT`, TX/RX pinove, brojače bajtova i trenutnu brzinu prijenosa (baud rate).
4. Pritisnite <kbd>←</kbd> (`Config`) za postavljanje (tablica u nastavku), zatim <kbd>BACK</kbd> za povratak na zaslon statusa.
5. Otvorite priključak u terminalskom programu (PuTTY, minicom, screen, Arduino serial monitor…).
6. Za završetak pritisnite <kbd>BACK</kbd> i potvrdite `Exit USB-UART?` opcijom `Exit` (ili odaberite `Stay`).

![Zaslon statusa USB-UART Bridge: USB Serial, COM PORT 0, TX pin 13, RX pin 14, brojači bajtova, Baud 115200](/screens/gpio/usb_uart.png)

Dok podaci prolaze, LED dioda treperi **plavo za TX** i **zeleno za RX**, a pozadinsko osvjetljenje ostaje uključeno.

### Zaslon Config

![USB-UART Bridge Config: USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Postavka | Vrijednosti | Značenje |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)`: most preuzima glavni USB serijski priključak, CLI je onemogućen dok radi. `1`: Flipper izlaže dva serijska priključka; CLI ostaje na prvom, most koristi drugi |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` prati brzinu prijenosa koju terminalski program postavi na priključku. Broj prisilno postavlja fiksnu brzinu (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART na pinovima 13 (TX) / 14 (RX) ili LPUART na pinovima 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Izlaz linija RTS i DTR s računala (prvi pin RTS, drugi DTR, aktivno nisko). `16,15` nije ponuđeno kada je `UART Pins` postavljen na `15,16` |
| `DE/RE Pin` | `None`, `4` | Upravlja pinom 4 kao signalom smjera (driver enable) za RS-485 primopredajnik |

::: tip Programiranje ESP pločica
Izlaz RTS/DTR je ono što očekuju krugovi za automatsko resetiranje/pokretanje na ESP8266/ESP32 i Arduino pločicama. Spojite ta dva pina na EN/RST i BOOT/GPIO0 logiku pločice (putem uobičajenog para tranzistora) i esptool je može prebaciti u bootloader bez pritiskanja tipki.
:::

### Ako piše "Connection Is Active!"

Most se ne može pokrenuti dok qFlipper, mobilna aplikacija ili druga RPC sesija drži USB vezu. Na zaslonu piše `Connection Is Active! Disconnect from PC or phone to use this function.` Zatvorite qFlipper / prekinite vezu aplikacije i pokušajte ponovno.

## GPIO Manual Control

Brz način za provjeru ožičenja ili LED diode / releja na pinu.

1. Otvorite `Main Menu → GPIO → GPIO Manual Control`. Na zaslonu piše `GPIO Output Mode Test`.
2. Odaberite pin tipkama <kbd>←</kbd> / <kbd>→</kbd>: `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6), `PC3` (7), `PC1` (15), `PC0` (16) ili `ALL`.
3. **Držite** <kbd>OK</kbd>: pin (ili svi pinovi) prelazi u visoko stanje, 3,3 V, i svijetli zelena LED dioda. Pustite tipku i pin se vraća u nisko stanje.

Svi navedeni pinovi rade kao push-pull izlazi dok je ovaj zaslon otvoren; pri izlasku se vraćaju u način visoke impedancije (analogni). Ne spajajte ništa što samo pobuđuje te pinove tijekom testiranja.

## 5V on GPIO

Uključuje ili isključuje izlaz od 5 V na pinu 1. Odaberite stavku i promijenite je tipkama <kbd>←</kbd> / <kbd>→</kbd>. Postavka nije način rada aplikacije: 5 V ostaje uključeno i nakon izlaska iz aplikacije GPIO, sve dok ga ne isključite, ne isključite Flipper ili se ne dogodi preopterećenje. Za ograničenja struje pogledajte [raspored pinova](/hr/gpio/pinout).

## CLI alati

Dvije povezane naredbe dostupne su u Flipperovom [CLI-ju](/hr/dev/cli):

```text
gpio mode <pin_name> <0|1>   # 0 - ulaz, 1 - izlaz
gpio set <pin_name> <0|1>    # postavi izlaz na nisko/visoko stanje
gpio read <pin_name>         # pročitaj ulaznu razinu
power 5v <0|1>               # 5 V na pinu 1 isključeno/uključeno
i2c                          # skeniraj vanjsku I2C sabirnicu
```

- Nazivi pinova su nazivi priključaka (`PA7`, `PC0`, …). Pinovi za otklanjanje grešaka (`PA13`, `PA14`, `PB6`, `PB7`, `PB14`) prihvaćaju se samo kada je uključen Debug način rada, a CLI prvo pita `Changing this pin mode may damage hardware...`.
- `i2c` skenira adrese na **PC0 (SCL, pin 16) / PC1 (SDA, pin 15)** na 100 kHz, 7-bitno adresiranje, i ispisuje tablicu u kojoj `#` označava uređaj koji je odgovorio. Većina I2C pločica već ima pull-up otpornike; ako se ništa ne pojavi, provjerite ima li ih vaša.

::: tip Unleashed
Za napredniji rad s I2C-om (sniffer, čitanje i pisanje registara) i senzore pogledajte dodatke `i2c Tools` i `Unitemp` u dodatnim paketima aplikacija navedenima na stranici [Vanjski moduli](/hr/gpio/external-modules).
:::

## Rješavanje problema

- **Nečitljivi znakovi u terminalu:** brzina prijenosa se ne podudara. Postavite `Baudrate` na brzinu uređaja ili ostavite `Host` i postavite brzinu u terminalskom programu.
- **Nema nikakvih podataka:** zamijenite TX i RX, provjerite je li GND zajednički i provjerite odgovara li `UART Pins` vašem ožičenju.
- **CLI je nestao:** `USB Channel` je postavljen na `0 (CLI)`. Izađite iz mosta ili koristite kanal `1`.
- **5V on GPIO ne ostaje uključen:** trošilo vuče previše struje (zaštitno isključivanje) ili veliki kondenzator na modulu ruši boost pretvarač pri pokretanju. Isključite Flipper, spojite modul, zatim ponovno uključite Flipper.

## Povezano

- [Raspored GPIO pinova](/hr/gpio/pinout)
- [Vanjski moduli](/hr/gpio/external-modules)
- [Devboard: otklanjanje grešaka i zapisnici](/hr/gpio/devboard-debug)
