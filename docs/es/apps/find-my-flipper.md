---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (de @MatthewKuKanich) convierte el Bluetooth del Flipper en una baliza de localización. El Flipper
emite el mismo anuncio BLE que una etiqueta localizadora, y los móviles de la red de rastreo que haya cerca informan
de su posición, de modo que un Flipper perdido se puede encontrar en la app del propietario de la etiqueta.

Tipos de etiqueta compatibles: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag**
y **Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper se incluye con el firmware, y Unleashed instala además un pequeño gancho de arranque: si la baliza
estaba activa cuando se apagó el Flipper, **se vuelve a iniciar automáticamente después de reiniciar**, sin abrir la
app. La baliza sigue funcionando en segundo plano mientras usas otras apps.
:::

::: warning
Úsalo solo con tus propias etiquetas y dispositivos. Rastrear a otras personas puede ser ilegal donde vives.
:::

## Qué necesitas

El Flipper necesita la **dirección MAC** y el **payload** de la etiqueta (o un archivo de claves). Los puedes obtener
de dos formas:

- **Clonar una etiqueta existente** (lo más sencillo; la ubicación aparece entonces en la app habitual del
  propietario de la etiqueta).
- **Generar tus propias claves** con el método de OpenHaystack (no hace falta una etiqueta física, solo funciona en la
  red de Apple; la ubicación se consulta con OpenHaystack o una alternativa sin Mac).

### Opción A: clonar una etiqueta existente

1. Empareja el AirTag o el SmartTag con tu móvil como de costumbre.
2. Ponlo en modo «perdido»: mantenlo alejado del móvil en el que está registrado durante unos 15 minutos.
3. En un móvil Android instala **nRF Connect** (la versión de iOS no muestra los datos en bruto).
4. En nRF Connect pon el filtro en la marca de la etiqueta (Apple o Samsung), ajusta el RSSI al valor más bajo y
   escanea.
5. Cuando la etiqueta aparezca como dispositivo «FindMy», abre **Raw** / **View Raw** y apunta el **payload** y la
   **dirección MAC**. También puedes exportarlo como archivo `.txt`.
6. **Quita inmediatamente la pila de la etiqueta**, porque si no rotará su clave y su MAC y tu copia dejará de
   funcionar.

### Opción B: claves de OpenHaystack

1. Descarga `generate_keys.py` del [repositorio FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper) y
   ejecútalo (necesita `python3 -m pip install cryptography`).
2. Te da una **Private Key**, una **Public Key**, un **Payload** y una **MAC Address**, además de un archivo `.keys`.
3. Guarda la Private Key: la necesitas para recibir los informes de ubicación.
4. Consulta las ubicaciones en [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS anterior a 14) o
   sin Mac con [macless-haystack](https://github.com/dchristl/macless-haystack) o
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Configurar el Flipper

1. Copia el `.txt` exportado de nRF Connect o el archivo `.keys` a `/ext/apps_data/findmy/` en la tarjeta SD (o
   sáltate este paso e introduce los datos a mano).
2. Abre `Apps → Bluetooth → FindMy Flipper` y pulsa <kbd>→</kbd> (**Config**).
3. Elige **Register Tag** y después el tipo de etiqueta: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` o
   `Google Find My`.
4. Elige cómo importarla:
   - `nRF Connect (.txt)`: selecciona el archivo exportado;
   - `OpenHaystack (.keys)`: selecciona el archivo de claves;
   - `Register Tag Manually`: escribe la dirección MAC y después el payload.
5. Vuelve a la pantalla principal y pulsa <kbd>OK</kbd>. Cambia a `Broadcast Active`.

## Pantalla principal

| Botón | Acción |
|---|---|
| <kbd>OK</kbd> | iniciar / detener la baliza (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | cambiar el intervalo de emisión |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | salir de la app dejando la baliza en marcha en segundo plano |
| <kbd>Back</kbd> | cerrar la app |

## Menú Config

| Elemento | Valores | Notas |
|---|---|---|
| Broadcast Interval | 1-10 s (Google: 1-2 s) | cada cuánto se envía la baliza; Google exige al menos cada 2 s |
| Transmit Power | 0-6 dBm | más potencia = más alcance y más consumo de batería |
| Register Tag | | tipo de etiqueta e importación (arriba) |
| Show MAC | Yes / No | mostrar la MAC en la pantalla principal |

La app guarda su estado en `/ext/apps_data/findmy/findmy_state.txt`; eso es lo que permite que la baliza se reanude
después de un reinicio.

## Rastreo

- **Clon de AirTag**: el Flipper aparece como tu AirTag en la app Find My.
- **Clon de SmartTag**: en SmartThings (SmartThings Find), en el móvil o en el navegador.
- **Claves de OpenHaystack**: en OpenHaystack o macless-haystack.

## Resolución de problemas

- **La ubicación nunca se actualiza**: la clave y la MAC de la etiqueta rotaron antes de que le quitaras la pila;
  vuelve a capturarlas.
- **La baliza se detiene después de reiniciar**: comprueba que la tarjeta SD está insertada (el archivo de estado está
  en ella) y que la baliza estaba en `Broadcast Active` antes de apagar.
- **La batería se agota más rápido**: aumenta el intervalo de emisión y reduce la potencia de transmisión.

## Páginas relacionadas

- [Aplicaciones incluidas en Unleashed](/es/apps/catalog)
- [Ajustes](/es/start/settings)
