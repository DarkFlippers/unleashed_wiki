---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** crea un mando virtual completamente nuevo y lo guarda como fichero `.sub`. No necesitas un mando
original para ello: el Flipper genera un número de serie aleatorio (y un contador, una semilla, etc., allí donde el
protocolo los necesite). El mando nuevo se puede después **registrar en un receptor** como mando adicional, igual
que registrarías un mando de repuesto comprado en una tienda.

**Add Manually [Advanced]** hace lo mismo, pero te pide que escribas cada valor en hexadecimal en lugar de
generarlo.

::: tip Unleashed
El firmware original solo tiene un puñado de protocolos estáticos en Add Manually. Unleashed lista **más de 100
sistemas**, incluidos los de código rodante (fabricantes KeeLoq, FAAC SLH, BFT Mitto, Nice FloR-S / O-Code,
CAME Atomo, Somfy, Security+ 2.0, …), te permite elegir cualquiera de las 15 bandas de frecuencia/modulación para
cada uno, y añade la entrada **[Advanced]**.
:::

## Cuándo usarlo

| Situación | Qué usar |
|---|---|
| Tienes un mando **estático** (código fijo) y solo quieres una copia | [Read](/es/subghz/read) y guardarlo: no hace falta Add Manually |
| Tienes un mando de **código rodante** y quieres que el Flipper funcione *junto* a él | **Add Manually** → registra el mando nuevo en el receptor ([cómo](/es/subghz/remote-prog)) |
| Necesitas un mando con valores conocidos (semilla recuperada, código de instalador, un serial concreto) | **Add Manually [Advanced]** |
| Has perdido el mando estático original pero conoces sus microinterruptores o su código | **Add Manually [Advanced]** escribiendo la clave |

¿Por qué no clonar simplemente un mando de código rodante? Véase [Códigos rodantes](/es/subghz/rolling-codes): el
clon y el original entran en conflicto por el contador.

## Crear un mando

1. `Main Menu → Sub-GHz → Add Manually`.
2. Recorre la lista y elige el sistema, por ejemplo `BFT Mitto` o `KL: DoorHan`. Las entradas que empiezan por
   `KL:` son fabricantes KeeLoq.

   ![Add Manually: lista alfabética de sistemas con KL: Allmatic seleccionado](/screens/subghz/add_manually.png)

3. Se abre un **selector de banda**, con el nombre del sistema como encabezado. Las bandas se etiquetan como
   `frecuencia modulación`, por ejemplo `433.92 AM650`. La banda por defecto del sistema aparece primero, después
   las demás bandas que se sabe que usa ese sistema y, por último, todas las bandas restantes (para instalaciones
   en una frecuencia poco habitual). Pulsa <kbd>OK</kbd> sobre la banda que necesites.
