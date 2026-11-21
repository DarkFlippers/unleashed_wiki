---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` est le point d'entrée unique pour compiler, flasher, déboguer et analyser le firmware. Vous l'exécutez avec
`./fbt` (ou `fbt.cmd` sous Windows) depuis la racine du dépôt. En interne, c'est une enveloppe autour du système de
compilation [SCons](https://scons.org/).

Si vous voulez seulement compiler et déboguer **une application**, vous n'avez pas besoin de toute l'arborescence du
firmware — utilisez plutôt [uFBT](https://pypi.org/project/ufbt/) (voir
[Votre première application en C](/fr/dev/first-app-c)).

## Environnement {#environment}

La seule chose que vous devez avoir installée est `git`. Au premier lancement, `fbt` télécharge et décompresse une
chaîne d'outils précompilée et ajuste les variables d'environnement **pour lui seul** — votre `PATH` global n'est pas
modifié.

Pour utiliser la chaîne d'outils fournie en dehors de `fbt` (par exemple pour appeler `arm-none-eabi-gdb`
manuellement), ouvrez un *fbt shell* :

- Windows : lancez `scripts/toolchain/fbtenv.cmd`
- Linux / macOS : lancez `source scripts/toolchain/fbtenv.sh` dans un nouvel interpréteur
- ou tapez `` . `./fbt -s env` `` dans votre interpréteur (gardez le `.` initial)

Variables d'environnement qui modifient le comportement de `fbt` :

| Variable | Effet |
|---|---|
| `FBT_NOENV=1` | Ignore le téléchargement et la mise en place de la chaîne d'outils ; tous les outils doivent déjà être dans le `PATH` (indisponible sous Windows) |
| `FBT_TOOLCHAIN_PATH=…` | Répertoire dans lequel décompresser la chaîne d'outils (par défaut : `toolchain/` à la racine du dépôt) |
| `FBT_VERBOSE=1` | Sortie de débogage supplémentaire de `fbt` et des scripts de la chaîne d'outils |
| `FBT_NO_SYNC=1` | N'exécute pas `git submodule update --init` à chaque démarrage |

Définir une variable pour une seule exécution :

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

D'autres variables sont documentées dans les sources des scripts `fbt` et `fbtenv`.

## Appeler fbt

Passez les options de configuration et les cibles souhaitées :

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Pour nettoyer les cibles indiquées (comme `make clean`), ajoutez `-c`.

`fbt` suit les dépendances : vous ne nommez donc que la cible de plus haut niveau dont vous avez besoin — tout ce
dont elle dépend est recompilé automatiquement.

## Répertoires de build

Le firmware et l'updater sont compilés dans des sous-répertoires distincts de `build/`, nommés d'après les réglages
d'optimisation (`COMPACT`, `DEBUG`). Pour les IDE, la variante compilée le plus récemment est toujours liée à
`build/latest`, avec un fichier `compile_commands.json` utilisé pour l'autocomplétion.

::: info
`build/latest` et la base de données de compilation ne sont mis à jour que par les **cibles de compilation du
firmware**. Le flashage, ou la construction de paquets de mise à jour pour une *autre* configuration debug/release ou
une autre cible matérielle, ne déplace pas `build/latest`.
:::

## Intégration à VS Code {#vs-code-integration}

```sh
./fbt vscode_dist
```

copie une configuration d'environnement prête à l'emploi dans `.vscode/`. Ouvrez la racine du firmware avec
**File → Open Folder**.

- Pour utiliser un serveur de langage autre que `cpptools` (le choix par défaut), lancez
  `./fbt vscode_dist LANG_SERVER=<language-server>`. Pris en charge : `cpptools` (par défaut) et `clangd`.
- Au premier démarrage, les extensions recommandées vous sont proposées (listées dans `.vscode/extensions.json`) —
  installez-les.
- Les tâches de compilation sont accessibles via <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Le débogage nécessite une sonde prise en charge : Wi-Fi Devboard avec son firmware d'origine (Blackmagic), ST-Link
  et compatibles, ou J-Link (VS Code uniquement ; les outils J-Link ne sont pas fournis —
  [téléchargez-les](https://www.segger.com/downloads/jlink/) et placez-les dans le `PATH`).
- Sans sonde, vous pouvez tout de même installer le firmware par USB.

## Cibles de haut niveau {#high-level-targets}

Ce sont les cibles que vous utiliserez le plus souvent.

| Cible | Ce qu'elle fait |
|---|---|
| `fw_dist` | Compile le firmware et le publie dans `dist/`. **Cible par défaut** quand aucune n'est indiquée |
| `fap_dist` | Compile les applications externes (FAP) et les publie dans `dist/` |
| `updater_package` | Paquet d'auto-mise à jour complet : DFU du firmware + pile radio + ressources de la carte SD |
| `updater_minpackage` | Paquet de mise à jour minimal : uniquement le DFU du firmware |
| `copro_dist` | Regroupe les binaires FUS du Core2 et de la pile radio pour qFlipper |
| `flash` | Flashe en SWD avec une sonde prise en charge (détectée automatiquement ; forcez-la avec `SWD_TRANSPORT=...`, choisissez parmi plusieurs sondes avec `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Compile, envoie et installe le paquet de mise à jour par USB (paquet minimal / complet) |
| `debug` | Compile et flashe le firmware, puis attache GDB avec le `.elf` du firmware chargé |
| `debug_other`, `debug_other_blackmagic` | Attache GDB sans charger de `.elf` ; ajoutez des `.elf` externes avec `add-symbol-file` |
| `updater_debug` | Attache GDB avec le `.elf` de l'updater chargé |
| `devboard_flash` | Met à jour la Wi-Fi Devboard ; arguments supplémentaires via `ARGS="..."`, par ex. `ARGS="-c dev"` |
| `blackmagic` | Débogue le firmware avec une sonde Blackmagic (Wi-Fi Devboard) |
| `openocd` | Démarre simplement OpenOCD ; arguments supplémentaires via `ARGS="..."` |
| `get_blackmagic` | Affiche l'adresse Blackmagic au format distant de GDB (pour l'intégration à un IDE) |
| `get_stlink` | Affiche les numéros de série des sondes ST-Link connectées (pour `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Vérifie / reformate le code C avec clang-format (`.clang-format`) ; arguments supplémentaires via `ARGS="..."` |
| `lint_py`, `format_py` | Vérifie / reformate le Python, les fichiers de build et les manifestes avec [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Vérifie / corrige les ressources graphiques (profondeur de couleur, suppression des métadonnées) |
| `lint_all`, `format_all` | Exécute tous les analyseurs / formateurs |
| `firmware_pvs` | Rapport PVS-Studio (PVS-Studio doit être dans le `PATH`) |
| `doxygen` | Génère la documentation Doxygen ; `doxy` l'ouvre aussi dans un navigateur |
| `cli` | Ouvre une session [CLI](/fr/dev/cli) du Flipper par USB |

## Cibles du firmware

| Cible | Ce qu'elle fait |
|---|---|
| `faps` | Compile toutes les applications externes et les plugins en `.fap` |
| `fap_<appid>` | Compile une application en `.fap` à partir de son identifiant, par ex. `fap_snake_game` |
| `fap_<appid>_list` | Génère le listing source + assembleur du `.fap` de cette application |
| `flash`, `firmware_flash` | Flashe le build courant en SWD |
| `jflash` | Flashe avec JFlash en utilisant une sonde J-Link (JFlash doit être dans le `PATH`) |
| `firmware_all`, `updater_all` | Compile un jeu de binaires de base |
| `firmware_list`, `updater_list` | Génère les listings source + assembleur |
| `firmware_cdb`, `updater_cdb` | Génère `compilation_database.json` pour les IDE — fonctionne sans compilation complète |

Utilisez `--extra-ext-apps` (ci-dessous) pour forcer des applications supplémentaires dans le build externe.

## Cibles de ressources

| Cible | Ce qu'elle fait |
|---|---|
| `resources` | Construit les ressources de la carte SD et leurs fichiers de manifeste |
| `dolphin_ext` | Traite les animations du dauphin destinées à la carte SD |
| `icons` | Génère les `.c` + `.h` des icônes depuis les ressources PNG |
| `proto` | Génère les `.pb.c` + `.pb.h` depuis les sources `.proto` |
| `proto_ver` | Génère un `.h` contenant la version de protobuf |
| `dolphin_internal`, `dolphin_blocking` | Génèrent les `.c` + `.h` des ressources du dauphin correspondantes |

## Paramètres en ligne de commande

| Paramètre | Signification |
|---|---|
| `--options optionfile.py` | Charge un fichier de valeurs de configuration (par défaut `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Force la compilation des applications listées **dans** le firmware (cible `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Force la compilation des applications listées en **externe** (cible `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Définitions C/C++ globales supplémentaires ; peut être répété |
| `--proxy-env=VAR1,VAR2` | Variables d'environnement supplémentaires à transmettre aux sous-processus. Par défaut, `fbt` assainit l'environnement ; la liste des variables toujours transmises se trouve dans `environ.scons` |

## Configuration

Les valeurs par défaut se trouvent dans `fbt_options.py`. Celles passées en ligne de commande ont la priorité. Pour
des **surcharges personnelles persistantes**, créez `fbt_options_local.py` à côté : il est évalué lors du chargement
des options par défaut, vous n'avez donc jamais besoin de modifier le fichier suivi par le dépôt. Lancez `./fbt -h`
pour lister toutes les options.

Valeurs par défaut notables d'Unleashed dans `fbt_options.py` :

| Option | Par défaut | Remarques |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Indiqué dans les informations de l'appareil |
| `TARGET_HW` | `7` | Flipper Zero (f7) ; voir [cibles matérielles](/fr/dev/hardware-targets) |
| `COMPACT` | `1` | Optimise pour la taille |
| `DEBUG` | `1` | Passez `DEBUG=0` pour des builds installables |
| `DIST_SUFFIX` | `"local"` | Suffixe dans les noms des fichiers produits |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` est pris en charge mais peut ne pas tenir dans les builds de débogage |
| `FIRMWARE_APP_SET` | `"default"` | Voir ci-dessous |

### Jeux d'applications du firmware {#firmware-app-sets}

Les applications intégrées au firmware sont déterminées par `FIRMWARE_APPS` — une table associant *nom de
configuration → tuple d'identifiants d'applications*. Choisissez-en une avec `FIRMWARE_APP_SET`. Unleashed définit
deux jeux :

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Par exemple, pour construire une image avec les tests unitaires :

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Voir [Tests unitaires](/fr/dev/unit-tests) pour comprendre pourquoi ce build nécessite `DEBUG=0`.

## Pages liées

- [Compiler le firmware](/fr/dev/build)
- [Manifestes d'application (.fam)](/fr/dev/app-manifests)
- [Déboguer les applications](/fr/dev/debugging)
- [Mises à jour OTA](/fr/dev/ota)
