---
title: "JavaScript : boucle d'événements"
sidebarTitle: "JS : event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Module event loop

La boucle d'événements est le cœur de la programmation événementielle, et le sous-système JS du Flipper est construit
autour d'elle. Apprenez-la **avant** d'utiliser les modules avancés (interruptions GPIO, GUI).

```js
let eventLoop = require("event_loop");
```

## L'idée

En JavaScript, vous passez en permanence une fonction destinée à être appelée plus tard, quand quelque chose se
produit. C'est un callback :

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Derrière cela, la plupart des moteurs JS font tourner une file d'événements et une longue boucle qui prend les
événements dans la file et appelle les callbacks correspondants. En pseudo-code :

```js
while(loop_is_running()) {
    if(event_available_in_queue()) {
        let event = fetch_event_from_queue();
        let callback = get_callback_associated_with(event);
        if(callback)
            callback(get_extra_data_for(event));
    } else {
        // avoid wasting CPU time
        sleep_until_any_event_becomes_available();
    }
}
```

Les navigateurs et Node.js masquent cette boucle. **Le JS du Flipper, non** : vous créez les sources d'événements,
vous y abonnez des callbacks et vous démarrez la boucle vous-même.

## Exemple : un minuteur à déclenchement unique

L'équivalent Flipper de l'exemple `setTimeout` :

```js
// import module
let eventLoop = require("event_loop");

// create an event source that will fire once 1 second after it has been created
let timer = eventLoop.timer("oneshot", 1000);

// subscribe a callback to the event source
eventLoop.subscribe(timer, function(_subscription, _item, eventLoop) {
    print("Hello, World!");
    eventLoop.stop();
}, eventLoop); // notice this extra argument. we'll come back to this later

// run the loop until it is stopped
eventLoop.run();

// the previous line will only finish executing once `.stop()` is called, hence
// the following line will execute only after "Hello, World!" is printed
print("Stopped");
```

## Des arguments supplémentaires au lieu des fermetures

mJS **ne prend pas en charge les fermetures** : une fonction ne peut pas lire les variables de la portée où elle a
été définie. C'est pourquoi `subscribe()` accepte des arguments supplémentaires après le callback et les lui
transmet. Ci-dessus, `eventLoop` est passé pour que le callback puisse appeler `eventLoop.stop()`.

Le callback peut aussi **modifier** ces valeurs pour l'appel suivant en renvoyant un tableau de même longueur :

```js
// this timer will fire every second
let timer = eventLoop.timer("periodic", 1000);
eventLoop.subscribe(timer, function(_subscription, _item, counter, eventLoop) {
    print("Counter is at:", counter);
    if(counter === 10)
        eventLoop.stop();
    // modify the extra arguments that will be passed to us the next time
    return [counter + 1, eventLoop];
}, 0, eventLoop);
```

Il y a ici deux arguments supplémentaires : toute valeur de retour autre qu'un tableau de longueur 2 les laisse
inchangés.

Les deux premiers arguments de chaque callback sont toujours :

1. le **gestionnaire d'abonnement**, qui permet d'appeler `.cancel()` sur l'abonnement ;
2. l'**élément d'événement**, pour les événements qui transportent des données. Les événements de minuteur n'en
   transportent pas et donnent `undefined`.

## Référence de l'API

### run()
Exécute la boucle d'événements jusqu'à son arrêt par `stop()`.

### subscribe()
Abonne une fonction à un événement.

- **Paramètres :**
  - `contract` : un identifiant de source d'événements ;
  - `callback` : la fonction à appeler lorsque l'événement se produit ;
  - arguments supplémentaires : transmis comme arguments supplémentaires au callback.

Le callback reçoit au moins deux arguments, plus les arguments supplémentaires : le gestionnaire d'abonnement (le
même objet que celui renvoyé par `subscribe`) et l'élément d'événement (`undefined` pour les événements sans
données). Il peut renvoyer un tableau de la même longueur que le nombre d'arguments supplémentaires pour les
remplacer lors de l'appel suivant. Les autres valeurs de retour sont ignorées.

- **Renvoie :** un objet `SubscriptionManager` :
  - `SubscriptionManager.cancel()` désabonne le callback de l'événement.

::: warning
Chaque source d'événements ne peut avoir qu'**un seul** callback.
:::

### stop()
Arrête la boucle d'événements.

### timer()
Crée une source d'événements qui se déclenche à intervalle fixe, une seule fois ou indéfiniment.

- **Paramètres :**
  - `mode` : `"oneshot"` ou `"periodic"` ;
  - `interval` : le délai (pour les minuteurs `"oneshot"`) ou la période (pour les minuteurs `"periodic"`), en ms.
- **Renvoie :** un objet `Contract` destiné au premier paramètre de `subscribe()`.

### queue()
Crée une file pour transmettre des messages.

- **Paramètres :** `length`, le nombre maximal d'éléments dans la file.
- **Renvoie :** un objet `Queue` :
  - `Queue.send(message)` : place `message` (de n'importe quel type) à la fin de la file ;
  - `input` : un `Contract` (source d'événements) qui retire les éléments en tête de file.

## Pages liées

- [GPIO](/fr/dev/js-gpio) : les interruptions de broche sont des contrats de boucle d'événements.
- [GUI](/fr/dev/js-gui) : les événements de vue et la navigation sont des contrats de boucle d'événements.
