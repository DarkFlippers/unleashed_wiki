---
title: Crédits et remerciements
order: 10
author: gromovyna
original: [https://t.me/gromovyna, https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13, https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05, https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15, https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Mifare-Classic-Magic-Tags-11-16, https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/how2flipper_rus, https://docs.flipper.net/zero, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://blog.li0ard.rest/wtfiskeeloq]
sources: [gromovyna, how2flipper, flipper-docs, unleashed-readme, unleashed-docs, unleashed-src, li0ard]
---
# Crédits et remerciements

Ce wiki est une compilation du travail d'autres personnes. Rien de tout cela n'existerait sans les développeurs de
firmware qui construisent Unleashed, sans les chercheurs qui font du reverse engineering sur les systèmes qui nous
entourent, et sans les auteurs qui prennent le temps de tout expliquer. Cette page remercie chacune des sources sur
lesquelles le wiki est construit. Chaque page porte son propre bloc de crédits renvoyant aux originaux exacts.

## @gromovyna

Un immense merci à **[@gromovyna](https://t.me/gromovyna)**. Ses articles constituent le corpus le plus précieux
derrière ce wiki : des analyses approfondies, pratiques et honnêtes de vraies recherches sur le contrôle d'accès —
Iron Logic, Vizit, Moskvyonok, les magic tags MIFARE Classic, les backdoors Nested et Fudan, les badges vierges
LF RFID et bien d'autres. Si ce wiki peut entrer dans une véritable profondeur pratique sur le NFC et les systèmes
d'accès, c'est parce qu'il a publié cette profondeur le premier.

Chacune des pages ci-dessous est construite à partir de l'un de ses articles. Lisez les originaux et abonnez-vous à
son canal.

| Article (original) | Page du wiki |
|---|---|
| [ZKTeco CMP200 — du Princeton sous emballage chinois](https://telegra.ph/ZKTeco-CMP200---Princeton-v-kitajskoj-obyortke-03-09) · [publication](https://t.me/gromovyna/28) | [ZKTeco CMP200](/fr/subghz/zkteco-cmp200) |
| [Guide des nouveaux backdoors Nested et Fudan pour le Flipper](https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13) · [publication](https://t.me/gromovyna/4) | [Backdoors Nested et Fudan](/fr/nfc/nested-fudan) |
| [MIFARE Classic Magic Tags](https://telegra.ph/Mifare-Classic-Magic-Tags-11-16) · [publication](https://t.me/gromovyna/6) | [Cartes magic](/fr/nfc/magic-cards) |
| [NFC Magic 2.0 — la magie désormais aussi pour l'Ultralight](https://telegra.ph/NFC-Magic-20---magiya-teper-i-dlya-Ultralight-06-25) · [publication](https://t.me/gromovyna/31) | [Application NFC Magic](/fr/nfc/nfc-magic) |
| [MFKey 4.1 — plus vite, plus haut, plus fort](https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03) · [publication](https://t.me/gromovyna/27) | [MFKey](/fr/nfc/mfkey) |
| [Casser rapidement les clés MIFARE Classic avec qUnleashed](https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18) · [publication](https://t.me/gromovyna/32) | [qUnleashed](/fr/nfc/qunleashed) |
| [Les lecteurs Iron Logic et quoi en faire](https://telegra.ph/Schityvateli-Iron-Logic-i-chto-s-nimi-delat-03-13) · [publication](https://t.me/gromovyna/15) | [Lecteurs Iron Logic](/fr/nfc/iron-logic) |
| [Attaque par enrôlement sur les codes dynamiques d'Iron Logic](https://telegra.ph/Enrollment-ataka-na-dinamiku-ot-Iron-Logic-06-05) · [publication](https://t.me/gromovyna/25) | [Enrôlement Iron Logic](/fr/nfc/iron-logic-enrollment) |
| [Les filtres des lecteurs Vizit contre les clones de badges Vizit RF 3.1](https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15) · [publication](https://t.me/gromovyna/23) | [Filtres Vizit](/fr/nfc/vizit-filters) |
| [Cartes, bracelets et porte-clés « Moskvyonok » et comment les aborder](https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16) · [publication](https://t.me/gromovyna/8) | [Moskvyonok](/fr/nfc/moskvyonok) |
| [Aperçu des fonctions LF (RFID) que j'ai préparées pour Unleashed](https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08) · [publication](https://t.me/gromovyna/29) | [Badges vierges T5577 et Hitag](/fr/rfid/t5577-hitag) |

## Flipper Devices

Merci à **[Flipper Devices](https://flipperzero.one)** d'avoir créé le Flipper Zero et de maintenir la documentation
officielle sur **[docs.flipper.net](https://docs.flipper.net/zero)**. Les caractéristiques matérielles, les notions de
fond et une grande partie du comportement du firmware d'origine décrits dans ce wiki proviennent de leur documentation
et de leur firmware open source. Ce wiki est un projet communautaire indépendant et n'est **pas affilié à Flipper
Devices**.

## L'équipe DarkFlippers / Unleashed

Le firmware Unleashed est développé et maintenu par **[@xMasterX](https://github.com/xMasterX)** et une petite équipe,
par pur enthousiasme, et il reste gratuit et open source. Merci à toutes les personnes de l'équipe et à l'ensemble des
contributeurs cités dans le
[ReadMe](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md) :

- **@xMasterX** — développeur principal et mainteneur
- **@mishamyte** — NFC, RFID, Sub-GHz, modération des discussions
- **@quen0n** — matériel, Sub-GHz, modération des discussions
- **@Drone1950** — reverse engineering, bot Telegram, modération des discussions
- **@HackcatDev** — support et modération des discussions
- **@Leptopt1los** — NFC, RFID, plugins, modération des discussions
- **@gid9798** — Sub-GHz, plugins et beaucoup d'autres choses
- **@assasinfil** — protocoles Sub-GHz, parseurs NFC, modération des discussions
- **@Svaarich** — design de l'interface et animations
- **@amec0e** — ressources infrarouge
- Et les contributeurs Sub-GHz : `@RocketGod-git, @zero-mega, @ashphx, @pkooiman, Vitaly, Carlos, @li0ard,
  @mishamyte, d82k, Steffen (bastelbudenbuben.de), @assasinfil, @gid9798`
- Les modérateurs de la communauté sur Telegram, Discord et Reddit, ainsi que toutes les personnes ayant un jour
  envoyé une pull request.

Merci également à l'**équipe du firmware officiel** — en particulier à son développeur Sub-GHz **Skorp** — pour le
travail sur les décodeurs et encodeurs sur lequel repose l'essentiel de la prise en charge des protocoles Sub-GHz.

## li0ard

Merci à **[li0ard](https://blog.li0ard.rest/wtfiskeeloq)** (membre de l'équipe de recherche de gromovyna) pour son
article de fond sur **KeeLoq**, dont s'inspirent les pages consacrées aux codes tournants Sub-GHz pour expliquer le
fonctionnement réel de l'algorithme et de ses clés constructeur.

## Autres sources

- **[@how2flipper_rus](https://t.me/how2flipper_rus)** — chaîne russophone consacrée au Flipper Zero, utilisée comme source sur plusieurs pages pratiques Sub-GHz.

## Et vous

Si ce wiki vous a été utile, le meilleur remerciement que vous puissiez adresser aux développeurs du firmware est de
le leur dire et, si vous le pouvez, de soutenir le projet via les liens de la page
[liens officiels](/fr/community/links). Voyez [Contribuer](/fr/community/contributing) si vous souhaitez améliorer le
wiki lui-même.
