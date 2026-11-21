---
title: Фаззер iButton
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Фаззер iButton

**Фаззер** по очереди эмулирует серию ID ключей, чтобы посмотреть, как реагирует считыватель — например, проверить,
принимает ли ваш домофон ID по умолчанию или некорректные ID.

::: tip Unleashed
В ReadMe Unleashed указаны **LFRFID and iButton Fuzzer plugins**. Фаззер — внешнее приложение, его нет в дереве
исходников прошивки: готовые паки приложений добавляются в релизные сборки, а **extra apps pack**, публикуемый с каждым
релизом, содержит все известные рабочие приложения. Меню зависят от версии приложения, поэтому здесь не описываются.
:::

## Что ставит прошивка: примеры списков UID

Прошивка кладёт примеры списков ID в **`/ext/ibtnfuzzer/`**:

| Файл | Протокол | Длина ID (hex-символов) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 байт) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 байта) |
| `example_uids_metakom.txt` | Metakom | 8 (4 байта) |

Формат — по одному hex-ID в строке, `#` для комментариев, **пустая строка в конце**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Чтобы сделать свой список, скопируйте пример и замените ID; длина должна соответствовать протоколу.

Словари от сообщества, на которые ссылается FAQ Unleashed:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Используйте фаззер только на своих считывателях или с разрешения владельца.
:::

## Связанные страницы

- [Протоколы](/ru/ibutton/protocols) · [Эмуляция ключей](/ru/ibutton/read) · [RFID-фаззер](/ru/rfid/fuzzer)
