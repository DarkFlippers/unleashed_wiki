---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** es la aplicación de escritorio oficial del Flipper Zero: actualiza el firmware y las bases de datos,
gestiona los archivos de la tarjeta microSD, hace copias de seguridad y las restaura, repara un firmware roto y
duplica la pantalla. Funciona en Windows, macOS y Linux.

::: tip Unleashed
Los canales de actualización de qFlipper (Release / RC / Dev) instalan el firmware **oficial**. Para instalar
Unleashed usa **Install from file** con el `.tgz` de Unleashed (qFlipper 1.2.0 o posterior), como se explica más
abajo, o el [Web Installer](/es/mobile/web-tools#unleashed-web-installer).
:::

## Instalar qFlipper

Descárgalo de [flipperzero.one/update](https://flipperzero.one/update) y ejecuta el instalador.

- **Windows**: solo Windows 10 y 11. El instalador instala también los controladores.
- **macOS**: 10.14 o posterior, optimizado para Apple Silicon.
- **Linux**: un AppImage. Dale permisos de ejecución y configura las reglas de udev:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # run it
./qFlipper-x86_64.AppImage rules install   # udev rules, to use it as a normal user
```

(Desde un gestor de archivos: Propiedades → Permisos → «Permitir ejecutar el archivo como un programa» / «Es
ejecutable».)

## Vista general

Conecta el Flipper por USB con la tarjeta SD puesta y arranca qFlipper.

- **Device information**: datos del hardware y del firmware, botón de actualización, control remoto.
- **Advanced controls**: copia de seguridad, restauración, reinicio de fábrica, canal de actualización e **Install
  from file**.
- **File manager**: explora, sube, descarga, renombra y borra archivos de la tarjeta SD y del almacenamiento
  interno.

## Instalar Unleashed con qFlipper

1. Asegúrate de que hay una **tarjeta SD** puesta.
2. Descarga `flipper-z-f7-update-(version).tgz` de las
   [releases de Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (elige la letra de
   build que quieras, véase [variantes de build](/es/apps/catalog#build-variants)).
3. Arranca qFlipper y conecta el Flipper.
4. Pulsa **Install from file** y selecciona el `.tgz`.
5. Espera a que terminen todas las fases. El Flipper se reinicia en Unleashed con todos los recursos instalados.

¿Ya tienes Unleashed? Instala la versión nueva encima sin más, no hace falta volver al firmware oficial.
Más opciones: [Instalar Unleashed](/es/start/install), [Actualizar](/es/start/updating).

## Subir y descargar archivos

En **File manager**, arrastra archivos a una carpeta o haz clic derecho en una carpeta → **Upload here**. Clic
derecho en un archivo o una carpeta → **Download** para copiarlo al ordenador (una forma sencilla de respaldar toda
la tarjeta SD).

| Acción | Windows / Linux | macOS |
|---|---|---|
| Entrar en la carpeta | Return | Return |
| Atrás | Backspace | Backspace |
| Subir | Ctrl+L | Cmd+L |
| Descargar | Ctrl+D | Cmd+D |
| Borrar | Delete | Fn+Backspace |
| Borrar de inmediato | Shift+Delete | Shift+Fn+Backspace |
| Carpeta nueva | Ctrl+N | Cmd+N |
| Renombrar | Ctrl+E | Cmd+E |
| Actualizar | Ctrl+G | Cmd+G |

## Control remoto y capturas de pantalla

En **Device information**, haz clic en la imagen del Flipper y luego pulsa los botones en pantalla o usa el teclado
(ℹ️ muestra la correspondencia de teclas). **SAVE SCREENSHOT** guarda la pantalla actual como imagen.

## Registros e informes de fallos

- **LOGS → OPEN FULL LOG** muestra el registro de la sesión actual; puedes guardarlo como `.txt`.
- qFlipper conserva los registros de las últimas 100 sesiones: en **LOGS**, clic derecho en el área del registro →
  **Browse all logs**.
- Informa de los problemas del qFlipper oficial en [forum.flipperzero.one](https://forum.flipperzero.one/) (sección
  Firmware update / qFlipper). Los problemas de Unleashed en sí van a los chats de Unleashed o a las issues de
  GitHub.

## Resolución de problemas

### qFlipper no ve el Flipper / Chrome no puede conectarse

Solo un programa puede usar el puerto serie. Si qFlipper está abierto, Flipper Lab, el Web Installer y las demás
herramientas web no pueden conectarse, y al contrario. Cierra qFlipper (y las pestañas de más de Flipper Lab) antes
de usar una herramienta del navegador.

### Controladores de Windows

1. Instala qFlipper solo desde fuentes oficiales; así se instalan los controladores correctos. Busca
   actualizaciones en **Advanced controls → CHECK APP UPDATES**.
2. **Modo normal** (Flipper en funcionamiento): el Flipper aparece como **USB Serial Device** en
   `Device Manager → Ports (COM & LPT)`, con ID de hardware **VID 0483, PID 5740** y controlador de **Microsoft**.
   Si está instalado otro controlador, desinstálalo y vuelve a conectar.
3. **Conflicto de puerto COM**: dos dispositivos serie con el mismo número de COM. Abre uno de ellos →
   **Port Settings → Advanced** y asígnale un **COM Port Number** que esté libre.
4. **Modo de recuperación (DFU)**: mantén <kbd>←</kbd> + <kbd>Back</kbd>, suelta <kbd>Back</kbd> y sigue pulsando
   <kbd>←</kbd> hasta que el LED se ponga azul. El Flipper debe aparecer como **DFU in FS Mode** en
   `Universal Serial Bus devices`, con **VID 0483, PID DF11** y controlador **STMicroelectronics**.
5. Si ves **STM Device in DFU mode** en `Universal Serial Bus controllers`, el controlador instalado es el
   equivocado: desinstala qFlipper, reinstálalo desde la web oficial y vuelve a comprobarlo.
6. Si **DFU in FS Mode** aparece en `Other devices` con un signo de exclamación: clic derecho → **Update driver →
   Browse my computer → Let me pick** → **Universal serial bus devices** → **WinUsb Device**.

Si el Flipper no arranca en absoluto, consulta [Recuperación](/es/start/recovery).

## Páginas relacionadas

- [Instalar Unleashed](/es/start/install)
- [Aplicación móvil de Flipper](/es/mobile/mobile-app)
- [Herramientas web](/es/mobile/web-tools)
