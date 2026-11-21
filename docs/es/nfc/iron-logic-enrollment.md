---
title: Alta dinámica en Iron Logic
order: 110
author: gromovyna
original: [https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://t.me/gromovyna/14, https://t.me/gromovyna/19, https://t.me/gromovyna/20, https://t.me/gromovyna/25]
sources: [gromovyna]
---
# La «dinámica» de Iron Logic y el fallo lógico del alta

Un informe de investigación sobre cómo implementan los lectores Iron Logic la «dinámica» anticlonado (el modo «ТП» o «first only») y sobre un fallo lógico en la versión 7.29 del firmware del lector que se **corrigió en la 7.30**. Lectura formativa para propietarios e investigadores.

::: tip Alcance
Solo para tus propias credenciales y para investigación lícita. El fallo que se describe aquí está parcheado en el firmware actual (7.30). Basado en el artículo de @gromovyna (05-06-2025) y en sus publicaciones del canal.
:::

## Cómo se defienden estos sistemas del clonado

Un llavero MIFARE Classic estático lo puede copiar cualquiera que tenga las claves. Los fabricantes responden de dos maneras:

1. **Filtros**, que detectan tarjetas mágicas y emuladores (véase [Lectores Iron Logic](/es/nfc/iron-logic) y [Filtros de Vizit](/es/nfc/vizit-filters)).
2. **Dinámica**: algunos datos de la tarjeta se sincronizan con la memoria del lector en cada paso (un «contador»). Una copia hecha antes ya no coincide y se rechaza. Variantes de esto las usan Intratone, Hexact, Comelit, Noralsy y Urmet en Francia, Bélgica y Luxemburgo (donde una desincronización detectada puede inutilizar todas las etiquetas de un usuario), y se ha visto en algunos porteros Eltis en Rusia.

## El modo «ТП» («Только первый» / «solo el primero»)

Del anuncio del fabricante citado en el canal (publicación 20): en cada acceso el lector escribe una **contraseña nueva** en la tarjeta. En el acceso siguiente se comprueban el número de tarjeta y la contraseña contra lo que el lector guardó; si coinciden, la tarjeta se acepta y se escribe una contraseña nueva. Resultado: por muchas copias que existan, solo una tarjeta sigue funcionando. Al principio solo lo admitía el **CP-Z2 MF-I**, con el firmware 7.29 (anunciado como no completamente probado). El fabricante advierte de que ahora cada paso **escribe en la tarjeta**, así que conviene comprobar la resistencia a escrituras de tus tarjetas antes de cambiar.

Por qué es un dolor de cabeza: el mercado está lleno de etiquetas MIFARE Classic chinas falsificadas, que pueden no sobrevivir al número de reescrituras, y una escritura interrumpida (mala posición, corte de alimentación) puede dejar la tarjeta desincronizada. Por eso también emular o clonar en estos sistemas puede **arruinar tu original**.

## Firmware 7.29: sin filtros, con la dinámica como modo principal

El firmware 7.29 (prueba abierta) desactivó todos los filtros y convirtió la dinámica en el modo principal. El equipo de investigación encontró vulnerabilidades en esa versión; un fallo lógico se corrigió en la **7.30**, y después el autor publicó la descripción.

## Alta: cómo pasa una tarjeta a ser dinámica

Para pasar miles de tarjetas estáticas existentes a la dinámica sin obligar a los usuarios a reexpedirlas, Iron Logic introdujo el **alta** (enrollment). Se escriben metadatos en el **sector 14** de la tarjeta. Lógica simplificada del lector:

1. El lector comprueba los metadatos de la tarjeta.
2. Si la tarjeta **todavía no está en modo dinámico**, el lector la da de alta y guarda un valor de contador. **No** comprueba si ese identificador de tarjeta ya está en su memoria.
3. Si la tarjeta ya está dada de alta, se aplican comprobaciones estrictas del contador.

Las parejas identificador/contador se guardan en la memoria no volátil del lector.

## El fallo (parcheado en la 7.30)

La debilidad se deriva del paso 2: un lector al que se le presenta una tarjeta que sigue pareciendo «estática» simplemente la vuelve a dar de alta. El único obstáculo para un atacante es disponer de un volcado de la tarjeta **anterior** a su primera alta. Las tarjetas lo bastante antiguas para no tener metadatos no las acepta el lector, así que la conversión de datos dinámicos de vuelta a un estado «estático» solo se exploró superficialmente.

El autor describe dos formas prácticas de presentar cada vez una tarjeta «estática»:

- **Etiquetas GDM (GDMIC)**, una variante de USCUID con modo de sombra: los datos se escriben en una memoria temporal y vuelven a la memoria permanente cuando el campo del lector se apaga, así que la original (ya dada de alta) y un número ilimitado de copias pueden convivir. El autor señala que es sencillo pero está fuera del alcance de la mayoría de los cerrajeros, y que se puede contrarrestar con los filtros anteriores o con una gestión más inteligente del campo de RF.
- **Flipper Zero, a mano**: leer la tarjeta estática, emularla, usar `Return to Initial State` y repetir. Vale para pruebas, es impracticable a diario.

El equipo tiene otros ataques teóricos y prácticos, y compartió algunas ideas con iKey.

## Qué deberían hacer los propietarios

- Actualizar los lectores a la **7.30 o posterior**.
- Probar la resistencia a escrituras de tus tarjetas antes de activar la dinámica.
- Preferir familias de tarjetas modernas (MIFARE Plus, DESFire y similares) donde sea posible; MIFARE Classic se considera obsoleta incluso por su propio fabricante.

## Relacionado

- [Lectores Iron Logic](/es/nfc/iron-logic) · [Tarjetas mágicas](/es/nfc/magic-cards) · [Filtros de Vizit](/es/nfc/vizit-filters)
