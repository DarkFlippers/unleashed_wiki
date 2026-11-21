---
title: Commandes
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Commandes

Le Flipper Zero dispose d'un pavé directionnel à 5 positions et d'un bouton <kbd>BACK</kbd> séparé.

| Bouton | Rôle |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Se déplacer dans les menus et les claviers virtuels. <kbd>←</kbd>/<kbd>→</kbd> modifient la valeur de l'option sélectionnée |
| <kbd>OK</kbd> | Lancer une application, valider un choix. Un appui long ouvre souvent des actions supplémentaires |
| <kbd>BACK</kbd> | Revenir en arrière ou quitter l'application. Un appui long sur le bureau ouvre l'écran d'extinction |

Dans une liste, les flèches déplacent le cadre autour de l'élément sélectionné et <kbd>OK</kbd> l'ouvre :

![Menu principal avec le cadre sur Sub-GHz](/screens/mainmenu/subghz.png)

Dans ce wiki, « maintenir » ou « appui long » signifie garder un bouton enfoncé pendant environ une seconde. Les
indications de boutons en bas de l'écran (par exemple `◀ Cancel` ou `Save ▶`) montrent le rôle de <kbd>←</kbd>,
<kbd>OK</kbd> et <kbd>→</kbd> sur cet écran.

## Mode gaucher

**Main Menu → Settings → System → Hand Orient → `Lefty`**

L'écran pivote de 180° et le pavé est réaffecté en conséquence, ce qui permet de tenir le Flipper dans la main gauche.

## Raccourcis

| Action | Comment |
|---|---|
| Allumer | Maintenir <kbd>BACK</kbd> environ 3 s |
| Éteindre | Maintenir <kbd>BACK</kbd> sur le bureau → **Power Off** (<kbd>→</kbd>) |
| Redémarrer (appareil figé) | Maintenir <kbd>←</kbd> + <kbd>BACK</kbd> environ 5 s |
| Redémarrage matériel (coupure d'alimentation) | Débrancher l'USB, maintenir <kbd>BACK</kbd> environ 30 s |
| Redémarrer en DFU (restauration) | Maintenir <kbd>←</kbd> + <kbd>BACK</kbd>, relâcher <kbd>BACK</kbd>, garder <kbd>←</kbd> jusqu'à ce que la LED bleue s'allume |

Toutes les combinaisons de réinitialisation et de DFU, et les cas où chacune échoue, sont décrites dans
[Combinaisons de touches](/fr/start/key-combos).

## Raccourcis du bureau

| Bouton | Appui court | Appui long |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | Application favorite (OK Long) |
| <kbd>↑</kbd> | Lock Menu | **Verrouiller le Flipper** (avec le code PIN s'il y en a un) |
| <kbd>↓</kbd> | Archive | Infos sur l'appareil / écran de debug |
| <kbd>←</kbd> | Application favorite (Left Short), menu Apps par défaut | Application favorite (Left Long) |
| <kbd>→</kbd> | Passport (ou l'application assignée) | Application favorite (Right Long) |
| <kbd>BACK</kbd> | — | Écran d'extinction |

Les applications s'assignent dans **Settings → Desktop → Favorite App - …**. Les détails figurent sur la page
[Bureau](/fr/start/desktop).

::: tip Unleashed
Maintenir <kbd>↑</kbd> sur le bureau verrouille immédiatement l'appareil (avec le code PIN s'il y en a un). Sur le
firmware d'origine, le verrouillage passe par le `Lock Menu`.
:::

Un appui court sur <kbd>↑</kbd> ouvre le Lock Menu :

![Lock Menu : Turn Bluetooth On sélectionné, avec Mute et Dummy Mode en dessous](/screens/desktop/lock_menu.png)

Si un code PIN est défini, le Flipper le demande avant de se déverrouiller. Les flèches saisissent le code,
<kbd>BACK</kbd> l'efface et <kbd>OK</kbd> le valide :

![Enter PIN : quatre chiffres saisis affichés sous forme d'étoiles, une cinquième case vide, l'indication d'effacement et le bouton OK](/screens/desktop/pin_input.png)

Un appui long sur <kbd>↓</kbd> ouvre l'écran d'informations de l'appareil — temps de fonctionnement, révision du
matériel, nom du Flipper, version du firmware et date de build, commit, version de l'API et état du mode Debug. Un
appui long sur <kbd>OK</kbd> y active ou désactive Debug :

![Écran d'informations de l'appareil : Uptime 1h23m45s, matériel 13.F7B9C6 R00, firmware unlshd-080 compilé le 21-11-2026 et D:ON](/screens/desktop/debug.png)

## Retour haptique

**Main Menu → Settings → Input**

| Entrée | Valeurs | Signification |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Courte vibration à chaque événement bouton. Plus la valeur est élevée, plus la vibration est longue |
| Vibro Trigger | `Press`, `Release`, `Both` | Moment où la vibration se déclenche |

## Saisie de texte

Sur le clavier virtuel, déplacez-vous avec les flèches et appuyez sur <kbd>OK</kbd> pour saisir le caractère
sélectionné. Maintenez <kbd>OK</kbd> sur une lettre pour la saisir en majuscule. Sélectionnez la touche `⏎` /
**Save** pour valider. <kbd>BACK</kbd> supprime le dernier caractère ou quitte le clavier.

::: tip Unleashed
La saisie de texte dispose d'un **curseur**, ce qui permet de corriger au milieu du texte. Dans la saisie
hexadécimale (**byte input**, par exemple lors de l'ajout manuel d'une clé), appuyez plusieurs fois sur
<kbd>↑</kbd> jusqu'à faire apparaître le **mini-éditeur de nibble** : il permet de modifier un demi-octet à la fois.
:::
