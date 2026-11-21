---
title: MIFARE Ultralight AES
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_QA.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/MifareUltralightAES_SecureMessaging_QA.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_ultralight]
sources: [unleashed-docs, unleashed-src]
---
# MIFARE Ultralight AES (MF0AES20)

**MIFARE Ultralight AES** est une Ultralight dotée d'une authentification mutuelle **AES-128** au lieu d'un mot de
passe (NTAG21x) ou de 3DES (Ultralight C). Elle possède 60 pages, trois compteurs unidirectionnels, une signature
d'authenticité ECC de 48 octets, un mode **Random ID** optionnel et une **messagerie sécurisée** optionnelle (chaque
commande et chaque réponse protégées par un CMAC).

::: tip Unleashed
La prise en charge d'Ultralight AES (lecture, attaque par dictionnaire, saisie manuelle de clé, émulation,
réécriture, décodage de la configuration, Random ID, messagerie sécurisée) est une fonction d'Unleashed, validée sur
une véritable carte MF0AES20 par comparaison avec les résultats de référence d'un Proxmark3.
:::

## Ce que le Flipper en fait

| Fonction | Détails |
|---|---|
| Identification et lecture | Détectée comme `Mifare Ultralight AES`, ATQA `0044`, SAK `00`, `60/60` pages sur une carte ouverte, compteurs. |
| Signature d'authenticité | Enregistrée dans le fichier `.nfc` sous forme d'une ligne `AES signature:` (48 octets) et rejouée pendant l'émulation, de sorte que la vérification de signature d'un lecteur réussisse. |
| Authentification AES | Défi-réponse AES en 3 passes, puis lecture des pages protégées. |
| Attaque par dictionnaire | Se lance automatiquement sur une lecture incomplète : **MFUL AES User Dictionary**, puis **MFUL AES System Dictionary**. |
| Clé manuelle | `Saved → <carte> → Unlock` → **« Enter key in hex »** (16 octets) → confirmer avec **Unlock**. |
| Gestion des clés | `NFC → Extra Actions → MIFARE UL AES Keys` → **Add** / **List**. |
| Réécriture | **Write (Keep Key)** / **Write (Copy Key)** sur un dump entièrement lu. |
| Émulation | Complète, y compris l'authentification AES côté carte, la barrière AUTH0 et la messagerie sécurisée. |
| Décodage de la configuration | `Info` affiche un bloc **UL-AES Config** (voir plus bas). |
| Random ID | Détecté et affiché (`Random ID: on`) ; **Reveal Real UID** tente de récupérer le véritable UID. |

Dictionnaires : système `/ext/nfc/assets/mf_ultralight_aes_dict.nfc` (clé d'usine tout à zéro, `BREAKMEIFYOUCAN!`
réutilisé en AES, et d'autres valeurs par défaut courantes issues de Proxmark3), utilisateur
`/ext/nfc/assets/mf_ultralight_aes_dict_user.nfc`. Une carte d'usine utilise la clé tout à zéro
`00000000000000000000000000000000` à la fois pour la DataProtKey et pour l'UIDRetrKey.

## Lire une carte protégée

1. `Main Menu → NFC → Read`, présentez la carte.
2. Les pages ouvertes sont lues ; si la carte possède une zone protégée par AES, l'attaque par dictionnaire démarre
   d'elle-même (dictionnaire utilisateur d'abord, puis système).
3. Si une clé fonctionne, toutes les pages sont lues et la clé est affichée et enregistrée avec le dump. Sinon, vous
   obtenez une lecture partielle (par exemple `42/60` pages) et **« AES-protected pages! »**, sans blocage ni
   consommation de tentatives sur une carte sans limite.
4. Enregistrez la carte. Vous pourrez réessayer plus tard avec **Unlock with Dictionary** (après avoir ajouté des
   clés) ou **Unlock** (clé manuelle).

::: warning Ordre des octets de la clé
Les écritures de pages brutes (p. ex. `hf mfu wrbl` sur Proxmark3) stockent la clé dans l'**ordre de la mémoire du
tag** ; le moteur AES, la saisie manuelle du Flipper et `hf mfu aesauth --key` sur PM3 utilisent l'ordre **inverse**.
Une carte dont les pages `0x30–0x33` se lisent `A0A1A2A3 A4A5A6A7 A8A9AAAB ACADAEAF` s'authentifie avec
`AFAEADACABAAA9A8A7A6A5A4A3A2A1A0`. Saisissez une clé récupérée manuellement **dans l'ordre AES**. Dans le `.nfc`
enregistré, les pages de clé (`Page 48`–`51`) sont stockées dans l'ordre de la mémoire du tag afin de pouvoir être
réécrites à l'identique ; la ligne `DataProtKey:` affichée à l'écran n'est qu'une représentation.
:::

## Mémoire et configuration

