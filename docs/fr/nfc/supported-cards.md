---
title: Cartes prises en charge (analyseurs)
order: 85
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/nfc/read]
sources: [unleashed-src, unleashed-readme, flipper-docs]
---
# Cartes prises en charge (analyseurs)

Pour beaucoup de cartes, le Flipper ne se contente pas d'extraire la mémoire : il la **décode** — numéro de carte,
solde, trajets restants, validité, données de chambre d'hôtel, figurine de jeu… Cela se fait via des **plugins
d'analyse**, de petits fichiers `.fal` que l'application NFC charge depuis la carte SD après une lecture réussie.
Quand un analyseur reconnaît la carte, l'écran de résultat affiche les données décodées au lieu du résumé brut ;
**More** mène au menu habituel.

Certains analyseurs embarquent aussi les **clés** du système de la carte (ou une fonction de dérivation de clé). Pour
les cartes MIFARE Classic, cela signifie que le Flipper lit la carte **entièrement sans attaque par dictionnaire** :
l'analyseur vérifie d'abord que la carte appartient bien au système, puis la lit avec les bonnes clés.

::: tip Unleashed
Unleashed livre de nombreux analyseurs absents du firmware d'origine, notamment pour les systèmes russes et de la
CEI : Umarsh, Zolotaya Korona (et Online), Kazan, Metromoney, carte sociale de Moscou, un Troika retravaillé,
Plantain, Troika+Plantain, les billets de train de banlieue PPK, ainsi que les bobines de filament Bambu Lab, les
cartes d'arcade Banapass/Aime/AIC, les têtes de brosse Sonicare et bien d'autres (par @Leptopt1los, @assasinfil et de
nombreux contributeurs).
:::

## Liste des analyseurs

Clés intégrées = l'analyseur peut lire la carte avec ses propres clés (ou sa dérivation de clé), sans dictionnaire.

### Transport

