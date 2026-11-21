---
title: Recuperación
order: 130
original: [https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://docs.flipper.net/zero/basics/firmware-update/storage-repair, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings]
sources: [flipper-docs, unleashed-docs, unleashed-src]
---
# Recuperación

Qué hacer cuando el Flipper se cuelga, no se actualiza, no muestra nada o has olvidado el PIN. Ve recorriendo los
pasos en orden, de los más suaves a los más drásticos.

## 1. Primero, reiniciar

- **Colgado:** mantén <kbd>←</kbd> + <kbd>BACK</kbd> unos 5 segundos.
- **Sigue colgado:** desconecta el USB y mantén <kbd>BACK</kbd> durante 30 segundos (corte de alimentación).
- **Batería agotada:** cárgalo varios minutos (o una hora) y vuelve a intentarlo.
- Desde un Flipper que funcione: **Settings → Power → Reboot → Reboot Flipper**.

Todas las combinaciones: [Combinaciones de teclas](/es/start/key-combos).

## 2. Recuperación del firmware desde el modo DFU {#firmware-recovery}

Usa esto cuando el firmware esté corrupto: la actualización falla, la pantalla muestra basura o nada, o los botones
no reaccionan. El bootloader DFU por USB flashea el firmware sin el sistema operativo del propio dispositivo.

### Paso 1: pon el Flipper en modo DFU (recuperación)

**Si el Flipper todavía funciona pero no se actualiza bien:**
1. **Main Menu → Settings → Power → Reboot → Firmware Upgrade**.
2. Confirma `Reboot to DFU Mode?` con <kbd>→</kbd> **Reboot**.

*o bien:* mantén <kbd>←</kbd> + <kbd>BACK</kbd> 5 s, suelta <kbd>BACK</kbd> y sigue manteniendo <kbd>←</kbd> hasta
que se encienda el **LED azul**.

**Si la pantalla no muestra nada y los botones no reaccionan:**
1. **Desconecta el cable USB.**
2. Mantén <kbd>OK</kbd> + <kbd>BACK</kbd> durante **30 segundos**. Aquí es normal que la pantalla esté en blanco.

Después conecta el Flipper al ordenador con un cable USB.

### Paso 2: comprueba que el ordenador ve un dispositivo DFU

| Sistema | Dónde mirar | Nombre |
|---|---|---|
| Windows | Administrador de dispositivos | **DFU in FS Mode** |
| macOS | Menú Apple → Acerca de este Mac → Informe del sistema → Hardware → USB (o `system_profiler SPUSBDataType`) | **DFU in FS Mode** |
| Linux | `lsusb` | **STMicroelectronics STM Device in DFU Mode** |

¿No se detecta? Prueba otro cable. Conéctalo directamente a un puerto USB de la placa base, no a un hub ni a un
adaptador. O saca la tarjeta SD, cárgalo una hora y conéctalo sin la tarjeta.

### Paso 3: repara

Cualquiera de las dos aplicaciones sirve. Las dos vuelven a flashear el Flipper por completo por USB.

**[qUnleashed](/es/mobile/qunleashed-app)** — Android, Windows, macOS y Linux (iOS no tiene USB):

1. Conecta el Flipper en modo DFU por USB.
2. Abre **Repair from DFU mode** e inícialo.

**qFlipper** — Windows, macOS y Linux:

1. Arranca **qFlipper**. Detecta el dispositivo DFU.
2. Pulsa **Repair**. qFlipper instala el firmware **oficial** por completo.

Después vuelve a instalar Unleashed: [Instalar Unleashed](/es/start/install).

::: tip Unleashed
El **Repair** de qFlipper restaura siempre el firmware oficial. No pasa nada: te deja una base limpia. Tras la
reparación, reinstala Unleashed con qUnleashed, con el Web Installer o con **Install from file**. La reparación no
toca los archivos de tu tarjeta SD.
:::

### Si qFlipper no puede repararlo

- Comprueba que qFlipper está bien instalado. En Windows, consulta la resolución de problemas de controladores de
  qFlipper.
- Desconecta el USB, reinicia con <kbd>←</kbd> + <kbd>BACK</kbd> y repite.
- Haz un corte de alimentación (<kbd>BACK</kbd> 30 s con el USB desconectado) y repite.
- Ejecuta qFlipper como administrador.
- Usa un puerto USB directamente de la placa base.
- Último recurso: flashea por SWD con un ST-Link (véase
  [Combinaciones de teclas](/es/start/key-combos#if-nothing-helps)).

## 3. Reparar el almacenamiento interno / reinicio de fábrica {#factory-reset}

Si las actualizaciones fallan porque el almacenamiento interno está lleno o dañado, devuelve el Flipper al estado de
fábrica. Esto borra el **almacenamiento interno**: ajustes, emparejamientos de Bluetooth, PIN y nivel del delfín.
**Los archivos de la tarjeta SD se conservan.**

::: info El almacenamiento interno en el firmware actual
En el firmware actual, el almacenamiento interno (`/int`) es **virtual** y vive en la carpeta oculta `/ext/.int/` de
la tarjeta SD. **Settings → Storage → About Internal Storage** muestra `Type: Virtual (/.int on SD)`.
:::

### Haz primero una copia de seguridad (opcional)

qFlipper → **Advanced controls** → **BACKUP** → elige una carpeta → **BACKUP**. Esto guarda el almacenamiento
interno como un `.tgz`. La tarjeta SD no se incluye, así que cópiala por separado.

### Reinicio desde el dispositivo

1. **Main Menu → Settings → Storage → Factory Reset**.
2. La pantalla pregunta `Confirm Factory Reset?`: *«Internal storage will be erased, data and settings will be
   lost!»*
3. Pulsa <kbd>→</kbd> **Erase** **5 veces**. La pantalla cuenta las pulsaciones que quedan.
4. El Flipper se reinicia y formatea el almacenamiento interno.

### Reinicio con qFlipper

**Advanced controls** → **ERASE** → **ERASE** → **CONTINUE** al terminar.

### Restaurar

qFlipper → **Advanced controls** → **RESTORE** → selecciona el `.tgz` de la copia → **RESTORE** → **CONTINUE**.

Si después de un reinicio la actualización sigue fallando, reinicia otra vez **sin** restaurar la copia de
seguridad, o haz la [recuperación del firmware](#firmware-recovery).

## 4. Restablecer un PIN olvidado {#reset-pin}

Si el Flipper está bloqueado con un PIN que no recuerdas:

1. **Desconecta el cable USB.**
2. Apaga el Flipper: mantén <kbd>BACK</kbd> → **Power Off**. Si no puedes, usa el paso siguiente pero manteniendo
   los botones 30–40 segundos.
3. Mantén <kbd>↑</kbd> + <kbd>BACK</kbd> unos 5 segundos. El Flipper arranca con <kbd>↑</kbd> pulsado y muestra la
   **pantalla de restablecimiento del PIN**.
4. **Mantén <kbd>→</kbd>** hasta que la barra de progreso se llene para confirmar el restablecimiento. Pulsa
   <kbd>↓</kbd> en su lugar para salir sin restablecer.
5. El Flipper se reinicia.

Esto devuelve la configuración de usuario (registros del RTC, almacenamiento interno con los ajustes y el PIN) al
estado de fábrica. **Los archivos de usuario de la tarjeta microSD se conservan.**

## 5. ¿Sigue muerto?

- Cárgalo una hora y vuelve a intentarlo.
- Desconecta y vuelve a conectar la batería (hay que abrir la carcasa).
- Flashéalo por SWD con un ST-Link u otro programador.

Si nada de esto funciona, el problema es de hardware, no de software.

## Relacionado

- [Combinaciones de teclas](/es/start/key-combos)
- [Instalar Unleashed](/es/start/install)
- [Aplicación complementaria qUnleashed](/es/mobile/qunleashed-app)
- [qFlipper](/es/mobile/qflipper)
