---
title: Формат tar + heatshrink
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Формат tar-архива со сжатием Heatshrink

Флиппер умеет читать архивы `.tar`, сжатые библиотекой [Heatshrink](https://github.com/atomicobject/heatshrink).
Это уменьшает пакеты обновлений и ускоряет OTA-обновление — ресурсы для SD-карты в каждом пакете обновления
(`resources.ths`) хранятся именно в этом формате.

Сам Heatshrink не определяет контейнер для хранения параметров сжатия, поэтому Флиппер добавляет небольшой
заголовок.

## Структура файла

| Смещение | Размер | Поле | Значение |
|--:|--:|---|---|
| 0 | 4 байта | Magic | `0x48 0x53 0x44 0x53` — ASCII `HSDS` («HeatShrink DataStream») |
| 4 | 1 байт | Версия | `0x01` |
| 5 | 1 байт | Размер окна | Логарифм по основанию 2 размера скользящего окна; то же, что `-w` в CLI Heatshrink |
| 6 | 1 байт | Размер lookahead | Логарифм по основанию 2 размера буфера lookahead; то же, что `-l` в CLI Heatshrink |
| 7 | … | Данные | Поток, сжатый Heatshrink |

Общий размер заголовка — **7 байт**. Внутри сжатого потока — обычный несжатый tar-архив (USTAR).

## Как его создают инструменты прошивки

По `scripts/flipper/assets/tarball.py` и `heatshrink_stream.py`:

- расширение: `.ths` («.Tar.HeatShrink»);
- параметры по умолчанию: окно `13`, lookahead `6`;
- заголовок упаковывается как `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (magic — 32-битное число в
  little-endian, что на диске даёт байты `48 53 44 53`);
- tar в формате USTAR, uid/gid `0`, mtime `0`, имя пользователя/группы `furippa`, служебные файлы macOS
  отфильтровываются.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Использование на устройстве

Tar-библиотека прошивки открывает архивы `.ths` в режиме *heatshrink* только для чтения; режим выбирается
автоматически по расширению файла. Поэтому [CLI](/ru/dev/cli#storage) распаковывает их напрямую:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Связанные страницы

- [OTA-обновления](/ru/dev/ota)
- [Командная строка (CLI)](/ru/dev/cli)
