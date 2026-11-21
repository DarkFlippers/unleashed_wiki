---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (by @MatthewKuKanich) turns the Flipper's Bluetooth into a tracker beacon. The Flipper broadcasts
the same BLE advertisement as a tag, and phones of the tracking network nearby report its location, so a lost
Flipper can be found in the tag owner's app.

Supported tag types: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag** and
**Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper ships with the firmware, and Unleashed also installs a small startup hook: if the beacon was active
when the Flipper was switched off, it **starts again automatically after a reboot**, without opening the app. The
beacon keeps running in the background while you use other apps.
:::

::: warning
Only use it with your own tags and devices. Tracking other people may be illegal where you live.
:::

## What you need

The Flipper needs the tag's **MAC address** and **payload** (or a key file). You get them in one of two ways:

- **Clone an existing tag** (simplest; the location then shows up in the tag owner's normal app).
- **Generate your own keys** with the OpenHaystack method (no physical tag needed, Apple network only; you view the
  location with OpenHaystack or a Mac-less alternative).

### Option A: clone an existing tag

1. Pair the AirTag or SmartTag with your phone as usual.
2. Put it into "lost" mode: keep it away from the phone it is registered to for about 15 minutes.
3. On an Android phone install **nRF Connect** (the iOS version does not show the raw data).
4. In nRF Connect set the filter to the tag's brand (Apple or Samsung), set RSSI to the lowest setting and scan.
5. When the tag shows up as a "FindMy" device, open **Raw** / **View Raw** and note the **payload** and the **MAC
   address**. You can also export it as a `.txt` file.
6. **Immediately remove the tag's battery**, otherwise it rotates its key and MAC and your copy stops working.

### Option B: OpenHaystack keys

1. Download `generate_keys.py` from the [FindMyFlipper repository](https://github.com/MatthewKuKanich/FindMyFlipper)
   and run it (it needs `python3 -m pip install cryptography`).
2. It gives you a **Private Key**, **Public Key**, **Payload** and **MAC Address**, and a `.keys` file.
3. Keep the Private Key: you need it to receive location reports.
4. View locations in [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS below 14) or without a
   Mac with [macless-haystack](https://github.com/dchristl/macless-haystack) or
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Setting up the Flipper

1. Copy your nRF Connect `.txt` export or the `.keys` file to `/ext/apps_data/findmy/` on the SD card (or skip this
   and enter the data by hand).
2. Open `Apps → Bluetooth → FindMy Flipper` and press <kbd>→</kbd> (**Config**).
3. Choose **Register Tag**, then the tag type: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` or
   `Google Find My`.
4. Choose how to import:
   - `nRF Connect (.txt)`: pick the exported file;
   - `OpenHaystack (.keys)`: pick the key file;
   - `Register Tag Manually`: type the MAC address, then the payload.
5. Go back to the main screen and press <kbd>OK</kbd>. It changes to `Broadcast Active`.

## Main screen

| Button | Action |
|---|---|
| <kbd>OK</kbd> | start / stop the beacon (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | change the broadcast interval |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | leave the app with the beacon still running in the background |
| <kbd>Back</kbd> | quit the app |

## Config menu

| Item | Values | Notes |
|---|---|---|
| Broadcast Interval | 1-10 s (Google: 1-2 s) | how often the beacon is sent; Google requires at least every 2 s |
| Transmit Power | 0-6 dBm | more power = more range, more battery use |
| Register Tag | | tag type and import (above) |
| Show MAC | Yes / No | show the MAC on the main screen |

The app saves its state in `/ext/apps_data/findmy/findmy_state.txt`; that is what lets the beacon resume after a
reboot.

## Tracking

- **AirTag clone**: the Flipper appears as your AirTag in the Find My app.
- **SmartTag clone**: in SmartThings (SmartThings Find), on a phone or in the browser.
- **OpenHaystack keys**: in OpenHaystack or macless-haystack.

## Troubleshooting

- **Location never updates**: the tag's key/MAC rotated before you removed its battery; capture it again.
- **Beacon stops after reboot**: check that the SD card is inserted (the state file is on it) and that the beacon was
  `Broadcast Active` before switching off.
- **Battery drains faster**: increase the broadcast interval and lower the transmit power.

## Related pages

- [Apps that ship with Unleashed](/apps/catalog)
- [Settings](/start/settings)
