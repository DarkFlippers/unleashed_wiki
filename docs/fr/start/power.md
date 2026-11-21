---
title: Alimentation et batterie
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Alimentation et batterie

Le Flipper Zero embarque une batterie Li-Po de **2100 mAh**. Elle peut tenir jusqu'à un mois environ en veille et se
recharge en USB-C en deux heures environ.

## Allumage et extinction

- **Allumer :** maintenez <kbd>BACK</kbd> environ 3 s. Un Flipper complètement déchargé s'allume de lui-même dès que
  vous branchez l'USB.
- **Éteindre :** maintenez <kbd>BACK</kbd> sur le bureau. L'écran **Turn Off Device?** apparaît : <kbd>→</kbd>
  **Power Off** éteint l'appareil et <kbd>←</kbd> **Battery** ouvre les informations sur la batterie. Vous pouvez
  aussi passer par **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? avec le dauphin en pleurs, Battery sur le bouton de gauche et Power Off sur celui de droite](/screens/settings/power_off.png)

## Recharge

Branchez le câble USB-C sur un chargeur ou un ordinateur. L'icône de batterie affiche un éclair pendant la charge.
L'entrée de charge est de 5 V / 1 A, une charge complète prend donc environ 2 heures.

::: warning Stockage prolongé
Si vous n'allez pas utiliser le Flipper pendant longtemps, chargez-le à environ **50 %** avant de l'éteindre. Le
stocker complètement déchargé abîme la batterie. Conservez-le entre 0 et 40 °C.
:::

## Settings → Power

| Entrée | Rôle |
|---|---|
| **Battery Info** | Pourcentage de charge, tension, courant, température et état de santé de la batterie |
| **Reboot** | **Firmware Upgrade** (redémarrage en mode DFU) ou **Reboot Flipper** (redémarrage normal). Confirmez avec <kbd>→</kbd> **Reboot** |
| **Power OFF** | Éteindre l'appareil |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` : extinction après cette durée d'inactivité |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` : arrêter la charge à ce niveau |

![Settings → Power : Battery Info, Reboot, Power OFF, Auto PowerOff OFF, Limit Charge OFF](/screens/settings/power.png)

::: tip Limit Charge
`Limit Charge` est utile si le Flipper reste branché en USB la majeure partie de la journée, par exemple comme gadget
de bureau. Maintenir la batterie sous 100 % allonge sa durée de vie.
:::

## Écran Battery Info

L'écran affiche un message différent selon l'état :

| En-tête | Signification |
|---|---|
| `Yummy!` / `Charging at` | En charge. Affiche la tension USB et le courant de charge |
| `Om-nom-nom!` / `Consumption is` | Sur batterie, avec le courant consommé. `Oh no!` et `mA!` signalent une consommation élevée |
| `Charged!` | USB connecté, pas de charge en cours (batterie pleine) |
| `Charged!` / `Limited to` | USB connecté, et une limite de tension de charge autre que celle par défaut est active (affichée en V) |
| `Napping...` | Sur batterie, consommation quasi nulle |

L'écran indique aussi le pourcentage de batterie, la tension, la température (°C ou °F, selon
**Settings → System → Units**) et l'état de **santé** de la batterie en pourcentage.

![Battery Info : Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4.1 V, santé 100 %](/screens/settings/battery_info.png)

## Consommation

| Mode | Courant typique |
|---|---|
| Veille (méthode `Default`) | ~1,5 mA |
| Veille (méthode `Legacy`) | ~9 mA |
| Actif, rétroéclairage allumé | jusqu'à ~30 mA (jusqu'à ~50 mA avec une mauvaise carte SD) |
| Radio active | jusqu'à ~400 mA |
| Radio + module externe | jusqu'à ~2 A |

**Sleep Method** se trouve dans **Settings → System**. `Default` économise l'énergie. `Legacy` en consomme davantage
mais peut aider en cas de plantages en veille.

La veille exige **Debug** = `OFF` (**Settings → System**) et **Listen UART** = `None`
(**Settings → Expansion Modules**). Sinon l'appareil ne peut pas se mettre en veille et la batterie se vide plus vite.

## Conseils pour prolonger l'autonomie

- Gardez le firmware à jour.
- Désactivez le Bluetooth quand vous n'en avez pas besoin (`Lock Menu` → **Turn Bluetooth Off**).
- Réduisez **LCD Backlight** et **Backlight Time** dans **LCD and Notifications**.
- Utilisez une bonne carte microSD de marque.
- Réglez **Auto PowerOff**.
- Si la batterie se vide vite, vérifiez le courant dans **Battery Info**.

## Caractéristiques d'alimentation

| Paramètre | Valeur |
|---|---|
| Capacité de la batterie | 2100 mAh |
| Tension de fonctionnement de la batterie | 3,3–4,2 V |
| Temps de charge | ~2 heures |
| Tension / courant de charge | 5 V, 1 A |
| Connecteur | USB Type-C |
| Courant maximal depuis l'USB, appareils connectés inclus | 3 A |

## Pages liées

- Redémarrage et combinaisons de réinitialisation : [Combinaisons de touches](/fr/start/key-combos)
- L'appareil ne s'allume pas : [Restauration](/fr/start/recovery)
