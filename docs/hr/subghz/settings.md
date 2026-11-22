---
title: Postavke radija
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Postavke radija (Radio Settings)

`Main Menu → Sub-GHz → Radio Settings` sadrži postavke koje se primjenjuju na cijelu aplikaciju Sub-GHz: koji se radio koristi, snaga odašiljanja, imenovanje datoteka i ponašanje promjenjivog brojača. Postavke za primanje (frekvencija, modulacija, skakanje frekvencija, filtri) nalaze se u `Read → Config` — pogledajte [Čitanje signala](/hr/subghz/read#config).

::: tip Unleashed
U tvorničkom firmveru ovaj izbornik samo prebacuje između unutarnjeg i vanjskog modula. Unleashed dodaje **TX Power**,
**Protocol Names**, **Counter Incr.**, a u načinu Debug **Ext Amp & LEDs** i **Debug Pin**.
:::

## Stavke izbornika

![Radio Settings: Module, TX Power, Protocol Names i Counter Incr.](/screens/subghz/radio_settings.png)

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| `Module` | `Internal`, `External` | Radio koji se koristi za primanje i odašiljanje. `External` se nudi samo kada je vanjski CC1101 otkriven na GPIO-u; ako ne odgovori, Flipper se vraća na `Internal` |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Snaga odašiljanja. `Preset` = vrijednost koju definira unaprijed zadana postavka modulacije (zadano). Niže vrijednosti korisne su za testiranja na kratkom dometu |
| `Protocol Names` | `OFF` / `ON` | Kada je `ON`, automatski generirani nazivi datoteka sadrže naziv protokola + vremensku oznaku umjesto samo vremenske oznake/nasumičnog naziva |
| `Counter Incr.` | `+1`, `+2`, `+3` (uobičajeno) | Za koliko se povećava promjenjivi brojač po odašiljanju za dinamičke protokole. Zadano `+1` |

Dodatne stavke u **načinu Debug** (`Settings → System → Debug → ON`):

| Stavka | Vrijednosti | Što radi |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Cjeloviti popis koraka brojača za eksperimente: veliki skokovi, `OVFL` (korak 65535), `OFEX` (poseban način), `No` (brojač se ne mijenja) i negativni koraci |
| `Ext Amp & LEDs` | `ON` / `OFF` | Upravlja pinom pojačala / LED dioda vanjskih modula (GPIO PC3, kao na modulima E07). Zadano `ON`. Isključite ako vaš modul koristi taj pin za nešto drugo |
| `Debug Pin` | `OFF` / `17(1W)` | Zrcali podatkovni signal radija na GPIO pin 17 (1-Wire) — za razvoj protokola pomoću logičkog analizatora |

`TX Power`, `Protocol Names` i `Ext Amp & LEDs` spremaju se odmah (u `/ext/subghz/assets/last_subghz.settings`).
`Counter Incr.` se ne sprema: ostaje aktivan do ponovnog pokretanja Flippera, a zatim se vraća na `+1`.

::: warning Povećanje brojača
Veliki ili negativni koraci brojača služe za eksperimente **na vlastitim prijamnicima**. Pomicanje brojača daleko unaprijed
trajno pomiče pohranjeni brojač prijamnika ispred vašeg izvornog daljinskog upravljača; vraćanje unatrag uzrokuje da vas prijamnik ignorira.
Za suživot s izvornim daljinskim upravljačem koristite [Načine rada brojača](/hr/subghz/counter-mode) ili izradite novi daljinski upravljač pomoću
[Ručnog dodavanja](/hr/subghz/add-manually). Pozadina: [Promjenjivi kodovi](/hr/subghz/rolling-codes).
:::

## Ostale postavke koje se nalaze na SD kartici

| Datoteka | Svrha | Pojedinosti |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Dodatne frekvencije, popis za hopper, zadana frekvencija, prilagođene postavke modulacije | [Frekvencije](/hr/subghz/frequencies#adding-frequencies), [Formati datoteka](/hr/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Prošireni frekvencijski raspon (izvan specifikacija) | [Frekvencije](/hr/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vaši vlastiti KeeLoq ključevi proizvođača | [Formati datoteka](/hr/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/hr/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Zadnje korištena frekvencija, modulacija, filtri, okidač analizatora — zapisuje aplikacija | ne uređivati ručno |

Datoteke koje završavaju na `.example` su predlošci: preimenujte ih u `…_user` kako biste ih aktivirali. Datoteke `_user` ne prepisuju se prilikom ažuriranja firmvera.

## Rješavanje problema

- **`Module` prikazuje samo `Internal`** — nijedan vanjski CC1101 nije otkriven. Provjerite ožičenje i napajanje, zatim ponovno uđite u izbornik.
  Pogledajte [Vanjski CC1101](/hr/subghz/external-cc1101).
- **Signali su slabi pri slanju** — provjerite nije li `TX Power` postavljen na negativnu vrijednost.
- **Nazivi datoteka samo su datumi** — uključite `Protocol Names`.
- **Nema stavki `Ext Amp & LEDs` / `Debug Pin`** — pojavljuju se samo u načinu Debug.

## Povezano

- [Read → Config](/hr/subghz/read#config) · [Frekvencije](/hr/subghz/frequencies) · [Vanjski CC1101](/hr/subghz/external-cc1101)
- [Načini rada brojača](/hr/subghz/counter-mode) · [Formati datoteka](/hr/subghz/file-format) · [Opasne postavke](/hr/start/dangerous-settings)
