---
title: Combinazioni di tasti
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/KeyCombo.md, https://docs.flipper.net/zero/basics/reboot, https://docs.flipper.net/zero/basics/firmware-update/firmware-recovery, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/src]
sources: [unleashed-docs, flipper-docs, unleashed-src]
---
# Combinazioni di tasti

A volte il Flipper smette di rispondere per un problema software. Queste combinazioni di pulsanti lo resettano a
livello hardware o lo avviano in modalità DFU (aggiornamento del firmware), senza l'aiuto del firmware bloccato.

## Riepilogo rapido

| Obiettivo | Combinazione | USB |
|---|---|---|
| Riavviare un Flipper bloccato | <kbd>←</kbd> + <kbd>BACK</kbd>, ~2–5 s | qualsiasi |
| Reset dell'alimentazione | <kbd>BACK</kbd>, 30 s | **scollegata** |
| DFU tramite bootloader Flipper (con segnalazione) | <kbd>←</kbd> + <kbd>BACK</kbd>, rilascia <kbd>BACK</kbd>, tieni <kbd>←</kbd> fino al LED blu | qualsiasi |
| DFU tramite bootloader ST (senza segnalazione) | <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd>, rilascia <kbd>BACK</kbd> e <kbd>←</kbd> | qualsiasi |
| Schermata di reset di PIN / impostazioni | tieni premuto <kbd>↑</kbd> mentre il Flipper si avvia | — |

## Combinazioni di base

### Reset hardware

1. Tieni premuti <kbd>←</kbd> e <kbd>BACK</kbd> per un paio di secondi.
2. Rilascia entrambi.

Questo porta a massa la linea di reset dell'MCU. Percorso: tasti → DD8 (NC7SZ32M5X, porta OR) → DD1 (STM32WB55, MCU).

**Non funziona se:** il blocco di debug dell'MCU è attivo e tiene la linea di reset dall'interno.

### Reset hardware dell'alimentazione

1. Scollega il cavo USB e qualsiasi alimentatore esterno. Verifica due volte che l'USB sia davvero scollegata.
2. Tieni premuto <kbd>BACK</kbd> per **30 secondi**. Funziona solo con l'USB scollegata.
3. Rilascia <kbd>BACK</kbd>.

Questo spegne e riaccende la linea di alimentazione SYS tramite il chip di ricarica DD6 (bq25896).

**Non funziona se:** è collegata l'alimentazione su USB o su 5V_ext.

### DFU software

Tieni premuto <kbd>←</kbd> mentre il Flipper si avvia. Entra in modalità DFU tramite il **bootloader Flipper**.

**Non funziona se:** il bootloader Flipper è danneggiato o assente.

### DFU hardware

Tieni premuto <kbd>OK</kbd> mentre il Flipper si avvia. Entra in modalità DFU tramite il **bootloader ST** integrato
nell'MCU.

**Non funziona se:** gli Option Bytes sono danneggiati o impostati per ignorare il tasto <kbd>OK</kbd>.

## Combinazioni DFU

### Reset hardware + DFU software

1. Tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> per un paio di secondi.
2. Rilascia <kbd>BACK</kbd>.
3. Il dispositivo entra in DFU **con segnalazione**: LED blu e schermata DFU.
4. Rilascia <kbd>←</kbd>.

**Non funziona se:** il blocco di debug dell'MCU tiene la linea di reset, oppure il bootloader Flipper è danneggiato o
assente.

### Reset hardware + DFU hardware

1. Tieni premuti <kbd>←</kbd> + <kbd>BACK</kbd> + <kbd>OK</kbd> per un paio di secondi.
2. Rilascia <kbd>BACK</kbd> e <kbd>←</kbd>.
3. Il dispositivo entra in DFU **senza segnalazione**. Lo schermo resta spento: è normale.

**Non funziona se:** il blocco di debug dell'MCU tiene la linea di reset, oppure gli Option Bytes sono danneggiati o
impostati per ignorare <kbd>OK</kbd>.

### Reset hardware dell'alimentazione + DFU software

1. Scollega l'USB e qualsiasi alimentazione esterna.
2. Tieni premuti <kbd>BACK</kbd> + <kbd>←</kbd> per 30 secondi.
3. Rilascia <kbd>BACK</kbd>.
4. Il dispositivo entra in DFU con segnalazione (LED blu + schermata DFU).
5. Rilascia <kbd>←</kbd>.
6. Collega l'USB.

**Non funziona se:** è collegata l'alimentazione su USB o su 5V_ext, oppure il bootloader Flipper è danneggiato o
assente.

### Reset hardware dell'alimentazione + DFU hardware

1. Scollega l'USB e qualsiasi alimentazione esterna.
2. Tieni premuti <kbd>BACK</kbd> + <kbd>OK</kbd> per 30 secondi.
3. Rilascia <kbd>BACK</kbd> e <kbd>OK</kbd>.
4. Il dispositivo entra in DFU senza segnalazione.
5. Collega l'USB.

**Non funziona se:** è collegata l'alimentazione su USB o su 5V_ext, oppure gli Option Bytes sono danneggiati o
impostati per ignorare <kbd>OK</kbd>.

## Cosa fare in modalità DFU

Collega il Flipper a un computer. Viene rilevato come **DFU in FS Mode** (Windows/macOS) o
**STMicroelectronics STM Device in DFU Mode** (`lsusb` su Linux). Poi ripara il firmware con qFlipper:
[Ripristino](/it/start/recovery#firmware-recovery).

## Se niente funziona {#if-nothing-helps}

- Assicurati che la batteria sia carica: lascialo in carica per un'ora.
- Scollega e ricollega la batteria (richiede l'apertura del case).
- Programma il dispositivo con un ST-Link o un altro programmatore SWD.

Se dopo tutto questo il dispositivo ancora non funziona, il problema **non è software**.
