---
title: Read RAW (enregistrement du signal brut)
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/SubGhzFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/sub-ghz/read-raw]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Read RAW

**Read RAW** enregistre le signal démodulé « tel quel », sans le décoder — comme un dictaphone. L'enregistrement
peut être rejoué, sauvegardé, décodé plus tard ou édité. Utilisez-le quand :

- **Read** ne reconnaît pas la télécommande (protocole inconnu) ;
- vous voulez capturer un signal pour l'analyser ou signaler un nouveau protocole aux développeurs ;
- vous avez besoin de rejouer à l'identique un signal statique dont le Flipper ne connaît pas le protocole.

L'enregistrement s'effectue avec la **fréquence et la modulation** sélectionnées — le Flipper n'est pas un SDR. Avec
une mauvaise fréquence ou modulation, vous n'enregistrerez que du bruit.

::: warning Codes tournants
Rejouer en RAW une télécommande à code tournant revient exactement à un clone : cela fait avancer le compteur du
récepteur et peut désynchroniser votre télécommande d'origine. **Ne faites jamais cela avec une clé de voiture** —
la clé risque de se retrouver sur liste noire. Détails : [Codes tournants](/fr/subghz/rolling-codes).
:::

## Enregistrer

1. Trouvez la fréquence avec le [Frequency Analyzer](/fr/subghz/frequency-analyzer) si vous ne la connaissez pas.
2. Ouvrez `Main Menu → Sub-GHz → Read RAW`.
3. Appuyez sur <kbd>←</kbd> **Config** et réglez `Frequency`, `Modulation` et `RSSI Threshold:` (voir plus bas).
   Appuyez sur <kbd>Back</kbd> pour revenir.

   ![Read RAW prêt à enregistrer : forme d'onde vide, boutons Config et REC](/screens/subghz/read_raw.png)

4. Appuyez sur <kbd>OK</kbd> **REC**. La forme d'onde commence à défiler, le RSSI est affiché à droite.
5. Appuyez sur le bouton de la télécommande (maintenez 1–2 s).

   ![Read RAW en cours d'enregistrement : deux salves de signal sur la forme d'onde, compteur d'échantillons et bouton Stop](/screens/subghz/read_raw_recording.png)

6. Appuyez sur <kbd>OK</kbd> **Stop**.
7. Vous avez alors trois possibilités :
   - <kbd>←</kbd> **Erase** — jeter l'enregistrement et recommencer ;
   - <kbd>OK</kbd> **Send** — rejouer l'enregistrement (maintenir pour le répéter) ;
   - <kbd>→</kbd> **Save** — saisir un nom (par défaut `RAW_<date-heure>`) et enregistrer dans `/ext/subghz/`.

## Config dans Read RAW

Le menu de configuration RAW est plus court que celui de Read :

| Entrée | Valeurs | Signification |
|---|---|---|
| `Frequency` | liste des fréquences | Fréquence de réception |
| `Modulation` | `AM270`, `AM650`, `FM238`, `FM476`, `FM12K` + presets personnalisés | Preset de démodulation |
| `Sound` | `OFF` / `ON` | Jouer le signal reçu dans le haut-parleur |
| `RSSI Threshold:` | `-----`, `-85.0` … `-40.0` | N'enregistre que tant que le signal est au-dessus de ce niveau. `-----` = tout enregistrer |

::: tip Quand utiliser le seuil
Avec un seuil, le fichier ne contient que les salves de votre télécommande et pas des secondes de bruit entre les
appuis — les fichiers sont beaucoup plus petits et plus propres. Pour les captures que vous envoyez aux
développeurs, laissez-le sur `-----` (enregistrement complet).
:::

## Rejouer un RAW enregistré {#playback}

1. `Main Menu → Sub-GHz → Saved`, puis sélectionnez le fichier RAW. Il s'ouvre dans l'écran Read RAW.
2. <kbd>OK</kbd> **Send** — émet tout l'enregistrement une fois ; gardez <kbd>OK</kbd> enfoncé pour le répéter
   (**Hold to repeat**).
3. <kbd>←</kbd> **New** — démarrer un nouvel enregistrement.
4. <kbd>→</kbd> **More** :
   - `Decode` — passer l'enregistrement dans tous les décodeurs de l'application Sub-GHz ; les signaux trouvés
     peuvent être enregistrés comme des fichiers-clés normaux ;
   - `Edit` — ouvrir le fichier dans l'application [Sub-GHz RAW Edit](/fr/subghz/raw-editor) (affiché seulement si
     cette application est installée dans une version compatible) ; Sub-GHz se réouvre quand vous quittez l'éditeur ;
   - `Rename`, `Delete`.

::: tip Unleashed
`More → Decode` et `More → Edit` sont des fonctionnalités supplémentaires d'Unleashed. Avec `Edit`, vous pouvez retrouver le vrai signal dans
une capture bruitée, le rogner, fusionner des fichiers et ne décoder qu'une sélection.
:::

Les fichiers RAW longs et denses sont diffusés depuis la carte SD pendant l'émission. Si des impulsions très courtes
(moins de 10 µs) sont en jeu et que la carte est lente, l'émission peut s'arrêter avant la fin du fichier — utilisez
une bonne carte.

## Enregistrer une télécommande pour une demande de protocole

Voici la procédure demandée par les développeurs d'Unleashed pour collecter des échantillons d'un signal inconnu en
vue de le décoder et de l'ajouter à la liste des protocoles pris en charge :

1. Trouvez la fréquence avec l'analyseur. Dans Read, essayez `AM650`, `FM238`, `FM476`, `FM12K` — si rien ne se
   décode, continuez.
2. Dans Read RAW, réglez cette fréquence et **`RSSI Threshold: -----`**.
3. Faites **un RAW par modulation** : `AM650`, `FM238`, `FM476`, `FM12K`.
4. Pour chaque enregistrement : appuyez sur **REC**, puis appuyez sur un bouton de la télécommande **5 fois en le maintenant 1–2 s**,
   puis **5 fois en le maintenant environ 5 s**. Arrêtez et enregistrez.
5. Si la télécommande a plusieurs boutons, enregistrez chaque bouton de la même façon. Nommez chaque fichier d'après
   le bouton.
6. Copiez les fichiers sur un ordinateur, compressez-les dans une archive et ouvrez une issue dans le
   [dépôt du firmware](https://github.com/DarkFlippers/unleashed-firmware/issues), ou transmettez votre demande à
   l'équipe via tout autre canal disponible ([Liens officiels](/fr/community/links) — chats Telegram, [Discord](https://discord.unleashedflip.com)).
   Ajoutez de bonnes photos de la télécommande (de l'intérieur aussi, si possible), le modèle et le constructeur.

## Dépannage

- **L'enregistrement est plat / ne contient que du bruit** — mauvaise fréquence ou mauvaise modulation, ou
  télécommande trop éloignée. Tenez-la tout près.
- **Fichiers énormes** — définissez un `RSSI Threshold`.
- **Le rejeu ne fonctionne pas** — la télécommande utilise un code tournant (le récepteur rejette les anciens
  compteurs), la modulation était mauvaise, ou l'enregistrement ne contient qu'une partie du signal. Enregistrez des
  appuis plus longs.
- **L'émission s'arrête en cours de route** — carte SD lente avec un fichier long et dense. Rognez le fichier avec
  [RAW Edit](/fr/subghz/raw-editor) ou utilisez une carte plus rapide.
- **`Edit` est absent de `More`** — l'application Sub-GHz RAW Edit n'est pas installée ou est trop ancienne.

## Voir aussi

- [Read](/fr/subghz/read) · [Sub-GHz RAW Edit](/fr/subghz/raw-editor) · [Remote Analyzer](/fr/subghz/remote-analyzer)
- [Formats de fichiers (RAW, BinRAW)](/fr/subghz/file-format) · [Codes tournants](/fr/subghz/rolling-codes)
