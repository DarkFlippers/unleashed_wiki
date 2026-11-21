---
title: Recuperación rápida de claves con qUnleashed
order: 45
author: gromovyna
original: [https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://t.me/gromovyna/32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, unleashed-readme, unleashed-src]
---
# Recuperación rápida de claves MIFARE Classic con qUnleashed

Una guía práctica de **@gromovyna**: recuperar claves de MIFARE Classic rápidamente usando Unleashed y su aplicación
acompañante **qUnleashed** (desarrollada y mantenida por el equipo de Unleashed; muchas gracias a
[apfxtech](https://github.com/apfxtech), el autor original de la aplicación). Es la continuación de
[Ataques anidados y puertas traseras de Fudan](/es/nfc/nested-fudan); se recomienda leer esa página primero, aunque
no es obligatorio.

La recuperación cubre **todos los ataques y tipos de nonce** conocidos en el momento de escribir esto: *débiles,
difíciles, estáticos y cifrados estáticos*. A diferencia de la [aplicación MFKey](/es/nfc/mfkey-app), el cálculo
pesado se ejecuta en tu móvil o en tu ordenador, así que normalmente lleva **minutos**, no horas.

::: warning Necesitas la etiqueta en tus manos
La etiqueta debe estar presente físicamente para la lectura final. Un «hice un volcado para un amigo y la etiqueta
ya no está» no sirve.
:::

## Versiones

La funcionalidad puede existir en versiones algo anteriores, pero estas son las que se usaron para las pruebas:

- Unleashed [unlshd-093](https://github.com/DarkFlippers/unleashed-firmware/releases/tag/unlshd-093)
- qUnleashed [beta-0.11.2](https://github.com/DarkFlippers/qUnleashed/releases/tag/beta-0.11.2)

Véase también [aplicación qUnleashed](/es/mobile/qunleashed-app) para la instalación y otras funciones.

## Qué necesitas

Una etiqueta **MIFARE Classic** (o **MIFARE Plus en SL1**, solo SL1) con **al menos una clave conocida o una puerta
trasera**.

![Una etiqueta con una clave desconocida](/img/remote/286db70e86cfa835.png)

![Una etiqueta con puerta trasera: claves desconocidas, pero sectores leídos por la puerta trasera](/img/remote/59bd4aa5ae1242c1.png)

Si tu etiqueta no tiene puerta trasera ni una sola clave conocida, consigue una del lector primero con
[MFKey32](/es/nfc/mfkey). qUnleashed también puede recuperar claves a partir de nonces de lector (véase el paso 2).

## Paso 1. Recopilar nonces

1. Antes del ataque conviene limpiar `/ext/nfc/.nested.log` si tienes uno (`/ext/` es la tarjeta SD). Después de la
   recuperación también tiene sentido borrarlo, para que no crezca y lo llene todo. Para qUnleashed esto no es
   crítico, pero es una buena práctica.
2. Lee la etiqueta: `Main Menu → NFC → Read`. Espera mientras se ejecutan las fases; cuáles aparecen depende del tipo
   de nonce de la etiqueta: **Backdoor Read**, **Nested Dictionary (Backdoor)**, **PRNG Analysis**,
   **Calibration**, **Nonce Collection**.

   ![Recopilación de nonces](/img/remote/786d77b7b65b3fd0.png)

3. Cuando aparezca la información de la etiqueta, **guarda el volcado incompleto**: lo necesitarás más adelante.
4. Opcionalmente, comprueba en qUnleashed que los nonces están ahí: conecta el Flipper, abre
   `Archive → External → nfc`, activa los ficheros ocultos (el menú de «hamburguesa» o de tres puntos de la esquina
   superior derecha) y busca `.nested.log`.

   ![.nested.log en qUnleashed](/img/remote/c4c534fbe93faa8a.png)

## Paso 2. Recuperar las claves

Todo ocurre en **qUnleashed**; el Flipper debe permanecer conectado (por Bluetooth o por cable) todo el tiempo.

1. Abre `Tools → Recover MIFARE Keys`.

   ![La entrada del menú](/img/remote/1a255b9128f988ab.png)

2. Espera a que termine la recuperación.

   ![Recuperando claves](/img/remote/1e1b3e63595aa99a.png)

   ::: warning Ten paciencia
   Puede llevar un rato según el tamaño de `.nested.log`, los tipos de nonce, la potencia del aparato que ejecuta
   qUnleashed y demás. Normalmente son minutos. Espera a que la operación se complete. Los nonces cifrados estáticos
   son los que más tardan.
   :::

3. Revisa el resultado. La fase de recuperación trabaja con **`.mfkey32.log`** (nonces de lector) y con
   **`.nested.log`** (nonces de etiqueta). La pantalla muestra de dónde viene cada clave, cuántas se han añadido al
   diccionario de usuario o al de candidatas, y así sucesivamente.

   ![Resultado de la recuperación](/img/remote/1c5f56614caf4530.png)

Dónde van a parar las claves depende del tipo de nonce:

| Nonces | Resultado |
|---|---|
| débiles, difíciles, estáticos | Las claves se añaden al **diccionario de usuario** `/ext/nfc/assets/mf_classic_dict_user.nfc`. |
| cifrados estáticos | En esta fase la clave no se puede calcular exactamente, así que se construye un **diccionario de candidatas** (también llamado **diccionario CUID**): `/ext/nfc/assets/mf_classic_dict_{UID}.nfc`, donde `{UID}` es el identificador de tu etiqueta. Puede ser grande: el ejemplo del autor tenía más de **1,2 millones de candidatas** para una sola etiqueta. |

## Paso 3. Volver a leer la etiqueta

Pon la etiqueta sobre el Flipper y ve a `NFC → Read`, o abre el volcado incompleto guardado y elige
**Unlock with Dictionary**.

![Unlock with Dictionary](/img/remote/b949b0a741d92f15.png)

Con un **diccionario CUID**, lo primero que ocurre es que se carga. El diccionario de candidatas es grande, así que
eso lleva tiempo, y verás una barra de progreso (*"CUID dictionary is loading"*). Aquí el tiempo real de carga se
mide en **minutos**.

![Pantalla de carga, compilación de desarrollo 1437 o posterior](/img/remote/47427c58e2a34889.png)

::: tip Actualización del 22-09-2026
En las primeras versiones del firmware este momento mostraba solo una pantalla en blanco, lo que confundía a muchos
usuarios. A partir de la compilación de desarrollo **1437** (y de la versión **094**) la pantalla tiene barra de
progreso.
:::

Después se ejecuta el ataque de diccionario con las claves recuperadas.

![Ataque de diccionario](/img/remote/f77ef58bda94b088.png)

De nuevo, con **nonces cifrados estáticos (diccionario CUID)** deja el Flipper sobre la etiqueta durante la búsqueda
y vete a preparar un té.

Una vez encontradas todas las claves puedes actualizar el volcado parcial guardado para convertirlo en uno completo,
o guardarlo con un nombre nuevo.

![Etiqueta completamente leída](/img/remote/9f9745d0d2ee0a4a.png)

Ahora todas las opciones están disponibles: emulación, escritura en tarjetas en blanco, compartirlo con un amigo,
etc.

::: warning Antes de escribir en una tarjeta en blanco
Conoce la diferencia entre las tarjetas en blanco y cómo los lectores pueden filtrarlas: véase
[Tarjetas mágicas](/es/nfc/magic-cards).
:::

## Opcional: guardar las claves de una etiqueta con cifrado estático en el diccionario de usuario

Por cómo funciona el ataque, las claves recuperadas del diccionario de candidatas se guardan **solo en ese
diccionario y en el volcado de la etiqueta**. Eso es un problema si quieres escribir una tarjeta en blanco y
borrarla después: [NFC Magic](/es/nfc/nfc-magic) funciona únicamente con la caché de claves y con los diccionarios
de usuario y de sistema.

Por eso el equipo añadió al firmware el guardado automático de claves, con comprobación de duplicados. Abre el menú
del volcado guardado (debe conocerse al menos una clave) y elige **Save Keys to Dictionary**.

![Save Keys to Dictionary](/img/remote/1b1aafbeca5dace4.png)

El Flipper muestra *"Saving keys to user dictionary"* y después *"New keys: N, Already known: M"*.

## Alternativas

También existe un [proyecto de CLI](https://github.com/phntm-lab/mfkey_desktop_cli) para la recuperación. En algunos
aspectos es más rápido, pero la línea de comandos es para frikis irreductibles. Para el uso diario el autor prefiere
la cómoda aplicación acompañante, sobre todo teniendo en cuenta cuántas otras funciones útiles tiene. Si solo
dispones del Flipper, usa la [aplicación MFKey](/es/nfc/mfkey-app).

El proceso puede parecer algo complicado al principio, pero con algo de práctica se vuelve rutinario.

## Relacionado

[Ataques anidados](/es/nfc/nested-fudan) · [MFKey32](/es/nfc/mfkey) · [Aplicación MFKey](/es/nfc/mfkey-app) ·
[MIFARE Classic](/es/nfc/mifare-classic) · [Tarjetas mágicas](/es/nfc/magic-cards) · [Aplicación qUnleashed](/es/mobile/qunleashed-app)
