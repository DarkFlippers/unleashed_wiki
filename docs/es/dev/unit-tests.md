---
title: Pruebas unitarias
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Pruebas unitarias

Las pruebas unitarias alimentan el código de una función con entradas conocidas y comprueban que los resultados son
correctos. Son esenciales para tener un código robusto y libre de fallos.

El firmware contiene una app aparte, **`unit_tests`** (`applications/debug/unit_tests`), que se ejecuta **en el propio
Flipper** — así las pruebas usan el hardware real y se descartan las diferencias relacionadas con la plataforma.

Cuando contribuyas al firmware, incluye pruebas unitarias con las funciones nuevas siempre que sea posible, y ejecuta
las existentes para asegurarte de que tu cambio no introduce regresiones.

## Ejecutar las pruebas

1. **Compila el firmware con el conjunto de apps de pruebas:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` es obligatorio
   `fbt_options.py` usa por defecto `DEBUG=1`, y una imagen de depuración ya no cabe por debajo de la región de flash
   de la pila de radio — el empaquetado se detiene con
   `Firmware image overlaps C2 region and is not programmable!`. Desde la API 88.23, una imagen de depuración es unos
   7 KB demasiado grande para este conjunto de apps (10 KB para el conjunto por defecto), así que recortar las pruebas
   no ayuda. (`COMPACT=1` ya es el valor por defecto; se escribe explícitamente para que coincida con los demás
   comandos.)

   Ten en cuenta que `DEBUG=0` elimina en compilación las llamadas a `furi_assert()`, así que las aserciones del
   código que se está probando no se activarán. `furi_check()` y las aserciones de minunit no se ven afectadas.
   :::

   El conjunto de apps `unit_tests` contiene: `basic_services`, `updater_app`, `radio_device_cc1101_ext`,
   `unit_tests`, `infrared` y `archive`.

2. **Flashea el firmware incluyendo los recursos de la tarjeta SD** (`build/latest/resources`) — por ejemplo,
   instalando el `.tgz` generado en `dist/` con qFlipper, o con
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Los recursos de las pruebas deben acabar en
   la tarjeta SD.
3. **Abre una sesión de [CLI](/es/dev/cli)** y ejecuta:

   ```
   unit_tests
   ```

**Resultado esperado:** las suites se ejecutan una tras otra y después aparece un informe como este:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Si ves `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, los recursos de la
tarjeta SD no se han instalado — repite el paso 2 con los recursos.

Para ejecutar **una sola** prueba y omitir el resto, pasa su nombre:

```
unit_tests test_infrared
```

Las demás suites se omiten (`Skipping …`); un nombre incorrecto da `No suite named …`. Los nombres de las pruebas
coinciden con los ID de app (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`, `test_lfrfid`,
…) definidos en
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam).

::: info
Esta es una compilación especial del firmware sin las apps habituales. Vuelve a instalar una compilación normal cuando
termines.
:::

## Añadir pruebas unitarias

### Punto de entrada

Todas las pruebas se ejecutan desde la app «madre» `unit_tests`. El código de las pruebas se empaqueta como una app de
tipo `PLUGIN` en un subdirectorio de `tests/` dentro de `unit_tests`, y se referencia en el `application.fam` común.
Copia la estructura de una prueba existente.

### Recursos de las pruebas

Algunas pruebas necesitan datos externos («assets»). Residen en
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
cada una en su propio subdirectorio. Los recursos pueden ser de cualquier tipo: texto plano, Flipper Format (FFF),
binario, etc.

### Ejemplo: protocolos de infrarrojos

Cada protocolo de infrarrojos tiene un conjunto de pruebas unitarias, así que añade uno cuando añadas un protocolo
nuevo:

1. Crea `test_<your_protocol_name>.irtest` en el
   [directorio de recursos de infrarrojos](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Rellénalo con datos de prueba (véase más abajo).
3. Añade el código de la prueba a
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Compila e instala el firmware con los recursos, después ejecuta las pruebas y comprueba que pasan.

#### Formato de los datos de prueba

Cada prueba de infrarrojos tiene tres secciones:

| Sección | Qué hace |
|---|---|
| `decoder` | Toma una señal en bruto y produce mensajes decodificados |
| `encoder` | Toma mensajes decodificados y produce una señal en bruto |
| `encoder_decoder` | Codifica mensajes decodificados a señal en bruto y después los vuelve a decodificar |

Los archivos `.irtest` son [archivos `.ir`](/es/infrared/file-format) normales con algunos añadidos:

- las señales de entrada del decodificador se llaman `decoder_input_N` (N = número de secuencia de la prueba) y la
  salida esperada, `decoder_expected_N`;
- en las pruebas del codificador los dos se intercambian;
- los datos decodificados son un **array**, porque una misma señal en bruto puede decodificarse en varios mensajes —
  un único mensaje es un array de tamaño 1.

Usa los archivos `.irtest` existentes como ejemplos de sintaxis.

#### Grabar señales en bruto

Abre una sesión de CLI y ejecuta:

```
ir rx raw
```

Apunta el mando al Flipper y pulsa botones. Los datos en bruto se imprimen en un formato listo para usar.

## Páginas relacionadas

- [Pruebas de integración](/es/dev/testing)
- [Flipper Build Tool (fbt)](/es/dev/fbt)
- [Interfaz de línea de comandos](/es/dev/cli)
