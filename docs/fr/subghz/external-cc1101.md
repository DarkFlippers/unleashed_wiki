---
title: Module CC1101 externe
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# Module CC1101 externe

La radio Sub-GHz intégrée au Flipper est une puce CC1101 avec une petite antenne interne. Vous pouvez brancher une seconde carte CC1101 sur le connecteur GPIO et faire en sorte que l'application Sub-GHz (et les applications système Sub-GHz) l'utilisent à la place. Les cartes externes disposent généralement d'une véritable antenne SMA et souvent d'un amplificateur de puissance : elles portent donc beaucoup plus loin, en réception comme en émission.

**Quand l'utiliser :** la télécommande ou le récepteur est éloigné, l'antenne interne ne capte pas une télécommande faible, ou vous avez besoin de plus de portée en émission. Pour trouver la fréquence d'une télécommande, continuez d'utiliser la radio interne (voir [Frequency Analyzer](/fr/subghz/frequency-analyzer)).

::: tip Fonctionne sur tous les firmwares
Les modules radio externes fonctionnent sur tous les firmwares, y compris celui d'origine. La première implémentation est celle de @quen0n pour Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)) ; celle utilisée aujourd'hui a été écrite par **Skorp** dans le firmware officiel, et c'est celle-là qu'Unleashed reprend.
:::

## Câblage

Le module communique via le bus SPI externe du Flipper. Le câblage standard est le suivant :

| Broche CC1101 | GPIO Flipper | Broche du connecteur |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 ou 18 |
| Commande amplificateur / LED (modules E07) | PC3 | 7 |

Pour les cartes prêtes à l'emploi, les schémas et les photos, voir le guide de quen0n : [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (lié depuis la FAQ d'Unleashed). La numérotation du connecteur se trouve sur la page [Brochage GPIO](/fr/gpio/pinout) ; les autres cartes d'extension sont sur [Modules externes](/fr/gpio/external-modules).

::: warning
N'alimentez le module qu'en **3,3 V**. Le CC1101 n'est pas une puce 5 V.
:::

## Passer au module externe

1. Branchez le module avec le Flipper éteint, ou au moins sans aucune application Sub-GHz en cours d'exécution.
2. Ouvrez `Main Menu → Sub-GHz → Radio Settings`.
3. Sur la ligne **Module**, appuyez sur <kbd>→</kbd> pour passer de `Internal` à `External`.
4. Appuyez sur <kbd>←</kbd> (Back) et utilisez `Read`, `Read RAW`, `Saved`, etc. comme d'habitude.

À quoi s'attendre :

- La ligne **Module** ne propose `External` que si un module est réellement détecté. Si rien n'est branché, la ligne n'a qu'une seule valeur, `Internal`.
- Le firmware sonde le module au moment où vous le sélectionnez. Si le test échoue, il retombe sur la radio interne et la ligne affiche à nouveau `Internal` — ce que vous voyez correspond donc bien à ce qui est réellement utilisé.
- Sur l'écran d'émission d'un signal enregistré, la ligne du bas affiche `R: Int` ou `R: Ext` — la radio qui va émettre.
- Les applications système Sub-GHz ([Nice O-Code](/fr/subghz/nice-o-code), [Seed Capturer](/fr/subghz/seed-capturer), [Security+ PIN](/fr/subghz/secplus-pin)) affichent `Int` ou `Ext` dans leur en-tête et utilisent automatiquement un module externe lorsqu'il est branché.

## Autres entrées de Radio Settings

`Sub-GHz → Radio Settings` contient :

| Entrée | Valeurs | Rôle |
|---|---|---|
| Module | `Internal` / `External` | radio utilisée par l'application Sub-GHz |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | remplace la puissance d'émission du preset ; `Preset` conserve la puissance définie par le preset de modulation |
| Protocol Names | `OFF` / `ON` | voir [Réglages](/fr/subghz/settings) |
| Counter Incr. | `+1`… | voir [Réglages](/fr/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **mode debug uniquement** — piloter la broche de commande amplificateur / LED (PC3, broche 7 du connecteur) des modules de type E07 |
| Debug Pin | `OFF` / `17(1W)` | **mode debug uniquement** — recopier le signal sur la broche 17 pour le développement de protocoles |

`Ext Amp & LEDs` est **sur ON par défaut**. Lorsqu'il est actif, le firmware n'active l'amplificateur du module sur PC3 que pendant que la puce émet réellement. Ne le désactivez que si votre module utilise la broche 7 pour autre chose ; l'entrée du menu apparaît quand le mode debug est activé dans `Settings → System`.

## Module 1 W haute puissance (en test)

Début 2025, @gromovyna a partagé ses essais d'un nouveau module Sub-GHz beaucoup plus puissant, réalisé par quen0n (membre de l'équipe Unleashed) :

- Au moment de ces publications, c'était le seul exemplaire existant, avec une puissance d'émission **allant jusqu'à 1 W**.
- Il est construit sur une puce différente du CC1101 — personne n'avait jamais rien construit sur cette puce auparavant.
- La prise en charge par le firmware **n'était pas encore terminée** ; elle était développée pour Unleashed en collaboration avec Flipper Market, et gromovyna faisait office de testeur.

![Module haute puissance à côté d'une carte CC1101](/img/remote/29279ff04df77e30.jpg)

Ses résultats empiriques (sans mesure de puissance) :

- Le module est bien plus puissant que tout ce qu'il avait vu à base de CC1101.
- En ville, en émettant depuis un appartement avec un autre immeuble en travers, il a envoyé un signal **Hollarm** à **600 m** à l'horizontale.
- La même distance a été atteinte avec l'antenne fournie comme avec une antenne de talkie-walkie recommandée par MMX et quen0n — même si, avec l'antenne de talkie-walkie, l'ensemble n'est « absolument pas portable ».
- Un éventuel avantage en *réception* par rapport au CC1101 n'était pas encore établi.

![Le module avec une antenne de talkie-walkie](/img/remote/0998ad639bb38e82.jpg)

Ceci décrit un appareil en phase de test ; consultez les notes de version actuelles d'Unleashed pour connaître l'état de sa prise en charge.

::: warning
N'émettez que sur les fréquences et aux puissances légales là où vous vous trouvez, et uniquement vers votre propre matériel.
:::

## Dépannage

- **Impossible de sélectionner `External`** — le module n'est pas détecté : vérifiez le 3,3 V, la masse et les quatre lignes SPI (CSN, SCK, MOSI, MISO). Un fil CSN ou MISO mal branché est l'erreur la plus fréquente.
- **Repasse tout seul sur `Internal`** — le test a échoué quand le module a été sélectionné ; rebranchez le module et réessayez.
- **Reçoit bien mais la portée est mauvaise en émission** — sur les modules E07, l'amplificateur a besoin de la broche 7 (PC3) connectée et de `Ext Amp & LEDs` sur ON.
- **Le Frequency Analyzer affiche des détections aléatoires** — le module externe est bien plus sensible au bruit ; utilisez la radio interne pour l'analyse de fréquence.
- **Émission bloquée** — la fréquence est en dehors de la plage du CC1101 ; voir [Fréquences](/fr/subghz/frequencies).

## Pages liées

- [Réglages Sub-GHz](/fr/subghz/settings)
- [Fréquences](/fr/subghz/frequencies)
- [Brochage GPIO](/fr/gpio/pinout) · [Modules externes](/fr/gpio/external-modules)
