---
title: Usare Bad USB
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Usare Bad USB

Questa pagina illustra l'esecuzione di uno script via USB e via Bluetooth, e spiega ogni voce del menu **Config**. Le
etichette di menu e i messaggi sono esattamente quelli che compaiono nel firmware.

::: warning
Esegui gli script solo su computer di tua proprietà o che ti è consentito testare. Leggi uno script prima di
eseguirlo: farà esattamente quello che dice, con i diritti del tuo utente.
:::

## Prima di iniziare

- Serve una scheda microSD con le risorse del firmware. Senza di essa l'app mostra *"No SD card or app data found.
  This app will not work without required files."*
- Metti il tuo script (`.txt`) in `/ext/badusb/` (le sottocartelle vanno bene).
- **La modalità USB prende il controllo della porta USB del Flipper.** Se qFlipper o la [CLI](/it/dev/cli) sono
  collegati via USB, l'app mostra *"Connection Is Active! Disconnect from PC or phone to use this function."* Chiudi
  prima qFlipper.

## La schermata principale

1. Apri `Main Menu → Bad USB`.
2. Scegli uno script nel file browser. Si apre la schermata dello script.

La riga in alto mostra il nome dello script, sotto di essa il layout di tastiera tra parentesi, `(default)` oppure per
esempio `(de-DE)`, e il tempo trascorso; in modalità BLE, invece, il PIN di pairing. L'immagine al centro mostra una
spina USB o un simbolo Bluetooth.

![Schermata di uno script Bad USB: demo_windows caricato, 0/34 righe, suggerimenti Config / Run / BLE](/screens/badusb/script_ready.png)

| Stato | Testo a schermo | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Inattivo / Done / non collegato | avanzamento oppure *Connect to device* | **Run** | **Config** | passa a **BLE** / **USB** |
| In attesa della connessione dopo Run | *Will run on connect* | **Cancel** | | |
| In esecuzione o in un `DELAY` | `line/total`, percentuale, `Delay Ns` | **Stop** | | **Pause** |
| In pausa | *Paused* | **End** | | **Resume** |
| In attesa a `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Errore | *ERROR:* + `line N` + messaggio | | | |

Se premi **Run** prima che l'host abbia riconosciuto il Flipper, l'app attende (*"Will run on connect"*) e avvia lo
script automaticamente **1,5 s dopo** che la connessione è attiva, così l'host ha il tempo di installare la tastiera.

Mentre non è collegato alcun host, la clessidra e *Connect to device* prendono il posto dell'avanzamento:

![Bad USB in attesa di un host USB, lo schermo mostra Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> lascia la schermata dello script e torna al file browser.

## Eseguire via USB

1. Chiudi qFlipper sul computer.
2. `Main Menu → Bad USB` → seleziona lo script.
3. Assicurati che lo schermo mostri l'immagine **USB**; se no, premi <kbd>→</kbd> **USB**.
4. Facoltativo: <kbd>←</kbd> **Config → Keyboard Layout (global)** per far corrispondere il layout del computer
   (predefinito `en-US`).
5. Collega il Flipper al computer con un cavo USB.
6. Premi <kbd>OK</kbd> **Run**. L'avanzamento `line/total` arriva al 100 %.

![Bad USB che esegue uno script: 32 %, riga 12 di 34, suggerimenti Stop e Pause](/screens/badusb/script_running.png)

![Bad USB in modalità USB](/img/remote/d49323518c0b4b18.jpg)

## Eseguire via Bluetooth (BLE)

1. Assicurati che il Bluetooth sia abilitato sul Flipper (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → seleziona lo script.
3. Premi <kbd>→</kbd> **BLE**; compare l'immagine del Bluetooth. Il Flipper inizia ad annunciarsi come tastiera.
4. Sul computer o sul telefono apri le impostazioni Bluetooth e collegati a
   **`BadUSB <nome del tuo Flipper>`** (il nome predefinito).
5. Conferma il pairing su entrambi i dispositivi. Con la modalità di pairing predefinita lo stesso PIN è mostrato su
   entrambi gli schermi; verifica che corrisponda. Il PIN è mostrato anche nella schermata dello script.
6. Premi <kbd>OK</kbd> **Run**.
7. Per rimuovere il pairing più tardi: <kbd>←</kbd> **Config → Remove BLE Pairing**, poi dimentica il dispositivo
   anche sull'host.

![Bad USB in modalità BLE](/img/remote/083420027c3f836c.jpg)

::: tip Identità e pairing separati
In modalità BLE il Flipper usa un **indirizzo MAC proprio** (derivato dal MAC del Flipper) e un proprio archivio dei
pairing, separati dal profilo Bluetooth normale. Accoppiare un computer con Bad USB non rompe quindi il pairing con la
Flipper Mobile App. Quando esci dall'app, il profilo Bluetooth normale viene ripristinato.
:::

## Script che cambiano modalità da sé

Se la **prima riga** di uno script è un comando `ID` (USB) oppure `BLE_ID` / `BT_ID` (Bluetooth), l'app passa
automaticamente a quella modalità quando lo script viene aperto e applica l'identità indicata. Puoi comunque passare da
una all'altra manualmente con <kbd>→</kbd>. Vedi
[Formato degli script → ID del dispositivo](/it/badusb/script-format#device-id).

## Menu Config

<kbd>←</kbd> **Config** è disponibile solo quando lo script non è in esecuzione. Il contenuto dipende dalla modalità
di connessione attuale.

### Comuni

| Voce | Valori | Cosa fa |
|---|---|---|
| **Keyboard Layout (global)** | file browser | Seleziona un file `.kl` da `/ext/badusb/assets/layouts/`. Si applica a ogni script che non imposta il proprio con `DUCKY_LANG`. Vedi [Layout di tastiera](/it/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Come <kbd>→</kbd> nella schermata principale. L'elenco sottostante cambia di conseguenza. |

### Modalità BLE

| Voce | Valori | Cosa fa |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | ON (predefinito): crea un bond con l'host e lo ricorda, così si ricollega senza rifare il pairing. OFF: pairing ogni volta. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo`: pairing senza PIN. `PIN Type`: il Flipper mostra un PIN che digiti sull'host. `PIN Y/N` (predefinito): entrambi mostrano un PIN; confermi che corrisponda. |
| **Set Device Name** | testo | Nome Bluetooth (*"Set BLE device name"*). Vuoto = `BadUSB <nome del Flipper>`. |
| **Set MAC Address** | 6 byte | *"Set BLE MAC address"*. |
| **Randomize MAC Address** | azione | Genera un MAC statico casuale e mostra **Done**. Utile per presentarsi come una tastiera "nuova". |
| **Restore BLE Defaults** | azione | Azzera nome e MAC, Persist Pairing su ON, Pairing Mode su `PIN Y/N`. |
| **Remove BLE Pairing** | azione | *"Unpair the Device?"* → **Unpair** dimentica tutti gli host accoppiati con Bad USB. |

