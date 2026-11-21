---
title: Lecture des tags
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# Lire, enregistrer et émuler des tags 125 kHz

Un tag 125 kHz est un transpondeur qui, alimenté par le champ d’un lecteur, émet un ID fixe. Si le tag utilise l’un des
[protocoles pris en charge](/fr/rfid/protocols), le Flipper Zero décode cet ID, l’affiche, et peut l’enregistrer sur la
carte SD, l’émuler vers un lecteur ou l’[écrire sur un support vierge](/fr/rfid/write).

**À utiliser quand** vous voulez une copie de votre propre badge d’accès sur le Flipper, identifier le type de tag que
vous avez en main, ou récupérer l’ID pour un système de contrôle d’accès que vous administrez.

::: tip Insérez une carte SD
Les clés enregistrées, les dictionnaires et les réglages résident sur la carte microSD (`/ext/lfrfid/`). Installez le
firmware avec la carte SD insérée pour que les ressources de l’application soient présentes.
:::

## Lire un tag

1. Allez dans `Main Menu → 125 kHz RFID → Read`.
2. Placez le tag contre le **dos** du Flipper, à peu près au centre, et maintenez-le immobile. L’écran affiche
   *Don’t move card*.
3. Le Flipper enchaîne trois passes de lecture d’environ 2 secondes chacune et indique celle en cours sous la forme
   **Reading 1/3 … 3/3** : **ASK** (125 kHz), **PSK** (125 kHz) et **134kHz** (ASK à 134,2 kHz, pour les puces
   animales).

   ![Reading 1/3 avec la passe ASK active, PSK et 134 kHz en dessous, et « Don’t move card » en bas](/screens/lfrfid/read.png)

4. Surveillez la LED : elle clignote en **cyan** pendant la lecture, passe au **jaune** dès qu’elle capte quelque chose
   et au **vert** quand les trames d’un tag commencent à être décodées — pratique pour trouver le bon emplacement.
5. Une fois un tag décodé, le Flipper émet un bip et affiche l’écran de résultat :
   - en-tête : fabricant et protocole, par exemple **EM-Micro EM4100** ;
   - `Hex:` — les données brutes de la clé (les 7 premiers octets, les clés plus longues se terminant par `...`) ;
   - les champs décodés (facility code, numéro de carte, etc. — voir [protocoles](/fr/rfid/protocols)).

   ![Résultat de lecture : EM-Micro EM4100 avec ses données hexadécimales, son facility code, son numéro de carte, DEZ 8 et DEZ 10, Retry et More en bas](/screens/lfrfid/read_success.png)

