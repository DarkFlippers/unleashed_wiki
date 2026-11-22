---
title: Ce qu'Unleashed ajoute
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings]
sources: [unleashed-readme, unleashed-src]
---
# Ce qu'Unleashed ajoute

Unleashed est construit sur le firmware officiel (OFW) et reste **entièrement compatible avec son API et ses
applications**. Tout ce que fait le firmware d'origine continue de fonctionner. Ci-dessous figurent les ajouts et modifications par rapport au firmware officiel (OFW), classés par domaine,
avec des liens vers les pages du wiki qui détaillent chaque fonction.

## Sub-GHz : bibliothèque radio et matériel

- **Restrictions régionales de transmission supprimées.** Toutes les fréquences prises en charge par la puce CC1101
  peuvent émettre, sans manipulation supplémentaire.
- **Fréquences supplémentaires** dans la liste par défaut et liste de fréquences modifiable par l'utilisateur : [Fréquences et presets](/fr/subghz/frequencies).
- **Plage de fréquences étendue en option**, au-delà des spécifications de la puce. Cela peut endommager le matériel :
  [Réglages dangereux](/fr/start/dangerous-settings).
- **Un grand nombre de protocoles supplémentaires**, avec la possibilité d'**enregistrer et d'envoyer de nombreux systèmes à codes
  tournants** : [Systèmes pris en charge](/fr/subghz/supported-systems),
  [Codes tournants](/fr/subghz/rolling-codes), [KeeLoq](/fr/subghz/keeloq).
- Prise en charge du **module CC1101 externe** via le SPI matériel, avec pilotage de l'amplificateur et de la LED :
  [CC1101 externe](/fr/subghz/external-cc1101).
- **Modes de compteur spéciaux** pour les codes tournants, afin d'éviter la désynchronisation : [Mode compteur](/fr/subghz/counter-mode).

## Sub-GHz : application principale

- **Les derniers réglages utilisés sont mémorisés** (fréquence, modulation…).
- **Améliorations du Frequency Analyzer** : le fonctionnement de base est identique au firmware officiel, avec en plus
  dans Unleashed <kbd>OK</kbd> pour envoyer la fréquence détectée vers Read et un appui long sur <kbd>OK</kbd> pour passer directement à Read : [Frequency Analyzer](/fr/subghz/frequency-analyzer).
- **Améliorations de Read** : affiche le moment où chaque signal a été reçu. Maintenez <kbd>→</kbd> dans la liste pour
  supprimer un signal. Les protocoles multi-systèmes affichent le nom du système décodé (CAME, Nice FloR-S, FAAC SLH,
  KeeLoq) : [Read](/fr/subghz/read).
- **Noms de protocole dans les noms de fichiers** : `Radio Settings → Protocol Names = ON` nomme les fichiers
  enregistrés avec un horodatage suivi du protocole.
- **Boutons personnalisés** pour KeeLoq, Alutech AT4N, Nice Flor S, Somfy Telis, Security+ 2.0, CAME Atomo, BelKorn et
  d'autres. Utilisez les flèches de la croix directionnelle pour envoyer le code d'un autre bouton :
  [Utilisation comme télécommande](/fr/subghz/remote).
- **`Add manually` étendu** : une entrée par système, sélecteur de bande, mode avancé avec TE, temps de garde et
  d'autres champs. Créez des télécommandes FAAC SLH, BFT Mitto, Somfy Telis, Nice Flor S, CAME Atomo et d'autres, puis
  appariez-les à un récepteur : [Add manually](/fr/subghz/add-manually),
  [Programmer une nouvelle télécommande](/fr/subghz/remote-prog).
- **Read RAW → More → Edit** ouvre un fichier RAW directement dans Sub-GHz RAW Edit :
  [Éditeur RAW](/fr/subghz/raw-editor).
