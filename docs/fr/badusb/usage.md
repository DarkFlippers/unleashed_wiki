---
title: Utiliser le Bad USB
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Utiliser le Bad USB

Cette page détaille l'exécution d'un script via USB et via Bluetooth, et explique chaque entrée du menu **Config**.
Les libellés de menu et les messages sont reproduits exactement comme ils apparaissent dans le firmware.

::: warning Attention
N'exécutez des scripts que sur des ordinateurs qui vous appartiennent ou que vous êtes autorisé à tester. Lisez un
script avant de le lancer : il fera exactement ce qu'il contient, avec les droits de votre session.
:::

## Avant de commencer

- Une carte microSD contenant les ressources du firmware est obligatoire. Sans elle, l'application affiche
  *« No SD card or app data found. This app will not work without required files. »*
- Placez votre script (`.txt`) dans `/ext/badusb/` (les sous-dossiers sont acceptés).
- **Le mode USB monopolise le port USB du Flipper.** Si qFlipper ou la [CLI](/fr/dev/cli) est connecté en USB,
  l'application affiche *« Connection Is Active! Disconnect from PC or phone to use this function. »*
  Fermez d'abord qFlipper.

## L'écran principal

1. Ouvrez `Main Menu → Bad USB`.
2. Choisissez un script dans le navigateur de fichiers. L'écran du script s'ouvre.

La ligne du haut affiche le nom du script, en dessous la disposition de clavier entre parenthèses, `(default)` ou
par exemple `(de-DE)`, et le temps écoulé — ou, en mode BLE, le code PIN d'appairage. L'illustration centrale montre
une prise USB ou un symbole Bluetooth.

![Écran de script Bad USB : demo_windows chargé, 0/34 lignes, indications Config / Run / BLE](/screens/badusb/script_ready.png)

| État | Texte à l'écran | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Au repos / terminé / non connecté | progression ou *Connect to device* | **Run** | **Config** | bascule vers **BLE** / **USB** |
| Attente de connexion après Run | *Will run on connect* | **Cancel** | | |
| En cours d'exécution ou dans un `DELAY` | `line/total`, pourcentage, `Delay Ns` | **Stop** | | **Pause** |
| En pause | *Paused* | **End** | | **Resume** |
| Attente sur `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Erreur | *ERROR:* + `line N` + message | | | |

Si vous appuyez sur **Run** avant que l'hôte n'ait reconnu le Flipper, l'application attend
(*« Will run on connect »*) et démarre le script automatiquement **1,5 s après l'établissement de la connexion**,
pour laisser à l'hôte le temps d'installer le clavier.

Tant qu'aucun hôte n'est connecté, le sablier et *Connect to device* remplacent la progression :

![Bad USB en attente d'un hôte USB, l'écran affiche Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> quitte l'écran du script et revient au navigateur de fichiers.

## Exécuter via USB

1. Fermez qFlipper sur l'ordinateur.
2. `Main Menu → Bad USB` → sélectionnez le script.
3. Vérifiez que l'écran affiche l'illustration **USB** ; sinon, appuyez sur <kbd>→</kbd> **USB**.
4. Facultatif : <kbd>←</kbd> **Config → Keyboard Layout (global)** pour correspondre à la disposition de
   l'ordinateur (`en-US` par défaut).
5. Reliez le Flipper à l'ordinateur avec un câble USB.
6. Appuyez sur <kbd>OK</kbd> **Run**. La progression `line/total` monte jusqu'à 100 %.

![Bad USB exécutant un script : 32 %, ligne 12 sur 34, indications Stop et Pause](/screens/badusb/script_running.png)

![Bad USB en mode USB](/img/remote/d49323518c0b4b18.jpg)

## Exécuter via Bluetooth (BLE)

1. Assurez-vous que le Bluetooth est activé sur le Flipper (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → sélectionnez le script.
3. Appuyez sur <kbd>→</kbd> **BLE** ; l'illustration Bluetooth apparaît. Le Flipper commence à s'annoncer comme
   clavier.
4. Sur l'ordinateur ou le téléphone, ouvrez les réglages Bluetooth et connectez-vous à
   **`BadUSB <nom de votre Flipper>`** (le nom par défaut).
5. Confirmez l'appairage sur les deux appareils. Avec le mode d'appairage par défaut, le même code PIN s'affiche sur
   les deux écrans ; vérifiez qu'il correspond. Le PIN est aussi visible sur l'écran du script.
6. Appuyez sur <kbd>OK</kbd> **Run**.
7. Pour supprimer l'appairage par la suite : <kbd>←</kbd> **Config → Remove BLE Pairing**, puis oubliez aussi
   l'appareil côté hôte.

![Bad USB en mode BLE](/img/remote/083420027c3f836c.jpg)

::: tip Identité et appairage séparés
En mode BLE, le Flipper utilise sa **propre adresse MAC** (dérivée de celle du Flipper) et son propre stockage
d'appairage, distincts du profil Bluetooth habituel. Appairer un ordinateur avec Bad USB ne casse donc pas
l'appairage avec l'application Flipper Mobile. En quittant l'application, le profil Bluetooth normal est restauré.
:::

## Les scripts qui changent eux-mêmes de mode

Si la **première ligne** d'un script est une commande `ID` (USB) ou `BLE_ID` / `BT_ID` (Bluetooth), l'application
bascule automatiquement dans ce mode à l'ouverture du script et applique l'identité indiquée. Vous pouvez toujours
changer manuellement avec <kbd>→</kbd>. Voir
[Format des scripts → Identité du périphérique](/fr/badusb/script-format#device-id).

## Menu Config

<kbd>←</kbd> **Config** n'est accessible que lorsque le script n'est pas en cours d'exécution. Son contenu dépend du
mode de connexion actuel.

### Commun

| Entrée | Valeurs | Rôle |
|---|---|---|
| **Keyboard Layout (global)** | navigateur de fichiers | Sélectionne un fichier `.kl` dans `/ext/badusb/assets/layouts/`. S'applique à tous les scripts qui ne définissent pas la leur avec `DUCKY_LANG`. Voir [Dispositions de clavier](/fr/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Équivalent de <kbd>→</kbd> sur l'écran principal. La liste ci-dessous change en conséquence. |

### Mode BLE

| Entrée | Valeurs | Rôle |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | `ON` (défaut) : établir un lien avec l'hôte et le mémoriser, pour qu'il se reconnecte sans réappairage. `OFF` : appairer à chaque fois. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo` : appairage sans PIN. `PIN Type` : le Flipper affiche un PIN que vous saisissez sur l'hôte. `PIN Y/N` (défaut) : les deux affichent un PIN, vous confirmez qu'il correspond. |
| **Set Device Name** | texte | Nom Bluetooth (*« Set BLE device name »*). Vide = `BadUSB <nom du Flipper>`. |
| **Set MAC Address** | 6 octets | *« Set BLE MAC address »*. |
| **Randomize MAC Address** | action | Génère une adresse MAC statique aléatoire et affiche **Done**. Pratique pour apparaître comme un « nouveau » clavier. |
| **Restore BLE Defaults** | action | Efface le nom et la MAC, `Persist Pairing` sur `ON`, `Pairing Mode` sur `PIN Y/N`. |
| **Remove BLE Pairing** | action | *« Unpair the Device? »* → **Unpair** oublie tous les hôtes appairés avec Bad USB. |

