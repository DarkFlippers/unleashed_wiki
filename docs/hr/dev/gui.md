---
title: GUI u aplikacijama
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI u aplikacijama

Ova stranica objašnjava osnovne koncepte grafičkog sučelja (GUI) u firmveru Flippera i uspoređuje tri načina izrade sučelja
aplikacije, od najjednostavnijeg do najnaprednijeg:

1. [Dijalozi](#using-dialogs) — nekoliko okvira s porukama, bez prilagođenog iscrtavanja.
2. [ViewPort](#using-a-viewport) — jedno područje preko cijelog zaslona koje sami iscrtavate; idealno za igre.
3. [Views i Scenes](#using-views-and-scenes) — aplikacije s više zaslona, izbornicima i navigacijom (većina ugrađenih aplikacija).

## Osnovni koncepti

### Petlja događaja (Event loop)

Asinkroni mehanizam za obradu događaja. Umjesto neprekidnog provjeravanja (polling) ili blokiranja dok čekate događaje (pritiske tipki,
primljene pakete, timere), registrirate funkcije rukovatelje (handler) koje se pozivaju kad se događaj dogodi, čime glavna petlja
ostaje slobodna za drugi posao.

### Canvas

**Canvas** je sirovo područje za crtanje bez apstrakcija. Izravno crtanje po njemu korisno je za prilagođene vizualne
elemente (npr. u igrama), no većini aplikacija nije potrebno.

### ViewPort

**ViewPort** definira kako se područje zaslona zadanog položaja i veličine iscrtava te kako reagira na unos.
Više ViewPortova čini *stog iscrtavanja* koji se renderira odozdo prema gore, pa se mogu preklapati. ViewPort se može uključiti ili
isključiti nakon stvaranja.

### Model, View i View Dispatcher

Ovi elementi razdvajaju GUI od podataka, što aplikacije čini lakšima za razvoj, održavanje i testiranje.

- **Model** — podaci; tehnički gledano, struktura u memoriji.
- **View** — renderiranje i obrada unosa. Čita Model za iscrtavanje i mijenja ga pri obradi događaja.
- **View Dispatcher** — čuva reference na sve Viewove koji su aplikaciji potrebni i prebacuje se između njih na zahtjev.

### Moduli prikaza (View modules)

Gotovi predlošci preko cijelog zaslona (View + Model) za tipična sučelja Flippera, uključeni u firmver
(`applications/services/gui/modules/`):

| Modul | Tipična upotreba |
|---|---|
| `button_menu` | Izbornik velikih gumba |
| `button_panel` | Mreža gumba koji se mogu odabrati |
| `byte_input` | Unos heksadecimalnih bajtova |
| `date_time_input` | Unos datuma i vremena |
| `dialog_ex` | Dijalog sa zaglavljem, tekstom, ikonom i do tri gumba |
| `empty_screen` | Prazan zaslon |
| `file_browser` | Odabir datoteke na SD kartici |
| `loading` | Animacija „Loading…” |
| `menu` | Popis u stilu glavnog izbornika s ikonama |
| `number_input` | Unos broja |
| `popup` | Privremena poruka s vremenskim ograničenjem |
| `submenu` | Jednostavan okomiti popis stavki |
| `text_box` | Tekst s pomicanjem (scroll) |
| `text_input` | Tipkovnica na zaslonu |
| `variable_item_list` | Popis postavki s vrijednostima ◀ ▶ |
| `widget` | Slobodna kompozicija teksta, ikona i gumba |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Izvorni kôd: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scena (Scene) i Scene Manager

**Scene** upravlja ponašanjem aplikacije na jednom zaslonu. Primjerice, aplikacija GPIO deklarira ove scene u datoteci
`applications/main/gpio/scenes/gpio_scene_config.h`:

| Scena | Zaslon |
|---|---|
| `gpio_scene_start` | Početni izbornik |
| `gpio_scene_usb_uart` | Sučelje USB-UART mosta |
| `gpio_scene_usb_uart_cfg` | Postavke USB-UART mosta (datoteka `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | „Connection Is Active! Disconnect from PC or phone to use this function.” — prikazuje se kad otvorite USB-UART most dok je spojen qFlipper ili mobilna aplikacija |
| `gpio_scene_test` | Ručno upravljanje GPIO-om |

Iz početnog izbornika idete na ručno upravljanje ili u način rada USB-UART mosta, a iz mosta u njegove postavke.

Svaka scena implementira tri funkcije:

- `on_enter` — inicijalizacija prikaza (viewova) scene;
- `on_exit` — deinicijalizacija i oslobađanje resursa;
- `on_event` — obrada pristiglih događaja.

Rukovatelj događajima može prebaciti na drugu scenu — npr. odabir stavke izbornika prelazi na odgovarajuću scenu.
**Scene Manager** obavlja te prijelaze i čuva povijest navigacije, što složene tokove navigacije čini
lakima za upravljanje.

## Pristupi razvoju GUI-ja

Što je vaše sučelje složenije, to vam je više GUI apstrakcija potrebno.

### Korištenje dijaloga (Dialogs) {#using-dialogs}

Najjednostavniji pristup — prikladan kad se cijelo sučelje sastoji samo od dijaloških okvira. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Pristup s dijalozima](/img/dev/app_dev_gui_dialogs.jpg)

**Prednosti:** jednostavno i lako.
**Nedostaci:** samo dijalozi, bez složenih GUI-ja; dijalozi su **sinkroni** — nikakav drugi kôd aplikacije ne izvodi se dok korisnik ne pritisne
gumb.

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

### Korištenje ViewPorta {#using-a-viewport}

Stvarate jedan ViewPort preko cijelog zaslona koji iscrtava zaslon i obrađuje sav unos.

![Pristup s ViewPortom](/img/dev/app_dev_gui_viewport.png)

**Prednosti:** jednostavno — jedan ViewPort, bez drugih apstrakcija; brzo i pogodno za igre; potpuna kontrola nad zaslonom.
**Nedostaci:** nema pomoćnika za navigaciju; nema višekratno iskoristivih Viewova.

Primjeri:

- mnogi [alati za otklanjanje pogrešaka](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- [dijalog za BLE uparivanje](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- većina igara, npr. [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game)
  koja dolazi uz Unleashed

### Korištenje Viewova i Scena {#using-views-and-scenes}

Glavni pristup za aplikacije sa složenim, hijerarhijskim sučeljima — koristi ga većina Flipperovih aplikacija.

![Pristup s Viewovima i Scenama](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Prednosti:** podržava složenu navigaciju; prikazi se ponovno koriste; mnogo gotovih modula prikaza.
**Nedostaci:** zahtijeva vrijeme za razumijevanje; složenija implementacija.

Primjeri (izvorni kôd Unleasheda):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
U aplikacijama temeljenima na scenama popis scena nalazi se u `scenes/<app>_scene_config.h`, a svaka datoteka `scenes/*.c` implementira
jedan zaslon. Čitanje tih datoteka najbrži je način da shvatite kako su izgrađeni izbornici aplikacije.
:::

## Odabir pristupa

| Želite… | Koristite |
|---|---|
| Prikazati poruku ili postaviti pitanje da/ne | Dijalozi (Dialogs) |
| Igru, vizualizator ili jedan prilagođeni zaslon | ViewPort |
| Izbornike, postavke, odabir datoteka, više zaslona | Views i Scenes |

## Saznajte više (vanjske poveznice)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/) — Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial) — Derek Jamison
- YouTube vodiči Dereka Jamisona:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Povezane stranice

- [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c)
- [Furi API](/hr/dev/furi-api)
- [JavaScript na Flipperu](/hr/dev/js-about) — JS skripte mogu koristiti mnoge od istih modula prikaza
