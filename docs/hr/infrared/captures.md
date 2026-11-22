---
title: Doprinos snimljenih signala
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# Doprinos IR snimljenih signala univerzalnim daljinskim upravljačima

Ako [univerzalni daljinski upravljač](/hr/infrared/universal-remotes) ne radi s vašim uređajem, možete snimiti svoj izvorni daljinski upravljač i dodati ga u biblioteku kako bi radio svima. **Čista** snimka je kratka, dekodirana gdje je to moguće i imenovana točno onako kako univerzalni daljinski upravljač očekuje.

Metoda je Unleashed vodič autora **@amec0e** (koji održava IR resurse za Unleashed), temeljen na izvornoj dokumentaciji *UniversalRemotes* autora @gsurkov, @skotopes, @knrn-ai, @DrZlo13 i @ahumeniy.

## Nazivi tipki po biblioteci {#button-names-per-library}

Univerzalni daljinski upravljač koristi samo signale čije se polje `name:` točno podudara s jednom od njegovih tipki (velika i mala slova su važna). Bilo koja od njih može se izostaviti ako je vaš uređaj nema.

| Biblioteka | Datoteka | Nazivi signala |
|---|---|---|
| TV uređaji | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projektori | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LED rasvjeta | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Ventilatori | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| Klima-uređaji | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

Na mnogim audio daljinskim upravljačima `Play` i `Pause` su ista tipka: snimite je kao `Play` i izostavite `Pause`.

## TV uređaji, audio, projektori, ventilatori, LED rasvjeta

1. Usmjerite daljinski upravljač prema Flipperovom IR prijemniku.
2. Pokrenite `Infrared → Learn New Remote` za prvu tipku ili odaberite `+` u daljinskom upravljaču za sljedeće.
3. Napravite **kratak pritisak** tipke daljinskog upravljača i spremite signal pod odgovarajućim nazivom iz gornje tablice.
4. Ponovite korake 2-3 za sve tipke.
5. Testirajte svaku spremljenu tipku na stvarnom uređaju: svaka mora raditi ono što njezin naziv kaže.

::: warning Nemojte držati tipku
Držanje tipke daljinskog upravljača stvara dugačke snimke s mnogo ponavljanja. One traju dulje pri slanju i usporavaju cijeli univerzalni daljinski upravljač za sve korisnike.
:::

### Parsed naspram RAW

**Parsed** je najbolji rezultat: protokol je prepoznat i pohranjeni su samo protokol, adresa i naredba.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Smetnje drugih uređaja oko vas (svjetiljke, pozadinska rasvjeta TV-a, drugi daljinski upravljači) mogu prebaciti snimku u **RAW** čak i ako je protokol poznat. Ako ste za uobičajeni daljinski upravljač dobili RAW, pritisnite **Retry** na Flipperu nekoliko puta dok ne dobijete čistu dekodiranu (parsed) snimku.

**RAW** je u redu kada daljinski upravljač stvarno koristi nepoznat protokol. Ciljajte na *najmanji broj uzoraka* koji i dalje radi na uređaju: kratak pritisak, obično **oko 100 uzoraka**. Idealna snimka jednog pritiska izgleda ovako:

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Klima-uređaji {#air-conditioners}

Daljinski upravljači klima-uređaja su drukčiji: daljinski upravljač čuva stanje (način rada, temperaturu, ventilator, krilca) na svom zaslonu i svaki pritisak šalje **cijelo stanje** odjednom. Zato je svaka „tipka“ klima-uređaja zapravo cjelovito stanje koje se mora snimiti u cijelosti.

Za svaki signal **osim `Off`**:

1. Pritisnite **Power** na daljinskom upravljaču tako da njegov zaslon prikazuje da je klima-uređaj UKLJUČEN (ON).
2. Postavite način rada i temperaturu prema tablici u nastavku. Sve ostalo (brzinu ventilatora, krilca) ostavite na **AUTO** ako je moguće.
3. Pritisnite **Power** na daljinskom upravljaču kako biste ga ISKLJUČILI (OFF).
4. Na Flipperu pokrenite učenje (`Learn New Remote` za prvi signal, `+` za ostale).
5. Usmjerite daljinski upravljač prema Flipperu i još jednom pritisnite **Power** (ovo je okvir signala „uključi u ovom načinu rada“).
6. Spremite signal pod nazivom iz tablice.
7. Ponovite za svaki redak.

| Signal | Način rada | Temperatura | Napomena |
|:---:|:---:|:---:|---|
| `Dh` | Odvlaživanje (Dehumidify) | N/A | |
| `Cool_hi` | Hlađenje (Cooling) | najniža | najniža dostupna temperatura u načinu hlađenja |
| `Cool_lo` | Hlađenje (Cooling) | 23 °C | |
| `Heat_hi` | Grijanje (Heating) | najviša | najviša dostupna temperatura u načinu grijanja |
| `Heat_lo` | Grijanje (Heating) | 23 °C | |

Zatim snimite **`Off`**:

1. Provjerite prikazuje li zaslon daljinskog upravljača da je klima-uređaj UKLJUČEN (ON).
2. Pokrenite učenje na Flipperu i usmjerite daljinski upravljač prema njemu.
3. Pritisnite **Power** tako da daljinski upravljač prikaže OFF.
4. Spremite signal kao `Off`.

Na kraju imate do 6 signala. Sve ih testirajte na stvarnom klima-uređaju.

## Priprema datoteke i slanje

1. Kopirajte `.ir` datoteku iz `/ext/infrared/` na svoje računalo pomoću [qFlippera](/hr/mobile/qflipper) (ili mobilne aplikacije) i otvorite je u uređivaču teksta.
2. Ispred svojih signala dodajte komentar s modelom kako bi biblioteka ostala uredna:
   ```text
   # Model: <your brand and model>
   ```
   Redoslijed signala unutar bloka nije važan.
3. Forkajte [repozitorij Unleashed](https://github.com/DarkFlippers/unleashed-firmware) i **dodajte** svoj blok **na kraj** odgovarajuće datoteke u `applications/main/infrared/resources/infrared/assets/`.
4. Otvorite pull request s izmijenjenom datotekom. Nakon pregleda bit će uključen u sljedeće izdanje za sve korisnike.

Format datoteke opisan je na stranici [Format IR datoteka](/hr/infrared/file-format#library-files). Velike zbirke gotovih daljinskih upravljača iz zajednice: [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) i službeni [flipperdevices/IRDB](https://github.com/flipperdevices/IRDB) koji koristi [mobilna aplikacija](/hr/infrared/mobile).

## Povezane stranice

- [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes)
- [Učenje i slanje signala](/hr/infrared/read)
- [Format IR datoteka](/hr/infrared/file-format)