| Élément | Emplacement |
|---|---|
| DataProtKey | pages `0x30`–`0x33` |
| UIDRetrKey | pages `0x34`–`0x37` |
| CFG | page `0x29` : octet 0 bit0 = `RID_ACT`, bit1 = `SEC_MSG_ACT` ; octet 3 = `AUTH0` |
| ACCESS | page `0x2A` : octet 0 bit2 = `CNT_RD_EN`, bit3 = `CNT_INC_EN`, bit6 = `CFGLCK`, bit7 = `PROT` ; octets 2–3 = `AUTH_LIM` |
| LOCK_KEYS | page `0x2D` : octet 0 = bits de verrouillage par clé |

Le bloc **UL-AES Config** d'`Info` décode tout cela, par exemple :

- `Auth from: off (open)` ou `Auth from: page 0x10 (r+w)` / `(write)` : `AUTH0` et `PROT` ;
- `Auth limit: unlimited` ou `Auth limit: N (locks!)` ;
- `Counter 2: rd open / inc auth` et similaires ;
- `Random ID: on/off`, `Secure msg: on/off`, `User cfg: open/locked`, `Key lock: DP N / UID N` ;
- `Real UID:` une fois révélé.

::: danger N'expérimentez pas avec ces bits
`CFGLCK` verrouille la configuration **définitivement**, `AUTH_LIM` arme un blocage après des authentifications
échouées, et les `LOCK_KEYS` / octets de verrouillage statique peuvent rendre la carte inutilisable. Ne les modifiez
jamais sur une carte à laquelle vous tenez. Notez également que le `hf mfu info` de PM3 étiquette les pages
`0x34`–`0x37` du MF0AES20 avec un modèle Ultralight hérité (`cfg0/cfg1/PWD/PACK`) ; fiez-vous au tableau ci-dessus.
:::

## Réécrire un dump

Proposé uniquement sur un dump Ultralight AES **entièrement lu**, sous forme de deux entrées :

- **Write (Keep Key)** : écrit les pages de données `0x04`–`0x27` ; la clé de la cible est conservée.
- **Write (Copy Key)** : les pages de données plus la **DataProtKey** (`0x30`–`0x33`) issue du dump.

Règles intégrées au firmware :

- L'écriture **s'authentifie d'abord auprès de la cible** avec une clé de dictionnaire : la clé *actuelle* de la
  cible doit donc figurer dans un dictionnaire (la clé d'usine tout à zéro y est).
- Les pages de configuration / verrouillage `0x28`–`0x2F` ne sont **jamais** écrites ; l'UIDRetrKey (`0x34`–`0x37`)
  n'est jamais écrite.
- La cible doit être du même **type** ; l'UID n'a pas besoin de correspondre.

## Émulation

`Saved → <carte> → Emulate`. La carte émulée répond à GET_VERSION, fournit la signature, les compteurs et la
configuration comme la vraie, réalise l'authentification AES en tant que carte en utilisant
`reverse(pages 0x30–0x33)` comme clé, rejette les mauvaises clés et applique `AUTH0`. À noter : les lectures
restreintes sans authentification renvoient des données de pages antérieures (par repliement) au lieu d'un NAK.

## Messagerie sécurisée (CMAC)

Avec `SEC_MSG_ACT` activé, une fois authentifié, **chaque** commande et chaque réponse doit porter un CMAC. Le
Flipper gère cela de manière adaptative : après l'authentification, le premier `READ`/`WRITE` en clair échoue (le
silicium réel se contente de se taire, ce que le lecteur interprète comme un dépassement de délai), le firmware se
réauthentifie et passe aux `READ`, `READ_CNT` et `WRITE` encapsulés par un MAC. Le compteur de commandes avance de 2
par échange (la commande utilise `CmdCtr`, la réponse `CmdCtr+1`). Validé sur matériel : une lecture complète 60/60
sous CMAC sans aucune incohérence de MAC, des compteurs sous CMAC, les pages de clé `0x30`–`0x37` masquées à zéro
dans le dump, et une réécriture CMAC des pages de données.

L'émulateur parle également la messagerie sécurisée : il vérifie le MAC de la commande, encapsule chaque réponse
dans un MAC, remplace l'accusé de réception du `WRITE` par un MAC, et abandonne la session sur un MAC incorrect.

::: warning Réversibilité
Une fois `SEC_MSG_ACT` activé, les écritures de configuration dans une zone protégée nécessitent une écriture
authentifiée par CMAC, ce que le Proxmark3 ne sait pas faire et que l'écriture du Flipper contourne (les pages de
configuration ne sont jamais écrites). Ne réglez pas `AUTH0 ≤ 0x29` sur une carte en messagerie sécurisée, sous
peine de ne plus pouvoir la désactiver.
:::

### Marqueurs de débogage

Avec `Settings → System → Log Level → Debug`, vous pouvez suivre ce qui se passe dans le journal, par exemple
`UL-AES: plain read failed post-auth, switching to secure messaging`,
`UL-AES response MAC mismatch (ctr N)` (ne devrait pas apparaître lors d'une exécution saine),
`UL-AES command MAC mismatch, dropping session` (côté émulateur).

## Voir aussi

[Déverrouillage par mot de passe](/fr/nfc/unlock-with-password) · [Lire des cartes](/fr/nfc/read) · [Format de fichier NFC](/fr/nfc/file-format) ·
[Ajouter des cartes manuellement](/fr/nfc/add-manually)
