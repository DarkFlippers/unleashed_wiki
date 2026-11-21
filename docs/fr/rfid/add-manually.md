---
title: Ajout manuel de clés
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Ajouter des clés 125 kHz manuellement

Vous pouvez créer une clé sans disposer du tag physique : choisissez le protocole et saisissez ses données. Le résultat
est enregistré comme une clé lue et peut être émulé ou [écrit sur un support vierge](/fr/rfid/write).

**À utiliser quand** vous connaissez le numéro imprimé sur une carte ou présent dans une base de contrôle d’accès, que
vous voulez restaurer une clé à partir de vos notes, ou tester un lecteur avec un ID précis.

## Étapes

1. Allez dans `Main Menu → 125 kHz RFID → Add Manually`.
2. Choisissez le protocole / format dans la liste (voir ci-dessous).

   ![Liste des types de tags d’Add Manually : EM-Micro EM4100, EM4100/32, EM4100/16 et Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Pour les formats structurés en facility code / numéro de carte, un choix vous est proposé :
   - **Enter FC/ID** — saisir les champs décimaux un par un. L’en-tête indique le nom du champ et sa plage, par exemple
     `Facility Code (0-255)`. <kbd>Back</kbd> revient au champ précédent.
   - **Enter Hex Data** — saisir les octets bruts.

   Les autres protocoles ouvrent directement l’éditeur hexadécimal *Enter the data in hex*.

   ![L’éditeur « Enter the data in hex » avec les octets du tag au-dessus d’un clavier hexadécimal à l’écran](/screens/lfrfid/add_manually_data.png)

4. Saisissez un nom et enregistrez. La clé est stockée sous `/ext/lfrfid/<name>.rfid`.

Pour modifier une clé enregistrée par la suite : `Saved` → clé → **Edit** (éditeur hexadécimal, même nom de fichier).

::: tip Unleashed
La saisie du **FC / numéro de carte** au lieu de l’hexadécimal, les formats **HID** supplémentaires et **Casi-Rusco**
sont des ajouts d’Unleashed. Le firmware d’origine n’accepte que l’hexadécimal. Les sommes de contrôle et la parité
Wiegand sont calculées pour vous.
:::

## La liste, dans l’ordre de l’appareil

| Libellé du menu | Enregistré comme (`Key type`) | Saisie | Octets hex |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID ou hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID ou hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID ou hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID ou hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID ou hex | 4 |
| AWID | AWID | FC/ID ou hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID ou hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID ou hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Plages des champs pour « Enter FC/ID »

| Format | Champs (décimal) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (stockés dans les 3 derniers octets, les 2 premiers à zéro) |
| HID H10301 (Wiegand 26 bits) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (format 26 bits, parité ajoutée) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26 bits, parité et CRC ajoutés) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (somme de contrôle ajoutée) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (tels que les imprime le système d’accès ; enregistré comme EM4100/32) |
| HID H10304 (37 bits) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37 bits) | Card Number uniquement (35 bits) |
| HID S10401 (37 bits) | Facility Code 0–63, Card Number (29 bits) |
| HID H10306 (34 bits) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35 bits) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Numéros de carte élevés
La saisie numérique travaille sur un entier signé de 32 bits : le tout haut d’un champ plus large que 31 bits (par
exemple le numéro de carte de 35 bits du H10302) ne peut donc être saisi que via **Enter Hex Data** / **Edit**.
:::

## Astuces

- Un numéro imprimé d’EM4100 du type `0001234567` correspond généralement à la forme **DEZ 10** ; après
  enregistrement, comparez-le sur l’écran **Info** (qui affiche FC/Card, DEZ 8 et DEZ 10) pour vérifier votre saisie.

  ![Écran Info d’un tag enregistré : nom de fichier, EM-Micro EM4100, données hexadécimales, FC/Card, DEZ 8 et DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 et EM4100/16 sont la même trame aux débits binaires RF/32 et RF/16 ; choisissez celui avec lequel
  l’original se lit.
- Pour les protocoles à saisie hexadécimale uniquement, le plus simple pour obtenir les bons octets est de lire une
  fois le tag réel et de recopier la valeur `Hex:`.

## Voir aussi

- [Protocoles](/fr/rfid/protocols) · [Format de fichier](/fr/rfid/file-format) · [Écriture](/fr/rfid/write) ·
  [Lecture](/fr/rfid/read)
