---
title: Vanjski CC1101 modul
order: 130
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/drivers/subghz/cc1101_ext, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://t.me/gromovyna/10, https://t.me/gromovyna/12, https://t.me/gromovyna/13]
sources: [unleashed-src, unleashed-readme, unleashed-docs, gromovyna]
---
# Vanjski CC1101 modul

Flipperov vlastiti Sub-GHz radio je čip CC1101 s malom unutarnjom antenom. U GPIO priključak možete spojiti drugu pločicu s čipom CC1101 i podesiti da Sub-GHz aplikacija (i Sub-GHz sistemske aplikacije) koristi nju umjesto unutarnjeg radija. Vanjske pločice obično imaju pravu SMA antenu, a često i pojačalo snage, pa imaju znatno veći domet i pri primanju i pri odašiljanju.

**Kada ga koristiti:** kada je daljinski upravljač ili prijamnik daleko, kada unutarnja antena ne hvata slab daljinski upravljač ili kada vam treba veći domet odašiljanja. Za pronalaženje frekvencije daljinskog upravljača i dalje koristite unutarnji radio (pogledajte [Analizator frekvencije](/hr/subghz/frequency-analyzer)).

::: tip Radi na svakom firmveru
Vanjski radiomoduli rade na svakom firmveru, uključujući tvornički. @quen0n je napisao prvu implementaciju, za Unleashed ([PR 307](https://github.com/DarkFlippers/unleashed-firmware/pull/307), [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101)); implementaciju koja se danas koristi napisao je **Skorp** u službenom firmveru, a Unleashed koristi nju.
:::

## Ožičenje

Modul komunicira putem Flipperove vanjske SPI sabirnice. Standardno ožičenje glasi:

| Pin modula CC1101 | Flipper GPIO | Pin priključka |
|---|---|---|
| GDO0 | PB2 | 6 |
| CSN | PA4 | 4 |
| SCK | PB3 | 5 |
| MOSI | PA7 | 2 |
| MISO (GDO1) | PA6 | 3 |
| VCC | 3.3V | 9 |
| GND | GND | 11 ili 18 |
| Upravljanje pojačalom / LED diodama (moduli E07) | PC3 | 7 |

Za gotove pločice, sheme i fotografije pogledajte quen0nov vodič: [flipperzero-ext-cc1101](https://github.com/quen0n/flipperzero-ext-cc1101) (povezan iz Unleashed FAQ-a). Numeriranje pinova nalazi se na stranici [GPIO raspored pinova](/hr/gpio/pinout); ostale dodatne pločice opisane su na stranici [Vanjski moduli](/hr/gpio/external-modules).

::: warning
Napajajte modul isključivo s **3.3 V**. CC1101 nije čip za 5 V.
:::

## Prebacivanje na vanjski modul

1. Spojite modul dok je Flipper isključen ili barem dok nije pokrenuta nijedna Sub-GHz aplikacija.
2. Otvorite `Main Menu → Sub-GHz → Radio Settings`.
3. Na retku **Module** pritisnite <kbd>→</kbd> za promjenu iz `Internal` u `External`.
4. Pritisnite <kbd>←</kbd> (Natrag) i koristite `Read`, `Read RAW`, `Saved` itd. kao i obično.

Što možete očekivati:

- Redak **Module** nudi `External` samo kada je modul doista otkriven. Ako ništa nije spojeno, redak ima samo jednu vrijednost, `Internal`.
- Firmver ispituje modul prilikom odabira. Ako ispitivanje ne uspije, vraća se na unutarnji radio i redak ponovno prikazuje `Internal` — tako je ono što vidite uvijek ono što se stvarno koristi.
- Na zaslonu odašiljanja spremljenog signala donji redak prikazuje `R: Int` ili `R: Ext` — radio koji će odašiljati.
- Sub-GHz sistemske aplikacije ([Nice O-Code](/hr/subghz/nice-o-code), [Seed Capturer](/hr/subghz/seed-capturer), [Security+ PIN](/hr/subghz/secplus-pin)) prikazuju `Int` ili `Ext` u zaglavlju i automatski koriste vanjski modul kada je spojen.

## Ostale postavke u Radio Settings

`Sub-GHz → Radio Settings` sadrži:

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| Module | `Internal` / `External` | radio koji koristi Sub-GHz aplikacija |
| TX Power | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | nadjačava snagu odašiljanja unaprijed zadane postavke; `Preset` zadržava snagu iz postavke modulacije |
| Protocol Names | `OFF` / `ON` | pogledajte [Postavke](/hr/subghz/settings) |
| Counter Incr. | `+1`… | pogledajte [Postavke](/hr/subghz/settings) |
| Ext Amp & LEDs | `OFF` / `ON` | **samo u načinu Debug** — upravlja pinom pojačala / LED dioda (PC3, pin priključka 7) modula tipa E07 |
| Debug Pin | `OFF` / `17(1W)` | **samo u načinu Debug** — zrcali signal na pin 17 za razvoj protokola |

`Ext Amp & LEDs` je **zadano ON**. Kada je uključeno, firmver aktivira pojačalo modula na PC3 samo dok čip stvarno odašilje. Isključite ga samo ako vaš modul koristi pin 7 za nešto drugo; ova stavka izbornika pojavljuje se kada je način Debug uključen u `Settings → System`.

## Modul velike snage od 1 W (u testiranju)

Početkom 2025. @gromovyna je podijelio svoja testiranja novog, znatno snažnijeg Sub-GHz modula koji je izradio quen0n (član tima Unleashed):

- U trenutku objava to je bio jedini takav primjerak, sa snagom odašiljača **do 1 W**.
- Izgrađen je na drugom čipu umjesto CC1101 — nitko prije toga nije napravio modul na tom čipu.
- Podrška u firmveru još **nije bila dovršena**; razvijala se za Unleashed u suradnji s Flipper Marketom, a gromovyna je sudjelovao kao tester.

![Modul velike snage pokraj pločice CC1101](/img/remote/29279ff04df77e30.jpg)

Njegovi empirijski rezultati (bez mjerenja snage):

- Modul je daleko snažniji od svega što je vidio na temelju čipa CC1101.
- U gradu, odašiljući iz stana s drugom zgradom na putu, poslao je signal **Hollarm** na udaljenost od **600 m** vodoravno.
- Ista udaljenost postignuta je i s priloženom antenom i s antenom za walkie-talkie koju su preporučili MMX i quen0n — iako s antenom za walkie-talkie sklop „uopće nije prenosiv”.
- Bilo kakva prednost pri *primanju* u usporedbi s CC1101 još nije bila jasna.

![Modul s antenom za walkie-talkie](/img/remote/0998ad639bb38e82.jpg)

Ovdje je opisan uređaj u fazi testiranja; provjerite aktualne bilješke o izdanju firmvera Unleashed za status njegove podrške.

::: warning
Odašiljite samo na frekvencijama i snagama koje su zakonite u vašoj državi i samo prema vlastitoj opremi.
:::

## Rješavanje problema

- **Ne može se odabrati `External`** — modul nije otkriven: provjerite 3.3 V, GND i četiri SPI linije (CSN, SCK, MOSI, MISO). Pogrešno spojena žica CSN ili MISO najčešća je pogreška.
- **Sam se vraća na `Internal`** — ispitivanje nije uspjelo prilikom odabira modula; ponovno dobro umetnite modul i pokušajte ponovno.
- **Prima signale, ali je domet pri slanju slab** — na modulima E07 pojačalo zahtijeva spojen pin 7 (PC3) i uključeno `Ext Amp & LEDs` (`ON`).
- **Analizator frekvencije prikazuje nasumična očitanja** — vanjski je modul mnogo osjetljiviji na šum; za analizu frekvencije koristite unutarnji radio.
- **Odašiljanje je blokirano** — frekvencija je izvan raspona čipa CC1101; pogledajte [Frekvencije](/hr/subghz/frequencies).

## Povezane stranice

- [Postavke Sub-GHz](/hr/subghz/settings)
- [Frekvencije](/hr/subghz/frequencies)
- [GPIO raspored pinova](/hr/gpio/pinout) · [Vanjski moduli](/hr/gpio/external-modules)
