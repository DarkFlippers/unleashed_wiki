---
title: Compilare il firmware
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToBuild.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/fbt.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py]
sources: [unleashed-docs, unleashed-src]
---
# Compilare il firmware

Compila il firmware Unleashed dai sorgenti quando vuoi modificare il firmware stesso, includere app proprie nella
build oppure provare il codice `dev` più recente prima di una release ufficiale.

Se vuoi soltanto scrivere un'app (`.fap`), non ti serve l'intero firmware — usa invece
[uFBT](/it/dev/first-app-c) e passa direttamente a
[compilare app contro l'SDK Unleashed](#build-apps-against-the-unleashed-sdk-with-ufbt).

## Cosa ti serve

- **Git** — [download](https://git-scm.com/downloads) per Windows; su Linux/macOS installalo con il tuo gestore di
  pacchetti (`brew`, `apt`, …).
- **VS Code** (consigliato per lo sviluppo, facoltativo se vuoi solo compilare).
- Qualche GB di spazio su disco. Nient'altro: `fbt` scarica la propria toolchain ARM al primo avvio e non modifica il
  `PATH` di sistema (vedi [fbt → Ambiente](/it/dev/fbt#environment)).

## 1. Clonare il repository

Clona sempre **con i submodule**:

```shell
git clone --recursive https://github.com/DarkFlippers/unleashed-firmware.git
cd unleashed-firmware
```

Se l'hai già clonato senza `--recursive`, inizializza i submodule:

```shell
git submodule update --init --recursive
```

## 2. Compilare su Linux / macOS

Compila tutto e produci un pacchetto di aggiornamento installabile dalla scheda microSD:

```sh
./fbt COMPACT=1 DEBUG=0 updater_package
```

Compila una singola app da `applications_user/` e avviala su un Flipper collegato via USB:

```sh
./fbt COMPACT=1 DEBUG=0 launch_app APPSRC=applications_user/yourplugin
```

## 3. Compilare su Windows

Usa `fbt.cmd` in PowerShell o in `cmd`:

```powershell
./fbt.cmd COMPACT=1 DEBUG=0 updater_package
```

::: warning
Su Windows può essere necessario scrivere `.\fbt.cmd` (con la barra rovesciata) invece di `./fbt.cmd`, a seconda della
shell.
:::

## 4. Trovare il risultato e installarlo

Tutti i risultati della compilazione finiscono in `dist/`. Il file da installare è il pacchetto di aggiornamento:

```
dist/f7-C/flipper-z-f7-update-local.tgz
```

Lo schema del nome è `flipper-z-{target}-update-{suffix}.tgz`. Il suffisso predefinito è `local` (impostato da
`DIST_SUFFIX` in `fbt_options.py`, oppure dalla variabile d'ambiente `DIST_SUFFIX`).

Modi per installarlo:

- apri il `.tgz` in **qFlipper** (*Install from file*) o nel web installer di Unleashed;
- oppure lascia fare a `fbt` via USB: `./fbt COMPACT=1 DEBUG=0 flash_usb_full` (compila, carica e installa);
- oppure flasha via SWD con una sonda di debug: `./fbt flash` (vedi [target di fbt](/it/dev/fbt#high-level-targets)).

::: tip Perché `DEBUG=0`?
Il file `fbt_options.py` di Unleashed imposta per impostazione predefinita `COMPACT=1` e **`DEBUG=1`**. Un'immagine di
debug è più grande e può non entrare sotto lo stack radio nella flash — l'impacchettamento si interrompe allora con
`Firmware image overlaps C2 region and is not programmable!`. Per qualunque cosa che intendi installare, passa
`DEBUG=0` esplicitamente. Nota che `DEBUG=0` elimina in compilazione anche `furi_assert()`.
:::

## Integrazione con VS Code

`fbt` include una configurazione VS Code già pronta:

```sh
./fbt vscode_dist
```

Questo comando copia la configurazione in `.vscode/`. Poi apri la radice del firmware in VS Code con
**File → Open Folder**, accetta le estensioni consigliate e usa <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> per i
task di compilazione. Altri dettagli in [fbt → VS Code](/it/dev/fbt#vs-code-integration).

## Compilare app contro l'SDK Unleashed con uFBT {#build-apps-against-the-unleashed-sdk-with-ufbt}

uFBT (micro-fbt) compila singole app contro un SDK scaricato, invece dell'intero albero dei sorgenti. **Per
impostazione predefinita scarica l'SDK del firmware ufficiale.** Per compilare per Unleashed, puntalo all'indice
degli aggiornamenti di Unleashed:

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

I canali sono `dev` e `release`. Usa gli stessi flag per **ogni** successivo `ufbt update`, altrimenti uFBT torna
silenziosamente all'SDK ufficiale e l'app compilata riporta la versione delle API sbagliata.

::: tip Unleashed
Unleashed mantiene le API ufficiali, quindi la maggior parte delle app ufficiali funziona così com'è. Un'app rifiuta
di caricarsi solo quando la sua versione major delle API non corrisponde a quella del firmware — ricompilarla contro
l'SDK corrispondente risolve il problema.
:::

## Compilare app su Android

Le app (non il firmware) si possono compilare anche direttamente su un telefono Android con uFBT dentro Termux — vedi
[Compilare app su Android](/it/dev/android-build).

## Risoluzione dei problemi

| Problema | Rimedio |
|---|---|
| La compilazione fallisce con file mancanti / errori sui submodule | `git submodule update --init --recursive` |
| `Firmware image overlaps C2 region and is not programmable!` | Aggiungi `DEBUG=0` al comando |
| `./fbt` non trovato su Windows | Usa `fbt.cmd` / `.\fbt.cmd` |
| Un'app compilata con uFBT non si avvia: versione delle API non corrispondente | Esegui di nuovo `ufbt update` con l'`--index-url` di Unleashed e ricompila |
| Vuoi una ricompilazione pulita | Aggiungi `-c` per ripulire i target indicati, per esempio `./fbt -c fw_dist` |

## Pagine correlate

- [Flipper Build Tool (fbt)](/it/dev/fbt) — tutti i target e le opzioni
- [La tua prima app in C](/it/dev/first-app-c)
- [Aggiornamenti OTA](/it/dev/ota) — cosa c'è dentro un pacchetto di aggiornamento
- [Target hardware](/it/dev/hardware-targets)
