---
title: Izgradnja firmvera
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Izgradnja firmvera

Izgradite Unleashed Firmware iz izvornog kôda kada želite mijenjati sam firmver, uključiti vlastite aplikacije u
izgradnju ili testirati najnoviji `dev` kôd prije službenog izdanja.

Ako želite napisati samo aplikaciju (`.fap`), ne treba vam cijeli firmver — umjesto toga koristite
[uFBT](/hr/dev/first-app-c) i prijeđite na odjeljak
[izgradnja aplikacija za Unleashed SDK pomoću uFBT-a](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Što vam je potrebno

- **Git** — [preuzimanje](https://git-scm.com/downloads) za Windows; na Linuxu/macOS-u instalirajte ga putem upravitelja
  paketa (`brew`, `apt`, …).
- **VS Code** (preporučeno za razvoj, opcionalno ako samo gradite firmver).
- Nekoliko GB slobodnog prostora na disku. Ništa drugo: `fbt` pri prvom pokretanju sam preuzima vlastiti ARM toolchain
  i ne mijenja sistemski `PATH` (pogledajte [fbt → Okruženje](/hr/dev/fbt#environment)).

## 1. Klonirajte repozitorij

Uvijek klonirajte **s podmodulima**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Ako ste već klonirali bez `--recursive`, inicijalizirajte podmodule:

```shell
git submodule update --init --recursive
```

## 2. Izgradnja na Linuxu / macOS-u

Izgradite sve i stvorite paket za ažuriranje koji možete instalirati s microSD kartice:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Izgradite jednu aplikaciju iz `applications_user/` i pokrenite je na Flipperu povezanom putem USB-a:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Izgradnja na Windowsu

Koristite `fbt.cmd` u PowerShellu ili `cmd`-u:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
Na Windowsu ćete možda trebati upisati `.\fbt.cmd` (obrnuta kosa crta) umjesto `./fbt.cmd`, ovisno o ljusci koju koristite.
:::

## 4. Pronađite rezultat i instalirajte ga

Svi rezultati izgradnje spremaju se u `dist/`. Datoteka za instalaciju jest paket za ažuriranje:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Uzorak naziva je `flipper-z-{target}-update-{suffix}.tgz`. Zadani sufiks je `local` (postavljen pomoću `DIST_SUFFIX` u
`fbt_options.py` ili varijablom okruženja `DIST_SUFFIX`).

Načini instalacije:

- otvorite `.tgz` u programu **qFlipper** (*Install from file*) ili u web instalatoru Unleashed;
- ili prepustite to alatu `fbt` putem USB-a: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (izgradi, prenese i instalira);
- ili zapišite putem SWD-a pomoću debug sonde: `./fbt flash` (pogledajte [ciljevi alata fbt](/hr/dev/fbt#high-level-targets)).

::: tip Zašto `DEBUG=0`?
Unleashed u `fbt_options.py` zadano koristi `COMPACT=1` i **`DEBUG=1`**. Debug slika je veća i možda neće stati
ispod radijskog stoga u flash memoriji — pakiranje tada staje uz poruku
`Firmware image overlaps C2 region and is not programmable!`. Za sve što namjeravate instalirati izričito proslijedite
`DEBUG=0`. Imajte na umu da `DEBUG=0` također isključuje `furi_assert()` pri prevođenju.
:::

## Integracija s VS Codeom

`fbt` dolazi sa spremnom konfiguracijom za VS Code:

```sh
./fbt vscode_dist
```

Ova naredba kopira konfiguraciju u `.vscode/`. Zatim otvorite korijensku mapu firmvera u VS Codeu putem
**File → Open Folder**, prihvatite preporučena proširenja i koristite <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>
za zadatke izgradnje. Više u [fbt → VS Code](/hr/dev/fbt#vs-code-integration).

## Izgradnja aplikacija za Unleashed SDK pomoću uFBT-a {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) gradi pojedinačne aplikacije oslanjajući se na preuzeti SDK umjesto na cijelo stablo izvornog kôda.
**Zadano preuzima SDK službenog firmvera.** Da biste gradili za Unleashed, usmjerite ga na Unleashed indeks ažuriranja:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Kanali su `dev` i `release`. Koristite iste zastavice pri **svakom** kasnijem pokretanju `ufbt update`, inače će se
uFBT tiho prebaciti natrag na službeni SDK i izgrađena će aplikacija prijavljivati pogrešnu verziju API-ja.

::: tip Unleashed
Unleashed zadržava službeni API, pa većina službenih aplikacija radi bez izmjena. Aplikacija se odbija učitati samo
kada se njezina glavna verzija API-ja ne podudara s firmverom — ponovna izgradnja za odgovarajući SDK rješava taj problem.
:::

## Izgradnja aplikacija na Androidu

Aplikacije (ne i sam firmver) moguće je graditi i izravno na Android telefonu pomoću uFBT-a unutar Termuxa — pogledajte
[Izgradnja aplikacija na Androidu](/hr/dev/android-build).

## Rješavanje problema

| Problem | Rješenje |
|---|---|
| Izgradnja ne uspijeva zbog datoteka koje nedostaju / pogrešaka podmodula | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Dodajte `DEBUG=0` u naredbu |
| `./fbt` nije pronađen na Windowsu | Koristite `fbt.cmd` / `.\fbt.cmd` |
| Aplikacija izgrađena s uFBT-om ne pokreće se: nepodudaranje API-ja | Ponovno pokrenite `ufbt update` s Unleashed `--index-url`, ponovno izgradite |
| Želite čistu ponovnu izgradnju | Dodajte `-c` za čišćenje zadanih ciljeva, npr. `./fbt -c fw_dist` |

## Povezane stranice

- [Flipper Build Tool (fbt)](/hr/dev/fbt) — svi ciljevi i opcije
- [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c)
- [OTA ažuriranja](/hr/dev/ota) — što se nalazi unutar paketa za ažuriranje
- [Hardverski ciljevi](/hr/dev/hardware-targets)
