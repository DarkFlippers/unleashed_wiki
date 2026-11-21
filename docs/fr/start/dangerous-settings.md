---
title: Réglages dangereux
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Réglages dangereux : plage Sub-GHz étendue

Unleashed peut autoriser la radio CC1101 à fonctionner **en dehors de sa plage de fréquences officielle**. Cette page
explique ce que fait ce réglage, pourquoi vous n'en avez presque certainement pas besoin, et comment l'activer si vous
en avez réellement besoin.

::: danger À lire en premier
1. Ne faites pas cela si vous ne savez pas exactement ce que vous faites.
2. La plage étendue n'est nécessaire pour presque aucun usage.
3. Émettre en dehors des spécifications du matériel **peut endommager votre matériel**.
4. Ni l'équipe Flipper Devices ni les développeurs d'Unleashed ne sont responsables des dommages causés par un
   firmware personnalisé ou par l'extension de la plage de fréquences.
:::

## Vous n'en avez probablement pas besoin : il n'y a pas de verrou régional

::: tip Unleashed
Sur Unleashed, **toutes les restrictions régionales d'émission sont supprimées par défaut**. Toute fréquence située
dans la plage prise en charge par la puce émet sans aucune manipulation supplémentaire. N'utilisez pas le réglage
dangereux pour « débloquer votre région » : ce n'est pas nécessaire.
:::

Si l'émission est bloquée sur une fréquence, vérifiez d'abord que cette fréquence se trouve dans la plage d'émission
normale indiquée ci-dessous. En dehors de celle-ci, le firmware journalise
`Frequency blocked - outside default range`.

## Plages de fréquences

| | Plages |
|---|---|
| Fiche technique du CC1101 | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Plage d'**émission** par défaut d'Unleashed | ≈ 300–350 MHz, 387–467.75 MHz, 779–928 MHz (élargie pour inclure 350 MHz et 467 MHz) |
| Émission avec `dangerous_settings` activé | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

La plage étendue correspond à la plage étendue du YARD Stick One (d'après le code source du firmware). En dehors des
plages de la fiche technique, la puce fonctionne hors spécifications et une émission peut l'endommager.

## Comment l'activer

1. Retirez la carte microSD, ou connectez-vous avec qFlipper / le gestionnaire de fichiers de votre choix.
2. Ouvrez le fichier **`/ext/subghz/assets/dangerous_settings`**. Il ressemble à ceci :
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Lisez les commentaires, puis remplacez `false` par `true` :
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Enregistrez le fichier et redémarrez le Flipper. Le réglage est lu au démarrage.

Pour revenir en arrière, remettez la valeur à `false` et redémarrez.

::: warning Mises à jour
Ce fichier fait partie des ressources du firmware. Une mise à jour peut l'écraser avec la valeur par défaut `false`.
Vérifiez-le après une mise à jour si vous dépendez de ce réglage.
:::

## Pages liées

- Fréquences et presets Sub-GHz, ajout de vos propres fréquences : [Fréquences](/fr/subghz/frequencies)
- Réglages Sub-GHz dans l'application : [Réglages Sub-GHz](/fr/subghz/settings)
- Module CC1101 externe : [CC1101 externe](/fr/subghz/external-cc1101)

N'utilisez la radio que sur vos propres appareils et dans le respect de la réglementation radio locale.
