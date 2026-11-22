---
title: Načini brojača
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Načini brojača (eksperimentalno)

**Counter Mode** mijenja način na koji se pomični brojač povećava kada Flipper odašilje spremljeni signal s pomičnim kôdom (rolling code). Cilj je klon vašeg originalnog daljinskog upravljača koji **ne dolazi u sukob** s njim, tako da se i Flipper i original mogu koristiti s istim prijemnikom bez gubitka sinkronizacije. (Pozadina: [Pomični kodovi](/hr/subghz/rolling-codes).)

::: tip Unleashed
Načini brojača značajka su dostupna samo u firmveru Unleashed. Podržani protokoli: **Nice FloR-S, CAME Atomo, Alutech AT-4N, KeeLoq, V2 Phoenix**.
:::

::: danger Pročitajte prije korištenja
Nemojte eksperimentirati s opremom kojoj nemate pristup. Ako niste sigurni koji način rada odgovara vašem sustavu i **ne možete ponovno upariti svoj originalni daljinski upravljač** u prijemnik — nemojte koristiti ove načine. Mogu poremetiti sinkronizaciju ili blokirati vaš daljinski upravljač. Ako možete testirati na vlastitom prijemniku, javite timu Unleasheda što radi (GitHub issues / razgovori zajednice).
:::

## Kako postaviti način rada

### 1. mogućnost — uredite `.sub` datoteku

1. Kopirajte datoteku iz `/ext/subghz/` na računalo (qFlipper, mobilna aplikacija ili čitač kartica).
2. Na kraj dodajte redak:
   ```text
   CounterMode: X
   ```
   gdje je `X` broj načina rada. Obratite pozornost na razmak nakon dvotočke.
3. Kopirajte datoteku natrag.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### 2. mogućnost — Signal Settings na Flipperu

Kad je uključen **Debug**, izbornik spremljenog signala dobiva dodatnu stavku: `Sub-GHz → Saved → <file> → Signal Settings`. Njezin redak `Counter Mode` nudi `System` (način 0) i `Mode 1` … do posljednjeg načina koji protokol ima te odmah zapisuje vaš odabir u datoteku. Isti zaslon također može uređivati brojač i kôd tipke: pogledajte [Signal Settings](/hr/subghz/signal-settings).

## Načini rada po protokolu {#modes-by-protocol}

Način 0 uvijek je zadani: ponaša se kao običan daljinski upravljač, brojač raste za globalnu vrijednost [Counter Incr.](/hr/subghz/settings) (zadano +1) i vraća se na 0 nakon `0xFFFF`.

### Nice FloR-S

| Način | Brojač | Napomene |
|---|---|---|
| 0 | +multiplier | zadano |
| 1 | `0x0001 / 0xFFFE` | prijemnik **floxi2r** |
| 2 | `0x0000 / 0x0001` | prijemnik **ox2** |

### CAME Atomo

| Način | Brojač | Napomene |
|---|---|---|
| 0 | +multiplier | zadano |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | radi s vanjskim CAME **RE432**, možda i drugima |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | radi s vanjskim CAME **RE432**, možda i drugima |
| 3 | zamrznut | brojač se ne povećava |

### Alutech AT-4N

| Način | Brojač | Napomene |
|---|---|---|
| 0 | +multiplier | zadano |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | prijemnik **MCSW-3.3M** |
| 2 | `0x0000 … 0x0005` | druge ploče prijemnika |

### KeeLoq

| Način | Brojač | Napomene |
|---|---|---|
| 0 | +multiplier | zadano |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | može raditi s nekim sustavima |
| 2 | `+0x3333` po odašiljanju (13107) | npr. DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | npr. Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | npr. Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | izmjenjuje 0 i 65535 |
| 6 | zamrznut | brojač se ne povećava |
| 7–10 | paketi za prisilnu resinkronizaciju | DoorHan, Phantom / Hiland, pogledajte u nastavku |

#### Načini 7–10: paketi za prisilnu resinkronizaciju (DoorHan, Phantom / Hiland)

Ovi načini ne pomiču brojač; svaki pritisak šalje **fiksni paket** kodova. Prijemnik se ponovno sinkronizira tek kada čuje dva odašiljanja s **uzastopnim** brojačima, pa je paket sastavljen od uzastopnih parova, razmaknutih tako da svaki skok ostane unutar prozora resinkronizacije prijemnika, a parovi zajedno pokriju cijeli prostor brojača. To vraća prijemnik iz bilo kojeg stanja. Brojač u vašoj datoteci ne mijenja se, pa svaki pritisak šalje isti paket i datoteka ostaje upotrebljiva.

