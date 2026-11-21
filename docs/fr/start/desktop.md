---
title: Bureau
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Bureau

Le bureau est l'écran d'accueil. Votre [dauphin](/fr/start/dolphin) y habite, et une barre d'état court en haut de
l'écran. Depuis le bureau, un simple appui sur une touche ouvre le menu principal, l'Archive, le Lock Menu et vos
applications favorites.

## Barre d'état

La ligne du haut affiche de petites icônes :

| Icône | Signification |
|---|---|
| Batterie | Niveau de charge. Affiche un éclair pendant la charge. Le style est défini par `Battery View` |
| Carte SD | microSD montée. Une icône barrée signifie que la carte n'a pas pu être montée : voir [Carte microSD](/fr/start/sd-card) |
| Bluetooth | Le BLE est activé. Une icône différente signale qu'un appareil est connecté |
| Cadenas | Le Flipper est verrouillé |
| Haut-parleur barré | Mode furtif : son et vibration désactivés (voir [Lock Menu](#lock-menu)) |
| PC | Connecté à qFlipper / Flipper Lab en USB |
| Manette | Le Dummy Mode est activé |
| Module | Un module d'extension est connecté |
| Balise | Mode balise BLE (par exemple FindMy Flipper) |
| Application en arrière-plan | Une application tourne en arrière-plan |

::: tip Unleashed
- **Settings → Desktop → Battery View** choisit le style de la batterie : `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`,
  `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` affiche l'heure sur le bureau. Le format (24h/12h) vient de
  **Settings → System → Time Format**.
:::

## Boutons du bureau

| Bouton | Appui court | Appui long |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Verrouillage** (avec le PIN s'il est défini) |
| <kbd>↓</kbd> | **Archive** | Écran d'informations / de débogage de l'appareil |
| <kbd>←</kbd> | Favorite App - Left Short (menu **Apps** par défaut) | Favorite App - Left Long |
| <kbd>→</kbd> | **Passport** par défaut (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Écran d'**extinction** |

### Écran d'informations de l'appareil {#info-screen}

Un appui long sur <kbd>↓</kbd> ouvre un écran d'information : version du firmware et date de build, version du
matériel, temps de fonctionnement, nom du Flipper et état du mode Debug (`ON`/`OFF`).

![Écran d'informations de l'appareil : version du firmware, version du matériel, temps de fonctionnement et état du mode Debug](/screens/desktop/debug.png)

Sur cet écran, un **appui long sur <kbd>OK</kbd> active ou désactive Debug** — le même interrupteur que
`Settings → System → Debug` ([Paramètres](/fr/start/settings)), sans parcourir les menus. Un appui court sur
<kbd>BACK</kbd> ramène au bureau.

Debug `ON` ajoute des entrées normalement masquées : l'onglet **Internal** de l'[Archive](#archive) et
`Signal Settings` dans le menu d'un signal Sub-GHz enregistré ([Signal Settings](/fr/subghz/signal-settings)).
Désactivez-le une fois terminé — les réglages de débogage ralentissent le Flipper et l'empêchent de se mettre en
veille.

## Main Menu

Appuyez sur <kbd>OK</kbd>. Le menu principal s'ouvre sur **Apps** (toutes les applications `.fap` de la carte SD,
regroupées par catégorie), suivi de **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock**, et enfin **Settings**. La liste est circulaire : appuyer sur <kbd>↑</kbd> sur
**Apps** saute directement à **Settings**.

![Menu principal avec Apps sélectionné, Settings au-dessus et Sub-GHz en dessous](/screens/mainmenu/main.png)

::: tip Styles de menu
**Settings → Desktop → Menu Style** change l'apparence du menu principal. Les styles sont des plugins dans
`/ext/apps_data/loader/plugins/` (fichiers commençant par `menu_style_`). `Default` correspond à la liste intégrée.
:::

## Lock Menu {#lock-menu}

Appuyez sur <kbd>↑</kbd> depuis le bureau. Déplacez-vous avec <kbd>↑</kbd>/<kbd>↓</kbd> et appuyez sur <kbd>OK</kbd> :

| Entrée | Effet |
|---|---|
| **Turn Bluetooth On / Off** | Active ou désactive le BLE sans passer par les réglages |
| **Mute / Unmute** | Mode furtif : plus de son ni de vibration. Les réglages **Volume** et **Vibro** affichent `Stealth` tant qu'il est actif |
| **Dummy Mode / Default Mode** | Entrer dans le [Dummy Mode](#dummy-mode) ou en sortir |

Appuyez sur <kbd>←</kbd> ou <kbd>→</kbd> dans le Lock Menu pour ouvrir la seconde page, **Quick Settings** :

| Entrée | Commande |
|---|---|
| Luminosité | <kbd>OK</kbd> pour éditer, puis <kbd>←</kbd>/<kbd>→</kbd> (ou <kbd>↑</kbd>/<kbd>↓</kbd>), par pas de 5 % |
| Volume | Idem. Un bref bip est joué pour que vous entendiez le nouveau niveau |
| Vibro | <kbd>OK</kbd> l'active ou le désactive immédiatement |

<kbd>BACK</kbd> quitte l'entrée en cours d'édition, et un second <kbd>BACK</kbd> quitte la page. Les modifications
vont dans les mêmes réglages que **LCD and Notifications**.

::: tip Unleashed
Dans Unleashed, le **verrouillage lui-même** s'obtient par un appui long sur <kbd>↑</kbd> depuis le bureau : avec le
PIN s'il y en a un, ou par un verrouillage simple sinon.
:::

## Verrouillage et PIN

- **Verrouiller :** maintenez <kbd>↑</kbd> depuis le bureau. Sans PIN, les boutons sont bloqués. **Pour déverrouiller,
  appuyez trois fois sur <kbd>BACK</kbd>** rapidement.
- **Avec un PIN :** définissez-le dans **Settings → Desktop → PIN Setup → Set PIN**. Un PIN compte de 4 à 10 appuis sur
  les flèches. Le Flipper verrouillé demande alors le PIN. Après des tentatives erronées, il affiche `Wrong PIN!` et
  impose un délai avant l'essai suivant.
- **Verrouillage automatique :** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) verrouille l'appareil
  après ce délai d'inactivité. **Auto Lock disarm by active USB session** = `ON` empêche le verrouillage automatique
  tant que le Flipper est connecté en USB.

::: warning PIN oublié
Un PIN oublié ne peut être réinitialisé qu'avec l'ensemble des réglages utilisateur : voir
[Restauration → Réinitialiser un code PIN oublié](/fr/start/recovery#reset-pin). Les fichiers de la carte microSD sont
conservés.
:::

## Dummy Mode {#dummy-mode}

Le Dummy Mode transforme le Flipper en jouet. La plupart des fonctions sont masquées et les boutons lancent les applications de votre choix, par exemple des jeux. Activez-le dans **Lock Menu → Dummy Mode**, et désactivez-le avec **Lock Menu → Default Mode**.

En Dummy Mode, chaque bouton peut lancer sa propre application. Configurez-les dans **Settings → Desktop** :

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`, `- Ok Long`.

Un bouton non affecté ouvre le Passport. Un appui court sur <kbd>↑</kbd> ouvre toujours le Lock Menu. Si
`DummyMode - Up Long` est réglé sur `None`, un appui long sur <kbd>↑</kbd> verrouille l'appareil.

::: tip Unleashed
Le firmware d'origine propose 4 raccourcis en Dummy Mode. Unleashed en propose 9 (appui court et appui long sur chaque
bouton), ce qui permet de garder plusieurs jeux à un appui de distance.
:::

## Applications favorites (accès rapide)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Pour chaque emplacement, vous pouvez choisir :
- **Apps Menu (Default)** ou **Passport (Default)** : la valeur par défaut intégrée pour cet emplacement ;
- **None (disable)** : le bouton ne fait rien ;
- **Lock Flipper** ;
- n'importe quelle application du menu principal ;
- **[Select App]** : sélectionnez n'importe quel fichier `.fap` dans `/ext/apps/`.

## Archive

Appuyez sur <kbd>↓</kbd>. L'Archive présente vos fichiers enregistrés, répartis en onglets. Changez d'onglet avec
<kbd>←</kbd>/<kbd>→</kbd> :

| Onglet | Dossier / contenu |
|---|---|
| Favorites | Les fichiers que vous avez épinglés |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote` : maps Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` et dumps T5577) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook` : répertoire SIM800 (`.phone`) |
| U2F | Jeton U2F |
| Apps | `/ext/apps` (`.fap` et `.js`) |
| Internal | Stockage interne (uniquement avec **Debug** = `ON`) |
| Browser | Toute la carte microSD |

Appuyez sur <kbd>OK</kbd> sur un fichier pour ouvrir son menu contextuel : exécuter/émuler, **Pin**/**Unpin** (ajouter
aux Favorites), **Rename**, **Delete**, et dans le Browser également **Cut**, **Copy**, **Paste** et **NewDir**. Dans
l'onglet Favorites, maintenez <kbd>OK</kbd> pour ouvrir le menu.

::: tip Épingler des réglages dans les favoris
Dans **Main Menu → Settings**, maintenez <kbd>OK</kbd> sur n'importe quelle entrée de réglages pour l'épingler dans les
Favorites. Vous pourrez ensuite l'ouvrir depuis l'Archive sans parcourir les menus.
:::

## Passport

Appuyez sur <kbd>→</kbd> depuis le bureau, ou ouvrez **Settings → Passport**. Cet écran affiche le nom du dauphin (le
nom du Flipper), son humeur et son niveau : voir [Le dauphin](/fr/start/dolphin).
