---
title: Combinaisons de touches
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Combinaisons de touches

Il arrive que le Flipper ne réponde plus à cause d'un problème logiciel. Ces combinaisons de boutons le
réinitialisent au niveau matériel ou le démarrent en mode DFU (mise à jour du firmware), sans l'aide du firmware figé.

## Aide-mémoire

| Objectif | Combinaison | USB |
|---|---|---|
| Redémarrer un Flipper figé | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | indifférent |
| Coupure d'alimentation | <kbd>BACK</kbd>, 30 s | **débranché** |
| DFU via le bootloader Flipper (avec indication) | <kbd>←</kbd> + <kbd>BACK</kbd>, relâcher <kbd>BACK</kbd>, maintenir <kbd>←</kbd> jusqu'à la LED bleue | indifférent |
| DFU via le bootloader ST (sans indication) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, relâcher <kbd>BACK</kbd> et <kbd>←</kbd> | indifférent |
| Écran de réinitialisation du PIN / des réglages | maintenir <kbd>↑</kbd> pendant le démarrage du Flipper | — |

## Combinaisons de base

### Réinitialisation matérielle

1. Maintenez <kbd>←</kbd> et <kbd>BACK</kbd> enfoncés pendant deux secondes environ.
2. Relâchez les deux boutons.

Cela tire vers le bas la ligne de reset du microcontrôleur. Chemin : touches → DD8 (NC7SZ32M5X, porte OU) → DD1
(STM32WB55, MCU).

**Ne fonctionne pas si :** le bloc de debug du MCU est actif et maintient la ligne de reset depuis l'intérieur.

### Coupure matérielle de l'alimentation

1. Débranchez le câble USB et toute alimentation externe. Vérifiez deux fois que l'USB est réellement débranché.
2. Maintenez <kbd>BACK</kbd> enfoncé pendant **30 secondes**. Cela ne fonctionne qu'avec l'USB débranché.
3. Relâchez <kbd>BACK</kbd>.

Cela coupe puis rétablit la ligne d'alimentation SYS via la puce de charge DD6 (bq25896).

**Ne fonctionne pas si :** une alimentation est connectée à l'USB ou à 5V_ext.

### DFU logiciel

Maintenez <kbd>←</kbd> pendant le démarrage du Flipper. Il entre en mode DFU via le **bootloader Flipper**.

**Ne fonctionne pas si :** le bootloader Flipper est endommagé ou absent.

### DFU matériel

Maintenez <kbd>OK</kbd> pendant le démarrage du Flipper. Il entre en mode DFU via le **bootloader ST** intégré au MCU.

**Ne fonctionne pas si :** les Option Bytes sont endommagés ou configurés pour ignorer la touche <kbd>OK</kbd>.

## Combinaisons DFU

### Réinitialisation matérielle + DFU logiciel

1. Maintenez <kbd>←</kbd> + <kbd>BACK</kbd> pendant deux secondes environ.
2. Relâchez <kbd>BACK</kbd>.
3. L'appareil entre en DFU **avec indication** : LED bleue et écran DFU.
4. Relâchez <kbd>←</kbd>.

**Ne fonctionne pas si :** le bloc de debug du MCU maintient la ligne de reset, ou si le bootloader Flipper est
endommagé ou absent.

### Réinitialisation matérielle + DFU matériel

1. Maintenez <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> pendant deux secondes environ.
2. Relâchez <kbd>BACK</kbd> et <kbd>←</kbd>.
3. L'appareil entre en DFU **sans indication**. L'écran reste éteint : c'est normal.

**Ne fonctionne pas si :** le bloc de debug du MCU maintient la ligne de reset, ou si les Option Bytes sont endommagés
ou configurés pour ignorer <kbd>OK</kbd>.

### Coupure matérielle de l'alimentation + DFU logiciel

1. Débranchez l'USB et toute alimentation externe.
2. Maintenez <kbd>BACK</kbd> + <kbd>←</kbd> pendant 30 secondes.
3. Relâchez <kbd>BACK</kbd>.
4. L'appareil entre en DFU avec indication (LED bleue + écran DFU).
5. Relâchez <kbd>←</kbd>.
6. Branchez l'USB.

**Ne fonctionne pas si :** une alimentation est connectée à l'USB ou à 5V_ext, ou si le bootloader Flipper est
endommagé ou absent.

### Coupure matérielle de l'alimentation + DFU matériel

1. Débranchez l'USB et toute alimentation externe.
2. Maintenez <kbd>BACK</kbd> + <kbd>OK</kbd> pendant 30 secondes.
3. Relâchez <kbd>BACK</kbd> et <kbd>OK</kbd>.
4. L'appareil entre en DFU sans indication.
5. Branchez l'USB.

**Ne fonctionne pas si :** une alimentation est connectée à l'USB ou à 5V_ext, ou si les Option Bytes sont endommagés
ou configurés pour ignorer <kbd>OK</kbd>.

## Que faire en mode DFU

Connectez le Flipper à un ordinateur. Il apparaît comme **DFU in FS Mode** (Windows/macOS) ou
**STMicroelectronics STM Device in DFU Mode** (`lsusb` sous Linux). Réparez ensuite le firmware avec qFlipper :
[Restauration](/fr/start/recovery#firmware-recovery).

## Si rien n'y fait {#if-nothing-helps}

- Assurez-vous que la batterie est chargée : laissez l'appareil sur un chargeur pendant une heure.
- Débranchez la batterie puis rebranchez-la (il faut ouvrir le boîtier).
- Flashez l'appareil avec un ST-Link ou un autre programmateur SWD.

Si l'appareil ne fonctionne toujours pas après tout cela, le problème n'est **pas logiciel**.
