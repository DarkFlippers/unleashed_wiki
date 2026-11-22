---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** i **BFT Mitto** grade svoj pomični kôd iz tajne vrijednosti **Seed**. Bez nje Flipper ne može dekodirati te daljinske upravljače (čitaju se kao `KL: Unknown` ili se uopće ne čitaju) i ne može izraditi daljinski upravljač koji prijemnik prihvaća. **Seed Capturer** (autor @xMasterX) prikuplja sirove podatke za otkrivanje Seeda: vrijednost `Fix` daljinskog upravljača i niz uzastopnih vrijednosti `Hop`.

On **ne** otkriva sam Seed i **nikada ne odašilje** — samo sluša i zapisuje datoteku. Pretraga se pokreće u pratećoj aplikaciji [qUnleashed](/hr/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer je ugrađena sistemska aplikacija u firmveru Unleashed, a qUnleashed izravno dohvaća njezine snimke s Flippera. Jednom kada je Seed poznat, Unleashed može dekodirati daljinski upravljač i izraditi nove putem `Add Manually [Advanced]`.
:::

## Kada vam je potreban

- Programiranje putem radija na prijemniku onemogućeno je, pa je jedini ulaz klon poznatog daljinskog upravljača — a za klon je potreban Seed.
- Vaš FAAC / Genius daljinski upravljač je **podređeni (slave)**, koji ne može poslati kôd za programiranje.
- Ne možete pristupiti prijemniku.
- Sustavi **Erreka** u kojima svaki daljinski upravljač dijeli isti Seed.
- **Stariji BFT Mitto** daljinski upravljači s jedinstvenim Seedom kada postupak s tipkom za programiranje ne radi (noviji BFT daljinski upravljači izvode Seed iz serijskog broja i dekodiraju se u običnom Readu).

Ako se daljinski upravljač može staviti u način programiranja, Seed se često šalje nekriptirano — taj je put brži; pogledajte [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).

## Snimanje

1. Otvorite `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Odaberite `New capture`.
3. **Vrsta daljinskog upravljača:** `FAAC SLH`, `Genius`, `Erreka` ili `BFT Mitto`.
4. **Frekvencija:** `433.92 MHz  AM650` ili `868.35 MHz  AM650` (`BFT Mitto` nudi samo 433.92 MHz).
5. Pritišćite **istu tipku istog daljinskog upravljača** iznova i iznova, otprilike jednom u sekundi, držeći daljinski upravljač tik uz Flipper.
6. Pratite zaslon:
   - `Fix XXXXXXXX` — fiksni dio daljinskog upravljača; aplikacija se zaključa na prvi koji čuje;
   - `Hops n/10  Xpkt` — koliko je **različitih** hopova prikupljeno te ukupan broj sirovih paketa;
   - status `Hop n: XXXXXXXX` svaki put kada stigne novi.
7. Od **2 hopa** nadalje na tipki <kbd>OK</kbd> pojavljuje se `Save`. Pritisnite je; aplikacija prikazuje `Saved N hops` i naziv datoteke.

<kbd>←</kbd> (`Reset`) odbacuje snimku kako biste se mogli zaključati na drugi daljinski upravljač ili drugu tipku.

| Status | Značenje |
|---|---|
| `Hop n: XXXXXXXX` | spremljen novi pomični dio — nastavite pritiskati |
| `Other remote XXXXXXXX` | drugi daljinski upravljač ili druga tipka — zanemareno |
| `Same hop, ignored` | ponavljanje posljednjeg pritiska |
| `Have 10, enough` | puno — pritisnite `Save` |

**Koliko pritisaka:** 2 je minimum, 5–10 je bolje. Jednako je važno da pritisci budu **uzastopni bez ijednog propuštenog** — provjerite povećava li se `Hops` pri svakom pritisku. Ako je jedan propušten, pritisnite `Reset` i počnite ispočetka.

::: warning
Na sustavima **FAAC SLH i Genius Seed je različit za svaku tipku** — snimite upravo onu tipku koju stvarno želite koristiti. Na sustavu Erreka Seed je po daljinskom upravljaču (ponekad po instalaciji), a na BFT Mitto po daljinskom upravljaču.
:::

## Ostale stavke izbornika

- `Decode RAW file` — preuzima Fix/Hopove iz RAW `.sub` datoteke (iz `/ext/subghz`) prethodno snimljene pomoću [Read RAW](/hr/subghz/read-raw); frekvencija se uzima iz datoteke. Datoteka ključa odbija se s porukom `Not a RAW capture`. Ovdje je <kbd>←</kbd> `Back` umjesto `Reset`.
- `Delete all captures` — pita `Delete every capture file in subghz_seed_captures?`, a zatim ih sve briše.
- `Exit`.

## Datoteka snimke

Datoteke idu u `/ext/apps_data/subghz_seed_captures/`, s nazivom `<Type>_<Fix>_<date-time>.txt`, npr. `Erreka_F00F1C9B_261008-142233.txt`. To je tekstualna datoteka, **a ne `.sub` datoteka za reprodukciju**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Otkrivanje Seeda u aplikaciji qUnleashed

1. Povežite Flipper s aplikacijom **qUnleashed** i otvorite njezin alat za otkrivanje Seeda. On sam dohvaća snimke iz `subghz_seed_captures` — bez kopiranja ili preimenovanja.
2. Odaberite snimku i pokrenite pretragu (pretraga grubom silom, zbog čega se i ne izvodi na Flipperu).
3. Ako je Seed pronađen, qUnleashed može sastaviti gotovu klon `.sub` datoteku (serijski broj i tipka iz `Fix`, plus Seed i brojač) i prebaciti je na Flipper.
4. Ako ništa nije pronađeno, snimka je najvjerojatnije imala prekid u nizu — snimite ponovno, pažljivo.

Sa Seedom možete i ručno izraditi daljinske upravljače u `Sub-GHz → Add Manually [Advanced]`: vlastiti `SERIAL` + `SEED` za novi daljinski upravljač ili originalni `SERIAL`/`BUTTON` + `SEED` + malo veći `COUNTER` za klon. Klon se natječe s originalom oko brojača — pogledajte [Pomični kodovi](/hr/subghz/rolling-codes).

::: warning
Samo za daljinske upravljače i prijemnike u vašem vlasništvu.
:::

## Povezane stranice

- [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog) · [KeeLoq](/hr/subghz/keeloq) · [Ručno dodavanje](/hr/subghz/add-manually)
- [Aplikacija qUnleashed](/hr/mobile/qunleashed-app)
