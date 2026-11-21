---
title: Styles du menu principal
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/menu_styles, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-src]
---
# Styles du menu principal

::: tip Unleashed
Unleashed permet de changer l'apparence du **menu principal** (la liste qui s'ouvre en appuyant sur <kbd>OK</kbd>
depuis le bureau). Chaque apparence est un petit plugin fourni avec le firmware ; le firmware d'origine ne propose que
la liste par défaut.
:::

## Choisir un style

1. Ouvrez `Main Menu → Settings → Desktop`.
2. Descendez jusqu'à **Menu Style**.
3. Appuyez sur <kbd>←</kbd> / <kbd>→</kbd> pour choisir un style. **Default** correspond au menu standard.
4. Quittez les réglages et appuyez sur <kbd>OK</kbd> depuis le bureau : le menu s'ouvre dans le nouveau style.

## Styles disponibles

| Style | Apparence | Origine |
|---|---|---|
| Default | la liste Flipper standard | intégré |
| 3D | un carrousel d'icônes en 3D | porté par @apfxtech, d'après le menu carrousel OLED 3D de @upiir |
| C64 | écran de Commodore 64 | porté depuis Momentum, par Sil (@Sil333033) |
| Compact | une liste plus dense | porté depuis Momentum, par @MatthewKuKanich |
| CoverFlow | carrousel façon pochettes d'album | porté depuis Momentum, par Cody Tolene (@CodyTolene), affiné par @956MB |
| DSi | style Nintendo DSi | porté depuis Momentum, par Willy-JL |
| Grid | icônes en grille | par @apfxtech |
| Macintosh | bureau Mac OS classique | porté par @apfxtech, d'après Ardutosh de @jhhoward |
| PS4 | style PlayStation 4 | porté depuis Momentum, par Willy-JL |
| Vertical | liste verticale | porté depuis Momentum, par Willy-JL |
| Wii | grille de chaînes Nintendo Wii | porté depuis Momentum, par Willy-JL |

Dans les réglages, les styles sont listés par ordre alphabétique après **Default**. Dans tous les styles,
<kbd>OK</kbd> ouvre l'application sélectionnée et <kbd>Back</kbd> ramène au bureau.

## Où résident les styles

Les styles sont des plugins du loader : des fichiers `.fal` nommés `menu_style_<name>.fal` dans
`/ext/apps_data/loader/plugins/`. La liste **Menu Style** est construite à partir des fichiers trouvés là, par
conséquent :

- les styles nécessitent la **carte SD** ;
- un style apparaît comme **Missing** si le fichier sélectionné a été supprimé (réinstallez le firmware pour le
  restaurer), et comme **Unknown** si la carte n'a pas pu être lue ;
- si un style échoue au chargement, le Flipper revient au menu par défaut.

::: info Pour les développeurs
Un nouveau style est un `FlipperAppType.PLUGIN` avec `requires=["loader"]` et un `appid` commençant par
`menu_style_` ; c'est ce préfixe que les réglages utilisent pour distinguer les styles de menu des autres plugins du
loader présents dans le même dossier. Voir `applications/system/menu_styles/` dans les sources du firmware et
[Manifestes d'application](/fr/dev/app-manifests).
:::

## Pages liées

- [Bureau](/fr/start/desktop)
- [Paramètres](/fr/start/settings)
- [Ce qu'Unleashed ajoute](/fr/start/unleashed-features)
