---
title: Target hardware
order: 25
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HardwareTargets.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets]
sources: [unleashed-docs, unleashed-src]
---
# Target hardware

Il firmware è modulare: un'unica base di codice supporta diverse configurazioni hardware. Tutto ciò che varia tra le
schede — l'implementazione di `furi_hal`, il codice di inizializzazione della board, gli script del linker, le tabelle
dei simboli dell'SDK — è raccolto in una **definizione di target**.

Il repository Unleashed include due target in `targets/`:

| Cartella | Hardware |
|---|---|
| `targets/f7` | Flipper Zero — quello predefinito (`TARGET_HW = 7`) |
| `targets/f18` | "Not Flipper Zero" — una scheda senza i front-end radio; eredita da f7 |

Le intestazioni condivise si trovano in `targets/furi_hal_include`.

## Come è organizzato un target

Ogni target risiede in una propria sottocartella di `targets/`. Deve contenere `target.json` e può contenere qualunque
altro file a cui quella definizione fa riferimento. Per impostazione predefinita `fbt` compila **tutti i file
sorgente** della cartella del target, a meno che non siano esplicitamente esclusi. I target possono **ereditare** da
un altro target, per evitare di duplicare codice.

## Campi di `target.json`

| Campo | Tipo | Significato |
|---|---|---|
| `include_paths` | elenco di stringhe | Cartelle (relative al target) aggiunte al percorso di include globale C/C++ |
| `sdk_header_paths` | elenco di stringhe | Cartelle le cui intestazioni sono incluse nell'SDK |
| `startup_script` | nome di file | Script di avvio che esegue l'inizializzazione iniziale dell'hardware |
| `linker_script_flash` | nome di file | Script del linker per l'immagine principale del firmware |
| `linker_script_ram` | nome di file | Script del linker per la configurazione "updater" (eseguita dalla RAM) |
| `linker_script_app` | nome di file | Script del linker per i file `.fap` |
| `sdk_symbols` | nome di file | File `.csv` con la definizione corrente dell'SDK (API) per questo target |
| `linker_dependencies` | elenco | Librerie con cui collegare il firmware. Le librerie non elencate **non vengono compilate**. Più passaggi di link possono richiedere lo stesso nome due volte |
| `inherit` | stringa | Target da cui prendere la configurazione di base. I valori di tipo elenco vengono estesi, gli altri valori sovrascritti |
| `excluded_sources` | elenco | File della configurazione (o delle configurazioni) ereditata da **non** compilare |
| `excluded_headers` | elenco | Intestazioni della configurazione (o delle configurazioni) ereditata da **non** inserire nell'SDK |
| `excluded_modules` | elenco | Nomi di librerie (moduli) di `fbt` da escludere nella configurazione della build |

## Esempio: come f18 eredita da f7

`targets/f18/target.json` (abbreviato) mostra ereditarietà ed esclusioni nella pratica — prende tutto da f7 e
rimuove i driver Sub-GHz, NFC, RFID, iButton e infrarossi:

```json
{
    "inherit": "7",
    "include_paths": [
        "furi_hal"
    ],
    "sdk_symbols": "api_symbols.csv",
    "excluded_sources": [
        "furi_hal_infrared.c",
        "furi_hal_nfc.c",
        "furi_hal_rfid.c",
        "furi_hal_subghz.c"
    ],
    "excluded_modules": [
        "nfc",
        "lfrfid",
        "subghz",
        "ibutton",
        "infrared"
    ]
}
```

## App e hardware

Non tutte le app sono disponibili su ogni target.

- **App integrate:** scegli un insieme di app compatibile con l'opzione `FIRMWARE_APP_SET=...`
  (vedi [fbt → insiemi di app del firmware](/it/dev/fbt#firmware-app-sets)).
- **App esterne (FAP):** elenca i target compatibili nell'`application.fam` dell'app. Per esempio, per compilare
  un'app solo per f7, aggiungi:

```python
    targets=["f7"],
```

Non verrà compilata per gli altri target. Vedi [Manifest delle app](/it/dev/app-manifests).

## Compilare per un target specifico

Passa `TARGET_HW` (e facoltativamente `FIRMWARE_APP_SET`) a `fbt`. Per esempio, per compilare e flashare il firmware
per f18 via USB:

```sh
./fbt TARGET_HW=18 flash_usb_full
```

## Pagine correlate

- [Flipper Build Tool (fbt)](/it/dev/fbt)
- [Manifest delle app (.fam)](/it/dev/app-manifests)
- [API FuriHalBus](/it/dev/furi-hal-bus)
