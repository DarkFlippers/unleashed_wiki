---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (автор @xMasterX) работает с записанным сигналом **клавиатуры Security+ 2.0** — 86-битным пакетом беспроводных кодовых панелей Chamberlain / LiftMaster. PIN-код клавиатуры лежит внутри этого пакета. PIN можно задать вручную или перебрать `0000`–`9999`: приложение отправляет каждый вариант и записывает найденный PIN обратно в файл.

::: tip Unleashed
Security+ 2.0 Keypad (86 бит, 315 / 390 / 868 МГц) декодируется приложением Sub-GHz в Unleashed, а это встроенное системное приложение редактирует его PIN. Обычные 62-битные пульты Security+ 2.0 — не пакеты клавиатуры, они отклоняются.
:::

::: warning
Только для своих гаражных ворот и своей клавиатуры.
:::

## Подготовка

1. Запишите свою клавиатуру через `Sub-GHz → Read` на её частоте (см. [Read](/ru/subghz/read)) и сохраните. В файле должно быть `Security+ 2.0` и `Bit: 86`.
2. Файл лежит в `/ext/subghz/`.

## Работа с приложением

1. Откройте `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Выберите `Open .sub file` и файл клавиатуры. После загрузки в статусе частота и `ready` (например, `315MHz  ready`). Если в файле уже есть `Pin`, он будет показан.
3. На экране четыре цифры PIN, активная — в рамке:
   - <kbd>←</kbd> / <kbd>→</kbd> — переход между цифрами
   - <kbd>↑</kbd> / <kbd>↓</kbd> — изменить PIN
   - <kbd>OK</kbd> (`Send`) — отправить текущий PIN (`Sending 1234...` → `Sent 1234`)
   - удержание <kbd>OK</kbd> — **перебор**: отправка всех PIN начиная с текущего, полоска `N of 9999`. Короткое <kbd>OK</kbd> или <kbd>←</kbd> (Back) останавливает на `Stopped at NNNN`
   - удержание <kbd>←</kbd> — **сохранить** текущий PIN в файл (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — назад в меню

Подсказка на экране: `hold OK sweep   < save`.

Сохранение обновляет открытый файл: записываются поля `Pin`, `Key` и `Secplus_packet_1`. После этого файл можно отправлять обычным образом из `Sub-GHz → Saved`.

## Сообщения

| Сообщение | Значение |
|---|---|
| `Not Security+ 2.0: …` | в файле другой протокол |
| `Not an 86-bit keypad` | пульт Security+ 2.0, а не пакет клавиатуры |
| `Missing packet 1` / `No Key value` | неполная запись — считайте клавиатуру заново |
| `Unsupported preset …` / `Bad custom preset` | пресет файла не поддерживается |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | передача на этой частоте запрещена (см. [Частоты](/ru/subghz/frequencies)) |
| `TX failed` | радио не смогло передать |

## Проблемы и решения

- **Перебор идёт долго** — каждый PIN — отдельная передача с паузой, полный перебор занимает много времени. Начинайте с вероятного значения и останавливайте, как только ворота среагировали.
- **Ворота сработали, но PIN проскочил** — перебор останавливается на показанном числе; вернитесь <kbd>↓</kbd>, отправляйте по одному через <kbd>OK</kbd>, затем удержите <kbd>←</kbd> для сохранения.
- **Файл отклонён** — записывайте именно клавиатуру, а не брелок.

## Связанные страницы

- [Read](/ru/subghz/read) · [Поддерживаемые системы](/ru/subghz/supported-systems)
- [Динамические коды](/ru/subghz/rolling-codes)
