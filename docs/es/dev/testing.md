---
title: Pruebas de integración
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Pruebas de integración

Además de las [pruebas unitarias](/es/dev/unit-tests), el firmware tiene un **plan manual de pruebas de
integración**: casos de prueba paso a paso agrupados por subsistema, cada uno con su resultado esperado. Está escrito
para los mantenedores del repositorio, pero resulta igual de útil si compilas tu propio firmware y quieres
comprobarlo antes de usarlo o compartirlo.

Esta página resume el plan. Las listas completas de pasos están en el repositorio de Unleashed, en
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Qué probar y cuándo

- **Prueba lo que has cambiado, más las regresiones relacionadas.** Prueba el comportamiento nuevo y vuelve a
  ejecutar algunos casos existentes del mismo subsistema. Ejemplo: al añadir un protocolo Sub-GHz, pruébalo y prueba
  también algunos protocolos ya existentes.
- **Omite los subsistemas no relacionados.** No hace falta probar NFC si solo ha cambiado Sub-GHz.
- **Prueba todo si el cambio afecta al núcleo** — si algo global ha cambiado, ejecuta todos los casos en orden.

Cuándo: **antes de aceptar pull requests** y **antes de una release candidate**.

## Patrón de prueba común para llaves y tarjetas

Los casos de protocolos de RFID, iButton y NFC reutilizan los mismos «pasos compartidos»:

1. **Leer** el original — los datos coinciden con el original.
2. **Emular** — leer la llave emulada con un segundo Flipper; los datos son idénticos.
3. **Guardar** — se guarda con el nombre dado; la escena cambia al directorio *Saved*.
4. **Escribir** en un chip virgen — aparece una escena de éxito.
5. **Leer el chip virgen escrito** — los datos son idénticos a la llave guardada.

Por eso muchos casos necesitan **un segundo Flipper**, lectores reales y chips vírgenes (T5577, RW2004/RW1990, etc.).

## Casos de prueba por subsistema

### General (35 casos)

| Área | Qué se comprueba |
|---|---|
| BLE | Bluetooth activo después de reiniciar; emparejamiento con la app móvil y nombre correcto del Flipper; reemparejamiento con un segundo teléfono |
| U2F | Registrar y autenticar una llave en el sitio de demostración WebAuthn de Yubico |
| Settings | Código PIN, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive y explorador de archivos | Tarjeta SD con muchos archivos: <kbd>↓</kbd> en el escritorio abre el Archive; cada pestaña (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) muestra sus archivos; ejecutar, renombrar y borrar llaves |
| Tarjetas y protocolos | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Actualización de fábrica | Con qFlipper en macOS, Windows 11 y Ubuntu; con las apps de Android e iOS; con la web de Flipper Lab |
| Aprovisionamiento de región | Los mismos seis canales que la actualización de fábrica, más el propio ajuste de región |
| Apps | Apps del pack Base, scripts de JS y el menú del botón Arriba |
| Cumplimiento normativo | Todas las pantallas de cumplimiento se muestran correctamente |

### CLI (3 casos)

- **Comandos de control:** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode, `gpio set PA7 1` enciende
  un LED de la devboard), `led b 255`, `vibro 1` / `vibro 0`.
- **Comandos de información:** conectar con `minicom -D /dev/ttyACM0 -b 230400` o PuTTY; `log debug` mientras se usa
  el dispositivo, parar con <kbd>Ctrl</kbd>+<kbd>C</kbd>; comparar `device_info` / `!` con la pantalla de información
  del firmware (mantener <kbd>↓</kbd> en el escritorio 3 s); `bt hci_info`; `date`; `help` / `?`; `free`;
  `free_blocks`.
- **Comandos de almacenamiento:** `storage info /ext`, `storage format /ext` (rechazar y después confirmar),
  información con y sin tarjeta; `factory_reset` — responder `n` no hace nada, `y` borra los ajustes pero
  **conserva los datos de la tarjeta SD y la hora**.

Valores de referencia de `bt hci_info` según el plan:

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 casos)

| Caso | Comprobaciones clave |
|---|---|
| Read RAW | Grabar en 315, 433 y 868 MHz, incluido un mando cifrado (con código rodante) como un Came Atomo; reproducirlo en los receptores del banco de pruebas |
| Frequency Analyzer | Muestra la frecuencia correcta de distintos mandos |
| Módulo externo | CC1101 externo (módulo de 433,92 MHz): el icono cambia a externo y la señal de Read RAW es más fuerte que con el interno; volver al interno funciona. No desconectes nunca el módulo mientras está en uso — el Flipper puede quedarse colgado |
| Archivos guardados | Guardar señales decodificadas y RAW, añadirlas a favoritos y enviarlas desde ahí, renombrarlas (se mantienen en favoritos) y borrarlas |
| Recepción / transmisión | Leer en 315,000, 433,920 y 868,350 MHz, y después con el salto de frecuencia activado; enviar las llaves guardadas — los relés del banco (o un segundo Flipper) reaccionan |
| Add Manually | Crear señales manualmente |

