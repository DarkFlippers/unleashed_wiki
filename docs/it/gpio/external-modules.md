---
title: Moduli esterni
order: 30
original: [https://docs.flipper.net/zero/gpio-and-modules, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SIM800.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz]
sources: [flipper-docs, unleashed-readme, unleashed-docs, unleashed-src]
---
# Moduli esterni

La maggior parte delle schede aggiuntive per il Flipper Zero si innesta direttamente nel connettore GPIO e comunica
su uno di tre bus: **SPI** (pin 2–5), **UART** (pin 13/14 o 15/16) o **I2C** (pin 15/16). Questa pagina è una mappa:
quali tipi di modulo esistono, quale firmware o app li pilota e quali pin occupano, così da capire quali possono
essere usati insieme.

## Tipi di modulo

| Modulo | Bus / pin | Pilotato da | Pagina |
|---|---|---|---|
| CC1101 esterno (Sub-GHz) | SPI 2–5, GDO0 sul 6, controllo ampli sul 7 | App Sub-GHz integrata (`Radio Settings → Module → External`) | [CC1101 esterno](/it/subghz/external-cc1101) |
| NRF24L01 (2,4 GHz) | SPI 2–5, CE sul 6 | Plugin NRF24 Sniffer / Mouse Jacker | [NRF24](/it/gpio/nrf24) |
| Schede Wi-Fi ESP32 / ESP8266, Wi-Fi Devboard | UART 13/14 (SWD 10/12 per il debug) | Plugin Marauder, Wi-Fi Scanner, Deauther; firmware Black Magic | [ESP32](/it/gpio/esp32), [Devboard](/it/gpio/devboard) |
| GSM SIM800C / SIM800L | UART 13/14 o 15/16, alimentazione dal pin 1 | App SIM800 integrata | [SIM800](/it/gpio/sim800) |
| GPS (NMEA) | UART | Plugin `[NMEA] GPS` | [GPS](/it/gpio/gps) |
| Video Game Module | UART 13/14, pin 2–7, alimentazione | Firmware del Flipper + firmware del modulo | [Video Game Module](/it/gpio/video-game-module) |
| Moduli di espansione (protocollo) | UART 13/14 o 15/16 | `Settings → Expansion Modules` | [Moduli di espansione](/it/gpio/expansion-modules) |
| LED IR esterno / booster IR | Pin 2 (PA7), 5 V sul pin 1 | App Infrared integrata (`GPIO Settings`) | vedi sotto |
| Sensori di temperatura / umidità / pressione | dipende dal sensore (vedi il README) | Plugin `Unitemp` | [README di Unitemp](https://github.com/quen0n/unitemp-flipperzero#readme) |
| Qualsiasi dispositivo I2C | I2C 15/16 | Plugin `i2c Tools`, comando CLI `i2c` | [App GPIO](/it/gpio/gpio-app) |
| ESP32-CAM | UART | Plugin Camera Suite | [Camera Suite](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |
| Casseforti Sentry Safe / Master Lock (due fili) | Pin 15 (C1) + GND 8 | Plugin SentrySafe | [SentrySafe](/it/apps/sentry-safe) |

::: tip Unleashed
Unleashed aggiunge direttamente nel firmware il supporto per:
- il **CC1101 esterno** su SPI hardware, con controllo dell'amplificatore e dei LED esterni (`Ext Amp & LEDs`, attivo
  per impostazione predefinita) in `Sub-GHz → Radio Settings`;
- i **moduli IR esterni** in `Infrared → GPIO Settings` (rilevamento automatico come nel firmware stock);
- l'app GSM **SIM800** (`Apps → GPIO → SIM800`).

I moduli radio esterni funzionano su qualsiasi firmware, non solo su Unleashed. La prima implementazione del CC1101
l'ha scritta @quen0n per Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307)); quella in uso oggi l'ha scritta **Skorp** nel firmware ufficiale,
ed è quella che usa Unleashed.

I plugin per tutto il resto (NRF24, Marauder, GPS, Unitemp, i2c Tools, Camera Suite…) sono nei pacchetti Base ed
Extra: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest). Vedi
[App sulla scheda SD](/it/apps/sd-card-apps).
:::

## Conflitti sui pin

I moduli che condividono un bus non possono funzionare contemporaneamente senza qualche attenzione. I conflitti più
comuni:

| Pin | Occupati da |
|---|---|
| 2, 3, 4, 5 | SPI: CC1101 esterno, NRF24 (MOSI, MISO, CS, SCK) |
| 6 | GDO0 del CC1101 / CE dell'NRF24 |
| 7 | Controllo dell'amplificatore del CC1101 (moduli E07) |
| 13, 14 | USART: schede Wi-Fi, SIM800, moduli di espansione, Video Game Module, bridge USB-UART, uscita dei log |
| 15, 16 | LPUART oppure I2C (non entrambi insieme) |
| 10, 12 | Debug SWD (Devboard) |

Se usi una scheda "combo" che porta più radio (per esempio CC1101 + NRF24 + ESP32 sullo stesso PCB), segui la
documentazione di quella scheda per sapere quali pin e quali impostazioni dei plugin usa ciascuna radio.

## Moduli IR esterni

1. Collega l'ingresso del driver del LED IR al **pin 2 (A7)**, la massa alla massa e l'alimentazione al pin 1 (5 V)
   se il modulo la richiede.
2. Apri `Main Menu → Infrared → GPIO Settings`.
3. Imposta `Signal Output`:
   - `Flipper` — il LED IR integrato;
   - `2 (A7)` — il modulo esterno sul pin 2;
   - `Detect` — il firmware rileva automaticamente il modulo collegato.
4. Con `2 (A7)` selezionato puoi anche commutare `5V on GPIO` da qui. Con `Detect` la voce dei 5 V mostra `Auto`.

Per l'uso dei telecomandi vedi la sezione [Infrarossi](/it/infrared/).

## Regole generali

1. **Spegni prima di collegare.** Collegare a caldo grandi condensatori può corrompere la scheda SD.
2. **Logica a 3,3 V.** Non pilotare le uscite del Flipper verso logiche a 5 V; gli ingressi sono tolleranti a 5 V
   solo mentre sono configurati come ingressi.
3. **Rispetta i limiti di corrente:** 1,2 A sul pin 1 e sul pin 9, 20 mA per pin di I/O. Vedi il
   [pinout](/it/gpio/pinout).
4. **Incrocia TX e RX** sui moduli UART: il TX del Flipper va all'RX del modulo.
5. **Inserisci a fondo.** Un modulo inserito a metà fa contatto in modo intermittente.

## Argomenti correlati

- [Pinout GPIO](/it/gpio/pinout)
- [App GPIO](/it/gpio/gpio-app)
- [Moduli di espansione](/it/gpio/expansion-modules)
- [Moduli e le loro app](/it/gpio/module-apps)
