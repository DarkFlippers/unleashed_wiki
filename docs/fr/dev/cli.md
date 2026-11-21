---
title: Interface en ligne de commande (CLI)
order: 100
original: [https://docs.flipper.net/zero/development/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/cli, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/toolbox/cli]
sources: [flipper-docs, unleashed-src]
---
# Interface en ligne de commande (CLI)

Le Flipper expose une console texte via le port série USB. Depuis celle-ci, vous pouvez lire et émettre des signaux,
lancer des applications, gérer des fichiers, surveiller les logs, piloter le GPIO et les LED, discuter avec d'autres
Flippers en Sub-GHz et bien plus encore — pratique pour les scripts, le débogage et le développement
d'applications.

## Se connecter au CLI

::: warning Fermez d'abord qFlipper
Un seul programme à la fois peut utiliser le port série du Flipper. Quittez **qFlipper** (et fermez Flipper Lab ou
les autres terminaux) avant de vous connecter.
:::

La vitesse série est de **230400** bauds (pour l'USB CDC, la valeur est généralement ignorée, mais certains terminaux
exigent qu'elle soit définie).

### Option 1 : Flipper Lab (navigateur)

Fonctionne dans Chrome, Edge ou un autre navigateur Chromium prenant en charge Web Serial.

1. Connectez le Flipper en USB.
2. Ouvrez [lab.flipper.net](https://lab.flipper.net/) → **CLI**.

### Option 2 : terminal série web (navigateur)

1. Connectez le Flipper en USB, ouvrez un navigateur Chromium.
2. Rendez-vous sur le [terminal série web](https://googlechromelabs.github.io/serial-terminal/).
3. Réglez **Baud rate** sur **230400**, cliquez sur **Connect**, sélectionnez votre Flipper, cliquez sur
   **Connect**.

### Option 3 : terminal série — macOS

1. Trouvez le port :

   ```sh
   ls /dev/cu.*
   ```

   Le Flipper apparaît comme `/dev/cu.usbmodemflip_NAME`, où `NAME` est le nom de votre Flipper.
2. Connectez-vous avec **screen** :

   ```sh
   screen /dev/cu.usbmodemflip_NAME
   ```

   Pour quitter : <kbd>Ctrl</kbd>+<kbd>A</kbd>, puis <kbd>K</kbd>, puis <kbd>Y</kbd>.
3. …ou avec **minicom** (installez-le via [Homebrew](https://brew.sh/) : `brew install minicom`) :

   ```sh
   minicom -D /dev/cu.usbmodemflip_NAME
   ```

   Pour quitter : <kbd>Esc</kbd>+<kbd>Z</kbd>, puis <kbd>X</kbd>, puis <kbd>Return</kbd>.

### Option 3 : terminal série — Linux

1. Trouvez le port :

   ```sh
   ls /dev/serial/by-id/
   ```

   Cherchez `usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00`. Si vous n'avez qu'un seul périphérique série,
   c'est généralement aussi `/dev/ttyACM0` ; qFlipper affiche également le nom du port.
2. Connectez-vous :

   ```sh
   screen /dev/serial/by-id/usb-Flipper_Devices_Inc._Flipper_NAME_flip_NAME-if00
   # or
   minicom -D /dev/ttyACM0
   ```

   Pour quitter screen : <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>K</kbd>, <kbd>Y</kbd>. Pour quitter minicom :
   <kbd>Ctrl</kbd>+<kbd>A</kbd>, <kbd>X</kbd>, <kbd>Return</kbd>.

::: tip
Si vous obtenez « permission denied » sous Linux, ajoutez-vous au groupe `dialout` (ou `uucp` sur certaines
distributions) et reconnectez-vous.
:::

### Option 3 : terminal série — Windows

1. Installez [PuTTY](https://www.chiark.greenend.org.uk/~sgtatham/putty/latest.html).
2. Connectez le Flipper ; dans **Device Manager → Ports (COM & LPT)**, repérez son port COM (débranchez puis
   rebranchez pour voir lequel apparaît).
3. Dans PuTTY, choisissez **Connection type: Serial**, **Serial line** : par ex. `COM3`, **Speed** : `230400`,
   puis cliquez sur **Open**.

### Depuis l'arborescence du firmware

Si vous avez les sources du firmware, `./fbt cli` ouvre directement une session CLI ; avec uFBT, utilisez
`ufbt cli`.

**Résultat attendu :** une bannière ASCII du Flipper, « Welcome to Flipper Zero Command Line Interface! », la ligne
de version du firmware, et une invite `>:`.

## Commandes intégrées et externes

Lancez `help` ou `?` pour lister les commandes disponibles sur votre appareil.

::: tip Unleashed / nouvelle architecture du CLI
La plupart des commandes radio et de périphériques (`subghz`, `nfc`, `ir`, `rfid`, `ikey`, `onewire`, `bt`,
`crypto`, `js`, `gpio`, `led`, `vibro`, `buzzer`, `i2c`, `neofetch`, …) sont des **plugins CLI externes** chargés
depuis le dossier `/ext/apps_data/cli/plugins` de la carte SD (fichiers préfixés par `cli_`). Sans carte SD — ou avec
une carte endommagée — seules les commandes du cœur restent disponibles. Après avoir copié ou mis à jour des
plugins, lancez `reload_ext_cmds` au lieu de redémarrer.
:::

### Vue d'ensemble des commandes

| Commande | Description |
|---|---|
| `!` | Alias de `info device` |
| `?`, `help` | Liste les commandes disponibles |
| `bt` | Outil de test du cœur radio (BLE) — version HCI et, en mode debug, tests de porteuse et de paquets |
| `buzzer` | Joue une tonalité ou une note sur le haut-parleur piézo |
| `crypto` | Provisionnement de clés dans l'enclave sécurisée et chiffrement/déchiffrement AES |
| `date` | Affiche / règle la date et l'heure |
| `device_info` | Alias de `info device` (obsolète) |
| `echo` | Renvoie tels quels les octets reçus (sert aux tests de performance) ; s'arrête sur <kbd>Ctrl</kbd>+<kbd>C</kbd> |
| `exit` | Quitte le shell (utile dans les sous-shells comme `nfc`) |
| `factory_reset` | Réinitialise aux réglages d'usine ; les données de la carte microSD sont conservées |
| `free` | Informations sur l'allocateur du tas — profilage mémoire général |
| `free_blocks` | Blocs libres du tas et leurs tailles — pour estimer la fragmentation |
| `gpio` | Règle le mode, écrit ou lit les broches GPIO |
| `i2c` | Analyse le bus I2C à la recherche de périphériques |
| `ikey` | Lit, émule et écrit des clés iButton |
| `info` | Informations détaillées sur l'appareil et l'alimentation |
| `input` | Affiche les événements de boutons, injecte des appuis |
| `ir` | Reçoit, émet, décode des signaux infrarouges ; télécommandes universelles |
| `js` | Exécute un fichier JavaScript, la sortie console va vers le CLI |
| `led` | Pilote la LED RVB et le rétroéclairage de l'écran |
| `loader` | Liste, ouvre et ferme des applications |
| `log` | Affiche le journal système |
| `neofetch` | Informations système, comme `neofetch` sous Linux |
| `nfc` | Sous-shell NFC : dump, émulation, raw, APDU, scanner |
| `onewire` | Analyse le bus 1-Wire (broches iButton) |
| `power` | Extinction, redémarrage, redémarrage en DFU, 5 V / 3,3 V sur le GPIO |
| `reload_ext_cmds` | Recharge la liste des commandes externes depuis la carte SD |
| `rfid` | Lit, écrit, émule des cartes 125 kHz ; outils RAW |
| `sleep` | Attend une durée donnée, par ex. `sleep 5s` (utile dans les scripts) |
| `start_rpc_session` | Passe le CLI en mode RPC protobuf (utilisé par qFlipper et les applications ; normalement inutile) |
| `storage` | Commandes du système de fichiers |
| `subghz` | Outils Sub-GHz : rx/tx, RAW, décodage, chat |
| `sysctl` | Réglages système : mode debug, suivi du tas |
| `top` | Liste en direct des threads (comme le `top` de Linux) ; <kbd>Ctrl</kbd>+<kbd>C</kbd> pour quitter |
| `update` | Installe un paquet de mise à jour, sauvegarde / restaure le stockage interne |
| `uptime` | Temps écoulé depuis le dernier démarrage |
| `vibro` | Active/désactive le moteur de vibration |
| `unit_tests` | Uniquement dans le build `unit_tests` du firmware — voir [Tests unitaires](/fr/dev/unit-tests) |

## Lire les logs {#reading-logs}

1. Connectez-vous au CLI.
2. Démarrez la journalisation au niveau souhaité :

   | Commande | Affiche |
   |---|---|
   | `log` | Le niveau courant issu des réglages système |
   | `log error` | Uniquement les erreurs critiques et les messages importants |
   | `log warn` | Les avertissements et erreurs non critiques, plus `error` |
   | `log info` | Les informations non critiques, plus `warn` |
   | `log default` | Le niveau système par défaut (= `info`) |
   | `log debug` | Les informations de débogage, plus `info` (impacte les performances) |
   | `log trace` | Les traces système, plus `debug` (impacte les performances) |

   `log ?` affiche cette liste sur l'appareil.
3. Utilisez le Flipper — les messages apparaissent dans le terminal.
4. Arrêtez avec <kbd>Ctrl</kbd>+<kbd>C</kbd>.

## Discuter en Sub-GHz

Plusieurs Flippers réglés sur la même fréquence peuvent discuter via le CLI.

1. Chaque participant se connecte au CLI de son Flipper.
2. Lancez `subghz chat <frequency_in_hz> <device>`, par exemple :

   ```
   subghz chat 868150000 0
   ```

   - fréquence en Hz comprise dans 299999755–348000000, 386999938–464000000 ou 778999847–928000000 ;
   - appareil `0` = CC1101 interne, `1` = module CC1101 externe.
3. Tapez un message et appuyez sur <kbd>Enter</kbd>.
4. Quittez avec <kbd>Ctrl</kbd>+<kbd>C</kbd>.

::: tip Unleashed
Le firmware d'origine n'émet que sur les fréquences autorisées dans votre région ; Unleashed supprime les
restrictions régionales d'émission. Respectez la réglementation radio locale.
:::

## Référence des commandes

### bt

| Commande | Description |
|---|---|
| `bt hci_info` | Informations HCI du Bluetooth |
| `bt tx_carrier <channel:0-39> <power:0-6>` | *Mode debug uniquement.* Démarre le test de porteuse en émission |
| `bt rx_carrier <channel:0-39>` | *Mode debug uniquement.* Démarre le test de porteuse en réception |
| `bt tx_packet <channel:0-39> <pattern:0-5> <datarate:1-2>` | *Mode debug uniquement.* Démarre le test de paquets en émission |
| `bt rx_packet <channel:0-39> <datarate:1-2>` | *Mode debug uniquement.* Démarre le test de paquets en réception |

### buzzer

| Commande | Description |
|---|---|
| `buzzer freq <frequency_in_hz> <duration>` | Joue une tonalité |
| `buzzer note <note> <duration>` | Joue une note ; `s` signifie dièse, par ex. `cs3` = do♯3 ; les bémols ne sont pas pris en charge |

La durée accepte `ms`, `s`, `m`, `h`, par ex. `buzzer note cs3 500ms`.

### crypto

Chiffre et déchiffre avec des clés stockées dans l'enclave sécurisée du MCU.

| Commande | Description |
|---|---|
| `crypto encrypt <key_slot> <iv_hex>` | Chiffre du texte en AES256-CBC, sortie en hexadécimal |
| `crypto decrypt <key_slot> <iv_hex>` | Déchiffre de l'hexadécimal vers du texte |
| `crypto has_key <key_slot>` | Vérifie si un emplacement (1–100) contient une clé |
| `crypto store_key <key_slot> <key_type> <key_size> <key_data_hex>` | **Irréversible !** Stocke une clé — elle ne peut pas être supprimée |

- `key_slot` : les emplacements 1 à 11 sont préremplis avec les clés utilisées par le firmware.
- `iv_hex` : vecteur d'initialisation de 16 octets en hexadécimal.
- `key_type` : `master`, `simple` ou `encrypted` ; `key_size` : `128` ou `256`.

### gpio

| Commande | Description |
|---|---|
| `gpio mode <pin_name> <0/1>` | Règle la broche en entrée (0) ou en sortie (1) |
| `gpio set <pin_name> <0/1>` | Définit la valeur de la broche |
| `gpio read <pin_name>` | Lit la valeur de la broche |

Noms de broches : `PA7`, `PA6`, `PA4`, `PB3`, `PB2`, `PC3`, `PC1`, `PC0` — voir
[Brochage GPIO](/fr/gpio/pinout).

### ikey

| Commande | Description |
|---|---|
| `ikey read` | Lit une clé iButton |
| `ikey emulate <key_type> <key_data>` | Émule une clé |
| `ikey write Dallas <key_data>` | Écrit 8 octets sur un badge vierge compatible Dallas |

Types de clés et longueur des données (hexadécimal) : `Dallas` — 8 octets, `Cyfral` — 2 octets, `Metakom` —
4 octets (doit contenir une parité correcte).

### info

| Commande | Description |
|---|---|
| `info device` | Informations sur l'appareil (firmware, matériel, pile radio, …) |
| `info power` | Informations sur le système d'alimentation |
| `info power_debug` | Informations détaillées sur l'alimentation |

### input

| Commande | Description |
|---|---|
| `input dump` | Affiche les événements de boutons |
| `input send <key> <type>` | Injecte un événement ; `key` : `up`, `down`, `left`, `right`, `back`, `ok` ; `type` : `press`, `release`, `short`, `long` |

Un appui court complet se compose de trois commandes, sinon l'entrée est ignorée :

```
input send ok press
input send ok short
input send ok release
```

Pour un appui long, utilisez `long` au lieu de `short`.

### ir

| Commande | Description |
|---|---|
| `ir rx` | Reçoit et décode les signaux IR |
| `ir rx raw` | Reçoit au format RAW |
| `ir tx <protocol> <address> <command>` | Émet une commande ; adresse et commande en hexadécimal |
| `ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...` | Émet des données RAW : fréquence 10000–56000, rapport cyclique 0–100, 512 échantillons maximum |
| `ir decode <input_file> [<output_file>]` | Décode un fichier contenant des signaux RAW |
| `ir universal list <remote_name>` | Liste les signaux d'une télécommande universelle |
| `ir universal <remote_name> <signal_name>` | Émet un signal d'une télécommande universelle |

Protocoles : `NEC`, `NECext`, `NEC42`, `NEC42ext`, `Samsung32`, `RC6`, `RC5`, `RC5X`, `SIRC`, `SIRC15`, `SIRC20`,
`Kaseikyo`, `RCA`, `Pioneer`.

::: tip Unleashed
Les noms des télécommandes universelles proviennent des fichiers de `/ext/infrared/assets/`. Unleashed fournit `tv`,
`audio`, `ac`, `projectors`, `fans` et `leds` (le firmware d'origine en propose moins). Lancez
`ir universal list tv` pour voir les noms de signaux valides.
:::

### js

| Commande | Description |
|---|---|
| `js <path>` | Exécute un fichier JavaScript et affiche sa sortie console — voir [JavaScript](/fr/dev/js-about) |

### led

| Commande | Description |
|---|---|
| `led r <0-255>` / `led g <0-255>` / `led b <0-255>` | Luminosité de la composante rouge / verte / bleue de la LED |
| `led bl <0-255>` | Luminosité du rétroéclairage de l'écran (`128` ≈ 50 %) |

Pour un rouge pur : `led r 255`, `led g 0`, `led b 0`.

### loader

| Commande | Description |
|---|---|
| `loader list` | Liste les applications disponibles |
| `loader open <Application Name> [args]` | Ouvre une application par son nom, éventuellement avec des arguments |
| `loader info` | Affiche l'état du chargeur |
| `loader close` | Ferme l'application en cours |
| `loader signal <signal> [arg_hex]` | Envoie un signal avec un argument hexadécimal facultatif |

Les arguments contenant des espaces peuvent être mis entre guillemets :

```
loader open subghz "/ext/subghz/Some File.sub"
```

### nfc

`nfc` ouvre un **sous-shell**. À l'intérieur : `help` / `?` liste les commandes, `<command> -h` affiche les détails,
`exit` en sort.

| Commande | Description |
|---|---|
| `dump -f <path>` | Copie une carte physique dans un fichier `.nfc`. Options : `-k <key>`, `-p <protocol>`, `-t <timeout_ms>` |
| `emulate -f <path>` | Émule un fichier `.nfc` |
| `field` | Active le champ 13,56 MHz ; <kbd>Ctrl</kbd>+<kbd>C</kbd> pour arrêter |
| `scanner` | Liste tous les protocoles pris en charge par un tag ; `-t` affiche l'arbre des protocoles |
| `raw -p <protocol> -d <data>` | Envoie des octets bruts. Options : `-t <timeout>` (cycles de porteuse), `-k` garde le champ actif, `-c` ajoute le CRC, `-s` effectue d'abord l'activation et l'anticollision |
| `apdu -d <data> [<data2> ...]` | Envoie des APDU aux tags ISO14443-4A/4B ou ISO15693-3 ; `-p 4a`/`4b`/`15` force le protocole |
| `mfu info` | Informations de base sur un tag MIFARE Ultralight |
| `mfu rdbl -b <block>` | Lit un bloc |
| `mfu wrbl -b <block> -d <data>` | Écrit un bloc de 4 octets |

Protocoles de `dump -p` : `14_3a`, `14_3b`, `14_4a`, `14_4b`, `15` (ISO 15693-3), `felica`, `mfu`, `mfc`, `mfp`,
`des`, `slix`, `st25`, `ntag4` (NTAG 4xx), `t4t` (Type 4 Tag).
Protocoles de `raw -p` : `14a` / `iso14a`, `14b` / `iso14b`, `15`, `felica`.

### onewire

| Commande | Description |
|---|---|
| `onewire search` | Recherche les périphériques 1-Wire |

### power

| Commande | Description |
|---|---|
| `power off` | Éteint l'appareil |
| `power reboot` | Redémarre |
| `power reboot2dfu` | Redémarre en mode DFU |
| `power 5v <1/0>` | Active/désactive le 5 V sur la broche GPIO 1 |
| `power 3v3 <1/0>` | Active/désactive le 3,3 V sur la broche GPIO 9 (mode debug uniquement) |

### rfid

| Commande | Description |
|---|---|
| `rfid read [normal/indala/ask134]` | Lit une carte en mode ASK/PSK ; l'argument facultatif choisit un mode de lecture (`ask134` — puces animalières 134 kHz) |
| `rfid write <key_type> <key_data>` | Écrit sur un T5577 |
| `rfid emulate <key_type> <key_data>` | Émule |
| `rfid raw_read <ask/ask134/psk> <filename>` | Enregistre le signal brut dans un fichier |
| `rfid raw_emulate <filename>` | Émule un fichier brut (débogage de protocole) |
| `rfid raw_analyze <filename>` | Affiche un fichier brut et tente de le décoder (développement de protocole) |

Types de clés et longueur des données (octets en hexadécimal) :

| Type | Octets | Type | Octets | Type | Octets |
|---|---|---|---|---|---|
| EM4100 | 5 | IoProxXSF | 4 | Paradox | 6 |
| EM4100/32 | 5 | AWID | 9 | PAC/Stanley | 4 |
| EM4100/16 | 5 | FDX-A | 5 | Keri | 4 |
| Electra | 8 | FDX-B | 11 | Gallagher | 8 |
| H10301 | 3 | HIDProx | 6 | Nexwatch | 8 |
| Idteck | 8 | HIDExt | 12 | Radio Key | 6 |
| Indala26 | 4 | Pyramid | 4 | GProxII | 12 |
| Viking | 4 | Jablotron | 5 | Noralsy | 12 |

### storage

Les chemins commencent par `/int` (flash interne) ou `/ext` (carte SD).

| Commande | Description |
|---|---|
| `storage info /ext` | Informations sur le système de fichiers et espace libre |
| `storage format /ext` | Formate la carte SD (demande confirmation) |
| `storage list <path>` | Liste un répertoire |
| `storage tree <path>` | Liste récursivement |
| `storage remove <path>` | Supprime un fichier ou un répertoire **vide** |
| `storage read <file>` | Affiche la taille et le contenu texte |
| `storage read_chunks <file> <1-512>` | Affiche le contenu par blocs de la taille indiquée |
| `storage write <file>` | Ajoute le texte saisi dans le CLI ; <kbd>Ctrl</kbd>+<kbd>C</kbd> pour terminer |
| `storage write_chunk <file> <1-512>` | Ajoute exactement N octets depuis le CLI (la saisie n'est pas renvoyée en écho) |
| `storage copy <src> <dst>` | Copie un fichier |
| `storage rename <old> <new>` | Renomme / déplace |
| `storage mkdir <path>` | Crée un répertoire |
| `storage md5 <file>` | Empreinte MD5 |
| `storage stat <path>` | Informations sur un fichier ou un répertoire |
| `storage timestamp <file>` | Date de dernière modification |
| `storage extract <archive.tar> <dir>` | Extrait une archive `.tar` |

### subghz

| Commande | Description |
|---|---|
| `subghz chat <frequency> <device>` | Discute avec d'autres Flippers |
| `subghz tx <3-byte_key_hex> <frequency> <te_us> <repeat> <device>` | Émet une clé (Princeton) |
| `subghz rx <frequency> <device>` | Reçoit et décode |
| `subghz rx_raw <frequency>` | Reçoit en RAW |
| `subghz decode_raw <path_to_raw_file>` | Décode un fichier RAW `.sub` et affiche les résultats |
| `subghz tx_from_file <path> <repeat> <device>` | Émet un fichier `.sub` enregistré |

Mode debug uniquement :

| Commande | Description |
|---|---|
| `subghz tx_carrier <frequency>` | Émet une porteuse non modulée |
| `subghz rx_carrier <frequency>` | Reçoit la porteuse (RSSI) |
| `subghz encrypt_keeloq <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Chiffre un fichier de clés constructeur KeeLoq |
| `subghz encrypt_raw <decrypted_file> <encrypted_file> <iv_16_bytes_hex>` | Chiffre des données RAW |

`device` : `0` — CC1101 interne, `1` — CC1101 externe ([module externe](/fr/subghz/external-cc1101)).
`te_us` — la durée d'impulsion de base en µs.

Exemple — émettre un fichier enregistré 3 fois via la radio interne :

```
subghz tx_from_file /ext/subghz/gate.sub 3 0
```

### sysctl

| Commande | Description |
|---|---|
| `sysctl debug <0/1>` | Désactive / active le mode debug du système |
| `sysctl heap_track <none/main>` | Suivi des allocations du tas pour le thread principal de l'application ; les builds de débogage (`DEBUG=1`) acceptent aussi `tree` (thread principal + threads enfants) et `all` |

### update

| Commande | Description |
|---|---|
| `update install /ext/path/to/update.fuf` | Vérifie et installe un paquet de mise à jour (le manifeste `.fuf` situé dans le dossier du paquet décompressé) |
| `update backup /ext/backup.tar` | Sauvegarde le stockage interne |
| `update restore /ext/backup.tar` | Restaure le stockage interne depuis une sauvegarde |

Voir [Mises à jour OTA](/fr/dev/ota).

### vibro

| Commande | Description |
|---|---|
| `vibro <1/0>` | Active / désactive le moteur de vibration |

## Pages liées

- [Déboguer les applications](/fr/dev/debugging)
- [Mises à jour OTA](/fr/dev/ota)
- [Tests unitaires](/fr/dev/unit-tests)
- [qFlipper](/fr/mobile/qflipper)

MIFARE, MIFARE Ultralight, MIFARE Classic, DESFire et ICODE sont des marques déposées de NXP B.V. FeliCa est une
marque de Sony Corporation.
