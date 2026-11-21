---
title: Sub-GHz Bruteforce
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/xMasterX/all-the-plugins]
sources: [unleashed-readme]
---
# Sub-GHz Bruteforce

**Sub-GHz Bruteforce** est une application de force brute sur les codes statiques, développée par l'équipe Unleashed. Elle parcourt les codes possibles d'un protocole à code fixe et les émet l'un après l'autre. Vous pouvez utiliser un protocole préconfiguré de sa liste, ou charger votre propre fichier `.sub` et choisir les octets à faire varier.

::: warning
À n'utiliser que sur votre propre matériel ou avec une autorisation explicite. Attaquer par force brute le portail ou la barrière d'autrui est illégal dans la plupart des pays.
:::

::: tip Unleashed
L'application ne fait pas partie de l'image du firmware et n'est pas dans l'arborescence des sources. Elle est distribuée comme application externe (`.fap`) dans les packs d'applications Unleashed, compilée depuis [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins). Installez le pack (voir [Applications sur la carte SD](/fr/apps/sd-card-apps)) et cherchez-la sous `Apps → Sub-GHz`.
:::

## Quand c'est pertinent

- **Uniquement pour les codes statiques (fixes).** La force brute ne fonctionne que si le récepteur accepte indéfiniment le même code, comme avec les télécommandes à interrupteurs DIP de type CAME 12-bit, Nice Flo 12-bit, Princeton et similaires. Un récepteur à code tournant (KeeLoq, Nice Flor-S, CAME Atomo et autres) n'accepte jamais un code devine : la force brute y est donc inutile (voir [Codes tournants](/fr/subghz/rolling-codes)).
- **Vous avez perdu la télécommande de votre propre installation à code fixe** et vous ne connaissez pas son code, ou vous voulez tester la rapidité avec laquelle votre système à code fixe peut être devine.

Si vous disposez encore d'une télécommande fonctionnelle, il est beaucoup plus rapide de simplement la [lire](/fr/subghz/read).

## Utilisation

### Protocoles préconfigurés

1. Ouvrez `Apps → Sub-GHz` et lancez l'application Bruteforce.
2. Choisissez un protocole dans la liste.
3. Pour modifier le nombre de répétitions de chaque code, appuyez sur <kbd>→</kbd> sur le protocole sélectionné.
4. Démarrez l'attaque et gardez le Flipper près du récepteur jusqu'à ce qu'il réagisse.

### Votre propre fichier

1. Enregistrez d'abord un signal du protocole visé, par exemple avec [Read](/fr/subghz/read) ou [Add Manually](/fr/subghz/add-manually).
2. Dans l'application, chargez ce fichier `.sub`.
3. Sélectionnez les octets de la clé à attaquer par force brute. Les autres octets restent tels qu'ils sont dans le fichier.
4. Démarrez l'attaque.

### Délai entre les signaux

Le délai entre les codes émis se règle sur l'écran principal de l'application. **Maintenez <kbd>↑</kbd>** à cet endroit (l'indication à l'écran affiche « Up to Save ») pour l'enregistrer. Un délai plus court termine plus vite, mais certains récepteurs manquent les codes qui se suivent de trop près.

## Conseils et erreurs fréquentes

- **Mauvaise fréquence ou mauvaise modulation** : le récepteur n'entend rien. Vérifiez d'abord la bande avec le [Frequency Analyzer](/fr/subghz/frequency-analyzer).
- **Trop peu de répétitions** : beaucoup de récepteurs ont besoin qu'un code soit répété plusieurs fois avant d'agir. Augmentez les répétitions avec <kbd>→</kbd> sur le protocole.
- **L'attaque dure longtemps** : le nombre de codes croît exponentiellement avec le nombre de bits. Les codes de 12 bits sont rapides, alors que des clés plus longues peuvent demander un temps déraisonnable. Réduisez l'espace de recherche en n'attaquant que les octets inconnus de votre propre fichier.
- **L'émission est bloquée** : la fréquence est en dehors de la plage autorisée. Voir [Fréquences](/fr/subghz/frequencies).

## Pages liées

- [Systèmes pris en charge](/fr/subghz/supported-systems) : quels protocoles sont statiques
- [Add Manually](/fr/subghz/add-manually)
- [Format de fichier .sub](/fr/subghz/file-format)
