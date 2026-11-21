---
title: Enregistrement RAW
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Lire des données 125 kHz en RAW

Le mode RAW enregistre le signal du tag tel quel — les durées d’impulsion et de période — au lieu de le décoder, un peu
comme un dictaphone. Il est destiné à la **recherche sur les protocoles** : si votre tag n’est pas reconnu,
enregistrez-le et envoyez les fichiers (avec une photo de la carte) aux développeurs dans une issue GitHub.

## Activer le mode Debug

Les entrées RAW restent masquées tant que Debug n’est pas activé :

1. `Main Menu → Settings → System`.
2. Passez **Debug** sur **ON**.

## Enregistrer

1. Allez dans `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Nommez l’enregistrement (par défaut `RfidRecord`).
3. Lisez les instructions (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) et appuyez sur <kbd>OK</kbd>.
4. Maintenez la carte sur le dos du Flipper. Celui-ci enregistre trois passes de **5 secondes** chacune — *Reading
   ASK*, *ASK 134kHz*, *Reading PSK* — et demande *Don’t move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Appuyez sur <kbd>OK</kbd>.

Trois fichiers sont créés dans `/ext/lfrfid/` :

| Fichier | Passe |
|---|---|
| `<name>.ask.raw` | ASK, porteuse 125 kHz |
| `<name>.ask134.raw` | ASK, porteuse 134,2 kHz |
| `<name>.psk.raw` | PSK, porteuse 125 kHz |

::: tip Unleashed
La documentation d’Unleashed et le firmware d’origine mentionnent deux fichiers (ASK et PSK). Le firmware actuel
enregistre une troisième passe, **ASK 134kHz**, pour les tags animaux.
:::

Si vous voyez *RAW Reading error! This may be caused by SD card issues*, vérifiez la carte (espace libre, erreurs).
Sans carte SD, l’application affiche *No SD Card!*.

## Rejouer un enregistrement

`Extra Actions → Emulate RAW RFID data` ouvre le navigateur de fichiers pour les fichiers `.raw` et rejoue celui que
vous sélectionnez (*Emulating RAW RFID*). C’est surtout utile pour déboguer des protocoles, pas comme substitut à
l’émulation normale.

## CLI

La même chose est disponible en CLI, ce qui est pratique en développement :

```text
rfid raw_read <ask | ask134 | psk> <filename>   - read and save raw data to a file
rfid raw_emulate <filename>                     - emulate raw data
rfid raw_analyze <filename>                     - print the raw data and try to decode it
```

`raw_analyze` affiche chaque paire impulsion/durée, signale l’endroit où un protocole a été décodé, et se termine par
la fréquence, le rapport cyclique, les moyennes et le protocole détecté (ou `not found`).

## Application LF-RFID Debug

Les sources du firmware contiennent également un outil de développement, **LF-RFID Debug**
(`applications/debug/lfrfid_debug`), dont l’écran **Tune** ajuste en direct le timer de la porteuse (ARR/CCR — fréquence
et rapport cyclique). C’est une application de débogage destinée au développement de protocoles, inutile pour un usage
normal.

## Voir aussi

- [Formats de fichiers](/fr/rfid/file-format) · [Lecture](/fr/rfid/read) · [Protocoles](/fr/rfid/protocols)
