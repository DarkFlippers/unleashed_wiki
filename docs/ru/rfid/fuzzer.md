---
title: RFID-фаззер
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# RFID-фаззер

**Фаззер** по очереди эмулирует длинную серию ID, чтобы посмотреть, как реагирует считыватель: принимает ли он ID по
умолчанию, ломается ли на некорректных данных — или чтобы проверить диапазон допустимых карт в своей системе.

::: tip Unleashed
В ReadMe Unleashed среди функций NFC/RFID/iButton указаны **LFRFID and iButton Fuzzer plugins**. Фаззер — внешнее
приложение, его нет в дереве исходников прошивки: готовые паки приложений добавляются в релизные сборки, а **extra
apps pack**, который публикуется с каждым релизом, содержит все известные рабочие приложения. Меню зависят от версии
приложения, поэтому здесь не описываются.
:::

## Что ставит прошивка: примеры списков UID

Прошивка кладёт примеры списков ID для фаззера в **`/ext/rfidfuzzer/`**:

| Файл | Протокол | Длина ID (hex-символов) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 байт) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 байта) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 байт) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 байта) |

Формат — по одному hex-ID в строке, `#` для комментариев и **пустая строка в конце** файла:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Свой список проще сделать, скопировав пример и заменив ID; длина ID должна соответствовать размеру ключа протокола (см.
[протоколы](/ru/rfid/protocols), столбец *Байт*).

В FAQ Unleashed есть ссылки на готовые словари от сообщества:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) и
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Используйте фаззер только на своих считывателях или с разрешения владельца.
:::

## Связанные страницы

- [Протоколы](/ru/rfid/protocols) · [Чтение](/ru/rfid/read) · [Фаззер iButton](/ru/ibutton/fuzzer)
