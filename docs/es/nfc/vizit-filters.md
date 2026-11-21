---
title: Filtros de los lectores Vizit
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# Filtros de los lectores Vizit contra los clones de Vizit RF 3.1

Cómo intentan los lectores Vizit detectar llaves **Vizit RF 3.1** (MIFARE Ultralight EV1) clonadas, y qué busca cada filtro. Basado en el artículo de @gromovyna (15-05-2025).

::: tip Alcance
Solo para tus propias credenciales y para investigación lícita.
:::

## Contexto

Vizit es un fabricante ruso de control de acceso (desde 1996, según sus propias palabras). Los lectores antiguos usaban llaves **Dallas**, después **EM Marine**; los más nuevos usan **Vizit RF 3.1** (= MIFARE Ultralight, con UID que empieza por `34`); las llaves más recientes, **Vizit RF 7.1**, son **MIFARE Ultralight C** (autenticación 3DES). El firmware mínimo para RF 7.1 está indicado en la web del fabricante. El autor señala que la derivación de claves de las llaves 7.1 es conocida por iKey y que investigadores occidentales están trabajando en la recuperación de claves 3DES (sin detalles revelados).

## Cómo se defienden estos sistemas del clonado

A diferencia de Iron Logic, los filtros de Vizit que conoce el autor son de **software**, no de hardware, así que son visibles en el tráfico capturado con un Proxmark3. Se encontraron en el lector **RD-5F, firmware 212**; otros paneles también los llevan, pero no se sabe en qué versión apareció cada filtro.

### Filtro 1: puerta trasera Gen1

El lector envía el conocido comando de puerta trasera `40(7)` y espera respuesta. Una etiqueta genuina no responde. Va dirigido a las tarjetas en blanco más antiguas (UL-0116 / UL-0416), que se escribían a través de la puerta trasera, incluido el UID.

### Filtro 2: EV1 VERSION

El lector envía `EV1 VERSION` y compara el **segundo byte del resultado** con el **primer byte del UID de la etiqueta**. Las etiquetas Vizit RF 3.1 declaran como fabricante **Micron Russia** (byte `34`), y sus UID empiezan por `34`. Esto derrota a las variantes USCUID-UL (las «UL-21» chinas, «UL-2» en el mercado ruso). La respuesta del mercado fueron las etiquetas «ULtra», USCUID-UL con la misma versión que las 3.1 (que se puede configurar a mano con dos comandos de Proxmark3 si la configuración está abierta). Después de 2022 en Ucrania, los equipos compatibles con Vizit (lectores Grazhda, paneles Mriya) usan chips NXP originales con la versión correcta, así que las copias ULtra pueden no funcionar allí.

### Filtro 3: OTP

La página 3 de una Ultralight es OTP: ceros de fábrica, los bits solo se pueden poner a 1, nunca al revés (véase la sección 8.5.4 de la hoja de datos del MF0ULX1). En las etiquetas USCUID-UL normales es libremente reescribible. El lector intenta escribir ceros en esa página y la vuelve a leer; si ha cambiado, la etiqueta es una copia, el lector restaura el valor «original» y la rechaza. Una etiqueta genuina responde **NACK** y deja de responder hasta el siguiente SELECT, que es la máquina de estados correcta.

Otras implementaciones tenían el mismo fallo: el Flipper Zero es correcto desde la refactorización de NFC, y la emulación de Proxmark3 lo tuvo hasta que el autor lo comunicó ([issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) y se corrigió.

La respuesta de iKey fue la tarjeta en blanco **UL-5**, escribible una sola vez; una vez cambiada la página 0 se bloquea y se comporta como una original. Llega de China con una versión que no es Micron Russia. El autor sospecha que es una USCUID-UL configurada de forma especial. El mismo filtro también se puede superar con una USCUID-UL normal (por ejemplo, en configuración ULtra) cambiando correctamente el bloque de configuración, si está abierto.

## Conclusión para los propietarios

Vizit RF 7.1 (Ultralight C) cumple los estándares de seguridad modernos y pone fin a este juego del gato y el ratón.

## Relacionado

- [Lectores Iron Logic](/es/nfc/iron-logic) · [Tarjetas mágicas](/es/nfc/magic-cards) · [Leer tarjetas](/es/nfc/read)
