---
title: Escritorio
order: 60
original: [https://docs.flipper.net/zero/basics/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/archive, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Escritorio

El escritorio es la pantalla de inicio. Aquí vive tu [delfín](/es/start/dolphin), y arriba hay una barra de estado.
Desde el escritorio, una sola pulsación abre el menú principal, el Archive, el Lock Menu y tus aplicaciones
favoritas.

## Barra de estado

La línea superior muestra iconos pequeños:

| Icono | Significado |
|---|---|
| Batería | Nivel de carga. Muestra un rayo mientras carga. El estilo lo fija `Battery View` |
| Tarjeta SD | microSD montada. Un icono tachado significa que la tarjeta no se ha podido montar: véase [Tarjeta microSD](/es/start/sd-card) |
| Bluetooth | BLE activado. Un icono distinto indica que hay un dispositivo conectado |
| Candado | El Flipper está bloqueado |
| Altavoz silenciado | Modo sigiloso: sonido y vibración desactivados (véase [Lock Menu](#lock-menu)) |
| PC | Conectado a qFlipper / Flipper Lab por USB |
| Mando | El Dummy Mode está activado |
| Módulo | Hay un módulo de expansión conectado |
| Baliza | Modo baliza BLE (por ejemplo, FindMy Flipper) |
| Aplicación en segundo plano | Hay una aplicación ejecutándose en segundo plano |

::: tip Unleashed
- **Settings → Desktop → Battery View** selecciona el estilo de la batería: `Bar`, `%`, `Inv. %`, `Retro 3`,
  `Retro 5`, `Bar %`.
- **Settings → Desktop → Show Clock** = `ON` muestra la hora en el escritorio. El formato (24 h / 12 h) viene de
  **Settings → System → Time Format**.
:::

## Botones del escritorio

| Botón | Pulsación corta | Pulsación larga |
|---|---|---|
| <kbd>OK</kbd> | **Main Menu** | Favorite App - Ok Long |
| <kbd>↑</kbd> | **Lock Menu** | **Bloquear** (con PIN si hay uno configurado) |
| <kbd>↓</kbd> | **Archive** | Pantalla de información y depuración del dispositivo |
| <kbd>←</kbd> | Favorite App - Left Short (por defecto, el menú **Apps**) | Favorite App - Left Long |
| <kbd>→</kbd> | Por defecto, **Passport** (Favorite App - Right Short) | Favorite App - Right Long |
| <kbd>BACK</kbd> | — | Pantalla de **apagado** |

### Pantalla de información del dispositivo {#info-screen}

Una pulsación larga de <kbd>↓</kbd> abre una pantalla informativa: versión del firmware y fecha de compilación,
versión del hardware, tiempo encendido, nombre del Flipper y si Debug está en `ON` u `OFF`.

![Pantalla de información del dispositivo: versión del firmware, versión del hardware, tiempo encendido y el estado de Debug](/screens/desktop/debug.png)

En esa pantalla, una **pulsación larga de <kbd>OK</kbd> activa y desactiva Debug**: el mismo interruptor que
`Settings → System → Debug` ([Ajustes](/es/start/settings)), sin recorrer los menús. Una pulsación corta de
<kbd>BACK</kbd> vuelve al escritorio.

Debug en `ON` añade elementos que de otro modo están ocultos: la pestaña **Internal** del [Archive](#archive) y
`Signal Settings` en el menú de la señal guardada de Sub-GHz ([Signal Settings](/es/subghz/signal-settings)). Vuelve
a desactivarlo cuando termines: los ajustes de depuración ralentizan el Flipper y le impiden dormir.

## Main Menu

Pulsa <kbd>OK</kbd>. El menú principal se abre en **Apps** (todas las aplicaciones `.fap` de la tarjeta SD,
agrupadas por categoría), seguido de **Sub-GHz**, **125 kHz RFID**, **NFC**, **Infrared**, **GPIO**, **iButton**,
**Bad USB**, **U2F**, **Clock** y, al final, **Settings**. La lista es circular, así que pulsar <kbd>↑</kbd> sobre
**Apps** salta directamente a **Settings**.

![Menú principal con Apps seleccionado, Settings encima y Sub-GHz debajo](/screens/mainmenu/main.png)

::: tip Estilos de menú
**Settings → Desktop → Menu Style** cambia el aspecto del menú principal. Los estilos son plugins que están en
`/ext/apps_data/loader/plugins/` (archivos que empiezan por `menu_style_`). `Default` es la lista integrada.
:::

## Lock Menu {#lock-menu}

Pulsa <kbd>↑</kbd> en el escritorio. Muévete con <kbd>↑</kbd>/<kbd>↓</kbd> y pulsa <kbd>OK</kbd>:

| Elemento | Qué hace |
|---|---|
| **Turn Bluetooth On / Off** | Conmuta el BLE sin entrar en los ajustes |
| **Mute / Unmute** | Modo sigiloso: sin sonido ni vibración. Los ajustes **Volume** y **Vibro** muestran `Stealth` mientras está activo |
| **Dummy Mode / Default Mode** | Entrar o salir del [Dummy Mode](#dummy-mode) |

Pulsa <kbd>←</kbd> o <kbd>→</kbd> en el Lock Menu para abrir la segunda página, **Quick Settings**:

| Elemento | Control |
|---|---|
| Brightness | <kbd>OK</kbd> para editar y luego <kbd>←</kbd>/<kbd>→</kbd> (o <kbd>↑</kbd>/<kbd>↓</kbd>), en pasos del 5 % |
| Volume | Igual. Suena un pitido corto para que oigas el nivel nuevo |
| Vibro | <kbd>OK</kbd> lo conmuta al instante |

<kbd>BACK</kbd> sale del elemento que estés editando, y un segundo <kbd>BACK</kbd> sale de la página. Los cambios van
a los mismos ajustes que **LCD and Notifications**.

::: tip Unleashed
En Unleashed, **el bloqueo en sí** es una pulsación larga de <kbd>↑</kbd> en el escritorio: con el PIN si hay uno
configurado, o un bloqueo normal si no.
:::

## Bloqueo y PIN

- **Bloquear:** mantén <kbd>↑</kbd> en el escritorio. Sin PIN, los botones quedan bloqueados. **Para desbloquear,
  pulsa <kbd>BACK</kbd> tres veces** rápido.
- **Con PIN:** configúralo en **Settings → Desktop → PIN Setup → Set PIN**. Un PIN son de 4 a 10 pulsaciones de las
  flechas. El Flipper bloqueado pide entonces el PIN. Tras varios intentos fallidos muestra `Wrong PIN!` y un tiempo
  de espera antes del siguiente intento.
- **Auto Lock:** **Settings → Desktop → Auto Lock Time** (`OFF`, `10s` … `10min`) bloquea el dispositivo tras ese
  tiempo de inactividad. **Auto Lock disarm by active USB session** = `ON` evita el bloqueo automático mientras el
  Flipper esté conectado por USB.

::: warning PIN olvidado
Un PIN olvidado solo se puede restablecer junto con todos los ajustes de usuario: véase
[Recuperación → Restablecer un PIN olvidado](/es/start/recovery#reset-pin). Los archivos de la tarjeta microSD se
conservan.
:::

## Dummy Mode {#dummy-mode}

El Dummy Mode convierte el Flipper en un juguete. La mayoría de las funciones quedan ocultas y los botones lanzan
las aplicaciones que elijas, por ejemplo juegos. Se activa en **Lock Menu → Dummy Mode** y se desactiva con
**Lock Menu → Default Mode**.

En el Dummy Mode, cada botón puede arrancar su propia aplicación. Se configuran en **Settings → Desktop**:

`DummyMode - Left`, `- Left Long`, `- Right`, `- Right Long`, `- Up Long`, `- Down`, `- Down Long`, `- Ok`,
`- Ok Long`.

Un botón sin asignar abre el Passport. Una pulsación corta de <kbd>↑</kbd> sigue abriendo el Lock Menu. Si
`DummyMode - Up Long` está en `None`, una pulsación larga de <kbd>↑</kbd> bloquea el dispositivo.

::: tip Unleashed
El firmware de serie tiene 4 atajos de Dummy Mode. Unleashed tiene 9 (pulsación corta y larga en cada botón), así
que puedes tener varios juegos a una sola pulsación.
:::

## Aplicaciones favoritas (acceso rápido)

**Settings → Desktop → Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long**

Para cada ranura puedes elegir:
- **Apps Menu (Default)** o **Passport (Default)**: el valor por defecto integrado de esa ranura;
- **None (disable)**: el botón no hace nada;
- **Lock Flipper**;
- cualquier aplicación del menú principal;
- **[Select App]**: elige cualquier archivo `.fap` de `/ext/apps/`.

## Archive

Pulsa <kbd>↓</kbd>. El Archive muestra tus archivos guardados ordenados en pestañas. Cambia de pestaña con
<kbd>←</kbd>/<kbd>→</kbd>:

| Pestaña | Carpeta / contenido |
|---|---|
| Favorites | Los archivos que has fijado |
| iButton | `/ext/ibutton` (`.ibtn`) |
| NFC | `/ext/nfc` (`.nfc`) |
| Sub-GHz | `/ext/subghz` (`.sub`) |
| SubRem | `/ext/subghz_remote`: mapas de Sub-GHz Remote |
| RFID LF | `/ext/lfrfid` (`.rfid` y volcados de T5577) |
| Infrared | `/ext/infrared` (`.ir`) |
| Bad USB | `/ext/badusb` (`.txt`) |
| Phone | `/ext/phonebook`: agenda de SIM800 (`.phone`) |
| U2F | Token U2F |
| Apps | `/ext/apps` (`.fap` y `.js`) |
| Internal | Almacenamiento interno (solo con **Debug** = `ON`) |
| Browser | Toda la tarjeta microSD |

Pulsa <kbd>OK</kbd> sobre un archivo para abrir su menú contextual: ejecutar/emular, **Pin**/**Unpin** (añadir a
favoritos), **Rename**, **Delete** y, en el Browser, también **Cut**, **Copy**, **Paste** y **NewDir**. En la
pestaña Favorites, mantén <kbd>OK</kbd> para abrir el menú.

::: tip Fijar ajustes a favoritos
En **Main Menu → Settings**, mantén <kbd>OK</kbd> sobre cualquier elemento de ajustes para fijarlo a favoritos.
Después podrás abrirlo desde el Archive sin pasar por los menús.
:::

## Passport

Pulsa <kbd>→</kbd> en el escritorio, o abre **Settings → Passport**. Muestra el nombre del delfín (el nombre del
Flipper), su humor y su nivel: véase [El delfín mascota](/es/start/dolphin).
