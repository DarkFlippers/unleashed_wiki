---
title: Heatshrink-Tarball-Format
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Mit Heatshrink komprimiertes Tarball-Format

Der Flipper kann `.tar`-Archive lesen, die mit der Bibliothek
[Heatshrink](https://github.com/atomicobject/heatshrink) komprimiert wurden. Das macht Update-Pakete kleiner und
OTA-Updates schneller — die SD-Karten-Ressourcen in jedem Update-Paket (`resources.ths`) verwenden dieses Format.

Heatshrink selbst definiert keinen Container für seine Kompressionsparameter, deshalb ergänzt der Flipper einen
kleinen Header.

## Dateiaufbau

| Offset | Größe | Feld | Wert |
|--:|--:|---|---|
| 0 | 4 Bytes | Magic | `0x48 0x53 0x44 0x53` — ASCII `HSDS` ("HeatShrink DataStream") |
| 4 | 1 Byte | Version | `0x01` |
| 5 | 1 Byte | Window size | Logarithmus zur Basis 2 der Größe des Sliding Window; entspricht `-w` in der Heatshrink-CLI |
| 6 | 1 Byte | Lookahead size | Logarithmus zur Basis 2 der Größe des Lookahead-Puffers; entspricht `-l` in der Heatshrink-CLI |
| 7 | … | Daten | Mit Heatshrink komprimierter Datenstrom |

Der Header ist insgesamt **7 Bytes** groß. Im komprimierten Datenstrom steckt ein gewöhnliches, unkomprimiertes
Tar-Archiv (USTAR).

## Wie die Firmware-Werkzeuge es erzeugen

Aus `scripts/flipper/assets/tarball.py` und `heatshrink_stream.py`:

- Endung: `.ths` (".Tar.HeatShrink");
- Standardparameter: Window `13`, Lookahead `6`;
- der Header wird als `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` gepackt (das Magic ist eine
  32-Bit-Little-Endian-Ganzzahl, was auf der Platte die Bytes `48 53 44 53` ergibt);
- das Tar ist USTAR, mit uid/gid `0`, mtime `0`, Benutzer-/Gruppenname `furippa`, und macOS-Müll-Dateien werden
  herausgefiltert.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Verwendung auf dem Gerät

Die Tar-Bibliothek der Firmware öffnet `.ths`-Archive in einem schreibgeschützten *heatshrink*-Modus, der anhand der
Dateiendung automatisch gewählt wird. Die [CLI](/de/dev/cli#storage) kann sie daher direkt entpacken:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Verwandte Seiten

- [OTA-Updates](/de/dev/ota)
- [Kommandozeile](/de/dev/cli)
