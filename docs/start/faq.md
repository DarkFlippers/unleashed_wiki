---
title: FAQ
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# FAQ

## General

### I just bought a Flipper Zero. Where do I start?

Read [First start](/start/first-start), then [Installing Unleashed](/start/install). The official
[flipperzero.one](https://flipperzero.one/) site and [docs.flipper.net](https://docs.flipper.net/) cover the stock
basics.

### Official firmware, Unleashed or another fork?

If you are unsure, start with the official firmware. If you need more features, or want Sub-GHz without region locks,
install **Unleashed**: a fork of the official firmware with many new features and preinstalled apps (try the `e`
build). Other forks based on Unleashed exist for those who want to experiment more with the UI. You can also make your
own fork.

**Before reporting a bug, check which firmware you run.** Don't report issues from other forks or the stock firmware
in the Unleashed repo or Unleashed chats.

### Where can I see the differences from the official firmware?

[What Unleashed adds](/start/unleashed-features).

### Which build should I install? What do `e` and `c` mean?

`e` = base + extra community apps, no suffix = base apps, `c` = no community apps. Built-in system apps are in all of
them. Details: [Installing Unleashed](/start/install#which-file-to-download).

### What are dev builds?

Automatic builds of the latest commits on the `dev` branch that are not released yet. They **may have bugs**. Get them
in the Web Installer (Dev), on [dev.unleashedflip.com](https://dev.unleashedflip.com), in Telegram
[@kotnehleb](https://t.me/kotnehleb) or in the Discord channel `unleashed-development`. The previous build is deleted
when a new one is uploaded, and old ones remain only as files in the Telegram channel. Found a bug?
[Report it](https://github.com/DarkFlippers/unleashed-firmware/issues).

### What is the Unleashed update server?

`https://up.unleashedflip.com/directory.json`. It uses the same format as the official one, but official apps can't be
switched to it without rebuilding them. You can pass it to **uFBT** to build apps for the Unleashed SDK. It stays online
and updates automatically.

### Which apps are included?

The built-in system apps, plus the base pack (and the extra pack for `e`) from
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).
See [What Unleashed adds](/start/unleashed-features#built-in-apps).

### How can I support the project?

See the [support section](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project)
of the ReadMe. Even a simple "thank you" helps. Every build is and will remain free and open source.

## After installing

### The backlight doesn't work after installing Unleashed {#backlight-does-not-work}

You enabled the **RGB backlight mod** setting, which is meant only for Flippers with the RGB hardware mod. Go to
**Settings → LCD and Notifications → RGB Mod Settings** and set **RGB backlight installed** to `OFF`. If you *do* have
the mod, enable it there instead.

### The mobile app doesn't connect (after installing Unleashed or changing the name)

1. In the mobile app, tap **Forget Flipper**.
2. In the phone's **Settings → Bluetooth**, find the Flipper and choose **Forget this device**.
3. On the Flipper: **Settings → Bluetooth → Unpair All Devices**, then confirm.
4. Make sure Bluetooth is `ON` on the Flipper, then pair again from the app.

### My settings (PIN, favourites, desktop…) were reset after an update

Set them again. A settings file is reset only when a release changes its structure, which happens in specific releases,
not every time. Check the changelogs of the releases since your previous version.

### The Flipper doesn't connect to Chrome / the Web Installer

Most often **qFlipper is open**, or a second Flipper Lab / web page is connected. Only one program can use the port.
Close the others and try again. Use a Chromium-based browser.

## Problems

### The Flipper crashed, froze or hangs

Hold <kbd>←</kbd> + <kbd>BACK</kbd> to reboot. More: [Key combos](/start/key-combos).

### The Flipper doesn't work at all. How do I restore the firmware?

[Recovery → Firmware recovery](/start/recovery#firmware-recovery).

### I forgot my PIN

Unplug USB, turn the Flipper off, hold <kbd>↑</kbd> + <kbd>BACK</kbd> for about 5 s until the reset screen appears,
then hold <kbd>→</kbd>. Settings and PIN are reset, but files on the SD card stay. Details:
[Recovery → Reset a forgotten PIN](/start/recovery#reset-pin).

### The Flipper is slow and unresponsive

1. Use a good branded microSD card. The Flipper uses SPI, and not every card handles it well.
2. In **Settings → System** check:
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Charge the battery. A low battery affects performance too.

### How do I change the Flipper's name, or reset it?

**Settings → Desktop → Change Flipper Name**: enter a name, **Save**, leave Settings and the Flipper reboots. Save an
empty name to go back to the default. See [Custom Flipper name](/start/custom-name).

## Sub-GHz

### Is there a region lock? How do I unlock Sub-GHz?

There is **no region lock in Unleashed**: every frequency the chip supports works out of the box. Going **beyond the
chip specification** is possible but can damage the hardware: [Dangerous settings](/start/dangerous-settings).

### Which protocols are supported, and with which frequency and modulation?

[Supported systems](/subghz/supported-systems).

### How do I add extra frequencies?

[Frequencies and presets](/subghz/frequencies).

### Can I clone my own car key fob to use the Flipper as a key?

**No.** Car keys and most garage remotes use **rolling codes**. Replaying a captured signal (for example from Read RAW)
desyncs the counter. In the worst case the original key is unpaired or blacklisted, and re-pairing needs service tools.

**Why:** the receiver remembers the last counter value it got from a remote (how many times any button was pressed).
Say the original remote sent counter `0002`, and you sent the same signal from the Flipper with `0003`. The receiver
accepts it. But the original remote is still at `0002`, so its next press sends `0003`, which the receiver has already
seen, and it doesn't react. This is not unpairing yet: press the original a few more times to "overtake" the Flipper
(`0004`) and it works again. But if this race goes on, the gap can grow to **100+ presses**, and the original remote can
no longer be brought back without re-pairing it to the receiver.

**What to do instead:**
- use only **one** remote: either the Flipper or the original;
- **best:** create a **new remote** on the Flipper with **Add manually** and pair it with the receiver as a separate
  remote ([Add manually](/subghz/add-manually), [Programming a new remote](/subghz/remote-prog));
- if you must use both, use them alternately so the counters never drift far apart.

More: [Rolling codes](/subghz/rolling-codes), [Counter mode](/subghz/counter-mode).

### How do I use the Flipper as a new remote (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors…)?

[Programming a new remote](/subghz/remote-prog).

### How do I use the Sub-GHz Remote app?

1. Open the app, press <kbd>BACK</kbd> and select **New map file**.
2. Choose a signal file and a label for each button. You can leave buttons empty.
3. Save the map.
4. Open the map file you created.
5. Press the buttons to send the assigned signals.

Details: [Sub-GHz Remote](/subghz/remote).

### My remote is not supported (not a car key). How do I record it for the developers?

1. **Find the frequency.** **Sub-GHz → Frequency Analyzer**: hold the remote's button near the Flipper (the antenna is
   near the IR window on the left). Release it, and the frequency goes into the history. Hold <kbd>OK</kbd> to jump to
   **Read** and press the remote a few times, holding each press for at least 2 s. Try `AM650`, `FM238`, `FM476`,
   `FM12K`.
2. **Nothing decodes? Record RAW.** Open **Read RAW**, set the frequency in the config and the **RSSI Threshold** to
   `----`. Make one recording for **each** modulation (`AM650`/`FM238`/`FM476`/`FM12K`). Press **REC**, then press one
   button 5 times holding it 1–2 s, then 5 times holding it ~5 s. Record every button the same way and name each file
   after the button.
3. **Report it.** Zip the RAW files and open an issue in the firmware repo. Attach good photos of the remote (inside
   too, if possible), the model and manufacturer, and a photo of the receiver board if you can.

If the remote is not encrypted and is unique enough, support may be added. To analyse signals yourself, try
[lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter).

### How do I connect an external CC1101 module?

[External CC1101](/subghz/external-cc1101).

## NFC and RFID

### MIFARE Ultralight

Read the card, hold the Flipper to the reader to capture the password that unlocks the remaining pages, then read the
card again: [Unlock with password](/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

There are no attacks for these cards on the Flipper at the moment.

### Bank cards

You can't clone bank cards, the Flipper can't emulate them, and it can't act as a payment terminal. It can only read
public data: [Bank cards (EMV)](/nfc/emv).

### Amiibo

Amiibo are `NTAG215`. They can't go on a MIFARE Classic, and currently you can't write Amiibo to new physical tags.

### HID / iClass (Picopass)

- Read iClass with the **Picopass** app. Emulation is supported in the current Unleashed builds with apps.
- 26-bit Picopass can be downgraded to H10301 LF RFID credentials. This only works if the reader is configured for LF.
  Some iClass readers are HF only.
- Write support for personalisation-mode cards is possible with the app.
- The **Seader** app with a SAM expansion board reads more secure HID cards.

### 125 kHz RFID cloning

To copy an LF tag, write it to a **T5577**. The chips the Flipper reads are read-only, and "blanks" of them don't
exist. The T5577 is a multi-emulator chip that can be programmed to act as other tags:
[Writing RFID](/rfid/write), [T5577 app](/rfid/t5577-app).

### Unknown card or fob

If NFC, RFID and Picopass all fail, take photos of the front and back of the credential and of the reader. For a card,
hold it in front of a bright light and photograph the antenna. Post them in the community chats to identify it.

## Infrared

### Is there a right way to capture IR signals (especially air conditioners)?

Yes: [IR captures](/infrared/captures).

## Files and computers

### Where can I find files (Sub-GHz, IR, NFC…) for my Flipper?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) and [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) cover most needs.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero): almost every link you might need.

### How do I copy files from GitHub to the Flipper?

Download the files on a PC and copy them to the SD card (card reader, or qFlipper's file manager). There is also a
detailed [community guide](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf).

### How do I clean `.DS_Store` and dot files left by macOS, or sort files?

See [microSD card → macOS](/start/sd-card#macos-hidden-files-and-sorting).

### How do I open the CLI or view logs?

Close qFlipper first. Only one program can hold the serial port.

- **Browser (Chromium):** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → choose the USB serial
  device → **CLI** in the sidebar.
- **Windows:** find the COM port in qFlipper, close qFlipper, then in PuTTY choose **Serial**, enter the COM port and
  speed `115200`, and click **Open**. "Access Denied" means qFlipper is still running.
- **macOS/Linux:** find the device path in qFlipper (it starts with `/dev/tty`) or with `ls /dev/tty.*`, close
  qFlipper, then run (replace `PATH`):
  ```bash
  screen PATH 115200
  ```
- **Android:** the *Serial USB Terminal* app, connected over USB OTG.
- **iPhone:** no USB serial. Use another method.

To see logs, set **Settings → System → Log Level** to `Debug` and type `log` in the CLI. <kbd>Ctrl</kbd>+<kbd>C</kbd>
exits. More: [CLI](/dev/cli).

### How do I build the firmware myself?

[Build the firmware](/dev/build).

## Community

- Releases: Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Dev builds: Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- More links: [Links](/community/links)
