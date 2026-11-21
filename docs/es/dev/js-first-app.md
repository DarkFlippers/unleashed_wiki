---
title: "JavaScript: tu primera app"
sidebarTitle: "JS: primera app"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# Tu primera app en JavaScript

En esta guía escribirás un script diminuto que imprime números con un retardo y después lo ejecutarás en Flipper Zero de dos formas: desde el menú del dispositivo y desde un PC a través de la CLI. Necesitas un Flipper Zero, un PC y un cable USB.

## Paso 1. Crear el script

Crea un archivo de texto llamado `first_app.js` con este contenido:

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

Qué hace:

- imprime **start** y espera 1 segundo;
- imprime **1**, **2** y **3**, con una pausa de 0,5 segundos después de cada uno;
- imprime **end**.

`print()` saca texto y `delay()` pausa durante el número de milisegundos indicado (1000 ms = 1 s). Ambas son **funciones integradas**, así que no hay que cargar ningún módulo antes. Consulta [Funciones integradas](/es/dev/js-builtin) para ver la lista completa.

## Paso 2. Copiar el archivo a Flipper Zero

1. Conecta Flipper Zero al PC por USB.
2. Abre [qFlipper](/es/mobile/qflipper).
3. Ve a la pestaña **File manager** y abre `SD Card/apps/Scripts/`.
4. Arrastra y suelta `first_app.js` en la ventana de qFlipper.

También puedes copiar el archivo con un lector de tarjetas. Debe acabar en `/ext/apps/Scripts/`.

## Paso 3. Ejecutar el script

### Desde el menú del Flipper

1. Abre `Main Menu → Apps → Scripts`. La lista muestra los scripts de `SD Card/apps/Scripts/`.
2. Selecciona `first_app`.
3. Pulsa <kbd>OK</kbd> para ejecutarlo.

![Script ejecutándose en Flipper Zero](/img/dev/js_first_app_on_fz.jpg)

Las líneas aparecen en la pantalla del Flipper con los retardos definidos en el script.

### Desde la CLI

Ejecutarlo desde la [CLI](/es/dev/cli) resulta práctico para depurar: editas y pruebas el script sin tocar el dispositivo.

1. Conecta Flipper Zero por USB.
2. Abre la CLI (por ejemplo con la pestaña CLI de qFlipper, un terminal serie o `./fbt cli`).
3. Ejecuta `js` seguido de la ruta del script:

```sh
js /ext/apps/Scripts/first_app.js
```

![Salida del script en la CLI](/img/dev/js_first_app_on_cli.jpg)

Cuando un script se inicia desde la CLI, todo lo que se imprime con `print()` va a la CLI y no a la pantalla del Flipper.

## Resolución de problemas

- **El script no aparece en la lista.** Comprueba que el archivo tiene la extensión `.js` y está en `/ext/apps/Scripts/` (las subcarpetas valen; entra en ellas).
- **El script se detiene con un error.** mJS solo admite un subconjunto de JavaScript (sin closures, sin funciones flecha, sin clases). Ejecútalo desde la CLI para ver el mensaje de error y la línea.

**Siguiente:** [Desarrollar apps con el SDK de JavaScript](/es/dev/js-sdk)
