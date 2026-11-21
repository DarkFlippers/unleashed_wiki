---
title: Risoluzione dei problemi con le app
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Risoluzione dei problemi con le app

Quando un'app non riesce ad avviarsi, il Flipper mostra `Error: <nome>` con un breve suggerimento e un link
`r.flipper.net/err_0X`. Questa pagina spiega ogni messaggio così come appare in Unleashed.

::: tip Unleashed
Unleashed non blocca le app compilate per una versione diversa delle API. Invece degli errori **Outdated App** /
**Outdated Firmware** del firmware di serie mostra un avviso e lascia decidere a te, vedi
[App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New {#app-too-old-app-too-new}

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

La **versione major delle API** dell'app è diversa da quella del firmware: **App Too Old** significa che l'app è stata
compilata per API più vecchie, **App Too New** per API più recenti.

- Premi **Continue** (<kbd>→</kbd>) per provare comunque. Molte app funzionano, ma un'app che chiama una funzione
  modificata può andare in crash.
- Premi <kbd>Back</kbd> per annullare.
- La soluzione vera: aggiorna l'app (prendila dal pacchetto Unleashed corrente oppure ricompilala per l'SDK attuale)
  oppure, in caso di **App Too New**, aggiorna il firmware.

## Error: App Not Found (err_01)

`Update firmware or app`

| Causa | Rimedio |
|---|---|
| il file dell'app è stato eliminato dalla scheda SD | reinstalla l'app, oppure reinstalla il firmware (per le app di sistema) |
| un'app mobile vecchia o in versione beta ha aperto un'app del catalogo che non è presente sulla scheda | installa l'app mobile Flipper ufficiale dall'App Store / Google Play e reinstalla l'app |

Un messaggio affine, **SD card needed** / `Install SD card to run this app`, indica che un'app del menu risiede sulla
scheda SD e non è inserita alcuna scheda. **Update needed** / `Update firmware to run this app` significa che la
scheda è presente ma il file dell'app manca: reinstalla il firmware con la scheda inserita.

## Error: Invalid File (err_02)

`Update the app`. Il `.fap` è danneggiato: intestazione ELF corrotta, file incompleto (copia interrotta) o sezioni che
non possono essere caricate. Copia o installa di nuovo l'app.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. Il manifest (una sezione ELF speciale con la versione delle API e le informazioni sull'app)
non può essere letto. Il file è corrotto, oppure app e firmware sono troppo distanti tra loro. Aggiorna l'app; se è
più recente del tuo firmware, aggiorna il firmware.

## Error: Missing Imports (err_04)

`Update firmware or app`. L'app chiama funzioni che il tuo firmware non esporta.

| Causa | Rimedio |
|---|---|
| l'app è stata compilata per un firmware più recente | aggiorna Unleashed |
| l'app è stata compilata per un altro fork (usa funzioni proprie di quel fork) | cerca una build dell'app per Unleashed, oppure ricompilala con l'SDK Unleashed |

## Error: HW Target Mismatch (err_05)

`App not supported`. L'app è stata compilata per un target hardware Flipper diverso. Non può essere eseguita su questo
dispositivo.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. Un FAP viene caricato in RAM; se l'heap è frammentato o se
c'è troppo in esecuzione (per esempio un beacon BLE in background o un'app di grandi dimensioni), non ci sta. Premi
**Reboot** e avvia l'app subito dopo il riavvio.

## Se ancora non funziona

1. Aggiorna all'ultima release di Unleashed, vedi [Aggiornamento](/it/start/updating).
2. Reinstalla l'app dal [pacchetto di app](/it/apps/catalog#base-and-extra-packs) corrente o dal catalogo
   ([App sulla scheda SD](/it/apps/sd-card-apps)).
3. Se un'app fa andare in crash il Flipper, riavvialo con <kbd>←</kbd> + <kbd>Back</kbd>; vedi
   [Ripristino](/it/start/recovery) se non si avvia più.
4. Chiedi nelle chat della comunità, vedi [FAQ](/it/start/faq).

## Pagine correlate

- [App sulla scheda SD (.fap)](/it/apps/sd-card-apps)
- [App incluse in Unleashed](/it/apps/catalog)
