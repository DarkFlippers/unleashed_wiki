---
title: Ajouter des cartes manuellement
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Ajouter des cartes NFC manuellement

`Add Manually` crée une carte virtuelle sans en lire une. Deux cas d'usage :

- **Générer une carte d'un type standard** avec un UID aléatoire et un contenu par défaut (vierge), comme si vous
  aviez une carte physique neuve. Vous pouvez ensuite l'émuler pour l'« enrôler » dans un système d'accès, ou laisser
  un téléphone y écrire des données NDEF (un lien, une vCard).
- **Créer une carte NFC-A à partir de valeurs connues** : UID, ATQA et SAK. Suffisant pour les systèmes simples qui
  ne vérifient que l'UID.

## Générer une carte d'un type standard

1. Allez dans `Main Menu → NFC → Add Manually`.
2. Choisissez le type de carte (liste ci-dessous).

   ![Add Manually : liste des types de cartes avec NFC-A 7-bytes UID sélectionné](/screens/nfc/add_manually.png)

3. Un écran affichant l'**UID** généré s'ouvre. Appuyez sur <kbd>→</kbd> **More**.
4. Dans le menu, choisissez **Save** (vous pouvez aussi faire **Change UID** d'abord, ou **Emulate** tout de suite).
5. Saisissez un nom et validez. La carte est enregistrée dans `/ext/nfc/`.

Types disponibles (noms exacts tels qu'ils apparaissent dans le menu) :

| Groupe | Types |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID ; Mifare Plus S 2K / 4K, 4byte / 7byte UID ; Mifare Plus X 2K / 4K, 4byte / 7byte UID ; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID ; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Le firmware d'origine ne génère que des Ultralight/NTAG et des MIFARE Classic. Unleashed ajoute
**Mifare Ultralight C** (avec la clé 3DES par défaut `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, toutes les
variantes **MIFARE Plus**, les clés d'interphone **Texkom**, et **Change UID** juste après la génération, ce qui
permet de créer une MIFARE Classic avec un UID personnalisé (« NFC Add manually → Mifare Classic with custom UID »
dans le ReadMe).
:::

::: tip Quel type pour un téléphone ?
Pour écrire un lien ou une carte de visite depuis un téléphone, **NTAG216** convient dans la plupart des cas.
Vérifiez ce qu'attendent votre application ou votre système.
:::

## Créer une carte NFC-A à partir d'un UID, d'un ATQA et d'un SAK

Certains systèmes d'accès accordent l'accès sur la base de l'UID (parfois avec l'ATQA/SAK). Si vous connaissez ces
valeurs :

1. Allez dans `Main Menu → NFC → Add Manually`.
2. Sélectionnez **NFC-A 7-bytes UID** ou **NFC-A 4-bytes UID**.
3. **« Enter SAK in hex »** : saisissez le SAK (1 octet), validez.
4. **« Enter ATQA in hex »** : saisissez l'ATQA (2 octets), validez.
5. **« Enter UID in hex »** : saisissez l'UID, validez.
6. Nommez la carte et enregistrez.

Valeurs typiques : MIFARE Classic 1K : ATQA `00 04` (UID de 4 octets) ou `00 44` (7 octets), SAK `08` ;
Ultralight/NTAG : ATQA `00 44`, SAK `00`. Astuce pour la saisie d'octets : appuyez plusieurs fois sur <kbd>↑</kbd>
jusqu'à ce que l'éditeur de quartets apparaisse (Unleashed).

## Utiliser la carte

- **Emulate** : `Main Menu → NFC → Saved → <carte> → Emulate` (ou **Emulate UID** pour une carte NFC-A) et présentez
  le Flipper au lecteur. Pour « programmer » une clé virtuelle dans un système d'accès, mettez le système en mode
  enrôlement selon son manuel et présentez la carte émulée.
- **Edit UID** plus tard : `Saved → <carte> → Edit UID` (cartes NFC-A).

::: warning
Les différents systèmes d'accès et applications enrôlent les cartes de façons différentes ; consultez leur
documentation pour connaître les types de cartes pris en charge. Une carte virtuelle ne peut rien faire face aux
systèmes qui vérifient la cryptographie de la carte (DESFire, Plus SL3 avec des clés inconnues, EMV).
:::

## Voir aussi

[Lire des cartes](/fr/nfc/read) · [Format de fichier NFC](/fr/nfc/file-format) · [Cartes magiques](/fr/nfc/magic-cards)
