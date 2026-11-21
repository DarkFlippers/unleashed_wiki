---
title: El delfín mascota
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# El delfín mascota

En el escritorio del Flipper vive un delfín digital. Se pone más contento y sube de nivel según usas las
herramientas del dispositivo, y sus animaciones cambian con su humor y su nivel.

## Passport

Pulsa <kbd>→</kbd> en el escritorio, o ve a **Main Menu → Settings → Passport**. El pasaporte muestra:

- el dibujo del delfín correspondiente al nivel actual;
- el **nombre**: el nombre de dispositivo del Flipper ([puedes cambiarlo](/es/start/custom-name));
- **Mood**: `Happy`, `Ok` o `Angry`;
- el **Level** y una barra de progreso hacia el siguiente nivel.

![Passport: el retrato del delfín, el nombre del Flipper, Mood: Happy, Level: 2 y la barra de progreso hasta el nivel 3](/screens/settings/passport.png)

## Humor

El delfín se pone más triste cuando no usas el Flipper. Su contador de «enfado» sube en uno aproximadamente **cada
48 horas** sin actividad. Usar aplicaciones le devuelve el buen humor, con un límite diario de velocidad de
recuperación.

El **Happy Mode** mantiene al delfín contento pase lo que pase:

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. El diálogo dice: *«I will never get angry at you for
not spending time with me as long as this mode is enabled»*. Vuelve a abrirlo y elige **Disable** para
desactivarlo.

## Niveles y XP

| Nivel | XP necesarios |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Cada aplicación puede dar como máximo **20 XP al día**. Hay 7 grupos contabilizados (Sub-GHz, RFID, NFC,
infrarrojos, iButton, Bad USB y los «plugins», que incluyen U2F, GPIO y las aplicaciones externas), así que el
máximo es de **140 XP al día**. Los límites se reinician a diario.

### XP por acción

| Aplicación | Acción | XP |
|---|---|---|
| Sub-GHz | Recibir y ver una señal | 1 |
| | Guardar una señal | 3 |
| | Grabar en RAW | 1 |
| | Add manually | 2 |
| | Enviar una señal guardada | 2 |
| | Usar el Frequency Analyzer | 1 |
| RFID de 125 kHz | Entrar en Read | 1 |
| | Lectura con éxito | 3 |
| | Guardar | 3 |
| | Emular | 2 |
| | Add manually | 2 |
| NFC | Entrar en Read | 1 |
| | Lectura con éxito | 3 |
| | Guardar | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emular | 2 |
| | Añadir una clave a mano | 2 |
| | Add manually y guardar o emular | 1 |
| Infrarrojos | Enviar una señal | 1 |
| | Aprendizaje con éxito | 3 |
| | Guardar | 3 |
| iButton | Entrar en Read | 1 |
| | Lectura con éxito | 3 |
| | Guardar | 3 |
| | Emular | 2 |
| | Add manually | 2 |
| Bad USB | Ejecutar un script | 3 |
| U2F | Autorización con éxito | 3 |
| GPIO | Abrir el USB-UART Bridge | 1 |
| Apps | Arrancar una aplicación externa | 2 |
| | Arrancar un juego | 1 |
| | Ganar un juego | 10 |

Cuando el delfín alcanza un nivel nuevo, el Flipper muestra una notificación de subida de nivel y las animaciones
del escritorio cambian.

## Dónde se guarda el estado

Los XP, el nivel y el humor del delfín se guardan en `.dolphin.state`, en el almacenamiento interno. Un
[reinicio de fábrica](/es/start/recovery#factory-reset) devuelve al delfín al nivel 1.
