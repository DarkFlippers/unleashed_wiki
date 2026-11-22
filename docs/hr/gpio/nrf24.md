---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2.4 GHz)

**nRF24L01(+)** tvrtke Nordic Semiconductor jeftin je 2.4 GHz primopredajnik koji se koristi u mnogim bežičnim miševima, tipkovnicama
i hobi projektima. Na Flipper se spaja putem SPI sabirnice.

## Aplikacije

Osnovni paket (Base) sadrži Sniffer i Mouse Jacker, koje koriste upute u nastavku. Dodatni paket (Extra) dodaje još šest aplikacija:

| Aplikacija | Paket | Što radi |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Hvata adrese bežičnih tipkovnica za Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Ubrizgava pritiske tipki u ranjivi prijamnik bežične tipkovnice ili miša |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Opći uslužni program za nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Traži i dekodira nRF24 pakete |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Prikazuje koji su od 2.4 GHz kanala zauzeti |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Čita i zapisuje imenovana polja na nRF24 uređaju iz konfiguracijske datoteke |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Alternativna inačica gornjeg Sniffera |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Alternativna inačica gornjeg Mouse Jackera |

Upravljački program, Sniffer i Mouse Jacker izradio je [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Sve ove aplikacije nalaze se u
[paketima aplikacija](https://github.com/xMasterX/all-the-plugins/releases/latest) — pogledajte [Moduli i njihove aplikacije](/hr/gpio/module-apps).

::: warning Pravna napomena
Samo u obrazovne svrhe i isključivo za vlastitu opremu. Ubrizgavanje pritisaka tipki u tuđe računalo je nezakonito.
:::

## Spajanje

| Pin Flippera | Pin nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — ostaviti nepovezano |

![Spajanje modula nRF24L01 na Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Raspored pinova izradio UberGuidoZ.*

nRF24 koristi iste SPI pinove (2–5) kao [vanjski CC1101](/hr/subghz/external-cc1101). Povezujte samo jedan modul
istodobno, osim ako ne koristite kombiniranu pločicu dizajniranu za oba (u tom slučaju slijedite njezinu dokumentaciju).

## Korištenje

1. Isključite Flipper, spojite modul, uključite Flipper.
2. Otvorite **NRF24: Sniffer** (`Apps → GPIO`). Pokrenite skeniranje; gumbima mijenjajte načine rada i kanale kako je
   prikazano na zaslonu.
3. Pričekajte dok sniffer ne pronađe **adresu**.
4. Otvorite **NRF24: Mouse Jacker**.
5. Odaberite adresu, zatim otvorite Bad USB skriptu koju želite poslati.
6. Pritisci tipki šalju se ciljnom USB prijamniku.

Demo video: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). Sintaksa skripte jednaka je kao za
[Bad USB](/hr/badusb/script-format).

## Ako je modul nestabilan

nRF24 vuče struju u kratkim impulsima. Ako radi samo povremeno, dodajte kondenzator između **VCC i GND** neposredno na
samom modulu:

- elektrolitski od 3.3 µF do 10 µF (pazite na polaritet: minus na GND). Jedan od 10 µF obično je dovoljan.
- Opcionalno keramički od 0.1 µF paralelno: veći kondenzator ublažava spore promjene, a manji brze sklopne šiljke.

Inačicama "plus" (nRF24L01+PA+LNA) s pojačalom ovo je još potrebnije.

![Kondenzator na modulu nRF24](/img/remote/218b238eb91c9e38.jpg)

## Zasluge

- Tehnika prisluškivanja: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Ranjivosti MouseJack: Marc Newlin, [Bastille research](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Upravljački program nadahnut bibliotekom [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html); MouseJack kôd
  nadahnut projektom [JackIt](https://github.com/insecurityofthings/jackit).

## Povezano

- [Vanjski moduli](/hr/gpio/external-modules)
- [Bad USB](/hr/badusb/usage)
- [Raspored GPIO pinova](/hr/gpio/pinout)
