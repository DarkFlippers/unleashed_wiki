---
title: Archive (file browser)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Archive (file browser)

**Archive** is the Flipper's file browser. It lists the keys, cards, remotes and scripts you have saved, lets you
run them straight away, and handles basic file management: pin to favorites, rename, copy, move, create folders and
delete.

**Open it:** on the desktop press <kbd>↓</kbd>.

![Archive on the Sub-GHz tab: a Garage folder and saved .sub signals, with Barrier selected](/screens/apps/archive.png)

## Tabs

Press <kbd>←</kbd> / <kbd>→</kbd> to switch tabs. Each tab shows one folder, filtered by file type:

| Tab | Folder | Files shown |
|---|---|---|
| Favorites | your pinned files | everything you pinned (`/ext/favorites.txt`) |
| Sub-GHz | `/ext/subghz` | `.sub` |
| SubRem | `/ext/subghz_remote` | `.txt` ([Sub-GHz Remote](/subghz/remote) maps) |
| RFID LF | `/ext/lfrfid` | `.rfid` and T5577 dumps |
| NFC | `/ext/nfc` | `.nfc` |
| Infrared | `/ext/infrared` | `.ir` |
| iButton | `/ext/ibutton` | `.ibtn` |
| Bad USB | `/ext/badusb` | `.txt` |
| Phone | `/ext/phonebook` | `.phone` ([SIM800](/gpio/sim800) phonebook) |
| U2F | internal | the U2F app entry |
| Apps | `/ext/apps` | `.fap` and `.js` |
| Internal | internal flash | everything (only with Debug mode on) |
| Browser | whole SD card | everything |

The Archive opens on **Favorites**.

::: tip Unleashed
Unleashed adds the **SubRem** tab for Sub-GHz Remote maps, the **Phone** tab for the SIM800 phonebook (a `.phone`
entry opens straight in the SIM800 app), shows T5577 dumps next to the keys in **RFID LF**, and lists `.js`
scripts in **Apps**.
:::

## Buttons in the list

| Button | Action |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | move through the list (hold to scroll faster) |
| <kbd>←</kbd> / <kbd>→</kbd> | previous / next tab |
| <kbd>OK</kbd> on a file | open its menu |
| <kbd>OK</kbd> on a folder | enter the folder |
| hold <kbd>OK</kbd> on a folder | open the folder's menu |
| <kbd>OK</kbd> in Favorites | run the file right away |
| hold <kbd>OK</kbd> in Favorites | open the menu |
| hold <kbd>OK</kbd> in an empty folder | open the menu (Paste / NewDir) |
| <kbd>Back</kbd> | up one folder, or exit |

## The file menu: Actions and Manage

The menu has two pages. Its title shows which one is open: **Actions** or **Manage**. Press <kbd>←</kbd> or
<kbd>→</kbd> inside the menu to flip between them (not in the Favorites tab). <kbd>↑</kbd> / <kbd>↓</kbd> choose an item,
<kbd>OK</kbd> runs it, <kbd>Back</kbd> closes the menu.

**Actions** (a file the firmware knows how to open):

- **Run**: open the file in its app (emulate a key, send a signal, run a script...).
- **Pin** / **Unpin**: add to or remove from Favorites.
- **Info**: file name and size.
- **Show**: view the file as text (for text formats).

For an unknown file type Actions offers only **Info** and, for text files, **Show**.

**Manage:**

- **Cut** / **Copy**, then **Paste** in the target folder.
- **NewDir**: create a folder.
- **Rename**: type a new name.
- **Delete**: asks for confirmation first.

In the **Favorites** tab the menu is **Run**, **Unpin**, **Show** (if applicable) and **Move**. Move lets you reorder
favorites: press <kbd>↑</kbd> / <kbd>↓</kbd> to shift the item and <kbd>OK</kbd> to save the new position
(<kbd>Back</kbd> cancels).

## Common tasks

### Pin a file to Favorites

1. Desktop → <kbd>↓</kbd> to open the Archive.
2. Go to the right tab with <kbd>←</kbd> / <kbd>→</kbd> and select the file.
3. Press <kbd>OK</kbd> → **Pin**. The file now appears in the Favorites tab.

### Rename a saved key or signal

1. Select the file and press <kbd>OK</kbd>.
2. Press <kbd>→</kbd> to switch the menu to **Manage**.
3. Choose **Rename**, type the name, confirm.

### Delete files to free space

1. Select the file, <kbd>OK</kbd>, <kbd>→</kbd> to **Manage**.
2. Choose **Delete** and confirm.

To clean a whole folder, use the **Browser** tab: select the folder, hold <kbd>OK</kbd>, **Manage → Delete**.

### Move a file to another folder

1. Select the file, <kbd>OK</kbd>, **Manage → Cut**.
2. Go to the target folder (the **Browser** tab reaches every folder on the card).
3. Press <kbd>OK</kbd> on any file (or hold <kbd>OK</kbd> in an empty folder) → **Paste**.

## Troubleshooting

- **"Empty"** means the folder has no files of that tab's type. Check the file extension: an `.ir` file in `/ext/nfc`
  will not show in either tab, but the Browser tab shows it.
- **Internal tab is missing**: it is visible only when `Settings → System → Debug` is ON.
- **A favorite disappeared**: favorites whose file no longer exists (moved, renamed or deleted outside the
  Archive) are dropped from the list. Pin the file again at its new location.
- **Delete** always asks `Delete <name>?` with **Cancel** / **Delete** buttons, so nothing is removed by one stray press.

## Related pages

- [microSD card](/start/sd-card)
- [Apps on the SD card](/apps/sd-card-apps)
- [Desktop](/start/desktop)
