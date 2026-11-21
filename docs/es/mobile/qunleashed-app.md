---
title: Aplicación complementaria qUnleashed
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# Aplicación complementaria qUnleashed

::: tip Unleashed
**qUnleashed** es la aplicación complementaria del propio equipo de Unleashed, para móvil y ordenador.
Está escrita desde cero en Flutter como alternativa a la app móvil oficial de Flipper, así que no es un
fork de qFlipper. Licencia GPL-3.0 o posterior, código y descargas en
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

Está hecha para Unleashed, pero también funciona con otros firmwares. La versión estable actual es la **0.17.2**.

## ¿Funcionará en tu dispositivo? {#requirements}

| Sistema | Necesitas |
|---|---|
| Android | 10 (API 29) o posterior |
| iOS | 15 o posterior |
| macOS | 12 o posterior |
| Windows | 10 o posterior, de 64 bits |
| Linux | GLib 2.72 y glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 o posteriores |

En un Linux más antiguo el binario ni siquiera arranca.

## Instalación {#install}

Elige la descarga de tu sistema en la
[página de releases](https://github.com/DarkFlippers/qUnleashed/releases). No hay versión en las tiendas
de aplicaciones ni script de instalación.

## Conexión {#connecting}

El Bluetooth funciona en los cinco sistemas. El puerto serie USB funciona en Android, Windows, macOS y
Linux; en iOS no hay opción de USB, porque Apple no deja que las apps hablen con un puerto serie USB.

La app recuerda los Flipper que has usado y se reconecta sola. Si hay uno enchufado por USB, gana sobre el
último dispositivo Bluetooth. En Android un servicio en primer plano mantiene viva la conexión Bluetooth
mientras la app está en segundo plano.

## Firmware {#firmware}

- **Actualizador** con canales release y dev y sus listas de cambios. Descarga e instala desde la propia
  app: la build base de Unleashed, la de aplicaciones extra, la compacta y los canales oficiales.
- **Reparar desde modo DFU** reinstala el firmware completo por USB. La misma idea que el Full Repair de
  qFlipper, para un dispositivo que ya no arranca.
- **Avisos de nuevas versiones**, opcionales, y el canal dev tiene su propio interruptor aparte.

## Dispositivo {#device}

- **Información del dispositivo**: versión y fecha de compilación del firmware, batería, almacenamiento.
- **Compartir GPS e internet**: el móvil pasa su ubicación a las aplicaciones del Flipper y le presta su
  conexión de red. Para esto tu firmware necesita la extensión RPC de GPS y red.
- **Escritorio remoto**: la pantalla del Flipper en directo en tu móvil o PC, con los botones en pantalla.
  En un ordenador puedes usar el teclado de verdad. Las capturas se pueden exportar y la pantalla se puede
  grabar en GIF.
- **Línea de comandos**: la CLI completa del Flipper. Solo por USB, así que en iOS no está.

## Archivo de llaves {#archive}

En el móvil queda una copia de tus llaves, un archivo por cada Flipper. Cada fichero se marca como
**synced**, **remote-only**, **local-only** o **deleted**, así ves qué hay en cada sitio, y un fichero
borrado se puede recuperar. Los ficheros se pueden marcar como favoritos.

Categorías: Sub-GHz, Wardriving (con los autoguardados), RFID 125, NFC, Infrared, iButton, Bad USB,
JavaScript.

Puedes ejecutar un fichero desde la propia app. NFC, RFID e iButton se emulan por RPC; Sub-GHz, Infrared,
Bad USB y JavaScript se abren en la aplicación correspondiente del Flipper.

También hay un editor de texto con resaltado para los formatos de fichero del Flipper, así que puedes
arreglar un `.sub` o un `.ir` sin ordenador.

## Gestor de ficheros {#file-manager}

Navega por `/ext` (la tarjeta SD) y `/int` (la memoria interna). Crea, renombra, borra, descarga, sube y
edita ficheros de texto.

## Aplicaciones {#apps}

El catálogo de aplicaciones, con búsqueda, categorías, orden, página de detalles y capturas. Instala,
actualiza y borra aplicaciones. También ve lo que ya hay en el Flipper, incluidas las preinstaladas.

## Herramientas {#tools}

- **Pixel Draw**: un editor de pixel art con gestor de proyectos y animación de varios fotogramas. Puede
  importar animaciones del delfín y mostrar una vista previa en directo en el Flipper.
- **Extract MIFARE Keys**: ejecuta Mfkey32 en el móvil a partir de los nonces que recogió el Flipper. El
  procedimiento completo está en [Recuperación rápida de claves con qUnleashed](/es/nfc/qunleashed).
- **Remotes Library**: mandos de infrarrojos de la fuente oficial y del repositorio público
  [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB). Navega, busca, edita el fichero `.ir`
  y guárdalo en el archivo o directamente en `/ext/infrared`.
- **Pulse Plotter**: dibuja capturas de pulsos en bruto de Sub-GHz, infrarrojos y RFID.
- **Saved Locations**: chinchetas en un mapa a partir de la latitud y la longitud guardadas en los ficheros
  del archivo.

## Recuperación de Seed para capturas Sub-GHz {#seed-recovery}

Algunos mandos basados en KeeLoq (FAAC SLH, Genius, Erreka, los BFT Mitto más antiguos) usan un **Seed** secreto
que hace falta para decodificarlos. El Flipper solo recopila los datos, con la aplicación
[Seed Capturer](/es/subghz/seed-capturer); la búsqueda en sí es una fuerza bruta, así que se ejecuta en qUnleashed,
no en el Flipper.

1. Captura el mando con `Apps → Sub-GHz → Seed Capturer`: pulsa el **mismo botón** varias veces, con pulsaciones
   firmes y de una en una, y comprueba que el contador `Hops` sube con cada pulsación.
2. Conecta el Flipper a **qUnleashed** y abre su herramienta **Seed recovery**.
3. Elige tu captura de la lista. qUnleashed lee las capturas directamente de la carpeta `subghz_seed_captures` del
   Flipper; el fabricante, la frecuencia y los valores `Fix` y `Hop` ya están en el fichero. **No tienes que
   copiar, mover, renombrar ni editar ningún fichero.**
4. Lanza la búsqueda y espera.
5. Si se encuentra el Seed, qUnleashed devuelve el Seed y el contador, y puede **guardarte el mando clonado
   completo** como fichero `.sub` (el `Fix` ya lleva el número de serie y el botón). Vuelve a ponerlo en el Flipper
   y envíalo: no hace falta teclear nada en `Add Manually`.
6. Si no se encuentra nada, lo más probable es que la captura tuviera algún hueco. Vuelve a capturar sujetando el
   mando justo al lado del Flipper, y pulsa `Reset` (<kbd>←</kbd>) para empezar de cero si alguna pulsación no se
   registra.

::: warning El Seed pertenece a la instalación
En FAAC SLH y Genius el Seed es **distinto para cada botón**, así que captura el botón que vayas a usar. En Erreka
el Seed es por mando (a veces por instalación). En BFT Mitto es por mando, y solo los mandos antiguos con un Seed
único necesitan una captura.
:::

El procedimiento completo, incluida la programación del clon en un receptor, está en
[Programar mandos de código rodante](/es/subghz/remote-prog) y [KeeLoq](/es/subghz/keeloq).

Usa esto solo con tus propios mandos y tus propias puertas.

## Páginas relacionadas {#related}

- [Recuperación rápida de claves con qUnleashed](/es/nfc/qunleashed)
- [Seed Capturer](/es/subghz/seed-capturer)
- [Aplicación móvil de Flipper](/es/mobile/mobile-app)
- [qFlipper](/es/mobile/qflipper)
- [Herramientas web](/es/mobile/web-tools)
