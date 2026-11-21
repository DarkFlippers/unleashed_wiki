---
title: Mises à jour OTA
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/OTA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/update.py]
sources: [unleashed-docs, unleashed-src]
---
# Le processus de mise à jour OTA

Comment le Flipper installe un paquet de mise à jour — ce qui se passe à chaque étape, ce que contient le manifeste
de mise à jour, ce que signifient les codes d'erreur `[XX-YY]`, et comment construire vos propres paquets.

Pour le côté utilisateur (installer Unleashed avec qFlipper, l'installateur web ou depuis la carte SD), voir
[Mise à jour](/fr/start/updating). Si une mise à jour échoue gravement, voir
[Restauration](/fr/start/recovery).

## Exécuter du code depuis la RAM

Le firmware dispose d'un mode de démarrage particulier qui charge en **RAM** une image système spécialement conçue et
qui y saute. Du code exécuté depuis la RAM a un accès complet en écriture à toute la mémoire flash — ce qui est
impossible tant que le firmware principal s'exécute depuis cette même flash. L'updater OTA utilise ce mode, y compris
pour mettre à jour la pile radio sur le second cœur du MCU.

## Les trois étapes

### 1. Sauvegarder le stockage interne (`/int`)

`/int` est une partition de la flash du Flipper qui occupe tout l'espace non utilisé par le firmware. Un nouveau
firmware peut avoir une taille différente : l'installer repartitionnerait donc la flash et perdrait les données.
C'est pourquoi, avant toute autre chose, le contenu actuel de `/int` est sauvegardé dans une archive `.tar` ordinaire
sur la carte SD.

### 2. Mettre l'appareil à jour

Le firmware principal charge en RAM l'**updater** — un build personnalisé du firmware — et l'exécute. L'updater
travaille sur la flash système comme le décrit le manifeste de mise à jour :

1. Si le paquet contient une image de **pile radio**, sa version est comparée à celle installée. Si elles diffèrent,
   l'ancienne pile est désinstallée et la nouvelle est écrite puis installée. L'installation est effectuée par le
   **FUS** propriétaire de ST, exécuté sur le Core2, et implique plusieurs redémarrages.
2. Les **Option Bytes** (configuration bas niveau du MCU) sont validés et corrigés.
3. Le fichier `.dfu` du firmware est chargé, son intégrité est vérifiée par CRC32, puis il est écrit en flash et
   vérifié.

### 3. Restaurer le stockage interne et mettre à jour les ressources

Le système redémarre sur le nouveau firmware, restaure le contenu sauvegardé de `/int` et — si le paquet contient une
archive de ressources — l'extrait sur la carte SD.

## Manifeste de mise à jour

Chaque paquet est accompagné d'un manifeste (le fichier `.fuf`) au format Flipper File Format — un fichier texte brut
de paires clé-valeur.

### Champs obligatoires (dans cet ordre)

| Clé | Signification |
|---|---|
| `Filetype` | Chaîne constante `Flipper firmware upgrade configuration` |
| `Version` | Version du manifeste, actuellement `2` |
| `Info` | Description libre du paquet |
| `Target` | Révision matérielle pour laquelle le paquet est construit |
| `Loader` | Nom du fichier du chargeur de deuxième étage exécuté depuis la RAM |
| `Loader CRC` | CRC32 du fichier du chargeur, en hexadécimal **little-endian** |

### Champs facultatifs

Ils peuvent être vides — l'updater ignore alors les opérations correspondantes.

| Clé | Signification |
|---|---|
| `Radio` | Nom du fichier de l'image de la pile radio (fournie par ST) |
| `Radio address` | Adresse à laquelle installer la pile radio (d'après les notes de version de ST) |
| `Radio version` | Versions majeure, mineure et sous-version, branche, release et type de pile, condensés dans 6 octets hexadécimaux |
| `Radio CRC` | CRC32 de l'image radio |
| `Resources` | Nom du fichier de l'archive des ressources de la carte SD — `resources.ths`, une archive tar compressée en heatshrink (voir [Format d'archive Heatshrink](/fr/dev/tar-heatshrink)) |
| `OB reference`, `OB mask`, `OB write mask` | Valeurs de référence pour valider et corriger les option bytes |

## Codes d'erreur

Le processus est conçu pour être le plus sûr possible : aucune opération risquée ne démarre avant que toutes les
données concernées n'aient été validées, de sorte que l'appareil ne reste pas à moitié mis à jour ni ne devienne
inutilisable. Si quelque chose se passe mal, l'updater vous laisse réessayer et affiche un code d'erreur `[XX-YY]` :
`XX` est l'opération qui a échoué, `YY` l'avancement ou le détail au niveau duquel elle a échoué.

