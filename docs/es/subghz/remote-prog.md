---
title: El Flipper como mando nuevo
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually]
sources: [unleashed-docs, unleashed-src]
---
# Usar el Flipper como mando Sub-GHz nuevo

Convierte el Flipper en un **mando completamente nuevo** y regístralo en el receptor de tu cancela, garaje o persiana, igual que registrarías un mando de repuesto comprado en una tienda. Esto **no** es clonar.

::: warning
Hazlo únicamente en receptores de tu propiedad o que tengas permiso para gestionar.
:::

## ¿Clon o mando nuevo? {#clone-or-new}

- **Mandos de código rodante (dinámico)**: BFT, Erreka, FAAC, Nice, CAME Atomo, Somfy, KeeLoq y el resto de esta página. Cada pulsación envía un código nuevo construido a partir de un contador, y el receptor solo acepta un contador que haya avanzado. Un clon comparte el contador del original, así que los dos pelean por él: funciona el que hayas pulsado más recientemente, y el otro necesita varias pulsaciones para ponerse al día (véase [Códigos rodantes](/es/subghz/rolling-codes)). Por eso se crea un mando **nuevo**: obtiene su propio serial y su propio contador y convive con tus mandos originales.
- **Mandos de código estático (fijo)**: CAME de 12/24 bits, Nice Flo, Princeton, Marantec, Holtek, Roger, Gate TX y los demás protocolos estáticos. No hay contador, así que **clonar está bien**: la copia es idéntica y ambos siguen funcionando en cualquier orden. Usa `Sub-GHz → Read` y guárdalo (véase [Leer señales](/es/subghz/read)). Esta página solo te hace falta si quieres un mando con su propio código independiente.

## Lee esto primero {#read-first}

**Qué hace Add Manually.** `Main Menu → Sub-GHz → Add Manually` construye un mando nuevo con un número de serie generado al azar y lo guarda como fichero. No se envía nada hasta que abres ese fichero y pulsas una tecla. Tus mandos originales no se tocan.

::: tip Unleashed: Add Manually en dos pasos
En el firmware actual de Unleashed el menú tiene dos pasos:
1. Elige el **sistema** de la lista, por ejemplo `BFT Mitto`, `KL: DoorHan` o `Somfy Telis`.
2. Elige la **banda** (frecuencia + modulación). Las bandas propias del sistema están arriba, por ejemplo `433.92 AM650` o `868.35 AM650`. Todas las demás bandas se listan debajo, para instalaciones que usen alguna poco habitual: `433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`, `868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`, `430.50 AM650`.

Después pones nombre al fichero y se guarda en `/ext/subghz/`. Las guías más antiguas escriben cosas como «BFT Mitto 433MHz» como un único elemento de menú. Hoy eso es `BFT Mitto` → `433.92 AM650`.
:::

**Si tu sistema no está en esta página, puede que el Flipper lo admita igualmente.** Recorre la lista de `Add Manually`. Si tu marca está ahí, crea un mando y sigue los pasos de programación del *manual de tu propio receptor*. La lista completa de protocolos está en [Sistemas compatibles](/es/subghz/supported-systems), y cada entrada del menú se describe en [Add Manually](/es/subghz/add-manually).

**Read y Add Manually son dos trabajos distintos.** `Read` captura y reproduce un mando que ya tienes. `Add Manually` crea un mando nuevo que se puede registrar en el receptor. Muchos protocolos solo admiten `Read`.

**Las teclas del Flipper son los botones del mando original.** Cuando un fichero de mando está abierto (`Saved → fichero → Emulate`):

| Tecla del Flipper | Qué envía |
|---|---|
| <kbd>OK</kbd> (se muestra como `Send`) | el botón principal del mando |
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | los demás botones del mando (botones personalizados) |

