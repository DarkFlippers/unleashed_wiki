---
title: Integracijsko testiranje
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Integracijsko testiranje

Uz [jedinične testove](/hr/dev/unit-tests), firmver ima i **plan ručnog integracijskog testiranja**: testne slučajeve korak po korak
grupirane po podsustavima, pri čemu svaki ima očekivani rezultat. Plan je pisan za održavatelje repozitorija, ali je jednako
koristan ako sami gradite firmver i želite ga provjeriti prije korištenja ili dijeljenja.

Ova stranica sažima taj plan. Cjeloviti popisi koraka nalaze se u repozitoriju Unleashed pod
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Što i kada testirati

- **Testirajte ono što je promijenjeno, plus povezane regresije.** Testirajte novo ponašanje i ponovno pokrenite nekoliko postojećih
  slučajeva istog podsustava. Primjer: kada dodajete Sub-GHz protokol, testirajte njega i nekoliko postojećih protokola.
- **Preskočite nepovezane podsustave.** Nema potrebe testirati NFC kada se mijenjao samo Sub-GHz.
- **Testirajte sve kod promjena jezgre** — ako se promijenilo nešto globalno, pokrenite sve slučajeve redom.

Kada: **prije prihvaćanja pull zahtjeva** i **prije izdanja kandidata za objavu (release candidate)**.

## Zajednički obrazac testiranja za ključeve i kartice

Testni slučajevi za RFID, iButton i NFC protokole koriste iste "zajedničke korake":

1. **Čitanje** originala — podaci odgovaraju originalu.
2. **Emulacija** — pročitajte emulirani ključ drugim Flipperom; podaci su identični.
3. **Spremanje** — spremljeno pod zadanim nazivom; prikaz prelazi u mapu *Saved*.
4. **Pisanje** na praznu oznaku — prikazuje se ekran uspjeha.
5. **Čitanje zapisane** prazne oznake — podaci su identični spremljenom ključu.

Mnogi slučajevi stoga zahtijevaju **drugi Flipper**, stvarne čitače i prazne oznake (T5577, RW2004/RW1990 itd.).

## Testni slučajevi po podsustavima

### Općenito (35 slučajeva)

| Područje | Što se provjerava |
|---|---|
| BLE | Bluetooth uključen nakon ponovnog pokretanja; uparivanje s mobilnom aplikacijom, ispravan naziv Flippera; ponovno uparivanje s drugim telefonom |
| U2F | Registracija i autentifikacija ključa na Yubico WebAuthn demo stranici |
| Postavke | PIN kôd, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Arhiva i preglednik datoteka | SD kartica s mnogo datoteka: <kbd>↓</kbd> na radnoj površini otvara Archive; svaka kartica (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) prikazuje svoje datoteke; pokretanje, preimenovanje, brisanje ključeva |
| Kartice i protokoli | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Tvorničko ažuriranje | Putem qFlippera na sustavima macOS, Windows 11, Ubuntu; putem Android i iOS aplikacija; putem weba u Flipper Labu |
| Postavljanje regije | Istih šest kanala kao kod tvorničkog ažuriranja, plus sama postavka regije |
| Aplikacije | Osnovne aplikacije, JS skripte, izbornik na tipki Gore |
| Usklađenost | Svi zasloni o sukladnosti prikazuju se ispravno |

### CLI (3 slučaja)

