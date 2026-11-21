---
title: Télécommandes dans l'application mobile
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Télécommandes IR dans l'application Flipper Mobile

L'application Flipper Mobile (iOS / Android) dispose d'une **Remotes Library** : une base de données en ligne de
télécommandes IR. Vous choisissez votre type d'appareil et sa marque, l'application trouve la bonne télécommande en
testant quelques signaux, la télécharge sur le Flipper, puis affiche une vraie façade de télécommande sur l'écran de
votre téléphone. C'est le Flipper qui émet réellement.

Par rapport aux [télécommandes universelles](/fr/infrared/universal-remotes), qui envoient toute la bibliothèque à
chaque appui, une télécommande issue de la Remotes Library n'est trouvée qu'**une seule fois** et fonctionne ensuite
instantanément. Elle comporte aussi plus de boutons et couvre davantage de types d'appareils.

## Ce que vous pouvez y trouver

La bibliothèque comprend entre autres des télécommandes pour : téléviseurs, projecteurs, box TV, ventilateurs,
purificateurs d'air, lecteurs DVD, appareils photo et amplis AV. La base est open source :
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB) ; vous pouvez y contribuer avec votre télécommande en
suivant son
[guide de contribution](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md).

::: tip Unleashed
L'application mobile fonctionne avec Unleashed exactement comme avec le firmware d'origine : elle dialogue avec
l'application Infrared via RPC. Pendant que le téléphone la pilote, l'écran du Flipper affiche
**« Infrared – RPC mode »**. Les télécommandes téléchargées depuis l'application sont de simples fichiers `.ir` dans
`/ext/infrared/` et peuvent être utilisées, modifiées et renommées sur le Flipper comme n'importe quelle
télécommande apprise. Plus d'informations sur l'application elle-même :
[Flipper Mobile App](/fr/mobile/mobile-app).
:::

## Trouver la télécommande de votre appareil

1. Connectez le Flipper à l'application en Bluetooth.
2. Dans l'application, allez dans `Tools → Remotes Library`.
3. Sélectionnez le **type d'appareil**, puis la **marque**.
4. Beaucoup de marques ont plusieurs télécommandes : l'application teste donc les signaux un par un. Pointez le
   Flipper vers l'appareil, appuyez sur le bouton pour envoyer le signal et indiquez si l'appareil a réagi.
5. Quand la bonne télécommande est trouvée, l'application affiche sa façade. Vous pouvez l'utiliser immédiatement.
6. Appuyez sur **Save** (en haut à droite) et donnez un nom à la télécommande. Elle est écrite sur le Flipper.
7. *(Facultatif)* Appuyez sur **⋯ → Add to Favorites** pour la retrouver dans l'onglet Archive en accès rapide.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Utiliser une télécommande enregistrée

**Depuis le téléphone.** Dans l'application, ouvrez `Archive → Infrared` (ou les favoris), sélectionnez la
télécommande, pointez le Flipper vers l'appareil et appuyez sur les boutons du téléphone. L'application indique au
Flipper quel signal envoyer.

![Façade de télécommande dans l'application](/img/remote/7387cb59433e202d.jpg)

**Depuis le Flipper seul.** Allez dans `Main Menu → Infrared → Saved Remotes`, ouvrez la télécommande, choisissez un
bouton avec <kbd>↑</kbd> / <kbd>↓</kbd> et appuyez sur <kbd>OK</kbd>. Voir
[Apprendre et envoyer des signaux](/fr/infrared/read#send-a-saved-button).

## Dépannage

| Problème | Que faire |
|---|---|
| L'application ne peut pas émettre / rien ne se passe | Vérifiez que le Flipper est connecté et qu'il n'est pas occupé par une autre application. Fermez toute application en cours sur le Flipper et réessayez. |
| Aucune télécommande trouvée pour votre marque | Apprenez la télécommande d'origine sur le Flipper ([comment faire](/fr/infrared/read)) ou essayez les [télécommandes universelles](/fr/infrared/universal-remotes). |
| L'appareil ne réagit que de très près | Utilisez un [module IR externe](/fr/infrared/external-ir) ; l'application se sert de l'émetteur sélectionné dans les GPIO Settings de l'application Infrared. |

## Voir aussi

- [Flipper Mobile App](/fr/mobile/mobile-app)
- [Télécommandes universelles](/fr/infrared/universal-remotes)
- [Format des fichiers IR](/fr/infrared/file-format)
