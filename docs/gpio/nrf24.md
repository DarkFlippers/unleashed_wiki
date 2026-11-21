---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2.4 GHz)

The **nRF24L01(+)** from Nordic Semiconductor is a cheap 2.4 GHz transceiver used in many wireless mice, keyboards
and hobby projects. It connects to the Flipper over SPI.

## Apps

The Base pack has the Sniffer and the Mouse Jacker, which the guide below uses. The Extra pack adds six more:

| App | Pack | What it does |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Captures wireless-keyboard addresses for Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Injects keystrokes into a vulnerable wireless keyboard or mouse receiver |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | General nRF24L01 utility |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Scans for and decodes nRF24 packets |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Shows which of the 2.4 GHz channels are busy |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Reads and writes named fields on an nRF24 device from a config file |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Variant build of the Sniffer above |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Variant build of the Mouse Jacker above |

Driver, Sniffer and Mouse Jacker by [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). All of these apps are in the
[app packs](https://github.com/xMasterX/all-the-plugins/releases/latest) — see [Modules and their apps](/gpio/module-apps).

::: warning Legal
For education and for your own equipment only. Injecting keystrokes into someone else's computer is illegal.
:::

## Wiring

| Flipper pin | nRF24L01 pin |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — leave unconnected |

![nRF24L01 to Flipper Zero wiring](/img/remote/511927f9f2d850ad.png)

*Pinout by UberGuidoZ.*

The nRF24 uses the same SPI pins (2–5) as an [external CC1101](/subghz/external-cc1101). Connect only one of them
at a time, unless you use a combo board designed for both (then follow its documentation).

## Usage

1. Power the Flipper off, connect the module, power on.
2. Open **NRF24: Sniffer** (`Apps → GPIO`). Start scanning; use the buttons to switch modes and channels as shown on
   screen.
3. Wait until the sniffer finds an **address**.
4. Open **NRF24: Mouse Jacker**.
5. Select the address, then open the Bad USB script to send.
6. The keystrokes are transmitted to the target dongle.

Demo video: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). Script syntax is the same as for
[Bad USB](/badusb/script-format).

## If the module is flaky

The nRF24 draws current in short bursts. If it works only sometimes, add a capacitor across **VCC and GND** right at
the module:

- 3.3 µF to 10 µF electrolytic (mind the polarity: negative to GND). A single 10 µF is usually enough.
- Optionally a 0.1 µF ceramic in parallel: the large cap handles slow changes, the small one fast switching spikes.

The "plus" (nRF24L01+PA+LNA) versions with an amplifier need this even more.

![Capacitor on the nRF24 module](/img/remote/218b238eb91c9e38.jpg)

## Credits

- Sniffing technique: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- MouseJack vulnerabilities: Marc Newlin, [Bastille research](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Driver inspired by [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html); MouseJack code
  inspired by [JackIt](https://github.com/insecurityofthings/jackit).

## Related

- [External modules](/gpio/external-modules)
- [Bad USB](/badusb/usage)
- [GPIO pinout](/gpio/pinout)