6. Boutons : <kbd>←</kbd> **Retry** (demande *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More** ;
   <kbd>Back</kbd> demande si vous voulez quitter et perdre la lecture non enregistrée.

::: tip Unleashed
La documentation d’origine ne décrit que la bascule ASK/PSK. Unleashed ajoute la troisième passe à **134 kHz** (les
tags FDX-A/FDX-B sont accordés sur 134,2 kHz et les plus faibles ne répondent que là), et affiche aussi, pour
l’EM4100, les valeurs **DEZ 8** et **DEZ 10** — les formes décimales imprimées sur de nombreux porte-clés. Un EM4100
qui se décode aussi en badge Casi-Rusco C10106 reçoit une ligne supplémentaire `or C10106: …`, et une clé Generic
HIDProx est confrontée aux formats HID connus (H10304, H10302, S10401, H10306, Corp1000-35) avec affichage de leur
FC / numéro de carte.
:::

## Après la lecture : More

<kbd>→</kbd> **More** ouvre :

| Élément | Action |
|---|---|
| **Save** | Saisir un nom (préfixe par défaut `RFID`), enregistré sous `/ext/lfrfid/<name>.rfid` |
| **Emulate** | Émuler la clé immédiatement, sans l’enregistrer |
| **Write** | Écrire la clé sur un support vierge — voir [Écriture](/fr/rfid/write) |

## Lire avec une modulation fixe

Certains tags ont besoin de plus d’une passe de 2 secondes pour être décodés, ou ne sont détectés de façon fiable
qu’avec un démodulateur précis. `Main Menu → 125 kHz RFID → Extra Actions` propose :

| Élément | Ce qu’il lit |
|---|---|
| **Read ASK (Regular)** | ASK à 125 kHz uniquement, jusqu’à trouver un tag : EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | PSK uniquement : Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | ASK à 134,2 kHz uniquement — puces animales, voir [Puces d’identification animale](/fr/rfid/animal-microchips) |

En mode Debug, ce même menu contient également **Read RAW RFID data** et **Emulate RAW RFID data** — voir
[RAW](/fr/rfid/raw).

## Clés enregistrées

`Main Menu → 125 kHz RFID → Saved` ouvre le navigateur de fichiers dans `/ext/lfrfid/`. Sélectionner une clé `.rfid`
ouvre :

![Menu d’un tag enregistré avec Emulate, Write, Write and set password et Edit](/screens/lfrfid/saved_menu.png)

| Élément | Action |
|---|---|
| **Emulate** | Se faire passer pour cette clé auprès d’un lecteur |
| **Write** | L’écrire sur un support vierge ([Écriture](/fr/rfid/write)) |
| **Write and set password** | Écrire sur un T5577 et le protéger par mot de passe ([Écriture](/fr/rfid/write#write-and-set-password)) |
| **Edit** | Modifier les données de la clé en hexadécimal ; enregistré sous le même nom |
| **Rename** | Changer le nom du fichier |
| **Delete** | Supprimer le fichier (avec confirmation) |
| **Info** | Nom, protocole, données hexadécimales complètes et tous les champs décodés |

::: tip Unleashed
Le navigateur liste également les dumps de blocs **`.t5577`** (signalés par l’icône T5577). En sélectionner un lance
l’[application T5577](/fr/rfid/t5577-app) avec ce dump. Si l’application est absente, vous obtenez *No T5577 app — It
comes with the firmware - install its resources to get it*.
:::

## Émulation

1. Ouvrez une clé enregistrée (ou une lecture fraîche via **More**) et choisissez **Emulate**.
2. L’écran affiche *Emulating*, `[Protocol]` et le nom de la clé (ou *Unsaved Tag*) ; la LED clignote en magenta.

   ![Écran d’émulation affichant « Emulating », le protocole [EM4100] et le nom de la clé](/screens/lfrfid/emulate.png)

3. Maintenez le dos du Flipper bien à plat contre le lecteur. Appuyez sur <kbd>Back</kbd> pour arrêter.

## CLI

Via la CLI USB/série (commande `rfid`) :

```text
rfid read <optional: normal | indala | ask134>   - read in ASK/PSK mode
rfid <write | emulate> <key_type> <key_data>      - write or emulate a card
rfid raw_read <ask | ask134 | psk> <filename>     - read and save raw data to a file
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` est le nom du protocole tel qu’il est stocké dans les fichiers `.rfid` (par exemple `EM4100`, `H10301`),
`key_data` est en hexadécimal.

## Dépannage

- **Rien n’est détecté.** La carte est peut-être en 13,56 MHz — essayez le [NFC](/fr/nfc/read). Beaucoup de cartes
  « bi-technologie » contiennent les deux.
- **La lecture tourne en boucle.** Essayez un mode fixe dans **Extra Actions** — une passe de 2 s peut être trop courte
  pour certains tags.
- **Tags faibles / petits porte-clés.** Déplacez lentement le tag sur le dos de l’appareil ; guettez la LED
  jaune/verte. Ne le tenez pas dans la main au-dessus d’une surface métallique.
- **Protocole inconnu.** Réalisez une capture [RAW](/fr/rfid/raw) et transmettez-la aux développeurs.
- **Émulation refusée.** Certains lecteurs sont exigeants sur la distance et l’orientation — tenez le Flipper à plat et
  essayez plusieurs positions. Les lecteurs qui vérifient autre chose que l’ID (cartes à crypto, par exemple) ne peuvent
  pas être trompés par l’émulation.

## Voir aussi

- [Écriture sur supports vierges](/fr/rfid/write) · [Ajout manuel](/fr/rfid/add-manually) ·
  [Protocoles](/fr/rfid/protocols) · [Format de fichier](/fr/rfid/file-format)
