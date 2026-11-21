---
title: Développement
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Développement

Cette section s'adresse à ceux qui veulent aller plus loin que l'utilisation du Flipper : compiler le firmware
Unleashed depuis les sources, écrire leurs propres applications en C ou en JavaScript, les déboguer sur du matériel
réel, dialoguer avec l'appareil en ligne de commande, ou comprendre le fonctionnement interne des mises à jour et du
matériel.

::: tip Unleashed
Unleashed est un fork du firmware officiel qui reste **entièrement compatible avec l'API et les applications
officielles**. Presque tout ce que dit la documentation développeur officielle s'applique tel quel. Les points
principaux à retenir :

- clonez `https://github.com/DarkFlippers/unleashed-firmware` au lieu du dépôt officiel ;
- lorsque vous compilez des applications avec **uFBT**, pointez-le vers le SDK Unleashed
  (`--index-url=https://up.unleashedflip.com/directory.json`), sinon votre application est compilée contre le SDK
  officiel et peut refuser de se charger
  ([détails](/fr/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt)) ;
- l'origine du firmware est signalée comme `Unleashed`, la version d'API actuelle sur `dev` est **88.27**.
:::

## Compiler le firmware

| Page | Ce que vous y trouverez |
|---|---|
| [Compiler le firmware](/fr/dev/build) | Cloner, compiler et flasher Unleashed sous Linux, macOS et Windows |
| [Flipper Build Tool (fbt)](/fr/dev/fbt) | Toutes les cibles, options et variables d'environnement de `fbt` |
| [Cibles matérielles](/fr/dev/hardware-targets) | Comment `targets/` et `target.json` décrivent les variantes matérielles (f7, f18) |
| [Compiler des applications sur Android](/fr/dev/android-build) | Compiler des applications `.fap` sur un téléphone avec Termux + uFBT, sans PC |

## Écrire des applications

| Page | Ce que vous y trouverez |
|---|---|
| [Votre première application en C](/fr/dev/first-app-c) | uFBT, modèle d'application, « Hello world » avec une boîte de dialogue, compilation et exécution |
| [Manifestes d'application (.fam)](/fr/dev/app-manifests) | Tous les champs d'`application.fam`, les options des applications externes, les bibliothèques privées |
| [API Furi](/fr/dev/furi-api) | Architecture matérielle et logicielle, cœur Furi, `furi_assert` / `furi_check` |
| [Interface graphique dans les applications](/fr/dev/gui) | Boîtes de dialogue, ViewPort, Views et Scenes, modules de vue |
| [Déboguer les applications](/fr/dev/debugging) | Sondes SWD, débogage dans VS Code, signaux de débogage du HAL Furi |
| [API FuriHalBus](/fr/dev/furi-hal-bus) | Activer / désactiver correctement les périphériques du MCU, carte des canaux DMA |
| [JavaScript sur le Flipper](/fr/dev/js-about) | Écrire des scripts en JavaScript plutôt qu'en C (groupe de pages distinct) |
| Modules JS propres à Unleashed | [subghz](/fr/dev/js-subghz), [infrared](/fr/dev/js-infrared), [blebeacon](/fr/dev/js-blebeacon), [usbdisk](/fr/dev/js-usbdisk), [i2c](/fr/dev/js-i2c), [spi](/fr/dev/js-spi), [vgm](/fr/dev/js-vgm) — absents du firmware d'origine comme de la documentation officielle |

## Travailler avec l'appareil

| Page | Ce que vous y trouverez |
|---|---|
| [Interface en ligne de commande (CLI)](/fr/dev/cli) | Se connecter via le port série USB ; toutes les commandes du CLI et leurs arguments |
| [Mises à jour OTA](/fr/dev/ota) | Fonctionnement de l'updater, champs du manifeste, codes d'erreur `[XX-YY]`, création de paquets |
| [Format d'archive Heatshrink](/fr/dev/tar-heatshrink) | Le conteneur `.tar.hs` utilisé pour les ressources des paquets de mise à jour |
| [Matériel](/fr/dev/hardware) | Caractéristiques techniques, schémas, modèles 3D, plans des modules et de la dev board |

## Tests

| Page | Ce que vous y trouverez |
|---|---|
| [Tests unitaires](/fr/dev/unit-tests) | Compiler et exécuter l'application `unit_tests` sur l'appareil, ajouter vos propres tests |
| [Tests d'intégration](/fr/dev/testing) | Le plan de test manuel utilisé avant la fusion des PR et les releases |

## Autres ressources utiles

- Documentation développeur officielle (Doxygen) : [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — c'est là qu'on cherche les API du firmware que ce wiki ne couvre pas : programmation système, développement d'applications, JavaScript, modules d'extension, formats de fichiers
- Configuration d'un espace de travail CLion — [guide de Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Tutoriels de plugin « Hello world! » : [en anglais (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [en russe (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [Comment écrire votre propre application](https://flipper.atmanos.com/docs/overview/intro)

### Structure du dépôt du firmware

| Dossier | Contenu |
|---|---|
| `applications` | Applications et services utilisés dans le firmware |
| `assets` | Ressources utilisées par les applications et services |
| `furi` | Furi Core : primitives et utilitaires de niveau système |
| `debug` | Outils de débogage : plugins GDB, fichier SVD, etc. |
| `documentation` | Sources de la documentation et configurations du générateur |
| `firmware` | Code source du firmware |
| `lib` | Bibliothèques propres et tierces, pilotes |
| `site_scons` | Utilitaires de compilation |
| `scripts` | Scripts complémentaires et bibliothèques Python |
| `targets` | Définitions des cibles matérielles (`f7`, `f18`) |

Beaucoup de ces dossiers possèdent leur propre `ReadMe.md` — ils valent la lecture.
