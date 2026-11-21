---
title: Lecture des clés
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Lire, enregistrer et émuler des clés iButton

Le Flipper Zero lit les clés Dallas 1-Wire (leur ID et, pour les clés à mémoire, le contenu de celle-ci), les clés
Cyfral et Metakom, puis peut les enregistrer et les émuler.

| Clé | Ce qui est lu |
|---|---|
| Dallas **DS1990** / **DS1420** | Uniquement la ROM de 8 octets (l’ID) — la clé n’a pas de mémoire |
| Dallas **DS1992** | ROM + 128 octets de SRAM |
| Dallas **DS1996** | ROM + 8192 octets de SRAM |
| Dallas **DS1971** | ROM + 32 octets d’EEPROM |
| Autres périphériques 1-Wire | ROM seule, affichée comme **Dallas (non-specific)** |
| **Cyfral** | Code de 2 octets |
| **Metakom** | Code de 4 octets |

## Lire une clé

1. Allez dans `Main Menu → iButton → Read`. L’écran affiche **Reading — Connect key with pogo pins**.

   ![Écran de lecture avec le message « Connect key with pogo pins »](/screens/ibutton/read.png)

2. Présentez la clé sur la **partie plate** de la plage iButton, de sorte que son centre touche la **broche de données
   de gauche** et sa couronne la **broche de masse du milieu**. Maintenez-la immobile.
3. Dès que la clé est lue, le Flipper émet un bip et affiche le protocole (par exemple **Dallas DS1990**) et son ID.

   ![Résultat de lecture : Dallas DS1990 avec son ID de huit octets et son family code, Retry et More en bas](/screens/ibutton/read_success.png)

4. Boutons : <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> demande *Exit to iButton Menu? All unsaved
   data will be lost!*

**More** propose (les entrées dépendent du protocole) :

| Élément | Quand il apparaît | Action |
|---|---|---|
| **Save** | toujours | Nommer la clé, enregistrée dans `/ext/ibutton/<name>.ibtn` |
| **Emulate** | toujours | Émuler immédiatement |
| **Write ID** | protocoles inscriptibles | Écrire l’ID sur un support vierge — [Écriture](/fr/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Copier la mémoire vers une clé du même type |
| **Data Info** | DS1992, DS1996, DS1971 | Afficher le dump de la mémoire |

## Erreurs de lecture

Si les données ne passent pas le contrôle du protocole, l’écran d’erreur en explique la raison et propose malgré tout
**Retry** et **More** :

- **CRC Error** (Dallas) — le 8e octet de la ROM est un CRC calculé sur les sept premiers ; l’écran montre la ROM avec
  l’octet fautif mis en évidence, ainsi que l’*Expected CRC*. C’est en général un mauvais contact : nettoyez la clé et
  relisez-la. Si l’erreur persiste, vous pouvez quand même enregistrer la clé et tenter l’émulation — certains lecteurs
  ignorent le CRC. Si l’émulation échoue, l’erreur n’est pas corrigeable.
- **Invalid Metakom key: odd parity in byte N** — un octet Metakom n’a pas passé son contrôle de parité ; relisez la clé.

## Clés enregistrées

`Main Menu → iButton → Saved` ouvre `/ext/ibutton/`. Le menu d’une clé :

| Élément | Action |
|---|---|
| **Emulate** | Émuler vers un lecteur |
| **Write ID** | Écrire l’ID sur un support vierge |
| **Full Write on Same Type** | DS1992/DS1996/DS1971 uniquement — copier la mémoire |
| **Edit** | Modifier l’ID en hexadécimal, puis enregistrer sous un nom |
| **Rename** / **Delete** | Gérer le fichier |
| **Info** | Nom, protocole, ID ; <kbd>→</kbd> **More** affiche le contenu de la mémoire pour les clés à mémoire |

## Émulation

1. Ouvrez une clé enregistrée → **Emulate** (ou **More → Emulate** juste après la lecture). L’écran affiche
   **Emulating**, `[Protocol]` et le nom de la clé (ou *Unsaved Key*).

   ![Écran d’émulation affichant « Emulating », le protocole [DS1990] et le nom de la clé](/screens/ibutton/emulate.png)

2. Appuyez la **partie saillante** de la plage contre le lecteur : la **broche de données de droite** doit toucher le
   centre du lecteur, la **broche de masse du milieu** sa couronne.
3. Si la broche de masse n’atteint pas la couronne, branchez deux fils : GPIO **17** → centre du lecteur,
   GPIO **8 / 11 / 18** (GND) → couronne.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Dépannage

- **Rien ne se passe.** La clé ne touche pas les deux broches — inclinez-la pour que sa couronne touche la broche de masse.
- **Clé non prise en charge.** Elle utilise peut-être un protocole non pris en charge (ou c’est un badge RFID — essayez
  le [RFID 125 kHz](/fr/rfid/read)).
- **Émulation refusée.** Vérifiez le contact des broches ; certains lecteurs détectent les émulateurs ou contrôlent des
  éléments que le Flipper ne peut pas imiter. Si vous avez modifié ou saisi la clé à la main, revérifiez l’ID.

## Voir aussi

- [Écriture](/fr/ibutton/write) · [Ajout manuel](/fr/ibutton/add-manually) · [Protocoles](/fr/ibutton/protocols) ·
  [Format de fichier](/fr/ibutton/file-format)
