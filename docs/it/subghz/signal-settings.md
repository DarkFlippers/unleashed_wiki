---
title: Signal Settings
order: 95
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-src]
---
# Signal Settings

**Signal Settings** modifica un segnale che hai già salvato: la sua modalità contatore, il contatore rolling corrente
e il codice del tasto. È una piccola schermata per utenti esperti, nascosta se Debug non è attivo, e quasi tutto al
suo interno funziona solo sui pochi protocolli che supportano le [modalità contatore](/it/subghz/counter-mode).

## Dove si trova {#where}

È una voce nel menu di un segnale salvato, non una voce del menu principale di Sub-GHz. Apri un file da
`Sub-GHz → Saved` (oppure dall'[Archive](/it/apps/archive)) e il menu è questo:

`Emulate` · `Rename` · `Delete` · `Signal Settings`

## Come farla comparire {#enable}

`Signal Settings` viene aggiunto a quel menu solo mentre **Debug** è attivo. Con Debug disattivato la voce non c'è.

- Via rapida: tieni premuto <kbd>↓</kbd> sul desktop, poi tieni premuto <kbd>OK</kbd> sulla schermata informativa
  ([Desktop → Schermata informativa del dispositivo](/it/start/desktop#info-screen)).
- Oppure `Settings → System → Debug` = `ON` ([Impostazioni](/it/start/settings)).

## Le tre voci {#items}

![Signal Settings: Counter Mode, Edit Counter e Edit Button](/screens/subghz/signal_settings.png)

| Voce | Cosa fa |
|---|---|
| `Counter Mode` | <kbd>←</kbd>/<kbd>→</kbd> scelgono `System` (modalità 0) oppure `Mode 1` … fino al limite del protocollo. La scelta viene scritta subito nel file `.sub` come riga `CounterMode:` e il file viene ricaricato; non si trasmette nulla |
| `Edit Counter` | <kbd>OK</kbd> apre un campo esadecimale per il contatore corrente, intitolato `Enter <N>-bits counter in HEX` con la lunghezza del contatore del protocollo: 4 cifre esadecimali (2 byte) fino a 16 bit, 8 cifre (4 byte) oltre |
| `Edit Button` | <kbd>OK</kbd> apre un campo esadecimale per il codice del tasto, intitolato `Enter <N>-bits button in HEX`: sempre un byte, 2 cifre esadecimali |

Il valore che ogni voce contiene al momento è mostrato nella sua riga, in esadecimale. Cosa fanno le modalità
contatore al contatore, e come impostarne una modificando il file su un PC, sono spiegati in
[Modalità contatore](/it/subghz/counter-mode#modes-by-protocol).

::: warning Confermare una modifica del contatore o del tasto trasmette
`Edit Counter` e `Edit Button` scrivono il file passando per il percorso di trasmissione: il firmware avvia un invio
con il nuovo valore e lo ferma immediatamente, e il file viene riscritto quando quell'invio si ferma. La radio resta
attiva per un istante, quindi fallo lontano dal ricevitore che non vuoi azionare.

Il contatore che digiti viene salvato esattamente così come lo hai digitato: per quella singola riscrittura la
modalità contatore e il passo [Counter Incr.](/it/subghz/settings) non vengono applicati. Una modifica del tasto,
invece, porta il passo a 0 per la riscrittura, così cambiare il tasto lascia il contatore dov'era.

Se l'invio viene rifiutato — una frequenza su cui questo firmware non trasmette — il file non viene scritto
affatto.
:::

## Protocolli con le modalità contatore {#protocols}

`Counter Mode` è sbloccato per cinque protocolli. `System` è la modalità 0, quella normale:

| Protocollo | Scelte |
|---|---|
| Nice FloR-S | `System`, `Mode 1`–`Mode 2` |
| CAME Atomo | `System`, `Mode 1`–`Mode 3` |
| Alutech AT-4N | `System`, `Mode 1`–`Mode 2` |
| KeeLoq | `System`, `Mode 1`–`Mode 10` |
| `Phoenix_V2` (V2 Phoenix) | `System`, `Mode 1`–`Mode 2` |

Il confronto avviene sulla riga `Protocol:` del file. Su tutti gli altri protocolli la voce è bloccata.

## Voci bloccate {#locked}

Una voce bloccata non può essere aperta né modificata; premendola compare `Not available for this protocol !`

- `Counter Mode` — il protocollo del file non è uno dei cinque qui sopra.
- `Edit Counter` — il protocollo non ha un contatore. Può dipendere anche dal produttore: su KeeLoq la voce è
  bloccata per `AN-Motors`, che ha solo un pseudo-contatore, e per `Unknown`.
- `Edit Button` — il protocollo non ha un codice del tasto nella sua trama.

`Edit Button` è sbloccato anche sui protocolli statici che portano un codice tasto — Princeton, Dooya, GangQi,
Hollarm, Nord ICE, Proteco e Roger — e lì funziona esattamente come su un segnale a codice rolling.

## Pagine correlate {#related}

- [Modalità contatore](/it/subghz/counter-mode) — cosa fa ogni modalità e la riga `CounterMode:` nel file
- [Codici rolling](/it/subghz/rolling-codes) · [Formato dei file .sub](/it/subghz/file-format)
- [Desktop](/it/start/desktop#info-screen) — la scorciatoia per Debug · [Impostazioni](/it/start/settings) — Debug
  nei menu
