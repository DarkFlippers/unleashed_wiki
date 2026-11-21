---
title: Protocoles
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Protocoles IR pris en charge

La bibliothèque infrarouge (`lib/infrared/encoder_decoder/`) contient un décodeur et un encodeur pour chacun des
protocoles ci-dessous. Un signal qui correspond à l'un d'eux est enregistré en `type: parsed` (protocole + adresse +
commande) ; tout le reste est enregistré en `type: raw` et rejoué sous forme de timings. La liste et les valeurs de
cette page sont tirées des sources du firmware.

::: tip Unleashed
**RCA** est un ajout d'Unleashed. Les autres protocoles sont communs avec le firmware officiel.
:::

## Table des protocoles

| Protocole (valeur de `protocol:`) | Famille | Bits d'adresse | Bits de commande | Porteuse |
|---|---|---|---|---|
| `NEC` | NEC | 8 | 8 | 38 kHz |
| `NECext` | NEC (étendu, sans octets inversés) | 16 | 16 | 38 kHz |
| `NEC42` | NEC 42 bits | 13 | 8 | 38 kHz |
| `NEC42ext` | NEC 42 bits étendu | 26 | 16 | 38 kHz |
| `Samsung32` | Samsung | 8 | 8 | 38 kHz |
| `RC5` | Philips RC5 | 5 | 6 | 36 kHz |
| `RC5X` | Philips RC5 étendu | 5 | 7 | 36 kHz |
| `RC6` | Philips RC6 | 8 | 8 | 36 kHz |
| `SIRC` | Sony SIRC 12 bits | 5 | 7 | 40 kHz |
| `SIRC15` | Sony SIRC 15 bits | 8 | 7 | 40 kHz |
| `SIRC20` | Sony SIRC 20 bits | 13 | 7 | 40 kHz |
| `Kaseikyo` | Kaseikyo (Panasonic, Denon…) | 26 | 10 | 38 kHz |
| `RCA` | RCA | 4 | 8 | 38 kHz |
| `Pioneer` | Pioneer | 8 | 8 | 40 kHz |

Le rapport cyclique de tous les encodeurs intégrés est de 33 %. Les mêmes noms sont acceptés par la commande CLI
`ir tx` (par exemple `ir tx NEC 0x04 0x08`) et sont ceux que `protocol:` doit contenir dans un fichier `.ir`.

::: info Pioneer
Le protocole `Pioneer` est implémenté dans le firmware (et utilisé dans les bibliothèques Audio et TV) même si la
liste du document officiel *InfraredFileFormats* ne le mentionne pas encore.
:::

## Référence des timings

Timings d'impulsion et de silence des principaux protocoles, tels que définis dans les encodeurs (µs). La tolérance
de décodage est de ±200 µs sur le préambule et de ±120 µs sur les bits.

| Protocole | Préambule marque / silence | Bit 1 marque / silence | Bit 0 marque / silence |
|---|---|---|---|
| NEC (toutes variantes) | 9000 / 4500 | 560 / 1690 | 560 / 560 |
| Samsung32 | 4500 / 4500 | 550 / 1650 | 550 / 550 |
| RCA | 4000 / 4000 | 500 / 2000 | 500 / 1000 |
| Pioneer | 8500 / 4225 | 500 / 1500 | 500 / 500 |
| SIRC | 2400 / 600 | 1200 / 600 | 600 / 600 |
| Kaseikyo | 3456 / 1728 (8 / 4 unités de 432) | 432 / 1296 | 432 / 432 |
| RC5 / RC5X | aucun (Manchester) | demi-bit de 888 µs | |
| RC6 | 2666 / 889 | demi-bit de 444 µs (Manchester) | |

## Ce que ces chiffres changent pour vous

- **Apprentissage :** le récepteur intégré est optimisé pour 38 kHz, mais les décodeurs des protocoles à 36 kHz
  (RC5, RC6) et 40 kHz (Sony SIRC, Pioneer) sont bien présents : ces télécommandes sont donc elles aussi apprises
  sous forme de signaux parsed.
- **Enregistrement :** un signal parsed est minuscule et robuste. Si un signal décodé ne fonctionne pas sur votre
  appareil, apprenez-le en RAW (mode debug `Learn New Remote RAW`, voir
  [Apprentissage](/fr/infrared/read#debug-mode-extras)).
- **Les télécommandes inconnues** (la plupart des télécommandes de climatiseur : 181 des 182 signaux de `ac.ir` sont
  en RAW) ne sont pas analysées du tout et sont toujours stockées en RAW. Les signaux RAW peuvent contenir jusqu'à
  1024 timings ; les captures RAW apprises sont normalement stockées avec `frequency: 38000` et
  `duty_cycle: 0.330000`.

## Voir aussi

- [Format des fichiers IR](/fr/infrared/file-format)
- [Apprendre et envoyer des signaux](/fr/infrared/read)
- [Télécommandes universelles](/fr/infrared/universal-remotes)
