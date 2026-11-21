---
title: "JavaScript: panoramica"
sidebarTitle: "JS: panoramica"
order: 200
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_about.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript su Flipper Zero

Scrivere un'app per Flipper Zero significava un tempo usare il C, una toolchain completa e leggere molto codice sorgente di altre app. Il firmware include ora un **motore JavaScript integrato**, così puoi scrivere un semplice file `.js`, copiarlo sulla scheda SD ed eseguirlo direttamente dal dispositivo. Non serve compilare su un PC, e gli script sono facili da condividere.

- Gli script risiedono in `/ext/apps/Scripts/` e si avviano da `Main Menu → Apps → Scripts`, oppure dalla CLI con `js <path>`.
- Il motore è basato su [mJS](https://github.com/cesanta/mjs), un interprete JavaScript progettato per i microcontrollori: richiede meno di 50 KB di flash e circa 2 KB di RAM. Il Flipper mantiene il nucleo di mJS e vi aggiunge alcune estensioni, come gli array binari compatti (`ArrayBuffer`, array tipizzati).
- Gli script possono usare la GUI, i pulsanti, l'USB HID (BadUSB), i GPIO, l'UART, il filesystem e altro ancora tramite i **moduli** caricati con `require()`.

::: warning mJS non è un motore da browser
mJS supporta un sottoinsieme di JavaScript. In particolare **non esistono le closure** (una funzione non può usare le variabili dello scope circostante; vedi [Event loop](/it/dev/js-event-loop) per l'alternativa), le stringhe sono a un byte senza supporto UTF-8 e molti oggetti della libreria standard non sono presenti. Consulta il [README di mJS](https://github.com/cesanta/mjs) per l'elenco completo dei limiti.
:::

## Per iniziare

1. [La tua prima app JS](/it/dev/js-first-app): scrivere uno script, copiarlo sul Flipper, eseguirlo dal menu o dalla CLI.
2. [SDK JavaScript](/it/dev/js-sdk): TypeScript, completamento del codice e caricamento con un solo comando grazie a `npm start`.
3. [Usare i moduli JS](/it/dev/js-modules): come funziona `require()`.

## Riferimento del linguaggio

- [Tipi di dati](/it/dev/js-data-types)
- [Funzioni integrate](/it/dev/js-builtin): `print`, `delay`, `require`, `load`, metodi su stringhe/array, controlli di compatibilità dell'SDK.

## Riferimento dei moduli

| Modulo | Nome per `require()` | Pagina |
|---|---|---|
| Event loop | `event_loop` | [Event loop](/it/dev/js-event-loop) |
| GUI | `gui`, `gui/*` | [GUI](/it/dev/js-gui), [View della GUI](/it/dev/js-gui-views) |
| BadUSB (tastiera USB HID) | `badusb` | [BadUSB](/it/dev/js-badusb) |
| Informazioni sul dispositivo | `flipper` | [Flipper](/it/dev/js-flipper) |
| GPIO, ADC, PWM | `gpio` | [GPIO](/it/dev/js-gpio) |
| Math | `math` | [Math](/it/dev/js-math) |
| Notifiche LED / vibrazione / suono | `notification` | [Notification](/it/dev/js-notification) |
| UART | `serial` | [Serial](/it/dev/js-serial) |
| File e cartelle | `storage` | [Storage](/it/dev/js-storage) |

Script di esempio per ogni modulo sono installati con il firmware in `/ext/apps/Scripts/js_examples/` (per esempio `gui.js`, `badusb_demo.js`, `gpio.js`, `storage.js`). Leggerli è il modo più rapido per imparare le API.

## Extra di Unleashed: moduli senza documentazione dedicata {#unleashed-extras}

::: tip Unleashed
Unleashed riporta `flipper.firmwareVendor === "unleashed"` e include **moduli JS aggiuntivi** che il firmware di serie non ha. Non sono trattati dalla documentazione JS ufficiale, quindi le pagine qui sotto sono scritte partendo dai sorgenti del firmware (`applications/system/js_app/modules/`) e dalle definizioni TypeScript in `packages/fz-sdk/`. Ogni modulo è anche una "feature" dell'SDK, quindi verificane la presenza con `doesSdkSupport([...])` o `checkSdkFeatures([...])` (vedi [Funzioni integrate](/it/dev/js-builtin#sdk-compatibility)) per mantenere lo script funzionante su altri firmware.
:::

L'elenco completo delle feature aggiuntive riportate da Unleashed è: `baseline`, `gpio-pwm`, `gui-widget`, `serial-framing`, `gui-widget-extras`, `blebeacon`, `i2c`, `spi`, `infrared-send`, `subghz`, `usbdisk`, `usbdisk-createimage`, `vgm`.

| Modulo | Nome della feature | Funzione | Pagina |
|---|---|---|---|
| `subghz` | `subghz` | Controlla la radio Sub-GHz (CC1101 interno o esterno): RX, RSSI, frequenza, trasmissione di file `.sub` | [JS: subghz](/it/dev/js-subghz) |
| `infrared` | `infrared-send` | Invia segnali IR per protocollo o come temporizzazioni grezze | [JS: infrared](/it/dev/js-infrared) |
| `blebeacon` | `blebeacon` | Trasmette pacchetti di advertisement BLE personalizzati (extra beacon) | [JS: blebeacon](/it/dev/js-blebeacon) |
| `usbdisk` | `usbdisk` | Emula un dispositivo di archiviazione di massa USB a partire da un'immagine disco | [JS: usbdisk](/it/dev/js-usbdisk) |
| `i2c` | `i2c` | Dialoga con dispositivi I2C sul connettore GPIO | [JS: i2c](/it/dev/js-i2c) |
| `spi` | `spi` | Dialoga con dispositivi SPI sul bus SPI esterno | [JS: spi](/it/dev/js-spi) |
| `vgm` | `vgm` | Legge la IMU (pitch/roll/yaw) del Video Game Module | [JS: vgm](/it/dev/js-vgm) |

Anche il modulo GUI offre view assenti dalla documentazione ufficiale: `button_menu`, `button_panel`, `menu`, `number_input`, `popup`, `vi_list`. Sono descritte in [View della GUI](/it/dev/js-gui-views).

Le API del firmware che questa wiki non copre si cercano nel [riferimento API Doxygen](https://developer.flipper.net/flipperzero/doxygen/) ufficiale.

## Pagine correlate

- [Scrivere app in C](/it/dev/first-app-c), per quando JS non è abbastanza rapido o flessibile.
- [Formato degli script BadUSB](/it/badusb/script-format), la classica alternativa DuckyScript al modulo JS `badusb`.
