---
title: Rasporedi tipkovnice
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Rasporedi tipkovnice za Bad USB

USB tipkovnica ne šalje znakove, nego **položaje tipki**. Računalo ih pretvara u znakove
prema *svojem* rasporedu tipkovnice. Tako, da bi upisao `z` na njemačkom (QWERTZ) računalu, Flipper mora pritisnuti tipku koja
je `y` na američkoj (US) tipkovnici. **Datoteka rasporeda** (`.kl`) govori Bad USB-u koja tipka (i modifikator) proizvodi pojedini znak na
ciljanom rasporedu.

::: tip Unleashed
Rasporedi tipkovnice za Bad USB potječu iz projekta [rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)
i dio su firmvera Unleashed. Naredba `DUCKY_LANG` po pojedinoj skripti novost je u Unleashedu (PR #1224).
:::

## Dostupni rasporedi

Datoteke u mapi `/ext/badusb/assets/layouts/` (31 u trenutačnoj verziji):

| Datoteka | Raspored |
|---|---|
| `en-US.kl` | Engleski (SAD), **zadani** i ugrađeni pričuvni raspored |
| `en-UK.kl` | Engleski (UK) |
| `de-DE.kl`, `de-DE-mac.kl` | Njemački (Njemačka), PC i Mac |
| `de-CH.kl` | Njemački (Švicarska) |
| `fr-FR.kl`, `fr-FR-mac.kl` | Francuski (Francuska), PC i Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | Francuski (Belgija, Kanada, Švicarska) |
| `es-ES.kl`, `es-LA.kl` | Španjolski (Španjolska, Latinska Amerika) |
| `it-IT.kl`, `it-IT-mac.kl` | Talijanski, PC i Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portugalski (Portugal, Brazil) |
| `nl-NL.kl` | Nizozemski |
| `da-DA.kl` | Danski |
| `nb-NO.kl` | Norveški |
| `sv-SE.kl` | Švedski |
| `fi-FI.kl` | Finski |
| `cz_CS.kl` | Češki |
| `sk-SK.kl` | Slovački |
| `hu-HU.kl` | Mađarski |
| `hr-HR.kl` | Hrvatski |
| `si-SI.kl` | Slovenski |
| `ba-BA.kl` | Bosanski |
| `tr-TR.kl` | Turski |
| `ja-JP.kl` | Japanski |
| `dvorak.kl` | Dvorak (SAD) |
| `colemak.kl` | Colemak |

Ne postoji ruski/ćirilični raspored: format može opisati samo ASCII znakove (pogledajte u nastavku).

## Odabir rasporeda

**Globalno** (za sve skripte): na zaslonu skripte pritisnite <kbd>←</kbd> **Config → Keyboard Layout (global)** i odaberite
`.kl` datoteku. Odabir se sprema u `/ext/badusb/.badusb.settings` i prikazuje se na zaslonu skripte u zagradama, npr.
`(de-DE)`. Ako spremljena datoteka nedostaje ili je oštećena, koristi se `en-US`.

![Izbornik Bad USB Config, Keyboard Layout (global) je prva stavka](/screens/badusb/config.png)

**Po skripti**: stavite `DUCKY_LANG <name>` na vrh skripte:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` je naziv datoteke bez nastavka `.kl`. Zamjenski nazivi (aliasi): `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Primjenjuje se od tog retka nadalje i vraća se na globalni raspored na početku svakog pokretanja.
- Nepoznat ili neispravan naziv vraća se na ugrađeni `en-US` bez zaustavljanja skripte.

## Što raspored NE mijenja

- Kroz raspored prolaze samo tekst naredbi `STRING` / `STRINGLN` i jednoznakovne tipke (`CTRL c`, `HOLD a`…). Imenovane tipke
  (`ENTER`, `F5`, strelice…) jednake su posvuda.
- `ALTCHAR` / `ALTSTRING` uopće ne koriste raspored; oni upisuju znakove prema njihovu kodu putem `ALT`+Numpad, zbog
  čega rade na bilo kojem rasporedu u sustavu Windows.
- Raspored mora odgovarati **trenutačnom jeziku unosa na računalu domaćinu**. Na računalu s više jezika (npr. engleski i
  ruski) prebacite računalo na jezik odabranog rasporeda prije pokretanja, inače će `STRING` upisivati ćirilična slova.

## Format datoteke (`.kl`)

Datoteka `.kl` binarna je tablica od točno **256 bajtova**: 128 unosa od po 2 bajta (little-endian `uint16`), po jedan za svaki
ASCII kôd od 0 do 127.

- **Niži bajt (low byte)**: HID usage kôd tipke koju treba pritisnuti (npr. `0x1F` = tipka `2`).
- **Viši bajt (high byte)**: bitovi modifikatora koje treba držati uz tipku:

| Bit (viši bajt) | Modifikator |
|---|---|
| `0x01` | Left Ctrl |
| `0x02` | Left Shift |
| `0x04` | Left Alt |
| `0x08` | Left GUI |
| `0x10` | Right Ctrl |
| `0x20` | Right Shift |
| `0x40` | Right Alt (AltGr) |
| `0x80` | Right GUI |

Primjer iz `de-DE.kl`: unos za `"` (ASCII 34) jest `1F 02`, odnosno Shift + `2`, gdje se na njemačkoj tipkovnici nalazi
dvostruki navodnik.

Budući da tablica ima samo 128 unosa, **mogu se upisivati samo ASCII znakovi**; `STRING` s bilo kojim bajtom ≥ 128 (UTF-8 dijakritički znakovi,
ćirilica, emojiji) zaustavlja skriptu uz poruku *"Native .kl supports ASCII, not UTF-8"*. Nazivi datoteka smiju sadržavati slova,
znamenke, `-` i `_` (najviše 32 znaka prije `.kl`).

Da biste izradili vlastiti raspored, slijedite upute u repozitoriju
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl) i kopirajte dobivenu datoteku u
`/ext/badusb/assets/layouts/`.

## Povezane stranice

- [Format skripti](/hr/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Korištenje Bad USB-a](/hr/badusb/usage)
- [Primjeri](/hr/badusb/examples)
