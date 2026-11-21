---
title: "JavaScript : blebeacon"
sidebarTitle: "JS : blebeacon"
order: 420
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/system/js_app/modules/js_blebeacon.c]
sources: [unleashed-src]
---
# Module balise BLE

Un extra Unleashed, absent du firmware d'origine. Il diffuse une annonce Bluetooth LE personnalisée : votre propre adresse MAC, vos propres données. C'est la « balise supplémentaire » que le firmware utilise pour la diffusion en arrière-plan, elle fonctionne donc en même temps que la connexion Bluetooth normale.

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");
```

Script d'exemple : `/ext/apps/Scripts/js_examples/blebeacon.js`.

À la fin du script, le module restaure la configuration, les données et l'état de la balise tels qu'ils étaient avant — sauf si vous l'en avez empêché avec `keepAlive(true)`.

## Méthodes

### isActive()
- **Renvoie :** un booléen, indiquant si la balise diffuse en ce moment. Vérifiez-le au démarrage : une balise laissée en route par un script précédent est toujours active.

### setConfig()
Définit les paramètres de l'annonce.

- **Paramètres :**
  - `mac` : `Uint8Array` de 6 octets exactement. Toute autre taille lève `Wrong MAC address` ;
  - `power` (facultatif) : puissance d'émission sur l'échelle GapAdvPowerLevel, de `0x00` (-40 dBm) à `0x1F` (+6 dBm). 0 dBm par défaut, les valeurs hors plage sont ramenées aux bornes ;
  - `minInterval` (facultatif) : intervalle d'annonce minimal en ms. 50 par défaut, les valeurs sous 20 sont remontées à 20, le maximum est 255 ;
  - `maxInterval` (facultatif) : intervalle maximal en ms. 150 par défaut, jamais inférieur à `minInterval`, maximum 255.

### setData()
- **Paramètres :** `data`, un `Uint8Array` contenant les données de l'annonce. La limite matérielle est de 31 octets.

### start()
Démarre la diffusion.

### stop()
Arrête la diffusion.

### keepAlive()
- **Paramètres :** `keep`, booléen. Avec `true`, la balise continue de diffuser après la fin du script et rien n'est restauré. `false` par défaut.

## Exemple

Diffuser une courte annonce pendant cinq secondes :

```js
checkSdkFeatures(["blebeacon"]);
let blebeacon = require("blebeacon");

if (blebeacon.isActive()) {
    blebeacon.stop();
}
blebeacon.keepAlive(false);

blebeacon.setConfig(Uint8Array([0xDE, 0xAD, 0xBE, 0xEF, 0x00, 0x01]), 0x1F, 50, 150);
blebeacon.setData(Uint8Array([0x02, 0x01, 0x06, 0x03, 0xFF, 0xAB, 0xCD]));

blebeacon.start();
print("Advertising");
delay(5000);
blebeacon.stop();
print("Stopped");
```

## Pages liées

- [JavaScript : présentation](/fr/dev/js-about)
- [Types de données](/fr/dev/js-data-types) — le fonctionnement d'`Uint8Array` dans mJS
