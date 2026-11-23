---
title: Read (lecture)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Read (lecture)

**Read** écoute une fréquence (ou en balaie plusieurs), **décode** les signaux des protocoles connus et les affiche
sous forme de liste. Un signal décodé peut être enregistré dans un fichier-clé puis réémis. C'est le principal moyen
de copier une télécommande à **code fixe (statique)** — portails, barrières, sonnettes, prises télécommandées — et
d'identifier le protocole utilisé par une télécommande.

Pour les télécommandes que Read ne reconnaît pas, utilisez [Read RAW](/fr/subghz/read-raw). Pour les télécommandes à
code tournant, lisez [Codes tournants](/fr/subghz/rolling-codes) **avant** d'émettre quoi que ce soit.

::: tip Unleashed
Par rapport au firmware d'origine, Unleashed ajoute : des dizaines de protocoles supplémentaires
([liste complète](/fr/subghz/supported-systems)), l'enregistrement et l'émission de nombreux protocoles à **code
tournant**, des **boutons personnalisés** sur les touches fléchées lors de l'émission, le hopping avec un seuil
RSSI, les filtres `Ignore …`, `Delete old signals when memory is full`, le **maintien de <kbd>→</kbd> pour
supprimer** un signal de la liste, l'heure de réception affichée pour chaque signal, et la mémorisation des
derniers réglages.
:::

## Lire une télécommande

1. Trouvez d'abord la fréquence si vous ne la connaissez pas :
   [Frequency Analyzer](/fr/subghz/frequency-analyzer) (un appui long sur <kbd>OK</kbd> y ouvre directement Read sur
   la fréquence trouvée).
