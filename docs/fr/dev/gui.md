---
title: Interface graphique dans les applications
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# Interface graphique dans les applications

Cette page explique les notions de base de l'interface graphique du firmware du Flipper et compare les trois façons
de construire l'interface d'une application, de la plus simple à la plus puissante :

1. [Dialogs](#using-dialogs) — quelques boîtes de message, aucun dessin personnalisé.
2. [ViewPort](#using-a-viewport) — une zone plein écran que vous dessinez vous-même ; idéal pour les jeux.
3. [Views et Scenes](#using-views-and-scenes) — applications multi-écrans avec menus et navigation (la plupart des
   applications intégrées).

## Notions de base

### Boucle d'événements

Un mécanisme asynchrone de traitement des événements. Au lieu d'interroger en boucle ou de bloquer en attendant des
événements (appuis de boutons, paquets reçus, minuteurs), vous enregistrez des fonctions de traitement appelées
lorsque l'événement se produit : la boucle principale reste ainsi libre pour d'autres tâches.

### Canvas

Le **canvas** est une zone de dessin brute, sans aucune abstraction. Y dessiner directement est utile pour des
éléments visuels personnalisés (dans les jeux par exemple), mais la plupart des applications n'en ont pas besoin.

### ViewPort

Un **ViewPort** définit la façon dont une zone d'écran, de position et de taille données, est dessinée et réagit aux
entrées. Plusieurs ViewPorts forment une *pile de dessin* rendue de bas en haut : ils peuvent donc se chevaucher. Un
ViewPort peut être activé ou désactivé après sa création.

### Model, View et View Dispatcher

Ces éléments séparent l'interface graphique des données, ce qui rend les applications plus faciles à développer, à
maintenir et à tester.

- **Model** — les données ; techniquement une structure en mémoire.
- **View** — le rendu et le traitement des entrées. Elle lit le Model pour dessiner et le modifie lors du traitement
  des événements.
- **View Dispatcher** — conserve des références vers toutes les Views dont l'application a besoin et bascule entre
  elles à la demande.

### Modules de vue

Des modèles plein écran prêts à l'emploi (View + Model) pour les interfaces Flipper typiques, inclus dans le firmware
(`applications/services/gui/modules/`) :

| Module | Usage typique |
|---|---|
| `button_menu` | Menu de grands boutons |
| `button_panel` | Grille de boutons sélectionnables |
| `byte_input` | Saisir des octets en hexadécimal |
| `date_time_input` | Saisir une date et une heure |
| `dialog_ex` | Boîte de dialogue avec en-tête, texte, icône et jusqu'à trois boutons |
| `empty_screen` | Écran vide |
| `file_browser` | Choisir un fichier sur la carte SD |
| `loading` | Animation « Loading… » |
| `menu` | Liste façon menu principal, avec icônes |
| `number_input` | Saisir un nombre |
| `popup` | Message temporaire avec délai d'expiration |
| `submenu` | Simple liste verticale d'entrées |
| `text_box` | Texte défilant |
| `text_input` | Clavier à l'écran |
| `variable_item_list` | Liste de réglages avec valeurs ◀ ▶ |
| `widget` | Composition libre de textes, d'icônes et de boutons |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Code source : [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene et Scene Manager

Une **Scene** contrôle le comportement de l'application sur un écran. Par exemple, l'application GPIO déclare ces
scènes dans `applications/main/gpio/scenes/gpio_scene_config.h` :

| Scène | Écran |
|---|---|
| `gpio_scene_start` | Menu de départ |
| `gpio_scene_usb_uart` | Interface du pont USB-UART |
| `gpio_scene_usb_uart_cfg` | Réglages du pont USB-UART (fichier `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | « Connection Is Active! Disconnect from PC or phone to use this function. » — affiché lorsque vous ouvrez le pont USB-UART alors que qFlipper ou l'application mobile est connecté |
| `gpio_scene_test` | Contrôle manuel du GPIO |

Depuis le menu de départ, vous allez vers le contrôle manuel ou vers le mode pont USB-UART, et depuis le pont vers
ses réglages.

Chaque scène implémente trois fonctions :

- `on_enter` — initialiser les vues de la scène ;
- `on_exit` — désinitialiser et libérer les ressources ;
- `on_event` — traiter les événements entrants.

Un gestionnaire d'événements peut basculer vers une autre scène — par exemple, sélectionner une entrée de menu mène à
la scène correspondante. Le **Scene Manager** effectue ces transitions et conserve l'historique de navigation, ce qui
rend gérables les parcours de navigation complexes.

## Approches du développement de l'interface

Plus votre interface est complexe, plus vous avez besoin d'abstractions graphiques.

### Avec Dialogs {#using-dialogs}

L'approche la plus simple — adaptée quand toute l'interface se résume à des boîtes de dialogue. API :
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Approche Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Avantages :** simple et facile.
**Inconvénients :** uniquement des boîtes de dialogue, pas d'interface complexe ; les dialogues sont
**synchrones** — aucun autre code de l'application ne s'exécute avant que l'utilisateur n'appuie sur un bouton.

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app(void* p) {
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

### Avec un ViewPort {#using-a-viewport}

Vous créez un unique ViewPort plein écran qui dessine l'affichage et traite toutes les entrées.

![Approche ViewPort](/img/dev/app_dev_gui_viewport.png)

**Avantages :** facile — un seul ViewPort, aucune autre abstraction ; rapide et bien adapté aux jeux ; contrôle total
de l'écran.
**Inconvénients :** aucune aide à la navigation ; pas de Views réutilisables.

Exemples :

- de nombreux [outils de débogage](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- la [boîte de dialogue d'appairage BLE](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- la plupart des jeux, par ex. [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game),
  fourni avec Unleashed

### Avec Views et Scenes {#using-views-and-scenes}

L'approche principale pour les applications dotées d'interfaces complexes et hiérarchiques — utilisée par la plupart
des applications Flipper.

![Approche Views et Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Avantages :** prend en charge les navigations complexes ; les vues sont réutilisées ; de nombreux modules de vue
sont prêts à l'emploi.
**Inconvénients :** demande du temps pour être assimilée ; implémentation plus complexe.

Exemples (sources Unleashed) :

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
Dans les applications fondées sur les scènes, la liste des scènes se trouve dans `scenes/<app>_scene_config.h`, et
chaque fichier `scenes/*.c` implémente un écran. Les lire est la façon la plus rapide de comprendre comment les menus
d'une application sont construits.
:::

## Choisir une approche

| Vous voulez… | Utilisez |
|---|---|
| Afficher un message ou poser une question oui/non | Dialogs |
| Un jeu, un visualiseur, ou un seul écran personnalisé | ViewPort |
| Des menus, des réglages, une sélection de fichiers, plusieurs écrans | Views et Scenes |

## Pour aller plus loin (ressources externes)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) de Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) de Derek Jamison
- Tutoriels YouTube de Derek Jamison :
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Pages liées

- [Votre première application en C](/fr/dev/first-app-c)
- [API Furi](/fr/dev/furi-api)
- [JavaScript sur le Flipper](/fr/dev/js-about) — les scripts JS peuvent utiliser beaucoup des mêmes modules de vue
