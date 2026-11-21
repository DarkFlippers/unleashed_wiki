---
title: Sentry Safe
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SentrySafe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# Sentry Safe

Le plugin **Sentry Safe** de [H4ckd4ddy](https://github.com/H4ckd4ddy/flipperzero-sentry-safe-plugin) ouvre les
coffres-forts électroniques Sentry Safe et Master Lock **sans le code PIN**, en exploitant une vulnérabilité connue
dans la liaison de leur clavier. La vulnérabilité et une démonstration sont décrites dans
[bypass-sentry-safe](https://github.com/H4ckd4ddy/bypass-sentry-safe).

::: warning
À n'utiliser que sur un coffre-fort qui vous appartient. Ouvrir le coffre-fort d'autrui est illégal.
:::

::: tip Unleashed
Sentry Safe est un plugin GPIO issu des [packs d'applications](/fr/apps/catalog#base-and-extra-packs) communautaires ;
il ne fait pas partie du firmware lui-même.
:::

## Câblage

Le Flipper se connecte à deux fils du coffre-fort (noir et vert). La
[description de la vulnérabilité](https://github.com/H4ckd4ddy/bypass-sentry-safe) montre où les atteindre.

| Broche GPIO du Flipper | Fil du coffre-fort |
|---|---|
| 8 (GND) | noir |
| 15 (C1) | vert |

Les numéros de broches sont ceux imprimés sur le connecteur GPIO du Flipper, voir
[Brochage GPIO](/fr/gpio/pinout).

## Utilisation

1. Ouvrez l'application **Sentry Safe** depuis `Main Menu → Apps` (c'est un plugin GPIO, cherchez dans le dossier
   GPIO).
2. Branchez les fils comme indiqué à l'écran de l'application et dans le tableau ci-dessus.
3. Appuyez sur <kbd>OK</kbd> (entrée).
4. Ouvrez le coffre-fort.

## Dépannage

- Rien ne se passe : vérifiez que GND va bien au fil noir et que C1 (broche 15) va bien au fil vert, et que le contact
  est franc.

## Pages liées

- [Brochage GPIO](/fr/gpio/pinout)
- [Applications fournies avec Unleashed](/fr/apps/catalog)
