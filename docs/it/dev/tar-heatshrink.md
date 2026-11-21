---
title: Formato tarball heatshrink
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Formato dei tarball compressi con heatshrink

Il Flipper è in grado di leggere archivi `.tar` compressi con la libreria
[Heatshrink](https://github.com/atomicobject/heatshrink). Questo riduce le dimensioni dei pacchetti di aggiornamento e
rende più rapidi gli aggiornamenti OTA — le risorse per la scheda SD presenti in ogni pacchetto di aggiornamento
(`resources.ths`) usano questo formato.

Heatshrink in sé non definisce un contenitore per i propri parametri di compressione, quindi il Flipper aggiunge una
piccola intestazione.

## Struttura del file

| Offset | Dimensione | Campo | Valore |
|--:|--:|---|---|
| 0 | 4 byte | Magic | `0x48 0x53 0x44 0x53` — in ASCII `HSDS` ("HeatShrink DataStream") |
| 4 | 1 byte | Version | `0x01` |
| 5 | 1 byte | Window size | Logaritmo in base 2 della dimensione della finestra scorrevole; equivalente a `-w` nella CLI di Heatshrink |
| 6 | 1 byte | Lookahead size | Logaritmo in base 2 della dimensione del buffer di lookahead; equivalente a `-l` nella CLI di Heatshrink |
| 7 | … | Data | Flusso compresso con Heatshrink |

L'intestazione è in totale di **7 byte**. All'interno del flusso compresso c'è un normale archivio tar non compresso
(USTAR).

## Come lo creano gli strumenti del firmware

Da `scripts/flipper/assets/tarball.py` e `heatshrink_stream.py`:

- estensione: `.ths` (".Tar.HeatShrink");
- parametri predefiniti: window `13`, lookahead `6`;
- l'intestazione viene impacchettata come `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (il magic è un
  intero a 32 bit little-endian, che su disco produce i byte `48 53 44 53`);
- il tar è in formato USTAR, con uid/gid `0`, mtime `0`, nome utente/gruppo `furippa`, e i file di servizio di macOS
  vengono filtrati.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Usarlo sul dispositivo

La libreria tar del firmware apre gli archivi `.ths` in una modalità *heatshrink* di sola lettura, scelta
automaticamente in base all'estensione del file. Quindi la [CLI](/it/dev/cli#storage) può estrarli direttamente:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Pagine correlate

- [Aggiornamenti OTA](/it/dev/ota)
- [Interfaccia a riga di comando](/it/dev/cli)
