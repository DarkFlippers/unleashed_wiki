---
title: "JavaScript: SDK y TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Desarrollar apps con el SDK de JavaScript

Copiar un script al dispositivo con qFlipper después de cada cambio se vuelve tedioso enseguida. El **SDK de JavaScript para Flipper Zero** es un conjunto de herramientas que elimina esos pasos:

- **un solo comando** (`npm start`) compila la app, la sube y la ejecuta;
- **autocompletado** y comprobación de tipos (escribes TypeScript);
- un **minificador de JS** opcional.

::: tip Unleashed
Unleashed tiene su propio fork del SDK: **`@darkflippers/fz-sdk-ul`**, creado con **`@darkflippers/create-fz-app-ul`**. Añade declaraciones de tipos para los [módulos exclusivos de Unleashed](/es/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`, `spi`, `vgm`) y para las vistas de GUI adicionales. Los scripts escritos para el SDK oficial (`@flipperdevices/fz-sdk`) también funcionan en Unleashed. Si usas los extras de Unleashed, protégelos con `doesSdkSupport([...])` para que tu app siga funcionando en otros firmwares, o llama a `checkSdkFeatures([...])` al principio si la característica es imprescindible.
:::

## Instalar el SDK

El SDK se distribuye como paquete de NPM, así que necesitas **Node.js** con un gestor de paquetes (npm, pnpm o yarn). Esta guía usa npm.

1. Instala **Node.js + npm** desde la [página oficial de descargas](https://nodejs.org/en/download/package-manager).
2. Abre un terminal en la carpeta donde quieras guardar tu proyecto.
3. Crea un proyecto a partir de la plantilla. El asistente interactivo pregunta el nombre del proyecto y el gestor de paquetes:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

La carpeta del proyecto contiene ahora la app de plantilla, el paquete del SDK, las dependencias y las configuraciones. Tu código va en `index.ts`.

## Ejecutar tu app {#run}

1. Conecta Flipper Zero al PC por USB.
2. Abre un terminal en la carpeta del proyecto (`cd my-flip-app`).
3. Ejecuta:

```sh
npm start
```

El SDK compila la app, copia el archivo `.js` al Flipper Zero y lo ejecuta. La salida de `print()` se muestra en el terminal.

![Salida de npm start](/img/dev/js_sdk_npm_start.jpg)

## Actualizar tu app

Después de cambiar el código, vuelve a ejecutar `npm start`. Mientras el Flipper siga conectado, el archivo `.js` antiguo del dispositivo se sustituye y arranca la versión nueva.

## Configuración: `fz-sdk.config.json5`

La configuración de la plantilla (SDK de Unleashed) tiene este aspecto:

```js
{
    build: {
        // Where to put the compiled file
        output: "dist/<app_name>.js",

        // Whether to reduce the final file size at the cost of readability and
        // clarity of error messages
        minify: false,

        // Set this to `false` if you've thoroughly read the documentation and
        // are sure that you can use manual version checks to your advantage
        enforceSdkVersion: true,
    },

    upload: {
        // Where to grab the file from. If you're not doing any extra processing
        // after the SDK, this should match `build.output`
        input: "dist/<app_name>.js",

        // Where to put the file on the device
        output: "/ext/apps/Scripts/<app_name>.js",
    },
}
```

### Autocompletado

Los editores con soporte de Language Server (por ejemplo [VS Code](https://code.visualstudio.com/)) sugieren las funciones de los módulos y sus parámetros mientras escribes, así que rara vez tendrás que consultar nada.

![Autocompletado en VS Code](/img/dev/js_sdk_code_completion.jpg)

### Minificador de JS

El minificador elimina espacios, tabulaciones y saltos de línea y acorta los nombres de las variables. El script queda más pequeño y puede ejecutarse algo más rápido, pero los mensajes de error se vuelven mucho más difíciles de leer. Por eso está **desactivado por defecto**. Para activarlo, pon `minify: true` en `fz-sdk.config.json5`.

## Diferencias con el JS normal del Flipper

Con el SDK escribes **TypeScript**: mejor autocompletado y avisos de tipos, pero el código tiene un aspecto algo distinto.

- **Importar módulos**
  - JS normal: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (en el SDK de Unleashed: `"@darkflippers/fz-sdk-ul/module"`)
- **Varios archivos fuente.** El SDK todavía no admite varios archivos `.ts` que se importen entre sí. Puedes usar `load()` igualmente, pero sin comprobación de tipos.
- **Conversión de valores.** Algunas funciones devuelven tipos genéricos. Por ejemplo, `eventLoop.subscribe()` llama a tu callback con un `Item` genérico. Conviértelo cuando sea necesario:
  - en línea: `<string>item`
  - con una variable nueva: `let text = item as string;`

`npm start` transpila tu código a JavaScript normal (y lo minifica si está activado). El archivo `.js` resultante en `dist/` es el que compartes con otras personas.

## Páginas relacionadas

- [Tu primera app en JS](/es/dev/js-first-app)
- [Usar módulos de JS](/es/dev/js-modules)
- [Funciones integradas: compatibilidad del SDK](/es/dev/js-builtin#sdk-compatibility)
