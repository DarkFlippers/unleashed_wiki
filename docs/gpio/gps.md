---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

There are two ways to give the Flipper a location:

| Option | Hardware | How it works |
|---|---|---|
| **GPS service (companion location)** | None: a phone or computer connected over USB or Bluetooth | Apps ask the connected companion app for its location via RPC |
| **NMEA GPS module** | A serial GPS receiver on the GPIO UART | The `[NMEA] GPS` plugin reads NMEA sentences from the module |

## GPS service (companion location)

::: tip Unleashed
The Unleashed firmware contains a `gps` system service (record `gps`, started at boot). It doesn't use any GPIO pins:
it forwards location requests over the active **RPC session** (USB or Bluetooth) to the companion app, which answers
with the phone's / computer's position.
:::

What an app gets from it:

| Field | Unit |
|---|---|
| Latitude, longitude | degrees × 10⁷ |
| Heading | degrees × 100 (0…36000) |
| Speed | mm/s |
| Altitude | cm |
| Accuracy | mm |
| Satellites | count |

Apps can request a single fix (`gps_request_location()`), a stream at **1–10 Hz** (`gps_request_stream()` /
`gps_stop_stream()`), and can also send a location back to the companion (`gps_report_location()`). The companion can
answer with an error: not supported, no permission, location disabled, unknown error.

### Trying it out

The source tree includes two example apps by @apfxtech (category `Examples`, built as FAPs):

- **`[RPC] GPS Click`** — one-shot request: press <kbd>OK</kbd> to get the location; shows latitude, longitude,
  course, speed, altitude, satellites and accuracy. <kbd>BACK</kbd> exits.
- **`[RPC] GPS Stream`** — continuous stream of the same data.

Messages you may see:

| Message | Meaning |
|---|---|
| `No USB/BLE connection` | No RPC session: connect the companion app over USB or Bluetooth |
| `GPS not available` | The companion doesn't support location |
| `Permission denied` | Location permission not granted to the companion app |
| `Location disabled` | Location services are off on the phone / computer |
| `No response` | The companion didn't answer in time |
| `Waiting for data...` | Stream started, no fix yet |

The companion app must support these RPC GPS requests; check your companion app (see [Mobile](/mobile/)).

App developers: include `<gps/gps.h>` and open the record with `furi_record_open(RECORD_GPS)`; the header also has
helpers to format coordinates, heading, speed, altitude and accuracy.

## NMEA GPS module on the UART

For a location without a phone, connect a serial GPS receiver (most modules that output NMEA sentences at 3.3 V logic).

Wiring (USART):

| Flipper pin | GPS module |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) or 1 (5V) | VCC (check the module's supply range) |
| 8, 11 or 18 (GND) | GND |

Then open the `[NMEA] GPS` plugin from the extra app packs. Setup, baud rate and supported modules are in its
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
The GPS module and other UART users (Wi-Fi boards, SIM800, expansion modules, log output) share pins 13/14. If the
plugin gets no data, check `Settings → Expansion Modules → Listen UART` and `Settings → System → Log Device`.
:::

## Apps

Apps that work with a GPS module, all from the app packs:

| App | Pack | What it does |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Position from any NMEA GPS module on UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Shows and logs data from u-blox GPS modules over I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | NMEA tracker with breadcrumb navigation |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | File browser that sorts your files by distance from where you are |

Full list of module apps: [Modules and their apps](/gpio/module-apps).

## Related

- [ESP32 & Wi-Fi](/gpio/esp32) — wardriving map
- [External modules](/gpio/external-modules)
- [GPIO pinout](/gpio/pinout)
