---
title: Format tar arhive komprimirane Heatshrinkom
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Format tar arhive komprimirane Heatshrinkom

Flipper može čitati `.tar` arhive komprimirane bibliotekom [Heatshrink](https://github.com/atomicobject/heatshrink).
Time paketi za ažuriranje postaju manji, a OTA ažuriranja brža — resursi za microSD karticu u svakom paketu za ažuriranje
(`resources.ths`) koriste taj format.

Sam Heatshrink ne definira spremnik za svoje parametre kompresije, pa Flipper dodaje malo zaglavlje.

## Raspored datoteke

| Pomak | Veličina | Polje | Vrijednost |
|--:|--:|---|---|
| 0 | 4 bajta | Magic | `0x48 0x53 0x44 0x53` — ASCII `HSDS` ("HeatShrink DataStream") |
| 4 | 1 bajt | Inačica | `0x01` |
| 5 | 1 bajt | Veličina prozora | Logaritam po bazi 2 veličine kliznog prozora; isto kao `-w` u alatu Heatshrink CLI |
| 6 | 1 bajt | Veličina pregleda unaprijed | Logaritam po bazi 2 veličine međuspremnika pregleda unaprijed (lookahead); isto kao `-l` u alatu Heatshrink CLI |
| 7 | … | Podaci | Tok komprimiran Heatshrinkom |

Zaglavlje ima ukupno **7 bajtova**. Unutar komprimiranog toka nalazi se obična nekomprimirana (USTAR) tar arhiva.

## Kako ga alati firmvera stvaraju

Iz datoteka `scripts/flipper/assets/tarball.py` i `heatshrink_stream.py`:

- nastavak: `.ths` (".Tar.HeatShrink");
- zadani parametri: prozor `13`, lookahead `6`;
- zaglavlje je pakirano kao `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (magic je little-endian
  32-bitni cijeli broj, što na disku daje bajtove `48 53 44 53`);
- tar je USTAR, s uid/gid `0`, mtime `0`, imenom korisnika/grupe `furippa` i filtriranim suvišnim macOS datotekama.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Korištenje na uređaju

Tar biblioteka u firmveru otvara `.ths` arhive u načinu *heatshrink* samo za čitanje, koji se automatski bira prema nastavku
datoteke. Stoga ih [CLI](/hr/dev/cli#storage) može izravno raspakirati:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Povezane stranice

- [OTA ažuriranja](/hr/dev/ota)
- [Sučelje naredbenog retka (CLI)](/hr/dev/cli)
