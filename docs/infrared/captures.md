---
title: Contributing captures
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Contributing IR captures to the universal remotes

If a [universal remote](/infrared/universal-remotes) doesn't work with your device, you can record your original
remote and add it to the library, so it works for everyone. A **clean** capture is short, decoded where possible,
and named exactly as the universal remote expects.

The method is the Unleashed guide by **@amec0e** (who maintains the Unleashed IR assets), based on the original
*UniversalRemotes* documentation by @gsurkov, @skotopes, @knrn-ai, @DrZlo13 and @ahumeniy.

## Button names per library

The universal remote only uses signals whose `name:` matches one of its buttons exactly (case matters). Any of them
can be omitted if your device doesn't have it.

| Library | File | Signal names |
|---|---|---|
| TVs | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projectors | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LEDs | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Fans | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| ACs | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

On many audio remotes `Play` and `Pause` are the same button: record it as `Play` and leave out `Pause`.

## TVs, audio, projectors, fans, LEDs

1. Point the remote at the Flipper's IR receiver.
2. Start `Infrared → Learn New Remote` for the first button, or select `+` in the remote for the next ones.
3. Do a **quick press** of the remote button and save it under the matching name from the table above.
4. Repeat steps 2-3 for all buttons.
5. Test every saved button against the real device: each one must do what its name says.

::: warning Don't hold the button
Holding the remote button produces long captures with many repeats. They take longer to send and slow down the
whole universal remote for everyone.
:::

### Parsed vs RAW

**Parsed** is the best result: the protocol was recognised and only protocol, address and command are stored.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Interference from other devices around you (lamps, TV backlights, other remotes) can push a capture into **RAW**
even if the protocol is known. If you got RAW for a common remote, press **Retry** on the Flipper a few times until
you get a clean parsed capture.

**RAW** is fine when the remote really uses an unknown protocol. Aim for the *smallest number of samples* that still
works on the device: a quick press, typically **around 100 samples**. An ideal single-press capture looks like this:

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Air conditioners

AC remotes are different: the remote keeps the state (mode, temperature, fan, vanes) on its display, and every press
sends **the whole state** at once. So each AC "button" is really a complete state that must be captured as a whole.

For each signal **except `Off`**:

1. Press **Power** on the remote so its display shows the AC as ON.
2. Set the mode and temperature from the table below. Leave everything else (fan speed, vanes) on **AUTO** if possible.
3. Press **Power** on the remote to switch it OFF.
4. On the Flipper start learning (`Learn New Remote` for the first one, `+` for the rest).
5. Point the remote at the Flipper and press **Power** once more (this is the "turn on in this mode" frame).
6. Save the signal under the name from the table.
7. Repeat for every row.

| Signal | Mode | Temperature | Note |
|:---:|:---:|:---:|---|
| `Dh` | Dehumidify | N/A | |
| `Cool_hi` | Cooling | lowest | lowest temperature available in cooling mode |
| `Cool_lo` | Cooling | 23 °C | |
| `Heat_hi` | Heating | highest | highest temperature available in heating mode |
| `Heat_lo` | Heating | 23 °C | |

Then record **`Off`**:

1. Make sure the remote display shows the AC as ON.
2. Start learning on the Flipper and point the remote at it.
3. Press **Power** so the remote shows OFF.
4. Save the signal as `Off`.

You end up with up to 6 signals. Test them all against the real AC.

## Prepare the file and submit it

1. Copy the `.ir` file from `/ext/infrared/` to your computer with [qFlipper](/mobile/qflipper) (or the mobile app)
   and open it in a text editor.
2. Precede your signals with a model comment so the library stays organised:
   ```text
   # Model: <your brand and model>
   ```
   The order of the signals inside the block doesn't matter.
3. Fork the [Unleashed repository](https://github.com/DarkFlippers/unleashed-firmware) and **append** your block **to the
   end** of the matching file in `applications/main/infrared/resources/infrared/assets/`.
4. Open a pull request with the changed file. After review it ships in the next build for everyone.

The file format is described in [IR file format](/infrared/file-format#library-files). Large community collections
of ready-made remotes: [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) and the official
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB) used by the [mobile app](/infrared/mobile).

## Related pages

- [Universal remotes](/infrared/universal-remotes)
- [Learning and sending signals](/infrared/read)
- [IR file format](/infrared/file-format)
