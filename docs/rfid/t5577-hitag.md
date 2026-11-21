---
title: T5577 and Hitag Micro (by @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Hitag Micro writing, write UX and T5577 wipe

Based on @gromovyna's article *"Preview of the LF (RFID) features I prepared for Unleashed"* (June 2026), updated
with how the features look in the current firmware.

![](/img/remote/2e30c69f7eded901.png)

## Intro

After a long break, @gromovyna went back to research and looked at the **H5.5** blanks sold by *iKey*. From Iceman's
Discord it was already known that H5.5 is the same Chinese **Hitag Micro** clone, on which iKey set their own
password. The naming situation:

| Name | What it is |
|---|---|
| **8265 / H5** | the chip with the default password |
| **H5.5** | the same chip with the **iKey** password |
| **8210** | the same chip with the password of the Chinese cloner **FURUI** |

He recovered the iKey password (on day two of trying), shared it with the community and
[updated the Proxmark3 magic cards notes](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265).
Then he implemented the features for Flipper — as pull requests to **Unleashed**, hoping to bring them to OFW too once
it is in active development again.

The passwords the firmware uses for the three variants:

| Variant | Password |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Hitag Micro support

The Flipper can now **write** Hitag Micro clones — **8265/H5**, **H5.5** and **8210** — as EM4100 keys (the chip is
configured to send the EM4100 frame by itself, "transponder talks first").

Limitations of the current architecture:
- the Flipper's LF hardware only **transmits** while writing, so success can only be checked by **reading the tag
  back**;
- a lot of time went into calibrating constants, but writing these chips still needs **good positioning**.

### Why writing got slower

Adding support made the UX worse, because the write logic is now a loop that tries, one after another:

- **T5577**
- **EM4305**
- **Hitag Micro** — and here three variants, one per known factory password; these operations are slower by themselves

For Hitag Micro the Flipper tries the password of every known variant in turn, so that it doesn't have to ask the user
— asking would kill one of the main ideas of Flipper Zero, simplicity. The price is write speed. A wrong password is
just rejected by the chip and leaves the tag untouched; the variant that reads back correctly is the one present.

For the user this looked terrible — as if nothing was happening — and it was not clear which protocol the tag had been
written with. Hence the next feature.

## UX: what are we writing with / what did we write?

During a write the screen now shows **which chip is being tried**:

![Write in progress](/img/remote/34b72cbd8417d74e.png)

Technically it is not a protocol but the market name of the blank variant — but you get the idea. After writing, the
result is shown with the same detail:

![Write result](/img/remote/3ca59457a78dad5b.png)

::: tip In the current firmware
- The chips to try are configurable: `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210, H5.5 (all ON)
  and **8268** (ID8268 / Hitag S magic chip, OFF by default). Switch off what you don't use to speed writes up.
- The 8268 target writes only EM4100 at RF/64 and is opt-in, because on a genuine Hitag S it would overwrite user data.
- The write screen format is `[Protocol]`, file name, `(chip)`; **Success!** shows the chip that took the data. Details:
  [Writing to blanks](/rfid/write).
:::

## Wiping T5577 back to stock

A function @gromovyna had long missed on the Flipper: resetting a T5577 to the blank state. An earlier attempt to add it
to Unleashed had been blocked; later, features like *clear T5577 password* were merged with the same architectural
issues, so a proper fix would have to be global.

Behaviour (matching Proxmark3):

- before starting you are warned that **all data will be erased** and the tag **will not be readable by Read** until
  you write new data to it;
- the wipe **does not remove a password** — if the tag is protected, clear the password first with the dedicated
  function;
- a progress bar is shown. Most of the time goes not into the wipe itself but into **verifying** it: because of the LF
  API the Flipper checks that the tag is clean by trying to read it and expecting that read to fail;
- at the end you get a success or a failure message.

![Wipe warning](/img/remote/f5ed0aa91bfcae98.png)

![Wipe in progress](/img/remote/153b85d1fede96d9.png)

![Verifying](/img/remote/0f2f4e240a35940d.png)

![Success](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — where it is now
In the article the wipe lived in `125 kHz RFID → Extra Actions`. In the current firmware it (and Clear Password) moved
to the bundled **T5577** app: `Apps → RFID → T5577 → Wipe Tag`. The warning reads *Wipe T5577 — Erases all data. The
tag stops working as a key. Hold still while running*; the result is **Wiped!** or **Not wiped** (e.g. *No answer.
Protected? Try Clear Password*). The wipe writes zeroed data blocks and a default configuration, so the T5577 app can
still read the chip afterwards. See [T5577 app](/rfid/t5577-app).
:::

## "You vibe-coded this!"

In the author's words, this was an experiment in whether you can write proper code for such systems with an LLM. The
process was meticulous: datasheets, the Unleashed firmware code to understand the architecture, the Proxmark3 code.
Every step was validated, tested on real hardware and fine-tuned. So the features were *written by Claude Code*, but
*created by @gromovyna*.

## Pull requests

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

More articles and research: [@gromovyna](https://t.me/gromovyna).

## Related

- [Writing to blanks](/rfid/write) · [T5577 app](/rfid/t5577-app) · [Protocols](/rfid/protocols)
