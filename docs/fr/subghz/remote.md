---
title: Application Sub-GHz Remote
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** transforme le Flipper en télécommande à cinq boutons. Vous associez jusqu'à cinq fichiers `.sub` enregistrés aux touches <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> et <kbd>OK</kbd>, vous donnez un libellé à chacun, puis vous les émettez d'un seul appui, sans parcourir `Sub-GHz → Saved`.

::: tip Unleashed
Sub-GHz Remote est intégrée à Unleashed et se trouve dans le **menu principal** : `Main Menu → Sub-GHz Remote`. Elle a été écrite par @gid9798 et @xMasterX, et son code source réside dans un dépôt séparé, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), inclus dans le firmware comme sous-module. Le firmware d'origine ne l'a pas dans son menu ; pour le firmware officiel, il existe une build distincte dans le catalogue d'applications.
:::

## Quand s'en servir {#when-to-use}

- Vous utilisez quelques signaux en permanence, par exemple un portail, une porte de garage et une barrière, et vous les voulez à un appui.
- Vous pilotez plusieurs appareils (ventilateur, éclairage, sonnette) et vous les voulez sur un seul écran avec des libellés lisibles.

Chaque bouton émet un fichier `.sub` normal : tout ce qui marche depuis `Sub-GHz → Saved → Emulate` marche aussi ici, clés statiques, télécommandes à code tournant créées avec [Add Manually](/fr/subghz/add-manually), enregistrements RAW et BinRAW. Les protocoles que le Flipper sait seulement recevoir ne peuvent pas être associés.

## Le menu {#menu}

L'application ouvre tout de suite le navigateur de fichiers de carte. Appuyez sur <kbd>Back</kbd> pour accéder au menu :

| Entrée | Ce qu'elle fait |
|---|---|
| `Open Map File` | choisir une carte et passer à l'écran de télécommande |
| `Edit Map File` | choisir une carte et l'ouvrir dans l'éditeur |
| `New Map File` | saisir un nom et construire une nouvelle carte |
| `Set Default` | choisir la carte que l'application ouvrira d'elle-même désormais |
| `Clear Default` | oublier cette carte (affiché seulement quand une carte est définie) |

Les cartes sont des fichiers `.txt` dans le dossier `subghz_remote` de la carte SD. Le nom du fichier n'a pas d'importance et vous pouvez en garder autant que vous voulez. Si vous avez un ancien dossier `unirf` hérité des versions précédentes, l'application le déplace vers `subghz_remote` à son premier démarrage.

## Construire une carte sur le Flipper {#builtin-editor}

L'application a un éditeur intégré, un PC n'est donc pas nécessaire.

1. Enregistrez d'abord les signaux voulus avec [Read](/fr/subghz/read), [Read RAW](/fr/subghz/read-raw) ou [Add Manually](/fr/subghz/add-manually).
2. Ouvrez `Main Menu → Sub-GHz Remote`, appuyez sur <kbd>Back</kbd> et choisissez `New Map File`.
3. Saisissez un nom, 25 caractères au maximum. La carte devient `/ext/subghz_remote/<name>.txt`.
4. L'éditeur s'ouvre sur l'emplacement `UP`.

| Touche dans l'éditeur | Ce qu'elle fait |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | se déplacer entre les cinq emplacements : `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — ouvrir le menu de l'emplacement |
| <kbd>→</kbd> | `Save` — passer à l'aperçu |
| <kbd>←</kbd> ou <kbd>Back</kbd> | `Back` |

La barre du haut affiche le nom de l'emplacement et son libellé. En dessous, vous voyez le chemin du fichier associé, ou `Button not set` si l'emplacement est vide, ou `ERR:` suivi de la raison : `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

Le menu d'un emplacement comporte quatre entrées :

