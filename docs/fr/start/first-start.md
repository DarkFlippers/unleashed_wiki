---
title: Premier démarrage
order: 10
original: [https://docs.flipper.net/zero/basics/first-start, https://docs.flipper.net/zero/basics/sd-card, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md]
sources: [flipper-docs, unleashed-docs]
---
# Premier démarrage

Ce qu'il faut faire pendant les dix premières minutes avec un Flipper Zero neuf, avant d'installer Unleashed.

## 1. Allumer l'appareil

Maintenez <kbd>BACK</kbd> enfoncé pendant environ 3 secondes. Le bureau apparaît, avec votre dauphin et la barre d'état :

![Le bureau du Flipper : l'animation du dauphin au repos et la barre d'état avec les icônes de carte SD et de batterie](/screens/desktop/idle.png)

::: details Le Flipper ne s'allume pas
- La batterie est peut-être complètement vide. Branchez le câble USB-C : l'appareil s'allume de lui-même au bout d'un moment.
- Si l'écran reste éteint, maintenez <kbd>←</kbd> + <kbd>BACK</kbd> pendant 5 secondes (redémarrage).
- Toujours rien : voyez [Combinaisons de touches](/fr/start/key-combos) et [Restauration](/fr/start/recovery).
:::

## 2. Insérer une carte microSD

Une carte microSD est **indispensable**. Elle contient les clés, les cartes, les télécommandes, les bases de données,
les applications livrées avec le firmware, et même le stockage « interne » (voir [Carte microSD](/fr/start/sd-card)).
La carte n'est pas fournie avec l'appareil.

1. Repérez le logement situé en bas du Flipper.
2. Tenez la carte **contacts vers le haut** et poussez-la jusqu'au clic.
3. La barre d'état affiche une icône de carte SD lorsque la carte est montée.

Une carte de marque de **16 à 32 Go** suffit largement. Les cartes jusqu'à 256 Go fonctionnent, mais les grandes
capacités mettent plus de temps à être montées. Les cartes bon marché sans marque peuvent rendre l'appareil lent ou
instable.

## 3. Installer Unleashed

Utilisez l'**[Unleashed Web Installer](https://web.unleashedflip.com)** : c'est la méthode la plus simple. Toutes les
méthodes sont décrites dans [Installer Unleashed](/fr/start/install).

## 4. Réglages de base

Après l'installation, ouvrez **Main Menu → Settings** et vérifiez :

- **Clock & Alarm** : réglez la date et l'heure ;
- **System → Hand Orient** : `Lefty` si vous tenez l'appareil dans la main gauche ;
- **Desktop** : code PIN, horloge sur le bureau (`Show Clock`), affichage de la batterie (`Battery View`), applications
  en accès rapide ;
- **Desktop → Change Flipper Name** : donnez un nom personnalisé à votre Flipper
  ([Nom personnalisé du Flipper](/fr/start/custom-name)).

Chaque entrée est décrite dans [Réglages](/fr/start/settings).

## Étapes suivantes

- Apprenez les boutons et les raccourcis : [Commandes](/fr/start/controls)
- Explorez le bureau : [Bureau](/fr/start/desktop)
- Découvrez les apports d'Unleashed : [Les apports d'Unleashed](/fr/start/unleashed-features)
