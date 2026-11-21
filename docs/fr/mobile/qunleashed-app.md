---
title: Application compagnon qUnleashed
order: 30
original: [https://github.com/DarkFlippers/qUnleashed, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md]
sources: [unleashed-readme, unleashed-docs]
---
# Application compagnon qUnleashed

::: tip Unleashed
**qUnleashed** est l'application compagnon de l'équipe Unleashed, pour téléphone et ordinateur. Elle a été
écrite de zéro en Flutter comme alternative à l'application mobile Flipper officielle : ce n'est pas un fork
de qFlipper. Licence GPL-3.0 ou ultérieure, sources et binaires sur
[DarkFlippers/qUnleashed](https://github.com/DarkFlippers/qUnleashed).
:::

Elle est faite pour Unleashed mais fonctionne aussi avec les autres firmwares. La version stable actuelle est la **0.17.2**.

## Tournera-t-elle sur votre appareil ? {#requirements}

| Système | Il vous faut |
|---|---|
| Android | 10 (API 29) ou plus récent |
| iOS | 15 ou plus récent |
| macOS | 12 ou plus récent |
| Windows | 10 ou plus récent, 64 bits |
| Linux | GLib 2.72 et glibc 2.35 — Ubuntu 22.04, Debian 12, Mint 21 ou plus récent |

Sur un Linux plus ancien, le binaire ne démarre même pas.

## Installation {#install}

Choisissez le binaire de votre système sur la
[page des releases](https://github.com/DarkFlippers/qUnleashed/releases). Il n'y a ni fiche sur un magasin
d'applications ni script d'installation.

## Connexion {#connecting}

Le Bluetooth fonctionne sur les cinq systèmes. Le port série USB fonctionne sur Android, Windows, macOS et
Linux — sur iOS il n'y a aucune option USB, parce qu'Apple interdit aux applications de dialoguer avec un
périphérique série USB.

L'application retient les Flipper que vous avez utilisés et se reconnecte toute seule. Si l'un d'eux est
branché en USB, il passe devant le dernier appareil Bluetooth. Sur Android, un service de premier plan
maintient le lien Bluetooth pendant que l'application est en arrière-plan.

## Firmware {#firmware}

- **Mise à jour** avec les canaux release et dev et leurs changelogs. Tout se télécharge et s'installe depuis
  l'application : la build Unleashed de base, celle avec les applications supplémentaires, la build compacte
  et les canaux officiels.
- **Réparation depuis le mode DFU** reflashe entièrement le Flipper par USB. Même idée que le Full Repair de
  qFlipper, pour un appareil qui ne démarre plus.
- **Notifications de release**, facultatives, avec un interrupteur distinct pour le canal dev.

## Appareil {#device}

- **Infos appareil** : version et date de build du firmware, batterie, stockage.
- **Partage du GPS et d'internet** : le téléphone donne sa position aux applications du Flipper et transporte
  le trafic réseau du Flipper. Votre firmware doit disposer de l'extension RPC GPS/réseau.
- **Bureau à distance** : l'écran du Flipper en direct sur le téléphone ou le PC, avec les boutons à l'écran.
  Sur ordinateur, vous pouvez utiliser le vrai clavier. Les captures d'écran s'exportent et l'écran
  s'enregistre en GIF.
- **Ligne de commande** : le CLI complet du Flipper. USB uniquement, donc pas sur iOS.

## Archive {#archive}

Une copie de vos clés réside sur le téléphone, une archive par Flipper. Chaque fichier est marqué **synced**,
**remote-only**, **local-only** ou **deleted** : vous voyez ce qui se trouve où, et un fichier supprimé peut
être restauré. Les fichiers peuvent être mis en favoris.

Catégories : Sub-GHz, Wardriving (autosaves compris), RFID 125, NFC, Infrared, iButton, Bad USB, JavaScript.

Vous pouvez lancer un fichier directement depuis l'application. NFC, RFID et iButton sont émulés par RPC ;
Sub-GHz, Infrared, Bad USB et JavaScript s'ouvrent dans l'application correspondante sur le Flipper.

Il y a aussi un éditeur de texte avec coloration des formats de fichiers Flipper : vous corrigez un `.sub` ou
un `.ir` sans ordinateur.

## Gestionnaire de fichiers {#file-manager}

Parcourt `/ext` (la carte SD) et `/int` (la mémoire interne). Créer, renommer, supprimer, télécharger,
envoyer et éditer des fichiers texte.

## Applications {#apps}

Le catalogue d'applications, avec recherche, catégories, tri, page de détails et captures d'écran. Installer,
mettre à jour et supprimer des applications. Il voit aussi ce qui est déjà sur le Flipper, applications
préinstallées comprises.

## Outils {#tools}

- **Pixel Draw** : un éditeur de pixel art avec gestionnaire de projets et animation multi-images. Il importe
  les animations du dauphin et affiche un aperçu en direct sur le Flipper.
- **Extract MIFARE Keys** : exécute Mfkey32 sur le téléphone à partir des nonces collectés par le Flipper. La
  procédure complète est sur [Récupération rapide des clés avec qUnleashed](/fr/nfc/qunleashed).
- **Remotes Library** : des télécommandes infrarouges issues de la source officielle et du dépôt public
  [Lucaslhm/Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB). Parcourez, cherchez, éditez le fichier
  `.ir`, puis enregistrez-le dans l'archive ou directement dans `/ext/infrared`.
- **Pulse Plotter** : trace les captures brutes d'impulsions Sub-GHz, infrarouges et RFID.
- **Saved Locations** : des points sur une carte, construits à partir de la latitude et de la longitude
  stockées dans les fichiers de l'archive.

## Récupération du Seed pour les captures Sub-GHz {#seed-recovery}

Certaines télécommandes basées sur KeeLoq (FAAC SLH, Genius, Erreka, anciennes BFT Mitto) utilisent un **Seed**
secret, nécessaire pour les décoder. Le Flipper ne fait que collecter les données, avec l'application
[Seed Capturer](/fr/subghz/seed-capturer) ; la recherche elle-même est une attaque par force brute, elle tourne
donc dans qUnleashed et non sur le Flipper.

1. Capturez la télécommande avec `Apps → Sub-GHz → Seed Capturer` : appuyez plusieurs fois sur **le même
   bouton**, un appui franc à la fois, et vérifiez que le compteur `Hops` augmente à chaque appui.
2. Connectez le Flipper à **qUnleashed** et ouvrez l'outil **Seed recovery**.
3. Choisissez votre capture dans la liste. qUnleashed lit les captures directement dans le dossier
   `subghz_seed_captures` du Flipper ; le constructeur, la fréquence et les valeurs `Fix` et `Hop` sont déjà dans
   le fichier. **Vous ne copiez, ne déplacez, ne renommez et n'éditez aucun fichier.**
4. Lancez la recherche et attendez.
5. Si le Seed est trouvé, qUnleashed renvoie le Seed et le compteur, et peut **enregistrer la télécommande
   clonée complète** dans un fichier `.sub` (le `Fix` porte déjà le numéro de série et le bouton). Remettez-le sur
   le Flipper et émettez-le, sans rien saisir dans `Add Manually`.
6. Si rien n'est trouvé, la capture avait probablement un trou. Recommencez en tenant la télécommande tout contre
   le Flipper, et appuyez sur `Reset` (<kbd>←</kbd>) pour repartir de zéro si un appui n'est pas pris en compte.

::: warning Le Seed appartient à l'installation
Sur FAAC SLH et Genius, le Seed est **différent pour chaque bouton** : capturez donc celui que vous comptez
utiliser. Sur Erreka, il est propre à la télécommande (parfois à l'installation). Sur BFT Mitto il est propre à la
télécommande, et seules les anciennes, qui ont un Seed unique, demandent une capture.
:::

La procédure entière, programmation du clone dans un récepteur comprise, est sur
[Flipper comme nouvelle télécommande](/fr/subghz/remote-prog) et [KeeLoq](/fr/subghz/keeloq).

N'utilisez ceci que sur vos propres télécommandes et portails.

## Pages liées {#related}

- [Récupération rapide des clés avec qUnleashed](/fr/nfc/qunleashed)
- [Seed Capturer](/fr/subghz/seed-capturer)
- [Application mobile Flipper](/fr/mobile/mobile-app)
- [qFlipper](/fr/mobile/qflipper)
- [Outils web](/fr/mobile/web-tools)
