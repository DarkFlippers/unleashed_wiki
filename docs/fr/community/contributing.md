---
title: Contribuer et traduire
order: 40
---
# Contribuer et traduire

Ce wiki est un site [VitePress](https://vitepress.dev). Les pages sont du Markdown pur, chaque page existe dans
**toutes les langues**, et chaque page qui s'appuie sur une source la **crédite**. Cette page explique comment ajouter
ou modifier une page, comment fonctionnent les crédits, et comment ajouter une langue entière.

## Organisation du wiki

Le contenu se trouve sous `docs/`, réparti par langue puis par section :

```
docs/              # English (the root locale)
  nfc/read.md
  community/credits.md
docs/ru/           # Russian — mirrors docs/ exactly
  nfc/read.md
  community/credits.md
```

La règle est simple : **chaque page existe au même chemin dans toutes les langues.** Le fichier anglais
`docs/nfc/read.md` et le fichier russe `docs/ru/nfc/read.md` sont la même page en deux langues. Si une page existe
dans une langue, elle doit exister dans toutes les autres — lancez `npm run check` pour lister celles qui manquent.

Les sections (les dossiers de premier niveau) sont fixées dans `docs/.vitepress/i18n/sections.ts` ; chaque section
possède un `index.md` qui sert de page d'accueil.

## Frontmatter

Chaque page commence par un bloc de frontmatter YAML :

```yaml
---
title: Reading cards            # sidebar label + page title
order: 20                       # sort order inside the section sidebar (10, 20, 30…)
author: gromovyna               # ONLY if the page uses @gromovyna's material
original: [https://docs.flipper.net/zero/nfc/read, https://telegra.ph/...]
sources: [flipper-docs, unleashed-docs]
---
# Reading cards
```

- **`title`** — affiché dans la barre latérale et comme titre de la page.
- **`order`** — position dans la barre latérale de la section. Utilisez des multiples de 10 afin de pouvoir insérer
  des pages plus tard. Les `index.md` de section sont des pages d'accueil et ne reçoivent pas d'`order`.
- **`author`** — à renseigner avec `gromovyna` (la seule clé d'auteur enregistrée) dès que **n'importe quel** élément
  de son matériel est utilisé, même partiellement. Cela affiche une carte de crédit mise en évidence en bas de page.
- **`original`** — la liste des URL **exactes** à partir desquelles la page a été construite. Obligatoire dès qu'une
  source a été utilisée.
- **`sources`** — les clés de toutes les sources utilisées (voir ci-dessous). Obligatoire sur chaque page de contenu,
  y compris les pages d'index de section.

Conservez le **même frontmatter dans toutes les langues** : traduire une page ne change pas à qui elle est créditée.

## Les crédits sont obligatoires

Si une page utilise *une quelconque* source — un article, un message de canal, de la documentation ou du code de
firmware — elle doit la créditer. Le bloc de crédits en bas de chaque page est généré à partir du frontmatter
ci-dessus. Les clés de sources valides sont définies dans `docs/.vitepress/sources.ts` ; les clés actuelles sont :

| Clé | Source |
|---|---|
| `gromovyna` | Articles et canal de @gromovyna |
| `how2flipper` | Canal @how2flipper_rus |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | Documentation Unleashed |
| `unleashed-readme` | ReadMe d'Unleashed |
| `unleashed-src` | Code source du firmware Unleashed |
| `li0ard` | Blog de li0ard |

Construire une page à partir du code source du firmware compte comme l'utilisation d'une source : ajoutez
`unleashed-src` à `sources` et indiquez le répertoire source GitHub concerné dans `original`.

Comment composer les URL d'`original` :

- **Documentation Flipper** — `https://docs.flipper.net/zero/<path>` (donc `zero_nfc_read.md` → `/zero/nfc/read`).
- **Documentation Unleashed** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md`
  (les espaces s'écrivent `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — l'URL `telegra.ph` de l'article et/ou `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Style de rédaction

- Un véritable guide pratique, pas une copie. Reformulez avec vos propres mots, fusionnez les sources qui se
  recoupent, restructurez pour le lecteur.
- Soyez **orienté Unleashed** : quand Unleashed diffère du firmware d'origine, dites-le dans un encadré
  `::: tip Unleashed`.
- Pour chaque page de fonctionnalité : de quoi il s'agit → quand l'utiliser → des étapes numérotées avec les chemins
  de menu exacts (`Main Menu → Sub-GHz → Read`), les boutons sous la forme `<kbd>OK</kbd>`, les résultats attendus, le
  dépannage, les liens connexes.
- Reproduisez les faits techniques à l'identique : fréquences, formats de fichiers, chemins comme `/ext/subghz/`,
  commandes CLI, noms de protocoles, numéros de version. N'inventez pas de fonctionnalités — en cas de doute,
  n'écrivez rien.
- Utilisez les conteneurs VitePress : `::: tip`, `::: warning`, `::: danger`, `::: details`. Le seul HTML brut
  autorisé est `<kbd>` ; aucun composant Vue.
- Les liens internes sont absolus et sans extension : `/nfc/mfkey` en anglais, `/ru/nfc/mfkey` en russe. Ne faites des
  liens que vers des pages qui existent.

## Ajouter une page

1. Créez `docs/<section>/<page>.md` avec son frontmatter et son contenu.
2. Créez le miroir dans **toutes** les autres langues au même chemin (par exemple `docs/ru/<section>/<page>.md`).
3. Ajoutez-la à la liste de l'`index.md` de la section.
4. Lancez `npm run check` pour vérifier qu'aucune langue ne manque la page, puis `npx vitepress build docs` pour
   détecter les liens morts (ils sont signalés comme des erreurs de build).

La barre latérale est générée automatiquement à partir des fichiers et de leur `order` : il n'y a donc aucune liste de
barre latérale à modifier.

## Captures d'écran de l'appareil

Les écrans du Flipper situés sous `/screens/…` sont **générés, pas capturés**. `npm run screens` compile le code de
l'interface du firmware lui-même (le canvas, `gui/modules/*` et les vues des applications) et rend chaque écran dans
`docs/public/screens/<section>/<name>.png`. Le résultat est identique au pixel près à une capture qFlipper : la même
image 128x64, les deux mêmes couleurs, mise à l'échelle ×4. Le moteur de rendu se trouve dans `scripts/screens/` —
son `README.md` explique les prérequis, d'où vient la copie du firmware et comment le format de sortie est dérivé du
code de qFlipper.

Pour ajouter un nouvel écran :

1. Écrivez un bloc `SCREEN(...)` dans `scripts/screens/specs/<section>.c`. Construisez la vue exactement comme le fait
   la scène de l'application (`submenu_add_item`, `widget_add_*`, `popup_set_*`, les setters propres à la vue) avec des
   données d'exemple réalistes.
2. Lancez `npm run screens` (ou `bash scripts/screens/build.sh --only <section>/` pour une seule section).
3. Référencez le PNG depuis la page : `![alt text](/screens/<section>/<name>.png)`. Le chemin est **identique dans
   toutes les langues** ; seul le texte alternatif est traduit.

Placez chaque capture à côté de l'étape ou de l'écran qu'elle illustre, et non dans une galerie en haut de page, et
limitez-vous à quelques captures par page. `docs/public/screens/manifest.json` liste chaque écran généré avec son
titre, son chemin de menu et la scène du firmware d'où provient l'état d'exemple.

## Ajouter une nouvelle langue

Le registre des langues est `docs/.vitepress/i18n/`. Pour ajouter la langue `xx` :

1. **Copiez les chaînes.** Copiez `docs/.vitepress/i18n/en.ts` vers `docs/.vitepress/i18n/xx.ts` et traduisez toutes
   les chaînes qu'il contient. Définissez `prefix: 'xx'` (cela devient le préfixe d'URL `/xx/`).
2. **Enregistrez-la.** Dans `docs/.vitepress/i18n/index.ts`, importez votre fichier et ajoutez-le au tableau
   `LOCALES`.
3. **Créez les pages.** Créez `docs/xx/` en miroir de `docs/` — mêmes noms de fichiers et mêmes chemins — et traduisez
   chaque page. Conservez un frontmatter identique (mêmes `author`, `original`, `sources`).
4. **Vérifiez.** Lancez `npm run check` pour lister les pages manquantes dans la nouvelle langue, comblez les trous,
   puis compilez.

::: tip Vous ne touchez pas à `.vitepress/` pour le contenu
Tout ce qui précède, à l'exception de l'*ajout d'une langue*, est du pur Markdown sous `docs/`. La barre latérale, la
barre de navigation et le bloc de crédits sont tous générés : ne touchez pas à `docs/.vitepress/` sauf si vous ajoutez
précisément une langue ou une clé de source.
:::

::: tip Voir aussi
- [Crédits et remerciements](/fr/community/credits) — comment les pages existantes sont créditées
- [Vue d'ensemble de la communauté](/fr/community/) — le reste de cette section
:::
