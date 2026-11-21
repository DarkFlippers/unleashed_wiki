---
title: FAQ
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# FAQ

## Généralités

### Je viens d'acheter un Flipper Zero. Par où commencer ?

Lisez [Premier démarrage](/fr/start/first-start), puis [Installer Unleashed](/fr/start/install). Le site officiel
[flipperzero.one](https://flipperzero.one/) et [docs.flipper.net](https://docs.flipper.net/) couvrent les bases du
firmware d'origine.

### Firmware officiel, Unleashed ou un autre fork ?

Si vous hésitez, commencez par le firmware officiel. S'il vous faut plus de fonctions, ou du Sub-GHz sans
restrictions régionales, installez **Unleashed** : un fork du firmware officiel qui apporte de nombreuses nouveautés
et des applications préinstallées (essayez la build `e`). D'autres forks basés sur Unleashed existent pour qui veut
expérimenter davantage avec l'interface. Vous pouvez aussi faire votre propre fork.

**Avant de signaler un bug, vérifiez quel firmware vous utilisez.** Ne signalez pas dans le dépôt ou les chats
Unleashed des problèmes qui concernent d'autres forks ou le firmware d'origine.

### Où voir les différences avec le firmware officiel ?

[Ce qu'Unleashed ajoute](/fr/start/unleashed-features).

### Quelle build installer ? Que signifient `e` et `c` ?

`e` = applications de base + applications supplémentaires de la communauté, sans suffixe = applications de base,
`c` = sans applications de la communauté. Les applications système intégrées sont présentes dans toutes les builds.
Détails : [Installer Unleashed](/fr/start/install#which-file-to-download).

### Que sont les builds dev ?

Des builds automatiques des derniers commits de la branche `dev`, qui ne sont pas encore passés en release. **Elles
peuvent contenir des bugs.** Où les récupérer : dans le Web Installer (Dev), sur
[dev.unleashedflip.com](https://dev.unleashedflip.com), sur Telegram [@kotnehleb](https://t.me/kotnehleb) ou dans le
canal Discord `unleashed-development`. La build précédente est supprimée dès qu'une nouvelle est mise en ligne, et les
anciennes ne subsistent que sous forme de fichiers dans le canal Telegram. Vous avez trouvé un bug ?
[Signalez-le](https://github.com/DarkFlippers/unleashed-firmware/issues).

### Qu'est-ce que le serveur de mise à jour Unleashed ?

`https://up.unleashedflip.com/directory.json`. Il utilise le même format que le serveur officiel, mais les
applications officielles ne peuvent pas être basculées dessus sans être recompilées. Vous pouvez l'indiquer à **uFBT**
pour compiler des applications contre le SDK Unleashed. Il reste en ligne et se met à jour automatiquement.

### Quelles applications sont incluses ?

Les applications système intégrées, plus le pack de base (et le pack supplémentaire pour la build `e`) de
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).
Voir [Ce qu'Unleashed ajoute](/fr/start/unleashed-features#built-in-apps).

### Comment soutenir le projet ?

Voir la [section dédiée](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project)
du ReadMe. Un simple « merci » fait déjà plaisir. Toutes les builds sont et resteront gratuites et open source.

## Après l'installation

### Le rétroéclairage ne fonctionne plus après l'installation d'Unleashed {#backlight-does-not-work}

Vous avez activé le réglage du **mod RGB du rétroéclairage**, qui est réservé aux Flipper équipés de la modification
matérielle RGB. Ouvrez **Settings → LCD and Notifications → RGB Mod Settings** et mettez **RGB backlight installed**
sur `OFF`. Si vous avez *réellement* ce mod, activez-le au contraire à cet endroit.

### L'application mobile ne se connecte plus (après l'installation d'Unleashed ou un changement de nom)

1. Dans l'application mobile, appuyez sur **Forget Flipper**.
2. Dans les **Réglages → Bluetooth** du téléphone, trouvez le Flipper et choisissez **Oublier cet appareil**.
3. Sur le Flipper : **Settings → Bluetooth → Unpair All Devices**, puis confirmez.
4. Vérifiez que le Bluetooth est sur `ON` sur le Flipper, puis réassociez-le depuis l'application.

### Mes réglages (PIN, favoris, bureau…) ont été réinitialisés après une mise à jour

Reconfigurez-les. Un fichier de réglages n'est réinitialisé que lorsqu'une release change sa structure, ce qui n'arrive
que sur certaines releases, pas à chaque fois. Consultez les changelogs des releases sorties depuis votre version
précédente.

### Le Flipper ne se connecte pas à Chrome / au Web Installer

Le plus souvent, **qFlipper est ouvert**, ou une deuxième page Flipper Lab / page web est connectée. Un seul programme
peut occuper le port. Fermez les autres et réessayez. Utilisez un navigateur basé sur Chromium.

## Problèmes

### Le Flipper a planté, s'est figé ou ne répond plus

Maintenez <kbd>←</kbd> + <kbd>BACK</kbd> pour redémarrer. Plus de détails : [Combinaisons de touches](/fr/start/key-combos).

### Le Flipper ne fonctionne plus du tout. Comment restaurer le firmware ?

[Restauration du firmware](/fr/start/recovery#firmware-recovery).

### J'ai oublié mon PIN

Débranchez l'USB, éteignez le Flipper, maintenez <kbd>↑</kbd> + <kbd>BACK</kbd> pendant environ 5 s jusqu'à ce que
l'écran de réinitialisation apparaisse, puis maintenez <kbd>→</kbd>. Les réglages et le PIN sont réinitialisés, mais
les fichiers de la carte SD sont conservés. Détails :
[Restauration → Réinitialiser un code PIN oublié](/fr/start/recovery#reset-pin).

### Le Flipper est lent et répond mal

1. Utilisez une bonne carte microSD de marque. Le Flipper l'utilise en SPI, et toutes les cartes ne le supportent pas
   bien.
2. Dans **Settings → System**, vérifiez :
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Rechargez la batterie : un niveau de charge faible dégrade aussi les performances.

### Comment changer le nom du Flipper, ou revenir au nom d'origine ?

**Settings → Desktop → Change Flipper Name** : saisissez un nom, **Save**, quittez les réglages et le Flipper
redémarre. Enregistrez un nom vide pour revenir au nom par défaut. Voir
[Nom personnalisé du Flipper](/fr/start/custom-name).

## Sub-GHz

### Y a-t-il un blocage régional ? Comment débloquer le Sub-GHz ?

**Il n'y a aucun blocage régional dans Unleashed** : toutes les fréquences prises en charge par la puce fonctionnent
d'emblée. Il est possible d'aller **au-delà des spécifications de la puce**, mais cela peut endommager le matériel :
[Réglages dangereux](/fr/start/dangerous-settings).

### Quels protocoles sont pris en charge, et avec quelle fréquence et quelle modulation ?

[Systèmes pris en charge](/fr/subghz/supported-systems).

### Comment ajouter des fréquences supplémentaires ?

[Fréquences et presets](/fr/subghz/frequencies).

### Puis-je cloner la clé de ma voiture pour utiliser le Flipper comme clé ?

**Non.** Les clés de voiture et la plupart des télécommandes de garage utilisent des **codes tournants** (rolling
codes). Rejouer un signal capturé (par exemple depuis Read RAW) désynchronise le compteur. Dans le pire des cas, la
clé d'origine est désappariée ou mise sur liste noire, et il faut des outils d'atelier pour la réapparier.

**Pourquoi :** le récepteur mémorise la dernière valeur de compteur reçue d'une télécommande (le nombre de fois où un
bouton a été pressé). Imaginons que la télécommande d'origine ait envoyé le compteur `0002` et que vous ayez envoyé le
même signal depuis le Flipper avec `0003`. Le récepteur l'accepte. Mais la télécommande d'origine est toujours à
`0002` : son prochain appui envoie donc `0003`, que le récepteur a déjà vu, et il ne réagit pas. Ce n'est pas encore un
désappariement : appuyez quelques fois de plus sur la télécommande d'origine pour « rattraper » le Flipper (`0004`) et
elle fonctionne à nouveau. Mais si cette course se poursuit, l'écart peut atteindre **plus de 100 appuis**, et la
télécommande d'origine ne peut plus être récupérée sans être réappariée au récepteur.

**Que faire à la place :**
- n'utilisez qu'**une seule** télécommande : soit le Flipper, soit l'originale ;
- **le mieux :** créez une **nouvelle télécommande** sur le Flipper avec **Add manually** et appariez-la au récepteur
  comme une télécommande distincte ([Add manually](/fr/subghz/add-manually),
  [Programmer une nouvelle télécommande](/fr/subghz/remote-prog)) ;
- si vous devez vraiment utiliser les deux, alternez-les pour que les compteurs ne s'écartent jamais beaucoup.

Plus de détails : [Codes tournants](/fr/subghz/rolling-codes), [Mode compteur](/fr/subghz/counter-mode).

### Comment utiliser le Flipper comme nouvelle télécommande (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors…) ?

[Programmer une nouvelle télécommande](/fr/subghz/remote-prog).

### Comment utiliser l'application Sub-GHz Remote ?

1. Ouvrez l'application, appuyez sur <kbd>BACK</kbd> et sélectionnez **New map file**.
2. Choisissez un fichier de signal et un libellé pour chaque bouton. Vous pouvez laisser des boutons vides.
3. Enregistrez la map.
4. Ouvrez le fichier de map que vous venez de créer.
5. Appuyez sur les boutons pour envoyer les signaux assignés.

Détails : [Sub-GHz Remote](/fr/subghz/remote).

### Ma télécommande n'est pas prise en charge (ce n'est pas une clé de voiture). Comment l'enregistrer pour les développeurs ?

1. **Trouvez la fréquence.** **Sub-GHz → Frequency Analyzer** : maintenez le bouton de la télécommande près du Flipper
   (l'antenne se trouve près de la fenêtre IR, sur la gauche). Relâchez-le et la fréquence passe dans l'historique.
   Maintenez <kbd>OK</kbd> pour passer directement à **Read** et appuyez plusieurs fois sur la télécommande, en tenant
   chaque appui au moins 2 s. Essayez `AM650`, `FM238`, `FM476`, `FM12K`.
2. **Rien ne se décode ? Enregistrez en RAW.** Ouvrez **Read RAW**, réglez la fréquence dans la configuration et mettez
   le **RSSI Threshold** sur `----`. Faites un enregistrement pour **chaque** modulation
   (`AM650`/`FM238`/`FM476`/`FM12K`). Appuyez sur **REC**, puis appuyez 5 fois sur un bouton en le tenant 1–2 s, puis 5
   fois en le tenant environ 5 s. Enregistrez chaque bouton de la même manière et nommez chaque fichier d'après son
   bouton.
3. **Signalez-le.** Compressez les fichiers RAW dans une archive zip et ouvrez une issue dans le dépôt du firmware.
   Joignez de bonnes photos de la télécommande (à l'intérieur aussi, si possible), le modèle et le fabricant, et une
   photo de la carte du récepteur si vous pouvez.

Si la télécommande n'est pas chiffrée et qu'elle est suffisamment originale, la prise en charge pourra être ajoutée.
Pour analyser les signaux vous-même, essayez
[lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter).

### Comment connecter un module CC1101 externe ?

[CC1101 externe](/fr/subghz/external-cc1101).

## NFC et RFID

### MIFARE Ultralight

Lisez la carte, approchez le Flipper du lecteur pour capturer le mot de passe qui déverrouille les pages restantes,
puis relisez la carte : [Déverrouiller avec un mot de passe](/fr/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

Il n'existe actuellement aucune attaque pour ces cartes sur le Flipper.

### Cartes bancaires

Vous ne pouvez pas cloner de carte bancaire, le Flipper ne sait pas les émuler et il ne peut pas servir de terminal de
paiement. Il peut seulement lire les données publiques : [Cartes bancaires (EMV)](/fr/nfc/emv).

### Amiibo

Les Amiibo sont des `NTAG215`. Ils ne peuvent pas être placés sur une MIFARE Classic, et il n'est actuellement pas
possible d'écrire un Amiibo sur un nouveau tag physique.

### HID / iClass (Picopass)

- Lisez les cartes iClass avec l'application **Picopass**. L'émulation est prise en charge dans les builds Unleashed
  actuelles qui incluent les applications.
- Un Picopass 26 bits peut être rétrogradé en identifiants LF RFID H10301. Cela ne fonctionne que si le lecteur est
  configuré pour le LF. Certains lecteurs iClass sont HF uniquement.
- L'écriture des cartes en mode personnalisation est possible avec l'application.
- L'application **Seader**, associée à une carte d'extension SAM, lit des cartes HID plus sécurisées.

### Clonage RFID 125 kHz

Pour copier un tag LF, écrivez-le sur un **T5577**. Les puces que le Flipper lit sont en lecture seule, et il n'existe
pas de « vierges » de ces puces. Le T5577 est une puce multi-émulation qui peut être programmée pour se comporter comme
d'autres tags : [Écrire en RFID](/fr/rfid/write), [Application T5577](/fr/rfid/t5577-app).

### Carte ou badge inconnu

Si le NFC, le RFID et le Picopass échouent tous, photographiez le recto et le verso du badge ainsi que le lecteur. Pour
une carte, tenez-la devant une lumière vive et photographiez l'antenne. Publiez le tout dans les chats de la communauté
pour l'identifier.

## Infrarouge

### Y a-t-il une bonne méthode pour capturer les signaux IR (surtout ceux des climatiseurs) ?

Oui : [Captures IR](/fr/infrared/captures).

## Fichiers et ordinateurs

### Où trouver des fichiers (Sub-GHz, IR, NFC…) pour mon Flipper ?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) et [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) couvrent la plupart des besoins.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero) : à peu près tous les liens dont vous pourriez
  avoir besoin.

### Comment copier des fichiers de GitHub vers le Flipper ?

Téléchargez les fichiers sur un PC et copiez-les sur la carte SD (lecteur de cartes, ou gestionnaire de fichiers de
qFlipper). Il existe aussi un [guide communautaire détaillé](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf).

### Comment nettoyer les `.DS_Store` et les fichiers cachés laissés par macOS, ou trier les fichiers ?

Voir [Carte microSD → macOS](/fr/start/sd-card#macos-hidden-files-and-sorting).

### Comment ouvrir la CLI ou consulter les logs ?

Fermez d'abord qFlipper. Un seul programme peut occuper le port série.

- **Navigateur (Chromium) :** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → choisissez le
  périphérique série USB → **CLI** dans la barre latérale.
- **Windows :** trouvez le port COM dans qFlipper, fermez qFlipper, puis dans PuTTY choisissez **Serial**, saisissez le
  port COM et la vitesse `115200`, et cliquez sur **Open**. Un message « Access Denied » signifie que qFlipper tourne
  encore.
- **macOS/Linux :** trouvez le chemin du périphérique dans qFlipper (il commence par `/dev/tty`) ou avec
  `ls /dev/tty.*`, fermez qFlipper, puis lancez (en remplaçant `PATH`) :
  ```bash
  screen PATH 115200
  ```
- **Android :** l'application *Serial USB Terminal*, connectée en USB OTG.
- **iPhone :** pas de série USB. Utilisez une autre méthode.

Pour voir les logs, mettez **Settings → System → Log Level** sur `Debug` et tapez `log` dans la CLI.
<kbd>Ctrl</kbd>+<kbd>C</kbd> permet de sortir. Plus de détails : [CLI](/fr/dev/cli).

### Comment compiler le firmware moi-même ?

[Compiler le firmware](/fr/dev/build).

## Communauté

- Releases : Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Builds dev : Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord : [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Plus de liens : [Liens](/fr/community/links)
