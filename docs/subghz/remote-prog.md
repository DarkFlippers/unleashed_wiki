---
title: Flipper as a new remote
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Using the Flipper as a new Sub-GHz remote

Turn the Flipper into a **brand new remote** and register it in your gate, garage or blind receiver, the same way you would register a spare remote bought in a shop. This is **not** cloning.

::: warning
Use this only on receivers you own or are allowed to manage.
:::

## Clone or new remote?

- **Rolling code (dynamic) remotes**: BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq and the rest of this page. Every press sends a new code built from a counter, and the receiver only accepts a counter that moved forward. A clone shares the original's counter, so the two fight over it: whichever you pressed last works, and the other needs several presses to catch up (see [Rolling codes](/subghz/rolling-codes)). That is why you make a **new** remote. It gets its own serial and counter and lives alongside your original remotes.
- **Static (fixed) code remotes**: CAME 12/24 bit, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX and the other static protocols. There is no counter, so **cloning is fine**: the copy is identical and both keep working in any order. Use `Sub-GHz → Read` and save it (see [Reading signals](/subghz/read)). You only need this page if you want a remote with its own separate code.

## Read this first

**What Add Manually does.** `Main Menu → Sub-GHz → Add Manually` builds a new remote with a randomly generated serial number and saves it as a file. Nothing is sent until you open that file and press a key. Your original remotes are not touched.

::: tip Unleashed: two-step Add Manually
In current Unleashed firmware the menu is two steps:
1. Pick the **system** from the list, for example `BFT Mitto`, `KL: DoorHan` or `Somfy Telis`.
2. Pick the **band** (frequency + modulation). The system's own bands are at the top, for example `433.92 AM650` or `868.35 AM650`. All the other bands are listed below them for installations that use an unusual one: `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Then you name the file and it is saved to `/ext/subghz/`. Older guides write things like "BFT Mitto 433MHz" as one menu item. Today that is `BFT Mitto` → `433.92 AM650`.
:::

**If your system is not on this page, the Flipper may still support it.** Scroll through the `Add Manually` list. If your brand is there, create a remote and follow the programming steps from your *receiver's own manual*. The full protocol list is in [Supported systems](/subghz/supported-systems), and every menu entry is described in [Add Manually](/subghz/add-manually).

**Read and Add Manually are different jobs.** `Read` captures and replays a remote you already have. `Add Manually` creates a new remote that can be registered in the receiver. Many protocols support only `Read`.

**The Flipper's keys are the original remote's buttons.** When a remote file is open (`Saved → file → Emulate`):

| Flipper key | What it sends |
|---|---|
| <kbd>OK</kbd> (shown as `Send`) | the remote's main button |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | the remote's other buttons (custom buttons) |

