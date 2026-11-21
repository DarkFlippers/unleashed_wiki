---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

Il **Video Game Module** (VGM) è un accessorio ufficiale costruito attorno al **Raspberry Pi RP2040**. Si innesta nel
connettore GPIO e aggiunge:

- **Video Out** — duplica lo schermo del Flipper su una TV o un monitor (segnale DVI-D, 640×480);
- un **sensore di movimento a 6 assi** (TDK ICM-42688-P: giroscopio a 3 assi + accelerometro) per i comandi
  giroscopici;
- una **porta USB-C** collegata all'RP2040 (per la programmazione, o usata da firmware personalizzati);
- un **breakout GPIO a 14 pin** dell'RP2040;
- i **pulsanti BOOT / RESET** (si premono con una graffetta) per la modalità di programmazione UF2 e per il reset;
- un LED RGB sul lato superiore.

Può funzionare anche come scheda RP2040 autonoma, compatibile con i progetti per Raspberry Pi Pico.

![Pulsanti e connettori del Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Installazione e collegamento a una TV

1. **Monta il modulo.** Arriva con un paracolpi in silicone pensato per un Flipper *senza* custodia. Se il tuo Flipper
   è in una custodia in silicone, togli il paracolpi dal modulo (o la custodia dal Flipper).
2. **Firmware.** Il modulo richiede firmware del Flipper 0.98.3 o successivo; le release attuali di Unleashed vanno
   bene.
3. **Verifica l'impostazione della UART:** `Main Menu → Settings → Expansion Modules → Listen UART` deve essere
   **`USART`**. Con qualsiasi altro valore il modulo non viene rilevato. (Vedi
   [Moduli di espansione](/it/gpio/expansion-modules).)
4. Collega il modulo (con il Flipper spento) e accendi. Il Flipper rileva il modulo e lo prepara automaticamente.
5. Collega il cavo della TV alla porta **Video Out** del modulo e seleziona quell'ingresso sulla TV.

### "Video Game Module not initialized"

Questo testo sulla TV significa che il modulo non sta comunicando con un Flipper: il firmware è troppo vecchio,
`Listen UART` non è su `USART`, oppure il modulo è alimentato (per esempio via USB) senza un Flipper collegato.

## Giochi e app

Il sensore di movimento è usato da app del Flipper Apps Catalog, per esempio
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) e
[Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse) (mouse giroscopico per computer).

::: tip Unleashed
Il motore JavaScript di Unleashed include un modulo `vgm` (feature JS `vgm`): `getPitch()`, `getRoll()`, `getYaw()` e
`deltaYaw(angle, timeout)` leggono l'orientamento del modulo da uno script, restituendo `undefined` se nessun VGM è
presente. Vedi la sezione [Sviluppo](/it/dev/) per le app in JavaScript.
:::

## Aggiornare il firmware del modulo

Gli aggiornamenti si installano con l'app **Video Game Module Tool** (dal Flipper Apps Catalog). Il suo menu:

- `Install Official Firmware` — l'ultimo firmware ufficiale del modulo, incluso nell'app;
- `Install Firmware from File` — un `.uf2` personalizzato dalla scheda SD.

Per aggiornare:

1. Installa (o **aggiorna prima**) Video Game Module Tool: nell'app mobile del Flipper vai in **Apps**, cerca
   *Video Game Module Tool* e tocca **INSTALL** / **UPDATE**. Un nuovo firmware del modulo arriva con una nuova
   versione dell'app, quindi aggiorna sempre l'app prima di aggiornare il modulo.
2. Collega il modulo al Flipper.
3. Apri `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Seleziona `Install Official Firmware` e confermi con `Install` (<kbd>→</kbd>).
5. Attendi il messaggio **Video Game Module Updated**.

## Firmware personalizzato

Il modulo può eseguire un firmware RP2040 tuo.

### Dal Flipper Zero

Permette di tenere più firmware del modulo sulla scheda SD e passare dall'uno all'altro senza computer.

1. Copia il file `.uf2` sulla scheda SD del Flipper (per esempio con [qFlipper](/it/mobile/qflipper):
   `File manager → SD Card`, crea una cartella, carica il file).
2. Collega il modulo e apri `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Seleziona il file e confermi con `Install` (<kbd>→</kbd>). Attendi **Video Game Module Updated**.

::: warning Limiti dei file UF2 installati dal Flipper
- I blocchi diversi da quelli di flash non sono supportati.
- Il payload dei blocchi deve essere esattamente di 256 byte.
- Gli indirizzi di destinazione del payload devono essere allineati a 256 byte, senza interruzioni.
- I container di file e i tag di estensione non sono supportati.
:::

### Da un computer

1. Scollega il modulo dal Flipper e dall'USB.
2. Tieni premuto il pulsante **BOOT** del modulo con una graffetta.
3. Collega il modulo al computer con un cavo USB-C. Viene montato come un'unità USB chiamata **RPI-RP2**. Rilascia
   **BOOT**.
4. Trascina il file `.uf2` su **RPI-RP2**. Il modulo si riavvia e si smonta da sé.

## Dettagli hardware (per l'uso autonomo)

### GPIO dell'RP2040

- I GPIO **8–15** e **18–20** sono usati per l'uscita video e non sono disponibili sui connettori.
- I GPIO **0–7, 16, 17, 21, 22, 26–28** sono sui connettori (come su un Raspberry Pi Pico). I GPIO **2–7** sono
  collegati anche al sensore di movimento.
- I GPIO **23–25 e 29** (usati internamente su un Pico) sono liberi sul VGM e portati sul breakout a 14 pin.

![Pinout del breakout a 14 pin del Video Game Module](/img/remote/b030c6a0375c6254.png)

![Pinout del Video Game Module e del Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Periferiche disponibili per l'RP2040

- **Video Out:** video e audio verso una TV o un monitor, più lo scambio di dati sul
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** dispositivo o host USB (nessun USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **Breakout GPIO:** 11 pin GPIO con protezione dalle scariche elettrostatiche.
- **Connettore verso il Flipper Zero:** i pin 13 e 14 del Flipper sono pienamente funzionanti; i pin 2–7 hanno
  funzionalità limitate (condivisi con l'IMU). Protetti dalle scariche elettrostatiche.
- **LED RGB**, controllato da un GPIO dell'RP2040.

### Alimentazione

- 5 V via USB-C nell'uso autonomo;
- 3,3 V (pin 9) o 5 V (pin 1) dal Flipper.

Alimentare contemporaneamente da USB-C e dal Flipper è sicuro per il modulo e per entrambe le sorgenti.

Schemi, disegni di assemblaggio del PCB e pinout in PDF si trovano nella pagina ufficiale
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Argomenti correlati

- [Moduli di espansione](/it/gpio/expansion-modules)
- [Pinout GPIO](/it/gpio/pinout)
- [Moduli esterni](/it/gpio/external-modules)
