---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** y **BFT Mitto** construyen su código rodante a partir de una **semilla**
secreta. Sin ella el Flipper no puede decodificar estos mandos (se leen como `KL: Unknown` o no se leen en absoluto)
ni construir un mando que el receptor acepte. **Seed Capturer** (de @xMasterX) recopila el material bruto para
recuperar la semilla: el `Fix` del mando y una serie de valores `Hop` consecutivos.

**No** recupera la semilla por sí mismo y **nunca transmite**: solo escucha y escribe un fichero. La búsqueda se
ejecuta en la aplicación acompañante [qUnleashed](/es/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer es una aplicación de sistema integrada de Unleashed, y qUnleashed lee sus capturas directamente del
Flipper. Una vez conocida la semilla, Unleashed puede decodificar el mando y crear otros nuevos mediante
`Add Manually [Advanced]`.
:::

## Cuándo lo necesitas

- La programación por radio del receptor está desactivada, así que la única vía de entrada es un clon de un mando
  conocido, y un clon necesita la semilla.
- Tu mando FAAC / Genius es un **esclavo**, que no puede enviar el código de programación.
- No puedes acceder al receptor.
- Instalaciones **Erreka** en las que todos los mandos comparten una misma semilla.
- Mandos **BFT Mitto antiguos** con semilla única cuando la vía del botón de programación no funciona (los mandos
  BFT más nuevos derivan la semilla del número de serie y se decodifican en un Read normal).

Si el mando se puede poner en modo de programación, la semilla suele enviarse en claro; esa vía es más rápida: véase
[Programar un mando nuevo](/es/subghz/remote-prog).

## Capturar

1. Abre `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Elige `New capture`.
3. **Tipo de mando:** `FAAC SLH`, `Genius`, `Erreka` o `BFT Mitto`.
4. **Frecuencia:** `433.92 MHz  AM650` o `868.35 MHz  AM650` (`BFT Mitto` solo ofrece 433.92 MHz).
5. Pulsa **el mismo botón del mismo mando** una y otra vez, aproximadamente una vez por segundo, con el mando pegado
   al Flipper.
6. Observa la pantalla:
   - `Fix XXXXXXXX`: la parte fija del mando; la aplicación se queda con la primera que oye;
   - `Hops n/10  Xpkt`: cuántos saltos **distintos** se han recopilado y el número de paquetes en bruto;
   - el estado `Hop n: XXXXXXXX` cada vez que llega uno nuevo.
7. A partir de **2 saltos** aparece `Save` en <kbd>OK</kbd>. Púlsalo; la aplicación muestra `Saved N hops` y el
   nombre del fichero.

<kbd>←</kbd> (`Reset`) descarta la captura para que puedas fijarte en otro mando u otro botón.

| Estado | Significado |
|---|---|
| `Hop n: XXXXXXXX` | parte rodante nueva almacenada: sigue pulsando |
| `Other remote XXXXXXXX` | otro mando u otro botón: se ignora |
| `Same hop, ignored` | repetición de la última pulsación |
| `Have 10, enough` | lleno: pulsa `Save` |

**Cuántas pulsaciones:** 2 es el mínimo, 5–10 es mejor. Y hay algo igual de importante: las pulsaciones deben ser
**consecutivas, sin perder ninguna**; comprueba que `Hops` suba con cada pulsación. Si se pierde una, pulsa `Reset`
y empieza de nuevo.

::: warning
En **FAAC SLH y Genius la semilla es distinta para cada botón**: captura el botón que realmente vayas a usar. En
Erreka la semilla es por mando (a veces por instalación), y en BFT Mitto por mando.
:::

## Otros elementos del menú

- `Decode RAW file`: toma el Fix y los Hops de un `.sub` RAW (de `/ext/subghz`) grabado previamente con
  [Read RAW](/es/subghz/read-raw); la frecuencia se toma del fichero. Un fichero de clave se rechaza con
  `Not a RAW capture`. Aquí <kbd>←</kbd> es `Back` en lugar de `Reset`.
- `Delete all captures`: pregunta `Delete every capture file in subghz_seed_captures?` y después los borra.
- `Exit`.

## El fichero de captura

Los ficheros van a `/ext/apps_data/subghz_seed_captures/`, con el nombre `<Tipo>_<Fix>_<fecha-hora>.txt`, por
ejemplo `Erreka_F00F1C9B_261008-142233.txt`. Es un fichero de texto, **no un `.sub` reproducible**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Recuperar la semilla en qUnleashed

1. Conecta el Flipper a **qUnleashed** y abre su herramienta de recuperación de semillas. Obtiene las capturas de
   `subghz_seed_captures` por sí misma: no hay que copiar ni renombrar nada.
2. Elige la captura e inicia la búsqueda (una búsqueda por fuerza bruta, razón por la cual no se ejecuta en el
   Flipper).
3. Si se encuentra la semilla, qUnleashed puede componer el `.sub` del clon terminado (serial y botón a partir de
   `Fix`, más la semilla y el contador) y ponerlo en el Flipper.
4. Si no se encuentra nada, lo más probable es que la captura tuviera un hueco: vuelve a capturar con cuidado.

Con la semilla también puedes construir mandos a mano en `Sub-GHz → Add Manually [Advanced]`: tu propio `SERIAL` +
la `SEED` para un mando nuevo, o el `SERIAL`/`BUTTON` del original + `SEED` + un `COUNTER` ligeramente superior para
un clon. Un clon entra en conflicto con el original por el contador; véase
[Códigos rodantes](/es/subghz/rolling-codes).

::: warning
Solo para mandos y receptores de tu propiedad.
:::

## Páginas relacionadas

- [Programar un mando nuevo](/es/subghz/remote-prog) · [KeeLoq](/es/subghz/keeloq) · [Add Manually](/es/subghz/add-manually)
- [Aplicación qUnleashed](/es/mobile/qunleashed-app)
