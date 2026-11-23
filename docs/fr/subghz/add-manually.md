---
title: Add Manually
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/add_manually, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Add Manually

**Add Manually** crée une toute nouvelle télécommande virtuelle et l'enregistre dans un fichier `.sub`. Vous n'avez
pas besoin d'une télécommande d'origine pour cela : le Flipper génère un numéro de série aléatoire (ainsi qu'un
compteur, un seed, etc. là où le protocole en a besoin). La nouvelle télécommande peut ensuite être **enregistrée
dans un récepteur** comme une télécommande supplémentaire, exactement comme vous enregistreriez une télécommande de
rechange achetée en magasin.

**Add Manually [Advanced]** fait la même chose, mais vous demande de saisir chaque valeur en hexadécimal au lieu de
la générer.

::: tip Unleashed
Le firmware d'origine ne propose qu'une poignée de protocoles statiques dans Add Manually. Unleashed liste **plus de
100 systèmes**, y compris des systèmes à code tournant (constructeurs KeeLoq, FAAC SLH, BFT Mitto, Nice FloR-S /
O-Code, CAME Atomo, Somfy, Security+ 2.0, …), vous laisse choisir pour chacun n'importe laquelle des 15 bandes
fréquence/modulation, et ajoute l'entrée **[Advanced]**.
:::

## Quand l'utiliser

| Situation | À utiliser |
|---|---|
| Vous avez une télécommande **statique** (code fixe) et vous voulez simplement une copie | [Read](/fr/subghz/read) et enregistrez — Add Manually est inutile |
| Vous avez une télécommande à **code tournant** et vous voulez que le Flipper fonctionne *en plus* d'elle | **Add Manually** → enregistrez la nouvelle télécommande dans le récepteur ([comment faire](/fr/subghz/remote-prog)) |
| Vous avez besoin d'une télécommande avec des valeurs connues (seed récupéré, code installateur, numéro de série précis) | **Add Manually [Advanced]** |
| Vous avez perdu la télécommande statique d'origine mais vous connaissez ses interrupteurs DIP / son code | **Add Manually [Advanced]** avec la clé saisie à la main |

Pourquoi ne pas simplement cloner une télécommande à code tournant ? Voir
[Codes tournants](/fr/subghz/rolling-codes) : le clone et l'originale se disputent le compteur.

## Créer une télécommande

1. `Main Menu → Sub-GHz → Add Manually`.
2. Faites défiler la liste et choisissez le système, par exemple `BFT Mitto` ou `KL: DoorHan`. Les entrées commençant
   par `KL:` sont des constructeurs KeeLoq.

   ![Add Manually : liste alphabétique des systèmes avec KL: Allmatic sélectionné](/screens/subghz/add_manually.png)

3. Un **sélecteur de bande** s'ouvre, avec le nom du système en en-tête. Les bandes sont étiquetées
   `fréquence modulation`, par exemple `433.92 AM650`. La bande par défaut du système vient en premier, puis les
   autres bandes que ce système est connu pour utiliser, puis toutes les bandes restantes (pour les installations sur
   une fréquence inhabituelle). Appuyez sur <kbd>OK</kbd> sur la bande dont vous avez besoin.
