---
title: Web tools
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/apps]
sources: [unleashed-readme, unleashed-docs, flipper-docs]
---
# Web tools

Several Flipper tools run right in the browser, nothing to install. Tools that talk to the Flipper over USB need the
**Web Serial API**, so use **Chrome, Edge or another Chromium-based browser**.

::: warning Close qFlipper first
A browser tool cannot connect while qFlipper (or a second Flipper Lab tab) holds the Flipper's serial port. This is
the most common reason "Chrome does not see the Flipper".
:::

## Unleashed tools

| Tool | Address | What it does |
|---|---|---|
| Unleashed Web Installer | [web.unleashedflip.com](https://web.unleashedflip.com) | install or update Unleashed (Release or Dev) over USB |
| Dev builds | [dev.unleashedflip.com](https://dev.unleashedflip.com) | automatic testing builds from the dev branch with new features |
| Sub-GHz & Coordinates Map | [map.unleashedflip.com](https://map.unleashedflip.com) | view Sub-GHz wardriving files and any other files with coordinates on a map |
| Wi-Fi Wardriving Map | [wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) | combine and display several WiGLE-format captures (ESP32 Marauder and others) |
| ESP32 Web Flasher | [espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) | flash popular ESP32 modules from the browser |

### Unleashed Web Installer

The recommended way to install Unleashed.

1. Make sure a **microSD card** is inserted.
2. Close qFlipper. Connect the Flipper with a USB data cable.
3. Open [web.unleashedflip.com](https://web.unleashedflip.com) in a Chromium browser.
4. Press **Connect** and choose your Flipper in the browser's pop-up.
5. Select the **Release** or **Dev** branch.
6. Press **Install** and wait. When it finishes, all assets are installed and the Flipper boots into Unleashed.

Alternatively, every [GitHub release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) has an
**Install via Web Updater** link that opens the release in Flipper Lab's web updater: press **Connect**, then
**Install**. Full guide: [Installing Unleashed](/start/install).

### Sub-GHz & Coordinates Map

[map.unleashedflip.com](https://map.unleashedflip.com) puts your Sub-GHz captures with coordinates (for example from
Sub-GHz wardriving with a GPS module) and any other files that contain coordinates on a map.

### Wi-Fi Wardriving Map

[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com) merges multiple **WiGLE-formatted** captures, from
ESP32 Marauder and similar tools, and shows the access points on one map. See [ESP32 and Wi-Fi modules](/gpio/esp32).

### ESP32 Web Flasher

[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com) flashes popular ESP32 modules from the browser,
with no flashing tools to install. See [ESP32](/gpio/esp32) and [Dev board](/gpio/devboard).

## Flipper Lab (official)

[lab.flipper.net](https://lab.flipper.net) is the official web toolbox. It works with Unleashed:

- [Apps](https://lab.flipper.net/apps): the official app catalog, install / update / delete apps over USB, see
  [Apps on the SD card](/apps/sd-card-apps).
- [CLI](https://lab.flipper.net/cli): a terminal for the Flipper's command line, see [CLI](/dev/cli).
- [Pulse Plotter](https://lab.flipper.net/pulse-plotter): visualise Sub-GHz RAW signals, useful to analyse an unknown
  remote.
- The **web updater** used by the "Install via Web Updater" links.

## Other links

- Unleashed home page: [flipperunleashed.com](https://flipperunleashed.com)
- Direct `.tgz` update links: [unleashedflip.com](https://unleashedflip.com)
- Directory JSON for uFBT builds: [up.unleashedflip.com/directory.json](https://up.unleashedflip.com/directory.json)

::: danger Beware of fakes
[DarkFlippers/unleashed-firmware](https://github.com/DarkFlippers/unleashed-firmware) is the only official page of the
project. There are no paid, premium or closed-source versions; anyone offering one is a scammer.
:::

## Related pages

- [Installing Unleashed](/start/install)
- [qFlipper](/mobile/qflipper)
- [qUnleashed companion app](/mobile/qunleashed-app)
