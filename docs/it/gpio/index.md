---
title: GPIO e moduli
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# GPIO e moduli

Il connettore a 18 pin sul lato superiore del Flipper Zero lo trasforma in uno strumento hardware: può alimentare e
dialogare con moduli esterni, fare da adattatore USB-UART, pilotare i pin a mano per fare prove e fungere da target
per un debugger hardware.

![Connettore GPIO del Flipper Zero](/img/remote/f9f4fe12522d6f9d.png)

## Le basi

| Pagina | Cosa contiene |
|---|---|
| [Pinout GPIO](/it/gpio/pinout) | Tutti i 18 pin, tensioni, limiti di corrente, i 5 V sul pin 1, tolleranza 3,3 V / 5 V |
| [App GPIO](/it/gpio/gpio-app) | `Main Menu → GPIO`: USB-UART Bridge, GPIO Manual Control, 5V on GPIO; comandi CLI `gpio` e `i2c` |
| [Moduli esterni](/it/gpio/external-modules) | Panoramica dei tipi di modulo e di quali pin usa ciascuno |
| [Moduli di espansione](/it/gpio/expansion-modules) | `Settings → Expansion Modules` e l'Expansion Module Protocol |
| [Moduli e le loro app](/it/gpio/module-apps) | Tutti i moduli supportati dai pacchetti di app, e cosa fa ciascuna app |

## Moduli

| Pagina | Modulo |
|---|---|
| [CC1101 esterno](/it/subghz/external-cc1101) | Radio Sub-GHz con uno stadio d'ingresso più potente (trattato nella sezione Sub-GHz) |
| [ESP32 / Wi-Fi](/it/gpio/esp32) | Wi-Fi Devboard, ESP32 Marauder, il flasher web di Unleashed e la mappa di wardriving |
| [NRF24](/it/gpio/nrf24) | Sniffer nRF24L01 a 2,4 GHz e MouseJack |
| [SIM800](/it/gpio/sim800) | Modulo GSM: chiamate, SMS, rubrica, USSD (app integrata in Unleashed) |
| [GPS](/it/gpio/gps) | Posizione dal telefono abbinato (servizio GPS) e moduli GPS NMEA su UART |
| [Video Game Module](/it/gpio/video-game-module) | Modulo RP2040 con uscita video e sensore di movimento |

## Wi-Fi Developer Board

| Pagina | Cosa contiene |
|---|---|
| [Devboard: primi passi](/it/gpio/devboard) | Preparare il Flipper, collegare la scheda, connessione via USB e Wi-Fi |
| [Devboard: debug e log](/it/gpio/devboard-debug) | Black Magic / DAPLink, debug con VS Code, lettura dei log UART |
| [Devboard: aggiornamento del firmware](/it/gpio/devboard-firmware) | Programmare il firmware della scheda con uFBT |

::: tip Unleashed
Unleashed include strumenti GPIO aggiuntivi già pronti: l'app [SIM800](/it/gpio/sim800)
(`Apps → GPIO → SIM800`), il supporto per il CC1101 esterno con controllo dell'amplificatore nel Sub-GHz, l'uscita per
i moduli IR esterni in `Infrared → GPIO Settings` e un ampio insieme di plugin GPIO nei pacchetti di app extra. Vedi
[Moduli esterni](/it/gpio/external-modules).
:::

::: warning Prima di collegare qualcosa
Spegni il Flipper prima di collegare un modulo e inserisci il modulo a fondo nel connettore. Collegare a caldo un
modulo con un grande carico capacitivo può corrompere la scheda microSD, perché la scheda e il pin 9 condividono la
stessa linea a 3,3 V.
:::
