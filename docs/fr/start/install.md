---
title: Installer Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Installer Unleashed

Il existe plusieurs façons d'installer le firmware Unleashed. Toutes installent le même paquet de mise à jour, qui
contient le firmware, l'updater et l'ensemble des ressources (applications, bibliothèques IR, réglages Sub-GHz, etc.).

::: tip Avant de commencer
- **Première installation uniquement :** commencez par passer à la **dernière version officielle**
  ([Premier démarrage](/fr/start/first-start)).
- **Déjà sous Unleashed :** n'installez rien entre les deux. Installez la nouvelle version par-dessus l'actuelle.
- Vérifiez qu'une **carte microSD est insérée**. La mise à jour est décompressée sur la carte, et les applications y
  résident.
- Chargez la batterie. Une mise à jour complète prend plusieurs minutes.
:::

## Quel fichier télécharger {#which-file-to-download}

Les fichiers de release sont nommés `flipper-z-f7-update-(version)(e / c).tgz` :

| Élément | Signification |
|---|---|
| `flipper-z` | Pour l'appareil Flipper Zero |
| `f7` | Cible matérielle. Identique sur tous les Flipper Zero |
| `update` | Paquet d'auto-mise à jour : updater, firmware et toutes les ressources |
| `(version)` | Version du firmware |
| suffixe | Variante du pack d'applications, voir ci-dessous |

| Suffixe | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(aucun)* | ✅ | — |
| `c` | — | — |

- **`e`** : tout. Le pack de base plus le pack supplémentaire d'applications communautaires. À choisir en cas de doute.
- **Sans suffixe** : uniquement le pack de base d'applications communautaires.
- **`c`** (« clean ») : aucune application communautaire.

