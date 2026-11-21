---
title: Preguntas frecuentes
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# Preguntas frecuentes

## General

### Acabo de comprar un Flipper Zero. ¿Por dónde empiezo?

Lee [Primer arranque](/es/start/first-start) y después [Instalar Unleashed](/es/start/install). La web oficial
[flipperzero.one](https://flipperzero.one/) y [docs.flipper.net](https://docs.flipper.net/) cubren los conceptos
básicos del firmware de serie.

### ¿Firmware oficial, Unleashed u otro fork?

Si no lo tienes claro, empieza con el firmware oficial. Si necesitas más funciones, o quieres Sub-GHz sin bloqueos
regionales, instala **Unleashed**: un fork del firmware oficial con muchas funciones nuevas y aplicaciones
preinstaladas (prueba el build `e`). Existen otros forks basados en Unleashed para quien quiera experimentar más con
la interfaz. También puedes hacer tu propio fork.

**Antes de informar de un fallo, comprueba qué firmware usas.** No informes de problemas de otros forks ni del
firmware de serie en el repositorio ni en los chats de Unleashed.

### ¿Dónde puedo ver las diferencias con el firmware oficial?

En [Qué añade Unleashed](/es/start/unleashed-features).

### ¿Qué build debería instalar? ¿Qué significan `e` y `c`?

`e` = base + aplicaciones extra de la comunidad, sin sufijo = aplicaciones base, `c` = sin aplicaciones de la
comunidad. Las aplicaciones de sistema integradas están en todos ellos. Detalles:
[Instalar Unleashed](/es/start/install#which-file-to-download).

### ¿Qué son los builds dev?

Compilaciones automáticas de los últimos commits de la rama `dev` que todavía no se han publicado como release.
**Pueden tener fallos.** Se consiguen en el Web Installer (Dev), en
[dev.unleashedflip.com](https://dev.unleashedflip.com), en Telegram [@kotnehleb](https://t.me/kotnehleb) o en el
canal de Discord `unleashed-development`. El build anterior se borra cuando se sube uno nuevo, y los antiguos solo
quedan como archivos en el canal de Telegram. ¿Has encontrado un fallo?
[Infórmalo](https://github.com/DarkFlippers/unleashed-firmware/issues).

### ¿Qué es el servidor de actualizaciones de Unleashed?

`https://up.unleashedflip.com/directory.json`. Usa el mismo formato que el oficial, pero las aplicaciones oficiales
no se pueden cambiar a él sin recompilarlas. Puedes pasárselo a **uFBT** para compilar aplicaciones para el SDK de
Unleashed. Se mantiene en línea y se actualiza automáticamente.

### ¿Qué aplicaciones vienen incluidas?

Las aplicaciones de sistema integradas, más el paquete base (y el paquete extra en los `e`) de
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).
Véase [Qué añade Unleashed](/es/start/unleashed-features#built-in-apps).

### ¿Cómo puedo apoyar el proyecto?

Consulta la
[sección de apoyo](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project) del
ReadMe. Incluso un simple «gracias» ayuda. Todas las compilaciones son y seguirán siendo gratuitas y de código
abierto.

## Después de instalar

### La retroiluminación no funciona después de instalar Unleashed {#backlight-does-not-work}

Has activado el ajuste del **mod de retroiluminación RGB**, que está pensado solo para los Flipper con el mod de
hardware RGB. Ve a **Settings → LCD and Notifications → RGB Mod Settings** y pon **RGB backlight installed** en
`OFF`. Si *sí* tienes el mod, actívalo ahí en su lugar.

### La aplicación móvil no se conecta (después de instalar Unleashed o de cambiar el nombre)

1. En la aplicación móvil, toca **Forget Flipper**.
2. En los **Ajustes → Bluetooth** del móvil, busca el Flipper y elige **Olvidar este dispositivo**.
3. En el Flipper: **Settings → Bluetooth → Unpair All Devices** y confirma.
4. Asegúrate de que el Bluetooth del Flipper está en `ON` y vuelve a emparejarlo desde la aplicación.

### Mis ajustes (PIN, favoritos, escritorio…) se han restablecido después de una actualización

Vuelve a configurarlos. Un archivo de ajustes solo se restablece cuando una release cambia su estructura, lo que
ocurre en releases concretas, no cada vez. Consulta los changelogs de las releases posteriores a tu versión
anterior.

### El Flipper no se conecta a Chrome ni al Web Installer

Lo más habitual es que **qFlipper esté abierto**, o que haya una segunda página de Flipper Lab o web conectada. Solo
un programa puede usar el puerto. Cierra los demás y vuelve a intentarlo. Usa un navegador basado en Chromium.

## Problemas

### El Flipper se ha colgado, se ha quedado congelado o no responde

Mantén <kbd>←</kbd> + <kbd>BACK</kbd> para reiniciarlo. Más información:
[Combinaciones de teclas](/es/start/key-combos).

### El Flipper no funciona en absoluto. ¿Cómo restauro el firmware?

[Recuperación → Recuperación del firmware](/es/start/recovery#firmware-recovery).

### He olvidado mi PIN

Desconecta el USB, apaga el Flipper, mantén <kbd>↑</kbd> + <kbd>BACK</kbd> unos 5 s hasta que aparezca la pantalla
de restablecimiento y después mantén <kbd>→</kbd>. Los ajustes y el PIN se restablecen, pero los archivos de la
tarjeta SD se conservan. Detalles:
[Recuperación → Restablecer un PIN olvidado](/es/start/recovery#reset-pin).

### El Flipper va lento y no responde bien

1. Usa una tarjeta microSD de marca y de buena calidad. El Flipper usa SPI, y no todas las tarjetas lo manejan bien.
2. En **Settings → System**, comprueba:
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Carga la batería. Una batería baja también afecta al rendimiento.

### ¿Cómo cambio el nombre del Flipper o lo restablezco?

**Settings → Desktop → Change Flipper Name**: escribe un nombre, pulsa **Save**, sal de Settings y el Flipper se
reinicia. Guarda un nombre vacío para volver al predeterminado. Véase
[Nombre personalizado del Flipper](/es/start/custom-name).

## Sub-GHz

### ¿Hay bloqueo regional? ¿Cómo desbloqueo Sub-GHz?

**En Unleashed no hay bloqueo regional**: todas las frecuencias que admite el chip funcionan de serie. Ir **más allá
de las especificaciones del chip** es posible, pero puede dañar el hardware:
[Ajustes peligrosos](/es/start/dangerous-settings).

### ¿Qué protocolos son compatibles, y con qué frecuencia y modulación?

[Sistemas compatibles](/es/subghz/supported-systems).

### ¿Cómo añado frecuencias adicionales?

[Frecuencias y presets](/es/subghz/frequencies).

### ¿Puedo clonar la llave de mi coche para usar el Flipper como llave?

**No.** Las llaves de coche y la mayoría de los mandos de garaje usan **códigos rodantes**. Reproducir una señal
capturada (por ejemplo, de Read RAW) desincroniza el contador. En el peor de los casos, la llave original se
desemparaja o entra en la lista negra, y volver a emparejarla requiere herramientas de servicio técnico.

**Por qué:** el receptor recuerda el último valor de contador que recibió de un mando (cuántas veces se ha pulsado
cualquier botón). Imagina que el mando original envió el contador `0002` y que tú envías la misma señal desde el
Flipper con `0003`. El receptor lo acepta. Pero el mando original sigue en `0002`, así que su siguiente pulsación
envía `0003`, que el receptor ya ha visto, y no reacciona. Esto todavía no es un desemparejamiento: pulsa el
original unas cuantas veces más para «adelantar» al Flipper (`0004`) y volverá a funcionar. Pero si esta carrera
continúa, la distancia puede crecer hasta **más de 100 pulsaciones**, y el mando original ya no se puede recuperar
sin volver a emparejarlo con el receptor.

**Qué hacer en su lugar:**
- usa solo **un** mando: el Flipper o el original;
- **lo mejor:** crea un **mando nuevo** en el Flipper con **Add manually** y emparéjalo con el receptor como un mando
  aparte ([Add manually](/es/subghz/add-manually),
  [Programar un mando nuevo](/es/subghz/remote-prog));
- si tienes que usar los dos, altérnalos para que los contadores nunca se separen mucho.

Más información: [Códigos rodantes](/es/subghz/rolling-codes), [Modo de contador](/es/subghz/counter-mode).

### ¿Cómo uso el Flipper como mando nuevo (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors…)?

[Programar un mando nuevo](/es/subghz/remote-prog).

### ¿Cómo se usa la aplicación Sub-GHz Remote?

1. Abre la aplicación, pulsa <kbd>BACK</kbd> y selecciona **New map file**.
2. Elige un archivo de señal y una etiqueta para cada botón. Puedes dejar botones vacíos.
3. Guarda el mapa.
4. Abre el archivo de mapa que has creado.
5. Pulsa los botones para enviar las señales asignadas.

Detalles: [Sub-GHz Remote](/es/subghz/remote).

### Mi mando no es compatible (y no es una llave de coche). ¿Cómo lo grabo para los desarrolladores?

1. **Encuentra la frecuencia.** **Sub-GHz → Frequency Analyzer**: mantén pulsado el botón del mando cerca del
   Flipper (la antena está junto a la ventana de IR, en el lado izquierdo). Suéltalo y la frecuencia pasa al
   historial. Mantén <kbd>OK</kbd> para saltar a **Read** y pulsa el mando unas cuantas veces, manteniendo cada
   pulsación al menos 2 s. Prueba `AM650`, `FM238`, `FM476`, `FM12K`.
2. **¿No se decodifica nada? Graba en RAW.** Abre **Read RAW**, pon la frecuencia en la configuración y el
   **RSSI Threshold** en `----`. Haz una grabación para **cada** modulación (`AM650`/`FM238`/`FM476`/`FM12K`). Pulsa
   **REC** y después pulsa un botón 5 veces manteniéndolo 1–2 s, y otras 5 veces manteniéndolo unos 5 s. Graba todos
   los botones de la misma forma y nombra cada archivo según el botón.
3. **Infórmalo.** Comprime los archivos RAW y abre una issue en el repositorio del firmware. Adjunta buenas
   fotografías del mando (también por dentro, si es posible), el modelo y el fabricante, y una foto de la placa del
   receptor si puedes.

Si el mando no está cifrado y es lo bastante singular, puede que se añada el soporte. Para analizar señales tú
mismo, prueba [lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter).

### ¿Cómo conecto un módulo CC1101 externo?

[CC1101 externo](/es/subghz/external-cc1101).

## NFC y RFID

### MIFARE Ultralight

Lee la tarjeta, acerca el Flipper al lector para capturar la contraseña que desbloquea las páginas restantes y
vuelve a leer la tarjeta: [Desbloquear con contraseña](/es/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

Por el momento, no hay ataques para estas tarjetas en el Flipper.

### Tarjetas bancarias

No puedes clonar tarjetas bancarias, el Flipper no puede emularlas y no puede hacer de terminal de pago. Solo puede
leer datos públicos: [Tarjetas bancarias (EMV)](/es/nfc/emv).

### Amiibo

Los Amiibo son `NTAG215`. No se pueden poner en una MIFARE Classic y, por ahora, no se pueden escribir Amiibo en
etiquetas físicas nuevas.

### HID / iClass (Picopass)

- Lee iClass con la aplicación **Picopass**. La emulación está admitida en los builds actuales de Unleashed con
  aplicaciones.
- Picopass de 26 bits se puede degradar a credenciales H10301 de RFID LF. Esto solo funciona si el lector está
  configurado para LF. Algunos lectores iClass son solo HF.
- Con la aplicación es posible escribir en tarjetas en modo de personalización.
- La aplicación **Seader** con una placa de expansión SAM lee tarjetas HID más seguras.

### Clonado de RFID de 125 kHz

Para copiar una etiqueta LF, escríbela en una **T5577**. Los chips que lee el Flipper son de solo lectura, y no
existen «blancos» de ellos. La T5577 es un chip multiemulador que se puede programar para actuar como otras
etiquetas: [Escribir RFID](/es/rfid/write), [Aplicación T5577](/es/rfid/t5577-app).

### Tarjeta o llavero desconocidos

Si NFC, RFID y Picopass fallan todos, haz fotos del anverso y del reverso de la credencial y del lector. Si es una
tarjeta, ponla delante de una luz intensa y fotografía la antena. Publícalas en los chats de la comunidad para
identificarla.

## Infrarrojos

### ¿Hay una forma correcta de capturar señales de IR (sobre todo de aires acondicionados)?

Sí: [Capturas de IR](/es/infrared/captures).

## Archivos y ordenadores

### ¿Dónde encuentro archivos (Sub-GHz, IR, NFC…) para mi Flipper?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) y
  [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) cubren casi todo lo que puedas necesitar.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero): prácticamente todos los enlaces que te
  puedan hacer falta.

### ¿Cómo copio archivos de GitHub al Flipper?

Descarga los archivos en un PC y cópialos a la tarjeta SD (con un lector de tarjetas o con el gestor de archivos de
qFlipper). También hay una
[guía detallada de la comunidad](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf).

### ¿Cómo limpio los `.DS_Store` y los archivos de punto que deja macOS, o cómo ordeno los archivos?

Véase [Tarjeta microSD → macOS](/es/start/sd-card#macos-hidden-files-and-sorting).

### ¿Cómo abro la CLI o veo los registros?

Cierra qFlipper primero. Solo un programa puede tener tomado el puerto serie.

- **Navegador (Chromium):** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → elige el dispositivo
  serie USB → **CLI** en la barra lateral.
- **Windows:** busca el puerto COM en qFlipper, cierra qFlipper y después, en PuTTY, elige **Serial**, escribe el
  puerto COM y la velocidad `115200` y pulsa **Open**. Un «Access Denied» significa que qFlipper sigue abierto.
- **macOS/Linux:** busca la ruta del dispositivo en qFlipper (empieza por `/dev/tty`) o con `ls /dev/tty.*`, cierra
  qFlipper y ejecuta (sustituyendo `PATH`):
  ```bash
  screen PATH 115200
  ```
- **Android:** la aplicación *Serial USB Terminal*, conectada por USB OTG.
- **iPhone:** no hay puerto serie por USB. Usa otro método.

Para ver los registros, pon **Settings → System → Log Level** en `Debug` y escribe `log` en la CLI.
<kbd>Ctrl</kbd>+<kbd>C</kbd> sale. Más información: [CLI](/es/dev/cli).

### ¿Cómo compilo el firmware yo mismo?

[Compilar el firmware](/es/dev/build).

## Comunidad

- Releases: Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Builds dev: Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Más enlaces: [Enlaces](/es/community/links)
