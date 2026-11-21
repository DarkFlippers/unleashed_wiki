---
title: Frequency Analyzer
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Frequency Analyzer

Le Frequency Analyzer vous indique **sur quelle fréquence une télécommande émet**. Il balaie les fréquences de la
liste Sub-GHz, mesure la puissance du signal (RSSI) et affiche la plus forte. Utilisez-le avant **Read** ou
**Read RAW** lorsque vous ne connaissez pas la fréquence d'une télécommande.

::: tip Unleashed
Unleashed livre un analyseur retravaillé (à l'origine par ClusterM) avec un historique de 4 entrées, un seuil de
déclenchement réglable, un retour utilisateur au choix (son / vibreur / muet) et un **accès direct à Read** : un
appui court sur <kbd>OK</kbd> mémorise la fréquence pour Read / Read RAW, un appui long sur <kbd>OK</kbd> la
mémorise et ouvre Read immédiatement.
:::

## La règle d'or

L'analyseur est conçu pour fonctionner **à quelques centimètres seulement de l'antenne du Flipper, sur la radio
interne**. L'antenne se trouve sur le flanc gauche, à côté de la fenêtre noire de l'infrarouge. Ses réglages
existent pour filtrer le bruit, pas pour capter des signaux lointains. Avec un seuil très bas, l'analyseur se
contente de signaler des interférences aléatoires et le bruit propre du Flipper au lieu de votre télécommande. Pour
réellement *recevoir* des signaux, utilisez [Read](/fr/subghz/read) et [Read RAW](/fr/subghz/read-raw).

::: warning
L'utilisation de l'analyseur avec un module externe n'est pas recommandée : les modules externes sont plus sensibles
et captent beaucoup plus de bruit.
:::

## L'écran

![Frequency Analyzer affichant 433.920 MHz, les entrées d'historique et la barre RSSI](/screens/subghz/frequency_analyzer.png)

| Élément | Signification |
|---|---|
| Icône en haut à droite | Retour utilisateur quand un signal est capté : haut-parleur = vibreur + son, petit haut-parleur = vibreur seul, barré = muet |
| Grand nombre au centre | Fréquence courante (principale). Pendant la réception d'un signal au-dessus du seuil, elle est affichée **en inversion vidéo dans un cadre noir** |
| Les quatre entrées en dessous | Historique : fréquence arrondie et nombre de fois où elle a été captée (`x3`). Utile pour les télécommandes faibles ou celles qui dérivent |
| Barre `RSSI` en bas | Puissance du signal en direct, avec le repère du seuil |
| `T-` / `+T` | Boutons de réglage du seuil |

## Boutons

| Bouton | Action |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Déplacer le seuil (de −97 dBm à −60 dBm, par pas de 1 dBm). À gauche = plus sensible, à droite = moins sensible |
| <kbd>↑</kbd> | Faire défiler le mode de retour : vibreur + son → muet → vibreur → … |
| <kbd>↓</kbd> | Sélectionner une entrée de l'historique (un cadre apparaît autour) |
| <kbd>OK</kbd> court | Mémoriser la fréquence sélectionnée pour Read / Read RAW |
| <kbd>OK</kbd> long | Mémoriser la fréquence et ouvrir **Read** aussitôt |
| <kbd>Back</kbd> | Quitter (le seuil et le mode de retour sont mémorisés) |

Quelle fréquence <kbd>OK</kbd> retient :

- si un signal est reçu **à cet instant** (cadre noir autour de la fréquence principale) — cette fréquence, même si
  une entrée de l'historique est sélectionnée ;
- si rien n'est reçu et qu'une entrée de l'historique est sélectionnée — l'entrée sélectionnée ;
- sinon — la dernière fréquence ayant franchi le seuil, ce qui vous évite de maintenir la télécommande enfoncée.

::: warning Arrondi
La fréquence mémorisée est toujours **arrondie à la fréquence la plus proche de la liste**
([Fréquences](/fr/subghz/frequencies)). Si votre télécommande se situe loin de toutes les valeurs standard, ajoutez
sa fréquence à `setting_user`. Le nombre principal affichera alors la fréquence réelle, mais après être passé dans
Read / Read RAW, il vous faudra la régler manuellement dans `Config`.
:::

Mémoriser une fréquence depuis l'analyseur **désactive aussi le Hopping**, afin que Read démarre exactement sur
cette fréquence.

## Comment trouver la fréquence d'une télécommande

1. Éloignez-vous des alimentations à découpage, des chargeurs et des autres appareils électroniques bruyants.
2. Ouvrez `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Tenez la télécommande collée au flanc gauche du Flipper (près de la fenêtre noire).
4. Appuyez sur un bouton de la télécommande et maintenez-le. La fréquence principale passe en inversion vidéo
   pendant la réception du signal.
5. Relâchez le bouton et attendez que la fréquence arrive dans l'historique.
6. Appuyez sur <kbd>OK</kbd> pour la mémoriser, ou maintenez <kbd>OK</kbd> pour aller directement dans **Read**.

La plupart des télécommandes émettent autour de 315, 433.92 ou 868.35 MHz. Dans Read, essayez tout de même
plusieurs modulations si rien ne se décode (`AM650` d'abord, puis `FM238`, `FM476`, `FM12K`).

## Régler le seuil

Par défaut, le seuil est à −93 dBm, une position qui convient dans la plupart des cas : normalement, vous n'y
touchez pas. Ne l'ajustez que si la télécommande n'est pas captée même à bout portant, ou s'il y a beaucoup de
bruit :

1. Sans appuyer sur aucune télécommande, déplacez le repère avec <kbd>←</kbd> / <kbd>→</kbd> jusqu'à ce que le
   Flipper ne capte plus rien (pas de bruit, pas de détections aléatoires). La position la plus à gauche est la plus
   sensible — elle capte les signaux *et* le bruit interne du Flipper et toutes les interférences ; la plus à droite
   est la moins sensible aux deux.
2. Tenez la télécommande contre le bord gauche du Flipper et appuyez sur son bouton.
3. Si rien n'est capté, déplacez le seuil **vers la gauche** pas à pas jusqu'à ce que le signal apparaisse.
4. Appuyez puis relâchez le bouton de la télécommande à plusieurs reprises pendant le réglage — un signal
   intermittent rend la bonne position plus facile à trouver qu'un signal continu.

## Dépannage

- **Des fréquences aléatoires apparaissent sans arrêt** — seuil trop bas ou bruit à proximité. Déplacez-le vers la
  droite, éloignez-vous des alimentations.
- **La télécommande n'est jamais captée** — rapprochez-la, vérifiez sa pile, déplacez le seuil vers la gauche.
  Certaines télécommandes émettent de très courtes salves : appuyez à répétition.
- **Read n'affiche rien sur la fréquence trouvée** — mauvaise modulation. Changez-la dans `Read → Config`. Si rien
  ne se décode, enregistrez le signal avec [Read RAW](/fr/subghz/read-raw).
- **La fréquence diffère de l'étiquette de la télécommande** — c'est normal ; les télécommandes bon marché dérivent.
  Servez-vous des compteurs de l'historique pour retenir la valeur la plus fréquente.

## Voir aussi

- [Fréquences](/fr/subghz/frequencies) · [Read](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw)
- [Remote Analyzer](/fr/subghz/remote-analyzer) — une application avec son propre analyseur et un décodage d'une
  télécommande à la fois
