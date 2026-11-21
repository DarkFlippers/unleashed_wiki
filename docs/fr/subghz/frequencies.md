---
title: Fréquences et portée
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Fréquences et portée

Le Flipper Zero dialogue avec le monde sub-1 GHz via un émetteur-récepteur **TI CC1101**. Cette page couvre les
bandes prises en charge par la puce, la liste de fréquences livrée avec Unleashed, le fonctionnement des limites
d'émission dans Unleashed, et la façon d'ajouter vos propres fréquences.

## Bandes matérielles

La fiche technique du CC1101 spécifie trois bandes :

| Bande | Usage typique |
|---|---|
| 300–348 MHz | Portes de garage et portails américains (famille 300, 310, 315, 318, 390 MHz), télécommandes de voiture |
| 387–464 MHz | Télécommandes LPD433 à 433.92 MHz, barrières, capteurs, sonnettes (la majeure partie de l'Europe et de la CEI) |
| 779–928 MHz | Appareils en 868 MHz (SRD européen) et 915 MHz (ISM américain) |

Unleashed élargit légèrement la fenêtre d'émission par défaut afin que les fréquences courantes de 350 MHz et
467.75 MHz fonctionnent.

## Limites d'émission dans Unleashed

::: tip Unleashed
Le firmware d'origine verrouille l'émission sur les fréquences autorisées dans la **région** détectée lors de la
mise à jour (par exemple seulement 433.05–434.79 et 868.15–868.55 MHz en UE/Russie). **Unleashed supprime
totalement ce verrou régional.** Vous pouvez émettre sur n'importe quelle fréquence prise en charge par la puce,
sans aucune manipulation supplémentaire.
:::

Ce qui subsiste, c'est une limite matérielle de sécurité (issue de `furi_hal_subghz.c`) :

| Mode | Plages d'émission autorisées |
|---|---|
| Par défaut | 300–350 MHz, 387–467.75 MHz, 779–928 MHz |
| Étendu (« dangereux ») | 281–361 MHz, 378–481 MHz, 749–962 MHz |

Si vous tentez d'émettre en dehors de la plage autorisée, le Flipper refuse de transmettre.

### Étendre la plage (dangereux) {#extended-range}

::: danger Danger
Émettre en dehors des spécifications du CC1101 peut **endommager la puce radio**. Ni l'équipe Flipper ni les
développeurs d'Unleashed ne sont responsables des dommages. Presque personne n'a besoin de cela : la plage par
défaut couvre déjà pratiquement toutes les télécommandes réelles.
:::

1. Connectez la carte SD à un PC (ou utilisez qFlipper / le gestionnaire de fichiers de l'application mobile).
2. Ouvrez `/ext/subghz/assets/dangerous_settings`. Son contenu ressemble à ceci :
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Remplacez `false` par `true`, enregistrez le fichier et redémarrez le Flipper (le réglage est lu au démarrage).

Voir aussi [Réglages dangereux](/fr/start/dangerous-settings).

## Liste de fréquences par défaut

Voici les fréquences que vous pouvez parcourir avec <kbd>←</kbd> <kbd>→</kbd> dans **Read**, dans **Read RAW** →
`Config`, et sur lesquelles le Frequency Analyzer arrondit. **433.92 MHz** est la valeur par défaut.

| 300–350 MHz | 387–467.75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (début de LPD433), 433.220, 433.420, 433.657070, 433.889, **433.920** (milieu de LPD433, valeur par défaut), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (fin de LPD433), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Liste de hopping

Quand **Hopping** est activé, le récepteur ne parcourt qu'une courte liste (une longue liste raterait des signaux) :

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulations (presets)

La fréquence seule ne suffit pas : le Flipper n'est pas une SDR, il faut lui indiquer la modulation à l'avance.
Presets intégrés :

| Nom dans le menu | Preset dans le fichier `.sub` | Signification |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, bande passante de 270 kHz |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, bande passante de 650 kHz — **par défaut, utilisé par la plupart des télécommandes** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, excursion de 2,38 kHz |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, excursion de 47,6 kHz |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, excursion de 12 kHz (par exemple Cardin S449, Sommer) |

Vous pouvez ajouter vos propres presets (par exemple `FM15k`, `Pagers`) — voir
[Formats de fichiers](/fr/subghz/file-format#setting-user).

## Ajouter ses propres fréquences {#adding-frequencies}

1. Sur la carte SD, allez dans `/ext/subghz/assets/`.
2. Renommez `setting_user.example` en `setting_user` (les fichiers `_user` survivent aux mises à jour du firmware).
3. Ajoutez des lignes à ce format — toujours 9 chiffres, en Hz :
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Redémarrez l'application Sub-GHz.

Quelques règles utiles :

- Les fréquences utilisateur sont **ajoutées à la suite** de la liste par défaut : descendez jusqu'à la fin de la
  liste pour les trouver.
- `Hopper_frequency` ajoute une fréquence au hopping. Gardez la liste de hopping courte. Répéter une fréquence fait
  que le Flipper l'écoute plus souvent.
- Pour n'utiliser **que** vos propres fréquences, remplacez `#Add_standard_frequencies: true` par
  `Add_standard_frequencies: false`. Vous devez alors remplir **les deux** listes (`Frequency:` et
  `Hopper_frequency:`) — sinon la liste principale sera vide.
- `Default_frequency: 433920000` définit la fréquence sur laquelle Read et Read RAW démarrent.

## Dépannage

- **Rien n'est reçu** — la fréquence ou la modulation est mauvaise. Trouvez la fréquence avec le
  [Frequency Analyzer](/fr/subghz/frequency-analyzer), puis essayez `AM650`, puis les presets FM.
- **Ma fréquence n'est pas dans la liste** — ajoutez-la à `setting_user` (voir ci-dessus). L'analyseur arrondira
  quand même à l'entrée la plus proche de la liste : réglez donc la valeur exacte manuellement dans `Config`.
- **Émission refusée** — la fréquence est en dehors de la fenêtre d'émission par défaut ; vérifiez le tableau
  ci-dessus. N'activez pas la plage étendue juste « pour essayer ».

## Voir aussi

- [Frequency Analyzer](/fr/subghz/frequency-analyzer) · [Read](/fr/subghz/read) · [Read RAW](/fr/subghz/read-raw)
- [Réglages radio](/fr/subghz/settings) · [Formats de fichiers](/fr/subghz/file-format) · [CC1101 externe](/fr/subghz/external-cc1101)
