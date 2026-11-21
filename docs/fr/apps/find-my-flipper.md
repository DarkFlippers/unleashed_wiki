---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (de @MatthewKuKanich) transforme le Bluetooth du Flipper en balise de traçage. Le Flipper diffuse
la même annonce BLE qu'un traceur, et les téléphones du réseau de localisation situés à proximité signalent sa
position : un Flipper perdu peut donc être retrouvé dans l'application du propriétaire du traceur.

Types de traceurs pris en charge : **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find),
**Tile SmartTag** et **Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper est fourni avec le firmware, et Unleashed installe en plus un petit crochet de démarrage : si la balise
était active lors de l'extinction du Flipper, elle **redémarre automatiquement après un redémarrage**, sans ouvrir
l'application. La balise continue de fonctionner en arrière-plan pendant que vous utilisez d'autres applications.
:::

::: warning
À n'utiliser qu'avec vos propres traceurs et appareils. Suivre d'autres personnes peut être illégal là où vous vivez.
:::

## Ce dont vous avez besoin

Le Flipper a besoin de l'**adresse MAC** et du **payload** du traceur (ou d'un fichier de clés). Vous les obtenez de
deux façons :

- **Cloner un traceur existant** (le plus simple ; la position apparaît alors dans l'application habituelle du
  propriétaire du traceur).
- **Générer vos propres clés** avec la méthode OpenHaystack (aucun traceur physique nécessaire, réseau Apple
  uniquement ; vous consultez la position avec OpenHaystack ou une solution sans Mac).

### Option A : cloner un traceur existant

1. Appairez l'AirTag ou le SmartTag avec votre téléphone comme d'habitude.
2. Mettez-le en mode « perdu » : éloignez-le du téléphone auquel il est enregistré pendant environ 15 minutes.
3. Sur un téléphone Android, installez **nRF Connect** (la version iOS n'affiche pas les données brutes).
4. Dans nRF Connect, réglez le filtre sur la marque du traceur (Apple ou Samsung), mettez le RSSI au réglage le plus
   faible et lancez le scan.
5. Quand le traceur apparaît comme appareil « FindMy », ouvrez **Raw** / **View Raw** et notez le **payload** et
   l'**adresse MAC**. Vous pouvez aussi les exporter dans un fichier `.txt`.
6. **Retirez immédiatement la pile du traceur**, sinon il fera tourner sa clé et son adresse MAC et votre copie
   cessera de fonctionner.

### Option B : clés OpenHaystack

1. Téléchargez `generate_keys.py` depuis le [dépôt FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper) et
   exécutez-le (il nécessite `python3 -m pip install cryptography`).
2. Il vous fournit une **Private Key**, une **Public Key**, un **Payload** et une **MAC Address**, ainsi qu'un fichier
   `.keys`.
3. Conservez la Private Key : elle est nécessaire pour recevoir les rapports de position.
4. Consultez les positions dans [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS antérieur à 14)
   ou sans Mac avec [macless-haystack](https://github.com/dchristl/macless-haystack) ou
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Configurer le Flipper

1. Copiez votre export `.txt` de nRF Connect ou le fichier `.keys` dans `/ext/apps_data/findmy/` sur la carte SD (ou
   passez cette étape et saisissez les données à la main).
2. Ouvrez `Apps → Bluetooth → FindMy Flipper` et appuyez sur <kbd>→</kbd> (**Config**).
3. Choisissez **Register Tag**, puis le type de traceur : `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` ou
   `Google Find My`.
4. Choisissez le mode d'import :
   - `nRF Connect (.txt)` : sélectionnez le fichier exporté ;
   - `OpenHaystack (.keys)` : sélectionnez le fichier de clés ;
   - `Register Tag Manually` : saisissez l'adresse MAC, puis le payload.
5. Revenez à l'écran principal et appuyez sur <kbd>OK</kbd>. Il passe à `Broadcast Active`.

## Écran principal

| Bouton | Action |
|---|---|
| <kbd>OK</kbd> | démarrer / arrêter la balise (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | modifier l'intervalle de diffusion |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | quitter l'application en laissant la balise active en arrière-plan |
| <kbd>Back</kbd> | fermer l'application |

## Menu Config

| Entrée | Valeurs | Remarques |
|---|---|---|
| Broadcast Interval | 1-10 s (Google : 1-2 s) | fréquence d'émission de la balise ; Google exige au moins toutes les 2 s |
| Transmit Power | 0-6 dBm | plus de puissance = plus de portée, plus de consommation |
| Register Tag | | type de traceur et import (ci-dessus) |
| Show MAC | Yes / No | afficher la MAC sur l'écran principal |

L'application enregistre son état dans `/ext/apps_data/findmy/findmy_state.txt` ; c'est ce qui permet à la balise de
reprendre après un redémarrage.

## Localisation

- **Clone d'AirTag** : le Flipper apparaît comme votre AirTag dans l'application Find My.
- **Clone de SmartTag** : dans SmartThings (SmartThings Find), sur un téléphone ou dans le navigateur.
- **Clés OpenHaystack** : dans OpenHaystack ou macless-haystack.

## Dépannage

- **La position ne se met jamais à jour** : la clé / l'adresse MAC du traceur a tourné avant que vous n'ayez retiré sa
  pile ; refaites la capture.
- **La balise s'arrête après un redémarrage** : vérifiez que la carte SD est insérée (le fichier d'état s'y trouve) et
  que la balise était bien en `Broadcast Active` avant l'extinction.
- **La batterie se vide plus vite** : augmentez l'intervalle de diffusion et réduisez la puissance d'émission.

## Pages liées

- [Applications fournies avec Unleashed](/fr/apps/catalog)
- [Paramètres](/fr/start/settings)
