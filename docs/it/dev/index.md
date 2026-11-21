---
title: Sviluppo
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Sviluppo

Questa sezione è destinata a chi vuole andare oltre il semplice uso del Flipper: compilare il firmware Unleashed dai
sorgenti, scrivere app proprie in C o in JavaScript, eseguirne il debug su hardware reale, dialogare con il
dispositivo dalla riga di comando o capire come funzionano aggiornamenti e hardware sotto il cofano.

::: tip Unleashed
Unleashed è un fork del firmware ufficiale che resta **pienamente compatibile con le API e le app ufficiali**. Quasi
tutto quello che si trova nella documentazione ufficiale per sviluppatori si applica senza modifiche. Le cose
principali da ricordare:

- clona `https://github.com/DarkFlippers/unleashed-firmware` invece del repository ufficiale;
- quando compili app con **uFBT**, puntalo all'SDK Unleashed
  (`--index-url=https://up.unleashedflip.com/directory.json`), altrimenti la tua app verrà compilata contro l'SDK
  ufficiale e potrebbe rifiutare di caricarsi
  ([dettagli](/it/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- l'origine del firmware è riportata come `Unleashed`, la versione corrente delle API su `dev` è **88.27**.
:::

## Compilare il firmware

| Pagina | Cosa ci trovi |
|---|---|
| [Compilare il firmware](/it/dev/build) | Clonare, compilare e flashare Unleashed su Linux, macOS e Windows |
| [Flipper Build Tool (fbt)](/it/dev/fbt) | Tutti i target, le opzioni e le variabili d'ambiente di `fbt` |
| [Target hardware](/it/dev/hardware-targets) | Come `targets/` e `target.json` descrivono le varianti hardware (f7, f18) |
| [Compilare app su Android](/it/dev/android-build) | Compilare app `.fap` su un telefono con Termux + uFBT, senza PC |

## Scrivere app

| Pagina | Cosa ci trovi |
|---|---|
| [La tua prima app in C](/it/dev/first-app-c) | uFBT, template dell'app, "Hello world" con una finestra di dialogo, compilazione ed esecuzione |
| [Manifest delle app (.fam)](/it/dev/app-manifests) | Tutti i campi di `application.fam`, opzioni per le app esterne, librerie private |
| [API Furi](/it/dev/furi-api) | Architettura hardware e software, il core Furi, `furi_assert` / `furi_check` |
| [GUI nelle app](/it/dev/gui) | Dialogs, ViewPort, Views e Scenes, moduli di view |
| [Debug delle app](/it/dev/debugging) | Sonde SWD, debug in VS Code, segnali di debug di Furi HAL |
| [API FuriHalBus](/it/dev/furi-hal-bus) | Attivare/disattivare correttamente le periferiche dell'MCU, mappa dei canali DMA |
| [JavaScript sul Flipper](/it/dev/js-about) | Scrivere script in JavaScript invece che in C (gruppo di pagine a parte) |
| Moduli JS solo di Unleashed | [subghz](/it/dev/js-subghz), [infrared](/it/dev/js-infrared), [blebeacon](/it/dev/js-blebeacon), [usbdisk](/it/dev/js-usbdisk), [i2c](/it/dev/js-i2c), [spi](/it/dev/js-spi), [vgm](/it/dev/js-vgm) — non ci sono né nel firmware di serie né nella documentazione ufficiale |

## Lavorare con il dispositivo

| Pagina | Cosa ci trovi |
|---|---|
| [Interfaccia a riga di comando (CLI)](/it/dev/cli) | Collegarsi via seriale USB; tutti i comandi CLI con i relativi argomenti |
| [Aggiornamenti OTA](/it/dev/ota) | Come funziona l'updater, campi del manifest, codici di errore `[XX-YY]`, creazione dei pacchetti |
| [Formato tarball heatshrink](/it/dev/tar-heatshrink) | Il contenitore `.tar.hs` usato per le risorse nei pacchetti di aggiornamento |
| [Hardware](/it/dev/hardware) | Specifiche tecniche, schemi, modelli 3D, disegni di moduli e devboard |

## Test

| Pagina | Cosa ci trovi |
|---|---|
| [Unit test](/it/dev/unit-tests) | Compilare ed eseguire l'app `unit_tests` sul dispositivo, aggiungere test propri |
| [Test di integrazione](/it/dev/testing) | Il piano di test manuale usato prima di integrare PR e release |

## Altre risorse utili

- Documentazione ufficiale per sviluppatori (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — è lì che si cercano le API del firmware che questa wiki non copre: programmazione di sistema, sviluppo di app, JavaScript, moduli di espansione, formati dei file
- Configurazione di un workspace CLion — [guida di Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- Tutorial per un plugin "Hello world!": [in inglese (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [in russo (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [Come scrivere la propria app](https://flipper.atmanos.com/docs/overview/intro)

### Struttura del repository del firmware

| Cartella | Contenuto |
|---|---|
| `applications` | Applicazioni e servizi usati nel firmware |
| `assets` | Asset usati da applicazioni e servizi |
| `furi` | Furi Core: primitive e utilità a livello di sistema operativo |
| `debug` | Strumenti di debug: plugin GDB, file SVD, ecc. |
| `documentation` | Sorgenti della documentazione e configurazioni dei generatori |
| `firmware` | Codice sorgente del firmware |
| `lib` | Librerie proprie e di terze parti, driver |
| `site_scons` | Utilità per la compilazione |
| `scripts` | Script accessori e librerie Python |
| `targets` | Definizioni dei target hardware (`f7`, `f18`) |

Molte di queste cartelle hanno un proprio `ReadMe.md` — vale la pena leggerlo.
