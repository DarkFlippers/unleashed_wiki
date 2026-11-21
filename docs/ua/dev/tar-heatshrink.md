---
title: Формат tar + heatshrink
order: 115
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/TarHeatshrinkFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/tarball.py, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/scripts/flipper/assets/heatshrink_stream.py]
sources: [unleashed-docs, unleashed-src]
---
# Формат tar зі стисканням Heatshrink

Flipper уміє читати архіви `.tar`, стиснуті бібліотекою [Heatshrink](https://github.com/atomicobject/heatshrink).
Завдяки цьому пакети оновлення менші, а OTA-оновлення швидші — ресурси для картки microSD у кожному пакеті
оновлення (`resources.ths`) використовують саме цей формат.

Сам Heatshrink не визначає контейнера для своїх параметрів стискання, тому Flipper додає невеликий заголовок.

## Структура файлу

| Зсув | Розмір | Поле | Значення |
|--:|--:|---|---|
| 0 | 4 байти | Magic | `0x48 0x53 0x44 0x53` — ASCII `HSDS` («HeatShrink DataStream») |
| 4 | 1 байт | Версія | `0x01` |
| 5 | 1 байт | Розмір вікна | Логарифм за основою 2 від розміру рухомого вікна; те саме, що `-w` у CLI Heatshrink |
| 6 | 1 байт | Розмір lookahead | Логарифм за основою 2 від розміру буфера попереднього перегляду; те саме, що `-l` у CLI Heatshrink |
| 7 | … | Дані | Потік, стиснутий Heatshrink |

Загалом заголовок займає **7 байтів**. Усередині стиснутого потоку лежить звичайний нестиснутий tar-архів (USTAR).

## Як його створюють інструменти прошивки

За файлами `scripts/flipper/assets/tarball.py` і `heatshrink_stream.py`:

- розширення: `.ths` («.Tar.HeatShrink»);
- типові параметри: вікно `13`, lookahead `6`;
- заголовок пакується як `struct.pack("<IBBB", 0x53445348, 1, window, lookahead)` (magic — 32-бітне ціле в
  порядку little-endian, що на диску дає байти `48 53 44 53`);
- tar має формат USTAR, uid/gid `0`, mtime `0`, ім’я користувача та групи `furippa`, а сміттєві файли macOS
  відфільтровані.

```python
def compress_tree_tarball(
    src_dir, output_name, filter=tar_sanitizer_filter, hs_window=13, hs_lookahead=6
):
```

## Використання на пристрої

Бібліотека tar у прошивці відкриває архіви `.ths` у режимі *heatshrink* лише для читання, вибираючи цей режим
автоматично за розширенням файлу. Тому [CLI](/ua/dev/cli#storage) може розпаковувати їх напряму:

```
storage extract /ext/my_resources.ths /ext/target_dir
```

## Пов’язані сторінки

- [OTA-оновлення](/ua/dev/ota)
- [Командний рядок](/ua/dev/cli)
