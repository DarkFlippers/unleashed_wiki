---
title: Códigos rodantes
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Códigos rodantes

Los mandos Sub-GHz son de dos tipos:

- **Código estático (fijo)**: cada pulsación envía exactamente el mismo paquete (Princeton, CAME 12/24 bit,
  Nice Flo, Marantec, Roger, Gate TX…). Una copia es idéntica al original; ambos siguen funcionando
  indefinidamente y en cualquier orden. Basta con [leerlo](/es/subghz/read) y guardarlo.
- **Código rodante (dinámico)**: cada pulsación envía un paquete nuevo construido a partir de un **contador** que
  aumenta en uno con cada pulsación (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+,
  Alutech AT-4N…). El contador va normalmente cifrado, así que el código siguiente solo puede calcularse si el
  firmware conoce la clave del protocolo.

::: tip Unleashed
Unleashed puede decodificar, guardar **y enviar** muchos protocolos de código rodante, crear mandos nuevos para
ellos con [Add Manually](/es/subghz/add-manually), enviar los demás botones del mando con las teclas de flecha
([botones personalizados](#custom-buttons)) y ajustar cómo se incrementa el contador
([Counter Incr.](#counter-increment), [modos de contador](/es/subghz/counter-mode)). El firmware original
decodifica la mayoría de ellos, pero no los transmite.
:::

## Cómo comprueba el receptor el contador

El receptor almacena el último contador que aceptó **para cada mando** (un valor por mando, no por botón):

- contador **igual al siguiente esperado o dentro de la ventana hacia delante** → aceptado, la cancela se abre;
- contador **muy adelantado** → muchos receptores se resincronizan: la primera pulsación se almacena y la siguiente
  consecutiva funciona;
- contador **por detrás** del valor almacenado → se ignora. Algunos receptores desemparejan un mando después de
  varios códigos «antiguos».

## El conflicto de contadores

*¿Por qué no se puede simplemente capturar tu propio mando de código rodante en Read y usarlo desde el Flipper?*
(adaptado de [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Imagina:

1. Pulsas el mando original: envía el contador `0002`.
2. Guardaste esa señal en el Flipper; cuando la envías, el Flipper envía `0003`.
3. El receptor cree que simplemente has vuelto a pulsar el original, y abre.
4. Pero el mando original sigue en `0002`; su siguiente pulsación es `0003`, un valor que el receptor ya ha visto,
   así que **no abre**.

No te alarmes: el mando no se ha desemparejado. Vuelve a pulsarlo: `0004` adelanta al Flipper y el original
funciona de nuevo. Pero esas «carreras» pueden separar los contadores más de 100 pulsaciones, y entonces el
original no se puede recuperar sin volver a emparejarlo en el receptor.

Salidas posibles:

- **La mejor: crea un mando nuevo** en el Flipper (`Sub-GHz → Add Manually`) y regístralo en el receptor. Tiene su
  propio serial y su propio contador y nunca entra en conflicto con los originales. Véase
  [programación de mandos](/es/subghz/remote-prog).
- Decide cuál vas a usar, el Flipper **o** el original, y usa solo ese.
- Usa los dos, pero no dejes nunca que los contadores se separen mucho (pulsa unas cuantas veces el que vaya por
  detrás).
- Experimental: hay [modos de contador](/es/subghz/counter-mode) especiales que, en algunos receptores, permiten
  que un clon y el original convivan.

::: danger Coches
No clones el mando de un coche. Reproducirlo (incluso mediante Read RAW) puede desincronizar la llave o dejarla en
lista negra, y volver a emparejarla suele requerir herramientas de servicio del concesionario.
:::

## Botones personalizados {#custom-buttons}

Cuando un fichero compatible de código rodante (o algunos estáticos) está abierto en `Emulate`:

- <kbd>OK</kbd> (`Send`) envía el botón que se grabó o se generó;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> envían **otros códigos de botón** del mismo mando, con el
  contador correctamente incrementado, mientras se mantienen pulsadas. El código del botón original se muestra como
  un pequeño dígito hexadecimal a la derecha de la pantalla mientras se usa una flecha.

Qué flecha corresponde a qué botón depende del protocolo; los botones ocultos o de programación (por ejemplo `0xF`
en el BFT Mitto, o `Prog` en Somfy) también son accesibles de esta forma: la tabla completa está en
[programación de mandos](/es/subghz/remote-prog) (referencia de botones ocultos).

Protocolos con botones personalizados en el firmware actual (el número indica cuántos códigos adicionales pueden
enviar las flechas):

| Protocolo | Extra | Protocolo | Extra |
|---|---|---|---|
| KeeLoq (todos los fabricantes `KL:`) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (programación) |
| Somfy Keytis | 1 (`Prog`) | | |

## Incremento del contador {#counter-increment}

`Sub-GHz → Radio Settings → Counter Incr.` fija cuánto crece el contador por transmisión: `+1` (por defecto), `+2`,
`+3`. Con el **modo depuración** activado (`Settings → System → Debug`) la lista se amplía a `+4`, `+5`, `+10`,
`+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50`: son herramientas de desarrollo de protocolos; no las uses en una
instalación real. Véase [Ajustes](/es/subghz/settings).

## Programar un mando nuevo en el receptor

La forma normal y libre de conflictos de usar el Flipper con una cancela de código rodante:

1. Lee tu mando original (`Sub-GHz → Read`) para conocer el protocolo, la frecuencia y la modulación.
2. `Sub-GHz → Add Manually` → tu sistema → la misma banda → guardar.
3. Pon el receptor en modo de aprendizaje (con el botón de la placa, o desde un mando que funcione: el Flipper
   envía el botón oculto de «programación» con una de las teclas de flecha).
4. Abre el fichero nuevo y mantén <kbd>OK</kbd>.

Procedimientos por fabricante: **[Usar el Flipper como mando nuevo](/es/subghz/remote-prog)**.

## Resolución de problemas

- **Funcionó una vez y luego dejó de hacerlo**: estás usando un clon. Pulsa varias veces seguidas para
  resincronizar, o crea mejor un mando nuevo.
- **El mando original dejó de funcionar**: el Flipper se adelantó. Pulsa el original varias veces; si la diferencia
  es demasiado grande, vuelve a registrarlo en el receptor.
- **Las flechas no hacen nada**: el protocolo no tiene botones personalizados, o el fichero es estático y no tiene
  campo de botón.
- **`KL: Unknown` después de Read**: la clave de fabricante es desconocida y no se puede transmitir. Véase
  [KeeLoq](/es/subghz/keeloq).

::: warning
Usa estas funciones únicamente con tus propios equipos o con el permiso del propietario.
:::

## Relacionado

- [Add Manually](/es/subghz/add-manually) · [Programación de mandos](/es/subghz/remote-prog)
- [KeeLoq](/es/subghz/keeloq) · [Modos de contador](/es/subghz/counter-mode)
- [Sistemas compatibles](/es/subghz/supported-systems)
