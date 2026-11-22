---
title: Daljinski upravljač za rampu ZKTeco CMP200
order: 210
author: gromovyna
original: [https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09, https://t.me/gromovyna/28, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md]
sources: [gromovyna, unleashed-src, unleashed-docs]
---
# ZKTeco CMP200 — Princeton u kineskom ruhu

*Kratak osvrt autora @gromovyna o daljinskom upravljaču za rampe ZKTeco te kako s njim raditi na Unleashed firmveru.*

![Daljinski upravljač ZKTeco CMP200](/img/remote/a2cb668ab24d6625.png)

## Uvod

Prije nekog vremena u blizini autorova doma otvorena je privatna klinika i postavila podiznu rampu **ZKTeco**. Bio je znatiželjan, ali bilo je malo prometa i nije bilo posebnog razloga za istraživanje, pa je to ostalo na čekanju u glavi.

![Rampa ZKTeco (fotografija s interneta)](/img/remote/4cfaf6cbf4b21db6.png)

Zatim je, izlazeći s pregleda, s gornjeg kata vidio privjesak kako leži na recepciji, fotografirao ga, prepoznao model pomoću Google Lensa i stavio ga na svoj popis "za kupnju". Prije kupnje pitao je MMX-a (xMasterX) — i pokazalo se da je misterij već riješen.

## Kako su Kinezi zapakirali Princeton

Sve je prilično prozaično, a u **Unleashed** firmveru (zahvaljujući MMX-u) podržano je već više od godinu dana. Ispod haube to je običan **Princeton** s 8-bitnim kodom tipke — a kodovi tipki su dobro poznati i **isti za svaki daljinski upravljač**:

| Parametar | Vrijednost |
|---|---|
| Frekvencija | **430,50 MHz** |
| Modulacija | **AM650** |
| Tipka UP | `0x30` |
| Tipka STOP | `0x03` |
| Tipka DOWN | `0x0C` |

Najbolje od svega, u Unleashdu su ti kodovi tipki **već mapirani na tipke sa strelicama**, pa jedan spremljeni signal funkcionira kao cijeli daljinski upravljač.

::: tip Unleashed
ZKTeco se na popisu podržanih sustava u Unleashdu pojavljuje kao `ZKTeco 430.5MHz AM650 (24 bits, Static - Princeton based)` i ima vlastiti unos u `Add Manually`. 430.50 MHz nalazi se na zadanom popisu frekvencija.
:::

## Kako ga koristiti s Flipperom

Budući da je kôd statički, kopija je identična originalu — oba nastavljaju raditi bilo kojim redoslijedom.

### 1. opcija — pročitajte svoj daljinski upravljač

1. `Main Menu → Sub-GHz → Read`.
2. <kbd>←</kbd> `Config` → **Frequency** `430.50`, **Modulation** `AM650`. Natrag.
3. Pritisnite tipku na CMP200 u blizini Flippera. Pojavljuje se signal `Princeton`.
4. <kbd>OK</kbd> → `Save`, imenujte datoteku.
5. Otvorite je u `Sub-GHz → Saved` → `Emulate`. <kbd>OK</kbd> šalje snimljenu tipku; tipke sa strelicama šalju ostale tipke (UP / STOP / DOWN).

### 2. opcija — izradite daljinski upravljač

1. `Main Menu → Sub-GHz → Add Manually → ZKTeco`.
2. Odaberite pojas `430.50 AM650` (naveden je prvi za ovaj unos).
3. Imenujte i spremite. Flipper stvara 24-bitni Princeton ključ s nasumičnim kodom, TE 357 µs, tipkom `0x30` (UP).

Daljinski upravljač stvoren na ovaj način ima vlastiti kôd — rampa će reagirati tek nakon što se registrira u prijemniku rampe (slijedite priručnik rampe). Da bi radio kao postojeći daljinski upravljač, umjesto toga ga pročitajte (1. opcija).

::: warning
Samo za rampe koje posjedujete ili kojima upravljate.
:::

## Je li to sve?

Za sada — da. Kako napominje gromovyna, ova je podrška stigla tiho pa je većina zajednice nije ni primijetila; on ju je testirao i podijelio rezultate.

## Rješavanje problema

- **Ništa se ne prima** — provjerite je li frekvencija 430.50, a ne 433.92; provjerite pomoću [Analizatora frekvencija](/hr/subghz/frequency-analyzer).
- **`Ignore Princeton` je uključen (ON)** u Read `Config` — daljinski upravljači temeljeni na Princetonu poput ovog tada su skriveni; isključite tu opciju.
- **Strelice ne šalju ništa** — otvorite signal iz `Saved → Emulate`; prilagođene tipke rade na zaslonu za odašiljanje.

## Povezane stranice

- [Read](/hr/subghz/read) · [Ručno dodavanje](/hr/subghz/add-manually) · [Podržani sustavi](/hr/subghz/supported-systems)
- [Plivajući kodovi](/hr/subghz/rolling-codes) — objašnjenje prilagođenih tipki
