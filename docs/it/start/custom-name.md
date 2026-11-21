---
title: Nome personalizzato del Flipper
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Nome personalizzato del Flipper

Ogni Flipper ha un nome di fabbrica. Compare nel Passport, in **About**, negli elenchi dei dispositivi Bluetooth e in
qFlipper. Unleashed ti permette di sostituirlo con un nome tuo.

::: tip Unleashed
Il firmware stock non ha un menu per rinominare il dispositivo. In Unleashed si trova in
**Settings → Desktop → Change Flipper Name**, e il nome **sopravvive agli aggiornamenti del firmware** perché è
salvato sulla scheda microSD.
:::

## Impostare un nome

1. Vai in **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Scrivi il nuovo nome. L'intestazione della tastiera dice `Leave empty for default`.
   - **da 2 a 8 caratteri**;
   - **solo lettere latine e cifre** (`A–Z`, `a–z`, `0–9`). Qualsiasi altro carattere fa comparire *"Please only enter
     letters and numbers!"*.
3. Seleziona **Save**.
4. Compare il messaggio **`Name is set!`** / *"Your Flipper will be restarted on exit."*
5. Esci dalle Settings con <kbd>BACK</kbd>. Il Flipper **si riavvia automaticamente**.
6. Dopo il riavvio il nuovo nome compare nel Passport, in **Settings → About** e via Bluetooth.

## Tornare al nome di fabbrica

1. Apri **Settings → Desktop → Change Flipper Name**.
2. Cancella tutti i caratteri e lascia il campo **vuoto**.
3. Seleziona **Save** ed esci dalle Settings. Il Flipper si riavvia con il nome originale.

## Come funziona

- Il nome è salvato in **`/ext/dolphin/name.settings`** sulla scheda SD:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- All'avvio il servizio `namechanger` attende la scheda SD, legge questo file e applica il nome se è valido:
  intestazione e versione corrette, da 2 a 8 caratteri, solo lettere e cifre. Poi riavvia la seriale USB e i profili
  Bluetooth, così da usare il nuovo nome.
- Salvando un nome vuoto il file viene eliminato.
- Il servizio gira solo all'avvio normale, non nell'updater né in DFU.

Poiché il nome risiede sulla scheda, resta anche dopo gli aggiornamenti. Si perde se formatti o sostituisci la scheda,
oppure se elimini il file.

## Risoluzione dei problemi

| Problema | Soluzione |
|---|---|
| Il nome non è cambiato | Sei uscito dalle Settings (il riavvio lo applica)? La scheda SD è inserita? Il nome ha da 2 a 8 lettere/cifre? Un nome di un solo carattere viene salvato ma ignorato all'avvio |
| L'app mobile non si connette più | Il nome Bluetooth è cambiato. Rimuovi il Flipper dall'app **e** dalle impostazioni Bluetooth del telefono, esegui **Settings → Bluetooth → Unpair All Devices** sul Flipper, poi accoppia di nuovo |
| Un file del nome copiato da altrove viene ignorato | Controlla l'intestazione `Flipper Name File`, `Version: 1` e le regole sul nome |
