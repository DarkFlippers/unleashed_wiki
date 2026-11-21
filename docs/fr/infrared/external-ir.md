---
title: Modules IR externes
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Modules IR externes (GPIO)

Les trois LED IR intégrées suffisent pour un salon, mais la portée reste limitée. Pour plus de puissance, vous
pouvez relier un **émetteur IR externe** (une carte avec des LED plus puissantes et un transistor de commande) au
connecteur GPIO. L'application Infrared émet alors par celui-ci au lieu des LED intégrées. Les télécommandes
universelles, les télécommandes enregistrées, l'application mobile et le bouton « Send » de l'écran de capture
utilisent tous la sortie sélectionnée.

::: tip Unleashed
La prise en charge des modules IR externes avec détection automatique fait partie des fonctions annoncées
d'Unleashed ; la logique de détection elle-même vient du firmware officiel, le comportement décrit ici est donc le
même sur les deux.
:::

## Câblage

| Broche du module | Broche GPIO du Flipper |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, alimentée quand « 5V on GPIO » est sur `ON`, ou 9 (3V3) pour les modules en 3,3 V |
| GND | 8, 11 ou 18 (GND) |

La broche 2 porte **le même signal modulé** (porteuse comprise, typiquement 38 kHz) que celui qui pilote
normalement les LED internes : le module n'a donc besoin que d'un étage de commande et de LED, pas de son propre
modulateur. Voir [Brochage GPIO](/fr/gpio/pinout) pour la disposition du connecteur.

::: warning Attention
L'apprentissage (la réception) passe toujours par le récepteur intégré. Le module externe est uniquement émetteur.
:::

## GPIO Settings

Allez dans `Main Menu → Infrared → GPIO Settings`. Deux options y figurent :

| Option | Valeurs | Signification |
|---|---|---|
| **Signal Output** | `Flipper` | LED IR intégrées (par défaut). |
| | `2 (A7)` | Toujours émettre sur la broche GPIO 2. |
| | `Detect` | Détecter automatiquement un module externe sur la broche 2 à chaque démarrage de l'application Infrared. |
| **5V on GPIO** | `OFF` / `ON` | Active le 5 V sur la broche GPIO 1 pour alimenter le module. Avec `Detect`, l'option affiche **`Auto`** et est pilotée automatiquement. |

Les réglages sont enregistrés en quittant l'écran, dans `/ext/infrared/.infrared.settings`, et appliqués à chaque
démarrage de l'application Infrared. Quand vous quittez l'application Infrared, la sortie revient aux LED intégrées
et le 5 V est coupé, pour que le module ne vide pas la batterie dans les autres applications.

### Pas à pas

1. Branchez le module (Signal → broche 2, VCC → broche 1, GND → broche 8/11/18).
2. Ouvrez `Infrared → GPIO Settings`.
3. Réglez **Signal Output** sur `Detect` (ou sur `2 (A7)` si la détection ne fonctionne pas avec votre module).
4. Avec `2 (A7)`, réglez **5V on GPIO** sur `ON` si le module est alimenté par la broche 1.
5. Appuyez sur <kbd>Back</kbd>. Envoyez n'importe quel bouton enregistré ou une télécommande universelle ; les LED
   du module doivent maintenant émettre.

## Comment fonctionne la détection automatique

Quand `Detect` est sélectionné, le firmware active brièvement une **faible résistance de tirage haut** sur la
broche 2 et relit son état :

- si la broche reste à l'état **bas**, c'est que quelque chose avec une résistance de tirage bas y est raccordé : un
  module externe est donc supposé présent. La sortie passe sur la broche 2 et le **5 V sur GPIO est activé
  automatiquement** ;
- si la broche est lue à l'état **haut**, rien n'est connecté et les LED intégrées sont utilisées.

Cela fonctionne au mieux avec les modules dont le pilotage des LED repose sur un **MOSFET avec une forte résistance
de tirage bas** sur la grille, ou sur un **transistor bipolaire** pour commander les LED IR. Le module **doit tirer
la broche à 0,9 V ou moins** pour être détecté. Si votre module n'a pas de résistance de tirage bas, choisissez
`2 (A7)` manuellement et activez le 5 V vous-même.

La détection a lieu au démarrage de l'application Infrared (et lorsque vous sélectionnez `Detect`). Si vous branchez
le module alors que l'application est déjà ouverte, resélectionnez `Detect` ou redémarrez l'application.

## Dépannage

| Problème | Que faire |
|---|---|
| `Detect` utilise toujours les LED intégrées | Le module ne tire pas la broche 2 suffisamment bas (≤ 0,9 V). Utilisez `2 (A7)` et activez `5V on GPIO` manuellement. |
| La LED du module ne s'allume pas | Vérifiez le VCC : avec `2 (A7)`, le 5 V doit être sur `ON`. Vérifiez la masse. Observez les LED à travers l'appareil photo d'un téléphone pendant l'émission. |
| La batterie se vide vite | Un module puissant consomme beaucoup sur le 5 V. Débranchez-le quand vous ne l'utilisez pas. |

## Voir aussi

- [Brochage GPIO](/fr/gpio/pinout)
- [Modules GPIO](/fr/gpio/external-modules)
- [Apprendre et envoyer des signaux](/fr/infrared/read)
- [Télécommandes universelles](/fr/infrared/universal-remotes)
