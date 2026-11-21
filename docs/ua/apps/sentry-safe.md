---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Плагін **Sentry Safe** від [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) відкриває
електронні сейфи Sentry Safe і Master Lock **без PIN-коду**, використовуючи відому вразливість у підключенні їхньої
клавіатури. Вразливість і демонстрація описані в
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Використовуйте це лише на власному сейфі. Відкривати чужий сейф незаконно.
:::

::: tip Unleashed
Sentry Safe — це GPIO-плагін із [наборів застосунків](/ua/apps/catalog#base-and-extra-packs) спільноти, він не є
частиною самої прошивки.
:::

## Підключення

Flipper під’єднується до двох проводів сейфа (чорного й зеленого). У
[розборі вразливості](https://github.com/H4ckd4ddy/bypass-sentry-safe) показано, де до них дістатися.

| Пін GPIO на Flipper | Провід сейфа |
|---|---|
| 8 (GND) | чорний |
| 15 (C1) | зелений |

Номери пінів — це номери, нанесені на GPIO-гребінку Flipper, див. [Розпіновка GPIO](/ua/gpio/pinout).

## Використання

1. Відкрийте застосунок **Sentry Safe** через `Main Menu → Apps` (це GPIO-плагін, шукайте в папці GPIO).
2. Під’єднайте проводи так, як показано на екрані застосунку та в таблиці вище.
3. Натисніть <kbd>OK</kbd> (enter).
4. Відкрийте сейф.

## Усунення проблем

- Нічого не відбувається: перевірте, що GND справді йде до чорного проводу, а C1 (пін 15) — до зеленого, і що
  контакт надійний.

## Пов’язані сторінки

- [Розпіновка GPIO](/ua/gpio/pinout)
- [Застосунки у складі Unleashed](/ua/apps/catalog)
