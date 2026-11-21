---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic est la carte la plus répandue dans le contrôle d'accès, les interphones, les hôtels et les anciens
systèmes de transport. C'est aussi la plus « intéressante » pour le Flipper : son chiffrement Crypto-1 est cassé, de
sorte qu'avec suffisamment d'efforts les clés de presque n'importe quelle carte peuvent être récupérées, puis la
carte peut être émulée ou écrite sur une [carte vierge magique](/fr/nfc/magic-cards).

## Organisation de la mémoire

| Type | Secteurs | Blocs | Clés à trouver | SAK typique |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 blocs + 8 × 16 blocs) | 256 | 80 | `18` |

- Un **bloc** fait 16 octets. Le **bloc 0** (bloc constructeur) contient l'UID et les données du fabricant ; sur les
  cartes authentiques il est en lecture seule, ce qui est précisément la raison d'être des cartes magiques.
- Le dernier bloc de chaque secteur est le **trailer de secteur** :
  `Clé A (6 octets) | bits d'accès (4 octets) | Clé B (6 octets)`, par exemple
  `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` sur une carte vierge.
- Les bits d'accès déterminent quelle clé peut lire/écrire quel bloc. Souvent la clé A lit et la clé B écrit ; parfois
  la clé B est elle-même lisible, et ne peut alors pas servir de clé.

## Dictionnaires de clés

Le Flipper ne « connaît » jamais les clés : il essaie des clés candidates issues de dictionnaires. Ce sont tous des
fichiers texte avec une clé de 12 chiffres hexadécimaux par ligne, `#` pour les commentaires (voir
[format de fichier](/fr/nfc/file-format)).

| Dictionnaire | Chemin | Qui l'écrit |
|---|---|---|
| **Système** | `/ext/nfc/assets/mf_classic_dict.nfc` | Livré avec le firmware (écrasé à chaque mise à jour). Dans Unleashed, il contient **plus de 4000 clés**. |
| **Utilisateur** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Vous, MFKey, qUnleashed, *Save Keys to Dictionary*. Survit aux mises à jour. |
| **CUID** (par carte) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed pour les cartes à nonces *static encrypted* : une longue liste de clés candidates pour un seul UID. |
| **Cache de clés** | `/ext/nfc/.cache/<UID>.keys` | Écrit automatiquement quand vous **enregistrez** une carte ; utilisé en premier à la lecture suivante du même UID. |

::: tip Unleashed
Le dictionnaire système d'Unleashed contient un grand ensemble de clés supplémentaires collectées par la communauté
(« Extra Mifare Classic keys in system dict » dans le ReadMe). L'écran de chargement du dictionnaire CUID avec sa
barre de progression (*« CUID dictionary is loading »*) est apparu dans le build de développement 1437 / la
version 094.
:::

### Gérer le dictionnaire utilisateur sur l'appareil

