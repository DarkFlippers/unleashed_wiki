---
title: Applications mobiles et de bureau
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Applications mobiles et de bureau

Le Flipper fonctionne très bien tout seul, mais un ordinateur ou un téléphone simplifie nettement certaines tâches :
installer et mettre à jour le firmware, copier des fichiers, installer des applications, sauvegarder vos clés et vos
télécommandes, piloter le Flipper à distance.

| Outil | Plateformes | Utile pour |
|---|---|---|
| [qFlipper](/fr/mobile/qflipper) | Windows, macOS, Linux | installer Unleashed depuis un `.tgz`, gestionnaire de fichiers, sauvegarde / restauration, recovery |
| [Application mobile Flipper](/fr/mobile/mobile-app) | iOS, Android | mise à jour par Bluetooth (y compris avec votre propre `.tgz`), archive des clés, catalogue d'applications, télécommande |
| [qUnleashed](/fr/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | l'application maison d'Unleashed : mises à jour du firmware par BLE ou USB, archive, catalogue d'applications, écran déporté, CLI, récupération du Seed |
| [Outils web](/fr/mobile/web-tools) | navigateur | Web Installer, carte Sub-GHz et coordonnées, carte de wardriving Wi-Fi, flasheur ESP32, Flipper Lab |

::: tip Unleashed
Unleashed est entièrement compatible avec le qFlipper officiel et l'application mobile Flipper officielle. Le moyen
le plus rapide d'installer ou de mettre à jour Unleashed reste le
[Web Installer](/fr/mobile/web-tools#unleashed-web-installer) dans un navigateur Chromium.
:::

::: warning Une seule connexion à la fois
Un seul programme peut utiliser le port série USB du Flipper. Fermez qFlipper avant d'utiliser Flipper Lab, le
Web Installer, un terminal CLI ou U2F, et ne gardez qu'un seul onglet Flipper Lab ouvert.
:::

## Pages de cette section

- [qFlipper](/fr/mobile/qflipper)
- [Application mobile Flipper](/fr/mobile/mobile-app)
- [Application compagnon qUnleashed](/fr/mobile/qunleashed-app)
- [Outils web](/fr/mobile/web-tools)
