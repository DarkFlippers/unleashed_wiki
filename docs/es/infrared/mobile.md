---
title: Mandos en la aplicación móvil
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Mandos IR en Flipper Mobile App

Flipper Mobile App (iOS / Android) incluye una **Remotes Library**: una base de datos en línea de mandos IR. Eliges
el tipo de aparato y la marca, la aplicación encuentra el mando adecuado probando unas pocas señales, lo descarga al
Flipper y después muestra un diseño de mando completo en la pantalla del móvil. La transmisión la hace el Flipper.

Frente a los [mandos universales](/es/infrared/universal-remotes), que envían toda la biblioteca en cada pulsación,
un mando de la Remotes Library se localiza **una sola vez** y después funciona al instante. Además tiene más botones
y cubre más tipos de aparatos.

## Qué puedes encontrar

La biblioteca incluye mandos para, entre otros: televisores, proyectores, TV boxes, ventiladores, purificadores de
aire, reproductores de DVD, cámaras y receptores AV. La base de datos es de código abierto:
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB); puedes aportar tu mando siguiendo su
[guía de contribución](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md).

::: tip Unleashed
La aplicación móvil funciona con Unleashed igual que con el firmware original: se comunica con la aplicación
Infrared por RPC. Mientras el móvil la controla, la pantalla del Flipper muestra **"Infrared – RPC mode"**. Los
mandos descargados desde la aplicación son ficheros `.ir` normales en `/ext/infrared/` y se pueden usar, editar y
renombrar en el Flipper como cualquier mando aprendido. Más sobre la aplicación en sí:
[Flipper Mobile App](/es/mobile/mobile-app).
:::

## Encontrar el mando de tu aparato

1. Conecta el Flipper a la aplicación por Bluetooth.
2. En la aplicación ve a `Tools → Remotes Library`.
3. Selecciona el **tipo de aparato** y después la **marca**.
4. Muchas marcas tienen varios mandos, así que la aplicación prueba las señales una a una: apunta con el Flipper al
   aparato, toca el botón para enviar la señal y responde si el aparato ha reaccionado.
5. Cuando se encuentra el mando correcto, la aplicación muestra su diseño. Puedes usarlo de inmediato.
6. Toca **Save** (arriba a la derecha) y ponle un nombre al mando. Se escribe en el Flipper.
7. *(Opcional)* Toca **⋯ → Add to Favorites** para tenerlo en la pestaña Archive y acceder rápidamente.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Usar un mando guardado

**Desde el móvil.** En la aplicación abre `Archive → Infrared` (o Favorites), selecciona el mando, apunta con el
Flipper al aparato y toca los botones en el móvil. La aplicación le indica al Flipper qué señal debe enviar.

![Diseño del mando en la aplicación](/img/remote/7387cb59433e202d.jpg)

**Solo desde el Flipper.** Ve a `Main Menu → Infrared → Saved Remotes`, abre el mando, elige un botón con
<kbd>↑</kbd> / <kbd>↓</kbd> y pulsa <kbd>OK</kbd>. Véase
[Aprender y enviar señales](/es/infrared/read#send-a-saved-button).

## Resolución de problemas

| Problema | Qué probar |
|---|---|
| La aplicación no puede enviar / no pasa nada | Comprueba que el Flipper esté conectado y no esté ocupado en otra aplicación. Cierra cualquier aplicación abierta en el Flipper y vuelve a intentarlo. |
| No se encuentra ningún mando para tu marca | Aprende el mando original en el Flipper ([cómo](/es/infrared/read)) o prueba los [mandos universales](/es/infrared/universal-remotes). |
| El aparato solo reacciona desde muy cerca | Usa un [módulo IR externo](/es/infrared/external-ir); la aplicación emplea el transmisor seleccionado en los GPIO Settings de Infrared. |

## Páginas relacionadas

- [Flipper Mobile App](/es/mobile/mobile-app)
- [Mandos universales](/es/infrared/universal-remotes)
- [Formato de los ficheros IR](/es/infrared/file-format)
