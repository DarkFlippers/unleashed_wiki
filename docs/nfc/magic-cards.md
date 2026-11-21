---
title: MIFARE Classic magic cards
order: 50
author: gromovyna
original: [https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://t.me/gromovyna/6, https://docs.flipper.net/zero/nfc/magic-cards]
sources: [gromovyna, flipper-docs]
---
# MIFARE Classic magic cards (blanks)

On a MIFARE Classic tag **block 0**, which holds the UID and manufacturer data, can't be rewritten. To make a full copy
of such a tag, special **blanks** ("magic cards", "UID-rewritable cards") were invented, where block 0 can be written
many times or once.

This page, based on the article by **@gromovyna**, explains briefly what's what: Gen1 to Gen4, international names,
the local (ex-USSR) market names, and which behaviour matters for which reader. It mentions tags that are available
without "dancing with a tambourine" towards China and that the author has checked or seen himself. To write them with
the Flipper see [NFC Magic 2.0](/nfc/nfc-magic).

> Below, "tag", "chip", "card" and "fob" are synonyms: what matters is the chip inside and how it behaves, not the
> form factor.

Further reading:

- the excellent [magic cards notes](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md)
  in the Proxmark3 docs (English), kept up to date by researchers, covers other protocols too and gives technical
  details and commands. With experience and a Proxmark3 you can save money by buying the cheapest blanks on a given
  chip and reconfiguring them (for some chips);
- the author's [Google Sheets table](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing)
  with the tags below, their generation, names and whether Flipper Zero can write them.

## Generations

![Magic tag generations](/img/remote/f659ade923b6ca4f.png)

The split into generations ("Gen") is not formal: it's an attempt to classify chips by behaviour. Four generations
have stuck. A chip can belong to several at once (e.g. **M1-4K**). The author follows the standard classification used
by Proxmark3, though he doesn't fully agree with it for some chips.

| Gen | Nickname | How block 0 is written | Notes |
|---|---|---|---|
| **Gen1** | Backdoor | special backdoor commands | The oldest. Backdoor commands always allow writing, reading (and wiping, for Gen1a) the tag. Because a filter against them is trivial, **every self-respecting system filters them**. |
| **Gen2** | Direct Write | block 0 is written like any other block | Can be written by NFC phones (mostly Android) with the right software. |
| **Gen3** | APDU | a special APDU command | Some allow changing the UID separately from block 0. A rare beast. |
| **Gen4** | Configurable | config block | Has configuration and memory, can be set up as different MFC formats (and more). The most flexible; can mimic Gen1/Gen2 behaviour. |

## Gen1 (backdoor)

### Gen1a

Need the backdoor commands `40` (7-bit) and `43` to write.

**UID** (RU name: *Zero*). Internationally exists with a 4-byte ID; iKey LLC presumably made a 7-byte variant too
(awaiting confirmation that it's the same chip). Also supports backdoor read (no keys needed) and wipe.

**OTP 2.0** (RU; also sold as **MF** for the Ukrainian market). According to iKey LLC, their own design. **One time
programmable**: after the first write (via the backdoor) the chip locks and behaves like a genuine MFC. Has a **hard
PRNG**.

::: tip Author's note
The tag doesn't fully match a genuine MFC and behaves differently under stress, which let Iron Logic build a filter
against it. How that filter works was unknown to the author at the time of writing.
:::

**MF-4** (RU). An improved OTP 2.0. Also **one time programmable** after the first backdoor write, **hard PRNG**.
According to the description it can:

- switch UID length 4 / 7 bytes;
- set arbitrary ATQA/SAK and ATS;
- support the PPS command (which, as far as the author knows, isn't part of the MFC protocol at all).

### Gen1b

Like Gen1, but works right after command `40` (7-bit). The author hasn't personally seen Gen1b UID chips for MFC 1K.

**M1-4K**: a chip for copying **MIFARE Classic 4K**. Behaves as **Gen1b and Gen2 CUID** at the same time. Has a
**static nonce `f17e64cd`**.

## Gen2 (direct write)

Block 0 can be written directly. They can be written from Android with the *Mifare Classic Tool* app.

### CUID

RU names: **MF-3**, **MF3-2**, **MF-8**.

The main, universal (for most cases) and widespread chip. It bypasses simple Gen1 filters, is rewritable many times
and can be written from a phone: that's what made it a crowd favourite.

::: tip Author's note
In the ex-USSR the interest in this chip, and the details of its behaviour, matter for **Iron Logic** readers, which
have filters against blanks. Those readers are cheap and therefore everywhere. See [Iron Logic readers](/nfc/iron-logic).
:::

Many chips are sold as "CUID", and they can differ in edge-case behaviour. The newest are **CUID with static nonce
(MF-3.2)**: at the time of writing they bypass all known ex-USSR filters (including Iron Logic "4 stripes").

Local names:

- **MF-3**: CUID that bypasses Iron Logic "3 stripes" filters.
- **MF-8**: CUID that does **not** bypass Iron Logic OTP 1.0 filters (a "defective batch" whose number, eight, came
  from a simple modification of the three).
- **MF-3.2**: CUID with static nonce, bypasses all Iron Logic filters against MFC.

China also has a **"Perfect CUID"** that answers the RATS command (the author found no practical use for that).

## Gen3 (APDU)

Tags driven by APDU commands. Currently the least researched category. Potentially configurable by type, but that
hasn't been proven. No RU name.

Sold for different MFC variants, in various combinations:

- by memory: **MFC 1K**, **MFC 4K**, **MIFARE Mini**;
- by ID length: **4 bytes**, **7 bytes**.

The author owns MFC 1K 7b, MFC 4K 4b, MFC 4K 7b, MF Mini (S20) 4b and MF Mini (S20) 7b variants (MFC 1K 4b most likely
exists too) and used them a couple of times to test hypotheses with 7-byte IDs, before discovering how configurable
USCUID chips are. That variety (and experience with other tags) made him think these chips *may* be configurable by
type, UID length and memory size.

## Gen4 (configurable)

The most advanced chips: a configuration block controls the tag and its behaviour.

### USCUID (GDM in Proxmark3 commands)

A cheap chip with MFC 1K memory plus hidden blocks used by some configurations. Depending on the config it
supports three kinds of backdoor commands and Direct Write. Can carry 4-byte or 7-byte IDs, can return an MFC EV1
signature, has a shadow mode and many other useful features.

Backdoor variants:

- **Gen1a** (`40`/`43`) magic wakeup;
- **GDM** (`20`/`23`) magic wakeup: exactly like Gen1, but other commands. No readers with filters against this
  backdoor have been seen so far (unlike Gen1a);
- **Magic Authentication** (select tag, `8000` + CRC, Crypto-1 auth with key `000000000000`).

Knowing the configuration principles you can fine-tune the chip for specific needs. With Gen1a/GDM backdoors enabled
and Gen1-style commands, writing or wiping has been seen to be unreliable. Proxmark3 users should read the chip's
documentation linked above: compared to the Ultimate Magic Card it costs little and gives plenty.

Market configurations of USCUID:

| Name | RU name | Behaviour |
|---|---|---|
| **FUID** | *OTP* | **One time programmable**: Direct Write of block 0, then the block locks. Was marketed in the ex-USSR as iKey LLC's "OTP" but turned out to be a Chinese chip. In the default config it has a **GDM** backdoor, so the ID can be changed more than once and data read without keys. In early November 2024 researchers reported versions with a **locked** backdoor on the Chinese market, which removes reuse. |
| **UFUID** | — | Sold by the Chinese as a "sealable UID". Stock config has a **Gen1a** backdoor, rewritable many times. "Sealing": Chinese duplicators (CopyKey etc.) check the config block after writing and then send a command that changes it and disables the backdoor, turning the tag into a plain MFC. A cut-down USCUID: accepts only part of the config. |
| **ZUID** | — | A UID tag on a cut-down USCUID. Given chip prices, the point of this variant is unclear. Accepts only part of the config. |
| **GDM (GDMIC)** | — | Gave USCUID one of its first names. Key feature: **shadow mode**: in the field all changes go to temporary memory that is lost when the field disappears; next time data comes from permanent memory. The Chinese advertise it for "rides left" cards (e.g. lifts). It does **not** help against readers using dynamic data (e.g. Eltis intercoms with their fobs). |
| **GDCUID** | — | CUID implemented on USCUID. Not sold separately but may turn up when buying CUID. |
| **M1-7B** | — | For writing MIFARE Classic 1K with a **7-byte** ID. Has a **GDM** backdoor. In 7-byte mode it reads the ID from a **hidden block**: just writing a dump into main memory can "brick" the tag (recoverable). |

The names **ZUID** and **GDCUID** were proposed by the author himself while writing the Proxmark3 magic chip
documentation.

### Ultimate Magic Card (GTU)

The most expensive chip at the moment: large memory and configs let it act not only as different MIFARE Classic /
Mini formats, but also as MIFARE Ultralight, NTAG and others (though its Ultralight implementation is rather limited).
The config allows:

- changing **ATQA/SAK** and **ATS**;
- **ID** length of 4, 7 or 10 bytes;
- **shadow mode** and its settings;
- enabling/disabling **Direct Write** of block 0;
- changing the **backdoor password** (used by all commands);
- setting **Version** and **Signature**;
- switching to **Ultralight mode** and configuring it.

Before CUID with static nonce appeared, the UMC was the only blank that bypassed Iron Logic "4 stripes" filters.

## Summary table

![Comparison table](/img/remote/a29bf09269c612bb.jpg)

The full, maintained version is in the author's
[Google Sheets table](https://docs.google.com/spreadsheets/d/1qv4-UXguySLHLRM_Q-cE4B8yLJimWJAAm9hp2_zUCKg/edit?usp=sharing).

If you're afraid of buying the wrong chip in China, the author recommends the shop
[FlipperMarket](https://flipper.market/catalog#services-3), where the main tags needed in the CIS (and writable by the
Flipper) are picked and sold by an experienced seller.

## What the Flipper can write

According to the official docs, Flipper Zero (via the **NFC Magic** app) writes **Gen1**, **Gen2** and **Gen4** magic
cards, plus **regular MIFARE Classic** cards (without changing the UID):

| Blank | Can be configured as |
|---|---|
| Gen1 | MIFARE Classic 1K |
| Gen2 | MIFARE Classic 1K, MIFARE Classic 4K (a compatible Gen2 card is required) |
| Gen4 (Ultimate) | any MIFARE Classic, MIFARE Ultralight EV1/EV2, NTAG203, NTAG213, NTAG215, NTAG216 |

::: tip Unleashed
The Unleashed build of **NFC Magic 2.0** additionally detects and writes **USCUID-UL** Ultralight/NTAG blanks
(UL11, UL21 / "Ultra", NTAG213/215/216, UL-C, UL-5) and reports honest *Success / Partial / Fail* results.
See [NFC Magic 2.0](/nfc/nfc-magic).
:::

### Cloning a card in short

1. [Read](/nfc/read) and save the original. Make sure **all** sectors/pages were read (recover keys with
   [MFKey32](/nfc/mfkey), [nested attacks](/nfc/nested-fudan) or [qUnleashed](/nfc/qunleashed) if needed).
2. Pick a blank that the target reader accepts (see above: Gen1 is filtered almost everywhere).
3. Write it with [NFC Magic](/nfc/nfc-magic).

::: tip Legal
Copy only your own credentials or with explicit permission.
:::

## Related

[NFC Magic 2.0](/nfc/nfc-magic) · [MIFARE Classic](/nfc/mifare-classic) · [Iron Logic readers](/nfc/iron-logic) ·
[Vizit reader filters](/nfc/vizit-filters)