4. Saisissez un nom de fichier (un nom est proposé) et validez.
5. La télécommande est enregistrée dans `/ext/subghz/` et apparaît dans `Sub-GHz → Saved`.

   ![Menu d'un signal enregistré : Emulate, Rename, Delete, Signal Settings](/screens/subghz/saved_menu.png)

6. Ouvrez-la : `Sub-GHz → Saved → <votre fichier> → Emulate`. Maintenez <kbd>OK</kbd> (`Send`) pour émettre ; sur les
   protocoles avec [boutons personnalisés](/fr/subghz/rolling-codes#custom-buttons), les flèches émettent les autres
   boutons.

   ![Écran d'émission d'un signal enregistré avec R: Int et le bouton Send](/screens/subghz/emulate.png)


Rien n'est émis avant que vous ouvriez le fichier et appuyiez sur une touche.

::: warning Noms obsolètes
Les guides plus anciens (y compris les anciennes versions de `SubGHzRemoteProg.md`) nomment des entrées du type
`BFT Mitto 433MHz` ou `KL: DoorHan 315MHz`. Le firmware actuel sépare cela en deux étapes : système (`BFT Mitto`) →
bande (`433.92 AM650`).
:::

### Les 15 bandes

Toutes sont proposées pour chaque système :

`433.92 AM650`, `433.92 FM12K`, `433.42 AM650`, `434.42 FM476`, `434.42 FM12K`, `868.35 AM650`, `868.00 AM650`,
`868.46 AM650`, `868.80 FM476`, `868.80 FM12K`, `300.00 AM650`, `310.00 AM650`, `315.00 AM650`, `390.00 AM650`,
`430.50 AM650`.

## Add Manually [Advanced]

`Main Menu → Sub-GHz → Add Manually [Advanced]` → système → bande, puis une série d'écrans de saisie hexadécimale.
Les écrans proposés dépendent de la famille de protocole :

| Famille | Écrans (dans l'ordre) |
|---|---|
| Protocoles statiques (Princeton, CAME, Nice Flo, …) | `Enter KEY in hex` ; les protocoles qui stockent un timing demandent aussi `Enter TE in us` (et `Enter GT in TE`) |
| KeeLoq (entrées `KL:`, AN-Motors AT4) | `SERIAL` → `BUTTON` → `COUNTER` |
| KeeLoq avec seed (BFT Mitto, Erreka) | `SERIAL` → `BUTTON` → `COUNTER` → `SEED` |
| `KL: FAAC FIX`, `KL: Monarch`, `KL:Phantom(Hiland)`, `KL: DEA Mio` | `SERIAL` → `BUTTON` → `COUNTER` → `DISC.` (discriminateur du hop, stocké dans le champ `Seed`) |
| FAAC SLH, Genius | `SERIAL` → `BUTTON` → `COUNTER` (32 bits) → `SEED` |
| CAME Atomo, V2 Phoenix | `SERIAL` → `COUNTER` |
| Alutech AT4N, Somfy Telis/Keytis, KingGates, Beninca ARC, Jarolift, Ditec GOL4, Prastel, BelKorn, Security+2.0 | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice FloR-S, Nice One | `SERIAL` → `BUTTON` → `COUNTER` |
| Nice O-Code, Nice O-Code One | `SERIAL` → `BUTTON` → `COUNTER` → `IC` (code installateur) |
| Nice O-Code+Crt | `SERIAL` → `BUTTON` → `COUNTER` → `IC` → `CERT` (demandé même depuis Add Manually simple) |
| Security+1.0 | rien à saisir, généré directement |

Les valeurs sont en hexadécimal gros-boutiste (big-endian). `BUTTON` et `SERIAL` forment ensemble le `Fix` que vous
voyez après un [Read](/fr/subghz/read) : sur KeeLoq, le bouton est le **premier** chiffre hexadécimal du `Fix` (le
numéro de série = le `Fix` avec ce chiffre remplacé par `0`), sur FAAC SLH / Genius c'est le **dernier** chiffre.

::: tip Saisie d'octets
La saisie d'octets d'Unleashed dispose d'un mini-éditeur de quartets : appuyez plusieurs fois sur <kbd>↑</kbd>
jusqu'à ce qu'il apparaisse.
:::

## Toutes les entrées de la liste

Ordre et étiquettes exactement comme dans le menu du firmware. « Par défaut » est la bande listée en premier ;
« Aussi » sont les bandes alternatives du système listées juste après.

| Entrée du menu | Par défaut | Aussi | Type |
|---|---|---|---|
| `KL: Allmatic` | 433.92 AM650 | 868.35 AM650 | KeeLoq (clé Beninca) |
| `Alutech AT4N` | 433.92 AM650 | | Dynamique (Alutech AT-4N) |
| `AN-Motors AT4` | 433.92 AM650 | | KeeLoq |
| `KL: Aprimatic` | 433.92 AM650 | | KeeLoq |
| `KL: ATA PTX4` | 433.92 AM650 | | KeeLoq |
| `BelKorn` | 433.92 AM650 | | Dynamique (compteur simple) |
| `KL: Beninca` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `Beninca ARC` | 433.92 AM650 | | Dynamique (AES-128) |
| `BETT` | 433.92 AM650 | | Statique |
| `BFT Mitto` | 433.92 AM650 | | KeeLoq + Seed |
| `CAME 12bit` | 433.92 AM650 | 868.35 AM650 | Statique |
| `CAME 24bit` | 433.92 AM650 | 868.35 AM650 | Statique |
| `CAME Atomo` | 433.92 AM650 | 868.35 AM650 | Dynamique |
| `KL: CAME Space` | 433.92 AM650 | | KeeLoq |
| `CAME TWEE` | 433.92 AM650 | | Statique (pseudo-dynamique) |
| `KL: Cardin S449` | **433.92 FM12K** | | KeeLoq |
| `KL: Centurion` | 433.92 AM650 | | KeeLoq |
| `KL: Clm.Mutancode` | 433.92 AM650 | | KeeLoq (Clemsa Mutancode) |
| `KL: Comunello` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `KL: DEA Mio` | 433.92 AM650 | | KeeLoq + discriminateur |
| `Ditec GOL4` | 433.92 AM650 | | Dynamique |
| `KL: DoorHan` | 433.92 AM650 | 315.00 AM650 | KeeLoq |
| `KL: Doormatic` | 433.92 AM650 | | KeeLoq |
| `KL: DTM Neo` | 433.92 AM650 | | KeeLoq |
| `KL: Elmes (PL)` | 433.92 AM650 | | KeeLoq |
| `KL: Elvox` | 433.92 AM650 | | KeeLoq |
| `Erreka` | 433.92 AM650 | 868.35 AM650 | KeeLoq + Seed |
| `KL: ET Blue` | 433.92 AM650 | | KeeLoq |
| `KL: ET Blue Mix` | 433.92 AM650 | | KeeLoq |
| `KL: FAAC FIX` | 433.92 AM650 | | KeeLoq + discriminateur |
| `KL: FAAC RC,XT` | 433.92 AM650 | 868.35 AM650 | KeeLoq |
| `FAAC SLH` | 433.92 AM650 | 868.35 AM650 | FAAC SLH + Seed |
| `FAAC TM` | 433.92 AM650 | 868.35 AM650 | Statique (12 interrupteurs DIP) |
| `KL: Fadini` | 433.92 AM650 | | KeeLoq |
| `GangQi` | 433.92 AM650 | | Statique (alarme de vélo) |
| `Gate TX` | 433.92 AM650 | | Statique |
| `Genius` | 433.92 AM650 | 868.35 AM650 | Paquet FAAC SLH, clé Genius |
| `KL: Genius TX4RC` | 433.92 AM650 | | KeeLoq (Genius Bravo/Echo RC) |
| `KL: Gibidi` | 433.92 AM650 | | KeeLoq |
| `KL: GSN` | 433.92 AM650 | | KeeLoq |
| `KL: HCS101` | 433.92 AM650 | | Type KeeLoq |
| `Hollarm` | 433.92 AM650 | | Statique (alarme de vélo) |
| `KL: HomeGate` | 433.92 AM650 | | KeeLoq |
| `KL: Hor. EcoStar` | 433.92 AM650 | | KeeLoq (Hormann EcoStar) |
| `KL: IronLogic` | 433.92 AM650 | | KeeLoq |
| `KL: IronLogic SM` | 433.92 AM650 | | KeeLoq (IL-100 Smart) |
| `Jarolift` | 433.92 AM650 | | Dynamique (basé sur KeeLoq) |
| `KL: JCM Tech` | 433.92 AM650 | | KeeLoq |
| `KL: Jolly Mot.` | 433.92 AM650 | | KeeLoq (Jolly Motors) |
| `KL: KEY` | 433.92 AM650 | | KeeLoq |
| `KingGates Stylo4k` | 433.92 AM650 | | Dynamique (basé sur KeeLoq) |
| `Linear` | **300.00 AM650** | | Statique (10 bits) |
| `Marantec` | 433.92 AM650 | 868.35 AM650 | Statique |
| `Marantec24` | **868.35 AM650** | | Statique |
| `KL: Mc Garcia` | 433.92 AM650 | | KeeLoq |
| `KL: Mhouse` | 433.92 AM650 | | KeeLoq |
| `KL: Monarch` | 433.92 AM650 | | KeeLoq + discriminateur |
| `KL: Motorline` | 433.92 AM650 | | KeeLoq |
| `Nice Flo 12bit` | 433.92 AM650 | | Statique |
| `Nice Flo 24bit` | 433.92 AM650 | | Statique |
| `Nice FloR-S` | 433.92 AM650 | | Dynamique |
| `Nice O-Code` | 433.92 AM650 | | Dynamique, code installateur |
| `Nice O-Code One` | 433.92 AM650 | | Dynamique, code installateur (paquet Nice One) |
| `Nice O-Code+Crt` | 433.92 AM650 | | Dynamique, code installateur + certificat |
| `Nice One` | 433.92 AM650 | | Dynamique |
| `KL: Nice Smilo` | 433.92 AM650 | | KeeLoq |
| `Nord ICE` | 433.92 AM650 | | Statique |
| `KL: Normstahl` | 433.92 AM650 | | KeeLoq |
| `KL: Novoferm` | 433.92 AM650 | | KeeLoq |
| `KL:Phantom(Hiland)` | 433.92 AM650 | | KeeLoq + discriminateur |
| `Prastel` | 433.92 AM650 | | Dynamique (42 bits) |
| `Princeton` | 433.92 AM650 | 315.00 AM650 | Statique (24 bits) |
| `Proteco` | 433.92 AM650 | | Statique |
| `KL: Pujol` | 433.92 AM650 | | KeeLoq |
| `KL: Pujol Vario` | 433.92 AM650 | | KeeLoq |
| `Revers RB2` | 433.92 AM650 | | Statique |
| `Roger` | 433.92 AM650 | | Statique |
| `KL: Seav` | 433.92 AM650 | | KeeLoq |
| `Security+1.0` | 433.92 AM650 | 315.00, 390.00 AM650 | Dynamique |
| `Security+2.0` | 433.92 AM650 | 310.00, 315.00, 390.00 AM650 | Dynamique |
| `Somfy Keytis` | **433.42 AM650** | | Dynamique |
| `Somfy Telis` | **433.42 AM650** | | Dynamique (Somfy RTS) |
| `KL: Sommer` | **434.42 FM12K** | 868.80 FM12K, 434.42 FM476, 868.80 FM476 | KeeLoq |
| `KL: Stilmatic` | 433.92 AM650 | | KeeLoq |
| `KL: Superrollo` | 433.92 AM650 | | KeeLoq (HCS361) |
| `Telcoma EDGE` | 433.92 AM650 | | Statique |
| `V2 Phoenix` | 433.92 AM650 | | Dynamique |
| `KL: Verex` | 433.92 AM650 | | KeeLoq |
| `KL: Wisniowski` | 433.92 AM650 | | KeeLoq |
| `ZKTeco` | **430.50 AM650** | | Statique (Princeton, voir [ZKTeco CMP200](/fr/subghz/zkteco-cmp200)) |

Pour `KL: Sommer`, les bandes FM476 génèrent la télécommande avec l'autre variante de modulation de Sommer : une
seule ligne de menu couvre donc les deux sortes de télécommandes Sommer.

## Enregistrer la nouvelle télécommande dans un récepteur

Une télécommande à code tournant fraîchement créée est inconnue du récepteur. Enregistrez-la comme n'importe quelle
télécommande de rechange — avec le bouton d'apprentissage du récepteur ou depuis une télécommande déjà
fonctionnelle. Les boutons cachés / de programmation de la télécommande d'origine sont émis avec une seule touche
fléchée sur le Flipper. Procédures pas à pas par constructeur :
**[Utiliser le Flipper comme nouvelle télécommande](/fr/subghz/remote-prog)**.

## Dépannage

- **`Function requires an SD card with fresh databases.`** — les bases de clés constructeur dans
  `/ext/subghz/assets/` sont absentes ou obsolètes. Réinstallez ou mettez à jour le firmware avec la carte SD en
  place.
- **Le récepteur ne réagit pas du tout** — mauvaise bande. Lisez d'abord votre télécommande d'origine
  (`Sub-GHz → Read`) et choisissez la même fréquence et la même modulation. DoorHan existe en 315 et 433.92 MHz ;
  FAAC, Genius, Erreka en 433.92 et 868.35.
- **Le récepteur réagit mais n'enregistre jamais la télécommande** — vous avez manqué la fenêtre d'apprentissage ou, pour
  une autre raison (par exemple des interférences), le récepteur n'a pas reçu un signal correct du Flipper.
- **La nouvelle télécommande Erreka/BFT est refusée** — certaines installations partagent un même Seed entre toutes
  les télécommandes ; récupérez-le ([Seed Capturer](/fr/subghz/seed-capturer)) et utilisez
  Add Manually [Advanced]. Voir [KeeLoq](/fr/subghz/keeloq).
- **La télécommande Nice O-Code est ignorée** — un récepteur sortant d'usine n'a pas de code installateur ;
  utilisez-y `Nice One` ou `Nice FloR-S`. Pour un système déjà installé, voir
  [Nice O-Code](/fr/subghz/nice-o-code).

::: warning
N'enregistrez des télécommandes que dans des récepteurs que vous possédez ou que vous êtes autorisé à gérer.
:::

## Voir aussi

- [Codes tournants et boutons personnalisés](/fr/subghz/rolling-codes)
- [Enregistrer une nouvelle télécommande dans un récepteur](/fr/subghz/remote-prog)
- [KeeLoq](/fr/subghz/keeloq) · [Systèmes pris en charge](/fr/subghz/supported-systems)
- [Modes de compteur](/fr/subghz/counter-mode) · [Format de fichier .sub](/fr/subghz/file-format)
