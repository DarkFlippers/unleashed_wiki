---
title: Ajout manuel de clés
order: 30
original: [https://docs.flipper.net/zero/ibutton/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# Ajouter des clés iButton manuellement

Vous pouvez créer une clé virtuelle à partir de son seul ID, sans disposer de la clé physique — par exemple d’après un
numéro gravé sur la clé ou noté auparavant. Elle peut être émulée et, pour les protocoles inscriptibles,
[écrite sur un support vierge](/fr/ibutton/write).

## Étapes

1. Allez dans `Main Menu → iButton → Add Manually`.
2. Choisissez le protocole :

   | Libellé du menu | ID à saisir |
   |---|---|
   | **Dallas DS1990** | ROM de 8 octets |
   | **Dallas DS1992** | ROM de 8 octets |
   | **Dallas DS1996** | ROM de 8 octets |
   | **Dallas DS1971** | ROM de 8 octets |
   | **Dallas DS1420** | ROM de 8 octets |
   | **Dallas (non-specific)** | ROM de 8 octets — n’importe quel périphérique 1-Wire, aucun contrôle |
   | **Cyfral** | 2 octets |
   | **Metakom** | 4 octets (chaque octet doit avoir la bonne parité) |

   ![Liste des types de clés d’Add Manually : Dallas DS1990, DS1992, DS1996 et DS1971](/screens/ibutton/add_manually.png)

3. L’écran **Enter the key** ouvre un éditeur hexadécimal. Saisissez les octets et appuyez sur **Save**.
4. Entrez un nom (préfixe par défaut `iBtn`) et enregistrez. La clé est stockée dans `/ext/ibutton/<name>.ibtn`.

## Modifier une clé enregistrée

`Main Menu → iButton → Saved` → clé → **Edit** → modifiez l’hexadécimal → **Save** → nom → **Save**.

## Remarques sur les ID Dallas

Une ROM Dallas est constituée du `family code` (1 octet) + du `serial` (6 octets) + du `CRC` (1 octet) :

```text
01 DE AD BE EF 00 00 ??
^^ family code (01 = DS1990, 81 = DS1420, 08 = DS1992, 0C = DS1996, 14 = DS1971)
                     ^^ CRC-8 over the first 7 bytes
```

- La plupart des clés d’interphone sont des DS1990 avec le family code `01`.
- Si le CRC est incorrect, un lecteur peut refuser la clé, et le Flipper signale une erreur de CRC lorsqu’il la relit.
- Besoin d’une clé avec un family code ou un CRC volontairement invalide ? Utilisez **Dallas (non-specific)** — il
  n’effectue aucun contrôle.
- Une clé ajoutée manuellement n’a **aucune donnée de mémoire** ; Full Write on Same Type exige une véritable lecture.

::: tip Éditeur d’octets
Dans Unleashed, appuyer plusieurs fois sur <kbd>↑</kbd> dans la saisie d’octets ouvre un mini-éditeur de quartets —
pratique pour les ID longs.
:::

## Voir aussi

- [Lecture](/fr/ibutton/read) · [Écriture](/fr/ibutton/write) · [Protocoles](/fr/ibutton/protocols) ·
  [Format de fichier](/fr/ibutton/file-format)
