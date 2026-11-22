---
title: microSD kartica
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# microSD kartica

microSD kartica nije neobavezna. Na njoj se nalaze vaši spremljeni ključevi, kartice i daljinski upravljači, sve `.fap` aplikacije (uključujući
ugrađene Unleashed aplikacije), baze podataka, paket za ažuriranje te, u trenutnom firmveru, čak i **unutarnja pohrana**.

## Odabir kartice

- **Kapacitet:** 16–32 GB je sasvim dovoljno. Podržano je do 256 GB, ali se veće kartice sporije montiraju.
- **Datotečni sustav:** FAT12, FAT16, FAT32 ili exFAT.
- **Kvaliteta:** koristite **markiranu** karticu (SanDisk, Kingston…). Flipper s karticom komunicira putem **SPI** sučelja, a ne brzog
  SDIO načina rada koji koriste telefoni i računala. Ne snalazi se svaka kartica dobro sa SPI-jem, čak i ako u drugim uređajima radi bez problema. Loša kartica
  usporava Flipper, može brže prazniti bateriju (do ~50 mA umjesto ~30 mA) i može oštetiti podatke.
- Brzina čitanja putem SPI-ja doseže gotovo 600 KiB/s, što je dovoljno za sve što Flipper radi.

## Umetanje

1. Utor se nalazi na donjoj strani Flippera.
2. Držite karticu **kontaktima okrenutim prema gore** i gurnite je unutra dok ne škljocne.
3. U statusnoj traci pojavljuje se ikona SD kartice.

## Ako kartica nije prepoznata

Pojavljuje se poruka o SD kartici ili je ikona na statusnoj traci prekrižena. Mogući uzroci:

| Uzrok | Rješenje |
|---|---|
| Pogrešan ili nepostojeći datotečni sustav | Formatirajte karticu (u nastavku) |
| Prašina u utoru | Pažljivo ga očistite komprimiranim zrakom |
| Kartica ne podržava SPI | Upotrijebite drugu karticu |
| Kartica je oštećena | Upotrijebite drugu karticu |

## Settings → Storage

**Main Menu → Settings → Storage**

| Stavka | Što radi |
|---|---|
| **About Internal Storage** | Naziv, vrsta `Virtual (/.int on SD)`, ukupni i slobodni prostor, slobodni flash |
| **About SD Card** | Oznaka, vrsta datotečnog sustava, ukupni i slobodni prostor, proizvođač i serijski broj |
| **Unmount SD Card** / **Mount SD Card** | Sigurno demontirajte prije vađenja ili ponovno montirajte. Montiranje može nakratko prekinuti napajanje vanjskih modula |
| **Format SD Card** | Formatira karticu. **Svi podaci bit će izgubljeni!** |
| **Benchmark SD Card** | Testira brzinu pisanja/čitanja u SPI načinu rada |
| **Factory Reset** | Briše unutarnju pohranu (postavke, uparivanja, dupina). Pogledajte [Oporavak](/hr/start/recovery#factory-reset) |

### Formatiranje

1. **Settings → Storage → Format SD Card**.
2. Potvrdite tipkom <kbd>→</kbd> **Format**.
3. Pričekajte `Formatted`, zatim pritisnite **Finish**.

Ako formatiranje na Flipperu ne uspije (`Cannot Format SD Card`), formatirajte karticu na računalu kao FAT32/exFAT ili isprobajte drugu karticu.

### Sigurno uklanjanje

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. Kada vidite `SD Card Unmounted` / `You can remove SD card now.`, pritisnite karticu kako biste je otpustili i izvucite je.

Vađenje kartice dok Flipper zapisuje na nju može oštetiti datoteke ili datotečni sustav.

### Testiranje brzine (Benchmark)

Test brzine zapisuje testnu datoteku `/ext/rwfiletest.bin` i prikazuje retke poput `4096b : W 300K R 600K`: veličina bloka, zatim
brzina pisanja i čitanja u KiB/s. Kartica bi trebala pisati **najmanje ~260 KiB/s** za normalan rad. Rezultati se razlikuju od
testova na računalu jer se test izvodi u SPI načinu rada. Pokrenite ga nekoliko puta kako biste dobili realnu sliku.

## Raspored mapa

`/ext` je korijenska mapa kartice. Glavne mape:

| Mapa | Sadržaj |
|---|---|
| `/ext/subghz/` | Sub-GHz `.sub` datoteke. `assets/` sadrži `dangerous_settings`, `setting_user.example` (predložak za vlastiti popis frekvencija) te KeeLoq bazu ključeva `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Mape za Sub-GHz Remote |
| `/ext/nfc/` | NFC `.nfc` datoteke. `assets/` sadrži rječnike ključeva |
| `/ext/lfrfid/` | 125 kHz RFID `.rfid` datoteke |
| `/ext/ibutton/` | iButton `.ibtn` datoteke |
| `/ext/infrared/` | IR `.ir` daljinski upravljači. `assets/` sadrži biblioteke univerzalnih daljinskih upravljača |
| `/ext/badusb/` | Bad USB skripte (`.txt`). `assets/layouts/` sadrži rasporede tipkovnice (`.kl`) |
| `/ext/apps/` | `.fap` aplikacije po kategorijama (ugrađene aplikacije i paketi aplikacija) |
| `/ext/apps_data/` | Podaci i postavke aplikacija |
| `/ext/dolphin/` | `name.settings` (prilagođeni naziv) i animacije |
| `/ext/update/` | Raspakirani paketi za ažuriranje |
| `/ext/.int/` | Pozadinska pohrana za unutarnju pohranu (`/int`). Nemojte je ručno uređivati |

::: tip
Povremeno napravite sigurnosnu kopiju cijele kartice (qFlipper može preuzeti datoteke, ili ih kopirajte na računalu). Vaši ključevi i daljinski upravljači
postoje samo na kartici.
:::

## macOS: skrivene datoteke i sortiranje {#macos-hidden-files-and-sorting}

macOS na kartici ostavlja datoteke `._*` i `.DS_Store`. Očistite ih:

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Zamijenite `Flipper\ SD` nazivom svoje kartice.

Preglednik datoteka brže ispisuje datoteke kada je FAT mapa sortirana. Na macOS-u (pomoću alata [Homebrew](https://brew.sh)):

```bash
brew install fatsort
diskutil list                         # pronađite karticu, npr. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # upotrijebite vlastiti ID diska
```

`fatsort` je također dostupan na Linuxu.

## Povezano

- Što preživljava ažuriranje: [Ažuriranje](/hr/start/updating)
- Formati datoteka: [Sub-GHz](/hr/subghz/file-format), [NFC](/hr/nfc/file-format), [RFID](/hr/rfid/file-format),
  [Infracrveno](/hr/infrared/file-format), [iButton](/hr/ibutton/file-format)
