---
title: Doprinos i prevođenje
order: 40
---
# Doprinos i prevođenje

Ovaj wiki je web-sjedište temeljeno na [VitePressu](https://vitepress.dev). Stranice su običan Markdown, svaka stranica postoji na **svakom jeziku**, a svaka stranica koja koristi neki izvor obavezno ga **navodi**.

## Kako je wiki organiziran

Sadržaj se nalazi u mapi `docs/`, podijeljen po jezicima i zatim po odjeljcima:

```
docs/              # engleski (izvorni jezik)
  nfc/read.md
  community/credits.md
docs/ru/           # ruski — u potpunosti zrcali docs/
  nfc/read.md
  community/credits.md
```

**Svaka stranica postoji na istoj putanji na svakom jeziku.** Engleski `docs/nfc/read.md` i ruski `docs/ru/nfc/read.md` ista su stranica na dvama jezicima. Ako stranica postoji na jednom jeziku, mora postojati na svima — pokrenite `npm run check` za popis stranica koje nedostaju.

Odjeljci (mape na najvišoj razini) zadani su u `docs/.vitepress/i18n/sections.ts`; svaki odjeljak ima `index.md` koji služi kao njegova početna stranica.

## Frontmatter

Svaka stranica započinje YAML blokom frontmattera:

```yaml
---
title: Reading cards            # naziv u bočnom izborniku + naslov stranice
order: 20                       # redoslijed u bočnom izborniku odjeljka (10, 20, 30…)
author: gromovyna               # SAMO ako stranica koristi materijale autora @gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://telegra.ph/...]
sources: [flipper-docs, unleashed-docs]
---
# Reading cards
```

- **`title`** — prikazuje se u bočnom izborniku i kao naslov stranice.
- **`order`** — položaj u bočnom izborniku odjeljka. Koristite višekratnike broja 10 kako bi se nove stranice mogle umetnuti kasnije. Stranice `index.md` pojedinih odjeljaka jesu početne stranice i nemaju `order`.
- **`author`** — postavlja se na `gromovyna` (jedini registrirani ključ autora) kad god se koristi **bilo koji** dio njegovih materijala, čak i djelomično. Na dnu stranice prikazuje istaknutu karticu sa zaslugama.
- **`original`** — popis **točnih** URL-ova na temelju kojih je stranica izrađena. Obavezno kad god je korišten neki izvor.
- **`sources`** — ključevi svih korištenih izvora (pogledajte u nastavku). Obavezno na svakoj stranici sadržaja, uključujući početne stranice odjeljaka.

Zadržite **isti frontmatter na svakom jeziku** — prevođenje stranice ne mijenja kome se pripisuju zasluge.

## Navođenje izvora je obavezno

Ako stranica koristi *bilo koji* izvor — članak, objavu na kanalu, dokumentaciju ili izvorni kôd firmvera — mora ga navesti. Blok zasluga na dnu svake stranice generira se iz gore navedenog frontmattera. Valjani ključevi izvora definirani su u `docs/.vitepress/sources.ts`; trenutačni ključevi uključuju:

| Ključ | Izvor |
|---|---|
| `gromovyna` | Članci i kanal autora @gromovyna |
| `how2flipper` | Kanal @how2flipper_rus |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | Dokumentacija firmvera Unleashed |
| `unleashed-readme` | ReadMe firmvera Unleashed |
| `unleashed-src` | Izvorni kôd firmvera Unleashed |
| `li0ard` | Blog autora li0ard |

Izrada stranice na temelju izvornog kôda firmvera također se smatra korištenjem izvora: dodajte `unleashed-src` u `sources` i navedite odgovarajuću mapu izvornog kôda na GitHubu u `original`.

Kako oblikovati URL-ove u `original`:

- **Flipper docs** — `https://docs.flipper.net/zero/<path>` (tako `zero_nfc_read.md` postaje `/zero/nfc/read`).
- **Unleashed docs** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md` (razmaci kao `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — URL članka na `telegra.ph` i/ili `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Stil pisanja

- Prave upute, a ne puka kopija. Prepišite vlastitim riječima, spojite preklapajuće izvore i prilagodite strukturu čitatelju.
- Neka upute budu **prvenstveno za Unleashed**: kada se Unleashed razlikuje od službenog firmvera, istaknite to okvirom `::: tip Unleashed`.
- Svaka stranica značajke treba sadržavati: što je to → kada je koristiti → numerirane korake s točnim putanjama izbornika (`Main Menu → Sub-GHz → Read`), tipke kao `<kbd>OK</kbd>`, očekivane rezultate, rješavanje problema i povezane poveznice.
- Točno sačuvajte tehničke činjenice: frekvencije, formate datoteka, putanje poput `/ext/subghz/`, CLI naredbe, nazive protokola, brojeve inačica. Nemojte izmišljati značajke — ako niste sigurni, izostavite ih.
- Koristite VitePress spremnike: `::: tip`, `::: warning`, `::: danger`, `::: details`. Jedini dopušteni sirovi HTML jest `<kbd>`; bez Vue komponenti.
- Unutarnje poveznice su apsolutne i bez nastavka datoteke: `/nfc/mfkey` na engleskom, `/ru/nfc/mfkey` na ruskom. Povezujte samo stranice koje postoje.

## Dodavanje stranice

1. Izradite `docs/<section>/<page>.md` s frontmatterom i sadržajem.
2. Izradite zrcalnu stranicu na **svakom** drugom jeziku na istoj putanji (npr. `docs/ru/<section>/<page>.md`).
3. Dodajte je na popis u `index.md` tog odjeljka.
4. Pokrenite `npm run check` kako biste provjerili da nijednom jeziku ne nedostaje stranica, a zatim `npx vitepress build docs` za otkrivanje neispravnih poveznica (prijavljuju se kao pogreške pri izgradnji).

Bočni izbornik generira se automatski iz datoteka i njihova polja `order`, pa nema zasebnog popisa bočnog izbornika za uređivanje.

## Snimke zaslona uređaja

Zasloni Flippera pod `/screens/…` **generiraju se, a ne snimaju**. `npm run screens` prevodi vlastiti GUI kôd firmvera (platno, `gui/modules/*` i prikaze aplikacija) te iscrtava svaki zaslon u `docs/public/screens/<section>/<name>.png`. Rezultat je na razini piksela identičan snimci zaslona iz qFlippera: isti okvir veličine 128×64, iste dvije boje, uvećano ×4. Alat za iscrtavanje nalazi se u `scripts/screens/` — njegov `README.md` objašnjava preduvjete, odakle dolazi izvorni kôd firmvera i kako je izlazni format izveden iz kôda qFlippera.

Za dodavanje novog zaslona:

1. Napišite blok `SCREEN(...)` u `scripts/screens/specs/<section>.c`. Izgradite prikaz na potpuno isti način kao što to radi scena aplikacije (`submenu_add_item`, `widget_add_*`, `popup_set_*`, vlastiti setteri prikaza) s realističnim oglednim podacima.
2. Pokrenite `npm run screens` (ili `bash scripts/screens/build.sh --only <section>/` za jedan odjeljak).
3. Referencirajte PNG datoteku sa stranice: `![zamjenski tekst](/screens/<section>/<name>.png)`. Putanja je **identična na svakom jeziku**; prevodi se samo zamjenski tekst.

Svaku snimku zaslona postavite uz korak ili zaslon koji prikazuje, a ne u galeriju na vrhu stranice, i ograničite ih na nekoliko po stranici. `docs/public/screens/manifest.json` navodi svaki generirani zaslon s njegovim naslovom, putanjom izbornika i scenom firmvera iz koje potječe ogledno stanje.

## Dodavanje novog jezika

Registar jezika nalazi se u `docs/.vitepress/i18n/`. Za dodavanje jezika `xx`:

1. **Kopirajte tekstove sučelja.** Kopirajte `docs/.vitepress/i18n/en.ts` u `docs/.vitepress/i18n/xx.ts` i prevedite svaki tekst u njoj. Postavite `prefix: 'xx'` (to postaje URL prefiks `/xx/`).
2. **Registrirajte jezik.** U `docs/.vitepress/i18n/index.ts` uvezite svoju datoteku i dodajte je u polje `LOCALES`.
3. **Izradite stranice.** Izradite `docs/xx/` kao zrcalnu kopiju `docs/` — isti nazivi datoteka i putanje — i prevedite svaku stranicu. Zadržite identičan frontmatter (isti `author`, `original`, `sources`).
4. **Provjerite.** Pokrenite `npm run check` za popis stranica koje nedostaju u novom jeziku, popunite praznine, a zatim pokrenite izgradnju.

::: tip Za sadržaj ne dirate .vitepress/
Sve gore navedeno, osim *dodavanja jezika*, čisti je Markdown pod `docs/`. Bočni izbornik, navigacijska traka i blok zasluga generiraju se automatski — ostavite `docs/.vitepress/` na miru osim ako izričito ne dodajete jezik ili ključ izvora.
:::

::: tip Pogledajte i
- [Zasluge i zahvale](/hr/community/credits) — kako su postojeće stranice navedene
- [Pregled zajednice](/hr/community/) — ostatak ovog odjeljka
:::
