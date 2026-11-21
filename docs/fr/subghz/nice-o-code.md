---
title: Application Nice O-Code
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Application Nice O-Code

**Nice O-Code** (par @xMasterX) récupère le **code installateur (IC)** de 16 bits d'une télécommande Nice O-Code et enregistre la télécommande dans un fichier `.sub` — soit comme simple clone, soit comme **nouvelle télécommande** de la même installation, que vous pouvez enregistrer dans le récepteur.

## Contexte

Nice O-Code est un Nice FloR-S clé par un code installateur — une valeur partagée par toutes les télécommandes d'une installation. Le récepteur n'accepte qu'une télécommande qui porte son code installateur. Un seul appui capturé ne suffit pas à le retrouver, mais **quatre appuis ou plus** y parviennent : seul le bon code fait que tous les appuis décodent vers le même numéro de série. L'application collecte les appuis et attaque par force brute les 65 536 codes directement sur le Flipper.

Certaines télécommandes O-Code portent aussi le **certificat** du récepteur (un paquet plus long, de 112 bits, émis seulement pendant les vingt premières utilisations de la télécommande). Lorsque l'application en voit un, elle le démasque dès que l'IC est connu et l'affiche sous la forme `Cert`.

::: tip Unleashed
Nice O-Code est une application système intégrée d'Unleashed, et l'application Sub-GHz peut décoder et émettre des télécommandes O-Code dès qu'un fichier porte l'IC. `Add Manually` propose les entrées correspondantes `Nice O-Code`, `Nice O-Code One` et `Nice O-Code+Crt` — voir [Add manually](/fr/subghz/add-manually) et [Programmer une nouvelle télécommande](/fr/subghz/remote-prog).
:::

::: warning
À n'utiliser que sur votre propre installation. Un clone partage le compteur avec la télécommande d'origine et les deux vont se gêner mutuellement (voir [Codes tournants](/fr/subghz/rolling-codes)).
:::

## Prérequis

- Le fichier de clés Nice FloR-S `/ext/subghz/assets/nice_flor_s` sur la carte SD (il est fourni avec le firmware). Sans lui, l'application signale `No rainbow table`.
- Une télécommande O-Code fonctionnelle de l'installation. L'application écoute sur **433.92 MHz AM650**, avec la radio interne ou une radio [externe](/fr/subghz/external-cc1101) (`Int` / `Ext` dans l'en-tête).

## Capturer une télécommande

1. Ouvrez `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Choisissez `Capture remote`. L'état affiche `Listening 433.92`.
3. Appuyez sur le bouton de la télécommande **4 fois ou plus — des appuis courts, ne maintenez pas le bouton**. Chaque nouvel appui affiche `Press N: …` ; la ligne `Presses n/4  Xpkt` et la barre de progression se remplissent. Si la télécommande a un certificat, la ligne se termine par `+Crt`.
4. Une fois 4 appuis collectés, `Solve` apparaît — appuyez sur <kbd>OK</kbd>.
5. L'écran affiche `Trying installer codes` avec un compteur allant jusqu'à 65536. <kbd>←</kbd> (`Cancel`) l'interrompt.
6. En cas de succès, vous voyez `IC XXXX`, `Serial XXXXXXX` et, le cas échéant, `Cert XXXXXX`.

États que vous pouvez voir pendant la capture :

| État | Signification |
|---|---|
| `Not O-Code, ignored` | un paquet qui n'est pas de l'O-Code (par exemple une simple télécommande FloR-S) |
| `Same press, ignored` | la répétition d'un appui déjà mémorisé |
| `Need 4+ packets` | pas assez d'appuis pour résoudre |
| `Ambiguous, capture more` | plusieurs codes conviennent — appuyez encore quelques fois sur la télécommande et relancez la résolution |
| `No code fits, not O-Code?` | aucun code installateur ne correspond — ce n'est probablement pas une télécommande O-Code, ou des appuis de télécommandes différentes ont été mélangés |

## Enregistrement

Sur l'écran de résultat :

- <kbd>OK</kbd> (`Save`) — un **clone** de la télécommande capturée (nom par défaut `NiceO`). Utile pour les essais, mais il entre en conflit avec votre télécommande d'origine sur le compteur.
- <kbd>→</kbd> (`New`) — une **nouvelle télécommande** : le même code installateur, le même bouton et le même certificat, mais un numéro de série et un compteur qui lui sont propres (nom par défaut `NiceO_new`). C'est celle-là qu'il faut enregistrer dans le récepteur. Le compteur est positionné proche de celui de votre télécommande fonctionnelle, et un peu en dessous.

Les deux sont écrits dans `/ext/subghz/` après que vous les avez nommés (`Name the .sub file`). Ouvrez-les dans `Sub-GHz → Saved`.

Pour enregistrer la nouvelle télécommande, suivez la procédure Nice FloR-S décrite dans [Programmer une nouvelle télécommande](/fr/subghz/remote-prog). Une télécommande avec certificat s'enrôle elle-même : appuyez sur sa touche environ une fois par seconde, **10 à 15 fois d'affilée** — le portail s'ouvre vers le dixième appui.

## Decode RAW file

`Decode RAW file` exécute la même récupération sur un fichier `.sub` RAW enregistré auparavant avec [Read RAW](/fr/subghz/read-raw) (enregistrez 4 appuis distincts ou plus). Un fichier-clé est refusé avec `Not a RAW capture`. La barre de progression indique où l'on en est dans le fichier.

## Dépannage

- **`No rainbow table`** — `/ext/subghz/assets/nice_flor_s` est absent ; réinstallez le firmware avec la carte SD en place, ou restaurez le dossier des assets.
- **Les appuis ne sont pas comptés** — faites des appuis courts et distincts ; maintenir le bouton répète le même appui.
- **Un récepteur sortant d'usine ignore la télécommande O-Code** — un récepteur jamais configuré n'a pas de code installateur ; enregistrez plutôt une simple télécommande `Nice One` / `Nice FloR-S` via le bouton du récepteur (voir [Programmer une nouvelle télécommande](/fr/subghz/remote-prog)).
- **Le récepteur refuse la nouvelle télécommande** — gardez le compteur proche de celui de votre télécommande fonctionnelle ; ne le remettez pas à zéro.

## Pages liées

- [Programmer une nouvelle télécommande](/fr/subghz/remote-prog) · [Add manually](/fr/subghz/add-manually)
- [Codes tournants](/fr/subghz/rolling-codes) · [Systèmes pris en charge](/fr/subghz/supported-systems)