2. Ouvrez `Main Menu → Sub-GHz → Read`. L'écran affiche `Fixed scan...` (ou `Hopper scan...` si le hopping est
   activé), et la fréquence et la modulation actuelles en bas.

   ![Écran Read en attente d'un signal : Fixed scan sur 433.92 MHz, AM650](/screens/subghz/read.png)

3. Tenez la télécommande près du flanc gauche du Flipper et appuyez sur son bouton pendant 1–2 secondes.
4. Le signal décodé apparaît dans la liste sous la forme `nom du protocole` + heure de réception. Le compteur en bas
   indique combien de signaux contient la liste.

   ![Liste Read avec trois signaux reçus : Princeton, CAME 12bit et KL: DoorHan](/screens/subghz/read_list.png)

5. Sélectionnez-le avec <kbd>↑</kbd> <kbd>↓</kbd> et appuyez sur <kbd>OK</kbd> pour voir les détails (clé, nombre de
   bits, numéro de série, bouton, compteur, constructeur pour KeeLoq, etc.).

   ![Détails du signal : Princeton 24bit avec la clé, le numéro de série et le bouton, boutons Send et Save](/screens/subghz/signal_info.png)

6. Appuyez sur <kbd>→</kbd> **Save**, saisissez un nom et validez. Le fichier est écrit dans `/ext/subghz/`.
7. Ou appuyez sur <kbd>OK</kbd> **Send** pour l'émettre immédiatement.

Les signaux enregistrés se trouvent dans `Main Menu → Sub-GHz → Saved` (voir [plus bas](#saved-signals)).

## Boutons sur l'écran Read

| Bouton | Action |
|---|---|
| <kbd>←</kbd> | **Config** — réglages du récepteur |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Se déplacer dans la liste des signaux reçus |
| <kbd>OK</kbd> | Ouvrir le signal sélectionné |
| maintien de <kbd>→</kbd> | Supprimer le signal sélectionné de la liste |
| <kbd>Back</kbd> | Quitter Read. S'il reste des signaux non enregistrés, vous obtenez **Exit to Sub-GHz Menu?** — `Exit` / `Stay` |

Selon la taille des données reçues, la liste peut contenir jusqu'à 128 signaux.

## Config

Appuyez sur <kbd>←</kbd> **Config** depuis l'écran Read :

![Menu Config de Read : Frequency, Modulation, Hopping et Bin RAW](/screens/subghz/read_config.png)

| Entrée | Valeurs | Rôle |
|---|---|---|
| `Frequency` | liste issue de [Fréquences](/fr/subghz/frequencies) | Fréquence de réception fixe. Affiche ` -----` quand le hopping est activé |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + presets personnalisés | Preset de démodulation. `AM650` convient à la plupart des télécommandes |
| `Hopping` / `Hopping RSSI` | `OFF`, `-90dBm` … `-40dBm` | Parcourt la liste de hopping (315, 390, 430.5, 433.92, 434.42, 868.35 MHz). La valeur est le niveau RSSI qui arrête le balayage sur une fréquence |
| `Bin RAW` | `OFF` / `ON` | Collecter aussi les signaux fixes inconnus en **BinRAW** (motif répétitif avec débit binaire reconstitué). Maintenez le bouton de la télécommande un peu plus longtemps pour accumuler assez de données |
| `Ignore ReversRB2` | `OFF` / `ON` | Masquer les signaux Revers RB-2(M) |
| `Ignore Alarms` | `OFF` / `ON` | Masquer les protocoles d'alarmes de vélo et de moto (Hollarm, GangQi) |
| `Ignore Sensors` | `OFF` / `ON` | Masquer les capteurs et le bavardage similaire : Magellan, Honeywell, sonnettes Honeywell WDB et Legrand, Doorbell32, KeyFinder/KeyFinder2, Feron |
| `Ignore Princeton` | `OFF` / `ON` | Masquer Princeton (PT2262 et clones) — utile là où des télécommandes bon marché saturent l'air |
| `Ignore Nice Flor-S / Nice One` | `OFF` / `ON` | Masquer Nice Flor-S / Nice One |
| `Delete old signals when memory is full` | `OFF` / `ON` | Quand la liste est pleine, supprimer les signaux les plus anciens au lieu de s'arrêter. Le compteur affiche alors `!` |
| `Sound` | `OFF` / `ON` | Diffuser dans le haut-parleur tout ce que la radio reçoit |
| `Reset to default` | — | Retour à 433.92 MHz AM650, hopping désactivé, tous les filtres désactivés, Bin RAW désactivé, puissance d'émission `Preset` |
| `Lock Keyboard` | — | Verrouille les boutons pendant le balayage (dans une poche). **Déverrouillage : appuyer trois fois sur <kbd>Back</kbd>** |

Tous les réglages de Read sont enregistrés et restaurés au prochain lancement de l'application.

::: tip Quelle valeur de hopping choisir
Avec `Hopping` activé, le récepteur ne reste sur une fréquence que si le signal dépasse le niveau choisi. `-90dBm`
est le plus sensible ; augmentez-le si le bruit arrête sans cesse le balayage. Pour une réception fiable, préférez
une **fréquence fixe** trouvée avec l'analyseur : les signaux émis pendant un changement de fréquence sont perdus.
:::

## Envoyer un signal

Ouvrez le signal (depuis la liste Read ou depuis `Saved → <fichier> → Emulate`). L'écran d'émission affiche les
données de la clé, la fréquence, la modulation et `R: Int` / `R: Ext` (quelle radio va émettre).

- **Appuyez sur** <kbd>OK</kbd> (**Send**) — un appui simple envoie un paquet de signal complet (en général avec 1 à 3
  répétitions pour la fiabilité). **Maintenir** le bouton enfoncé répète l'émission en continu jusqu'au relâchement
  (utile à distance ou en présence d'interférences). Pour les protocoles à code tournant, maintenir le bouton
  n'incrémente **pas** le compteur (voir aussi [Mode compteur](/fr/subghz/counter-mode)) — le signal est réémis avec
  le même compteur tant que le bouton n'est pas relâché puis pressé à nouveau.
- <kbd>Back</kbd> — quitter.

### Boutons personnalisés (Unleashed)

::: tip Unleashed
Pour de nombreux protocoles, les touches fléchées envoient **la même télécommande avec un autre code de bouton** :
un seul fichier enregistré se comporte alors comme la télécommande complète. Sont pris en charge, entre autres :
KeeLoq, Alutech AT-4N, Nice Flor-S, Somfy Telis/Keytis, Security+ 2.0, CAME Atomo, FAAC SLH, BelKorn, Beninca ARC,
Ditec GOL4, Jarolift, KingGates Stylo 4k, V2 Phoenix, Prastel, Roger, Nord ICE, Princeton, Proteco, Dooya, Hay21,
GangQi, Hollarm. Pendant qu'une flèche est maintenue, le code de bouton envoyé s'affiche sur le bord droit de
l'écran. La correspondance entre flèche et bouton dépend du protocole — voir
[Codes tournants](/fr/subghz/rolling-codes) et
[Programmer une nouvelle télécommande](/fr/subghz/remote-prog).
:::

## Signaux enregistrés {#saved-signals}

`Main Menu → Sub-GHz → Saved` liste les fichiers de `/ext/subghz/`. Choisissez-en un et vous obtenez :

- `Emulate` — ouvrir l'écran d'émission ;
- `Rename` — renommer ;
- `Delete` — supprimer ;
- `Signal Settings` — **uniquement en mode Debug** (`Settings → System → Debug`) : modifier `Counter Mode`,
  `Edit Counter`, `Edit Button` d'un fichier à code tournant. Voir [Modes de compteur](/fr/subghz/counter-mode).

Les fichiers RAW s'ouvrent dans l'écran Read RAW à la place — voir [Read RAW](/fr/subghz/read-raw#playback).

Les noms de fichiers sont générés automatiquement (date et heure), sauf si `Protocol Names` est activé dans
[Radio Settings](/fr/subghz/settings) — dans ce cas le nom du protocole est placé devant l'horodatage.

## Codes fixes et codes tournants

- **Code fixe** (Princeton, CAME 12/24 bit, Nice Flo, Marantec, Roger, Gate TX…) : chaque appui envoie le même
  code. Une copie enregistrée fonctionne indéfiniment aux côtés de l'originale.
- **Code tournant (dynamique)** (KeeLoq, Nice Flor-S, CAME Atomo, FAAC SLH, Somfy, Security+…) : chaque appui
  transporte une nouvelle valeur de compteur. Unleashed sait en enregistrer et en émettre beaucoup, **mais émettre
  une copie désynchronise la télécommande d'origine**. Lisez [Codes tournants](/fr/subghz/rolling-codes) et
  préférez [Add Manually](/fr/subghz/add-manually) pour créer une *nouvelle* télécommande.

::: danger Télécommandes de voiture
N'expérimentez pas avec la clé de votre voiture. Rejouer une télécommande de voiture (Read ou Read RAW) peut
désynchroniser ou blacklister la clé d'origine, et un nouvel appairage nécessite souvent l'outillage du
concessionnaire. N'utilisez le Flipper qu'avec votre propre matériel et pour des recherches licites.
:::

## Dépannage

- **Rien n'apparaît** — mauvaise fréquence ou mauvaise modulation. Utilisez l'analyseur et essayez différentes
  modulations (`AM650`/`FM238`/`FM476`/`FM12K`). Vérifiez qu'un filtre `Ignore …` ne masque pas le protocole.
- **Signal reçu mais non décodé** — le protocole est inconnu : activez `Bin RAW` (télécommandes à code fixe) ou
  enregistrez avec [Read RAW](/fr/subghz/read-raw). Essayez aussi l'application
  [Remote Analyzer](/fr/subghz/remote-analyzer).
- **KeeLoq affiche un constructeur `Unknown`** — la clé constructeur n'est pas dans la base, ou la télécommande a
  besoin d'un seed (BFT, Erreka, FAAC SLH). Voir [KeeLoq](/fr/subghz/keeloq) et
  [Seed Capturer](/fr/subghz/seed-capturer).
- **Pas de bouton `Send`** — le protocole est en décodage seul (par exemple iDo), ou il s'agit d'un paquet
  Nice O-Code sans code installateur (utilisez l'application [Nice O-Code](/fr/subghz/nice-o-code)).
- **La liste se remplit de bruit** — activez les options `Ignore` pertinentes ou
  `Delete old signals when memory is full`.

## Voir aussi

- [Read RAW](/fr/subghz/read-raw) · [Frequency Analyzer](/fr/subghz/frequency-analyzer) · [Systèmes pris en charge](/fr/subghz/supported-systems)
- [Codes tournants](/fr/subghz/rolling-codes) · [Add Manually](/fr/subghz/add-manually) · [Radio Settings](/fr/subghz/settings) · [Formats de fichiers](/fr/subghz/file-format)
