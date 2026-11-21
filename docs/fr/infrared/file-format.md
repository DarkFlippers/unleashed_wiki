---
title: Format des fichiers IR
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Format de fichier infrarouge (`.ir`)

Toutes les données IR du Flipper sont stockées en texte brut au format Flipper Format (des lignes `key: value`).
L'extension est toujours `.ir`. Il en existe trois variantes, qui ne diffèrent que par l'en-tête `Filetype` et par
leur usage.

| Filetype | Sert à | Emplacement |
|---|---|---|
| `IR signals file` | Vos télécommandes (apprises, enregistrées depuis une télécommande universelle, téléchargées depuis l'application) | `/ext/infrared/` |
| `IR library file` | Les bibliothèques de télécommandes universelles | `/ext/infrared/assets/` |
| fichier de test (`.irtest`) | Les tests unitaires des décodeurs/encodeurs | dépôt du firmware uniquement |

## Fichier de télécommande

### Exemple

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

Le fichier peut contenir un nombre quelconque de boutons. Chaque bouton commence par `name:` ; la ligne de
commentaire `#` entre deux boutons n'est là que pour la lisibilité.

### Champs

| Champ | Utilisé dans | Type | Description |
|---|---|---|---|
| `name` | les deux | chaîne | Nom du bouton. ASCII imprimable uniquement. L'interface du Flipper limite les noms à 23 caractères. |
| `type` | les deux | chaîne | `parsed` ou `raw`. |
| `protocol` | parsed | chaîne | Nom du protocole, exactement comme dans la [liste des protocoles](/fr/infrared/protocols) (la commande CLI `ir` l'affiche aussi). |
| `address` | parsed | hex | Adresse, toujours sur **4 octets**, octet de poids faible en premier : `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Commande, toujours sur **4 octets**, octet de poids faible en premier. |
| `frequency` | raw | uint32 | Fréquence de la porteuse en Hz, en général `38000`. Plage valide : 10000-1000000. |
| `duty_cycle` | raw | flottant | Rapport cyclique de la porteuse, en général `0.33`. Doit être > 0 et ≤ 1. |
| `data` | raw | liste de uint32 | Timings en microsecondes entre les changements de niveau (marque, silence, marque, …), séparés par des espaces. **1024 valeurs maximum.** |

### Valeurs valides de `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` est un ajout d'Unleashed. `Pioneer` existe dans le firmware même si le document de format officiel ne le
liste pas encore.
:::

### Modifier à la main

- Conservez les deux lignes d'en-tête (`Filetype`, `Version`) en haut du fichier.
- Chaque bouton a besoin de `name` et `type`, puis soit de `protocol`/`address`/`command`, soit de
  `frequency`/`duty_cycle`/`data`.
- Pour fusionner deux télécommandes, copiez les blocs de boutons d'un fichier à la fin de l'autre.
- Les octets d'adresse et de commande doivent rester sur 4 octets même si le protocole utilise moins de bits ; les
  octets inutilisés valent `00`.
- Si le Flipper affiche *« Failed to load … »*, c'est qu'un des champs est mal formé (par exemple une ligne `data`
  RAW de plus de 1024 valeurs, ou une fréquence hors plage).

## Fichiers de bibliothèque {#library-files}

Les fichiers de bibliothèque utilisent exactement la même structure ; seul l'en-tête diffère :

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

La télécommande universelle recherche les signaux **par nom** : les noms doivent donc correspondre exactement aux
boutons de la bibliothèque (voir le tableau sur
[Contribuer ses captures](/fr/infrared/captures#button-names-per-library)). Les nouveaux modèles sont ajoutés à la
fin, précédés d'un commentaire `# Model: …`.

Un fichier de bibliothèque ne peut pas être ouvert via `Saved Remotes` : l'application signale
*« Library file … can't be opened as a remote »*.

## Fichiers de test (`.irtest`)

Utilisés uniquement par les tests unitaires du firmware
(`applications/debug/unit_tests/resources/unit_tests/infrared` dans le dépôt). Ils ressemblent aux fichiers de
télécommande, auxquels s'ajoute un type `parsed_array` pour des séquences entières de messages décodés :

| Champ | Utilisé dans | Type | Description |
|---|---|---|---|
| `name` | les deux | chaîne | Nom du signal, voir la convention de nommage ci-dessous. |
| `type` | les deux | chaîne | `parsed_array` ou `raw`. |
| `count` | parsed_array | uint32 | Nombre de messages du tableau, au moins 1. |
| `protocol`, `address`, `command` | parsed_array | | Comme ci-dessus, un jeu par message. |
| `repeat` | parsed_array | booléen | Indique si le message est une répétition (bouton maintenu). |
| `frequency`, `duty_cycle`, `data` | raw | | Comme ci-dessus. |

Les noms suivent le schéma `<name><test_number>` : `decoder_input1` (entrée raw du décodeur, qui est aussi la sortie
attendue de l'encodeur), `decoder_expected1` (sortie attendue du décodeur, qui est aussi l'entrée de l'encodeur),
`encoder_decoder_input1` (tableau parsed qui doit survivre à un aller-retour encodage → décodage). Chaque protocole
doit disposer d'un tel fichier de test.

## Voir aussi

- [Protocoles](/fr/infrared/protocols)
- [Contribuer ses captures](/fr/infrared/captures)
- [Apprendre et envoyer des signaux](/fr/infrared/read)
