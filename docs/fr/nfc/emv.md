---
title: Cartes bancaires (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Cartes bancaires (EMV)

Les cartes bancaires sans contact et les portefeuilles sur téléphone utilisent **EMV** au-dessus d'ISO14443-4. Le
Flipper peut lire les informations **publiques** qu'une carte fournit à n'importe quel terminal et les afficher sous
une forme lisible. Il ne peut pas lire les clés secrètes et **ne peut ni émuler ni cloner** une carte bancaire :
chaque paiement est signé par une clé qui ne quitte jamais la puce.

::: tip Unleashed
Le protocole EMV et l'analyseur de données publiques viennent d'Unleashed (par @Leptopt1los et @wosk).
:::

## Lire une carte bancaire

1. `Main Menu → NFC → Read`, présentez la carte (ou un téléphone déverrouillé avec le portefeuille ouvert) au dos du
   Flipper.
2. Le résultat analysé montre ce que la carte a divulgué, par exemple :
   - le libellé ou le nom de l'application (p. ex. le réseau de paiement), ou simplement `EMV` ;
   - le numéro de carte (PAN), groupé par 4 chiffres ;
   - `Cardholder name:` (la plupart des cartes modernes ne l'émettent plus) ;
   - les dates `Effective:` / `Expires:` (au format de date de votre locale) ;
   - `Country:` et `Currency:` d'émission ;
   - `PIN attempts left:` ;
   - `Mobile: yes` pour les portefeuilles sur téléphone ou montre ;
   - *« No data was parsed »* si rien d'exploitable n'est revenu.
3. <kbd>→</kbd> **More** ouvre le menu : **Save**, **Transactions** (uniquement si la carte a renvoyé un journal de
   transactions), **Info**.

L'écran **Info** affiche la vue technique : UID, `AID`, `Interchange profile`, `Currency code`, `Country code`,
`Transactions count` et `Last Online ATC` lorsqu'ils sont disponibles.

## Transactions

Certaines cartes conservent un court journal des transactions récentes et le délivrent sans code PIN.
`More → Transactions` liste chaque entrée avec son compteur (ATC), le montant, la devise, le pays et la date/heure
lorsqu'ils sont présents (`???` / `UNK` pour les valeurs inconnues).

## Noms des pays, des devises et des applications

L'analyseur EMV traduit les codes à l'aide de fichiers de correspondance sur la carte SD :

- `/ext/nfc/assets/aid.nfc` : identifiants d'applications → noms ;
- `/ext/nfc/assets/country_code.nfc` : codes pays ISO ;
- `/ext/nfc/assets/currency_code.nfc` : codes devises ISO.

Chaque fichier comporte l'en-tête `Filetype: Flipper EMV resources`, `Version: 1`, puis des lignes
`<code>: <nom>`, par exemple `0985: PLN`. Voir [le format de fichier](/fr/nfc/file-format#emv-resources).

## Ce qui ne fonctionne pas, et pourquoi

- **Émulation / paiements** : impossible. La carte calcule un cryptogramme pour chaque transaction avec ses clés
  privées.
- **Numéro de carte absent** : certaines cartes et la plupart des portefeuilles sur téléphone fournissent un numéro
  tokenisé, ou rien du tout sans dialogue avec un terminal.
- **Cartes hybrides** (carte bancaire + puce de transport/accès) : utilisez
  `Extra Actions → Read Specific Card Type` pour lire l'autre partie.

::: warning Confidentialité
Un dump EMV enregistré peut contenir votre numéro de carte et sa date d'expiration. Ne le partagez pas.
:::

## Voir aussi

[Lire des cartes](/fr/nfc/read) · [Cartes prises en charge](/fr/nfc/supported-cards) · [Format de fichier NFC](/fr/nfc/file-format)
