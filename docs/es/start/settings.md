---
title: Ajustes
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Ajustes

**Main Menu → Settings** contiene estos elementos, en el orden en el que aparecen en el dispositivo:

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

En listas como estas, muévete con <kbd>↑</kbd>/<kbd>↓</kbd>, cambia un valor con <kbd>←</kbd>/<kbd>→</kbd> y abre con
<kbd>OK</kbd> los elementos que tienen una subpantalla.

![Menú Settings: About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Fijar un ajuste a favoritos
Mantén <kbd>OK</kbd> sobre cualquier elemento de la lista de Settings para fijarlo a la pestaña **Favorites** del
Archive (o quitarlo de ella). Así lo tienes a mano desde el escritorio con <kbd>↓</kbd>.
:::

::: info
La mayoría de las aplicaciones de ajustes (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input, LCD
and Notifications, Passport) son archivos `.fap` que la actualización del firmware instala en
`/ext/apps/assets/`. **Power**, **Storage** y **System** están integrados en el firmware y funcionan incluso sin
tarjeta SD.
:::

## About

Pantallas informativas. Pasa de una a otra con **Next** (<kbd>→</kbd>) y **Prev.** (<kbd>←</kbd>):

1. Aviso de **Unleashed Firmware**: solo con fines experimentales, no para uso ilícito;
2. licencia: el firmware es libre y de código abierto, y *«If you paid any money for it - you got scammed.»*;
3. *«Community apps included in all builds except `c` build»* y un enlace a github.com/DarkFlippers;
4. producto, modelo, FCC ID / IC;
5. enlace de conformidad y dirección del fabricante;
6. **HW Version Info**: versión del hardware, región, nombre del Flipper, número de serie;
7. **FW Version Info**: versión y fecha de compilación, hash de git, versión de la API, pila de radio, objetivo y
   rama.

## Bluetooth

| Elemento | Valores / acción |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Muestra `Broken` si la pila de radio está dañada ([Recuperación](/es/start/recovery)) |
| **Unpair All Devices** | Confirma con **Unpair**. Elimina todos los emparejamientos, incluidas las claves de emparejamiento de Bad USB por Bluetooth (BadKB), del Bluetooth Remote y del Authenticator |

Usa **Unpair All Devices** si la aplicación móvil deja de conectarse después de una instalación o de un cambio de
nombre. Véase las [preguntas frecuentes](/es/start/faq).

## Clock & Alarm

Una sola pantalla con tres filas: **Time** (hh:mm:ss), **Date** (dd.mm.yyyy) y **Alarm** (hh:mm, `On`/`Off`).

1. Selecciona una fila con <kbd>↑</kbd>/<kbd>↓</kbd> y un campo con <kbd>←</kbd>/<kbd>→</kbd>.
2. Pulsa <kbd>OK</kbd> para editar y cambia el valor con <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Pulsa <kbd>OK</kbd> o <kbd>BACK</kbd> para dejar de editar.

Cuando suena la alarma, <kbd>BACK</kbd> la **posterga** 9 minutos y cualquier otro botón la detiene. Una alarma que
nadie detiene se apaga sola al cabo de 10 minutos. La aplicación **Clock** del menú principal muestra un reloj
grande y tiene controles de brillo, la alarma y un temporizador.

## Desktop

| Elemento | Valores | Descripción |
|---|---|---|
| **PIN Setup** | → submenú | **Set PIN** / **Change PIN** / **Remove PIN**. Un PIN son de 4 a 10 pulsaciones de las flechas |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Bloquear tras un tiempo de inactividad |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Sin bloqueo automático mientras esté conectado por USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Estilo del icono de la batería |
| **Show Clock** | `OFF` / `ON` | Reloj en el escritorio |
| **Menu Style** | `Default` + los estilos instalados | Aspecto del menú principal. Los estilos son plugins `menu_style_*` de `/ext/apps_data/loader/plugins/`. Muestra `Missing` si el archivo del estilo seleccionado se ha borrado |
| **Change Flipper Name** | texto | [Nombre personalizado del Flipper](/es/start/custom-name) |
| **Happy Mode** | Enable / Disable | El delfín no se enfada nunca ([El delfín mascota](/es/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | aplicación | Aplicaciones de acceso rápido del escritorio |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | aplicación | Aplicaciones para el [Dummy Mode](/es/start/desktop#dummy-mode) |

Para cada ranura de Favorite/Dummy puedes elegir **Apps Menu (Default)** o **Passport (Default)**,
**None (disable)**, **Lock Flipper**, cualquier aplicación del menú principal, o **[Select App]** para elegir
cualquier `.fap` de `/ext/apps/`.

::: warning PIN
La pantalla de configuración advierte: *«Forgotten PIN can only be reset with entire device.»* El restablecimiento
del PIN borra también tus ajustes (los archivos de la tarjeta SD se conservan): véase
[Recuperación](/es/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock y las 9 ranuras del Dummy Mode son añadidos de Unleashed.
:::

## Expansion Modules

| Elemento | Valores | Descripción |
|---|---|---|
| **Listen UART** | `USART` (pines 13, 14), `LPUART` (pines 15, 16), `None` | Qué UART escucha a los módulos que usan el protocolo de expansión (por ejemplo, el [Video Game Module](/es/gpio/video-game-module)) |

Ponlo en `None` si no usas módulos de ese tipo. Así se ahorra energía y el Flipper puede dormir.

## Input

| Elemento | Valores | Descripción |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Respuesta vibratoria en los eventos de botón. Los números más altos dan un pulso más largo |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Cuándo se dispara la respuesta |

## LCD and Notifications

| Elemento | Valores | Descripción |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Contraste de la pantalla |
| **LCD Backlight** | `0%` … `100%` (en pasos del 5 %) | Brillo de la retroiluminación |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Tiempo hasta apagar la retroiluminación |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Atenúa la retroiluminación en esa cantidad durante la franja nocturna |
| **. Start** | `17:00` … `23:30` | Inicio de la franja nocturna (bloqueado mientras Night Shift esté en `OFF`) |
| **. End** | `05:00` … `11:30` | Fin de la franja nocturna |
| **LED Brightness** | `0%` … `100%` | Brillo del LED de estado |
| **Volume** | `0%` … `100%` | Volumen del altavoz (`Stealth` cuando está silenciado desde el Lock Menu) |
| **Vibro** | `OFF` / `ON` | Vibración (`Stealth` cuando está silenciada) |
| **LCD Inversion** | `OFF` / `ON` | Invierte los colores de la pantalla |
| **RGB Mod Settings** | → submenú | Solo para los Flipper con el **mod de hardware** de retroiluminación RGB |

**RGB Mod Settings** (<kbd>OK</kbd> sobre el elemento): **RGB backlight installed** (`OFF`/`ON`). Los demás
elementos siguen bloqueados (`RGB MOD OFF!`) hasta que esto esté en `ON`: **LED 1 Color**, **LED 2 Color**,
**LED 3 Color**, **Effects** (`OFF`, `Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`),
**. Saturation**, **. Wave wide** (`1`–`3`).

::: danger Mod RGB
Activa **RGB backlight installed** **solo** si tu Flipper tiene el
[mod de hardware de retroiluminación RGB](https://github.com/quen0n/flipperzero-firmware-rgb#readme). En un Flipper
de serie, la retroiluminación deja de funcionar. Si te ha pasado, vuelve aquí y ponlo en `OFF` (véase las
[preguntas frecuentes](/es/start/faq#backlight-does-not-work)).
:::

## Passport

El perfil del delfín: nombre, humor y nivel. También se abre con <kbd>→</kbd> en el escritorio. Véase
[El delfín mascota](/es/start/dolphin).

## Power

| Elemento | Valores | Descripción |
|---|---|---|
| **Battery Info** | — | Carga, tensión, corriente, temperatura y salud |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Reiniciar en modo DFU (`Reboot to DFU Mode?`) o un reinicio normal |
| **Power OFF** | — | Apagar |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Apagar tras un tiempo de inactividad |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Dejar de cargar en ese nivel |

Más información: [Energía y batería](/es/start/power).

## Storage

| Elemento | Descripción |
|---|---|
| **About Internal Storage** | Información del almacenamiento interno (`Virtual (/.int on SD)`) y flash libre |
| **About SD Card** | Etiqueta, tipo, tamaño, espacio libre, fabricante y número de serie de la tarjeta |
| **Unmount SD Card** / **Mount SD Card** | Extracción segura / volver a montar |
| **Format SD Card** | Borrar y formatear la tarjeta |
| **Benchmark SD Card** | Prueba de velocidad por SPI |
| **Factory Reset** | Pulsa **Erase** 5 veces. Borra el almacenamiento interno y reinicia |

Más información: [Tarjeta microSD](/es/start/sd-card), [Recuperación](/es/start/recovery#factory-reset).

## System

| Elemento | Valores | Descripción |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Modo para zurdos: gira la pantalla y reasigna los botones |
| **Units** | `Metric` / `Imperial` | Unidades (por ejemplo, °C/°F en Battery Info) |
| **Time Format** | `24h` / `12h` | Formato del reloj |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Formato de la fecha |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Cuánto se registra. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART usado para los registros (USART = pines 13/14, LPUART = pines 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Velocidad del UART de registro |
| **Debug** | `OFF` / `ON` | Modo de depuración: funciones de depuración adicionales en las aplicaciones, pestaña **Internal** del Archive, acceso SWD |
| **Heap Trace** | `None`, `Main` | Trazado de las asignaciones de memoria (para desarrolladores) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` consume más (~9 mA frente a ~1,5 mA), pero puede ser más estable |
| **File Naming** | `Default` / `Detailed` | `Detailed` incluye el tipo, la fecha y la hora en los nombres de los archivos nuevos |

![Settings → System: Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

**Debug** tiene un atajo: mantén <kbd>↓</kbd> en el escritorio y después mantén <kbd>OK</kbd> en la pantalla
informativa ([Escritorio → Pantalla de información del dispositivo](/es/start/desktop#info-screen)).

::: warning ¿El Flipper va lento?
Para el uso normal, mantén **Log Level** en `None` (o `Default`), **Debug** en `OFF` y **Heap Trace** en `None`. Los
ajustes de depuración ralentizan el dispositivo y le impiden dormir.
:::

## Relacionado

- [Escritorio](/es/start/desktop): qué hacen en la práctica los ajustes del escritorio
- [Nombre personalizado del Flipper](/es/start/custom-name)
- [Ajustes de Sub-GHz](/es/subghz/settings): los ajustes de radio dentro de la aplicación Sub-GHz
