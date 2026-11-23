---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** modifie un signal déjà enregistré : son mode de compteur, son compteur tournant actuel et son
code de bouton. C'est un petit écran pour utilisateurs avertis, masqué tant que le mode Debug est désactivé, et
l'essentiel ne fonctionne que sur la poignée de protocoles qui prennent en charge les
[modes de compteur](/fr/subghz/counter-mode).

## Où il se trouve {#where}

C'est une entrée du menu d'un signal enregistré, pas une entrée du menu principal Sub-GHz. Ouvrez un fichier depuis
`Sub-GHz → Saved` (ou depuis l'[Archive](/fr/apps/archive)) et le menu est le suivant :

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Le faire apparaître {#enable}

`Signal Settings` n'est ajouté à ce menu que lorsque **Debug** est activé. Avec Debug désactivé, l'entrée est absente.

- Méthode rapide : maintenez <kbd>↓</kbd> sur le bureau, puis maintenez <kbd>OK</kbd> sur l'écran d'information
  ([Bureau → Écran d'informations de l'appareil](/fr/start/desktop#info-screen)).
- Ou `Settings → System → Debug` = `ON` ([Paramètres](/fr/start/settings)).

## Les trois entrées {#items}

![Signal Settings : Counter Mode, Edit Counter et Edit Button](/screens/subghz/signal_settings.png)

| Entrée | Rôle |
|---|---|
| `Counter Mode` | <kbd>←</kbd>/<kbd>→</kbd> choisissent `System` (mode 0) ou `Mode 1` … jusqu'à la limite du protocole. Le choix est écrit aussitôt dans le fichier `.sub` sous forme d'une ligne `CounterMode:` et le fichier est rechargé ; rien n'est émis |
| `Edit Counter` | <kbd>OK</kbd> ouvre une saisie hexadécimale du compteur courant, intitulée `Enter <N>-bits counter in HEX` avec la longueur de compteur du protocole : 4 chiffres hexadécimaux (2 octets) jusqu'à 16 bits, 8 chiffres (4 octets) au-delà |
| `Edit Button` | <kbd>OK</kbd> ouvre une saisie hexadécimale du code de bouton, intitulée `Enter <N>-bits button in HEX` — toujours un octet, 2 chiffres hexadécimaux |

La valeur que contient actuellement chaque entrée est affichée sur sa ligne, en hexadécimal. Ce que les modes de
compteur font eux-mêmes au compteur, et comment en définir un en modifiant plutôt le fichier sur un ordinateur, se
trouve sur [Modes de compteur](/fr/subghz/counter-mode#modes-by-protocol).

::: warning Valider une modification du compteur ou du bouton déclenche une émission
`Edit Counter` et `Edit Button` écrivent les nouvelles valeurs dans le fichier en utilisant le mécanisme d'émission du signal : le firmware démarre un
envoi avec la nouvelle valeur et l'arrête aussitôt, et le fichier est réécrit à l'arrêt de cet envoi. La radio émet
pendant un instant : faites-le donc loin du récepteur que vous ne voulez pas actionner.

Le compteur que vous saisissez est enregistré exactement tel que saisi — pour cette seule réécriture, le mode de
compteur et le pas [Counter Incr.](/fr/subghz/settings) sont ignorés. Une modification du bouton met plutôt ce pas à
0 pour la réécriture : changer le bouton laisse donc le compteur là où il était.

Si l'envoi est refusé — une fréquence sur laquelle ce firmware n'émet pas — le fichier n'est pas écrit du tout.
:::

## Protocoles avec modes de compteur {#protocols}

`Counter Mode` est déverrouillé pour cinq protocoles. `System` est le mode 0, le mode normal :

| Protocole | Choix |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

La correspondance se fait sur la ligne `Protocol:` du fichier. Sur tous les autres protocoles, l'entrée est
verrouillée.

## Entrées verrouillées {#locked}

Une entrée verrouillée ne peut être ni ouverte ni modifiée ; appuyer dessus affiche
`Not available for this protocol !`

- `Counter Mode` — le protocole du fichier ne fait pas partie des cinq ci-dessus.
- `Edit Counter` — le protocole n'a pas de compteur. Cela peut aussi dépendre du constructeur : en KeeLoq, l'entrée
  est verrouillée pour `AN-Motors`, qui n'a qu'un pseudo-compteur, et pour `Unknown`.
- `Edit Button` — le protocole n'a pas de code de bouton dans sa trame.

`Edit Button` est aussi déverrouillé sur les protocoles fixes qui portent un code de bouton — Princeton, Dooya,
GangQi, Hollarm, Nord ICE, Proteco et Roger — et il y fonctionne exactement comme sur un signal à code tournant.

## Voir aussi {#related}

- [Modes de compteur](/fr/subghz/counter-mode) — ce que fait chaque mode, et la ligne `CounterMode:` du fichier
- [Codes tournants](/fr/subghz/rolling-codes) · [Format de fichier .sub](/fr/subghz/file-format)
- [Bureau](/fr/start/desktop#info-screen) — le raccourci Debug · [Paramètres](/fr/start/settings) — Debug dans les
  menus
