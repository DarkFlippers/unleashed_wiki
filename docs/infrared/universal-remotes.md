---
title: Universal remotes
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Universal remotes

A universal remote lets you control a device **without learning its remote first**. When you press, say, *Power*,
the Flipper sends the Power code of every model in its library, one after another. When it hits the code your
device understands, the device reacts. That's why a universal button takes a few seconds instead of being instant.

Open `Main Menu → Infrared → Universal Remotes`.

![The Universal Remotes category list: TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
The official firmware ships TV, Audio, Projector and AC libraries. Unleashed adds **LEDs** and **Fans** and keeps all
libraries much larger and regularly re-verified by the team (IR assets by @amec0e). The TV library is recompiled so
**all** its buttons work, not only Power.
:::

## Categories

The menu items and button names below are taken from the firmware; the signal counts are from the libraries
shipped with the current `dev` build (`/ext/infrared/assets/`, last updated October 2024 / February 2024 for AC).

| Menu item | Library file | Buttons | Signals in library |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (295 of them Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

"Audio" covers sound bars, AV receivers, music centres and similar. "LEDs" means IR-controlled LED strips and bulbs.

### Air conditioners

AC remotes keep the device state themselves and send the full state with every press, so the AC library contains
complete "scenes" rather than single buttons:

| Button | Meaning |
|---|---|
| **Off** | Turn the AC off. This is the *only* button that turns it off. |
| **Dh** | Dehumidify (dry) mode. |
| **Cool_hi** | Cooling at the lowest temperature the remote allows (maximum cooling). |
| **Cool_lo** | Cooling at 23 °C. |
| **Heat_hi** | Heating at the highest temperature the remote allows (maximum heating). |
| **Heat_lo** | Heating at 23 °C. |

To turn an AC **on**, press any button other than Off. The temperature buttons show °C or °F depending on
`Settings → System → Units`.

## How to use

1. Go to `Main Menu → Infrared → Universal Remotes` and select a category.
2. Point the top edge of the Flipper at the device. Stay close and in line of sight.
3. Select a button with the arrows and press <kbd>OK</kbd>.

   ![The universal TV remote, shown on the vertical screen: Power and Mute on top, Channel and Volume up/down below](/screens/infrared/universal_tv.png)

4. The **"Sending..."** window shows the progress as `current/total` and a progress bar. Keep pointing at the device.
5. When the device reacts, press <kbd>OK</kbd> to **pause**, or let the library run to the end.

![Universal remote in action](/img/remote/bdb3541a3f2e88fe.png)

### Controls while sending

| State | Button | Action |
|---|---|---|
| Sending | <kbd>OK</kbd> | **pause** |
| Sending | <kbd>Back</kbd> | **stop** |
| Paused | <kbd>Back</kbd> | **resume** sending from where it stopped |
| Paused | <kbd>OK</kbd> | **send 1**: send only the currently selected signal |
| Paused | <kbd>←</kbd> / <kbd>→</kbd> (arrows) | **select** the previous / next signal in the library |
| Paused | <kbd>↓</kbd> | **save** the selected signal |

## Find the exact code and save it

Pausing lets you find the one code that works and keep it, so next time the button is instant.

1. Run a universal button. As soon as the device reacts, press <kbd>OK</kbd> (pause). The counter now points at the
   last signal sent.
2. Because you are never perfectly fast, step back with the left arrow and use **send 1** (<kbd>OK</kbd>) on each
   signal until you find the one that triggers the device. Use the right arrow to go forward again.
3. Press <kbd>↓</kbd> **save**. The menu header shows the button name (e.g. `Power`), which is also the name the
   signal is saved under:
   - **Save as New Remote**: enter a remote name in **"Name the remote"**; a new `.ir` file is created in
     `/ext/infrared/`;
   - **Add to Existing Remote**: choose an existing `.ir` file; the signal is appended to it.
4. **"Saved"** confirms it. The remote is now in `Infrared → Saved Remotes`.

Repeat for Vol_up, Mute and so on, adding each one to the same remote: you end up with a personal, instant remote
built from the universal library.

![A saved remote on the vertical screen: the button list Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## From the command line

The same libraries can be played over the [CLI](/dev/cli):

```text
ir universal list tv        # list the signal names in tv.ir
ir universal tv Power       # send every "Power" signal from tv.ir
```

`ir universal` without arguments lists the available libraries (all `.ir` files in `/ext/infrared/assets/`).
Press <kbd>Ctrl</kbd>+<kbd>C</kbd> in the terminal to stop.

## Troubleshooting

| Problem | What to try |
|---|---|
| *"Function requires SD card with fresh databases."* | The library files are missing. Insert the microSD card and reinstall / update the firmware with the SD card in place, see [Updating](/start/updating). |
| Nothing reacts after the whole library | Your model is not in the library. [Learn](/infrared/read) the original remote instead, try the [mobile app's Remotes Library](/infrared/mobile), and consider [contributing captures](/infrared/captures). |
| The device reacts, but too late to pause | Use the left arrow + **send 1** to step back to the right signal, see above. |
| Works only at very short distance | The built-in LEDs are weak for big rooms. Use an [external IR module](/infrared/external-ir). |
| AC won't turn on with Off | Expected: Off only turns it off. Use Cool/Heat/Dh to turn it on. |

## Related pages

- [Contributing captures](/infrared/captures): add your device to the libraries
- [IR file format](/infrared/file-format): library file format
- [Learning and sending signals](/infrared/read)
