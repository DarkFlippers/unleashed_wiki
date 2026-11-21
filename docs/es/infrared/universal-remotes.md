---
title: Mandos universales
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Mandos universales

Un mando universal te permite controlar un aparato **sin aprender antes su mando**. Cuando pulsas, por ejemplo,
*Power*, el Flipper envía el código de encendido de todos los modelos de su biblioteca, uno tras otro. Cuando acierta
con el código que tu aparato entiende, este reacciona. Por eso un botón universal tarda unos segundos en lugar de ser
instantáneo.

Abre `Main Menu → Infrared → Universal Remotes`.

![La lista de categorías de Universal Remotes: TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
El firmware oficial incluye bibliotecas de televisores, audio, proyectores y aires acondicionados. Unleashed añade
**LEDs** y **Fans** y mantiene todas las bibliotecas mucho más grandes y verificadas con regularidad por el equipo
(recursos IR de @amec0e). La biblioteca de televisores se recompila para que funcionen **todos** sus botones, no solo
Power.
:::

## Categorías

Los elementos de menú y los nombres de botón que figuran abajo están tomados del firmware; el número de señales
corresponde a las bibliotecas incluidas en la compilación `dev` actual (`/ext/infrared/assets/`, actualizadas por
última vez en octubre de 2024, y en febrero de 2024 para el aire acondicionado).

| Elemento de menú | Fichero de biblioteca | Botones | Señales en la biblioteca |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (295 de ellas Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

«Audio» cubre barras de sonido, receptores AV, minicadenas y similares. «LEDs» se refiere a tiras y bombillas LED
controladas por infrarrojos.

### Aires acondicionados

Los mandos de aire acondicionado mantienen ellos mismos el estado del aparato y envían el estado completo en cada
pulsación, así que la biblioteca de aires acondicionados contiene «escenas» completas en lugar de botones sueltos:

| Botón | Significado |
|---|---|
| **Off** | Apagar el aire acondicionado. Es el *único* botón que lo apaga. |
| **Dh** | Modo deshumidificador (seco). |
| **Cool_hi** | Refrigeración a la temperatura más baja que permita el mando (frío máximo). |
| **Cool_lo** | Refrigeración a 23 °C. |
| **Heat_hi** | Calefacción a la temperatura más alta que permita el mando (calor máximo). |
| **Heat_lo** | Calefacción a 23 °C. |

Para **encender** un aire acondicionado, pulsa cualquier botón que no sea Off. Los botones de temperatura muestran
°C o °F según `Settings → System → Units`.

## Cómo se usa

1. Ve a `Main Menu → Infrared → Universal Remotes` y selecciona una categoría.
2. Apunta con el borde superior del Flipper hacia el aparato. Mantente cerca y con visión directa.
3. Selecciona un botón con las flechas y pulsa <kbd>OK</kbd>.

   ![El mando universal de televisor, en pantalla vertical: Power y Mute arriba, Channel y Volume arriba/abajo debajo](/screens/infrared/universal_tv.png)

4. La ventana **"Sending..."** muestra el progreso como `actual/total` y una barra de progreso. Sigue apuntando al
   aparato.
5. Cuando el aparato reaccione, pulsa <kbd>OK</kbd> para **pausar**, o deja que la biblioteca llegue al final.

![Mando universal en funcionamiento](/img/remote/bdb3541a3f2e88fe.png)

### Controles durante el envío

| Estado | Botón | Acción |
|---|---|---|
| Enviando | <kbd>OK</kbd> | **pausar** |
| Enviando | <kbd>Back</kbd> | **detener** |
| En pausa | <kbd>Back</kbd> | **reanudar** el envío desde donde se detuvo |
| En pausa | <kbd>OK</kbd> | **send 1**: enviar solo la señal seleccionada |
| En pausa | <kbd>←</kbd> / <kbd>→</kbd> (flechas) | **seleccionar** la señal anterior / siguiente de la biblioteca |
| En pausa | <kbd>↓</kbd> | **guardar** la señal seleccionada |

## Encontrar el código exacto y guardarlo

La verdadera utilidad de la pantalla de pausa: puedes localizar el único código que funciona y conservarlo, de modo
que la próxima vez el botón sea instantáneo.

1. Ejecuta un botón universal. En cuanto el aparato reaccione, pulsa <kbd>OK</kbd> (pausa). El contador apunta ahora
   a la última señal enviada.
2. Como nunca eres perfectamente rápido, retrocede con la flecha izquierda y usa **send 1** (<kbd>OK</kbd>) en cada
   señal hasta encontrar la que activa el aparato. Usa la flecha derecha para avanzar de nuevo.
3. Pulsa <kbd>↓</kbd> **save**. El encabezado del menú muestra el nombre del botón (por ejemplo `Power`), que es
   también el nombre con el que se guarda la señal:
   - **Save as New Remote**: escribe un nombre de mando en **"Name the remote"**; se crea un fichero `.ir` nuevo en
     `/ext/infrared/`;
   - **Add to Existing Remote**: elige un fichero `.ir` existente; la señal se añade al final.
4. **"Saved"** lo confirma. El mando está ya en `Infrared → Saved Remotes`.

Repítelo para Vol_up, Mute, etc., añadiendo cada uno al mismo mando: acabarás con un mando personal e instantáneo
construido a partir de la biblioteca universal.

![Un mando guardado en pantalla vertical: la lista de botones Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## Desde la línea de comandos

Las mismas bibliotecas se pueden reproducir desde la [CLI](/es/dev/cli):

```text
ir universal list tv        # list the signal names in tv.ir
ir universal tv Power       # send every "Power" signal from tv.ir
```

`ir universal` sin argumentos lista las bibliotecas disponibles (todos los ficheros `.ir` de
`/ext/infrared/assets/`). Pulsa <kbd>Ctrl</kbd>+<kbd>C</kbd> en el terminal para detenerlo.

## Resolución de problemas

| Problema | Qué probar |
|---|---|
| *"Function requires SD card with fresh databases."* | Faltan los ficheros de biblioteca. Inserta la tarjeta microSD y reinstala o actualiza el firmware con la tarjeta puesta; véase [Actualización](/es/start/updating). |
| Nada reacciona después de recorrer toda la biblioteca | Tu modelo no está en la biblioteca. [Aprende](/es/infrared/read) el mando original, prueba la [Remotes Library de la aplicación móvil](/es/infrared/mobile) y considera [contribuir con capturas](/es/infrared/captures). |
| El aparato reacciona, pero demasiado tarde para pausar | Usa la flecha izquierda + **send 1** para retroceder hasta la señal correcta; véase más arriba. |
| Solo funciona a muy poca distancia | Los LED integrados son débiles para habitaciones grandes. Usa un [módulo IR externo](/es/infrared/external-ir). |
| El aire acondicionado no se enciende con Off | Es lo esperado: Off solo lo apaga. Usa Cool/Heat/Dh para encenderlo. |

## Páginas relacionadas

- [Contribuir con capturas](/es/infrared/captures): añade tu aparato a las bibliotecas
- [Formato de los ficheros IR](/es/infrared/file-format): formato de los ficheros de biblioteca
- [Aprender y enviar señales](/es/infrared/read)
