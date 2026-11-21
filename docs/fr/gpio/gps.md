---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Il y a deux façons de donner une position au Flipper :

| Option | Matériel | Fonctionnement |
|---|---|---|
| **Service GPS (position du compagnon)** | Aucun : un téléphone ou un ordinateur connecté en USB ou en Bluetooth | Les applications demandent sa position à l'application compagnon connectée, via RPC |
| **Module GPS NMEA** | Un récepteur GPS série sur l'UART du GPIO | Le plugin `[NMEA] GPS` lit les trames NMEA envoyées par le module |

## Service GPS (position du compagnon)

::: tip Unleashed
Le firmware Unleashed contient un service système `gps` (record `gps`, démarré au boot). Il n'utilise aucune broche
GPIO : il transmet les demandes de position via la **session RPC** active (USB ou Bluetooth) à l'application
compagnon, qui répond avec la position du téléphone ou de l'ordinateur.
:::

Ce qu'une application en obtient :

| Champ | Unité |
|---|---|
| Latitude, longitude | degrés × 10⁷ |
| Cap | degrés × 100 (0…36000) |
| Vitesse | mm/s |
| Altitude | cm |
| Précision | mm |
| Satellites | nombre |

Les applications peuvent demander un point unique (`gps_request_location()`), un flux à **1–10 Hz**
(`gps_request_stream()` / `gps_stop_stream()`), et peuvent aussi renvoyer une position au compagnon
(`gps_report_location()`). Le compagnon peut répondre par une erreur : non pris en charge, pas d'autorisation,
localisation désactivée, erreur inconnue.

### Essayer

L'arborescence des sources comprend deux applications d'exemple de @apfxtech (catégorie `Examples`, compilées en
FAP) :

- **`[RPC] GPS Click`** — demande unique : appuyez sur <kbd>OK</kbd> pour obtenir la position ; affiche latitude,
  longitude, cap, vitesse, altitude, satellites et précision. <kbd>BACK</kbd> quitte.
- **`[RPC] GPS Stream`** — flux continu des mêmes données.

Messages que vous pouvez voir :

| Message | Signification |
|---|---|
| `No USB/BLE connection` | Pas de session RPC : connectez l'application compagnon en USB ou en Bluetooth |
| `GPS not available` | Le compagnon ne prend pas en charge la localisation |
| `Permission denied` | L'autorisation de localisation n'a pas été accordée à l'application compagnon |
| `Location disabled` | Les services de localisation sont désactivés sur le téléphone / l'ordinateur |
| `No response` | Le compagnon n'a pas répondu à temps |
| `Waiting for data...` | Le flux a démarré, pas encore de point |

L'application compagnon doit prendre en charge ces requêtes GPS RPC ; vérifiez la vôtre (voir
[Mobile](/fr/mobile/)).

Pour les développeurs d'applications : incluez `<gps/gps.h>` et ouvrez le record avec
`furi_record_open(RECORD_GPS)` ; l'en-tête fournit aussi des fonctions utilitaires pour mettre en forme les
coordonnées, le cap, la vitesse, l'altitude et la précision.

## Module GPS NMEA sur l'UART

Pour obtenir une position sans téléphone, connectez un récepteur GPS série (la plupart des modules qui émettent des
trames NMEA en logique 3,3 V).

Câblage (USART) :

| Broche du Flipper | Module GPS |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) ou 1 (5V) | VCC (vérifiez la plage d'alimentation du module) |
| 8, 11 ou 18 (GND) | GND |

Ouvrez ensuite le plugin `[NMEA] GPS` des packs d'applications extra. La configuration, le débit en bauds et les
modules pris en charge sont décrits dans son
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
Le module GPS et les autres utilisateurs de l'UART (cartes Wi-Fi, SIM800, modules d'extension, sortie des logs) se
partagent les broches 13/14. Si le plugin ne reçoit aucune donnée, vérifiez
`Settings → Expansion Modules → Listen UART` et `Settings → System → Log Device`.
:::

## Apps

Les apps qui fonctionnent avec un module GPS, toutes issues des packs :

| App | Pack | Ce qu'elle fait |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position depuis n'importe quel module GPS NMEA en UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Affiche et enregistre les données des modules GPS u-blox en I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Traceur NMEA avec navigation par points |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Explorateur qui trie vos fichiers par distance depuis l'endroit où vous êtes |

Liste complète des apps de modules : [Les modules et leurs apps](/fr/gpio/module-apps).

## Pages liées

- [ESP32 et Wi-Fi](/fr/gpio/esp32) — carte de wardriving
- [Modules externes](/fr/gpio/external-modules)
- [Brochage GPIO](/fr/gpio/pinout)
