---
title: "Dev board : mise à jour du firmware"
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md]
sources: [unleashed-docs]
---
# Dev board : mise à jour du firmware

Comment mettre à jour (ou restaurer) le firmware de la Wi-Fi Developer Board elle-même, à l'aide de **uFBT**. Il ne
s'agit pas du firmware du Flipper : pour celui-ci, voir [Mise à jour](/fr/start/updating).

## Étape 1. Installer uFBT

[uFBT (micro Flipper Build Tool)](https://pypi.org/project/ufbt/) compile et débogue les applications, flashe des
firmwares, crée des configurations VS Code et flashe la Wi-Fi Devboard.

**Linux et macOS**

1. Installez `pipx` ([instructions](https://pipx.pypa.io/stable/installation/)) et redémarrez le terminal.
2. Installez uFBT :

   ```bash
   pipx install ufbt
   ```

**Windows**

1. Installez la dernière version de [Python](https://www.python.org/downloads/windows/).
2. Dans PowerShell :

   ```powershell
   py -m pip install --user pipx
   py -m pipx ensurepath
   ```

3. Redémarrez PowerShell, puis :

   ```powershell
   pipx install ufbt
   ```

## Étape 2. Mettre la carte en mode bootloader

1. Listez les périphériques série : macOS `ls /dev/cu.*`, Linux `ls /dev/tty*`, Windows Gestionnaire de périphériques →
   **Ports (COM et LPT)**.
2. Connectez la dev board à l'ordinateur avec un câble USB-C.
3. Entrez en mode bootloader :
   1. appuyez sur **BOOT** et maintenez-le ;
   2. appuyez puis relâchez **RESET** en maintenant **BOOT** ;
   3. relâchez **BOOT**.
4. Listez de nouveau les périphériques et notez le nouveau venu.

![Boutons bootloader de la dev board](/img/remote/060af5decf4b567c.jpg)

## Étape 3. Flasher

Linux et macOS :

```bash
python3 -m ufbt devboard_flash
```

Windows (PowerShell) :

```powershell
py -m ufbt devboard_flash
```

Message de réussite : `WiFi board flashed successfully`.

### Si le flashage échoue

Des erreurs comme

```text
A fatal error occurred: Serial data stream stopped: Possible serial noise or corruption.
```

ou

```text
FileNotFoundError: [Errno 2] No such file or directory: '/dev/cu.usbmodem01'
```

se corrigent généralement ainsi :

- débranchez puis rebranchez la carte, et repassez en mode bootloader ;
- un autre port USB ;
- un autre câble USB-C.

## Étape 4. Terminer

1. Appuyez sur **RESET** sur la carte.
2. Débranchez puis rebranchez le câble USB-C.

La carte exécute désormais le dernier firmware Black Magic officiel. C'est également ainsi que vous la restaurez après
avoir flashé un autre firmware (par exemple [Marauder](/fr/gpio/esp32)). Continuez avec
[le branchement sur le Flipper](/fr/gpio/devboard).