| Étape | XX | YY | Signification |
|---|--:|---|---|
| Chargement du manifeste de mise à jour | **1** | **13** | L'updater a signalé une incompatibilité de version matérielle |
| | | **20** | Impossible d'obtenir le chemin du manifeste enregistré |
| | | **30** | Échec du chargement du manifeste |
| | | **40** | Version du paquet de mise à jour non prise en charge |
| | | **50** | Le paquet ne correspond pas à la cible matérielle |
| | | **60** | Fichier DFU manquant |
| | | **80** | Fichier du firmware radio manquant |
| Sauvegarde de la configuration | **2** | **0-100** | Erreur de lecture/écriture du système de fichiers |
| Vérification du firmware radio | **3** | **0-99** | Erreur de lecture du fichier du firmware radio |
| | | **100** | CRC incorrect |
| Désinstallation du firmware radio | **4** | **0** | Erreur de la commande SHCI Delete |
| | | **80** | Erreur lors de l'attente du statut de la commande |
| Écriture du firmware radio | **5** | **0-100** | Erreur de lecture/écriture d'un bloc |
| Installation du firmware radio | **6** | **10** | Erreur de la commande SHCI Install |
| | | **80** | Erreur lors de l'attente du statut de la commande |
| Core2 occupé | **7** | **10** | Impossible de démarrer le C2 |
| | | **20** | Échec du passage du C2 en mode FUS |
| | | **30** | Erreur lors d'une opération FUS |
| | | **50** | Échec du passage du C2 en mode pile |
| Validation des option bytes | **8** | **yy** | Code de l'option byte |
| Vérification du fichier DFU | **9** | **0** | Erreur à l'ouverture du fichier DFU |
| | | **1-98** | Erreur de lecture du fichier DFU |
| | | **99-100** | Fichier DFU corrompu |
| Écriture de la flash | **10** | **0-100** | Erreur de lecture/écriture d'un bloc |
| Validation de la flash | **11** | **0-100** | Erreur de lecture/écriture d'un bloc |
| Restauration de la configuration | **12** | **0-100** | Erreur de lecture/écriture du système de fichiers |
| Mise à jour des ressources | **13-15** | **0-100** | Erreur de lecture/écriture de la carte SD |

::: tip Que faire en cas d'erreur
- **1-50 / 1-13** — le paquet est destiné à une autre cible matérielle : téléchargez le bon.
- **2, 12, 13-15** — problème de carte SD : vérifiez / reformatez la carte, recopiez le paquet.
- **3-100, 9-99/100** — fichiers corrompus : téléchargez de nouveau le paquet.
- Réessayez d'abord — l'updater est conçu pour cela. Si le Flipper ne démarre plus du tout, utilisez
  [Restauration](/fr/start/recovery).
:::

## Construire des paquets de mise à jour

N'oubliez pas de passer `DEBUG=0` — voir [Compiler le firmware](/fr/dev/build).

**Paquet complet** — firmware, pile radio et ressources de la carte SD :

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

**Paquet minimal** — firmware seul :

```sh
./fbt COMPACT=1 DEBUG=0 updater_minpackage
```

Le résultat se trouve dans `dist/<target>-<cfg>/`, sous forme d'un dossier `f7-update-<suffix>` et d'un fichier
`flipper-z-f7-update-<suffix>.tgz`.

### Choisir une autre pile radio

Les paquets utilisent par défaut la pile **Bluetooth Light**. Si votre firmware prend en charge une autre pile,
passez son type et son binaire :

```sh
./fbt updater_package COMPACT=1 DEBUG=0 COPRO_OB_DATA=scripts/ob_custradio.data COPRO_STACK_BIN=stm32wb5x_BLE_Stack_full_fw.bin COPRO_STACK_TYPE=ble_full
```

`COPRO_OB_DATA` doit pointer vers un fichier de `scripts/` contenant les données d'Option Bytes de référence
correspondant à ce type de pile. Dans certains cas, vous devez aussi confirmer avec `COPRO_DISCLAIMER=...` en ligne
de commande.

### Paquets partiels

Appelez directement `scripts/update.py` pour un contenu personnalisé. Par exemple, un paquet qui n'installe que la
pile BLE FULL :

```shell
scripts/update.py generate \
  -t f7 -d r13.3_full -v "BLE FULL 13.3" \
  --stage dist/f7/flipper-z-f7-updater-*.bin \
  --radio lib/stm32wb_copro/firmware/stm32wb5x_BLE_Stack_full_fw.bin \
  --radiotype ble_full
```

Voir `scripts/update.py generate --help` pour toutes les options.

## Installer un paquet depuis le CLI

Copiez le dossier du paquet décompressé sur la carte SD et lancez :

```
update install /ext/update/f7-update-local/update.fuf
```

Le [CLI](/fr/dev/cli#update) propose aussi `update backup` et `update restore` pour le stockage interne.

## Pages liées

- [Mettre à jour le firmware](/fr/start/updating)
- [Restauration](/fr/start/recovery)
- [Format d'archive Heatshrink](/fr/dev/tar-heatshrink)
- [Flipper Build Tool (fbt)](/fr/dev/fbt)
