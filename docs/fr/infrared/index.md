---
title: Infrarouge
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Infrarouge

Le Flipper Zero embarque un module infrarouge (IR). Il peut **apprendre** les boutons de presque n'importe quelle
télécommande IR, les **enregistrer** sous forme de télécommande virtuelle sur la carte microSD, les **réémettre**, et
servir de **télécommande universelle** en parcourant une bibliothèque de codes connus pour les téléviseurs, les
systèmes audio, les projecteurs, les rubans LED, les ventilateurs et les climatiseurs.

![L'infrarouge sur le Flipper Zero](/img/remote/133011d2bd3dc44c.png)

## Matériel

- Une fenêtre en plastique transparent à l'IR sur la tranche supérieure du Flipper.
- **Trois LED IR** pour l'émission.
- Un **récepteur IR** qui démodule la porteuse (il est optimisé pour la porteuse courante de 38 kHz).
  L'apprentissage passe toujours par ce récepteur intégré.
- En option, un **émetteur IR externe** sur la broche GPIO 2 (A7) pour une portée accrue, voir
  [Modules IR externes](/fr/infrared/external-ir).

## Le menu Infrared

Ouvrez `Main Menu → Infrared`. Les entrées du menu sont reprises telles quelles du firmware :

![Le menu Infrared avec Universal Remotes, Learn New Remote, Saved Remotes et GPIO Settings](/screens/infrared/menu.png)

| Entrée | Rôle |
|---|---|
| **Universal Remotes** | Envoie toute une bibliothèque de codes pour un même bouton (Power, Vol+…) jusqu'à ce que votre appareil réagisse. Voir [Télécommandes universelles](/fr/infrared/universal-remotes). |
| **Learn New Remote** | Capture les boutons d'une télécommande physique et les enregistre comme nouvelle télécommande. Voir [Apprendre et envoyer des signaux](/fr/infrared/read). |
| **Saved Remotes** | Ouvre le navigateur de fichiers sur `/ext/infrared/` pour envoyer, modifier, renommer ou supprimer vos télécommandes. |
| **GPIO Settings** | Choisit l'émetteur (intégré, broche 2 (A7) ou détection automatique) et le 5 V sur le GPIO. Voir [Modules IR externes](/fr/infrared/external-ir). |
| **Learn New Remote RAW** | Uniquement avec `Settings → System → Debug` sur `ON`. Comme Learn, mais le décodeur est désactivé : chaque signal est enregistré en RAW. |
| **Debug RX** | Uniquement avec le mode Debug activé. Un « INFRARED monitor » en direct de ce que reçoit le récepteur. |

::: tip Unleashed
L'application Infrared, ses décodeurs de protocoles et le mécanisme des télécommandes universelles viennent du
firmware officiel. Unleashed ajoute :
- le protocole IR **RCA** (voir [Protocoles](/fr/infrared/protocols)) ;
- des bibliothèques de télécommandes universelles supplémentaires (**LEDs**, **Fans**) et des bibliothèques bien
  plus volumineuses et régulièrement revérifiées pour les téléviseurs, l'audio, les projecteurs et les
  climatiseurs, maintenues par l'équipe Unleashed (ressources IR par @amec0e). La bibliothèque TV est recompilée
  afin que **tous** ses boutons fonctionnent ;
- la prise en charge des modules IR externes avec détection automatique (reprise du firmware officiel).
:::

## Où se trouvent les fichiers

| Chemin | Contenu |
|---|---|
| `/ext/infrared/*.ir` | Vos télécommandes enregistrées (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Bibliothèques de télécommandes universelles : `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Elles sont installées et mises à jour avec le firmware. |
| `/ext/infrared/.infrared.settings` | Réglages GPIO (broche de sortie, 5 V). |

Le format des fichiers `.ir` est décrit sur [Format des fichiers IR](/fr/infrared/file-format).

## Ligne de commande

La commande `ir` est disponible dans la [CLI](/fr/dev/cli) (par exemple via qFlipper ou un terminal série) :

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Pages de cette section

| Page | Ce que vous y apprenez |
|---|---|
| [Apprendre et envoyer des signaux](/fr/infrared/read) | Apprendre une télécommande, l'enregistrer, envoyer des boutons, modifier / déplacer / renommer / supprimer des boutons |
| [Télécommandes universelles](/fr/infrared/universal-remotes) | Toutes les catégories de télécommandes universelles, les boutons, les commandes, l'enregistrement d'un code qui marche |
| [Télécommandes dans l'application mobile](/fr/infrared/mobile) | La Remotes Library de l'application Flipper Mobile |
| [Contribuer ses captures](/fr/infrared/captures) | Comment enregistrer des signaux propres pour les bibliothèques universelles |
| [Modules IR externes](/fr/infrared/external-ir) | Sortie GPIO, détection automatique, alimentation 5 V |
| [Protocoles](/fr/infrared/protocols) | Tous les protocoles connus du décodeur, y compris RCA |
| [Format des fichiers IR](/fr/infrared/file-format) | Les formats de fichiers `.ir` de télécommande, de bibliothèque et de test |
