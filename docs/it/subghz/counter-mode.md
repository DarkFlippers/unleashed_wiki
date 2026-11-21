---
title: Modalità contatore
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzCounterMode.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/signal_settings]
sources: [unleashed-docs, unleashed-src]
---
# Modalità contatore (sperimentali)

**Counter Mode** cambia il modo in cui il contatore rolling avanza quando il Flipper trasmette un segnale a codice
rolling salvato. L'obiettivo: un clone del tuo telecomando originale che **non entri in conflitto** con esso, così da
poter usare sia il Flipper sia l'originale con lo stesso ricevitore senza desincronizzazioni. (Contesto:
[Codici rolling](/it/subghz/rolling-codes).)

::: tip Unleashed
Le modalità contatore sono una funzione esclusiva di Unleashed. Protocolli supportati: **Nice FloR-S, CAME Atomo,
Alutech AT-4N, KeeLoq, V2 Phoenix**.
:::

::: danger Leggi prima di usarle
Non fare esperimenti con apparecchiature a cui non hai accesso. Se non sei sicuro di quale modalità funzioni per il tuo
sistema e **non puoi riprogrammare il tuo telecomando originale** nel ricevitore, non usare queste modalità. Potrebbero
desincronizzare o bloccare il tuo telecomando. Se puoi provare sul tuo ricevitore, comunica al team di Unleashed cosa
funziona (issue su GitHub / chat della comunità).
:::

## Come impostare una modalità

### Opzione 1 — modificare il file `.sub`

1. Copia il file da `/ext/subghz/` su un PC (qFlipper, app mobile o lettore di schede).
2. Aggiungi una riga alla fine:
   ```text
   CounterMode: X
   ```
   dove `X` è il numero della modalità. Attenzione allo spazio dopo i due punti.
3. Ricopia il file sul dispositivo.

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: Nice FloR-S
Bit: 52
Key: AA AA AA AA AA AA AA
CounterMode: 1
```

### Opzione 2 — Signal Settings sul Flipper

Con **Debug** attivo, il menu di un segnale salvato acquista una voce in più:
`Sub-GHz → Saved → <file> → Signal Settings`. La sua riga `Counter Mode` offre `System` (modalità 0) e `Mode 1` …
fino all'ultima modalità che il protocollo possiede, e scrive subito la tua scelta nel file. La stessa schermata
permette anche di modificare il contatore e il codice del tasto: vedi
[Signal Settings](/it/subghz/signal-settings).

## Modalità per protocollo {#modes-by-protocol}

La modalità 0 è sempre quella predefinita: si comporta come un normale telecomando, il contatore cresce del valore
globale [Counter Incr.](/it/subghz/settings) (predefinito +1) e torna a 0 dopo `0xFFFF`.

### Nice FloR-S

| Modalità | Contatore | Note |
|---|---|---|
| 0 | +moltiplicatore | predefinita |
| 1 | `0x0001 / 0xFFFE` | ricevitore **floxi2r** |
| 2 | `0x0000 / 0x0001` | ricevitore **ox2** |

### CAME Atomo

| Modalità | Contatore | Note |
|---|---|---|
| 0 | +moltiplicatore | predefinita |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | funziona con il CAME **RE432** esterno, forse con altri |
| 2 | `0x807B / 0x807C / 0x007B / 0x007C` | funziona con il CAME **RE432** esterno, forse con altri |
| 3 | congelato | il contatore non si incrementa |

### Alutech AT-4N

| Modalità | Contatore | Note |
|---|---|---|
| 0 | +moltiplicatore | predefinita |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | ricevitore **MCSW-3.3M** |
| 2 | `0x0000 … 0x0005` | altre schede ricevitore |

### KeeLoq

| Modalità | Contatore | Note |
|---|---|---|
| 0 | +moltiplicatore | predefinita |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` | potrebbe funzionare con alcuni sistemi |
| 2 | `+0x3333` per trasmissione (13107) | per esempio DoorHan |
| 3 | `0x8006 / 0x8007 / 0x0006 / 0x0007` | per esempio Hormann EcoStar |
| 4 | `0x807B / 0x807C / 0x007B / 0x007C` | per esempio Nice Smilo |
| 5 | `0x0000 / 0xFFFF` | alterna 0 e 65535 |
| 6 | congelato | il contatore non si incrementa |
| 7–10 | pacchetti di risincronizzazione forzata | DoorHan, Phantom / Hiland, vedi sotto |

#### Modalità 7–10: pacchetti di risincronizzazione forzata (DoorHan, Phantom / Hiland)

