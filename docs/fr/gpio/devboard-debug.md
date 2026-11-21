---
title: "Dev board : débogage et logs"
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Debugging%20via%20the%20Devboard.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Devboard%20debug%20modes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Reading%20logs%20via%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-docs, unleashed-src]
---
# Dev board : débogage et logs

Une fois la [dev board configurée](/fr/gpio/devboard), vous pouvez déboguer le firmware depuis VS Code et lire les logs
du Flipper via l'UART.

## Fonctionnement

La dev board est la sonde de débogage placée entre le débogueur de votre ordinateur (en USB ou en Wi-Fi) et le MCU du
Flipper. Elle dialogue avec le Flipper en **Serial Wire Debug** :

- **broche 10** — SWCLK (Serial Wire Clock) ;
- **broche 12** — SWDIO (Serial Wire Debug Data I/O).

![Matériel de la dev board](/img/remote/06e0a9eb98e4130d.jpg)

## Modes de débogage

| Connexion | Modes disponibles |
|---|---|
| Wi-Fi | Black Magic uniquement |
| USB | Black Magic (par défaut) ou DAPLink |

Le mode Black Magic ne prend pas en charge la connaissance des threads du RTOS ; tout le reste fonctionne.

### Changer le mode USB

Curieusement, le mode USB se change par Wi-Fi :

1. Ouvrez l'interface web de la carte (<http://192.168.4.1> en mode point d'accès ou <http://blackmagic.local> en mode
   client, voir [connexion](/fr/gpio/devboard)).
2. Dans l'onglet **WiFi**, mettez **USB mode** sur **BlackMagicProbe** ou **DapLink**.
3. Cliquez sur **SAVE**, puis sur **REBOOT**.
4. Dans VS Code, sélectionnez le débogueur correspondant (ci-dessous).

## Déboguer le firmware dans VS Code

### Prérequis

1. Installez [Git](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).
2. Clonez et compilez le firmware. Pour Unleashed :

   ```bash
   git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
   cd unleashed-firmware
   ./fbt
   ```

   (Les mêmes étapes fonctionnent avec le dépôt d'origine `flipperdevices/flipperzero-firmware`.) Pour en savoir plus
   sur la compilation : [Compiler le firmware](/fr/dev/build), [FBT](/fr/dev/fbt).

### Démarrer une session

1. Flashez le firmware que vous venez de compiler via la dev board :

   ```bash
   ./fbt flash
   ```

2. Ouvrez le dossier du firmware dans **VS Code** et installez les extensions recommandées (notification, ou
   `@recommended` dans l'onglet Extensions).
3. Générez la configuration VS Code :

   ```bash
   ./fbt vscode_dist
   ```

4. Dans **Run and Debug**, choisissez :
   - **Attach FW (blackmagic)** — en Wi-Fi ou en USB ;
   - **Attach FW (DAP)** — en USB uniquement, carte en mode DAPLink.

   En USB, le débogueur doit correspondre au **USB mode** de la carte (vérifiez-le dans l'interface web).
5. Cliquez sur ▷ **Start Debugging**. Le firmware est mis en pause au démarrage de la session ; cliquez sur
   **Continue** dans la barre d'outils pour le laisser s'exécuter.

![Débogage dans VS Code](/img/remote/92c6a616e2e5f86f.jpg)

Voir aussi le [guide de débogage VS Code](https://code.visualstudio.com/docs/editor/debugging) et
[Débogage](/fr/dev/debugging).

## Lire les logs

La dev board lit la sortie de logs du Flipper sur son UART, indépendamment du système du Flipper. Vous voyez donc les
logs pendant le démarrage, les mises à jour et les plantages, ce que la commande CLI `log` ne peut pas montrer. Les
logs ne sont disponibles **qu'en USB**.

### Définir le niveau et le périphérique de log

1. Ouvrez `Main Menu → Settings → System`.
2. `Log Level` : `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace`.
3. `Log Device` : conservez `USART` (broches 13/14), là où la dev board écoute. `LPUART` envoie les logs vers les
   broches 15/16, `None` désactive la journalisation sur l'UART.

::: tip
Si un autre module a besoin des broches 13/14 (carte Wi-Fi, SIM800, GPS), mettez `Log Device` sur `LPUART` ou `None`
afin que la sortie des logs ne le perturbe pas.
:::

### macOS

1. Installez [Homebrew](https://brew.sh/), puis `brew install minicom`.
2. Éteignez le Flipper, branchez la dev board, rallumez.
3. Lancez `ls /dev/cu.*`, connectez la dev board en USB, relancez la commande. Deux nouveaux périphériques
   apparaissent, par exemple `/dev/cu.usbmodemblackmagic1` et `/dev/cu.usbmodemblackmagic3`.
4. Ouvrez celui dont le **numéro est le plus élevé** :

   ```bash
   minicom -D /dev/cu.usbmodemblackmagic3 -b 230400
   ```

5. Les logs défilent dans le terminal. Quittez via le menu de minicom ou fermez la fenêtre.

### Linux

1. Installez minicom, par exemple `sudo apt install minicom`.
2. Éteignez le Flipper, branchez la dev board, rallumez.
3. Lancez `ls /dev/tty*`, connectez la dev board en USB, relancez la commande. Deux nouveaux périphériques
   apparaissent, par exemple `/dev/ttyACM0` et `/dev/ttyACM1`.
4. Ouvrez celui dont le numéro est le plus élevé :

   ```bash
   minicom -D /dev/ttyACM1 -b 230400
   ```

5. Si rien ne s'affiche, essayez l'autre périphérique.

### Windows

1. Installez [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Éteignez le Flipper, branchez la dev board, rallumez, puis connectez la dev board en USB.
3. Dans **Gestionnaire de périphériques → Ports (COM et LPT)**, notez le nouveau port COM.
4. Dans PuTTY, choisissez **Serial**, saisissez le port dans **Serial line**, mettez **Speed** à **230400**, cliquez
   sur **Open**.

![Réglages PuTTY](/img/remote/2bb43453a91a142e.jpg)

## Pages liées

- [Dev board : prise en main](/fr/gpio/devboard)
- [Dev board : mise à jour du firmware](/fr/gpio/devboard-firmware)
- [CLI](/fr/dev/cli)
