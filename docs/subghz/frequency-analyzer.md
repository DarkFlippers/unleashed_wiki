---
title: Frequency Analyzer
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Frequency Analyzer

The Frequency Analyzer tells you **on which frequency a remote transmits**. It sweeps the frequencies of the
Sub-GHz list, measures signal strength (RSSI) and shows the strongest one. Use it before **Read** or **Read RAW**
when you don't know the frequency of a remote.

::: tip Unleashed
Unleashed ships a reworked analyzer (originally by ClusterM) with a 4-entry history, an adjustable trigger,
selectable feedback (sound / vibro / mute), and a **direct jump to Read**: short <kbd>OK</kbd> stores the
frequency for Read / Read RAW, long <kbd>OK</kbd> stores it and opens Read immediately.
:::

## The golden rule

The analyzer is meant to work **only a few centimetres from the Flipper's antenna, on the internal radio**.
The antenna is on the left side, next to the black IR window. Its settings exist to filter noise, not to catch
signals from far away. With a very low trigger the analyzer just reports random interference and the Flipper's
own noise instead of your remote. To actually *receive* signals use [Read](/subghz/read) and
[Read RAW](/subghz/read-raw).

::: warning
Using the analyzer with an external module is not recommended: external modules are more sensitive and pick up much
more noise.
:::

## Screen

![Frequency Analyzer showing 433.920 MHz, the history entries and the RSSI bar](/screens/subghz/frequency_analyzer.png)

| Element | Meaning |
|---|---|
| Top right icon | Feedback when a signal is caught: speaker = vibro + sound, small speaker = vibro only, crossed = mute |
| Big number in the middle | Current (main) frequency. While a signal above the trigger is being received it is shown **inverted in a black box** |
| Four entries below | History: rounded frequency and how many times it was caught (`x3`). Helps with weak remotes or remotes that drift |
| `RSSI` bar at the bottom | Live signal strength with the trigger mark |
| `T-` / `+T` | Trigger level buttons |

## Buttons

| Button | Action |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Move the trigger (from −97 dBm to −60 dBm, step 1 dBm). Left = more sensitive, right = less sensitive |
| <kbd>↑</kbd> | Cycle feedback mode: vibro + sound → mute → vibro → … |
| <kbd>↓</kbd> | Select an entry in the history (a frame appears around it) |
| <kbd>OK</kbd> short | Save the selected frequency for Read / Read RAW |
| <kbd>OK</kbd> long | Save the frequency and open **Read** right away |
| <kbd>Back</kbd> | Exit (trigger and feedback mode are remembered) |

Which frequency <kbd>OK</kbd> takes:

- if a signal is being received **right now** (black box around the main frequency) — that frequency, even if a
  history entry is selected;
- if nothing is being received and a history entry is selected — the selected entry;
- otherwise — the last frequency that crossed the trigger, so you don't have to keep the remote pressed.

::: warning Rounding
The saved frequency is always **rounded to the nearest frequency in the list** ([Frequencies](/subghz/frequencies)).
If your remote sits far from all standard values, add its frequency to `setting_user`. The main number will then
show the real frequency, but after jumping to Read / Read RAW you will have to set it manually in `Config`.
:::

Saving a frequency from the analyzer also **turns Hopping off**, so Read starts on that exact frequency.

## How to find the frequency of a remote

1. Move away from switching power supplies, chargers and other noisy electronics.
2. Open `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Hold the remote right against the left side of the Flipper (near the black window).
4. Press and hold a button on the remote. The main frequency turns inverted while the signal is received.
5. Release the button and wait until the frequency lands in the history.
6. Press <kbd>OK</kbd> to remember it, or hold <kbd>OK</kbd> to go straight to **Read**.

Most remotes transmit around 315, 433.92 or 868.35 MHz. In Read, still try several modulations if nothing
decodes (`AM650` first, then `FM238`, `FM476`, `FM12K`).

## Tuning the trigger

By default the trigger sits at −93 dBm, which works in most cases. Tune it only when the remote is not caught
even at point-blank range, or when there is a lot of noise:

1. With no remote pressed, move the mark with <kbd>←</kbd> / <kbd>→</kbd> until the Flipper stops catching
   anything (no noise, no random hits). The leftmost position is the most sensitive — it catches signals *and* the
   Flipper's internal noise and any interference; the rightmost is the least sensitive to both.
2. Hold the remote against the left edge of the Flipper and press its button.
3. If nothing is caught, move the trigger **left** step by step until the signal appears.
4. Press and release the remote button repeatedly while tuning — an intermittent signal makes the right position
   easier to find than a continuous one.

## Troubleshooting

- **Random frequencies keep appearing** — trigger too low or noise nearby. Move it right, move away from PSUs.
- **The remote is never caught** — hold it closer, check the battery, move the trigger left. Some remotes send
  very short bursts: press repeatedly.
- **Read shows nothing on the found frequency** — wrong modulation. Change it in `Read → Config`. If nothing
  decodes, record it with [Read RAW](/subghz/read-raw).
- **Frequency is off from the label on the remote** — normal; cheap remotes drift. Use the history counts to pick
  the most frequent value.

## Related

- [Frequencies](/subghz/frequencies) · [Read](/subghz/read) · [Read RAW](/subghz/read-raw)
- [Remote Analyzer](/subghz/remote-analyzer) — an app with its own analyzer and one-remote-at-a-time decoding
