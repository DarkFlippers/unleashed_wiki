---
title: "Devboard: ažuriranje firmvera"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Devboard: ažuriranje firmvera

Kako ažurirati (ili vratiti izvorni) firmver same Wi-Fi razvojne ploče (Wi-Fi Developer Board), pomoću alata **uFBT**. Ovo nije firmver
samog Flippera: za njega pogledajte [Ažuriranje](/hr/start/updating).

## Korak 1. Instalirajte uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) prevodi i otklanja pogreške aplikacija, snima (flasha) firmver, stvara VS Code
konfiguracije i snima firmver na Wi-Fi Devboard.

**Linux i macOS**

1. Instalirajte `pipx` ([upute](https://pipx.pypa.io/stable/installation/)) i ponovno pokrenite terminal.
2. Instalirajte uFBT:

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Instalirajte najnoviji [Python](https://www.python.org/downloads/windows/).
2. U PowerShellu:

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Ponovno pokrenite PowerShell, zatim:

   ```powershell
   pipx install ufbt
   ```

## Korak 2. Stavite ploču u način bootloadera

1. Popišite serijske uređaje: macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows Device Manager → **Ports (COM & LPT)**.
2. Povežite Devboard s računalom pomoću USB-C kabela.
3. Uđite u način bootloadera:
   1. pritisnite i držite **BOOT**;
   2. pritisnite i pustite **RESET** dok držite **BOOT**;
   3. pustite **BOOT**.
4. Ponovno popišite uređaje i zabilježite novi uređaj.

![Tipke bootloadera na Devboardu](/img/remote/060af5decf4b567c.jpg)

## Korak 3. Snimanje (flash)

Linux i macOS:

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell):

```powershell
py -m ufbt devboard_flash
```

Poruka o uspjehu: `WiFi board flashed successfully`.

### Ako snimanje ne uspije

Pogreške kao što su

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

ili

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

obično se rješavaju na sljedeći način:

- odspajanjem i ponovnim spajanjem ploče te ponovnim ulaskom u način bootloadera;
- drugim USB priključkom;
- drugim USB-C kabelom.

## Korak 4. Završetak

1. Pritisnite **RESET** na ploči.
2. Odspojite i ponovno spojite USB-C kabel.

Ploča sada pokreće najnoviji službeni Black Magic firmver. Ovo je ujedno i način kako je možete vratiti u izvorno stanje nakon snimanja drugog
firmvera (npr. [Marauder](/hr/gpio/esp32)). Nastavite s [priključivanjem u Flipper](/hr/gpio/devboard).
