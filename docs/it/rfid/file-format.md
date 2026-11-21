---
title: Formati dei file
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# Formati dei file RFID 125 kHz

In `/ext/lfrfid/` risiedono tre tipi di file:

| Estensione | Cosa descrive | Creato da |
|---|---|---|
| `.rfid` | Una **tessera**: protocollo + ID | Read → Save, Add Manually |
| `.t5577` | Un **chip**: tutti i blocchi di un T5577 | [App T5577](/it/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | Una registrazione del segnale grezzo | [RAW](/it/rfid/raw) |

## `.rfid` — chiave LF RFID

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

Il file memorizza una chiave del tipo indicato da `Key type`.

| Campo | Descrizione |
|---|---|
| `Key type` | Nome del protocollo, esattamente come nella [tabella dei protocolli](/it/rfid/protocols) |
| `Data` | Dati della chiave in esadecimale; la lunghezza è fissa per ciascun protocollo |

Valori di `Key type` validi in questo firmware: `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Cronologia delle versioni: 1 — versione iniziale. I file legacy con `Key type: I40134` (3 byte) vengono convertiti in
`Indala26` al caricamento.

::: tip
Puoi creare una chiave da computer: scrivi le quattro righe mostrate sopra con il `Key type` corretto e il numero
giusto di byte in `Data`, copia il file in `/ext/lfrfid/` e comparirà in **Saved**.
:::

## `.t5577` — dump di un T5577

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

Un file `.t5577` descrive il **silicio**, un file `.rfid` descrive la **tessera**. Un T5577 configurato come EM4100 si
può salvare in entrambi i modi, e i due formati non sono interscambiabili: il `.t5577` comprende la configurazione che
decide come il chip comunica e la password che lo protegge.

| Campo | Descrizione |
|---|---|
| `Page 0 blocks read` | Blocchi della pagina 0 i cui valori provengono dal chip, separati da spazi |
| `Page 0 Block 0..7` | Contenuto dei blocchi, 4 byte esadecimali, MSB per primo. Blocco 0 = configurazione, blocco 7 = archivio della password |
| `Page 1 blocks read` | Blocchi della pagina 1 effettivamente letti |
| `Page 1 Block 0..3` | Il blocco 0 ripete la configurazione; da 1 a 3 contengono i dati di tracciabilità di fabbrica |
| `Password` | Facoltativo. Una password **di cui si sa che funziona** sul chip |

Regole fondamentali:

- **Ogni blocco ha una chiave**, letto o no. Solo i blocchi elencati in `blocks read` sono contenuto reale; il resto è
  riempimento e non va mai scritto su un tag. Un file che non elenca alcun blocco viene rifiutato.
- Un chip protetto rifiuta la lettura del blocco 0 necessaria al rilevamento, quindi senza la password non si ottiene
  alcun dump (nemmeno parziale). Un dump parziale significa che il tag è uscito dal campo.
- `Password` e `Page 0 Block 7` sono due informazioni distinte e possono non coincidere: il blocco 7 è ciò che il
  blocco conteneva al momento della lettura (normale area di memoria se non è attiva alcuna password), mentre
  `Password` è una credenziale che ha funzionato. Cancellare una password azzera solo il bit nel blocco 0, quindi il
  blocco 7 conserva il valore precedente.
- La riga di commento che decodifica il blocco 0 è destinata solo alla lettura umana.

### Ordine di ripristino

Quando si riscrive un dump sul tag (app T5577 → **Write to Tag**), l'ordine corrisponde a quello di Proxmark3:

1. Pagina 0, blocchi da 1 a 7. Dal blocco 7 in poi le scritture devono usare la password ormai memorizzata nel
   blocco 7.
2. Pagina 1, blocchi da 1 a 3 (il blocco 0 della pagina 1 non viene mai scritto). I chip autentici rifiutano di
   modificare i blocchi 1 e 2 — risultato riportato come *unchanged*, non come errore.
3. Pagina 0, blocco 0 **per ultimo** — modifica il modo in cui il chip comunica.
4. Vengono scritti solo i blocchi elencati in `blocks read`.
5. Un blocco 0 pari a zero non viene **mai** scritto: un chip che lo contiene non risponde più in alcun modo e non si
   può tornare indietro.

I frame di scrittura non ricevono risposta, quindi il successo si conosce solo rileggendo i blocchi.

## `.raw` — registrazioni RAW

File binari scritti dalla lettura RAW. Iniziano con un'intestazione:

| Campo | Tipo | Valore |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | frequenza della portante, Hz (125000 o 134200) |
| duty_cycle | float | duty cycle della portante |
| max_buffer_size | uint32 | buffer più grande presente nel file |

seguita dai buffer, ciascuno preceduto dalla propria dimensione, che contengono coppie *(impulso, durata)* codificate
come varint. Per decodificarli usa `rfid raw_analyze <filename>` nella CLI.

## Pagine correlate

- [Protocolli](/it/rfid/protocols) · [App T5577](/it/rfid/t5577-app) · [RAW](/it/rfid/raw)
