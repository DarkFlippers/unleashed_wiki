---
title: Nested attacks and Fudan backdoors
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Nested attacks and Fudan backdoors

A practical "what to press" guide by **@gromovyna** to the card-only attacks on MIFARE Classic that are built into
`NFC → Read`. They arrived in official firmware **1.1.2** (work by [@noproto](https://github.com/noproto)) and are
part of Unleashed. While they were being developed, a community researcher made two important discoveries: an
attack on **static encrypted nonces**, and **backdoor keys** in chips made by **Fudan** (and others) that let you
read the sectors of a MIFARE Classic tag without knowing its keys. Both made it into the firmware and into
**MFKey 3** (now [MFKey 4.1](/nfc/mfkey-app)). The research paper: [eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Faster way (update, September 2026)
If you just want to recover MIFARE Classic keys quickly, use the companion app **qUnleashed**, which runs all these
attacks, including HardNested, on your phone or PC: see [Fast key recovery with qUnleashed](/nfc/qunleashed).
:::

## The idea in short

**Nested attacks** are *card-only* attacks (no reader needed): knowing at least one key of a card, they recover the
unknown ones. Conceptually, tags fall into four groups (strictly speaking there is Nested and HardNested, but this
split is easier to understand):

| Tag is vulnerable to | Nonce type | Where the key is computed |
|---|---|---|
| **Nested** | weak PRNG | MFKey on the Flipper, qUnleashed |
| **HardNested** | hard PRNG | qUnleashed or a PC (not on the Flipper) |
| **Static Nested** | static nonce | MFKey on the Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | static encrypted nonce | MFKey on the Flipper (slowest), qUnleashed |

**Backdoor keys** are keys that open a tag's data **without** its real keys.

For the examples the author used tags of each type, with sector 0 encrypted by a generated key pair:
Key A `A3F92C8E7D3A`, Key B `4F6D91C5BA7E` (access bits left default). On a Proxmark3 the default-key check showed
those keys as unknown:

![Default key check on Proxmark3](/img/remote/86130b06142278a1.png)

## Step 1. Read the tag

Go to `Main Menu → NFC → Read` and hold the tag still.

### 1.1 The tag has a backdoor

You'll see screens with **Backdoor Read** and then a few more with **(Backdoor)** in the header:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Reading through the backdoor](/img/remote/e9be977d84486794.png)

This means the chip has a backdoor: Flipper reads the sector data through it and collects nonces so the keys can be
recovered. The typical result is **all sectors read, but fewer keys than needed**:

![All sectors, but only 30 keys](/img/remote/9e7db33e51594779.png)

### 1.2 The tag has no backdoor

Then the classic key search runs: first the **user** dictionary, then the **system** dictionary.

![User dictionary](/img/remote/fff8f5662df941b9.png)

![System dictionary](/img/remote/0da64f609fc2c770.png)

If at least one key was found, Flipper switches to **PRNG Analysis**, then goes through the **Nested Dictionary**:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

then **Calibration** and **Nonce Collection**:

![Calibration and nonce collection](/img/remote/f5b036a96f5a0869.png)

If the tag is vulnerable **only to HardNested**, nonce collection takes longer and the header gets a **(Hard)**
suffix:

![Nonce collection for a hard PRNG tag](/img/remote/fca9f1b2e4475631.png)

> In that case go straight to [step 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Here the result looks more familiar: the number of keys found is close to the number of sectors read (depending on
the access bits).

![Result after the nested phase](/img/remote/d15656101dfafcc4.png)

All collected nonces are appended to `/ext/nfc/.nested.log`.

## Step 2. Recover the keys

Go to `Main Menu → Apps → NFC → MFKey`.

::: warning Check the app version
Make sure the MFKey app is the one that matches your firmware and hasn't been overwritten by an old copy if you
installed apps separately. Unleashed ships **MFKey 4.1**.
:::

![MFKey start screen](/img/remote/195a1b6a411e7bf3.png)

Press <kbd>OK</kbd> **Start** and…

### 2.1 The tag is vulnerable to Nested, Static Nested or Static Encrypted Nested

The cracking process starts. You can leave the Flipper alone and do something else:

![Cracking in progress](/img/remote/a514db67a986ae2c.png)

All that's left is to wait. On the Flipper's hardware this is not fast (hello, SPI) and depends on:

- the attack type: Nested < Static Nested < Static Encrypted Nested (SEN is the slowest);
- the number of unknown keys (fewer is faster);
- how unique the keys are: a key reused everywhere is found faster than a partly diversified tag (e.g. Iron Logic),
  which in turn is faster than a fully diversified tag (e.g. Bambu Lab filament spools).

The UI is not always responsive and sometimes "thinks". Occasionally the Flipper may look frozen; don't rush to
reboot it. The **RAM** line at the top keeps changing while the work goes on.

::: warning Static encrypted nonces
With static encrypted nonces, because of how the attack works, the nonces are not marked as "solved"; MFKey only
builds **candidates** (keys that must be checked on the tag later), and the app may look stuck at the last (or an
earlier) step. If enough time has passed, exit and check the result (step 3). Since MFKey 4.x the candidates are
saved to a per-card **CUID dictionary** `/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, which `Read` tries first.
:::

When decryption is finished, you get a summary with the number of keys added to the user dictionary
(**Keys added to user dict: N**, and for SEN tags **SEN key candidates: N**):

![MFKey complete](/img/remote/c9ef77139b74cc89.png)

Continue with step 3.

### 2.2 The tag is vulnerable to HardNested

You could tell from the **(Hard)** screen during nonce collection, or MFKey will show an error that no nonces were
found:

![MFKey: no nonces found](/img/remote/2519c7dce0b881c9.png)

HardNested is the one attack that can't be run on the Flipper. Options:

- **qUnleashed** (recommended, phone or PC): `Tools → Recover MIFARE Keys`, see [qUnleashed](/nfc/qunleashed).
  Keys go straight to the user dictionary.
- **A PC with HardnestedRecovery**, as in the original guide:
  1. Copy `/ext/nfc/.nested.log` from the Flipper's SD card to the computer.
  2. Clone and build [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery) with
     `make build` (on Windows use WSL or Docker).
  3. Run it with the log as the argument:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. The key appears in the output:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Add the keys by hand
Unlike 2.1, keys found by HardnestedRecovery on a PC are **not** added automatically. Add them to the user dictionary
yourself: `NFC → Extra Actions → MIFARE Classic Keys → Add`, or append them to
`/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Step 3. Read the tag again

Once the keys are recovered, read the tag again via `NFC → Read`.

::: tip Pro tip
If you saved the tag after the first read, you can unlock it right from the saved card's menu:
`Saved → <card> → Unlock with Dictionary`.
:::

![Unlock with Dictionary from a saved card](/img/remote/8232d690446c70b6.png)

::: tip Pro tip
For better performance next time, clean up `/ext/nfc/.nested.log` after you've cracked the keys of a tag.
:::

## Related

[MIFARE Classic](/nfc/mifare-classic) · [MFKey app](/nfc/mfkey-app) · [qUnleashed](/nfc/qunleashed) ·
[MFKey32](/nfc/mfkey) · [Iron Logic readers](/nfc/iron-logic) · more articles in the author's channel
[@gromovyna](https://t.me/gromovyna)
