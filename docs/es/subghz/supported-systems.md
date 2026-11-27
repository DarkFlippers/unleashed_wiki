---
title: Sistemas compatibles
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz/protocols]
sources: [unleashed-docs, unleashed-readme, unleashed-src]
---
# Sistemas compatibles

Todos los protocolos Sub-GHz que la aplicación `Sub-GHz` de **Unleashed** puede decodificar, guardar y (en su
mayoría) enviar, elaborados a partir del registro de protocolos de `lib/subghz/protocols/` y de la documentación de
protocolos de Unleashed. Aplicaciones como *Weather Station* o [Remote Analyzer](/es/subghz/remote-analyzer) tienen
sus propias listas de protocolos adicionales.

::: tip Unleashed
Unleashed es un fork, así que decodifica todo lo que decodifica el firmware oficial: 38 de los 64 decodificadores
de protocolo que hay detrás de estas tablas son de OFW, y la mayoría los escribió Skorp. Sobre ellos añade BelKorn,
Beninca ARC, Ditec GOL4, Jarolift, Nice O-Code, Telcoma EDGE, Treadmill37, Freezer y otros, más de 100 fabricantes
KeeLoq y la capacidad de **enviar** protocolos de código rodante, con
[botones personalizados](/es/subghz/rolling-codes#custom-buttons) y creación mediante
[Add Manually](/es/subghz/add-manually).
:::

## Cómo leer las tablas

- **433 MHz** normalmente significa `433.92 MHz`, y **868 MHz** significa `868.35 MHz`. Sin frecuencia = aún no se
  conoce.
- **Modulación** es lo que hay que poner en `Read → Config → Modulation`: `AM650`, `AM270`, `FM238`, `FM476`,
  `FM12K`. «FM» = prueba todos los presets FM; `FSK12K` en la documentación del fabricante = `FM12K` en el Flipper.
- **Estático**: código fijo, una copia funciona junto al original. **Dinámico**: código rodante; véase
  [Códigos rodantes](/es/subghz/rolling-codes).
- **Nombre en el fichero**: el valor de `Protocol:` en el fichero `.sub` ([formato](/es/subghz/file-format)).
- **Add Manually**: la entrada en `Sub-GHz → Add Manually`, si existe.

## Cancelas, garajes, barreras y persianas

| Sistema | Frecuencia | Mod. | Bits / tipo | Nombre en el fichero | Add Manually | Notas |
|---|---|---|---|---|---|---|
| Airforce | 433.92, 868 | AM650 | 18, estático | | | |
| Allstar Firefly 318ALD31K | 318 | AM650 | 18, estático | `Allstar Firefly` | | |
| Alutech AT-4N | 433.92 | AM650 | 72, dinámico | `Alutech AT-4N` | `Alutech AT4N`, `Alutech AT4L` | botones personalizados, [modos de contador](/es/subghz/counter-mode) |
| AN-Motors (Alutech) AT4 | 433.92 | AM650 | 64, pseudodinámico | `KeeLoq` | `AN-Motors AT4` | basado en KeeLoq |
| Ansonic | 433 | FM | 12, estático | `Ansonic` | | |
| BelKorn (Korn, BelGate, Furniteh, Euro5…) | 433.92 | AM650 | 118, dinámico | `BelKorn` | `BelKorn` | sin cifrar: serial de 36 bits + contador en claro; no hay campo de fabricante, todos los mandos se leen como BelKorn |
| Beninca ARC (TO.GO 2VA) | 433.92 | AM650 | 128, dinámico AES-128 | `Beninca ARC` | `Beninca ARC` | botón `0` = botón oculto |
| BETT | 433.92 | AM650 | 18, estático | `BETT` | `BETT` | |
| BFT Mitto | 433.92 | AM650 | 64, KeeLoq + semilla | `KeeLoq` | `BFT Mitto` | los mandos más nuevos derivan la semilla del serial (se decodifican en Read); los más antiguos la necesitan: modo de programación o [Seed Capturer](/es/subghz/seed-capturer); botón `0xF` = modo de programación |
| CAME | 433.92, 868 | AM650 | 12/24, estático | `CAME` | `CAME 12bit`, `CAME 24bit` | |
| CAME Atomo (TOPD4REN, TOP44RBN, TOP42R, TOP44R) | 433.92, 868 | AM650 | 62, dinámico | `CAME Atomo` | `CAME Atomo` | mantén Send ≥ 2 s |
| CAME TWEE (+ TOP44FGN, «New Fixed Code») | 433.92 | AM650 | 54, pseudodinámico | `CAME TWEE` | `CAME TWEE` | |
| Chamberlain Code | 315 | AM650 | 10, estático | `Cham_Code` | | |
| Clemsa | 433 | AM650 | 18, estático | `Clemsa` | | |
| Dickert MAHS | 433 | AM650 | 36, estático | `Dickert_MAHS` | | |
| Ditec GOL4 (BIXLG4, BIXLS2, BIXLP2) | 433.92 | AM650 | 54, dinámico | `Ditec GOL4` | `Ditec GOL4` | → = botón `0` (oculto) |
| Doitrand | 433 | AM650 | 37 | `Doitrand` | | la documentación lo lista como dinámico, pero en el firmware está registrado como tipo estático |
| Elplast / P-11B / 3BK / E.C.A | 433 | AM650 | 18, estático | `Elplast` | | |
| Erreka IRIS (IR02/IR04) | 433.92, 868.35 | AM650 | 64, KeeLoq + semilla | `KeeLoq` | `Erreka` | requiere semilla; `0xF` = modo de programación, envía la semilla en claro |
| FAAC SLH | 433.92, 868.35 | AM650 | 64, dinámico | `Faac SLH` | `FAAC SLH` | semilla por botón |
| FAAC TM (TM 433/868 DS) | 433.92, 868 | AM650 | 12, estático | `Faac TM` | `FAAC TM` | microinterruptores; el Te se conserva de la captura |
| Gate TX | 433.92 | AM650 | 64, estático | `GateTX` | `Gate TX` | |
| Genius (KILO TX2/4 JLC, Amigo…) | 433.92, 868.35 | AM650 | 64, dinámico | `Faac SLH` | `Genius` | paquete FAAC SLH con clave Genius, `Manufacture: Genius` |
| HCS101 | 433 | AM650 | 64, dinámico simple | `KeeLoq` | `KL: HCS101` | similar a KeeLoq |
| Hormann | 868 | AM650 | 44, estático | `Hormann HSM` | | |
| iDo | 433 | AM650 | 48, dinámico | `iDo 117/111` | | **solo decodificación** (no se puede enviar) |
| Jarolift | 433.92 | AM650 | 72, dinámico | `Jarolift` | `Jarolift` | persianas enrollables, basado en KeeLoq |
| KingGates Stylo 4k | 433.92 | AM650 | 89, dinámico | `KingGates Stylo4k` | `KingGates Stylo4k` | basado en KeeLoq |
| Linear | 300 | AM650 | 10, estático | `Linear` | `Linear` | |
| Linear Delta3 | 315 | AM650 | 8, estático | `LinearDelta3` | | |
| Marantec | 433.92, 868 | AM650 | 49, estático | `Marantec` | `Marantec` | |
| Marantec24 | 868 | AM650 | 24, estático | `Marantec24` | `Marantec24` | |
| Mastercode | 433 | AM650 | 36, estático | `Mastercode` | | |
| Megacode | 315 | AM650 | 24, estático | `MegaCode` | | |
| Nero Radio | 434.42 | AM650 | 56, estático | `Nero Radio` | | solo modo estático, el dinámico no es compatible |
| Nero Sketch | 433 | AM650 | 40, estático | `Nero Sketch` | | |
| Nice Flo | 433.92 | AM650 | 12/24, estático | `Nice FLO` | `Nice Flo 12bit`, `Nice Flo 24bit` | |
| Nice FloR-S | 433.92 | AM650 | 52, dinámico | `Nice FloR-S` | `Nice FloR-S` | modos de contador |
| Nice One | 433.92 | AM650 | 72, dinámico | `Nice FloR-S` | `Nice One` | |
| Nice O-Code | 433.92 | AM650 | 52/72/112, dinámico | `Nice FloR-S` | `Nice O-Code`, `Nice O-Code One`, `Nice O-Code+Crt` | cifrado con un código de instalador de 16 bits; véase la [aplicación Nice O-Code](/es/subghz/nice-o-code) |
| Nord ICE | 433.92 | AM650 | 33, estático | `Nord ICE` | `Nord ICE` | |
| Prastel | 433.92, 868 | AM650 | 25, estático | | | |
| Prastel | 433.92, 868 | AM650 | 42, dinámico | `Prastel` | `Prastel` | codificación de línea CAME, serial mezclado + contador |
| Proteco MOVER (TX3) | 433.92 | AM650 | 24, estático | `Proteco` | `Proteco` | |
| Revers RB2 (Реверс РБ-2(М)) | 433.92 | AM650 | 64, estático | `Revers_RB2` | `Revers RB2` | |
| Roger | 433.92 | AM650 | 28, estático | `Roger` | `Roger` | |
| Security+ 1.0 | 315, 433.92, 390 | AM650 | 42, dinámico | `Security+ 1.0` | `Security+1.0` | |
| Security+ 2.0 | 310, 315, 390, 868 | AM650 | 62, dinámico | `Security+ 2.0` | `Security+2.0` | |
| Security+ 2.0 Keypad | 315, 390, 868 | AM650 | 86, dinámico | `Security+ 2.0` | | PIN: [Security+ PIN](/es/subghz/secplus-pin) |
| Somfy Keytis (KeyGo 4 RTS, Keytis NS 2RTS) | 433.42, 868 | AM650 | 80, dinámico | `Somfy Keytis` | `Somfy Keytis` | |
| Superrollo GW60 | 433.92 | AM650 | 67, dinámico (KeeLoq HCS361, CRC) | `KeeLoq` | `KL: Superrollo` | botones `0x3(0xA)` Up / `0x5(0xC)` Down / `0x7(0xE)` Stop |
| Telcoma/Cardin EDGE (EDGE2/4/20) | 433.92 | AM650 | 32, estático | `Telcoma/Cardin EDGE` | `Telcoma EDGE` | preámbulo `0xFF` + serial + canal one-hot, cancela = Ch 0 |
| V2 Phoenix (Phox) | 433.92 | AM650 | 52, dinámico | `Phoenix_V2` | `V2 Phoenix` | algunos receptores tienen un modo estático; modos de contador |
| ZKTeco | 430.5 | AM650 | 24, estático | `Princeton` | `ZKTeco` | botones `0x30` UP, `0x03` STOP, `0x0C` DOWN asignados a las flechas — [ZKTeco CMP200](/es/subghz/zkteco-cmp200) |

## Sensores y domótica

| Sistema | Frecuencia | Mod. | Bits / tipo | Nombre en el fichero | Notas |
|---|---|---|---|---|---|
| Dooya | 433, 315 | AM650 | 40, estático | `Dooya` | persianas eléctricas, botones personalizados |
| Feron | 433.92 | AM650 | 32, estático | `Feron` | mandos de LED RGB; filtro de omisión «Sensors» |
| Honeywell | 315 | AM650 | 64, estático | `Honeywell Sec` | sensores de alarma |
| Honeywell WDB | 433, 315 | AM650 | 48, estático | `Honeywell` | timbres |
| Intertechno V3 | 433 | AM650 | 32, estático | `Intertechno_V3` | luces, enchufes |
| Jarolift | 433.92 | AM650 | 72, dinámico | `Jarolift` | persianas enrollables |
| Legrand | 433 | AM650 | 18, estático | `Legrand` | timbres |
| Magellan | 433.92 | AM650 | 32, estático | `Magellan` | sensores, alarmas |
| Power Smart | 433 | AM650 | 64, estático | `Power Smart` | persianas y estores |
| Somfy Telis (RTS) | 433.42 | AM650 | 56, dinámico | `Somfy Telis` | Add Manually `Somfy Telis` → `433.42 AM650` |

## Alarmas

| Sistema | Frecuencia | Mod. | Bits / tipo | Nombre en el fichero | Notas |
|---|---|---|---|---|---|
| GangQi | 433.92 | AM650 | 34, estático | `GangQi` | alarmas de bicicleta; filtro de omisión «Alarms» |
| Hollarm | 433.92 | AM650 | 42, estático | `Hollarm` | alarmas de bicicleta; filtro de omisión «Alarms» |

## Mandos genéricos y sin marca

| Sistema | Frecuencia | Mod. | Bits / tipo | Nombre en el fichero | Notas |
|---|---|---|---|---|---|
| Doorbell32 | 433.92 | AM650 | 32, estático | `Doorbell32` | PWM 1:3 estilo Princeton, guarda de 14·Te |
| Freezer | 433.92 | AM650 | 24, estático | `Freezer` | está en el registro; aún no en la lista original |
| Hay21 | 433.92 | AM650 | 21, dinámico | `Hay21` | |
| Holtek | 433/868/315 | AM650 | 40, estático | `Holtek` | |
| Holtek HT12X | 433/868/315 | AM650/FM | 12, estático | `Holtek_HT12X` | |
| KeyFinder | 433.92 | AM650 | 24, estático | `KeyFinder` | llaveros buscadores |
| KeyFinder2 | 433.92 | AM650 | 11, estático | `KeyFinder2` | btn(3)+10011+btn(3), sin serial |
| Princeton (PT2262…) | 315, 433.92, cualquiera | AM650 | 24, estático | `Princeton` | tiene su propio filtro «Ignore Princeton» |
| SMC5326 | 315, 433.92, cualquiera | AM650 | 25, estático | `SMC5326` | |
| Treadmill37 (QH-433) | 433.92 | AM650 | 37, estático | `Treadmill37` | |

## No son protocolos: RAW y BinRAW

- **RAW** (`Protocol: RAW`): temporizaciones en bruto grabadas con [Read RAW](/es/subghz/read-raw); reproduce
  cualquier cosa, no decodifica nada.
- **BinRAW** (`Protocol: BinRAW`): con `Read → Config → Bin RAW: ON`, una señal estática desconocida pero
  repetitiva se guarda como una secuencia de bits depurada con el Te recuperado. Puede emular casi cualquier
  protocolo estático que el Flipper no conozca.

## Fabricantes KeeLoq

Todos se decodifican como `Protocol: KeeLoq` con `Manufacture:`; se muestran como `KL: <nombre>`. Salvo indicación
contraria, el aprendizaje es «simple» con una parte de serial de 10 bits en el hop. Más sobre KeeLoq:
[KeeLoq](/es/subghz/keeloq).

### Cancelas y garajes

| Fabricante | Frec. / mod. | Aprendizaje / notas |
|---|---|---|
| AERF Collbaix, Hy dom, Medva, Motorgate, Otros, Sabutom, Temp, VDS | | aprendizaje especial, serial de 10 bits en el hop |
| Allmatic | 868, AM650 | sin serial en el hop: magic XOR |
| Aprimatic | 433.92, AM650 | serial de 12 bits en el hop + 2 bits de «paridad» |
| ATA PTX4 | | normal, 12 bits |
| Beninca | 433.92, 868, AM650 | sin serial en el hop: magic XOR |
| CAME Space | 433.92, AM650 | simple, 12 bits |
| Cardin S449 | 433.92, **FM12K** | normal, 12 bits (originales) / 10 bits (chinos) |
| Centurion | 433.92, AM650 | normal, valor fijo `0x1CE` en lugar del serial |
| Clemsa Mutancode | | normal, 12 bits |
| Comunello | 433.92, 868, AM650 | normal |
| DEA Mio | 433.92, AM650 | simple, serial modificado (`419` → `C19`) |
| DoorHan | 315, 433.92, AM650 | |
| Doormatic | | normal |
| DTM Neo | 433.92, AM650 | simple, 12 bits |
| Elmes Poland | 303, 433.92, AM650 | normal |
| Elvox | | normal |
| Erreka | 433.92, 868.35, AM650 | secure con semilla, serial de 8 bits |
| ET Blue, ET Blue Mix | | normal, 10 bits |
| FAAC FIX | 433.92, AM650 | normal, 10 bits; el discriminador de 12 bits se guarda en `Seed`, igual que Phantom / Hiland |
| FAAC RC, XT | 433.92, 868, AM650 | normal, 12 bits |
| Fadini | | simple, 12 bits |
| Genius Bravo (ECHO, Bravo) | 433.92, AM650 | normal, 12 bits; `0xB` = programación |
| Gibidi | 433.92, AM650 | |
| GSN | 433.92, AM650 | normal, 12 bits |
| HomeGate | 433.92, AM650 | |
| Hormann EcoStar | 433.92, AM650 | normal |
| IronLogic IL-100, IL-100 Smart PPult | 433.92, AM650 | |
| JCM Tech | 433.92, AM650 | simple, 8 bits |
| JCM Tech Gen2 | | especial; un byte de entrada no está en el paquete, se obtiene por fuerza bruta y se muestra como `Seed` |
| JCM1G (Antonio Meca, Baleato, Cas, Cubells, Cyacsa, DMIL, EMFA, Forsa, Gandara, Gibidi, Gibidi2, Hy dom, Hybrid, Norton, Nueva Castilla, Puertas Lorenzo, Pujol, Serviparking, Tech, Zibor) | | simple, 8 bits |
| Jolly Motors | 433.92, AM650 | |
| KEY | 433.92, AM650 | simple, valor fijo `0x2FF` |
| Mc Garcia | | simple, 10 bits |
| Mhouse | 433.92, AM650 | simple, 8 bits |
| Monarch | 433.92, AM650 | normal, fijo `0x100` o `0x280` (el Dorcas 22366CLN usa `0x280`) |
| Motorline | 433.92, AM650 | normal |
| Nice Smilo | 433.92, AM650 | simple, 8 bits |
| Normstahl | 433.92, AM650 | |
| Novoferm | 433.92, AM650 | |
| Phantom / Hiland | 433.92, AM650 | HCS300, normal, 10 bits; el discriminador de 12 bits se guarda en `Seed` |
| Pujol (Vario 4…) | 433.92, AM650 | especial, 8 bits |
| Pujol Vario (más antiguos) | 433.92, AM650 | simple, 8 bits |
| SEA | | simple |
| Seav | | normal, 12 bits |
| Sommer (TX03-868-4, Pearl, SOMloq) | 434.42, 868.80, FM12K o FM476 | normal |
| Stagnoli | | especial |
| Steelmate | 433.92, AM650 | normal, 12 bits |
| Stilmatic (R-Tech) | 433.92, AM650 | normal, 12 bits |
| Telcoma | | aprendizaje basado en tablas |
| Verex | | normal |
| Wisniowski | 433.92, AM650 | normal, 12 bits |
| Wisniowski 1 ByteReversed, Wisniowski 2 | | normal |

### Alarmas y otros

Alligator, Alligator S-275, APS-1100/APS-2550, Cenmax, Cenmax St-5, Cenmax St-7, Faraon, FFFF Normal, FFFF Simple,
Guard RF-311A (normal), Harpoon, KGB/Subaru (magic serial type 1), Leopard, Magic 1 / Magic 2 (magic serial type 2),
Magic 3 / Magic 4 (magic serial type 3), Merlin (XOR simple, sin serial en el hop), Miserere (normal), Mongoose
(normal), Pantera, Pantera CLK, Pantera XS/Jaguar, Partisan RX, Pecinin (simple, 12 bits), Reff, Rosh (simple,
12 bits), Rossi (simple, 12 bits), Sheriff, SL A2-A4, SL A6-A9/Tomahawk 9010, SL B6,B9 dop, Teco, Tomahawk TZ-9030,
Tomahawk Z,X 3-5, Zero Normal, Zero Simple, ZX-730-750-1055.

## Mi mando no está en la lista

1. Localiza la frecuencia con el [Frequency Analyzer](/es/subghz/frequency-analyzer) y después prueba
   [Read](/es/subghz/read) con todas las modulaciones (`AM650`, `FM238`, `FM476`, `FM12K`), manteniendo el botón
   ≥ 2 s.
2. Prueba `Bin RAW: ON` con los mandos estáticos.
3. ¿Todavía nada? Graba ficheros con [Read RAW](/es/subghz/read-raw) (umbral de RSSI `-----`, uno por modulación;
   pulsa un botón 5 veces manteniéndolo 1–2 s y después 5 veces manteniéndolo 5 s), fotografía el mando (también
   abierto) y abre una issue en el repositorio de Unleashed con los ficheros.

## Relacionado

- [Add Manually](/es/subghz/add-manually) · [KeeLoq](/es/subghz/keeloq) · [Códigos rodantes](/es/subghz/rolling-codes)
- [Read](/es/subghz/read) · [Read RAW](/es/subghz/read-raw) · [Programación de mandos](/es/subghz/remote-prog)
