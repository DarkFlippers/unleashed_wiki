---
title: Dispositions de clavier
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Dispositions de clavier Bad USB

Un clavier USB n'envoie pas des caractères, il envoie des **positions de touches**. C'est l'ordinateur qui les
transforme en caractères selon *sa* disposition de clavier. Pour taper `z` sur un PC allemand (QWERTZ), le Flipper
doit donc appuyer sur la touche qui correspond à `y` sur un clavier américain. Un **fichier de disposition** (`.kl`)
indique à Bad USB quelle touche (et quel modificateur) produit chaque caractère sur la disposition cible.

::: tip Unleashed
Les dispositions de clavier pour Bad USB proviennent de
[rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl) et font partie d'Unleashed. La commande
`DUCKY_LANG` par script est une nouveauté d'Unleashed (PR #1224).
:::

## Dispositions disponibles

Fichiers présents dans `/ext/badusb/assets/layouts/` (31 dans la version actuelle) :

| Fichier | Disposition |
|---|---|
| `en-US.kl` | Anglais (États-Unis), la disposition **par défaut** et le repli intégré |
| `en-UK.kl` | Anglais (Royaume-Uni) |
| `de-DE.kl`, `de-DE-mac.kl` | Allemand (Allemagne), PC et Mac |
| `de-CH.kl` | Allemand (Suisse) |
| `fr-FR.kl`, `fr-FR-mac.kl` | Français (France), PC et Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | Français (Belgique, Canada, Suisse) |
| `es-ES.kl`, `es-LA.kl` | Espagnol (Espagne, Amérique latine) |
| `it-IT.kl`, `it-IT-mac.kl` | Italien, PC et Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portugais (Portugal, Brésil) |
| `nl-NL.kl` | Néerlandais |
| `da-DA.kl` | Danois |
| `nb-NO.kl` | Norvégien |
| `sv-SE.kl` | Suédois |
| `fi-FI.kl` | Finnois |
| `cz_CS.kl` | Tchèque |
| `sk-SK.kl` | Slovaque |
| `hu-HU.kl` | Hongrois |
| `hr-HR.kl` | Croate |
| `si-SI.kl` | Slovène |
| `ba-BA.kl` | Bosnien |
| `tr-TR.kl` | Turc |
| `ja-JP.kl` | Japonais |
| `dvorak.kl` | Dvorak (US) |
| `colemak.kl` | Colemak |

Il n'existe pas de disposition russe ou cyrillique : le format ne peut décrire que des caractères ASCII (voir
ci-dessous).

## Choisir une disposition

**Globalement** (pour tous les scripts) : sur l'écran du script, appuyez sur <kbd>←</kbd>
**Config → Keyboard Layout (global)** et choisissez un fichier `.kl`. Le choix est enregistré dans
`/ext/badusb/.badusb.settings` et affiché entre parenthèses sur l'écran du script, par exemple `(de-DE)`. Si le
fichier enregistré est absent ou corrompu, `en-US` est utilisé.

![Menu Config de Bad USB, Keyboard Layout (global) en première entrée](/screens/badusb/config.png)

**Par script** : placez `DUCKY_LANG <name>` en tête du script :

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` est le nom du fichier sans `.kl`. Alias : `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Elle s'applique à partir de cette ligne et est réinitialisée à la disposition globale au début de chaque
  exécution.
- Un nom inconnu ou invalide retombe sur la disposition intégrée `en-US` sans arrêter le script.

## Ce qu'une disposition ne change PAS

- Seuls le texte de `STRING` / `STRINGLN` et les touches à caractère unique (`CTRL c`, `HOLD a`…) passent par la
  disposition. Les touches nommées (`ENTER`, `F5`, flèches…) sont identiques partout.
- `ALTCHAR` / `ALTSTRING` n'utilisent pas du tout la disposition ; elles tapent les caractères par leur code via
  `ALT`+pavé numérique, ce qui explique qu'elles fonctionnent avec n'importe quelle disposition sous Windows.
- La disposition doit correspondre à la **langue de saisie active de l'hôte**. Sur un PC avec plusieurs langues (par
  exemple l'anglais et le russe), basculez l'hôte sur la langue de la disposition avant de lancer le script, sinon
  `STRING` tapera des lettres cyrilliques.

## Format de fichier (`.kl`)

Un fichier `.kl` est une table binaire de **256 octets** exactement : 128 entrées de 2 octets (`uint16` en
little-endian), une pour chaque code ASCII de 0 à 127.

- **Octet de poids faible** : le code d'usage HID de la touche à presser (par exemple `0x1F` = la touche `2`).
- **Octet de poids fort** : les bits de modificateurs à maintenir avec elle :

| Bit (octet de poids fort) | Modificateur |
|---|---|
| `0x01` | Ctrl gauche |
| `0x02` | Maj gauche |
| `0x04` | Alt gauche |
| `0x08` | GUI gauche |
| `0x10` | Ctrl droit |
| `0x20` | Maj droite |
| `0x40` | Alt droit (AltGr) |
| `0x80` | GUI droit |

Exemple tiré de `de-DE.kl` : l'entrée pour `"` (ASCII 34) vaut `1F 02`, c'est-à-dire Maj + `2`, qui est bien la
position du guillemet droit sur un clavier allemand.

Comme la table ne compte que 128 entrées, **seul l'ASCII peut être tapé** ; un `STRING` contenant un octet ≥ 128
(accents UTF-8, cyrillique, émoji) arrête le script avec *« Native .kl supports ASCII, not UTF-8 »*. Les noms de
fichiers peuvent contenir des lettres, des chiffres, `-` et `_` (32 caractères maximum avant `.kl`).

Pour créer votre propre disposition, suivez les instructions de
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) et copiez le fichier
obtenu dans `/ext/badusb/assets/layouts/`.

## Voir aussi

- [Format des scripts](/fr/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Utiliser le Bad USB](/fr/badusb/usage)
- [Exemples](/fr/badusb/examples)
