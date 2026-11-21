---
title: ESP32 et Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 et Wi-Fi

Le Flipper Zero n'a pas de Wi-Fi propre. Les outils Wi-Fi proviennent d'une carte **ESP32** (ou ESP8266) placée sur le
connecteur GPIO, qui assure le travail radio et dialogue avec une application du Flipper via l'UART. Cette page est un
panorama des options et des outils web Unleashed qui les accompagnent.

## Quelle carte

| Carte | Usage typique |
|---|---|
| **Wi-Fi Developer Board officielle** (ESP32-S2) | Livrée avec le firmware de sonde de débogage Black Magic pour le [débogage](/fr/gpio/devboard). Peut être reflashée avec Marauder |
| **Cartes ESP32 Marauder** (diverses cartes ESP32 / ESP32-S2 / ESP32-S3, cartes combinées) | Balayage Wi-Fi et BLE, capture de paquets, wardriving |
| **Cartes ESP8266** | Firmwares Wi-Fi Scanner et Deauther |
| **ESP32-CAM** | Camera Suite (image de la caméra sur l'écran du Flipper) |

## Apps

Chacune n'est que le côté Flipper : la carte doit d'abord recevoir le firmware correspondant.

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Interface pour le firmware Marauder : scan Wi-Fi et BLE, capture de paquets, wardriving |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Liste les réseaux Wi-Fi proches, pour le firmware Scanner sur ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Interface pour le firmware DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Image en direct d'une ESP32-CAM sur l'écran du Flipper, avec prise de photo |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Une deuxième app ESP32-CAM : image en direct et photos |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Interface pour le firmware Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Monte sur l'ESP32 un point d'accès avec portail captif |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Pour le firmware Deauther v2 de @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Flashe un firmware sur une carte ESP depuis le Flipper, par UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Déclenche un webhook IFTTT via un ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Cartographie des réseaux Wi-Fi avec un ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Affiche le visage et l'état d'un Pwnagotchi sur le Flipper, par UART |

Liste complète des apps de modules : [Les modules et leurs apps](/fr/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder), de justcallmekoko, est un firmware pour cartes
ESP32. Sur le Flipper, on l'utilise via l'application **WiFi Marauder** des packs d'applications extra, qui envoie des
commandes à la carte et affiche sa sortie.

Déroulement typique :

1. **Flashez Marauder** sur la carte ESP32 (voir le flasher ci-dessous).
2. Éteignez le Flipper, branchez la carte sur le connecteur GPIO, rallumez.
3. Ouvrez l'application Marauder sous `Apps → GPIO` et choisissez une commande (balayer les points d'accès, sniffer,
   wardriving, etc.).
4. Les résultats sont affichés dans l'application ; les captures et les journaux de wardriving sont stockés selon les
   réglages de la carte et de l'application (voir la documentation Marauder de votre carte).

Guide d'utilisation complet de la Wi-Fi Devboard avec Marauder (par UberGuidoZ) :
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Aspect légal
Le balayage est passif, mais la désauthentification et les autres attaques Wi-Fi actives sont illégales contre des
réseaux qui ne vous appartiennent pas ou que vous n'êtes pas autorisé à tester.
:::

## ESP32 Web Flasher

::: tip Unleashed
L'équipe Unleashed met à disposition un outil de flashage dans le navigateur pour les modules ESP32 courants :
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Il fonctionne entièrement dans le navigateur,
vous n'avez donc pas besoin d'installer esptool. Utilisez un navigateur prenant en charge Web Serial (navigateurs
basés sur Chromium).
:::

Étapes générales :

1. Débranchez la carte ESP32 du Flipper et connectez-la à l'ordinateur en USB.
2. Si la carte ne passe pas d'elle-même en mode flashage, maintenez **BOOT**, appuyez brièvement sur **RESET**,
   relâchez **BOOT**.
3. Ouvrez le flasher, choisissez la carte et le firmware, cliquez sur connecter et sélectionnez le port série de la
   carte.
4. Attendez la fin du flashage, réinitialisez la carte, rebranchez-la sur le Flipper (Flipper éteint).

Autres façons de flasher une carte ESP :

- L'application Flipper **ESP flasher** — flashe un `.bin` depuis la carte SD du Flipper via l'UART du GPIO :
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Guide Windows pour esptool / Flash Download Tool :
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- Le [pont USB-UART de l'application GPIO](/fr/gpio/gpio-app) avec `RTS/DTR Pins` peut servir d'adaptateur USB pour
  les cartes dépourvues de port USB.

::: tip Revenir au firmware de débogage
Si vous avez mis Marauder sur la Wi-Fi Devboard officielle et que vous voulez retrouver le débogueur Black Magic,
reflashez-la avec `ufbt devboard_flash` comme décrit dans
[Dev board : mise à jour du firmware](/fr/gpio/devboard-firmware).
:::

## Wi-Fi Wardriving Map

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** combine et affiche sur une seule carte plusieurs
captures de wardriving au format WiGLE issues d'ESP32 Marauder et d'autres outils.
:::

1. Réalisez un wardrive avec Marauder (le wardriving nécessite un module GPS connecté à la carte ESP32).
2. Copiez les journaux CSV au format WiGLE sur votre ordinateur.
3. Ouvrez la carte et chargez un ou plusieurs fichiers ; les réseaux sont tracés ensemble.

Pour les captures Sub-GHz et les autres fichiers contenant des coordonnées, il existe une carte distincte,
[map.unleashedflip.com](https://map.unleashedflip.com).

## Autres firmwares ESP

| Firmware | Carte | Liens |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Utilisation](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Utilisation](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Utilisation](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Les applications Flipper correspondantes se trouvent dans les packs Base/Extra :
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Dépannage

- **L'application n'obtient aucune réponse de la carte :** la carte n'est pas flashée avec le firmware attendu par
  l'application, TX/RX sont sur le mauvais UART, ou la carte n'est pas enfoncée à fond.
- **Comportement étrange sur l'UART :** une autre fonction écoute sur les mêmes broches. Vérifiez
  `Settings → Expansion Modules → Listen UART` (voir [Modules d'extension](/fr/gpio/expansion-modules)) et
  `Settings → System → Log Device`.
- **La carte n'est pas détectée par le flasher web :** utilisez un câble USB transportant les données, passez en mode
  bootloader manuellement, essayez un autre port USB ou un autre navigateur.

## Pages liées

- [Wi-Fi Devboard](/fr/gpio/devboard)
- [Modules externes](/fr/gpio/external-modules)
- [GPS](/fr/gpio/gps)
