---
title: Puces d’identification animale
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Puces d’identification animale (FDX-B, FDX-A)

Les puces pour animaux de compagnie sont des transpondeurs RFID de la taille d’un grain de riz, implantés sous la peau.
Alimentés par un lecteur, ils émettent un ID que l’on peut rechercher dans les bases de données d’identification. Le
Flipper Zero lit les deux types LF courants :

| Type | Nom dans le Flipper | Description |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, ID à 15 chiffres ; le type le plus répandu ; certaines puces indiquent aussi la température corporelle |
| **FDX-A** | `FDX-A` (FECAVA) | Puces plus anciennes à 10 chiffres, non ISO |

La plupart des puces animales fonctionnent à **134,2 kHz**, alors que l’antenne du Flipper est accordée sur 125 kHz : la
distance de lecture est donc courte — environ **1 cm**. Les puces de la plage 110–140 kHz peuvent être lues, mais de
plus près encore.

::: tip Unleashed
La documentation officielle vous dit d’utiliser *Read ASK*. Unleashed génère un véritable champ à **134,2 kHz** pour ces
puces :
- **Read** effectue désormais une troisième passe, **134kHz**, après ASK et PSK ;
- `Extra Actions → Read FDX-B (Animals)` reste sur 134,2 kHz en permanence — le meilleur choix pour les puces faibles ;
- le nom du pays, pour le FDX-B, est recherché dans `/ext/lfrfid/assets/iso3166.lfrfid`.
:::

## Lire la puce d’un animal

1. Allez dans `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. L’écran affiche *Reading FDX-B*.
2. Localisez la puce :
   - chiens et chats : en général sous la peau **entre les omoplates** ; en Europe continentale, souvent **à
     mi-hauteur sur le côté gauche du cou**. Les puces peuvent migrer un peu ;
   - palpez doucement du bout des doigts pour repérer un petit corps dur en forme de grain de riz, puis placez le
     centre du dos du Flipper juste au-dessus.
3. Maintenez le Flipper immobile environ **3 secondes** à chaque emplacement. Si rien ne vient, déplacez-le par petits
   pas sur la zone, puis faites-le pivoter de 90° et recommencez.
4. Surveillez la LED : jaune/vert signifie qu’un signal est capté — restez là.
5. Une fois le décodage obtenu, l’écran de résultat apparaît. <kbd>→</kbd> **More → Save** pour le conserver.

## Ce que le Flipper affiche pour le FDX-B

| Champ | Signification |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | Code pays à 3 chiffres (ISO 3166-1 numérique) ou code fabricant + ID national à 12 chiffres — le numéro à 15 chiffres à rechercher |
| Country Code / Country | Le code et son nom, d’après la table ISO 3166 |
| Temperature | Pour les puces thermiques, en °C et °F ; `---` si absente |
| Animal | Indicateur d’application animale |
| Visual Start Digit, Replacement Number, User Info, RFU | Champs d’en-tête de la trame ISO |
| Data Block | Present / Absent — bloc de données supplémentaire (la température, par exemple) |
| RUDI Bit | Yes / No |

Le FDX-A affiche un `ID` de 10 chiffres hexadécimaux et un champ `Parity`.

::: warning
La température mesurée par la puce ne remplace pas un vrai thermomètre.
:::

## Rechercher l’ID

Saisissez l’ID à 15 chiffres dans une base de données d’identification animale, par exemple :
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — États-Unis et Canada
- [Europetnet](https://www.europetnet.com/) — Europe
- [PETMAXX](http://www.petmaxx.com/) — monde entier

Ou adressez-vous à votre vétérinaire / au fichier national d’identification.

## Si la puce n’est pas trouvée

- Hors de portée — avancez par pas plus petits et restez plus longtemps à chaque point.
- La puce a migré — balayez une zone plus large.
- Du métal ou de l’électronique à proximité — éloignez-vous-en.
- L’animal porte peut-être une puce 13,56 MHz — essayez le [NFC](/fr/nfc/read).
- Puce non prise en charge — demandez à un vétérinaire de la lire.

Les clés FDX-B peuvent également être [émulées ou écrites](/fr/rfid/write) (supports T5577 et EM4305, qui existent
aussi en version tag de verre), par exemple pour tester une chatière électronique.

## Voir aussi

- [Lecture](/fr/rfid/read) · [Protocoles](/fr/rfid/protocols) · [Écriture](/fr/rfid/write)
