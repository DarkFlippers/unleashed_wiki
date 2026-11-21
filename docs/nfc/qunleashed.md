---
title: Fast key recovery with qUnleashed
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Fast MIFARE Classic key recovery with qUnleashed

A hands-on guide by **@gromovyna**: recover MIFARE Classic keys quickly using Unleashed and its companion app
**qUnleashed** (developed and maintained by the Unleashed team; big thanks to
[apfxtech](https://github.com/apfxtech), the app's original author). It's a continuation of
[Nested attacks and Fudan backdoors](/nfc/nested-fudan); reading that page first is recommended but not required.

The recovery covers **all attacks and nonce types** known at the time of writing: *weak, hard, static, static
encrypted*. Unlike the [MFKey app](/nfc/mfkey-app), the heavy computation runs on your phone or computer, so it
usually takes **minutes**, not hours.

::: warning You need the tag in your hands
The tag must be physically present for the final read. "I made a dump for a friend and the tag is gone" won't work.
:::

## Versions

The functionality may exist in slightly earlier versions, but these were used for testing:

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

See also [qUnleashed app](/mobile/qunleashed-app) for installation and other features.

## What you need

A **MIFARE Classic** tag (or **MIFARE Plus in SL1**, only SL1) with **at least one known key or a backdoor**.

![A tag with one unknown key](/img/remote/286db70e86cfa835.png)

![A backdoored tag: keys unknown, but sectors read via the backdoor](/img/remote/59bd4aa5ae1242c1.png)

If your tag has no backdoor and not a single known key, get one from the reader first with [MFKey32](/nfc/mfkey).
qUnleashed can recover keys from reader nonces too (see step 2).

## Step 1. Collect nonces

1. Before the attack, it's a good idea to clear `/ext/nfc/.nested.log` if you have one (`/ext/` is the SD card). After
   recovery it also makes sense to delete it, so it doesn't grow and clutter things up. For qUnleashed this is not
   critical, but it's good practice.
2. Read the tag: `Main Menu → NFC → Read`. Wait while the phases run; which ones appear depends on the tag's nonce
   type: **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**, **Calibration**,
   **Nonce Collection**.

   ![Nonce collection](/img/remote/786d77b7b65b3fd0.png)

3. When the tag info appears, **save the incomplete dump**: you'll need it later.
4. Optionally check in qUnleashed that the nonces are there: connect the Flipper, open `Archive → External → nfc`,
   enable hidden files (the "burger"/three-dots menu in the top right) and look for `.nested.log`.

   ![.nested.log in qUnleashed](/img/remote/c4c534fbe93faa8a.png)

## Step 2. Recover the keys

Everything happens in **qUnleashed**; the Flipper must stay connected (Bluetooth or cable) the whole time.

1. Open `Tools → Recover MIFARE Keys`.

   ![The menu entry](/img/remote/1a255b9128f988ab.png)

2. Wait for the recovery to finish.

   ![Recovering keys](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Be patient
   It can take a while depending on the size of `.nested.log`, the nonce types, the power of the device running
   qUnleashed and so on. Usually it's minutes. Wait for the operation to complete. Static encrypted nonces take the
   longest.
   :::

3. Review the result. The recovery phase works with **`.mfkey32.log`** (reader nonces) and **`.nested.log`** (tag
   nonces). The screen shows where each key came from, how many were added to the user dictionary or to the
   candidate dictionary, and so on.

   ![Recovery result](/img/remote/1c5f56614caf4530.png)

Where the keys go depends on the nonce type:

| Nonces | Result |
|---|---|
| weak, hard, static | Keys are added to the **user dictionary** `/ext/nfc/assets/mf_classic_dict_user.nfc`. |
| static encrypted | The key can't be computed exactly at this stage, so a **candidate dictionary** (a.k.a. **CUID dictionary**) is built: `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, where `{UID}` is the ID of your tag. It can be big: the author's example had more than **1.2 million candidates** for one tag. |

## Step 3. Read the tag again

Put the tag on the Flipper and either go to `NFC → Read`, or open the saved incomplete dump and choose
**Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

With a **CUID dictionary**, it gets loaded first. The candidate dictionary is big, so this takes time, and you see a
progress bar (*"CUID dictionary is loading"*). **Minutes** is the real loading time here.

![Loading screen, dev build 1437+](/img/remote/47427c58e2a34889.png)

::: tip Update 22.09.2026
In early firmware versions this moment showed just a blank screen, which confused many users. Starting with dev
build **1437** (and release **094**) the screen has a progress bar.
:::

Then the dictionary attack runs with the recovered keys.

![Dictionary attack](/img/remote/f77ef58bda94b088.png)

Again, for **static encrypted nonces (CUID dictionary)** leave the Flipper on the tag during the search and go make
some tea.

Once all keys are found you can update the saved partial dump to a full one, or save it under a new name.

![Fully read tag](/img/remote/9f9745d0d2ee0a4a.png)

Now all options are available: emulation, writing to blanks, sharing with a friend, etc.

::: warning Before writing to a blank
Know the difference between blanks and how readers can filter them: see [Magic cards](/nfc/magic-cards).
:::

## Optional: save the keys of a static-encrypted tag to the user dictionary

Because of how the attack works, keys recovered from the candidate dictionary are stored **only in that dictionary
and in the tag's dump**. That's a problem if you want to write a blank and wipe it later:
[NFC Magic](/nfc/nfc-magic) works only with the key cache and the user and system dictionaries.

So the team added automatic saving of keys, with a duplicate check, to the firmware. Open the saved dump's menu (at
least one key must be known) and choose **Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

The Flipper shows *"Saving keys to user dictionary"* and then *"New keys: N, Already known: M"*.

## Alternatives

There's also a [CLI project](https://github.com/phntm-lab/mfkey_desktop_cli) for the recovery. In some respects it is
faster, but CLI is for hardcore geeks. For everyday use the author prefers the convenient companion app, especially
given how many other useful features it has. On the Flipper alone, use the [MFKey app](/nfc/mfkey-app).

The process may look a little complicated at first, but after some practice it becomes routine.

## Related

[Nested attacks](/nfc/nested-fudan) · [MFKey32](/nfc/mfkey) · [MFKey app](/nfc/mfkey-app) ·
[MIFARE Classic](/nfc/mifare-classic) · [Magic cards](/nfc/magic-cards) · [qUnleashed app](/mobile/qunleashed-app)
