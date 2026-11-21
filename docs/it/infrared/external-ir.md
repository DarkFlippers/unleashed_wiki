---
title: Moduli IR esterni
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/targets/furi_hal_include/furi_hal_infrared.h, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/infrared]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Moduli IR esterni (GPIO)

I tre LED IR integrati vanno bene per un soggiorno, ma la portata è limitata. Per avere più potenza puoi collegare un
**trasmettitore IR esterno** (una schedina con LED più potenti e un transistor di pilotaggio) al connettore GPIO.
L'app Infrared trasmette allora attraverso di esso invece che con i LED integrati. I telecomandi universali, i
telecomandi salvati, l'app mobile e il pulsante "Send" della schermata di acquisizione usano tutti l'uscita
selezionata.

::: tip Unleashed
Il supporto ai moduli IR esterni con rilevamento automatico è elencato tra le funzioni di Unleashed; la logica di
rilevamento in sé arriva dal firmware ufficiale, quindi il comportamento descritto qui è lo stesso su entrambi.
:::

## Collegamenti

| Pin del modulo | Pin GPIO del Flipper |
|---|---|
| Signal / IN | **2 (A7)** |
| VCC | **1 (5V)**, alimentato quando "5V on GPIO" è ON, oppure 9 (3V3) per i moduli a 3,3 V |
| GND | 8, 11 o 18 (GND) |

Il pin 2 porta lo **stesso segnale modulato** (portante compresa, tipicamente 38 kHz) che normalmente pilota i LED
interni, quindi il modulo ha bisogno solo di uno stadio di pilotaggio e dei LED, non di un modulatore proprio. Vedi
[Pinout GPIO](/it/gpio/pinout) per la disposizione del connettore.

::: warning
L'apprendimento (la ricezione) usa sempre il ricevitore integrato. Il modulo esterno è solo in trasmissione.
:::

## GPIO Settings

Vai in `Main Menu → Infrared → GPIO Settings`. Ci sono due opzioni:

| Opzione | Valori | Significato |
|---|---|---|
| **Signal Output** | `Flipper` | LED IR integrati (predefinito). |
| | `2 (A7)` | Trasmette sempre sul pin GPIO 2. |
| | `Detect` | Rileva automaticamente un modulo esterno sul pin 2 ogni volta che l'app Infrared parte. |
| **5V on GPIO** | `OFF` / `ON` | Commuta i 5 V sul pin GPIO 1 per alimentare il modulo. Con `Detect` mostra **`Auto`** ed è gestito automaticamente. |

Le impostazioni vengono salvate quando lasci la schermata, in `/ext/infrared/.infrared.settings`, e applicate ogni
volta che l'app Infrared parte. Quando esci dall'app Infrared, l'uscita torna ai LED integrati e i 5 V vengono
spenti di nuovo, così il modulo non consuma batteria nelle altre app.

### Passo per passo

1. Collega il modulo (Signal → pin 2, VCC → pin 1, GND → pin 8/11/18).
2. Apri `Infrared → GPIO Settings`.
3. Imposta **Signal Output** su `Detect` (oppure su `2 (A7)` se il rilevamento non funziona con il tuo modulo).
4. Con `2 (A7)`, imposta **5V on GPIO** su `ON` se il modulo è alimentato dal pin 1.
5. Premi <kbd>Back</kbd>. Invia un qualsiasi pulsante salvato o un telecomando universale; i LED del modulo ora
   dovrebbero trasmettere.

## Come funziona il rilevamento automatico

Quando è selezionato `Detect`, il firmware abilita brevemente un **pull-up debole** sul pin 2 e lo rilegge:

- se il pin resta **basso**, è collegato qualcosa con un pull-down, quindi si presume un modulo esterno. L'uscita va
  sul pin 2 e i **5 V sul GPIO vengono attivati automaticamente**;
- se il pin si legge **alto**, non c'è nulla collegato e vengono usati i LED integrati.

Funziona al meglio con i moduli il cui driver dei LED è un **MOSFET con un pull-down forte** sul gate, oppure un
**BJT** per pilotare i LED IR. Per essere rilevato, il modulo **deve tirare il pin a 0,9 V o meno**. Se il tuo modulo
non ha un pull-down, scegli `2 (A7)` manualmente e attiva tu i 5 V.

Il rilevamento avviene all'avvio dell'app Infrared (e quando selezioni `Detect`). Se colleghi il modulo mentre l'app
è aperta, riseleziona `Detect` o riavvia l'app.

## Risoluzione dei problemi

| Problema | Cosa provare |
|---|---|
| `Detect` usa sempre i LED integrati | Il modulo non tira il pin 2 abbastanza in basso (≤ 0,9 V). Usa `2 (A7)` e attiva manualmente `5V on GPIO`. |
| Il LED del modulo non si accende | Controlla il VCC: con `2 (A7)` i 5 V devono essere ON. Controlla il GND. Guarda i LED attraverso la fotocamera di un telefono durante l'invio. |
| La batteria si scarica rapidamente | Un modulo potente assorbe molto dai 5 V. Scollegalo quando non lo usi. |

## Pagine correlate

- [Pinout GPIO](/it/gpio/pinout)
- [Moduli GPIO](/it/gpio/external-modules)
- [Apprendere e inviare segnali](/it/infrared/read)
- [Telecomandi universali](/it/infrared/universal-remotes)
