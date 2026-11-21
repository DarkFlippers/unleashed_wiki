---
title: App mobili e desktop
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/mobile-app]
sources: [unleashed-readme, flipper-docs]
---
# App mobili e desktop

Il Flipper funziona da solo, ma un computer o un telefono rendono molte cose più semplici: installare e aggiornare il
firmware, copiare file, installare app, fare il backup delle chiavi e dei telecomandi, controllare il Flipper a
distanza.

| Strumento | Gira su | Utile per |
|---|---|---|
| [qFlipper](/it/mobile/qflipper) | Windows, macOS, Linux | installare Unleashed da un `.tgz`, file manager, backup / ripristino, recupero |
| [App mobile Flipper](/it/mobile/mobile-app) | iOS, Android | aggiornare via Bluetooth (anche con un `.tgz` custom), archivio delle chiavi, catalogo delle app, controllo remoto |
| [qUnleashed](/it/mobile/qunleashed-app) | Android, iOS, Windows, macOS, Linux | l'app di Unleashed: aggiornamenti del firmware via BLE o USB, archivio, catalogo delle app, schermo remoto, CLI, recupero del Seed |
| [Strumenti web](/it/mobile/web-tools) | browser | Web Installer, mappa Sub-GHz e delle coordinate, mappa di wardriving Wi-Fi, flasher ESP32, Flipper Lab |

::: tip Unleashed
Unleashed è pienamente compatibile con qFlipper ufficiale e con l'app mobile Flipper ufficiale. Il modo più rapido per
installare o aggiornare Unleashed è il [Web Installer](/it/mobile/web-tools#unleashed-web-installer) in un browser
Chromium.
:::

::: warning Una connessione alla volta
Solo un programma alla volta può usare la porta seriale USB del Flipper. Chiudi qFlipper prima di usare Flipper Lab, il
Web Installer, un terminale CLI o l'U2F, e tieni aperta una sola scheda di Flipper Lab.
:::

## Pagine

- [qFlipper](/it/mobile/qflipper)
- [App mobile Flipper](/it/mobile/mobile-app)
- [App companion qUnleashed](/it/mobile/qunleashed-app)
- [Strumenti web](/it/mobile/web-tools)
