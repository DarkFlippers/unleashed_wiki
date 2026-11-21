---
title: Paramètres
order: 100
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/desktop, https://docs.flipper.net/zero/basics/settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-src, flipper-docs, unleashed-docs]
---
# Paramètres

**Main Menu → Settings** contient les entrées suivantes, dans l'ordre où elles apparaissent sur l'appareil :

**About** · **Bluetooth** · **Clock & Alarm** · **Desktop** · **Expansion Modules** · **Input** ·
**LCD and Notifications** · **Passport** · **Power** · **Storage** · **System**

Dans ce genre de listes, <kbd>↑</kbd>/<kbd>↓</kbd> déplacent la sélection, <kbd>←</kbd>/<kbd>→</kbd> changent une
valeur, et <kbd>OK</kbd> ouvre une entrée qui possède un sous-écran.

![Menu Settings : About, Bluetooth, Clock & Alarm, Desktop…](/screens/settings/menu.png)

::: tip Épingler un réglage dans les favoris
Maintenez <kbd>OK</kbd> sur n'importe quelle entrée de la liste Settings pour l'épingler dans l'onglet **Favorites**
de l'Archive (ou l'en retirer). Vous y avez alors accès rapidement depuis le bureau avec <kbd>↓</kbd>.
:::

::: info
La plupart des applications de réglages (About, Bluetooth, Clock & Alarm, Desktop, Expansion Modules, Input,
LCD and Notifications, Passport) sont des fichiers `.fap` que la mise à jour du firmware installe dans
`/ext/apps/assets/`. **Power**, **Storage** et **System** sont intégrés au firmware et fonctionnent même sans carte SD.
:::

## About

Des écrans d'information. Passez de l'un à l'autre avec **Next** (<kbd>→</kbd>) et **Prev.** (<kbd>←</kbd>) :

