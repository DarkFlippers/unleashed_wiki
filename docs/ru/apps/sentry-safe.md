---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Плагин **Sentry Safe** от [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) открывает
электронные сейфы Sentry Safe и Master Lock **без PIN-кода**, используя известную уязвимость в подключении их
клавиатуры. Уязвимость и демонстрация описаны в
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Используйте только на своём сейфе. Вскрытие чужого сейфа незаконно.
:::

::: tip Unleashed
Sentry Safe — GPIO-плагин из комьюнити [паков приложений](/ru/apps/catalog), в саму прошивку он не входит.
:::

## Подключение

Флиппер подключается к двум проводам сейфа (чёрному и зелёному). Где до них добраться, показано в
[описании уязвимости](https://github.com/H4ckd4ddy/bypass-sentry-safe).

| Пин GPIO Флиппера | Провод сейфа |
|---|---|
| 8 (GND) | чёрный |
| 15 (C1) | зелёный |

Номера пинов — те, что напечатаны на GPIO-разъёме Флиппера, см. [Распиновка GPIO](/ru/gpio/pinout).

## Использование

1. Откройте приложение **Sentry Safe** из `Main Menu → Apps` (это GPIO-плагин, ищите в папке GPIO).
2. Подключите провода, как показано на экране приложения и в таблице выше.
3. Нажмите <kbd>OK</kbd> (ввод).
4. Откройте сейф.

## Решение проблем

- Ничего не происходит: проверьте, что GND действительно идёт на чёрный провод, а C1 (пин 15) — на зелёный, и что
  контакт надёжный.

## Связанные страницы

- [Распиновка GPIO](/ru/gpio/pinout)
- [Приложения в составе Unleashed](/ru/apps/catalog)
