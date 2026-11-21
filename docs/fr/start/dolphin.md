---
title: Le dauphin
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# Le dauphin

Un dauphin numérique vit sur le bureau du Flipper. Il devient plus heureux et monte de niveau à mesure que vous
utilisez les outils de l'appareil, et ses animations changent selon son humeur et son niveau.

## Passport

Appuyez sur <kbd>→</kbd> sur le bureau, ou allez dans **Main Menu → Settings → Passport**. Le passeport affiche :

- l'illustration du dauphin correspondant au niveau actuel ;
- le **nom** : le nom de l'appareil ([vous pouvez le changer](/fr/start/custom-name)) ;
- **Mood** : `Happy`, `Ok` ou `Angry` ;
- **Level** et une barre de progression vers le niveau suivant.

![Passport : le portrait du dauphin, le nom du Flipper, Mood: Happy, Level: 2 et la barre de progression vers le niveau 3](/screens/settings/passport.png)

## Humeur

Le dauphin devient plus triste quand vous n'utilisez pas le Flipper. Son compteur de contrariété (« butthurt »)
augmente d'une unité environ **toutes les 48 heures** sans activité. Utiliser les applications fait remonter l'humeur,
avec un plafond quotidien sur la vitesse de récupération.

Le **Happy Mode** maintient le dauphin heureux quoi qu'il arrive :

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. Le dialogue affiche : *« I will never get angry at you
for not spending time with me as long as this mode is enabled »*. Rouvrez-le et choisissez **Disable** pour le
désactiver.

## Niveaux et expérience

| Niveau | Expérience requise |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Chaque application peut rapporter au maximum **20 XP par jour**. Il y a 7 groupes comptabilisés (Sub-GHz, RFID, NFC,
Infrared, iButton, Bad USB et les « plugins », qui regroupent U2F, GPIO et les applications externes), ce qui porte le
maximum à **140 XP par jour**. Les limites sont remises à zéro chaque jour.

### Expérience par action

| Application | Action | XP |
|---|---|---|
| Sub-GHz | Recevoir et consulter un signal | 1 |
| | Enregistrer un signal | 3 |
| | Enregistrer en RAW | 1 |
| | Add manually | 2 |
| | Envoyer un signal enregistré | 2 |
| | Utiliser le Frequency Analyzer | 1 |
| RFID 125 kHz | Entrer dans Read | 1 |
| | Lecture réussie | 3 |
| | Save | 3 |
| | Emulate | 2 |
| | Add manually | 2 |
| NFC | Entrer dans Read | 1 |
| | Lecture réussie | 3 |
| | Save | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emulate | 2 |
| | Ajouter une clé manuellement | 2 |
| | Add manually puis enregistrer / émuler | 1 |
| Infrared | Envoyer un signal | 1 |
| | Apprentissage réussi | 3 |
| | Save | 3 |
| iButton | Entrer dans Read | 1 |
| | Lecture réussie | 3 |
| | Save | 3 |
| | Emulate | 2 |
| | Add manually | 2 |
| Bad USB | Exécuter un script | 3 |
| U2F | Autorisation réussie | 3 |
| GPIO | Ouvrir l'`USB-UART Bridge` | 1 |
| Apps | Lancer une application externe | 2 |
| | Lancer un jeu | 1 |
| | Gagner une partie | 10 |

Quand le dauphin atteint un nouveau niveau, le Flipper affiche une notification de passage de niveau et les animations
du bureau changent.

## Où l'état est stocké

L'expérience, le niveau et l'humeur du dauphin sont conservés dans `.dolphin.state`, dans le stockage interne. Une
[réinitialisation d'usine](/fr/start/recovery#factory-reset) ramène le dauphin au niveau 1.