- **Filtres d'exclusion** pour les protocoles bruyants (alarmes, capteurs, sonnettes, porte-clés traceurs, éclairages
  Feron…) et options de débogage (pas d'incrémentation du compteur, sortie sur broche de débogage) :
  [Réglages Sub-GHz](/fr/subghz/settings).

## Applications Sub-GHz

| Application | Rôle | Page |
|---|---|---|
| Sub-GHz Remote | Associer jusqu'à 5 fichiers `.sub` aux boutons, avec un configurateur intégré | [Remote](/fr/subghz/remote) |
| Sub-GHz Bruteforcer | Brute force de codes statiques, fichiers personnalisés, délai et répétitions | [Bruteforce](/fr/subghz/bruteforce) |
| Remote Analyzer | Décoder une télécommande à la fois, avec analyseur de fréquences intégré | [Remote Analyzer](/fr/subghz/remote-analyzer) |
| Nice O-Code | Retrouver le code installateur d'une télécommande Nice O-Code | [Nice O-Code](/fr/subghz/nice-o-code) |
| Security+ PIN | Trouver le code du clavier d'un signal Security+ 2.0 | [Security+ PIN](/fr/subghz/secplus-pin) |
| Seed Capturer | Collecter des paires Fix + Hop (FAAC SLH, Genius, Erreka, BFT Mitto) pour retrouver la seed | [Seed Capturer](/fr/subghz/seed-capturer) |
| Sub-GHz RAW Edit | Rogner, fusionner et décoder des captures RAW | [Éditeur RAW](/fr/subghz/raw-editor) |

## NFC, RFID et iButton

- **Clés MIFARE Classic supplémentaires** dans le dictionnaire système : [MIFARE Classic](/fr/nfc/mifare-classic).
  Guides de récupération de clés : [Nested et Fudan](/fr/nfc/nested-fudan), [MFKey](/fr/nfc/mfkey).
- **MFKey** directement sur l'appareil : [Application MFKey](/fr/nfc/mfkey-app).
- **Protocole EMV et parseur de données publiques** : [Cartes bancaires (EMV)](/fr/nfc/emv).
- **NFC `Add manually` → MIFARE Classic avec UID personnalisé** : [Add manually](/fr/nfc/add-manually).
- **De nombreux parseurs de cartes supplémentaires** (cartes de transport et municipales : Troika, Umarsh,
  Zolotaya Korona, Kazan, Metromoney, carte sociale de Moscou et d'autres) :
  [Cartes prises en charge](/fr/nfc/supported-cards).
- **NFC Magic 2.0** pour les cartes magic, y compris Ultralight : [NFC Magic](/fr/nfc/nfc-magic).
- **Application T5577** : lire, modifier et écrire des blocs, effacer la puce ou son mot de passe, sniffer de mot de passe (`Sniff Password`) : [Application T5577](/fr/rfid/t5577-app).
- Format d'affichage **EM4100 DEZ 8** : [Lire en RFID](/fr/rfid/read).
- **Fuzzers RFID et iButton** : [RFID Fuzzer](/fr/rfid/fuzzer), [iButton Fuzzer](/fr/ibutton/fuzzer).

## Infrarouge

- La télécommande universelle TV a été refaite pour couvrir **tous les boutons**.
- **Vaste collection de télécommandes universelles pour projecteurs, ventilateurs, climatiseurs et audio** (barres de
  son…), régulièrement mise à jour, vérifiée et enrichie par l'équipe.
- Protocole **RCA** et prise en charge du module IR externe (détecté automatiquement) :
  [Télécommandes universelles](/fr/infrared/universal-remotes).
- Comment réaliser de bonnes captures à intégrer dans la base de données des télécommandes universelles :
  [Captures IR](/fr/infrared/captures).

## Bad USB et USB/Bluetooth

- **BadKB** : exécuter des scripts Bad USB via **Bluetooth**, intégré à l'application Bad USB :
  [Bad USB](/fr/badusb/usage).
- **Dispositions de clavier**, et la commande `DUCKY_LANG` qui permet à un script de choisir sa propre disposition :
  [Format des scripts](/fr/badusb/script-format).

## Bureau, réglages et confort d'utilisation

- **Nom personnalisé du Flipper** dans **Settings → Desktop → Change Flipper Name** :
  [Nom personnalisé](/fr/start/custom-name).
- **Horloge sur le bureau** (`Settings → Desktop → Show Clock`) et **styles de batterie** (`Battery View` : Bar, %,
  Inv. %, Retro 3, Retro 5, Bar %) : [Bureau](/fr/start/desktop).
- **Verrouillage par appui long sur <kbd>↑</kbd>** depuis le bureau : avec le PIN s'il y en a un, verrouillage simple
  sinon.
- **Plus de jeux en Dummy Mode** : chaque flèche (appui court et appui long) et <kbd>OK</kbd> peuvent lancer leur propre
  application.
- Prise en charge du **[mod de rétroéclairage RGB](https://github.com/quen0n/flipperzero-firmware-rgb#readme)** dans **LCD and Notifications → RGB Mod Settings** (uniquement pour
  les Flipper modifiés matériellement).
- **Curseur dans la saisie de texte**, et **mini-éditeur de saisie d'octets** (appuyez plusieurs fois sur <kbd>↑</kbd>
  jusqu'à ce que l'éditeur de quartets apparaisse).
- **Archive** avec des onglets supplémentaires (SubRem pour les maps Sub-GHz Remote, Phone pour le répertoire SIM800).

Toutes les entrées de réglages sont décrites dans [Paramètres](/fr/start/settings).

## Applications intégrées {#built-in-apps}

Ces applications sont compilées depuis le dépôt du firmware et installées dans `/ext/apps/` par chaque mise à jour,
dans **toutes** les variantes de build (`e`, sans suffixe, `c`). Les packs d'applications ne les contiennent pas, de
sorte qu'un pack ne peut jamais les écraser ni les rétrograder.

**Dans le menu principal :** GPIO, iButton, Infrared, NFC, 125 kHz RFID, Bad USB (avec BadKB), U2F, **Clock** (réglages
de luminosité, alarme, minuteur), **Sub-GHz Remote**. Sub-GHz, Archive et Settings font partie du binaire du firmware.

**Dans Apps :**

| Application | Catégorie | Page |
|---|---|---|
| MFKey | NFC | [Application MFKey](/fr/nfc/mfkey-app) |
| T5577 | RFID | [Application T5577](/fr/rfid/t5577-app) |
| Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer, Sub-GHz RAW Edit | Sub-GHz | voir le tableau ci-dessus |
| SIM800 (appels, SMS, répertoire, USSD, terminal AT) | GPIO | [SIM800](/fr/gpio/sim800) |
| FindMy Flipper (balise Apple FindMy / Google Find My Device) | Bluetooth | [Catalogue d'applications](/fr/apps/catalog) |
| USB Keyboard & Mouse, Bluetooth Remote | USB / Bluetooth | [Contrôleurs](/fr/apps/controllers) |
| Snake Game | Jeux | — |

## Packs d'applications de la communauté

- **Pack de base** (dans les builds sans suffixe et `e`) et **pack supplémentaire** (uniquement `e`) : sources et liste
  complète sur [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev). Les packs les plus
  récents se trouvent sur les [releases GitHub](https://github.com/xMasterX/all-the-plugins/releases/latest).
- Le catalogue officiel fonctionne également : [lab.flipper.net/apps](https://lab.flipper.net/apps) ou l'application
  mobile.
- Plus de détails : [Catalogue d'applications](/fr/apps/catalog),
  [Applications sur la carte SD](/fr/apps/sd-card-apps).

## Applications compagnons et outils web

- **qUnleashed** : application compagnon pour téléphone et PC : [qUnleashed](/fr/mobile/qunleashed-app).
- **Outils web** : [Web Installer](https://web.unleashedflip.com), carte Sub-GHz
  ([map.unleashedflip.com](https://map.unleashedflip.com)), carte de wardriving Wi-Fi
  ([wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)), flasheur web ESP32
  ([espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)) : [Outils web](/fr/mobile/web-tools).
