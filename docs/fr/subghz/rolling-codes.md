---
title: Codes tournants
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Codes tournants

Les télécommandes Sub-GHz se répartissent en deux familles :

- **Code statique (fixe)** — chaque appui émet exactement le même paquet (Princeton, CAME 12/24 bit, Nice Flo,
  Marantec, Roger, Gate TX…). Une copie est identique à l'originale ; les deux continuent de fonctionner
  indéfiniment, dans n'importe quel ordre. Il suffit de faire un [Read](/fr/subghz/read) et d'enregistrer.
- **Code tournant (dynamique)** — chaque appui émet un nouveau paquet construit à partir d'un **compteur** qui
  augmente de un à chaque appui (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+, Alutech AT-4N…). Le
  compteur est généralement chiffré, de sorte que le code suivant ne peut être calculé que si le firmware connaît la
  clé du protocole.

::: tip Unleashed
Unleashed sait décoder, enregistrer **et émettre** de nombreux protocoles à code tournant, créer de nouvelles
télécommandes pour ceux-ci avec [Add Manually](/fr/subghz/add-manually), émettre les autres boutons de la
télécommande avec les touches fléchées ([boutons personnalisés](#custom-buttons)) et régler l'incrément du compteur
([Counter Incr.](#counter-increment), [Modes de compteur](/fr/subghz/counter-mode)). Le firmware d'origine décode la
plupart d'entre eux mais ne les émet pas.
:::

## Comment le récepteur contrôle le compteur

Le récepteur mémorise le dernier compteur qu'il a accepté **pour chaque télécommande** (une valeur par télécommande,
pas par bouton) :

- compteur **égal au suivant attendu / dans la fenêtre avant** → accepté, le portail s'ouvre ;
- compteur **loin en avant** → de nombreux récepteurs se resynchronisent : le premier appui est mémorisé, l'appui
  consécutif suivant fonctionne ;
- compteur **en retard** sur la valeur mémorisée → ignoré. Certains récepteurs désapparient une télécommande après
  plusieurs codes « anciens ».

## Le conflit de compteur

*Pourquoi ne peut-on pas simplement capturer sa propre télécommande à code tournant dans Read et l'utiliser depuis le
Flipper ?*
(adapté de [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Imaginez :

1. Vous appuyez sur la télécommande d'origine — elle émet le compteur `0002`.
2. Vous avez enregistré ce signal sur le Flipper ; quand vous l'émettez, le Flipper envoie `0003`.
3. Le récepteur pense que vous avez simplement réappuyé sur l'originale, et il ouvre.
4. Mais la télécommande d'origine est toujours à `0002` ; son prochain appui sera `0003` — une valeur que le
   récepteur a déjà vue, donc **il n'ouvre pas**.

Pas de panique — la télécommande n'est pas désappariée. Appuyez à nouveau : `0004` dépasse le Flipper et l'originale
fonctionne de nouveau. Mais ces « courses » peuvent écarter les compteurs de plus de 100 appuis, et l'originale ne
peut alors plus être récupérée sans la réapparier au récepteur.

Les solutions :

- **La meilleure : créer une nouvelle télécommande** sur le Flipper (`Sub-GHz → Add Manually`) et l'enregistrer dans
  le récepteur. Elle a son propre numéro de série et son propre compteur, et n'entre jamais en conflit avec les
  originales. Voir [programmation d'une télécommande](/fr/subghz/remote-prog).
- Décidez laquelle vous utiliserez — le Flipper **ou** l'originale — et n'utilisez que celle-là.
- Utilisez les deux, mais ne laissez jamais les compteurs s'écarter beaucoup (appuyez plusieurs fois sur celle qui
  est en retard).
- Expérimental : des [modes de compteur](/fr/subghz/counter-mode) spéciaux permettent, sur certains récepteurs, à un
  clone et à l'originale de coexister.

::: danger Voitures
Ne clonez pas la clé d'une voiture. La rejouer (même via Read RAW) peut désynchroniser la clé ou la faire mettre sur
liste noire, et la réapparier nécessite souvent les outils de diagnostic du concessionnaire.
:::

## Boutons personnalisés {#custom-buttons}

Lorsqu'un fichier à code tournant pris en charge (ou certains fichiers statiques) est ouvert dans `Emulate` :

- <kbd>OK</kbd> (`Send`) émet le bouton qui a été enregistré / généré ;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> émettent **d'autres codes de boutons** de la même
  télécommande, avec un compteur correctement incrémenté, tant qu'elles sont maintenues. Le code du bouton d'origine
  est affiché comme un petit chiffre hexadécimal à droite de l'écran pendant l'utilisation d'une flèche.

L'association entre flèche et bouton dépend du protocole ; les boutons cachés / de programmation (par exemple `0xF`
sur BFT Mitto, `Prog` sur Somfy) sont également accessibles de cette manière — le tableau complet se trouve dans
[programmation d'une télécommande](/fr/subghz/remote-prog) (référence des boutons cachés).

Protocoles avec boutons personnalisés dans le firmware actuel (le nombre = combien de codes supplémentaires les
flèches peuvent émettre) :

| Protocole | Extra | Protocole | Extra |
|---|---|---|---|
| KeeLoq (tous les constructeurs `KL:`) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (programmation) |
| Somfy Keytis | 1 (`Prog`) | | |

## Incrément du compteur {#counter-increment}

`Sub-GHz → Radio Settings → Counter Incr.` définit de combien le compteur augmente à chaque émission : `+1` (par
défaut), `+2`, `+3`. Avec le **mode Debug** activé (`Settings → System → Debug`), la liste s'étend à `+4`, `+5`,
`+10`, `+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50` — des outils de développement de protocoles ; ne les utilisez pas
sur une installation réelle. Voir [Réglages](/fr/subghz/settings).

## Enregistrer une nouvelle télécommande dans le récepteur

La façon normale et sans conflit d'utiliser le Flipper avec un portail à code tournant :

1. Lisez votre télécommande d'origine (`Sub-GHz → Read`) pour connaître le protocole, la fréquence et la modulation.
2. `Sub-GHz → Add Manually` → votre système → la même bande → enregistrer.
3. Mettez le récepteur en mode apprentissage (bouton sur la carte, ou depuis une télécommande fonctionnelle — le
   Flipper émet le bouton « programmation » caché avec une des touches fléchées).
4. Ouvrez le nouveau fichier et maintenez <kbd>OK</kbd>.

Procédures par constructeur : **[Utiliser le Flipper comme nouvelle télécommande](/fr/subghz/remote-prog)**.

## Dépannage

- **Ça a fonctionné une fois, puis plus du tout** — vous utilisez un clone. Appuyez plusieurs fois de suite pour
  resynchroniser, ou créez plutôt une nouvelle télécommande.
- **La télécommande d'origine ne fonctionne plus** — le Flipper a pris de l'avance. Appuyez plusieurs fois sur
  l'originale ; si l'écart est trop grand, réenregistrez-la auprès du récepteur.
- **Les flèches ne font rien** — le protocole n'a pas de boutons personnalisés, ou le fichier est statique sans
  champ de bouton.
- **`KL: Unknown` après un Read** — la clé constructeur est inconnue ; le signal ne peut pas être émis. Voir
  [KeeLoq](/fr/subghz/keeloq).

::: warning
N'utilisez ces fonctions qu'avec votre propre matériel ou avec l'autorisation du propriétaire.
:::

## Voir aussi

- [Add Manually](/fr/subghz/add-manually) · [Programmation d'une télécommande](/fr/subghz/remote-prog)
- [KeeLoq](/fr/subghz/keeloq) · [Modes de compteur](/fr/subghz/counter-mode)
- [Systèmes pris en charge](/fr/subghz/supported-systems)
