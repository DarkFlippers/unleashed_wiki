---
title: Primer arranque
order: 10
original: [https://docs.flipper.net/zero/basics/first-start, https://docs.flipper.net/zero/basics/sd-card, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md]
sources: [flipper-docs, unleashed-docs]
---
# Primer arranque

Qué hacer en los diez primeros minutos con un Flipper Zero nuevo, antes de instalar Unleashed.

## 1. Enciéndelo

Mantén pulsado <kbd>BACK</kbd> unos 3 segundos. Aparece el escritorio, con tu delfín y la barra de estado:

![El escritorio del Flipper: la animación de reposo del delfín y la barra de estado con los iconos de tarjeta SD y batería](/screens/desktop/idle.png)

::: details El Flipper no se enciende
- Puede que la batería esté completamente agotada. Conecta el cable USB-C. El dispositivo se encenderá solo al cabo
  de un rato.
- Si sigue sin mostrar nada, mantén <kbd>←</kbd> + <kbd>BACK</kbd> durante 5 segundos (reinicio).
- ¿Nada todavía? Consulta [Combinaciones de teclas](/es/start/key-combos) y
  [Recuperación](/es/start/recovery).
:::

## 2. Inserta una tarjeta microSD

La tarjeta microSD es **obligatoria**. En ella se guardan las llaves, las tarjetas, los mandos, las bases de datos,
las aplicaciones que vienen con el firmware e incluso el almacenamiento «interno» (véase
[Tarjeta microSD](/es/start/sd-card)). La tarjeta no viene incluida con el dispositivo.

1. Busca la ranura en la parte inferior del Flipper.
2. Sujeta la tarjeta **con los contactos hacia arriba** y empújala hasta que haga clic.
3. La barra de estado muestra el icono de tarjeta SD cuando la tarjeta está montada.

Una tarjeta de marca de **16–32 GB** es más que suficiente. Funcionan tarjetas de hasta 256 GB, pero las grandes
tardan más en montarse. Las tarjetas baratas sin marca pueden hacer que el dispositivo vaya lento o inestable.

## 3. Actualiza el firmware oficial (solo en la primera instalación)

La guía de instalación de Unleashed te pide que **actualices primero a la última versión oficial** si vas a
instalar Unleashed por primera vez. Así se ponen al día el bootloader, la pila de radio y los datos internos.

- **qFlipper** (Windows/macOS/Linux): conéctalo por USB, abre la pestaña **Advanced controls**, pon el
  **Update Channel** en **Release** y pulsa **Update**.
- **Flipper Mobile App** (iOS/Android): activa el Bluetooth en el Flipper (**Main Menu → Settings → Bluetooth**),
  emparéjalo con la aplicación y toca **Update**. Tarda unos 10 minutos.

Más sobre qFlipper y la aplicación móvil: [qFlipper](/es/mobile/qflipper),
[Aplicación móvil](/es/mobile/mobile-app).

## 4. Instala Unleashed

Usa el **[Unleashed Web Installer](https://web.unleashedflip.com)**. Es el método más sencillo. Todos los métodos
están descritos en [Instalar Unleashed](/es/start/install).

## 5. Configuración básica

Después de instalarlo, abre **Main Menu → Settings** y revisa:

- **Clock & Alarm**: pon la fecha y la hora;
- **System → Hand Orient**: `Lefty` si sujetas el dispositivo con la mano izquierda;
- **Desktop**: PIN, reloj en el escritorio (`Show Clock`), estilo de la batería (`Battery View`), aplicaciones de
  acceso rápido;
- **Desktop → Change Flipper Name**: ponle a tu Flipper un nombre propio
  ([Nombre personalizado del Flipper](/es/start/custom-name)).

Todos los elementos están descritos en [Ajustes](/es/start/settings).

## Siguientes pasos

- Aprende los botones y los atajos: [Controles](/es/start/controls)
- Explora el escritorio: [Escritorio](/es/start/desktop)
- Descubre qué añade Unleashed: [Qué añade Unleashed](/es/start/unleashed-features)
