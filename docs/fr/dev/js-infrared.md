---
title: "JavaScript : infrared"
sidebarTitle: "JS : infrared"
order: 410
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_infrared]
sources: [unleashed-src]
---
# Module infrarouge

Un extra Unleashed, absent du firmware d'origine. Il émet des signaux IR depuis un script, soit par nom de protocole, soit sous forme de liste brute de timings. Il n'y a pas de réception : capturez d'abord le signal avec l'application Infrared.

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");
```

Le nom de la fonctionnalité est `infrared-send`, celui du module est `infrared`.

Script d'exemple : `/ext/apps/Scripts/js_examples/infrared-send.js`.

## Méthodes

### sendSignal()
Émet un signal avec un protocole connu du firmware.

- **Paramètres :**
  - `protocol` : `"NEC"`, `"NECext"`, `"NEC42"`, `"NEC42ext"`, `"Samsung32"`, `"RC6"`, `"RC5"`, `"RC5X"`, `"SIRC"`, `"SIRC15"`, `"SIRC20"`, `"Kaseikyo"` ou `"RCA"` ;
  - `address` : nombre ;
  - `command` : nombre ;
  - `options` (facultatif) : `{ repeat?: boolean, times?: number }`. `repeat` marque le signal comme paquet de répétition, `times` est le nombre d'émissions (1 par défaut).

```js
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
```

Dans les fichiers `.ir`, l'adresse et la commande sont stockées en hexadécimal little-endian, alors qu'un littéral numérique JS est en big-endian. `A9 00 00 00` dans un fichier s'écrit `0x000000A9` ici : inversez les octets avant de les recopier.

### sendRawSignal()
Émet un signal par ses timings marche/arrêt, pour les télécommandes qu'aucun protocole ne couvre.

- **Paramètres :**
  - `timings` : tableau de nombres, durées en microsecondes ;
  - `startFromMark` (facultatif) : booléen, indique si la première valeur est une impulsion et non une pause. `true` par défaut ;
  - `advancedSettings` (facultatif) : `{ frequency: number, dutyCycle: number }`. Les deux champs sont obligatoires dès que l'objet est fourni. Sans lui, la porteuse est à 38000 Hz avec un rapport cyclique de 0,33.

## Exemple

```js
checkSdkFeatures(["infrared-send"]);
let infrared = require("infrared");

// Samsung TV, volume down
print("Sending Samsung32");
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b);
delay(1000);

// Three presses in a row
infrared.sendSignal("Samsung32", 0x00000007, 0x0000000b, { times: 3 });
delay(1000);

// Raw timings at 36 kHz
infrared.sendRawSignal([3298, 1571, 442, 368, 442, 367], true, {
  frequency: 36000,
  dutyCycle: 0.33,
});
print("Done");
```

## Pages liées

- [Format de fichier infrarouge](/fr/infrared/file-format) — où lire l'adresse et la commande
- [Protocoles IR pris en charge](/fr/infrared/protocols)
- [JavaScript : présentation](/fr/dev/js-about)
