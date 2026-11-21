---
title: Custom Flipper name
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Custom Flipper name

Every Flipper has a factory name. It appears in the Passport, in **About**, in Bluetooth device lists and in qFlipper.
Unleashed lets you replace it with your own name.

::: tip Unleashed
Stock firmware has no menu to rename the device. In Unleashed it is in **Settings → Desktop → Change Flipper Name**,
and the name **survives firmware updates** because it is stored on the microSD card.
:::

## Set a name

1. Go to **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Type the new name. The keyboard header says `Leave empty for default`.
   - **2 to 8 characters**;
   - **only Latin letters and digits** (`A–Z`, `a–z`, `0–9`). Anything else shows *"Please only enter letters and numbers!"*.
3. Select **Save**.
4. The message **`Name is set!`** / *"Your Flipper will be restarted on exit."* appears.
5. Leave Settings with <kbd>BACK</kbd>. The Flipper **reboots automatically**.
6. After the reboot, the new name shows in the Passport, in **Settings → About** and over Bluetooth.

## Reset to the factory name

1. Open **Settings → Desktop → Change Flipper Name**.
2. Delete all characters and leave the field **empty**.
3. Select **Save** and leave Settings. The Flipper reboots with its original name.

## How it works

- The name is saved to **`/ext/dolphin/name.settings`** on the SD card:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- At boot, the `namechanger` service waits for the SD card, reads this file and applies the name if it is valid: right
  header and version, 2–8 characters, letters and digits only. It then restarts the USB serial and Bluetooth profiles
  so they use the new name.
- Saving an empty name deletes the file.
- The service runs only on a normal boot, not in the updater or DFU.

Because the name lives on the card, it stays after updates. It is lost if you format or replace the card, or delete the file.

## Troubleshooting

| Problem | Fix |
|---|---|
| The name did not change | Did you leave Settings (the reboot applies it)? Is the SD card inserted? Is the name 2–8 letters/digits? A 1-character name is saved but ignored at boot |
| The mobile app no longer connects | The Bluetooth name changed. Forget the Flipper in the app **and** in the phone's Bluetooth settings, run **Settings → Bluetooth → Unpair All Devices** on the Flipper, then pair again |
| A name file copied from elsewhere is ignored | Check the header `Flipper Name File`, `Version: 1` and the name rules |
