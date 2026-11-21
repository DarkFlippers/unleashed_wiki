---
title: Sub-GHz
sources: [unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz]
---
# Sub-GHz

Le Flipper Zero embarque un émetteur-récepteur **CC1101** et une antenne pour les bandes inférieures à 1 GHz. Il
permet de lire, enregistrer et rejouer les signaux des télécommandes de garage et de portail, des barrières, des
volets roulants, des sonnettes, des capteurs sans fil et d'autres appareils fonctionnant dans les plages
**300–348 MHz, 387–464 MHz et 779–928 MHz**. La plupart des télécommandes que vous rencontrerez utilisent
**315 MHz**, **433.92 MHz** ou **868.35 MHz**.

L'application se trouve dans `Main Menu → Sub-GHz`. Son menu principal dans Unleashed :

![Menu principal Sub-GHz : Read, Read RAW, Saved, Add Manually](/screens/subghz/menu.png)

| Entrée de menu | Rôle | Page |
|---|---|---|
| `Read` | Décoder les télécommandes des protocoles connus, les enregistrer et les envoyer | [Read](/fr/subghz/read) |
| `Read RAW` | Enregistrer le signal brut de n'importe quelle télécommande et le rejouer | [Read RAW](/fr/subghz/read-raw) |
| `Saved` | Fichiers `.sub` enregistrés : Emulate, Rename, Delete, et Signal Settings quand Debug est activé | [Read](/fr/subghz/read) |
| `Add Manually` | Créer une télécommande toute neuve avec un numéro de série aléatoire | [Add Manually](/fr/subghz/add-manually) |
| `Add Manually [Advanced]` | Idem, mais vous saisissez vous-même le numéro de série / le bouton / le compteur / le seed | [Add Manually](/fr/subghz/add-manually) |
| `Frequency Analyzer` | Déterminer sur quelle fréquence une télécommande émet | [Frequency Analyzer](/fr/subghz/frequency-analyzer) |
| `Radio Settings` | Module interne / externe, puissance d'émission, noms de fichiers, pas du compteur | [Réglages](/fr/subghz/settings) |

::: tip Unleashed
L'application Sub-GHz, sa bibliothèque de protocoles et le Frequency Analyzer viennent du firmware officiel.
Unleashed supprime les restrictions régionales d'émission, ajoute des fréquences supplémentaires et d'autres
protocoles, permet d'enregistrer et d'envoyer beaucoup de protocoles à code tournant,
crée de nouvelles télécommandes à code tournant que vous pouvez enregistrer dans votre récepteur (`Add Manually`),
utilise les touches fléchées comme boutons de télécommande supplémentaires, prend en charge un module CC1101 externe
et livre des applications Sub-GHz supplémentaires (Remote Analyzer, Seed Capturer, Nice O-Code, Security+ PIN,
Sub-GHz RAW Edit, Sub-GHz Remote).
:::

::: warning Attention
N'utilisez ces fonctions qu'avec votre propre matériel ou pour des recherches licites.
:::

## Pour commencer

1. Trouvez la fréquence de votre télécommande — [Frequency Analyzer](/fr/subghz/frequency-analyzer).
2. Essayez de la décoder — [Read](/fr/subghz/read). Si elle se décode et que le protocole est **fixe**,
   enregistrez-la et c'est terminé.
3. S'il s'agit d'une télécommande à **code tournant**, ne la clonez pas : lisez
   [Codes tournants](/fr/subghz/rolling-codes) et créez une nouvelle télécommande avec
   [Add Manually](/fr/subghz/add-manually) + [Programmer une nouvelle télécommande](/fr/subghz/remote-prog).
4. Si rien ne se décode, enregistrez-la avec [Read RAW](/fr/subghz/read-raw).

## Toutes les pages

**Les bases**
- [Fréquences](/fr/subghz/frequencies) — bandes, listes par défaut, verrous régionaux et plage étendue
- [Frequency Analyzer](/fr/subghz/frequency-analyzer) — trouver la fréquence d'une télécommande
- [Read](/fr/subghz/read) — décoder, enregistrer et envoyer des signaux
- [Read RAW](/fr/subghz/read-raw) — enregistrer des signaux bruts

**Codes tournants et nouvelles télécommandes**
- [Add Manually](/fr/subghz/add-manually) — tous les protocoles du menu
- [Codes tournants](/fr/subghz/rolling-codes) — conflits de compteur, boutons personnalisés
- [KeeLoq](/fr/subghz/keeloq) — fonctionnement de KeeLoq, clés constructeur et seeds
- [Programmer une nouvelle télécommande](/fr/subghz/remote-prog) — pas à pas pour chaque système
- [Modes de compteur](/fr/subghz/counter-mode) — le `CounterMode` expérimental pour les clones
- [Signal Settings](/fr/subghz/signal-settings) — mode de compteur, compteur et bouton d'un signal enregistré
- [Systèmes pris en charge](/fr/subghz/supported-systems) — table complète des protocoles

**Configuration et matériel**
- [Réglages](/fr/subghz/settings) — Radio Settings, config de Read, fréquences utilisateur
- [Format de fichier](/fr/subghz/file-format) — `.sub`, presets, fichiers de réglages utilisateur
- [CC1101 externe](/fr/subghz/external-cc1101) — modules externes et amplificateurs

**Applications**
- [Sub-GHz Remote](/fr/subghz/remote) — jusqu'à 5 signaux sur la croix directionnelle
- [Sub-GHz Bruteforce](/fr/subghz/bruteforce) — force brute sur les codes fixes
- [Remote Analyzer](/fr/subghz/remote-analyzer) — décoder une télécommande, protocoles supplémentaires
- [Nice O-Code](/fr/subghz/nice-o-code) — retrouver le code installateur
- [Security+ PIN](/fr/subghz/secplus-pin) — le code PIN du clavier Security+ 2.0
- [Seed Capturer](/fr/subghz/seed-capturer) — collecter des sauts pour retrouver un seed
- [Sub-GHz RAW Edit](/fr/subghz/raw-editor) — rogner, fusionner et décoder des fichiers RAW

**Notes de terrain**
- [ZKTeco CMP200](/fr/subghz/zkteco-cmp200) — une télécommande Princeton déguisée

## Où les fichiers sont stockés

| Chemin | Contenu |
|---|---|
| `/ext/subghz/` | Signaux enregistrés (`.sub`), enregistrements RAW |
| `/ext/subghz/assets/setting_user` | Vos propres fréquences, liste de hopping, presets personnalisés |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Vos propres clés constructeur KeeLoq |
| `/ext/subghz/assets/dangerous_settings` | Interrupteur de la plage de fréquences étendue |
| `/ext/subghz_remote/` | Fichiers de carte de l'application Sub-GHz Remote |
| `/ext/apps_data/subghz_seed_captures/` | Captures de Seed Capturer |
