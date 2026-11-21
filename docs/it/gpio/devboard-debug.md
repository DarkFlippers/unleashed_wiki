---
title: "Devboard: debug e log"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Devboard: debug e log

Con la [Devboard configurata](/it/gpio/devboard) puoi fare il debug del firmware da VS Code e leggere i log del
Flipper via UART.

## Come funziona

La Devboard è la sonda di debug tra il debugger sul tuo computer (via USB o Wi-Fi) e l'MCU del Flipper. Comunica con
il Flipper tramite **Serial Wire Debug**:

- **pin 10** — SWCLK (Serial Wire Clock);
- **pin 12** — SWDIO (Serial Wire Debug Data I/O).

![Hardware della Devboard](/img/remote/06e0a9eb98e4130d.jpg)

## Modalità di debug

| Connessione | Modalità disponibili |
|---|---|
| Wi-Fi | Solo Black Magic |
| USB | Black Magic (predefinita) o DAPLink |

La modalità Black Magic non supporta la consapevolezza dei thread dell'RTOS; tutto il resto funziona.

### Cambiare la modalità USB

Curiosamente, la modalità USB si cambia via Wi-Fi:

1. Apri l'interfaccia web della scheda (<http://192.168.4.1> in modalità access point o <http://blackmagic.local> in
   modalità client, vedi [connessione](/it/gpio/devboard)).
2. Nella scheda **WiFi** imposta **USB mode** su **BlackMagicProbe** o **DapLink**.
3. Clicca **SAVE**, poi **REBOOT**.
4. In VS Code seleziona il debugger corrispondente (vedi sotto).

## Fare il debug del firmware in VS Code

### Prerequisiti

1. Installa [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Clona e compila il firmware. Per Unleashed:

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Gli stessi passaggi funzionano con il repository stock `flipperdevices/flipperzero-firmware`.) Altro sulla
   compilazione: [Compilare il firmware](/it/dev/build), [FBT](/it/dev/fbt).

### Avviare una sessione

1. Installa sul Flipper il firmware che hai appena compilato, attraverso la Devboard:

   ```bash
   ./fbt flash
   ```

2. Apri la cartella del firmware in **VS Code** e installa le estensioni consigliate (dalla notifica, oppure con
   `@recommended` nella scheda Estensioni).
3. Genera la configurazione per VS Code:

   ```bash
   ./fbt vscode_dist
   ```

4. In **Run and Debug** scegli:
   - **Attach FW (blackmagic)** — via Wi-Fi o USB;
   - **Attach FW (DAP)** — solo USB, con la scheda in modalità DAPLink.

   Via USB il debugger deve corrispondere alla **USB mode** della scheda (verificala nell'interfaccia web).
5. Clicca ▷ **Start Debugging**. Il firmware si arresta all'avvio della sessione; clicca **Continue** nella barra degli
   strumenti per lasciarlo proseguire.

![Debug in VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Vedi anche la [guida al debug di VS Code](https://code.visualstudio.com/docs/editor/debugging) e
[Debug](/it/dev/debugging).

## Leggere i log

La Devboard legge l'output di log del Flipper dalla sua UART, indipendentemente dal sistema operativo del Flipper.
Così vedi i log durante l'avvio, gli aggiornamenti e i crash, che il comando CLI `log` non può mostrare. I log sono
disponibili **solo via USB**.

### Impostare il livello e il dispositivo di log

1. Apri `Main Menu → Settings → System`.
2. `Log Level`: `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device`: lascia `USART` (pin 13/14), dove la Devboard è in ascolto. `LPUART` invia i log sui pin 15/16,
   `None` disattiva i log su UART.

::: tip
Se un altro modulo ha bisogno dei pin 13/14 (scheda Wi-Fi, SIM800, GPS), imposta `Log Device` su `LPUART` o `None` così
l'output dei log non interferisce.
:::

### macOS

1. Installa [Homebrew](https://brew.sh/), poi `brew install minicom`.
2. Spegni il Flipper, collega la Devboard, riaccendi.
3. Esegui `ls /dev/cu.*`, collega la Devboard via USB ed eseguilo di nuovo. Compaiono due nuovi dispositivi, per
   esempio `/dev/cu.usbmodemblackmagic1` e `/dev/cu.usbmodemblackmagic3`.
4. Apri quello con il **numero più alto**:

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. I log scorrono nel terminale. Esci dal menu di minicom o chiudi la finestra.

### Linux

1. Installa minicom, per esempio con `sudo apt install minicom`.
2. Spegni il Flipper, collega la Devboard, riaccendi.
3. Esegui `ls /dev/tty*`, collega la Devboard via USB ed eseguilo di nuovo. Compaiono due nuovi dispositivi, per
   esempio `/dev/ttyACM0` e `/dev/ttyACM1`.
4. Apri quello con il numero più alto:

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Se non compare nulla, prova l'altro dispositivo.

### Windows

1. Installa [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Spegni il Flipper, collega la Devboard, riaccendi e collega la Devboard via USB.
3. In **Gestione dispositivi → Porte (COM e LPT)** prendi nota della nuova porta COM.
4. In PuTTY scegli **Serial**, inserisci la porta in **Serial line**, imposta **Speed** su **230400** e clicca
   **Open**.

![Impostazioni di PuTTY](/img/remote/2bb43453a91a142e.jpg)

## Argomenti correlati

- [Devboard: primi passi](/it/gpio/devboard)
- [Devboard: aggiornamento del firmware](/it/gpio/devboard-firmware)
- [CLI](/it/dev/cli)
