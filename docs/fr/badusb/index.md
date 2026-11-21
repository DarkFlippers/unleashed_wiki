---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

L'application **Bad USB** transforme le Flipper en clavier (et en souris) qui tape un script préparé à l'avance sur
un ordinateur. La machine hôte voit un périphérique HID (Human Interface Device) ordinaire : aucun pilote n'est
nécessaire. Les scripts sont écrits en **DuckyScript** étendu (le langage de l'USB Rubber Ducky) et stockés sous
forme de simples fichiers `.txt` sur la carte microSD.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Usages légitimes courants : automatiser une configuration répétitive sur vos propres machines, saisir de longs mots
de passe ou fichiers de configuration, installer des logiciels sur un PC neuf, faire des démonstrations et des
formations de sensibilisation à la sécurité.

::: danger Aspect légal
Un dispositif d'injection de frappes peut faire tout ce qu'une personne assise au clavier peut faire. N'exécutez des
scripts que sur des ordinateurs qui vous appartiennent ou que vous êtes explicitement autorisé à tester.
:::

L'application fonctionne via un câble **USB** ou via **Bluetooth (BLE)** ; dans ce dernier cas, elle apparaît à
l'hôte comme un clavier Bluetooth.

::: tip Unleashed
Unleashed intègre **BadKB** (de Willy-JL, ClaraCrazy et des contributeurs XFW) directement dans l'application
Bad USB :
- le **mode BLE**, avec nom de périphérique, adresse MAC, mode d'appairage et appairage persistant configurables,
  ainsi que les commandes de script `BLE_ID` / `BT_ID` ;
- les réglages d'**identité USB** : nom du fabricant et du produit, VID/PID, randomisation ;
- des **dispositions de clavier** pour de nombreuses langues ([par rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)) ;
- la commande **`DUCKY_LANG`**, qui permet à un script de choisir sa propre disposition de clavier (nouveauté de la version actuelle, PR #1224 par @ANTONiO-eagle).
:::

## Fichiers

| Chemin | Contenu |
|---|---|
| `/ext/badusb/` | Vos scripts (`.txt`). Le navigateur de fichiers de l'application s'ouvre ici. |
| `/ext/badusb/examples/` | Scripts de démonstration livrés avec le firmware (Windows, macOS, GNOME, ChromeOS, test de souris, installateurs qFlipper). |
| `/ext/badusb/assets/layouts/` | Fichiers de disposition de clavier (`.kl`). Voir [Dispositions de clavier](/fr/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | Réglages de l'application : disposition globale, mode USB/BLE, identité USB et BLE. |

Transférez vos scripts avec [qFlipper](/fr/mobile/qflipper), l'[application mobile](/fr/mobile/mobile-app) ou en les
copiant directement sur la carte SD. Un fichier portant le même nom est écrasé sans avertissement.

## Pages de cette section

| Page | Ce que vous y apprenez |
|---|---|
| [Utiliser le Bad USB](/fr/badusb/usage) | Exécuter des scripts via USB et BLE, le menu `Config`, tous les réglages |
| [Format des scripts](/fr/badusb/script-format) | Référence complète des commandes : STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, souris, ID, DUCKY_LANG… |
| [Exemples](/fr/badusb/examples) | Des scripts d'exemple sans risque pour démarrer |
| [Dispositions de clavier](/fr/badusb/layouts) | Quelles dispositions existent, comment elles fonctionnent, en choisir une par script |
