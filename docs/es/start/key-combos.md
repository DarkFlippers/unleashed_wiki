---
title: Combinaciones de teclas
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Combinaciones de teclas

A veces el Flipper deja de responder por un problema de software. Estas combinaciones de botones lo reinician a
nivel de hardware o lo arrancan en modo DFU (actualización de firmware), sin ayuda del firmware colgado.

## Referencia rápida

| Objetivo | Combinación | USB |
|---|---|---|
| Reiniciar un Flipper colgado | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | cualquiera |
| Corte de alimentación | <kbd>BACK</kbd>, 30 s | **desconectado** |
| DFU por el bootloader del Flipper (con indicación) | <kbd>←</kbd> + <kbd>BACK</kbd>, suelta <kbd>BACK</kbd> y mantén <kbd>←</kbd> hasta el LED azul | cualquiera |
| DFU por el bootloader de ST (sin indicación) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, suelta <kbd>BACK</kbd> y <kbd>←</kbd> | cualquiera |
| Pantalla de restablecimiento de PIN / ajustes | mantén <kbd>↑</kbd> mientras el Flipper arranca | — |

## Combinaciones básicas

### Reinicio por hardware

1. Mantén pulsados <kbd>←</kbd> y <kbd>BACK</kbd> un par de segundos.
2. Suelta los dos.

Esto lleva a nivel bajo la línea de reinicio del MCU. Recorrido: teclas → DD8 (NC7SZ32M5X, puerta OR) → DD1
(STM32WB55, MCU).

**No funciona si:** el bloque de depuración del MCU está activo y mantiene la línea de reinicio desde dentro.

### Corte de alimentación por hardware

1. Desconecta el cable USB y cualquier alimentación externa. Comprueba dos veces que el USB está realmente
   desconectado.
2. Mantén pulsado <kbd>BACK</kbd> durante **30 segundos**. Esto solo funciona con el USB desconectado.
3. Suelta <kbd>BACK</kbd>.

Esto apaga y vuelve a encender la línea de alimentación SYS a través del chip de carga DD6 (bq25896).

**No funciona si:** hay alimentación conectada al USB o a 5V_ext.

### DFU por software

Mantén <kbd>←</kbd> mientras el Flipper arranca. Entra en modo DFU a través del **bootloader del Flipper**.

**No funciona si:** el bootloader del Flipper está dañado o falta.

### DFU por hardware

Mantén <kbd>OK</kbd> mientras el Flipper arranca. Entra en modo DFU a través del **bootloader de ST** integrado en
el MCU.

**No funciona si:** los Option Bytes están dañados o configurados para ignorar la tecla <kbd>OK</kbd>.

## Combinaciones de DFU

### Reinicio por hardware + DFU por software

1. Mantén <kbd>←</kbd> + <kbd>BACK</kbd> un par de segundos.
2. Suelta <kbd>BACK</kbd>.
3. El dispositivo entra en DFU **con indicación**: LED azul y pantalla de DFU.
4. Suelta <kbd>←</kbd>.

**No funciona si:** el bloque de depuración del MCU mantiene la línea de reinicio, o el bootloader del Flipper está
dañado o falta.

### Reinicio por hardware + DFU por hardware

1. Mantén <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> un par de segundos.
2. Suelta <kbd>BACK</kbd> y <kbd>←</kbd>.
3. El dispositivo entra en DFU **sin indicación**. La pantalla se queda en blanco. Es normal.

**No funciona si:** el bloque de depuración del MCU mantiene la línea de reinicio, o los Option Bytes están dañados
o configurados para ignorar <kbd>OK</kbd>.

### Corte de alimentación por hardware + DFU por software

1. Desconecta el USB y cualquier alimentación externa.
2. Mantén <kbd>BACK</kbd> + <kbd>←</kbd> durante 30 segundos.
3. Suelta <kbd>BACK</kbd>.
4. El dispositivo entra en DFU con indicación (LED azul + pantalla de DFU).
5. Suelta <kbd>←</kbd>.
6. Conecta el USB.

**No funciona si:** hay alimentación conectada al USB o a 5V_ext, o el bootloader del Flipper está dañado o falta.

### Corte de alimentación por hardware + DFU por hardware

1. Desconecta el USB y cualquier alimentación externa.
2. Mantén <kbd>BACK</kbd> + <kbd>OK</kbd> durante 30 segundos.
3. Suelta <kbd>BACK</kbd> y <kbd>OK</kbd>.
4. El dispositivo entra en DFU sin indicación.
5. Conecta el USB.

**No funciona si:** hay alimentación conectada al USB o a 5V_ext, o los Option Bytes están dañados o configurados
para ignorar <kbd>OK</kbd>.

## Qué hacer en modo DFU

Conecta el Flipper a un ordenador. Aparece como **DFU in FS Mode** (Windows/macOS) o como
**STMicroelectronics STM Device in DFU Mode** (`lsusb` en Linux). Después repara el firmware con qFlipper:
[Recuperación](/es/start/recovery#firmware-recovery).

## Si nada funciona {#if-nothing-helps}

- Asegúrate de que la batería está cargada: déjalo una hora en el cargador.
- Desconecta la batería y vuelve a conectarla (hay que abrir la carcasa).
- Flashea el dispositivo con un ST-Link u otro programador SWD.

Si después de todo esto el dispositivo sigue sin funcionar, el problema **no es de software**.
