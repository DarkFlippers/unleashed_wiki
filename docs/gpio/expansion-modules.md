---
title: Expansion modules
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Expansion modules

An **expansion module** is a third-party board on the GPIO header that the Flipper detects automatically and lets
control it over **RPC** (the same protocol qFlipper and the mobile app use). The [Video Game Module](/gpio/video-game-module)
is the best-known example. Detection and the link are handled by the firmware's `expansion` service and the
**Expansion Module Protocol** described below.

## Setting: which UART to listen on

1. Open `Main Menu → Settings → Expansion Modules`.
2. Set `Listen UART`:
   - `USART` — pins 13 (TX) / 14 (RX). Required for the Video Game Module.
   - `LPUART` — pins 15 (TX) / 16 (RX).
   - `None` — detection off; the Flipper ignores modules.
3. Press <kbd>BACK</kbd>. The choice is saved and applied immediately.

| UART | TX pin | RX pin |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip When to choose None
If you use the same UART for something else (a Wi-Fi board, GSM, GPS, the USB-UART bridge) and see odd behaviour,
set `Listen UART` to `None` or to the other UART. Apps that take over the serial port pause detection while they run.
:::

## Expansion Module Protocol (for module developers)

A byte-oriented, synchronous, request-response protocol over the UART, with module detection, baud-rate negotiation,
an XOR checksum and transparent forwarding of RPC traffic.

### Terms

- **Host** — the Flipper. **Device / module** — the expansion module.
- **Timeout interval, Tto = 250 ms** — inactivity treated as a lost connection.
- **Baud rate switch dead time, Tdt = 25 ms** — no traffic allowed right after a speed change.

### Frame structure

| Header (1 byte) | Contents (0+ bytes) | Checksum (1 byte) |
|---|---|---|
| Frame type | Payload | XOR of all previous bytes, initial value 0 |

| Type | Header | Contents | Purpose |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Keeps an idle connection alive |
| STATUS | `0x02` | error code (1 byte) | Confirms every received frame |
| BAUD RATE | `0x03` | baud rate (4 bytes) | Negotiates speed |
| CONTROL | `0x04` | command (1 byte) | Starts/stops RPC, controls 5 V |
| DATA | `0x05` | size (1 byte, `0x00`–`0x40`) + up to 64 data bytes | Carries RPC data |

STATUS error codes: `0x00` OK, `0x01` unknown error, `0x02` baud rate not supported.

CONTROL commands:

| Command | Meaning | Allowed when |
|---|---|---|
| `0x00` | Start RPC session | RPC not active |
| `0x01` | Stop RPC session | RPC active |
| `0x02` | Enable OTG (5 V) on GPIO | RPC not active (otherwise use RPC messages) |
| `0x03` | Disable OTG (5 V) on GPIO | RPC not active (otherwise use RPC messages) |

### Connection flow

1. **The module starts it** by briefly pulling the Flipper's RX pin low.
2. The Flipper answers with a **HEARTBEAT**: ready.
3. Within Tto the module must send a **BAUD RATE** frame — always first, even if 9600 is fine. The initial speed is
   always **9600 baud**. The Flipper answers STATUS OK or `0x02`; on refusal the module may offer other rates.
   Nothing else is allowed until negotiation succeeds.
4. Both sides switch speed; the module waits Tdt.
5. The module sends **CONTROL → Start RPC**, Flipper confirms with STATUS.
6. RPC requests go in **DATA** frames (split into 64-byte chunks; each chunk is confirmed by STATUS). RPC responses
   come back as DATA frames, which the module must confirm with STATUS.
7. When idle, the module sends **HEARTBEAT** more often than every Tto; the Flipper replies with HEARTBEAT.
8. **CONTROL → Stop RPC** ends the session. After Tto of silence the Flipper returns to the waiting state.

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

### Errors

On any detected error (bad checksum, unexpected frame) the side that noticed it **stops all communication and resets**.
The other side times out after Tto and the connection is re-established from step 1.

### Programmatic control

Firmware apps can call `expansion_enable()` / `expansion_disable()` (and `expansion_set_listen_serial()`) from the
`expansion` service instead of the Settings screen. A debug app, `expansion_test`, is included in the source tree as a
reference module implementation.

## Related

- [Video Game Module](/gpio/video-game-module)
- [GPIO pinout](/gpio/pinout)
- [External modules](/gpio/external-modules)
