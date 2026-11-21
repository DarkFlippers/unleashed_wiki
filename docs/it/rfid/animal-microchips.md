---
title: Microchip per animali
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Microchip per animali (FDX-B, FDX-A)

I microchip per animali domestici sono transponder RFID grandi come un granello di riso, impiantati sotto la pelle.
Quando un lettore li alimenta trasmettono un ID che può essere cercato nelle banche dati per il ritrovamento degli
animali. Flipper Zero legge i due tipi LF più diffusi:

| Tipo | Nome nel Flipper | Descrizione |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, ID a 15 cifre; il tipo più comune; alcuni chip riportano anche la temperatura corporea |
| **FDX-A** | `FDX-A` (FECAVA) | Chip più vecchi a 10 cifre, non ISO |

La maggior parte dei chip per animali lavora a **134,2 kHz**, mentre l'antenna del Flipper è accordata su 125 kHz:
la distanza di lettura è quindi ridotta, intorno a **1 cm**. I microchip nella gamma 110–140 kHz si possono leggere,
ma solo più da vicino.

::: tip Unleashed
La documentazione ufficiale consiglia di usare *Read ASK*. Unleashed genera per questi chip un vero campo a
**134,2 kHz**:
- **Read** esegue ora una terza passata, **134kHz**, dopo ASK e PSK;
- `Extra Actions → Read FDX-B (Animals)` resta su 134,2 kHz per tutto il tempo — la scelta migliore per i chip
  debolmente accoppiati;
- il nome del paese per FDX-B viene cercato in `/ext/lfrfid/assets/iso3166.lfrfid`.
:::

## Leggere il chip di un animale

1. Vai su `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. Lo schermo mostra *Reading FDX-B*.
2. Individua il chip:
   - cani e gatti: di solito sotto la pelle **tra le scapole**; nell'Europa continentale spesso **a metà del lato
     sinistro del collo**. I chip possono migrare un poco;
   - tasta delicatamente con la punta delle dita cercando un oggetto duro a forma di granello di riso, poi appoggiaci
     sopra il centro del retro del Flipper.
3. Tieni il Flipper fermo per circa **3 secondi** in ogni punto. Se non succede nulla, spostalo a piccoli passi su
   tutta la zona, poi ruota il Flipper di 90° e ripeti.
4. Osserva il LED: giallo/verde indica che un segnale viene captato — resta in quella posizione.
5. Una volta decodificato compare la schermata dei risultati. <kbd>→</kbd> **More → Save** per conservarlo.

## Cosa mostra il Flipper per FDX-B

| Campo | Significato |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | codice del paese a 3 cifre (ISO 3166-1 numerico) o codice del produttore + ID nazionale a 12 cifre — il numero a 15 cifre da cercare |
| Country Code / Country | Il codice e il relativo nome dalla tabella ISO 3166 |
| Temperature | Per i chip con termometro, in °C e °F; `---` se assente |
| Animal | Flag di applicazione animale |
| Visual Start Digit, Replacement Number, User Info, RFU | Campi di intestazione del frame ISO |
| Data Block | Present / Absent — blocco dati aggiuntivo (per esempio la temperatura) |
| RUDI Bit | Yes / No |

FDX-A mostra un `ID` di 10 cifre esadecimali e il campo `Parity`.

::: warning
La temperatura rilevata dal chip non sostituisce un termometro vero e proprio.
:::

## Cercare l'ID

Inserisci l'ID a 15 cifre in una banca dati per il ritrovamento degli animali, per esempio:
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — Stati Uniti e Canada
- [Europetnet](https://www.europetnet.com/) — Europa
- [PETMAXX](http://www.petmaxx.com/) — in tutto il mondo

Oppure rivolgiti al tuo veterinario o all'anagrafe animale locale.

## Se il chip non viene trovato

- Fuori portata — usa passi più piccoli e resta più a lungo in ogni punto.
- Il chip è migrato — esamina un'area più ampia.
- Metallo o apparecchi elettronici nelle vicinanze — allontanati da essi.
- L'animale può avere un chip a 13,56 MHz — prova con [NFC](/it/nfc/read).
- Chip non supportato — chiedi a un veterinario di leggerlo.

Le chiavi FDX-B possono anche essere [emulate o scritte](/it/rfid/write) (vergini T5577 ed EM4305, che esistono anche
come tag in vetro), per esempio per provare una porta per animali.

## Pagine correlate

- [Lettura](/it/rfid/read) · [Protocolli](/it/rfid/protocols) · [Scrittura](/it/rfid/write)
