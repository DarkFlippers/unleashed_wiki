---
title: GUI in Apps
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI in Apps

Diese Seite erklärt die grundlegenden GUI-Konzepte der Flipper-Firmware und vergleicht die drei Wege, die
Oberfläche einer App zu bauen, vom einfachsten bis zum mächtigsten:

1. [Dialogs](#using-dialogs) — ein paar Meldungsfenster, kein eigenes Zeichnen.
2. [ViewPort](#using-a-viewport) — eine bildschirmfüllende Fläche, die du selbst zeichnest; ideal für Spiele.
3. [Views & Scenes](#using-views-and-scenes) — Apps mit mehreren Bildschirmen, Menüs und Navigation (die meisten
   eingebauten Apps).

## Grundbegriffe

### Event loop

Ein asynchroner Mechanismus zur Ereignisbehandlung. Statt beim Warten auf Ereignisse (Tastendrücke, empfangene
Pakete, Timer) zu pollen oder zu blockieren, registrierst du Handler-Funktionen, die beim Eintreten des Ereignisses
aufgerufen werden, sodass die Hauptschleife für andere Arbeit frei bleibt.

### Canvas

Der **Canvas** ist eine rohe Zeichenfläche ohne Abstraktionen. Direkt darauf zu zeichnen ist für eigene visuelle
Elemente nützlich (z. B. in Spielen), die meisten Apps brauchen es aber nicht.

### ViewPort

Ein **ViewPort** legt fest, wie ein Bildschirmbereich mit gegebener Position und Größe gezeichnet wird und wie er
auf Eingaben reagiert. Mehrere ViewPorts bilden einen *Zeichenstapel*, der von unten nach oben gerendert wird, sie
können sich also überlappen. Ein ViewPort kann nach dem Erzeugen aktiviert oder deaktiviert werden.

### Model, View und View Dispatcher

Diese trennen die GUI von den Daten, was Apps leichter entwickelbar, pflegbar und testbar macht.

- **Model** — die Daten; technisch eine Struktur im Speicher.
- **View** — Darstellung und Eingabebehandlung. Sie liest das Model zum Zeichnen und ändert es beim Behandeln von
  Ereignissen.
- **View Dispatcher** — hält Referenzen auf alle Views, die die App braucht, und schaltet auf Anforderung zwischen
  ihnen um.

### View-Module

Fertige bildschirmfüllende Vorlagen (View + Model) für typische Flipper-Oberflächen, in der Firmware enthalten
(`applications/services/gui/modules/`):

| Modul | Typische Verwendung |
|---|---|
| `button_menu` | Menü aus großen Schaltflächen |
| `button_panel` | Raster aus auswählbaren Schaltflächen |
| `byte_input` | Hex-Bytes eingeben |
| `date_time_input` | Datum und Uhrzeit eingeben |
| `dialog_ex` | Dialog mit Kopfzeile, Text, Icon und bis zu drei Schaltflächen |
| `empty_screen` | Leerer Bildschirm |
| `file_browser` | Eine Datei auf der SD-Karte auswählen |
| `loading` | "Loading…"-Animation |
| `menu` | Liste im Stil des Hauptmenüs mit Icons |
| `number_input` | Eine Zahl eingeben |
| `popup` | Zeitweilige Meldung mit Timeout |
| `submenu` | Einfache vertikale Liste von Einträgen |
| `text_box` | Scrollbarer Text |
| `text_input` | Tastatur auf dem Display |
| `variable_item_list` | Einstellungsliste mit ◀ ▶ Werten |
| `widget` | Freie Komposition aus Text, Icons und Schaltflächen |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Quellcode: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene und Scene Manager

Eine **Scene** steuert das Verhalten der App auf einem Bildschirm. Die GPIO-App deklariert zum Beispiel diese
Scenes in `applications/main/gpio/scenes/gpio_scene_config.h`:

| Scene | Bildschirm |
|---|---|
| `gpio_scene_start` | Startmenü |
| `gpio_scene_usb_uart` | Oberfläche der USB-UART-Bridge |
| `gpio_scene_usb_uart_cfg` | Einstellungen der USB-UART-Bridge (Datei `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | "Connection Is Active! Disconnect from PC or phone to use this function." — erscheint, wenn du die USB-UART-Bridge öffnest, während qFlipper oder die Mobil-App verbunden ist |
| `gpio_scene_test` | Manuelle GPIO-Steuerung |

Vom Startmenü gelangst du zur manuellen Steuerung oder in den USB-UART-Bridge-Modus und von der Bridge zu ihren
Einstellungen.

Jede Scene implementiert drei Funktionen:

- `on_enter` — die Views der Scene initialisieren;
- `on_exit` — deinitialisieren und Ressourcen freigeben;
- `on_event` — eingehende Ereignisse behandeln.

Ein Event-Handler kann auf eine andere Scene umschalten — die Auswahl eines Menüeintrags führt z. B. zur passenden
Scene. Der **Scene Manager** führt diese Übergänge aus und verwaltet die Navigationshistorie, was komplexe
Navigationsabläufe handhabbar macht.

## Ansätze zur GUI-Entwicklung

Je komplexer deine Oberfläche, desto mehr GUI-Abstraktionen brauchst du.

### Dialogs {#using-dialogs}

Der einfachste Ansatz — passend, wenn die gesamte Oberfläche nur aus Dialogfenstern besteht. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Ansatz Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Vorteile:** einfach und unkompliziert.
**Nachteile:** nur Dialoge, keine komplexen GUIs; Dialoge sind **synchron** — es läuft kein anderer App-Code, bis
der Benutzer eine Taste drückt.

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

### ViewPort {#using-a-viewport}

Du erzeugst einen einzigen bildschirmfüllenden ViewPort, der das Display zeichnet und alle Eingaben behandelt.

![Ansatz ViewPort](/img/dev/app_dev_gui_viewport.png)

**Vorteile:** einfach — ein ViewPort, keine weiteren Abstraktionen; schnell und gut für Spiele geeignet;
vollständige Kontrolle über den Bildschirm.
**Nachteile:** keine Navigationshilfen; keine wiederverwendbaren Views.

Beispiele:

- viele der [Debug-Werkzeuge](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- der [BLE-Kopplungsdialog](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- die meisten Spiele, z. B. das mit Unleashed ausgelieferte
  [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game)

### Views und Scenes {#using-views-and-scenes}

Der Hauptansatz für Apps mit komplexen, hierarchischen Oberflächen — von den meisten Flipper-Apps verwendet.

![Ansatz Views und Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Vorteile:** unterstützt komplexe Navigation; Views werden wiederverwendet; viele fertige View-Module.
**Nachteile:** braucht Zeit, bis man es verinnerlicht hat; aufwendigere Implementierung.

Beispiele (Unleashed-Quellcode):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
In scenebasierten Apps steht die Liste der Scenes in `scenes/<app>_scene_config.h`, und jede `scenes/*.c`-Datei
implementiert einen Bildschirm. Diese zu lesen ist der schnellste Weg, um zu verstehen, wie die Menüs einer App
aufgebaut sind.
:::

## Den richtigen Ansatz wählen

| Du willst … | Nimm |
|---|---|
| Eine Meldung zeigen oder Ja/Nein fragen | Dialogs |
| Ein Spiel, eine Visualisierung oder einen eigenen Bildschirm | ViewPort |
| Menüs, Einstellungen, Dateiauswahl, mehrere Bildschirme | Views & Scenes |

## Mehr erfahren (extern)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) von Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) von Derek Jamison
- YouTube-Tutorials von Derek Jamison:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Verwandte Seiten

- [Deine erste App in C](/de/dev/first-app-c)
- [Furi-API](/de/dev/furi-api)
- [JavaScript auf dem Flipper](/de/dev/js-about) — JS-Skripte können viele derselben View-Module nutzen
