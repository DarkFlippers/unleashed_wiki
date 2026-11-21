---
title: Récupération rapide des clés avec qUnleashed
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Récupération rapide des clés MIFARE Classic avec qUnleashed

Un guide pratique de **@gromovyna** : récupérer rapidement des clés MIFARE Classic à l'aide d'Unleashed et de son
application compagnon **qUnleashed** (développée et maintenue par l'équipe Unleashed ; un grand merci à
[apfxtech](https://github.com/apfxtech), l'auteur d'origine de l'application). C'est la suite de
[Attaques nested et backdoors Fudan](/fr/nfc/nested-fudan) ; lire d'abord cette page est recommandé mais pas
obligatoire.

La récupération couvre **toutes les attaques et tous les types de nonces** connus au moment de la rédaction :
*weak, hard, static, static encrypted*. Contrairement à l'[application MFKey](/fr/nfc/mfkey-app), le calcul lourd
s'exécute sur votre téléphone ou votre ordinateur, ce qui prend généralement des **minutes**, et non des heures.

::: warning Il vous faut le tag en main
Le tag doit être physiquement présent pour la lecture finale. « J'ai fait un dump pour un ami et le tag n'est plus
là » ne fonctionnera pas.
:::

## Versions

La fonctionnalité existe peut-être dans des versions légèrement antérieures, mais voici celles qui ont servi aux
tests :

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

Voir aussi [Application qUnleashed](/fr/mobile/qunleashed-app) pour l'installation et les autres fonctions.

## Ce qu'il vous faut

Un tag **MIFARE Classic** (ou une **MIFARE Plus en SL1**, SL1 uniquement) avec **au moins une clé connue ou une
backdoor**.

![Un tag avec une clé inconnue](/img/remote/286db70e86cfa835.png)

![Un tag avec backdoor : clés inconnues, mais secteurs lus via la backdoor](/img/remote/59bd4aa5ae1242c1.png)

Si votre tag n'a pas de backdoor et pas une seule clé connue, obtenez-en d'abord une auprès du lecteur avec
[MFKey32](/fr/nfc/mfkey). qUnleashed peut aussi récupérer des clés à partir de nonces de lecteur (voir l'étape 2).

## Étape 1. Collecter les nonces

1. Avant l'attaque, c'est une bonne idée d'effacer `/ext/nfc/.nested.log` si vous en avez un (`/ext/` est la carte
   SD). Après la récupération, il est également judicieux de le supprimer, pour qu'il ne grossisse pas et n'encombre
   pas. Pour qUnleashed, ce n'est pas critique, mais c'est une bonne pratique.
2. Lisez le tag : `Main Menu → NFC → Read`. Attendez le déroulement des phases ; celles qui apparaissent dépendent du
   type de nonces du tag : **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**, **Calibration**,
   **Nonce Collection**.

   ![Collecte de nonces](/img/remote/786d77b7b65b3fd0.png)

3. Quand les informations du tag apparaissent, **enregistrez le dump incomplet** : vous en aurez besoin plus tard.
4. Vous pouvez éventuellement vérifier dans qUnleashed que les nonces sont bien là : connectez le Flipper, ouvrez
   `Archive → External → nfc`, activez l'affichage des fichiers cachés (le menu « burger » / à trois points en haut à
   droite) et cherchez `.nested.log`.

   ![.nested.log dans qUnleashed](/img/remote/c4c534fbe93faa8a.png)

## Étape 2. Récupérer les clés

Tout se passe dans **qUnleashed** ; le Flipper doit rester connecté (Bluetooth ou câble) pendant toute la durée.

1. Ouvrez `Tools → Recover MIFARE Keys`.

   ![L'entrée du menu](/img/remote/1a255b9128f988ab.png)

2. Attendez la fin de la récupération.

   ![Récupération des clés](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Soyez patient
   Cela peut prendre un certain temps selon la taille de `.nested.log`, les types de nonces, la puissance de
   l'appareil qui exécute qUnleashed, etc. Il s'agit généralement de minutes. Attendez la fin de l'opération. Les
   static encrypted nonces sont les plus longs.
   :::

3. Examinez le résultat. La phase de récupération travaille avec **`.mfkey32.log`** (nonces de lecteur) et
   **`.nested.log`** (nonces de tag). L'écran indique d'où vient chaque clé, combien ont été ajoutées au dictionnaire
   utilisateur ou au dictionnaire de candidates, etc.

   ![Résultat de la récupération](/img/remote/1c5f56614caf4530.png)

L'endroit où vont les clés dépend du type de nonces :

| Nonces | Résultat |
|---|---|
| weak, hard, static | Les clés sont ajoutées au **dictionnaire utilisateur** `/ext/nfc/assets/mf_classic_dict_user.nfc`. |
| static encrypted | La clé ne peut pas être calculée exactement à ce stade : un **dictionnaire de candidates** (aussi appelé **dictionnaire CUID**) est donc construit : `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, où `{UID}` est l'identifiant de votre tag. Il peut être volumineux : l'exemple de l'auteur comportait plus de **1,2 million de candidates** pour un seul tag. |

## Étape 3. Relire le tag

Posez le tag sur le Flipper et allez soit dans `NFC → Read`, soit ouvrez le dump incomplet enregistré et choisissez
**Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

Avec un **dictionnaire CUID**, celui-ci est chargé en premier. Le dictionnaire de candidates est volumineux, ce
chargement prend donc du temps, et vous voyez une barre de progression (*« CUID dictionary is loading »*). Ici, le
temps de chargement réel se compte en **minutes**.

![Écran de chargement, build de développement 1437+](/img/remote/47427c58e2a34889.png)

::: tip Update 22.09.2026
Dans les premières versions du firmware, ce moment n'affichait qu'un écran vide, ce qui a dérouté beaucoup
d'utilisateurs. À partir du build de développement **1437** (et de la version **094**), l'écran comporte une barre de
progression.
:::

L'attaque par dictionnaire s'exécute ensuite avec les clés récupérées.

![Attaque par dictionnaire](/img/remote/f77ef58bda94b088.png)

Là encore, pour les **static encrypted nonces (dictionnaire CUID)**, laissez le Flipper sur le tag pendant la
recherche et allez vous faire un thé.

Une fois toutes les clés trouvées, vous pouvez mettre à jour le dump partiel enregistré pour en faire un dump
complet, ou l'enregistrer sous un nouveau nom.

![Tag entièrement lu](/img/remote/9f9745d0d2ee0a4a.png)

Toutes les options sont désormais disponibles : émulation, écriture sur des cartes vierges, partage avec un ami, etc.

::: warning Avant d'écrire sur une carte vierge
Sachez faire la différence entre les cartes vierges et comprenez comment les lecteurs peuvent les filtrer : voir
[Cartes magiques](/fr/nfc/magic-cards).
:::

## Facultatif : enregistrer les clés d'un tag static encrypted dans le dictionnaire utilisateur

En raison du fonctionnement de l'attaque, les clés récupérées depuis le dictionnaire de candidates sont stockées
**uniquement dans ce dictionnaire et dans le dump du tag**. C'est un problème si vous voulez écrire une carte vierge
puis l'effacer plus tard : [NFC Magic](/fr/nfc/nfc-magic) ne travaille qu'avec le cache de clés et les dictionnaires
utilisateur et système.

L'équipe a donc ajouté au firmware l'enregistrement automatique des clés, avec contrôle de doublons. Ouvrez le menu
du dump enregistré (au moins une clé doit être connue) et choisissez **Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

Le Flipper affiche *« Saving keys to user dictionary »* puis *« New keys: N, Already known: M »*.

## Alternatives

Il existe aussi un [projet en ligne de commande](https://github.com/phntm-lab/mfkey_desktop_cli) pour la
récupération. À certains égards il est plus rapide, mais la ligne de commande est réservée aux geeks acharnés. Pour
un usage quotidien, l'auteur préfère la commodité de l'application compagnon, surtout au vu du nombre d'autres
fonctions utiles qu'elle propose. Sur le Flipper seul, utilisez l'[application MFKey](/fr/nfc/mfkey-app).

Le processus peut sembler un peu compliqué au début, mais après un peu de pratique il devient une routine.

## Voir aussi

[Attaques nested](/fr/nfc/nested-fudan) · [MFKey32](/fr/nfc/mfkey) · [Application MFKey](/fr/nfc/mfkey-app) ·
[MIFARE Classic](/fr/nfc/mifare-classic) · [Cartes magiques](/fr/nfc/magic-cards) · [Application qUnleashed](/fr/mobile/qunleashed-app)
