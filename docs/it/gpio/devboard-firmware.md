---
title: "Devboard: aggiornamento del firmware"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: aggiornamento del firmware

Come aggiornare (o ripristinare) il firmware della Wi-Fi Developer Board stessa, usando **uFBT**. Non si tratta del
firmware del Flipper: per quello vedi [Aggiornare](/it/start/updating).

## Passo 1. Installare uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) compila e fa il debug delle app, installa il
firmware, crea le configurazioni per VS Code e programma la Wi-Fi Devboard.

**Linux e macOS**

1. Installa `pipx` ([istruzioni](https://pipx.pypa.io/stable/installation/)) e riavvia il terminale.
2. Installa uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Installa l'ultima versione di [Python](https://www.python.org/downloads/windows/).
2. In PowerShell:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Riavvia PowerShell, poi:

   ```powershell
   pipx install ufbt
   ```

## Passo 2. Mettere la scheda in modalità bootloader

1. Elenca i dispositivi seriali: macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows Gestione dispositivi →
   **Porte (COM e LPT)**.
2. Collega la Devboard al computer con un cavo USB-C.
3. Entra in modalità bootloader:
   1. tieni premuto **BOOT**;
   2. premi e rilascia **RESET** mentre tieni premuto **BOOT**;
   3. rilascia **BOOT**.
4. Elenca di nuovo i dispositivi e prendi nota di quello nuovo.

![Pulsanti del bootloader della Devboard](/img/remote/060af5decf4b567c.jpg)

## Passo 3. Programmare

Linux e macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Messaggio di successo: `WiFi board flashed successfully`.

### Se la programmazione fallisce

Errori come

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

oppure

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

si risolvono di solito così:

- scollega e ricollega la scheda, poi entra di nuovo in modalità bootloader;
- prova un'altra porta USB;
- prova un altro cavo USB-C.

## Passo 4. Concludere

1. Premi **RESET** sulla scheda.
2. Scollega e ricollega il cavo USB-C.

La scheda ora esegue l'ultimo firmware Black Magic ufficiale. È anche il modo per ripristinarla dopo aver installato
altri firmware (per esempio [Marauder](/it/gpio/esp32)). Prosegui con
[il collegamento al Flipper](/it/gpio/devboard).
