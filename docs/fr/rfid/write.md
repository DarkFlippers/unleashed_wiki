---
title: Écriture sur supports vierges
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# Écrire des clés 125 kHz sur des supports vierges

Les cartes et porte-clés 125 kHz d’origine sont presque toujours en lecture seule. Pour en faire une copie physique, il
vous faut un **support vierge inscriptible** — une puce « magique » qui peut être programmée pour se comporter comme une
carte d’un autre protocole. Le Flipper Zero peut écrire sur un tel support n’importe quelle clé enregistrée, lue ou
ajoutée manuellement.

## Quels supports vierges peuvent être écrits

| Puce (telle qu’affichée à l’écran) | Noms commerciaux courants | Ce qu’elle accepte | Par défaut |
|---|---|---|---|
| **T5577** | T5577, ATA5577, cartes/porte-clés/stickers « 5577 » | tous les protocoles | ON |
| **EM4305** | supports EM4305 / EM4205 | famille EM4100, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (clone Hitag Micro, mot de passe par défaut) | famille EM4100 | ON |
| **8210** | ID8210 (même puce, mot de passe du cloneur FURUI) | famille EM4100 | ON |
| **H5.5** | iKey H5.5 (même puce, mot de passe iKey) | famille EM4100 | ON |
| **8268** | ID8268 (puce magique Hitag S) | EM4100 en RF/64 uniquement | **OFF** |

::: tip Unleashed
La documentation officielle ne parle que du T5577. La prise en charge Hitag Micro des **8265/H5, H5.5 et 8210** a été
ajoutée à Unleashed par **@gromovyna** — ces puces ne diffèrent que par leur mot de passe de login, le Flipper essaie
donc chaque mot de passe connu à tour de rôle au lieu de vous le demander. Contexte et historique :
[T5577 et Hitag Micro](/fr/rfid/t5577-hitag).
:::

::: warning Le 8268 est à activer soi-même
La cible **8268** (Hitag S) est désactivée par défaut. Contrairement aux autres routines d’écriture, elle sélectionne
n’importe quel tag Hitag S qui répond, et sur un véritable Hitag S les pages 4 et 5 contiennent des données
applicatives — le Flipper est incapable de distinguer un tag authentique d’un clone. Ne l’activez que si vous savez
qu’un support 8268 est bien sur la bobine.
:::

## Écrire une clé

1. Lisez un tag (`Read` → **More** → **Write**) ou ouvrez-en un enregistré (`Saved` → clé → **Write**).
2. Placez le support vierge contre le dos du Flipper et **ne le bougez pas**. La LED clignote en magenta.
3. L’écran affiche **Writing**, le protocole entre crochets, le nom du fichier (ou *Unsaved Tag*) et, entre
   parenthèses, la **puce actuellement tentée**, par exemple :

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Écran d’écriture avec le protocole [EM4100], le nom de la clé et la puce tentée, (T5577), entre parenthèses](/screens/lfrfid/write.png)

4. Le Flipper écrit sur chaque type de puce activé à tour de rôle et **relit le tag** après chaque tentative. Dès que
   la relecture correspond, il s’arrête.
5. En cas de réussite, vous voyez **Success!** accompagné du nom de la puce qui a réellement accepté les données (par
   exemple `T5577`, `EM4305`, `H5.5`), et l’application revient au menu de la clé.

![Écriture en cours, avec la puce en cours d’essai](/img/remote/34b72cbd8417d74e.png)

![Résultat de l’écriture, avec le nom de la puce](/img/remote/3ca59457a78dad5b.png)

