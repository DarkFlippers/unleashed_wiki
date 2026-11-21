---
title: Qué añade Unleashed
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Qué añade Unleashed

Unleashed está construido sobre el firmware oficial (OFW) y se mantiene **totalmente compatible con su API y sus
aplicaciones**. Todo lo que hace el firmware de serie sigue funcionando. Esta página lista lo que Unleashed añade o
cambia, agrupado por áreas, con enlaces a las páginas de la wiki que cubren cada función en detalle.

## Sub-GHz: biblioteca de radio y hardware

- **Restricciones regionales de transmisión eliminadas.** Todas las frecuencias que admite el chip CC1101 pueden
  transmitir sin pasos adicionales.
- **Frecuencias adicionales** en la lista por defecto (por ejemplo, 317.0 y 336.1 MHz se añadieron hace poco) y una
  lista de frecuencias editable por el usuario: [Frecuencias y presets](/es/subghz/frequencies).
- **Rango de frecuencias ampliado opcional** más allá de las especificaciones del chip. Puede dañar el hardware:
  [Ajustes peligrosos](/es/start/dangerous-settings).
- **Muchos protocolos nuevos** y la capacidad de **guardar y enviar numerosos sistemas de código rodante**:
  [Sistemas compatibles](/es/subghz/supported-systems), [Códigos rodantes](/es/subghz/rolling-codes),
  [KeeLoq](/es/subghz/keeloq).
- Soporte de **módulos CC1101 externos** por SPI por hardware, con control del amplificador y de los LED:
  [CC1101 externo](/es/subghz/external-cc1101).
- **Modos de contador** para los códigos rodantes, para evitar la desincronización:
  [Modo de contador](/es/subghz/counter-mode).

## Sub-GHz: la aplicación principal

- **Se recuerdan los últimos ajustes usados** (frecuencia, modulación…).
- **Mejoras en el Frequency Analyzer**. El analizador en sí es del firmware oficial; en Unleashed <kbd>OK</kbd>
  envía la frecuencia detectada a Read y una pulsación larga de <kbd>OK</kbd> salta directamente a Read: [Frequency Analyzer](/es/subghz/frequency-analyzer).
- **Mejoras en Read**: muestra cuándo se recibió cada señal. Mantén <kbd>→</kbd> en la lista para borrar una señal.
  Los protocolos multisistema muestran el nombre del sistema decodificado (CAME, Nice FloR-S, FAAC SLH, KeeLoq):
  [Read](/es/subghz/read).
- **Nombres de protocolo en los nombres de archivo**: con `Radio Settings → Protocol Names = ON`, los archivos
  guardados llevan una marca de tiempo más el protocolo.
- **Botones personalizados** para KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn
  y otros. Usa las flechas para enviar el código de otro botón: [Usarlo como mando](/es/subghz/remote).
- **`Add manually` ampliado**: una entrada por sistema, selector de banda, modo avanzado con TE, tiempo de guarda y
  otros campos. Crea mandos FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo y otros, y emparéjalos con un
  receptor: [Add manually](/es/subghz/add-manually),
  [Programar un mando nuevo](/es/subghz/remote-prog).
- **Read RAW → More → Edit** abre un archivo RAW directamente en Sub-GHz RAW Edit:
  [Editor RAW](/es/subghz/raw-editor).
- **Filtros de ignorado** para los protocolos ruidosos (alarmas, sensores, timbres, buscadores de llaves, luces
  Feron…) y opciones de depuración (paso de incremento del contador, salida por pin de depuración):
  [Ajustes de Sub-GHz](/es/subghz/settings).

## Aplicaciones de Sub-GHz

