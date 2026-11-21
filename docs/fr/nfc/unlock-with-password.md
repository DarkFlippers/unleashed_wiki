---
title: Déverrouillage par mot de passe
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Déverrouiller des cartes avec des mots de passe et des clés

Les cartes organisées en **pages** (MIFARE Ultralight, NTAG) peuvent protéger une partie de leur mémoire. Si `Read`
affiche **« Some Pages Are Locked! »** / **« Password-protected pages! »** et `Pages Read: X/Y` avec X < Y, la carte
a besoin d'un mot de passe ou d'une clé. Selon la carte :

| Carte | Protection | Comment le Flipper la déverrouille |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | mot de passe de 4 octets (PWD) + PACK de 2 octets | capture depuis le lecteur, génération depuis l'UID (amiibo, Xiaomi), ou saisie manuelle |
| Ultralight C | clé 3DES de 16 octets | attaque par dictionnaire (automatique) ou saisie manuelle de la clé |
| Ultralight AES | clé AES de 16 octets | attaque par dictionnaire (automatique) ou saisie manuelle de la clé, voir [Ultralight AES](/fr/nfc/ultralight-aes) |
| ICODE SLIX-L | mot de passe de 4 octets | `Extra Actions → Unlock SLIX-L` |

::: danger De mauvais mots de passe peuvent verrouiller la carte
Beaucoup de cartes comptent les authentifications échouées (`AUTHLIM`) et se verrouillent définitivement au bout d'un
certain nombre. Le Flipper avertit avec **« Risky action! Wrong password can block your card. »** avant d'essayer un
mot de passe. Ne faites pas de force brute.
:::

## Capturer le mot de passe depuis le lecteur

Si vous avez la carte et le lecteur qui l'accepte : émulez la carte, laissez le lecteur envoyer son mot de passe,
capturez-le, puis lisez la carte avec.

1. [Lisez et enregistrez](/fr/nfc/read) la carte.
2. Allez dans `Main Menu → NFC → Saved → <carte> → Unlock`.
3. Sélectionnez **Unlock With Reader**. L'écran affiche *« Touch the reader to get password... »*. Touchez le lecteur
   avec le Flipper.
4. Lorsque le mot de passe est capturé, vous voyez **Password Captured!** avec sa valeur. Appuyez sur **Continue**.
5. Présentez la carte au dos du Flipper (*« Hold card next to Flipper's back »*, puis *« Don't move »*).
6. Quand les pages sont déverrouillées (**« All Pages Are Unlocked! »**), allez dans **More → Save**, nommez la carte
   et enregistrez-la.

Si rien n'est capturé (*« Password not captured. »*), c'est que le lecteur n'utilise peut-être pas de mot de passe, ou
que la carte appartient à un autre lecteur.

`Unlock With Reader` n'est pas proposé pour les Ultralight C (elles utilisent une authentification mutuelle 3DES,
aucun mot de passe n'est envoyé en clair).

## Générer le mot de passe à partir de l'UID

Pour les figurines **toys-to-life** (NTAG215 de type amiibo) et les filtres **Xiaomi Air Purifier**, le mot de passe
est dérivé de l'UID de la carte.

1. Allez dans `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (ou, pour une carte enregistrée, `Saved → <carte> → Unlock`).
2. Sélectionnez **Auth As Ameebo** ou **Auth As Xiaomi Air Purifier**.
3. Confirmez l'avertissement et présentez la carte au Flipper.
4. Quand les pages sont déverrouillées, faites **Save** pour enregistrer la carte.

## Saisir le mot de passe manuellement

1. `Main Menu → NFC → Saved → <carte> → Unlock` (ou `Extra Actions → Unlock NTAG/Ultralight` avant la lecture).
2. Sélectionnez **Enter Password Manually**.
3. **« Enter the password in hex »** : saisissez les 4 octets, validez.
4. Confirmez l'avertissement *« Try to unlock the card with password: … »* et présentez la carte au Flipper.
5. Faites **Save** pour enregistrer la carte déverrouillée.

## Ultralight C : les clés 3DES

Les cartes Ultralight C utilisent une clé 3DES de 16 octets. Le Flipper intègre un dictionnaire de clés connues
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 clés, dont la clé d'exemple NXP `BREAKMEIFYOUCAN!`) et un
dictionnaire utilisateur (`mf_ultralight_c_dict_user.nfc`).

- Lors d'un `Read`, si la carte n'est pas entièrement lisible, l'attaque par dictionnaire se lance d'elle-même :
  en-têtes **« MFUL C User Dictionary »**, puis **« MFUL C System Dictionary »**, avec `Key found: Yes/No` et
  `Pages read: X/Y`.
- Sur une carte enregistrée incomplète : **Unlock with Dictionary** relance l'attaque ; **Unlock** demande
  **« Enter key in hex »** (16 octets) puis **« Risky Action! Unlock with key: … ? »** avec **Unlock** / **Cancel**.
- Ajoutez vos propres clés : `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Un dump Ultralight C entièrement lu propose **Write (Keep Key)** (conserve la clé 3DES de la carte cible) et
**Write (Copy Key)** (écrit aussi les pages de clé du dump) vers une carte du même type.

::: tip Unleashed
La saisie manuelle des clés 3DES/AES, la réécriture Ultralight C/AES avec Keep/Copy Key, et le dictionnaire
Ultralight AES (`Extra Actions → MIFARE UL AES Keys`) sont des fonctions d'Unleashed.
:::

## ICODE SLIX-L

1. Allez dans `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Choisissez **Enter Password Manually** (4 octets en hexadécimal) ou **Auth As TommyBox** (le mot de passe connu des
   tags TommyBox).
3. Présentez le tag au Flipper (*« Unlocking — Hold card next to Flipper's back »*).
4. Sur **SLIX Unlocked!**, appuyez sur **More** pour continuer vers le résultat de lecture et l'enregistrer, ou sur
   **Retry**.

## Si le déverrouillage a échoué

- La carte est peut-être appariée à un autre lecteur, ou utilise une clé dérivée par carte.
- Le mot de passe est correct mais certaines pages restent verrouillées : les bits de verrouillage ou les réglages
  `AUTH0`/`PROT` peuvent rendre des pages définitivement en lecture seule ou illisibles sans authentification.
- Pour Ultralight AES, voir la note sur l'ordre des octets dans [Ultralight AES](/fr/nfc/ultralight-aes).

## Voir aussi

[Lire des cartes](/fr/nfc/read) · [Ultralight AES](/fr/nfc/ultralight-aes) · [Filtres des lecteurs Vizit](/fr/nfc/vizit-filters) ·
[Format de fichier NFC](/fr/nfc/file-format)
