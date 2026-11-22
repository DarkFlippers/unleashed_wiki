---
title: Herramientas web
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Herramientas web

Varias herramientas para el Flipper funcionan directamente en el navegador, sin instalar nada. Las que hablan con
el Flipper por USB necesitan la **Web Serial API**, así que usa **Chrome, Edge u otro navegador basado en
Chromium**.

::: warning Cierra qFlipper primero
Una herramienta del navegador no puede conectarse mientras qFlipper (o una segunda pestaña de Flipper Lab) tenga
ocupado el puerto serie del Flipper. Es el motivo más habitual de que «Chrome no vea el Flipper».
:::

## Herramientas de Unleashed

| Herramienta | Dirección | Qué hace |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | instala o actualiza Unleashed (Release o Dev) por USB |
| Builds dev | [dev.unleashedflip.com](https://dev.unleashedflip.com) | compilaciones de prueba automáticas de la rama dev con nuevas funciones |
| Sub-GHz & Coordinates Map | [map.unleashedflip.com](https://map.unleashedflip.com) | muestra en un mapa los archivos de wardriving Sub-GHz y cualquier otro archivo con coordenadas |
| Wi-Fi Wardriving Map | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | combina y muestra varias capturas en formato WiGLE (ESP32 Marauder y otros) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | flashea los módulos ESP32 más habituales desde el navegador |

### Unleashed Web Installer {#unleashed-web-installer}

La forma recomendada de instalar Unleashed.

1. Asegúrate de que hay una **tarjeta microSD** puesta.
2. Cierra qFlipper. Conecta el Flipper con un cable USB de datos.
3. Abre [web.unleashedflip.com](https://web.unleashedflip.com) en un navegador basado en Chromium.
4. Pulsa **Connect** y elige tu Flipper en la ventana emergente del navegador.
5. Selecciona la rama **Release** o **Dev**.
6. Pulsa **Install** y espera. Al terminar, todos los recursos quedan instalados y el Flipper arranca en Unleashed.

Como alternativa, cada [release de GitHub](https://github.com/DarkFlippers/unleashed-firmware/releases/latest)
tiene un enlace **Install via Web Updater** que abre la release en el web updater de Flipper Lab: pulsa **Connect**
y después **Install**. Guía completa: [Instalar Unleashed](/es/start/install).

### Sub-GHz & Coordinates Map

[map.unleashedflip.com](https://map.unleashedflip.com) coloca en un mapa tus capturas Sub-GHz con coordenadas (por
ejemplo, de wardriving Sub-GHz con un módulo GPS) y cualquier otro archivo que contenga coordenadas.

### Wi-Fi Wardriving Map

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) fusiona varias capturas **en formato WiGLE**, de ESP32
Marauder y herramientas similares, y muestra los puntos de acceso en un solo mapa. Véase
[ESP32 y módulos Wi-Fi](/es/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) es un flasher fácil de usar para los módulos
ESP32 más habituales, que funciona por completo en el navegador y sin instalar ninguna herramienta de flasheo.
Véase [ESP32](/es/gpio/esp32) y [Dev board](/es/gpio/devboard).

## Flipper Lab (oficial)

[lab.flipper.net](https://lab.flipper.net) es la caja de herramientas web oficial. Funciona con Unleashed:

- [Apps](https://lab.flipper.net/apps): el catálogo oficial de aplicaciones; instala, actualiza o borra
  aplicaciones por USB, véase [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): un terminal para la línea de comandos del Flipper, véase [CLI](/es/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): visualiza señales Sub-GHz RAW, útil para analizar un
  mando desconocido.
- El **web updater** que usan los enlaces «Install via Web Updater».

## Otros enlaces

- Página principal de Unleashed: [flipperunleashed.com](https://flipperunleashed.com)
- Enlaces directos de actualización `.tgz`: [unleashedflip.com](https://unleashedflip.com)
- JSON de directorio para compilaciones con uFBT: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Cuidado con las falsificaciones
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) es la única página oficial del
proyecto. No existen versiones de pago, premium ni de código cerrado; quien te ofrezca una es un estafador.
:::

## Páginas relacionadas

- [Instalar Unleashed](/es/start/install)
- [qFlipper](/es/mobile/qflipper)
- [Aplicación complementaria qUnleashed](/es/mobile/qunleashed-app)
