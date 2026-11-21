---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 GHz)

L'**nRF24L01(+)** di Nordic Semiconductor è un transceiver a 2,4 GHz economico, usato in molti mouse e tastiere
wireless e in tanti progetti hobbistici. Si collega al Flipper via SPI.

## App

Il pacchetto Base contiene lo Sniffer e il Mouse Jacker, quelli che usa la guida qui sotto. Il pacchetto Extra ne aggiunge altri sei:

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Raccoglie gli indirizzi delle tastiere wireless per Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Inietta tasti nel ricevitore vulnerabile di una tastiera o di un mouse wireless |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Utility generica per nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Cerca e decodifica i pacchetti nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Mostra quali canali a 2,4 GHz sono occupati |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Legge e scrive campi con nome di un dispositivo nRF24 da un file di configurazione |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Variante dello Sniffer qui sopra |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Variante del Mouse Jacker qui sopra |

Driver, Sniffer e Mouse Jacker di [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Tutte queste app sono nei
[pacchetti di app](https://github.com/xMasterX/all-the-plugins/releases/latest) — vedi [Moduli e le loro app](/it/gpio/module-apps).

::: warning Aspetti legali
Solo per scopi didattici e sui tuoi dispositivi. Iniettare pressioni di tasti nel computer di qualcun altro è
illegale.
:::

## Collegamenti

| Pin del Flipper | Pin dell'nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — lascialo scollegato |

![Collegamento dell'nRF24L01 al Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Pinout di UberGuidoZ.*

L'nRF24 usa gli stessi pin SPI (2–5) di un [CC1101 esterno](/it/subghz/external-cc1101). Collegane solo uno alla
volta, a meno che non usi una scheda combo progettata per entrambi (in quel caso segui la sua documentazione).

## Uso

1. Spegni il Flipper, collega il modulo, riaccendi.
2. Apri **NRF24: Sniffer** (`Apps → GPIO`). Avvia la scansione; usa i pulsanti per cambiare modalità e canali come
   indicato sullo schermo.
3. Attendi che lo sniffer trovi un **indirizzo**.
4. Apri **NRF24: Mouse Jacker**.
5. Seleziona l'indirizzo, poi apri lo script Bad USB da inviare.
6. Le pressioni dei tasti vengono trasmesse al dongle bersaglio.

Video dimostrativo: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). La sintassi degli script è la stessa di
[Bad USB](/it/badusb/script-format).

## Se il modulo è instabile

L'nRF24 assorbe corrente a brevi impulsi. Se funziona solo a volte, aggiungi un condensatore tra **VCC e GND**
direttamente sul modulo:

- un elettrolitico da 3,3 µF a 10 µF (attenzione alla polarità: il negativo a GND). Di solito un solo da 10 µF è
  sufficiente.
- facoltativamente un ceramico da 0,1 µF in parallelo: il condensatore grande gestisce le variazioni lente, quello
  piccolo i picchi di commutazione rapidi.

Le versioni "plus" (nRF24L01+PA+LNA) con amplificatore ne hanno ancora più bisogno.

![Condensatore sul modulo nRF24](/img/remote/218b238eb91c9e38.jpg)

## Crediti

- Tecnica di sniffing: Travis Goodspeed,
  [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Vulnerabilità MouseJack: Marc Newlin,
  [ricerca Bastille](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Driver ispirato a [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html); il codice di
  MouseJack è ispirato a [JackIt](https://github.com/insecurityofthings/jackit).

## Argomenti correlati

- [Moduli esterni](/it/gpio/external-modules)
- [Bad USB](/it/badusb/usage)
- [Pinout GPIO](/it/gpio/pinout)
