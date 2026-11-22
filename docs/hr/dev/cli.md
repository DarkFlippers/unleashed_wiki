---
title: "Sučelje naredbenog retka (CLI)"
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Sučelje naredbenog retka (CLI)

Flipper pruža tekstualnu konzolu putem USB serijske veze. Iz nje možete čitati i slati signale, pokretati aplikacije, upravljati datotekama, pratiti zapisnike, upravljati GPIO pinovima i LED diodama, dopisivati se s drugim Flipperima putem Sub-GHz veze i još mnogo toga — korisno za pisanje skripti, otklanjanje pogrešaka i razvoj aplikacija.

## Povezivanje na CLI

::: warning Najprije zatvorite qFlipper
Samo jedan program može istovremeno koristiti serijski priključak Flippera. Zatvorite **qFlipper** (i zatvorite Flipper Lab ili druge terminale) prije povezivanja.
:::

Brzina serijske veze iznosi **230400** bauda (za USB CDC ta se vrijednost uglavnom zanemaruje, no neki je terminali zahtijevaju).

### Opcija 1: Flipper Lab (preglednik)

Radi u preglednicima Chrome, Edge ili drugom Chromium pregledniku s podrškom za Web Serial.

1. Povežite Flipper putem USB-a.
2. Otvorite [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Opcija 2: Web serijski terminal (preglednik)

1. Povežite Flipper putem USB-a i otvorite Chromium preglednik.
2. Otvorite [web serijski terminal](https://googlechromelabs.github.io/serial-terminal/).
3. Postavite **Baud rate** na **230400**, kliknite **Connect**, odaberite svoj Flipper i kliknite **Connect**.

### Opcija 3: Serijski terminal — macOS

1. Pronađite priključak:

   ```sh
   ls /dev/cu.*
   ```

   Flipper se pojavljuje kao `/dev/cu.usbmodemflip_NAME`, gdje je `NAME` ime vašeg Flippera.
2. Povežite se pomoću programa **screen**:

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Izlaz: <kbd>Ctrl</kbd>+<kbd>A</kbd>, zatim <kbd>K</kbd>, zatim <kbd>Y</kbd>.
3. …ili pomoću programa **minicom** (instalacija putem [Homebrew](https://brew.sh/): `brew install minicom`):

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Izlaz: <kbd>Esc</kbd>+<kbd>Z</kbd>, zatim <kbd>X</kbd>, zatim <kbd>Return</kbd>.

### Opcija 3: Serijski terminal — Linux

1. Pronađite priključak:

   ```sh
   ls /dev/serial/by-id/
   ```

   Potražite `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Ako imate samo jedan serijski uređaj, obično je dostupan i kao `/dev/ttyACM0`; qFlipper također prikazuje naziv priključka.
2. Povežite se:

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # ili
   minicom -D /dev/ttyACM0
   ```

   Izlaz iz programa screen: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Izlaz iz programa minicom: <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Ako na Linuxu dobijete poruku "permission denied", dodajte svog korisnika u grupu `dialout` (ili `uucp` na nekim distribucijama) i ponovno se prijavite.
:::

### Opcija 3: Serijski terminal — Windows

1. Instalirajte [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Povežite Flipper; u **Device Manager → Ports (COM & LPT)** zabilježite njegov COM priključak (odspojite i ponovno spojite kabel kako biste vidjeli koji se pojavljuje).
3. U programu PuTTY odaberite **Connection type: Serial**, **Serial line**: npr. `COM3`, **Speed**: `230400` i kliknite **Open**.

### Iz izvornog koda firmvera

Ako imate izvorni kod firmvera, `./fbt cli` izravno otvara CLI sesiju; uz uFBT koristite `ufbt cli`.

**Očekivani rezultat:** ASCII natpis Flippera, "Welcome to Flipper Zero Command Line Interface!", redak s verzijom firmvera i odzivnik `>:`.

## Ugrađene i vanjske naredbe

Pokrenite `help` ili `?` za popis naredbi dostupnih na vašem uređaju.

::: tip Unleashed / nova CLI arhitektura
Većina radio i perifernih naredbi (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`, `crypto`, `js`, `gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) su **vanjski CLI dodaci** koji se učitavaju iz mape na SD kartici `/ext/apps_data/cli/plugins` (datoteke s prefiksom `cli_`). Bez SD kartice — ili s oštećenom karticom — ostaju samo osnovne naredbe. Nakon kopiranja ili ažuriranja dodataka pokrenite `reload_ext_cmds` umjesto ponovnog pokretanja uređaja.
:::

### Pregled naredbi

| Naredba | Opis |
|---|---|
| `!` | Pseudonim za `info device` |
| `?`, `help` | Popis dostupnih naredbi |
| `bt` | Alat za testiranje radijske jezgre (BLE) — HCI verzija i, u načinu za otklanjanje pogrešaka, testovi nositelja/paketa |
| `buzzer` | Reproducira ton ili notu na piezo zvučniku |
| `crypto` | Pohrana ključeva u sigurnosnu enklavu te AES šifriranje/dešifriranje |
| `date` | Prikaz / postavljanje datuma i vremena |
| `device_info` | Pseudonim za `info device` (zastarjelo) |
| `echo` | Vraća primljene bajtove u izvornom obliku (za testiranje performansi); zaustavlja se s <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Izlaz iz ljuske (korisno u podljuskama poput `nfc`) |
| `factory_reset` | Vraćanje na tvorničke postavke; podatci na microSD kartici ostaju sačuvani |
| `free` | Podatci o alokatoru gomile — opće profiliranje memorije |
| `free_blocks` | Slobodni blokovi gomile i njihove veličine — procjena fragmentacije |
| `gpio` | Postavljanje načina rada / zapisivanje / čitanje GPIO pinova |
| `i2c` | Skeniranje I2C sabirnice u potrazi za uređajima |
| `ikey` | Čitanje, emulacija i zapisivanje iButton ključeva |
| `info` | Detaljni podatci o uređaju i napajanju |
| `input` | Prikaz događaja tipki, simulacija pritisaka tipki |
| `ir` | Primanje, slanje i dekodiranje infracrvenih signala; univerzalni daljinski upravljači |
| `js` | Pokretanje JavaScript datoteke, ispis konzole ide u CLI |
| `led` | Upravljanje RGB LED diodom i pozadinskim osvjetljenjem zaslona |
| `loader` | Popis, otvaranje i zatvaranje aplikacija |
| `log` | Pregled zapisnika sustava |
| `neofetch` | Podatci o sustavu, slično alatu `neofetch` na Linuxu |
| `nfc` | NFC podljuska: dump, emulacija, raw, APDU, skener |
| `onewire` | Skeniranje 1-Wire sabirnice (iButton pinovi) |
| `power` | Isključivanje, ponovno pokretanje, pokretanje u DFU način, GPIO 5 V / 3.3 V |
| `reload_ext_cmds` | Ponovno učitavanje popisa vanjskih naredbi sa SD kartice |
| `rfid` | Čitanje, zapisivanje, emulacija 125 kHz kartica; RAW alati |
| `sleep` | Čekanje zadano vrijeme, npr. `sleep 5s` (korisno u skriptama) |
| `start_rpc_session` | Prebacivanje CLI-ja u protobuf RPC način (koriste ga qFlipper/aplikacije; obično nije potrebno) |
| `storage` | Naredbe datotečnog sustava |
| `subghz` | Sub-GHz alati: rx/tx, RAW, dekodiranje, razgovor |
| `sysctl` | Postavke sustava: način za otklanjanje pogrešaka, praćenje gomile |
| `top` | Popis niti u stvarnom vremenu (poput Linuxovog `top`); <kbd>Ctrl</kbd>+<kbd>C</kbd> za izlaz |
| `update` | Instalacija paketa ažuriranja, sigurnosna kopija / vraćanje unutarnje pohrane |
| `uptime` | Vrijeme od posljednjeg pokretanja |
| `vibro` | Uključivanje/isključivanje vibracijskog motora |
| `unit_tests` | Samo u `unit_tests` verziji firmvera — pogledajte [Jedinični testovi](/hr/dev/unit-tests) |

## Čitanje zapisnika {#reading-logs}

1. Povežite se na CLI.
2. Pokrenite zapisivanje na razini koja vam je potrebna:

   | Naredba | Prikazuje |
   |---|---|
   | `log` | Trenutačnu razinu iz postavki sustava |
   | `log error` | Samo kritične pogreške i važne poruke |
   | `log warn` | Upozorenja i nekritične pogreške, plus `error` |
   | `log info` | Nekritične informacije, plus `warn` |
   | `log default` | Zadanu razinu sustava (= `info`) |
   | `log debug` | Informacije za otklanjanje pogrešaka, plus `info` (utječe na performanse) |
   | `log trace` | Tragove sustava, plus `debug` (utječe na performanse) |

   `log ?` ispisuje ovaj popis na uređaju.
3. Koristite Flipper — poruke se pojavljuju u terminalu.
4. Zaustavite pomoću <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Razgovor putem Sub-GHz veze

Više Flippera na istoj frekvenciji može se dopisivati putem CLI-ja.

1. Svaki sudionik povezuje se na CLI svojeg Flippera.
2. Pokrenite `subghz chat <frequency_in_hz> <device>`, primjerice:

   ```
   subghz chat 868150000 0
   ```

   - frekvencija u Hz unutar 299999755–348000000, 386999938–464000000 ili 778999847–928000000;
   - uređaj `0` = unutarnji CC1101, `1` = vanjski CC1101 modul.
3. Upišite poruku i pritisnite <kbd>Enter</kbd>.
4. Izađite pomoću <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
Izvorni firmver odašilje samo na frekvencijama dopuštenima u vašoj regiji; Unleashed uklanja regionalna TX ograničenja. Poštujte lokalne propise o radiokomunikacijama.
:::

## Referenca naredbi

### bt

| Naredba | Opis |
|---|---|
| `bt hci_info` | Bluetooth HCI podatci |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Samo u debug načinu.* Pokreće TX test nositelja |
| `bt rx_carrier <channel:0-39>` | *Samo u debug načinu.* Pokreće RX test nositelja |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Samo u debug načinu.* Pokreće TX test paketa |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Samo u debug načinu.* Pokreće RX test paketa |

### buzzer

| Naredba | Opis |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Reproducira ton |
| `buzzer note <note> <duration>` | Reproducira notu; `s` označava povisilicu, npr. `cs3` = C♯3; snizilice nisu podržane |

Trajanje prihvaća `ms`, `s`, `m`, `h`, npr. `buzzer note cs3 500ms`.

### crypto

Šifrira/dešifrira pomoću ključeva pohranjenih u sigurnosnoj enklavi mikrokontrolera (MCU).

| Naredba | Opis |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Šifrira tekst pomoću AES256-CBC, ispisuje hex |
| `crypto decrypt <key_slot> <iv_hex>` | Dešifrira hex natrag u tekst |
| `crypto has_key <key_slot>` | Provjerava sadrži li utor (1–100) ključ |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Nepovratno!** Pohranjuje ključ — ne može se ukloniti |

- `key_slot`: utori 1–11 unaprijed su popunjeni ključevima koje koristi firmver.
- `iv_hex`: 16-bajtni inicijalizacijski vektor u hex zapisu.
- `key_type`: `master`, `simple` ili `encrypted`; `key_size`: `128` ili `256`.

### gpio

| Naredba | Opis |
|---|---|
| `gpio mode <pin_name> <0/1>` | Postavlja pin na ulaz (0) ili izlaz (1) |
| `gpio set <pin_name> <0/1>` | Postavlja vrijednost pina |
| `gpio read <pin_name>` | Čita vrijednost pina |

Nazivi pinova: `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — pogledajte [Raspored GPIO pinova](/hr/gpio/pinout).

### ikey

| Naredba | Opis |
|---|---|
| `ikey read` | Čita iButton ključ |
| `ikey emulate <key_type> <key_data>` | Emulira ključ |
| `ikey write Dallas <key_data>` | Zapisuje 8 bajtova na prazni medij kompatibilan sa standardom Dallas |

Vrste ključeva i duljina podataka (hex): `Dallas` — 8 bajtova, `Cyfral` — 2 bajta, `Metakom` — 4 bajta (mora sadržavati ispravan paritet).

### info

| Naredba | Opis |
|---|---|
| `info device` | Podatci o uređaju (firmver, hardver, radijski stog, …) |
| `info power` | Podatci o sustavu napajanja |
| `info power_debug` | Detaljni podatci o napajanju |

### input

| Naredba | Opis |
|---|---|
| `input dump` | Ispisuje događaje tipki |
| `input send <key> <type>` | Šalje događaj; `key`: `up`, `down`, `left`, `right`, `back`, `ok`; `type`: `press`, `release`, `short`, `long` |

Potpuni kratki pritisak sastoji se od tri naredbe, inače se unos odbacuje:

```
input send ok press
input send ok short
input send ok release
```

Za dugi pritisak koristite `long` umjesto `short`.

### ir

| Naredba | Opis |
|---|---|
| `ir rx` | Prima i dekodira IR signale |
| `ir rx raw` | Prima u RAW formatu |
| `ir tx <protocol> <address> <command>` | Šalje naredbu; adresa i naredba u hex zapisu |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Šalje RAW podatke: frekvencija 10000–56000, radni ciklus 0–100, najviše 512 uzoraka |
| `ir decode <input_file> [<output_file>]` | Dekodira datoteku s RAW signalima |
| `ir universal list <remote_name>` | Ispisuje signale univerzalnog daljinskog upravljača |
| `ir universal <remote_name> <signal_name>` | Šalje signal iz univerzalnog daljinskog upravljača |

Protokoli: `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`, `Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Nazivi univerzalnih daljinskih upravljača preuzimaju se iz datoteka u `/ext/infrared/assets/`. Unleashed sadrži `tv`, `audio`, `ac`, `projectors`, `fans` i `leds` (izvorni firmver ima manje). Pokrenite `ir universal list tv` kako biste vidjeli valjane nazive signala.
:::

### js

| Naredba | Opis |
|---|---|
| `js <path>` | Pokreće JavaScript datoteku i ispisuje njezin izlaz konzole — pogledajte [JavaScript](/hr/dev/js-about) |

### led

| Naredba | Opis |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Svjetlina crvene / zelene / plave komponente LED diode |
| `led bl <0-255>` | Svjetlina pozadinskog osvjetljenja zaslona (`128` ≈ 50%) |

Za čistu crvenu boju: `led r 255`, `led g 0`, `led b 0`.

### loader

| Naredba | Opis |
|---|---|
| `loader list` | Popis dostupnih aplikacija |
| `loader open <Application Name> [args]` | Otvara aplikaciju po imenu, po želji s argumentima |
| `loader info` | Prikazuje stanje učitavača |
| `loader close` | Zatvara pokrenutu aplikaciju |
| `loader signal <signal> [arg_hex]` | Šalje signal s neobaveznim hex argumentom |

Argumenti koji sadrže razmake mogu se staviti u navodnike:

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` otvara **podljusku**. Unutar nje: `help` / `?` ispisuje naredbe, `<command> -h` prikazuje pojedinosti, a `exit` izlazi.

| Naredba | Opis |
|---|---|
| `dump -f <path>` | Sprema sadržaj fizičke kartice u `.nfc` datoteku. Opcije: `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Emulira `.nfc` datoteku |
| `field` | Uključuje polje od 13.56 MHz; <kbd>Ctrl</kbd>+<kbd>C</kbd> za zaustavljanje |
| `scanner` | Ispisuje sve protokole koje oznaka podržava; `-t` prikazuje stablo protokola |
| `raw -p <protocol> -d <data>` | Šalje sirove bajtove. Opcije: `-t <timeout>` (ciklusi nositelja), `-k` ostavlja polje uključenim, `-c` dodaje CRC, `-s` najprije izvršava aktivaciju/antikoliziju |
| `apdu -d <data> [<data2> ...]` | Šalje APDU(e) oznakama ISO14443-4A/4B ili ISO15693-3; `-p 4a`/`4b`/`15` prisiljava protokol |
| `mfu info` | Osnovni podatci o oznaci MIFARE Ultralight |
| `mfu rdbl -b <block>` | Čita blok |
| `mfu wrbl -b <block> -d <data>` | Zapisuje blok od 4 bajta |

Protokoli za `dump -p`: `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`, `des`, `slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Protokoli za `raw -p`: `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Naredba | Opis |
|---|---|
| `onewire search` | Pretražuje 1-Wire uređaje |

### power

| Naredba | Opis |
|---|---|
| `power off` | Isključivanje |
| `power reboot` | Ponovno pokretanje |
| `power reboot2dfu` | Ponovno pokretanje u DFU način |
| `power 5v <1/0>` | Uključuje/isključuje 5 V na GPIO pinu 1 |
| `power 3v3 <1/0>` | Uključuje/isključuje 3.3 V na GPIO pinu 9 (samo u debug načinu) |

### rfid

| Naredba | Opis |
|---|---|
| `rfid read [normal/indala/ask134]` | Čita karticu u ASK/PSK načinu; neobavezni argument odabire način čitanja (`ask134` — životinjske oznake od 134 kHz) |
| `rfid write <key_type> <key_data>` | Zapisuje na T5577 |
| `rfid emulate <key_type> <key_data>` | Emulira |
| `rfid raw_read <ask/ask134/psk> <filename>` | Sprema sirovi signal u datoteku |
| `rfid raw_emulate <filename>` | Emulira sirovu datoteku (otklanjanje pogrešaka protokola) |
| `rfid raw_analyze <filename>` | Ispisuje sirovu datoteku i pokušava je dekodirati (razvoj protokola) |

Vrste ključeva i duljina podataka (hex bajtovi):

| Vrsta | Bajtovi | Vrsta | Bajtovi | Vrsta | Bajtovi |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage {#storage}

Putanje započinju s `/int` (unutarnja flash memorija) ili `/ext` (SD kartica).

| Naredba | Opis |
|---|---|
| `storage info /ext` | Podatci o datotečnom sustavu i slobodnom prostoru |
| `storage format /ext` | Formatira SD karticu (traži potvrdu) |
| `storage list <path>` | Ispisuje sadržaj mape |
| `storage tree <path>` | Rekurzivni ispis |
| `storage remove <path>` | Briše datoteku ili **praznu** mapu |
| `storage read <file>` | Ispisuje veličinu i tekstualni sadržaj |
| `storage read_chunks <file> <1-512>` | Ispisuje sadržaj u blokovima zadane veličine |
| `storage write <file>` | Dodaje tekst upisan u CLI; <kbd>Ctrl</kbd>+<kbd>C</kbd> za završetak |
| `storage write_chunk <file> <1-512>` | Dodaje točno N bajtova iz CLI-ja (unos se ne prikazuje) |
| `storage copy <src> <dst>` | Kopira datoteku |
| `storage rename <old> <new>` | Preimenuje / premješta |
| `storage mkdir <path>` | Stvara mapu |
| `storage md5 <file>` | MD5 sažetak |
| `storage stat <path>` | Podatci o datoteci ili mapi |
| `storage timestamp <file>` | Vrijeme posljednje izmjene |
| `storage extract <archive.tar> <dir>` | Raspakirava `.tar` arhivu |

### subghz

| Naredba | Opis |
|---|---|
| `subghz chat <frequency> <device>` | Razgovor s drugim Flipperima |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Odašilje ključ (Princeton) |
| `subghz rx <frequency> <device>` | Prima i dekodira |
| `subghz rx_raw <frequency>` | Prima RAW |
| `subghz decode_raw <path_to_raw_file>` | Dekodira RAW `.sub` datoteku i ispisuje rezultate |
| `subghz tx_from_file <path> <repeat> <device>` | Odašilje spremljenu `.sub` datoteku |

Samo u debug načinu:

| Naredba | Opis |
|---|---|
| `subghz tx_carrier <frequency>` | Odašilje nemodulirani nositelj |
| `subghz rx_carrier <frequency>` | Prima nositelj (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Šifrira datoteku KeeLoq proizvođačkih ključeva |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Šifrira RAW podatke |

`device`: `0` — unutarnji CC1101, `1` — vanjski CC1101 ([vanjski modul](/hr/subghz/external-cc1101)).
`te_us` — osnovna duljina impulsa u µs.

Primjer — odašiljanje spremljene datoteke 3 puta putem unutarnjeg radija:

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Naredba | Opis |
|---|---|
| `sysctl debug <0/1>` | Onemogućuje / omogućuje debug način sustava |
| `sysctl heap_track <none/main>` | Praćenje alokacija na gomili za glavnu nit aplikacije; debug verzije (`DEBUG=1`) prihvaćaju i `tree` (glavna + podređene niti) te `all` |

### update {#update}

| Naredba | Opis |
|---|---|
| `update install /ext/path/to/update.fuf` | Provjerava i instalira paket ažuriranja (`.fuf` manifest unutar raspakirane mape paketa) |
| `update backup /ext/backup.tar` | Izrađuje sigurnosnu kopiju unutarnje pohrane |
| `update restore /ext/backup.tar` | Vraća unutarnju pohranu iz sigurnosne kopije |

Pogledajte [OTA ažuriranja](/hr/dev/ota).

### vibro

| Naredba | Opis |
|---|---|
| `vibro <1/0>` | Uključuje / isključuje vibracijski motor |

## Povezane stranice

- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging)
- [OTA ažuriranja](/hr/dev/ota)
- [Jedinični testovi](/hr/dev/unit-tests)
- [qFlipper](/hr/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire i ICODE registrirani su zaštitni znakovi tvrtke NXP B.V. FeliCa je zaštitni znak tvrtke Sony Corporation.
