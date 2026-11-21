---
title: La aplicación MFKey
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# La aplicación MFKey (MFKey 4.1)

**MFKey** (de [@noproto](https://github.com/noproto)) recupera claves de MIFARE Classic **en el propio Flipper** a
partir de los nonces recopilados por la aplicación NFC: nonces de lector (MFKey32) y nonces de tarjeta de los
ataques anidados. Es la herramienta para cuando no tienes móvil ni PC a mano; es más lenta que
[qUnleashed](/es/nfc/qunleashed), pero funciona en cualquier parte, incluso en el bolsillo.

| | |
|---|---|
| Ubicación | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Versión en Unleashed | **4.1** |
| Entradas | `/ext/nfc/.mfkey32.log` (nonces de lector), `/ext/nfc/.nested.log` (nonces de tarjeta) |
| Salida | `/ext/nfc/assets/mf_classic_dict_user.nfc` (claves), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (candidatas SEN) |

## Uso

1. Recopila primero los nonces:
   - de un lector: [MFKey32](/es/nfc/mfkey) (`Extract MFC Keys`);
   - de la tarjeta: [ataques anidados](/es/nfc/nested-fudan) durante `NFC → Read`.
2. Abre `Main Menu → Apps → NFC → MFKey`, o pulsa **Run** en la pantalla *"Now run Mfkey32 to extract keys"* de la
   aplicación NFC (aparece después de `Extract MFC Keys` y después de `Crack nonces in MFKey32`).
3. La pantalla dice **Ready**. <kbd>→</kbd> **Help** muestra *"Collect nonces by reading tag or reader in NFC app"*.
   Pulsa <kbd>OK</kbd> **Start**.
4. MFKey comprueba primero los nonces contra los diccionarios existentes: **Dict solves: N (in progress)**,
   **Keys in dict: N**. Los nonces cuya clave ya se conoce se saltan.
5. Después se ejecuta el ataque con tres barras de progreso: **Cracking: X/Y**, **Round: X/Y – ETA NN Sec** y
   **Total ETA NNN Sec**. La línea **RAM** de arriba muestra el montículo libre.
6. Al terminar oirás un pitido y verás **Complete**, **Keys added to user dict: N** y, en el caso de los nonces
   cifrados estáticos, **SEN key candidates: N**.
7. Vuelve a la aplicación NFC y lee la tarjeta otra vez (o usa `Saved → <tarjeta> → Unlock with Dictionary`).

<kbd>←</kbd> detiene el trabajo y sale (el hilo se para de forma limpia; las claves encontradas hasta ese momento se
escriben igualmente).

### Errores

| Pantalla | Significado |
|---|---|
| **No nonces found** | No existe ni `.mfkey32.log` ni `.nested.log`. Recopila nonces primero. También aparece con las etiquetas que solo admiten HardNested: sus nonces no se pueden romper en el Flipper. |
| **Nonces already cracked** | Todos los nonces de los registros ya están resueltos por una clave de tus diccionarios. |
| **No free RAM** | Memoria insuficiente. Reinicia el Flipper y vuelve a intentarlo; cierra otras aplicaciones. |

## Qué cambió MFKey 4.x

Del artículo de @gromovyna «MFKey 4.1: más rápido, más alto, más fuerte»: la nueva versión mayor llegó de forma
bastante discreta, pero supone una gran mejora de velocidad. Está disponible en las **compilaciones de desarrollo de
Unleashed desde la 1251**. (En el momento del artículo los cambios de la aplicación también estaban integrados en el
firmware oficial, pero no los cambios del lado del firmware que necesita.) Gracias a @noproto y su equipo.

Más abajo, **SEN** = static encrypted nonce, nonce cifrado estático (véase [Ataques anidados](/es/nfc/nested-fudan)).

**4.0**

- Compatibilidad con el nuevo formato de diccionario SEN: la recuperación de claves es **10 veces más rápida**.
- El formato antiguo de diccionario SEN ya no es compatible.

**4.1**

- La recuperación de claves es otro **40 % más rápida**; mejor eficiencia de memoria.
- El monolítico `mfkey.c` se dividió en módulos: `mfkey_batch_prelude`, `mfkey_state_expansion`, `mfkey_bs_verify`,
  `mfkey_recovery`, `mfkey_dedup`.
- 32 candidatas verificadas en paralelo mediante SWAR (operaciones de bits en lugar de comprobaciones de una en
  una).
- Una «Super-LUT» precalculada de 2 KB para las rondas 0 a 3: una carga indexada por ronda en lugar de un cálculo.
- Ordenación radix O(n) en lugar de quicksort; deduplicación mediante hash de Fibonacci en lugar de un barrido
  ingenuo.
- Los registros de la FPU del M4 se usan como espacio de trabajo adicional (`vmov`), lo que reduce la presión sobre
  los registros.
- Un bucle con dispositivo de Duff desenrollado 8 veces al buscar duplicados.

### Tiempos reales

El autor probó el caso más difícil: una etiqueta con **nonces cifrados estáticos**. En esas etiquetas las claves
calculadas no se verifican al vuelo ni van directamente al diccionario de usuario; en su lugar se construye un
diccionario de **candidatas** que después hay que comprobar contra la etiqueta. Así que se extraen **todas** las
claves que podrían producir un nonce: el diccionario más grande, el escenario más largo. Ni un solo
*Out Of Memory* durante las pruebas.

| Prueba | Configuración | Resultado |
|---|---|---|
| Llave Iron Logic | Etiqueta cifrada con una tarjeta de objeto de [Iron Logic](/es/nfc/iron-logic); ninguna clave en el diccionario, atacada por la puerta trasera; **18 claves únicas en 32 sectores** | Ciclo completo de **6 h 8 min**, más de **1,2 millones de candidatas**; después, varias horas más comprobando candidatas en la etiqueta. |
| 1 sector, 2 claves | La misma etiqueta (borrada), con el sector 0 cifrado con claves A y B aleatorias y distintas | **17 minutos**; la comprobación de candidatas en un solo sector también fue rápida. |

Para comparar, recuperar la primera prueba en un Proxmark3 con un ordenador llevó 24 segundos, así que el Flipper
nunca competirá con eso. Pero si estás de viaje o simplemente tienes tiempo para un trabajo en segundo plano, el
Flipper que llevas en el bolsillo puede recuperar las claves y emular la etiqueta. Y como son sobre todo los
sistemas tipo Iron Logic los que adoran la diversificación de claves, la probabilidad de toparse con el escenario
más largo es relativamente pequeña.

::: tip Unleashed
Unleashed incluye MFKey 4.1 con los cambios del lado del firmware que necesita (el diccionario CUID en `Read`, con
una barra de progreso mientras se carga). Cuando MFKey termine con una etiqueta SEN, usa **Save Keys to Dictionary**
en el volcado completamente leído para copiar las claves recuperadas a tu diccionario de usuario; véase
[MIFARE Classic](/es/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Consejos

- Limpia `/ext/nfc/.nested.log` y `/ext/nfc/.mfkey32.log` después de una recuperación correcta: los nonces antiguos
  se vuelven a comprobar en cada arranque.
- Si instalaste aplicaciones por separado, comprueba que un `mfkey.fap` antiguo no haya sobrescrito el del firmware.
- Alternativas mucho más rápidas: [qUnleashed](/es/nfc/qunleashed) en un móvil o PC, o el proyecto
  [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli).

## Relacionado

[MFKey32](/es/nfc/mfkey) · [Ataques anidados](/es/nfc/nested-fudan) · [qUnleashed](/es/nfc/qunleashed) ·
[MIFARE Classic](/es/nfc/mifare-classic)
