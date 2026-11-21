---
title: Formats de fichiers
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/LfRfidFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/T5577FileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-docs, unleashed-src]
---
# Formats de fichiers du RFID 125 kHz

Trois sortes de fichiers cohabitent dans `/ext/lfrfid/` :

| Extension | Ce qu’elle décrit | Créée par |
|---|---|---|
| `.rfid` | Une **carte** : protocole + ID | Read → Save, Add Manually |
| `.t5577` | Une **puce** : tous les blocs d’un T5577 | [Application T5577](/fr/rfid/t5577-app) |
| `.ask.raw` / `.ask134.raw` / `.psk.raw` | Un enregistrement de signal brut | [RAW](/fr/rfid/raw) |

## `.rfid` — clé RFID LF

```text
Filetype: Flipper RFID key
Version: 1
Key type: EM4100
Data: 01 23 45 67 89
```

Le fichier contient une clé du type indiqué par `Key type`.

| Champ | Description |
|---|---|
| `Key type` | Nom du protocole, exactement comme dans le [tableau des protocoles](/fr/rfid/protocols) |
| `Data` | Données de la clé en hexadécimal ; leur longueur est fixe pour chaque protocole |

Valeurs de `Key type` valides dans ce firmware : `EM4100`, `EM4100/32`, `EM4100/16`, `Electra`, `H10301`, `Idteck`,
`Indala26`, `Indala224`, `IoProxXSF`, `AWID`, `FDX-A`, `FDX-B`, `HIDProx`, `HIDExt`, `Pyramid`, `Viking`,
`Jablotron`, `Paradox`, `PAC/Stanley`, `Keri`, `Gallagher`, `Nexwatch`, `Radio Key`, `GProxII`, `Noralsy`.

Historique des versions : 1 — version initiale. Les anciens fichiers portant `Key type: I40134` (3 octets) sont
convertis en `Indala26` au chargement.

::: tip
Vous pouvez créer une clé depuis un ordinateur : écrivez les quatre lignes ci-dessus avec le bon `Key type` et le bon
nombre d’octets dans `Data`, copiez le fichier dans `/ext/lfrfid/` et il apparaîtra dans **Saved**.
:::

## `.t5577` — dump de T5577

```text
Filetype: Flipper T5577 dump
Version: 1
# Block 0: ASK/Manchester, RF/64, 2 data blocks, password enabled
Page 0 blocks read: 0 1 2 7
Page 0 Block 0: 00 14 80 50
Page 0 Block 1: 12 34 56 78
Page 0 Block 2: 9A BC DE F0
Page 0 Block 3: 00 00 00 00
Page 0 Block 4: 00 00 00 00
Page 0 Block 5: 00 00 00 00
Page 0 Block 6: 00 00 00 00
Page 0 Block 7: 0C 0D 0E 0F
Page 1 blocks read: 0 1
Page 1 Block 0: E0 15 00 1A
Page 1 Block 1: 20 24 10 00
Page 1 Block 2: 00 00 00 00
Page 1 Block 3: 00 00 00 00
Password: 0C 0D 0E 0F
```

Un fichier `.t5577` décrit la **puce**, un fichier `.rfid` décrit la **carte**. Un T5577 configuré en EM4100 peut être
enregistré dans l’un ou l’autre format, et les deux ne sont pas interchangeables : le `.t5577` contient la
configuration qui détermine la manière dont la puce dialogue, ainsi que le mot de passe qui la protège.

| Champ | Description |
|---|---|
| `Page 0 blocks read` | Blocs de la page 0 dont la valeur provient de la puce, séparés par des espaces |
| `Page 0 Block 0..7` | Contenu du bloc, 4 octets hexadécimaux, MSB en premier. Bloc 0 = configuration, bloc 7 = emplacement du mot de passe |
| `Page 1 blocks read` | Blocs de la page 1 qui ont été lus |
| `Page 1 Block 0..3` | Le bloc 0 reprend la configuration ; les blocs 1–3 contiennent les données de traçabilité d’usine |
| `Password` | Facultatif. Un mot de passe **dont on sait qu’il fonctionne** sur la puce |

Règles essentielles :

- **Chaque bloc a une clé**, qu’il ait été lu ou non. Seuls les blocs nommés dans `blocks read` sont du contenu ; le
  reste est du remplissage et ne doit jamais être écrit sur un tag. Un fichier qui ne liste aucun bloc est rejeté.
- Une puce protégée refuse la lecture du bloc 0 nécessaire à la détection : sans le mot de passe, vous n’obtenez donc
  aucun dump (et non un dump partiel). Un dump partiel signifie que le tag est sorti du champ.
- `Password` et `Page 0 Block 7` sont deux informations distinctes et peuvent se contredire : le bloc 7 est ce que
  contenait le bloc à la lecture (du stockage ordinaire si aucun mot de passe n’est activé), tandis que `Password` est
  un identifiant qui a fonctionné. Supprimer un mot de passe n’efface que le bit du bloc 0, le bloc 7 conserve donc son
  ancienne valeur.
- La ligne de commentaire qui décode le bloc 0 n’est destinée qu’aux humains.

### Ordre de restauration

Lors de la réécriture d’un dump (application T5577 → **Write to Tag**), l’ordre est celui du Proxmark3 :

1. Page 0, blocs 1–7. À partir du bloc 7, les écritures doivent utiliser le mot de passe désormais stocké dans le
   bloc 7.
2. Page 1, blocs 1–3 (le bloc 0 de la page 1 n’est jamais écrit). Les puces authentiques refusent de modifier les
   blocs 1–2 — signalé comme *unchanged*, et non comme un échec.
3. Page 0, bloc 0 **en dernier** — il modifie la façon dont la puce dialogue.
4. Seuls les blocs listés dans `blocks read` sont écrits.
5. Un bloc 0 à zéro n’est **jamais** écrit : une puce qui le contient ne répond plus du tout, et il n’y a pas de retour
   possible.

Les trames d’écriture ne reçoivent aucune réponse : la réussite n’est connue qu’en relisant les blocs.

## `.raw` — enregistrements RAW

Fichiers binaires écrits par la lecture RAW. Ils commencent par un en-tête :

| Champ | Type | Valeur |
|---|---|---|
| magic | uint32 | `0x4C464952` |
| version | uint32 | `1` |
| frequency | float | fréquence porteuse, en Hz (125000 ou 134200) |
| duty_cycle | float | rapport cyclique de la porteuse |
| max_buffer_size | uint32 | plus grand tampon du fichier |

suivi des tampons, chacun préfixé de sa taille et contenant des paires *(impulsion, durée)* encodées en varint.
Utilisez `rfid raw_analyze <filename>` dans la CLI pour les décoder.

## Voir aussi

- [Protocoles](/fr/rfid/protocols) · [Application T5577](/fr/rfid/t5577-app) · [RAW](/fr/rfid/raw)