| Aplicación | Qué hace | Página |
|---|---|---|
| Sub-GHz Remote | Asocia hasta 5 archivos `.sub` a los botones, con un configurador integrado | [Remote](/es/subghz/remote) |
| Sub-GHz Bruteforcer | Fuerza bruta de códigos estáticos, archivos propios, retardo y repeticiones | [Fuerza bruta](/es/subghz/bruteforce) |
| Remote Analyzer | Decodifica un mando a la vez, con un analizador de frecuencias integrado | [Remote Analyzer](/es/subghz/remote-analyzer) |
| Nice O-Code | Recupera el código de instalador de un mando Nice O-Code | [Nice O-Code](/es/subghz/nice-o-code) |
| Security+ PIN | Encuentra el PIN del teclado de una señal Security+ 2.0 | [Security+ PIN](/es/subghz/secplus-pin) |
| Seed Capturer | Recopila pares Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) para recuperar el seed | [Seed Capturer](/es/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Recorta, combina y decodifica capturas RAW | [Editor RAW](/es/subghz/raw-editor) |

## NFC, RFID e iButton

- **Claves de MIFARE Classic adicionales** en el diccionario del sistema:
  [MIFARE Classic](/es/nfc/mifare-classic). Guías de recuperación de claves:
  [Nested y Fudan](/es/nfc/nested-fudan), [MFKey](/es/nfc/mfkey).
- **MFKey** en el propio dispositivo: [Aplicación MFKey](/es/nfc/mfkey-app).
- **Protocolo EMV y parser de los datos públicos**: [Tarjetas bancarias (EMV)](/es/nfc/emv).
- **`Add manually` de NFC → MIFARE Classic con un UID personalizado**:
  [Add manually](/es/nfc/add-manually).
- **Muchos parsers de tarjetas adicionales** (tarjetas de transporte y de ciudad: Troika, Umarsh, Zolotaya Korona,
  Kazan, Metromoney, tarjeta social de Moscú y más): [Tarjetas compatibles](/es/nfc/supported-cards).
- **NFC Magic 2.0** para las tarjetas magic, incluidas las Ultralight: [NFC Magic](/es/nfc/nfc-magic).
- **Aplicación T5577**: leer, editar y escribir bloques, borrar o limpiar la contraseña y hacer sniffing de una
  contraseña: [Aplicación T5577](/es/rfid/t5577-app).
- Formato de visualización **EM4100 DEZ 8**: [Leer RFID](/es/rfid/read).
- **Fuzzers de RFID e iButton**: [RFID Fuzzer](/es/rfid/fuzzer), [iButton Fuzzer](/es/ibutton/fuzzer).

## Infrarrojos

- El mando universal de televisores está reconstruido para cubrir **todos los botones**.
- **Mandos universales para proyectores, ventiladores, aires acondicionados y audio** (barras de sonido…),
  mantenidos al día por el equipo.
- Protocolo **RCA** y soporte de módulos IR externos (con detección automática):
  [Mandos universales](/es/infrared/universal-remotes).
- Cómo hacer buenas capturas para la base de datos de mandos universales:
  [Capturas de IR](/es/infrared/captures).

## Bad USB y USB/Bluetooth

- **BadKB**: ejecuta scripts de Bad USB por **Bluetooth**, integrado en la aplicación Bad USB:
  [Bad USB](/es/badusb/usage).
- **Distribuciones de teclado** y el comando `DUCKY_LANG`, que permite a un script elegir su propia distribución:
  [Formato de script](/es/badusb/script-format).

## Escritorio, ajustes y comodidades

- **Nombre personalizado del Flipper** en **Settings → Desktop → Change Flipper Name**:
  [Nombre personalizado](/es/start/custom-name).
- **Reloj en el escritorio** (`Settings → Desktop → Show Clock`) y **estilos de batería** (`Battery View`: Bar, %,
  Inv. %, Retro 3, Retro 5, Bar %): [Escritorio](/es/start/desktop).
- **Bloqueo manteniendo <kbd>↑</kbd>** en el escritorio: con el PIN si hay uno configurado, o un bloqueo normal si
  no.
- **Más juegos en el Dummy Mode**: cada flecha (pulsación corta y larga) y <kbd>OK</kbd> pueden lanzar su propia
  aplicación.
- Soporte del **mod de retroiluminación RGB** en **LCD and Notifications → RGB Mod Settings** (solo para los Flipper
  con el mod de hardware).
- **Cursor en la entrada de texto** y un **minieditor de entrada de bytes** (pulsa <kbd>↑</kbd> repetidamente hasta
  que aparezca el editor de nibbles).
- **Archive** con pestañas adicionales (SubRem para los mapas de Sub-GHz Remote, Phone para la agenda de SIM800).

Todos los elementos de Settings están descritos en [Ajustes](/es/start/settings).

## Aplicaciones integradas {#built-in-apps}

Estas aplicaciones se compilan desde el repositorio del firmware y se instalan en `/ext/apps/` con cada
actualización, en **todas** las variantes de build (`e`, sin sufijo y `c`). Los paquetes de aplicaciones no las
contienen, así que un paquete nunca puede sobrescribirlas ni dejarlas en una versión anterior.

**En el menú principal:** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (con BadKB), U2F, **Clock** (controles
de brillo, alarma, temporizador) y **Sub-GHz Remote**. Sub-GHz, Archive y Settings forman parte del binario del
firmware.

**En Apps:**

| Aplicación | Categoría | Página |
|---|---|---|
| MFKey | NFC | [Aplicación MFKey](/es/nfc/mfkey-app) |
| T5577 | RFID | [Aplicación T5577](/es/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | véase la tabla anterior |
| SIM800 (llamadas, SMS, agenda, USSD, terminal AT) | GPIO | [SIM800](/es/gpio/sim800) |
| FindMy Flipper (baliza de Apple FindMy / Google Find My Device) | Bluetooth | [Catálogo de aplicaciones](/es/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Mandos](/es/apps/controllers) |
| Snake Game | Juegos | — |

## Paquetes de aplicaciones de la comunidad

- **Paquete base** (en los builds sin sufijo y en los `e`) y **paquete extra** (solo en los `e`): el código y la
  lista completa están en
  [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Los paquetes más recientes están
  en las [releases de GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).
- El catálogo oficial también funciona: [lab.flipper.net/apps](https://lab.flipper.net/apps) o la aplicación móvil.
- Más información: [Catálogo de aplicaciones](/es/apps/catalog),
  [Aplicaciones en la tarjeta SD](/es/apps/sd-card-apps).

## Aplicaciones complementarias y herramientas web

- **qUnleashed**: aplicación complementaria para móvil y PC: [qUnleashed](/es/mobile/qunleashed-app).
- **Herramientas web**: [Web Installer](https://web.unleashedflip.com), mapa de Sub-GHz
  ([map.unleashedflip.com](https://map.unleashedflip.com)), mapa de wardriving Wi-Fi
  ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), web flasher de ESP32
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)):
  [Herramientas web](/es/mobile/web-tools).
