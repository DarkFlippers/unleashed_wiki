---
title: Što Unleashed dodaje
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Što Unleashed dodaje

Unleashed se temelji na službenom firmveru (OFW) i ostaje **potpuno kompatibilan s njegovim API-jem i aplikacijama**. Sve što radi izvorni firmver i dalje radi. U nastavku su navedene izmjene i dodaci u odnosu na službeni firmver (OFW), razvrstani po područjima.

## Sub-GHz: radijska biblioteka i hardver

- **Uklonjena regionalna TX ograničenja.** Svaka frekvencija koju podržava čip CC1101 može odašiljati bez dodatnih koraka.
- **Dodatne frekvencije** na zadanom popisu i popis frekvencija koji korisnik može uređivati: [Frekvencije i predlošci](/hr/subghz/frequencies).
- **Neobavezni prošireni raspon frekvencija** izvan specifikacija čipa. Može oštetiti hardver: [Opasne postavke](/hr/start/dangerous-settings).
- **Velik skup dodatnih protokola**, uz mogućnost **spremanja i slanja mnogih sustava s promjenjivim kodom (rolling code)**: [Podržani sustavi](/hr/subghz/supported-systems), [Promjenjivi kodovi](/hr/subghz/rolling-codes), [KeeLoq](/hr/subghz/keeloq).
- Podrška za **vanjski modul CC1101** putem hardverskog SPI-ja, uz upravljanje pojačalom/LED-om: [Vanjski CC1101](/hr/subghz/external-cc1101).
- **Posebni načini brojača** za promjenjive kodove radi sprječavanja desinkronizacije: [Načini brojača](/hr/subghz/counter-mode).

## Sub-GHz: glavna aplikacija

- **Pamte se zadnje korištene postavke** (frekvencija, modulacija…).
- **Poboljšanja alata Frequency Analyzer**: osnovna funkcionalnost odgovara službenom firmveru, a Unleashed dodatno omogućuje da <kbd>OK</kbd> pošalje otkrivenu frekvenciju u Read te da dugo držanje <kbd>OK</kbd> odmah prijeđe na Read: [Frequency Analyzer](/hr/subghz/frequency-analyzer).
- **Poboljšanja značajke Read**: prikazuje kada je svaki signal primljen. Držite <kbd>→</kbd> na popisu za brisanje signala. Višesustavni protokoli prikazuju dekodirani naziv sustava (CAME, Nice FloR-S, FAAC SLH, KeeLoq): [Read](/hr/subghz/read).
- **Nazivi protokola u nazivima datoteka**: `Radio Settings → Protocol Names = ON` imenuje spremljene datoteke vremenskom oznakom i nazivom protokola.
- **Prilagođeni gumbi** za KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn i druge. Koristite tipke smjera na D-padu za slanje drugog koda gumba: [Korištenje kao daljinski upravljač](/hr/subghz/remote).
- **Prošireni `Add manually`**: jedan unos po sustavu, odabir pojasa, napredni način s TE, zaštitnim vremenom (guard time) i drugim poljima. Izradite daljinske upravljače FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo i druge te ih uparite s prijamnikom: [Add manually](/hr/subghz/add-manually), [Programiranje novog daljinskog upravljača](/hr/subghz/remote-prog).
- **Read RAW → More → Edit** otvara RAW datoteku izravno u alatu Sub-GHz RAW Edit: [RAW uređivač](/hr/subghz/raw-editor).
- **Filtri zanemarivanja** za šumne protokole (alarmi, senzori, zvonca, tražila ključeva, Feron rasvjeta…) i mogućnosti otklanjanja pogrešaka (korak uvećanja brojača, izlaz na debug pin): [Sub-GHz postavke](/hr/subghz/settings).

## Sub-GHz aplikacije

| Aplikacija | Što radi | Stranica |
|---|---|---|
| Sub-GHz Remote | Povežite do 5 `.sub` datoteka na tipke, uz ugrađeni konfigurator | [Remote](/hr/subghz/remote) |
| Sub-GHz Bruteforcer | Grubo pogađanje statičkog koda, prilagođene datoteke, odgoda i ponavljanja | [Bruteforce](/hr/subghz/bruteforce) |
| Remote Analyzer | Dekodira jedan po jedan daljinski upravljač, s ugrađenim analizatorom frekvencije | [Remote Analyzer](/hr/subghz/remote-analyzer) |
| Nice O-Code | Otkriva instalaterski kôd daljinskog upravljača Nice O-Code | [Nice O-Code](/hr/subghz/nice-o-code) |
| Security+ PIN | Pronalazi PIN tipkovnice signala Security+ 2.0 | [Security+ PIN](/hr/subghz/secplus-pin) |
| Seed Capturer | Prikuplja parove Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) za oporavak Seeda | [Seed Capturer](/hr/subghz/seed-capturer) |
| Sub-GHz RAW Edit | RAW uređivač na SD kartici: obrezivanje, izrezivanje/kopiranje/lijepljenje, povijest poništavanja, spajanje i dekodiranje | [RAW uređivač](/hr/subghz/raw-editor) |

## NFC, RFID i iButton