### Modalità USB

| Voce | Valori | Cosa fa |
|---|---|---|
| **Set Manufacturer Name** | testo | Stringa del produttore USB (*"Set USB manufacturer name"*). |
| **Set Product Name** | testo | Stringa del prodotto USB (*"Set USB product name"*). |
| **Set VID and PID** | 4 byte | *"Set USB VID:PID"*. Permette al Flipper di presentarsi con un dato ID vendor/prodotto. |
| **Randomize VID and PID** | azione | VID e PID casuali, mostra **Done**. |
| **Restore USB Defaults** | azione | Azzera VID/PID e i nomi: viene usata l'identità di tastiera predefinita del Flipper. |

Tutto questo, insieme al layout e alla modalità scelti, viene salvato in `/ext/badusb/.badusb.settings`. Una riga
`ID` / `BLE_ID` in uno script sovrascrive l'identità solo per quello script.

## Risoluzione dei problemi

| Problema | Cosa provare |
|---|---|
| Il testo digitato è incomprensibile (`z` e `y` scambiate, simboli sbagliati) | Il layout di tastiera dell'host non corrisponde a quello dell'app. Scegli il layout giusto in Config, oppure aggiungi `DUCKY_LANG` allo script. Su un PC con più lingue di inserimento, porta l'host sulla lingua del layout prima di eseguire (per esempio inglese, non russo). |
| Mancano dei caratteri | L'host è troppo lento. Aggiungi `DEFAULT_STRING_DELAY 10` (o più) e dei `DELAY` più lunghi dopo l'apertura delle finestre. |
| Lo script parte prima che la finestra sia aperta | Aumenta il `DELAY` dopo `GUI r`, `ENTER` e simili. |
| *ERROR: line N* | La riga contiene un comando sconosciuto, un errore di battitura, un numero non valido o testo non ASCII. I comandi sono **sensibili alle maiuscole** (`STRING`, non `string`). Vedi [Formato degli script](/it/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` contiene caratteri non ASCII (accenti, cirillico…). Usa `ALTSTRING`/`ALTCHAR` su Windows, oppure digita quel testo in un altro modo. |
| *Connection Is Active!* | Scollega qFlipper / la CLI dalla porta USB. |
| macOS apre l'*Assistente Impostazione Tastiera* | Usa una riga `ID` con il VID/PID di una tastiera Apple (vedi l'esempio `demo_macos.txt`) oppure chiudi semplicemente l'assistente. |
| L'host BLE non trova il Flipper | Abilita il Bluetooth sul Flipper, resta nella schermata dello script in modalità BLE, rimuovi i vecchi pairing da entrambe le parti (`Remove BLE Pairing`). |

## Pagine correlate

- [Formato degli script](/it/badusb/script-format)
- [Esempi](/it/badusb/examples)
- [Layout di tastiera](/it/badusb/layouts)
