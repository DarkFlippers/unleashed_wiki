---
title: Remote Analyzer
order: 160
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/remote_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Remote Analyzer

**Remote Analyzer** (autor @xMasterX) dekodira jedan po jedan daljinski upravljač na internom čipu CC1101 i prikazuje svako polje koje uspije prepoznati. Za razliku od `Sub-GHz → Read`, **ne čuva povijest** — na zaslonu je samo zadnji signal — i **nikada ne sprema** `.sub` datoteku. To je alat za odgovor na pitanje „kakav je ovo daljinski upravljač?“.

::: tip Unleashed
Remote Analyzer je ugrađena sistemska aplikacija Unleashed firmvera. Uz sve protokole koje aplikacija Sub-GHz poznaje, sadrži i vlastite protokole samo za dekodiranje: **Crypt**, **Crypt Lite**, **Hormann BiSecur**, **KCE6xxx**, **Life Fido**, **Nero Intro II** i **PC4**.
:::

**Kada ga koristiti:** kada želite brzo identificirati nepoznati daljinski upravljač, vidjeti ima li fiksni ili promjenjivi (rolling) kod ili provjeriti daljinski upravljač koji glavna aplikacija ne može dekodirati. Za snimanje i ponovno slanje koristite [Read](/hr/subghz/read) ili [Read RAW](/hr/subghz/read-raw).

## Glavni izbornik

`Main Menu → Apps → Sub-GHz → Remote Analyzer`:

- `Read` — dekodiranje uživo
- `Decode RAW File` — provlačenje spremljene RAW snimke kroz iste dekodere
- `Frequency Analyzer` — pronalaženje frekvencije daljinskog upravljača
- `How to use` — ugrađeni priručnik

## Čitanje daljinskog upravljača

1. Otvorite `Read`. Zaslon prikazuje `Waiting for a signal`.
2. Pritisnite <kbd>←</kbd> (`Config`) i postavite **Frequency** i **Modulation** (ili uključite **Hopping**).
3. Držite daljinski upravljač blizu Flippera i pritisnite njegovu tipku.
4. Pojavljuje se očitanje:
   - ikona u gornjem lijevom kutu označava **fiksni** ili **promjenjivi (rolling)** kod;
   - redak ispod naziva protokola i broja bitova govori poznaje li i aplikacija Sub-GHz taj protokol ili je dostupan **samo u analizatoru** (analyzer only);
   - `xN` u gornjem desnom kutu broji koliko je puta taj kod primljen;
   - traka ispod retka prikazuje jačinu signala.
5. <kbd>↑</kbd> / <kbd>↓</kbd> pomiču očitanje koje ne stane na zaslon, a <kbd>→</kbd> (`Reset`) ga briše.

**LED dioda:** ljubičasta — sluša; žuta — nešto je u eteru, ali ništa nije dekodirano; zelena — kod je primljen.

## Config

| Stavka | Što radi |
|---|---|
| Frequency | frekvencija prijema (zanemareno dok je uključen Hopping) |
| Modulation | predložak: AM270, AM650, FM238, FM476, FM12K i bilo koji prilagođeni predlošci |
| Hopping | `OFF` ili razina od `-90dB` do `-40dB` |
| Sound | reprodukcija demoduliranog signala na zvučniku |
| Mod. sweep | isprobavanje drugih modulacija kada se ništa ne dekodira |
| Notify | kratka vibracija na kod koji se razlikuje od prethodnog |
| Reset to default | vraćanje zadanih vrijednosti |

**Hopping.** Kada je postavljena razina, aplikacija obilazi **315, 390, 430.5, 433.92, 434.42 i 868.35 MHz** dok je eter tih i zaustavlja se na prvom pojasu gdje nositelj dosegne tu razinu. Dekodiranje zadržava pojas dvije sekunde prije nastavka skakanja. Odabirom frekvencije u alatu Frequency Analyzer isključuje se hopping. Ta je razina ujedno ono što sweep i LED dioda tretiraju kao „signal“, pa je važna i kada je hopping `OFF`.

**Mod. sweep.** Kada daljinski upravljač očito odašilje, ali ga ništa ne dekodira, aplikacija prolazi kroz ostale modulacije, otprilike po sekundu svaku. Znak `~` uz modulaciju znači da još pokušava — **držite tipku daljinskog upravljača pritisnutom**. Prvo uspješno dekodiranje zaključava modulaciju i `~` nestaje; nakon dvije sekunde bez dekodiranja pretraga ponovno kreće od te točke. `Unknown remote` znači da cijeli krug nije pronašao ništa; krug se ponavlja dok je tipka pritisnuta.

**Notify.** Držani daljinski upravljač ponavlja jedan kod, pa tada samo treperi LED dioda; novi, drukčiji kod ujedno aktivira vibraciju.

## Decode RAW File

1. Odaberite `Decode RAW File` i odaberite RAW `.sub` datoteku iz `/ext/subghz`.
2. Traka napretka prikazuje dokle je obrada datoteke stigla.
3. Prikazuje se popis svih pronađenih različitih kodova; pritisnite <kbd>OK</kbd> na jedan za potpuno očitanje.

Samo RAW snimka sadrži uzorke — spremljena datoteka ključa se odbija. Ako ništa nije dekodirano (ili je datoteka odbijena), uređaj zapišti pogrešku i zadrži crvenu LED diodu.

## Frequency Analyzer

Držite tipku daljinskog upravljača blizu Flippera, zatim **zadržite** <kbd>OK</kbd> da biste otkrivenu frekvenciju prenijeli u `Read`. Tipke <kbd>←</kbd> / <kbd>→</kbd> pomiču razinu okidača. Radi jednako kao [analizator glavne aplikacije](/hr/subghz/frequency-analyzer).

## Rješavanje problema

- **Uvijek `Waiting for a signal`** — pogrešna frekvencija; pokrenite Frequency Analyzer ili uključite Hopping.
- **Žuta LED dioda, ali bez dekodiranja** — uključite `Mod. sweep` i držite tipku, ili ga snimite pomoću [Read RAW](/hr/subghz/read-raw) i pokušajte `Decode RAW File`.
- **Protokol samo za analizator** — glavna aplikacija Sub-GHz ne može ga spremiti niti poslati; Remote Analyzer ga samo prepoznaje.
- **Želite spremiti signal** — koristite [Read](/hr/subghz/read); ova aplikacija ne zapisuje datoteke.

## Povezane stranice

- [Read](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw) · [Frequency Analyzer](/hr/subghz/frequency-analyzer)
- [Podržani sustavi](/hr/subghz/supported-systems)
