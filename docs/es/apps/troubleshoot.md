---
title: Resolución de problemas de apps
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Resolución de problemas de apps

Cuando una app no puede arrancar, el Flipper muestra `Error: <name>` con una pista breve y un enlace
`r.flipper.net/err_0X`. Esta página explica cada mensaje tal como aparece en Unleashed.

::: tip Unleashed
Unleashed no bloquea las apps compiladas para otra versión de la API. En lugar de los errores de fábrica **Outdated
App** / **Outdated Firmware** muestra una advertencia y te deja decidir; consulta
[App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New {#app-too-old-app-too-new}

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

La **versión mayor de la API** de la app difiere de la del firmware: **App Too Old** significa que la app se compiló
para una API más antigua y **App Too New**, para una más reciente.

- Pulsa **Continue** (<kbd>→</kbd>) para intentarlo igualmente. Muchas apps funcionan, pero una app que llame a una
  función modificada puede fallar.
- Pulsa <kbd>Back</kbd> para cancelar.
- La solución real: actualizar la app (tómala del pack actual de Unleashed, o recompílala para el SDK actual) o, en el
  caso de **App Too New**, actualizar el firmware.

## Error: App Not Found (err_01)

`Update firmware or app`

| Causa | Solución |
|---|---|
| el archivo de la app se borró de la tarjeta SD | reinstala la app, o reinstala el firmware (en las apps de sistema) |
| una app móvil antigua o beta abrió una app del catálogo que no está en la tarjeta | instala la app móvil oficial de Flipper desde la App Store / Google Play y reinstala la app |

Un mensaje relacionado, **SD card needed** / `Install SD card to run this app`, significa que una app del menú reside
en la tarjeta SD y no hay ninguna tarjeta insertada. **Update needed** / `Update firmware to run this app` significa
que la tarjeta está puesta pero falta el archivo de la app: reinstala el firmware con la tarjeta insertada.

## Error: Invalid File (err_02)

`Update the app`. El `.fap` está dañado: cabecera ELF corrupta, archivo incompleto (copia interrumpida) o secciones
que no se pueden cargar. Vuelve a copiar o instalar la app.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. No se puede leer el manifiesto (una sección ELF especial con la versión de la API y la
información de la app). El archivo está corrupto, o la app y el firmware están demasiado alejados. Actualiza la app; si
es más nueva que tu firmware, actualiza el firmware.

## Error: Missing Imports (err_04)

`Update firmware or app`. La app llama a funciones que tu firmware no exporta.

| Causa | Solución |
|---|---|
| la app se compiló para un firmware más reciente | actualiza Unleashed |
| la app se compiló para otro fork (usa las funciones propias de ese fork) | busca una compilación de la app para Unleashed, o recompílala con el SDK de Unleashed |

## Error: HW Target Mismatch (err_05)

`App not supported`. La app se compiló para otro objetivo de hardware del Flipper. No puede ejecutarse en este
dispositivo.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. Un FAP se carga en la RAM; si el heap está fragmentado o
hay demasiado en ejecución (por ejemplo una baliza BLE en segundo plano o una app grande), no cabe. Pulsa **Reboot** e
inicia la app de nuevo justo después del arranque.

## Si sigue sin funcionar

1. Actualiza a la última release de Unleashed; consulta [Actualizar](/es/start/updating).
2. Reinstala la app desde el [pack de apps](/es/apps/catalog#base-and-extra-packs) actual o desde el catálogo
   ([Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps)).
3. Si una app cuelga el Flipper, reinícialo con <kbd>←</kbd> + <kbd>Back</kbd>; consulta
   [Recuperación](/es/start/recovery) si ya no arranca.
4. Pregunta en los chats de la comunidad; consulta el [FAQ](/es/start/faq).

## Páginas relacionadas

- [Aplicaciones en la tarjeta SD (.fap)](/es/apps/sd-card-apps)
- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
