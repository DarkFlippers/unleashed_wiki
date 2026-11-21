---
title: "MFKey32 : des clés depuis le lecteur"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32 : récupérer des clés depuis un lecteur

**MFKey32** est une attaque sur le chiffrement Crypto-1 de MIFARE Classic. Le Flipper se fait passer pour la carte ;
le lecteur tente de s'authentifier avec sa vraie clé, et les deux paires nonce/réponse qu'il envoie suffisent à
calculer cette clé hors ligne. L'attaque nécessite donc un **accès au lecteur**, et non aux clés.

Utilisez-la quand :

- la carte n'est lue que partiellement et les clés manquantes sont celles que le lecteur utilise (le cas le plus
  fréquent) ;
- vous n'avez pas de carte du tout mais vous voulez connaître les clés d'un lecteur et les ajouter à votre
  dictionnaire ;
- la carte n'a ni backdoor ni clé connue, de sorte que les [attaques nested](/fr/nfc/nested-fudan) ne peuvent pas
  démarrer.

## Avec la carte et le lecteur (recommandé)

Disposer de la carte signifie qu'après la récupération des clés du lecteur, vous pouvez lire davantage de secteurs,
ce qui correspond généralement à ce que le lecteur vérifie réellement.

1. Lisez la carte (`Main Menu → NFC → Read`). Elle finit partiellement lue.
2. Dans **More**, sélectionnez **Extract MFC Keys**. Le Flipper demande *« Save the Key? »* : choisissez **Save**
   (vous aurez besoin du dump plus tard) ou **Skip**.
   *Autre possibilité :* ouvrez une carte déjà enregistrée :
   `Main Menu → NFC → Saved → <carte> → Extract MFC Keys`.
3. L'écran affiche **« Emulating... MIFARE MFkey32 »** avec l'UID de la carte et *« Touch the reader »*.

   ![Émulation MIFARE MFkey32 avec l'UID de la carte, invitation à toucher le lecteur](/screens/nfc/mfkey_start.png)

4. Touchez le lecteur avec le dos du Flipper, éloignez-le (*« Move the Flipper away »*), touchez de nouveau
   (*« Touch the reader again »*). Le compteur **Nonce pairs: X/10** augmente à chaque tentative réussie.

   ![Collecte de paires de nonces : 4 sur 10 collectées, invitation à éloigner le Flipper](/screens/nfc/mfkey_collecting.png)

5. Quand 10 paires sont collectées, l'écran affiche **Completed!**. Vous pouvez arrêter plus tôt avec <kbd>OK</kbd>
   **Done**.
6. L'écran suivant indique **Nonce pairs saved: N** et les **Authenticated sectors** (quel secteur et quel type de
   clé le lecteur a demandés). Appuyez sur <kbd>OK</kbd>.

   ![Nonce pairs saved: 5, avec la liste des secteurs authentifiés et des types de clés](/screens/nfc/mfkey_nonces_info.png)

7. Le Flipper propose de récupérer les clés : **« Now run Mfkey32 to extract keys »** avec **Run** (ouvre
   l'[application MFKey](/fr/nfc/mfkey-app)). Si l'application est absente, un QR code vers
   `r.flipper.net/nfc-tools` s'affiche, avec **Finish**.
8. Récupérez les clés avec l'un des outils ci-dessous. Elles sont ajoutées au dictionnaire utilisateur.
9. Relisez la carte (ou `Saved → <carte> → Unlock with Dictionary`). Davantage de clés et de secteurs devraient
   maintenant être trouvés.
10. Émulez ou écrivez la carte.

Les nonces sont stockés dans `/ext/nfc/.mfkey32.log`, une ligne par paire :
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Le compteur n'augmente pas ?
Le lecteur n'essaie pas d'authentifier la carte émulée. Certains lecteurs ne vérifient que l'UID ou utilisent un autre
protocole ; d'autres rejettent l'émulation d'emblée. Essayez différentes distances et différents angles ; il faut
parfois plusieurs contacts pour obtenir une seule paire.
:::

## Avec le lecteur seul

1. Allez dans `Main Menu → NFC → Extract MFC Keys`. Le Flipper émule une carte MIFARE Classic générique.
2. Étapes 3 à 8 comme ci-dessus.
3. Les clés récupérées se trouvent dans le dictionnaire utilisateur et seront essayées automatiquement lorsque vous
   lirez plus tard des cartes de ce système.

## Récupérer les clés à partir des nonces

| Outil | Où | Remarques |
|---|---|---|
| **Application MFKey** sur le Flipper | `Main Menu → Apps → NFC → MFKey` | Aucun téléphone ni ordinateur nécessaire. Traite `.mfkey32.log` et `.nested.log`. Plus lent. Voir [Application MFKey](/fr/nfc/mfkey-app). |
| **qUnleashed** (application compagnon d'Unleashed) | `Tools → Recover MIFARE Keys` | Traite `.mfkey32.log` et `.nested.log`, y compris les nonces difficiles et les static encrypted nonces. Rapide. Voir [qUnleashed](/fr/nfc/qunleashed). |
| **Application mobile Flipper** | `Tools → Mfkey32 (Extract MF Keys)` | Application officielle, nonces de lecteur uniquement. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Via USB, dans le navigateur. |

::: tip Unleashed
Dans Unleashed, l'entrée de menu s'appelle **Extract MFC Keys** (firmware d'origine : *Extract MF Keys*), et
l'application compagnon **qUnleashed** peut récupérer les clés directement sur votre téléphone ou votre ordinateur.
Depuis **MFKey 4.x** (build de développement Unleashed 1251+), la récupération sur le Flipper lui-même est plusieurs
fois plus rapide, voir [Application MFKey](/fr/nfc/mfkey-app).
:::

## Si la récupération échoue

- **Aucune clé trouvée à partir des nonces** : le lecteur n'a pas correctement accepté l'émulation du Flipper.
  Recollectez, essayez un autre dump de carte (une vraie carte enregistrée fonctionne mieux qu'une émulation
  générique).
- **MFKey affiche « No nonces found »** : ni `.mfkey32.log` ni `.nested.log` n'existe.
- **MFKey se bloque ou plante** : redémarrez (maintenez <kbd>←</kbd> + <kbd>Back</kbd> pendant 5 secondes),
  supprimez `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log`, et recollectez.
- **En dernier recours** : sauvegardez puis supprimez `/ext/nfc/assets/mf_classic_dict_user.nfc` (cela efface
  **toutes** vos clés utilisateur).

## Voir aussi

[MIFARE Classic](/fr/nfc/mifare-classic) · [Attaques nested](/fr/nfc/nested-fudan) · [Application MFKey](/fr/nfc/mfkey-app) ·
[qUnleashed](/fr/nfc/qunleashed)
