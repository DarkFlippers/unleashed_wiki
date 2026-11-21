---
title: Télécommande USB / Bluetooth (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# Télécommande USB / Bluetooth (HID)

L'application HID fait passer le Flipper pour un clavier, une souris ou une télécommande multimédia (un **H**uman
**I**nterface **D**evice USB) aux yeux d'un ordinateur, d'un téléphone ou d'une tablette. La même application est
compilée en deux variantes :

| Application | Emplacement sur le Flipper | Connexion |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | câble USB |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

La façon de la connecter est décrite dans [Appairer la télécommande HID](/fr/apps/controllers). Cette page décrit
chaque mode.

## Modes

Le menu de départ propose :

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

La version Bluetooth propose en plus `Bluetooth Remote Name` et `Bluetooth Unpairing`.

::: tip Unleashed
La documentation officielle décrit Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler et Mouse Clicker. Le build
Unleashed de l'application comporte aussi **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**,
**PushToTalk**, ainsi que **Bluetooth Remote Name** pour changer le nom diffusé par la télécommande.
:::

Dans presque tous les modes, **maintenez <kbd>Back</kbd> pour revenir** à la liste des modes ; toutes les touches sont
relâchées à la sortie.

### Keynote et Keynote Vertical

Un télécommande de présentation. Keynote Vertical est identique, mais pivoté pour tenir le Flipper à la verticale.

| Bouton | Envoie |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | touches fléchées (diapositive suivante / précédente) |
| <kbd>OK</kbd> | Espace |
| <kbd>Back</kbd> | Retour arrière + « AC Back » (quitte le mode diaporama dans la plupart des applications) |
| maintenir <kbd>Back</kbd> | quitter |

### Keyboard

Un clavier QWERTY à l'écran avec chiffres, symboles, F1-F12, Esc, Tab, Entrée, Retour arrière, Suppr et les
modificateurs Ctrl, Alt, Shift et Cmd (Win).

1. Déplacez-vous avec les flèches, appuyez sur <kbd>OK</kbd> pour saisir la touche sélectionnée.
2. Sélectionnez la touche ⬆ (Shift) pour saisir les majuscules et la deuxième rangée de symboles.
3. Pour un raccourci, appuyez d'abord sur le modificateur (Ctrl, Alt ou Cmd), puis sur la touche.
4. Maintenez <kbd>Back</kbd> pour quitter.

### Numpad

