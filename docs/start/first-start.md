---
title: First start
order: 10
original: [https://docs.flipper.net/zero/basics/first-start, https://docs.flipper.net/zero/basics/sd-card, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md]
sources: [flipper-docs, unleashed-docs]
---
# First start

What to do in the first ten minutes with a new Flipper Zero, before you install Unleashed.

## 1. Power on

Press and hold <kbd>BACK</kbd> for about 3 seconds. The desktop appears, with your dolphin and the status bar:

![The Flipper desktop: the dolphin idle animation and the status bar with the SD card and battery icons](/screens/desktop/idle.png)

::: details The Flipper does not turn on
- The battery may be completely drained. Plug in the USB-C cable. The device turns on by itself after a short time.
- If it still shows nothing, hold <kbd>←</kbd> + <kbd>BACK</kbd> for 5 seconds (reboot).
- Still nothing: see [Key combos](/start/key-combos) and [Recovery](/start/recovery).
:::

## 2. Insert a microSD card

A microSD card is **required**. The card holds keys, cards, remotes, databases, the apps that come with the firmware,
and even the "internal" storage (see [microSD card](/start/sd-card)). The card is not included with the device.

1. Find the slot at the bottom of the Flipper.
2. Hold the card **with the pins facing up** and push it in until it clicks.
3. The status bar shows an SD card icon when the card is mounted.

A branded **16–32 GB** card is plenty. Cards up to 256 GB work, but large cards take longer to mount. Cheap no-name
cards can make the device slow or unstable.

## 3. Update the official firmware (first install only)

The Unleashed install guide asks you to **update to the latest official release first** if you are installing
Unleashed for the first time. This brings the bootloader, radio stack and internal data up to date.

- **qFlipper** (Windows/macOS/Linux): connect via USB, open the **Advanced controls** tab, set the **Update Channel**
  to **Release** and click **Update**.
- **Flipper Mobile App** (iOS/Android): turn on Bluetooth on the Flipper (**Main Menu → Settings → Bluetooth**),
  pair with the app, then tap **Update**. This takes about 10 minutes.

More on qFlipper and the mobile app: [qFlipper](/mobile/qflipper), [Mobile app](/mobile/mobile-app).

## 4. Install Unleashed

Use the **[Unleashed Web Installer](https://web.unleashedflip.com)**. It is the easiest method. All methods are
described in [Installing Unleashed](/start/install).

## 5. Basic setup

After installing, open **Main Menu → Settings** and check:

- **Clock & Alarm**: set the date and time;
- **System → Hand Orient**: `Lefty` if you hold the device in your left hand;
- **Desktop**: PIN, desktop clock (`Show Clock`), battery style (`Battery View`), quick-access apps;
- **Desktop → Change Flipper Name**: give your Flipper its own name ([Custom Flipper name](/start/custom-name)).

Every item is described in [Settings](/start/settings).

## Next steps

- Learn the buttons and hotkeys: [Controls](/start/controls)
- Explore the desktop: [Desktop](/start/desktop)
- See what Unleashed adds: [What Unleashed adds](/start/unleashed-features)
