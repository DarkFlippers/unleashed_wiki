---
title: Il delfino
order: 70
original: [https://docs.flipper.net/zero/basics/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/dolphin, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/dolphin_passport]
sources: [flipper-docs, unleashed-src]
---
# Il delfino

Sul desktop del Flipper vive un delfino digitale. Diventa più felice e sale di livello man mano che usi gli strumenti
del dispositivo, e le sue animazioni cambiano in base all'umore e al livello.

## Passport

Premi <kbd>→</kbd> sul desktop oppure vai in **Main Menu → Settings → Passport**. Il passaporto mostra:

- l'immagine del delfino per il livello attuale;
- il **nome**: il nome del dispositivo Flipper ([puoi cambiarlo](/it/start/custom-name));
- **Mood**: `Happy`, `Ok` o `Angry`;
- **Level** e una barra di avanzamento verso il livello successivo.

![Passport: il ritratto del delfino, il nome del Flipper, Mood: Happy, Level: 2 e la barra verso il livello 3](/screens/settings/passport.png)

## Umore

Il delfino diventa più triste quando non usi il Flipper. Il suo contatore "butthurt" sale di uno circa **ogni 48 ore**
di inattività. Usare le app riporta su l'umore, con un limite giornaliero alla velocità di recupero.

La **Happy Mode** mantiene il delfino felice in ogni caso:

**Main Menu → Settings → Desktop → Happy Mode** → **Enable**. Il messaggio dice: *"I will never get angry at you for
not spending time with me as long as this mode is enabled"* ("Non mi arrabbierò mai con te per non aver passato tempo
insieme, finché questa modalità è attiva"). Riaprilo e scegli **Disable** per disattivarla.

## Livelli e XP

| Livello | XP necessari |
|---|---|
| 1 | 0 |
| 2 | 300 |
| 3 | 1800 |

Ogni app può assegnare al massimo **20 XP al giorno**. Esistono 7 gruppi conteggiati (Sub-GHz, RFID, NFC, Infrared,
iButton, Bad USB e i "plugin", che includono U2F, GPIO e le app esterne), quindi il massimo è **140 XP al giorno**. I
limiti si azzerano ogni giorno.

### XP per azione

| App | Azione | XP |
|---|---|---|
| Sub-GHz | Ricevere e visualizzare un segnale | 1 |
| | Salvare un segnale | 3 |
| | Registrare in RAW | 1 |
| | Add manually | 2 |
| | Inviare un segnale salvato | 2 |
| | Usare il Frequency Analyzer | 1 |
| 125 kHz RFID | Entrare in Read | 1 |
| | Lettura riuscita | 3 |
| | Salvataggio | 3 |
| | Emulazione | 2 |
| | Add manually | 2 |
| NFC | Entrare in Read | 1 |
| | Lettura riuscita | 3 |
| | Salvataggio | 3 |
| | Detect Reader (Extract MF Keys) | 1 |
| | Emulazione | 2 |
| | Aggiungere una chiave manualmente | 2 |
| | Add manually e salvataggio / emulazione | 1 |
| Infrared | Inviare un segnale | 1 |
| | Apprendimento riuscito | 3 |
| | Salvataggio | 3 |
| iButton | Entrare in Read | 1 |
| | Lettura riuscita | 3 |
| | Salvataggio | 3 |
| | Emulazione | 2 |
| | Add manually | 2 |
| Bad USB | Eseguire uno script | 3 |
| U2F | Autorizzazione riuscita | 3 |
| GPIO | Aprire il bridge USB-UART | 1 |
| Apps | Avviare un'app esterna | 2 |
| | Avviare un gioco | 1 |
| | Vincere un gioco | 10 |

Quando il delfino raggiunge un nuovo livello, il Flipper mostra una notifica di passaggio di livello e le animazioni
del desktop cambiano.

## Dove è salvato lo stato

XP, livello e umore del delfino sono conservati in `.dolphin.state` nella memoria interna. Un
[reset di fabbrica](/it/start/recovery#factory-reset) riporta il delfino al livello 1.
