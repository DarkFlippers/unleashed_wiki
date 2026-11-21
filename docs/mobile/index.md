---
title: Mobile & desktop apps
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# Mobile & desktop apps

The Flipper works on its own, but a computer or phone makes some things much easier: installing and updating
firmware, copying files, installing apps, backing up your keys and remotes, controlling the Flipper remotely.

| Tool | Runs on | Good for |
|---|---|---|
| [qFlipper](/mobile/qflipper) | Windows, macOS, Linux | install Unleashed from a `.tgz`, file manager, backup / restore, recovery |
| [Flipper mobile app](/mobile/mobile-app) | iOS, Android | update over Bluetooth (custom `.tgz` too), archive of keys, app catalog, remote control |
| [qUnleashed](/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | Unleashed's own app: firmware updates over BLE or USB, archive, app catalog, remote screen, CLI, Seed recovery |
| [Web tools](/mobile/web-tools) | browser | Web Installer, Sub-GHz & coordinates map, Wi-Fi wardriving map, ESP32 flasher, Flipper Lab |

::: tip Unleashed
Unleashed is fully compatible with the official qFlipper and the official Flipper mobile app. The fastest way to
install or update Unleashed is the [Web Installer](/mobile/web-tools#unleashed-web-installer) in a Chromium browser.
:::

::: warning One connection at a time
Only one program can use the Flipper's USB serial port. Close qFlipper before using Flipper Lab, the Web Installer, a
CLI terminal or U2F, and keep just one Flipper Lab tab open.
:::

## Pages

- [qFlipper](/mobile/qflipper)
- [Flipper mobile app](/mobile/mobile-app)
- [qUnleashed companion app](/mobile/qunleashed-app)
- [Web tools](/mobile/web-tools)
