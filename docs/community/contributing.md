---
title: Contributing & translating
order: 40
---
# Contributing & translating

This wiki is a [VitePress](https://vitepress.dev) site. Pages are plain Markdown, every page exists in **every
language**, and every page that uses a source **credits** it.

## How the wiki is organised

Content lives under `docs/`, split by language and then by section:

```
docs/              # English (the root locale)
  nfc/read.md
  community/credits.md
docs/ru/           # Russian — mirrors docs/ exactly
  nfc/read.md
  community/credits.md
```

**Every page exists at the same path in every language.** The English `docs/nfc/read.md` and
the Russian `docs/ru/nfc/read.md` are the same page in two languages. If a page exists in one language it must exist
in all of them — run `npm run check` to list any that are missing.

Sections (the top-level folders) are fixed in `docs/.vitepress/i18n/sections.ts`; each section has an `index.md`
that acts as its landing page.

## Frontmatter

Every page starts with a YAML frontmatter block:

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

- **`title`** — shown in the sidebar and as the page title.
- **`order`** — position in the section sidebar. Use multiples of 10 so pages can be inserted later. Section
  `index.md` pages are landing pages and get no `order`.
- **`author`** — set to `gromovyna` (the only registered author key) whenever **any** of his material is used, even
  partially. It renders a highlighted credit card at the bottom.
- **`original`** — the list of **exact** URLs the page was built from. Mandatory whenever a source was used.
- **`sources`** — the keys of every source used (see below). Required on every content page, including section
  index pages.

Keep the **same frontmatter in every language** — translating a page does not change who it is credited to.

## Credits are required

If a page uses *any* source — an article, a channel post, documentation, or firmware code — it must credit it. The
credits block at the bottom of each page is generated from the frontmatter above. The valid source keys are defined
in `docs/.vitepress/sources.ts`; current keys include:

| Key | Source |
|---|---|
| `gromovyna` | @gromovyna's articles and channel |
| `how2flipper` | @how2flipper_rus channel |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | Unleashed documentation |
| `unleashed-readme` | Unleashed ReadMe |
| `unleashed-src` | Unleashed firmware source |
| `li0ard` | li0ard's blog |

Building a page from the firmware source counts as using a source: add `unleashed-src` to `sources` and put the
relevant GitHub source directory in `original`.

How to form the `original` URLs:

- **Flipper docs** — `https://docs.flipper.net/zero/<path>` (so `zero_nfc_read.md` → `/zero/nfc/read`).
- **Unleashed docs** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md`
  (spaces as `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — the `telegra.ph` URL of the article and/or `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Writing style

- A real how-to, not a copy. Rewrite in your own words, merge overlapping sources, restructure for the reader.
- Be **Unleashed-first**: when Unleashed differs from the stock firmware, say so with a `::: tip Unleashed` box.
- Each feature page: what it is → when to use it → numbered steps with exact menu paths
  (`Main Menu → Sub-GHz → Read`), buttons as `<kbd>OK</kbd>`, expected results, troubleshooting, related links.
- Preserve technical facts exactly: frequencies, file formats, paths like `/ext/subghz/`, CLI commands, protocol
  names, version numbers. Don't invent features — if you're unsure, leave it out.
- Use VitePress containers: `::: tip`, `::: warning`, `::: danger`, `::: details`. The only raw HTML allowed is
  `<kbd>`; no Vue components.
- Internal links are absolute and extension-less: `/nfc/mfkey` in English, `/ru/nfc/mfkey` in Russian. Only link to
  pages that exist.

## Adding a page

1. Create `docs/<section>/<page>.md` with frontmatter and content.
2. Create the mirror in **every** other language at the same path (e.g. `docs/ru/<section>/<page>.md`).
3. Add it to the section's `index.md` list.
4. Run `npm run check` to confirm no language is missing the page, then
   `npx vitepress build docs` to catch dead links (they are reported as build errors).

The sidebar is generated automatically from the files and their `order`, so there's no sidebar list to edit.

## Device screenshots

The Flipper screens under `/screens/…` are **generated, not captured**. `npm run screens` compiles the firmware's own
GUI code (the canvas, `gui/modules/*` and the app views) and renders every screen into
`docs/public/screens/<section>/<name>.png`. The result is pixel-identical to a qFlipper screenshot: the same 128x64
frame, the same two colours, scaled ×4. The renderer lives in `scripts/screens/` — its `README.md` explains the
requirements, where the firmware checkout comes from and how the output format is derived from qFlipper's code.

To add a new screen:

1. Write a `SCREEN(...)` block in `scripts/screens/specs/<section>.c`. Build the view exactly the way the app scene
   does (`submenu_add_item`, `widget_add_*`, `popup_set_*`, the view's own setters) with realistic placeholder data.
2. Run `npm run screens` (or `bash scripts/screens/build.sh --only <section>/` for a single section).
3. Reference the PNG from the page: `![alt text](/screens/<section>/<name>.png)`. The path is **identical in every
   language**; only the alt text is translated.

Put each screenshot next to the step or screen it illustrates, not in a gallery at the top of the page, and keep it to
a few per page. `docs/public/screens/manifest.json` lists every generated screen with its title, menu path and the
firmware scene the placeholder state comes from.

## Adding a new language

The language registry is `docs/.vitepress/i18n/`. To add language `xx`:

1. **Copy the strings.** Copy `docs/.vitepress/i18n/en.ts` to `docs/.vitepress/i18n/xx.ts` and translate every
   string in it. Set `prefix: 'xx'` (this becomes the `/xx/` URL prefix).
2. **Register it.** In `docs/.vitepress/i18n/index.ts`, import your file and append it to the `LOCALES` array.
3. **Create the pages.** Create `docs/xx/` mirroring `docs/` — the same file names and paths — and translate each
   page. Keep the frontmatter identical (same `author`, `original`, `sources`).
4. **Check.** Run `npm run check` to list any pages missing in the new language, fill the gaps, then build.

::: tip You don't touch `.vitepress/` for content
Everything above except *adding a language* is pure Markdown under `docs/`. The sidebar, navbar and credits block
are all generated — leave `docs/.vitepress/` alone unless you are specifically adding a language or a source key.
:::

::: tip See also
- [Credits & thanks](/community/credits) — how existing pages are credited
- [Community overview](/community/) — the rest of this section
:::
