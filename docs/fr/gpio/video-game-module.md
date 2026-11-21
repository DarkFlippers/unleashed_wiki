---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

Le **Video Game Module** (VGM) est un accessoire officiel construit autour du **Raspberry Pi RP2040**. Il se branche
sur le connecteur GPIO et ajoute :

- une sortie **Video Out** — recopie l'écran du Flipper sur un téléviseur ou un moniteur (signal DVI-D, 640×480) ;
- un **capteur de mouvement 6 axes** (TDK ICM-42688-P : gyroscope 3 axes + accéléromètre) pour les commandes
  gyroscopiques ;
- un **port USB-C** relié au RP2040 (flashage, ou utilisé par un firmware personnalisé) ;
- une **sortie GPIO à 14 broches** du RP2040 ;
- des **boutons BOOT / RESET** (à presser avec un trombone) pour le mode flash UF2 et la réinitialisation ;
- une LED RGB sur le dessus.

Il peut aussi fonctionner comme carte RP2040 autonome, compatible avec les projets Raspberry Pi Pico.

![Boutons et connecteurs du Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Installation et connexion à un téléviseur

1. **Mettez le module en place.** Il est livré avec un pare-chocs en silicone conçu pour un Flipper *sans* coque. Si
   votre Flipper est dans une coque en silicone, retirez le pare-chocs du module (ou la coque du Flipper).
2. **Firmware.** Le module nécessite un firmware Flipper 0.98.3 ou ultérieur ; les releases Unleashed actuelles
   conviennent.
3. **Vérifiez le réglage de l'UART :** `Main Menu → Settings → Expansion Modules → Listen UART` doit être sur
   **`USART`**. Avec toute autre valeur, le module n'est pas détecté. (Voir
   [Modules d'extension](/fr/gpio/expansion-modules).)
4. Branchez le module (Flipper éteint), allumez. Le Flipper détecte le module et le prépare automatiquement.
5. Reliez le câble du téléviseur au port **Video Out** du module et sélectionnez cette entrée sur le téléviseur.

### « Video Game Module not initialized »

Ce texte sur le téléviseur signifie que le module ne dialogue pas avec un Flipper : le firmware est trop ancien,
`Listen UART` n'est pas sur `USART`, ou le module est alimenté (par USB par exemple) sans Flipper rattaché.

## Jeux et applications

Le capteur de mouvement est exploité par des applications du catalogue Flipper Apps, par exemple
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) et [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(souris gyroscopique pour ordinateur).

::: tip Unleashed
Le moteur JavaScript d'Unleashed inclut un module `vgm` (fonctionnalité JS `vgm`) : `getPitch()`, `getRoll()`,
`getYaw()` et `deltaYaw(angle, timeout)` lisent l'orientation du module depuis un script et renvoient `undefined` si
aucun VGM n'est présent. Voir la section [Développement](/fr/dev/) pour les applications JavaScript.
:::

## Mettre à jour le firmware du module

Les mises à jour s'installent avec l'application **Video Game Module Tool** (du catalogue Flipper Apps). Son menu :

- `Install Official Firmware` — le dernier firmware officiel du module, livré avec l'application ;
- `Install Firmware from File` — un `.uf2` personnalisé depuis la carte SD.

Pour mettre à jour :

1. Installez (ou **mettez d'abord à jour**) Video Game Module Tool : dans l'application mobile Flipper, allez dans
   **Apps**, cherchez *Video Game Module Tool*, touchez **INSTALL** / **UPDATE**. Un nouveau firmware de module arrive
   avec une nouvelle version de l'application : mettez donc toujours l'application à jour avant le module.
2. Connectez le module au Flipper.
3. Ouvrez `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Sélectionnez `Install Official Firmware`, confirmez avec `Install` (<kbd>→</kbd>).
5. Attendez le message **Video Game Module Updated**.

## Firmware personnalisé

Le module peut exécuter votre propre firmware RP2040.

### Depuis le Flipper Zero

Permet de conserver plusieurs firmwares de module sur la carte SD et d'en changer sans ordinateur.

1. Copiez le fichier `.uf2` sur la carte SD du Flipper (par exemple avec [qFlipper](/fr/mobile/qflipper) :
   `File manager → SD Card`, créez un dossier, envoyez le fichier).
2. Connectez le module, ouvrez
   `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Sélectionnez le fichier et confirmez avec `Install` (<kbd>→</kbd>). Attendez **Video Game Module Updated**.

::: warning Limitations de l'UF2 lors d'une installation via le Flipper
- Les blocs hors flash ne sont pas pris en charge.
- Les charges utiles des blocs doivent faire exactement 256 octets.
- Les adresses cibles des charges utiles doivent être alignées sur 256 octets, sans trous.
- Les conteneurs de fichiers et les balises d'extension ne sont pas pris en charge.
:::

### Depuis un ordinateur

1. Débranchez le module du Flipper et de l'USB.
2. Maintenez le bouton **BOOT** du module avec un trombone.
3. Connectez le module à l'ordinateur en USB-C. Il se monte comme un disque USB nommé **RPI-RP2**. Relâchez **BOOT**.
4. Glissez le fichier `.uf2` sur **RPI-RP2**. Le module redémarre et se démonte de lui-même.

## Détails matériels (pour un usage autonome)

### GPIO du RP2040

- Les GPIO **8–15** et **18–20** servent à la sortie vidéo et ne sont pas disponibles sur les connecteurs.
- Les GPIO **0–7, 16, 17, 21, 22, 26–28** sont sur les connecteurs (comme sur un Raspberry Pi Pico). Les GPIO **2–7**
  sont également reliés au capteur de mouvement.
- Les GPIO **23–25 et 29** (utilisés en interne sur un Pico) sont libres sur le VGM et accessibles sur la sortie à
  14 broches.

![Brochage de la sortie 14 broches du Video Game Module](/img/remote/b030c6a0375c6254.png)

![Brochages du Video Game Module et du Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Périphériques accessibles au RP2040

- **Video Out :** vidéo et son vers un téléviseur/moniteur, ainsi qu'échange de données via le
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C :** périphérique ou hôte USB (pas d'USB Power Delivery).
- **IMU :** TDK ICM-42688-P.
- **Sortie GPIO :** 11 broches GPIO avec protection contre les décharges électrostatiques.
- **Connecteur vers le Flipper Zero :** les broches 13 et 14 du Flipper sont pleinement fonctionnelles ; les broches
  2–7 ont des fonctionnalités limitées (partagées avec l'IMU). Protégé contre les décharges électrostatiques.
- **LED RGB**, pilotée depuis un GPIO du RP2040.

### Alimentation

- 5 V par USB-C en usage autonome ;
- 3,3 V (broche 9) ou 5 V (broche 1) depuis le Flipper.

Alimenter en USB-C et depuis le Flipper en même temps est sans danger pour le module comme pour les deux sources.

Les schémas, les plans d'assemblage du PCB et les brochages en PDF sont sur la page officielle
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Pages liées

- [Modules d'extension](/fr/gpio/expansion-modules)
- [Brochage GPIO](/fr/gpio/pinout)
- [Modules externes](/fr/gpio/external-modules)
