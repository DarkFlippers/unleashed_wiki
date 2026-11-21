---
title: microSD card
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# microSD card

The microSD card is not optional. It holds your saved keys, cards and remotes, all `.fap` apps (including the
built-in Unleashed apps), databases, the update package, and, in current firmware, even the **internal storage**.

## Choosing a card

- **Capacity:** 16–32 GB is plenty. Up to 256 GB is supported, but large cards take longer to mount.
- **File system:** FAT12, FAT16, FAT32 or exFAT.
- **Quality:** use a **branded** card (SanDisk, Kingston…). The Flipper talks to the card over **SPI**, not the fast
  SDIO mode phones and PCs use. Not every card handles SPI well, even if it works fine in other devices. A bad card
  makes the Flipper slow, can drain the battery faster (up to ~50 mA instead of ~30 mA) and can corrupt data.
- SPI reads reach almost 600 KiB/s, which is enough for everything the Flipper does.

## Inserting

1. The slot is at the bottom of the Flipper.
2. Hold the card **pins up** and push it in until it clicks.
3. The SD icon appears in the status bar.

## If the card is not recognised

A message about the SD card appears, or the status-bar icon is crossed out. Possible causes:

| Cause | Fix |
|---|---|
| Wrong or no file system | Format the card (below) |
| Dust in the slot | Clean it carefully with compressed air |
| The card does not support SPI | Use another card |
| The card is damaged | Use another card |

## Settings → Storage

**Main Menu → Settings → Storage**

| Item | What it does |
|---|---|
| **About Internal Storage** | Name, type `Virtual (/.int on SD)`, total and free space, free flash |
| **About SD Card** | Label, file system type, total and free space, manufacturer and serial |
| **Unmount SD Card** / **Mount SD Card** | Safely unmount before removing, or mount again. Mounting may briefly cut power to external modules |
| **Format SD Card** | Formats the card. **All data will be lost!** |
| **Benchmark SD Card** | Tests write/read speed in SPI mode |
| **Factory Reset** | Erases internal storage (settings, pairing, dolphin). See [Recovery](/start/recovery#factory-reset) |

### Formatting

1. **Settings → Storage → Format SD Card**.
2. Confirm with <kbd>→</kbd> **Format**.
3. Wait for `Formatted`, then press **Finish**.

If formatting on the Flipper fails (`Cannot Format SD Card`), format the card on a PC as FAT32/exFAT, or try another card.

### Safe removal

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. When you see `SD Card Unmounted` / `You can remove SD card now.`, push the card to release it and pull it out.

Removing a card while the Flipper writes to it can corrupt files or the file system.

### Benchmark

The benchmark writes a test file `/ext/rwfiletest.bin` and shows lines like `4096b : W 300K R 600K`: block size, then
write and read speed in KiB/s. A card should write **at least ~260 KiB/s** for normal operation. Results differ from
PC benchmarks because the test runs in SPI mode. Run it a few times to get a fair picture.

## Folder layout

`/ext` is the root of the card. The main folders:

| Folder | Content |
|---|---|
| `/ext/subghz/` | Sub-GHz `.sub` files. `assets/` holds `dangerous_settings`, `setting_user.example` (template for your own frequency list), the KeeLoq keystore `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Sub-GHz Remote maps |
| `/ext/nfc/` | NFC `.nfc` files. `assets/` holds key dictionaries |
| `/ext/lfrfid/` | 125 kHz RFID `.rfid` files |
| `/ext/ibutton/` | iButton `.ibtn` files |
| `/ext/infrared/` | IR `.ir` remotes. `assets/` holds universal remote libraries |
| `/ext/badusb/` | Bad USB scripts (`.txt`). `assets/layouts/` holds keyboard layouts (`.kl`) |
| `/ext/apps/` | `.fap` apps by category (built-in apps and app packs) |
| `/ext/apps_data/` | App data and settings |
| `/ext/dolphin/` | `name.settings` (custom name) and animations |
| `/ext/update/` | Unpacked update packages |
| `/ext/.int/` | Backing store for the internal storage (`/int`). Don't edit it by hand |

::: tip
Back up the whole card from time to time (qFlipper can download files, or copy them on a PC). Your keys and remotes
exist only on the card.
:::

## macOS: hidden files and sorting {#macos-hidden-files-and-sorting}

macOS leaves `._*` and `.DS_Store` files on the card. Clean them up:

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Replace `Flipper\ SD` with your card's name.

The file browser lists files faster when the FAT directory is sorted. On macOS (with [Homebrew](https://brew.sh)):

```bash
brew install fatsort
diskutil list                         # find the card, e.g. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # use your own disk id
```

`fatsort` is also available on Linux.

## Related

- What survives an update: [Updating](/start/updating)
- File formats: [Sub-GHz](/subghz/file-format), [NFC](/nfc/file-format), [RFID](/rfid/file-format),
  [Infrared](/infrared/file-format), [iButton](/ibutton/file-format)
