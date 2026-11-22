---
title: Postavke signala (Signal Settings)
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Postavke signala (Signal Settings)

**Signal Settings** uređuje signal koji ste već spremili: njegov način rada brojača, trenutni promjenjivi brojač i kod tipke. To je mali stručni zaslon, skriven osim ako je uključen Debug način rada, a većina njegovih opcija radi samo na nekolicini protokola koji podržavaju [načine brojača](/hr/subghz/counter-mode).

## Gdje se nalazi {#where}

To je stavka u izborniku spremljenog signala, a ne stavka u glavnom izborniku Sub-GHz. Otvorite datoteku iz `Sub-GHz → Saved` (ili iz aplikacije [Archive](/hr/apps/archive)) i izbornik je:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Kako je prikazati {#enable}

`Signal Settings` dodaje se tom izborniku samo dok je **Debug** uključen. Kada je Debug isključen, opcija nije prisutna.

- Brzi način: držite <kbd>↓</kbd> na radnoj površini, zatim držite <kbd>OK</kbd> na zaslonu s informacijama ([Radna površina → Zaslon s informacijama o uređaju](/hr/start/desktop#info-screen)).
- Ili `Settings → System → Debug` = `ON` ([Postavke](/hr/start/settings)).

## Tri stavke {#items}

![Signal Settings: Counter Mode, Edit Counter i Edit Button](/screens/subghz/signal_settings.png)

| Stavka | Što radi |
|---|---|
| `Counter Mode` | Tipkama <kbd>←</kbd>/<kbd>→</kbd> odaberite `System` (način 0) ili `Mode 1` … do ograničenja protokola. Odabir se odmah zapisuje u `.sub` datoteku kao redak `CounterMode:` i datoteka se ponovno učitava; ništa se ne odašilje |
| `Edit Counter` | Tipka <kbd>OK</kbd> otvara heksadekadski unos za trenutni brojač s naslovom `Enter <N>-bits counter in HEX` i duljinom brojača za taj protokol: 4 hex znamenke (2 bajta) do 16 bitova, 8 znamenki (4 bajta) iznad toga |
| `Edit Button` | Tipka <kbd>OK</kbd> otvara heksadekadski unos za kod tipke s naslovom `Enter <N>-bits button in HEX` — uvijek jedan bajt, 2 hex znamenke |

Vrijednost koju svaka stavka trenutno sadrži prikazana je u njezinom retku, u heksadekadskom zapisu. Što sami načini brojača rade brojaču i kako ga umjesto toga postaviti uređivanjem datoteke na računalu, opisano je na stranici [Načini brojača](/hr/subghz/counter-mode#modes-by-protocol).

::: warning Potvrda uređivanja brojača ili tipke pokreće odašiljanje
`Edit Counter` i `Edit Button` zapisuju datoteku pokretanjem putanje odašiljanja: firmver započinje slanje s novom vrijednošću i odmah ga zaustavlja, a datoteka se ponovno zapisuje kada to slanje stane. Radio se aktivira na djelić sekunde, pa to radite podalje od prijemnika kojim ne želite upravljati.

Brojač koji upišete sprema se točno onako kako je upisan — za to jedno ponovno spremanje način brojača i korak [Counter Incr.](/hr/subghz/settings) se preskaču. Uređivanje tipke umjesto toga postavlja korak na 0 za ponovno spremanje, tako da promjena tipke ostavlja brojač ondje gdje je bio.

Ako je slanje odbijeno — na frekvenciji na kojoj ovaj firmver neće odašiljati — datoteka se uopće ne zapisuje.
:::

## Protokoli s načinima brojača {#protocols}

`Counter Mode` je otključan za pet protokola. `System` je način 0, uobičajeni način:

| Protokol | Izbori |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

Podudaranje se provjerava prema retku `Protocol:` u datoteci. Za svaki drugi protokol stavka je zaključana.

## Zaključane stavke {#locked}

Zaključana stavka ne može se otvoriti niti promijeniti; pritiskom na nju prikazuje se `Not available for this protocol !`

- `Counter Mode` — protokol datoteke nije jedan od gornjih pet.
- `Edit Counter` — protokol nema brojač. Može ovisiti i o proizvođaču: kod protokola KeeLoq stavka je zaključana za `AN-Motors`, koji ima samo pseudobrojač, te za `Unknown`.
- `Edit Button` — protokol nema kod tipke u svom okviru signala.

`Edit Button` također je otključan na statičkim protokolima koji nose kod tipke — Princeton, Dooya, GangQi, Hollarm, Nord ICE, Proteco i Roger — i na njima radi jednako kao i na signalu s promjenjivim kodom.

## Povezano {#related}

- [Načini brojača](/hr/subghz/counter-mode) — što svaki način radi i redak datoteke `CounterMode:`
- [Promjenjivi kodovi](/hr/subghz/rolling-codes) · [Format `.sub` datoteke](/hr/subghz/file-format)
- [Radna površina](/hr/start/desktop#info-screen) — prečac za Debug · [Postavke](/hr/start/settings) — Debug u izbornicima
