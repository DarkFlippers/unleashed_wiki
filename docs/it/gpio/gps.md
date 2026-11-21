---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Ci sono due modi per dare una posizione al Flipper:

| Opzione | Hardware | Come funziona |
|---|---|---|
| **Servizio GPS (posizione dal companion)** | Nessuno: un telefono o un computer collegato via USB o Bluetooth | Le app chiedono la posizione all'app companion collegata tramite RPC |
| **Modulo GPS NMEA** | Un ricevitore GPS seriale sulla UART del GPIO | Il plugin `[NMEA] GPS` legge le frasi NMEA dal modulo |

## Servizio GPS (posizione dal companion)

::: tip Unleashed
Il firmware Unleashed contiene un servizio di sistema `gps` (record `gps`, avviato al boot). Non usa nessun pin GPIO:
inoltra le richieste di posizione sulla **sessione RPC** attiva (USB o Bluetooth) all'app companion, che risponde con
la posizione del telefono o del computer.
:::

Cosa ottiene un'app dal servizio:

| Campo | Unità |
|---|---|
| Latitudine, longitudine | gradi × 10⁷ |
| Direzione | gradi × 100 (0…36000) |
| Velocità | mm/s |
| Altitudine | cm |
| Precisione | mm |
| Satelliti | numero |

Le app possono richiedere una singola posizione (`gps_request_location()`), un flusso a **1–10 Hz**
(`gps_request_stream()` / `gps_stop_stream()`) e possono anche inviare una posizione al companion
(`gps_report_location()`). Il companion può rispondere con un errore: non supportato, permesso negato, geolocalizzazione
disattivata, errore sconosciuto.

### Provarlo

Nei sorgenti sono incluse due app di esempio di @apfxtech (categoria `Examples`, compilate come FAP):

- **`[RPC] GPS Click`** — richiesta singola: premi <kbd>OK</kbd> per ottenere la posizione; mostra latitudine,
  longitudine, rotta, velocità, altitudine, satelliti e precisione. <kbd>BACK</kbd> esce.
- **`[RPC] GPS Stream`** — flusso continuo degli stessi dati.

Messaggi che potresti vedere:

| Messaggio | Significato |
|---|---|
| `No USB/BLE connection` | Nessuna sessione RPC: collega l'app companion via USB o Bluetooth |
| `GPS not available` | Il companion non supporta la geolocalizzazione |
| `Permission denied` | Il permesso di geolocalizzazione non è stato concesso all'app companion |
| `Location disabled` | I servizi di localizzazione sono disattivati sul telefono o sul computer |
| `No response` | Il companion non ha risposto in tempo |
| `Waiting for data...` | Flusso avviato, nessuna posizione ancora disponibile |

L'app companion deve supportare queste richieste GPS via RPC; verificalo con la tua app companion (vedi
[Mobile](/it/mobile/)).

Per chi sviluppa app: includi `<gps/gps.h>` e apri il record con `furi_record_open(RECORD_GPS)`; l'header contiene
anche funzioni di utilità per formattare coordinate, direzione, velocità, altitudine e precisione.

## Modulo GPS NMEA sulla UART

Per avere una posizione senza telefono, collega un ricevitore GPS seriale (la maggior parte dei moduli che emettono
frasi NMEA con logica a 3,3 V).

Collegamenti (USART):

| Pin del Flipper | Modulo GPS |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) o 1 (5V) | VCC (verifica l'intervallo di alimentazione del modulo) |
| 8, 11 o 18 (GND) | GND |

Poi apri il plugin `[NMEA] GPS` dai pacchetti di app extra. Configurazione, velocità in baud e moduli supportati sono
nel suo [README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
Il modulo GPS e gli altri utilizzatori della UART (schede Wi-Fi, SIM800, moduli di espansione, uscita dei log)
condividono i pin 13/14. Se il plugin non riceve dati, controlla
`Settings → Expansion Modules → Listen UART` e `Settings → System → Log Device`.
:::

## App

App che funzionano con un modulo GPS, tutte dai pacchetti:

| App | Pacchetto | Cosa fa |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Posizione da qualsiasi modulo GPS NMEA su UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Mostra e registra i dati dei moduli GPS u-blox via I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Tracker NMEA con navigazione a breadcrumb |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Browser di file che ordina i file per distanza dal punto in cui ti trovi |

Elenco completo delle app per i moduli: [Moduli e le loro app](/it/gpio/module-apps).

## Argomenti correlati

- [ESP32 e Wi-Fi](/it/gpio/esp32) — mappa di wardriving
- [Moduli esterni](/it/gpio/external-modules)
- [Pinout GPIO](/it/gpio/pinout)
