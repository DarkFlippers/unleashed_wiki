---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

El **Video Game Module** (VGM) es un accesorio oficial construido en torno al **Raspberry Pi RP2040**. Se conecta al
conector GPIO y añade:

- **Video Out**: duplica la pantalla del Flipper en un televisor o monitor (señal DVI-D, 640×480);
- un **sensor de movimiento de 6 ejes** (TDK ICM-42688-P: giroscopio de 3 ejes + acelerómetro) para controles por
  giroscopio;
- un **puerto USB-C** conectado al RP2040 (para flashear, o para que lo use un firmware propio);
- una **salida de 14 pines** con el GPIO del RP2040;
- **botones BOOT / RESET** (se pulsan con un clip) para el modo de flasheo UF2 y el reinicio;
- un LED RGB en la parte superior.

También puede funcionar como placa RP2040 independiente, compatible con los proyectos de la Raspberry Pi Pico.

![Botones y conectores del Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Instalarlo y conectarlo a un televisor

1. **Encaja el módulo.** Viene con un protector de silicona pensado para un Flipper *sin* funda. Si tu Flipper lleva
   funda de silicona, quítale el protector al módulo (o la funda al Flipper).
2. **Firmware.** El módulo necesita firmware del Flipper 0.98.3 o posterior; las releases actuales de Unleashed
   cumplen.
3. **Comprueba el ajuste del UART:** `Main Menu → Settings → Expansion Modules → Listen UART` debe estar en
   **`USART`**. Con cualquier otro valor el módulo no se detecta. (Véase
   [Módulos de expansión](/es/gpio/expansion-modules).)
4. Conecta el módulo (con el Flipper apagado) y enciéndelo. El Flipper detecta el módulo y lo prepara
   automáticamente.
5. Conecta el cable del televisor al puerto **Video Out** del módulo y selecciona esa entrada en el televisor.

### «Video Game Module not initialized»

Este texto en el televisor significa que el módulo no está hablando con un Flipper: el firmware es demasiado
antiguo, `Listen UART` no está en `USART`, o el módulo está alimentado (por ejemplo, por USB) sin un Flipper
conectado.

## Juegos y aplicaciones

El sensor de movimiento lo usan aplicaciones del Flipper Apps Catalog, por ejemplo
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) y [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(ratón por giroscopio para el ordenador).

::: tip Unleashed
El motor de JavaScript de Unleashed incluye un módulo `vgm` (característica JS `vgm`): `getPitch()`, `getRoll()`,
`getYaw()` y `deltaYaw(angle, timeout)` leen la orientación del módulo desde un script y devuelven `undefined` si
no hay ningún VGM conectado. Consulta la sección [Desarrollo](/es/dev/) para las aplicaciones en JavaScript.
:::

## Actualizar el firmware del módulo

Las actualizaciones se instalan con la aplicación **Video Game Module Tool** (del Flipper Apps Catalog). Su menú:

- `Install Official Firmware`: el firmware oficial más reciente del módulo, incluido con la aplicación;
- `Install Firmware from File`: un `.uf2` propio desde la tarjeta SD.

Para actualizar:

1. Instala (o **actualiza primero**) Video Game Module Tool: en la aplicación móvil de Flipper, ve a **Apps**, busca
   *Video Game Module Tool* y toca **INSTALL** / **UPDATE**. Un firmware nuevo del módulo llega con una versión
   nueva de la aplicación, así que actualiza siempre la aplicación antes de actualizar el módulo.
2. Conecta el módulo al Flipper.
3. Abre `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Selecciona `Install Official Firmware` y confirma con `Install` (<kbd>→</kbd>).
5. Espera a que aparezca **Video Game Module Updated**.

## Firmware propio

El módulo puede ejecutar tu propio firmware para el RP2040.

### Desde el Flipper Zero

Te permite tener varios firmwares del módulo en la tarjeta SD y cambiar entre ellos sin ordenador.

1. Copia el archivo `.uf2` a la tarjeta SD del Flipper (por ejemplo, con [qFlipper](/es/mobile/qflipper):
   `File manager → SD Card`, crea una carpeta y sube el archivo).
2. Conecta el módulo y abre `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Selecciona el archivo y confirma con `Install` (<kbd>→</kbd>). Espera a que aparezca
   **Video Game Module Updated**.

::: warning Limitaciones de UF2 al instalar desde el Flipper
- No se admiten los bloques que no sean de flash.
- Las cargas útiles de los bloques deben ser de exactamente 256 bytes.
- Las direcciones de destino de las cargas útiles deben estar alineadas a 256 bytes, sin huecos.
- No se admiten los contenedores de archivos ni las etiquetas de extensión.
:::

### Desde un ordenador

1. Desconecta el módulo del Flipper y del USB.
2. Mantén pulsado el botón **BOOT** del módulo con un clip.
3. Conecta el módulo al ordenador con USB-C. Se monta como una unidad USB llamada **RPI-RP2**. Suelta **BOOT**.
4. Arrastra el archivo `.uf2` a **RPI-RP2**. El módulo se reinicia y se desmonta por sí solo.

## Detalles de hardware (para uso independiente)

### GPIO del RP2040

- Los GPIO **8–15** y **18–20** se usan para la salida de vídeo y no están disponibles en los conectores.
- Los GPIO **0–7, 16, 17, 21, 22, 26–28** están en los conectores (como en una Raspberry Pi Pico). Los GPIO **2–7**
  están además conectados al sensor de movimiento.
- Los GPIO **23–25 y 29** (de uso interno en una Pico) están libres en el VGM y accesibles en la salida de 14 pines.

![Patillaje de la salida de 14 pines del Video Game Module](/img/remote/b030c6a0375c6254.png)

![Patillajes del Video Game Module y de la Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Periféricos disponibles para el RP2040

- **Video Out:** vídeo y sonido a un televisor o monitor, además de intercambio de datos por el
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** dispositivo o anfitrión USB (sin USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **Salida GPIO:** 11 pines GPIO con protección contra ESD.
- **Conector al Flipper Zero:** los pines 13 y 14 del Flipper, plenamente funcionales; los pines 2–7, con
  funcionalidad limitada (compartidos con la IMU). Con protección contra ESD.
- **LED RGB**, controlado desde el GPIO del RP2040.

### Alimentación

- 5 V por USB-C en modo independiente;
- 3,3 V (pin 9) o 5 V (pin 1) desde el Flipper.

Alimentarlo por USB-C y desde el Flipper al mismo tiempo es seguro para el módulo y para ambas fuentes.

Los esquemas, los planos de montaje del PCB y los patillajes en PDF están en la página oficial
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## Relacionado

- [Módulos de expansión](/es/gpio/expansion-modules)
- [Patillaje GPIO](/es/gpio/pinout)
- [Módulos externos](/es/gpio/external-modules)
