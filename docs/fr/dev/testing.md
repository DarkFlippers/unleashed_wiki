---
title: Tests d'intégration
order: 130
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/integration_tests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/general_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/badusb_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/cli_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/goodfaps_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/gpio_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/ibutton_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/infrared_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/nfc_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/rfid_test_cases.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/testing/subghz_test_cases.md]
sources: [unleashed-docs]
---
# Tests d'intégration

En plus des [tests unitaires](/fr/dev/unit-tests), le firmware dispose d'un **plan de test d'intégration manuel** :
des cas de test pas à pas regroupés par sous-système, chacun accompagné de son résultat attendu. Il est écrit pour
les mainteneurs du dépôt, mais il est tout aussi utile si vous compilez votre propre firmware et voulez le vérifier
avant de l'utiliser ou de le partager.

Cette page résume le plan. Les listes d'étapes complètes se trouvent dans le dépôt Unleashed, sous
[`documentation/testing/`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation/testing).

## Quoi tester, et quand

- **Testez ce qui a changé, plus les régressions associées.** Testez le nouveau comportement et rejouez quelques cas
  existants du même sous-système. Exemple : en ajoutant un protocole Sub-GHz, testez-le ainsi que quelques protocoles
  existants.
- **Laissez de côté les sous-systèmes non concernés.** Inutile de tester le NFC quand seul le Sub-GHz a changé.
- **Testez tout pour les changements touchant le cœur** — si quelque chose de global a changé, déroulez tous les cas
  dans l'ordre.

Quand : **avant d'accepter une pull request** et **avant une release candidate**.

## Schéma de test commun pour les clés et les cartes

Les cas de protocole RFID, iButton et NFC réutilisent les mêmes « étapes partagées » :

1. **Lire** l'original — les données correspondent à l'original.
2. **Émuler** — lire la clé émulée avec un second Flipper ; les données sont identiques.
3. **Enregistrer** — enregistrée sous le nom indiqué ; la scène passe au répertoire *Saved*.
4. **Écrire** sur un badge vierge — un écran de réussite apparaît.
5. **Lire le badge** écrit — les données sont identiques à la clé enregistrée.

Beaucoup de cas nécessitent donc **un second Flipper**, de vrais lecteurs et des badges vierges (T5577, RW2004/RW1990,
etc.).

## Cas de test par sous-système

### Général (35 cas)

| Domaine | Ce qui est vérifié |
|---|---|
| BLE | Bluetooth actif après redémarrage ; appairage avec l'application mobile, nom du Flipper correct ; réappairage avec un second téléphone |
| U2F | Enregistrer et authentifier une clé sur le site de démonstration WebAuthn de Yubico |
| Réglages | Code PIN, Storage, Power, System, Bluetooth, Desktop, LCD and Notifications, Flipper Name |
| Archive et navigateur de fichiers | Carte SD contenant de nombreux fichiers : <kbd>↓</kbd> depuis le bureau ouvre l'Archive ; chaque onglet (Favorites, iButton, NFC, Sub-GHz, RFID, Infrared, Browser) affiche ses fichiers ; lancer, renommer, supprimer des clés |
| Cartes et protocoles | NTAG215, MIFARE DESFire, MIFARE Ultralight, MIFARE Classic 1K / 4K, Metakom |
| Mise à jour usine | Via qFlipper sous macOS, Windows 11, Ubuntu ; via les applications Android et iOS ; via le web Flipper Lab |
| Provisionnement de la région | Les six mêmes canaux que la mise à jour usine, plus le réglage de région lui-même |
| Applications | Applications de base, scripts JS, le menu du bouton Haut |
| Conformité | Tous les écrans de conformité s'affichent correctement |

### CLI (3 cas)

- **Commandes de contrôle :** `power` (off, reboot, reboot to DFU, `power 5v 1`), `gpio` (mode,
  `gpio set PA7 1` allume une LED sur la dev board), `led b 255`, `vibro 1` / `vibro 0`.