1. avertissement **Unleashed Firmware** : à des fins expérimentales uniquement, pas pour un usage illégal ;
2. licence : le firmware est gratuit et open source, et *"If you paid any money for it - you got scammed."* (« si vous
   avez payé pour l'obtenir, vous avez été arnaqué ») ;
3. *"Community apps included in all builds except `c` build"* et un lien vers github.com/DarkFlippers ;
4. produit, modèle, FCC ID / IC ;
5. lien de conformité et adresse du fabricant ;
6. **HW Version Info** : version du matériel, région, nom du Flipper, numéro de série ;
7. **FW Version Info** : version et date de build, hash git, version de l'API, pile radio, cible et branche.

## Bluetooth

| Entrée | Valeurs / action |
|---|---|
| **Bluetooth** | `ON` / `OFF`. Affiche `Broken` si la pile radio est endommagée ([Restauration](/fr/start/recovery)) |
| **Unpair All Devices** | Confirmez avec **Unpair**. Supprime tous les appariements, y compris les clés d'appariement du Bad USB over Bluetooth (BadKB), de Bluetooth Remote et de l'Authenticator |

Utilisez **Unpair All Devices** si l'application mobile ne se connecte plus après une installation ou un changement de
nom. Voir la [FAQ](/fr/start/faq).

## Clock & Alarm

Un seul écran avec trois lignes : **Time** (hh:mm:ss), **Date** (jj.mm.aaaa) et **Alarm** (hh:mm, `On`/`Off`).

1. Sélectionnez une ligne avec <kbd>↑</kbd>/<kbd>↓</kbd> et un champ avec <kbd>←</kbd>/<kbd>→</kbd>.
2. Appuyez sur <kbd>OK</kbd> pour passer en édition et changez la valeur avec <kbd>↑</kbd>/<kbd>↓</kbd>.
3. Appuyez sur <kbd>OK</kbd> ou <kbd>BACK</kbd> pour quitter l'édition.

Quand l'alarme sonne, <kbd>BACK</kbd> la **reporte** de 9 minutes et n'importe quelle autre touche l'arrête. Une alarme
que personne n'arrête se coupe d'elle-même au bout de 10 minutes. L'application **Clock** du menu principal affiche une
grande horloge et propose des réglages de luminosité, l'alarme et un minuteur.

## Desktop

| Entrée | Valeurs | Description |
|---|---|---|
| **PIN Setup** | → sous-menu | **Set PIN** / **Change PIN** / **Remove PIN**. Un PIN compte 4 à 10 appuis sur les flèches |
| **Auto Lock Time** | `OFF`, `10s`, `15s`, `30s`, `60s`, `90s`, `2min`, `5min`, `10min` | Verrouillage après inactivité |
| **Auto Lock disarm by active USB session** | `OFF` / `ON` | Pas de verrouillage automatique pendant une connexion USB |
| **Battery View** | `Bar`, `%`, `Inv. %`, `Retro 3`, `Retro 5`, `Bar %` | Style de l'icône de batterie |
| **Show Clock** | `OFF` / `ON` | Horloge sur le bureau |
| **Menu Style** | `Default` + styles installés | Apparence du menu principal. Les styles sont des plugins `menu_style_*` dans `/ext/apps_data/loader/plugins/`. Affiche `Missing` si le fichier du style sélectionné a été supprimé |
| **Change Flipper Name** | texte | [Nom personnalisé du Flipper](/fr/start/custom-name) |
| **Happy Mode** | Enable / Disable | Le dauphin ne se fâche jamais ([Le dauphin](/fr/start/dolphin)) |
| **Favorite App - Left Short / Left Long / Right Short / Right Long / Ok Long** | application | Applications à accès rapide depuis le bureau |
| **DummyMode - Left / Left Long / Right / Right Long / Up Long / Down / Down Long / Ok / Ok Long** | application | Applications du [Dummy Mode](/fr/start/desktop#dummy-mode) |

Pour chaque emplacement Favorite/Dummy, vous pouvez choisir **Apps Menu (Default)** ou **Passport (Default)**,
**None (disable)**, **Lock Flipper**, n'importe quelle application du menu principal, ou **[Select App]** pour
sélectionner n'importe quel `.fap` dans `/ext/apps/`.

::: warning PIN
L'écran de configuration avertit : *"Forgotten PIN can only be reset with entire device."* La réinitialisation du PIN
efface aussi vos réglages (les fichiers de la carte SD sont conservés) : voir
[Restauration](/fr/start/recovery#reset-pin).
:::

::: tip Unleashed
Change Flipper Name, Battery View, Show Clock et les 9 emplacements Dummy Mode sont des ajouts d'Unleashed.
:::

## Expansion Modules

| Entrée | Valeurs | Description |
|---|---|---|
| **Listen UART** | `USART` (broches 13, 14), `LPUART` (broches 15, 16), `None` | UART qui écoute les modules utilisant le protocole d'extension (par exemple le [Video Game Module](/fr/gpio/video-game-module)) |

Mettez-le sur `None` si vous n'utilisez pas ce type de modules. Cela économise de l'énergie et permet au Flipper de se
mettre en veille.

## Input

| Entrée | Valeurs | Description |
|---|---|---|
| **Buttons Vibro** | `OFF`, `1`…`9` | Retour vibrant lors des appuis. Plus la valeur est élevée, plus l'impulsion est longue |
| **Vibro Trigger** | `Press`, `Release`, `Both` | Moment où le retour se déclenche |

## LCD and Notifications

| Entrée | Valeurs | Description |
|---|---|---|
| **LCD Contrast** | `-10` … `+18` | Contraste de l'écran |
| **LCD Backlight** | `0%` … `100%` (pas de 5 %) | Luminosité du rétroéclairage |
| **Backlight Time** | `Always ON`, `2s`, `5s`, `10s`, `15s`, `30s`, `60s`, `90s`, `120s`, `5min`, `10min`, `30min` | Délai d'extinction du rétroéclairage |
| **Night Shift** | `OFF`, `-10%` … `-60%` | Atténue le rétroéclairage d'autant pendant la plage nocturne |
| **. Start** | `17:00` … `23:30` | Début de la plage nocturne (verrouillé quand Night Shift est sur `OFF`) |
| **. End** | `05:00` … `11:30` | Fin de la plage nocturne |
| **LED Brightness** | `0%` … `100%` | Luminosité de la LED d'état |
| **Volume** | `0%` … `100%` | Volume du haut-parleur (`Stealth` quand le son est coupé depuis le Lock Menu) |
| **Vibro** | `OFF` / `ON` | Vibration (`Stealth` quand elle est coupée) |
| **LCD Inversion** | `OFF` / `ON` | Inverse les couleurs de l'écran |
| **RGB Mod Settings** | → sous-menu | Uniquement pour les Flipper équipés du **mod matériel** de rétroéclairage RGB |

**RGB Mod Settings** (<kbd>OK</kbd> sur l'entrée) : **RGB backlight installed** (`OFF`/`ON`). Les autres entrées
restent verrouillées (`RGB MOD OFF!`) jusqu'à ce que celle-ci soit sur `ON` : **LED 1 Color**, **LED 2 Color**,
**LED 3 Color**, **Effects** (`OFF`, `Rainbow`, `Wave`), **. Speed** (`0.1s`…`1s`), **. Color step** (`1`–`3`),
**. Saturation**, **. Wave wide** (`1`–`3`).

::: danger Mod RGB
N'activez **RGB backlight installed** **que** si votre Flipper possède le
[mod matériel de rétroéclairage RGB](https://github.com/quen0n/flipperzero-firmware-rgb#readme). Sur un Flipper
d'origine, le rétroéclairage cesse de fonctionner. Si cela vous est arrivé, revenez ici et remettez le réglage sur
`OFF` (voir la [FAQ](/fr/start/faq#backlight-does-not-work)).
:::

## Passport

Le profil du dauphin : nom, humeur et niveau. S'ouvre aussi avec <kbd>→</kbd> depuis le bureau. Voir
[Le dauphin](/fr/start/dolphin).

## Power

| Entrée | Valeurs | Description |
|---|---|---|
| **Battery Info** | — | Charge, tension, courant, température, état de santé |
| **Reboot** | **Firmware Upgrade** / **Reboot Flipper** | Redémarrage en mode DFU (`Reboot to DFU Mode?`) ou redémarrage normal |
| **Power OFF** | — | Extinction |
| **Auto PowerOff** | `OFF`, `5min`, `10min`, `15min`, `30min`, `45min`, `60min`, `90min` | Extinction après inactivité |
| **Limit Charge** | `OFF`, `90%`, `85%`, `80%`, `75%`, `70%` | Arrête la charge à ce niveau |

Plus de détails : [Alimentation et batterie](/fr/start/power).

## Storage

| Entrée | Description |
|---|---|
| **About Internal Storage** | Informations sur le stockage interne (`Virtual (/.int on SD)`) et flash disponible |
| **About SD Card** | Nom de volume, type, taille, espace libre, fabricant et numéro de série de la carte |
| **Unmount SD Card** / **Mount SD Card** | Retrait sécurisé / remontage |
| **Format SD Card** | Effacer et formater la carte |
| **Benchmark SD Card** | Test de débit SPI |
| **Factory Reset** | Appuyez 5 fois sur **Erase**. Efface le stockage interne et redémarre |

Plus de détails : [Carte microSD](/fr/start/sd-card), [Restauration](/fr/start/recovery#factory-reset).

## System

| Entrée | Valeurs | Description |
|---|---|---|
| **Hand Orient** | `Righty` / `Lefty` | Mode gaucher : fait pivoter l'écran et réaffecte les boutons |
| **Units** | `Metric` / `Imperial` | Unités (par exemple °C/°F dans Battery Info) |
| **Time Format** | `24h` / `12h` | Format de l'heure |
| **Date Format** | `D/M/Y`, `M/D/Y`, `Y/M/D` | Format de la date |
| **Log Level** | `Default`, `None`, `Error`, `Warning`, `Info`, `Debug`, `Trace` | Quantité d'informations journalisées. `Default` = `Info` |
| **Log Device** | `USART`, `LPUART`, `None` | UART utilisé pour les logs (USART = broches 13/14, LPUART = broches 15/16) |
| **Log Baud Rate** | `9600` … `1843200` | Vitesse de l'UART de logs |
| **Debug** | `OFF` / `ON` | Mode débogage : fonctions de débogage supplémentaires dans les applications, onglet **Internal** de l'Archive, accès SWD |
| **Heap Trace** | `None`, `Main` | Traçage des allocations mémoire (pour les développeurs) |
| **Sleep Method** | `Default` / `Legacy` | `Legacy` consomme plus (~9 mA contre ~1,5 mA) mais peut être plus stable |
| **File Naming** | `Default` / `Detailed` | `Detailed` ajoute le type, la date et l'heure dans le nom des nouveaux fichiers |

![Settings → System : Hand Orient Righty, Units Metric, Time Format 24h, Date Format D/M/Y…](/screens/settings/system.png)

**Debug** a un raccourci : maintenez <kbd>↓</kbd> sur le bureau, puis maintenez <kbd>OK</kbd> sur l'écran
d'information ([Bureau → Écran d'informations de l'appareil](/fr/start/desktop#info-screen)).

::: warning Flipper lent ?
Pour un usage normal, gardez **Log Level** = `None` (ou `Default`), **Debug** = `OFF` et **Heap Trace** = `None`. Les
réglages de débogage ralentissent l'appareil et l'empêchent de se mettre en veille.
:::

## Pour aller plus loin

- [Bureau](/fr/start/desktop) : ce que font concrètement les réglages du bureau
- [Nom personnalisé du Flipper](/fr/start/custom-name)
- [Réglages Sub-GHz](/fr/subghz/settings) : les réglages radio au sein de l'application Sub-GHz
