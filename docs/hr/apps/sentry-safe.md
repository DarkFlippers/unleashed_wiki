---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Dodatak **Sentry Safe** autora [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) otvara elektroničke sefove Sentry Safe i Master Lock **bez PIN koda**, koristeći poznatu ranjivost u vezi njihove tipkovnice. Ranjivost i demonstracija opisani su u repozitoriju [bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Koristite ga isključivo na sefu u vlastitom vlasništvu. Otvaranje tuđeg sefa je protuzakonito.
:::

::: tip Unleashed
Sentry Safe je GPIO dodatak iz [paketa aplikacija](/hr/apps/catalog#base-and-extra-packs) zajednice te nije dio samog firmvera.
:::

## Ožičenje

Flipper se povezuje na dvije žice sefa (crnu i zelenu). Gdje im pristupiti prikazano je u [opisu ranjivosti](https://github.com/H4ckd4ddy/bypass-sentry-safe).

| GPIO pin na Flipperu | Žica sefa |
|---|---|
| 8 (GND) | crna |
| 15 (C1) | zelena |

Brojevi pinova odgovaraju brojevima otisnutima na GPIO priključku Flippera, pogledajte [Raspored GPIO pinova](/hr/gpio/pinout).

## Korištenje

1. Otvorite aplikaciju **Sentry Safe** putem `Main Menu → Apps` (radi se o GPIO dodatku, potražite ga u mapi GPIO).
2. Povežite žice kako je prikazano na zaslonu aplikacije i u gornjoj tablici.
3. Pritisnite <kbd>OK</kbd> (potvrda).
4. Otvorite sef.

## Rješavanje problema

- Ništa se ne događa: provjerite je li GND doista spojen na crnu žicu, a C1 (pin 15) na zelenu žicu te je li kontakt stabilan.

## Povezane stranice

- [Raspored GPIO pinova](/hr/gpio/pinout)
- [Aplikacije koje dolaze uz Unleashed](/hr/apps/catalog)
