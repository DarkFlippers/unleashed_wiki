---
title: Contribuer ses captures
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Contribuer des captures IR aux télécommandes universelles

Si une [télécommande universelle](/fr/infrared/universal-remotes) ne fonctionne pas avec votre appareil, vous pouvez
enregistrer votre télécommande d'origine et l'ajouter à la bibliothèque, pour qu'elle serve à tout le monde. Cette
page explique comment réaliser des captures **propres** : courtes, décodées quand c'est possible, et nommées
exactement comme la télécommande universelle l'attend.

La méthode est celle du guide Unleashed de **@amec0e** (qui maintient les ressources IR d'Unleashed), basé sur la
documentation *UniversalRemotes* originale de @gsurkov, @skotopes, @knrn-ai, @DrZlo13 et @ahumeniy.

## Noms de boutons par bibliothèque {#button-names-per-library}

La télécommande universelle n'utilise que les signaux dont le champ `name:` correspond exactement à l'un de ses
boutons (la casse compte). Chacun d'eux peut être omis si votre appareil ne le possède pas.

| Bibliothèque | Fichier | Noms de signaux |
|---|---|---|
| TVs | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projectors | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LEDs | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Fans | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| ACs | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

Sur beaucoup de télécommandes audio, `Play` et `Pause` sont le même bouton : enregistrez-le en tant que `Play` et
omettez `Pause`.

## Téléviseurs, audio, projecteurs, ventilateurs, LED

1. Pointez la télécommande vers le récepteur IR du Flipper.
2. Lancez `Infrared → Learn New Remote` pour le premier bouton, ou sélectionnez `+` dans la télécommande pour les
   suivants.
3. Faites une **pression brève** sur le bouton de la télécommande et enregistrez-le sous le nom correspondant du
   tableau ci-dessus.
4. Répétez les étapes 2-3 pour tous les boutons.
5. Testez chaque bouton enregistré sur l'appareil réel : chacun doit faire ce que son nom annonce.

::: warning Ne maintenez pas le bouton
Maintenir le bouton de la télécommande produit de longues captures pleines de répétitions. Elles mettent plus de
temps à être envoyées et ralentissent toute la télécommande universelle, pour tout le monde.
:::

### Parsed ou RAW

Le **parsed** est le meilleur résultat : le protocole a été reconnu et seuls le protocole, l'adresse et la commande
sont stockés.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Les interférences des appareils autour de vous (lampes, rétroéclairage de téléviseur, autres télécommandes) peuvent
faire basculer une capture en **RAW** même si le protocole est connu. Si vous obtenez du RAW pour une télécommande
courante, appuyez plusieurs fois sur **Retry** sur le Flipper jusqu'à obtenir une capture parsed propre.

Le **RAW** convient quand la télécommande utilise réellement un protocole inconnu. Visez le *plus petit nombre
d'échantillons* qui fonctionne encore sur l'appareil : une pression brève, typiquement **une centaine
d'échantillons**. Une capture idéale d'un appui unique ressemble à ceci :

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Climatiseurs {#air-conditioners}

Les télécommandes de climatiseur sont différentes : la télécommande conserve l'état (mode, température, ventilation,
volets) sur son afficheur, et chaque appui envoie **tout l'état** d'un coup. Chaque « bouton » de climatiseur est
donc en réalité un état complet, qui doit être capturé dans son ensemble.

Pour chaque signal **sauf `Off`** :

1. Appuyez sur **Power** sur la télécommande pour que son afficheur indique le climatiseur allumé.
2. Réglez le mode et la température d'après le tableau ci-dessous. Laissez tout le reste (vitesse de ventilation,
   volets) sur **AUTO** si possible.
3. Appuyez sur **Power** sur la télécommande pour l'éteindre.
4. Sur le Flipper, lancez l'apprentissage (`Learn New Remote` pour le premier, `+` pour les suivants).
5. Pointez la télécommande vers le Flipper et appuyez une fois de plus sur **Power** (c'est la trame « allumer dans
   ce mode »).
6. Enregistrez le signal sous le nom indiqué dans le tableau.
7. Répétez pour chaque ligne.

| Signal | Mode | Température | Remarque |
|:---:|:---:|:---:|---|
| `Dh` | Déshumidification | N/A | |
| `Cool_hi` | Refroidissement | la plus basse | température la plus basse disponible en mode refroidissement |
| `Cool_lo` | Refroidissement | 23 °C | |
| `Heat_hi` | Chauffage | la plus haute | température la plus haute disponible en mode chauffage |
| `Heat_lo` | Chauffage | 23 °C | |

Enregistrez ensuite **`Off`** :

1. Vérifiez que l'afficheur de la télécommande indique le climatiseur allumé.
2. Lancez l'apprentissage sur le Flipper et pointez la télécommande vers lui.
3. Appuyez sur **Power** pour que la télécommande affiche l'état éteint.
4. Enregistrez le signal sous le nom `Off`.

Vous obtenez ainsi jusqu'à 6 signaux. Testez-les tous sur le climatiseur réel.

## Préparer le fichier et le soumettre

1. Copiez le fichier `.ir` de `/ext/infrared/` vers votre ordinateur avec [qFlipper](/fr/mobile/qflipper) (ou
   l'application mobile) et ouvrez-le dans un éditeur de texte.
2. Faites précéder vos signaux d'un commentaire indiquant le modèle, pour que la bibliothèque reste organisée :
   ```text
   # Model: <your brand and model>
   ```
   L'ordre des signaux au sein du bloc n'a pas d'importance.
3. Forkez le [dépôt Unleashed](https://github.com/DarkFlippers/unleashed-firmware) et **ajoutez** votre bloc **à la
   fin** du fichier correspondant dans `applications/main/infrared/resources/infrared/assets/`.
4. Ouvrez une pull request avec le fichier modifié. Après relecture, il sera livré dans la prochaine version pour
   tout le monde.

Le format de fichier est décrit sur [Format des fichiers IR](/fr/infrared/file-format#library-files). Grandes
collections communautaires de télécommandes prêtes à l'emploi :
[Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) et la base officielle
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB), utilisée par
l'[application mobile](/fr/infrared/mobile).

## Voir aussi

- [Télécommandes universelles](/fr/infrared/universal-remotes)
- [Apprendre et envoyer des signaux](/fr/infrared/read)
- [Format des fichiers IR](/fr/infrared/file-format)
