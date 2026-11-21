---
title: Desarrollo
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Desarrollo

Esta sección es para quien quiera ir más allá de usar el Flipper: compilar el firmware Unleashed desde el código
fuente, escribir sus propias apps en C o JavaScript, depurarlas en hardware real, hablar con el dispositivo por línea
de comandos o entender cómo funcionan por dentro las actualizaciones y el hardware.

::: tip Unleashed
Unleashed es un fork del firmware oficial que se mantiene **totalmente compatible con la API y las apps oficiales**.
Casi todo lo que dice la documentación oficial para desarrolladores se aplica tal cual. Lo principal que hay que tener
en cuenta:

- clona `https://github.com/DarkFlippers/unleashed-firmware` en lugar del repositorio oficial;
- al compilar apps con **uFBT**, apúntalo al SDK de Unleashed
  (`--index-url=https://up.unleashedflip.com/directory.json`); de lo contrario, tu app se compila contra el SDK
  oficial y puede negarse a cargar
  ([detalles](/es/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- el origen del firmware se declara como `Unleashed` y la versión de API actual en `dev` es la **88.27**.
:::

## Compilar el firmware

| Página | Qué encontrarás |
|---|---|
| [Compilar el firmware](/es/dev/build) | Clonar, compilar y flashear Unleashed en Linux, macOS y Windows |
| [Flipper Build Tool (fbt)](/es/dev/fbt) | Todos los targets, opciones y variables de entorno de `fbt` |
| [Objetivos de hardware](/es/dev/hardware-targets) | Cómo describen `targets/` y `target.json` las variantes de hardware (f7, f18) |
| [Compilar apps en Android](/es/dev/android-build) | Compilar apps `.fap` en el móvil con Termux + uFBT, sin PC |

## Escribir apps

| Página | Qué encontrarás |
|---|---|
| [Tu primera app en C](/es/dev/first-app-c) | uFBT, plantilla de app, un «Hello world» con un diálogo, compilar y ejecutar |
| [Manifiestos de app (.fam)](/es/dev/app-manifests) | Todos los campos de `application.fam`, opciones de apps externas, bibliotecas privadas |
| [API Furi](/es/dev/furi-api) | Arquitectura de hardware y software, el núcleo Furi, `furi_assert` / `furi_check` |
| [GUI en las apps](/es/dev/gui) | Diálogos, ViewPort, Views y Scenes, módulos de vista |
| [Depurar apps](/es/dev/debugging) | Sondas SWD, depuración en VS Code, señales de depuración del Furi HAL |
| [API FuriHalBus](/es/dev/furi-hal-bus) | Activar y desactivar correctamente los periféricos del MCU, mapa de canales DMA |
| [JavaScript en el Flipper](/es/dev/js-about) | Escribir scripts en JavaScript en lugar de C (grupo de páginas aparte) |
| Módulos de JS solo de Unleashed | [subghz](/es/dev/js-subghz), [infrared](/es/dev/js-infrared), [blebeacon](/es/dev/js-blebeacon), [usbdisk](/es/dev/js-usbdisk), [i2c](/es/dev/js-i2c), [spi](/es/dev/js-spi), [vgm](/es/dev/js-vgm) — no están en el firmware de serie ni en la documentación oficial |

## Trabajar con el dispositivo

| Página | Qué encontrarás |
|---|---|
| [Interfaz de línea de comandos (CLI)](/es/dev/cli) | Conectarse por USB serie; todos los comandos de la CLI con sus argumentos |
| [Actualizaciones OTA](/es/dev/ota) | Cómo funciona el actualizador, campos del manifiesto, códigos de error `[XX-YY]`, compilar paquetes |
| [Formato tarball heatshrink](/es/dev/tar-heatshrink) | El contenedor `.tar.hs` usado para los recursos en los paquetes de actualización |
| [Hardware](/es/dev/hardware) | Especificaciones técnicas, esquemas, modelos 3D, planos de módulos y devboards |

## Pruebas

| Página | Qué encontrarás |
|---|---|
| [Pruebas unitarias](/es/dev/unit-tests) | Compilar y ejecutar la app `unit_tests` en el dispositivo y añadir tus propias pruebas |
| [Pruebas de integración](/es/dev/testing) | El plan de pruebas manual que se sigue antes de fusionar PR y publicar releases |

## Otros recursos útiles

- Documentación oficial para desarrolladores (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — ahí se buscan las APIs del firmware que esta wiki no cubre, con secciones de programación de sistema, desarrollo de apps, JavaScript, módulos de expansión y formatos de fichero
- Configuración de un workspace de CLion — [guía de Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Tutoriales de plugins «Hello world!»: [en inglés (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [en ruso (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [Cómo escribir tu propia app](https://flipper.atmanos.com/docs/overview/intro)

### Estructura del proyecto del repositorio del firmware

| Carpeta | Contenido |
|---|---|
| `applications` | Aplicaciones y servicios usados en el firmware |
| `assets` | Recursos usados por las aplicaciones y los servicios |
| `furi` | Furi Core: primitivas y utilidades a nivel de sistema operativo |
| `debug` | Herramientas de depuración: plugins de GDB, archivo SVD, etc. |
| `documentation` | Fuentes de la documentación y configuración de los generadores |
| `firmware` | Código fuente del firmware |
| `lib` | Bibliotecas propias y de terceros, controladores |
| `site_scons` | Utilidades de compilación |
| `scripts` | Scripts auxiliares y bibliotecas de Python |
| `targets` | Definiciones de los objetivos de hardware (`f7`, `f18`) |

Muchas de estas carpetas tienen su propio `ReadMe.md` — vale la pena leerlos.
