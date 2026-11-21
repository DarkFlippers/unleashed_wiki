---
title: NFC Magic 2.0
order: 55
author: gromovyna
original: [https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://t.me/gromovyna/31, https://docs.flipper.net/zero/nfc/magic-cards, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# NFC Magic 2.0: writing and wiping magic blanks

**NFC Magic** is the app for writing, cloning and wiping [magic blanks](/nfc/magic-cards) straight from the
Flipper. It started as an official Flipper Zero app; the version described here lives in the
[all-the-plugins](https://github.com/xMasterX/all-the-plugins) pack by **xMasterX** and is maintained by the
**Unleashed** team (they forked it and keep developing it). Version **2.0** was written by **@gromovyna**: the full
cycle from transport research to the last button in the UI.

Before 2.0 the app handled magic **MIFARE Classic** (Gen1a, Gen2) and the universal **Gen4** (UMC/GTU), a configurable
chip not tied to MFC. 2.0 adds **Ultralight/NTAG** magic blanks and honest results.

![New version, new icon](/img/remote/dafa43486592335f.png)

::: tip Where to get it
NFC Magic is **not part of the firmware binary**: it's an external app from the extra apps pack. 2.0 is available in
Unleashed **dev builds from 1307**. Update the app via the catalog, or update the firmware to a fresh dev build
(with the extra apps pack). Path on the device: `Main Menu → Apps → NFC → NFC Magic`.
:::

## Before you start

1. [Read](/nfc/read) the original card and **save** it. Make sure **all** sectors (MIFARE Classic) or pages
   (Ultralight/NTAG) were read: a partial dump gives a partial copy.
2. For MIFARE Classic blanks, NFC Magic authenticates with keys from the **key cache** and the **user and system
   dictionaries**, nothing else. If the keys of your card came from a CUID dictionary, first run
   **Save Keys to Dictionary** on the dump (see [MIFARE Classic](/nfc/mifare-classic#save-keys-to-dictionary)).

## Step 1. Detection

Everything starts when you put the blank on the Flipper (`Check Magic Tag`). The first big change: the app is no
longer fixated on MIFARE Classic. The scanner works **family-first**: it first figures out the family (**MFC** or
**Ultralight/NTAG**) and only then digs into the exact variant.

For **USCUID-UL** (magic blanks of the Ultralight family) the whole main zoo is recognised, plus a bit of local
Russian circus: **UL11**, **UL21** (including what's sold as **"Ultra"** in the ex-USSR market), **NTAG213/215/216**,
**UL-C**, **UL-5**, and tags already in **backdoor** mode (both wakeup sequences are checked).

![Detected USCUID-UL](/img/remote/557fa5d47ebeb0a6.png)

If you've got a preset the app doesn't know, it doesn't give up: it shows the **raw config**, so you can see and
analyse the raw configuration yourself. Handy for researchers.

![Raw config 1](/img/remote/7c3f38df0079d8fa.png)

![Raw config 2](/img/remote/c16eb844763ef4fa.png)

![Raw config 3](/img/remote/30f2a4b10d4be98a.png)

For a password-protected **Gen4** card: `Gen4 Actions → Auth with password`, enter the password, then check the tag.

## Step 2. Writing Ultralight / NTAG

Once the tag is recognised you can write and fully clone **UL/NTAG**. What you **don't** have to think about is the
transport: the app chooses it from the detection result.

- **Direct**: a normal ISO14443-3 write with command **`A2`**, for tags that accept writes head-on (e.g. factory
  **USCUID-UL** configurations, the same **UL21**, a.k.a. **"Ultra"**).
- **Backdoor**: if the chip has an exposed backdoor, the app uses it (raw wakeup plus backdoor commands). Simple
  logic: exposed backdoor → use it; none → write directly.

Your decisions:

- **Writing to a non-backdoored tag with a known password?** Supply it via **PWD-AUTH**: the app authenticates to
  the tag before writing or wiping.
- **The tag wasn't confirmed as magic but you know it is?** Press **Write anyway** and take responsibility.

The write process was made as un-scary as possible:

- **Live progress "Writing X/N"** on screen, so you're not staring at a frozen screen wondering whether anything is
  happening.

  ![Writing progress (fast: an NTAG216 was needed to catch the screenshot)](/img/remote/9914d55ba866082e.png)

- **Page order** is tuned per tag type (e.g. **UL-5**) and is **different for write and wipe** because of the lock
  bits. When writing, the service pages (including the UID) go **last**: write the lock/protection too early and the
  tag locks before the dump is complete. A wipe goes in ascending order, to remove the static lock first and only
  then clean the rest.
- Writing is **ACK-only with continue-on-error**: the app doesn't stop at the first failed page, it pushes through
  what it can.
- If something didn't make it, you get **Partial Write** with a **Details** list of exactly the pages that failed,
  not a cheerful "done". Pulled the tag off the antenna mid-way? Put it back and the write continues from the same
  place.

![Partial write](/img/remote/a50fa90dff60cdd8.png)

![Details](/img/remote/71b6fa77e1914b76.png)

And **Wipe** returns the tag to its factory state in one press.

## Step 3. Writing MIFARE Classic

1. In NFC Magic select **Check Magic Tag** and hold the blank to the back of the Flipper.
2. When the blank is recognised (Gen1a, Gen2, Gen4…), go to **More** for the options of this blank type.
3. **Write**: pick the original card in the file browser, hold the blank to the Flipper.
4. **Wipe** formats the blank: UID back to default, data in sectors/pages erased.

### Honest feedback: Success / Partial / Fail

This one is about good old **MIFARE Classic (Gen2)** and is just as important to the author as the new features.

Before, MFC wipe and clone **always** reported "Success". Always, even when not a single byte was written. That's not
just a bug, it's a lie: you walk away sure your copy works, and it doesn't.

Now operations are tracked **block by block** and you get an honest verdict: **Success / Partial / Fail**. On
**Partial** you see **Details**: which blocks weren't written or wiped. The read-only block 0 no longer fails the whole
sector 0 in the report (as in the original design), which is also handy when the tag is closed by **access bits**.

![Result](/img/remote/9e9d84e664f7da06.png)

![Details of a partial result](/img/remote/525faf18552333d1.png)

Things that make life calmer:

- On wipe, block 0 **keeps the real SAK/ATQA** of the tag. Classic case: **Perfect CUID** (answers RATS / has ATS). The
  firmware detected it as 4K and the wipe stamped block 0 as 4K. Fixed: a 1K stays 1K, and the UID is zeroed.
- No working key for the wipe? Instead of a doomed write attempt you immediately see **"No keys found"**.
- Every failure screen (Wipe / Write / Dump) has **Exit → menu**, so you don't feel trapped.
- A nasty bug is gone: keys from the previous tag **no longer carry over** to the next operation. The dictionary
  attack now re-reads the tag every time instead of reusing the last tag's keys (which could give a false sense of
  success and fake speed).

## Fool-proofing

Already in the previous release the app got protection around magic MFC tags and different **UID** lengths. 2.0
checks whether the dump can actually be written to the given **USCUID-UL** variant:

![Dump/blank compatibility check](/img/remote/a4dc82f2b66b73b5.png)

and, for the especially gifted, blocks attempts to pair **different families** (an MFC dump onto an Ultralight blank
and vice versa; such cases show up on forums and in chats regularly):

![Family mismatch](/img/remote/83e6e6cf1f0d9da6.png)

## It's less trivial than it looks

Behind the feature list are almost **3,000 lines** of changes: a USCUID-UL poller written from scratch, the Gen2 logic
rewritten and a pile of bugs fixed. All of it was **validated on real hardware** with a **QA matrix of nearly 100
cases**:

- **~15 test tags**: bought or crafted USCUID-UL variants (UL11, UL21 (NXP and Mikron "Ultra"), NTAG213/215/216,
  UL-C, UL-5, several UL-Y variants for edge cases), tags in backdoor mode (both wakeups), plus genuine non-magic and
  fully locked tags for honest Fails, and a heap of tags for regression;
- **categories**: detection (17 cases), direct/backdoor transport, data integrity and page order, UX scenarios,
  PWD-AUTH, wipe, a fat block for Gen2/MFC wipe (19 cases) and regression of all old protocols (Gen1a 4/7 bytes,
  Gen2, Gen4, plain MFC).

That run surfaced and killed many bugs: false "Success", dead buttons, a memory leak, a spinner that span forever on a
genuine Ultralight. Known limitations (including a 1K/4K detection nuance at the firmware level) are documented.

Next on the list: **UL-C** write support for USCUID-UL and possibly region-specific exotics.

## Troubleshooting

- **Tag not recognised**: it may not be a magic tag, or it's an unknown preset: check the raw config. For a Gen4 with
  a password, authenticate first.
- **"No keys found"** on an MFC wipe: the blank's current keys aren't in your dictionaries. Add them
  (`NFC → Extra Actions → MIFARE Classic Keys → Add`).
- **Partial write**: put the tag back and continue; check **Details**. Lock bits/access bits on the source dump can
  make some blocks/pages unwritable.
- **The reader rejects the copy**: the reader may filter your blank type. See [Magic cards](/nfc/magic-cards),
  [Iron Logic](/nfc/iron-logic), [Vizit filters](/nfc/vizit-filters).

## Related

[Magic cards](/nfc/magic-cards) · [MIFARE Classic](/nfc/mifare-classic) · [qUnleashed](/nfc/qunleashed) ·
[Unlocking cards](/nfc/unlock-with-password)
