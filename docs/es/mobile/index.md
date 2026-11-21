---
title: Aplicaciones de móvil y de escritorio
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Aplicaciones de móvil y de escritorio

El Flipper funciona por sí solo, pero un ordenador o un móvil hacen que algunas cosas sean mucho más fáciles:
instalar y actualizar el firmware, copiar archivos, instalar aplicaciones, respaldar tus llaves y mandos o
controlar el Flipper a distancia.

| Herramienta | Funciona en | Útil para |
|---|---|---|
| [qFlipper](/es/mobile/qflipper) | Windows, macOS, Linux | instalar Unleashed desde un `.tgz`, gestor de archivos, copia de seguridad y restauración, recuperación |
| [Aplicación móvil de Flipper](/es/mobile/mobile-app) | iOS, Android | actualizar por Bluetooth (también un `.tgz` propio), archivo de llaves, catálogo de aplicaciones, control remoto |
| [qUnleashed](/es/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | la aplicación propia de Unleashed: actualizaciones de firmware por BLE o USB, archivo, catálogo de aplicaciones, pantalla remota, CLI, recuperación de Seed |
| [Herramientas web](/es/mobile/web-tools) | navegador | Web Installer, mapa de Sub-GHz y coordenadas, mapa de wardriving Wi-Fi, flasher de ESP32, Flipper Lab |

::: tip Unleashed
Unleashed es totalmente compatible con el qFlipper oficial y con la aplicación móvil oficial de Flipper. La forma
más rápida de instalar o actualizar Unleashed es el [Web Installer](/es/mobile/web-tools#unleashed-web-installer)
en un navegador basado en Chromium.
:::

::: warning Una conexión a la vez
Solo un programa puede usar el puerto serie USB del Flipper. Cierra qFlipper antes de usar Flipper Lab, el Web
Installer, un terminal de la CLI o U2F, y mantén abierta una sola pestaña de Flipper Lab.
:::

## Páginas

- [qFlipper](/es/mobile/qflipper)
- [Aplicación móvil de Flipper](/es/mobile/mobile-app)
- [Aplicación complementaria qUnleashed](/es/mobile/qunleashed-app)
- [Herramientas web](/es/mobile/web-tools)
