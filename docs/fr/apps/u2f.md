---
title: Clé de sécurité U2F
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# Clé de sécurité U2F

L'application **U2F** transforme le Flipper Zero en clé de sécurité USB
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). Après avoir saisi votre mot de
passe sur un site web, le site réclame la clé et vous confirmez la connexion en appuyant sur <kbd>OK</kbd> sur le
Flipper. Google, GitHub, Facebook, X et bien d'autres sites prennent en charge les clés U2F ;
[dongleauth.com](https://www.dongleauth.com/) en tient une liste.

::: warning Clé purement logicielle
L'U2F du Flipper est implémenté en logiciel. Pour la banque et d'autres comptes à forte valeur, utilisez une clé de
sécurité matérielle certifiée. Conservez toujours un second facteur de secours (codes de récupération ou une autre
clé).
:::

## Avant de commencer

- Une **carte microSD est obligatoire**. Les données U2F résident dans `/ext/u2f/`. Sans elle, l'application affiche
  `No SD card or app data found. This app will not work without required files.`
- Les fichiers de certificat `/ext/u2f/assets/cert.der` et `/ext/u2f/assets/cert_key.u2f` sont installés par la mise à
  jour du firmware. S'ils manquent, mettez à nouveau le firmware à jour avec la carte insérée.
- **Fermez qFlipper** (et Flipper Lab) : le Flipper doit être libre de basculer son port USB en mode U2F. Si une
  connexion est active, l'application affiche
  `Connection Is Active! Disconnect from PC or phone to use this function.`

## Enregistrer le Flipper sur un site web

1. Connectez le Flipper à l'ordinateur avec un câble USB.
2. Ouvrez `Main Menu → U2F`. L'écran affiche `Connect me to computer`, puis `Connected!` dès que l'ordinateur a
   reconnu la clé.

   ![U2F : Connect me to computer, avec le Flipper dessiné sous forme de clé USB](/screens/apps/u2f_not_connected.png)
3. Sur le site web, ouvrez les réglages de double authentification et choisissez d'ajouter une **clé de sécurité** (la
   formulation varie d'un site à l'autre).
4. Le Flipper affiche `Press OK to register`. Appuyez sur <kbd>OK</kbd>.
5. Le site confirme que la clé a été ajoutée.

## Se connecter

1. Connectez le Flipper en USB et ouvrez `Main Menu → U2F` (`Connected!`).
2. Saisissez votre identifiant et votre mot de passe sur le site web.
3. Quand le site demande la clé de sécurité, le Flipper affiche `Press OK to authenticate`. Appuyez sur <kbd>OK</kbd>.

   ![U2F : Press OK to authenticate, avec l'indication du bouton OK](/screens/apps/u2f.png)
4. Le Flipper affiche `Authentication successful!` et le site vous connecte.

## Protégez vos fichiers U2F

| Fichier | Rôle |
|---|---|
| `/ext/u2f/key.u2f` | la clé U2F de cet appareil, chiffrée avec une clé propre à ce Flipper |
| `/ext/u2f/cnt.u2f` | compteur d'authentifications |
| `/ext/u2f/assets/` | certificat d'attestation et sa clé (`cert.der`, `cert_key.u2f`) |

::: danger Ne supprimez, ne modifiez et ne déplacez pas les fichiers U2F
- Chaque Flipper possède une clé interne unique qui chiffre les fichiers U2F. Une carte dont les fichiers U2F sont
  transférés sur **un autre Flipper n'y fonctionnera pas**.
- Si vous supprimez ou modifiez les fichiers, ou si vous insérez une nouvelle carte, le Flipper crée un nouveau jeu de
  fichiers U2F et vous devez **l'enregistrer de nouveau sur chaque site web**.
- Si vous supprimez `u2f/assets` (ou tout le dossier `u2f`), l'application cesse de fonctionner (elle signale
  `No SD card or app data found`) jusqu'à ce que vous restauriez le dossier en mettant le firmware à jour.
:::

## Dépannage

| Symptôme | Solution |
|---|---|
| Reste bloqué sur `Connect me to computer` | utilisez un câble de données (pas un câble de charge seule), fermez qFlipper, essayez un autre port USB |
| `Connection Is Active!` | fermez qFlipper, Flipper Lab, le CLI ou la session de l'application mobile, puis rouvrez U2F |
| `No SD card or app data found` | insérez la carte ; si elle est en place, restaurez `/ext/u2f/assets` en réinstallant le firmware |
| `Certificate error` | le moteur U2F n'a pas pu démarrer avec les fichiers présents sur la carte : réinstallez le firmware avec la carte insérée |
| Le site n'accepte plus la clé | les fichiers U2F ont été régénérés (nouvelle carte, fichiers supprimés) : connectez-vous avec votre facteur de secours et enregistrez de nouveau le Flipper |

L'onglet **U2F** de l'[Archive](/fr/apps/archive) lance aussi l'application.

## Pages liées

- [Applications fournies avec Unleashed](/fr/apps/catalog)
- [Bad USB](/fr/badusb/usage)
- [qFlipper](/fr/mobile/qflipper)
