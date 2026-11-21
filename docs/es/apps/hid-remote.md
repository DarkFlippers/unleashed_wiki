---
title: Mando por USB / Bluetooth (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# Mando por USB / Bluetooth (HID)

La app HID hace que el Flipper se presente como un teclado, un ratón o un mando multimedia (un **H**uman
**I**nterface **D**evice USB) ante un ordenador, un móvil o una tableta. La misma app se compila dos veces:

| App | Dónde está en el Flipper | Conexión |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | Cable USB |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Cómo conectarlo está en [Emparejar el mando HID](/es/apps/controllers). Esta página describe todos los modos.

## Modos

El menú inicial lista:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

La versión por Bluetooth tiene además `Bluetooth Remote Name` y `Bluetooth Unpairing`.

::: tip Unleashed
La documentación oficial describe Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler y Mouse Clicker. La
compilación de la app de Unleashed tiene además **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler
Stealth**, **PushToTalk** y **Bluetooth Remote Name** para cambiar el nombre con el que se anuncia el mando.
:::

En casi todos los modos, **mantén pulsado <kbd>Back</kbd> para salir** a la lista de modos; al salir se liberan todas
las teclas.

### Keynote y Keynote Vertical

Un mando para presentaciones. Keynote Vertical es el mismo, girado para sujetar el Flipper en vertical.

| Botón | Envía |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | teclas de flecha (diapositiva siguiente / anterior) |
| <kbd>OK</kbd> | Espacio |
| <kbd>Back</kbd> | Retroceso + «AC Back» (sale del modo presentación en la mayoría de las apps) |
| mantener <kbd>Back</kbd> | salir |

### Keyboard

Un teclado QWERTY en pantalla con dígitos, símbolos, F1-F12, Esc, Tab, Enter, Retroceso, Suprimir y los modificadores
Ctrl, Alt, Shift y Cmd (Win).

1. Muévete con las flechas y pulsa <kbd>OK</kbd> para escribir la tecla seleccionada.
2. Selecciona la tecla ⬆ (Shift) para escribir en mayúsculas y la segunda fila de símbolos.
3. Para un atajo pulsa primero el modificador (Ctrl, Alt o Cmd) y después la tecla.
4. Mantén <kbd>Back</kbd> para salir.

### Numpad

Un teclado numérico: `0`-`9`, `.`, `+`, `-`, `*`, `/`, `En` (Enter del teclado numérico), `NL` (Bloq Num) y Retroceso.
Las flechas seleccionan, <kbd>OK</kbd> pulsa la tecla y mantener <kbd>Back</kbd> sale.

### Media

| Botón | Envía |
|---|---|
| <kbd>OK</kbd> | Reproducir / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | pista anterior / siguiente |
| <kbd>↑</kbd> / <kbd>↓</kbd> | subir / bajar volumen |
| mantener <kbd>Back</kbd> | salir |

En los móviles las teclas de volumen funcionan también como disparador de la cámara: abre la cámara y pulsa
<kbd>↑</kbd> o <kbd>↓</kbd> para hacer una foto o iniciar/detener un vídeo.

### Apple Music macOS

| Botón | Envía |
|---|---|
| <kbd>OK</kbd> | Reproducir / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | pista anterior / siguiente |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (volumen en Apple Music) |
| mantener <kbd>Back</kbd> | salir |

### Movie

| Botón | Envía |
|---|---|
| <kbd>OK</kbd> | Reproducir / Pausa |
| <kbd>←</kbd> / <kbd>→</kbd> | flecha izquierda / derecha (avanzar o retroceder en la mayoría de los reproductores) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | subir / bajar volumen |
| mantener <kbd>Back</kbd> | salir |

### Mouse

| Botón | Acción |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | mover el cursor; al mantener pulsado se acelera |
| <kbd>OK</kbd> | clic izquierdo |
| mantener <kbd>OK</kbd> | mantener pulsado el botón izquierdo (arrastrar, «Selecting...») |
| <kbd>Back</kbd> | clic derecho |
| mantener <kbd>Back</kbd> | salir |

### TikTok / YT Shorts

Para las apps de vídeos cortos en un móvil o una tableta.

| Botón | Acción |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | pasar al vídeo anterior / siguiente |
| <kbd>OK</kbd> | doble toque (me gusta) |
| <kbd>←</kbd> / <kbd>→</kbd> | bajar / subir volumen |
| <kbd>Back</kbd> | un toque (pausa) |
| mantener <kbd>Back</kbd> | salir |

::: tip iPhone / iPad
Si el modo TikTok no hace nada en iOS, activa `Settings → Accessibility → Touch → AssistiveTouch` y después, en
**Pointer Devices → Devices → Bluetooth Devices**, selecciona tu Flipper.
:::

### Mouse Clicker

Hace clic automáticamente a un ritmo fijado.

| Botón | Acción |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | clics por segundo, hasta 100 (por defecto 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | qué botón: izquierdo, derecho o rueda (central) |
| <kbd>Back</kbd> | salir |

### Mouse Jiggler

Mueve un poco el cursor a un intervalo fijo, para que el ordenador no se duerma ni te muestre como «ausente».

1. Antes de arrancarlo, elige el intervalo con <kbd>←</kbd> / <kbd>→</kbd>: 500, 2000, 5000, 10000, 30000 o 60000 ms
   (por defecto 5000 ms).
2. Pulsa <kbd>OK</kbd> para **Start** y otra vez para **Stop**. Hasta que el host se conecta, la pantalla indica
   `Waiting for Connection...`.
3. <kbd>Back</kbd> sale.

### Mouse Jiggler Stealth

Igual que el jiggler, pero se mueve a intervalos aleatorios entre un mínimo y un máximo que fijas en minutos (de 1 a
30), lo que parece menos automático. Mientras está parado, <kbd>↑</kbd> / <kbd>↓</kbd> cambian el mínimo y
<kbd>→</kbd> / <kbd>←</kbd> suben o bajan el máximo; <kbd>OK</kbd> arranca o para.

### PushToTalk

Un botón de silencio / pulsar para hablar en videollamadas.

1. Elige la lista de tu sistema operativo (**macOS** o **Win/Linux**) y después la app: Google Meet, Google Meet
   Global, Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle, TeamSpeak,
   Teams, Webex, Zoom o Zoom Global.
2. Mantén pulsado <kbd>OK</kbd> sobre una entrada de la lista para leer su ayuda (algunas apps necesitan un ajuste o
   una extensión, por ejemplo un atajo global para Google Meet o asignar las teclas en TeamSpeak).
3. En la llamada: <kbd>Back</kbd> conmuta el micrófono, **mantener <kbd>OK</kbd>** activa el pulsar para hablar (el
   micrófono se apaga al soltar) y mantener <kbd>→</kbd> cambia el estado del micrófono en el Flipper si se ha
   desincronizado del ordenador. En Zoom, una pulsación larga de <kbd>←</kbd> envía Enter.
4. Mantén <kbd>Back</kbd> para salir.

### Bluetooth Remote Name y Bluetooth Unpairing (solo Bluetooth)

- **Bluetooth Remote Name**: escribe un nombre en `Bluetooth Name`; el mando se anuncia con él. Por defecto aparece
  como `Control <Flipper name>`.
- **Bluetooth Unpairing**: pregunta `Unpair All Devices? All previous pairings will be lost!`; pulsa **Unpair** para
  olvidar todos los hosts emparejados con el mando. El mando conserva sus propias claves de emparejamiento
  (`/ext/apps_data/hid_ble/.bt_hid.keys`), separadas de los emparejamientos Bluetooth principales del Flipper.

## Páginas relacionadas

- [Emparejar el mando HID](/es/apps/controllers)
- [Bad USB](/es/badusb/usage)
- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
