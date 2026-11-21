---
title: Pet dolphin
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# Pet dolphin

A digital dolphin lives on the Flipper's desktop. It gets happier and levels up as you use the device's tools, and its
animations change with its mood and level.

## Passport

Press <kbd>→</kbd> on the desktop, or go to **Main Menu → Settings → Passport**. The passport shows:

- the dolphin's picture for the current level;
- the **name**: the Flipper's device name ([you can change it](/start/custom-name));
- **Mood**: `Happy`, `Ok` or `Angry`;
- **Level** and a progress bar to the next level.

![Passport: the dolphin portrait, the Flipper's name, Mood: Happy, Level: 2 and the progress bar to level 3](/screens/settings/passport.png)

## Mood

The dolphin gets sadder when you don't use the Flipper. Its "butthurt" counter goes up by one about **every 48 hours**
without activity. Using apps brings the mood back up, with a daily cap on how fast it recovers.

**Happy Mode** keeps the dolphin happy no matter what:

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. The dialog says: *"I will never get angry at you for not
spending time with me as long as this mode is enabled"*. Open it again and choose **Disable** to turn it off.

## Levels and XP

| Level | XP needed |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Each app can give at most **20 XP per day**. There are 7 counted groups (Sub-GHz, RFID, NFC, Infrared, iButton,
Bad USB, and "plugins", which includes U2F, GPIO and external apps), so the maximum is **140 XP per day**. Limits reset
daily.

### XP per action

| App | Action | XP |
|---|---|---|
| Sub-GHz | Receive and view a signal | 1 |
| | Save a signal | 3 |
| | Record RAW | 1 |
| | Add manually | 2 |
| | Send a saved signal | 2 |
| | Use Frequency Analyzer | 1 |
| 125 kHz RFID | Enter Read | 1 |
| | Read success | 3 |
| | Save | 3 |
| | Emulate | 2 |
| | Add manually | 2 |
| NFC | Enter Read | 1 |
| | Read success | 3 |
| | Save | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emulate | 2 |
| | Add a key manually | 2 |
| | Add manually and save / emulate | 1 |
| Infrared | Send a signal | 1 |
| | Learn success | 3 |
| | Save | 3 |
| iButton | Enter Read | 1 |
| | Read success | 3 |
| | Save | 3 |
| | Emulate | 2 |
| | Add manually | 2 |
| Bad USB | Run a script | 3 |
| U2F | Successful authorization | 3 |
| GPIO | Open USB-UART Bridge | 1 |
| Apps | Start an external app | 2 |
| | Start a game | 1 |
| | Win a game | 10 |

When the dolphin reaches a new level, the Flipper shows a level-up notification and the desktop animations change.

## Where the state is stored

The dolphin's XP, level and mood are kept in `.dolphin.state` in internal storage. A
[factory reset](/start/recovery#factory-reset) sets the dolphin back to level 1.
