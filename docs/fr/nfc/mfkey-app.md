---
title: Application MFKey
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# L'application MFKey (MFKey 4.1)

**MFKey** (par [@noproto](https://github.com/noproto)) récupère les clés MIFARE Classic **sur le Flipper lui-même**, à
partir des nonces collectés par l'application NFC : nonces de lecteur (MFKey32) et nonces de carte issus des attaques
nested. C'est l'outil à utiliser quand vous n'avez ni téléphone ni ordinateur sous la main ; il est plus lent que
[qUnleashed](/fr/nfc/qunleashed), mais il fonctionne partout, y compris dans votre poche.

| | |
|---|---|
| Emplacement | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Version dans Unleashed | **4.1** |
| Entrées | `/ext/nfc/.mfkey32.log` (nonces de lecteur), `/ext/nfc/.nested.log` (nonces de carte) |
| Sorties | `/ext/nfc/assets/mf_classic_dict_user.nfc` (clés), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (candidates SEN) |

## Utilisation

1. Collectez d'abord des nonces :
   - auprès d'un lecteur : [MFKey32](/fr/nfc/mfkey) (`Extract MFC Keys`) ;
   - depuis la carte : [attaques nested](/fr/nfc/nested-fudan) pendant `NFC → Read`.
2. Ouvrez `Main Menu → Apps → NFC → MFKey`, ou appuyez sur **Run** sur l'écran
   *« Now run Mfkey32 to extract keys »* de l'application NFC (il apparaît après `Extract MFC Keys` et après
   `Crack nonces in MFKey32`).
3. L'écran affiche **Ready**. <kbd>→</kbd> **Help** affiche
   *« Collect nonces by reading tag or reader in NFC app »*. Appuyez sur <kbd>OK</kbd> **Start**.
4. MFKey compare d'abord les nonces aux dictionnaires existants : **Dict solves: N (in progress)**,
   **Keys in dict: N**. Les nonces dont la clé est déjà connue sont ignorés.
5. L'attaque s'exécute ensuite avec trois barres de progression : **Cracking: X/Y**,
   **Round: X/Y – ETA NN Sec** et **Total ETA NNN Sec**. La ligne **RAM** en haut indique le tas disponible.
6. À la fin, un bip retentit et vous voyez **Complete**, **Keys added to user dict: N** et, pour les static encrypted
   nonces, **SEN key candidates: N**.
7. Revenez dans l'application NFC et relisez la carte (ou `Saved → <carte> → Unlock with Dictionary`).

<kbd>←</kbd> interrompt le travail et quitte (le fil d'exécution est arrêté proprement ; les clés déjà trouvées sont
tout de même écrites).

### Erreurs

| Écran | Signification |
|---|---|
| **No nonces found** | Ni `.mfkey32.log` ni `.nested.log` n'existe. Collectez d'abord des nonces. Affiché aussi pour les tags exclusivement HardNested : leurs nonces ne peuvent pas être cassés sur le Flipper. |
| **Nonces already cracked** | Tous les nonces des journaux sont déjà résolus par une clé de vos dictionnaires. |
| **No free RAM** | Mémoire insuffisante. Redémarrez le Flipper et réessayez ; fermez les autres applications. |

## Ce que MFKey 4.x a changé

D'après l'article de @gromovyna « MFKey 4.1 — plus vite, plus haut, plus fort » : cette nouvelle version majeure est
arrivée assez discrètement, et pourtant elle apporte un gain de vitesse important. Elle est disponible dans les
**builds de développement Unleashed à partir de 1251**. (Au moment de l'article, les modifications de l'application
étaient aussi intégrées au firmware officiel, mais pas les changements côté firmware dont elle a besoin.) Merci à
@noproto et à son équipe.

Ci-dessous, **SEN** = static encrypted nonce (voir [Attaques nested](/fr/nfc/nested-fudan)).

**4.0**

- Prise en charge du nouveau format de dictionnaire SEN : récupération des clés **10× plus rapide**.
- L'ancien format de dictionnaire SEN n'est plus pris en charge.

**4.1**

- Récupération des clés encore **40 % plus rapide** ; meilleure efficacité mémoire.
- Le `mfkey.c` monolithique a été découpé en modules : `mfkey_batch_prelude`, `mfkey_state_expansion`,
  `mfkey_bs_verify`, `mfkey_recovery`, `mfkey_dedup`.
- 32 candidates vérifiées en parallèle via SWAR (opérations sur les bits au lieu de contrôles un par un).
- Une « Super-LUT » précalculée de 2 Ko pour les rondes 0 à 3 : un seul chargement indexé par ronde au lieu d'un
  calcul.
- Tri par base (radix sort) en O(n) au lieu d'un tri rapide ; déduplication par hachage de Fibonacci au lieu d'un
  parcours naïf.
- Les registres de la FPU du M4 servent d'espace de travail supplémentaire (`vmov`), réduisant la pression sur les
  registres.
- Une boucle déroulée 8 fois (dispositif de Duff) lors de la recherche de doublons.

### Mesures en conditions réelles

L'auteur a testé le cas le plus difficile : un tag à **static encrypted nonces**. Pour ces tags, les clés calculées
ne sont pas vérifiées à la volée et ne vont pas directement dans le dictionnaire utilisateur ; à la place, un
dictionnaire de **candidates** est construit, qui doit ensuite être vérifié contre le tag. **Toutes** les clés
pouvant produire un nonce sont donc extraites : le plus gros dictionnaire, le scénario le plus long. Pas un seul
*Out Of Memory* pendant les tests.

| Test | Configuration | Résultat |
|---|---|---|
| Clé Iron Logic | Tag chiffré avec une carte d'objet [Iron Logic](/fr/nfc/iron-logic) ; aucune clé dans le dictionnaire, attaqué via la backdoor ; **18 clés uniques sur 32 secteurs** | Cycle complet en **6 h 8 min**, plus de **1,2 million de candidates** ; puis plusieurs heures supplémentaires pour vérifier les candidates sur le tag. |
| 1 secteur, 2 clés | Le même tag (effacé), secteur 0 chiffré avec des clés A et B aléatoires différentes | **17 minutes** ; la vérification des candidates sur un seul secteur a été rapide elle aussi. |

À titre de comparaison, la récupération du premier test sur un Proxmark3 relié à un ordinateur a pris 24 secondes :
le Flipper ne rivalisera donc jamais avec cela. Mais si vous êtes en déplacement ou que vous avez simplement du temps
pour du travail de fond, le Flipper dans votre poche peut récupérer les clés et émuler le tag. Et comme ce sont
surtout les systèmes de type Iron Logic qui adorent la diversification de clés, la probabilité de tomber sur le
scénario le plus long est relativement faible.

::: tip Unleashed
Unleashed inclut MFKey 4.1 avec les modifications côté firmware dont il a besoin (le dictionnaire CUID dans `Read`,
avec une barre de progression pendant son chargement). Après la fin de MFKey sur un tag SEN, utilisez
**Save Keys to Dictionary** sur le dump entièrement lu pour copier les clés récupérées dans votre dictionnaire
utilisateur, voir [MIFARE Classic](/fr/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Astuces

- Nettoyez `/ext/nfc/.nested.log` et `/ext/nfc/.mfkey32.log` après une récupération réussie : les anciens nonces sont
  revérifiés à chaque démarrage.
- Si vous avez installé des applications séparément, vérifiez qu'un ancien `mfkey.fap` n'a pas écrasé celui du
  firmware.
- Alternatives beaucoup plus rapides : [qUnleashed](/fr/nfc/qunleashed) sur un téléphone ou un ordinateur, ou le
  projet [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli).

## Voir aussi

[MFKey32](/fr/nfc/mfkey) · [Attaques nested](/fr/nfc/nested-fudan) · [qUnleashed](/fr/nfc/qunleashed) ·
[MIFARE Classic](/fr/nfc/mifare-classic)