### NFC (7 casos)

| Caso | Comprobaciones clave |
|---|---|
| Desbloquear NTAG/Ultralight | *Auth as* con los dos tipos, aviso de tipo de tarjeta incorrecto, introducción manual de la contraseña; las tarjetas guardadas aparecen en *Saved* tras unos 1,5 s |
| Detect Reader | Recoger nonces de un lector (por ejemplo otro Flipper); después, la pantalla del código QR al pulsar <kbd>OK</kbd> es legible |
| Emulación | Legible por varios lectores, incluidos un Flipper a 10 mm y un Proxmark |
| Lectura | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, tarjetas bancarias EMV |
| Temporización | Comparar la temporización de la emulación de Ultralight y Classic con una referencia usando un Proxmark 3 |
| Add Manually | Crear y guardar tarjetas de todos los tipos y después emularlas |
| Acciones adicionales | *Read Specific Card Type*, *MIFARE Classic Keys* (añadir/borrar claves, el botón *List*), *Unlock SLIX* con contraseña |

Comandos de Proxmark usados en la prueba de temporización:

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### RFID de 125 kHz (9 casos)

Casos de protocolo con los pasos compartidos para **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass),
Indala26 y Troyka/Podorozhnik**, más lectura, escritura en **T5577**, Add Manually y emulación.

### iButton (9 casos)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral** y **Metakom**: leer, guardar, Add Manually, emular (leídas por
distintos dispositivos), escribir en un chip virgen **RW2004** y volver a leerlo, editar y borrar llaves.

### Infrarrojos (3 casos)

- **Biblioteca universal** — mandos de TV, audio y aire acondicionado: la función de encendido y las demás funcionan.
- **Learn new remote** — añadir y borrar mandos y botones, renombrarlos, transmitir los botones editados.
- **Mandos guardados** — añadir botones a un mando existente, controlar dispositivos desde **al menos 5 m**, borrar
  todos los botones y todos los mandos.

### Bad USB (2 casos)

En macOS y Windows: la lista de scripts se muestra; el script de demostración se ejecuta con la distribución EN y
también después de cambiar la distribución; el script de «qFlipper download» abre un terminal y descarga qFlipper;
cambiar al modo **BLE** (con el Bluetooth activado) empareja con el ordenador y el script se vuelve a ejecutar.

### GPIO (1 caso)

`GPIO → Manual Control` con la devboard ST-Link insertada: los LED siguen a los pines; activar los 5 V enciende los
LED de alimentación.

### GoodFAPs — apps oficiales (10 casos)

| App | Comprobaciones clave |
|---|---|
| PicoPass | Leer una tarjeta, guardarla y comprobar que arranca el *Elite Dictionary Attack* |
| Weather Station | Lee una estación meteorológica simulada por un segundo Flipper en distintas frecuencias |
| Apps del catálogo | Instalar desde la app móvil o la web, icono y nombre correctos, iniciar y salir, actualizar, desinstalar (desde la app, la web y el explorador de archivos) |
| AVR Flasher | Dump AVR, Flash AVR, programador ISP con `avrdude` |
| Video Game Module | Insertar el módulo → mensaje de inicialización e icono en la barra de estado; el HDMI replica la pantalla; «Air Arkanoid» usa el acelerómetro |
| Tools | Clock (a pantalla completa, con el formato de los ajustes); NFC/RFID Detector detecta los dos tipos de campo |
| Signal Generator | Generadores de PWM y de reloj en distintos pines, frecuencias y divisores |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (con aviso de riesgo), *Wipe* |
| SPI Mem Manager | Leer, escribir y borrar un chip de flash SPI |
| Flasheo del VGM | App VGM Tool: *Install official firmware*, instalar desde un archivo de la SD y la vía manual (botón Boot + almacenamiento masivo USB) |

Conexiones de AVR Flasher según el plan:

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Comprobación de la lectura de fuses (sustituye `m2560` por tu chip, por ejemplo `m328p`, y el puerto COM):

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
El plan procede del firmware oficial. En Unleashed, prueba también los añadidos exclusivos de Unleashed del
subsistema que hayas cambiado — por ejemplo los protocolos Sub-GHz adicionales y el
[modo contador](/es/subghz/counter-mode), o las apps extra de `applications/system/` (Remote Analyzer, Nice-O-Code,
Sec+ PIN, Seed Capturer, el editor RAW de Sub-GHz, T5577, SIM800…).
:::

## Páginas relacionadas

- [Pruebas unitarias](/es/dev/unit-tests)
- [Interfaz de línea de comandos](/es/dev/cli)
- [Compilar el firmware](/es/dev/build)
