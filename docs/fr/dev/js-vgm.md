---
title: "JavaScript : vgm"
sidebarTitle: "JS : vgm"
order: 460
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [unleashed-src]
---
# Video Game Module

Un extra Unleashed, absent du firmware d'origine. Il lit le capteur de mouvement (IMU ICM42688P) du [Video Game Module](/fr/gpio/video-game-module) et indique comment le Flipper est incliné.

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");
```

Il n'y a pas de script d'exemple dans le firmware pour ce module.

Les angles sont en degrés :

- **pitch** — le nez vers le haut et vers le bas ;
- **roll** — l'inclinaison à gauche et à droite ;
- **yaw** — la rotation à plat sur la table.

Sans module branché, `require("vgm")` fonctionne quand même, mais toutes les méthodes renvoient `undefined`. Testez ce cas plutôt que de supposer le matériel présent.

Le pilote de l'IMU vient du [moteur de jeu Flipper](https://github.com/flipperdevices/flipperzero-game-engine).

## Méthodes

### getPitch()
- **Renvoie :** un nombre, ou `undefined` si aucun module n'est branché.

### getRoll()
- **Renvoie :** un nombre, ou `undefined` si aucun module n'est branché.

### getYaw()
- **Renvoie :** un nombre, ou `undefined` si aucun module n'est branché.

### deltaYaw()
Bloque jusqu'à ce que le yaw ait tourné de `angle` degrés, en interrogeant le capteur 10 fois par seconde.

- **Paramètres :**
  - `angle` : de combien de degrés attendre la variation ;
  - `timeout` (facultatif) : attente en millisecondes. 3000 par défaut.
- **Renvoie :** la variation en degrés, signée — négative dans un sens, positive dans l'autre. `0` si l'angle n'a pas été atteint avant l'expiration du délai, `undefined` si aucun module n'est branché.

## Exemple

```js
checkSdkFeatures(["vgm"]);
let vgm = require("vgm");

if (vgm.getPitch() === undefined) {
    print("No Video Game Module attached");
} else {
    for (let i = 0; i < 10; i++) {
        print("pitch", vgm.getPitch(), "roll", vgm.getRoll(), "yaw", vgm.getYaw());
        delay(200);
    }

    print("Turn the Flipper 45 degrees...");
    let turned = vgm.deltaYaw(45, 5000);
    if (turned === 0) {
        print("Nothing happened");
    } else {
        print("Turned by", turned);
    }
}
```

## Pages liées

- [Video Game Module](/fr/gpio/video-game-module)
- [JavaScript : présentation](/fr/dev/js-about)
