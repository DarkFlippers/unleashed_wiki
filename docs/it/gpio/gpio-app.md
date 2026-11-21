---
title: App GPIO
order: 20
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli]
sources: [flipper-docs, unleashed-src]
---
# App GPIO

L'app **GPIO** integrata (`Main Menu → GPIO`) ha tre voci:

| Voce | Cosa fa |
|---|---|
| `USB-UART Bridge` | Trasforma il Flipper in un adattatore USB-seriale sui pin 13/14 o 15/16 |
| `GPIO Manual Control` | Porta a livello alto i pin utente mentre tieni premuto <kbd>OK</kbd> |
| `5V on GPIO` | `OFF` / `ON`: l'uscita a 5 V sul pin 1 |

![Menu dell'app GPIO: USB-UART Bridge, GPIO Manual Control, 5V on GPIO impostato su OFF](/screens/gpio/menu.png)

I numeri dei pin e le tensioni sono nella pagina del [pinout](/it/gpio/pinout).

## USB-UART Bridge

Usalo per dialogare con la console di un router, una scheda ESP32/ESP8266, un modulo GSM o GPS, o qualsiasi
dispositivo seriale a 3,3 V da un computer, con il Flipper nel ruolo di adattatore.

1. Collega il dispositivo: **TX del Flipper → RX del dispositivo**, **RX del Flipper → TX del dispositivo** e una
   massa comune (pin 8, 11 o 18). Per impostazione predefinita il TX è il pin 13 e l'RX il pin 14.
2. Collega il Flipper al computer via USB.
3. Apri `Main Menu → GPIO → USB-UART Bridge`. La schermata mostra `USB Serial`, il numero di `COM PORT`, i pin TX/RX,
   i contatori di byte e la velocità in baud attuale.
4. Premi <kbd>←</kbd> (`Config`) per configurarlo (tabella sotto), poi <kbd>BACK</kbd> per tornare alla schermata di
   stato.
5. Apri la porta in un programma di terminale (PuTTY, minicom, screen, il monitor seriale di Arduino…).
6. Per terminare premi <kbd>BACK</kbd> e confermi `Exit USB-UART?` con `Exit` (oppure scegli `Stay`).

![Schermata di stato dell'USB-UART Bridge: USB Serial, COM PORT 0, TX pin 13, RX pin 14, contatori di byte, Baud 115200](/screens/gpio/usb_uart.png)

Mentre i dati scorrono il LED lampeggia in **blu sul TX** e in **verde sull'RX**, e la retroilluminazione resta
accesa.

### Schermata di configurazione

![Config dell'USB-UART Bridge: USB Channel, Baudrate, UART Pins, RTS/DTR Pins, DE/RE Pin](/screens/gpio/usb_uart_config.png)

| Impostazione | Valori | Significato |
|---|---|---|
| `USB Channel` | `0 (CLI)`, `1` | `0 (CLI)`: il bridge prende il controllo della porta seriale USB principale, e la CLI è disattivata mentre è in funzione. `1`: il Flipper espone due porte seriali; la CLI resta sulla prima, il bridge usa la seconda |
| `Baudrate` | `Host`, 1200 … 921600 | `Host` segue la velocità in baud impostata dal programma di terminale sulla porta. Un numero forza una velocità fissa (1200, 2400, 4800, 9600, 19200, 28800, 38400, 57600, 115200, 230400, 460800, 921600) |
| `UART Pins` | `13,14`, `15,16` | USART sui pin 13 (TX) / 14 (RX), oppure LPUART sui pin 15 (TX) / 16 (RX) |
| `RTS/DTR Pins` | `None`, `2,3`, `6,7`, `16,15` | Replica le linee RTS e DTR dell'host (primo pin RTS, secondo DTR, attivi a livello basso). `16,15` non è disponibile quando `UART Pins` è `15,16` |
| `DE/RE Pin` | `None`, `4` | Pilota il pin 4 come segnale di direzione (driver enable) per un transceiver RS-485 |

::: tip Programmare le schede ESP
L'uscita RTS/DTR è esattamente ciò che si aspettano i circuiti di auto-reset/boot delle schede ESP8266/ESP32 e
Arduino. Collega i due pin alla logica EN/RST e BOOT/GPIO0 della scheda (attraverso la solita coppia di transistor) ed
esptool può portarla nel bootloader senza premere pulsanti.
:::

### Se compare "Connection Is Active!"

Il bridge non può partire se qFlipper, l'app mobile o un'altra sessione RPC occupa la connessione USB. La schermata
mostra `Connection Is Active! Disconnect from PC or phone to use this function.` Chiudi qFlipper o disconnetti l'app e
riprova.

## GPIO Manual Control

Un modo rapido per verificare i collegamenti o un LED / relè su un pin.

1. Apri `Main Menu → GPIO → GPIO Manual Control`. La schermata mostra `GPIO Output Mode Test`.
2. Scegli il pin con <kbd>←</kbd> / <kbd>→</kbd>: `PA7` (2), `PA6` (3), `PA4` (4), `PB3` (5), `PB2` (6), `PC3` (7),
   `PC1` (15), `PC0` (16) oppure `ALL`.
3. **Tieni premuto** <kbd>OK</kbd>: il pin (o tutti) passa a livello alto, 3,3 V, e il LED verde si accende.
   Rilasciando, il pin torna a livello basso.

Tutti i pin elencati sono uscite push-pull mentre questa schermata è aperta; all'uscita tornano in modalità ad alta
impedenza (analogica). Non collegare nulla che piloti a sua volta questi pin durante la prova.

## 5V on GPIO

Attiva o disattiva l'uscita a 5 V sul pin 1. Seleziona la voce e cambiala con <kbd>←</kbd> / <kbd>→</kbd>.
L'impostazione non è una modalità dell'app: i 5 V restano attivi anche dopo che esci dall'app GPIO, finché non li
disattivi, non spegni il Flipper o non si verifica un errore da sovraccarico. Per i limiti di corrente vedi il
[pinout](/it/gpio/pinout).

## Strumenti da CLI

Nella [CLI](/it/dev/cli) del Flipper sono disponibili due comandi correlati:

```text
gpio mode <pin_name> <0|1>   # 0 - input, 1 - output
gpio set <pin_name> <0|1>    # set output low/high
gpio read <pin_name>         # read input level
power 5v <0|1>               # 5 V on pin 1 off/on
i2c                          # scan the external I2C bus
```

- I nomi dei pin sono i nomi delle porte (`PA7`, `PC0`, …). I pin di debug (`PA13`, `PA14`, `PB6`, `PB7`, `PB14`)
  sono accettati solo con la modalità Debug attiva, e la CLI chiede prima
  `Changing this pin mode may damage hardware...`.
- `i2c` esegue una scansione degli indirizzi su **PC0 (SCL, pin 16) / PC1 (SDA, pin 15)** a 100 kHz, con indirizzi a
  7 bit, e stampa una tabella in cui `#` indica un dispositivo che ha risposto. La maggior parte delle schedine di
  breakout I2C ha già le resistenze di pull-up; se non compare nulla, verifica che la tua le abbia.

::: tip Unleashed
Per un lavoro più approfondito sull'I2C (sniffer, lettura e scrittura dei registri) e sui sensori, vedi i plugin
`i2c Tools` e `Unitemp` nei pacchetti di app extra, elencati in
[Moduli esterni](/it/gpio/external-modules).
:::

## Risoluzione dei problemi

- **Caratteri illeggibili nel terminale:** la velocità in baud non corrisponde. Imposta `Baudrate` sulla velocità del
  dispositivo, oppure lascia `Host` e imposta la velocità nel programma di terminale.
- **Nessun dato:** scambia TX e RX, verifica che la massa sia in comune e che `UART Pins` corrisponda ai tuoi
  collegamenti.
- **La CLI è sparita:** `USB Channel` è su `0 (CLI)`. Esci dal bridge, oppure usa il canale `1`.
- **5V on GPIO non resta attivo:** il carico assorbe troppo (spegnimento per errore) oppure un grosso condensatore sul
  modulo fa scattare il convertitore boost all'avvio. Spegni il Flipper, collega il modulo, poi accendi.

## Argomenti correlati

- [Pinout GPIO](/it/gpio/pinout)
- [Moduli esterni](/it/gpio/external-modules)
- [Devboard: debug e log](/it/gpio/devboard-debug)