Qué flecha envía qué botón depende del protocolo. Un botón *oculto* o de *programación* del mando original (un orificio hundido, dos botones mantenidos a la vez, contactos que hay que puentear dentro de la carcasa) se convierte en **una sola pulsación de tecla** en el Flipper. Cada sección de más abajo indica qué tecla es, y la [tabla de referencia](#programming-hidden-button-reference) las recoge todas.

La aplicación [Sub-GHz Remote](/es/subghz/remote) envía esos mismos botones: cada ranura de un mapa tiene un ajuste `Button` (`Default`, `Up`, `Down`, `Left`, `Right`), así que un botón oculto puede ocupar una tecla para él solo.

**Mantén <kbd>OK</kbd> pulsado durante 1–3 segundos**, salvo que un paso diga lo contrario.

**La sincronización importa.** La mayoría de los receptores abren una ventana de programación de 5, 10 o 30 segundos. Lee todo el procedimiento antes de empezar.

::: danger
En muchos receptores, mantener el botón de programación **demasiado tiempo** borra todos los mandos que conoce, no solo uno. Después tendrás que volver a registrar todos tus mandos originales. Cuando un paso dice «aproximadamente 1 segundo», no lo mantengas cinco.
:::

::: info Done! / Done?
Un procedimiento que termina en **Done!** está confirmado como funcional. **Done?** significa que proviene del manual del fabricante pero nadie ha informado todavía del resultado. Debería funcionar. Si no lo hace, dilo al equipo de Unleashed en las issues de GitHub.
:::

**Add Manually [Advanced]** es la entrada de menú justo debajo de `Add Manually`. Úsala cuando necesites escribir los valores a mano en lugar de obtener un serial aleatorio. Después del sistema y la banda pide, todo en hexadecimal, `Enter SERIAL in hex`, `Enter BUTTON in hex`, `Enter COUNTER in hex` y, en los protocolos que la usan, `Enter SEED in hex`. Nice O-Code pide `IC` (y `CERT`) en su lugar. FAAC FIX, Monarch, Phantom/Hiland y DEA Mio piden `DISC.` (discriminador) en lugar de SEED.

## Encuentra tu sistema {#find-your-system}

| | | |
|---|---|---|
| [Alutech AT4N](#alutech-at4n-an-motors) | [AN-Motors AT4](#an-motors-at4) | [Aprimatic TR](#aprimatic-tr) |
| [Beninca ARC (TO.GO)](#beninca-arc-to-go) | [BFT Mitto](#bft-mitto) | [CAME Atomo](#came-atomo) |
| [Cardin S449](#cardin-s449) | [DEA Mio](#dea-mio) | [Ditec GOL4](#ditec-gol4) |
| [DoorHan](#doorhan) | [Erreka IRIS](#erreka-iris) | [FAAC RC, XT](#faac-rc-xt) |
| [FAAC SLH](#faac-slh) | [Genius (SLH)](#genius-slh) | [Genius TX4RC](#genius-tx4rc-bravo-echo) |
| [Hormann EcoStar](#hormann-ecostar) | [Jarolift](#jarolift) | [KingGates Stylo 4k](#kinggates-stylo-4k) |
| [Mhouse](#mhouse) | [Nice Flor S](#nice-flor-s) | [Nice One](#nice-one) |
| [Nice O-Code](#nice-o-code) | [Nice Smilo](#nice-smilo) | [Security+ 1.0 / 2.0](#security-1-0-2-0-chamberlain-liftmaster-craftsman) |
| [Somfy Keytis](#somfy-keytis) | [Somfy Telis](#somfy-telis) | [Sommer](#sommer) |
| [V2 Phoenix (Phox)](#v2-phoenix-phox) | | |

¿No aparece? Consulta la [tabla de referencia](#programming-hidden-button-reference). Cubre todas las demás entradas del menú `Add Manually`.

---

## Alutech AT4N (AN-Motors) {#alutech-at4n-an-motors}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Alutech AT4N → 433.92 AM650`

Esto vale para placas con pantalla y botones `F`, `CL`, `+`, `-`. Si tu placa tiene en su lugar un botón `Learn`, usa [AN-Motors AT4](#an-motors-at4).

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor, localiza el botón `F` y mantenlo unos 3 s. La pantalla muestra `Pr`.
3. Pulsa `F` unas cuantas veces más hasta que la pantalla muestre `Lr`.
4. Elige un número de mando libre con `+` / `-`. Un número que ya tiene un mando muestra un punto rojo en la esquina inferior derecha.
5. Pulsa <kbd>OK</kbd> (`Send`) en el Flipper una vez. La pantalla destella y aparece un punto rojo junto a ese número.
6. Mantén `F` en la placa unos 3 s para salir del modo de programación.
7. Done!

[Vídeo explicativo; muestra también otros tipos de placa (en ruso)](https://www.youtube.com/watch?v=XrOVVYhFXDg)

## AN-Motors AT4 {#an-motors-at4}

- **Cómo crearlo:** `Sub-GHz → Add Manually → AN-Motors AT4 → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xC`

Esto vale para placas más antiguas con un botón `Learn`. Si tu placa tiene en su lugar `F`, `CL`, `+`, `-`, usa [Alutech AT4N](#alutech-at4n-an-motors).

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor y pulsa `Learn` una vez. El LED se enciende.
3. Pulsa `Send` en el Flipper una vez. El LED de la placa se apaga.
4. Pulsa `Send` otra vez. El LED empieza a parpadear. Espera un par de segundos hasta que se apague.
5. Done!

[Vídeo explicativo (en ruso)](https://www.youtube.com/watch?v=URVMtTELcnU)

## Aprimatic TR {#aprimatic-tr}

- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Aprimatic → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xF` (en el original, los 4 botones mantenidos a la vez)

1. Abre el fichero de tu mando nuevo.
2. En un mando existente que ya funcione con el receptor, pulsa los 4 botones al mismo tiempo.
3. El receptor emite un pitido continuo.
4. Pulsa `Send` en el Flipper y mantenlo unos 2 s.
5. Espera hasta que el receptor deje de pitar.
6. Done?

## Beninca ARC (TO.GO) {#beninca-arc-to-go}

- **También se vende como:** TO.GO 2VA / 4VA (antes TO.GO 2WV / 4WV). Receptores WB, WI y receptores integrados en el cuadro de maniobra.
- **Cómo crearlo:** `Sub-GHz → Add Manually → Beninca ARC → 433.92 AM650`
- **Tecla de programación:** **<kbd>↓</kbd>** = `0x0`, el botón oculto

En un original de 2 botones, el botón oculto consiste en mantener los dos botones a la vez, algo difícil de hacer con fiabilidad. En el Flipper es una sola tecla: <kbd>↓</kbd>.

### Con un mando que funcione: receptores WB / WI

1. Colócate cerca del receptor.
2. Abre el fichero del mando que ya funciona. Pulsa <kbd>↓</kbd> y mantenlo unos 3 s. La función oculta queda activa (aquí el LED de un mando original parpadearía).
3. En menos de 5 s, pulsa `Send` en ese mismo mando para el canal que quieras compartir.
4. En menos de 5 s, abre el fichero de tu mando nuevo y pulsa `Send`. Ese botón controlará ese canal.
5. El receptor sale del modo de programación. Prueba el mando nuevo.
6. Done?

### Con un mando que funcione: receptor integrado en el cuadro de maniobra

Aquí el botón oculto hay que enviarlo desde **los dos** mandos:

1. Mando que funciona: <kbd>↓</kbd> y después `Send` en menos de 5 s.
2. Mando nuevo: <kbd>↓</kbd> y después `Send` en menos de 5 s.
3. Done?

::: info
Los mandos ARC y HCS (código rodante) no pueden compartir un mismo receptor. El primer mando que guardes decide qué tipo acepta el receptor a partir de ese momento. Cambiarlo requiere un reinicio completo del receptor.
:::

## BFT Mitto {#bft-mitto}

- **Cómo crearlo:** `Sub-GHz → Add Manually → BFT Mitto → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xF` (en el original, el orificio de la parte de atrás o los botones 1+2 mantenidos a la vez)

::: info Semilla
**Los mandos BFT Mitto más nuevos derivan su semilla del número de serie**, así que un `Sub-GHz → Read` normal los decodifica al vuelo. Aparecen como `KL: BFT` directamente.
**Los modelos más antiguos tienen una semilla única** y se leen como `KL: Unknown` hasta que la tengas. Hay dos formas de recuperarla:
- Mantén 2 botones y lee el valor de `Hop`. El mando envía su semilla en claro (véase [Hacer un clon completo](#making-a-full-clone-reads-the-seed-off-your-original)).
- [Seed Capturer](/es/subghz/seed-capturer) + qUnleashed.
:::

### Con un mando que funcione

1. Abre el fichero de tu mando nuevo.
2. Colócate a 3 m como mínimo del receptor.
3. **Mando original:** pulsa el botón oculto de la parte de atrás con un alfiler, o pulsa los botones 1 y 2 a la vez, hasta que se encienda el LED del mando.
4. **Mando original:** pulsa brevemente el botón que abre el aparato.
5. En el Flipper, mantén pulsado <kbd>→</kbd> (`0xF`, mostrado como `Btn:F`) durante 3–5 s.
6. Pulsa el botón del Flipper que quieras usar para abrir el aparato.
7. Pulsa <kbd>→</kbd> otra vez.
8. Done?

### Con acceso a la caja del receptor

1. Abre el fichero de tu mando nuevo.
2. Abre la caja de la placa del receptor.
3. [Mira primero este vídeo](https://www.youtube.com/watch?v=5QXMBKI_-Ls). Muestra la parte del procedimiento que se hace en la placa.
4. En el Flipper, mantén pulsado <kbd>→</kbd> (`0xF`) durante 3–5 s. Eso hace exactamente lo mismo que mantener los botones 1 y 2 del original en el vídeo.
5. Done?

### Hacer un clon completo (lee la semilla de tu original) {#making-a-full-clone-reads-the-seed-off-your-original}

::: danger
Esto crea una copia que **pelea con tu mando original** por el contador. Tu original puede incluso dejar de funcionar hasta que lo vuelvas a registrar. Hazlo solo si el original está roto o desgastado y el Flipper está destinado a sustituirlo.
:::

1. Abre `Sub-GHz → Read`.
2. **Solo en el mando original:** mantén todos los botones a la vez (los dos en un mando de 2 botones, los dos de la fila superior en uno de 4 botones), o pulsa el botón oculto con un alfiler.
3. Recibirás una señal. Ábrela y mira `Fix:`. Empieza por `F`, por ejemplo `F00F1C9B`. La `F` inicial es el código de botón para «botón de programación pulsado».
4. El valor `Hop:` de esa misma señal es tu semilla.
5. Apunta el valor de `Hop` y sustituye su primer dígito `F` por `0`.
6. Ahora pulsa el botón de tu mando que realmente quieras clonar y lee esa señal.
7. Apunta su `Fix:`. Su primer dígito coincide con el `Btn:` que se muestra para la señal.
8. Crea el mando con `Sub-GHz → Add Manually [Advanced] → BFT Mitto → 433.92 AM650` e introduce:
   - `SERIAL`: el `Fix` del paso 7 con su **primer** dígito sustituido por `0`
   - `BUTTON`: el primer dígito de ese `Fix`
   - `COUNTER`: `FF F9`
   - `SEED`: el valor del paso 5
9. Un contador alto como `FF F9` adelanta al contador de tu original. Eso hace que el clon funcione de inmediato, y es también lo que desincroniza el original.

**O edita directamente un fichero guardado.** Guarda la señal de tu mando original (uno más antiguo aparece como `KL: Unknown`), copia el fichero a un PC y añade estas dos líneas después de la línea `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: BFT
```

Sustituye las `X` por los dígitos de la semilla del paso 4 y vuelve a copiar el fichero. Ya tienes un clon exacto con el mismo contador.

### Sin botón oculto, o no envía la semilla

Esto se aplica solo a los mandos con semilla única. Un mando que ya se lee como `KL: BFT` no tiene nada que recuperar. Si no puedes poner el original en modo de programación, usa la aplicación [Seed Capturer](/es/subghz/seed-capturer): elige `BFT Mitto` en 433.92 MHz, pulsa un botón repetidamente y después recupera la semilla en qUnleashed.

## CAME Atomo {#came-atomo}

- **También se vende como:** TOP42R / TOP44R / TOP44RGR (806TS-0130)
- **Cómo crearlo:** `Sub-GHz → Add Manually → CAME Atomo → 433.92 AM650` (o `868.35 AM650`)

::: warning
Con CAME Atomo, mantén siempre `Send` **al menos 2 segundos**. El protocolo necesita ese tiempo para sacar el código completo.
:::

### Con un mando que funcione (o su copia en el Flipper)

1. Abre el fichero de tu mando nuevo.
2. Colócate a 3 m como mínimo del receptor.
3. **Mando original:** pulsa y mantén el botón asociado a ese receptor unos 10 s.
4. Ahora tienes unos 20 s para añadir el mando nuevo.
5. Mantén `Send` en el fichero del mando nuevo durante 3–4 s y suelta. Eso lo registra.
6. Espera 20 s y después vuelve a mantener `Send`. Debería accionar el receptor.
7. Done!

### Con acceso a la caja del receptor

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor y localiza el botón de programación del canal que necesites. Algunos receptores tienen varios canales. Un RE432M / RE862M, por ejemplo, tiene dos, cada uno con sus propios mandos y botones. Pulsa `1` o `2` en la placa para entrar en modo de programación de ese canal.
3. Mantén `Send` en el Flipper durante 3–4 s y suelta.
4. Pulsa `CLEAR` una vez para salir del modo de programación, o espera unos 20 s.
5. Done!

::: info
Los mandos CAME estáticos de 12/24 bits y los CAME TWEE no pueden abrir el modo de programación, y no se pueden registrar en una ventana abierta por un mando Atomo. Solo los mandos Atomo pueden hacerlo.
:::

[Vídeo explicativo (en ruso)](https://www.youtube.com/watch?v=XeHUwfcSS30)

## Cardin S449 {#cardin-s449}

- **También se vende como:** S449 QZ1 / QZ2 / QZ4, TXQ449100 / TXQ449200. Receptores RCQ449.
- **Leer con:** modulación `FM12K`, **no** AM650
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Cardin S449 → 433.92 FM12K`
- **Tecla de programación:** <kbd>→</kbd> = `0xD` (en el original, el botón del pequeño orificio bajo las teclas)

1. Abre el fichero de tu mando nuevo.
2. Colócate a 1–2 m del receptor.
3. Abre el fichero del mando que ya funciona. Pulsa <kbd>→</kbd> y suéltalo cuando el receptor emita un pitido corto.
4. Pulsa `Send` en ese mismo mando una vez. El receptor emite otro pitido corto.
5. Abre el fichero de tu mando nuevo y pulsa `Send`. El receptor emite dos pitidos seguidos.
6. Suelta la tecla. El receptor emite un pitido más largo.
7. Espera al menos 10 s y después prueba el mando nuevo.
8. Done?

**Si falla**, o si oyes un pitido largo antes del paso 5, espera 20 s y empieza de nuevo desde el paso 3.

## DEA Mio {#dea-mio}

- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: DEA Mio → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xF`, el botón oculto

1. Abre el fichero de tu mando nuevo.
2. `Send` actúa como uno de los botones normales. Ese es el que se registra.
3. <kbd>→</kbd> actúa como el botón oculto del mando original.
4. Sigue las instrucciones de tu fabricante para añadir un mando, usando estas dos teclas en lugar de los botones del original.

## Ditec GOL4 {#ditec-gol4}

- **También se vende como:** GOL4 / GOL4C. Receptores BIXLG4, BIXLP2, BIXLS2, BIXR2.
- **Cómo crearlo:** `Sub-GHz → Add Manually → Ditec GOL4 → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0x0`, el botón oculto

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor. Pulsa y suelta `PRG`. El LED `SIG` se enciende y se queda fijo.
3. Pulsa `Send` en el Flipper para el canal que quieras almacenar.
4. `SIG` parpadea mientras almacena. Cuando vuelva a estar fijo puedes añadir otro mando.
5. El almacenamiento termina 10 s después del último mando, o pulsa `PRG` otra vez para salir de inmediato.
6. Done?

::: info
En algunas placas hay que colocar un puente en el receptor antes de que la programación funcione en absoluto. Consulta el manual de tu receptor.
:::

## DoorHan {#doorhan}

- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: DoorHan → 433.92 AM650` (o `315.00 AM650`)

### Localizar primero tu frecuencia {#doorhan-frequency}

DoorHan usa 315.00 o 433.92 MHz. Crea un mando en una de ellas, ábrelo y pulsa `Send` mientras observas el receptor. Si has acertado, la luz del receptor se enciende mientras mantienes la tecla y se apaga al soltarla. Si no pasa nada, prueba la otra banda. También puedes leer tu mando actual con `Sub-GHz → Read`.

### Con acceso a la caja del receptor

Quita la tapa protectora y mira los botones:

- **4 botones (`Radio`, `Reverse`, `Auto`, …):** mantén `Radio` hasta que se encienda el LED y después pulsa `Send` en el Flipper 2 veces. El LED se apaga.
- **4 botones (`R`, `P`, `+`, `-`) y pantalla:** pulsa `R`, pulsa `Send` 2 veces y espera unos 10 s.
- **4 botones (`+`, `-`, `F`, `TR`) y pantalla:** pulsa `TR`, pulsa `Send` 2 veces y espera unos 10 s.
- **Cualquier otro caso:** mantén `P` unos 2 s hasta que el LED parpadee y después pulsa `Send` 2 veces. El LED se apaga.

En todos los casos, espera a que el receptor vuelva al modo normal antes de probar.

### Con un mando original en la mano

1. Abre el fichero de tu mando nuevo.
2. Colócate a 1–2 m de la placa del receptor.
3. En el mando antiguo, pulsa y mantén el segundo botón (el inferior) y después pulsa también el primero (el superior). Mantén los dos 1 s y suelta.
4. Pulsa el botón que funciona del mando antiguo (el que abre la cancela). Mantenlo 1 s y suelta.
5. Los pasos 3 y 4 deben hacerse con menos de 5 s de diferencia. No lo mantengas demasiado, pero tampoco te precipites.
6. El receptor pita. Ahora tienes 10 s: pulsa `Send` en el mando nuevo 2 veces, manteniéndolo al menos 1 s cada vez.
7. El receptor pita de nuevo. El mando nuevo está registrado.
8. Done!

### Con una copia de tu mando original en el Flipper

1. Abre el fichero de tu mando **existente (original)**.
2. Colócate a 1–2 m de la placa del receptor.
3. Pulsa <kbd>←</kbd> (`0x8`), mantén 1 s y suelta. Después pulsa <kbd>→</kbd> (`0xA`), mantén 1 s y suelta.
4. Pulsa el botón que funciona (<kbd>OK</kbd>, `Send`), mantén 1 s y suelta.
5. Los pasos 3 y 4 deben hacerse con menos de 5 s de diferencia.
6. El receptor pita. Pulsa <kbd>Back</kbd> y abre el fichero de tu mando **nuevo**. En menos de 10 s, pulsa `Send` 2 veces, manteniéndolo al menos 1 s cada vez.
7. El receptor pita de nuevo. El mando nuevo está registrado.
8. Done!

[Vídeo explicativo (en ruso)](https://www.youtube.com/watch?v=wZ5121HYv50) y [un segundo](https://www.youtube.com/watch?v=1ucrDKF3vWc)

::: tip
Si un receptor DoorHan se ha desincronizado de tu fichero, Unleashed tiene modos de contador de resincronización forzada para DoorHan. Véase [Modos de contador](/es/subghz/counter-mode).
:::

## Erreka IRIS {#erreka-iris}

- **También se vende como:** IRIS IR02 / IR04 en 433.92 MHz, IR02/868 / IR04/868 en 868.35 MHz
- **Cómo crearlo:** `Sub-GHz → Add Manually → Erreka → 433.92 AM650` para IR02 / IR04, o `868.35 AM650` para los modelos /868
- **Tecla de programación:** <kbd>→</kbd> = `0xF` (en el original, puentear los pines `1` y `5` del conector de 5 vías que queda expuesto en el costado del mando)

Erreka IRIS es un mando de código rodante: KeeLoq con una semilla secreta. Los dos métodos de registro del fabricante funcionan desde el Flipper.

### Con acceso a la caja del receptor

1. Abre el fichero de tu mando nuevo.
2. Activa el modo de programación en el receptor, normalmente con un botón de la placa.
3. Pulsa `Send` en el Flipper una vez. El receptor pita **dos veces** si el mando se ha almacenado.
4. Repite el paso 3 con los demás mandos.
5. Desactiva el modo de programación.
6. Done!

### Con un mando que funcione

El IRIS original abre la ventana de programación cuando se puentean los pines `1` y `5`. Entonces envía su semilla en claro y el receptor responde con un pitido. En el Flipper lo hace <kbd>→</kbd>.

El mando que abre la ventana debe ser uno que el receptor ya conozca: o el primer mando del Flipper que registraste con el botón del receptor, o tu mando original con su semilla recuperada (véase más abajo).

1. Abre el fichero del mando Erreka registrado.
2. Mantén pulsado <kbd>→</kbd> (`0xF`) unos 2 s. El receptor pita **una vez** y está listo para almacenar códigos.
3. En menos de 10 s, pulsa <kbd>Back</kbd> y abre el fichero de tu mando nuevo.
4. Pulsa `Send`. El receptor pita **dos veces** si el mando se ha almacenado.
5. Si pasan 10 s sin almacenar nada, el receptor sale del modo de programación. Empieza de nuevo desde el paso 2.
6. Done?

### Si el mando nuevo no se registra

Algunas instalaciones dan **la misma semilla a todos los mandos** porque el instalador los programó como conjunto. En ellas, un mando con semilla aleatoria nunca se acepta. La solución es conservar la semilla existente y cambiar solo el serial:

1. Obtén la semilla de un mando que ya funcione (véase más abajo).
2. Crea un mando con `Sub-GHz → Add Manually [Advanced] → Erreka → 433.92 AM650` (o `868.35 AM650`) e introduce:
   - `SERIAL`: `0X XX XX XX`, cualquier valor que no sea uno de tus mandos existentes. **Conserva el `0` inicial.** Ese nibble es el botón, que se pide por separado.
   - `BUTTON`: `02`
   - `COUNTER`: `00 02`
   - `SEED`: la semilla del paso 1
3. Vuelve a ejecutar cualquiera de los procedimientos de registro.

::: tip Conserva los ceros iniciales
Algunos sistemas usan solo los 3 o 4 dígitos inferiores del serial, así que sus mandos tienen el aspecto `00 00 0A BC`. En ellos, un serial aleatorio largo puede ser rechazado. Lee uno de tus mandos que funcionen, copia la forma de su serial (el mismo número de dígitos significativos, con los ceros iniciales conservados) y cambia solo los últimos dígitos. Si dos de tus mandos originales muestran la misma semilla una vez recuperada, tienes este tipo de instalación y reutilizar la semilla es lo correcto.
:::

### Obtener la semilla de tu mando IRIS original

Un mando Erreka se lee como `KL: Unknown` hasta que se conoce la semilla.

**Opción 1: puentear los pines y leerla.** Es la vía rápida. Los pines están en el exterior de la carcasa.

1. Abre `Sub-GHz → Read`. En `Config`, pon la frecuencia en 433.92 o 868.35 y la modulación en `AM650`.
2. Puentea los pines `1` y `5` del conector de 5 vías del mando original.
3. Recibirás una señal. El fabricante aparece como **Unknown**. Es lo esperado, porque el Flipper aún no conoce la semilla.
4. Abre la señal. `Fix:` empieza por `F`, el código de «botón de programación pulsado».
5. **El valor `Hop:` de esa señal es tu semilla**, en claro.
6. Escríbela en `Add Manually [Advanced]` como se ha indicado, o guarda la señal, cópiala a un PC y añade estas líneas después de `Key: ...`:

```text
Seed: 0X XX XX XX
Manufacture: Erreka
```

El fichero ya se decodifica, y puedes usarlo para abrir la ventana de programación de mandos nuevos.

**Opción 2: [Seed Capturer](/es/subghz/seed-capturer)**, cuando no puedas puentear los pines. Elige `Erreka` y tu frecuencia, pulsa un botón repetidamente y después recupera la semilla en qUnleashed.

## FAAC RC, XT {#faac-rc-xt}

- **También se vende como:** XT2 / XT4 433 RC / 868 RC, y la codificación RC más antigua
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: FAAC RC,XT → 433.92 AM650` (o `868.35 AM650`)
- **Tecla de programación:** <kbd>→</kbd> = `0xB` (en el original, los botones 1+2 mantenidos a la vez, la pulsación «maestra»)

::: warning
Estos son KeeLoq, no SLH. Lee primero tu mando. Si el Flipper lo llama `KL: FAAC_RC,XT`, estás en el lugar correcto. Si dice `FAAC SLH`, ve a [FAAC SLH](#faac-slh).
:::

1. Abre el fichero de tu mando nuevo.
2. Colócate cerca del receptor.
3. Abre el fichero del mando que ya funciona. Pulsa <kbd>→</kbd> y mantenlo unos 1–2 s (hasta el momento en que el LED del original empezaría a parpadear) y después suelta.
4. Mientras la ventana está abierta, pulsa `Send` en ese mismo mando para el botón que quieras copiar.
5. Abre el fichero de tu mando nuevo y pulsa `Send`.
6. Repite los pasos 3–5 con cada uno de los demás botones.
7. Done?

::: info
Solo un mando **maestro** puede ceder su código de sistema. En un mando original, observa el LED al pulsar un botón. Un destello corto antes de quedarse fijo significa maestro. Si se queda fijo desde el principio, es esclavo. Con un esclavo, registra el mando nuevo directamente en el receptor.
:::

## FAAC SLH {#faac-slh}

- **Cómo crearlo:** `Sub-GHz → Add Manually → FAAC SLH → 433.92 AM650` (o `868.35 AM650`)
- **Tecla de programación:** **<kbd>↑</kbd>** envía la señal de programación

### Con acceso a la caja del receptor

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor y localiza el botón de programación de la placa.
3. Mantén <kbd>↑</kbd> en el Flipper y, al mismo tiempo, pulsa y mantén el botón de programación de la placa.
4. El LED de la placa se enciende, se apaga, se enciende, se apaga y se vuelve a encender.
5. Suelta todo.
6. Pulsa `Send` en el Flipper un par de veces, manteniendo cada pulsación 1–3 s.
7. Done!

[Vídeo explicativo](https://www.youtube.com/watch?v=NfZmMy37XUs)

### Con un mando maestro, sin necesidad de abrir la caja

FAAC puede registrar mandos nuevos desde un mando maestro existente, y el Flipper puede participar. Primero lee la semilla del maestro:

1. Abre `Sub-GHz → Read`. Pon la frecuencia en 868.35 o 433.92 y la modulación en `AM650`.
2. Mantén dos botones del mando maestro original hasta que se encienda su LED.
3. Pulsa el único botón del que quieras la semilla. **La semilla es distinta para cada botón.**
4. Recibirás una señal. Ábrela y apunta la semilla.
5. Crea el mando con `Sub-GHz → Add Manually [Advanced] → FAAC SLH → 433.92 AM650` (o 868.35) e introduce:
   - `SERIAL`: `0A 0R RR RR`, sustituyendo cada `R` por cualquier dígito
   - `BUTTON`: `06`
   - `COUNTER`: `00 00 00 02`
   - `SEED`: la semilla del paso 4
6. El Flipper actúa ya como un mando nuevo. Pulsa `Send` un par de veces cerca del receptor para registrarlo.
7. Done!

### Si ninguna de las dos cosas es posible

- **La programación por radio del receptor está desactivada.** Algunos instaladores la apagan, y entonces no se registra nada.
- **Tu mando es esclavo, no maestro.** Solo un maestro puede enviar el código de programación.

En ambos casos la única vía que queda es un **clon** de un mando que el receptor ya conozca, y eso requiere la semilla. Obtenla con [Seed Capturer](/es/subghz/seed-capturer) y construye después el clon con el `SERIAL` y el `BUTTON` del **mando original**.

::: tip Dónde están SERIAL y BUTTON dentro de Fix
- **FAAC SLH y Genius:** `BUTTON` es el **último** dígito de `Fix`. `SERIAL` es el resto, con un `0` delante.
- **KeeLoq** (BFT, Erreka, DoorHan, Cardin y las demás entradas `KL:`): `BUTTON` es el **primer** dígito de `Fix`. `SERIAL` es el mismo `Fix` con su primer dígito sustituido por `0`.
:::

## Genius (SLH) {#genius-slh}

- **También se vende como:** Echo TX2 433 SLH / Echo TX4 433 SLH / KILO TX2 / TX4 / JLC / Amigo
- **Cómo crearlo:** `Sub-GHz → Add Manually → Genius → 433.92 AM650` (o `868.35 AM650`)
- **Tecla de programación:** **<kbd>↑</kbd>** envía la señal de programación

Genius SLH es el mismo paquete que FAAC SLH con su propia clave de fabricante (una línea `Manufacture: Genius` en el fichero), así que **[los procedimientos de FAAC SLH](#faac-slh) se aplican exactamente tal cual**. Si la programación está desactivada o tu mando es esclavo, captura la semilla con [Seed Capturer](/es/subghz/seed-capturer) (elige `Genius`) y construye un clon como se describe en FAAC SLH.

::: warning
No lo confundas con `KL: Genius TX4RC`. Los modelos RC son KeeLoq, no SLH, y tienen [su propia sección](#genius-tx4rc-bravo-echo). Si no estás seguro, lee primero el mando.
:::

## Genius TX4RC (Bravo / Echo) {#genius-tx4rc-bravo-echo}

- **También se vende como:** Echo TX2 433 RC / Echo TX4 433 RC / TE443H Bravo
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Genius TX4RC → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xB`

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor y pulsa `SW1` para el canal 1 o `SW2` para el canal 2. `LED1` / `LED2` se enciende y se queda fijo. Ese es el modo de aprendizaje.
3. En menos de 10 s, pulsa `Send` en el Flipper y mantenlo al menos 1 s.
4. El LED parpadea dos veces. El mando está almacenado.
5. El receptor sigue en modo de aprendizaje, así que puedes añadir más mandos repitiendo el paso 3. Pulsa `SW1` / `SW2` otra vez para salir, o saldrá por sí solo 10 s después del último mando.
6. Done?

## Hormann EcoStar {#hormann-ecostar}

- **También se vende como:** RSC2 / RSE2 / RSZ1 en 433.92 MHz. Motores EcoStar Liftronic / Portronic.
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Hor. EcoStar → 433.92 AM650`
- **Tecla de programación:** **<kbd>↓</kbd>** = `0x6` (esta está en Abajo, no en Derecha)

1. Abre el fichero de tu mando nuevo.
2. Localiza el botón de borrado y programación del motor, normalmente en su parte inferior, y mantenlo unos 1 s. El LED del motor empieza a parpadear despacio.
3. Pulsa `Send` y mantenlo unos 2 s. El LED del motor parpadea más rápido.
4. Pulsa `Send` otra vez y mantenlo unos 2 s. El LED parpadea muy rápido y después se apaga. El mando está programado.
5. Done?

::: danger
Mantener ese botón de borrado unos 5 s elimina **todos** los mandos que conoce el motor.
:::

## Jarolift {#jarolift}

- **También se vende como:** motores tubulares de radio TDEF con mandos TDRC / TDRCE
- **Cómo crearlo:** `Sub-GHz → Add Manually → Jarolift → 433.92 AM650`

Las teclas ya están asignadas a los botones del mando original:

| Tecla del Flipper | Botón de Jarolift |
|---|---|
| <kbd>OK</kbd> (`Send`) | Bajar |
| <kbd>←</kbd> | Subir |
| <kbd>↓</kbd> | Stop |
| **<kbd>↑</kbd>** | **Learn** (`0x1`) |

En el original, `Learn` consiste en mantener Subir + Bajar a la vez y después pulsar Stop. En el Flipper es una sola pulsación de tecla.

### Con acceso al cabezal del motor

1. Abre el fichero de tu mando nuevo.
2. Pulsa el botón de aprendizaje del cabezal del motor. El motor vibra brevemente y se queda en modo de aprendizaje durante 5 s.
3. Si no puedes alcanzar ese botón, desconecta el motor de la red y vuelve a conectarlo. Entra en modo de aprendizaje durante 5 s por sí solo.
4. Dentro de esos 5 s, pulsa <kbd>↑</kbd> (`Learn`).
5. El motor vibra de nuevo. El código se ha aprendido.
6. Done!

### Con un mando que funcione

1. Abre el fichero de tu mando nuevo.
2. En el mando que funciona, mantén Subir + Bajar a la vez y después pulsa Stop 8 veces. El motor vibra brevemente.
3. Dentro de esos 5 s, pulsa <kbd>↑</kbd> (`Learn`) en el Flipper.
4. El motor vibra de nuevo.
5. Done?

::: tip
Si el mando que funciona está también en tu Flipper, el paso 2 es <kbd>↑</kbd> (`Learn`) en el fichero de ese mando.
:::

## KingGates Stylo 4k {#kinggates-stylo-4k}

- **También se vende como:** Stylo 2K / Stylo 4K (10S001). Receptores Fred, Myo.
- **Cómo crearlo:** `Sub-GHz → Add Manually → KingGates Stylo4k → 433.92 AM650`

No hay un botón de programación aparte. Las cuatro teclas son los cuatro canales del original:

| Tecla del Flipper | Código de canal |
|---|---|
| <kbd>OK</kbd> (`Send`) | `0xE` |
| <kbd>↑</kbd> | `0xD` |
| <kbd>↓</kbd> | `0xB` |
| <kbd>←</kbd> | `0x7` |

1. Abre el fichero de tu mando nuevo.
2. Abre la caja del receptor. En un `Fred` de 2 canales, el color del LED indica el canal: verde es el canal 1, rojo el canal 2.
3. Pulsa el botón del receptor una vez para el canal 1 (verde) o dos veces para el canal 2 (rojo). Eso inicia el modo de aprendizaje.
4. En menos de 5 s, pulsa `Send` en el Flipper durante unos 1 s.
5. El LED se apaga y se vuelve a encender. El mando se ha aprendido.
6. El aprendizaje termina tras 5 s sin señal, o pulsando otra vez el botón del receptor.
7. Done?

## Mhouse {#mhouse}

- **También se vende como:** GTX4 / GTX4C / TX3 / TX4, y también Moovo y Nice Home ECCO
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Mhouse → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xF`, el botón adicional (oculto)

### Con acceso a la caja del receptor

1. Abre el fichero de tu mando nuevo.
2. Pulsa y mantén `P1` en el receptor hasta que el LED `P1` se quede fijo, y después suelta.
3. Pulsa `Send` y mantenlo hasta que el LED `P1` parpadee 3 veces.
4. Suelta. Eso registra todos los botones del mando a la vez (el «modo 1» de Nice).
5. Espera 10 s antes de probar.
6. Done?

### Con un mando que funcione

Mhouse es la misma familia de receptores Nice que [Nice Smilo](#nice-smilo):

1. Colócate cerca del receptor.
2. Abre el fichero de tu mando nuevo. Pulsa y mantén `Send` al menos 5 s y después suelta.
3. En el mando que funciona, pulsa y suelta lentamente su botón 3 veces.
4. Abre de nuevo el fichero del mando nuevo, pulsa `Send` 1 s y suelta.
5. Espera 10 s antes de probar.
6. Done?

## Nice Flor S {#nice-flor-s}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Nice FloR-S → 433.92 AM650`

### Con un mando que funcione

No necesitas la caja del receptor, pero **el primer mando siempre hay que registrarlo con el botón del receptor**. Más abajo, `OLD` es el mando autorizado y `NEW` es el Flipper. Colócate a menos de 3 m del receptor.

1. Abre el fichero de tu mando nuevo. Pulsa y mantén `Send` al menos 5 s (7 s en un receptor OXIBD) y después suelta.
2. En `OLD`, pulsa su botón 3 veces lentamente.
3. Pulsa `Send` en el Flipper lentamente y después suelta.
4. Espera 10 s y después pulsa `Send` para probar.
5. Done?

### Con acceso a la caja del receptor

Regístralo tal como describa el manual de tu mando original. Para un receptor NICE FLOX2R típico:

1. Abre el fichero de tu mando nuevo.
2. Pulsa el botón de aprendizaje del receptor durante 1–2 s. El LED se enciende durante 5 s. Haz el paso siguiente dentro de esos 5 s.
3. Pulsa `Send` hasta que el LED del receptor se apague.
4. Suelta y espera 2 s.
5. Pulsa `Send` otra vez. El LED parpadea 3 veces y el mando queda registrado. Si no, empieza de nuevo desde el paso 2.
6. Espera 5 s y después pulsa `Send` para probar.
7. Done!

::: tip
Las variantes de contador de Nice Flor-S para receptores concretos (floxi2r, ox2) están disponibles como [modos de contador](/es/subghz/counter-mode).
:::

## Nice One {#nice-one}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Nice One → 433.92 AM650`

Nice One es la familia Nice FloR-S con un cifrado distinto, y el lado del receptor es idéntico. **[Los dos procedimientos de Nice Flor S](#nice-flor-s) se aplican exactamente tal cual.** Si tu mando se lee como FloR-S pero el contador parece erróneo, puede que en realidad sea Nice O-Code.

## Nice O-Code {#nice-o-code}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Nice O-Code → 433.92 AM650` (o `Nice O-Code One` para el cifrado de Nice One)
- **Cómo crearlo para un sistema ya instalado:** `Sub-GHz → Add Manually [Advanced] → Nice O-Code → 433.92 AM650`, que pide `SERIAL`, `BUTTON`, `COUNTER` y el código de instalador (`Enter IC in hex`)
- **Cómo crearlo con certificado:** `Sub-GHz → Add Manually → Nice O-Code+Crt → 433.92 AM650`, que pide siempre serial, botón, contador, código de instalador **y** el certificado del receptor (`Enter CERT in hex`)

O-Code es Nice FloR-S cifrado con un **código de instalador (IC)** de 16 bits compartido por todos los mandos de una misma instalación. El lado del receptor es igual que en FloR-S, así que [los dos procedimientos de Nice Flor S](#nice-flor-s) se aplican, pero un mando solo llega a un receptor configurado con el mismo código de instalador.

- **Para un sistema propio**, el `Nice O-Code` normal se inventa un código de instalador junto con el serial. Un receptor de fábrica no lo aceptará con el botón, así que registra primero un mando [Nice One](#nice-one) normal.
- **Para un sistema ya instalado**, recupera el código de instalador de un mando que funcione con la [aplicación Nice O-Code](/es/subghz/nice-o-code) (`Apps → Sub-GHz → Nice O-Code`). Pulsa el botón del mando 4 veces o más (sin mantenerlo). En la pantalla de resultados, <kbd>→</kbd> (`New`) escribe un mando nuevo con el mismo código de instalador y botón pero con su propio serial y contador. Ese es el que hay que registrar. `Save` escribe un clon sin más, para pruebas.

::: info Probado en un OXIBD recién salido de fábrica
En el modo I el receptor **ignora por completo los paquetes O-Code**, cualquiera que sea el código de instalador que lleven, mientras que un mando `Nice One` normal se memoriza al instante. Solo una O-Box escribe el código de instalador en el receptor. En un receptor virgen usa las entradas normales de Nice Flor S / Nice One.
:::

::: tip COUNTER
**No** dejes `COUNTER` cerca de cero. El receptor rechaza un contador por detrás del que almacenó, y también uno que quede inverosímilmente lejos por detrás de los mandos que conoce, incluso con un serial nuevo. Fíjalo algo por debajo del contador de tu mando en uso (el `New` de la aplicación lo hace por ti). Si ya has enviado paquetes desde ese serial, usa un valor algo por encima del más alto que enviaste.
:::

**Alta mediante certificado.** Un mando que lleve el certificado del receptor envía paquetes de 112 bits durante sus **veinte** primeros usos, y el receptor lo da de alta por sí mismo. Abre el fichero dentro del alcance de la cancela y pulsa la tecla aproximadamente una vez por segundo, **de diez a quince veces de una sentada**. La cancela se abre en torno a la décima pulsación y, a partir de ahí, el mando queda registrado definitivamente. Si pasan los veinte usos sin que la cancela se abra, borra el fichero y crea uno nuevo. Los certificados, las cinco vías de registro de Nice, los códigos del LED del receptor y la ventana del contador se tratan en detalle en la página de [Nice O-Code](/es/subghz/nice-o-code).

## Nice Smilo {#nice-smilo}

- **También se vende como:** SM2 / SM4. Receptores SMXI, SMXIS y OXI configurados con codificación Smilo.
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Nice Smilo → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0xB`, el botón adicional (oculto)

Los receptores Nice almacenan un mando en uno de dos modos. El **modo I** asigna a cada botón del mando la salida correspondiente del receptor. El **modo II** te permite elegir qué salida controla un único botón.

### Con acceso a la caja del receptor: modo I

1. Abre el fichero de tu mando nuevo.
2. Pulsa y mantén el botón del receptor al menos 3 s.
3. Suéltalo cuando el LED se encienda.
4. En menos de 10 s, pulsa `Send` y mantenlo al menos 2 s.
5. El LED del receptor parpadea 3 veces. El mando está almacenado.
6. Para añadir más, repite el paso 4 dentro de otros 10 s.
7. Done!

### Con acceso a la caja del receptor: modo II

1. Abre el fichero de tu mando nuevo.
2. Pulsa el botón del receptor tantas veces como el número de la salida (dos veces para la salida 2).
3. Comprueba que el LED parpadee el mismo número de veces.
4. En menos de 10 s, pulsa la tecla del Flipper que quieras para esa salida y mantenla al menos 2 s.
5. El LED parpadea 3 veces. El mando está almacenado.
6. Done?

### Con un mando que funcione

El primer mando siempre hay que registrarlo con el botón del receptor. El mando nuevo **hereda el modo** del antiguo, así que con el modo II hay que pulsar los botones correspondientes en los dos.

1. Colócate cerca del receptor.
2. Abre el fichero de tu mando nuevo. Pulsa y mantén `Send` al menos 5 s y después suelta.
3. En el mando que funciona, pulsa y suelta lentamente su botón 3 veces.
4. Abre de nuevo el fichero nuevo y pulsa y suelta lentamente `Send` una vez.
5. Done?

::: info
Estos receptores no pueden borrar un mando concreto, solo todos a la vez.
:::

## Security+ 1.0 / 2.0 (Chamberlain, LiftMaster, Craftsman) {#security-1-0-2-0-chamberlain-liftmaster-craftsman}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Security+2.0` o `Security+1.0`, y después la banda. La predeterminada es `433.92 AM650`. Security+ 1.0 ofrece además `315.00 AM650` y `390.00 AM650`. Security+ 2.0 ofrece `310.00`, `315.00` y `390.00 AM650`.

**¿Cuál tienes?** Fíjate en el color del botón `Learn` del motor:

| Botón Learn | Crea esto |
|---|---|
| Amarillo | `Security+2.0` |
| Morado | `Security+1.0` → `315.00 AM650` |
| Verde | `Security+1.0` → `390.00 AM650` |
| Rojo / naranja | Billion Code, no Security+ |
| Gris / blanco | mando de microinterruptores, no Security+ |

1. Abre el fichero de tu mando nuevo.
2. Localiza `Learn` en el motor: normalmente en la parte de atrás o en el panel lateral, a veces detrás de la lente de la luz.
3. Púlsalo y suéltalo una vez. El LED de aprendizaje se queda fijo durante 30 s.
4. Dentro de esos 30 s, pulsa y mantén `Send` en el Flipper.
5. Suelta cuando las luces del motor destellen o oigas dos clics. El mando está programado.
6. Pulsa `Send` otra vez para comprobar que la puerta se mueve.
7. Done?

::: tip
Si el botón del motor no colabora, algunos sistemas permiten programar desde la consola de pared. Para los paquetes de teclado de Security+ 2.0, véase [Security+ PIN](/es/subghz/secplus-pin).
:::

## Somfy Keytis {#somfy-keytis}

- **También se vende como:** Keytis NS 2 RTS / KeyGo 4 RTS
- **Cómo crearlo:** `Sub-GHz → Add Manually → Somfy Keytis → 433.42 AM650` (son **433.42 MHz**, no 433.92)
- **Tecla de programación:** **<kbd>↑</kbd>** = `0x3`, `Prog` (`Send` es `Key_1`)

Un Keytis original no tiene tecla `Prog` en la parte frontal. Hay que puentear con un destornillador los dos contactos `PROG` de la parte de atrás de la placa. El Flipper solo necesita <kbd>↑</kbd>.

### Con acceso al receptor

1. Abre el fichero de tu mando nuevo.
2. Pulsa y mantén `PROG` en el receptor unos 3 s, hasta que parpadee.
3. Pulsa <kbd>↑</kbd> (`Prog`) en el Flipper.
4. La persiana o la cancela se mueve brevemente arriba y abajo. El mando está registrado.
5. Done?

### Con un mando que funcione

1. Abre el fichero de tu mando nuevo.
2. Pon el mando registrado en modo de programación hasta que la persiana o la cancela se mueva brevemente. En un Keytis original, puentea los contactos `PROG`. En el Flipper, pulsa <kbd>↑</kbd> en el fichero de ese mando.
3. Abre el fichero de tu mando nuevo y pulsa <kbd>↑</kbd> (`Prog`) hasta que la persiana o la cancela se vuelva a mover brevemente.
4. Done?

::: danger
En muchos receptores Somfy, mantener el botón de programación más de unos 7 s borra todos los mandos y sensores que conoce.
:::

::: info
Keytis usa el protocolo de radio `NS`, más reciente. Un receptor RTS antiguo no NS no lo aceptará hasta que se cambie el protocolo del mando. Consulta la documentación de Somfy para tu receptor.
:::

## Somfy Telis {#somfy-telis}

- **Cómo crearlo:** `Sub-GHz → Add Manually → Somfy Telis → 433.42 AM650` (son **433.42 MHz**, no 433.92)
- **Tecla de programación:** **<kbd>←</kbd>** = `0x8`, `Prog`

1. Abre el fichero de tu mando nuevo.
2. Mantén pulsado `Prog` en un mando ya registrado en el aparato, hasta que las persianas se muevan brevemente arriba y abajo.
3. Pulsa y mantén <kbd>←</kbd> (`Prog`) en el Flipper hasta que las persianas se vuelvan a mover brevemente arriba y abajo.
4. Done?

## Sommer {#sommer}

- **También se vende como:** TX03-868-4 / TX03-868-2 (SOMloq). Motores Pearl, Duo, Sprint, Marathon.
- **Leer con:** modulación `FM12K` o `FM476`, la que decodifique tu mando
- **Cómo crearlo:** `Sub-GHz → Add Manually → KL: Sommer`, y después elige la banda que coincida con cómo se leyó tu mando: `434.42 FM12K` (por defecto), `868.80 FM12K`, `434.42 FM476` o `868.80 FM476`
- **Tecla de programación:** <kbd>→</kbd> = `0x6`

::: tip Unleashed
Las guías más antiguas listan cuatro entradas Sommer separadas (`fm2` y la normal). El firmware actual tiene una sola fila `KL: Sommer`, y el selector de banda elige tanto la frecuencia como la variante de modulación.
:::

### Con acceso al receptor

1. Abre el fichero de tu mando nuevo.
2. Localiza el botón `learn` / `code` del receptor. En un Duo está bajo la tapa de la luz, en un Sprint detrás de la tapa de la caja de maniobra, y en un Marathon bajo una tapa de plástico transparente junto al botón de código.
3. Púlsalo brevemente. El LED del receptor se enciende.
4. Pulsa y mantén `Send`. Cuando el LED del receptor empiece a parpadear rápido, suelta.
5. El LED del receptor se apaga. El mando está programado.
6. Done?

### En un motor de cancela corredera

Pulsa en su lugar el botón `Radio` de la unidad de control. Un LED rojo confirma el modo de programación. Púlsalo otra vez para elegir el canal y después mantén `Send` hasta que el LED del canal destelle y se apague. El receptor sale del modo de programación por sí solo tras unos 30 s sin señal.

## V2 Phoenix (Phox) {#v2-phoenix-phox}

- **También se vende como:** Phoenix 2/4, Phox 2/4, Handy 2/4, TXC2-4, TRC2-4, TSC2-4. Receptores RXP, MR2.
- **Cómo crearlo:** `Sub-GHz → Add Manually → V2 Phoenix → 433.92 AM650`
- **Tecla de programación:** <kbd>→</kbd> = `0x3` (en el original, los botones 1+2 o 1+3 mantenidos a la vez)

::: warning
Esta asignación **todavía no está confirmada**. Si no funciona, registra con el botón del receptor e informa en las issues de Unleashed.
:::

1. Abre el fichero de tu mando nuevo.
2. Abre el fichero del mando registrado. Pulsa <kbd>→</kbd> y mantenlo al menos 5 s, y después suelta.
3. En menos de 5 s, abre el fichero del mando nuevo y pulsa `Send`.
4. Suelta. Repítelo con los demás botones.
5. Done?

El mando que abre la ventana debe estar ya almacenado en el receptor, y todo lo que se almacene así hereda su lógica. Si solo tenía el botón 1 almacenado, los mandos nuevos solo se podrán almacenar en el botón 1. Algunos receptores V2 se pueden poner en modo `Static`, que ignora la parte rodante de la clave.

---

## Recuperar una semilla

**FAAC SLH**, **Genius**, **Erreka** y **BFT Mitto** construyen su código rodante a partir de una **semilla** secreta. Sin ella el Flipper no puede decodificar esos mandos (se leen como `KL: Unknown` o no se leen en absoluto) ni construir un mando que el receptor acepte. Necesitas la semilla cuando:

- la programación por radio del receptor está desactivada, así que solo funciona un clon;
- tu mando FAAC/Genius es esclavo y no puede enviar el código de programación;
- no puedes acceder al receptor;
- una instalación Erreka comparte una misma semilla entre todos los mandos;
- un BFT Mitto antiguo no entra en modo de programación.

La aplicación [Seed Capturer](/es/subghz/seed-capturer) (`Apps → Sub-GHz → Seed Capturer`) recopila parejas `Fix` + `Hop` consecutivas de un botón. Nunca transmite y las guarda en `/ext/apps_data/subghz_seed_captures/`. La aplicación acompañante qUnleashed (véase [aplicación qUnleashed](/es/mobile/qunleashed-app)) aplica después fuerza bruta a la semilla y puede escribir por ti el fichero del clon terminado.

Una vez tengas la semilla:

- **Mando nuevo** (el receptor debe aceptar mandos nuevos): `Add Manually [Advanced]` → tu sistema → banda, tu propio `SERIAL` y la `SEED` recuperada.
- **Clon** (funciona sin programación, porque el receptor ya conoce ese serial): deja que qUnleashed lo guarde, o introduce el `SERIAL` y el `BUTTON` **del original**, la `SEED` y un `COUNTER` algo por encima del valor actual del original.

::: danger
Un clon comparte el contador con el original y los dos pelearán por él. Clona solo cuando sea imposible crear un mando nuevo.
:::

## Referencia de botones de programación y ocultos {#programming-hidden-button-reference}

Busca el paso de «poner el receptor en modo de programación» en el manual de tu fabricante. Allí donde te diga que pulses algo en el mando original, pulsa en su lugar la tecla de esta tabla.

::: info
Estas son las teclas de un mando tal como lo crea `Add Manually`. Si cambias el código de botón a mano, las teclas se mueven con él.
:::

| Sistema (entrada de Add Manually) | Código | Tecla en el Flipper | En el mando original |
|---|---|---|---|
| `FAAC SLH`, `Genius` | – | **<kbd>↑</kbd>** | la señal de programación |
| `BFT Mitto` | `0xF` | <kbd>→</kbd> | orificio de la parte de atrás, o botones 1+2 mantenidos |
| `Erreka` | `0xF` | <kbd>→</kbd> | pines 1 y 5 del conector de 5 vías puenteados |
| `KL: DEA Mio` | `0xF` | <kbd>→</kbd> | botón oculto |
| `KL: Aprimatic` | `0xF` | <kbd>→</kbd> | los 4 botones mantenidos a la vez |
| `KL: Mhouse` | `0xF` | <kbd>→</kbd> | botón adicional / oculto |
| `KL: Nice Smilo` | `0xB` | <kbd>→</kbd> | botón adicional / oculto |
| `KL: FAAC RC,XT` | `0xB` | <kbd>→</kbd> | botones 1+2 mantenidos (pulsación maestra) |
| `KL: Genius TX4RC` | `0xB` | <kbd>→</kbd> | botón de modo de programación |
| `KL: Monarch` | `0xB` | *ninguna flecha lo envía* | fija el código de botón a mano en signal settings |
| `KL: FAAC FIX` | `0x9` | <kbd>→</kbd> | botón adicional / oculto *(sin confirmar)* |
| `KL: Novoferm` | `0x9` | <kbd>→</kbd> | botón adicional / oculto |
| `KL: Stilmatic` | `0x9` | <kbd>→</kbd> | botón adicional / oculto |
| `KL: Sommer` (todas las bandas) | `0x6` | <kbd>→</kbd> | botón adicional / oculto |
| `KL: Hor. EcoStar` | `0x6` | **<kbd>↓</kbd>** | botón adicional / oculto |
| `KL: Cardin S449` | `0xD` | <kbd>→</kbd> | botón del orificio bajo las teclas |
| `AN-Motors AT4` | `0xC` | <kbd>→</kbd> | botón adicional / oculto |
| `Beninca ARC` | `0x0` | **<kbd>↓</kbd>** | botón oculto (botones 1+2 mantenidos) |
| `Ditec GOL4` | `0x0` | <kbd>→</kbd> | botón oculto |
| `Jarolift` | `0x1` | **<kbd>↑</kbd>** | `Learn`: Subir+Bajar mantenidos y después Stop |
| `Somfy Telis` | `0x8` | **<kbd>←</kbd>** | botón `Prog` |
| `Somfy Keytis` | `0x3` | **<kbd>↑</kbd>** | contactos `Prog` de la parte de atrás de la placa |
| `V2 Phoenix` | `0x3` | <kbd>→</kbd> | botones 1+2 o 1+3 mantenidos *(sin confirmar)* |
| `Nice FloR-S` / `Nice One` / `Nice O-Code` | `0x3` | <kbd>→</kbd> | botón 3 *(sin confirmar como botón de programación)* |

### Todo lo demás del menú

Cualquier entrada que no esté en esta tabla y no tenga sección más arriba se registra de la forma habitual: **pon el receptor en modo de aprendizaje con su propio botón y después pulsa `Send` en el Flipper dentro de la ventana de tiempo que indique tu fabricante.**

Eso cubre la mayoría de los sistemas KeeLoq (Comunello, Allmatic, Motorline, Centurion, Phantom/Hiland, KEY, Jolly Motors, IronLogic, DTM Neo, Gibidi, GSN, HomeGate, Elmes, Normstahl, JCM Tech, Pujol, ET Blue, ATA PTX4, Seav, Wisniowski, Fadini, Mc Garcia, Clemsa Mutancode, Doormatic, Elvox, Verex, CAME Space, Beninca KeeLoq, Superrollo, HCS101) y todos los protocolos estáticos, como CAME, Nice Flo, Marantec, Princeton, Prastel, Roger, Telcoma EDGE, Gate TX, BETT, Nord ICE, Revers RB2, Linear, Nero y [ZKTeco](/es/subghz/zkteco-cmp200).

## Cuando no funciona

- **No pasa absolutamente nada.** Comprueba primero la frecuencia. Es el error más habitual. Lee tu mando original con `Sub-GHz → Read` y compara. Algunas marcas venden el mismo mando en dos frecuencias: DoorHan en 315 y 433.92, FAAC y Genius en 433.92 y 868.35. Usa el [Frequency Analyzer](/es/subghz/frequency-analyzer) si no estás seguro.
- **Modulación incorrecta.** La mayoría de los sistemas de esta página usan `AM650`, pero Cardin S449 usa `FM12K` y Sommer `FM12K` o `FM476`. Ajústala en `Sub-GHz → Read → Config` y elige la banda correspondiente en Add Manually.
- **El receptor reacciona pero nunca almacena el mando.** Lo más probable es que se te escape la ventana de tiempo. Vuelve a leer los pasos y ten el fichero del mando abierto antes de tocar el botón del receptor.
- **Almacenó el mando pero no abre nada.** Mantén `Send` más tiempo. Varios protocolos necesitan 1–3 s para sacar un código completo, y CAME Atomo necesita al menos 2 s cada vez.
- **Funcionó una vez y después dejó de hacerlo.** En un sistema de código rodante esto es un problema de contador: has clonado un mando en lugar de crear uno nuevo. Pulsa `Send` unas cuantas veces seguidas, porque el receptor acepta un contador adelantado dentro de una ventana. Para que ambos mandos sigan funcionando, crea en su lugar un mando nuevo (véase [Códigos rodantes](/es/subghz/rolling-codes)). Un mando estático no tiene contador, así que si deja de funcionar, comprueba la pila, la frecuencia o el receptor.
- **Todos tus mandos han dejado de funcionar.** Lo más probable es que hayas mantenido un botón de programación el tiempo suficiente para activar la función de borrado del receptor. Vuelve a registrar todos los mandos, originales incluidos.

## Fuentes y manuales

- [FAAC SLH: vídeo explicativo](https://www.youtube.com/watch?v=NfZmMy37XUs)
- [Análisis del protocolo Somfy RTS](https://pushstack.wordpress.com/somfy-rts-protocol/)
- [Somfy Universal Receiver RTS: instrucciones de instalación](https://service.somfy.com/downloads/nam_v5/universalreceiver_rts.pdf)
- [Registro del Somfy Keytis NS 2 RTS (foro de Somfy)](https://forum.somfy.fr/questions/1792206-programmer-telecommande-keitis-ns2-rts-recepteur-somfy-axorn-50)
- [Manual del BFT Mitto](https://www.retroremotes.com.au/wp-content/uploads/2017/03/BFT-MITTO-2-4-19-6-17.pdf)
- [Programación del receptor NICE FLOX2R](https://apollogateopeners.com/store/pdf/apollo-flor-s-receiver-programming-guide.pdf)
- [Programación de Nice Flor S](https://motepro.com.au/Instructions/Nice.pdf)
- [Manual de los Nice Smilo SM2/SM4 y del receptor SMXI](https://www.habitat-automatisme.com/blog/wp-content/uploads/2010/02/SMILO.pdf)
- Nice O-Code: manuales de instalador de [niceforyou.com](https://www.niceforyou.com/) (OXI/A `IS0242A00MM`, OXI/OXIT/OX2/OX4T `IST236R02`, OXIBD `idv0603a01it`, O-Box `IST225`, receptor FLOR `IS0063A00MM`, transmisores Era One `IS0102A01MM`)
- [Programación de los Mhouse GTX4 / TX4 / Nice Home ECCO5](https://www.allotelecommande.com/wp-content/uploads/2019/06/Notice-de-programmation-MHOUSE-GTX4-%E2%80%93-TX4-%E2%80%93-MT4-%E2%80%93-NICE-HOME-ECCO5-.pdf)
- Erreka IRIS: `Guia rapida mando IRIS` (MSR-044/03), de [erreka.com](https://www.erreka.com/)
- [Manual del motor Jarolift TDEF](https://www.jarolift.de/wp-content/themes/jarolift/manuals/motoren/en/Jarolift_TDEF_EN.pdf)
- [Programación de los transmisores Beninca TO.GO](https://www.allotelecommande.com/wp-content/uploads/2023/05/BENINCA-TO.GO_.pdf)
- [Manual de los receptores Ditec BIX L / BIX A](https://www.allotelecommande.com/wp-content/uploads/2023/03/DITEC-BIX-L-DITEC-BIX-A.pdf)
- [Instrucciones de programación del Cardin S449 QZ2](https://www.allotelecommande.com/wp-content/uploads/2024/02/CARDIN-S449-QZ2.pdf)
- [Manual del receptor Cardin RCQ449](https://www.allotelecommande.com/wp-content/uploads/2023/02/Recepteur-Radio-CARDIN-RCQ449-ND00.pdf)
- [Manual del emisor de mano Hormann RSC2](https://www.hoermann.de/fileadmin/_country/dok/Handsender_RSC2_%28H%C3%B6rmann%29_TR20L001-A.pdf)
- [Sommer: programar un emisor en un motor de cancela corredera](https://www.sommer.eu/en/magazine/programming-a-handheld-transmitter-to-a-sommer-sliding-gate-operator.html)
- [Manual del receptor V2 RXP4: aprendizaje por radio](https://manualslib.mx/manual/401640/V2-Rxp4.html?page=9)
- [Programación del receptor KingGates Fred](https://tecnoparking.com/tienda/gb/receptors/2096-outer-receiver-kinggates-fred-2-channels-rollingcode-is-433-mhz.html)

## Páginas relacionadas

- [Add Manually](/es/subghz/add-manually)
- [Códigos rodantes](/es/subghz/rolling-codes)
- [KeeLoq](/es/subghz/keeloq)
- [Modos de contador](/es/subghz/counter-mode)
- [Sistemas compatibles](/es/subghz/supported-systems)
- [Seed Capturer](/es/subghz/seed-capturer) · [Nice O-Code](/es/subghz/nice-o-code)
