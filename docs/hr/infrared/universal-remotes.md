---
title: Univerzalni daljinski upravljači
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Univerzalni daljinski upravljači

Univerzalni daljinski upravljač omogućuje upravljanje uređajem **bez prethodnog učenja njegova daljinskog upravljača**. Kada pritisnete, primjerice, *Power*,
Flipper šalje kôd za uključivanje/isključivanje svakog modela u svojoj biblioteci, jedan za drugim. Kada naiđe na kôd koji vaš
uređaj razumije, uređaj reagira. Zato pritisak na univerzalnu tipku traje nekoliko sekundi umjesto da djeluje trenutačno.

Otvorite `Main Menu → Infrared → Universal Remotes`.

![Popis kategorija u izborniku Universal Remotes: TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
Službeni firmver dolazi s bibliotekama za TV, Audio, Projectors i ACs. Unleashed dodaje **LEDs** i **Fans** te održava sve
biblioteke znatno opsežnijima i redovito iznova provjerenima od strane tima (IR resursi: @amec0e). Biblioteka za TV iznova je sastavljena tako da
rade **sve** njezine tipke, ne samo Power.
:::

## Kategorije

Stavke izbornika i nazivi tipki u nastavku preuzeti su iz firmvera; broj signala potječe iz biblioteka
priloženih uz trenutačnu `dev` verziju (`/ext/infrared/assets/`, zadnje ažuriranje listopad 2024. / veljača 2024. za klima-uređaje).

| Stavka izbornika | Datoteka biblioteke | Tipke | Signala u biblioteci |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (od toga 295 Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

"Audio" obuhvaća soundbarove, AV prijamnike, glazbene linije i slične uređaje. "LEDs" označava LED trake i žarulje s IR upravljanjem.

### Klima-uređaji

Daljinski upravljači klima-uređaja sami pamte stanje uređaja i pri svakom pritisku šalju cijelo stanje, pa biblioteka za klima-uređaje sadrži
potpune "scene" umjesto pojedinačnih tipki:

| Tipka | Značenje |
|---|---|
| **Off** | Isključivanje klima-uređaja. Ovo je *jedina* tipka koja ga isključuje. |
| **Dh** | Način odvlaživanja (dry). |
| **Cool_hi** | Hlađenje na najnižoj temperaturi koju daljinski dopušta (maksimalno hlađenje). |
| **Cool_lo** | Hlađenje na 23 °C. |
| **Heat_hi** | Grijanje na najvišoj temperaturi koju daljinski dopušta (maksimalno grijanje). |
| **Heat_lo** | Grijanje na 23 °C. |

Da biste **uključili** klima-uređaj, pritisnite bilo koju tipku osim Off. Tipke za temperaturu prikazuju °C ili °F ovisno o postavci
`Settings → System → Units`.

## Kako koristiti

1. Idite na `Main Menu → Infrared → Universal Remotes` i odaberite kategoriju.
2. Usmjerite gornji rub Flippera prema uređaju. Ostanite blizu i u liniji vidljivosti.
3. Odaberite tipku strelicama i pritisnite <kbd>OK</kbd>.

   ![Univerzalni daljinski za TV prikazan na okomitom zaslonu: Power i Mute gore, Channel i Volume gore/dolje ispod](/screens/infrared/universal_tv.png)

4. Prozor **"Sending..."** prikazuje napredak kao `current/total` i traku napretka. Nastavite usmjeravati prema uređaju.
5. Kada uređaj reagira, pritisnite <kbd>OK</kbd> za **pauzu** ili pustite da biblioteka prođe do kraja.

![Univerzalni daljinski upravljač u akciji](/img/remote/bdb3541a3f2e88fe.png)

### Kontrole tijekom slanja

| Stanje | Tipka | Radnja |
|---|---|---|
| Slanje | <kbd>OK</kbd> | **pause** (pauza) |
| Slanje | <kbd>Back</kbd> | **stop** (zaustavi) |
| Pauzirano | <kbd>Back</kbd> | **resume** — nastavi slanje od mjesta gdje je stalo |
| Pauzirano | <kbd>OK</kbd> | **send 1**: pošalji samo trenutačno odabrani signal |
| Pauzirano | <kbd>←</kbd> / <kbd>→</kbd> (strelice) | **odaberi** prethodni / sljedeći signal u biblioteci |
| Pauzirano | <kbd>↓</kbd> | **save** — spremi odabrani signal |

## Pronalaženje točnog koda i spremanje

Pauziranje vam omogućuje da pronađete jedan kôd koji radi i sačuvate ga, kako bi sljedeći put tipka reagirala trenutačno.

1. Pokrenite univerzalnu tipku. Čim uređaj reagira, pritisnite <kbd>OK</kbd> (pauza). Brojač sada pokazuje na
   zadnji poslani signal.
2. Budući da nikada niste savršeno brzi, vratite se natrag lijevom strelicom i koristite **send 1** (<kbd>OK</kbd>) za svaki
   signal dok ne pronađete onaj koji pokreće uređaj. Desnom strelicom idete ponovno naprijed.
3. Pritisnite <kbd>↓</kbd> **save**. Zaglavlje izbornika prikazuje naziv tipke (npr. `Power`), što je ujedno i naziv pod kojim
   se signal sprema:
   - **Save as New Remote**: unesite naziv daljinskog upravljača pod **"Name the remote"**; u `/ext/infrared/` stvara se nova `.ir` datoteka;
   - **Add to Existing Remote**: odaberite postojeću `.ir` datoteku; signal se dodaje u nju.
4. **"Saved"** potvrđuje spremanje. Daljinski upravljač sada se nalazi u `Infrared → Saved Remotes`.

Ponovite za Vol_up, Mute i ostale tipke te ih dodajte u isti daljinski: tako dobivate osobni, trenutačno odzivni daljinski upravljač
izgrađen iz univerzalne biblioteke.

![Spremljeni daljinski upravljač na okomitom zaslonu: popis tipki Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## Iz naredbenog retka

Iste se biblioteke mogu reproducirati putem sučelja [CLI](/hr/dev/cli):

```text
ir universal list tv        # ispis naziva signala u tv.ir
ir universal tv Power       # slanje svakog "Power" signala iz tv.ir
```

`ir universal` bez argumenata ispisuje dostupne biblioteke (sve `.ir` datoteke u `/ext/infrared/assets/`).
Pritisnite <kbd>Ctrl</kbd>+<kbd>C</kbd> u terminalu za zaustavljanje.

## Rješavanje problema

| Problem | Što pokušati |
|---|---|
| *"Function requires SD card with fresh databases."* | Datoteke biblioteka nedostaju. Umetnite microSD karticu i ponovno instalirajte / ažurirajte firmver s umetnutom karticom, pogledajte [Ažuriranje](/hr/start/updating). |
| Ništa ne reagira nakon cijele biblioteke | Vaš model nije u biblioteci. [Naučite](/hr/infrared/read) originalni daljinski, isprobajte [biblioteku daljinskih upravljača u mobilnoj aplikaciji](/hr/infrared/mobile) i razmislite o [slanju svojih snimaka](/hr/infrared/captures). |
| Uređaj reagira, ali prekasno da biste pauzirali | Koristite lijevu strelicu + **send 1** da biste se vratili na pravi signal, pogledajte iznad. |
| Radi samo na vrlo maloj udaljenosti | Ugrađene LED diode preslabe su za velike prostorije. Upotrijebite [vanjski IR modul](/hr/infrared/external-ir). |
| Klima-uređaj se ne uključuje tipkom Off | Očekivano: Off ga samo isključuje. Koristite Cool/Heat/Dh za uključivanje. |

## Povezane stranice

- [Slanje snimljenih signala](/hr/infrared/captures): dodajte svoj uređaj u biblioteke
- [Format IR datoteka](/hr/infrared/file-format): format datoteka biblioteka
- [Učenje i slanje signala](/hr/infrared/read)
