---
title: Formato degli script
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Formato degli script Bad USB (DuckyScript)

Bad USB esegue script in testo semplice scritti in una sintassi **DuckyScript estesa**. Gli script classici per USB
Rubber Ducky 1.0 funzionano così come sono; oltre a quelli, il Flipper aggiunge identità USB/BLE personalizzate,
l'inserimento con `ALT`+tastierino numerico, `SYSRQ`, i tasti multimediali, il controllo del mouse, l'attesa della
pressione di un pulsante e altro. Questo riferimento è verificato sulla tabella dei comandi presente nel firmware
(`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## Regole dei file

- Testo semplice, estensione **`.txt`**, nessuna compilazione. Fine riga `\n` oppure `\r\n`.
- Un comando per riga. Le righe vuote vengono saltate; le righe possono essere indentate con spazi o tabulazioni.
- I comandi sono **IN MAIUSCOLO e sensibili alle maiuscole**: `STRING`, non `string`.
- Comando e argomento sono separati da un solo spazio.
- I commenti sono righe intere che iniziano con `REM`. Non esistono commenti a fine riga.
- Il testo digitato (`STRING`, `STRINGLN`) deve essere **ASCII**. I caratteri non ASCII interrompono lo script con
  *"Native .kl supports ASCII, not UTF-8"*.
- In caso di errore lo script si ferma e lo schermo mostra *ERROR:*, il numero di riga e il motivo.

## Riferimento rapido

| Comando | Argomento | Effetto |
|---|---|---|
| `REM` | testo | Commento, ignorato. |
| `ID` | `VID:PID [Manufacturer:Product]` | Identità USB, **solo come prima riga**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Identità Bluetooth, **solo come prima riga**. |
| `DELAY` | ms | Attende una volta. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Attende prima di ogni comando successivo. |
| `STRING` | testo | Digita il testo. |
| `STRINGLN` | testo | Digita il testo e preme Invio. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Ritardo tra le battute solo per la `STRING` **successiva**. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Ritardo tra le battute per **ogni** `STRING`. |
| `REPEAT` | n | Ripete il comando precedente altre n volte. |
| `DUCKY_LANG` | nome del layout | Cambia il layout di tastiera per il resto dello script (Unleashed). |
| `HOLD` | tasto / pulsante del mouse | Premi e mantieni premuto. |
| `RELEASE` | tasto / pulsante del mouse | Rilascia un tasto tenuto premuto. |
| `ALTCHAR` | codice | Digita un carattere con `ALT`+tastierino numerico. |
| `ALTSTRING` / `ALTCODE` | testo | Digita il testo con `ALT`+tastierino numerico. |
| `SYSRQ` | carattere | Combinazione del tasto Magic SysRq. |
| `MEDIA` | tasto multimediale | Tasto di consumer control (volume, play…). |
| `GLOBE` | tasto | Fn/Globe + tasto (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | nessuno | Mette in pausa finché non si preme <kbd>OK</kbd> sul Flipper. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | nessuno | Clic del mouse. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Muove il mouse. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | delta | Fa scorrere la rotella. |
| combinazione di tasti | per esempio `CTRL-ALT DELETE` | Premi e rilascia i tasti insieme. |

## Commenti

```text
REM This line is ignored
```

## Ritardi

| Comando | Parametro | Note |
|---|---|---|
| `DELAY` | ms | Pausa singola. |
| `DEFAULT_DELAY` | ms | Aggiunta prima di ogni comando successivo. Equivale a `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

I ritardi sono il tuo strumento principale per l'affidabilità: l'host ha bisogno di tempo per aprire le finestre,
quindi aggiungi un `DELAY` dopo `GUI r`, dopo `ENTER` in un launcher e così via. I ritardi lunghi sono mostrati a
schermo come `Delay Ns`.

## Digitare testo

| Comando | Parametro | Note |
|---|---|---|
| `STRING` | testo | Digita il testo esattamente, usando il layout di tastiera attivo. |
| `STRINGLN` | testo | Idem, poi preme Invio. |
| `STRING_DELAY` | ms | Pausa tra le battute solo per la `STRING`/`STRINGLN` successiva. Equivale a `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pausa tra le battute per tutte le stringhe successive. Equivale a `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Senza un ritardo tra le battute il testo viene inviato il più rapidamente possibile; alcuni host o alcune app in quel
caso perdono caratteri. Gli script dimostrativi integrati usano `DEFAULT_STRING_DELAY 10`.

::: warning Il layout conta
`STRING` invia *posizioni di tasti*, tradotte attraverso il [layout di tastiera](/it/badusb/layouts) selezionato. Se
l'host usa un layout diverso da quello dell'app, ottieni caratteri sbagliati. Il testo deve essere ASCII.
:::

## Tasti e combinazioni

Una riga che non è un comando viene interpretata come pressione di tasti: zero o più **modificatori**, poi un
**tasto**. I modificatori si uniscono con spazi o trattini. Il tasto è il nome di un tasto speciale oppure un singolo
carattere.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modificatori

| Nome | Note |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Tasto Windows / Command / Super |

### Tasti speciali

| Nome | Note |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Frecce |
| `ENTER` | |
| `DELETE` | Cancellazione in avanti |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Break |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Tasto del menu contestuale |
| `F1` … `F24` | Tasti funzione (il firmware conosce anche F13-F24) |

## Ripetizione

```text
DOWN
REPEAT 9
```

`REPEAT n` esegue il **comando precedente** altre n volte (nell'esempio Giù viene premuto 10 volte). `n` deve essere ≥ 1.

## Hold e release

| Comando | Parametro | Note |
|---|---|---|
| `HOLD` | tasto speciale, modificatore, singolo carattere o pulsante del mouse | Premi e mantieni premuto fino a `RELEASE`. |
| `RELEASE` | lo stesso | Rilascia quel tasto. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Si possono tenere premuti al massimo **6** tasti/pulsanti contemporaneamente (la dimensione del report HID dei tasti);
di più dà *"Too many keys are held"*. Un `RELEASE` senza nulla premuto dà *"No keys are held"*. Il documento ufficiale
dice 5; il controllo nel firmware consente 6.

## Inserimento con ALT + tastierino numerico

Su Windows (e in alcune configurazioni Linux) qualsiasi carattere può essere digitato tenendo premuto `ALT` e
inserendo il suo codice sul tastierino numerico. Questo **non dipende dal layout di tastiera**, cosa che lo rende
comodo su macchine sconosciute.

| Comando | Parametro | Note |
|---|---|---|
| `ALTCHAR` | codice del carattere | Digita un carattere: tiene premuto ALT e digita le cifre sul tastierino numerico. |
| `ALTSTRING` | testo | Digita ogni carattere ASCII stampabile (32-126) del testo tramite il suo codice ALT. |
| `ALTCODE` | testo | Come `ALTSTRING` (nome usato da alcune implementazioni di DuckyScript). |

Il NumLock viene attivato automaticamente prima dell'inserimento con ALT.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Invia `ALT`+`PRINTSCREEN`+tasto, la combinazione Linux [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key).
Fai attenzione: alcuni tasti SysRq riavviano o arrestano immediatamente il sistema.

## Tasti multimediali

`MEDIA <key>` preme un tasto di consumer control:

| Tasto | Note |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | Sistema |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Navigazione nel browser / nell'app |
| `SNAPSHOT` | Scatta una foto in un'app fotocamera |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Riproduzione |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Volume |
| `FN` | Tasto Fn/Globe sulle tastiere Mac |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Luminosità dello schermo |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Tasto Fn / Globe (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` tiene premuto Fn/Globe, preme il tasto e rilascia entrambi (tasto speciale o singolo carattere).

## Attendere la pressione di un pulsante

```text
WAIT_FOR_BUTTON_PRESS
```

Lo script si mette in pausa a tempo indeterminato; il Flipper mostra **Press to continue**. Premi <kbd>OK</kbd> per
proseguire. Utile per sincronizzarsi con qualcosa che fai a mano (accedere, sbloccare lo schermo…).

## Mouse

| Comando | Parametro | Note |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | nessuno | Clic sinistro |
| `RIGHTCLICK` / `RIGHT_CLICK` | nessuno | Clic destro |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | nessuno | Clic centrale (rotella) |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (interi) | Movimento relativo; negativo = a sinistra / in alto |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (intero) | Rotella di scorrimento; il segno dà la direzione |

I pulsanti del mouse funzionano con `HOLD`/`RELEASE`, per esempio per il drag and drop:

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## ID del dispositivo {#device-id}

Puoi impostare l'identità che il Flipper presenta all'host. Il comando deve stare sulla **primissima riga**; viene
applicato all'apertura dello script, prima dell'esecuzione, e l'app **passa alla modalità di connessione
corrispondente** (puoi comunque tornare indietro manualmente). Su altre righe questi comandi vengono ignorati.

| Comando | Parametri | Esempio | Modalità |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | come `BLE_ID` |

- `ID`: VID e PID (in esadecimale) sono obbligatori; le stringhe di produttore e prodotto sono facoltative (max. 31
  caratteri ciascuna).
- `BLE_ID` / `BT_ID`: il MAC da 6 byte e il nome del dispositivo sono entrambi obbligatori.

## Layout di tastiera per singolo script: `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` è una novità di Unleashed (PR #1224 di @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Carica `/ext/badusb/assets/layouts/<name>.kl` e lo usa da quella riga in poi, al posto del layout globale impostato
  in Config. Alias brevi: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- Il nome può contenere lettere, cifre, `-` e `_`, e sulla riga non deve seguire nient'altro.
- Un file mancante o un nome non valido **non interrompono lo script**: si ripiega silenziosamente sul layout
  integrato `en-US`.
- Ogni nuova esecuzione riparte dal layout globale, quindi metti `DUCKY_LANG` vicino all'inizio.

L'elenco dei nomi dei layout è in [Layout di tastiera](/it/badusb/layouts).

## Pagine correlate

- [Esempi](/it/badusb/examples)
- [Layout di tastiera](/it/badusb/layouts)
- [Usare Bad USB](/it/badusb/usage)
