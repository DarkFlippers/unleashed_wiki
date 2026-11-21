---
title: Manifestes d'application (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# Manifestes d'application (.fam)

Chaque composant du firmware — services, applications utilisateur, pages de réglages — est développé indépendamment
et décrit par un fichier manifeste appelé `application.fam`. Celui-ci déclare les propriétés de base du composant et
la façon dont il s'articule avec le reste du système.

À la compilation, `fbt` collecte tous les manifestes, résout leurs dépendances et ne compile **que** les composants
référencés par la configuration de build actuelle (voir
[fbt → jeux d'applications du firmware](/fr/dev/fbt#firmware-app-sets)).

## Définition d'une application

Un manifeste est un extrait de Python appelant `App()` avec des arguments nommés. Seuls **`appid`** et **`apptype`**
sont obligatoires ; le reste est facultatif et certains champs n'ont de sens que pour certains types
d'applications.

### Types d'applications (`apptype`)

`apptype` est un membre de `FlipperAppType` :

| Valeur | Type de composant |
|---|---|
| `SERVICE` | Service système, créé très tôt au démarrage |
| `SYSTEM` | Non affiché dans les menus ; démarré par d'autres applications ou depuis le CLI |
| `APP` | Application classique du menu principal |
| `PLUGIN` | Compilé dans le firmware et placé dans le menu Plugins |
| `DEBUG` | Visible uniquement dans le menu Debug, avec le mode debug activé |
| `ARCHIVE` | L'unique application Archive |
| `SETTINGS` | Placé dans le menu Settings du système |
| `STARTUP` | Callback exécuté au démarrage du système ; ne définit pas d'application distincte |
| `EXTERNAL` | Compilé en application `.fap` |
| `METAPACKAGE` | Aucun code ; sert à déclarer des dépendances et des ensembles d'applications |

### Paramètres communs

| Paramètre | Signification |
|---|---|
| `appid` | Identifiant texte de l'application dans le système de build. Utilisé dans les configurations de build et pour résoudre les dépendances et les conflits |
| `apptype` | Voir le tableau ci-dessus |
| `name` | Nom affiché dans les menus |
| `entry_point` | Fonction C utilisée comme point d'entrée. Les noms C++ sont décorés — encadrez la fonction d'un `extern "C"` |
| `flags` | Drapeaux internes pour les applications système. **À ne pas utiliser** |
| `cdefines` | Définitions du préprocesseur C déclarées globalement pour les autres applications quand celle-ci est dans le build. Pour les applications externes — utilisées lors de la compilation de l'application elle-même |
| `requires` | Identifiants d'applications à ajouter au build chaque fois que celle-ci est compilée |
| `conflicts` | Identifiants d'applications en conflit avec celle-ci ; si l'une d'elles est présente, `fbt` interrompt la compilation |
| `provides` | Fonctionnellement identique à `requires` |
| `stack_size` | Taille de pile en octets allouée au démarrage de l'application. Trop petite → plantage par débordement de pile ; trop grande → moins de tas pour l'application |
| `icon` | Icône animée issue des ressources intégrées, utilisée quand l'application est compilée dans le firmware |
| `order` | Ordre de tri au sein de son groupe (plus petit = plus tôt). Utilisé pour les hooks de démarrage et les entrées de menu |
| `sdk_headers` | En-têtes C de cette application à inclure dans l'API destinée aux applications externes |
| `targets` | [Cibles matérielles](/fr/dev/hardware-targets) compatibles. Par défaut `["all"]` |
| `resources` | Dossier des sources de l'application empaqueté comme ressources de la carte SD (uniquement si l'application est dans le build). Par défaut `""` — aucun |

::: tip
Utilisez les [commandes CLI](/fr/dev/cli) `top` et `free` pour profiler l'utilisation mémoire de votre application
lors du choix de `stack_size`.
:::

### Paramètres des applications externes (FAP)

| Paramètre | Signification |
|---|---|
| `sources` | Masques de fichiers pour rassembler les sources du dossier de l'application. Par défaut `["*.c*"]` (C et C++). Le dossier `lib` est réservé à `fap_private_libs`. Les masques commençant par `!` excluent des fichiers ; les masques sans joker (`*`, `?`) sont des chemins littéraux. Exemple : `["*.c*", "!plugins"]` |
| `fap_version` | Chaîne de version de l'application, par défaut `"0.1"`. Un tuple `(x, y)` fonctionne aussi. Des parties supplémentaires séparées par des points sont autorisées, mais seuls les numéros majeur et mineur sont stockés dans le `.fap` |
| `fap_icon` | Fichier `.png`, couleur 1 bit, 10×10 px, embarqué dans le `.fap` |
| `fap_libs` | Bibliothèques supplémentaires à lier — donne accès à des fonctions non exportées par le firmware, au prix d'un `.fap` plus gros et de davantage de RAM |
| `fap_category` | Sous-catégorie de l'application ; détermine aussi le dossier sous `apps/` sur la carte SD |
| `fap_description` | Description courte (peut être vide) |
| `fap_author` | Auteur (peut être vide) |
| `fap_weburl` | Page d'accueil (peut être vide) |
| `fap_icon_assets` | Dossier contenant les ressources graphiques à prétraiter et à compiler avec l'application |
| `fap_extbuild` | Parties des sources compilées par des outils externes : une liste d'`ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Booléen, `False` par défaut. Type `PLUGIN` uniquement : embarque le plugin dans le `.fap` de l'application hôte comme ressource ; il est extrait dans `apps_assets/APPID` au démarrage |
| `fap_private_libs` | Bibliothèques livrées sous forme de sources avec l'application — voir ci-dessous |

#### Commandes de build externes (`fap_extbuild`)

Les commandes s'exécutent depuis la racine du firmware. Les fichiers intermédiaires doivent aller dans le dossier de
build temporaire de l'application. `fbt` développe ces variables (ainsi que d'autres variables internes) :

