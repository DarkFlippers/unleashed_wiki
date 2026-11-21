---
title: Compiler le firmware
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Compiler le firmware

Compilez le firmware Unleashed depuis les sources quand vous voulez modifier le firmware lui-même, inclure vos
propres applications dans le build, ou tester le code `dev` le plus récent avant une release officielle.

Si vous voulez seulement écrire une application (`.fap`), vous n'avez pas besoin de tout le firmware — utilisez plutôt
[uFBT](/fr/dev/first-app-c) et passez directement à
[compiler des applications contre le SDK Unleashed](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Ce dont vous avez besoin

- **Git** — [téléchargement](https://git-scm.com/downloads) pour Windows ; sous Linux/macOS, installez-le avec votre
  gestionnaire de paquets (`brew`, `apt`, …).
- **VS Code** (recommandé pour le développement, facultatif pour une simple compilation).
- Quelques Go d'espace disque. Rien d'autre : `fbt` télécharge sa propre chaîne d'outils ARM au premier lancement et
  ne touche pas au `PATH` de votre système (voir [fbt → Environnement](/fr/dev/fbt#environment)).

## 1. Cloner le dépôt

Clonez toujours **avec les sous-modules** :

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Si vous avez déjà cloné sans `--recursive`, initialisez les sous-modules :

```shell
git submodule update --init --recursive
```

## 2. Compiler sous Linux / macOS

Compiler tout et produire un paquet de mise à jour installable depuis la carte microSD :

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Compiler une seule application depuis `applications_user/` et la lancer sur un Flipper connecté en USB :

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Compiler sous Windows

Utilisez `fbt.cmd` dans PowerShell ou `cmd` :

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
Sous Windows, il vous faudra peut-être écrire `.\fbt.cmd` (barre oblique inverse) au lieu de `./fbt.cmd`, selon votre
interpréteur de commandes.
:::

## 4. Trouver le résultat et le flasher

Tous les résultats de compilation vont dans `dist/`. Le fichier à installer est le paquet de mise à jour :

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Le motif de nommage est `flipper-z-{target}-update-{suffix}.tgz`. Le suffixe par défaut est `local` (défini par
`DIST_SUFFIX` dans `fbt_options.py`, ou par la variable d'environnement `DIST_SUFFIX`).

Façons de l'installer :

- ouvrez le `.tgz` dans **qFlipper** (*Install from file*) ou dans l'installateur web Unleashed ;
- ou laissez `fbt` le faire par USB : `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (compile, envoie et installe) ;
- ou flashez en SWD avec une sonde de débogage : `./fbt flash` (voir
  [cibles fbt](/fr/dev/fbt#high-level-targets)).

::: tip Pourquoi `DEBUG=0` ?
Le `fbt_options.py` d'Unleashed utilise par défaut `COMPACT=1` et **`DEBUG=1`**. Une image debug est plus volumineuse
et risque de ne pas tenir sous la pile radio en flash — l'empaquetage s'arrête alors avec
`Firmware image overlaps C2 region and is not programmable!`. Pour tout ce que vous allez installer, passez
explicitement `DEBUG=0`. Notez que `DEBUG=0` supprime également `furi_assert()` à la compilation.
:::

## Intégration VS Code

`fbt` fournit une configuration VS Code prête à l'emploi :

```sh
./fbt vscode_dist
```

Cela copie la configuration dans `.vscode/`. Ouvrez ensuite la racine du firmware dans VS Code via
**File → Open Folder**, acceptez les extensions recommandées, et utilisez
<kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> pour les tâches de compilation. Plus d'informations dans
[fbt → VS Code](/fr/dev/fbt#vs-code-integration).

## Compiler des applications contre le SDK Unleashed avec uFBT {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) compile une application isolée contre un SDK téléchargé plutôt que contre l'arborescence complète des
sources. **Par défaut, il télécharge le SDK du firmware officiel.** Pour compiler pour Unleashed, pointez-le vers
l'index de mises à jour Unleashed :

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Les canaux sont `dev` et `release`. Utilisez les mêmes options à **chaque** `ufbt update` ultérieur, sinon uFBT
repasse silencieusement au SDK officiel et l'application compilée signale une mauvaise version d'API.

::: tip Unleashed
Unleashed conserve l'API officielle : la plupart des applications officielles fonctionnent donc telles quelles. Une
application ne refuse de se charger que lorsque sa version majeure d'API ne correspond pas à celle du firmware — la
recompiler contre le SDK adéquat résout le problème.
:::

## Compiler des applications sur Android

Les applications (pas le firmware) peuvent aussi être compilées directement sur un téléphone Android avec uFBT dans
Termux — voir [Compiler des applications sur Android](/fr/dev/android-build).

## Dépannage

| Problème | Solution |
|---|---|
| La compilation échoue avec des fichiers manquants / erreurs de sous-modules | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Ajoutez `DEBUG=0` à la commande |
| `./fbt` introuvable sous Windows | Utilisez `fbt.cmd` / `.\fbt.cmd` |
| L'application compilée avec uFBT ne démarre pas : incompatibilité d'API | Relancez `ufbt update` avec l'`--index-url` Unleashed, puis recompilez |
| Vous voulez une recompilation propre | Ajoutez `-c` pour nettoyer les cibles indiquées, par ex. `./fbt -c fw_dist` |

## Pages liées

- [Flipper Build Tool (fbt)](/fr/dev/fbt) — toutes les cibles et options
- [Votre première application en C](/fr/dev/first-app-c)
- [Mises à jour OTA](/fr/dev/ota) — ce que contient un paquet de mise à jour
- [Cibles matérielles](/fr/dev/hardware-targets)
