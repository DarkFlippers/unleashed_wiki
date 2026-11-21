---
title: Frequenze e portata
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Frequenze e portata

Il Flipper Zero dialoga con il mondo sotto 1 GHz tramite un transceiver **TI CC1101**. Questa pagina descrive le bande
supportate dal chip, l'elenco di frequenze incluso in Unleashed, come funzionano i limiti di trasmissione in Unleashed
e come aggiungere frequenze personalizzate.

## Bande hardware

Il datasheet del CC1101 specifica tre bande:

| Banda | Uso tipico |
|---|---|
| 300–348 MHz | Porte di garage e cancelli statunitensi (famiglia 300, 310, 315, 318, 390 MHz), radiochiavi per auto |
| 387–464 MHz | Telecomandi LPD433 a 433.92 MHz, sbarre, sensori, campanelli (gran parte di Europa/CSI) |
| 779–928 MHz | Dispositivi a 868 MHz (SRD UE) e 915 MHz (ISM USA) |

Unleashed allarga leggermente la finestra di trasmissione predefinita, così da far funzionare le comuni frequenze
350 MHz e 467.75 MHz.

## Limiti di trasmissione in Unleashed

::: tip Unleashed
Il firmware di serie blocca la trasmissione sulle frequenze consentite nella **regione** rilevata durante
l'aggiornamento (per esempio solo 433.05–434.79 e 868.15–868.55 MHz in UE/Russia). **Unleashed rimuove
completamente il blocco regionale.** Puoi trasmettere su qualsiasi frequenza supportata dal chip, senza passaggi
aggiuntivi.
:::

Resta valido un limite di sicurezza hardware (da `furi_hal_subghz.c`):

| Modalità | Intervalli TX consentiti |
|---|---|
| Predefinita | 300–350 MHz, 387–467.75 MHz, 779–928 MHz |
| Estesa ("dangerous") | 281–361 MHz, 378–481 MHz, 749–962 MHz |

Se provi a trasmettere fuori dall'intervallo consentito, il Flipper rifiuta di farlo.

### Estendere la portata (pericoloso) {#extended-range}

::: danger
Trasmettere fuori dalle specifiche del CC1101 può **danneggiare il chip radio**. Né il team di Flipper né gli
sviluppatori di Unleashed sono responsabili dei danni. Quasi a nessuno serve: l'intervallo predefinito copre già
praticamente ogni telecomando reale.
:::

1. Collega la scheda SD a un PC (oppure usa qFlipper / il file manager dell'app mobile).
2. Apri `/ext/subghz/assets/dangerous_settings`. Il contenuto è simile a questo:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Cambia `false` in `true`, salva il file e riavvia il Flipper (l'impostazione viene letta all'avvio).

Vedi anche [Impostazioni pericolose](/it/start/dangerous-settings).

## Elenco di frequenze predefinito

Sono le frequenze che puoi scorrere con <kbd>←</kbd> <kbd>→</kbd> in **Read**, **Read RAW** → `Config` e a cui il
Frequency Analyzer arrotonda. Il valore predefinito è **433.92 MHz**.

| 300–350 MHz | 387–467.75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (prima LPD433), 433.220, 433.420, 433.657070, 433.889, **433.920** (LPD433 centrale, predefinita), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (ultima LPD433), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Elenco dell'hopping

Quando **Hopping** è attivo, il ricevitore cicla soltanto su un elenco breve (con un elenco lungo perderebbe segnali):

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulazioni (preset)

La frequenza da sola non basta: il Flipper non è un SDR, la modulazione gli va indicata in anticipo.
Preset integrati:

| Nome nel menu | Preset nel file `.sub` | Significato |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, banda 270 kHz |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, banda 650 kHz — **predefinito, usato dalla maggior parte dei telecomandi** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, deviazione 2.38 kHz |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, deviazione 47.6 kHz |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, deviazione 12 kHz (per esempio Cardin S449, Sommer) |

Puoi aggiungere preset personalizzati (per esempio `FM15k`, `Pagers`) — vedi [Formati dei file](/it/subghz/file-format#setting-user).

## Aggiungere le proprie frequenze {#adding-frequencies}

1. Sulla scheda SD, vai in `/ext/subghz/assets/`.
2. Rinomina `setting_user.example` in `setting_user` (i file `_user` sopravvivono agli aggiornamenti del firmware).
3. Aggiungi righe in questo formato — sempre 9 cifre, in Hz:
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Riavvia l'app Sub-GHz.

Regole da conoscere:

- Le frequenze dell'utente vengono **aggiunte dopo** l'elenco predefinito: scorri fino in fondo all'elenco per trovarle.
- `Hopper_frequency` aggiunge una frequenza all'hopping. Mantieni corto l'elenco dell'hopper. Ripetere una frequenza
  fa sì che il Flipper la ascolti più spesso.
- Per usare **solo** le tue frequenze, cambia `#Add_standard_frequencies: true` in
  `Add_standard_frequencies: false`. In quel caso devi compilare **entrambi** gli elenchi (`Frequency:` e
  `Hopper_frequency:`) — altrimenti l'elenco principale resta vuoto.
- `Default_frequency: 433920000` imposta la frequenza con cui partono Read e Read RAW.

## Risoluzione dei problemi

- **Non si riceve nulla** — frequenza o modulazione sbagliate. Trova la frequenza con il
  [Frequency Analyzer](/it/subghz/frequency-analyzer), poi prova `AM650` e infine i preset FM.
- **La mia frequenza non è nell'elenco** — aggiungila a `setting_user` (vedi sopra). L'analizzatore arrotonderà comunque
  alla voce più vicina dell'elenco, quindi imposta manualmente il valore esatto in `Config`.
- **Trasmissione rifiutata** — la frequenza è fuori dalla finestra TX predefinita; controlla la tabella sopra. Non
  attivare la gamma estesa solo per "provare".

## Pagine correlate

- [Frequency Analyzer](/it/subghz/frequency-analyzer) · [Read](/it/subghz/read) · [Read RAW](/it/subghz/read-raw)
- [Radio Settings](/it/subghz/settings) · [Formati dei file](/it/subghz/file-format) · [Modulo CC1101 esterno](/it/subghz/external-cc1101)