- `Edit Label` — le texte affiché pour ce bouton. Jusqu'à 25 caractères, dont environ 16 tiennent sur l'écran de la télécommande. Un libellé vide est accepté, l'application demande d'abord `Empty Label Name / Continue?` ; sans libellé, elle affiche le nom du fichier.
- `Edit File` — un navigateur de fichiers `.sub` qui démarre dans `/ext/subghz`. Si le fichier est inutilisable, une fenêtre `ERROR` indique `Bad frequency`, `Bad modulation` ou `Unsupported protocol`, et l'emplacement garde ce qu'il avait.
- `Button` — quel bouton de la télécommande cet emplacement émet : `Default`, `Up`, `Down`, `Left`, `Right`. Voir [Boutons personnalisés](#custom-buttons).
- `Clear Slot` — vider l'emplacement.

Appuyez sur <kbd>→</kbd> quand vous avez fini. L'aperçu montre la télécommande terminée avec `Back` à gauche et `Save` à droite ; <kbd>→</kbd> ou <kbd>OK</kbd> écrit le fichier et un écran `Saved!` apparaît. Quitter l'éditeur avec des modifications non enregistrées demande d'abord `Changes are not saved / do you want to exit?`.

Laisser un emplacement vide ne pose pas de problème. Une carte avec un seul bouton fonctionne.

## Émettre {#sending}

Choisissez `Open Map File` et prenez votre carte. Cet écran est dessiné de côté, tenez donc le Flipper à la verticale.

- **Maintenez** une touche pour émettre. La ligne correspondante passe en noir et la LED clignote en magenta.
- Relâchez-la : le protocole envoie les répétitions qui lui restent, puis s'arrête. Un fichier RAW se joue jusqu'au bout de l'enregistrement et recommence si vous maintenez toujours la touche.
- Sous les cinq lignes, l'application affiche ce qu'elle émet : nom du protocole, fréquence et modulation, `Key:` (seulement pour les clés de 32 bits ou moins), `Sn:` ou `Fix:`, `Cnt:`, `MF:`. Cinq lignes au maximum tiennent à l'écran.
- L'icône en haut à gauche indique si la radio interne ou un [module externe](/fr/subghz/external-cc1101) est utilisé.
- <kbd>Back</kbd> arrête une émission en cours. Appuyez de nouveau pour quitter l'application.

Un emplacement dont le fichier n'a pas pu être chargé affiche `[X] Can't open file` ou `[X] Error in .sub file` à la place de son libellé. Les emplacements vides n'affichent rien, et les presser fait clignoter la LED en rouge.

## Boutons personnalisés {#custom-buttons}

Une télécommande à code tournant a plusieurs boutons, et un fichier `.sub` en stocke un seul. `Button`, dans le menu de l'emplacement, choisit lequel cet emplacement émet. `Default` garde le bouton du fichier ; `Up`, `Down`, `Left` et `Right` émettent les autres boutons de la même télécommande, ceux que ces touches vous donnent dans `Sub-GHz → Saved → Emulate`. L'éditeur ajoute alors `(Btn. Up)` après le chemin.

Le compteur avance d'un cran par appui, et l'application remet le bouton d'origine en place à la fin de l'émission.

C'est ainsi qu'on donne sa propre touche à un bouton caché ou de programmation. Quelle flèche correspond à quel bouton dépend du protocole, voir [Flipper comme nouvelle télécommande](/fr/subghz/remote-prog).

## Le fichier de carte {#map-file}

L'éditeur écrit un fichier texte simple au format Flipper :

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` sont les chemins complets des fichiers `.sub` associés à chaque direction de la croix.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` sont les textes affichés à l'écran pour ces boutons.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` sont le bouton personnalisé, en hexadécimal : `00` par défaut, `01` haut, `02` bas, `03` gauche, `04` droite. L'éditeur omet la ligne quand l'emplacement utilise `Default`.

Vous pouvez aussi écrire une carte sur un PC. Dans ce cas :

- Séparez la clé de la valeur par deux-points et **une** espace, exactement comme ci-dessus.
- L'ordre des lignes n'a pas d'importance, l'application cherche chaque clé par son nom. Une clé absente compte comme vide.
- Le **nom de fichier** d'un `.sub` doit être en ASCII imprimable et ne doit pas contenir `\ < > * | " : ?`. Un nom en cyrillique ou un emoji empêche l'emplacement de se charger.
- Tenez-vous à environ 16 caractères pour les libellés. Au-delà, ils sont coupés sur l'écran étroit de la télécommande.

L'éditeur intégré ne peut pas produire une carte cassée : préférez-le.

## Ouvrir une carte au démarrage {#default-map}

`Set Default` enregistre la carte choisie dans `/ext/subghz_remote/.config`. À partir de là, l'application va droit à l'écran de télécommande à son ouverture, et <kbd>Back</kbd> vous ramène au menu. `Clear Default` supprime ce fichier.

L'application accepte également un chemin de fichier de carte comme argument de lancement : une autre application peut donc ouvrir directement une télécommande précise.

## Si ça ne marche pas {#troubleshooting}

- **`[X] Can't open file`** : le fichier `.sub` visé par cet emplacement a été déplacé, renommé ou supprimé. Reprenez-le avec `Edit File`, ou corrigez le chemin dans la carte.
- **`[X] Error in .sub file`** : le fichier se charge mais ne peut pas être émis. L'éditeur en dit la raison : `Bad frequency` (la fréquence du signal n'est pas prise en charge par la radio sélectionnée, voir [Fréquences](/fr/subghz/frequencies)), `Bad modulation`, ou `Unsupported protocol` (le protocole est en réception seule).
- **Un bouton ne fait rien** et la LED clignote en rouge : cet emplacement est vide ou son fichier n'a pas pu être chargé.
- **Une télécommande à code tournant a cessé de fonctionner** après que vous avez utilisé le Flipper et l'originale : c'est un conflit de compteur, pas un bug de l'application. Voir [Codes tournants](/fr/subghz/rolling-codes) et refaites une télécommande avec [Flipper comme nouvelle télécommande](/fr/subghz/remote-prog).
- **Avertissement `Not official FW` au démarrage** : vous avez installé la build du catalogue, prévue pour le firmware officiel. Utilisez la Sub-GHz Remote déjà présente dans le menu principal d'Unleashed.
- D'anciens guides mentionnent un écran `Config is incorrect. Please configure map.`. L'application actuelle ne l'affiche pas ; elle signale les boutons cassés sur l'écran de télécommande.

## Pages liées {#related}

- [Lire des signaux](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw) · [Add Manually](/fr/subghz/add-manually)
- [Flipper comme nouvelle télécommande](/fr/subghz/remote-prog)
- [Format de fichier .sub](/fr/subghz/file-format)
