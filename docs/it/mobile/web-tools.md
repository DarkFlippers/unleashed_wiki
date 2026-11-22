---
title: Strumenti web
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Strumenti web

Diversi strumenti per il Flipper girano direttamente nel browser, senza nulla da installare. Quelli che comunicano con
il Flipper via USB richiedono la **Web Serial API**, quindi usa **Chrome, Edge o un altro browser basato su
Chromium**.

::: warning Chiudi prima qFlipper
Uno strumento nel browser non può connettersi mentre qFlipper (o una seconda scheda di Flipper Lab) occupa la porta
seriale del Flipper. È il motivo più comune per cui "Chrome non vede il Flipper".
:::

## Strumenti di Unleashed

| Strumento | Indirizzo | Cosa fa |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | installa o aggiorna Unleashed (Release o Dev) via USB |
| Build dev | [dev.unleashedflip.com](https://dev.unleashedflip.com) | build di test automatiche dal branch dev con le nuove funzioni |
| Mappa Sub-GHz e coordinate | [map.unleashedflip.com](https://map.unleashedflip.com) | mostra su una mappa i file di wardriving Sub-GHz e qualsiasi altro file con coordinate |
| Mappa di wardriving Wi-Fi | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | unisce e mostra più acquisizioni in formato WiGLE (ESP32 Marauder e altri) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | programma i moduli ESP32 più diffusi dal browser |

### Unleashed Web Installer {#unleashed-web-installer}

Il modo consigliato per installare Unleashed.

1. Assicurati che la **scheda microSD** sia inserita.
2. Chiudi qFlipper. Collega il Flipper con un cavo USB che trasporti dati.
3. Apri [web.unleashedflip.com](https://web.unleashedflip.com) in un browser Chromium.
4. Premi **Connect** e scegli il tuo Flipper nella finestra del browser.
5. Seleziona il branch **Release** o **Dev**.
6. Premi **Install** e attendi. Al termine tutti gli asset sono installati e il Flipper si avvia in Unleashed.

In alternativa, ogni [release su GitHub](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) ha un
link **Install via Web Updater** che apre la release nel web updater di Flipper Lab: premi **Connect**, poi
**Install**. Guida completa: [Installare Unleashed](/it/start/install).

### Mappa Sub-GHz e coordinate

[map.unleashedflip.com](https://map.unleashedflip.com) mostra su una mappa le tue acquisizioni Sub-GHz con coordinate
(per esempio da una sessione di wardriving Sub-GHz con un modulo GPS) e qualsiasi altro file che contenga coordinate.

### Mappa di wardriving Wi-Fi

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) unisce più acquisizioni in **formato WiGLE**, da
ESP32 Marauder e strumenti simili, e mostra gli access point su un'unica mappa. Vedi
[Moduli ESP32 e Wi-Fi](/it/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) è un flasher semplice da usare per i moduli ESP32
più diffusi che gira interamente nel browser, senza installare nessuno strumento di programmazione. Vedi
[ESP32](/it/gpio/esp32) e [Dev board](/it/gpio/devboard).

## Flipper Lab (ufficiale)

[lab.flipper.net](https://lab.flipper.net) è la raccolta ufficiale di strumenti web. Funziona con Unleashed:

- [Apps](https://lab.flipper.net/apps): il catalogo ufficiale delle app, per installare / aggiornare / eliminare app
  via USB, vedi [App sulla scheda SD](/it/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): un terminale per la riga di comando del Flipper, vedi [CLI](/it/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): visualizza i segnali Sub-GHz RAW, utile per analizzare un
  telecomando sconosciuto.
- Il **web updater** usato dai link "Install via Web Updater".

## Altri link

- Pagina principale di Unleashed: [flipperunleashed.com](https://flipperunleashed.com)
- Link diretti agli aggiornamenti `.tgz`: [unleashedflip.com](https://unleashedflip.com)
- JSON della directory per le build con uFBT:
  [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Attenzione ai falsi
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) è l'unica pagina ufficiale del
progetto. Non esistono versioni a pagamento, premium o closed source; chi te ne offre una è un truffatore.
:::

## Pagine correlate

- [Installare Unleashed](/it/start/install)
- [qFlipper](/it/mobile/qflipper)
- [App companion qUnleashed](/it/mobile/qunleashed-app)
