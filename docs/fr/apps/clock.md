---
title: Horloge
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Horloge

Une horloge de chevet : grand affichage de l'heure, date et niveau de batterie, réglage de la luminosité de l'écran
avec veilleuse à LED rouge, chronomètre et alarme quotidienne. Basée sur FlipperNightStand de @nymda, avec @Willy-JL,
@mishamyte et @xMasterX (version 1.3 de l'application).

`Main Menu → Clock`

![Clock : la date au-dessus du grand affichage de l'heure et le niveau de batterie en dessous](/screens/apps/clock.png)

::: tip Unleashed
Dans Unleashed, l'horloge est une application du menu principal dotée d'une alarme et d'une veilleuse. Si vous voulez
seulement l'heure sur le bureau, activez plutôt `Settings → Desktop → Show Clock`.
:::

## Boutons sur l'écran de l'horloge

| Bouton | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | luminosité de l'écran plus / moins forte (une barre apparaît et disparaît 3 s après le dernier appui) |
| <kbd>↓</kbd> à la luminosité 0 | allume / éteint la veilleuse à LED rouge tamisée |
| <kbd>OK</kbd> | Start / Stop du chronomètre |
| <kbd>←</kbd> | remet le chronomètre à zéro |
| <kbd>→</kbd> | réglage de l'alarme |
| <kbd>Back</kbd> | quitter |

L'heure suit le format système : 12 heures avec AM/PM ou 24 heures, selon le réglage de
`Settings → System → Time Format`.

## Chronomètre

1. Appuyez sur <kbd>OK</kbd> pour démarrer ; le temps écoulé s'affiche au format `MM:SS`.
2. Appuyez de nouveau sur <kbd>OK</kbd> pour arrêter, encore une fois pour reprendre.
3. Appuyez sur <kbd>←</kbd> (**Reset**) pour le remettre à zéro.

## Alarme quotidienne

1. Sur l'écran de l'horloge, appuyez sur <kbd>→</kbd>.
2. Mettez **Alarm** sur **ON** avec <kbd>←</kbd> / <kbd>→</kbd>.
3. Sélectionnez **Set time** et appuyez sur <kbd>OK</kbd>.
4. Dans le sélecteur `Alarm time` : <kbd>←</kbd> / <kbd>→</kbd> choisissent les heures, les minutes (et AM/PM en mode
   12 heures), <kbd>↑</kbd> / <kbd>↓</kbd> changent la valeur (maintenez pour répéter). <kbd>OK</kbd> ou
   <kbd>Back</kbd> enregistre.
5. Appuyez sur <kbd>Back</kbd> pour revenir à l'horloge. L'heure de l'alarme est affichée sur l'écran de l'horloge.

Lorsque l'alarme se déclenche, l'écran fait clignoter `! ALARM !` avec `Press any key to stop`, une mélodie est jouée
avec le vibreur et la LED rouge. Appuyez sur n'importe quelle touche pour l'arrêter. L'alarme reste armée et se
redéclenche le lendemain à la même heure.

::: warning
L'alarme ne sonne que si l'application Horloge est ouverte. Laissez le Flipper sur son chargeur avec l'horloge
ouverte pendant la nuit.
:::

L'alarme et le niveau de luminosité sont enregistrés dans `/ext/apps_data/clock/` et restaurés à la prochaine
ouverture de l'application.

## Pages liées

- [Bureau](/fr/start/desktop)
- [Paramètres](/fr/start/settings)
- [Applications fournies avec Unleashed](/fr/apps/catalog)
