---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** is a static-code brute-force app from the Unleashed team. It goes through the possible codes of a fixed-code protocol and transmits them one after another. You can use a preconfigured protocol from its list, or load your own `.sub` file and pick which bytes to iterate.

::: warning
Use it only on your own equipment or with explicit permission. Brute-forcing someone else's gate or barrier is illegal in most countries.
:::

::: tip Unleashed
The app is not part of the firmware image and is not in the firmware source tree. It ships as an external app (`.fap`) in the Unleashed app packs, built from [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Install the pack (see [Apps on the SD card](/apps/sd-card-apps)) and look for it under `Apps → Sub-GHz`.
:::

## When it makes sense

- **Static (fixed) code only.** Brute force works only when the receiver accepts the same code forever, as with CAME 12-bit, Nice Flo 12-bit, Princeton-style and similar dip-switch remotes. A rolling-code receiver (KeeLoq, Nice Flor-S, CAME Atomo and others) never accepts a guessed code, so brute force is useless there (see [Rolling codes](/subghz/rolling-codes)).
- **You lost the remote of your own static-code device** and do not know its code, or you want to test how quickly your own fixed-code system can be guessed.

If you still have a working remote, it is far faster to [read](/subghz/read) it.

## How to use it

### Preconfigured protocols

1. Open `Apps → Sub-GHz` and start the Bruteforce app.
2. Pick a protocol from the list.
3. To change how many times each code is repeated, press <kbd>→</kbd> on the selected protocol.
4. Start the attack and keep the Flipper close to the receiver until it reacts.

### Your own file

1. Save a signal of the target protocol first, for example with [Read](/subghz/read) or [Add Manually](/subghz/add-manually).
2. In the app, load that `.sub` file.
3. Select the bytes of the key you want to brute-force. The other bytes stay as they are in the file.
4. Start the attack.

### Delay between signals

The time delay between transmitted codes is set on the app's main screen. **Hold <kbd>↑</kbd>** there (the screen hint reads "Up to Save") to save it. A shorter delay finishes faster, but some receivers miss codes that come too close together.

## Tips and common mistakes

- **Wrong frequency or modulation**: the receiver hears nothing. Check the band with the [Frequency Analyzer](/subghz/frequency-analyzer) first.
- **Too few repeats**: many receivers need a code repeated several times before they act. Increase the repeats with <kbd>→</kbd> on the protocol.
- **It runs a long time**: the number of codes grows exponentially with the number of bits. 12-bit codes are quick, while longer keys can take impractically long. Narrow the search by brute-forcing only the unknown bytes of your own file.
- **Transmission is blocked**: the frequency is outside the allowed range. See [Frequencies](/subghz/frequencies).

## Related pages

- [Supported systems](/subghz/supported-systems): which protocols are static
- [Add Manually](/subghz/add-manually)
- [.sub file format](/subghz/file-format)
