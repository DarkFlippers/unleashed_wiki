---
title: Nombre personalizado del Flipper
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Nombre personalizado del Flipper

Todo Flipper tiene un nombre de fábrica. Aparece en el Passport, en **About**, en las listas de dispositivos
Bluetooth y en qFlipper. Unleashed te permite sustituirlo por un nombre propio.

::: tip Unleashed
El firmware de serie no tiene ningún menú para renombrar el dispositivo. En Unleashed está en
**Settings → Desktop → Change Flipper Name**, y el nombre **sobrevive a las actualizaciones de firmware** porque se
guarda en la tarjeta microSD.
:::

## Poner un nombre

1. Ve a **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Escribe el nombre nuevo. El encabezado del teclado indica `Leave empty for default`.
   - **De 2 a 8 caracteres**;
   - **solo letras latinas y dígitos** (`A–Z`, `a–z`, `0–9`). Cualquier otra cosa muestra *«Please only enter
     letters and numbers!»*.
3. Selecciona **Save**.
4. Aparece el mensaje **`Name is set!`** / *«Your Flipper will be restarted on exit.»*
5. Sal de Settings con <kbd>BACK</kbd>. El Flipper **se reinicia automáticamente**.
6. Tras el reinicio, el nombre nuevo aparece en el Passport, en **Settings → About** y por Bluetooth.

## Volver al nombre de fábrica

1. Abre **Settings → Desktop → Change Flipper Name**.
2. Borra todos los caracteres y deja el campo **vacío**.
3. Selecciona **Save** y sal de Settings. El Flipper se reinicia con su nombre original.

## Cómo funciona

- El nombre se guarda en **`/ext/dolphin/name.settings`**, en la tarjeta SD:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- Al arrancar, el servicio `namechanger` espera a la tarjeta SD, lee este archivo y aplica el nombre si es válido:
  encabezado y versión correctos, de 2 a 8 caracteres y solo letras y dígitos. Después reinicia los perfiles de
  serie USB y de Bluetooth para que usen el nombre nuevo.
- Guardar un nombre vacío borra el archivo.
- El servicio solo se ejecuta en un arranque normal, no en el actualizador ni en DFU.

Como el nombre vive en la tarjeta, se mantiene después de las actualizaciones. Se pierde si formateas o cambias la
tarjeta, o si borras el archivo.

## Resolución de problemas

| Problema | Solución |
|---|---|
| El nombre no ha cambiado | ¿Has salido de Settings (el reinicio es lo que lo aplica)? ¿Está insertada la tarjeta SD? ¿Tiene el nombre entre 2 y 8 letras o dígitos? Un nombre de un solo carácter se guarda, pero se ignora al arrancar |
| La aplicación móvil ya no se conecta | El nombre de Bluetooth ha cambiado. Olvida el Flipper en la aplicación **y** en los ajustes de Bluetooth del móvil, ejecuta **Settings → Bluetooth → Unpair All Devices** en el Flipper y vuelve a emparejarlo |
| Se ignora un archivo de nombre copiado de otro sitio | Comprueba el encabezado `Flipper Name File`, `Version: 1` y las reglas del nombre |
