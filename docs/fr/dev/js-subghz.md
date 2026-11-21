---
title: "JavaScript : subghz"
sidebarTitle: "JS : subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Module Sub-GHz

Un extra Unleashed, absent du firmware d'origine. Il donne la radio Sub-GHz à un script : passer de la réception au repos, lire le niveau du signal, changer de fréquence, émettre un fichier `.sub` enregistré.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` cherche d'abord un module CC1101 externe, puis se rabat sur la radio interne. Tant qu'elle n'a pas été appelée, toutes les autres méthodes lèvent `Radio is not setup`.

Script d'exemple : `/ext/apps/Scripts/js_examples/subghz.js`.

## Méthodes

### setup()
Initialise la radio et choisit l'appareil. Démarre à 433920000 Hz dans l'état `IDLE`. Lève une erreur si la radio est déjà initialisée.

### end()
Met la radio en veille et libère l'appareil. Se fait tout seul à la fin du script. Appeler `setup()` ensuite relance la recherche d'un module externe.

### setRx()
Passe la radio en réception.

### setIdle()
Passe la radio au repos. La fréquence ne peut être changée que dans cet état.

### getRssi()
Niveau du signal sur la fréquence courante, en dBm.

- **Renvoie :** un `number`, ou `undefined` si la radio n'est pas en RX.

### getState()
- **Renvoie :** `"RX"`, `"TX"` ou `"IDLE"`.

### getFrequency()
- **Renvoie :** la fréquence courante en Hz, sous forme de nombre.

### setFrequency()
Accorde la radio. Lève une erreur si la radio n'est pas en `IDLE` ou si la fréquence sort des bandes prises en charge par l'appareil.

- **Paramètres :** `frequency`, un nombre en Hz — par exemple `433920000`.
- **Renvoie :** la fréquence sur laquelle la radio s'est réellement accordée. Un CC1101 ne tombe pas exactement sur toutes les valeurs, il prend donc la plus proche possible.

### isExternal()
- **Renvoie :** un booléen — `true` quand un CC1101 externe est utilisé, `false` pour la radio interne.

### transmitFile()
Émet un fichier `.sub`. La fréquence et la modulation viennent du fichier, pas de `setFrequency()`. Renvoie `true` ; au moindre problème (fichier absent, en-tête incorrect, fréquence non prise en charge, preset inconnu) elle lève une erreur. La radio est laissée en `IDLE`.

- **Paramètres :**
  - `path` : chemin complet du fichier, par ex. `"/ext/subghz/0.sub"` ;
  - `repeat` (facultatif) : nombre d'émissions.

Sans `repeat`, les fichiers RAW partent une fois et les fichiers à protocole 10 fois, ce qui imite le maintien du bouton sur une vraie télécommande. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` et `Power Smart` envoient déjà plusieurs paquets par répétition, leur valeur par défaut est donc 1.

## Exemple

Écouter sur 433,92 MHz, puis émettre une clé enregistrée :

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## Pages liées

- [Format de fichier Sub-GHz](/fr/subghz/file-format) — ce que contient un `.sub`
- [Modules CC1101 externes](/fr/subghz/external-cc1101)
- [JavaScript : présentation](/fr/dev/js-about)
