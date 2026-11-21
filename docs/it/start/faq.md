---
title: FAQ
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# FAQ

## Generale

### Ho appena comprato un Flipper Zero. Da dove comincio?

Leggi [Primo avvio](/it/start/first-start), poi [Installare Unleashed](/it/start/install). Il sito ufficiale
[flipperzero.one](https://flipperzero.one/) e [docs.flipper.net](https://docs.flipper.net/) coprono le basi del
firmware stock.

### Firmware ufficiale, Unleashed o un altro fork?

Se hai dubbi, parti dal firmware ufficiale. Se ti servono più funzioni, o vuoi il Sub-GHz senza blocchi regionali,
installa **Unleashed**: un fork del firmware ufficiale con molte funzioni nuove e app preinstallate (prova la build
`e`). Esistono altri fork basati su Unleashed per chi vuole sperimentare di più con l'interfaccia. Puoi anche creare
un fork tuo.

**Prima di segnalare un bug, controlla quale firmware stai usando.** Non segnalare nel repository o nelle chat di
Unleashed problemi che riguardano altri fork o il firmware stock.

### Dove posso vedere le differenze rispetto al firmware ufficiale?

[Cosa aggiunge Unleashed](/it/start/unleashed-features).

### Quale build devo installare? Cosa significano `e` e `c`?

`e` = app base + app extra della community, senza suffisso = app base, `c` = nessuna app della community. Le app di
sistema integrate ci sono in tutte. Dettagli: [Installare Unleashed](/it/start/install#which-file-to-download).

### Cosa sono le build dev?

Build automatiche degli ultimi commit sul branch `dev` non ancora rilasciati. **Possono contenere bug.** Si ottengono
dal Web Installer (Dev), su [dev.unleashedflip.com](https://dev.unleashedflip.com), su Telegram
[@kotnehleb](https://t.me/kotnehleb) o nel canale Discord `unleashed-development`. La build precedente viene eliminata
quando ne viene caricata una nuova, e quelle vecchie restano solo come file nel canale Telegram. Hai trovato un bug?
[Segnalalo](https://github.com/DarkFlippers/unleashed-firmware/issues).

### Cos'è il server di aggiornamento di Unleashed?

`https://up.unleashedflip.com/directory.json`. Usa lo stesso formato di quello ufficiale, ma le app ufficiali non
possono essere indirizzate a questo server senza essere ricompilate. Puoi passarlo a **uFBT** per compilare app
contro l'SDK di Unleashed. Resta online e si aggiorna automaticamente.

### Quali app sono incluse?

Le app di sistema integrate, più il pacchetto base (e il pacchetto extra nelle build `e`) da
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).
Vedi [Cosa aggiunge Unleashed](/it/start/unleashed-features#built-in-apps).

### Come posso sostenere il progetto?

Vedi la
[sezione sul supporto](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project)
del ReadMe. Anche un semplice "grazie" è utile. Ogni build è e rimarrà gratuita e open source.

## Dopo l'installazione

### La retroilluminazione non funziona dopo l'installazione di Unleashed {#backlight-does-not-work}

Hai attivato l'impostazione della **mod di retroilluminazione RGB**, pensata solo per i Flipper con la mod hardware
RGB. Vai in **Settings → LCD and Notifications → RGB Mod Settings** e imposta **RGB backlight installed** su `OFF`.
Se la mod ce l'hai davvero, attivala invece da lì.

### L'app mobile non si connette (dopo l'installazione di Unleashed o il cambio di nome)

1. Nell'app mobile tocca **Forget Flipper**.
2. In **Impostazioni → Bluetooth** del telefono trova il Flipper e scegli **Dimentica questo dispositivo**.
3. Sul Flipper: **Settings → Bluetooth → Unpair All Devices**, poi confermi.
4. Verifica che il Bluetooth sia `ON` sul Flipper, poi accoppia di nuovo dall'app.

### Le mie impostazioni (PIN, preferiti, desktop…) si sono azzerate dopo un aggiornamento

Reimpostale. Un file di impostazioni viene azzerato solo quando una release ne cambia la struttura, e questo succede
in release specifiche, non ogni volta. Controlla i changelog delle release successive alla tua versione precedente.

### Il Flipper non si connette a Chrome / al Web Installer

Nella maggior parte dei casi **qFlipper è aperto**, oppure è connessa una seconda pagina web o scheda di Flipper Lab.
Solo un programma alla volta può usare la porta. Chiudi gli altri e riprova. Usa un browser basato su Chromium.

## Problemi

### Il Flipper è crashato, si è congelato o si blocca

Tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per riavviare. Altro: [Combinazioni di tasti](/it/start/key-combos).

### Il Flipper non funziona affatto. Come ripristino il firmware?

[Ripristino → Ripristino del firmware](/it/start/recovery#firmware-recovery).

### Ho dimenticato il PIN

Scollega l'USB, spegni il Flipper, tieni premuti <kbd>↑</kbd> + <kbd>BACK</kbd> per circa 5 s finché non compare la
schermata di reset, poi tieni premuto <kbd>→</kbd>. Impostazioni e PIN vengono azzerati, ma i file sulla scheda SD
restano. Dettagli: [Ripristino → Azzerare un PIN dimenticato](/it/start/recovery#reset-pin).

### Il Flipper è lento e non risponde bene

1. Usa una scheda microSD di marca e di buona qualità. Il Flipper usa l'SPI, e non tutte le schede lo gestiscono bene.
2. In **Settings → System** controlla:
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Carica la batteria. Anche una batteria scarica influisce sulle prestazioni.

### Come cambio il nome del Flipper, o come lo riporto all'originale?

**Settings → Desktop → Change Flipper Name**: inserisci un nome, **Save**, esci dalle Settings e il Flipper si riavvia.
Salva un nome vuoto per tornare al valore predefinito. Vedi
[Nome personalizzato del Flipper](/it/start/custom-name).

## Sub-GHz

### Esiste un blocco regionale? Come sblocco il Sub-GHz?

In **Unleashed non esiste nessun blocco regionale**: ogni frequenza supportata dal chip funziona subito. Andare
**oltre le specifiche del chip** è possibile, ma può danneggiare l'hardware:
[Impostazioni pericolose](/it/start/dangerous-settings).

### Quali protocolli sono supportati, e con quale frequenza e modulazione?

[Sistemi supportati](/it/subghz/supported-systems).

### Come aggiungo frequenze?

[Frequenze e preset](/it/subghz/frequencies).

### Posso clonare il telecomando della mia auto per usare il Flipper come chiave?

**No.** Le chiavi auto e la maggior parte dei telecomandi dei garage usano i **rolling code**. Ritrasmettere un
segnale acquisito (per esempio con Read RAW) desincronizza il contatore. Nel caso peggiore il telecomando originale
viene disaccoppiato o messo in blacklist, e per riaccoppiarlo servono gli strumenti dell'assistenza.

**Perché:** il ricevitore ricorda l'ultimo valore del contatore ricevuto da un telecomando (quante volte è stato
premuto un pulsante qualsiasi). Supponiamo che il telecomando originale abbia inviato il contatore `0002` e che tu
invii lo stesso segnale dal Flipper con `0003`: il ricevitore lo accetta. Ma il telecomando originale è ancora a
`0002`, quindi alla pressione successiva invia `0003`, che il ricevitore ha già visto, e non reagisce. Questo non è
ancora un disaccoppiamento: premi l'originale qualche volta in più per "superare" il Flipper (`0004`) e torna a
funzionare. Ma se questa rincorsa continua, il divario può crescere fino a **oltre 100 pressioni**, e a quel punto il
telecomando originale non può più essere recuperato senza riaccoppiarlo al ricevitore.

**Cosa fare invece:**
- usa solo **un** telecomando: o il Flipper o l'originale;
- **meglio ancora:** crea un **nuovo telecomando** sul Flipper con **Add manually** e accoppialo al ricevitore come
  telecomando separato ([Add manually](/it/subghz/add-manually),
  [Programmare un telecomando nuovo](/it/subghz/remote-prog));
- se devi usarli entrambi, usali alternandoli, così i contatori non si allontanano mai troppo.

Altro: [Rolling code](/it/subghz/rolling-codes), [Modalità contatore](/it/subghz/counter-mode).

### Come uso il Flipper come telecomando nuovo (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors…)?

[Programmare un telecomando nuovo](/it/subghz/remote-prog).

### Come si usa l'app Sub-GHz Remote?

1. Apri l'app, premi <kbd>BACK</kbd> e seleziona **New map file**.
2. Scegli un file di segnale e un'etichetta per ogni pulsante. Puoi lasciare dei pulsanti vuoti.
3. Salva la mappatura.
4. Apri il file di mappatura che hai creato.
5. Premi i pulsanti per inviare i segnali assegnati.

Dettagli: [Sub-GHz Remote](/it/subghz/remote).

### Il mio telecomando non è supportato (non è una chiave auto). Come lo registro per gli sviluppatori?

1. **Trova la frequenza.** **Sub-GHz → Frequency Analyzer**: tieni premuto il pulsante del telecomando vicino al
   Flipper (l'antenna è vicina alla finestra IR, sul lato sinistro). Rilascialo e la frequenza finisce nella
   cronologia. Tieni premuto <kbd>OK</kbd> per passare a **Read** e premi il telecomando alcune volte, tenendo premuto
   ogni volta per almeno 2 s. Prova `AM650`, `FM238`, `FM476`, `FM12K`.
2. **Non decodifica nulla? Registra in RAW.** Apri **Read RAW**, imposta la frequenza nella configurazione e la
   **RSSI Threshold** su `----`. Fai una registrazione per **ogni** modulazione
   (`AM650`/`FM238`/`FM476`/`FM12K`). Premi **REC**, poi premi un pulsante 5 volte tenendolo premuto 1–2 s, poi 5
   volte tenendolo premuto ~5 s. Registra ogni pulsante allo stesso modo e dai a ciascun file il nome del pulsante.
3. **Segnalalo.** Comprimi i file RAW in uno zip e apri una issue nel repository del firmware. Allega buone foto del
   telecomando (anche aperto, se possibile), modello e produttore, e una foto della scheda del ricevitore se ci riesci.

Se il telecomando non è cifrato ed è abbastanza particolare, il supporto potrebbe essere aggiunto. Per analizzare i
segnali da solo, prova [lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter).

### Come collego un modulo CC1101 esterno?

[CC1101 esterno](/it/subghz/external-cc1101).

## NFC e RFID

### MIFARE Ultralight

Leggi la card, avvicina il Flipper al lettore per catturare la password che sblocca le pagine rimanenti, poi leggi di
nuovo la card: [Sblocco con password](/it/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

Al momento non esistono attacchi per queste card sul Flipper.

### Carte bancarie

Le carte bancarie non si possono clonare, il Flipper non può emularle e non può fare da terminale di pagamento. Può
solo leggerne i dati pubblici: [Carte bancarie (EMV)](/it/nfc/emv).

### Amiibo

Gli Amiibo sono `NTAG215`. Non possono essere messi su una MIFARE Classic e attualmente non è possibile scrivere
Amiibo su nuovi tag fisici.

### HID / iClass (Picopass)

- Leggi le iClass con l'app **Picopass**. L'emulazione è supportata nelle build attuali di Unleashed con le app.
- Le Picopass a 26 bit possono essere convertite in credenziali LF RFID H10301. Funziona solo se il lettore è
  configurato per l'LF. Alcuni lettori iClass sono solo HF.
- Il supporto in scrittura per le card in modalità di personalizzazione è possibile con l'app.
- L'app **Seader** con una scheda di espansione SAM legge card HID più sicure.

### Clonazione RFID a 125 kHz

Per copiare un tag LF, scrivilo su un **T5577**. I chip che il Flipper legge sono a sola lettura, e non esistono
"blank" corrispondenti. Il T5577 è un chip multi-emulatore programmabile per comportarsi come altri tag:
[Scrivere RFID](/it/rfid/write), [App T5577](/it/rfid/t5577-app).

### Card o portachiavi non identificato

Se NFC, RFID e Picopass non danno risultati, fotografa il fronte e il retro della credenziale e il lettore. Se è una
card, tienila davanti a una luce intensa e fotografa l'antenna. Pubblica le foto nelle chat della community per
identificarla.

## Infrarossi

### Esiste un modo corretto di acquisire i segnali IR (soprattutto dei condizionatori)?

Sì: [Acquisizioni IR](/it/infrared/captures).

## File e computer

### Dove trovo file (Sub-GHz, IR, NFC…) per il mio Flipper?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) e
  [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) coprono la maggior parte delle necessità.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero): praticamente ogni link che ti possa servire.

### Come copio i file da GitHub al Flipper?

Scarica i file su un PC e copiali sulla scheda SD (con un lettore di schede o con il file manager di qFlipper). Esiste
anche una [guida della community](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf)
molto dettagliata.

### Come ripulisco i file `.DS_Store` e i dot file lasciati da macOS, o come ordino i file?

Vedi [Scheda microSD → macOS](/it/start/sd-card#macos-hidden-files-and-sorting).

### Come apro la CLI o leggo i log?

Chiudi prima qFlipper. Solo un programma alla volta può occupare la porta seriale.

- **Browser (Chromium):** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → scegli il dispositivo
  seriale USB → **CLI** nella barra laterale.
- **Windows:** trova la porta COM in qFlipper, chiudi qFlipper, poi in PuTTY scegli **Serial**, inserisci la porta COM
  e la velocità `115200` e clicca **Open**. "Access Denied" significa che qFlipper è ancora in esecuzione.
- **macOS/Linux:** trova il percorso del dispositivo in qFlipper (inizia con `/dev/tty`) oppure con `ls /dev/tty.*`,
  chiudi qFlipper, poi esegui (sostituisci `PATH`):
  ```bash
  screen PATH 115200
  ```
- **Android:** l'app *Serial USB Terminal*, collegata via USB OTG.
- **iPhone:** non c'è seriale USB. Usa un altro metodo.

Per vedere i log imposta **Settings → System → Log Level** su `Debug` e digita `log` nella CLI.
<kbd>Ctrl</kbd>+<kbd>C</kbd> esce. Altro: [CLI](/it/dev/cli).

### Come compilo il firmware da solo?

[Compilare il firmware](/it/dev/build).

## Community

- Release: Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Build dev: Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Altri link: [Link](/it/community/links)
