---
title: Format de fichier
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/iButtonFileFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-docs, unleashed-src]
---
# Format des fichiers de clé iButton (`.ibtn`)

Les clés enregistrées sont stockées dans `/ext/ibutton/` avec l’extension `.ibtn`. Un fichier contient une clé, avec
toutes les données exigées par son protocole.

## Exemple

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1992
Rom Data: 08 DE AD BE EF FA CE 4E
Sram Data: 4E 65 76 65 72 47 6F 6E 6E 61 47 69 76 65 59 6F 75 55 70 4E 65 76 65 72 47 6F 6E 6E 61 4C 65 74 59 6F 75 44 6F 77 6E 4E 65 76 65 72 47 6F 6E 6E 61 52 75 6E 41 72 6F 75 6E 64 41 6E 64 44 65 73 65 72 74 59 6F 75 4E 65 76 65 72 47 6F 6E 6E 61 4D 61 6B 65 59 6F 75 43 72 79 4E 65 76 65 72 47 6F 6E 6E 61 53 61 79 47 6F 6F 64 62 79 65 4E 65 76 65 72 47 6F 6E 6E 61 54 65 6C 6C 41 4C 69 65
```

Une clé DS1990 (les octets sont un exemple ; une vraie ROM se termine par un CRC valide) :

```text
Filetype: Flipper iButton key
Version: 2
Protocol: DS1990
Rom Data: 01 23 45 67 89 AB CD EF
```

Une clé Cyfral :

```text
Filetype: Flipper iButton key
Version: 2
Protocol: Cyfral
Data: A1 B2
```

## Version 2 (actuelle)

Les champs qui suivent `Protocol` dépendent du protocole.

| Champ | Type | Description |
|---|---|---|
| `Protocol` | chaîne | `DS1990`, `DS1992`, `DS1996`, `DS1971`, `DS1420`, `(non-specific)`, `Cyfral`, `Metakom` |
| `Rom Data` | hex | ROM de 8 octets (protocoles Dallas uniquement) |
| `Sram Data` | hex | Contenu de la SRAM (DS1992 : 128 octets, DS1996 : 8192 octets) |
| `Eeprom Data` | hex | Contenu de l’EEPROM (DS1971 : 32 octets) |
| `Data` | hex | Code de la clé (Cyfral : 2 octets, Metakom : 4 octets) |

Remarques :
- **(non-specific)** est la catégorie fourre-tout des périphériques 1-Wire inconnus (libellé de menu *Dallas
  (non-specific)*). Elle ne contient que la ROM et n’effectue aucun contrôle — utilisez-la pour les clés dont le family
  code ou le CRC est volontairement invalide. Le firmware l’enregistre sous la forme `Protocol: (non-specific)` ; le nom
  `DSGeneric` employé par la documentation officielle et les anciens fichiers reste accepté.
- Le **DS1420** est totalement compatible avec le DS1990 ; seul le family code diffère (`0x81` au lieu de `0x01`).
- L’ajout de nouveaux protocoles n’impose pas de changer la version du format — chaque protocole définit ses propres
  champs.

## Version 1 (obsolète)

```text
Filetype: Flipper iButton key
Version: 1
Key type: Dallas
Data: 01 23 45 67 89 AB CD EF
```

| Champ | Type | Description |
|---|---|---|
| `Key type` | chaîne | `Cyfral`, `Dallas`, `Metakom` |
| `Data` | hex | Données de la clé |

Les fichiers en version 1 sont toujours chargés (`Dallas` est interprété comme DS1990) et convertis en version 2
lorsque vous les enregistrez.

## Voir aussi

- [Protocoles](/fr/ibutton/protocols) · [Ajout manuel](/fr/ibutton/add-manually) · [Lecture](/fr/ibutton/read)
