---
title: Apprendre et envoyer des signaux
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# Apprendre et envoyer des signaux IR

Le Flipper Zero peut copier les boutons d'une télécommande IR un par un et les conserver sous forme de
**télécommande virtuelle** : un fichier `.ir` dans `/ext/infrared/`. Pratique quand la télécommande d'origine est
perdue, cassée ou simplement dans une autre pièce, ou quand une télécommande universelle ne trouve pas votre
appareil.

Les signaux des [protocoles connus](/fr/infrared/protocols) sont décodés et enregistrés sous une forme *parsed*
compacte (protocole + adresse + commande). Tout le reste est enregistré sous forme de timings **RAW**, ce qui
fonctionne également pour la relecture.

## Apprendre une nouvelle télécommande

1. Allez dans `Main Menu → Infrared → Learn New Remote`.
2. L'écran affiche **« Point the remote at IR port and push the button »**. Tenez la télécommande à quelques
   centimètres de la tranche supérieure du Flipper, en vue directe de la fenêtre IR.

   ![Learn New Remote en attente d'un signal : « Point the remote at IR port and push the button »](/screens/infrared/learn.png)

3. Appuyez **brièvement** sur le bouton de la télécommande. Ne le maintenez pas : un bouton maintenu donne une
   longue capture remplie de répétitions.
4. L'écran de capture apparaît :
   - un signal décodé affiche le nom du protocole et l'adresse/la commande, par exemple `NECext`, `A: 0x87EE`,
     `C: 0xA05D` ;
   - un signal inconnu affiche **Unknown** et le nombre d'échantillons, par exemple `150 samples`.

   ![Écran de capture : le protocole NEC décodé avec son adresse et sa commande, et Retry, Send et Save en bas](/screens/infrared/learn_success.png)

5. Choisissez ce que vous voulez faire :
   - <kbd>OK</kbd> **Send** : rejoue le signal capturé pendant que vous maintenez le bouton, pour le tester tout de
     suite ;
   - <kbd>←</kbd> **Retry** : demande *« Retry Reading? All unsaved data will be lost! »*, puis <kbd>←</kbd> Exit
     jette la capture et se remet à l'écoute, <kbd>→</kbd> Stay revient en arrière ;
   - <kbd>→</kbd> **Save** : passe au nommage.
6. Saisissez un nom de bouton dans **« Name the button »** (23 caractères maximum) et validez. Le nom par défaut est
   généré à partir du signal : les 4 premières lettres du protocole et la commande (par exemple `NECe_A05D`), ou
   `RAW_<samples>` pour un signal RAW.
7. **« Success! »** s'affiche et la nouvelle télécommande s'ouvre. La première télécommande est enregistrée sous
   `/ext/infrared/Remote.ir` ; si ce nom est déjà pris, ce sera `Remote1.ir`, `Remote2.ir`, et ainsi de suite.

![Signal capturé à l'écran](/img/remote/a62fc8f9d738534b.png)

::: tip Renommez la télécommande
Une télécommande fraîchement créée s'appelle toujours `Remote`. Renommez-la immédiatement via
`Edit → Rename Remote` (voir plus bas), sinon vous finirez avec `Remote`, `Remote1`, `Remote2`…
:::

### Ajouter d'autres boutons

Dans la liste des boutons de la télécommande, descendez tout en bas et sélectionnez **`+`**. L'écran
d'apprentissage s'ouvre à nouveau. Capturez, faites **Save**, nommez le bouton, et vous obtenez **« Saved »** : le
bouton est ajouté au même fichier.

Appuyer sur <kbd>Back</kbd> sur l'écran de capture demande *« Exit to Infrared Menu? »* (ou
*« Exit to Remote Menu? »* lors de l'ajout à une télécommande existante) : les données non enregistrées sont perdues
si vous choisissez Exit.

## Envoyer un bouton enregistré {#send-a-saved-button}

1. Allez dans `Main Menu → Infrared → Saved Remotes` et choisissez un fichier `.ir`.
2. Pointez la tranche supérieure du Flipper vers l'appareil.
3. Sélectionnez un bouton avec <kbd>↑</kbd> / <kbd>↓</kbd> et appuyez sur <kbd>OK</kbd>.

Le signal est envoyé **aussi longtemps que vous maintenez** <kbd>OK</kbd> : une simple pression pour une commande
unique, un appui maintenu pour les actions « presser et maintenir » comme la montée du volume. La LED clignote
pendant l'émission.

![Envoi d'un signal enregistré](/img/remote/d20ed673954c3711.png)

::: tip Favoris et Archive
Les télécommandes enregistrées apparaissent aussi dans l'**Archive** (`Main Menu → Archive → Infrared`) et peuvent y
être ajoutées aux favoris. Dans l'application Flipper Mobile, elles se trouvent sous **Archive → Infrared**, voir
[Télécommandes dans l'application mobile](/fr/infrared/mobile).
:::

## Modifier une télécommande

Ouvrez une télécommande et sélectionnez **Edit** tout en bas de la liste des boutons. Le menu Edit propose :

| Entrée | Rôle |
|---|---|
| **Add Button** | Apprendre un bouton de plus (équivalent de `+`). |
| **Rename Button** | Choisir un bouton et saisir un nouveau nom. |
| **Move Button** | Écran *« Select a Button to Move »* : sélectionnez un bouton, appuyez sur <kbd>OK</kbd> pour le saisir (il se décale vers la droite), déplacez-le avec <kbd>↑</kbd> / <kbd>↓</kbd>, puis appuyez de nouveau sur <kbd>OK</kbd> pour le déposer. |
| **Delete Button** | Choisir un bouton. La confirmation *« Delete Button? »* affiche son nom et son protocole / adresse / commande (ou `RAW` et le nombre d'échantillons). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Renomme la télécommande et le fichier. Si le nom existe déjà, un numéro est ajouté. |
| **Delete Remote** | Confirmation *« Delete Remote? »* avec le nombre de boutons. Supprime le fichier `.ir`. |

Les noms sont limités à **23 caractères**, pour les boutons comme pour les télécommandes. Les modifications plus
lourdes (fusionner des fichiers, supprimer beaucoup de boutons) sont plus simples sur un PC : récupérez le fichier
avec [qFlipper](/fr/mobile/qflipper) et modifiez-le comme du texte, voir le
[format des fichiers IR](/fr/infrared/file-format).

::: warning Les fichiers de bibliothèque ne sont pas des télécommandes
Si vous tentez d'ouvrir un fichier de `/ext/infrared/assets/` via Saved Remotes, vous obtenez
*« Library file … can't be opened as a remote »*. Les fichiers de bibliothèque (`Filetype: IR library file`) ne
servent qu'aux [télécommandes universelles](/fr/infrared/universal-remotes).
:::

## Extras du mode Debug {#debug-mode-extras}

Avec `Settings → System → Debug` sur `ON`, le menu Infrared affiche deux entrées supplémentaires :

- **Learn New Remote RAW** : le même déroulement que Learn, mais le décodeur est désactivé et chaque signal est
  stocké en RAW. Utile quand le décodeur reconnaît un protocole mais que la relecture décodée ne fonctionne pas sur
  votre appareil.
- **Debug RX** : l'écran *« INFRARED monitor »* qui montre en temps réel ce que reçoit le récepteur.

## Dépannage

| Problème | Que faire |
|---|---|
| Rien ne se passe quand on appuie sur la télécommande | Vérifiez les piles de la télécommande (regardez sa LED à travers l'appareil photo d'un téléphone). Rapprochez-vous et visez bien la tranche supérieure. Évitez le soleil direct et les lampes fluorescentes / LED à proximité. |
| Le signal est capturé en **Unknown / RAW** alors que la télécommande est courante | Les interférences peuvent forcer le RAW. Utilisez **Retry** plusieurs fois jusqu'à obtenir un signal décodé. S'il s'agit vraiment d'un protocole inconnu, le RAW convient parfaitement. |
| Captures RAW énormes (des centaines d'échantillons) | Vous avez maintenu le bouton. Faites une pression brève ; une centaine d'échantillons est typique pour un appui unique. Les captures très longues se rejouent lentement. Un signal RAW peut contenir au maximum 1024 timings. |
| L'appareil ne réagit pas au bouton enregistré | Rapprochez-vous, visez directement la fenêtre IR de l'appareil. Essayez de l'envoyer plusieurs fois ou de maintenir <kbd>OK</kbd> plus longtemps. Pour les grandes distances, utilisez un [module IR externe](/fr/infrared/external-ir). |
| Le climatiseur réagit de travers | Les télécommandes de climatiseur envoient l'état complet (mode, température, ventilation) à chaque appui. Enregistrez chaque état dont vous avez besoin comme un bouton distinct, voir [Contribuer ses captures](/fr/infrared/captures#air-conditioners). |
| « Failed to load … » à l'envoi | Le fichier `.ir` est endommagé ou a été modifié à la main de façon incorrecte. Vérifiez-le par rapport au [format de fichier](/fr/infrared/file-format). |

## Voir aussi

- [Télécommandes universelles](/fr/infrared/universal-remotes)
- [Télécommandes dans l'application mobile](/fr/infrared/mobile)
- [Format des fichiers IR](/fr/infrared/file-format)
- [Modules IR externes](/fr/infrared/external-ir)