Un pavé numérique : `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Entrée du pavé), `NL` (Verr. num.) et Retour arrière. Les
flèches sélectionnent, <kbd>OK</kbd> appuie sur la touche, maintenez <kbd>Back</kbd> pour quitter.

### Media

| Bouton | Envoie |
|---|---|
| <kbd>OK</kbd> | Lecture / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | piste précédente / suivante |
| <kbd>↑</kbd> / <kbd>↓</kbd> | volume plus / moins fort |
| maintenir <kbd>Back</kbd> | quitter |

Sur les téléphones, les touches de volume servent aussi de déclencheur photo : ouvrez l'appareil photo et appuyez sur
<kbd>↑</kbd> ou <kbd>↓</kbd> pour prendre une photo ou démarrer/arrêter une vidéo.

### Apple Music macOS

| Bouton | Envoie |
|---|---|
| <kbd>OK</kbd> | Lecture / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | piste précédente / suivante |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (volume dans Apple Music) |
| maintenir <kbd>Back</kbd> | quitter |

### Movie

| Bouton | Envoie |
|---|---|
| <kbd>OK</kbd> | Lecture / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | flèche gauche / droite (déplacement dans la plupart des lecteurs) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | volume plus / moins fort |
| maintenir <kbd>Back</kbd> | quitter |

### Mouse

| Bouton | Action |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | déplacer le curseur ; maintenir accélère |
| <kbd>OK</kbd> | clic gauche |
| maintenir <kbd>OK</kbd> | maintenir le bouton gauche enfoncé (glisser, « Selecting... ») |
| <kbd>Back</kbd> | clic droit |
| maintenir <kbd>Back</kbd> | quitter |

### TikTok / YT Shorts

Pour les applications de vidéos courtes sur téléphone ou tablette.

| Bouton | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | faire défiler vers la vidéo précédente / suivante |
| <kbd>OK</kbd> | double tap (j'aime) |
| <kbd>←</kbd> / <kbd>→</kbd> | volume moins / plus fort |
| <kbd>Back</kbd> | simple tap (pause) |
| maintenir <kbd>Back</kbd> | quitter |

::: tip iPhone / iPad
Si le mode TikTok ne fait rien sous iOS, activez
`Settings → Accessibility → Touch → AssistiveTouch`, puis, dans **Pointer Devices → Devices → Bluetooth Devices**,
sélectionnez votre Flipper.
:::

### Mouse Clicker

Clique automatiquement à une cadence définie.

| Bouton | Action |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | clics par seconde, jusqu'à 100 (1 par défaut) |
| <kbd>←</kbd> / <kbd>→</kbd> | quel bouton : gauche, droit ou molette (milieu) |
| <kbd>Back</kbd> | quitter |

### Mouse Jiggler

Déplace légèrement le curseur à intervalle fixe, pour que l'ordinateur ne se mette pas en veille et ne vous affiche pas
comme « absent ».

1. Avant de démarrer, choisissez l'intervalle avec <kbd>←</kbd> / <kbd>→</kbd> : 500, 2000, 5000, 10000, 30000 ou
   60000 ms (5000 ms par défaut).
2. Appuyez sur <kbd>OK</kbd> pour **Start**, de nouveau pour **Stop**. Tant que l'hôte n'est pas connecté, l'écran
   indique `Waiting for Connection...`.
3. <kbd>Back</kbd> quitte.

### Mouse Jiggler Stealth

Comme le jiggler, mais les déplacements se font à intervalles aléatoires entre un minimum et un maximum que vous
définissez en minutes (1 à 30), ce qui ressemble moins à une machine. À l'arrêt, <kbd>↑</kbd> / <kbd>↓</kbd>
modifient le minimum et <kbd>→</kbd> / <kbd>←</kbd> augmentent / réduisent le maximum ; <kbd>OK</kbd> démarre ou
arrête.

### PushToTalk

Un bouton muet / push-to-talk pour les appels vidéo.

1. Choisissez la liste correspondant à votre système (**macOS** ou **Win/Linux**), puis l'application : Google Meet,
   Google Meet Global, Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle,
   TeamSpeak, Teams, Webex, Zoom ou Zoom Global.
2. Faites un appui long sur <kbd>OK</kbd> sur une entrée de la liste pour lire son aide (certaines applications
   demandent un réglage ou une extension, par exemple un raccourci global pour Google Meet ou l'affectation des
   touches dans TeamSpeak).
3. Pendant l'appel : <kbd>Back</kbd> active/désactive le micro, **maintenez <kbd>OK</kbd>** pour le push-to-talk (le
   micro se coupe au relâchement), maintenez <kbd>→</kbd> pour changer l'état du micro côté Flipper s'il s'est
   désynchronisé de l'ordinateur. Pour Zoom, un appui long sur <kbd>←</kbd> envoie Entrée.
4. Maintenez <kbd>Back</kbd> pour quitter.

### Bluetooth Remote Name et Bluetooth Unpairing (Bluetooth uniquement)

- **Bluetooth Remote Name** : saisissez un nom dans `Bluetooth Name` ; la télécommande se diffuse sous ce nom. Par
  défaut, elle apparaît comme `Control <nom du Flipper>`.
- **Bluetooth Unpairing** : demande `Unpair All Devices? All previous pairings will be lost!` ; appuyez sur **Unpair**
  pour oublier tous les hôtes appairés avec la télécommande. La télécommande conserve ses propres clés d'appairage
  (`/ext/apps_data/hid_ble/.bt_hid.keys`), séparées des appairages Bluetooth principaux du Flipper.

## Pages liées

- [Appairer la télécommande HID](/fr/apps/controllers)
- [Bad USB](/fr/badusb/usage)
- [Applications fournies avec Unleashed](/fr/apps/catalog)
