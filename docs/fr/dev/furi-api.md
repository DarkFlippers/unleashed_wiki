---
title: API Furi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_furi_api.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FuriCheck.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi]
sources: [unleashed-docs, unleashed-src]
---
# API Furi

Pour utiliser le matériel du Flipper — écran, haut-parleur, radio, USB, NFC — votre application dialogue avec
**Furi**, l'ensemble de bibliothèques situé entre le matériel brut et le code applicatif. Cette page présente
l'architecture matérielle et logicielle, et explique les contrôles effectués par Furi à l'exécution.

## Matériel

Le cœur du Flipper Zero est un microcontrôleur (MCU) **STM32WB55** : deux cœurs, de la RAM, de la flash et des
dizaines de blocs périphériques (timers, RTC, BLE, GPIO, …). Leur fonctionnement est décrit dans le Reference Manual
du MCU. Autour du MCU se trouvent plusieurs puces externes (CC1101, ST25R3916, contrôleur d'écran, etc.) avec leurs
propres fiches techniques.

![Structure matérielle du Flipper Zero](/img/dev/flipper_zero_hardware.png)

Légende des couleurs :

- **Violet** — blocs internes au MCU
- **Bleu** — puces externes au MCU
- **Orange** — autres composants périphériques ne nécessitant pas d'interaction complexe

Comme le firmware est open source, vous *pouvez* accéder directement au matériel et écrire vos propres pilotes bas
niveau — mais en général, ce n'est pas nécessaire.

## Logiciel : Furi

**Furi** (**F**lipper **U**niversal **R**egistry **I**mplementation) est la couche d'abstraction incluse dans le
firmware. Elle offre une API simple pour le matériel et pour les tâches système courantes : threads, mémoire
dynamique, contrôle d'accès aux ressources (records), timers, files de messages, journalisation, etc.

Avec Furi, vous n'avez pas à lire des centaines de pages de fiches techniques ni à écrire des pilotes : apprendre
l'API Furi suffit. Cela évite aussi que chaque développeur réimplémente les mêmes choses.

![Structure matérielle + logicielle du Flipper Zero](/img/dev/flipper_zero_architecture.png)

Furi occupe toute la largeur du schéma : elle sépare le code de niveau applicatif (services et applications) du
matériel qui se trouve en dessous.

Furi est composée de deux parties :

| Partie | Emplacement | Contenu |
|---|---|---|
| Furi Core | `furi/` | Primitives du système : threads, mutex, files de messages, records, timers, boucle d'événements, journalisation, contrôles |
| Furi HAL | `targets/` (par ex. `targets/f7/furi_hal/`) | Abstraction matérielle : GPIO, SPI, I2C, USB, Sub-GHz, NFC, RFID, alimentation, … — voir [FuriHalBus](/fr/dev/furi-hal-bus) |

Code source :

- Furi Core : [unleashed-firmware/furi](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/furi)
  (officiel : [flipperzero-firmware/furi](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/furi))
- Furi HAL : [unleashed-firmware/targets](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets)
  (officiel : [flipperzero-firmware/targets](https://github.com/flipperdevices/flipperzero-firmware/tree/dev/targets))

## Trouver des exemples

Toutes les applications Flipper utilisent Furi : il existe donc des exemples pour n'importe quel bloc matériel.

- les applications d'exemple dans [`applications/examples/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples)
  (`example_event_loop`, `example_adc`, `example_ble_beacon`, …) ;
- les applications intégrées dans `applications/main/` et les applications Unleashed supplémentaires dans
  `applications/system/` ;
- les applications communautaires du [catalogue d'applications](https://lab.flipper.net/apps) — le lien vers les
  sources se trouve en bas de la page de chaque application. Choisissez des applications dont les fonctionnalités sont
  proches de ce que vous voulez construire.

Toutes les fonctions, structures et en-têtes de Furi sont listés dans la [référence API Doxygen officielle](https://developer.flipper.net/flipperzero/doxygen/) — allez-y quand ce wiki ne couvre pas l'appel qu'il vous faut.

## Contrôles à l'exécution et plantages volontaires

La meilleure façon de protéger l'intégrité du système est de traiter moins de cas impossibles et de **planter le plus
tôt possible** lorsque quelque chose ne va pas. Le fichier `check.h` de Furi Core fournit les outils pour cela.

Terminologie :

- **Crash** — journaliser l'événement, enregistrer les informations de plantage dans le RTC, redémarrer.
- **Halt** — journaliser l'événement, bloquer le système.

Remarques :

- Les builds debug et release ne se comportent pas de la même façon : un **build debug ne réinitialise jamais** le
  système, afin de préserver l'état pour le débogueur.
- Avec un débogueur connecté, l'exécution s'arrête automatiquement avant le redémarrage.
- Toutes ces fonctions acceptent un `MESSAGE_CSTR` facultatif. Il peut être en RAM ou en flash, mais **seuls les
  messages stockés en flash** sont affichés après le redémarrage (utilisez donc des littéraux de chaîne).
- `MESSAGE_CSTR` peut valoir `NULL`, mais les macros gèrent déjà le cas sans message — il suffit de l'omettre.

| Macro | Comportement | Quand l'utiliser |
|---|---|---|
| `furi_assert(CONDITION)` / `furi_assert(CONDITION, MESSAGE_CSTR)` | Plante si `CONDITION` est fausse — **uniquement dans les builds de développement** | Contrôles de phase de développement dans les applications et services |
| `furi_check(CONDITION)` / `furi_check(CONDITION, MESSAGE_CSTR)` | Plante **toujours** si `CONDITION` est fausse | Conditions qui doivent être vraies dans tous les builds |
| `furi_crash()` / `furi_crash(MESSAGE_CSTR)` | Plante inconditionnellement | Une condition anormale a été détectée |
| `furi_halt()` / `furi_halt(MESSAGE_CSTR)` | Bloque le système | Utilisé en interne, par exemple pour s'arrêter quand l'extinction est impossible |

::: warning Pièges de furi_assert
- Les builds release (`DEBUG=0`) ne contiennent jamais les contrôles `furi_assert`.
- Les bibliothèques n'en contiennent jamais par défaut ; compilez avec `LIB_DEBUG=1` si vous en avez besoin.
- Ne placez pas d'appels de fonction (effets de bord) dans la `CONDITION` — l'expression entière peut être éliminée à
  la compilation.
:::

Exemple :

```c
#include <furi.h>

void my_set_level(uint8_t level) {
    furi_check(level <= 100, "Level out of range");
    // ...
}
```

## Pages liées

- [Interface graphique dans les applications](/fr/dev/gui)
- [API FuriHalBus](/fr/dev/furi-hal-bus)
- [Déboguer les applications](/fr/dev/debugging) — comprend les signaux de débogage du HAL Furi
