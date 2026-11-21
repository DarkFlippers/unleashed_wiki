---
title: Carte microSD
order: 90
original: [https://docs.flipper.net/zero/basics/sd-card, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/storage_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Carte microSD

La carte microSD n'est pas optionnelle. Elle contient vos clés, cartes et télécommandes enregistrées, toutes les
applications `.fap` (y compris les applications Unleashed intégrées), les bases de données, le paquet de mise à jour
et, dans le firmware actuel, même le **stockage interne**.

## Choisir une carte

- **Capacité :** 16 à 32 Go suffisent largement. Jusqu'à 256 Go est pris en charge, mais les grandes cartes mettent
  plus de temps à être montées.
- **Système de fichiers :** FAT12, FAT16, FAT32 ou exFAT.
- **Qualité :** utilisez une carte **de marque** (SanDisk, Kingston…). Le Flipper dialogue avec la carte en **SPI**, et
  non via le mode SDIO rapide utilisé par les téléphones et les PC. Toutes les cartes ne gèrent pas bien le SPI, même
  si elles fonctionnent parfaitement ailleurs. Une mauvaise carte rend le Flipper lent, peut vider la batterie plus
  vite (jusqu'à ~50 mA au lieu de ~30 mA) et peut corrompre les données.
- Les lectures en SPI atteignent près de 600 Kio/s, ce qui est suffisant pour tout ce que fait le Flipper.

## Insertion

1. Le logement se trouve en bas du Flipper.
2. Tenez la carte **contacts vers le haut** et poussez-la jusqu'au clic.
3. L'icône SD apparaît dans la barre d'état.

## Si la carte n'est pas reconnue

Un message concernant la carte SD apparaît, ou l'icône de la barre d'état est barrée. Causes possibles :

| Cause | Solution |
|---|---|
| Système de fichiers absent ou incompatible | Formatez la carte (voir ci-dessous) |
| Poussière dans le logement | Nettoyez-le prudemment à l'air comprimé |
| La carte ne gère pas le SPI | Utilisez une autre carte |
| La carte est endommagée | Utilisez une autre carte |

## Settings → Storage

**Main Menu → Settings → Storage**

| Entrée | Rôle |
|---|---|
| **About Internal Storage** | Nom, type `Virtual (/.int on SD)`, espace total et libre, flash disponible |
| **About SD Card** | Nom de volume, type de système de fichiers, espace total et libre, fabricant et numéro de série |
| **Unmount SD Card** / **Mount SD Card** | Démonter proprement avant de retirer la carte, ou la remonter. Le montage peut brièvement couper l'alimentation des modules externes |
| **Format SD Card** | Formate la carte. **Toutes les données seront perdues !** |
| **Benchmark SD Card** | Teste la vitesse d'écriture et de lecture en mode SPI |
| **Factory Reset** | Efface le stockage interne (réglages, appairage, dauphin). Voir [Restauration](/fr/start/recovery#factory-reset) |

### Formatage

1. **Settings → Storage → Format SD Card**.
2. Confirmez avec <kbd>→</kbd> **Format**.
3. Attendez le message `Formatted`, puis appuyez sur **Finish**.

Si le formatage échoue sur le Flipper (`Cannot Format SD Card`), formatez la carte sur un PC en FAT32/exFAT, ou essayez
une autre carte.

### Retrait en toute sécurité

1. **Settings → Storage → Unmount SD Card** → <kbd>→</kbd> **Unmount**.
2. Lorsque vous voyez `SD Card Unmounted` / `You can remove SD card now.`, poussez la carte pour la déverrouiller puis
   retirez-la.

Retirer une carte pendant que le Flipper y écrit peut corrompre des fichiers ou le système de fichiers.

### Benchmark

Le benchmark écrit un fichier de test `/ext/rwfiletest.bin` et affiche des lignes du type `4096b : W 300K R 600K` :
taille de bloc, puis vitesses d'écriture et de lecture en Kio/s. Une carte doit écrire **au moins ~260 Kio/s** pour un
fonctionnement normal. Les résultats diffèrent des benchmarks sur PC parce que le test s'exécute en mode SPI.
Lancez-le plusieurs fois pour obtenir une image fidèle.

## Structure des dossiers

`/ext` est la racine de la carte. Les principaux dossiers :

| Dossier | Contenu |
|---|---|
| `/ext/subghz/` | Fichiers Sub-GHz `.sub`. `assets/` contient `dangerous_settings`, `setting_user.example` (modèle pour votre propre liste de fréquences) et le trousseau KeeLoq `keeloq_mfcodes` |
| `/ext/subghz_remote/` | Configurations Sub-GHz Remote |
| `/ext/nfc/` | Fichiers NFC `.nfc`. `assets/` contient les dictionnaires de clés |
| `/ext/lfrfid/` | Fichiers RFID 125 kHz `.rfid` |
| `/ext/ibutton/` | Fichiers iButton `.ibtn` |
| `/ext/infrared/` | Télécommandes IR `.ir`. `assets/` contient les bibliothèques de télécommandes universelles |
| `/ext/badusb/` | Scripts Bad USB (`.txt`). `assets/layouts/` contient les dispositions de clavier (`.kl`) |
| `/ext/apps/` | Applications `.fap` classées par catégorie (applications intégrées et packs d'applications) |
| `/ext/apps_data/` | Données et réglages des applications |
| `/ext/dolphin/` | `name.settings` (nom personnalisé) et animations |
| `/ext/update/` | Paquets de mise à jour décompressés |
| `/ext/.int/` | Support du stockage interne (`/int`). Ne le modifiez pas à la main |

::: tip
Sauvegardez l'intégralité de la carte de temps en temps (qFlipper permet de télécharger les fichiers, ou copiez-les
depuis un PC). Vos clés et vos télécommandes n'existent que sur la carte.
:::

## macOS : fichiers cachés et tri {#macos-hidden-files-and-sorting}

macOS laisse des fichiers `._*` et `.DS_Store` sur la carte. Pour les nettoyer :

```bash
sudo dot_clean -mn /Volumes/Flipper\ SD
```

Remplacez `Flipper\ SD` par le nom de votre carte.

Le navigateur de fichiers liste les fichiers plus vite lorsque le répertoire FAT est trié. Sous macOS (avec
[Homebrew](https://brew.sh)) :

```bash
brew install fatsort
diskutil list                         # find the card, e.g. disk4s1
diskutil unmount /Volumes/Flipper\ SD
sudo fatsort -n /dev/disk4s1          # use your own disk id
```

`fatsort` est également disponible sous Linux.

## Pages liées

- Ce qui est conservé lors d'une mise à jour : [Mise à jour](/fr/start/updating)
- Formats de fichiers : [Sub-GHz](/fr/subghz/file-format), [NFC](/fr/nfc/file-format),
  [RFID](/fr/rfid/file-format), [Infrarouge](/fr/infrared/file-format), [iButton](/fr/ibutton/file-format)
