---
title: Brochage GPIO
order: 10
original: [https://docs.flipper.net/zero/gpio-and-modules, https://docs.flipper.net/zero/development/hardware/tech-specs, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/f7/furi_hal/furi_hal_resources.c]
sources: [flipper-docs, unleashed-src]
---
# Brochage GPIO

Le Flipper Zero possède un connecteur de 18 broches au pas de 2,54 mm sur son bord supérieur. Il porte des sorties
d'alimentation, la masse, 13 broches d'entrée/sortie reliées au microcontrôleur STM32WB55, les lignes de débogage SWD
et la ligne 1-Wire partagée avec l'iButton.

![Fonctions des broches GPIO du Flipper Zero](/img/remote/b75cf29833cf8de8.jpg)

## Tableau des broches

Les numéros de broches sont comptés à partir de la **broche 1 (+5 V)**. Les noms de ports (`PA7`, `PC0`, …) sont ceux
que le firmware utilise à l'écran et dans le CLI.

| Broche | Nom | Fonctions principales | Remarques |
|---|---|---|---|
| 1 | +5V | sortie d'alimentation 5 V | Coupée sur batterie jusqu'à activation, voir ci-dessous |
| 2 | PA7 | SPI MOSI, PWM (TIM1), ADC | MOSI du CC1101 / NRF24 externe |
| 3 | PA6 | SPI MISO, ADC | MISO du CC1101 / NRF24 externe |
| 4 | PA4 | SPI CS, PWM (LPTIM2), ADC | CS du CC1101 / NRF24 externe ; broche DE/RE du pont USB-UART |
| 5 | PB3 | SPI SCK | SCK du CC1101 / NRF24 externe |
| 6 | PB2 | GPIO | GDO0 du CC1101 externe, CE du NRF24 |
| 7 | PC3 | GPIO, ADC | contrôle de l'amplificateur du CC1101 externe |
| 8 | GND | Masse | |
| 9 | 3V3 | sortie d'alimentation 3,3 V | Activée par défaut |
| 10 | PA14 | SWCLK | Débogage (SWD) |
| 11 | GND | Masse | |
| 12 | PA13 | SWDIO | Débogage (SWD) |
| 13 | PB6 | USART TX | UART par défaut pour le pont USB-UART, les logs, les modules d'extension |
| 14 | PB7 | USART RX | |
| 15 | PC1 | LPUART TX, I2C SDA, ADC | Second UART ; données I2C externes |
| 16 | PC0 | LPUART RX, I2C SCL, ADC | Second UART ; horloge I2C externe |
| 17 | PB14 | 1-Wire | ligne iButton |
| 18 | GND | Masse | |

Le firmware marque les broches 10, 12, 13, 14 et 17 comme **broches de débogage** : elles sont masquées dans
`GPIO Manual Control`, et la commande CLI `gpio` ne les liste qu'avec le mode Debug activé (et demande confirmation
avant de les modifier).

![Brochage GPIO détaillé du Flipper Zero](/img/remote/e77df2d4499cbbbc.jpg)

Un PDF imprimable du brochage est disponible sur la
[page GPIO officielle](https://docs.flipper.net/zero/gpio-and-modules).

## Limites électriques

- **Niveau logique :** CMOS 3,3 V. Chaque broche d'E/S rejoint le MCU à travers une résistance de 51 Ω et est
  protégée contre les décharges électrostatiques.
- **Courant par broche :** jusqu'à 20 mA.
- **Total sur les broches d'E/S :** restez en dessous de 5 W, sinon la protection de la batterie peut se déclencher et
  le Flipper s'éteint.
- **Tolérance 5 V :** uniquement pour une broche configurée en **entrée**. Une broche configurée en sortie n'est pas
  tolérante au 5 V. Évitez les périphériques en logique 5 V, sauf avec un adaptateur de niveau. Détails : note
  d'application ST
  [AN4899](https://www.st.com/resource/en/application_note/dm00315319-stm32-gpio-configuration-for-hardware-settings-and-lowpower-consumption-stmicroelectronics.pdf).

### +3,3 V (broche 9)

- Activée par défaut, charge maximale **1,2 A**.
- La carte microSD est alimentée par le même rail. La broche 9 est brièvement coupée pendant les mises à jour du
  firmware et au moment du montage de la carte.

::: warning
Ne connectez des modules à forte charge capacitive que lorsque le Flipper est éteint, sous peine de corrompre les
données de la carte microSD.
:::

### +5 V (broche 1)

- Depuis l'USB : lorsqu'un câble est branché, la broche 1 est alimentée directement par l'USB. Ne tirez jamais plus de
  **1,2 A**.
- Depuis la batterie : la sortie est **coupée par défaut**. Le convertisseur élévateur (OTG) fournit jusqu'à **1,2 A**
  lorsqu'il est activé.

Pour activer le 5 V en fonctionnement sur batterie :

1. Ouvrez `Main Menu → GPIO`.
2. Sélectionnez `5V on GPIO` et passez-le sur `ON` avec <kbd>→</kbd>.

Autres façons de le commuter :

- CLI : `power 5v 1` / `power 5v 0` (voir [CLI](/fr/dev/cli)).
- `Infrared → GPIO Settings → 5V on GPIO` pour les modules IR externes.
- Des applications comme Sub-GHz (CC1101 externe) et [SIM800](/fr/gpio/sim800) le demandent automatiquement, et un
  [module d'extension](/fr/gpio/expansion-modules) peut le réclamer via son protocole.

::: tip Comment le firmware gère le 5 V
Si vous demandez le 5 V alors que l'alimentation USB est présente, le service d'alimentation diffère l'activation du
convertisseur élévateur et l'active de lui-même dès que l'USB est débranché. Si le chargeur signale un défaut OTG
(surcharge ou court-circuit), le 5 V est coupé et la demande est effacée : vous devez donc la refaire.
:::

## Les broches en mode DFU

En mode DFU (bootloader), les broches d'E/S, à l'exception de la broche 17, changent d'état conformément à la note
STMicroelectronics
[AN2606](https://www.st.com/resource/en/application_note/cd00167594-stm32-microcontroller-system-memory-boot-mode-stmicroelectronics.pdf)
(tableau « STM32WB30xx/35xx/50xx/55xx configuration in system memory boot mode »). Gardez-le en tête si un module réagit
aux niveaux des broches pendant une [restauration](/fr/start/recovery) du Flipper.

## Insérer un module

- **Sans coque en silicone :** enfoncez le module à fond pour qu'aucune broche ne soit visible entre le Flipper et le
  module. Il faut parfois forcer un peu.
- **Avec une coque en silicone :** enfoncez-le jusqu'à ce qu'il n'y ait plus de jeu au milieu entre la coque et le
  module.

![Module enfoncé à fond](/img/remote/52e7045a797ed1c4.png)

## Pages liées

- [Application GPIO](/fr/gpio/gpio-app)
- [Modules externes](/fr/gpio/external-modules)
- [Schémas du Flipper Zero](https://docs.flipper.net/zero/development/hardware/schematic)