- **Dodatni MIFARE Classic ključevi** u sustavnom rječniku: [MIFARE Classic](/hr/nfc/mifare-classic). Upute za oporavak ključeva: [Nested i Fudan](/hr/nfc/nested-fudan), [MFKey](/hr/nfc/mfkey).
- **MFKey** na uređaju: [Aplikacija MFKey](/hr/nfc/mfkey-app).
- **EMV protokol i parser javnih podataka**: [Bankovne kartice (EMV)](/hr/nfc/emv).
- **NFC `Add manually` → MIFARE Classic s prilagođenim UID-om**: [Add manually](/hr/nfc/add-manually).
- **Mnogi dodatni parseri kartica** (prijevozne i gradske kartice: Troika, Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow Social Card i druge): [Podržane kartice](/hr/nfc/supported-cards).
- **NFC Magic 2.0** za magic kartice, uključujući Ultralight: [NFC Magic](/hr/nfc/nfc-magic).
- **Aplikacija T5577**: čitanje, uređivanje i pisanje blokova, brisanje ili uklanjanje lozinke, prisluškivač lozinke (`Sniff Password`): [Aplikacija T5577](/hr/rfid/t5577-app).
- Format prikaza **EM4100 DEZ 8**: [Čitanje RFID-a](/hr/rfid/read).
- **RFID i iButton fuzzers**: [RFID Fuzzer](/hr/rfid/fuzzer), [iButton Fuzzer](/hr/ibutton/fuzzer).

## Infrared

- Univerzalni daljinski upravljač za TV obnovljen je tako da pokriva **sve tipke**.
- **Velika zbirka univerzalnih daljinskih upravljača za projektore, ventilatore, klima-uređaje i audio uređaje** (soundbari…), koju tim redovito ažurira, provjerava i proširuje.
- Protokol **RCA** i podrška za vanjski IR modul (automatsko prepoznavanje): [Univerzalni daljinski upravljači](/hr/infrared/universal-remotes).
- Kako napraviti dobre snimke za uvrštavanje u bazu univerzalnih daljinskih upravljača: [IR snimke](/hr/infrared/captures).

## Bad USB i USB/Bluetooth

- **BadKB**: pokretanje Bad USB skripti putem **Bluetootha**, integrirano u aplikaciju Bad USB: [Bad USB](/hr/badusb/usage).
- **Rasporedi tipkovnice** i naredba `DUCKY_LANG` koja skripti omogućuje odabir vlastitog rasporeda: [Format skripte](/hr/badusb/script-format).

## Radna površina, postavke i poboljšanja korisničkog iskustva

- **Prilagođeni naziv Flippera** u **Settings → Desktop → Change Flipper Name**: [Prilagođeni naziv](/hr/start/custom-name).
- **Sat na radnoj površini** (`Settings → Desktop → Show Clock`) i **stilovi baterije** (`Battery View`: Bar, %, Inv. %, Retro 3, Retro 5, Bar %): [Radna površina](/hr/start/desktop).
- **Zaključavanje držanjem <kbd>↑</kbd>** na radnoj površini: uz PIN ako je postavljen, inače obično zaključavanje.
- **Više igara u načinu Dummy Mode**: svaka strelica (kratki i dugi pritisak) i <kbd>OK</kbd> mogu pokrenuti vlastitu aplikaciju.
- Podrška za **[RGB backlight mod](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** u **LCD and Notifications → RGB Mod Settings** (samo za hardverski modificirane Flippere).
- **Kursor za unos teksta** i **mini-uređivač za unos bajtova** (uzastopno pritišćite <kbd>↑</kbd> dok se ne pojavi uređivač polubajtova).
- **Archive** s dodatnim karticama (SubRem za mape aplikacije Sub-GHz Remote, Phone za imenik SIM800).

Sve stavke izbornika Settings opisane su na stranici [Postavke](/hr/start/settings).

## Ugrađene aplikacije {#built-in-apps}

Te se aplikacije prevode iz repozitorija firmvera i instaliraju u `/ext/apps/` pri svakom ažuriranju, u **svakoj** varijanti izdanja (`e`, bez sufiksa, `c`). Paketi aplikacija ih ne sadrže, pa paket nikada ne može prebrisati ili vratiti stariju verziju tih aplikacija.

**U glavnom izborniku:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (s BadKB-om), U2F, **Clock** (kontrole svjetline, alarm, mjerač vremena), **Sub-GHz Remote**. Sub-GHz, Archive i Settings dio su binarne datoteke firmvera.

**U Apps:**

| Aplikacija | Kategorija | Stranica |
|---|---|---|
| MFKey | NFC | [Aplikacija MFKey](/hr/nfc/mfkey-app) |
| T5577 | RFID | [Aplikacija T5577](/hr/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | pogledajte gornju tablicu |
| SIM800 (pozivi, SMS, imenik, USSD, AT terminal) | GPIO | [SIM800](/hr/gpio/sim800) |
| FindMy Flipper (Apple FindMy / Google Find My Device beacon) | Bluetooth | [Katalog aplikacija](/hr/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Kontroleri](/hr/apps/controllers) |
| Snake Game | Games | — |

## Paketi aplikacija zajednice

- **Base pack** (u izdanjima bez sufiksa i `e`) i **Extra pack** (samo `e`): izvorni kôd i cijeli popis na [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Najnoviji paketi nalaze se na [GitHub releases](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Službeni katalog također radi: [lab.flipper.net/apps](https://lab.flipper.net/apps) ili mobilna aplikacija.
- Više: [Katalog aplikacija](/hr/apps/catalog), [Aplikacije na SD kartici](/hr/apps/sd-card-apps).

## Prateće aplikacije i web-alati

- **qUnleashed**: prateća aplikacija za telefon i računalo: [Aplikacija qUnleashed](/hr/mobile/qunleashed-app).
- **Web-alati**: [Web Installer](https://web.unleashedflip.com), Sub-GHz karta ([map.unleashedflip.com](https://map.unleashedflip.com)), Wi-Fi wardriving karta ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), ESP32 web flasher ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)): [Web-alati](/hr/mobile/web-tools).