| Carte (telle qu'affichée) | Protocole | Région | Clés intégrées | Affiche |
|---|---|---|---|---|
| Troyka card | MIFARE Classic | Moscou, Russie | oui | données de l'application transport |
| Plantain Card | MIFARE Classic | Saint-Pétersbourg, Russie | oui | données de la carte, billet de banlieue PPK |
| Troika+Plantain | MIFARE Classic | Russie | oui | les deux applications sur une même carte |
| Social card (carte sociale de Moscou) | MIFARE Classic | Moscou, Russie | oui | numéro de carte (OMC), validité |
| Kazan transport card | MIFARE Classic | Kazan, Russie | oui | type de titre, solde |
| Umarsh | MIFARE Classic | Russie (systèmes régionaux) | non (clé B nécessaire pour les secteurs 0, 8, 12) | données de la carte |
| Zolotaya korona | MIFARE Classic | Russie | non | données de la carte |
| Zolotaya korona (Online) | MIFARE Classic | Russie | non | données de carte et de tarif |
| SZPPK Accompany Card | MIFARE Classic | Russie, trains de banlieue (SZPPK) | oui | validité, gare, entrée/sortie, compteur de passages |
| SKPPK Transport Card | MIFARE Classic | Russie, trains de banlieue (SKPPK) | oui | gare, dernier passage, statut, compteur de passages |
| SevPPK Transport Card | MIFARE Classic | Russie, trains de banlieue (SevPPK) | oui | gare, dernier passage, statut, compteur de passages |
| Metromoney | MIFARE Classic | Tbilissi, Géorgie | oui | données du titre |
| CharlieCard | MIFARE Classic | Boston (MBTA), États-Unis | oui | solde, transactions |
| Clipper | MIFARE DESFire | Baie de San Francisco, États-Unis | — | numéro de série, solde, trajets (opérateur, tarif, date) |
| Ventra | MIFARE Ultralight | Chicago (CTA), États-Unis | — | trajets restants, expiration |
| Tarjeta Bip! | MIFARE Classic | Santiago, Chili | oui | numéro de carte, solde |
| SmartRider | MIFARE Classic | Perth, Australie | oui | solde, tarif réduit, numéro de série |
| Opal | MIFARE DESFire | Sydney, Australie | — | solde, dernier tap on/off |
| myki | MIFARE DESFire | Melbourne, Australie | — | numéro de carte |
| ITSO Card | MIFARE DESFire | Royaume-Uni | — | données de la carte |
| TRT Tianjin Metro | MIFARE Ultralight | Tianjin, Chine | — | solde, date de vente |
| All-In-One | MIFARE Ultralight | titre de transport | — | numéro, trajets restants |

### Accès, hôtels, paiement et services

| Carte (telle qu'affichée) | Protocole | Quoi | Clés intégrées | Affiche |
|---|---|---|---|---|
| HID Card | MIFARE Classic | identifiant HID stocké sur une carte Classic | oui | longueur en bits et valeur de l'identifiant |
| Gallagher NZ | MIFARE Classic | contrôle d'accès Gallagher (Nouvelle-Zélande) | — | identifiants (une carte peut en contenir plusieurs) |
| Saflok MFC 1K Card / Saflok UL-C Card | MIFARE Classic, Ultralight C | serrures d'hôtel Saflok | oui (KDF) | numéro d'établissement, identifiant de clé, enregistrement de clé, niveau d'accès |
| H World Card | MIFARE Classic | clés d'hôtel H World (Chine continentale) | oui | numéro de chambre, dates d'arrivée et d'expiration |
| CSC Service Works | MIFARE Classic | carte de laverie rechargeable (États-Unis) | — | solde, dernier rechargement, utilisations restantes |
| WashCity | MIFARE Classic | carte de laverie WashCity / MarkItaly (Europe) | oui | solde en EUR |
| MiZIP Card | MIFARE Classic | badges de distributeurs MiZIP | oui | UID, crédit, crédit précédent |
| Microel Card | MIFARE Classic | badges de distributeurs Microel | oui (dérivées de l'UID) | UID, crédit, crédit précédent |
| HI! Card | MIFARE Classic | carte HI! | oui | UID |
| MyKey | ST25TB | badges de distributeurs MyKey | — | numéro de série, état vierge/verrouillé, LockID |
| EMV | EMV | cartes bancaires | — | voir [Cartes bancaires (EMV)](/fr/nfc/emv) |

### Jeux, jouets et autres

| Carte (telle qu'affichée) | Protocole | Quoi | Clés intégrées |
|---|---|---|---|
| Aime Card | MIFARE Classic | carte d'arcade SEGA Aime (code d'accès) | oui |
| Banapass | MIFARE Classic | Bandai Namco Passport (code d'accès, valeur) | oui |
| Amusement IC Card | FeliCa | cartes d'arcade (SEGA Aime, Bandai Namco Passport) | — |
| Skylanders | MIFARE Classic | figurines Skylanders (nom du personnage) | oui |
| Disney Infinity | MIFARE Classic | figurines Disney Infinity | oui (dérivées) |
| Bambu Lab Filament | MIFARE Classic 1K | tags des bobines de filament Bambu Lab (type, code de filament, matériau, couleur…) | oui (dérivées) |
| Philips Sonicare head | MIFARE Ultralight | têtes de brosse à dents Sonicare | — |
| NDEF Format Data | Ultralight/NTAG, MIFARE Classic, SLIX, Type 4 Tag | messages NDEF : URI (y compris téléphone, courriel), texte, adresse MAC Bluetooth, contact, Wi-Fi, SmartPoster | — |

Le code source de chaque analyseur se trouve dans
[`applications/main/nfc/plugins/supported_cards`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc/plugins/supported_cards).
Certains analyseurs utilisent des tables de correspondance de `/ext/nfc/assets/` (par exemple `skylanders.nfc`,
`vendors.nfc`, `sk_id.nfc`, `sz_id.nfc`, `sev_id.nfc` pour les noms de gares,
`aid.nfc`/`country_code.nfc`/`currency_code.nfc` pour l'EMV).

## Remarques

- L'analyseur d'une carte « à clés intégrées » vérifie d'abord la carte ; si la vérification échoue (autres clés,
  système différent), l'attaque par dictionnaire normale se lance.
- Certains analyseurs indiquent ce qui manque, par exemple *« Unknown SKPPK Card — TICKET BLOCKS NOT READ — RUN A
  DICTIONARY ATTACK TO READ THE TICKET SECTORS »*.
- **« Plugin Not Loaded — Plugin file missing or outdated. Update the firmware resources. »** : les fichiers `.fal`
  de la carte SD ne correspondent pas au firmware. Réinstallez le firmware avec la carte SD insérée.
- Un analyseur ne fait qu'afficher des données. Modifier un solde dans un dump et l'émuler constitue une fraude dans
  les systèmes de transport et de paiement.

## Voir aussi

[Lire des cartes](/fr/nfc/read) · [Cartes bancaires (EMV)](/fr/nfc/emv) · [MIFARE Classic](/fr/nfc/mifare-classic) ·
[Cartes Moskvyonok](/fr/nfc/moskvyonok)
