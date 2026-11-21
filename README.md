# Unleashed Wiki

A static wiki for Flipper Zero, centred on [Unleashed Firmware](https://github.com/DarkFlippers/unleashed-firmware).
Built with VitePress; the output is a plain folder of files you can serve with nginx.

## Build

```bash
npm install
npm run dev      # local preview at http://localhost:5173
npm run build    # output → docs/.vitepress/dist
npm run preview  # serve the built site
```

Deploy = copy `docs/.vitepress/dist/*` to your web root. See `nginx.conf.example`
(the site uses clean URLs, so nginx needs `try_files $uri $uri.html $uri/ =404`).

## Helper scripts

| Command | What it does |
|---|---|
| `npm run check` | Lists pages that exist in English but are missing in another language |
| `npm run images` | Downloads any remote image still referenced in markdown into `docs/public/img/remote/` and rewrites the links |
| `npm run screens` | Regenerates the Flipper screen images from the firmware source (see `scripts/screens/README.md`) |

Set `UL_SKIP_LINKCHECK=1` to build while a translation is still in progress; it
skips the dead-link check that fails on pages not yet written in some language.

## Search engines

`npm run build` defaults to `https://wiki.unleashedflip.com`. Override it for
another origin:

```bash
UL_SITE_URL=https://wiki.example.com npm run build
```

That turns on, for every page and every language:

| | |
|---|---|
| `sitemap.xml` | Every page in every language, generated at build time |
| `robots.txt` | Written at build time so it names the right sitemap URL |
| `<link rel="canonical">` | The page's own URL, so the seven languages are not read as duplicates |
| `<link rel="alternate" hreflang>` | One per language that actually has the page, plus `x-default` to English |
| `og:` / `twitter:` | Title, description and the `og.png` share image |
| `<meta name="description">` | Taken from frontmatter `description:`, or the page's first paragraph |

Running `vitepress build docs` directly, without the variable, still succeeds
but emits none of the absolute-URL tags and prints a warning: a wrong canonical
is worse than no canonical.

A page gets a better description from an explicit `description:` in its
frontmatter than from the automatic first-paragraph one.

## Layout

```
docs/
  index.md              English home page
  <section>/            English pages (start, subghz, nfc, rfid, infrared,
                        ibutton, badusb, gpio, apps, mobile, dev, community)
  ru/                   Russian pages, same paths as the English ones
  public/               Images and generated screenshots
  .vitepress/
    config.mts          Site config, builds one locale per language
    sidebar.ts          Sidebar generated from the file system
    sources.ts          Registry of sources and authors used in credits
    i18n/               Language registry: one file of strings per language
    theme/              Red/black Unleashed theme + credits component
```

## Writing a page

Frontmatter drives the sidebar and the credits block at the bottom of the page:

```yaml
---
title: Reading cards       # page title and sidebar label
order: 20                  # sort order inside the section
author: gromovyna          # only when the page uses his material
original:                  # exact URLs this page was built from
  - https://telegra.ph/...
sources: [unleashed-src, flipper-docs]
---
```

Credits are required on every page that uses a source. Source keys live in
`docs/.vitepress/sources.ts`. The firmware source is the source of truth for
Sub-GHz, RFID, iButton and NFC: the official docs are outdated in those areas.

## Language detection

A small inline script in every page sends a first-time visitor to the version
matching their browser language:

- English lives at the root, so an English speaker is never redirected.
- `uk-*` and `ru-UA` both map to Ukrainian (`/ua/`).
- A language the wiki doesn't have falls through to the next one the browser
  lists, then to English.
- Once someone picks a language from the menu it is stored in `localStorage`
  (`ul-lang`) and detection stops guessing — including when they pick English.
- A page not yet translated would 404, so the theme's 404 handler sends that
  path back to English, and a `sessionStorage` guard stops the two bouncing.

It is pure client-side, so no nginx configuration is needed. To turn it off,
remove `LANG_REDIRECT` from `head` in `docs/.vitepress/config.mts`.

## Adding a language

1. Copy `docs/.vitepress/i18n/en.ts` to `xx.ts`, translate the strings, set `prefix: 'xx'`.
2. Import it in `docs/.vitepress/i18n/index.ts` and append it to `LOCALES`.
3. Create `docs/xx/` and translate the pages, keeping the same file paths.
   Mark a machine-translated language with `machineTranslated: true` and an
   `mtNotice`, which puts a "may contain errors" banner on each of its pages.
4. Run `npm run check` to see what is still missing.

Nothing else needs changing: navigation, sidebar, search and the credits block
all read from the language registry.

## Credits

Content is built from the Unleashed firmware source and
[documentation](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation),
the official [Flipper docs](https://docs.flipper.net/zero), the research articles of
**[@gromovyna](https://t.me/gromovyna)**, and [@how2flipper_rus](https://t.me/how2flipper_rus).

The firmware source is the source of truth: the official docs are out of date for
Sub-GHz, 125 kHz RFID, iButton and parts of NFC, and the pages say so where they differ.

Per-page credits are shown on each page; the full list is on `/community/credits`.

Not affiliated with Flipper Devices. For educational and lawful use only.
