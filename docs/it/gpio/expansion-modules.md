---
title: Moduli di espansione
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/ExpansionModules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/expansion, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/expansion_settings_app, https://docs.flipper.net/zero/video-game-module/quick-start]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Moduli di espansione

Un **modulo di espansione** è una scheda di terze parti collegata al connettore GPIO che il Flipper rileva
automaticamente e alla quale consente di controllarlo via **RPC** (lo stesso protocollo usato da qFlipper e dall'app
mobile). Il [Video Game Module](/it/gpio/video-game-module) è l'esempio più noto. Il rilevamento e il collegamento
sono gestiti dal servizio `expansion` del firmware e dall'**Expansion Module Protocol** descritto qui sotto.

## Impostazione: quale UART mettere in ascolto

1. Apri `Main Menu → Settings → Expansion Modules`.
2. Imposta `Listen UART`:
   - `USART` — pin 13 (TX) / 14 (RX). Necessario per il Video Game Module.
   - `LPUART` — pin 15 (TX) / 16 (RX).
   - `None` — rilevamento disattivato; il Flipper ignora i moduli.
3. Premi <kbd>BACK</kbd>. La scelta viene salvata e applicata immediatamente.

| UART | Pin TX | Pin RX |
|---|---|---|
| USART | 13 | 14 |
| LPUART | 15 | 16 |

::: tip Quando scegliere None
Se usi la stessa UART per altro (una scheda Wi-Fi, GSM, GPS, il bridge USB-UART) e noti comportamenti strani, imposta
`Listen UART` su `None` oppure sull'altra UART. Le app che prendono il controllo della porta seriale sospendono il
rilevamento mentre sono in esecuzione.
:::

## Expansion Module Protocol (per chi sviluppa moduli)

Un protocollo orientato ai byte, sincrono, a richiesta-risposta sulla UART, con rilevamento del modulo, negoziazione
della velocità in baud, un checksum XOR e inoltro trasparente del traffico RPC.

### Terminologia

- **Host** — il Flipper. **Device / module** — il modulo di espansione.
- **Intervallo di timeout, Tto = 250 ms** — inattività trattata come connessione perduta.
- **Tempo morto al cambio di velocità, Tdt = 25 ms** — nessun traffico ammesso subito dopo un cambio di velocità.

### Struttura dei frame

| Header (1 byte) | Contenuto (0 o più byte) | Checksum (1 byte) |
|---|---|---|
| Tipo di frame | Payload | XOR di tutti i byte precedenti, valore iniziale 0 |

| Tipo | Header | Contenuto | Scopo |
|---|---|---|---|
| HEARTBEAT | `0x01` | — | Mantiene attiva una connessione inattiva |
| STATUS | `0x02` | codice di errore (1 byte) | Conferma ogni frame ricevuto |
| BAUD RATE | `0x03` | velocità in baud (4 byte) | Negozia la velocità |
| CONTROL | `0x04` | comando (1 byte) | Avvia/arresta l'RPC, controlla i 5 V |
| DATA | `0x05` | dimensione (1 byte, `0x00`–`0x40`) + fino a 64 byte di dati | Trasporta i dati RPC |

Codici di errore STATUS: `0x00` OK, `0x01` errore sconosciuto, `0x02` velocità in baud non supportata.

Comandi CONTROL:

| Comando | Significato | Ammesso quando |
|---|---|---|
| `0x00` | Avvia la sessione RPC | L'RPC non è attivo |
| `0x01` | Arresta la sessione RPC | L'RPC è attivo |
| `0x02` | Attiva l'OTG (5 V) sul GPIO | L'RPC non è attivo (altrimenti usa i messaggi RPC) |
| `0x03` | Disattiva l'OTG (5 V) sul GPIO | L'RPC non è attivo (altrimenti usa i messaggi RPC) |

### Sequenza di connessione

1. **È il modulo a iniziare**, portando brevemente a livello basso il pin RX del Flipper.
2. Il Flipper risponde con un **HEARTBEAT**: pronto.
3. Entro Tto il modulo deve inviare un frame **BAUD RATE** — sempre per primo, anche se 9600 va bene. La velocità
   iniziale è sempre **9600 baud**. Il Flipper risponde con STATUS OK oppure `0x02`; in caso di rifiuto il modulo può
   proporre altre velocità. Nient'altro è ammesso finché la negoziazione non va a buon fine.
4. Entrambi i lati cambiano velocità; il modulo attende Tdt.
5. Il modulo invia **CONTROL → Start RPC**, il Flipper conferma con STATUS.
6. Le richieste RPC viaggiano in frame **DATA** (divisi in blocchi da 64 byte; ogni blocco è confermato da STATUS). Le
   risposte RPC tornano come frame DATA, che il modulo deve confermare con STATUS.
7. Quando non c'è traffico, il modulo invia **HEARTBEAT** più spesso di ogni Tto; il Flipper risponde con HEARTBEAT.
8. **CONTROL → Stop RPC** chiude la sessione. Dopo Tto di silenzio il Flipper torna in attesa.

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

### Errori

In presenza di qualsiasi errore rilevato (checksum errato, frame inatteso) il lato che lo ha notato **interrompe ogni
comunicazione e si reimposta**. L'altro lato va in timeout dopo Tto e la connessione viene ristabilita dal punto 1.

### Controllo programmatico

Le app del firmware possono chiamare `expansion_enable()` / `expansion_disable()` (e
`expansion_set_listen_serial()`) del servizio `expansion` invece di usare la schermata delle impostazioni. Nei
sorgenti è incluso un app di debug, `expansion_test`, come implementazione di riferimento di un modulo.

## Argomenti correlati

- [Video Game Module](/it/gpio/video-game-module)
- [Pinout GPIO](/it/gpio/pinout)
- [Moduli esterni](/it/gpio/external-modules)