::: tip Pourquoi afficher le nom de la puce ?
Avec plusieurs types de puces à essayer (et trois mots de passe pour le Hitag Micro), une écriture peut prendre
nettement plus de temps, et on ne savait pas ce qui avait été écrit. Afficher la puce tentée puis la puce retenue est le
correctif d’ergonomie apporté par @gromovyna : techniquement, il s’agit du nom commercial de la variante de support, pas
d’un protocole.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` liste toutes les cibles : **T5577**, **EM4305**, **8265**,
**8210**, **H5.5**, **8268**, chacune sur **ON** / **OFF**.

- <kbd>OK</kbd>, <kbd>←</kbd> ou <kbd>→</kbd> bascule la puce sélectionnée.
- Le choix est enregistré dans `/ext/lfrfid/.lfrfid.settings` quand vous quittez la page (<kbd>Back</kbd>).
- Désactiver les puces que vous n’utilisez jamais accélère les écritures (chaque puce activée qui ne correspond pas
  coûte une écriture + une vérification).
- La commande CLI `rfid write` respecte le même réglage.

Si la page refuse de s’ouvrir, vous voyez *Settings plugin failed to load* — mettez à jour les ressources de la carte SD
(la page est un fichier de plugin distinct). Les écritures continuent d’utiliser ce qui est stocké dans le fichier de
réglages.

## Write and set password

`Saved` → clé → **Write and set password** écrit la clé sur un **T5577** et active sa protection par mot de passe, pour
que personne ne puisse réécrire le tag sans ce mot de passe.

1. Saisissez le mot de passe de 4 octets en hexadécimal. Si aucun n’a encore été défini, le champ est prérempli avec un
   mot tiré au hasard du dictionnaire T5577.
2. Maintenez le support immobile. L’écran affiche **Writing with password**, `[Protocol]` et l’étape en cours.
3. La clé est d’abord écrite puis relue, ensuite le mot de passe est placé dans le bloc 7 et relu, et c’est seulement
   alors que le bit de mot de passe est activé dans le bloc 0. **Notez le mot de passe** — un T5577 verrouillé avec un
   mot de passe inconnu n’est plus réutilisable.

Résultats possibles :

| Écran | Signification |
|---|---|
| **Success!** | Clé écrite, mot de passe stocké et protection activée |
| **Error** — *This protocol cannot be written with a password* | Le protocole a besoin des 7 blocs de données, le bloc 7 ne peut pas accueillir de mot de passe |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | Le tag est déjà protégé |
| **Cannot read it** | Quelque chose se trouve sur la bobine mais ses blocs ne sont pas lisibles — effacez-le ou supprimez d’abord son mot de passe |
| **Not written** | Un bloc a refusé la clé ; le tag en contient une partie et aucun mot de passe |
| **Not protected** | Le mot de passe n’a pas atteint le bloc 7, ou le tag a refusé d’activer la protection |
| **Not confirmed** | Le mot de passe est bien sur le tag, mais il a été impossible de relire l’état de la protection |
| **Still trying to write...** | Aucun tag ne répond — vérifiez qu’il s’agit bien d’un T5577 inscriptible |

## Messages d’erreur d’une écriture normale

| Message | Que faire |
|---|---|
| *This protocol cannot be written* | Aucun encodage sur puce n’existe pour lui |
| *No write chips enabled. Enable one in Settings* | Toutes les cibles sont sur OFF |
| *No enabled chip can write this protocol* | Par exemple, seul EM4305 est activé pour une clé HID — activez le T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Affiché après environ 10 s ou plusieurs vérifications infructueuses. Le tag est en lecture seule, protégé par mot de passe, d’un type de puce non pris en charge, ou mal positionné. Le Flipper continue d’essayer jusqu’à ce que vous appuyiez sur <kbd>Back</kbd>. |

## Dépannage

- **Le support vierge a un mot de passe.** Beaucoup de cloneurs bon marché verrouillent les T5577. Utilisez
  l’[application T5577](/fr/rfid/t5577-app) → **Clear Password** (essaie votre mot de passe, puis le dictionnaire).
- **Un T5577 a reçu une configuration incohérente** (il ne se lit plus du tout). Utilisez l’application T5577 →
  **Wipe Tag**.
- **Le Hitag Micro (8265/8210/H5.5) exige un bon positionnement.** Son écriture est plus longue et sensible au
  placement ; le Flipper n’a que l’émission en LF, la réussite n’est donc confirmée que par la relecture du tag.
- **« Success » sur une carte en lecture seule.** Si un tag non inscriptible porte déjà le même ID, la relecture
  correspond et l’écriture est signalée comme réussie.
- **Porte-clés métalliques ou à boîtier épais.** Essayez différents emplacements ; sur les porte-clés, la bobine est
  souvent décentrée.

## Voir aussi

- [T5577 et Hitag Micro](/fr/rfid/t5577-hitag) · [Application T5577](/fr/rfid/t5577-app) ·
  [Protocoles](/fr/rfid/protocols) · [Lecture](/fr/rfid/read)
