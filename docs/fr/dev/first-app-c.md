---
title: Votre première application en C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Votre première application en C

Dans ce tutoriel, vous mettez en place un environnement de développement avec **uFBT**, vous générez un modèle
d'application, vous ajoutez une interface graphique simple, puis vous compilez et exécutez l'application sur votre
Flipper Zero.

Les applications construites ainsi sont des fichiers `.fap` (Flipper App Package) — elles résident sur la carte
microSD et sont chargées à la demande : vous n'avez donc pas besoin de recompiler le firmware.

## 1. Préparer l'environnement

Il vous faut un Flipper Zero, un câble USB et, sous Windows / macOS / Linux :

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) (« micro Flipper Build Tool ») — une version de
  [fbt](/fr/dev/fbt) contenant tout le nécessaire pour développer des applications. Installez-le avec
  `pip install ufbt` (voir le README d'uFBT pour les détails).
- [**Visual Studio Code**](https://code.visualstudio.com/) — l'IDE recommandé. D'autres fonctionnent aussi, mais
  nécessitent une configuration manuelle pour s'intégrer à uFBT.

::: tip Unleashed
uFBT télécharge le SDK **officiel** par défaut. Pour compiler pour Unleashed, exécutez une fois (et utilisez les
mêmes options à chaque mise à jour ultérieure) :

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Utilisez `--channel=release` si votre Flipper exécute un build release. La version du SDK doit correspondre au
firmware présent sur l'appareil — voir [l'étape 5](#_5-build-and-run-the-app).
:::

## 2. Générer un modèle d'application

1. Créez un dossier pour l'application, par ex. `test_app`.
2. Ouvrez un terminal dans ce dossier et lancez :

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT génère la structure de fichiers.
3. Lancez :

   ```sh
   ufbt vscode_dist
   ```

   Cela configure VS Code pour compiler et déboguer l'application directement depuis l'IDE.

::: warning
`APPID` ne peut contenir que des lettres minuscules `a-z`, des chiffres `0-9` et `_`.
:::

La structure obtenue :

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| Fichier | Rôle |
|---|---|
| `application.fam` | Le manifeste de l'application que uFBT lit pour savoir comment la compiler — voir [Manifestes d'application](/fr/dev/app-manifests) |
| `test_app.c` | Fichier source principal, avec le point d'entrée |
| `test_app.png` | Icône de l'application (10×10, 1 bit) |
| `.github/workflows/build.yml` | Configuration GitHub Actions — [en savoir plus](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Vos ressources graphiques |
| `images/.gitkeep` | Fichier témoin pour que Git suive le dossier `images/` vide |

## 3. Le code du modèle

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Le rôle de chaque partie :

- `#include <furi.h>` — l'en-tête principal de **Furi**, le cœur du firmware du Flipper
  ([API Furi](/fr/dev/furi-api)).
- `#include <test_app_icons.h>` — nécessaire si l'application utilise des images. uFBT convertit les PNG de
  `images/` au format interne du Flipper et génère automatiquement cet en-tête.
- `int32_t` — le type de retour habituel de la fonction principale d'une application.
- `UNUSED(p);` — une macro qui supprime l'avertissement « paramètre non utilisé ».
- `FURI_LOG_I` — écrit un message de niveau `info` dans le log du Flipper. Observez-le via `ufbt cli` →
  `log info`.
- `return 0;` — succès, selon la convention du C.

## 4. Ajouter une interface graphique

Ouvrez le dossier de l'application dans VS Code (**File → Open Folder…**). Installez les extensions suggérées
lorsqu'on vous le demande.

Affichons deux lignes à l'écran : `Hello world` et `I'm test_app!`. Remplacez le contenu de `test_app.c` par :

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Cela utilise le service d'interface **Dialogs**, l'API graphique la plus simple. Les autres approches sont décrites
dans [Interface graphique dans les applications](/fr/dev/gui).

## 5. Compiler et lancer l'application {#_5-build-and-run-the-app}

**La méthode rapide :**

1. Connectez le Flipper à votre ordinateur avec le câble USB.
2. Fermez qFlipper et tout autre programme utilisant le port série du Flipper.
3. Lancez :

   ```sh
   ufbt launch
   ```

   Cela compile l'application, l'envoie et la démarre sur le Flipper.

**La méthode manuelle :**

1. Compilez avec <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) ou
   <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (macOS), ou lancez `ufbt` dans le terminal. Le `.fap` autonome (avec
   toutes ses ressources) apparaît dans `dist/`.
2. Dans qFlipper, ouvrez **File Manager → SD Card → apps → Examples** (créez le dossier si besoin) et glissez-y le
   `.fap`.
3. Sur le Flipper : `Main Menu → Apps → Examples → votre application`.

**Résultat attendu :** un écran avec « Hello world » en en-tête et « I'm test_app! » en dessous. Appuyez sur
n'importe quel bouton pour le fermer.

::: warning La version du SDK doit correspondre
La version du SDK (API) du firmware présent sur l'appareil doit correspondre à celle du SDK avec lequel uFBT a
compilé. Si vous obtenez une erreur d'incompatibilité d'API au lancement de l'application, mettez à jour le SDK
d'uFBT pour qu'il corresponde à votre firmware, ou flashez le firmware correspondant avec `ufbt flash_usb`. Sur
Unleashed, assurez-vous que uFBT utilise l'index Unleashed (voir l'encadré de l'étape 1) — sans quoi
`ufbt flash_usb` installerait le firmware **officiel**.
:::

Pour voir la sortie de `FURI_LOG_I` : lancez `ufbt cli`, puis `log` (ou `log info` si vous avez changé le niveau de
log par défaut).

## Dépannage

| Problème | Solution |
|---|---|
| `ufbt create` refuse l'APPID | N'utilisez que `a-z`, `0-9`, `_` |
| Incompatibilité d'API / de SDK au lancement | Mettez à jour le SDK d'uFBT pour votre firmware (index Unleashed !) et recompilez |
| `ufbt launch` ne trouve pas l'appareil | Fermez qFlipper / Lab / tout terminal série ; rebranchez le câble |
| L'application n'est pas dans le menu | Elle doit se trouver dans un dossier de catégorie sous `/ext/apps/`, par ex. `/ext/apps/Examples/` |
| Rien dans `log` | Démarrez `log` **avant** de lancer l'application ; vérifiez le niveau de log |

## La suite ?

- Si votre C est un peu rouillé, *The C Programming Language* de B. Kernighan et D. Ritchie reste la référence
  classique.
- [Déboguer les applications](/fr/dev/debugging) — avancer pas à pas dans votre application avec un débogueur.
- [Interface graphique dans les applications](/fr/dev/gui) — ViewPort, Views et Scenes.
- [Manifestes d'application](/fr/dev/app-manifests) — toutes les options d'`application.fam`.
- Pas de PC ? [Compiler des applications sur Android](/fr/dev/android-build).
- Vous préférez les scripts ? [JavaScript sur le Flipper](/fr/dev/js-about).
