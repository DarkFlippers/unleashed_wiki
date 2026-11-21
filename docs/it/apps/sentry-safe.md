---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Il plugin **Sentry Safe** di [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) apre le
casseforti elettroniche Sentry Safe e Master Lock **senza il codice PIN**, sfruttando una vulnerabilità nota nel
collegamento della loro tastiera. La vulnerabilità e una dimostrazione sono descritte in
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
Usalo solo su una cassaforte di tua proprietà. Aprire la cassaforte di qualcun altro è illegale.
:::

::: tip Unleashed
Sentry Safe è un plugin GPIO dei [pacchetti di app](/it/apps/catalog#base-and-extra-packs) della comunità, non fa
parte del firmware stesso.
:::

## Collegamenti

Il Flipper si collega a due fili della cassaforte (nero e verde). L'
[analisi della vulnerabilità](https://github.com/H4ckd4ddy/bypass-sentry-safe) mostra dove raggiungerli.

| Pin GPIO del Flipper | Filo della cassaforte |
|---|---|
| 8 (GND) | nero |
| 15 (C1) | verde |

I numeri dei pin sono quelli stampati sul connettore GPIO del Flipper, vedi [Pinout GPIO](/it/gpio/pinout).

## Utilizzo

1. Apri l'app **Sentry Safe** da `Main Menu → Apps` (è un plugin GPIO, cercala nella cartella GPIO).
2. Collega i fili come indicato nella schermata dell'app e nella tabella sopra.
3. Premi <kbd>OK</kbd> (enter).
4. Apri la cassaforte.

## Risoluzione dei problemi

- Non accade nulla: verifica che GND vada davvero al filo nero e C1 (pin 15) al filo verde, e che il contatto sia
  solido.

## Pagine correlate

- [Pinout GPIO](/it/gpio/pinout)
- [App incluse in Unleashed](/it/apps/catalog)
