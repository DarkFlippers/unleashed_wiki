---
title: Heatshrink tarball format
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Heatshrink-compressed tarball format

The Flipper can read `.tar` archives compressed with the [Heatshrink](https://github.com/atomicobject/heatshrink)
library. This makes update packages smaller and OTA updates faster — the SD card resources in every update package
(`resources.ths`) use this format.

Heatshrink itself doesn't define a container for its compression parameters, so the Flipper adds a small header.

## File layout

| Offset | Size | Field | Value |
|--:|--:|---|---|
| 0 | 4 bytes | Magic | `0x48 0x53 0x44 0x53` — ASCII `HSDS` ("HeatShrink DataStream") |
| 4 | 1 byte | Version | `0x01` |
| 5 | 1 byte | Window size | Base-2 log of the sliding window size; same as `-w` in the Heatshrink CLI |
| 6 | 1 byte | Lookahead size | Base-2 log of the lookahead buffer size; same as `-l` in the Heatshrink CLI |
| 7 | … | Data | Heatshrink-compressed stream |

The header is **7 bytes** in total. Inside the compressed stream is a regular uncompressed (USTAR) tar archive.

## How the firmware tools create it

From `scripts/flipper/assets/tarball.py` and `heatshrink_stream.py`:

- extension: `.ths` (".Tar.HeatShrink");
- default parameters: window `13`, lookahead `6`;
- the header is packed as `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (the magic is a little-endian
  32-bit integer, which gives the bytes `48 53 44 53` on disk);
- the tar is USTAR, with uid/gid `0`, mtime `0`, user/group name `furippa`, and macOS junk files filtered out.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Using it on the device

The firmware's tar library opens `.ths` archives in a read-only *heatshrink* mode, chosen automatically from the file
extension. So the [CLI](/dev/cli#storage) can unpack them directly:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Related pages

- [OTA updates](/dev/ota)
- [Command-line interface](/dev/cli)