- **Commandes d'information :** se connecter avec `minicom -D /dev/ttyACM0 -b 230400` ou PuTTY ; `log debug` pendant
  l'utilisation de l'appareil, arrêter avec <kbd>Ctrl</kbd>+<kbd>C</kbd> ; comparer `device_info` / `!` avec l'écran
  d'informations du firmware (maintenir <kbd>↓</kbd> depuis le bureau pendant 3 s) ; `bt hci_info` ; `date` ;
  `help` / `?` ; `free` ; `free_blocks`.
- **Commandes de stockage :** `storage info /ext`, `storage format /ext` (refuser, puis confirmer), informations avec
  et sans la carte ; `factory_reset` — répondre `n` ne fait rien, `y` efface les réglages mais **conserve les données
  de la carte SD et l'heure**.

Valeurs de référence pour `bt hci_info` figurant dans le plan :

```
Ret: 0, HCI_Version: 11, HCI_Revision: 16484, LMP_PAL_Version: 11, Manufacturer_Name: 48,
LMP_PAL_Subversion: 8548
```

### Sub-GHz (7 cas)

| Cas | Vérifications clés |
|---|---|
| Read RAW | Enregistrer sur 315, 433, 868 MHz, y compris une télécommande chiffrée (code tournant) comme une Came Atomo ; rejouer vers les récepteurs du banc de test |
| Frequency Analyzer | Affiche la fréquence correcte de différentes télécommandes |
| Module externe | CC1101 externe (module 433,92 MHz) : l'icône passe en externe, le signal Read RAW est plus fort qu'avec l'interne ; le retour à l'interne fonctionne. Ne débranchez jamais le module pendant son utilisation — le Flipper peut se figer |
| Fichiers enregistrés | Enregistrer des signaux décodés et RAW, les ajouter aux favoris et les émettre depuis là, renommer (reste dans les favoris), supprimer |
| Réception / émission | Lire sur 315.000, 433.920 et 868.350 MHz, puis avec le saut de fréquence activé ; émettre les clés enregistrées — les relais du banc (ou un second Flipper) réagissent |
| Add Manually | Créer des signaux manuellement |

### NFC (7 cas)

| Cas | Vérifications clés |
|---|---|
| Déverrouiller NTAG/Ultralight | *Auth as* pour les deux types, avertissement de type de carte incorrect, saisie manuelle du mot de passe ; les cartes enregistrées apparaissent dans *Saved* après ~1,5 s |
| Detect Reader | Collecter des nonces depuis un lecteur (par ex. un autre Flipper), puis l'écran de QR code sur <kbd>OK</kbd> est lisible |
| Émulation | Lisible par plusieurs lecteurs, dont un Flipper à 10 mm et un Proxmark |
| Lecture | MIFARE Classic, Ultralight, NTAG, DESFire, NFC-F, cartes bancaires EMV |
| Timing | Comparer le timing d'émulation Ultralight et Classic à une référence avec un Proxmark 3 |
| Add Manually | Créer et enregistrer des cartes de tous les types, puis les émuler |
| Actions supplémentaires | *Read Specific Card Type*, *MIFARE Classic Keys* (ajouter/supprimer des clés, le bouton *List*), *Unlock SLIX* avec mot de passe |

Commandes Proxmark utilisées pour le test de timing :

```
hf 14a raw -sc 3000
trace list -t 14a --frame -u
```

### RFID 125 kHz (9 cas)

Cas de protocole avec les étapes partagées pour **EM-Marine EM4100, Motorola Indala26, HID H10301 (Picopass),
Indala26, Troyka/Podorozhnik**, plus la lecture, l'écriture sur **T5577**, Add Manually et l'émulation.

### iButton (9 cas)

