---
title: Aplikacije uključene u Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Aplikacije uključene u Unleashed

Instalacija firmvera Unleashed sastoji se od tri sloja aplikacija:

1. **Sustavne (ugrađene) aplikacije.** Grade se iz repozitorija firmvera i instaliraju sa svakim ažuriranjem firmvera,
   bez obzira na to koju varijantu izdanja odaberete.
2. **Paket Base Apps.** Skup aplikacija zajednice, unaprijed instaliran u zadanom izdanju.
3. **Paket Extra Apps.** Mnogo veći skup aplikacija zajednice, unaprijed instaliran samo u izdanju `e`.

Povrh toga možete sami instalirati bilo koju drugu aplikaciju; pogledajte [Aplikacije na SD kartici](/hr/apps/sd-card-apps).

## Varijante izdanja {#build-variants}

Datoteke izdanja nazivaju se `flipper-z-f7-update-(version)(e / c).tgz`:

| Dio | Značenje |
|---|---|
| `flipper-z` | za Flipper Zero |
| `f7` | hardverski cilj, jednak za svaki Flipper Zero |
| `update` | paket za ažuriranje: program za ažuriranje, resursi (aplikacije, IR biblioteke itd.) i sam firmver |
| `(version)` | verzija firmvera |
| sufiks | koji su paketi aplikacija uključeni (dolje) |

| Sufiks | Base Apps | Extra Apps |
|---|:---:|:---:|
| nema (` `) | da | ne |
| `c` | ne | ne |
| `e` | da | da |

- **` ` (bez slova)** je zadana varijanta: firmver, sustavne aplikacije i paket Base.
- **`c`**: samo firmver i sustavne aplikacije, bez paketa aplikacija. Odaberite je ako želite sami sastaviti vlastiti skup aplikacija.
- **`e`**: firmver, sustavne aplikacije, paket Base i paket Extra.

Preporučeni način za instalaciju bilo koje od ovih varijanti jest [Web Installer](/hr/mobile/web-tools); pogledajte i
[Instalacija firmvera Unleashed](/hr/start/install).

::: tip Unleashed
Ugrađene aplikacije **nisu** dio paketa Base ni Extra. Ažuriranje firmvera zapisuje ih u mapu `apps/` na
SD kartici, tako da instaliranje paketa aplikacija nikada ne može prepisati sustavnu aplikaciju niti je vratiti na stariju verziju.
:::

## Sustavne aplikacije: prikazane u glavnom izborniku

| Aplikacija | Što radi | Autor / podrijetlo |
|---|---|---|
| GPIO | Upravljanje GPIO pinovima, USB-UART most i 1-Wire/iButton alati | OFW |
| iButton | Čitanje, spremanje i emulacija Dallas / Cyfral / Metakom ključeva | OFW |
| Infrared | Učenje, spremanje i slanje IR signala, univerzalni daljinski upravljači | OFW |
| NFC | Čitanje, spremanje, emulacija i raščlanjivanje NFC kartica | OFW |
| 125 kHz RFID | Čitanje, spremanje, emulacija i pisanje LF RFID oznaka | OFW |
| Bad USB | Izvršavanje Ducky Script skripti preko USB-a i BadKB preko Bluetootha | OFW + BadKB (Willy-JL, ClaraCrazy i suradnici XFW-a) |
| U2F | Sigurnosni token FIDO U2F preko USB-a, pogledajte [U2F](/hr/apps/u2f) | OFW |
| Clock | Sat s kontrolom svjetline zaslona, alarmom i osnovnim mjeračem vremena, pogledajte [Clock](/hr/apps/clock) | @nymda, uz @Willy-JL, @mishamyte i @xMasterX |
| Sub-GHz Remote | Dodjeljivanje do 5 spremljenih `.sub` datoteka tipkama i njihovo slanje, pogledajte [Sub-GHz Remote](/hr/subghz/remote) | @gid9798 i @xMasterX |

Sub-GHz, Archive, Settings i sustavni servisi prevedeni su izravno u binarnu datoteku firmvera.

## Sustavne aplikacije: u mapi Apps

Ovo su `.fap` datoteke pod `Main Menu → Apps`, razvrstane u mape po kategorijama.

