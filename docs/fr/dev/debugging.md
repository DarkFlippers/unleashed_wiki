---
title: Déboguer les applications
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_debugging_faps.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriHalDebugging.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md]
sources: [unleashed-docs]
---
# Déboguer les applications

Le débogage en temps réel (in-circuit) permet de lancer une application, de la mettre en pause n'importe où, de
parcourir le code ligne par ligne et d'observer les variables et la pile d'appels. Il trouve bien plus de bugs que
« ajouter une ligne de log et réessayer ».

::: info
Le débogage in-circuit est facultatif. Vous pouvez toujours déboguer en chargeant les applications par USB et en
lisant le [log](/fr/dev/cli#reading-logs).
:::

## Ce dont vous avez besoin

- Un Flipper Zero (la *cible*).
- Un ordinateur Windows, Linux ou macOS avec [uFBT](https://github.com/flipperdevices/flipperzero-ufbt) (pour les
  applications) ou l'arborescence complète du firmware avec [fbt](/fr/dev/fbt).
- Une **sonde SWD** prise en charge.

### Sondes SWD prises en charge

| Sonde | Remarques |
|---|---|
| Un **second Flipper Zero** | Exécutez l'[application DAP Link](https://lab.flipper.net/apps/dap_link) dessus pour en faire une sonde SWD |
| [Wi-Fi Devboard](https://shop.flipperzero.one/products/wifi-devboard) | Avec son firmware d'origine (Blackmagic) ; se connecte en USB ou en Wi-Fi — voir [Dev board](/fr/gpio/devboard) |
| Sondes CMSIS-DAP | par ex. [Raspberry Pi Debug Probe](https://www.raspberrypi.com/products/debug-probe/), [l-tek](https://www.l-tek.com/web-shop/cmsis-dap-debug-probe/), [makerdiary Pitaya-Link](https://makerdiary.com/products/pitaya-link) |
| [Sondes compatibles Blackmagic](https://black-magic.org/hardware.html) | |
| ST-Link | [ST-LINK V2](https://www.st.com/en/development-tools/st-link-v2.html), [ST-LINK V3](https://www.st.com/en/development-tools/stlink-v3set.html), la [dev board ST-Link V3](/fr/dev/hardware#st-link-v3-developer-board) |
| J-Link | Flashage et débogage depuis VS Code uniquement ; installez vous-même les outils SEGGER |

## Préparer le Flipper

Activez le mode debug sur la cible : `Main Menu → Settings → System → Debug` → **ON**.

## Pas à pas (VS Code)

1. **Connectez la sonde au connecteur GPIO du Flipper.** Les sondes conçues pour le Flipper se branchent
   directement. Pour une sonde générique, câblez trois fils :

   | Signal | Broche du Flipper |
   |---|---|
   | SWCLK | 10 |
   | SWDIO | 12 |
   | GND | 8, 11 ou 18 |

   Si la sonde dispose aussi d'un UART, reliez-le à l'USART du Flipper (broches **13** TX et **14** RX). Ce port
   affiche les logs et les informations de plantage, ce qui aide beaucoup.
2. **Connectez la sonde à l'ordinateur** — en général en USB ; la Wi-Fi Devboard fonctionne aussi en Wi-Fi.
3. **Préparez le projet :** exécutez une fois `ufbt vscode_dist` (application) ou `./fbt vscode_dist` (firmware),
   puis ouvrez le dossier dans VS Code.
4. **Passez VS Code en Run and Debug :** cliquez sur l'icône de débogage dans la barre latérale ou appuyez sur
   <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> (<kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>D</kbd> sous macOS).
   Choisissez la configuration correspondant à votre sonde et appuyez sur **Play**.

   ::: info
   Le démarrage d'une session de débogage **met le firmware en pause**. Cliquez sur **Continue** dans la barre d'outils
   de débogage pour reprendre.
   :::
5. **Utilisez les commandes de débogage :** reset, pause, continuer, entrer dans, sortir de, se déconnecter.
6. **Posez des points d'arrêt** en cliquant à gauche d'un numéro de ligne. L'exécution s'arrête quand elle atteint
   cette ligne.
7. **Examinez la pile d'appels** dans le panneau *Call Stack* pendant la pause.
8. **Examinez les variables** dans les panneaux *Variables*, *Watch* ou *Live Watch*.

Une vidéo de démonstration de Flipper Devices :
[Debugging FAPs in VS Code](https://cdn.flipperzero.one/app_dev_flipper_zero_debug_demo.mp4).

## Déboguer en ligne de commande avec fbt

Avec l'arborescence complète du firmware, vous pouvez déboguer sans VS Code :

| Commande | Ce qu'elle fait |
|---|---|
| `./fbt debug` | Compile et flashe le firmware, puis attache GDB avec le `.elf` du firmware chargé |
| `./fbt blackmagic` | Débogue avec une sonde Blackmagic (Wi-Fi Devboard) |
| `./fbt debug_other` / `debug_other_blackmagic` | Attache GDB sans charger de `.elf` ; ajoutez le `.elf` de votre application avec `add-symbol-file` |
| `./fbt updater_debug` | Attache GDB avec le `.elf` de l'updater |
| `./fbt openocd ARGS="..."` | Lance simplement OpenOCD |
| `./fbt get_stlink` | Liste les numéros de série des ST-Link, pour `SWD_TRANSPORT_SERIAL=...` |

## Signaux de débogage du HAL Furi

Certains sous-systèmes Furi peuvent exposer leur état interne sur des broches GPIO, pour un suivi à l'analyseur
logique ou à l'oscilloscope. Activez-les en ajoutant une définition à la compilation, par exemple :

```sh
./fbt --extra-define=FURI_HAL_OS_DEBUG flash
```

### `FURI_HAL_OS_DEBUG` — ordonnanceur et veille

Expose le tick, la suppression de tick, l'inactivité et l'écoulement du temps :

| Signal | Broche | Signification |
|---|---|---|
| `AWAKE` | `PA7` | Haut quand le système calcule, bas pendant la veille — suit les transitions vers la veille |
| `TICK` | `PA6` | Bascule à chaque tick système (uniquement quand aucune suppression de tick n'est en cours) — révèle les dérives de tick et les ordonnancements anormaux |
| `SECOND` | `PA4` | Bascule chaque seconde — des perturbations dans son rythme signifient que le système ne respecte pas le temps réel dur |

### `FURI_HAL_POWER_DEBUG` — modes d'alimentation

Trace les transitions de modes d'alimentation :

| Signal | Broche | Signification |
|---|---|---|
| `WFI` | `PB2` | Veille légère (wait for interrupt). Le mode d'économie le plus léger et non intrusif — tout fonctionne, y compris le débogage |
| `STOP` | `PC3` | Mode STOP, la veille profonde de la plateforme. La majeure partie du silicium est éteinte ou inutilisable ; déboguer le MCU dans ce mode est quasi impossible |

### `FURI_HAL_SD_SPI_DEBUG` — carte SD

Journalise le trafic du bus SPI de la carte SD.

## Dépannage

| Problème | Solution |
|---|---|
| La sonde se connecte mais rien ne se passe | Le firmware est en pause — appuyez sur **Continue** |
| Les points d'arrêt de votre application sont ignorés | Assurez-vous que les symboles du `.elf` de l'application sont chargés (la configuration VS Code issue de `vscode_dist` le fait ; avec `debug_other`, utilisez `add-symbol-file`) |
| Le débogueur perd la cible | Le MCU est peut-être en mode STOP ; voir `FURI_HAL_POWER_DEBUG`. Le mode Debug doit être sur **ON** sur le Flipper |
| Les variables apparaissent comme optimisées | Compilez avec `DEBUG=1` (attention : un tel firmware peut être trop volumineux pour être empaqueté — voir [Compiler](/fr/dev/build)) |

## Pages liées

- [Votre première application en C](/fr/dev/first-app-c)
- [Flipper Build Tool (fbt)](/fr/dev/fbt)
- [Dev board](/fr/gpio/devboard)
- [Matériel](/fr/dev/hardware) — plans de brochage et schémas de la dev board
