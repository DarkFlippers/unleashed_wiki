---
title: Fuzzer iButton
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# Fuzzer iButton

Un **fuzzer** émule une série d’ID de clés les uns après les autres pour observer la réaction d’un lecteur — par
exemple pour vérifier si votre propre interphone accepte des ID par défaut ou malformés.

::: tip Unleashed
Le ReadMe d’Unleashed mentionne les **plugins LFRFID et iButton Fuzzer**. Le fuzzer est une application externe, qui ne
fait pas partie des sources du firmware : des packs d’applications précompilées sont ajoutés aux builds de release, et
le **pack d’applications extra** publié avec chaque release contient toutes les applications connues comme
fonctionnelles. Ses menus dépendent de la version de l’application : ils ne sont donc pas décrits ici.
:::

## Ce que fournit le firmware : exemples de listes d’UID

Le firmware installe des exemples de listes d’ID dans **`/ext/ibtnfuzzer/`** :

| Fichier | Protocole | Longueur de l’ID (caractères hex) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 octets) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 octets) |
| `example_uids_metakom.txt` | Metakom | 8 (4 octets) |

Format — un ID hexadécimal par ligne, `#` pour les commentaires, et surtout une **ligne vide à la fin** :

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Pour créer votre propre liste, copiez un exemple et remplacez les ID ; leur longueur doit correspondre au protocole.

Dictionnaires communautaires référencés depuis la FAQ d’Unleashed :
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
N’utilisez le fuzzer que sur des lecteurs qui vous appartiennent ou que vous êtes autorisé à tester.
:::

## Voir aussi

- [Protocoles](/fr/ibutton/protocols) · [Émuler des clés](/fr/ibutton/read) · [Fuzzer RFID](/fr/rfid/fuzzer)
