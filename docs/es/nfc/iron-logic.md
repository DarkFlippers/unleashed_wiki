---
title: Lectores Iron Logic
order: 100
author: gromovyna
original: [https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://t.me/gromovyna/14]
sources: [gromovyna]
---
# Lectores Iron Logic (CP-Z-2 «3 franjas» / «4 franjas»)

Los lectores Iron Logic («enchufes») son habituales en porteros automáticos y control de acceso por toda la antigua URSS. Esta página explica cómo protegen los llaveros MIFARE Classic, cómo saber con qué variante estás tratando y qué dice la investigación publicada sobre leer, emular y copiar **tu propio** llavero con un Flipper Zero.

::: tip Alcance
Solo para tus propias credenciales y para investigación lícita. Basado en el artículo de @gromovyna (13-03-2025).
:::

## Cómo se defienden estos sistemas del clonado

Iron Logic parte del barato MIFARE Classic y le superpone defensas:

- **Diversificación de claves.** Las claves de sector se derivan por tarjeta a partir del UID de la tarjeta y del «mapa de objeto» del lector (una constante cargada en el lector). Por eso un ataque de diccionario normalmente no encuentra nada en un sistema configurado.
- **Filtros** contra tarjetas mágicas y emuladores (por ejemplo «IL-30 only», OTP1, OTP2), según el firmware del lector.
- **Modo dinámico** («only first», véase [Alta dinámica en Iron Logic](/es/nfc/iron-logic-enrollment)), en el que los datos de la tarjeta cambian en cada paso.

Entender esto te dice por qué un simple «leer y después escribir en una tarjeta en blanco» falla a menudo, y qué hacer en su lugar.

## Qué lector tienes

| Variante | Notas |
|---|---|
| CP-Z-2 («3 franjas») | Más antiguo, descontinuado, todavía habitual. |
| CP-Z-2 (mod. MF-I) («4 franjas») | Modelo actual, compatible con las versiones de firmware. El artículo está escrito para este, pero sirve también para el antiguo. |

La identificación por la carcasa no es fiable al 100 % (un instalador puede poner electrónica nueva en una carcasa vieja), pero en la práctica funciona casi siempre. Estos lectores se usan también dentro de paneles de otros fabricantes (Eltis, Metakom y otros); eso no importa, porque el objetivo es recuperar todos los sectores de la tarjeta MIFARE Classic.

## Comprueba si no hay nada que hacer

### Tarjeta SmartMX (IL-30)

Si se usa un lector de «4 franjas» y el Flipper muestra la pantalla de «tarjeta no compatible», revisa la tarjeta: **SAK = 28** y **ATQA = 0004** significa una tarjeta **SmartMX**, y puede que el lector tenga activado el filtro **«IL-30 only»**. Aun así puedes probar los pasos siguientes, por si el filtro está desactivado y el lector está en modo mixto (claves SmartMX nuevas y MIFARE Classic antiguas). Si nada funciona y necesitas una copia, el autor sugiere un taller equipado con aparatos iKey, que escriben los datos en chips originales (iMF+) aprovechando un fallo lógico de Iron Logic.

### Porteros automáticos dinámicos («Sokol», de Petrunya)

Los porteros Sokol (normalmente construidos sobre un panel Eltis 5000) usan lectores Iron Logic **con dinámica**: los datos de la llave cambian en cada paso y las copias antiguas dejan de valer. Emular o escribir una tarjeta en blanco puede **corromper tu original**. Detalles: [alta dinámica](/es/nfc/iron-logic-enrollment).

## Paso 1: volcar todos los sectores

Necesitas todos los sectores y todas las claves de la tarjeta. No esperes a que termine el ataque de diccionario: con claves diversificadas no tiene sentido.

1. Lee la tarjeta (`Main Menu → NFC → Read`). Véase [Leer tarjetas](/es/nfc/read).
2. Si el resultado es **16/16 sectores leídos pero 0/32 claves encontradas**, la tarjeta tiene una puerta trasera. Ve directamente a la [guía de Nested y puertas traseras de Fudan](/es/nfc/nested-fudan).
3. Si no tienes ninguna clave, recopila nonces del lector (véase más abajo) y después recupera las claves con [MFKey](/es/nfc/mfkey).
4. Recupera las claves restantes con Nested ([guía](/es/nfc/nested-fudan)).

### Recopilar nonces del lector

Hasta hace poco se creía que el Flipper no podía trabajar en absoluto con los lectores de 4 franjas. Gracias a @blowtreez resultó que sí es posible, aunque requiere precisión y práctica. El Flipper recopila nonces de **todas** las versiones de lector, independientemente del número de franjas o del firmware.

- Localiza la posición en la que el Flipper interactúa con el lector. Empíricamente: el texto **«FLI»** de la carcasa del Flipper debe quedar **por encima del lector**.
- Mantenlo lo más cerca posible, tocando el lector.
- A veces (como en el caso del autor) no funciona dentro de una funda; saca el Flipper y prueba sin ella.

Después sigue el artículo oficial [Recovering MIFARE Classic keys](https://docs.flipper.net/nfc/mfkey32).

::: tip Notas del autor
- En la mayoría de los casos bastan las claves y la lectura completa de los sectores **0, 1 y 14**, pero algunos sistemas guardan datos en sectores propios (por ejemplo, el 8). Haz siempre una copia completa y descifra todos los sectores.
- El autor menciona que tiene una API privada que calcula la clave del sector 14 a partir del UID de una tarjeta, para continuar con Nested (la ofrece en el chat de la comunidad de Unleashed).
:::

## Paso 2: emulación

- Funciona en todos los lectores de «3 franjas» (con raras excepciones) y en los de «4 franjas» salvo que lleven el firmware más reciente (**7.28**, según se indica en la publicación del canal).
- En versiones anteriores como la **7.20** (el firmware actual de fábrica) la emulación funciona, pero hay que encontrar la posición exacta del Flipper respecto al lector, igual que al recopilar nonces.
- Los filtros OTP1 y OTP2 **no** afectan a la emulación.
- El Chameleon Ultra se comporta igual.
- Con el filtro «IL-30 only» activado, la emulación no funcionará.

## Paso 3: copiar a una tarjeta en blanco

La elección universal es una tarjeta en blanco **CUID static nonce (también llamada MF-3.2)** (véase [Tarjetas mágicas](/es/nfc/magic-cards)). En el momento de escribir esto funcionaba en todas las versiones de firmware y con todas las configuraciones de filtro para los dos tipos de lector. Para las de «3 franjas» sirve una **CUID** corriente, y algunos lo han conseguido incluso con una **Zero**.

El autor recomienda no andar buscando la tarjeta en blanco mínima que funcione, salvo que te gusten los experimentos: la diferencia de precio entre una CUID static nonce y una CUID normal es pequeña, y te libras del «factor casino». También encontró varios chips CUID normales (revisiones más nuevas) que funcionan en todas las versiones de firmware de 4 franjas, además de informes anteriores de la comunidad con éxito usando tarjetas CUID normales, que no pudo reproducir de forma fiable hasta hace poco.

## Temas no tratados

El autor enumera los temas que quedan fuera del alcance o siguen en investigación: cómo se implementan los filtros OTP1 y OTP2, la KDF de la clave A del sector 14 a partir del UID, y el papel del mapa de objeto en el cifrado de los sectores.

## Relacionado

- [Nested y la puerta trasera de Fudan](/es/nfc/nested-fudan) · [MFKey](/es/nfc/mfkey) · [Tarjetas mágicas](/es/nfc/magic-cards)
- [Alta dinámica en Iron Logic](/es/nfc/iron-logic-enrollment) · [Filtros de Vizit](/es/nfc/vizit-filters)
