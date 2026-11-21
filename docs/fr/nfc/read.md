---
title: Lire des cartes
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Lire, enregistrer et émuler des cartes NFC

`Read` est le point d'entrée principal de l'application NFC. Le Flipper détecte le protocole tout seul, lit toutes
les données qu'il peut atteindre, exécute les attaques sur les clés là où elles s'appliquent (MIFARE Classic,
Ultralight C, Ultralight AES, MIFARE Plus SL3), puis vous laisse enregistrer, émuler ou écrire le résultat.

## Lire une carte

1. Allez dans `Main Menu → NFC → Read`.
2. L'écran affiche **« Reading — Hold card next to Flipper's back »**. Posez la carte à plat contre le **centre du
   dos** du Flipper et ne la bougez plus.

   ![Écran de lecture : Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Quand la carte est détectée, **« Don't move »** s'affiche pendant la lecture des données. Pour les cartes
   protégées, un écran d'attaque peut apparaître (attaque par dictionnaire, attaque nested, voir
   [MIFARE Classic](/fr/nfc/mifare-classic)).

   ![Attaque par dictionnaire système MIFARE Classic : déverrouillage du secteur 9, 19 clés trouvées sur 32](/screens/nfc/dict_attack.png)

4. L'écran de résultat affiche le nom de la carte et un résumé. Si un [analyseur](/fr/nfc/supported-cards) a reconnu
   la carte, vous voyez les données décodées (solde, nombre de trajets, numéro de carte…).

   ![Résultat de lecture : MIFARE Classic 1K avec son UID, 32/32 clés trouvées et 16/16 secteurs lus](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry** : demande *« Retry Reading? All unsaved data will be lost »*.
   - <kbd>→</kbd> **More** : ouvre le menu de la carte.
5. Dans **More**, choisissez **Save**, saisissez un nom dans **« Name the card »** et validez. Le fichier est écrit
   dans `/ext/nfc/<nom>.nfc`.

Le menu `More` après une lecture contient toujours **Save** et **Info** ; selon le type de carte, il contient aussi
**Emulate** / **Emulate UID**, ainsi que des entrées propres au protocole (p. ex. **Unlock**, **Show Keys**,
**Extract MFC Keys**, **Transactions** pour l'EMV).

### Cartes multi-protocoles

Certaines cartes répondent sur plusieurs protocoles (par exemple une carte bancaire qui contient aussi une zone
MIFARE Classic). Le Flipper affiche alors un menu **« Multi-protocol card »** avec des entrées comme
**Read as MIFARE Classic**. Pour contourner complètement la détection automatique, utilisez
`Main Menu → NFC → Extra Actions → Read Specific Card Type`, choisissez le type et appuyez sur <kbd>OK</kbd>.

## Types de cartes pris en charge

| Famille | Types de cartes (tels que nommés par le firmware) | Lecture | Émulation | Écriture |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Toute carte NFC-A : UID, ATQA, SAK | oui | UID seulement | — |
| MIFARE Classic | Mini, 1K, 4K (UID de 4 et 7 octets) | secteurs dont les clés sont connues | complète | vers la carte source uniquement |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | pages ouvertes, davantage après déverrouillage | complète | même type (voir plus bas) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2 ; SL0–SL3 | SL1 comme Classic, SL3 avec clés AES | SL3 complète, les autres UID | SL3 vers la carte source |
| MIFARE DESFire | DESFire | applications et fichiers non protégés | UID seulement | — |
| ISO14443-4A | Cartes ISO-DEP inconnues | UID, ATQA, SAK, ATS | UID seulement | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA ; tags NFC Forum Type 4 (NDEF) | oui | NTAG4xx : UID ; T4T : complète | T4T : oui |
| EMV | Cartes bancaires | données publiques | — | — |
| ISO14443-3B / -4B | Cartes NFC-B | UID, données d'application, infos de protocole | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | oui | — | — |
| ISO15693-3 (NFC-V) | Tags NFC-V inconnus | UID + blocs lisibles | complète | oui |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | oui, déverrouillage par mot de passe | complète | oui |
| FeliCa | FeliCa (Lite-S et autres) | IDm, PMm, blocs | complète | — |
| Texkom | Clés d'interphone Texkom TK13, TK15, TK17, MMBIT | oui | complète | — |

::: tip Unleashed
Les clés **Texkom** (porte-clés d'interphone 13,56 MHz courants en Russie, qui n'implémentent aucune norme ISO), les
dumps **MIFARE Plus SL3** avec clés AES, **Ultralight AES** et la prise en charge étendue de l'**écriture** pour les
Ultralight sont des ajouts du firmware qu'on ne trouve pas dans le firmware d'origine. MIFARE Classic bénéficie
également du dictionnaire CUID et de **Save Keys to Dictionary**.
:::

### MIFARE Classic

Pour lire les secteurs, le Flipper a besoin des clés : jusqu'à **10 clés pour 5 secteurs** (Mini), **32 clés pour
16 secteurs** (1K) ou **80 clés pour 40 secteurs** (4K). Il essaie le cache de clés propre à la carte, puis les
dictionnaires CUID, utilisateur et système, puis les attaques nested. Les détails se trouvent sur la page
[MIFARE Classic](/fr/nfc/mifare-classic) ; s'il manque encore des clés, voir [MFKey32](/fr/nfc/mfkey) et
[Attaques nested](/fr/nfc/nested-fudan).

### MIFARE Ultralight et NTAG

Les pages ouvertes sont lues directement. Les pages protégées par un mot de passe (NTAG21x, Ultralight EV1), une clé
3DES (Ultralight C) ou une clé AES (Ultralight AES) restent verrouillées jusqu'à ce que vous les déverrouilliez, voir
[Déverrouiller des cartes](/fr/nfc/unlock-with-password) et [Ultralight AES](/fr/nfc/ultralight-aes). Les
Ultralight C et Ultralight AES déclenchent automatiquement une attaque par dictionnaire.

**Write** est proposé pour un dump entièrement lu de **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11,
Ultralight 21, Ultralight C** et **Ultralight AES**, vers une carte du même type. Les Ultralight C et AES ont deux
entrées : **Write (Keep Key)** conserve la clé de la carte cible, **Write (Copy Key)** écrit aussi la clé du dump. Si
la cible est protégée par un mot de passe, AUTH0 ou des bits de verrouillage, vous obtenez
*« Card protected by password, AUTH0 or lock bits »*.

### Cartes inconnues

Pour une carte NFC-A inconnue, seuls l'UID, l'ATQA et le SAK sont enregistrés ; pour un tag NFC-V inconnu, l'UID et
les blocs lisibles. Beaucoup de lecteurs d'accès simples ne vérifient que l'UID : **Emulate UID** peut donc tout de
même fonctionner.

## Cartes enregistrées

`Main Menu → NFC → Saved` liste vos fichiers `.nfc`. Le menu d'une carte enregistrée contient (selon le type) :

- **Emulate** ou **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** +
  **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- des entrées liées au protocole : **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**,
  **Update from Initial Card**, **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (uniquement lorsqu'un fichier fantôme existe, voir plus bas)
- **Rename**, **Delete**, **Info**

## Émuler une carte

1. Allez dans `Main Menu → NFC → Saved` et choisissez la carte.
2. Sélectionnez **Emulate** (émulation complète) ou **Emulate UID** (seuls l'UID/ATQA/SAK sont émis).
3. L'écran affiche **Emulating** avec le nom de la carte. Présentez le dos du Flipper au lecteur.
4. Si le lecteur a dialogué avec la carte émulée, un bouton **Log** (<kbd>OK</kbd>) apparaît et affiche l'échange.
5. Appuyez sur <kbd>←</kbd> pour arrêter.

### Fichiers fantômes {#shadow-files}

Quand un lecteur écrit sur une carte émulée (par exemple pour mettre à jour un solde ou un compteur), le Flipper ne
modifie pas votre fichier d'origine. Il écrit le nouvel état dans un **fichier fantôme** (shadow file) placé à côté
(`<nom>.shd`). Le dump d'origine reste intact :

- **Restore to Original State** (`Saved → carte`) : demande *« Restore Card Data? »* et supprime le fichier fantôme.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3) : relit la carte physique avec les clés enregistrées
  et rafraîchit le dump. Seule la carte source est acceptée, sinon *« Wrong Card! Data management is only possible
  with source card »*.

## Si la lecture échoue

- **Rien n'est détecté** : il peut s'agir d'une carte 125 kHz. Essayez `Main Menu → 125 kHz RFID → Read`
  (voir la [section RFID](/fr/rfid/read)).
- **Mauvais type détecté / carte hybride** : utilisez `Extra Actions → Read Specific Card Type`.
- **« Lost the tag! »** pendant une longue attaque : remettez la carte exactement au même endroit et ne la bougez
  plus. Les étuis épais et le métal derrière la carte perturbent le champ.
- **Tous les secteurs / pages ne sont pas lus** : la carte est protégée. Continuez avec
  [MIFARE Classic](/fr/nfc/mifare-classic), [MFKey32](/fr/nfc/mfkey) ou
  [Déverrouiller des cartes](/fr/nfc/unlock-with-password).
- **« Plugin Not Loaded — Plugin file missing or outdated »** : les fichiers d'analyseurs `.fal` de la carte SD ne
  correspondent pas au firmware. Réinstallez ou mettez à jour le firmware avec la carte SD insérée.

## Voir aussi

- [MIFARE Classic](/fr/nfc/mifare-classic) · [Cartes prises en charge](/fr/nfc/supported-cards) · [Format de fichier NFC](/fr/nfc/file-format)
- [Cartes magiques](/fr/nfc/magic-cards) · [NFC Magic 2.0](/fr/nfc/nfc-magic)
