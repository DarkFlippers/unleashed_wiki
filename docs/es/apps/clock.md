---
title: Reloj
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/clock_app, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# Reloj

Un reloj de mesilla: hora en grande, fecha y nivel de batería, control del brillo de pantalla con luz nocturna de LED
rojo, cronómetro y alarma diaria. Basado en FlipperNightStand de @nymda, con @Willy-JL, @mishamyte y @xMasterX
(versión 1.3 de la app).

`Main Menu → Clock`

![Reloj: la fecha encima de la hora en grande y el nivel de batería debajo](/screens/apps/clock.png)

::: tip Unleashed
En Unleashed el reloj es una app del menú principal con alarma y luz nocturna. Si solo quieres la hora en el
escritorio, activa `Settings → Desktop → Show Clock` en su lugar.
:::

## Botones en la pantalla del reloj

| Botón | Acción |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | subir / bajar el brillo de pantalla (aparece una barra que se oculta 3 s después de la última pulsación) |
| <kbd>↓</kbd> con el brillo a 0 | encender / apagar la tenue luz nocturna del LED rojo |
| <kbd>OK</kbd> | Start / Stop del cronómetro |
| <kbd>←</kbd> | reiniciar el cronómetro |
| <kbd>→</kbd> | configuración de la alarma |
| <kbd>Back</kbd> | salir |

La hora sigue el formato del sistema: 12 horas con AM/PM o 24 horas, según lo configurado en
`Settings → System → Time Format`.

## Cronómetro

1. Pulsa <kbd>OK</kbd> para arrancarlo; el tiempo transcurrido aparece como `MM:SS`.
2. Pulsa <kbd>OK</kbd> otra vez para pararlo y una más para continuar.
3. Pulsa <kbd>←</kbd> (**Reset**) para ponerlo a cero.

## Alarma diaria

1. En la pantalla del reloj pulsa <kbd>→</kbd>.
2. Pon **Alarm** en **ON** con <kbd>←</kbd> / <kbd>→</kbd>.
3. Selecciona **Set time** y pulsa <kbd>OK</kbd>.
4. En el selector `Alarm time`: <kbd>←</kbd> / <kbd>→</kbd> eligen horas, minutos (y AM/PM en el modo de 12 horas) y
   <kbd>↑</kbd> / <kbd>↓</kbd> cambian el valor (mantén pulsado para repetir). <kbd>OK</kbd> o <kbd>Back</kbd> guardan.
5. Pulsa <kbd>Back</kbd> para volver al reloj. La hora de la alarma se muestra en la pantalla del reloj.

Cuando la alarma suena, la pantalla parpadea con `! ALARM !` y `Press any key to stop`, se reproduce una melodía con
vibración y el LED rojo. Pulsa cualquier tecla para detenerla. La alarma sigue armada y vuelve a sonar al día
siguiente a la misma hora.

::: warning
La alarma solo suena mientras la app Clock está abierta. Deja el Flipper en el cargador con el reloj en marcha durante
la noche.
:::

La alarma y el nivel de brillo se guardan en `/ext/apps_data/clock/` y se restauran la próxima vez que abras la app.

## Páginas relacionadas

- [Escritorio](/es/start/desktop)
- [Ajustes](/es/start/settings)
- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
