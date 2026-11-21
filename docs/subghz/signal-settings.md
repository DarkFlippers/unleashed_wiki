---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** edits a signal you have already saved: its counter mode, its current rolling counter and its
button code. It is a small expert screen, hidden unless Debug is on, and most of it works only on the handful of
protocols that support [counter modes](/subghz/counter-mode).

## Where it lives {#where}

It is an item in the menu of a saved signal, not an entry in the Sub-GHz main menu. Open a file from
`Sub-GHz → Saved` (or from the [Archive](/apps/archive)) and the menu is:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Making it appear {#enable}

`Signal Settings` is added to that menu only while **Debug** is on. With Debug off it is absent.

- Fast way: hold <kbd>↓</kbd> on the desktop, then hold <kbd>OK</kbd> on the info screen
  ([Desktop → Device info screen](/start/desktop#info-screen)).
- Or `Settings → System → Debug` = `ON` ([Settings](/start/settings)).

## The three items {#items}

![Signal Settings: Counter Mode, Edit Counter and Edit Button](/screens/subghz/signal_settings.png)

| Item | What it does |
|---|---|
| `Counter Mode` | <kbd>←</kbd>/<kbd>→</kbd> choose `System` (mode 0) or `Mode 1` … up to the protocol's limit. The choice is written into the `.sub` file as a `CounterMode:` line at once and the file is reloaded; nothing is transmitted |
| `Edit Counter` | <kbd>OK</kbd> opens a hex input for the current counter, headed `Enter <N>-bits counter in HEX` with the protocol's counter length: 4 hex digits (2 bytes) up to 16 bits, 8 digits (4 bytes) above that |
| `Edit Button` | <kbd>OK</kbd> opens a hex input for the button code, headed `Enter <N>-bits button in HEX` — always one byte, 2 hex digits |

The value each item currently holds is shown on its row, in hex. What the counter modes themselves do to the
counter, and how to set one by editing the file on a PC instead, is on
[Counter modes](/subghz/counter-mode#modes-by-protocol).

::: warning Confirming a counter or button edit transmits
`Edit Counter` and `Edit Button` write the file by running the transmit path: the firmware starts a send with the
new value and stops it immediately, and the file is rewritten when that send stops. The radio is keyed for an
instant, so do this away from the receiver you don't want to operate.

The counter you type is saved exactly as typed — for that one re-save the counter mode and the
[Counter Incr.](/subghz/settings) step are skipped. A button edit sets the step to 0 for the re-save instead,
so changing the button leaves the counter where it was.

If the send is refused — a frequency this firmware will not transmit on — the file is not written at all.
:::

## Protocols with counter modes {#protocols}

`Counter Mode` is unlocked for five protocols. `System` is mode 0, the normal one:

| Protocol | Choices |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

The match is on the `Protocol:` line of the file. On every other protocol the item is locked.

## Locked items {#locked}

A locked item cannot be opened or changed; pressing it shows `Not available for this protocol !`

- `Counter Mode` — the file's protocol is not one of the five above.
- `Edit Counter` — the protocol has no counter. It can also depend on the manufacturer: on KeeLoq the item is
  locked for `AN-Motors`, which has only a pseudo-counter, and for `Unknown`.
- `Edit Button` — the protocol has no button code in its frame.

`Edit Button` is also unlocked on the static protocols that carry a button code — Princeton, Dooya, GangQi,
Hollarm, Nord ICE, Proteco and Roger — and on those it works exactly as it does on a rolling-code signal.

## Related {#related}

- [Counter modes](/subghz/counter-mode) — what each mode does, and the `CounterMode:` file line
- [Rolling codes](/subghz/rolling-codes) · [.sub file format](/subghz/file-format)
- [Desktop](/start/desktop#info-screen) — the Debug shortcut · [Settings](/start/settings) — Debug in the menus
