---
title: Cibles matérielles
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Cibles matérielles

Le firmware est modulaire : une même base de code prend en charge plusieurs configurations matérielles. Tout ce qui
diffère d'une carte à l'autre — l'implémentation de `furi_hal`, le code d'initialisation de la carte, les scripts de
l'éditeur de liens, les tables de symboles du SDK — est regroupé dans une **définition de cible**.

Le dépôt Unleashed fournit deux cibles dans `targets/` :

| Dossier | Matériel |
|---|---|
| `targets/f7` | Flipper Zero — la cible par défaut (`TARGET_HW = 7`) |
| `targets/f18` | « Not Flipper Zero » — une carte dépourvue des étages radio ; hérite de f7 |

Les en-têtes partagés se trouvent dans `targets/furi_hal_include`.

## Organisation d'une cible

Chaque cible réside dans son propre sous-dossier de `targets/`. Elle doit contenir `target.json` et peut contenir tout
autre fichier auquel cette définition fait référence. Par défaut, `fbt` compile **tous les fichiers sources** du
dossier de la cible, sauf exclusion explicite. Les cibles peuvent **hériter** d'une autre cible afin d'éviter de
dupliquer du code.

## Champs de `target.json`

| Champ | Type | Signification |
|---|---|---|
| `include_paths` | liste de chaînes | Dossiers (relatifs à la cible) ajoutés au chemin d'inclusion C/C++ global |
| `sdk_header_paths` | liste de chaînes | Dossiers dont les en-têtes sont inclus dans le SDK |
| `startup_script` | nom de fichier | Script de démarrage effectuant l'initialisation matérielle initiale |
| `linker_script_flash` | nom de fichier | Script de l'éditeur de liens pour l'image principale du firmware |
| `linker_script_ram` | nom de fichier | Script de l'éditeur de liens pour la configuration « updater » (s'exécute depuis la RAM) |
| `linker_script_app` | nom de fichier | Script de l'éditeur de liens pour les fichiers `.fap` |
| `sdk_symbols` | nom de fichier | `.csv` contenant la définition actuelle du SDK (API) pour cette cible |
| `linker_dependencies` | liste | Bibliothèques avec lesquelles lier le firmware. Les bibliothèques non listées ne sont **pas compilées**. Plusieurs passes de liaison peuvent nécessiter le même nom deux fois |
| `inherit` | chaîne | Cible dont reprendre la configuration de base. Les valeurs de type liste sont étendues, les autres sont écrasées |
| `excluded_sources` | liste | Fichiers de la ou des configurations héritées à **ne pas** compiler |
| `excluded_headers` | liste | En-têtes de la ou des configurations héritées à **ne pas** inclure dans le SDK |
| `excluded_modules` | liste | Noms de bibliothèques (modules) `fbt` à exclure lors de la configuration de la compilation |

## Exemple : comment f18 hérite de f7

`targets/f18/target.json` (abrégé) montre l'héritage et les exclusions en pratique — il reprend tout de f7 et
abandonne les pilotes Sub-GHz, NFC, RFID, iButton et infrarouge :

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## Applications et matériel

Toutes les applications ne sont pas disponibles sur toutes les cibles.

- **Applications intégrées :** choisissez un jeu d'applications compatible avec l'option `FIRMWARE_APP_SET=...`
  (voir [fbt → jeux d'applications du firmware](/fr/dev/fbt#firmware-app-sets)).
- **Applications externes (FAP) :** listez les cibles compatibles dans l'`application.fam` de l'application. Par
  exemple, pour compiler une application uniquement pour f7, ajoutez :

```python
    targets=["f7"],
```

Elle ne sera pas compilée pour les autres cibles. Voir [Manifestes d'application](/fr/dev/app-manifests).

## Compiler pour une cible précise

Passez `TARGET_HW` (et éventuellement `FIRMWARE_APP_SET`) à `fbt`. Par exemple, pour compiler et flasher le firmware
pour f18 en USB :

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Pages liées

- [Flipper Build Tool (fbt)](/fr/dev/fbt)
- [Manifestes d'application (.fam)](/fr/dev/app-manifests)
- [API FuriHalBus](/fr/dev/furi-hal-bus)
