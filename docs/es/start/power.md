---
title: Energía y batería
order: 80
original: [https://docs.flipper.net/zero/basics/power, https://docs.flipper.net/zero/basics/reboot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/power_settings_app, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/power]
sources: [flipper-docs, unleashed-src]
---
# Energía y batería

El Flipper Zero tiene una batería Li-Po integrada de **2100 mAh**. Puede aguantar hasta un mes en reposo y se carga
por USB-C en unas dos horas.

## Encendido y apagado

- **Encender:** mantén <kbd>BACK</kbd> unos 3 s. Un Flipper completamente descargado se enciende solo en cuanto
  conectas el USB.
- **Apagar:** mantén <kbd>BACK</kbd> en el escritorio. Aparece la pantalla **Turn Off Device?**: <kbd>→</kbd>
  **Power Off** lo apaga y <kbd>←</kbd> **Battery** abre la información de la batería. También puedes usar
  **Main Menu → Settings → Power → Power OFF**.

![Turn Off Device? con el delfín llorando, Battery en el botón izquierdo y Power Off en el derecho](/screens/settings/power_off.png)

## Carga

Conecta el cable USB-C a un cargador o a un ordenador. El icono de la batería muestra un rayo mientras carga. La
entrada de carga es de 5 V / 1 A, así que una carga completa tarda unas 2 horas.

::: warning Almacenamiento prolongado
Si no vas a usar el Flipper durante mucho tiempo, cárgalo hasta un **50 %** aproximadamente antes de apagarlo.
Guardarlo completamente descargado daña la batería. Mantenlo entre 0 y 40 °C.
:::

## Settings → Power

| Elemento | Qué hace |
|---|---|
| **Battery Info** | Porcentaje de carga, tensión, corriente, temperatura y salud de la batería |
| **Reboot** | **Firmware Upgrade** (reiniciar en modo DFU) o **Reboot Flipper** (reinicio normal). Confirma con <kbd>→</kbd> **Reboot** |
| **Power OFF** | Apagar el dispositivo |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min`: apagar tras ese tiempo de inactividad |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%`: dejar de cargar en ese nivel |

![Settings → Power: Battery Info, Reboot, Power OFF, Auto PowerOff en OFF, Limit Charge en OFF](/screens/settings/power.png)

::: tip Limit Charge
Limit Charge resulta útil si el Flipper pasa la mayor parte del día conectado al USB, por ejemplo como cacharrito de
escritorio. Mantener la batería por debajo del 100 % alarga su vida útil.
:::

## Pantalla Battery Info

La pantalla muestra un mensaje distinto según el estado:

| Encabezado | Significado |
|---|---|
| `Yummy!` / `Charging at` | Cargando. Muestra la tensión del USB y la corriente de carga |
| `Om-nom-nom!` / `Consumption is` | Funcionando con batería, con el consumo actual. `Oh no!` y `mA!` indican un consumo alto |
| `Charged!` | USB conectado, sin cargar (batería llena) |
| `Charged!` / `Limited to` | USB conectado y con un límite de tensión de carga distinto del predeterminado (se muestra en V) |
| `Napping...` | Con batería, con un consumo de corriente casi nulo |

También muestra el porcentaje de batería, la tensión, la temperatura (°C o °F, según **Settings → System → Units**) y
el porcentaje de **salud** de la batería.

![Battery Info: Om-nom-nom! Consumption is 18 mA, 100 %, 29 °C, 4,1 V, salud 100 %](/screens/settings/battery_info.png)

## Consumo

| Modo | Corriente típica |
|---|---|
| Reposo (método de suspensión Default) | ~1,5 mA |
| Reposo (método de suspensión Legacy) | ~9 mA |
| Activo, con retroiluminación | hasta ~30 mA (hasta ~50 mA con una tarjeta SD mala) |
| Radio activa | hasta ~400 mA |
| Radio + módulo externo | hasta ~2 A |

El **Sleep Method** está en **Settings → System**. `Default` ahorra energía. `Legacy` consume más, pero puede ayudar
si ves cuelgues en reposo.

La suspensión requiere **Debug** = `OFF` (**Settings → System**) y **Listen UART** = `None`
(**Settings → Expansion Modules**). Si no, el dispositivo no puede dormirse y la batería se agota más rápido.

## Consejos para que la batería dure más

- Mantén el firmware actualizado.
- Desactiva el Bluetooth cuando no lo necesites (Lock Menu → **Turn Bluetooth Off**).
- Baja **LCD Backlight** y **Backlight Time** en **LCD and Notifications**.
- Usa una tarjeta microSD de marca y de buena calidad.
- Configura **Auto PowerOff**.
- Si la batería se agota rápido, comprueba la corriente en **Battery Info**.

## Especificaciones de alimentación

| Parámetro | Valor |
|---|---|
| Capacidad de la batería | 2100 mAh |
| Tensión de funcionamiento de la batería | 3,3–4,2 V |
| Tiempo de carga | ~2 horas |
| Tensión / corriente de carga | 5 V, 1 A |
| Conector | USB Type-C |
| Corriente máxima del USB, incluidos los dispositivos conectados | 3 A |

## Relacionado

- Reinicios y combinaciones de reinicio: [Combinaciones de teclas](/es/start/key-combos)
- El dispositivo no se enciende: [Recuperación](/es/start/recovery)
