---
title: Analizator frekvencija
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Analizator frekvencija

Analizator frekvencija (Frequency Analyzer) govori vam **na kojoj frekvenciji daljinski upravljač odašilje**. Pretražuje frekvencije s
Sub-GHz popisa, mjeri jačinu signala (RSSI) i prikazuje najjaču. Koristite ga prije **Read** ili **Read RAW**
kada ne znate frekvenciju daljinskog upravljača.

::: tip Unleashed
Unleashed dolazi s prerađenim analizatorom (izvorno autora ClusterM) s poviješću od 4 zapisa, podesivim okidačem,
odabirom povratne informacije (zvuk / vibracija / tiho) i **izravnim skokom na Read**: kratki pritisak na <kbd>OK</kbd> sprema
frekvenciju za Read / Read RAW, a dugi pritisak na <kbd>OK</kbd> sprema je i odmah otvara Read.
:::

## Zlatno pravilo

Analizator je namijenjen za rad **samo nekoliko centimetara od Flipperove antene, na unutarnjem radiju**.
Antena se nalazi na lijevoj strani, pokraj crnog IR prozora. Njegove postavke služe za filtriranje šuma, a ne za hvatanje
signala iz daljine. Uz vrlo nizak okidač analizator samo javlja nasumične smetnje i Flipperov
vlastiti šum umjesto vašeg daljinskog upravljača. Za stvarno *primanje* signala koristite [Read](/hr/subghz/read) i
[Read RAW](/hr/subghz/read-raw).

::: warning
Korištenje analizatora s vanjskim modulom nije preporučljivo: vanjski moduli su osjetljiviji i hvataju puno
više šuma.
:::

## Zaslon

![Frequency Analyzer koji prikazuje 433.920 MHz, zapise povijesti i RSSI traku](/screens/subghz/frequency_analyzer.png)

| Element | Značenje |
|---|---|
| Ikona gore desno | Povratna informacija pri hvatanju signala: zvučnik = vibracija + zvuk, mali zvučnik = samo vibracija, prekriženo = tiho |
| Veliki broj u sredini | Trenutna (glavna) frekvencija. Dok se prima signal iznad okidača prikazuje se **invertirano u crnom okviru** |
| Četiri zapisa ispod | Povijest: zaokružena frekvencija i koliko je puta uhvaćena (`x3`). Pomaže kod slabih daljinskih upravljača ili onih kojima frekvencija bježi |
| `RSSI` traka na dnu | Jačina signala uživo s oznakom okidača |
| `T-` / `+T` | Gumbi za razinu okidača |

## Tipke

| Tipka | Radnja |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Pomicanje okidača (od −97 dBm do −60 dBm, korak 1 dBm). Lijevo = osjetljivije, desno = manje osjetljivo |
| <kbd>↑</kbd> | Promjena načina povratne informacije: vibracija + zvuk → tiho → vibracija → … |
| <kbd>↓</kbd> | Odabir zapisa u povijesti (oko njega se pojavljuje okvir) |
| <kbd>OK</kbd> kratko | Spremanje odabrane frekvencije za Read / Read RAW |
| <kbd>OK</kbd> dugo | Spremanje frekvencije i trenutačno otvaranje **Read** |
| <kbd>Back</kbd> | Izlaz (okidač i način povratne informacije se pamte) |

Koju frekvenciju <kbd>OK</kbd> preuzima:

- ako se signal prima **upravo sada** (crni okvir oko glavne frekvencije) — tu frekvenciju, čak i ako je
  odabran zapis iz povijesti;
- ako se ništa ne prima, a odabran je zapis iz povijesti — odabrani zapis;
- u suprotnom — zadnju frekvenciju koja je prešla okidač, tako da ne morate držati daljinski upravljač pritisnutim.

::: warning Zaokruživanje
Spremljena frekvencija uvijek se **zaokružuje na najbližu frekvenciju s popisa** ([Frekvencije](/hr/subghz/frequencies)).
Ako je vaš daljinski upravljač daleko od svih standardnih vrijednosti, dodajte njegovu frekvenciju u `setting_user`. Glavni broj tada će
prikazivati stvarnu frekvenciju, ali nakon skoka u Read / Read RAW morat ćete je ručno postaviti u `Config`.
:::

Spremanje frekvencije iz analizatora također **isključuje Hopping**, tako da Read počinje točno na toj frekvenciji.

## Kako pronaći frekvenciju daljinskog upravljača

1. Odmaknite se od prekidačkih napajanja, punjača i druge elektronike koja stvara smetnje.
2. Otvorite `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Držite daljinski upravljač tik uz lijevu stranu Flippera (blizu crnog prozora).
4. Pritisnite i držite tipku na daljinskom upravljaču. Glavna frekvencija postaje invertirana dok se signal prima.
5. Pustite tipku i pričekajte dok frekvencija ne uđe u povijest.
6. Pritisnite <kbd>OK</kbd> da biste je zapamtili, ili držite <kbd>OK</kbd> za izravan prijelaz u **Read**.

Većina daljinskih upravljača odašilje oko 315, 433,92 ili 868,35 MHz. U Readu ipak isprobajte nekoliko modulacija ako se ništa ne
dekodira (prvo `AM650`, zatim `FM238`, `FM476`, `FM12K`).

## Podešavanje okidača

Zadano je okidač postavljen na −93 dBm, što radi u većini slučajeva. Podešavajte ga samo kada se daljinski upravljač ne hvata
ni iz neposredne blizine, ili kada ima puno šuma:

1. Bez pritisnutog daljinskog upravljača pomičite oznaku tipkama <kbd>←</kbd> / <kbd>→</kbd> dok Flipper ne prestane hvatati
   bilo što (nema šuma, nema nasumičnih pogodaka). Krajnji lijevi položaj je najosjetljiviji — hvata signale *i*
   unutarnji šum Flippera te sve smetnje; krajnji desni je najmanje osjetljiv na oboje.
2. Držite daljinski upravljač uz lijevi rub Flippera i pritisnite njegovu tipku.
3. Ako se ništa ne uhvati, pomičite okidač **ulijevo** korak po korak dok se signal ne pojavi.
4. Tijekom podešavanja više puta pritisnite i pustite tipku daljinskog upravljača — isprekidan signal olakšava pronalaženje
   pravog položaja u odnosu na neprekidan signal.

## Rješavanje problema

- **Stalno se pojavljuju nasumične frekvencije** — okidač je prenisko ili ima šuma u blizini. Pomaknite ga udesno, odmaknite se od napajanja.
- **Daljinski upravljač se nikada ne hvata** — držite ga bliže, provjerite bateriju, pomaknite okidač ulijevo. Neki daljinski upravljači šalju
  vrlo kratke impulse: pritišćite više puta.
- **Read ne prikazuje ništa na pronađenoj frekvenciji** — pogrešna modulacija. Promijenite je u `Read → Config`. Ako se ništa ne
  dekodira, snimite signal pomoću [Read RAW](/hr/subghz/read-raw).
- **Frekvencija odstupa od oznake na daljinskom upravljaču** — uobičajeno; jeftini daljinski upravljači imaju odstupanja. Koristite brojač u povijesti za odabir
  najčešće vrijednosti.

## Povezano

- [Frekvencije](/hr/subghz/frequencies) · [Read](/hr/subghz/read) · [Read RAW](/hr/subghz/read-raw)
- [Remote Analyzer](/hr/subghz/remote-analyzer) — aplikacija s vlastitim analizatorom i dekodiranjem jednog po jednog daljinskog upravljača
