---
title: Llave de seguridad U2F
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# Llave de seguridad U2F

La app **U2F** convierte Flipper Zero en una llave de seguridad USB
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). Después de introducir tu
contraseña en un sitio web, el sitio pide la llave y tú confirmas el inicio de sesión pulsando <kbd>OK</kbd> en el
Flipper. Google, GitHub, Facebook, X y muchos otros sitios admiten llaves U2F;
[dongleauth.com](https://www.dongleauth.com/) mantiene una lista.

::: warning Llave solo por software
El U2F del Flipper está implementado en software. Para la banca y otras cuentas de alto valor usa una llave de
seguridad hardware certificada. Mantén siempre un segundo factor de reserva (códigos de recuperación u otra llave).
:::

## Antes de empezar

- **Se necesita una tarjeta microSD**. Los datos de U2F residen en `/ext/u2f/`. Sin ella la app muestra
  `No SD card or app data found. This app will not work without required files.`
- Los archivos de certificado `/ext/u2f/assets/cert.der` y `/ext/u2f/assets/cert_key.u2f` los instala la
  actualización del firmware. Si faltan, vuelve a actualizar el firmware con la tarjeta insertada.
- **Cierra qFlipper** (y Flipper Lab): el Flipper debe estar libre para poder conmutar su puerto USB al modo U2F. Si
  hay una conexión activa, la app muestra `Connection Is Active! Disconnect from PC or phone to use this function.`

## Registrar el Flipper en un sitio web

1. Conecta el Flipper al ordenador con un cable USB.
2. Abre `Main Menu → U2F`. La pantalla muestra `Connect me to computer` y después `Connected!` en cuanto el ordenador
   reconoce la llave.

   ![U2F: Connect me to computer, con el Flipper dibujado como un pendrive USB](/screens/apps/u2f_not_connected.png)

3. En el sitio web, abre los ajustes de doble factor y elige añadir una **llave de seguridad** (la redacción varía
   según el sitio).
4. El Flipper muestra `Press OK to register`. Pulsa <kbd>OK</kbd>.
5. El sitio confirma que la llave se ha añadido.

## Iniciar sesión

1. Conecta el Flipper por USB y abre `Main Menu → U2F` (`Connected!`).
2. Introduce tu usuario y contraseña en el sitio web.
3. Cuando el sitio pida la llave de seguridad, el Flipper muestra `Press OK to authenticate`. Pulsa <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate, con la indicación del botón OK](/screens/apps/u2f.png)

4. El Flipper muestra `Authentication successful!` y el sitio te deja entrar.

## Protege tus archivos U2F

| Archivo | Finalidad |
|---|---|
| `/ext/u2f/key.u2f` | la clave U2F de este dispositivo, cifrada con una clave única de este Flipper |
| `/ext/u2f/cnt.u2f` | contador de autenticaciones |
| `/ext/u2f/assets/` | certificado de atestación y su clave (`cert.der`, `cert_key.u2f`) |

::: danger No borres, edites ni muevas los archivos U2F
- Cada Flipper tiene una clave interna única que cifra los archivos U2F. Una tarjeta con los archivos U2F movida a
  **otro Flipper no funcionará** ahí.
- Si borras o editas los archivos, o insertas una tarjeta nueva, el Flipper crea un conjunto nuevo de archivos U2F y
  tendrás que **registrarlo otra vez en todos los sitios web**.
- Si borras `u2f/assets` (o toda la carpeta `u2f`), la app deja de funcionar (informa de `No SD card or app data
  found`) hasta que restaures la carpeta actualizando el firmware.
:::

## Resolución de problemas

| Síntoma | Solución |
|---|---|
| Se queda en `Connect me to computer` | usa un cable de datos (no solo de carga), cierra qFlipper, prueba otro puerto USB |
| `Connection Is Active!` | cierra qFlipper, Flipper Lab, la CLI o la sesión de la app móvil y vuelve a abrir U2F |
| `No SD card or app data found` | inserta la tarjeta; si ya está puesta, restaura `/ext/u2f/assets` reinstalando el firmware |
| `Certificate error` | el motor U2F no pudo arrancar con los archivos de la tarjeta: reinstala el firmware con la tarjeta insertada |
| El sitio ya no acepta la llave | los archivos U2F se regeneraron (tarjeta nueva, archivos borrados): inicia sesión con tu factor de reserva y vuelve a registrar el Flipper |

La pestaña **U2F** del [Archive](/es/apps/archive) también inicia la app.

## Páginas relacionadas

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
- [Bad USB](/es/badusb/usage)
- [qFlipper](/es/mobile/qflipper)
