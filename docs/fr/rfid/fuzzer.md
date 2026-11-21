---
title: Fuzzer RFID
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer RFID

Un **fuzzer** émule une longue série d’ID les uns après les autres pour tester la réaction d’un lecteur — par exemple
pour savoir s’il accepte un ID par défaut, s’il plante sur des données malformées, ou pour délimiter la plage de cartes
valides de votre propre système.

::: tip Unleashed
Le ReadMe d’Unleashed mentionne les **plugins LFRFID et iButton Fuzzer** parmi ses fonctions NFC/RFID/iButton. Le fuzzer
est une application externe, qui ne fait pas partie des sources du firmware : des packs d’applications précompilées sont
ajoutés aux builds de release, et le **pack d’applications extra** publié avec chaque release contient toutes les
applications connues comme fonctionnelles. Ses menus dépendent de la version de l’application : ils ne sont donc pas
décrits ici.
:::

## Ce que fournit le firmware : exemples de listes d’UID

Le firmware installe des exemples de listes d’ID pour le fuzzer dans **`/ext/rfidfuzzer/`** :

| Fichier | Protocole | Longueur de l’ID (caractères hex) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 octets) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 octets) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 octets) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 octets) |

Format — un ID hexadécimal par ligne, `#` pour les commentaires, et une **ligne vide à la fin** du fichier :

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Créez votre propre liste en copiant l’un des exemples et en remplaçant les ID ; la longueur de l’ID doit correspondre à
la taille de clé du protocole (voir [protocoles](/fr/rfid/protocols), colonne *Octets*).

La FAQ d’Unleashed renvoie vers des dictionnaires prêts à l’emploi partagés par la communauté :
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) et
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
N’utilisez le fuzzer que sur des lecteurs qui vous appartiennent ou que vous êtes autorisé à tester.
:::

## Voir aussi

- [Protocoles](/fr/rfid/protocols) · [Lecture](/fr/rfid/read) · [Fuzzer iButton](/fr/ibutton/fuzzer)
