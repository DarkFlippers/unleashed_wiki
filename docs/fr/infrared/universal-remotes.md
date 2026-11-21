---
title: Télécommandes universelles
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Télécommandes universelles

Une télécommande universelle permet de piloter un appareil **sans avoir à apprendre sa télécommande au préalable**.
Lorsque vous appuyez par exemple sur *Power*, le Flipper envoie le code Power de chaque modèle de sa bibliothèque,
l'un après l'autre. Dès qu'il tombe sur le code que votre appareil comprend, celui-ci réagit. C'est pourquoi un
bouton universel prend quelques secondes au lieu d'être instantané.

Ouvrez `Main Menu → Infrared → Universal Remotes`.

![La liste des catégories de Universal Remotes : TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
Le firmware officiel livre les bibliothèques TV, Audio, Projectors et AC. Unleashed ajoute **LEDs** et **Fans** et
maintient toutes les bibliothèques beaucoup plus volumineuses et régulièrement revérifiées par l'équipe (ressources
IR par @amec0e). La bibliothèque TV est recompilée afin que **tous** ses boutons fonctionnent, pas seulement Power.
:::

## Catégories

Les entrées de menu et les noms de boutons ci-dessous proviennent du firmware ; le nombre de signaux correspond aux
bibliothèques livrées avec la version `dev` actuelle (`/ext/infrared/assets/`, dernière mise à jour en octobre 2024,
février 2024 pour les climatiseurs).

