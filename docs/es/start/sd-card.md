---
title: Tarjeta microSD
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Tarjeta microSD

La tarjeta microSD no es opcional. En ella se guardan tus llaves, tarjetas y mandos, todas las aplicaciones `.fap`
(incluidas las aplicaciones integradas de Unleashed), las bases de datos, el paquete de actualización y, en el
firmware actual, incluso el **almacenamiento interno**.

## Elegir una tarjeta

- **Capacidad:** 16–32 GB es más que suficiente. Se admiten hasta 256 GB, pero las tarjetas grandes tardan más en
  montarse.
- **Sistema de archivos:** FAT12, FAT16, FAT32 o exFAT.
- **Calidad:** usa una tarjeta **de marca** (SanDisk, Kingston…). El Flipper habla con la tarjeta por **SPI**, no en
  el modo SDIO rápido que usan los móviles y los PC. No todas las tarjetas se llevan bien con SPI, aunque funcionen
  perfectamente en otros dispositivos. Una tarjeta mala hace que el Flipper vaya lento, puede agotar la batería más
  rápido (hasta ~50 mA en lugar de ~30 mA) y puede corromper datos.
- Las lecturas por SPI llegan a casi 600 KiB/s, de sobra para todo lo que hace el Flipper.

## Insertarla

1. La ranura está en la parte inferior del Flipper.
2. Sujeta la tarjeta **con los contactos hacia arriba** y empújala hasta que haga clic.
3. El icono de SD aparece en la barra de estado.

## Si la tarjeta no se reconoce

Aparece un mensaje sobre la tarjeta SD, o el icono de la barra de estado sale tachado. Causas posibles:

| Causa | Solución |
|---|---|
| Sistema de archivos incorrecto o inexistente | Formatea la tarjeta (más abajo) |
| Polvo en la ranura | Límpiala con cuidado con aire comprimido |
| La tarjeta no admite SPI | Usa otra tarjeta |
| La tarjeta está dañada | Usa otra tarjeta |

## Settings → Storage

**Main Menu → Settings → Storage**

| Elemento | Qué hace |
|---|---|
| **About Internal Storage** | Nombre, tipo `Virtual (/.int on SD)`, espacio total y libre, flash libre |
| **About SD Card** | Etiqueta, tipo de sistema de archivos, espacio total y libre, fabricante y número de serie |
| **Unmount SD Card** / **Mount SD Card** | Desmontar de forma segura antes de extraerla, o volver a montarla. Montarla puede cortar brevemente la alimentación de los módulos externos |
| **Format SD Card** | Formatea la tarjeta. **¡Se perderán todos los datos!** |
| **Benchmark SD Card** | Prueba la velocidad de escritura y lectura en modo SPI |
| **Factory Reset** | Borra el almacenamiento interno (ajustes, emparejamientos, delfín). Véase [Recuperación](/es/start/recovery#factory-reset) |

### Formatear

1. **Settings → Storage → Format SD Card**.
2. Confirma con <kbd>→</kbd> **Format**.
3. Espera a que aparezca `Formatted` y pulsa **Finish**.

Si el formateo falla en el Flipper (`Cannot Format SD Card`), formatea la tarjeta en un PC como FAT32/exFAT, o prueba
con otra tarjeta.

### Extracción segura

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. Cuando veas `SD Card Unmounted` / `You can remove SD card now.`, empuja la tarjeta para liberarla y sácala.

Extraer una tarjeta mientras el Flipper escribe en ella puede corromper archivos o el sistema de archivos.

### Benchmark

El benchmark escribe un archivo de prueba `/ext/rwfiletest.bin` y muestra líneas como `4096b : W 300K R 600K`:
tamaño de bloque y después velocidad de escritura y de lectura en KiB/s. Una tarjeta debería escribir **a 260 KiB/s
como mínimo** para funcionar con normalidad. Los resultados difieren de los benchmarks en un PC porque la prueba se
ejecuta en modo SPI. Lánzalo varias veces para hacerte una idea justa.

## Estructura de carpetas

`/ext` es la raíz de la tarjeta. Las carpetas principales:

| Carpeta | Contenido |
|---|---|
| `/ext/subghz/` | Archivos `.sub` de Sub-GHz. En `assets/` están `dangerous_settings`, `setting_user.example` (plantilla para tu propia lista de frecuencias) y el almacén de claves de KeeLoq `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Mapas de Sub-GHz Remote |
| `/ext/nfc/` | Archivos `.nfc` de NFC. En `assets/` están los diccionarios de claves |
| `/ext/lfrfid/` | Archivos `.rfid` de RFID de 125 kHz |
| `/ext/ibutton/` | Archivos `.ibtn` de iButton |
| `/ext/infrared/` | Mandos `.ir` de IR. En `assets/` están las bibliotecas de mandos universales |
| `/ext/badusb/` | Scripts de Bad USB (`.txt`). En `assets/layouts/` están las distribuciones de teclado (`.kl`) |
| `/ext/apps/` | Aplicaciones `.fap` por categoría (aplicaciones integradas y paquetes de aplicaciones) |
| `/ext/apps_data/` | Datos y ajustes de las aplicaciones |
| `/ext/dolphin/` | `name.settings` (nombre personalizado) y animaciones |
| `/ext/update/` | Paquetes de actualización descomprimidos |
| `/ext/.int/` | Almacén de respaldo del almacenamiento interno (`/int`). No lo edites a mano |

::: tip
Haz de vez en cuando una copia de seguridad de toda la tarjeta (qFlipper puede descargar los archivos, o cópialos en
un PC). Tus llaves y tus mandos solo existen en la tarjeta.
:::

## macOS: archivos ocultos y ordenación {#macos-hidden-files-and-sorting}

macOS deja archivos `._*` y `.DS_Store` en la tarjeta. Para limpiarlos:

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Sustituye `Flipper\ SD` por el nombre de tu tarjeta.

El explorador de archivos lista los archivos más rápido cuando el directorio FAT está ordenado. En macOS (con
[Homebrew](https://brew.sh)):

```bash
brew install fatsort
diskutil list                         # find the card, e.g. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # use your own disk id
```

`fatsort` está disponible también en Linux.

## Relacionado

- Qué sobrevive a una actualización: [Actualizar](/es/start/updating)
- Formatos de archivo: [Sub-GHz](/es/subghz/file-format), [NFC](/es/nfc/file-format),
  [RFID](/es/rfid/file-format), [Infrarrojos](/es/infrared/file-format), [iButton](/es/ibutton/file-format)
