---
title: Expansion-Module
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Expansion-Module

Ein **Expansion-Modul** ist eine Fremdplatine an der GPIO-Stiftleiste, die der Flipper automatisch erkennt und über
**RPC** steuern lässt (dasselbe Protokoll, das qFlipper und die mobile App verwenden). Das bekannteste Beispiel ist das
[Video Game Module](/de/gpio/video-game-module). Erkennung und Verbindung übernehmen der Dienst `expansion` der
Firmware und das unten beschriebene **Expansion Module Protocol**.

## Einstellung: auf welchem UART gelauscht wird

1. Öffne `Main Menu → Settings → Expansion Modules`.
2. Setze `Listen UART`:
   - `USART` — Pin 13 (TX) / 14 (RX). Für das Video Game Module erforderlich.
   - `LPUART` — Pin 15 (TX) / 16 (RX).
   - `None` — Erkennung aus; der Flipper ignoriert Module.
3. Drücke <kbd>BACK</kbd>. Die Auswahl wird gespeichert und sofort angewendet.

| UART | TX-Pin | RX-Pin |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Wann None sinnvoll ist
Wenn du denselben UART für etwas anderes nutzt (ein Wi-Fi-Board, GSM, GPS, die USB-UART-Bridge) und seltsames Verhalten
beobachtest, setze `Listen UART` auf `None` oder auf den anderen UART. Apps, die den seriellen Port übernehmen, pausieren
die Erkennung, solange sie laufen.
:::

## Expansion Module Protocol (für Modulentwickler)

Ein byteorientiertes, synchrones Request-Response-Protokoll über den UART, mit Modulerkennung, Aushandlung der
Baudrate, einer XOR-Prüfsumme und transparenter Weiterleitung von RPC-Verkehr.

### Begriffe

- **Host** — der Flipper. **Device / Modul** — das Expansion-Modul.
- **Timeout-Intervall, Tto = 250 ms** — Inaktivität gilt als abgerissene Verbindung.
- **Totzeit beim Baudratenwechsel, Tdt = 25 ms** — direkt nach einer Geschwindigkeitsänderung ist kein Verkehr erlaubt.

### Frame-Aufbau

| Header (1 Byte) | Inhalt (0+ Bytes) | Prüfsumme (1 Byte) |
|---|---|---|
| Frame-Typ | Payload | XOR aller vorangehenden Bytes, Startwert 0 |

| Typ | Header | Inhalt | Zweck |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Hält eine ungenutzte Verbindung offen |
| STATUS | `0x02` | Fehlercode (1 Byte) | Bestätigt jedes empfangene Frame |
| BAUD RATE | `0x03` | Baudrate (4 Bytes) | Handelt die Geschwindigkeit aus |
| CONTROL | `0x04` | Befehl (1 Byte) | Startet/stoppt RPC, steuert 5 V |
| DATA | `0x05` | Größe (1 Byte, `0x00`–`0x40`) + bis zu 64 Datenbytes | Überträgt RPC-Daten |

STATUS-Fehlercodes: `0x00` OK, `0x01` unbekannter Fehler, `0x02` Baudrate nicht unterstützt.

CONTROL-Befehle:

| Befehl | Bedeutung | Erlaubt, wenn |
|---|---|---|
| `0x00` | RPC-Sitzung starten | RPC nicht aktiv |
| `0x01` | RPC-Sitzung beenden | RPC aktiv |
| `0x02` | OTG (5 V) am GPIO aktivieren | RPC nicht aktiv (sonst RPC-Nachrichten verwenden) |
| `0x03` | OTG (5 V) am GPIO deaktivieren | RPC nicht aktiv (sonst RPC-Nachrichten verwenden) |

### Verbindungsablauf

1. **Das Modul beginnt**, indem es den RX-Pin des Flippers kurz auf Low zieht.
2. Der Flipper antwortet mit einem **HEARTBEAT**: bereit.
3. Innerhalb von Tto muss das Modul ein **BAUD RATE**-Frame senden — immer als Erstes, selbst wenn 9600 passt. Die
   Anfangsgeschwindigkeit ist immer **9600 Baud**. Der Flipper antwortet mit STATUS OK oder `0x02`; bei Ablehnung kann
   das Modul andere Raten anbieten. Bis die Aushandlung gelingt, ist nichts anderes erlaubt.
4. Beide Seiten wechseln die Geschwindigkeit; das Modul wartet Tdt ab.
5. Das Modul sendet **CONTROL → Start RPC**, der Flipper bestätigt mit STATUS.
6. RPC-Anfragen laufen in **DATA**-Frames (in 64-Byte-Blöcke aufgeteilt; jeder Block wird mit STATUS bestätigt).
   RPC-Antworten kommen als DATA-Frames zurück, die das Modul mit STATUS bestätigen muss.
7. Im Leerlauf sendet das Modul häufiger als alle Tto ein **HEARTBEAT**; der Flipper antwortet mit HEARTBEAT.
8. **CONTROL → Stop RPC** beendet die Sitzung. Nach Tto ohne Verkehr kehrt der Flipper in den Wartezustand zurück.

```text
        MODULE               |            FLIPPER
-----------------------------+---------------------------
Pull down RX                -->
                            <--       Heartbeat
Baud Rate                   -->
                            <--       Status [OK | Error]
(both change baud rate, module waits Tdt)
Control [Start RPC]         -->
                            <--       Status [OK | Error]
Data [RPC Request]          -->
                            <--       Status [OK | Error]
                            <--       Data [RPC Response]
Status [OK | Error]         -->
Heartbeat                   -->
                            <--       Heartbeat
Control [Stop RPC]          -->
                            <--       Status [OK | Error]
```

### Fehler

Bei jedem erkannten Fehler (falsche Prüfsumme, unerwartetes Frame) **stellt die Seite, die ihn bemerkt hat, jede
Kommunikation ein und setzt sich zurück**. Bei der anderen Seite läuft nach Tto der Timeout ab, und die Verbindung wird
ab Schritt 1 neu aufgebaut.

### Programmgesteuerte Steuerung

Firmware-Apps können statt des Settings-Bildschirms `expansion_enable()` / `expansion_disable()` (und
`expansion_set_listen_serial()`) aus dem Dienst `expansion` aufrufen. Im Quellbaum liegt eine Debug-App,
`expansion_test`, als Referenzimplementierung eines Moduls.

## Siehe auch

- [Video Game Module](/de/gpio/video-game-module)
- [GPIO-Pinbelegung](/de/gpio/pinout)
- [Externe Module](/de/gpio/external-modules)
