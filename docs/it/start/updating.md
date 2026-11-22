---
title: Aggiornare
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Aggiornare

Unleashed viene aggiornato spesso. Aggiornare funziona esattamente come installare: la nuova versione va messa
**sopra** quella attuale. Non serve tornare al firmware ufficiale né installare nulla nel mezzo.

## Come aggiornare

**Consigliato: [qUnleashed](/it/mobile/qunleashed-app)**, l'app companion di Unleashed per **Android, iOS,
Windows, macOS e Linux** (USB su tutti tranne iOS, che usa il Bluetooth). Scarica il nuovo firmware da sola.

1. Installa o aggiorna qUnleashed dalla sua
   [pagina delle release](https://github.com/DarkFlippers/qUnleashed/releases).
2. Collega il Flipper via USB o via Bluetooth.
3. Apri l'**aggiornamento del firmware**, scegli il canale **Unleashed** (**Release** o **Dev**) e la build che
   usi: **base**, **extra apps** o **compact**.
4. Avvia l'installazione e attendi che il Flipper completi tutte le fasi.

Se il Flipper ha smesso di avviarsi, **Repair from DFU mode** nella stessa app lo riflasha via USB
([Ripristino](/it/start/recovery#firmware-recovery)).

Le alternative, tutte descritte nei [metodi di installazione](/it/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → scegli Release o Dev → Install.
2. **qFlipper**: **Install from file** con il nuovo `flipper-z-f7-update-(version).tgz`.
3. **App mobile**: canale di aggiornamento custom con il `.tgz`.
4. **Offline**: copia `f7-update-(version)` in `/ext/update/` e apri `update.fuf` dall'Archive.

::: warning Non premere "Update" in qFlipper o nell'app ufficiale
Il pulsante **Update** integrato in qFlipper e nella Flipper Mobile App usa il server di aggiornamento **ufficiale**
e sostituisce Unleashed con il firmware stock. Per Unleashed usa l'aggiornamento di qUnleashed, **Install from
file**, il canale custom o il Web Installer.
:::

## Release o dev?

| | Release | Dev |
|---|---|---|
| Stabilità | Testata | Può avere bug |
| Nuove funzioni | A ogni release | Appena vengono integrate |
| Dove si trova | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Le build dev vengono compilate automaticamente dagli ultimi commit. La build dev precedente viene eliminata dal sito
quando ne viene caricata una nuova. Segnala i bug su
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Cosa sopravvive a un aggiornamento

- **I tuoi file sulla scheda microSD**: chiavi, card, telecomandi e script salvati rimangono intatti.
- **Il tuo nome personalizzato**: è salvato sulla scheda in `/ext/dolphin/name.settings`
  ([Nome personalizzato del Flipper](/it/start/custom-name)).
- **Le impostazioni**: di solito vengono conservate. **Eccezione:** quando una release cambia la struttura di un file
  di impostazioni, quel file viene riportato ai valori predefiniti una volta. Succede solo in release specifiche. Se
  dopo un aggiornamento le impostazioni del desktop (PIN, preferiti…) si azzerano, reimpostale e controlla il
  changelog.
- Le **app integrate** in `/ext/apps/` vengono sostituite solo con le versioni del nuovo firmware. I pacchetti di app
  aggiuntive non possono mai sovrascriverle o riportarle a una versione precedente.

## Controllare la propria versione

- **Main Menu → Settings → About**: versione del firmware, data di build, branch e commit;
- oppure tieni premuto <kbd>↓</kbd> sul desktop per la schermata di debug/informazioni.

## Dove leggere cosa è cambiato

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases): il changelog di ogni release;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) sul branch dev: cosa
  arriverà nella prossima release;
- aggiornamenti delle app: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Il server di aggiornamento di Unleashed

Unleashed gestisce un proprio server di aggiornamento con lo stesso formato di quello ufficiale:
`https://up.unleashedflip.com/directory.json`. Le app ufficiali non possono essere indirizzate a questo server senza
essere ricompilate. **uFBT** accetta questa URL come argomento per compilare le app contro l'SDK di Unleashed (vedi
[Compilare il firmware](/it/dev/build)).

## Se un aggiornamento fallisce

1. Riavvia con <kbd>←</kbd> + <kbd>BACK</kbd> e riprova.
2. Prova un metodo diverso (qUnleashed ↔ Web Installer ↔ qFlipper ↔ offline).
3. Controlla la scheda SD (**Settings → Storage → About SD Card**), oppure formattala dopo un backup.
4. Se continua a fallire: [Ripristino](/it/start/recovery).
