---
title: Protocoles pris en charge
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Protocoles 125 kHz pris en charge

Ce tableau est établi d’après `lib/lfrfid/protocols/` du firmware Unleashed. Tous les protocoles peuvent être **lus**,
**enregistrés**, **émulés** et **ajoutés manuellement** ; les dernières colonnes indiquent quelles puces vierges
peuvent les porter (voir [Écriture](/fr/rfid/write)).

- **Nom** — tel qu’il s’affiche à l’écran et tel qu’il est stocké dans les fichiers `.rfid` sous `Key type`.
- **Lecture** — la passe de lecture qui le décode : ASK, PSK ou les deux.
- **Octets** — longueur du champ `Data:`.

| Nom | Fabricant | Lecture | Octets | Champs affichés | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | identiques (débit RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | identiques (débit RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (Wiegand 26 bits) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, pays, température, indicateur animal… | ✓ | ✓ | — | — |
| HIDProx | Generic | ASK | 6 | longueur en bits ; formats HID correspondants | ✓ | — | — | — |
| HIDExt | Generic | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, contrôle CRC | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n bits (FC, Card) ou RKKTH en clair (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = les cibles 8265/H5, 8210 et H5.5. ² Le 8268 (Hitag S) n’accepte que l’EM4100 au débit RF/64 et est
désactivé par défaut.

::: tip Unleashed
Par rapport à la liste de la documentation officielle, ce firmware ajoute l’**Indala224** et une passe de lecture à
**134,2 kHz** pour FDX-A/FDX-B. La documentation officielle du format de fichier omet également EM4100/32, EM4100/16,
Electra, Nexwatch, Radio Key, Noralsy et Indala224 — qui sont ici des valeurs `Key type` valides.
:::

## Remarques sur certains protocoles

- **EM4100 / EM-Marin** — le type de porte-clés le plus répandu dans la CEI (« ЕМ-Марин »). ID de 40 bits ; le FC est
  le 3e octet, le numéro de carte les deux derniers. DEZ 8 / DEZ 10 sont les formes décimales imprimées sur les
  porte-clés.
- **Casi-Rusco C10106** — ce n’est pas un protocole distinct, mais une trame EM4100 (en général RF/32). Lorsque les
  données s’y prêtent, l’écran d’information ajoute une ligne `or C10106: credential card`, et Add Manually le propose
  comme format de saisie.
- **HIDProx** — conteneur HID Prox générique de 26 à 37 bits. Le Flipper essaie les agencements connus (H10304,
  H10302, S10401, H10306, Corp1000-35) et affiche le FC / numéro de carte pour chaque correspondance.
- **Paradox** — l’écran d’information affiche le CRC, et *CRC Mismatch, Invalid Card!* s’il ne concorde pas.
- **Ancien nom d’Indala26** — les très vieux fichiers portant `Key type: I40134` sont convertis en Indala26 au
  chargement.

## Voir aussi

- [Lecture](/fr/rfid/read) · [Ajout manuel](/fr/rfid/add-manually) · [Écriture](/fr/rfid/write) ·
  [Puces d’identification animale](/fr/rfid/animal-microchips) · [Format de fichier](/fr/rfid/file-format)
