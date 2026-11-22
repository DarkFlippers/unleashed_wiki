---
title: Installare Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Installare Unleashed

Ci sono diversi modi per installare Unleashed Firmware. Tutti installano lo stesso pacchetto di aggiornamento, che
contiene il firmware, l'updater e tutti gli asset (app, librerie IR, impostazioni Sub-GHz e così via).

::: tip Prima di iniziare
- **Nessun aggiornamento intermedio necessario:** installa Unleashed direttamente sopra il firmware stock o una versione precedente di Unleashed.
- Assicurati che la **scheda microSD sia inserita**. L'aggiornamento viene scompattato sulla scheda, e le app
  risiedono lì.
- Carica la batteria. Un aggiornamento completo richiede diversi minuti.
:::

## Quale file scaricare {#which-file-to-download}

I file delle release si chiamano `flipper-z-f7-update-(version)(e / c).tgz`:

| Parte | Significato |
|---|---|
| `flipper-z` | Per il dispositivo Flipper Zero |
| `f7` | Target hardware. È lo stesso per ogni Flipper Zero |
| `update` | Pacchetto di auto-aggiornamento: updater, firmware e tutti gli asset |
| `(version)` | Versione del firmware |
| suffisso | Variante del pacchetto di app, vedi sotto |

| Suffisso | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(nessuno)* | ✅ | — |
| `c` | — | — |

- **`e`**: tutto. Pacchetto base più il pacchetto extra di app della community. Scegli questo se hai dubbi.
- **Senza suffisso**: solo il pacchetto base di app della community.
- **`c`** ("clean"): nessuna app della community.

