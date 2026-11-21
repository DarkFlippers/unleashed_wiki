---
title: GUI en las apps
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_gui.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules]
sources: [unleashed-docs, unleashed-src]
---
# GUI en las apps

Esta página explica los conceptos básicos de la GUI del firmware del Flipper y compara las tres formas de construir la
interfaz de una app, de la más sencilla a la más potente:

1. [Dialogs](#using-dialogs) — unos pocos cuadros de mensaje, sin dibujo propio.
2. [ViewPort](#using-a-viewport) — una única zona a pantalla completa que dibujas tú; ideal para juegos.
3. [Views y Scenes](#using-views-and-scenes) — apps con varias pantallas, menús y navegación (la mayoría de las apps
   integradas).

## Conceptos básicos

### Bucle de eventos

Un mecanismo asíncrono de gestión de eventos. En lugar de sondear o bloquearte esperando eventos (pulsaciones de
botón, paquetes recibidos, temporizadores), registras funciones manejadoras que se llaman cuando el evento ocurre, de
modo que el bucle principal queda libre para otras tareas.

### Canvas

El **canvas** es una zona de dibujo en bruto, sin abstracciones. Dibujar directamente sobre él resulta útil para
elementos visuales propios (por ejemplo en juegos), pero la mayoría de las apps no lo necesitan.

### ViewPort

Un **ViewPort** define cómo se dibuja una zona de la pantalla de una posición y un tamaño dados y cómo reacciona a la
entrada. Varios ViewPorts forman una *pila de dibujo* que se renderiza de abajo arriba, así que pueden solaparse. Un
ViewPort se puede activar o desactivar después de crearlo.

### Model, View y View Dispatcher

Estos elementos separan la GUI de los datos, lo que facilita desarrollar, mantener y probar las apps.

- **Model** — los datos; técnicamente, una estructura en memoria.
- **View** — el renderizado y la gestión de la entrada. Lee el Model para dibujar y lo modifica al gestionar eventos.
- **View Dispatcher** — mantiene referencias a todas las Views que necesita la app y alterna entre ellas cuando se le
  pide.

### Módulos de vista

Plantillas a pantalla completa listas para usar (View + Model) para las interfaces típicas del Flipper, incluidas en el
firmware (`applications/services/gui/modules/`):

| Módulo | Uso típico |
|---|---|
| `button_menu` | Menú de botones grandes |
| `button_panel` | Cuadrícula de botones seleccionables |
| `byte_input` | Introducir bytes en hexadecimal |
| `date_time_input` | Introducir fecha y hora |
| `dialog_ex` | Diálogo con encabezado, texto, icono y hasta tres botones |
| `empty_screen` | Pantalla en blanco |
| `file_browser` | Elegir un archivo de la tarjeta SD |
| `loading` | Animación de «Loading…» |
| `menu` | Lista con iconos al estilo del menú principal |
| `number_input` | Introducir un número |
| `popup` | Mensaje temporal con tiempo de espera |
| `submenu` | Lista vertical sencilla de elementos |
| `text_box` | Texto con desplazamiento |
| `text_input` | Teclado en pantalla |
| `variable_item_list` | Lista de ajustes con valores ◀ ▶ |
| `widget` | Composición libre de texto, iconos y botones |

| | | |
|---|---|---|
| ![submenu](/img/dev/submenu.png) `submenu` | ![dialog](/img/dev/dialog.png) `dialog_ex` | ![text_input](/img/dev/text_input.png) `text_input` |
| ![byte_input](/img/dev/byte_input.png) `byte_input` | ![text_box](/img/dev/text_box.png) `text_box` | ![widget](/img/dev/widget.png) `widget` |
| ![loading](/img/dev/loading.png) `loading` | ![empty](/img/dev/empty.png) `empty_screen` | |

Código fuente: [applications/services/gui/modules](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gui/modules).

### Scene y Scene Manager

Una **Scene** controla el comportamiento de la app en una pantalla. Por ejemplo, la app GPIO declara estas escenas en
`applications/main/gpio/scenes/gpio_scene_config.h`:

| Escena | Pantalla |
|---|---|
| `gpio_scene_start` | Menú inicial |
| `gpio_scene_usb_uart` | Interfaz del puente USB-UART |
| `gpio_scene_usb_uart_cfg` | Ajustes del puente USB-UART (archivo `gpio_scene_usb_uart_config.c`) |
| `gpio_scene_usb_uart_close_rpc` | «Connection Is Active! Disconnect from PC or phone to use this function.» — aparece si abres el puente USB-UART mientras qFlipper o la app móvil están conectados |
| `gpio_scene_test` | Control manual del GPIO |

Desde el menú inicial se va al control manual o al modo de puente USB-UART, y desde el puente a sus ajustes.

Cada escena implementa tres funciones:

- `on_enter` — inicializar las vistas de la escena;
- `on_exit` — desinicializar y liberar recursos;
- `on_event` — gestionar los eventos entrantes.

Un manejador de eventos puede cambiar a otra escena — por ejemplo, seleccionar un elemento del menú lleva a la escena
correspondiente. El **Scene Manager** realiza estas transiciones y mantiene el historial de navegación, lo que hace
manejables los flujos de navegación complejos.

## Enfoques para desarrollar la GUI

Cuanto más compleja sea tu interfaz, más abstracciones de GUI necesitarás.

### Usar Dialogs {#using-dialogs}

El enfoque más sencillo — adecuado cuando toda la interfaz son cuadros de diálogo. API:
[`dialogs.h`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/dialogs/dialogs.h).

![Enfoque con Dialogs](/img/dev/app_dev_gui_dialogs.jpg)

**Ventajas:** simple y fácil.
**Inconvenientes:** solo diálogos, sin GUI complejas; los diálogos son **sincrónicos** — no se ejecuta ningún otro
código de la app hasta que el usuario pulsa un botón.

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

### Usar un ViewPort {#using-a-viewport}

Creas un único ViewPort a pantalla completa que dibuja el display y gestiona toda la entrada.

![Enfoque con ViewPort](/img/dev/app_dev_gui_viewport.png)

**Ventajas:** fácil — un solo ViewPort, sin otras abstracciones; rápido y adecuado para juegos; control total de la
pantalla.
**Inconvenientes:** sin utilidades de navegación; sin Views reutilizables.

Ejemplos:

- muchas de las [herramientas de depuración](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug)
- el [diálogo de emparejamiento BLE](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/services/bt/bt_service/bt.c)
- [Dolphin Passport](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/settings/dolphin_passport/passport.c)
- la mayoría de los juegos, por ejemplo [Snake](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/snake_game),
  incluido en Unleashed

### Usar Views y Scenes {#using-views-and-scenes}

El enfoque principal para apps con interfaces complejas y jerárquicas — es el que usan la mayoría de las apps del
Flipper.

![Enfoque con Views y Scenes](/img/dev/app_dev_gui_views_and_scenes.jpg)

**Ventajas:** admite navegación compleja; las vistas se reutilizan; hay muchos módulos de vista listos para usar.
**Inconvenientes:** cuesta asimilarlo; la implementación es más compleja.

Ejemplos (código de Unleashed):

- [Desktop](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop)
- [iButton](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton)
- [Infrared](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared)
- [GPIO](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/gpio)
- [NFC](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc)
- [RFID](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid)
- [Sub-GHz](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz)

::: tip
En las apps basadas en escenas, la lista de escenas está en `scenes/<app>_scene_config.h`, y cada archivo
`scenes/*.c` implementa una pantalla. Leerlos es la forma más rápida de entender cómo se construyen los menús de una
app.
:::

## Elegir un enfoque

| Si quieres… | Usa |
|---|---|
| Mostrar un mensaje o preguntar sí/no | Dialogs |
| Un juego, un visualizador o una sola pantalla propia | ViewPort |
| Menús, ajustes, selección de archivos, varias pantallas | Views y Scenes |

## Más información (externa)

- [A Visual Guide to Flipper Zero GUI Modules](https://brodan.biz/blog/a-visual-guide-to-flipper-zero-gui-components/), de Christopher Hranj
- [Scenes Demo Application Tutorial](https://github.com/jamisonderek/flipper-zero-tutorials/tree/main/ui/basic_scenes#scenes-demo-application-tutorial), de Derek Jamison
- Tutoriales en YouTube de Derek Jamison:
  [Using ViewPort](https://www.youtube.com/watch?v=5QwwihbxkC8) ·
  [Creating UI using Scenes](https://www.youtube.com/watch?v=YbskaB6caqk&list=PLM1cyTMe-PYJaMQ6TWeK1mAWxORdjYJZ5&index=8) ·
  [SceneManager Best Practice](https://www.youtube.com/watch?v=vQAk7fC_no4)

## Páginas relacionadas

- [Tu primera app en C](/es/dev/first-app-c)
- [API Furi](/es/dev/furi-api)
- [JavaScript en el Flipper](/es/dev/js-about) — los scripts de JS pueden usar muchos de los mismos módulos de vista
