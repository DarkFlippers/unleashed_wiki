---
title: Controles
order: 50
original: [https://docs.flipper.net/zero/basics/control, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/input_settings_app]
sources: [flipper-docs, unleashed-src]
---
# Controles

El Flipper Zero tiene un pad direccional de 5 posiciones y un botón <kbd>BACK</kbd> aparte.

| Botón | Qué hace |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Moverse por los menús y los teclados virtuales. <kbd>←</kbd>/<kbd>→</kbd> cambian el valor de la opción seleccionada |
| <kbd>OK</kbd> | Lanzar una aplicación, confirmar una elección. Una pulsación larga abre a menudo acciones adicionales |
| <kbd>BACK</kbd> | Volver atrás o salir de la aplicación. Una pulsación larga en el escritorio abre la pantalla de apagado |

En una lista, las flechas mueven el marco alrededor del elemento seleccionado y <kbd>OK</kbd> lo abre:

![Menú principal con el marco sobre Sub-GHz](/screens/mainmenu/subghz.png)

En esta wiki, «mantener» o «pulsación larga» significa pulsar un botón durante un segundo aproximadamente. Las
indicaciones de botón de la parte inferior de la pantalla (por ejemplo, `◀ Cancel` o `Save ▶`) muestran qué hacen
<kbd>←</kbd>, <kbd>OK</kbd> y <kbd>→</kbd> en esa pantalla.

## Modo para zurdos

**Main Menu → Settings → System → Hand Orient → `Lefty`**

La pantalla gira 180° y el pad se reasigna, de modo que puedes sujetar el Flipper con la mano izquierda.

## Atajos

| Acción | Cómo |
|---|---|
| Encender | Mantén <kbd>BACK</kbd> unos 3 s |
| Apagar | Mantén <kbd>BACK</kbd> en el escritorio → **Power Off** (<kbd>→</kbd>) |
| Reiniciar (dispositivo colgado) | Mantén <kbd>←</kbd> + <kbd>BACK</kbd> unos 5 s |
| Reinicio forzado (corte de alimentación) | Desconecta el USB y mantén <kbd>BACK</kbd> unos 30 s |
| Reiniciar en DFU (recuperación) | Mantén <kbd>←</kbd> + <kbd>BACK</kbd>, suelta <kbd>BACK</kbd> y sigue con <kbd>←</kbd> hasta que se encienda el LED azul |

Todas las combinaciones de reinicio y de DFU, y cuándo falla cada una, están en
[Combinaciones de teclas](/es/start/key-combos).

## Atajos del escritorio

| Botón | Pulsación corta | Pulsación larga |
|---|---|---|
| <kbd>OK</kbd> | Main Menu | Aplicación favorita (OK Long) |
| <kbd>↑</kbd> | Lock Menu | **Bloquear el Flipper** (con PIN si hay uno configurado) |
| <kbd>↓</kbd> | Archive | Pantalla de información y depuración del dispositivo |
| <kbd>←</kbd> | Aplicación favorita (Left Short), por defecto el menú Apps | Aplicación favorita (Left Long) |
| <kbd>→</kbd> | Passport (o la aplicación asignada) | Aplicación favorita (Right Long) |
| <kbd>BACK</kbd> | — | Pantalla de apagado |

Las aplicaciones se asignan en **Settings → Desktop → Favorite App - …**. Los detalles están en la página del
[Escritorio](/es/start/desktop).

::: tip Unleashed
Mantener <kbd>↑</kbd> en el escritorio bloquea el dispositivo al instante (con el PIN, si hay uno configurado). En el
firmware de serie, el bloqueo se hace desde el Lock Menu.
:::

Una pulsación corta de <kbd>↑</kbd> abre el Lock Menu:

![Lock Menu: Turn Bluetooth On seleccionado, con Mute y Dummy Mode debajo](/screens/desktop/lock_menu.png)

Si hay un PIN configurado, el Flipper lo pide antes de desbloquearse. Las flechas escriben el código, <kbd>BACK</kbd>
lo borra y <kbd>OK</kbd> confirma:

![Enter PIN: cuatro dígitos introducidos mostrados como asteriscos, una quinta casilla vacía, la indicación de borrado y el botón OK](/screens/desktop/pin_input.png)

Una pulsación larga de <kbd>↓</kbd> abre la pantalla de información del dispositivo: tiempo encendido, revisión del
hardware, nombre del Flipper, versión y fecha de compilación del firmware, commit, versión de la API y el flag Debug.
Una pulsación larga de <kbd>OK</kbd> en esa pantalla activa y desactiva Debug:

![Pantalla de información del dispositivo: Uptime 1h23m45s, hardware 13.F7B9C6 R00, firmware unlshd-080 compilado el 21-11-2026 y D:ON](/screens/desktop/debug.png)

## Respuesta de los botones

**Main Menu → Settings → Input**

| Elemento | Valores | Significado |
|---|---|---|
| Buttons Vibro | `OFF`, `1`…`9` | Vibración corta en cada evento de botón. Los números más altos vibran más tiempo |
| Vibro Trigger | `Press`, `Release`, `Both` | Cuándo se dispara la vibración |

## Entrada de texto

En el teclado virtual, muévete con las flechas y pulsa <kbd>OK</kbd> para escribir el carácter seleccionado. Mantén
<kbd>OK</kbd> sobre una letra para escribirla en mayúscula. Selecciona la tecla `⏎` / **Save** para confirmar.
<kbd>BACK</kbd> borra el último carácter o sale del teclado.

::: tip Unleashed
La entrada de texto tiene **cursor**, así que puedes editar en medio del texto. En la **entrada de bytes** en
hexadecimal (por ejemplo, al añadir una clave a mano), pulsa <kbd>↑</kbd> varias veces hasta que aparezca el
**minieditor de nibbles**. Te permite cambiar medio byte a la vez.
:::