| Entrée de menu | Fichier de bibliothèque | Boutons | Signaux dans la bibliothèque |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (dont 295 Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

« Audio » couvre les barres de son, les amplis AV, les chaînes hi-fi et équivalents. « LEDs » désigne les rubans et
ampoules LED pilotés en IR.

### Climatiseurs {#air-conditioners}

Les télécommandes de climatiseur conservent elles-mêmes l'état de l'appareil et envoient l'état complet à chaque
appui ; la bibliothèque AC contient donc des « scènes » complètes plutôt que des boutons isolés :

| Bouton | Signification |
|---|---|
| **Off** | Éteindre le climatiseur. C'est le *seul* bouton qui l'éteint. |
| **Dh** | Mode déshumidification (sec). |
| **Cool_hi** | Refroidissement à la température la plus basse autorisée par la télécommande (refroidissement maximal). |
| **Cool_lo** | Refroidissement à 23 °C. |
| **Heat_hi** | Chauffage à la température la plus haute autorisée par la télécommande (chauffage maximal). |
| **Heat_lo** | Chauffage à 23 °C. |

Pour **allumer** un climatiseur, appuyez sur n'importe quel bouton autre que Off. Les boutons de température
affichent des °C ou des °F selon `Settings → System → Units`.

## Utilisation

1. Allez dans `Main Menu → Infrared → Universal Remotes` et sélectionnez une catégorie.
2. Pointez la tranche supérieure du Flipper vers l'appareil. Restez proche et en vue directe.
3. Sélectionnez un bouton avec les flèches et appuyez sur <kbd>OK</kbd>.

   ![La télécommande TV universelle, affichée sur l'écran vertical : Power et Mute en haut, Channel et Volume haut/bas en dessous](/screens/infrared/universal_tv.png)

4. La fenêtre **« Sending... »** affiche la progression sous la forme `current/total` ainsi qu'une barre de
   progression. Continuez à viser l'appareil.
5. Dès que l'appareil réagit, appuyez sur <kbd>OK</kbd> pour **mettre en pause**, ou laissez la bibliothèque aller
   jusqu'au bout.

![Télécommande universelle en action](/img/remote/bdb3541a3f2e88fe.png)

### Commandes pendant l'envoi

| État | Bouton | Action |
|---|---|---|
| Envoi en cours | <kbd>OK</kbd> | **pause** |
| Envoi en cours | <kbd>Back</kbd> | **stop** |
| En pause | <kbd>Back</kbd> | **reprendre** l'envoi là où il s'est arrêté |
| En pause | <kbd>OK</kbd> | **send 1** : envoyer uniquement le signal actuellement sélectionné |
| En pause | <kbd>←</kbd> / <kbd>→</kbd> (flèches) | **sélectionner** le signal précédent / suivant de la bibliothèque |
| En pause | <kbd>↓</kbd> | **enregistrer** le signal sélectionné |

## Trouver le code exact et l'enregistrer

Le véritable intérêt de l'écran de pause : vous pouvez trouver le seul code qui fonctionne et le conserver, pour que
le bouton soit instantané la prochaine fois.

1. Lancez un bouton universel. Dès que l'appareil réagit, appuyez sur <kbd>OK</kbd> (pause). Le compteur pointe
   alors sur le dernier signal envoyé.
2. Comme vous n'êtes jamais parfaitement rapide, revenez en arrière avec la flèche gauche et utilisez **send 1**
   (<kbd>OK</kbd>) sur chaque signal jusqu'à trouver celui qui déclenche l'appareil. Utilisez la flèche droite pour
   avancer à nouveau.
3. Appuyez sur <kbd>↓</kbd> **save**. L'en-tête du menu affiche le nom du bouton (par exemple `Power`), qui est aussi
   le nom sous lequel le signal est enregistré :
   - **Save as New Remote** : saisissez un nom de télécommande dans **« Name the remote »** ; un nouveau fichier
     `.ir` est créé dans `/ext/infrared/` ;
   - **Add to Existing Remote** : choisissez un fichier `.ir` existant ; le signal y est ajouté.
4. **« Saved »** confirme l'opération. La télécommande est désormais dans `Infrared → Saved Remotes`.

Répétez l'opération pour Vol_up, Mute, etc., en ajoutant chacun à la même télécommande : vous obtenez une
télécommande personnelle et instantanée, construite à partir de la bibliothèque universelle.

![Une télécommande enregistrée sur l'écran vertical : la liste de boutons Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## Depuis la ligne de commande

Les mêmes bibliothèques peuvent être jouées via la [CLI](/fr/dev/cli) :

```text
ir universal list tv        # list the signal names in tv.ir
ir universal tv Power       # send every "Power" signal from tv.ir
```

`ir universal` sans argument liste les bibliothèques disponibles (tous les fichiers `.ir` de
`/ext/infrared/assets/`). Appuyez sur <kbd>Ctrl</kbd>+<kbd>C</kbd> dans le terminal pour arrêter.

## Dépannage

| Problème | Que faire |
|---|---|
| *« Function requires SD card with fresh databases. »* | Les fichiers de bibliothèque sont absents. Insérez la carte microSD et réinstallez / mettez à jour le firmware avec la carte SD en place, voir [Mise à jour](/fr/start/updating). |
| Rien ne réagit après toute la bibliothèque | Votre modèle n'est pas dans la bibliothèque. [Apprenez](/fr/infrared/read) plutôt la télécommande d'origine, essayez la [Remotes Library de l'application mobile](/fr/infrared/mobile), et envisagez de [contribuer vos captures](/fr/infrared/captures). |
| L'appareil réagit, mais trop tard pour mettre en pause | Utilisez la flèche gauche + **send 1** pour revenir au bon signal, voir plus haut. |
| Ne fonctionne qu'à très courte distance | Les LED intégrées sont faibles pour les grandes pièces. Utilisez un [module IR externe](/fr/infrared/external-ir). |
| Le climatiseur ne s'allume pas avec Off | C'est normal : Off ne sert qu'à l'éteindre. Utilisez Cool/Heat/Dh pour l'allumer. |

## Voir aussi

- [Contribuer ses captures](/fr/infrared/captures) : ajouter votre appareil aux bibliothèques
- [Format des fichiers IR](/fr/infrared/file-format) : le format des fichiers de bibliothèque
- [Apprendre et envoyer des signaux](/fr/infrared/read)