Le **app di sistema integrate** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer,
Sub-GHz RAW Edit, SIM800, FindMy Flipper, telecomandi USB/BT, Snake…) arrivano **con il firmware stesso** e sono
presenti in **tutte** le varianti, `c` compresa. Vedi
[Cosa aggiunge Unleashed](/it/start/unleashed-features#built-in-apps).

Altri file delle release:
- `flipper-z-any-scripts-(version).tgz`: la cartella `scripts` per lo sviluppo di firmware e app;
- `flipper-z-f7-sdk-(version).zip`: SDK per lo sviluppo di app e per uFBT.

## Metodo 1: qUnleashed (consigliato)

[qUnleashed](/it/mobile/qunleashed-app) è l'app companion del team di Unleashed. Scarica e installa il firmware
da sola, quindi non c'è nessun file da scegliere. Funziona su **Android, iOS, Windows, macOS e Linux** — via USB
su tutti tranne iOS, che si collega via Bluetooth.

1. Installa qUnleashed per il tuo sistema dalla sua
   [pagina delle release](https://github.com/DarkFlippers/qUnleashed/releases).
2. Collega il Flipper via USB, oppure accoppialo via Bluetooth (su iOS il Bluetooth è l'unica via).
3. Apri l'**aggiornamento del firmware** nell'app.
4. Scegli il canale **Unleashed**, **Release** o **Dev**.
5. Scegli la build: **base**, **extra apps** o **compact** ([cosa contengono](#which-file-to-download)).
6. Avvia l'installazione e attendi. Il Flipper si riavvia nell'updater e completa tutte le fasi.

Se il Flipper non si avvia più, usa **Repair from DFU mode** nella stessa app per riflasharlo via USB. Vedi
[Ripristino](/it/start/recovery#firmware-recovery).

I metodi qui sotto sono alternative. Usane uno se qUnleashed non va bene per la tua configurazione.

## Metodo 2: Unleashed Web Installer

Ti servono un **browser basato su Chromium** (Chrome, Edge, Opera, Brave, Vivaldi) e un cavo USB.

1. Chiudi **qFlipper** e qualsiasi altra pagina web del Flipper: occupano la porta seriale.
2. Collega il Flipper via USB.
3. Apri **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Premi **Connect** e scegli il tuo Flipper nella finestra del browser.
5. Seleziona il branch **Release** o **Dev**.
6. Premi **Install** e attendi. Il Flipper si riavvia nell'updater e completa tutte le fasi.
7. Fatto. Tutti gli asset sono installati.

## Metodo 3: aggiornamento web di Flipper Lab

1. Apri la [pagina dell'ultima release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Collega il Flipper e clicca il link **Install via Web Updater**.
3. Nella pagina del web updater premi **Connect**, poi **Install**.
4. Attendi la fine dell'aggiornamento.

![Web updater](/img/remote/b803c9d8ec0350d6.png)

## Metodo 4: qFlipper (1.2.0 o più recente)

1. Installa [qFlipper](https://flipperzero.one/update) 1.2.0+ (le versioni precedenti non riescono a installare i
   file `.tgz`).
2. Scarica `flipper-z-f7-update-(version).tgz` dalle [release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Avvia qFlipper e collega il Flipper.
4. Clicca **Install from file** e seleziona il `.tgz` scaricato.
5. L'aggiornamento parte. Attendi che finisca.

![Install from file in qFlipper](/img/remote/f1a3ede83085d040.png)

::: warning
**Non** usare il pulsante **Update** di qFlipper dopo aver installato Unleashed: installa il firmware **ufficiale**
sopra Unleashed. Usa invece **Install from file**.
:::

## Metodo 5: Flipper Mobile App

### Android, con un file `.tgz`
1. Scarica `flipper-z-f7-update-(version).tgz` sul telefono.
2. Nell'app Flipper tocca **Update channel** e scegli **Custom**.
3. Seleziona il `.tgz` scaricato e tocca **Update**.
4. Attendi la fine dell'aggiornamento.

### Android, con il link del web updater
1. Nella pagina della release tocca **Install via Web Updater**.
2. Quando viene chiesto se aprire con il browser o con l'app Flipper, scegli la **Flipper App**.
3. Prosegui con l'installazione e attendi.

### iOS
1. Scarica `flipper-z-f7-update-(version).tgz`.
2. Aprilo nell'app **Files**. Tocca **Share** e scegli la **Flipper App**.
3. Nell'app Flipper tocca il pulsante verde **Update**. Verifica che il canale di aggiornamento mostri
   `Custom flipper-z-f7-update...`.
4. Attendi. **L'app iOS può mostrare un errore alla fine, ma il Flipper viene aggiornato correttamente.**

## Metodo 6: aggiornamento offline dalla scheda microSD

Non serve nessun programma sul computer. Funziona da PC o da telefono.

1. Scompatta `flipper-z-f7-update-(version).tgz` (o `.zip`). Dentro c'è una cartella `f7-update-(version)` che
   contiene `update.fuf`, `resources.tar` e altri file.
2. Inserisci la scheda in un PC o in un telefono, oppure carica i file con qFlipper.
3. Crea una cartella `update` nella **radice** della scheda e sposta `f7-update-(version)` al suo interno:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Verifica che ci siano **tutti** i file. L'app Files di iOS può mostrarne solo 3 su 6: usa un'altra app per
   scompattare, un PC o Android.
5. Rimetti la scheda nel Flipper.
6. Apri **Archive** (<kbd>↓</kbd> dal desktop), vai alla scheda **Browser**, raggiungi
   `update/f7-update-(version)/` e apri `update.fuf`.
7. L'aggiornamento parte. Attendi che tutte le fasi finiscano.

![Aggiornamento offline](/img/remote/92717373349f3b7c.png)

## Dopo l'installazione

- La schermata About (**Settings → About**) mostra le informazioni sul firmware Unleashed e sulla versione.
- Al primo avvio dopo un aggiornamento il Flipper scompatta le risorse sulla scheda. È normale.
- Leggi [Cosa aggiunge Unleashed](/it/start/unleashed-features) e configura il dispositivo seguendo
  [Impostazioni](/it/start/settings).

## Risoluzione dei problemi

| Problema | Soluzione |
|---|---|
| Il browser non si connette | Chiudi qFlipper e le altre schede di Flipper Lab. Usa un browser Chromium. Prova un altro cavo o un'altra porta |
| L'aggiornamento fallisce o si blocca | Riavvia con <kbd>←</kbd> + <kbd>BACK</kbd>, controlla la scheda SD, prova un altro metodo |
| L'app mobile non si connette dopo l'installazione | Rimuovi il Flipper dall'app e dalle impostazioni Bluetooth del telefono. Poi **Settings → Bluetooth → Unpair All Devices** sul Flipper e accoppia di nuovo |
| La retroilluminazione è spenta dopo l'installazione | Vedi le [FAQ](/it/start/faq#backlight-does-not-work) (impostazione della mod RGB) |
| Il dispositivo è morto / brickato | [Ripristino](/it/start/recovery) |
