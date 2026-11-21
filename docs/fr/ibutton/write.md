---
title: Écriture sur supports vierges
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# Écrire des clés iButton sur des supports vierges

Les clés iButton d’origine ont un ID usine qui ne peut pas être modifié. Pour en copier une, il vous faut un **support
vierge** — une clé réinscriptible dont l’ID est programmable. Le Flipper Zero propose deux modes d’écriture :

- **Write ID** — écrit l’ID (la ROM / le code) sur un support vierge. C’est le cas classique du « je veux une copie de
  ma clé d’interphone ».
- **Full Write on Same Type** — réservé aux DS1992, DS1996 et DS1971 : copie le contenu de la **mémoire** vers une
  autre clé authentique du même type (DS1992 → DS1992). La clé cible conserve son propre ID.

## Supports vierges pris en charge

| Support vierge (comme dans Settings) | Ce qu’il accepte | Remarques |
|---|---|---|
| **RW1990.1** | ID DS1990, DS1420 | Supports de type RW1990 ; cette variante écrit les bits inversés |
| **RW1990.2** | ID DS1990, DS1420 | Supports de type RW1990, variante non inversée |
| **TM2004** | ID de DS1990, DS1420, DS1992, DS1996, DS1971 et 1-Wire générique | Supports RW2004/TM2004 ; seul l’ID est écrit, même si le support a de la mémoire |
| **TM01x** | ID DS1990, **Cyfral**, **Metakom** | Supports TM01/TM01x |

Les supports vendus sous les noms RW1990, TM1990 ou TM08v2 sont gérés par les variantes RW1990 ; le Flipper essaie les
deux, vous n’avez donc pas besoin de savoir laquelle vous avez en main.

::: tip Unleashed
- **Settings → Write Blanks** permet d’activer ou de désactiver chaque type de support (tous sont sur ON par défaut).
- L’écran d’écriture indique quel support est en cours d’essai, et l’écran de réussite affiche *Written to TM2004!*, etc.
- Les clés **Cyfral et Metakom** peuvent être écrites sur des supports **TM01x**.
:::

::: warning Le TM01x pour Cyfral / Metakom est sans retour
Pour Cyfral et Metakom, le support TM01x est écrit, relu, comparé, puis **finalisé** en mode Cyfral ou Metakom. Cette
finalisation est irréversible : le support ne répond plus comme un périphérique 1-Wire et ne peut plus être réécrit —
pas même en clé Dallas. Si la vérification échoue, le support n’est pas finalisé et reste inscriptible. Un ID Dallas
écrit sur un TM01x ne déclenche pas de finalisation.

Les clés Metakom à parité incorrecte sont refusées (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Ouvrez la clé : `Saved` → clé → **Write ID** (ou **More → Write ID** après une lecture).

   ![Menu d’une clé enregistrée avec Emulate, Write ID, Edit et Rename](/screens/ibutton/saved_menu.png)

2. L’écran affiche **Writing ID**, `[Protocol]`, le nom de la clé (ou *Unsaved Key*) et, entre parenthèses, le type de
   support en cours d’essai — par exemple `(RW1990.1)`.

   ![Écran Writing ID avec le protocole [DS1990], le nom de la clé et le support tenté, (RW1990.1)](/screens/ibutton/write.png)

3. Présentez le support vierge sur la **partie plate** de la plage (broche de données de gauche + masse du milieu),
   comme pour une lecture. Maintenez-le immobile.
4. Le Flipper essaie tous les types de supports activés capables de porter ce protocole, puis relit le résultat.
5. **Written to RW1990.2!** (ou *Successfully written!*) — c’est terminé.

## Full Write on Same Type

1. `Saved` → clé DS1992 / DS1996 / DS1971 → **Full Write on Same Type**.
2. L’écran affiche **Full Writing**. Présentez une clé authentique du **même** type.
3. La mémoire est écrite ; la clé cible conserve son propre ID. Ce mode n’utilise pas le réglage Write Blanks.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` liste **RW1990.1**, **RW1990.2**, **TM2004**, **TM01x** avec
**ON**/**OFF**. Basculez l’état avec <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd> ; le réglage est enregistré en quittant la
page, dans `/ext/ibutton/.ibutton.settings`. La commande CLI `ikey write` utilise le même réglage.

Si la page signale *Settings page missing. Update the SD resources*, réinstallez le firmware avec la carte SD insérée.

## Erreurs

| Écran | Signification |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | Tous les types de supports sont sur OFF |
| **Cannot Write** — *No enabled blank can write this key* | Par exemple, seul RW1990 est activé pour une clé Metakom |
| **Cannot Write** — *This key cannot be written* (ou le motif propre au protocole) | Les données de la clé ne sont pas valides pour une écriture |
| L’écran d’écriture reste affiché, la LED clignote | Aucun support détecté pour l’instant — vérifiez le contact, ou le type de support n’est pas pris en charge |

## Dépannage

- **Contact.** Le centre du support vierge doit toucher la broche de données et sa couronne la broche de masse.
- **Type de support inconnu.** Essayez d’activer tous les types. Certains supports bon marché sont de types que le
  Flipper ne sait pas programmer.
- **« Réussi », mais le lecteur refuse la copie.** Certains lecteurs filtrent les supports vierges (ils détectent le
  comportement propre aux clés réinscriptibles) — le Flipper n’y peut rien.
- **TM01x épuisé.** Un TM01x finalisé en Cyfral/Metakom n’est plus réutilisable.

## Voir aussi

- [Lecture](/fr/ibutton/read) · [Protocoles](/fr/ibutton/protocols) · [Ajout manuel](/fr/ibutton/add-manually)
