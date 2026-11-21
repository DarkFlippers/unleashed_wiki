---
title: Formato dei file IR
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Formato dei file infrarossi (`.ir`)

Tutti i dati IR sul Flipper sono memorizzati in testo semplice nel Flipper Format (righe `key: value`).
L'estensione è sempre `.ir`. Esistono tre varianti che differiscono solo nell'intestazione `Filetype` e nell'uso che
se ne fa.

| Filetype | Usato per | Posizione |
|---|---|---|
| `IR signals file` | I tuoi telecomandi (appresi, salvati da un telecomando universale, scaricati dall'app) | `/ext/infrared/` |
| `IR library file` | Librerie dei telecomandi universali | `/ext/infrared/assets/` |
| file di test (`.irtest`) | Unit test dei decoder/encoder | solo nel repository del firmware |

## File di telecomando

### Esempio

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

Il file contiene un numero qualsiasi di pulsanti. Ogni pulsante inizia con `name:`; una riga di commento `#` tra i
pulsanti serve solo alla leggibilità.

### Campi

| Campo | Usato in | Tipo | Descrizione |
|---|---|---|---|
| `name` | entrambi | stringa | Nome del pulsante. Solo ASCII stampabile. L'interfaccia del Flipper limita i nomi a 23 caratteri. |
| `type` | entrambi | stringa | `parsed` oppure `raw`. |
| `protocol` | parsed | stringa | Nome del protocollo, esattamente come nell'[elenco dei protocolli](/it/infrared/protocols) (lo stampa anche il comando CLI `ir`). |
| `address` | parsed | hex | Indirizzo, sempre **4 byte**, byte meno significativo per primo: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Comando, sempre **4 byte**, byte meno significativo per primo. |
| `frequency` | raw | uint32 | Frequenza della portante in Hz, di solito `38000`. Intervallo valido 10000-1000000. |
| `duty_cycle` | raw | float | Duty cycle della portante, di solito `0.33`. Deve essere > 0 e ≤ 1. |
| `data` | raw | elenco di uint32 | Temporizzazioni in microsecondi tra i cambi di livello (mark, space, mark, …), separate da spazi. **Max. 1024** valori. |

### Valori validi di `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` è un'aggiunta di Unleashed. `Pioneer` esiste nel firmware anche se il documento ufficiale sul formato non lo
elenca ancora.
:::

### Modificare a mano

- Mantieni le due righe di intestazione (`Filetype`, `Version`) in cima.
- Ogni pulsante ha bisogno di `name` e `type`, poi di `protocol`/`address`/`command` oppure di
  `frequency`/`duty_cycle`/`data`.
- Per unire due telecomandi, copia i blocchi dei pulsanti di un file alla fine dell'altro.
- I byte di indirizzo/comando devono restare lunghi 4 byte anche se il protocollo usa meno bit; i byte non usati sono
  `00`.
- Se il Flipper dice *"Failed to load …"*, uno dei campi è malformato (per esempio una riga RAW `data` con più di
  1024 valori oppure una frequenza fuori intervallo).

## File di libreria {#library-files}

I file di libreria usano esattamente la stessa struttura; cambia solo l'intestazione:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Il telecomando universale cerca i segnali **per nome**, quindi i nomi devono corrispondere esattamente ai pulsanti
della libreria (vedi la tabella in
[Contribuire con le acquisizioni](/it/infrared/captures#button-names-per-library)). I nuovi modelli vengono aggiunti
alla fine, preceduti da un commento `# Model: …`.

Un file di libreria non può essere aperto tramite `Saved Remotes`: l'app riporta *"Library file … can't be opened as a
remote"*.

## File di test (`.irtest`)

Usati solo dagli unit test del firmware (`applications/debug/unit_tests/resources/unit_tests/infrared` nel
repository). Assomigliano ai file di telecomando, con in più un tipo `parsed_array` per intere sequenze di messaggi
decodificati:

| Campo | Usato in | Tipo | Descrizione |
|---|---|---|---|
| `name` | entrambi | stringa | Nome del segnale, vedi la convenzione di denominazione sotto. |
| `type` | entrambi | stringa | `parsed_array` oppure `raw`. |
| `count` | parsed_array | uint32 | Numero di messaggi nell'array, almeno 1. |
| `protocol`, `address`, `command` | parsed_array | | Come sopra, uno per messaggio. |
| `repeat` | parsed_array | bool | Se il messaggio è una ripetizione (pulsante tenuto premuto). |
| `frequency`, `duty_cycle`, `data` | raw | | Come sopra. |

I nomi seguono lo schema `<name><test_number>`: `decoder_input1` (ingresso raw per il decoder, nonché uscita attesa
dell'encoder), `decoder_expected1` (uscita attesa del decoder, nonché ingresso dell'encoder),
`encoder_decoder_input1` (array parsed che deve sopravvivere a un ciclo codifica → decodifica). Ogni protocollo deve
avere un file di test di questo tipo.

## Pagine correlate

- [Protocolli](/it/infrared/protocols)
- [Contribuire con le acquisizioni](/it/infrared/captures)
- [Apprendere e inviare segnali](/it/infrared/read)
