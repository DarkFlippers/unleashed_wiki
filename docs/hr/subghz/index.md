---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Flipper Zero ima ugrađeni **CC1101** primopredajnik i antenu za pojaseve ispod 1 GHz. Pomoću njega možete
čitati, spremati i ponovno slati signale daljinskih upravljača garaža i vrata, rampi, roleta, zvonca,
bežičnih senzora i drugih uređaja koji rade u rasponima **300–348 MHz, 387–464 MHz i 779–928 MHz**.
Većina daljinskih upravljača koje ćete sresti koristi **315 MHz**, **433,92 MHz** ili **868,35 MHz**.

Aplikacija se nalazi u `Main Menu → Sub-GHz`. Njezin glavni izbornik u Unleashedu:

![Glavni izbornik Sub-GHz: Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Stavka izbornika | Što radi | Stranica |
|---|---|---|
| `Read` | Dekodira daljinske upravljače poznatih protokola, sprema ih i šalje | [Read](/hr/subghz/read) |
| `Read RAW` | Snima sirovi signal bilo kojeg daljinskog upravljača i ponavlja ga | [Read RAW](/hr/subghz/read-raw) |
| `Saved` | Spremljene `.sub` datoteke: Emulate, Rename, Delete i Signal Settings kad je uključen Debug | [Read](/hr/subghz/read) |
| `Add Manually` | Stvara potpuno novi daljinski upravljač sa nasumičnim serijskim brojem | [Add Manually](/hr/subghz/add-manually) |
| `Add Manually [Advanced]` | Isto, ali sami unosite serijski broj / tipku / brojač / seed | [Add Manually](/hr/subghz/add-manually) |
| `Frequency Analyzer` | Otkriva na kojoj frekvenciji daljinski upravljač odašilje | [Frequency Analyzer](/hr/subghz/frequency-analyzer) |
| `Radio Settings` | Unutarnji / vanjski modul, snaga odašiljanja, nazivi datoteka, korak brojača | [Postavke](/hr/subghz/settings) |

::: tip Unleashed
Aplikacija Sub-GHz, njezina biblioteka protokola i Frequency Analyzer dolaze iz službenog firmvera. Unleashed
uklanja regionalna TX ograničenja, dodaje dodatne frekvencije i više protokola, omogućuje spremanje i slanje mnogih protokola s promjenjivim kodom (rolling-code), stvara nove rolling-code daljinske upravljače koje možete
registrirati u svom prijemniku (`Add Manually`), koristi tipke sa strelicama kao dodatne tipke daljinskog upravljača, podržava vanjski
CC1101 modul i isporučuje dodatne Sub-GHz aplikacije (Remote Analyzer, Seed Capturer, Nice O-Code, Security+ PIN,
Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning
Koristite ove značajke samo na vlastitoj opremi ili za zakonito istraživanje.
:::

## Početak rada

1. Pronađite frekvenciju svog daljinskog upravljača — [Frequency Analyzer](/hr/subghz/frequency-analyzer).
2. Pokušajte ga dekodirati — [Read](/hr/subghz/read). Ako se dekodira i protokol je **statični**, spremite ga i gotovi ste.
3. Ako je riječ o daljinskom upravljaču s **promjenjivim kodom (rolling code)**, nemojte ga klonirati — pročitajte [Promjenjivi kodovi](/hr/subghz/rolling-codes) i izradite
   novi daljinski upravljač pomoću [Add Manually](/hr/subghz/add-manually) + [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).
4. Ako se ništa ne dekodira, snimite ga pomoću [Read RAW](/hr/subghz/read-raw).

## Sve stranice

**Osnove**
- [Frekvencije](/hr/subghz/frequencies) — pojasevi, zadani popisi, regionalna zaključavanja i prošireni raspon
- [Frequency Analyzer](/hr/subghz/frequency-analyzer) — pronalaženje frekvencije daljinskog upravljača
- [Read](/hr/subghz/read) — dekodiranje, spremanje i slanje signala
- [Read RAW](/hr/subghz/read-raw) — snimanje sirovih signala

**Promjenjivi kodovi i novi daljinski upravljači**
- [Add Manually](/hr/subghz/add-manually) — svaki protokol u izborniku
- [Promjenjivi kodovi](/hr/subghz/rolling-codes) — sukobi brojača, prilagođene tipke
- [KeeLoq](/hr/subghz/keeloq) — kako KeeLoq radi, proizvođački ključevi i seedovi
- [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog) — korak po korak za svaki sustav
- [Načini brojača](/hr/subghz/counter-mode) — eksperimentalni `CounterMode` za klonove
- [Signal Settings](/hr/subghz/signal-settings) — način brojača, brojač i tipka spremljenog signala
- [Podržani sustavi](/hr/subghz/supported-systems) — potpuna tablica protokola

**Konfiguracija i hardver**
- [Postavke](/hr/subghz/settings) — Radio Settings, konfiguracija Read načina, korisničke frekvencije
- [Format datoteke](/hr/subghz/file-format) — `.sub`, preseti, korisničke datoteke postavki
- [Vanjski CC1101](/hr/subghz/external-cc1101) — vanjski moduli i pojačala

**Aplikacije**
- [Sub-GHz Remote](/hr/subghz/remote) — do 5 signala na D-padu
- [Sub-GHz Bruteforce](/hr/subghz/bruteforce) — brute-force statičkih kodova
- [Remote Analyzer](/hr/subghz/remote-analyzer) — dekodiranje jednog daljinskog upravljača, dodatni protokoli
- [Nice O-Code](/hr/subghz/nice-o-code) — oporavak instalaterskog koda
- [Security+ PIN](/hr/subghz/secplus-pin) — PIN tipkovnice za Security+ 2.0
- [Seed Capturer](/hr/subghz/seed-capturer) — prikupljanje skokova za oporavak seeda
- [Sub-GHz RAW Edit](/hr/subghz/raw-editor) — rezanje, spajanje i dekodiranje RAW datoteka

**Terenske bilješke**
- [ZKTeco CMP200](/hr/subghz/zkteco-cmp200) — prikriveni Princeton daljinski upravljač

## Gdje se spremaju datoteke

| Putanja | Sadržaj |
|---|---|
| `/ext/subghz/` | Spremljeni signali (`.sub`), RAW snimke |
| `/ext/subghz/assets/setting_user` | Vaše vlastite frekvencije, popis za preskakanje (hopper), prilagođeni preseti |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vaši vlastiti KeeLoq proizvođački ključevi |
| `/ext/subghz/assets/dangerous_settings` | Prekidač za prošireni frekvencijski raspon |
| `/ext/subghz_remote/` | Datoteke mapiranja aplikacije Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Snimke aplikacije Seed Capturer |