4. Escribe un nombre de fichero (se propone uno) y confirma.
5. El mando se guarda en `/ext/subghz/` y aparece en `Sub-GHz → Saved`.

   ![Menú de una señal guardada: Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Ábrelo: `Sub-GHz → Saved → <tu fichero> → Emulate`. Mantén <kbd>OK</kbd> (`Send`) para transmitir; en los
   protocolos con [botones personalizados](/es/subghz/rolling-codes#custom-buttons) las flechas envían los demás
   botones.

   ![Pantalla de transmisión de una señal guardada con R: Int y el botón Send](/screens/subghz/emulate.png)


No se transmite nada hasta que abres el fichero y pulsas una tecla.

::: warning Nombres obsoletos
Las guías más antiguas (incluidas versiones antiguas de `SubGHzRemoteProg.md`) nombran entradas como
`BFT Mitto 433MHz` o `KL: DoorHan 315MHz`. El firmware actual divide esto en dos pasos: sistema (`BFT Mitto`) →
banda (`433.92 AM650`).
:::

### Las 15 bandas

Todas ellas se ofrecen para cada sistema:

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → sistema → banda, y después una serie de pantallas de entrada en
hexadecimal. Qué pantallas aparecen depende de la familia de protocolos:

| Familia | Pantallas (en orden) |
|---|---|
| Protocolos estáticos (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex`; los protocolos que almacenan una temporización piden además `Enter TE in us` (y `Enter GT in TE`) |
| KeeLoq (entradas `KL:`, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq con semilla (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (discriminador del hop, almacenado en el campo `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 bits) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (código de instalador) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (se pide incluso desde el Add Manually normal) |
| Security+1.0 | nada que introducir, se genera directamente |

Los valores son hexadecimales en big-endian. `BUTTON` y `SERIAL` forman juntos el `Fix` que ves después de un
[Read](/es/subghz/read): en KeeLoq el botón es el **primer** dígito hexadecimal de `Fix` (el serial = `Fix` con ese
dígito sustituido por `0`), y en FAAC SLH / Genius es el **último** dígito.

::: tip Entrada de bytes
La entrada de bytes de Unleashed tiene un minieditor de nibbles: pulsa <kbd>↑</kbd> repetidamente hasta que
aparezca.
:::

## Todas las entradas de la lista

El orden y las etiquetas son exactamente los del menú del firmware. «Por defecto» es la banda que aparece primera;
«También» son las bandas alternativas del sistema listadas justo después.

| Entrada de menú | Por defecto | También | Tipo |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (clave Beninca) |
| `Alutech AT4N` | 433.92 AM650 | | Dinámico (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dinámico (contador simple) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dinámico (AES-128) |
| `BETT` | 433.92 AM650 | | Estático |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + semilla |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Estático |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Estático |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dinámico |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Estático (pseudodinámico) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + discriminador |
| `Ditec GOL4` | 433.92 AM650 | | Dinámico |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + semilla |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + discriminador |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + semilla |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Estático (12 microinterruptores) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Estático (alarma de bicicleta) |
| `Gate TX` | 433.92 AM650 | | Estático |
| `Genius` | 433.92 AM650 | 868.35 AM650 | Paquete FAAC SLH, clave Genius |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | Similar a KeeLoq |
| `Hollarm` | 433.92 AM650 | | Estático (alarma de bicicleta) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dinámico (basado en KeeLoq) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dinámico (basado en KeeLoq) |
| `Linear` | **300.00 AM650** | | Estático (10 bits) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Estático |
| `Marantec24` | **868.35 AM650** | | Estático |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + discriminador |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Estático |
| `Nice Flo 24bit` | 433.92 AM650 | | Estático |
| `Nice FloR-S` | 433.92 AM650 | | Dinámico |
| `Nice O-Code` | 433.92 AM650 | | Dinámico, código de instalador |
| `Nice O-Code One` | 433.92 AM650 | | Dinámico, código de instalador (paquete Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dinámico, código de instalador + certificado |
| `Nice One` | 433.92 AM650 | | Dinámico |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Estático |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + discriminador |
| `Prastel` | 433.92 AM650 | | Dinámico (42 bits) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Estático (24 bits) |
| `Proteco` | 433.92 AM650 | | Estático |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Estático |
| `Roger` | 433.92 AM650 | | Estático |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dinámico |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dinámico |
| `Somfy Keytis` | **433.42 AM650** | | Dinámico |
| `Somfy Telis` | **433.42 AM650** | | Dinámico (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Estático |
| `V2 Phoenix` | 433.92 AM650 | | Dinámico |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Estático (Princeton; véase [ZKTeco CMP200](/es/subghz/zkteco-cmp200)) |

En `KL: Sommer`, las bandas FM476 generan el mando con la otra variante de modulación de Sommer, así que una sola
fila del menú cubre los dos tipos de mando Sommer.

## Programar el mando nuevo en un receptor

Un mando de código rodante recién creado es desconocido para el receptor. Regístralo como cualquier mando de
repuesto: con el botón de aprendizaje del receptor o desde un mando que ya funcione. Los botones ocultos o de
programación del mando original se envían con una sola tecla de flecha en el Flipper. Procedimientos paso a paso
por fabricante: **[Usar el Flipper como mando nuevo](/es/subghz/remote-prog)**.

## Resolución de problemas

- **`Function requires an SD card with fresh databases.`**: las bases de datos de claves de fabricante de
  `/ext/subghz/assets/` faltan o están obsoletas. Reinstala o actualiza el firmware con la tarjeta SD puesta.
- **El receptor no reacciona en absoluto**: banda incorrecta. Lee primero tu mando original (`Sub-GHz → Read`) y
  elige la misma frecuencia y modulación. DoorHan existe en 315 y 433.92 MHz; FAAC, Genius y Erreka en 433.92 y
  868.35.
- **El receptor reacciona pero nunca almacena el mando**: has perdido la ventana de aprendizaje o, por otro motivo (por
  ejemplo, interferencias), el receptor no recibió una señal correcta del Flipper.
- **Se rechaza el mando nuevo de Erreka/BFT**: algunas instalaciones comparten una misma semilla entre todos los
  mandos; recupérala ([Seed Capturer](/es/subghz/seed-capturer)) y usa Add Manually [Advanced]. Véase
  [KeeLoq](/es/subghz/keeloq).
- **El mando Nice O-Code se ignora**: un receptor de fábrica no tiene código de instalador; usa `Nice One` o
  `Nice FloR-S` en ese caso. Para un sistema ya instalado, véase [Nice O-Code](/es/subghz/nice-o-code).

::: warning
Registra mandos únicamente en receptores de tu propiedad o que estés autorizado a gestionar.
:::

## Relacionado

- [Códigos rodantes y botones personalizados](/es/subghz/rolling-codes)
- [Programar un mando nuevo en un receptor](/es/subghz/remote-prog)
- [KeeLoq](/es/subghz/keeloq) · [Sistemas compatibles](/es/subghz/supported-systems)
- [Modos de contador](/es/subghz/counter-mode) · [Formato de fichero .sub](/es/subghz/file-format)