- **Naredbe upravljanja:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1` pali
  LED na razvojnoj ploči), `led b 255`, `vibro 1` / `vibro 0`.
- **Informativne naredbe:** povezivanje putem `minicom -D /dev/ttyACM0 -b 230400` ili PuTTY-ja; `log debug` tijekom korištenja
  uređaja, prekid pomoću <kbd>Ctrl</kbd>+<kbd>C</kbd>; usporedba `device_info` / `!` sa zaslonom informacija o firmveru (držite
  <kbd>↓</kbd> na radnoj površini 3 s); `bt hci_info`; `date`; `help` / `?`; `free`; `free_blocks`.
- **Naredbe pohrane:** `storage info /ext`, `storage format /ext` (odbijte, pa potvrdite), informacije s karticom i bez
  nje; `factory_reset` — odgovor `n` ne radi ništa, `y` briše postavke, ali **zadržava podatke na SD kartici i vrijeme**.

Referentne vrijednosti za `bt hci_info` u planu:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 slučajeva)

| Slučaj | Ključne provjere |
|---|---|
| Read RAW | Snimanje na 315, 433, 868 MHz, uključujući kriptirani (promjenjivi) daljinski upravljač poput Came Atomo; ponovno slanje prijamnicima ispitnog stola |
| Frequency Analyzer | Prikazuje ispravnu frekvenciju različitih daljinskih upravljača |
| Vanjski modul | Vanjski CC1101 (433,92 MHz modul): ikona se mijenja u vanjsku, Read RAW signal jači od unutarnjeg; povratak na unutarnji radi. Nikada ne odspajajte modul dok je u upotrebi — Flipper se može smrznuti |
| Spremljene datoteke | Spremanje dekodiranih i RAW signala, dodavanje u favorite i slanje iz njih, preimenovanje (ostaje u favoritima), brisanje |
| Prijam / odašiljanje | Čitanje na 315.000, 433.920 i 868.350 MHz, zatim s uključenim skakanjem frekvencija (hopping); slanje spremljenih ključeva — releji na ispitnom stolu (ili drugi Flipper) reagiraju |
| Add Manually | Ručno stvaranje signala |

### NFC (7 slučajeva)

| Slučaj | Ključne provjere |
|---|---|
| Otključavanje NTAG/Ultralight | *Auth as* oba tipa, upozorenje za pogrešan tip kartice, ručni unos lozinke; spremljene kartice pojavljuju se u *Saved* nakon ~1,5 s |
| Detect Reader | Prikupljanje jednokratnih vrijednosti (nonce) s čitača (npr. drugog Flippera), zatim je QR kôd na zaslonu nakon <kbd>OK</kbd> čitljiv |
| Emulacija | Čitljivo na nekoliko čitača, uključujući Flipper na 10 mm i Proxmark |
| Čitanje | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, EMV bankovne kartice |
| Vremensko usklađivanje | Usporedba vremena emulacije za Ultralight i Classic s referencom pomoću Proxmarka 3 |
| Add Manually | Stvaranje i spremanje kartica svih tipova, zatim njihova emulacija |
| Dodatne radnje | *Read Specific Card Type*, *MIFARE Classic Keys* (dodavanje/brisanje ključeva, tipka *List*), *Unlock SLIX* pomoću lozinke |

Proxmark naredbe korištene za test vremenskog usklađivanja:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### 125 kHz RFID (9 slučajeva)

Testni slučajevi protokola sa zajedničkim koracima za **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass), Indala26,
Troyka/Podorozhnik**, plus čitanje, pisanje na **T5577**, Add Manually i emulacija.

### iButton (9 slučajeva)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom**: čitanje, spremanje, Add Manually, emulacija (čitanje na
različitim uređajima), pisanje na praznu oznaku **RW2004** i ponovno čitanje, uređivanje i brisanje ključeva.

### Infracrveno (3 slučaja)

- **Univerzalna biblioteka** — daljinski upravljači za TV, audio, klima-uređaje: uključivanje i ostale funkcije rade.
- **Učenje novog daljinskog upravljača** — dodavanje/brisanje daljinskih upravljača i tipki, preimenovanje, slanje uređenih tipki.
- **Spremljeni daljinski upravljači** — dodavanje tipki postojećem daljinskom upravljaču, upravljanje uređajima s udaljenosti od **najmanje 5 m**, brisanje svih tipki
  i daljinskih upravljača.

### Bad USB (2 slučaja)

Na sustavima macOS i Windows: prikazuje se popis skripti; demo skripta se izvršava s EN rasporedom i nakon promjene rasporeda;
skripta za preuzimanje qFlippera otvara terminal i preuzima qFlipper; prebacivanje u **BLE** način rada (uključen Bluetooth)
uparuje se s računalom i skripta se ponovno izvršava.

### GPIO (1 slučaj)

`GPIO → Manual Control` s umetnutom ST-Link razvojnom pločom: LED diode prate pinove; uključivanje 5 V pali LED diode napajanja.

### GoodFAPs — službene aplikacije (10 slučajeva)

| Aplikacija | Ključne provjere |
|---|---|
| PicoPass | Čitanje kartice, spremanje, pokreće se *Elite Dictionary Attack* |
| Weather Station | Čita meteorološku stanicu koju simulira drugi Flipper na različitim frekvencijama |
| Aplikacije iz kataloga | Instalacija putem mobilne aplikacije ili weba, ispravna ikona i naziv, pokretanje/izlaz, ažuriranje, deinstalacija (aplikacija, web, preglednik datoteka) |
| AVR Flasher | Izvoz AVR memorije, programiranje AVR-a, ISP programator s `avrdude` |
| Video Game Module | Umetanje modula → poruka inicijalizacije i ikona na statusnoj traci; HDMI zrcali zaslon; "Air Arkanoid" koristi akcelerometar |
| Tools | Clock (cijeli zaslon, format iz postavki); NFC/RFID Detector detektira obje vrste polja |
| Signal Generator | PWM i Clock generatori na različitim pinovima, frekvencijama i djeliteljima |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (s upozorenjem na rizik), *Wipe* |
| SPI Mem Manager | Čitanje, pisanje i brisanje SPI flash čipa |
| Programiranje VGM-a | Aplikacija VGM Tool: *Install official firmware*, instalacija iz datoteke na SD kartici i ručni način (tipka Boot + USB masovna pohrana) |

Ožičenje za AVR Flasher korišteno u planu:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Provjera očitavanja fuse bitova (zamijenite `m2560` svojim čipom, npr. `m328p`, i COM priključak):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
Plan potječe iz službenog firmvera. Na Unleashedu također isprobajte dodatke svojstvene Unleashedu u podsustavu
koji ste mijenjali — primjerice dodatne Sub-GHz protokole i [način rada brojača](/hr/subghz/counter-mode), ili dodatne aplikacije u
`applications/system/` (Remote Analyzer, Nice-O-Code, Sec+ PIN, Seed Capturer, Sub-GHz RAW editor, T5577, SIM800…).
:::

## Povezane stranice

- [Jedinični testovi](/hr/dev/unit-tests)
- [Sučelje naredbenog retka](/hr/dev/cli)
- [Izgradnja firmvera](/hr/dev/build)
