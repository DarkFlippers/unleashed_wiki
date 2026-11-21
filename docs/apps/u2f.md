---
title: U2F security key
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# U2F security key

The **U2F** app turns Flipper Zero into a USB [Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor)
(FIDO U2F) security key. After you enter your password on a website, the site asks for the key, and you confirm the
login by pressing <kbd>OK</kbd> on the Flipper. Google, GitHub, Facebook, X and many other sites support U2F keys;
[dongleauth.com](https://www.dongleauth.com/) keeps a list.

::: warning Software-only key
The Flipper's U2F is implemented in software. For banking and other high-value accounts use a certified
hardware security key. Always keep a backup second factor (recovery codes or another key).
:::

## Before you start

- A **microSD card is required**. The U2F data lives in `/ext/u2f/`. Without it the app shows
  `No SD card or app data found. This app will not work without required files.`
- The certificate files `/ext/u2f/assets/cert.der` and `/ext/u2f/assets/cert_key.u2f` are installed by the firmware
  update. If they are missing, update the firmware again with the card inserted.
- **Close qFlipper** (and Flipper Lab): the Flipper must be free to switch its USB port into U2F mode. If a
  connection is active, the app shows `Connection Is Active! Disconnect from PC or phone to use this function.`

## Registering the Flipper on a website

1. Connect the Flipper to the computer with a USB cable.
2. Open `Main Menu → U2F`. The screen shows `Connect me to computer`, then `Connected!` once the computer has
   recognised the key.

   ![U2F: Connect me to computer, with the Flipper drawn as a USB stick](/screens/apps/u2f_not_connected.png)

3. On the website, open the two-factor settings and choose to add a **security key** (the wording differs per site).
4. The Flipper shows `Press OK to register`. Press <kbd>OK</kbd>.
5. The site confirms that the key was added.

## Signing in

1. Connect the Flipper over USB and open `Main Menu → U2F` (`Connected!`).
2. Enter your login and password on the website.
3. When the site asks for the security key, the Flipper shows `Press OK to authenticate`. Press <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate, with the OK button hint](/screens/apps/u2f.png)

4. The Flipper shows `Authentication successful!` and the site logs you in.

## Keep your U2F files safe

| File | Purpose |
|---|---|
| `/ext/u2f/key.u2f` | this device's U2F key, encrypted with a key unique to this Flipper |
| `/ext/u2f/cnt.u2f` | authentication counter |
| `/ext/u2f/assets/` | attestation certificate and its key (`cert.der`, `cert_key.u2f`) |

::: danger Do not delete, edit or move the U2F files
- Every Flipper has a unique built-in key that encrypts the U2F files. A card with U2F files moved to **another
  Flipper will not work** there.
- If you delete or edit the files, or insert a new card, the Flipper creates a new set of U2F files, and you must
  **register it again on every website**.
- If you delete `u2f/assets` (or the whole `u2f` folder), the app stops working (it reports `No SD card or app
  data found`) until you restore the folder by updating the firmware.
:::

## Troubleshooting

| Symptom | Fix |
|---|---|
| Stays on `Connect me to computer` | use a data cable (not charge-only), close qFlipper, try another USB port |
| `Connection Is Active!` | close qFlipper, Flipper Lab, the CLI or the mobile app session, then reopen U2F |
| `No SD card or app data found` | insert the card; if it is in, restore `/ext/u2f/assets` by reinstalling the firmware |
| `Certificate error` | the U2F engine could not start with the files on the card: reinstall the firmware with the card inserted |
| Site no longer accepts the key | the U2F files were regenerated (new card, deleted files): sign in with your backup factor and register the Flipper again |

The **U2F** tab of the [Archive](/apps/archive) starts the app too.

## Related pages

- [Apps that ship with Unleashed](/apps/catalog)
- [Bad USB](/badusb/usage)
- [qFlipper](/mobile/qflipper)
