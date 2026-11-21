---
title: RFID 125 kHz
author: gromovyna
original: [https://docs.flipper.net/zero/rfid, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08]
sources: [unleashed-src, flipper-docs, unleashed-readme, gromovyna]
---
# RFID 125 kHz

Le RFID basse fréquence (LF) est la technologie « proximité » utilisée par les badges et porte-clés d’accès bon marché,
les clés d’interphone, certains systèmes de parking et de salles de sport, ainsi que les puces d’identification
animale. Ces tags se contentent en général de diffuser un ID fixe, sans aucune cryptographie, ce qui les rend faciles à
lire, à émuler et à cloner.

Le Flipper Zero possède une antenne 125 kHz à l’arrière (sur l’antenne bi-bande, à côté de la bobine NFC 13,56 MHz),
pilotée par le MCU STM32WB55. Avec elle, le Flipper peut **lire**, **enregistrer**, **émuler** et **écrire** des tags LF.

::: tip Unleashed
L’application 125 kHz RFID vient du firmware officiel. En plus, la version Unleashed offre :
- un menu **Settings → Write Chips** : outre le T5577, elle sait écrire les **EM4305** et les clones Hitag Micro
  (**8265**, **8210**, **H5.5**), ainsi qu’une cible **8268** (Hitag S) à activer soi-même. L’écran d’écriture indique
  quelle puce est tentée et laquelle a accepté l’écriture ;
- **Write and set password** pour les supports T5577 vierges ;
- des formats supplémentaires dans **Add Manually** (saisie du facility code / numéro de carte au lieu de
  l’hexadécimal, HID H10304/H10302/S10401/H10306/Corp1000-35, Casi-Rusco), un affichage DEZ 8 / DEZ 10 pour l’EM4100 ;
- une troisième passe de lecture à **134,2 kHz** pour les puces animales, et un mode dédié
  **Read FDX-B (Animals)** ;
- l’application **T5577** intégrée (lecture/édition/restauration des blocs, test, effacement, suppression et
  interception des mots de passe).
:::

## Menu principal

`Main Menu → 125 kHz RFID` ouvre un menu contenant les entrées suivantes (libellés exacts du firmware) :

![Le menu 125 kHz RFID avec Read, Saved, Add Manually et Extra Actions](/screens/lfrfid/menu.png)

| Élément | Rôle | Page |
|---|---|---|
| **Read** | Détection automatique et lecture d’un tag (cycle ASK → PSK → 134 kHz) | [Lecture des tags](/fr/rfid/read) |
| **Saved** | Parcourir `/ext/lfrfid/` — émuler, écrire, modifier, renommer, supprimer les clés enregistrées | [Lecture des tags](/fr/rfid/read), [Écriture](/fr/rfid/write) |
| **Add Manually** | Créer une clé à partir de son protocole et de son ID | [Ajout manuel](/fr/rfid/add-manually) |
| **Extra Actions** | Lire avec une modulation fixe (ASK, PSK, FDX-B) ; lecture/émulation RAW en mode Debug | [Lecture des tags](/fr/rfid/read), [RAW](/fr/rfid/raw) |
| **Settings** | **Write Chips** — les types de supports vierges qu’une écriture peut viser | [Écriture](/fr/rfid/write) |

## Pages de cette section

- [Lecture des tags](/fr/rfid/read) — lire, enregistrer et émuler des tags LF ; lecture avec une modulation fixe.
- [Écriture sur supports vierges](/fr/rfid/write) — quels supports fonctionnent (T5577, EM4305, Hitag Micro, 8268),
  réglage Write Chips, écriture avec mot de passe, messages d’erreur.
- [Ajout manuel](/fr/rfid/add-manually) — tous les protocoles d’Add Manually et les formats de saisie FC/ID.
- [Protocoles pris en charge](/fr/rfid/protocols) — tableau complet : modulation, taille des données, champs décodés,
  prise en charge de l’écriture.
- [Puces d’identification animale](/fr/rfid/animal-microchips) — puces FDX-B / FDX-A pour animaux.
- [T5577 et Hitag Micro (par @gromovyna)](/fr/rfid/t5577-hitag) — l’histoire des H5.5 / 8265 / 8210, l’ergonomie de
  l’écriture, l’effacement du T5577.
- [Application T5577](/fr/rfid/t5577-app) — lecture, édition, restauration, test, effacement bloc par bloc,
  suppression et interception du mot de passe.
- [Enregistrement RAW](/fr/rfid/raw) — enregistrer le signal ASK/PSK brut pour la recherche sur les protocoles.
- [Fuzzer](/fr/rfid/fuzzer) — ce que le firmware fournit pour l’application de fuzzing RFID.
- [Formats de fichiers](/fr/rfid/file-format) — les fichiers `.rfid`, `.t5577` et `.raw`.

## Où sont stockés les fichiers

| Chemin | Contenu |
|---|---|
| `/ext/lfrfid/*.rfid` | Clés enregistrées |
| `/ext/lfrfid/*.t5577` | Dumps de blocs T5577 (ouverts par l’application T5577) |
| `/ext/lfrfid/*.ask.raw`, `*.ask134.raw`, `*.psk.raw` | Enregistrements RAW |
| `/ext/lfrfid/.lfrfid.settings` | Réglage Write Chips |
| `/ext/lfrfid/assets/t5577_dict.lfrfid` | Dictionnaire de mots de passe T5577 (écrasé à chaque mise à jour) |
| `/ext/lfrfid/assets/t5577_dict_user.lfrfid` | Vos propres mots de passe T5577 |
| `/ext/lfrfid/assets/iso3166.lfrfid` | Noms de pays pour les puces FDX-B |

::: warning
Ne clonez et n’émulez que les tags qui vous appartiennent ou que vous êtes autorisé à tester.
:::