Svaki paket doslovno, kôd po kôd, reproducira ono što klon-daljinski šalje za tu obitelj ploča. Načini 7–9 = klon DoorHan Smart, način 10 = klon Phantom / Hiland. `X` = brojač u vašoj datoteci.

| Način | Za | Paket | Vrijeme po pritisku |
|---|---|---|---|
| 7 | najstarije ploče DoorHan | 12 kodova: `X / X+1`, četiri para koji koračaju unaprijed u koracima od 15998 (tipka 0), zatim `X-2 / X-1`; prvi i zadnji par nose vašu tipku | ~1,3 s |
| 8 | DHRE, većina novijih ploča, klonovi za krilna vrata | 12 kodova: `X / X+1`, četiri para razmaknuta za `+0x3334`, zatim povratak na vaš brojač gdje sjeda `X+1` s vašom tipkom | ~1,3 s |
| 9 | ploče za rolete CV01, druge stare ploče | 3 kôda s vašom tipkom: `X + 0x8000`, `X-1`, `X+1`, svaki poslan dvaput | ~0,65 s |
| 10 | Phantom / Hiland | 2 kôda s vašom tipkom: apsolutni `0xFFFE`, `0xFFFF`, svaki poslan triput | ~0,4 s |

::: warning Način 7 je promijenjen
Način 8 jest upravo ono što je `CounterMode: 7` radio u ranijim izdanjima. Ako imate datoteku s `CounterMode: 7` koja je radila, promijenite ga u `CounterMode: 8`.
:::

Detalji:

- U dugim paketima (7 i 8) svaki kôd ide van **jednom** (originalni klon šalje svaki dvaput ili triput) — cijeli paket gradi se u memoriji, a utrostručavanje bi zahtijevalo 20 KB umjesto 8 KB. Ponovno slanje paketa nije zamjena: prijemnik koji se već resinkronizirao drugi prolaz čita kao novi niz i ponovno pokreće vrata, dok se uzastopno ponavljanje istog kôda zanemaruje kao duplikat.
- Način 10 zanemaruje brojač u vašoj datoteci. Bez hodanja kroz prostor, jedan pritisak resinkronizira prijemnik koji drži bilo koju od 32768 vrijednosti ispod `0xFFFE` — gdje se nalazi prijemnik koji je odmaknuo ispred vašeg daljinskog. Ako ne primi odmah, pošaljite još jednom.
- **Držanje** tipke Send ponavlja paket sve dok je držite; prijemnik koji se resinkronizirao u prvom prolazu to čita kao još jedan pritisak. Ponovni pritisak na Send dok paket izlazi **prekida** slanje.

### V2 Phoenix (Phox)

| Način | Brojač | Napomene |
|---|---|---|
| 0 | +multiplier | zadano |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` („ofex like“) | potvrđeno da radi |
| 2 | `0x0000 … 0x0004` | može raditi |

## Primjer: KeeLoq DoorHan s +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Rješavanje problema i česta pitanja

- **Datoteka ne radi nakon dodavanja `CounterMode`** — provjerite sintaksu `CounterMode: X` (razmak nakon dvotočke) i je li broj valjan za taj protokol.
- **Nevažeći broj načina rada?** Koristi se posljednji način s popisa protokola.
- **Trebam li to u svakoj datoteci?** Ne. Bez `CounterMode` koristi se način 0.
- **Može li oštetiti moj daljinski upravljač/prijemnik?** Može poremetiti sinkronizaciju daljinskog upravljača, ovisno o prijemniku. Nemojte ga koristiti ako ne možete ponovno upariti original.
- **Koji način trebam koristiti?** Ako niste sigurni — nijedan. Radije odaberite [novi daljinski upravljač](/hr/subghz/add-manually).

## Povezano

- [Signal Settings](/hr/subghz/signal-settings) — postavljanje načina rada, brojača i tipke na Flipperu
- [Pomični kodovi](/hr/subghz/rolling-codes) · [KeeLoq](/hr/subghz/keeloq)
- [Radio Settings: Counter Incr.](/hr/subghz/settings) · [Format .sub datoteka](/hr/subghz/file-format)
