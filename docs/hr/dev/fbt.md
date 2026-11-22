---
title: Flipper Build Tool (fbt)
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Flipper Build Tool (fbt)

`fbt` je jedinstvena ulazna točka za prevođenje, flashanje, otklanjanje pogrešaka i lintanje firmvera. Pokrećete ga kao `./fbt`
(ili `fbt.cmd` na sustavu Windows) iz korijenskog direktorija repozitorija. Interno je to omotač oko
sustava za prevođenje [SCons](https://scons.org/).

Ako želite prevesti i otklanjati pogreške na **samo jednoj aplikaciji**, ne treba vam cijelo stablo izvornog koda firmvera — umjesto toga
upotrijebite [uFBT](https://pypi.org/project/ufbt/) (pogledajte [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c)).

## Okruženje {#environment}

Jedino što morate imati instalirano jest `git`. Pri prvom pokretanju `fbt` preuzima i raspakirava unaprijed pripremljeni
alatni lanac (toolchain) te prilagođava varijable okruženja **samo za sebe** — vaš globalni `PATH` ne mijenja se.

Za korištenje priloženog alatnog lanca izvan alata `fbt` (primjerice za ručno pozivanje `arm-none-eabi-gdb`), otvorite
*fbt ljusku*:

- Windows: pokrenite `scripts/toolchain/fbtenv.cmd`
- Linux / macOS: pokrenite `source scripts/toolchain/fbtenv.sh` u novoj ljusci
- ili u svojoj ljusci upišite `` . `./fbt -s env` `` (zadržite početnu točku `.`)

Varijable okruženja koje mijenjaju ponašanje alata `fbt`:

| Varijabla | Učinak |
|---|---|
| `FBT_NOENV=1` | Preskoči preuzimanje/postavljanje alatnog lanca; svi alati već moraju biti u varijabli `PATH` (nije dostupno na sustavu Windows) |
| `FBT_TOOLCHAIN_PATH=…` | Direktorij u koji se raspakirava alatni lanac (zadano: `toolchain/` u korijenu repozitorija) |
| `FBT_VERBOSE=1` | Dodatni ispis za otklanjanje pogrešaka iz alata `fbt` i skripti alatnog lanca |
| `FBT_NO_SYNC=1` | Ne pokreći `git submodule update --init` pri svakom pokretanju |

Postavljanje varijable za jedno pokretanje:

```sh
# Linux / macOS
FBT_NO_SYNC=1 ./fbt ...
```

```bat
:: Windows (cmd)
set "FBT_NO_SYNC=1"
```

Više varijabli dokumentirano je u izvornom kodu skripti `fbt` i `fbtenv`.

## Pozivanje alata fbt

Proslijedite opcije konfiguracije i ciljeve koje želite:

```sh
./fbt COMPACT=1 DEBUG=0 VERBOSE=1 updater_package copro_dist
```

Za čišćenje (poput `make clean`) navedenih ciljeva dodajte `-c`.

`fbt` prati ovisnosti, pa navodite samo najviši cilj koji vam je potreban — sve o čemu on ovisi
automatski se ponovno prevodi.

## Direktoriji za prevođenje

Firmver i program za ažuriranje (updater) prevode se u zasebnim poddirektorijima direktorija `build/`, imenovanim prema postavkama
optimizacije (`COMPACT`, `DEBUG`). Za razvojna okruženja (IDE), najnovija prevedena varijanta uvijek je povezana kao `build/latest`, zajedno s datotekom
`compile_commands.json` koja se koristi za dovršavanje koda.

::: info
`build/latest` i baza podataka prevođenja ažuriraju se samo **ciljevima za prevođenje firmvera**. Flashanje ili izrada
paketa za ažuriranje za *drukčiju* konfiguraciju debug/release ili drugi hardverski cilj ne pomiče `build/latest`.
:::

## Integracija s VS Codeom {#vs-code-integration}

```sh
./fbt vscode_dist
```

kopira gotovu konfiguraciju okruženja u `.vscode/`. Otvorite korijenski direktorij firmvera putem **File → Open Folder**.

- Za korištenje poslužitelja jezika koji nije zadani `cpptools`, pokrenite `./fbt vscode_dist LANG_SERVER=<language-server>`.
  Podržani su: `cpptools` (zadano) i `clangd`.
- Pri prvom pokretanju bit će vam ponuđena preporučena proširenja (navedena u `.vscode/extensions.json`) — instalirajte ih.
- Zadaci prevođenja nalaze se pod prečacem <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>.
- Otklanjanje pogrešaka zahtijeva podržanu sondu: Wi-Fi Devboard s tvorničkim (Blackmagic) firmverom, ST-Link i kompatibilne uređaje ili
  J-Link (samo VS Code; alati J-Link nisu priloženi — [preuzmite](https://www.segger.com/downloads/jlink/) ih i
  dodajte u `PATH`).
- Bez sonde i dalje možete instalirati firmver putem USB-a.

## Ciljevi visoke razine {#high-level-targets}

Ovo su ciljevi koje ćete najčešće koristiti.

| Cilj | Što radi |
|---|---|
| `fw_dist` | Prevodi firmver i objavljuje ga u `dist/`. **Zadani cilj** kada nije naveden nijedan |
| `fap_dist` | Prevodi vanjske aplikacije (FAP) i objavljuje ih u `dist/` |
| `updater_package` | Potpuni paket za samo-ažuriranje: DFU firmvera + radijski stog + resursi za microSD karticu |
| `updater_minpackage` | Minimalni paket za ažuriranje: samo DFU firmvera |
| `copro_dist` | Pakira Core2 FUS + binarne datoteke radijskog stoga za qFlipper |
| `flash` | Flasha putem SWD-a pomoću podržane sonde (automatski otkrivena; nadjačajte pomoću `SWD_TRANSPORT=...`, odaberite jednu od više sondi pomoću `SWD_TRANSPORT_SERIAL=...`) |
| `flash_usb`, `flash_usb_full` | Prevodi, prenosi i instalira paket za ažuriranje putem USB-a (minimalni / potpuni paket) |
| `debug` | Prevodi i flasha firmver, zatim priključuje GDB s učitanom `.elf` datotekom firmvera |
| `debug_other`, `debug_other_blackmagic` | Priključuje GDB bez učitavanja `.elf` datoteke; dodajte vanjske `.elf` datoteke pomoću `add-symbol-file` |
| `updater_debug` | Priključuje GDB s učitanom `.elf` datotekom programa za ažuriranje |
| `devboard_flash` | Ažurira Wi-Fi Devboard; dodatni argumenti putem `ARGS="..."`, npr. `ARGS="-c dev"` |
| `blackmagic` | Otklanja pogreške firmvera pomoću Blackmagic sonde (Wi-Fi Devboard) |
| `openocd` | Samo pokreće OpenOCD; dodatni argumenti putem `ARGS="..."` |
| `get_blackmagic` | Ispisuje Blackmagic adresu u GDB remote formatu (za integraciju u IDE) |
| `get_stlink` | Ispisuje serijske brojeve priključenih ST-Link sondi (za `SWD_TRANSPORT_SERIAL=...`) |
| `lint`, `format` | Provjerava / ponovno formatira C kôd pomoću alata clang-format (`.clang-format`); dodatni argumenti putem `ARGS="..."` |
| `lint_py`, `format_py` | Provjerava / ponovno formatira Python, datoteke prevođenja i manifeste pomoću alata [black](https://black.readthedocs.io/en/stable/index.html) |
| `lint_img`, `format_img` | Provjerava / popravlja slikovne resurse (dubina boja, uklanjanje metapodataka) |
| `lint_all`, `format_all` | Pokreće sve lintere / alate za formatiranje |
| `firmware_pvs` | Izvješće alata PVS-Studio (PVS-Studio mora biti u `PATH`) |
| `doxygen` | Generira Doxygen dokumentaciju; `doxy` je također otvara u pregledniku |
| `cli` | Otvara Flipper [CLI](/hr/dev/cli) sesiju putem USB-a |

## Ciljevi firmvera

| Cilj | Što radi |
|---|---|
| `faps` | Prevodi sve vanjske aplikacije i dodatke kao `.fap` |
| `fap_<appid>` | Prevodi jednu aplikaciju kao `.fap` prema njezinu ID-u, npr. `fap_snake_game` |
| `fap_<appid>_list` | Generira ispis izvornog i asemblerskog koda za `.fap` te aplikacije |
| `flash`, `firmware_flash` | Flasha trenutačnu verziju putem SWD-a |
| `jflash` | Flasha pomoću JFlasha koristeći J-Link sondu (JFlash mora biti u `PATH`) |
| `firmware_all`, `updater_all` | Prevodi osnovni skup binarnih datoteka |
| `firmware_list`, `updater_list` | Generira ispise izvornog i asemblerskog koda |
| `firmware_cdb`, `updater_cdb` | Generira `compilation_database.json` za razvojna okruženja — radi bez potpunog prevođenja |

Upotrijebite `--extra-ext-apps` (u nastavku) kako biste uključili dodatne aplikacije u vanjsko prevođenje.

## Ciljevi resursa

| Cilj | Što radi |
|---|---|
| `resources` | Izrađuje resurse za microSD karticu i njihove manifest datoteke |
| `dolphin_ext` | Obrađuje animacije dupina za microSD karticu |
| `icons` | Generira `.c` + `.h` za ikone iz PNG resursa |
| `proto` | Generira `.pb.c` + `.pb.h` iz `.proto` izvornih datoteka |
| `proto_ver` | Generira `.h` s inačicom protobufa |
| `dolphin_internal`, `dolphin_blocking` | Generira `.c` + `.h` za odgovarajuće resurse dupina |

## Parametri naredbenog retka

| Parametar | Značenje |
|---|---|
| `--options optionfile.py` | Učitava datoteku s konfiguracijskim vrijednostima (zadano `fbt_options.py`) |
| `--extra-int-apps=app1,app2,appN` | Prisilno uključuje navedene aplikacije u prevođenje **unutar** firmvera (cilj `firmware`) |
| `--extra-ext-apps=app1,app2,appN` | Prisilno uključuje navedene aplikacije u **vanjsko** prevođenje (cilj `firmware_extapps`) |
| `--extra-define=A --extra-define=B=C` | Dodatne globalne C/C++ definicije; može se ponavljati |
| `--proxy-env=VAR1,VAR2` | Dodatne varijable okruženja koje se prosljeđuju potprocesima. Zadano `fbt` pročišćava okruženje; popis uvijek proslijeđenih nalazi se u `environ.scons` |

## Konfiguracija

Zadane vrijednosti nalaze se u datoteci `fbt_options.py`. Vrijednosti zadane u naredbenom retku imaju prednost. Za **trajne osobne
izmjene**, stvorite `fbt_options_local.py` pokraj nje — ta se datoteka učitava pri učitavanju zadanih opcija, tako da nikada
ne morate uređivati datoteku pod verzioniranjem. Pokrenite `./fbt -h` za ispis svih opcija.

Važnije zadane vrijednosti u firmveru Unleashed iz `fbt_options.py`:

| Opcija | Zadano | Napomene |
|---|---|---|
| `FIRMWARE_ORIGIN` | `"Unleashed"` | Prikazuje se u podacima o uređaju |
| `TARGET_HW` | `7` | Flipper Zero (f7); pogledajte [hardverske ciljeve](/hr/dev/hardware-targets) |
| `COMPACT` | `1` | Optimizacija za veličinu |
| `DEBUG` | `1` | Proslijedite `DEBUG=0` za verzije spremne za instalaciju |
| `DIST_SUFFIX` | `"local"` | Sufiks u nazivima izlaznih datoteka |
| `COPRO_STACK_TYPE` | `"ble_light"` | `ble_full` je podržan, ali možda neće stati u debug verzije |
| `FIRMWARE_APP_SET` | `"default"` | Pogledajte u nastavku |

### Skupovi aplikacija firmvera {#firmware-app-sets}

Koje aplikacije ulaze u firmver određuje `FIRMWARE_APPS` — mapa oblika *naziv konfiguracije → n-torka ID-eva
aplikacija*. Odaberite jednu pomoću `FIRMWARE_APP_SET`. Unleashed definira dva skupa:

```python
FIRMWARE_APPS = {
    "default": [
        # Svc
        "basic_services",
        # Apps
        "main_apps",
        "system_apps",
        # Settings
        "settings_apps",
    ],
    "unit_tests": [
        "basic_services",
        "updater_app",
        "radio_device_cc1101_ext",
        "unit_tests",
        "infrared",
        "archive",
    ],
}
```

Primjerice, za prevođenje slike s jediničnim testovima:

```sh
./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests
```

Pogledajte [Jedinični testovi](/hr/dev/unit-tests) zašto ta verzija zahtijeva `DEBUG=0`.

## Povezane stranice

- [Prevođenje firmvera](/hr/dev/build)
- [Manifesti aplikacija (.fam)](/hr/dev/app-manifests)
- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging)
- [OTA ažuriranja](/hr/dev/ota)