Which arrow sends which button depends on the protocol. A *hidden* or *programming* button on the original remote (a recessed pin hole, two buttons held together, pads you bridge inside the case) becomes **one key press** on the Flipper. Each section below says which key that is, and the [reference table](#programming-hidden-button-reference) lists them all.

The [Sub-GHz Remote](/subghz/remote) app sends those same buttons: every slot in a map has a `Button` setting (`Default`, `Up`, `Down`, `Left`, `Right`), so a hidden button can sit on a key of its own.

**Hold <kbd>OK</kbd> for 1–3 seconds** unless a step says otherwise.

**Timing matters.** Most receivers open a programming window of 5, 10 or 30 seconds. Read the whole procedure before you start.

::: danger
On many receivers, holding the programming button **too long** erases every remote it knows, not just one. Then you have to re-register all of your original remotes. When a step says "about 1 second", do not hold it for five.
:::

::: info Done! / Done?
A procedure ending in **Done!** has been confirmed working. **Done?** means it comes from the manufacturer's manual but nobody has reported back yet. It should work. If it does not, tell the Unleashed team in the GitHub issues.
:::

**Add Manually [Advanced]** is the menu entry right under `Add Manually`. Use it when you need to type values by hand instead of getting a random serial. After the system and band it asks, all in hex, for `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` and, on protocols that use one, `Enter SEED in hex`. Nice O-Code asks for `IC` (and `CERT`) instead. FAAC FIX, Monarch, Phantom/Hiland and DEA Mio ask for `DISC.` (discriminator) instead of SEED.

## Find your system

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

Not listed? See the [reference table](#programming-hidden-button-reference). It covers every other entry in the `Add Manually` menu.

---

## Alutech AT4N (AN-Motors)

- **Create it:** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

Use this for boards with a display and `F`, `CL`, `+`, `-` buttons. If your board has a `Learn` button instead, use [AN-Motors AT4](#an-motors-at4).

1. Open your new remote file.
2. Open the receiver box, find the `F` button and hold it for about 3 s. The display shows `Pr`.
3. Press `F` a few more times until the display shows `Lr`.
4. Pick a free remote number with `+` / `-`. A number that already has a remote shows a red dot in the bottom right corner.
5. Press <kbd>OK</kbd> (`Send`) on the Flipper once. The display flashes and a red dot appears next to that number.
6. Hold `F` on the board for about 3 s to leave programming mode.
7. Done!

[Video walkthrough, also shows other board types (Russian)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4

- **Create it:** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xC`

Use this for older boards with a `Learn` button. If your board has `F`, `CL`, `+`, `-` instead, use [Alutech AT4N](#alutech-at4n-an-motors).

1. Open your new remote file.
2. Open the receiver box and press `Learn` once. The LED turns on.
3. Press `Send` on the Flipper once. The LED on the board turns off.
4. Press `Send` again. The LED starts flashing. Wait a couple of seconds until it turns off.
5. Done!

[Video walkthrough (Russian)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR

- **Create it:** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xF` (on the original, all 4 buttons held together)

1. Open your new remote file.
2. On an existing remote that already works with the receiver, press all 4 buttons at the same time.
3. The receiver gives a continuous beep.
4. Press `Send` on the Flipper and hold it for about 2 s.
5. Wait until the receiver stops beeping.
6. Done?

## Beninca ARC (TO.GO)

- **Also sold as:** TO.GO 2VA / 4VA (previously TO.GO 2WV / 4WV). Receivers WB, WI and receivers built into the control panel.
- **Create it:** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Programming key:** **<kbd>↓</kbd>** = `0x0`, the hidden button

On a 2-button original the hidden button means holding both buttons at once, which is hard to do reliably. On the Flipper it is one key: <kbd>↓</kbd>.

### With a working remote: receivers WB / WI

1. Stand close to the receiver.
2. Open the file of the remote that already works. Press <kbd>↓</kbd> and hold for about 3 s. The hidden function is now active (an original remote's LED blinks here).
3. Within 5 s, press `Send` on that same remote for the channel you want to share.
4. Within 5 s, open your new remote file and press `Send`. This button will control that channel.
5. The receiver leaves programming mode. Test the new remote.
6. Done?

### With a working remote: receiver built into the control panel

Here the hidden button has to be sent from **both** remotes:

1. Working remote: <kbd>↓</kbd>, then `Send` within 5 s.
2. New remote: <kbd>↓</kbd>, then `Send` within 5 s.
3. Done?

::: info
ARC and HCS (rolling code) remotes cannot share one receiver. The first remote you save decides which type the receiver accepts from then on. Changing it needs a full receiver reset.
:::

## BFT Mitto

- **Create it:** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xF` (on the original, the pin hole on the back or buttons 1+2 held together)

::: info Seed
**Newer BFT Mitto remotes derive their Seed from the serial**, so a normal `Sub-GHz → Read` decodes them on the fly. They show up as `KL: BFT` straight away.
**Older models have a unique Seed** and read as `KL: Unknown` until you have it. There are two ways to recover it:
- Hold 2 buttons and read the `Hop` value. The remote sends its Seed in the clear (see [Making a full clone](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/subghz/seed-capturer) + qUnleashed.
:::

### With a working remote

1. Open your new remote file.
2. Stand at least 3 m from the receiver.
3. **Original remote:** press the hidden button on the back with a pin, or press buttons 1 and 2 together, until the remote's LED lights up.
4. **Original remote:** briefly press the button that opens the device.
5. On the Flipper, long-press <kbd>→</kbd> (`0xF`, shown as `Btn:F`) for 3–5 s.
6. Press the Flipper button you want to use to open the device.
7. Press <kbd>→</kbd> again.
8. Done?

### With access to the receiver box

1. Open your new remote file.
2. Open the receiver board box.
3. [Watch this video first](https://www.youtube.com/watch?v=5QXMBKI_-Ls). It shows the board side of the procedure.
4. On the Flipper, long-press <kbd>→</kbd> (`0xF`) for 3–5 s. This does exactly what holding buttons 1 and 2 on the original remote does in the video.
5. Done?

### Making a full clone (reads the Seed off your original)

::: danger
This makes a copy that **fights with your original remote** over the counter. Your original may even stop working until it is re-registered. Only do this if the original is broken or worn out and the Flipper is meant to replace it.
:::

1. Open `Sub-GHz → Read`.
2. **On the original remote only:** hold every button at once (both on a 2-button remote, the two in the top row on a 4-button remote), or press the hidden button with a pin.
3. You receive a signal. Open it and look at `Fix:`. It starts with `F`, for example `F00F1C9B`. The leading `F` is the button code for "programming button pressed".
4. The `Hop:` value of that same signal is your Seed.
5. Write the `Hop` value down and replace its first digit `F` with `0`.
6. Now press the button on your remote that you actually want to clone, and read that signal.
7. Write down its `Fix:`. Its first digit matches the `Btn:` shown for the signal.
8. Create the remote with `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` and enter:
   - `SERIAL`: the `Fix` from step 7 with its **first** digit replaced by `0`
   - `BUTTON`: the first digit of that `Fix`
   - `COUNTER`: `FF F9`
   - `SEED`: the value from step 5
9. A high counter like `FF F9` jumps past your original's counter. That makes the clone work at once, and it is also what desyncs the original.

**Or edit a saved file instead.** Save the signal of your original remote (an older one is listed as `KL: Unknown`), copy the file to a PC and add these two lines after the `Key: ...` line:

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Replace the `X`s with the Seed digits from step 4 and copy the file back. You now have an exact clone with the same counter.

### No hidden button, or it will not send the Seed

This applies only to remotes with a unique Seed. A remote that already reads as `KL: BFT` has nothing to recover. If you cannot get the original into programming mode, use the [Seed Capturer](/subghz/seed-capturer) app: pick `BFT Mitto` at 433.92 MHz, press one button repeatedly, then recover the Seed in qUnleashed.

## CAME Atomo

- **Also sold as:** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Create it:** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (or `868.35 AM650`)

::: warning
With CAME Atomo, always hold `Send` for **at least 2 seconds**. The protocol needs that long to get the whole code out.
:::

### With a working remote (or its copy on the Flipper)

1. Open your new remote file.
2. Stand at least 3 m from the receiver.
3. **Original remote:** press and hold the button bound to that receiver for about 10 s.
4. You now have about 20 s to add the new remote.
5. Long-press `Send` in the new remote file for 3–4 s and release. This registers it.
6. Wait 20 s, then press and hold `Send` again. It should now operate the receiver.
7. Done!

### With access to the receiver box

1. Open your new remote file.
2. Open the receiver box and find the programming button for the channel you need. Some receivers have several channels. An RE432M / RE862M, for example, has two, each with its own remotes and buttons. Press `1` or `2` on the board to enter programming mode for that channel.
3. Long-press `Send` on the Flipper for 3–4 s and release.
4. Press `CLEAR` once to leave programming mode, or wait about 20 s.
5. Done!

::: info
Static 12/24-bit CAME and CAME TWEE remotes cannot open programming mode, and they cannot be registered into a window that an Atomo remote opened. Only Atomo remotes can do that.
:::

[Video walkthrough (Russian)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449

- **Also sold as:** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Receivers RCQ449.
- **Read with:** modulation `FM12K`, **not** AM650
- **Create it:** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Programming key:** <kbd>→</kbd> = `0xD` (on the original, the button in the small hole under the keys)

1. Open your new remote file.
2. Stand 1–2 m from the receiver.
3. Open the file of the remote that already works. Press <kbd>→</kbd> and release it when the receiver gives a short beep.
4. Press `Send` on that same remote once. The receiver gives another short beep.
5. Open your new remote file and press `Send`. The receiver beeps twice in a row.
6. Release the key. The receiver gives one longer beep.
7. Wait at least 10 s, then try the new remote.
8. Done?

**If it fails**, or you hear a long beep before step 5, wait 20 s and start again from step 3.

## DEA Mio

- **Create it:** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xF`, the hidden button

1. Open your new remote file.
2. `Send` acts as one of the normal buttons. This is the one you register.
3. <kbd>→</kbd> acts as the hidden button of the original remote.
4. Follow your manufacturer's instructions for adding a remote, using these two keys in place of the original's buttons.

## Ditec GOL4

- **Also sold as:** GOL4 / GOL4C. Receivers BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Create it:** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0x0`, the hidden button

1. Open your new remote file.
2. Open the receiver box. Press and release `PRG`. The `SIG` LED lights up and stays on.
3. Press `Send` on the Flipper for the channel you want to store.
4. `SIG` flashes while storing. When it is steady again you can add another remote.
5. Storing ends 10 s after the last remote, or press `PRG` again to leave at once.
6. Done?

::: info
On some boards a jumper on the receiver has to be set before programming works at all. Check your receiver manual.
:::

## DoorHan

- **Create it:** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (or `315.00 AM650`)

### Finding your frequency first

DoorHan uses either 315.00 or 433.92 MHz. Create a remote on one of them, open it and press `Send` while you watch the receiver. If you guessed right, the light on the receiver turns on while you hold the key and off when you release it. If nothing happens, try the other band. You can also read your existing remote with `Sub-GHz → Read`.

### With access to the receiver box

Take the protective cover off and look at the buttons:

- **4 buttons (`Radio`, `Reverse`, `Auto`, …):** hold `Radio` until the LED lights up, then press `Send` on the Flipper 2 times. The LED goes out.
- **4 buttons (`R`, `P`, `+`, `-`) and a display:** press `R`, press `Send` 2 times, wait about 10 s.
- **4 buttons (`+`, `-`, `F`, `TR`) and a display:** press `TR`, press `Send` 2 times, wait about 10 s.
- **Anything else:** hold `P` for about 2 s until the LED flashes, then press `Send` 2 times. The LED goes out.

In all cases, wait until the receiver returns to normal mode before testing.

### With an original remote in your hand

1. Open your new remote file.
2. Stand 1–2 m from the receiver board.
3. On the old remote, press and keep holding the second (lower) button, then also press the first (upper) one. Hold both for 1 s and release.
4. Press the working button on the old remote (the one that opens the gate). Hold it for 1 s and release.
5. Steps 3 and 4 must be done within 5 s of each other. Do not hold too long, and do not rush.
6. The receiver beeps. You now have 10 s: press `Send` on the new remote 2 times, holding at least 1 s each time.
7. The receiver beeps again. The new remote is registered.
8. Done!

### With a copy of your original remote on the Flipper

1. Open your **existing (original)** remote file.
2. Stand 1–2 m from the receiver board.
3. Press <kbd>←</kbd> (`0x8`), hold 1 s, release. Then press <kbd>→</kbd> (`0xA`), hold 1 s, release.
4. Press the working button (<kbd>OK</kbd>, `Send`), hold 1 s, release.
5. Steps 3 and 4 must be done within 5 s of each other.
6. The receiver beeps. Press <kbd>Back</kbd> and open your **new** remote file. Within 10 s, press `Send` 2 times, holding at least 1 s each time.
7. The receiver beeps again. The new remote is registered.
8. Done!

[Video walkthrough (Russian)](https://www.youtube.com/watch?v=wZ5121HYv50) and [a second one](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
If a DoorHan receiver drifted out of sync with your file, Unleashed has forced-resync counter modes for DoorHan. See [Counter modes](/subghz/counter-mode).
:::

## Erreka IRIS

- **Also sold as:** IRIS IR02 / IR04 on 433.92 MHz, IR02/868 / IR04/868 on 868.35 MHz
- **Create it:** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` for IR02 / IR04, or `868.35 AM650` for the /868 models
- **Programming key:** <kbd>→</kbd> = `0xF` (on the original, bridging pins `1` and `5` of the 5-way connector that is exposed on the side of the remote)

Erreka IRIS is a roller code remote: KeeLoq with a secret Seed. Both registration methods from the manufacturer work from the Flipper.

### With access to the receiver box

1. Open your new remote file.
2. Activate programming mode on the receiver, usually with a button on the board.
3. Press `Send` on the Flipper once. The receiver beeps **twice** if the remote was stored.
4. Repeat step 3 for any other remotes.
5. Turn programming mode off.
6. Done!

### With a working remote

The original IRIS opens the programming window when you bridge pins `1` and `5`. It then sends its Seed in the clear, and the receiver answers with one beep. On the Flipper, <kbd>→</kbd> does it.

The remote that opens the window must be one the receiver already knows: either the first Flipper remote you registered at the receiver button, or your original remote with its Seed recovered (see below).

1. Open the file of the registered Erreka remote.
2. Long-press <kbd>→</kbd> (`0xF`) for about 2 s. The receiver beeps **once** and is ready to store codes.
3. Within 10 s, press <kbd>Back</kbd> and open your new remote file.
4. Press `Send`. The receiver beeps **twice** if the remote was stored.
5. If 10 s pass with nothing stored, the receiver leaves programming mode. Start again from step 2.
6. Done?

### If the new remote will not register

Some installations give **every remote the same Seed** because the installer programmed them as a set. On those, a remote with a random Seed is never accepted. The fix is to keep the existing Seed and change only the serial:

1. Get the Seed off a remote that already works (see below).
2. Create a remote with `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (or `868.35 AM650`) and enter:
   - `SERIAL`: `0X XX XX XX`, any value that is not one of your existing remotes. **Keep the leading `0`**. That nibble is the button, which is asked for separately.
   - `BUTTON`: `02`
   - `COUNTER`: `00 02`
   - `SEED`: the Seed from step 1
3. Run either registration procedure again.

::: tip Keep the leading zeros
Some systems use only the bottom 3 or 4 digits of the serial, so their remotes look like `00 00 0A BC`. On those, a long random serial may be refused. Read one of your working remotes, copy the shape of its serial (same number of significant digits, leading zeros kept) and change only the last digits. If two of your original remotes show the same Seed once recovered, you have this kind of installation, and reusing the Seed is the right move.
:::

### Getting the Seed off your original IRIS remote

An Erreka remote reads as `KL: Unknown` until the Seed is known.

**Option 1: short the pins and read it.** This is the quick way. The pins are on the outside of the case.

1. Open `Sub-GHz → Read`. In `Config`, set the frequency to 433.92 or 868.35 and the modulation to `AM650`.
2. Bridge pins `1` and `5` of the 5-way connector on the original remote.
3. You receive a signal. The manufacturer shows as **Unknown**. That is expected, because the Flipper does not know the Seed yet.
4. Open the signal. `Fix:` starts with `F`, the "programming button pressed" code.
5. **The `Hop:` value of that signal is your Seed**, in the clear.
6. Either type it into `Add Manually [Advanced]` as above, or save the signal, copy it to a PC and add these lines after `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

The file now decodes, and you can use it to open the programming window for new remotes.

**Option 2: [Seed Capturer](/subghz/seed-capturer)**, when you cannot bridge the pins. Pick `Erreka` and your frequency, press one button repeatedly, then recover the Seed in qUnleashed.

## FAAC RC, XT

- **Also sold as:** XT2 / XT4 433 RC / 868 RC, and the older RC coding
- **Create it:** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (or `868.35 AM650`)
- **Programming key:** <kbd>→</kbd> = `0xB` (on the original, buttons 1+2 held together, the "master" press)

::: warning
These are KeeLoq, not SLH. Read your remote first. If the Flipper calls it `KL: FAAC_RC,XT`, you are in the right place. If it says `FAAC SLH`, go to [FAAC SLH](#faac-slh).
:::

1. Open your new remote file.
2. Stand close to the receiver.
3. Open the file of the remote that already works. Press <kbd>→</kbd> and hold for about 1–2 s (until the original's LED would start flashing), then release.
4. While the window is open, press `Send` on that same remote for the button you want to copy.
5. Open your new remote file and press `Send`.
6. Repeat steps 3–5 for every other button.
7. Done?

::: info
Only a **master** remote can hand over its system code. On an original remote, watch the LED when you press a button. A short blink before it goes steady means master. Steady straight away means slave. With a slave, register the new remote at the receiver instead.
:::

## FAAC SLH

- **Create it:** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (or `868.35 AM650`)
- **Programming key:** **<kbd>↑</kbd>** sends the programming signal

### With access to the receiver box

1. Open your new remote file.
2. Open the receiver box and find the programming button on the board.
3. Hold <kbd>↑</kbd> on the Flipper and, at the same time, press and hold the programming button on the board.
4. The board LED goes on, off, on, off, then on again.
5. Release everything.
6. Press `Send` on the Flipper a couple of times, holding each press for 1–3 s.
7. Done!

[Video walkthrough](https://www.youtube.com/watch?v=NfZmMy37XUs)

### With a master remote, no need to open the box

FAAC can register new remotes from an existing master remote, and the Flipper can take part. First read the Seed off the master:

1. Open `Sub-GHz → Read`. Set the frequency to 868.35 or 433.92 and the modulation to `AM650`.
2. Hold two buttons on the original master remote until its LED turns on.
3. Click the one button you want the Seed for. **The Seed is different for every button.**
4. You receive a signal. Open it and note the Seed.
5. Create the remote with `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (or 868.35) and enter:
   - `SERIAL`: `0A 0R RR RR`, replacing each `R` with any digit
   - `BUTTON`: `06`
   - `COUNTER`: `00 00 00 02`
   - `SEED`: the Seed from step 4
6. The Flipper now acts as a new remote. Press `Send` a couple of times near the receiver to register it.
7. Done!

### If neither of those is possible

- **The receiver's remote programming is disabled.** Some installers switch it off, and then nothing registers.
- **Your remote is a slave, not a master.** Only a master can send the programming code.

In both cases the only route left is a **clone** of a remote the receiver already knows, and that needs the Seed. Get it with [Seed Capturer](/subghz/seed-capturer), then build the clone with the **original remote's** `SERIAL` and `BUTTON`.

::: tip Where SERIAL and BUTTON sit inside Fix
- **FAAC SLH and Genius:** `BUTTON` is the **last** digit of `Fix`. `SERIAL` is the rest, with a `0` in front.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin and the other `KL:` entries): `BUTTON` is the **first** digit of `Fix`. `SERIAL` is the same `Fix` with its first digit replaced by `0`.
:::

## Genius (SLH)

- **Also sold as:** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Create it:** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (or `868.35 AM650`)
- **Programming key:** **<kbd>↑</kbd>** sends the programming signal

Genius SLH is the same frame as FAAC SLH with its own manufacturer key (a `Manufacture: Genius` line in the file), so **[the FAAC SLH procedures](#faac-slh) apply exactly as written**. If programming is disabled or your remote is a slave, capture the Seed with [Seed Capturer](/subghz/seed-capturer) (pick `Genius`) and build a clone as described under FAAC SLH.

::: warning
Do not confuse this with `KL: Genius TX4RC`. The RC models are KeeLoq, not SLH, and have [their own section](#genius-tx4rc-bravo-echo). If unsure, read the remote first.
:::

## Genius TX4RC (Bravo / Echo)

- **Also sold as:** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Create it:** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xB`

1. Open your new remote file.
2. Open the receiver box and press `SW1` for channel 1 or `SW2` for channel 2. `LED1` / `LED2` lights up and stays on. That is learning mode.
3. Within 10 s, press `Send` on the Flipper and hold at least 1 s.
4. The LED blinks twice. The remote is stored.
5. The receiver stays in learning mode, so you can add more remotes by repeating step 3. Press `SW1` / `SW2` again to leave, or it leaves by itself 10 s after the last remote.
6. Done?

## Hormann EcoStar

- **Also sold as:** RSC2 / RSE2 / RSZ1 on 433.92 MHz. EcoStar Liftronic / Portronic drives.
- **Create it:** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Programming key:** **<kbd>↓</kbd>** = `0x6` (this one is on Down, not Right)

1. Open your new remote file.
2. Find the clear programming button on the drive, usually underneath the motor, and hold it for about 1 s. The motor LED starts flashing slowly.
3. Press `Send` and hold for about 2 s. The motor LED speeds up.
4. Press `Send` again and hold for about 2 s. The LED flashes very fast, then goes out. The remote is programmed.
5. Done?

::: danger
Holding that clear button for about 5 s erases **every** remote the drive knows.
:::

## Jarolift

- **Also sold as:** TDEF radio tube motors with TDRC / TDRCE remotes
- **Create it:** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

The keys are already mapped to the original remote's buttons:

| Flipper key | Jarolift button |
|---|---|
| <kbd>OK</kbd> (`Send`) | Down |
| <kbd>←</kbd> | Up |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

On the original, `Learn` means holding Up + Down together and then pressing Stop. On the Flipper it is one key press.

### With access to the motor head

1. Open your new remote file.
2. Press the learning button on the motor head. The motor vibrates briefly and stays in learning mode for 5 s.
3. If you cannot reach that button, disconnect the motor from the mains and reconnect it. It enters learning mode for 5 s by itself.
4. Within those 5 s, press <kbd>↑</kbd> (`Learn`).
5. The motor vibrates again. The code was learned.
6. Done!

### With a working remote

1. Open your new remote file.
2. On the working remote, hold Up + Down together, then press Stop 8 times. The motor vibrates briefly.
3. Within 5 s, press <kbd>↑</kbd> (`Learn`) on the Flipper.
4. The motor vibrates again.
5. Done?

::: tip
If the working remote is also on your Flipper, step 2 is <kbd>↑</kbd> (`Learn`) in that remote's file.
:::

## KingGates Stylo 4k

- **Also sold as:** Stylo 2K / Stylo 4K (10S001). Receivers Fred, Myo.
- **Create it:** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

There is no separate programming button. The four keys are the four channels of the original:

| Flipper key | Channel code |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Open your new remote file.
2. Open the receiver box. On a 2-channel `Fred`, the LED colour shows the channel: green is channel 1, red is channel 2.
3. Press the receiver button once for channel 1 (green) or twice for channel 2 (red). This starts learning mode.
4. Within 5 s, press `Send` on the Flipper for about 1 s.
5. The LED turns off and then on again. The remote was learned.
6. Learning ends after 5 s with no signal, or press the receiver button again.
7. Done?

## Mhouse

- **Also sold as:** GTX4 / GTX4C / TX3 / TX4, also Moovo and Nice Home ECCO
- **Create it:** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xF`, the extra (hidden) button

### With access to the receiver box

1. Open your new remote file.
2. Press and hold `P1` on the receiver until the `P1` LED stays on, then release.
3. Press `Send` and hold until the `P1` LED flashes 3 times.
4. Release. This registers all buttons of the remote at once (Nice "mode 1").
5. Wait 10 s before testing.
6. Done?

### With a working remote

Mhouse is the same Nice receiver family as [Nice Smilo](#nice-smilo):

1. Stand close to the receiver.
2. Open your new remote file. Press and hold `Send` for at least 5 s, then release.
3. On the working remote, press and slowly release its button 3 times.
4. Open the new remote file again, press `Send` for 1 s and release.
5. Wait 10 s before testing.
6. Done?

## Nice Flor S

- **Create it:** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### With a working remote

You do not need the receiver box, but **the very first remote always has to be registered with the receiver button**. Below, `OLD` is the authorised remote and `NEW` is the Flipper. Stand within 3 m of the receiver.

1. Open your new remote file. Press and hold `Send` for at least 5 s (7 s on an OXIBD receiver), then release.
2. On `OLD`, press its button 3 times slowly.
3. Press `Send` on the Flipper slowly, then release.
4. Wait 10 s, then press `Send` to test.
5. Done?

### With access to the receiver box

Register it the way your original remote's manual describes. For a typical NICE FLOX2R receiver:

1. Open your new remote file.
2. Press the learning button on the receiver for 1–2 s. The LED turns on for 5 s. Do the next step within those 5 s.
3. Press `Send` until the LED on the receiver turns off.
4. Release and wait 2 s.
5. Press `Send` again. The LED flashes 3 times and the remote is registered. If not, start over from step 2.
6. Wait 5 s, then press `Send` to test.
7. Done!

::: tip
Nice Flor-S counter variants for specific receivers (floxi2r, ox2) are available as [counter modes](/subghz/counter-mode).
:::

## Nice One

- **Create it:** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One is the Nice FloR-S family with different keying, and the receiver side is identical. **[Both Nice Flor S procedures](#nice-flor-s) apply exactly as written.** If your remote reads as FloR-S but the counter looks wrong, it may be Nice O-Code instead.

## Nice O-Code

- **Create it:** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (or `Nice O-Code One` for the Nice One keying)
- **Create it for an installed system:** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, which asks for `SERIAL`, `BUTTON`, `COUNTER` and the installer code (`Enter IC in hex`)
- **Create it with a certificate:** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, which always asks for serial, button, counter, installer code **and** the receiver certificate (`Enter CERT in hex`)

O-Code is Nice FloR-S keyed with a 16-bit **installer code (IC)** shared by every remote of one installation. The receiver side is the same as FloR-S, so [both Nice Flor S procedures](#nice-flor-s) apply, but a remote only reaches a receiver set up with the same installer code.

- **For a system of your own**, plain `Nice O-Code` invents an installer code with the serial. A factory receiver will not take it at the button, so register a plain [Nice One](#nice-one) remote first.
- **For an installed system**, recover the installer code from a working remote with the [Nice O-Code app](/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`). Press the remote's button 4 or more times (do not hold it). On the result screen, <kbd>→</kbd> (`New`) writes a new remote with the same installer code and button but its own serial and counter. That is the one to register. `Save` writes a plain clone for testing.

::: info Tested on a factory-fresh OXIBD
In mode I the receiver **ignores O-Code frames completely**, whatever installer code they carry, while a plain `Nice One` remote is memorised at once. Only an O-Box writes the installer code into the receiver. On an untouched receiver use the plain Nice Flor S / Nice One entries.
:::

::: tip COUNTER
Do **not** leave `COUNTER` near zero. The receiver refuses a count behind the one it stored, and also one that sits implausibly far behind the remotes it knows, even for a new serial. Set it a little below your working remote's count (the app's `New` does that for you). If you have already sent frames from that serial, use a value a little above the highest you sent.
:::

**Certificate enrolment.** A remote carrying the receiver's certificate sends 112-bit frames during its first **twenty** uses, and the receiver enrols it by itself. Open the file in range of the gate and press the key about once a second, **ten to fifteen times in one sitting**. The gate opens around the tenth press, and after that the remote is registered for good. If all twenty uses pass without the gate opening, delete the file and make a new one. Certificates, the five Nice registration paths, receiver LED codes and the counter window are covered in detail on the [Nice O-Code](/subghz/nice-o-code) page.

## Nice Smilo

- **Also sold as:** SM2 / SM4. Receivers SMXI, SMXIS, and OXI set to Smilo coding.
- **Create it:** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0xB`, the extra (hidden) button

Nice receivers store a remote in one of two modes. **Mode I** gives each remote button the matching receiver output. **Mode II** lets you pick which output a single button controls.

### With access to the receiver box: mode I

1. Open your new remote file.
2. Press and hold the receiver button for at least 3 s.
3. Release it when the LED lights up.
4. Within 10 s, press `Send` and hold for at least 2 s.
5. The receiver LED flashes 3 times. The remote is stored.
6. To add more, repeat step 4 within another 10 s.
7. Done!

### With access to the receiver box: mode II

1. Open your new remote file.
2. Press the receiver button as many times as the output number (twice for output 2).
3. Check that the LED flashes the same number of times.
4. Within 10 s, press the Flipper key you want for that output and hold for at least 2 s.
5. The LED flashes 3 times. The remote is stored.
6. Done!

### With a working remote

The first remote always has to be registered with the receiver button. The new remote **inherits the mode** of the old one, so with mode II you press the matching buttons on both.

1. Stand close to the receiver.
2. Open your new remote file. Press and hold `Send` for at least 5 s, then release.
3. On the working remote, press and slowly release its button 3 times.
4. Open the new file again and press and slowly release `Send` once.
5. Done?

::: info
These receivers cannot delete a single remote, only all of them at once.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman)

- **Create it:** `Sub-GHz → Add Manually → Security+2.0` or `Security+1.0`, then the band. The default is `433.92 AM650`. Security+ 1.0 also offers `315.00 AM650` and `390.00 AM650`. Security+ 2.0 offers `310.00`, `315.00` and `390.00 AM650`.

**Which one do you have?** Look at the colour of the `Learn` button on the motor head:

| Learn button | Create this |
|---|---|
| Yellow | `Security+2.0` |
| Purple | `Security+1.0` → `315.00 AM650` |
| Green | `Security+1.0` → `390.00 AM650` |
| Red / orange | Billion Code, not Security+ |
| Grey / white | dip switch remote, not Security+ |

1. Open your new remote file.
2. Find `Learn` on the motor head: usually on the back or the side panel, sometimes behind the light lens.
3. Press and release it once. The learn LED glows steadily for 30 s.
4. Within those 30 s, press and hold `Send` on the Flipper.
5. Release when the motor lights flash or you hear two clicks. The remote is programmed.
6. Press `Send` again to check that the door moves.
7. Done?

::: tip
If the motor-head button will not cooperate, some systems let you program from the wall console instead. For Security+ 2.0 keypad frames, see [Security+ PIN](/subghz/secplus-pin).
:::

## Somfy Keytis

- **Also sold as:** Keytis NS 2 RTS / KeyGo 4 RTS
- **Create it:** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (this is **433.42 MHz**, not 433.92)
- **Programming key:** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` is `Key_1`)

An original Keytis has no `Prog` key on the front. You bridge the two `PROG` pads on the back of the board with a screwdriver. The Flipper needs only <kbd>↑</kbd>.

### With access to the receiver

1. Open your new remote file.
2. Press and hold `PROG` on the receiver for about 3 s, until it blinks.
3. Press <kbd>↑</kbd> (`Prog`) on the Flipper.
4. The blind or gate moves briefly up and down. The remote is registered.
5. Done?

### With a working remote

1. Open your new remote file.
2. Put the registered remote into programming mode until the blind or gate moves briefly. On an original Keytis, bridge the `PROG` pads. On the Flipper, press <kbd>↑</kbd> in that remote's file.
3. Open your new remote file and press <kbd>↑</kbd> (`Prog`) until the blind or gate moves briefly again.
4. Done?

::: danger
On many Somfy receivers, holding the programming button for more than about 7 s erases every remote and sensor it knows.
:::

::: info
Keytis uses the newer `NS` radio protocol. An older non-NS RTS receiver will not accept it until the remote's protocol is switched over. See Somfy's own documentation for your receiver.
:::

## Somfy Telis

- **Create it:** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (this is **433.42 MHz**, not 433.92)
- **Programming key:** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Open your new remote file.
2. Long-press `Prog` on a remote already registered to the device, until the blinds move briefly up and down.
3. Press and hold <kbd>←</kbd> (`Prog`) on the Flipper until the blinds move briefly up and down again.
4. Done?

## Sommer

- **Also sold as:** TX03-868-4 / TX03-868-2 (SOMloq). Pearl, Duo, Sprint, Marathon drives.
- **Read with:** modulation `FM12K` or `FM476`, whichever decodes your remote
- **Create it:** `Sub-GHz → Add Manually → KL: Sommer`, then pick the band that matches how your remote read: `434.42 FM12K` (default), `868.80 FM12K`, `434.42 FM476` or `868.80 FM476`
- **Programming key:** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Older guides list four separate Sommer entries (`fm2` and plain). Current firmware has one `KL: Sommer` row, and the band picker selects both the frequency and the modulation variant.
:::

### With access to the receiver

1. Open your new remote file.
2. Find the `learn` / `code` button on the receiver. On a Duo it is under the light cover, on a Sprint behind the switch box cover, and on a Marathon under a clear plastic cover next to the code button.
3. Press it briefly. The receiver LED lights up.
4. Press and hold `Send`. When the receiver LED starts blinking fast, release.
5. The receiver LED goes out. The remote is programmed.
6. Done?

### On a sliding gate operator

Press the `Radio` button on the control unit instead. A red LED confirms programming mode. Press it again to pick the channel, then hold `Send` until the channel LED flashes and goes dark. The receiver leaves programming mode by itself after about 30 s with no signal.

## V2 Phoenix (Phox)

- **Also sold as:** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Receivers RXP, MR2.
- **Create it:** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Programming key:** <kbd>→</kbd> = `0x3` (on the original, buttons 1+2 or 1+3 held together)

::: warning
This mapping is **not confirmed yet**. If it does not work, register at the receiver button and report it in the Unleashed issues.
:::

1. Open your new remote file.
2. Open the file of the registered remote. Press <kbd>→</kbd> and hold for at least 5 s, then release.
3. Within 5 s, open the new remote file and press `Send`.
4. Release. Repeat for any other buttons.
5. Done?

The remote that opens the window must already be stored in the receiver, and everything stored this way inherits its logic. If it only had button 1 stored, new remotes can only be stored on button 1. Some V2 receivers can be switched to `Static` mode, which ignores the rolling part of the key.

---

## Recovering a Seed

**FAAC SLH**, **Genius**, **Erreka** and **BFT Mitto** build their rolling code from a secret **Seed**. Without it the Flipper cannot decode those remotes (they read as `KL: Unknown` or not at all) and cannot build a remote the receiver accepts. You need the Seed when:

- the receiver's radio programming is switched off, so only a clone works;
- your FAAC/Genius remote is a slave and cannot send the programming code;
- you cannot get at the receiver;
- an Erreka installation shares one Seed across all remotes;
- an older BFT Mitto will not enter programming mode.

The [Seed Capturer](/subghz/seed-capturer) app (`Apps → Sub-GHz → Seed Capturer`) collects consecutive `Fix` + `Hop` pairs from one button. It never transmits, and saves them to `/ext/apps_data/subghz_seed_captures/`. The qUnleashed companion app (see [qUnleashed app](/mobile/qunleashed-app)) then brute-forces the Seed and can write the finished clone file for you.

Once you have the Seed:

- **New remote** (the receiver must accept new remotes): `Add Manually [Advanced]` → your system → band, your own `SERIAL`, and the recovered `SEED`.
- **Clone** (works without programming, because the receiver already knows that serial): let qUnleashed save it, or enter the **original's** `SERIAL` and `BUTTON`, the `SEED`, and a `COUNTER` a little above the original's current value.

::: danger
A clone shares the counter with the original and the two will fight over it. Only clone when making a new remote is impossible.
:::

## Programming / hidden button reference

Find the "put the receiver into programming mode" step in your manufacturer's manual. Wherever it tells you to press something on the original remote, press the key from this table instead.

::: info
These are the keys on a remote as `Add Manually` creates it. If you change the button code by hand, the keys move with it.
:::

| System (Add Manually entry) | Code | Key on the Flipper | On the original remote |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | the programming signal |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | pin hole on the back, or buttons 1+2 held |
| `Erreka` | `0xF` | <kbd>→</kbd> | pins 1 and 5 of the 5-way connector bridged |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | hidden button |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | all 4 buttons held together |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | extra / hidden button |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | extra / hidden button |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | buttons 1+2 held (master press) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | programming mode button |
| `KL: Monarch` | `0xB` | *no arrow sends it* | set the button code by hand in signal settings |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | extra / hidden button *(unconfirmed)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | extra / hidden button |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | extra / hidden button |
| `KL: Sommer` (all bands) | `0x6` | <kbd>→</kbd> | extra / hidden button |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | extra / hidden button |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | button in the hole under the keys |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | extra / hidden button |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | hidden button (buttons 1+2 held) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | hidden button |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn`: Up+Down held, then Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | `Prog` button |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | `Prog` pads on the back of the board |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | buttons 1+2 or 1+3 held *(unconfirmed)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | button 3 *(unconfirmed as a programming button)* |

### Everything else in the menu

Any entry that is not in this table and has no section above is registered the plain way: **put the receiver into learning mode with its own button, then press `Send` on the Flipper within the time window your manufacturer gives.**

That covers most KeeLoq systems (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) and every static protocol, such as CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero and [ZKTeco](/subghz/zkteco-cmp200).

## When it does not work

- **Nothing happens at all.** Check the frequency first. It is the most common mistake. Read your original remote with `Sub-GHz → Read` and compare. Some brands sell the same remote on two frequencies: DoorHan on 315 and 433.92, FAAC and Genius on 433.92 and 868.35. Use the [Frequency Analyzer](/subghz/frequency-analyzer) if you are unsure.
- **Wrong modulation.** Most systems here use `AM650`, but Cardin S449 is `FM12K` and Sommer is `FM12K` or `FM476`. Set it in `Sub-GHz → Read → Config`, and pick the matching band in Add Manually.
- **The receiver reacts but never stores the remote.** You are probably missing the time window. Re-read the steps and have the remote file open before you touch the receiver button.
- **It stored the remote but nothing opens.** Hold `Send` longer. Several protocols need 1–3 s to get a full code out, and CAME Atomo needs at least 2 s every time.
- **It worked once and then stopped.** On a rolling code system this is a counter problem: you cloned a remote instead of making a new one. Press `Send` a few more times in a row, because the receiver accepts a counter that ran ahead within a window. To keep both remotes working, create a new remote instead (see [Rolling codes](/subghz/rolling-codes)). A static remote has no counter, so if it stops working, check the battery, the frequency or the receiver.
- **All your remotes stopped working.** You most likely held a programming button long enough to trigger the receiver's erase function. Re-register every remote, originals included.

## Sources and manuals

- [FAAC SLH: video walkthrough](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Somfy RTS protocol write-up](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS: installation instructions](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Somfy Keytis NS 2 RTS registration (Somfy forum)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [BFT Mitto manual](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [NICE FLOX2R receiver programming](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Nice Flor S programming](https://motepro.com.au/Instructions/Nice.pdf)
- [Nice Smilo SM2/SM4 and SMXI receiver manual](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code: installer manuals from [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, FLOR receiver `IS0063A00MM`, Era One transmitters `IS0102A01MM`)
- [Mhouse GTX4 / TX4 / Nice Home ECCO5 programming](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS: `Guia rapida mando IRIS` (MSR-044/03), from [erreka.com](https://www.erreka.com/)
- [Jarolift TDEF motor manual](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Beninca TO.GO transmitter programming](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Ditec BIX L / BIX A receiver manual](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Cardin S449 QZ2 programming notice](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Cardin RCQ449 receiver manual](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Hormann RSC2 hand transmitter manual](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer: teaching a transmitter to a sliding gate operator](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [V2 RXP4 receiver manual: radio learning](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [KingGates Fred receiver programming](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Related pages

- [Add Manually](/subghz/add-manually)
- [Rolling codes](/subghz/rolling-codes)
- [KeeLoq](/subghz/keeloq)
- [Counter modes](/subghz/counter-mode)
- [Supported systems](/subghz/supported-systems)
- [Seed Capturer](/subghz/seed-capturer) · [Nice O-Code](/subghz/nice-o-code)
