---
title: Keyboard layouts
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Bad USB keyboard layouts

A USB keyboard doesn't send characters, it sends **key positions**. The computer turns them into characters
according to *its* keyboard layout. So to type `z` on a German (QWERTZ) PC, the Flipper has to press the key that
is `y` on a US keyboard. A **layout file** (`.kl`) tells Bad USB which key (and modifier) produces each character on
the target layout.

::: tip Unleashed
Keyboard layouts for Bad USB come from [rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)
and are part of Unleashed. The per-script `DUCKY_LANG` command is new in Unleashed (PR #1224).
:::

## Available layouts

Files in `/ext/badusb/assets/layouts/` (31 in the current build):

| File | Layout |
|---|---|
| `en-US.kl` | English (US), the **default** and the built-in fallback |
| `en-UK.kl` | English (UK) |
| `de-DE.kl`, `de-DE-mac.kl` | German (Germany), PC and Mac |
| `de-CH.kl` | German (Switzerland) |
| `fr-FR.kl`, `fr-FR-mac.kl` | French (France), PC and Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | French (Belgium, Canada, Switzerland) |
| `es-ES.kl`, `es-LA.kl` | Spanish (Spain, Latin America) |
| `it-IT.kl`, `it-IT-mac.kl` | Italian, PC and Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portuguese (Portugal, Brazil) |
| `nl-NL.kl` | Dutch |
| `da-DA.kl` | Danish |
| `nb-NO.kl` | Norwegian |
| `sv-SE.kl` | Swedish |
| `fi-FI.kl` | Finnish |
| `cz_CS.kl` | Czech |
| `sk-SK.kl` | Slovak |
| `hu-HU.kl` | Hungarian |
| `hr-HR.kl` | Croatian |
| `si-SI.kl` | Slovenian |
| `ba-BA.kl` | Bosnian |
| `tr-TR.kl` | Turkish |
| `ja-JP.kl` | Japanese |
| `dvorak.kl` | Dvorak (US) |
| `colemak.kl` | Colemak |

There is no Russian/Cyrillic layout: the format can only describe ASCII characters (see below).

## Choosing a layout

**Globally** (for all scripts): on the script screen press <kbd>←</kbd> **Config → Keyboard Layout (global)** and pick a
`.kl` file. The choice is saved in `/ext/badusb/.badusb.settings` and shown on the script screen in brackets, e.g.
`(de-DE)`. If the saved file is missing or broken, `en-US` is used.

![Bad USB Config menu, Keyboard Layout (global) is the first item](/screens/badusb/config.png)

**Per script**: put `DUCKY_LANG <name>` at the top of the script:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` is the file name without `.kl`. Aliases: `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- It applies from that line on and is reset to the global layout at the start of every run.
- An unknown or invalid name falls back to the built-in `en-US` without stopping the script.

## What a layout does NOT change

- Only `STRING` / `STRINGLN` text and single-character keys (`CTRL c`, `HOLD a`…) go through the layout. Named keys
  (`ENTER`, `F5`, arrows…) are the same everywhere.
- `ALTCHAR` / `ALTSTRING` don't use the layout at all; they type characters by their code via `ALT`+Numpad, which is
  why they work on any layout under Windows.
- The layout must match the **host's current input language**. On a PC with several languages (e.g. English and
  Russian) switch the host to the language of the layout before running, otherwise `STRING` types Cyrillic letters.

## File format (`.kl`)

A `.kl` file is a binary table of exactly **256 bytes**: 128 entries of 2 bytes (little-endian `uint16`), one for each
ASCII code 0-127.

- **Low byte**: the HID usage code of the key to press (e.g. `0x1F` = the `2` key).
- **High byte**: modifier bits to hold with it:

| Bit (high byte) | Modifier |
|---|---|
| `0x01` | Left Ctrl |
| `0x02` | Left Shift |
| `0x04` | Left Alt |
| `0x08` | Left GUI |
| `0x10` | Right Ctrl |
| `0x20` | Right Shift |
| `0x40` | Right Alt (AltGr) |
| `0x80` | Right GUI |

Example from `de-DE.kl`: the entry for `"` (ASCII 34) is `1F 02`, i.e. Shift + `2`, which is where the double quote
is on a German keyboard.

Because the table has only 128 entries, **only ASCII can be typed**; a `STRING` with any byte ≥ 128 (UTF-8 accents,
Cyrillic, emoji) stops the script with *"Native .kl supports ASCII, not UTF-8"*. File names may contain letters,
digits, `-` and `_` (max. 32 characters before `.kl`).

To make your own layout, follow the instructions in
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) and copy the resulting file to
`/ext/badusb/assets/layouts/`.

## Related pages

- [Script format](/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Using Bad USB](/badusb/usage)
- [Examples](/badusb/examples)