| Aplikacija | Mapa | Što radi | Autor / podrijetlo |
|---|---|---|---|
| MFKey | NFC | Oporavak MIFARE Classic ključeva iz nonce vrijednosti prikupljenih pomoću Detect Reader, pogledajte [aplikaciju MFKey](/hr/nfc/mfkey-app) | @noproto |
| T5577 | RFID | Čitanje, uređivanje i pisanje T5577 blokova, brisanje ili uklanjanje lozinke, prisluškivanje lozinke, pogledajte [aplikaciju T5577](/hr/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | Oporavak instalaterskog koda daljinskog upravljača Nice O-Code i spremanje kao `.sub`, pogledajte [Nice O-Code](/hr/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | Pronalaženje PIN-a tipkovnice u snimljenom Security+ 2.0 signalu, pogledajte [Security+ PIN](/hr/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | Prikupljanje parova Fix + Hop s daljinskih upravljača FAAC SLH, Genius, Erreka i BFT Mitto za izvanmrežni oporavak Seed vrijednosti, pogledajte [Seed Capturer](/hr/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | Dekodiranje jednog po jednog daljinskog upravljača na unutarnjem čipu CC1101, uz ugrađeni analizator frekvencija, pogledajte [Remote Analyzer](/hr/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | Otvaranje RAW `.sub` snimke, pronalaženje signala, skraćivanje, spajanje i dekodiranje, pogledajte [RAW editor](/hr/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | Upravljanje GSM modulom SIM800C/SIM800L: pozivi, SMS, imenik, USSD, DTMF, AT terminal, pogledajte [SIM800](/hr/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | BLE lokacijski odašiljač za Apple Find My / Google Find My Device i druge mreže, pogledajte [FindMy Flipper](/hr/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | HID daljinski upravljač preko USB-a, pogledajte [HID daljinski upravljač](/hr/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | HID daljinski upravljač preko Bluetootha, pogledajte [HID daljinski upravljač](/hr/apps/hid-remote) | OFW |
| Snake Game | Games | Igra Zmija, pogledajte [Snake](/hr/apps/snake) | OFW |

Firmver također sadrži **stilove glavnog izbornika** — male dodatke koje birate u `Settings → Desktop → Menu Style`,
pogledajte [Stilovi glavnog izbornika](/hr/apps/menu-styles), te JavaScript pokretač za `.js` skripte (pogledajte [JavaScript](/hr/dev/js-about)).

::: info Nedavne promjene
Od izdanja od 20. studenoga 2026., Sub-GHz RAW Edit isporučuje se s firmverom i više nije dio paketa Extra, a
SIM800 je nova ugrađena aplikacija (`Apps → GPIO → SIM800`).
:::

## Paketi Base i Extra {#base-and-extra-packs}

Aplikacije zajednice prikuplja @xMasterX u repozitoriju
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): taj repozitorij sadrži potpuni popis
i izvorni kôd, a njegova stranica [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) nudi pakete Base i
Extra kao zasebna preuzimanja, u slučaju da želite dodati paket na `c` izdanje ili ažurirati aplikacije između izdanja
firmvera.

Za ručno dodavanje paketa: preuzmite `.zip` sa [stranice izdanja](https://github.com/xMasterX/all-the-plugins/releases/latest), raspakirajte ga i kopirajte mape aplikacija u
mapu `apps` na SD kartici (`/ext/apps/`). API verzija paketa mora odgovarati verziji firmvera (`Current API:`
na vrhu svakog popisa promjena).

Aplikacije na koje upućuje Unleashed ReadMe (svaka se nalazi u jednom od paketa):

| Aplikacija | Gdje pročitati više |
|---|---|
| TOTP (Authenticator) | [opis konfiguracijske datoteke](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/hr/apps/barcode) |
| Multi Converter | [Multi Converter](/hr/apps/multi-converter) |
| WAV Player | [primjeri datoteka i kako ih pretvoriti](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [skripta za generiranje](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Sub-GHz bruteforce](/hr/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [RFID fuzzer](/hr/rfid/fuzzer), [iButton fuzzer](/hr/ibutton/fuzzer) |
| Unitemp (senzori temperature) | [kako koristiti i podržani senzori](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [kako koristiti](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [kako koristiti](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| NRF24 aplikacije | [NRF24](/hr/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 i Wi-Fi moduli](/hr/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/hr/apps/sentry-safe) |

::: warning
Sadržaj paketa mijenja se između izdanja. Oznaka izdanja trenutačnih paketa ispisana je na vrhu svakog
popisa promjena za Unleashed (na primjer `Apps: Build tag (20nov2026)`), s poveznicom na najnovije izmjene aplikacija.
:::

## Službeni katalog

Službeni katalog aplikacija za Flipper Zero dostupan je u [Flipper Labu](https://lab.flipper.net/apps) i u
[mobilnoj aplikaciji Flipper](/hr/mobile/mobile-app). Instalacija iz njega opisana je u
[Aplikacije na SD kartici](/hr/apps/sd-card-apps#installing-from-the-official-catalog).

## Povezane stranice

- [Aplikacije na SD kartici (.fap)](/hr/apps/sd-card-apps)
- [Rješavanje problema s aplikacijama](/hr/apps/troubleshoot)
- [Instalacija firmvera Unleashed](/hr/start/install)
