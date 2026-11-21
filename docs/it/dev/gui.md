---
title: GUI nelle app
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI nelle app

Questa pagina illustra i concetti di base della GUI nel firmware del Flipper e confronta i tre modi di costruire
l'interfaccia di un'app, dal più semplice al più potente:

1. [Dialogs](#using-dialogs) — qualche finestra di messaggio, senza disegno personalizzato.
2. [ViewPort](#using-a-viewport) — un'unica area a schermo intero che disegni tu; ideale per i giochi.
3. [Views e Scenes](#using-views-and-scenes) — app multi-schermata con menu e navigazione (la maggior parte delle app
   integrate).

## Concetti di base

### Event loop

Un meccanismo asincrono di gestione degli eventi. Invece di interrogare ciclicamente o bloccarti in attesa di eventi
(pressioni di pulsanti, pacchetti ricevuti, timer), registri funzioni gestore che vengono chiamate quando l'evento
accade, così il ciclo principale resta libero per altro lavoro.

### Canvas

Il **canvas** è un'area di disegno grezza senza alcuna astrazione. Disegnarvi direttamente è utile per elementi
visivi personalizzati (per esempio nei giochi), ma la maggior parte delle app non ne ha bisogno.

### ViewPort

Un **ViewPort** definisce come viene disegnata un'area dello schermo di posizione e dimensione date e come reagisce
all'input. Più ViewPort formano una *pila di disegno* resa dal basso verso l'alto, quindi possono sovrapporsi. Un
ViewPort può essere abilitato o disabilitato dopo la creazione.

### Model, View e View Dispatcher

Questi elementi separano la GUI dai dati, il che rende le app più facili da sviluppare, mantenere e testare.

- **Model** — i dati; tecnicamente una struttura in memoria.
- **View** — rendering e gestione dell'input. Legge il Model per disegnare e lo modifica gestendo gli eventi.
- **View Dispatcher** — contiene i riferimenti a tutte le View che l'app necessita e passa dall'una all'altra su
  richiesta.

### Moduli di view

Template a schermo intero già pronti (View + Model) per le interfacce tipiche del Flipper, inclusi nel firmware
(`applications/services/gui/modules/`):

| Modulo | Uso tipico |
|---|---|
| `button_menu` | Menu di pulsanti grandi |
| `button_panel` | Griglia di pulsanti selezionabili |
| `byte_input` | Inserimento di byte esadecimali |
| `date_time_input` | Inserimento di data e ora |
| `dialog_ex` | Finestra di dialogo con intestazione, testo, icona e fino a tre pulsanti |
| `empty_screen` | Schermata vuota |
| `file_browser` | Scelta di un file sulla scheda SD |
| `loading` | Animazione "Loading…" |
| `menu` | Elenco in stile menu principale con icone |
| `number_input` | Inserimento di un numero |
| `popup` | Messaggio temporaneo con timeout |
| `submenu` | Semplice elenco verticale di voci |
| `text_box` | Testo scorrevole |
| `text_input` | Tastiera a schermo |
| `variable_item_list` | Elenco di impostazioni con valori ◀ ▶ |
| `widget` | Composizione libera di testo, icone e pulsanti |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Codice sorgente: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene e Scene Manager

Una **Scene** governa il comportamento dell'app su una singola schermata. Per esempio, l'app GPIO dichiara queste
scene in `applications/main/gpio/scenes/gpio_scene_config.h`:

| Scena | Schermata |
|---|---|
| `gpio_scene_start` | Menu iniziale |
| `gpio_scene_usb_uart` | Interfaccia del ponte USB-UART |
| `gpio_scene_usb_uart_cfg` | Impostazioni del ponte USB-UART (file `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | "Connection Is Active! Disconnect from PC or phone to use this function." — mostrata quando apri il ponte USB-UART mentre qFlipper o l'app mobile è collegata |
| `gpio_scene_test` | Controllo manuale dei GPIO |

Dal menu iniziale si passa al controllo manuale o alla modalità ponte USB-UART, e dal ponte alle sue impostazioni.

Ogni scena implementa tre funzioni:

- `on_enter` — inizializza le view della scena;
- `on_exit` — deinizializza e libera le risorse;
- `on_event` — gestisce gli eventi in arrivo.

Un gestore di eventi può passare a un'altra scena — per esempio, selezionare una voce di menu porta alla scena
corrispondente. Lo **Scene Manager** esegue queste transizioni e conserva la cronologia della navigazione, cosa che
rende gestibili i flussi di navigazione complessi.

## Approcci allo sviluppo della GUI

Più complessa è l'interfaccia, più astrazioni grafiche ti servono.

### Con Dialogs {#using-dialogs}

L'approccio più semplice — adatto quando l'intera interfaccia consiste in finestre di dialogo. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Approccio con Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Pro:** semplice e immediato.
**Contro:** solo finestre di dialogo, nessuna GUI complessa; le finestre di dialogo sono **sincrone** — nessun altro
codice dell'app viene eseguito finché l'utente non preme un pulsante.

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app(void* p) {
    UNUSED(p);

    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

### Con un ViewPort {#using-a-viewport}

Crei un unico ViewPort a schermo intero che disegna il display e gestisce tutto l'input.

![Approccio con ViewPort](/img/dev/app_dev_gui_viewport.png)

**Pro:** facile — un solo ViewPort, nessun'altra astrazione; rapido e adatto ai giochi; controllo totale dello
schermo.
**Contro:** nessun supporto alla navigazione; nessuna View riutilizzabile.

Esempi:

- molti degli [strumenti di debug](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- la [finestra di associazione BLE](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- la maggior parte dei giochi, per esempio [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game),
  distribuito con Unleashed

### Con Views e Scenes {#using-views-and-scenes}

L'approccio principale per app con interfacce complesse e gerarchiche — usato dalla maggior parte delle app del
Flipper.

![Approccio con Views e Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Pro:** supporta navigazioni complesse; le view vengono riutilizzate; molti moduli di view già pronti.
**Contro:** richiede tempo per essere assimilato; implementazione più complessa.

Esempi (sorgenti di Unleashed):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
Nelle app basate sulle scene l'elenco delle scene si trova in `scenes/<app>_scene_config.h`, e ogni file `scenes/*.c`
implementa una schermata. Leggerli è il modo più rapido per capire come sono costruiti i menu di un'app.
:::

## Scegliere un approccio

| Se vuoi… | Usa |
|---|---|
| Mostrare un messaggio o porre una domanda sì/no | Dialogs |
| Un gioco, un visualizzatore o un'unica schermata personalizzata | ViewPort |
| Menu, impostazioni, selezione di file, più schermate | Views e Scenes |

## Approfondimenti (esterni)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) di Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) di Derek Jamison
- Tutorial su YouTube di Derek Jamison:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Pagine correlate

- [La tua prima app in C](/it/dev/first-app-c)
- [API Furi](/it/dev/furi-api)
- [JavaScript sul Flipper](/it/dev/js-about) — gli script JS possono usare molti degli stessi moduli di view