Les **applications système intégrées** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer,
Sub-GHz RAW Edit, SIM800, FindMy Flipper, télécommandes USB/BT, Snake…) sont livrées **avec le firmware lui-même** et
figurent dans **toutes** les variantes, `c` incluse. Voir
[Les apports d'Unleashed](/fr/start/unleashed-features#built-in-apps).

Autres fichiers de release :
- `flipper-z-any-scripts-(version).tgz` : le dossier `scripts` pour le développement de firmware et d'applications ;
- `flipper-z-f7-sdk-(version).zip` : le SDK pour le développement d'applications et uFBT.

## Méthode 1 : qUnleashed (recommandée)

[qUnleashed](/fr/mobile/qunleashed-app) est l'application compagnon de l'équipe Unleashed. Elle télécharge et
installe le firmware elle-même : il n'y a donc aucun fichier à choisir. Elle fonctionne sous **Android, iOS,
Windows, macOS et Linux** — en USB sur tous sauf iOS, qui se connecte en Bluetooth.

1. Installez qUnleashed pour votre système depuis sa
   [page des releases](https://github.com/DarkFlippers/qUnleashed/releases).
2. Connectez le Flipper en USB, ou appairez-le en Bluetooth (sous iOS, le Bluetooth est le seul moyen).
3. Ouvrez la **mise à jour du firmware** dans l'application.
4. Choisissez le canal **Unleashed** — **Release** ou **Dev**.
5. Choisissez la build : **de base**, **avec les applications supplémentaires** ou **compacte**
   ([ce qu'elles contiennent](#which-file-to-download)).
6. Lancez l'installation et patientez. Le Flipper redémarre dans l'updater et enchaîne toutes les étapes.

Si le Flipper ne démarre plus, la même application permet de le reflasher par USB avec
**Repair from DFU mode**. Voir [Restauration](/fr/start/recovery#firmware-recovery).

Les méthodes ci-dessous sont des alternatives. Prenez-en une si qUnleashed ne convient pas à votre configuration.

## Méthode 2 : Unleashed Web Installer

Il vous faut un **navigateur basé sur Chromium** (Chrome, Edge, Opera, Brave, Vivaldi) et un câble USB.

1. Fermez **qFlipper** et toute autre page web Flipper : elles monopolisent le port série.
2. Connectez le Flipper en USB.
3. Ouvrez **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Cliquez sur **Connect** et sélectionnez votre Flipper dans la fenêtre du navigateur.
5. Choisissez la branche **Release** ou **Dev**.
6. Cliquez sur **Install** et patientez. Le Flipper redémarre dans l'updater et enchaîne toutes les étapes.
7. C'est terminé. Toutes les ressources sont installées.

## Méthode 3 : updater web Flipper Lab

1. Ouvrez la [page de la dernière release](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Connectez le Flipper et cliquez sur le lien **Install via Web Updater**.
3. Sur la page de l'updater web, cliquez sur **Connect**, puis sur **Install**.
4. Attendez la fin de la mise à jour.

![Updater web](/img/remote/b803c9d8ec0350d6.png)

## Méthode 4 : qFlipper (1.2.0 ou plus récent)

1. Installez [qFlipper](https://flipperzero.one/update) 1.2.0+ (les versions plus anciennes ne savent pas installer de
   fichiers `.tgz`).
2. Téléchargez `flipper-z-f7-update-(version).tgz` depuis les
   [releases](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Lancez qFlipper et connectez le Flipper.
4. Cliquez sur **Install from file** et sélectionnez le `.tgz` téléchargé.
5. La mise à jour démarre. Attendez qu'elle se termine.

![qFlipper, install from file](/img/remote/f1a3ede83085d040.png)

::: warning
N'utilisez **pas** le bouton **Update** de qFlipper après avoir installé Unleashed : il installe le firmware
**officiel** par-dessus Unleashed. Passez par **Install from file**.
:::

## Méthode 5 : Flipper Mobile App

### Android, avec un fichier `.tgz`
1. Téléchargez `flipper-z-f7-update-(version).tgz` sur le téléphone.
2. Dans l'application Flipper, appuyez sur **Update channel** et sélectionnez **Custom**.
3. Sélectionnez le `.tgz` téléchargé et appuyez sur **Update**.
4. Attendez la fin de la mise à jour.

### Android, avec le lien de l'updater web
1. Sur la page de release, appuyez sur **Install via Web Updater**.
2. Lorsqu'on vous propose d'ouvrir le lien avec un navigateur ou avec l'application Flipper, choisissez la
   **Flipper App**.
3. Poursuivez l'installation et patientez.

### iOS
1. Téléchargez `flipper-z-f7-update-(version).tgz`.
2. Ouvrez-le dans l'application **Fichiers**. Appuyez sur **Partager** et choisissez la **Flipper App**.
3. Dans l'application Flipper, appuyez sur le bouton vert **Update**. Vérifiez que le canal de mise à jour affiche
   `Custom flipper-z-f7-update...`.
4. Patientez. **L'application iOS peut afficher une erreur à la fin, alors que le Flipper est bien mis à jour.**

## Méthode 6 : mise à jour hors ligne depuis la carte microSD

Aucun logiciel nécessaire sur l'ordinateur. Fonctionne depuis un PC comme depuis un téléphone.

1. Décompressez `flipper-z-f7-update-(version).tgz` (ou `.zip`). Il contient un dossier `f7-update-(version)` avec
   `update.fuf`, `resources.tar` et d'autres fichiers.
2. Mettez la carte dans un PC ou un téléphone, ou envoyez les fichiers avec qFlipper.
3. Créez un dossier `update` à la **racine** de la carte et déplacez-y `f7-update-(version)` :
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Vérifiez que **tous** les fichiers sont présents. L'application Fichiers d'iOS peut n'en afficher que 3 sur 6.
   Utilisez une autre application de décompression, un PC ou Android.
5. Remettez la carte dans le Flipper.
6. Ouvrez l'`Archive` (<kbd>↓</kbd> sur le bureau), allez dans l'onglet **Browser**, naviguez jusqu'à
   `update/f7-update-(version)/` et ouvrez `update.fuf`.
7. La mise à jour démarre. Attendez la fin de toutes les étapes.

![Mise à jour hors ligne](/img/remote/92717373349f3b7c.png)

## Après l'installation

- L'écran About (**Settings → About**) affiche le firmware Unleashed et les informations de version.
- Au premier démarrage après une mise à jour, le Flipper décompresse les ressources sur la carte. C'est normal.
- Lisez [Les apports d'Unleashed](/fr/start/unleashed-features) et configurez l'appareil dans
  [Réglages](/fr/start/settings).

## Dépannage

| Problème | Solution |
|---|---|
| Le navigateur n'arrive pas à se connecter | Fermez qFlipper et les autres onglets Flipper Lab. Utilisez un navigateur Chromium. Essayez un autre câble ou un autre port |
| La mise à jour échoue ou se bloque | Redémarrez avec <kbd>←</kbd> + <kbd>BACK</kbd>, vérifiez la carte SD, essayez une autre méthode |
| L'application mobile ne se connecte plus après l'installation | Oubliez le Flipper dans l'application et dans les réglages Bluetooth du téléphone. Puis **Settings → Bluetooth → Unpair All Devices** sur le Flipper et appairez à nouveau |
| Le rétroéclairage est éteint après l'installation | Voir la [FAQ](/fr/start/faq#backlight-does-not-work) (réglage du mod RGB) |
| L'appareil est mort / briqué | [Restauration](/fr/start/recovery) |