- `${FAP_WORK_DIR}` — le dossier de build temporaire de l'application
- `${FAP_SRC_DIR}` — le dossier des sources de l'application

Exemple — compiler une application depuis des sources Rust :

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Bibliothèques privées (`fap_private_libs`)

Les sources des bibliothèques vont dans un sous-dossier de `lib/` à l'intérieur du dossier de l'application. Chaque
bibliothèque est un appel à `Lib()` :

| Paramètre de `Lib()` | Signification | Par défaut |
|---|---|---|
| `name` | Nom du dossier de la bibliothèque (**obligatoire**) | — |
| `fap_include_paths` | Chemins (relatifs à la bibliothèque) ajoutés au chemin d'inclusion de l'application | `["."]` |
| `sources` | Masques de fichiers pour les sources de la bibliothèque, relatifs à sa racine | `["*.c*"]` |
| `cflags` | Options de compilation supplémentaires | `[]` |
| `cdefines` | Définitions supplémentaires du préprocesseur | `[]` |
| `cincludes` | Chemins d'inclusion supplémentaires, relatifs à la racine de l'**application** (par ex. pour des en-têtes de configuration) | `[]` |

Exemple :

```python
    fap_private_libs=[
            Lib(
                name="mbedtls",
                fap_include_paths=["include"],
                sources=[
                    "library/des.c",
                    "library/sha1.c",
                    "library/platform_util.c",
                ],
                cdefines=["MBEDTLS_ERROR_C"],
            ),
            Lib(
                name="loclass",
                cflags=["-Wno-error"],
            ),
        ],
```

Ce que `fbt` en fait :

- **mbedtls** — compilée depuis `lib/mbedtls` ; `lib/mbedtls/include` est ajouté au chemin d'inclusion de
  l'application ; seuls les trois fichiers listés sont compilés ; `MBEDTLS_ERROR_C` est défini pour ses sources.
- **loclass** — compilée depuis toutes les sources de `lib/loclass` ; `lib/loclass` est ajouté au chemin
  d'inclusion ; les avertissements ne sont **pas** traités comme des erreurs (`-Wno-error`), ce qui est pratique pour
  du code tiers volumineux.

Les deux bibliothèques sont liées à l'application.

## Un fichier `.fam` complet

Un même fichier peut définir plusieurs applications. Voici une partie de
`applications/services/bt/application.fam` :

```python
App(
    appid="bt_start",
    apptype=FlipperAppType.STARTUP,
    entry_point="bt_on_system_start",
    order=70,
)

App(
    appid="bt_settings",
    name="Bluetooth",
    apptype=FlipperAppType.SETTINGS,
    entry_point="bt_settings_app",
    stack_size=1 * 1024,
    requires=[
        "bt",
        "gui",
    ],
    order=10,
)
```

Un manifeste pour votre propre application externe, tel que généré par `ufbt create APPID=test_app` (depuis
`scripts/ufbt/project_template/app_template/application.fam`) :

```python
# For details & more options, see documentation/AppManifests.md in firmware repo

App(
    appid="test_app",  # Must be unique
    name="App test_app",  # Displayed in menus
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Optional values
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bit PNG
    # fap_description="A simple app",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Image assets to compile for this application
)
```

Pour d'autres exemples, consultez les fichiers `.fam` répartis dans le firmware — par exemple
`applications/system/*/application.fam` pour les applications Unleashed supplémentaires.

## Pages liées

- [Votre première application en C](/fr/dev/first-app-c)
- [Flipper Build Tool (fbt)](/fr/dev/fbt)
- [Cibles matérielles](/fr/dev/hardware-targets)
