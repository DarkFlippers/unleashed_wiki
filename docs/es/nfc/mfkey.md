---
title: "MFKey32: claves a partir del lector"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: recuperar claves a partir de un lector

**MFKey32** es un ataque al cifrado Crypto-1 de MIFARE Classic. El Flipper finge ser la tarjeta; el lector intenta
autenticarse con su clave real, y las dos parejas de nonce y respuesta que envía bastan para calcular esa clave sin
conexión. El ataque, por tanto, necesita **acceso al lector**, no a las claves.

Úsalo cuando:

- la tarjeta solo se lee en parte y las claves que faltan son las que usa el lector (el caso más habitual);
- no tienes la tarjeta pero quieres conocer las claves de un lector y añadirlas a tu diccionario;
- la tarjeta no tiene puerta trasera ni ninguna clave conocida, así que los [ataques anidados](/es/nfc/nested-fudan)
  no pueden empezar.

## Con la tarjeta y el lector (recomendado)

Tener la tarjeta significa que, una vez recuperadas las claves del lector, podrás leer más sectores, que suele ser
justo lo que el lector comprueba de verdad.

1. Lee la tarjeta (`Main Menu → NFC → Read`). Acaba leída solo en parte.
2. En **More** selecciona **Extract MFC Keys**. El Flipper pregunta *"Save the Key?"*: elige **Save** (necesitarás el
   volcado más adelante) o **Skip**.
   *Como alternativa*, abre una tarjeta ya guardada: `Main Menu → NFC → Saved → <tarjeta> → Extract MFC Keys`.
3. La pantalla muestra **"Emulating... MIFARE MFkey32"** con el UID de la tarjeta y *"Touch the reader"*.

   ![Emulando MIFARE MFkey32 con el UID de la tarjeta y el aviso de acercarla al lector](/screens/nfc/mfkey_start.png)

4. Toca el lector con la parte trasera del Flipper, apártalo (*"Move the Flipper away"*) y vuelve a tocarlo
   (*"Touch the reader again"*). El contador **Nonce pairs: X/10** crece con cada intento correcto.

   ![Recopilando parejas de nonces: 4 de 10 recopiladas, con el aviso de apartar el Flipper](/screens/nfc/mfkey_collecting.png)

5. Cuando se han recopilado 10 parejas, la pantalla dice **Completed!**. Puedes parar antes con <kbd>OK</kbd>
   **Done**.
6. La pantalla siguiente lista **Nonce pairs saved: N** y los **Authenticated sectors** (qué sector y qué tipo de
   clave ha pedido el lector). Pulsa <kbd>OK</kbd>.

   ![Nonce pairs saved: 5, con la lista de sectores autenticados y los tipos de clave](/screens/nfc/mfkey_nonces_info.png)

7. El Flipper ofrece recuperar las claves: **"Now run Mfkey32 to extract keys"** con **Run** (que abre la
   [aplicación MFKey](/es/nfc/mfkey-app)). Si la aplicación no está instalada, muestra un código QR a
   `r.flipper.net/nfc-tools` y **Finish**.
8. Recupera las claves con una de las herramientas de más abajo. Se añaden al diccionario de usuario.
9. Vuelve a leer la tarjeta (o usa `Saved → <tarjeta> → Unlock with Dictionary`). Ahora deberían encontrarse más
   claves y más sectores.
10. Emula o escribe la tarjeta.

Los nonces se guardan en `/ext/nfc/.mfkey32.log`, una línea por pareja:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip ¿El contador no crece?
El lector no está intentando autenticar la tarjeta emulada. Algunos lectores solo comprueban el UID o usan otro
protocolo; otros rechazan la emulación de plano. Prueba distintas distancias y ángulos; a veces hacen falta varios
toques para una sola pareja.
:::

## Solo el lector

1. Ve a `Main Menu → NFC → Extract MFC Keys`. El Flipper emula una tarjeta MIFARE Classic genérica.
2. Los pasos 3 a 8 son como arriba.
3. Las claves recuperadas quedan en el diccionario de usuario y se probarán automáticamente cuando leas tarjetas de
   ese sistema más adelante.

## Recuperar las claves a partir de los nonces

| Herramienta | Dónde | Notas |
|---|---|---|
| **Aplicación MFKey** en el Flipper | `Main Menu → Apps → NFC → MFKey` | No hace falta móvil ni PC. Procesa `.mfkey32.log` y `.nested.log`. Más lenta. Véase [aplicación MFKey](/es/nfc/mfkey-app). |
| **qUnleashed** (aplicación acompañante de Unleashed) | `Tools → Recover MIFARE Keys` | Procesa `.mfkey32.log` y `.nested.log`, incluidos los nonces difíciles y los de cifrado estático. Rápida. Véase [qUnleashed](/es/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Aplicación oficial, solo nonces de lector. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Por USB, en el navegador. |

::: tip Unleashed
En Unleashed el elemento del menú se llama **Extract MFC Keys** (en el firmware original, *Extract MF Keys*), y la
aplicación acompañante **qUnleashed** puede recuperar las claves directamente en tu móvil o en tu ordenador. Desde
**MFKey 4.x** (compilación de desarrollo 1251 o posterior de Unleashed) la recuperación en el propio Flipper es
varias veces más rápida; véase [aplicación MFKey](/es/nfc/mfkey-app).
:::

## Si la recuperación falla

- **No se encuentra ninguna clave a partir de los nonces**: el lector no ha aceptado correctamente la emulación del
  Flipper. Vuelve a recopilar y prueba con otro volcado de tarjeta (una tarjeta real guardada funciona mejor que una
  emulación genérica).
- **MFKey muestra "No nonces found"**: no existe ni `.mfkey32.log` ni `.nested.log`.
- **MFKey se cuelga o se cierra**: reinicia (mantén <kbd>←</kbd> + <kbd>Back</kbd> 5 segundos), borra
  `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log` y vuelve a recopilar.
- **Último recurso**: haz una copia de seguridad de `/ext/nfc/assets/mf_classic_dict_user.nfc` y bórralo (esto
  elimina **todas** tus claves de usuario).

## Relacionado

[MIFARE Classic](/es/nfc/mifare-classic) · [Ataques anidados](/es/nfc/nested-fudan) · [Aplicación MFKey](/es/nfc/mfkey-app) ·
[qUnleashed](/es/nfc/qunleashed)