Queste modalità non fanno avanzare il contatore; ogni pressione invia un **pacchetto fisso** di codici. Un ricevitore
si risincronizza solo quando sente due trasmissioni con contatori **consecutivi**, quindi il pacchetto è costruito con
coppie consecutive, distanziate in modo che ogni hop resti dentro la finestra di risincronizzazione del ricevitore e
che le coppie insieme coprano tutto lo spazio del contatore. Questo riporta il ricevitore in sincronia da qualsiasi
stato. Il contatore nel tuo file non viene modificato, così ogni pressione invia lo stesso pacchetto e il file resta
utilizzabile.

Ogni pacchetto riproduce, codice per codice, quello che invia un telecomando clone per quella famiglia di schede. Le
modalità 7–9 = clone DoorHan Smart, la modalità 10 = clone Phantom / Hiland. `X` = il contatore nel tuo file.

| Modalità | Per | Pacchetto | Tempo per pressione |
|---|---|---|---|
| 7 | le schede DoorHan più vecchie | 12 codici: `X / X+1`, quattro coppie che avanzano a passi di 15998 (tasto 0), poi `X-2 / X-1`; la prima e l'ultima coppia portano il tuo tasto | ~1.3 s |
| 8 | DHRE, la maggior parte delle schede più recenti, cloni per cancelli a battente | 12 codici: `X / X+1`, quattro coppie distanziate di `+0x3334`, poi ritorno al tuo contatore, dove cade `X+1` con il tuo tasto | ~1.3 s |
| 9 | schede per tapparelle CV01, altre schede vecchie | 3 codici con il tuo tasto: `X + 0x8000`, `X-1`, `X+1`, ciascuno inviato due volte | ~0.65 s |
| 10 | Phantom / Hiland | 2 codici con il tuo tasto: `0xFFFE`, `0xFFFF` assoluti, ciascuno inviato tre volte | ~0.4 s |

::: warning La modalità 7 è cambiata
La modalità 8 è esattamente ciò che faceva `CounterMode: 7` nelle versioni precedenti. Se hai un file con
`CounterMode: 7` che funzionava, cambialo in `CounterMode: 8`.
:::

Dettagli:

- Nei pacchetti lunghi (7 e 8) ogni codice viene inviato **una volta sola** (il clone originale invia ciascun codice
  due o tre volte): l'intero pacchetto viene costruito in memoria e triplicarlo richiederebbe 20 KB invece di 8 KB.
  Rinviare il pacchetto non è un sostituto: un ricevitore che si è già risincronizzato interpreta un secondo passaggio
  come una nuova sequenza e aziona di nuovo il cancello, mentre la ripetizione immediata di un singolo codice viene
  ignorata come duplicato.
- La modalità 10 ignora il contatore del tuo file. Senza sequenza, una sola pressione risincronizza un ricevitore che
  si trovi in uno qualsiasi dei 32768 valori sotto `0xFFFE` — dove si trova un ricevitore che è andato avanti rispetto
  al tuo telecomando. Se non funziona, invia ancora una volta.
- **Tenere premuto** Send ripete il pacchetto finché lo tieni premuto; un ricevitore che si è risincronizzato al primo
  passaggio lo interpreta come un'altra pressione. Premere di nuovo Send mentre un pacchetto è in corso lo **interrompe**.

### V2 Phoenix (Phox)

| Modalità | Contatore | Note |
|---|---|---|
| 0 | +moltiplicatore | predefinita |
| 1 | `0x0000 / 0x0001 / 0xFFFE / 0xFFFF` ("tipo ofex") | verificata funzionante |
| 2 | `0x0000 … 0x0004` | potrebbe funzionare |

## Esempio: KeeLoq DoorHan con +0x3333

```text
Filetype: Flipper SubGhz Key File
Version: 1
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Protocol: KeeLoq
Bit: 64
Key: DE AD BE EF CA FE BA BE
Manufacture: Doorhan
CounterMode: 2
```

## Risoluzione dei problemi e FAQ

- **Il file non funziona dopo aver aggiunto `CounterMode`** — controlla la sintassi `CounterMode: X` (spazio dopo i
  due punti) e che il numero sia valido per il protocollo.
- **Numero di modalità non valido?** Viene usata l'ultima modalità dell'elenco di quel protocollo.
- **Serve in ogni file?** No. Senza `CounterMode` si usa la modalità 0.
- **Può danneggiare il mio telecomando/ricevitore?** Può desincronizzare il tuo telecomando, a seconda del ricevitore.
  Non usarla se non puoi riaccoppiare l'originale.
- **Quale modalità dovrei usare?** Se non sei sicuro, nessuna. Preferisci un
  [nuovo telecomando](/it/subghz/add-manually).

## Pagine correlate

- [Signal Settings](/it/subghz/signal-settings) — impostare modalità, contatore e tasto sul Flipper
- [Codici rolling](/it/subghz/rolling-codes) · [KeeLoq](/it/subghz/keeloq)
- [Radio Settings: Counter Incr.](/it/subghz/settings) · [Formato dei file .sub](/it/subghz/file-format)
