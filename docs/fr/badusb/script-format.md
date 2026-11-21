---
title: Format des scripts
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Format des scripts Bad USB (DuckyScript)

Bad USB exécute des scripts en texte brut dans une syntaxe **DuckyScript étendue**. Les scripts USB Rubber Ducky 1.0
classiques fonctionnent tels quels ; par-dessus, le Flipper ajoute une identité USB/BLE personnalisée, la saisie
`ALT`+pavé numérique, `SYSRQ`, les touches multimédia, le contrôle de la souris, l'attente d'un appui sur un bouton
et bien d'autres. Cette référence a été vérifiée contre la table des commandes du firmware
(`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## Règles du fichier

- Texte brut, extension **`.txt`**, aucune compilation. Fins de ligne `\n` ou `\r\n`.
- Une commande par ligne. Les lignes vides sont ignorées ; les lignes peuvent être indentées avec des espaces ou des
  tabulations.
- Les commandes sont **en MAJUSCULES et sensibles à la casse** : `STRING`, pas `string`.
- La commande et son argument sont séparés par une seule espace.
- Les commentaires sont des lignes entières commençant par `REM`. Il n'y a pas de commentaire en fin de ligne.
- Le texte saisi (`STRING`, `STRINGLN`) doit être **ASCII**. Les caractères non ASCII arrêtent le script avec
  *« Native .kl supports ASCII, not UTF-8 »*.
- En cas d'erreur, le script s'arrête et l'écran affiche *ERROR:*, le numéro de ligne et la cause.

## Aide-mémoire

| Commande | Argument | Effet |
|---|---|---|
| `REM` | texte | Commentaire, ignoré. |
| `ID` | `VID:PID [Manufacturer:Product]` | Identité USB, **première ligne uniquement**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Identité Bluetooth, **première ligne uniquement**. |
| `DELAY` | ms | Attendre une fois. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Attendre avant chacune des commandes suivantes. |
| `STRING` | texte | Taper du texte. |
| `STRINGLN` | texte | Taper du texte puis appuyer sur Entrée. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Délai entre les frappes pour le **prochain** `STRING` seulement. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Délai entre les frappes pour **tous** les `STRING`. |
| `REPEAT` | n | Répéter n fois de plus la commande précédente. |
| `DUCKY_LANG` | nom de disposition | Changer la disposition de clavier pour la suite du script (Unleashed). |
| `HOLD` | touche / bouton de souris | Appuyer et maintenir. |
| `RELEASE` | touche / bouton de souris | Relâcher une touche maintenue. |
| `ALTCHAR` | code | Taper un caractère avec `ALT`+pavé numérique. |
| `ALTSTRING` / `ALTCODE` | texte | Taper du texte avec `ALT`+pavé numérique. |
| `SYSRQ` | caractère | Combinaison Magic SysRq. |
| `MEDIA` | touche multimédia | Touche de contrôle grand public (volume, lecture…). |
| `GLOBE` | touche | Fn/Globe + touche (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | aucun | Pause jusqu'à l'appui sur <kbd>OK</kbd> sur le Flipper. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | aucun | Clics de souris. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Déplacer la souris. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Faire défiler la molette. |
| combinaison de touches | par ex. `CTRL-ALT DELETE` | Appuyer puis relâcher les touches ensemble. |

## Commentaires

```text
REM This line is ignored
```

## Délais

| Commande | Paramètre | Remarques |
|---|---|---|
| `DELAY` | ms | Pause unique. |
| `DEFAULT_DELAY` | ms | Ajouté avant chaque commande suivante. Identique à `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Les délais sont votre principal outil de fiabilité : l'hôte a besoin de temps pour ouvrir des fenêtres, ajoutez donc
un `DELAY` après `GUI r`, après `ENTER` dans un lanceur, etc. Les longs délais sont affichés à l'écran sous la forme
`Delay Ns`.

## Saisir du texte

| Commande | Paramètre | Remarques |
|---|---|---|
| `STRING` | texte | Tape le texte exactement, en utilisant la disposition de clavier active. |
| `STRINGLN` | texte | Idem, puis appuie sur Entrée. |
| `STRING_DELAY` | ms | Pause entre les frappes pour le prochain `STRING`/`STRINGLN` seulement. Identique à `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pause entre les frappes pour toutes les chaînes suivantes. Identique à `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Sans délai de frappe, le texte est envoyé le plus vite possible ; certains hôtes ou applications perdent alors des
caractères. Les scripts de démonstration intégrés utilisent `DEFAULT_STRING_DELAY 10`.

::: warning La disposition compte
`STRING` envoie des *positions de touches*, traduites via la [disposition de clavier](/fr/badusb/layouts)
sélectionnée. Si l'hôte utilise une autre disposition que l'application, vous obtenez de mauvais caractères. Le
texte doit être en ASCII.
:::

## Touches et combinaisons

Une ligne qui n'est pas une commande est interprétée comme un appui de touche : zéro ou plusieurs **modificateurs**,
puis une **touche**. Les modificateurs sont séparés par des espaces ou des traits d'union. La touche est un nom de
touche spéciale ou un caractère unique.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modificateurs

| Nom | Remarques |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Touche Windows / Command / Super |

### Touches spéciales

| Nom | Remarques |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Flèches |
| `ENTER` | |
| `DELETE` | Suppression vers l'avant |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Attn |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Touche de menu contextuel |
| `F1` … `F24` | Touches de fonction (le firmware connaît aussi F13-F24) |

## Répétition

```text
DOWN
REPEAT 9
```

`REPEAT n` relance la **commande précédente** n fois de plus (dans l'exemple, la flèche Bas est pressée 10 fois).
`n` doit être ≥ 1.

## Maintenir et relâcher

| Commande | Paramètre | Remarques |
|---|---|---|
| `HOLD` | touche spéciale, modificateur, caractère unique ou bouton de souris | Appuie et maintient jusqu'au `RELEASE`. |
| `RELEASE` | le même | Relâche cette touche. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Au maximum **6** touches ou boutons peuvent être maintenus en même temps (la taille du rapport de touches HID) ;
au-delà, on obtient *« Too many keys are held »*. Un `RELEASE` alors que rien n'est maintenu donne
*« No keys are held »*. La documentation officielle indique 5 ; la vérification du firmware en autorise 6.

## Saisie ALT + pavé numérique

Sous Windows (et dans certaines configurations Linux), n'importe quel caractère peut être tapé en maintenant `ALT`
et en saisissant son code sur le pavé numérique. Cela **ne dépend pas de la disposition de clavier**, ce qui est
pratique sur des machines inconnues.

| Commande | Paramètre | Remarques |
|---|---|---|
| `ALTCHAR` | code de caractère | Tape un caractère : maintient ALT et saisit les chiffres sur le pavé numérique. |
| `ALTSTRING` | texte | Tape chaque caractère ASCII imprimable (32-126) du texte via son code ALT. |
| `ALTCODE` | texte | Identique à `ALTSTRING` (nom utilisé par certaines implémentations de DuckyScript). |

Le verrouillage numérique est activé automatiquement avant la saisie ALT.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Envoie `ALT`+`PRINTSCREEN`+touche, la combinaison [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key) de
Linux. Prudence : certaines touches SysRq redémarrent ou arrêtent le système immédiatement.

## Touches multimédia

`MEDIA <key>` appuie sur une touche de contrôle grand public :

| Touche | Remarques |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | Système |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Navigation navigateur / application |
| `SNAPSHOT` | Prendre une photo dans une application appareil photo |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Lecture |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Volume |
| `FN` | Touche Fn/Globe des claviers Mac |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Luminosité de l'écran |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Touche Fn / Globe (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` maintient Fn/Globe, appuie sur la touche, puis relâche les deux (touche spéciale ou caractère unique).

## Attendre un appui sur un bouton

```text
WAIT_FOR_BUTTON_PRESS
```

Le script se met en pause indéfiniment ; le Flipper affiche **Press to continue**. Appuyez sur <kbd>OK</kbd> pour
continuer. Pratique pour se synchroniser avec une action manuelle (se connecter, déverrouiller l'écran…).

## Souris

| Commande | Paramètre | Remarques |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | aucun | Clic gauche |
| `RIGHTCLICK` / `RIGHT_CLICK` | aucun | Clic droit |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | aucun | Clic du milieu (molette) |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (entiers) | Déplacement relatif ; valeur négative = vers la gauche / le haut |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (entier) | Molette de défilement ; le signe donne le sens |

Les boutons de souris fonctionnent avec `HOLD`/`RELEASE`, par exemple pour un glisser-déposer :

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## Identité du périphérique {#device-id}

Vous pouvez définir l'identité que le Flipper présente à l'hôte. La commande doit se trouver sur la **toute première
ligne** ; elle est appliquée à l'ouverture du script, avant son exécution, et l'application **bascule dans le mode de
connexion correspondant** (vous pouvez toujours revenir en arrière manuellement). Sur les autres lignes, ces
commandes sont ignorées.

| Commande | Paramètres | Exemple | Mode |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | identique à `BLE_ID` |

- `ID` : les VID et PID (en hexadécimal) sont obligatoires ; les chaînes de fabricant et de produit sont
  facultatives (31 caractères maximum chacune).
- `BLE_ID` / `BT_ID` : la MAC de 6 octets et le nom du périphérique sont tous deux obligatoires.

## Disposition de clavier par script : `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` est une nouveauté d'Unleashed (PR #1224 par @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Charge `/ext/badusb/assets/layouts/<name>.kl` et l'utilise à partir de cette ligne, au lieu de la disposition
  globale définie dans `Config`. Alias courts : `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- Le nom peut contenir des lettres, des chiffres, `-` et `_`, et rien ne doit le suivre sur la ligne.
- Un fichier manquant ou un nom invalide **n'arrête pas le script** : il retombe silencieusement sur la disposition
  intégrée `en-US`.
- Chaque nouvelle exécution repart de la disposition globale, placez donc `DUCKY_LANG` près du début du script.

La liste des noms de dispositions se trouve sur [Dispositions de clavier](/fr/badusb/layouts).

## Voir aussi

- [Exemples](/fr/badusb/examples)
- [Dispositions de clavier](/fr/badusb/layouts)
- [Utiliser le Bad USB](/fr/badusb/usage)