### Mode USB

| Entrée | Valeurs | Rôle |
|---|---|---|
| **Set Manufacturer Name** | texte | Chaîne de fabricant USB (*« Set USB manufacturer name »*). |
| **Set Product Name** | texte | Chaîne de produit USB (*« Set USB product name »*). |
| **Set VID and PID** | 4 octets | *« Set USB VID:PID »*. Permet au Flipper de se présenter avec un identifiant vendeur/produit donné. |
| **Randomize VID and PID** | action | VID et PID aléatoires, affiche **Done**. |
| **Restore USB Defaults** | action | Efface les VID/PID et les noms : l'identité de clavier par défaut du Flipper est utilisée. |

Tout cela, ainsi que la disposition et le mode choisis, est enregistré dans `/ext/badusb/.badusb.settings`. Une ligne
`ID` / `BLE_ID` dans un script ne remplace l'identité que pour ce script.

## Dépannage

| Problème | Que faire |
|---|---|
| Le texte tapé est incohérent (`z` et `y` inversés, mauvais symboles) | La disposition de clavier de l'hôte ne correspond pas à celle de l'application. Choisissez la bonne disposition dans `Config`, ou ajoutez `DUCKY_LANG` au script. Sur un PC avec plusieurs langues de saisie, basculez l'hôte sur la langue de la disposition avant de lancer le script (par exemple l'anglais, pas le russe). |
| Des caractères manquent | L'hôte est trop lent. Ajoutez `DEFAULT_STRING_DELAY 10` (ou plus) et des `DELAY` plus longs après l'ouverture de fenêtres. |
| Le script démarre avant que la fenêtre ne soit ouverte | Augmentez le `DELAY` après `GUI r`, `ENTER` et équivalents. |
| *ERROR: line N* | La ligne contient une commande inconnue, une faute de frappe, un nombre invalide ou du texte non ASCII. Les commandes sont **sensibles à la casse** (`STRING`, pas `string`). Voir [Format des scripts](/fr/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` contient des caractères non ASCII (accents, cyrillique…). Utilisez `ALTSTRING`/`ALTCHAR` sous Windows, ou saisissez ce texte autrement. |
| *Connection Is Active!* | Déconnectez qFlipper / la CLI du port USB. |
| macOS ouvre l'*Assistant de configuration du clavier* | Utilisez une ligne `ID` avec les VID/PID d'un clavier Apple (voir l'exemple `demo_macos.txt`), ou fermez simplement l'assistant. |
| L'hôte BLE ne trouve pas le Flipper | Activez le Bluetooth sur le Flipper, restez sur l'écran du script en mode BLE, supprimez les anciens appairages des deux côtés (`Remove BLE Pairing`). |

## Voir aussi

- [Format des scripts](/fr/badusb/script-format)
- [Exemples](/fr/badusb/examples)
- [Dispositions de clavier](/fr/badusb/layouts)