1. Allez dans `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Menu Extra Actions avec MIFARE Classic Keys parmi les entrées de dictionnaires](/screens/nfc/extra_actions.png)

2. L'écran affiche **System dict: N** et **User dict: N**.
3. <kbd>OK</kbd> **Add** : saisissez une clé de 6 octets en hexadécimal et enregistrez. Une clé en doublon déclenche
   un avertissement.
4. <kbd>→</kbd> **List** (seulement si le dictionnaire utilisateur n'est pas vide) : choisissez une clé pour la
   supprimer (*« Select key to delete: »*).

Vous pouvez aussi éditer `mf_classic_dict_user.nfc` sur un ordinateur (qFlipper, qUnleashed, ou directement sur la
carte SD).

### Save Keys to Dictionary {#save-keys-to-dictionary}

Tout dump MIFARE Classic enregistré ou fraîchement lu comportant au moins une clé connue propose
**Save Keys to Dictionary** dans son menu. Cette commande copie toutes les clés de ce dump dans le dictionnaire
utilisateur, en ignorant les doublons, et signale *« New keys: N, Already known: M »*. C'est surtout important pour
les cartes dont les clés ont été retrouvées depuis un dictionnaire CUID : sans cela, ces clés ne vivent que dans ce
fichier propre à l'UID et dans le dump, alors que [NFC Magic](/fr/nfc/nfc-magic) ne regarde que le cache de clés et
les dictionnaires utilisateur/système (c'est l'« enregistrement automatique des clés avec contrôle de doublons » que
@gromovyna mentionne dans son [article sur qUnleashed](/fr/nfc/qunleashed)).

## Ce qui se passe quand vous lisez une carte MIFARE Classic

`Main Menu → NFC → Read`, maintenez la carte immobile. Le firmware passe par les étapes suivantes ; l'en-tête de
l'écran d'attaque indique celle qui est en cours.

1. **Cache de clés.** Si vous avez déjà enregistré cet UID, les clés en cache sont utilisées et la carte est lue
   immédiatement.
2. **Attaque par dictionnaire**, dans cet ordre :
   - **MF Classic CUID Dictionary** : seulement si un fichier propre à l'UID existe (avant cela,
     *« CUID dictionary is loading »* avec une barre de progression ; un gros fichier met plusieurs minutes à se
     charger).
   - **MF Classic User Dictionary** : si le fichier utilisateur existe et n'est pas vide.
   - **MF Classic System Dictionary**.

   L'écran affiche `Keys found: X/Y`, `Sectors Read: X/Y`, le numéro de la clé en cours et *« Unlocking sector: N »* /
   *« Reuse key check for sector: N »*.

   ![Attaque par dictionnaire système : déverrouillage du secteur 9, clé 1244 sur 2271, 19 clés trouvées sur 32](/screens/nfc/dict_attack.png)

3. **Lecture par backdoor.** Si la puce possède une **clé de backdoor** connue (Fudan et quelques autres), l'en-tête
   affiche **Backdoor Read** / **(Backdoor)** et les secteurs sont lus sans les vraies clés. Des nonces sont
   collectés en même temps.
4. **Attaques nested** (dès qu'au moins une clé est connue) : **PRNG Analysis**, **Nested Dictionary**,
   **Calibration**, **Nonce Collection** (*« Collecting from sector: N »*). Un suffixe **(Hard)** signifie que la
   carte a un PRNG difficile. Les nonces collectés sont ajoutés à `/ext/nfc/.nested.log`.
5. L'écran de résultat s'ouvre. Une LED verte / un son de succès signifie que la carte est entièrement lue ; un bref
   « demi-succès » signifie qu'il manque encore des secteurs.

Appuyez sur <kbd>OK</kbd> **Skip** pour passer à l'étape suivante (CUID → User → System → résultat). <kbd>←</kbd>
demande *« Exit to NFC Menu? All unsaved data will be lost »*. Si la carte est retirée, vous obtenez
**« Lost the tag! Make sure the tag is positioned correctly. »** ; remettez-la en place et l'attaque continue.

Un parcours détaillé avec des captures d'écran de chaque phase se trouve sur
[Attaques nested et backdoors Fudan](/fr/nfc/nested-fudan).

### Après la lecture

Le menu de lecture (`More`) pour une carte MIFARE Classic contient :

| Entrée | Quand | Rôle |
|---|---|---|
| **Save** | toujours | Enregistrer le dump dans `/ext/nfc/`. Remplit aussi le cache de clés. |
| **Emulate** | toujours | Émulation complète du dump. |
| **Extract MFC Keys** | carte non entièrement lue | Demande *« Save the Key? »* (Save/Skip), puis collecte des nonces auprès d'un lecteur. Voir [MFKey32](/fr/nfc/mfkey). |
| **Unlock with Dictionary** | carte non entièrement lue | Relance l'attaque par dictionnaire / nested (p. ex. après l'ajout de clés). |
| **Crack nonces in MFKey32** | carte non entièrement lue | Propose d'enregistrer la carte, puis lance l'[application MFKey](/fr/nfc/mfkey-app) (**Run**). |
| **Show Keys** | toujours | *« Found MFC Keys »* : par secteur, les bits d'accès, la clé A, la clé B et les totaux. |
| **Save Keys to Dictionary** | au moins une clé connue | Voir ci-dessus. |
| **Info** | toujours | UID, ATQA, SAK, résumé clés/secteurs ; **More** affiche le dump hexadécimal (`??` = octets inconnus). |

Sur une carte **enregistrée**, vous obtenez en plus **Write to Initial Card**, **Update from Initial Card**,
**Restore to Original State** (si un fichier fantôme existe), **Rename** et **Delete**.

## Obtenir les clés manquantes

Si tous les secteurs n'ont pas été lus, choisissez la méthode qui correspond à votre situation :

| Situation | Méthode |
|---|---|
| Vous avez la carte **et** accès au lecteur | [MFKey32](/fr/nfc/mfkey) : le Flipper émule la carte, le lecteur révèle ses clés. |
| Vous avez la carte, au moins une clé est connue ou la puce a une backdoor | Les attaques nested s'exécutent automatiquement dans `Read` ; calculez ensuite les clés avec l'[application MFKey](/fr/nfc/mfkey-app) ou, beaucoup plus vite, avec [qUnleashed](/fr/nfc/qunleashed). |
| La carte a un **PRNG difficile** | HardNested : calculé par qUnleashed ou sur un ordinateur, voir [Attaques nested](/fr/nfc/nested-fudan). |
| Pas de carte, seulement le lecteur | [MFKey32](/fr/nfc/mfkey) via `Extract MFC Keys` depuis le menu NFC principal : les clés vont dans le dictionnaire utilisateur pour plus tard. |
| Les clés sont diversifiées par carte (p. ex. [Iron Logic](/fr/nfc/iron-logic)) | Chaque carte a ses propres clés : récupérez-les individuellement pour chaque carte. |

Une fois de nouvelles clés ajoutées, relisez la carte (ou ouvrez le fichier enregistré →
**Unlock with Dictionary**).

## Émulation

1. `Main Menu → NFC → Saved → <carte> → Emulate`.
2. Présentez le Flipper au lecteur.

Les secteurs qui n'ont jamais été lus sont émulés comme inconnus : un lecteur qui en a besoin rejettera la carte. Si
le lecteur écrit sur la carte (solde, compteurs, systèmes « dynamiques »), les modifications vont dans le
[fichier fantôme](/fr/nfc/read#shadow-files).

::: warning Systèmes dynamiques
Certains systèmes réécrivent des données sur la carte à chaque passage (p. ex.
[Iron Logic en mode dynamique](/fr/nfc/iron-logic-enrollment)). Une copie émulée et l'originale se désynchronisent
alors ; utiliser les deux peut bloquer l'originale.
:::

## Écriture

- **Write to Initial Card** réécrit le dump **sur la même carte** (l'UID doit correspondre). Toute autre carte donne
  *« Use source card! To write blanks use NFC Magic app »*. Si tous les blocs n'ont pas pu être écrits :
  *« Not all sectors were written correctly »*.
- Pour cloner sur une carte vierge, utilisez l'application [NFC Magic](/fr/nfc/nfc-magic) et une
  [carte magique](/fr/nfc/magic-cards) adaptée. Choisissez la carte vierge avec soin : beaucoup de lecteurs filtrent
  les cartes Gen1.

## Dépannage

- **Des clés sont trouvées mais certains secteurs restent non lus** : les bits d'accès peuvent interdire la lecture
  avec le type de clé trouvé ; récupérez l'autre clé (A ou B).
- **La lecture commence par un long « CUID dictionary is loading »** : une grande liste de candidates propre à cet
  UID existe pour cette carte. C'est normal après une attaque sur des static encrypted nonces. Supprimez
  `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` une fois la carte entièrement récupérée et ses clés enregistrées dans
  le dictionnaire utilisateur.
- **MFKey indique « Nonces already cracked » / rien de nouveau** : nettoyez `/ext/nfc/.nested.log` et
  `/ext/nfc/.mfkey32.log` après une récupération réussie ; les anciens nonces ralentissent tout.
- **Les clés récupérées ne semblent pas utilisées** : vérifiez qu'elles ont bien atterri dans
  `mf_classic_dict_user.nfc` (`Extra Actions → MIFARE Classic Keys → List`). Les clés trouvées par HardNested sur un
  ordinateur doivent être ajoutées à la main.

## Voir aussi

[Lire des cartes](/fr/nfc/read) · [MFKey32](/fr/nfc/mfkey) · [Attaques nested](/fr/nfc/nested-fudan) ·
[Application MFKey](/fr/nfc/mfkey-app) · [qUnleashed](/fr/nfc/qunleashed) · [Cartes magiques](/fr/nfc/magic-cards) ·
[MIFARE Plus](/fr/nfc/mifare-plus)