**Dallas DS1971, DS1990, DS1992, DS1996**, **Cyfral**, **Metakom** : lire, enregistrer, Add Manually, émuler (lues
par différents appareils), écrire sur un badge vierge **RW2004** et le relire, modifier et supprimer des clés.

### Infrarouge (3 cas)

- **Bibliothèque universelle** — télécommandes TV, audio, climatisation : l'alimentation et les autres fonctions
  fonctionnent.
- **Apprendre une nouvelle télécommande** — ajouter/supprimer des télécommandes et des boutons, renommer, émettre les
  boutons modifiés.
- **Télécommandes enregistrées** — ajouter des boutons à une télécommande existante, piloter des appareils à **au
  moins 5 m**, supprimer tous les boutons et toutes les télécommandes.

### Bad USB (2 cas)

Sous macOS et Windows : la liste des scripts s'affiche ; le script de démonstration s'exécute avec la disposition EN
puis après changement de disposition ; le script « qFlipper download » ouvre un terminal et télécharge qFlipper ; le
passage en mode **BLE** (Bluetooth activé) s'appaire avec l'ordinateur et le script s'exécute à nouveau.

### GPIO (1 cas)

`GPIO → Manual Control` avec la dev board ST-Link insérée : les LED suivent les broches ; l'activation du 5 V allume
les LED d'alimentation.

### GoodFAPs — applications officielles (10 cas)

| Application | Vérifications clés |
|---|---|
| PicoPass | Lire une carte, enregistrer, l'*Elite Dictionary Attack* démarre |
| Weather Station | Lit une station météo simulée par un second Flipper sur différentes fréquences |
| Applications du catalogue | Installation via l'application mobile ou le web, icône et nom corrects, lancement/fermeture, mise à jour, désinstallation (application, web, navigateur de fichiers) |
| AVR Flasher | Dump AVR, Flash AVR, programmateur ISP avec `avrdude` |
| Video Game Module | Insertion du module → message d'initialisation et icône dans la barre d'état ; le HDMI recopie l'écran ; « Air Arkanoid » utilise l'accéléromètre |
| Tools | Clock (plein écran, format issu des réglages) ; NFC/RFID Detector détecte les deux types de champ |
| Signal Generator | Générateurs PWM et Clock sur différentes broches, fréquences et diviseurs |
| NFC Magic | *Check Magic Tag*, *Write Gen1a* (avec avertissement de risque), *Wipe* |
| SPI Mem Manager | Lire, écrire, effacer une puce flash SPI |
| Flashage du VGM | Application VGM Tool : *Install official firmware*, installation depuis un fichier sur la carte SD, et la méthode manuelle (bouton Boot + stockage de masse USB) |

Câblage AVR Flasher utilisé dans le plan :

| AVR | Flipper |
|---|---|
| MISO | PA6 |
| MOSI | PA7 |
| SCK | PB3 |
| RESET | PB2 |
| GND | GND |
| VCC | 3V3 |

Vérification de la lecture des fusibles (remplacez `m2560` par votre puce, par ex. `m328p`, et le port COM) :

```
avrdude.exe -p m2560 -c stk500v1 -P COM7 -U lock:r:lock.hex:r -U hfuse:r:hfuse.hex:r -U lfuse:r:lfuse.hex:r -U efuse:r:efuse.hex:r
```

::: tip Unleashed
Le plan provient du firmware officiel. Sur Unleashed, exercez aussi les ajouts propres à Unleashed dans le
sous-système que vous avez modifié — par exemple les protocoles Sub-GHz supplémentaires et le
[mode compteur](/fr/subghz/counter-mode), ou les applications supplémentaires de `applications/system/` (Remote
Analyzer, Nice-O-Code, Sec+ PIN, Seed Capturer, éditeur RAW Sub-GHz, T5577, SIM800…).
:::

## Pages liées

- [Tests unitaires](/fr/dev/unit-tests)
- [Interface en ligne de commande](/fr/dev/cli)
- [Compiler le firmware](/fr/dev/build)
