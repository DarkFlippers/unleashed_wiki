---
title: "JavaScript : GPIO"
sidebarTitle: "JS : gpio"
order: 310
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_gpio.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/apps/Scripts/js_examples]
sources: [unleashed-docs, unleashed-src]
---
# Module GPIO

Le module `gpio` contrôle les broches du connecteur d'extension situé sur le dessus du Flipper Zero : sortie
numérique, entrée numérique et analogique, interruptions et PWM. Il dépend d'`event_loop` : il **doit** donc être
chargé après lui.

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");
```

Les numéros et noms de broches sont indiqués sur [Brochage GPIO](/fr/gpio/pinout).

::: warning
Les broches GPIO sont en 3,3 V. Ne connectez pas directement de signaux en 5 V.
:::

## Exemple : faire clignoter une LED

Branchez une LED (avec une résistance) entre la broche `PC3` (broche 7) et GND :

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");

let led = gpio.get("pc3");
led.init({ direction: "out", outMode: "push_pull" });

led.write(true);
delay(1000);
led.write(false);
delay(1000);
```

## Exemple : minuteurs, PWM, entrée analogique et interruption

Voici le script fourni `/ext/apps/Scripts/js_examples/gpio.js`. Il fait clignoter une LED sur PC3, fait varier
l'intensité d'une seconde LED sur PA7 en PWM, et affiche la tension du potentiomètre sur PC0 lorsqu'un bouton sur
PC1 est pressé :

```js
let eventLoop = require("event_loop");
let gpio = require("gpio");

// initialize pins
let led = gpio.get("pc3"); // same as `gpio.get(7)`
let led2 = gpio.get("pa7"); // same as `gpio.get(2)`
let pot = gpio.get("pc0"); // same as `gpio.get(16)`
let button = gpio.get("pc1"); // same as `gpio.get(15)`
led.init({ direction: "out", outMode: "push_pull" });
pot.init({ direction: "in", inMode: "analog" });
button.init({ direction: "in", pull: "up", inMode: "interrupt", edge: "falling" });

// blink led
print("Commencing blinking (PC3)");
eventLoop.subscribe(eventLoop.timer("periodic", 1000), function (_, _item, led, state) {
    led.write(state);
    return [led, !state];
}, led, true);

// cycle led pwm
print("Commencing PWM (PA7)");
eventLoop.subscribe(eventLoop.timer("periodic", 10), function (_, _item, led2, state) {
    led2.pwmWrite(10000, state);
    return [led2, (state + 1) % 101];
}, led2, 0);

// read potentiometer when button is pressed
print("Press the button (PC1)");
eventLoop.subscribe(button.interrupt(), function (_, _item, pot) {
    print("PC0 is at", pot.readAnalog(), "mV");
}, pot);

// the program will just exit unless this is here
eventLoop.run();
```

### Noms et numéros de broches

| Nom | Broche du connecteur | Nom | Broche du connecteur |
|---|---|---|---|
| `"pa7"` | 2 | `"pa14"` | 10 |
| `"pa6"` | 3 | `"pa13"` | 12 |
| `"pa4"` | 4 | `"pb6"` | 13 |
| `"pb3"` | 5 | `"pb7"` | 14 |
| `"pb2"` | 6 | `"pc1"` | 15 |
| `"pc3"` | 7 | `"pc0"` | 16 |
| | | `"pb14"` | 17 |

## Référence de l'API

### get()
Renvoie un objet `Pin` permettant de gérer une broche.

- **Paramètres :** `pin`, l'identifiant de la broche (exemples : `"pc3"`, `7`, `"pa6"`, `3`). Les noms de ports comme
  les numéros de broches du connecteur fonctionnent.
- **Renvoie :** un objet `Pin`.

### Pin.init()
Configure la broche.

- **Paramètres :** `mode`, un objet `Mode` :
  - `direction` (requis) : `"in"` ou `"out"` ;
  - `outMode` (requis pour `direction: "out"`) : `"open_drain"` ou `"push_pull"` ;
  - `inMode` (requis pour `direction: "in"`) : `"analog"`, `"plain_digital"`, `"interrupt"` ou `"event"` ;
  - `edge` (requis pour `inMode: "interrupt"` ou `"event"`) : `"rising"`, `"falling"` ou `"both"` ;
  - `pull` (facultatif) : `"up"`, `"down"` ou non défini.

### Pin.write()
Écrit une valeur numérique sur une broche configurée avec `direction: "out"`.

- **Paramètres :** `value`, le niveau logique booléen.

### Pin.read()
Lit une valeur numérique sur une broche configurée avec `direction: "in"` et n'importe quel `inMode` sauf
`"analog"`.

- **Renvoie :** le niveau logique booléen.

### Pin.readAnalog()
Lit la tension sur une broche configurée avec `direction: "in"` et `inMode: "analog"`.

- **Renvoie :** la tension en millivolts.

### Pin.interrupt()
Attache une interruption à une broche configurée avec `direction: "in"` et `inMode: "interrupt"` ou `"event"`.

- **Renvoie :** un `Contract` de boucle d'événements pour l'interruption. L'événement ne transporte aucune donnée
  supplémentaire.

### Pin.isPwmSupported()
Indique si cette broche prend en charge le PWM. Si `false`, toutes les autres méthodes PWM de cette broche lèvent une
erreur.

- **Renvoie :** un booléen.

### Pin.pwmWrite()
Définit les paramètres PWM et démarre le PWM. Configure la broche en `{ direction: "out", outMode: "push_pull" }`.
Lève une erreur si la broche ne prend pas en charge le PWM.

- **Paramètres :**
  - `freq` : fréquence en Hz ;
  - `duty` : rapport cyclique en %.

### Pin.isPwmRunning()
Indique si le PWM est en cours. Lève une erreur si la broche ne prend pas en charge le PWM.

- **Renvoie :** un booléen.

### Pin.pwmStop()
Arrête le PWM. Ne restaure **pas** la configuration précédente de la broche. Lève une erreur si la broche ne prend
pas en charge le PWM.

## Pages liées

- [Boucle d'événements](/fr/dev/js-event-loop)
- [Serial](/fr/dev/js-serial) pour l'UART du connecteur GPIO
- Les extras Unleashed `i2c` et `spi` : [Présentation de JavaScript](/fr/dev/js-about#unleashed-extras)
