---
title: "Devboard: primi passi"
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/USB%20connection%20to%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Wi-Fi%20connection%20to%20the%20Devboard.md, https://docs.flipper.net/zero/development/hardware/devboard-schematics, https://docs.flipper.net/zero/development/hardware/devboard-stlinkv3]
sources: [unleashed-docs, flipper-docs]
---
# Wi-Fi Devboard: primi passi

La **Wi-Fi Developer Board** ufficiale è un modulo ESP32-S2 (ESP32-S2-WROVER-N4R2) per il connettore GPIO. Appena
estratta dalla confezione esegue il firmware **Black Magic Probe** e funziona da **sonda di debug**: collega il
debugger del tuo computer all'STM32 del Flipper via SWD, attraverso USB o Wi-Fi. Può anche inoltrare i log UART del
Flipper.

![Wi-Fi Developer Board](/img/remote/7a7349f75be87abb.jpg)

::: tip Non serve per installare il firmware
Aggiornare, compilare e caricare il proprio firmware funziona tutto via semplice USB. La Devboard serve solo per il
debug in tempo reale (GDB, breakpoint) e per leggere i log indipendentemente dal sistema operativo del Flipper. Per
usare la stessa scheda come strumento Wi-Fi (Marauder), vedi [ESP32 e Wi-Fi](/it/gpio/esp32).
:::

## Passo 1. Attivare la modalità Debug sul Flipper

1. Apri `Main Menu → Settings → System`.
2. Imposta `Debug` su `ON`.

La modalità Debug è necessaria per fare il debug delle app e sblocca le opzioni di debug nelle app e nella
[CLI](/it/dev/cli). Riattivala dopo ogni aggiornamento del firmware.

## Passo 2. Aggiornare il firmware della scheda

La scheda arriva con un firmware non recente. Aggiornalo prima di tutto:
[Devboard: aggiornamento del firmware](/it/gpio/devboard-firmware).

## Passo 3. Collegare la Devboard al Flipper

1. **Prima spegni il Flipper.** La scheda e la microSD condividono la linea a 3,3 V del Flipper; collegare a caldo un
   grande carico capacitivo può corrompere la scheda.
2. **Inseriscila a fondo.** Senza custodia: nessuno spazio tra Flipper e scheda (può servire un po' di forza). Con
   custodia in silicone: nessuno spazio al centro tra custodia e scheda.
3. Tieni premuto <kbd>BACK</kbd> per accendere il Flipper.

![Devboard inserita, Flipper senza custodia](/img/remote/4eb1e40120ff42bb.jpg)

## Passo 4. Collegarsi a un computer

### Via USB

L'USB si usa per il debug in modalità **Black Magic** o **DAPLink** e per leggere i log.

1. Elenca i dispositivi seriali sul computer:
   - **macOS:** `ls /dev/cu.*`
   - **Linux:** `ls /dev/tty*`
   - **Windows:** Gestione dispositivi → **Porte (COM e LPT)**
2. Collega la porta USB-C **della Devboard** al computer.
3. Elenca di nuovo i dispositivi: compaiono **due nuove porte**, entrambe appartenenti alla Devboard.

Se non compare nulla, prova un altro cavo (deve trasportare dati), un'altra porta USB o un altro computer.

### Via Wi-Fi: modalità access point (predefinita)

La scheda crea una rete propria. Il computer perde la sua normale connessione Wi-Fi mentre è collegato a essa.

1. Dal computer o dal telefono collegati alla rete Wi-Fi:
   - Nome: `blackmagic`
   - Password: `iamwitcher`
2. Apri <http://192.168.4.1> oppure <http://blackmagic.local> per l'interfaccia web della scheda.

Se la rete `blackmagic` non compare:

- reimposta la connessione Wi-Fi sul computer;
- la scheda potrebbe essere configurata come client (STA). Tieni premuto il pulsante **BOOT** della scheda per
  **10 secondi** per azzerarne le impostazioni; dopo il riavvio torna a essere un access point.

### Via Wi-Fi: modalità client (STA)

La scheda si unisce alla tua rete a 2,4 GHz già esistente, così mantieni l'accesso a internet.

1. Collegati alla scheda in modalità access point (vedi sopra) e apri <http://192.168.4.1>.
2. Seleziona la modalità **STA** e inserisci **SSID** e **password** della tua rete. Il pulsante **+** elenca le reti
   a 2,4 GHz nelle vicinanze (i 5 GHz non sono supportati).
3. Salva e riavvia la scheda.
4. Da quel momento apri <http://blackmagic.local> sulla tua rete normale.

Via Wi-Fi è disponibile solo il debug **Black Magic**.

## Hardware

- MCU: ESP32-S2-WROVER-N4R2.
- SWD verso il Flipper sul **pin 10 (SWCLK)** e sul **pin 12 (SWDIO)**; log UART sui pin USART 13/14 del Flipper.
- Schemi (PCB, ESP32-S2, alimentazione, connettori) e disegno di assemblaggio:
  [schemi della Wi-Fi Developer Board](https://docs.flipper.net/zero/development/hardware/devboard-schematics).

## Prossimi passi

- [Devboard: debug e log](/it/gpio/devboard-debug)
- [Devboard: aggiornamento del firmware](/it/gpio/devboard-firmware)
- Community: [Discord](https://discord.com/invite/flipper) (canale #wifi-devboard),
  [Reddit](https://www.reddit.com/r/flipperzero/)
