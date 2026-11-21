---
title: Compilare app su Android
order: 15
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md, https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX]
sources: [unleashed-docs, unleashed-readme]
---
# Compilare app su Android (Termux + uFBT)

Configura `ufbt` dentro [Termux](https://termux.dev/) su un comune telefono Android non rootato e compila le app
(`.fap`) per il Flipper Zero direttamente sul telefono — senza PC, senza proot, senza macchine virtuali.

::: info Riconoscimenti
Messo a punto da [@CamsShaft](https://github.com/CamsShaft) dopo molti tentativi su un Samsung Galaxy S22
(SM-S901W, aarch64). Guida originale (MIT):
[BUILD-FLIPPER-FAPS-IN-TERMUX](https://github.com/CamsShaft/BUILD-FLIPPER-FAPS-IN-TERMUX). Fa parte della
documentazione di Unleashed.
:::

**Ambito:** questa procedura compila le **app**, non il firmware. Per il firmware stesso vedi
[Compilare il firmware](/it/dev/build).

I percorsi che seguono presuppongono un dispositivo **aarch64** e il prefisso predefinito di Termux
(`$PREFIX` = `/data/data/com.termux/files/usr`). Il tuo dispositivo può differire — i problemi tipici sono trattati
in [Risoluzione dei problemi](#troubleshooting).

## Perché serve del lavoro in più

uFBT scarica una cross-toolchain `arm-none-eabi-gcc` precompilata per un Linux ordinario con **glibc**. Termux gira
sulla libc **Bionic** di Android, con una disposizione del filesystem non standard, e ogni binario ELF della
toolchain richiede `/lib/ld-linux-aarch64.so.1` come proprio linker dinamico — che su Android non esiste.

La soluzione: installare lo strato di compatibilità glibc di Termux e poi eseguire ogni binario della toolchain
attraverso il linker di glibc tramite un piccolo script wrapper.

::: danger Non eseguire `patchelf` sui binari della toolchain
Corrompe la disposizione dei loro segmenti ELF e ottieni segfault da `cc1`. I wrapper descritti sotto lasciano i
binari intatti byte per byte.
:::

## Prerequisiti

- Un dispositivo Android aarch64.
- [Termux](https://f-droid.org/en/packages/com.termux/) installato **da F-Droid** — la versione su Google Play è
  obsoleta e non funziona.
- Connessione a Internet e un paio di GB liberi per toolchain, SDK e glibc.

## 1. Pacchetti di base

```sh
pkg update && pkg upgrade -y
pkg install python python-pip git file -y
```

`file` **non** è facoltativo: il ciclo dei wrapper al passo 6 lo usa per distinguere i binari ELF da tutto il resto.

## 2. Strato di compatibilità glibc

```sh
pkg install glibc-repo -y
pkg install glibc-runner -y
```

Devono essere **due comandi separati**: `glibc-repo` aggiunge il repository da cui proviene `glibc-runner`. Insieme
installano una glibc completa sotto `$PREFIX/glibc/`, linker dinamico compreso. Verificalo:

```sh
ls $PREFIX/glibc/lib/ld-linux-aarch64.so.1
```

::: warning
**Non impostare mai `LD_PRELOAD` sul `libc.so.6` di glibc a livello globale.** Rompe i binari Bionic di Termux,
Python compreso, in modi non evidenti. I wrapper del passo 6 lo rendono inutile.
:::

## 3. Installare uFBT e le dipendenze Python di build

```sh
pip install ufbt colorlog heatshrink2 pyelftools scons pillow
```

| Pacchetto | Serve per |
|---|---|
| `colorlog` | Log degli script di build |
| `heatshrink2` | Compressione di icone e asset |
| `pyelftools` | Il passo di post-elaborazione `FASTFAP` |
| `scons` | Il sistema di build — deve essere un'installazione autonoma; la copia inclusa nella toolchain qui è inutilizzabile |
| `pillow` | Conversione delle icone; senza di esso l'unico errore è un laconico `convert: No such file or directory` |

Se la compilazione del wheel di `pillow` fallisce, usa il pacchetto di Termux: `pkg install python-pillow`.

## 4. Puntare uFBT all'SDK Unleashed {#_4-point-ufbt-at-the-unleashed-sdk}

**uFBT usa per impostazione predefinita l'SDK del firmware ufficiale.** Per compilare contro Unleashed, passa
l'indice degli aggiornamenti di Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Canali: `dev` e `release`. **Ogni successivo `ufbt update` richiede gli stessi flag**, altrimenti torni
silenziosamente all'SDK ufficiale e compili contro l'API sbagliata.

Se `~/.ufbt/toolchain/` è ancora vuota, qualunque chiamata a uFBT avvia il bootstrap della toolchain:

```sh
ufbt -h
```

Un errore che qui menziona `python3` è previsto — il passo 5 lo risolve. Verifica che la toolchain sia arrivata:

```sh
ls ~/.ufbt/toolchain/aarch64-linux/bin/arm-none-eabi-gcc
ls ~/.ufbt/toolchain/aarch64-linux/arm-none-eabi/bin/as
ls ~/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*/cc1
```

## 5. Ridirigere il Python della toolchain

La toolchain include un proprio Python collegato a glibc, che qui non può funzionare. Fai puntare ogni voce
`python3*` al Python di Termux:

```sh
TOOLCHAIN="$HOME/.ufbt/toolchain/aarch64-linux"

for py in "$TOOLCHAIN"/bin/python3*; do
    [ -e "$py" ] || [ -L "$py" ] || continue
    ln -sf "$PREFIX/bin/python3" "$py"
done
```

## 6. Incapsulare i binari della toolchain

Tutto il resto dipende da questo passo. Ogni wrapper esegue il binario reale attraverso il linker dinamico di glibc
con un `--library-path` esplicito, così il binario stesso non viene mai modificato.

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

I tre glob corrispondono a tre directory distinte di binari ELF. Dimenticarne una produce un errore specifico:

| Directory | Contiene | Errore se non incapsulata |
|---|---|---|
| `bin/` | `arm-none-eabi-gcc`, `-g++`, … | `cannot execute` / `No such file or directory` |
| `arm-none-eabi/bin/` | `as`, `ld`, `ar`, `objcopy`, … | `cannot execute as` |
| `libexec/gcc/arm-none-eabi/<gcc-version>/` | `cc1`, `cc1plus`, `collect2`, `lto1` | `cannot execute cc1` |

Perché le protezioni sono importanti (soprattutto se riesegui lo script):

- `*.so` viene saltato perché `liblto_plugin.so` in `libexec/` è una libreria condivisa, non un eseguibile —
  incapsularla dà `invalid ELF header`.
- `*.real` e il controllo su `$f.real` rendono la funzione idempotente: rieseguirla dopo un aggiornamento della
  toolchain non può incapsulare un wrapper.
- In `bin/` viene incapsulato soltanto `arm-none-eabi-*` di proposito: `bin/python3` ora punta al Python Bionic di
  Termux e **non** deve passare per il linker di glibc.

::: warning
`ufbt update` può sostituire l'intera toolchain — **riesegui i passi 5 e 6 dopo ogni aggiornamento.**
:::

## 7. Compilare

```sh
git clone https://github.com/<owner>/<some-flipper-app>.git
cd <some-flipper-app>
ufbt
```

Una compilazione riuscita termina così:

```
scons: Entering directory '...'
        CC      ...
        LINK    ...
        FAP     ...
        FASTFAP ...
        APPCHK  dist/some_app.fap
                Target: 7, API: 88.2
```

Il `.fap` si trova in `dist/`. Confronta l'API riportata con quella del firmware del tuo Flipper — una discrepanza
significa che l'app rifiuterà di caricarsi.

## 8. Portare il .fap sul Flipper

`ufbt launch` e `ufbt flash_usb` richiedono una connessione seriale (`/dev/ttyACM*`). **Su un Android di serie, non
rootato, questo non funziona** — Android non espone a Termux i nodi di dispositivo USB CDC-ACM. Solo un dispositivo
rootato con un driver CDC-ACM funzionante può usare quei comandi.

Copia invece il file all'esterno. I FAP risiedono in `/ext/apps/<Category>/` sulla scheda microSD:

```sh
termux-setup-storage                        # one-time: grants Termux access to shared storage
cp dist/some_app.fap ~/storage/downloads/
```

Da `Downloads` il file è visibile alle altre app, quindi spostalo sul Flipper nel modo consueto — con l'app mobile
del Flipper o con un lettore di schede microSD USB-C.

## Risoluzione dei problemi {#troubleshooting}

### `cannot execute cc1` / `cannot execute as`

Una delle tre directory del passo 6 non è stata incapsulata. Riesegui le chiamate a `wrap` — si possono ripetere
senza rischi.

### `liblto_plugin.so: invalid ELF header`

È stata incapsulata una libreria condivisa. Ripristinala:

```sh
LIBEXEC="$(echo "$HOME"/.ufbt/toolchain/aarch64-linux/libexec/gcc/arm-none-eabi/*)"
mv "$LIBEXEC/liblto_plugin.so.real" "$LIBEXEC/liblto_plugin.so"
```

### `Segmentation fault` da cc1

Il binario è stato corrotto, quasi sempre da `patchelf`. Riscarica la toolchain:

```sh
rm -rf ~/.ufbt/toolchain
ufbt -h
```

Poi ripeti i passi 5 e 6. **Non usare mai `patchelf` su questi binari.**

### `No module named 'colorlog'` / `'heatshrink2'` / `'elftools'`

```sh
pip install colorlog heatshrink2 pyelftools
```

### `convert: No such file or directory`

Manca `pillow`: `pip install pillow`, oppure `pkg install python-pillow`.

### `python3: No such file or directory`

Il symlink al Python della toolchain è rotto o è stato ripristinato da un aggiornamento. Riesegui il passo 5.

### `CANNOT LINK EXECUTABLE "python3": library "ld-linux-aarch64.so.1" not found`

`LD_PRELOAD` punta al `libc.so.6` di glibc, cosa che rompe i binari Bionic di Termux. Azzeralo:

```sh
unset LD_PRELOAD
unset -f ufbt          # in case a shell function is shadowing ufbt
```

Poi controlla i file di avvio della tua shell per eventuali residui:

```sh
grep -r "glibc\|LD_PRELOAD" ~/.bashrc ~/.profile ~/.bash_profile ~/.zshrc 2>/dev/null
```

### `ufbt update` dice che l'SDK è aggiornato, ma la toolchain manca

uFBT tiene traccia di SDK e toolchain separatamente. Forzali entrambi:

```sh
rm -rf ~/.ufbt/current ~/.ufbt/toolchain
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
ufbt -h
```

Poi ripeti i passi 5 e 6.

### L'app si compila ma riporta la versione delle API sbagliata

Un `ufbt update` è stato eseguito senza `--index-url`, quindi uFBT è tornato all'SDK ufficiale. Riesegui il comando
del [passo 4](#_4-point-ufbt-at-the-unleashed-sdk).

### I wrapper sono scomparsi dopo un aggiornamento

È previsto: `ufbt update` può sostituire l'intera directory della toolchain. Riesegui i passi 5 e 6.

## Che cosa accade davvero

Ogni wrapper esegue il proprio binario reale attraverso il linker dinamico di glibc con `--library-path` puntato
alle librerie di glibc. Quando `arm-none-eabi-gcc` lancia `cc1`, incontra uno script di shell che passa per il linker
fino al binario `.real` intatto. L'output cross-compilato non ne è influenzato — ha come target un Cortex-M
bare-metal, non Linux.

```
ufbt (Python, Bionic)
  └─ arm-none-eabi-gcc (wrapper)
       └─ ld-linux-aarch64.so.1 → arm-none-eabi-gcc.real (glibc)
            ├─ cc1 (wrapper)      → ld-linux-aarch64.so.1 → cc1.real
            ├─ as (wrapper)       → ld-linux-aarch64.so.1 → as.real
            └─ collect2 → ld (wrapper) → ld-linux-aarch64.so.1 → ld.real
                 └─ output: some_app.fap (ARM Cortex-M4, for the Flipper Zero)
```

## Pagine correlate

- [La tua prima app in C](/it/dev/first-app-c)
- [Compilare il firmware](/it/dev/build)
- [App sulla scheda SD](/it/apps/sd-card-apps)
- [App mobile del Flipper](/it/mobile/mobile-app)
