---
title: Izrada aplikacija na Androidu
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Izrada aplikacija na Androidu (Termux + uFBT)

Postavite `ufbt` unutar [Termuxa](https://termux.dev/) na običnom, nerootanom Android telefonu i prevodite aplikacije za Flipper Zero
(`.fap`) izravno na telefonu — bez računala, bez proota i bez virtualnog stroja.

::: info Zasluge
Ovo je kroz mnogo pokušaja i pogrešaka razradio [@CamsShaft](https://github.com/CamsShaft) na uređaju Samsung Galaxy S22
(SM-S901W, aarch64). Izvorne upute (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Dio su
Unleashed dokumentacije.
:::

**Opseg:** ovime se izrađuju **aplikacije**, a ne sam firmver. Za izradu firmvera pogledajte [Izrada firmvera](/hr/dev/build).

Putanje u nastavku pretpostavljaju **aarch64** uređaj i zadani Termux prefiks
(`$PREFIX` = `/data/data/com.termux/files/usr`). Vaš se uređaj može razlikovati — tipične pogreške pokrivene su u odjeljku
[Rješavanje problema](#troubleshooting).

## Zašto je potreban dodatan posao

uFBT preuzima unaprijed izgrađeni unakrsni skup alata `arm-none-eabi-gcc` namijenjen običnom Linuxu s **glibc** bibliotekom. Termux se izvršava na
Androidovom **Bionic** libc-u s nestandardnim rasporedom datotečnog sustava, a svaka ELF binarna datoteka u skupu alata traži
`/lib/ld-linux-aarch64.so.1` kao svoj dinamički poveznik — koji na Androidu ne postoji.

Rješenje: instalirajte Termuxov sloj kompatibilnosti za glibc, a zatim svaku binarnu datoteku skupa alata pokrenite putem vlastitog poveznika za glibc pomoću
male skripte omotača (wrappera).

::: danger Nemojte pokretati `patchelf` na binarnim datotekama skupa alata
To oštećuje njihov raspored ELF segmenata i dobivat ćete pogreške segmentacije (segfault) iz `cc1`. Omotači u nastavku ostavljaju binarne datoteke
netaknutima do u bajt.
:::

## Preduvjeti

- Android uređaj s arhitekturom aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/) instaliran **s F-Droida** — verzija s Google Playa je
  zastarjela i neće raditi.
- Pristup internetu i nekoliko GB slobodnog prostora za skup alata, SDK i glibc.

## 1. Osnovni paketi

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` **nije** neobavezan — petlja za omotače u 6. koraku koristi ga kako bi razlikovala ELF binarne datoteke od svega ostalog.

## 2. Sloj kompatibilnosti za glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Ovo moraju biti **dvije odvojene naredbe**: `glibc-repo` dodaje repozitorij iz kojeg dolazi `glibc-runner`. Zajedno
instaliraju potpuni glibc pod `$PREFIX/glibc/`, uključujući dinamički poveznik. Provjerite to:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Nikada nemojte globalno postaviti `LD_PRELOAD` na glibc-ov `libc.so.6`.** To na neočite načine ruši Termuxove vlastite Bionic binarne datoteke, uključujući Python.
Omotači iz 6. koraka čine to nepotrebnim.
:::

## 3. Instalacija uFBT-a i Python ovisnosti za izradu

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Paket | Potreban za |
|---|---|
| `colorlog` | Zapisivanje izlaza skripte za izradu |
| `heatshrink2` | Sažimanje ikona i resursa |
| `pyelftools` | Korak naknadne obrade `FASTFAP` |
| `scons` | Sustav za izradu — mora biti instaliran zasebno; ugrađena kopija iz skupa alata ovdje je neupotrebljiva |
| `pillow` | Pretvorba ikona; bez njega je jedina pogreška golo `convert: No such file or directory` |

Ako izrada `pillow` wheela ne uspije, upotrijebite Termux paket: `pkg install python-pillow`.

## 4. Usmjerite uFBT na Unleashed SDK {#_4-point-ufbt-at-the-unleashed-sdk}

**uFBT zadano koristi SDK službenog firmvera.** Za izradu uz Unleashed proslijedite indeks ažuriranja za Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Kanali: `dev` i `release`. **Svaki kasniji `ufbt update` treba iste zastavice**, inače se tiho vraćate na
službeni SDK i gradite uz pogrešan API.

Ako je `~/.ufbt/toolchain/` još uvijek prazan, bilo koji poziv `ufbt` pokrenut će preuzimanje skupa alata:

```sh
ufbt -h
```

Pogreška koja spominje `python3` ovdje je očekivana — 5. korak to ispravlja. Provjerite je li skup alata stigao:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Preusmjerite Python skupa alata

Skup alata dolazi s vlastitim Pythonom povezanim s glibc-om, koji se ovdje ne može izvršavati. Usmjerite svaki unos `python3*` na Termuxov
Python:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Omotajte binarne datoteke skupa alata

Sve ostalo ovisi o ovom koraku. Svaki omotač pokreće stvarnu binarnu datoteku putem dinamičkog poveznika za glibc s izričitim
`--library-path`, tako da se sama binarna datoteka nikada ne mijenja.

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"
GLIBC_LIB="$PREFIX/glibc/lib"

wrap() {
    for f in "$@"; do
        [ -f "$f" ] || continue
        case "$f" in *.real | *.so | *.so.*) continue ;; esac
        [ -e "$f.real" ] && continue
        file -b "$f" | grep -q '^ELF' || continue

        mv "$f" "$f.real"
        cat > "$f" <<WRAPPER
#!$PREFIX/bin/bash
exec "$GLIBC_LIB/ld-linux-aarch64.so.1" --library-path "$GLIBC_LIB:$TOOLCHAIN/lib" "$f.real" "\$@"
WRAPPER
        chmod +x "$f"
        echo "wrapped $f"
    done
}

wrap "$TOOLCHAIN"/bin/arm-none-eabi-*
wrap "$TOOLCHAIN"/arm-none-eabi/bin/*
wrap "$TOOLCHAIN"/libexec/gcc/arm-none-eabi/*/*
```

Tri glob uzorka odnose se na tri odvojena direktorija ELF binarnih datoteka. Ako izostavite jedan, dobit ćete specifičnu pogrešku:

| Direktorij | Sadrži | Pogreška ako nije omotano |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Zašto su zaštitne provjere važne (osobito pri ponovnom pokretanju):

- `*.so` se preskače jer je `liblto_plugin.so` u `libexec/` dijeljena biblioteka, a ne izvršna datoteka — njezino omatanje
  daje `invalid ELF header`.
- `*.real` i provjera `$f.real` čine funkciju idempotentnom: ponovno pokretanje nakon ažuriranja skupa alata ne može omotati već postojeći
  omotač.
- U `bin/` se namjerno omotava samo `arm-none-eabi-*`: `bin/python3` sada pokazuje na Termuxov Bionic Python i **ne smije**
  prolaziti kroz poveznik za glibc.

::: warning
`ufbt update` može zamijeniti čitav skup alata — **ponovno pokrenite 5. i 6. korak nakon svakog ažuriranja.**
:::

## 7. Izrada

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Uspješna izrada završava ovako:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

`.fap` datoteka nalazi se u `dist/`. Usporedite prijavljeni API s firmverom na vašem Flipperu — neusklađenost znači da će aplikacija
odbiti učitavanje.

## 8. Prebacivanje .fap datoteke na Flipper

`ufbt launch` i `ufbt flash_usb` zahtijevaju serijsku vezu (`/dev/ttyACM*`). **Na tvorničkom, nerootanom Androidu to
ne radi** — Android ne izlaže USB CDC-ACM čvorove uređaja Termuxu. Samo rootani uređaj s ispravnim
CDC-ACM upravljačkim programom može koristiti te naredbe.

Umjesto toga kopirajte datoteku van. FAP datoteke nalaze se u `/ext/apps/<Category>/` na microSD kartici:

```sh
termux-setup-storage                        # jednokratno: daje Termuxu pristup dijeljenoj pohrani
cp dist/some_app.fap ~/storage/downloads/
```

Iz mape `Downloads` datoteka je vidljiva drugim aplikacijama, pa je premjestite na Flipper na uobičajeni način — putem mobilne aplikacije Flipper
ili USB-C čitača microSD kartica.

## Rješavanje problema {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Jedan od tri direktorija iz 6. koraka nije bio omotan. Ponovno pokrenite pozive `wrap` — sigurno ih je ponavljati.

### `liblto_plugin.so: invalid ELF header`

Omotana je dijeljena biblioteka. Vratite je:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` iz cc1

Binarna datoteka je oštećena, gotovo uvijek zbog alata `patchelf`. Ponovno preuzmite skup alata:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Zatim ponovite 5. i 6. korak. **Nikada ne koristite `patchelf` na ovim binarnim datotekama.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

Nedostaje `pillow`: `pip install pillow`, ili `pkg install python-pillow`.

### `python3: No such file or directory`

Simbolička poveznica za Python u skupu alata je neispravna ili ju je vratilo ažuriranje. Ponovno pokrenite 5. korak.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` pokazuje na glibc-ov `libc.so.6`, što ruši Termuxove Bionic binarne datoteke. Očistite ga:

```sh
unset LD_PRELOAD
unset -f ufbt          # u slučaju da funkcija ljuske zasjenjuje ufbt
```

Zatim provjerite početne datoteke svoje ljuske za zaostale unose:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` kaže da je SDK ažuran, ali skup alata nedostaje

uFBT prati SDK i skup alata odvojeno. Prisilno preuzmite oboje:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Zatim ponovite 5. i 6. korak.

### Aplikacija se izradi, ali prijavljuje pogrešnu verziju API-ja

`ufbt update` je pokrenut bez `--index-url`, pa se uFBT prebacio natrag na službeni SDK. Ponovno pokrenite naredbu iz
[4. koraka](#_4-point-ufbt-at-the-unleashed-sdk).

### Omotači su nestali nakon ažuriranja

Očekivano — `ufbt update` može zamijeniti čitav direktorij skupa alata. Ponovno pokrenite 5. i 6. korak.

## Što se zapravo događa

Svaki omotač pokreće svoju stvarnu binarnu datoteku putem dinamičkog poveznika za glibc s opcijom `--library-path` usmjerenom na biblioteke za glibc.
Kada `arm-none-eabi-gcc` pokrene `cc1`, nailazi na skriptu ljuske koja ga kroz poveznik prosljeđuje do netaknute
`.real` binarne datoteke. Unakrsno prevedeni izlaz ostaje nepromijenjen — cilja bare-metal Cortex-M, a ne Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Povezane stranice

- [Vaša prva aplikacija u C-u](/hr/dev/first-app-c)
- [Izrada firmvera](/hr/dev/build)
- [Aplikacije na SD kartici](/hr/apps/sd-card-apps)
- [Mobilna aplikacija Flipper](/hr/mobile/mobile-app)
