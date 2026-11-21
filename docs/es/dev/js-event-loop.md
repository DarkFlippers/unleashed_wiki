---
title: "JavaScript: bucle de eventos"
sidebarTitle: "JS: event_loop"
order: 260
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_event_loop.md]
sources: [unleashed-docs]
---
# Módulo Event loop

El bucle de eventos es el núcleo de la programación orientada a eventos, y el subsistema de JS del Flipper está construido en torno a él. Apréndelo **antes** de usar los módulos avanzados (interrupciones de GPIO, GUI).

```js
let eventLoop = require("event_loop");
```

## La idea

En JavaScript pasas constantemente una función para que se llame más tarde, cuando ocurra algo. Eso es un callback:

```js
setTimeout(function() { console.log("Hello, World!") }, 1000);
```

Detrás de esto, la mayoría de los entornos de ejecución de JS mantienen una cola de eventos y un bucle largo que toma eventos de la cola y llama a los callbacks correspondientes. En pseudocódigo:

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

Los navegadores y Node.js ocultan ese bucle. **El JS del Flipper no**: tú creas las fuentes de eventos, suscribes callbacks a ellas y arrancas el bucle.

## Ejemplo: un temporizador de una sola vez

El equivalente en el Flipper del ejemplo de `setTimeout`:

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

## Argumentos adicionales en lugar de closures

mJS **no admite closures**: una función no puede leer variables del ámbito en el que se definió. Por eso `subscribe()` acepta argumentos adicionales después del callback y los pasa a su interior. Arriba se pasa `eventLoop` para que el callback pueda llamar a `eventLoop.stop()`.

El callback también puede **cambiar** esos valores para la siguiente llamada devolviendo un array de la misma longitud:

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

Aquí hay dos argumentos adicionales, así que cualquier valor de retorno que no sea un array de longitud 2 los deja sin cambios.

Los dos primeros argumentos de cualquier callback son siempre:

1. el **gestor de la suscripción**, que te permite cancelarla con `.cancel()`;
2. el **elemento del evento**, en los eventos que llevan datos. Los eventos de temporizador no llevan ninguno y dan `undefined`.

## Referencia de la API

### run()
Ejecuta el bucle de eventos hasta que se detiene con `stop()`.

### subscribe()
Suscribe una función a un evento.

- **Parámetros:**
  - `contract`: un identificador de fuente de eventos;
  - `callback`: la función que se llamará cuando ocurra el evento;
  - argumentos adicionales: se pasan como argumentos adicionales al callback.

El callback recibe al menos dos argumentos más los adicionales: el gestor de la suscripción (el mismo objeto que devuelve `subscribe`) y el elemento del evento (`undefined` en los eventos sin datos). Puede devolver un array de la misma longitud que el número de argumentos adicionales para reemplazarlos en la siguiente llamada. Los demás valores de retorno se descartan.

- **Devuelve:** un objeto `SubscriptionManager`:
  - `SubscriptionManager.cancel()` desuscribe el callback del evento.

::: warning
Cada fuente de eventos puede tener **solo un** callback.
:::

### stop()
Detiene el bucle de eventos.

### timer()
Crea una fuente de eventos que se dispara a un intervalo fijo, una vez o indefinidamente.

- **Parámetros:**
  - `mode`: `"oneshot"` o `"periodic"`;
  - `interval`: el tiempo de espera (en los temporizadores `"oneshot"`) o el periodo (en los `"periodic"`), en ms.
- **Devuelve:** un objeto `Contract` para el primer parámetro de `subscribe()`.

### queue()
Crea una cola para pasar mensajes.

- **Parámetros:** `length`, el número máximo de elementos de la cola.
- **Devuelve:** un objeto `Queue`:
  - `Queue.send(message)`: pone `message` (de cualquier tipo) al final de la cola;
  - `input`: un `Contract` (fuente de eventos) que extrae elementos del principio de la cola.

## Páginas relacionadas

- [GPIO](/es/dev/js-gpio): las interrupciones de pin son contratos del bucle de eventos.
- [GUI](/es/dev/js-gui): los eventos de las vistas y la navegación son contratos del bucle de eventos.
