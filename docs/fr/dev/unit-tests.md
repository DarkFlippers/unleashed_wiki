---
title: Tests unitaires
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Tests unitaires

Les tests unitaires fournissent des entrées connues au code d'une fonctionnalité et vérifient que les résultats sont
corrects. Ils sont indispensables pour obtenir du code robuste et sans bug.

Le firmware contient une application distincte, **`unit_tests`** (`applications/debug/unit_tests`), qui s'exécute
**sur le Flipper lui-même** — les tests utilisent donc le matériel réel et écartent les différences liées à la
plateforme.

Lorsque vous contribuez au firmware, fournissez des tests unitaires avec les nouvelles fonctionnalités quand c'est
possible, et exécutez les tests existants pour vous assurer que votre modification n'introduit pas de régression.

## Exécuter les tests

1. **Compilez le firmware avec le jeu d'applications de test :**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` est obligatoire
   `fbt_options.py` utilise `DEBUG=1` par défaut, et une image debug ne tient plus sous la région flash de la pile
   radio — l'empaquetage s'arrête avec `Firmware image overlaps C2 region and is not programmable!`. À partir de
   l'API 88.23, une image debug est environ 7 Ko trop volumineuse pour ce jeu d'applications (10 Ko pour le jeu par
   défaut) : réduire les tests n'y changera rien. (`COMPACT=1` est déjà la valeur par défaut ; il est écrit
   explicitement pour rester cohérent avec les autres commandes.)

   Gardez en tête que `DEBUG=0` supprime `furi_assert()` à la compilation : les assertions du code testé ne se
   déclencheront donc pas. `furi_check()` et les assertions minunit ne sont pas concernées.
   :::

   Le jeu d'applications `unit_tests` contient : `basic_services`, `updater_app`, `radio_device_cc1101_ext`,
   `unit_tests`, `infrared`, `archive`.

2. **Flashez le firmware en incluant les ressources de la carte SD** (`build/latest/resources`) — par exemple en
   installant le `.tgz` généré dans `dist/` avec qFlipper, ou en utilisant
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Les ressources de test doivent se retrouver
   sur la carte SD.
3. **Ouvrez une session [CLI](/fr/dev/cli)** et lancez :

   ```
   unit_tests
   ```

**Résultat attendu :** les suites s'exécutent l'une après l'autre, puis un rapport du type :

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Si vous voyez `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, c'est que les
ressources de la carte SD n'ont pas été installées — reprenez l'étape 2 avec les ressources.

Pour exécuter **un seul** test et ignorer les autres, passez son nom :

```
unit_tests test_infrared
```

Les autres suites sont ignorées (`Skipping …`) ; un nom erroné donne `No suite named …`. Les noms de tests
correspondent aux identifiants d'application (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`,
`test_nfc`, `test_lfrfid`, …) définis dans
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Il s'agit d'un build de firmware particulier, dépourvu des applications habituelles. Réinstallez un build normal
quand vous avez terminé.
:::

## Ajouter des tests unitaires

### Point d'entrée

Tous les tests sont lancés depuis l'application « mère » `unit_tests`. Le code de test lui-même est empaqueté comme
application de type `PLUGIN` dans un sous-répertoire de `tests/` à l'intérieur de `unit_tests`, et il est référencé
dans l'`application.fam` commun. Copiez la structure d'un test existant.

### Ressources de test

Certains tests ont besoin de données externes (« assets »). Elles résident dans
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
chacune dans son propre sous-répertoire. Ces ressources peuvent être de n'importe quel type : texte brut, Flipper
Format (FFF), binaire, etc.

### Exemple : protocoles infrarouges

Chaque protocole infrarouge possède un jeu de tests unitaires : ajoutez-en donc un quand vous ajoutez un nouveau
protocole.

1. Créez `test_<your_protocol_name>.irtest` dans le
   [répertoire des ressources infrarouges](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Remplissez-le avec des données de test (voir ci-dessous).
3. Ajoutez le code de test dans
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Compilez et installez le firmware avec les ressources, puis exécutez les tests et vérifiez qu'ils passent.

#### Format des données de test

Chaque test infrarouge comporte trois sections :

| Section | Rôle |
|---|---|
| `decoder` | Prend un signal brut, produit des messages décodés |
| `encoder` | Prend des messages décodés, produit un signal brut |
| `encoder_decoder` | Encode des messages décodés en signal brut, puis les décode à nouveau |

Les fichiers `.irtest` sont des [fichiers `.ir`](/fr/infrared/file-format) classiques, avec quelques ajouts :

- les signaux d'entrée du décodeur sont nommés `decoder_input_N` (N = numéro de séquence du test), la sortie attendue
  `decoder_expected_N` ;
- pour les tests de l'encodeur, les deux sont inversés ;
- les données décodées forment un **tableau**, car un même signal brut peut se décoder en plusieurs messages — un
  message unique est un tableau de taille 1.

Utilisez les fichiers `.irtest` existants comme exemples de syntaxe.

#### Enregistrer des signaux bruts

Ouvrez une session CLI et lancez :

```
ir rx raw
```

Pointez la télécommande vers le Flipper et appuyez sur des boutons. Les données brutes sont affichées dans un format
directement utilisable.

## Pages liées

- [Tests d'intégration](/fr/dev/testing)
- [Flipper Build Tool (fbt)](/fr/dev/fbt)
- [Interface en ligne de commande](/fr/dev/cli)
