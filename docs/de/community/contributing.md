---
title: Mitmachen & Übersetzen
order: 40
---
# Mitmachen & Übersetzen

Dieses Wiki ist eine [VitePress](https://vitepress.dev)-Website. Die Seiten sind einfaches Markdown, jede Seite
existiert in **jeder Sprache**, und jede Seite, die eine Quelle verwendet, **nennt** sie. Diese Seite erklärt, wie
du eine Seite anlegst oder bearbeitest, wie die Credits funktionieren und wie eine ganz neue Sprache dazukommt.

## Wie das Wiki aufgebaut ist

Die Inhalte liegen unter `docs/`, aufgeteilt nach Sprache und dann nach Abschnitt:

```
docs/              # English (the root locale)
  nfc/read.md
  community/credits.md
docs/ru/           # Russian — mirrors docs/ exactly
  nfc/read.md
  community/credits.md
```

Die Regel ist einfach: **Jede Seite existiert in jeder Sprache unter demselben Pfad.** Das englische
`docs/nfc/read.md` und das russische `docs/ru/nfc/read.md` sind dieselbe Seite in zwei Sprachen. Existiert eine
Seite in einer Sprache, muss sie in allen existieren — `npm run check` listet die fehlenden auf.

Die Abschnitte (die Ordner der obersten Ebene) sind in `docs/.vitepress/i18n/sections.ts` festgelegt; jeder
Abschnitt hat eine `index.md`, die als Einstiegsseite dient.

## Frontmatter

Jede Seite beginnt mit einem YAML-Frontmatter-Block:

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

- **`title`** — erscheint in der Seitenleiste und als Seitentitel.
- **`order`** — die Position in der Seitenleiste des Abschnitts. Nimm Vielfache von 10, damit später Seiten
  dazwischen passen. Die `index.md` eines Abschnitts ist eine Einstiegsseite und bekommt kein `order`.
- **`author`** — auf `gromovyna` setzen (der einzige registrierte Autorenschlüssel), sobald **irgendetwas** aus
  seinem Material verwendet wird, auch nur teilweise. Daraus wird unten auf der Seite eine hervorgehobene
  Credits-Karte erzeugt.
- **`original`** — die Liste der **genauen** URLs, aus denen die Seite entstanden ist. Pflicht, sobald eine Quelle
  verwendet wurde.
- **`sources`** — die Schlüssel aller verwendeten Quellen (siehe unten). Pflicht auf jeder Inhaltsseite,
  einschließlich der Abschnitts-Einstiegsseiten.

Behalte in **jeder Sprache dasselbe Frontmatter** — eine Übersetzung ändert nichts daran, wem die Seite
zugeschrieben wird.

## Credits sind Pflicht

Wenn eine Seite *irgendeine* Quelle verwendet — einen Artikel, einen Kanalbeitrag, eine Dokumentation oder
Firmware-Code —, muss sie sie nennen. Der Credits-Block am Ende jeder Seite wird aus dem Frontmatter darüber
erzeugt. Die gültigen Quellenschlüssel sind in `docs/.vitepress/sources.ts` definiert; aktuell gibt es:

| Schlüssel | Quelle |
|---|---|
| `gromovyna` | Artikel und Kanal von @gromovyna |
| `how2flipper` | Kanal @how2flipper_rus |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | Unleashed-Dokumentation |
| `unleashed-readme` | Unleashed-ReadMe |
| `unleashed-src` | Quellcode der Unleashed-Firmware |
| `li0ard` | Blog von li0ard |

Eine Seite aus dem Firmware-Quellcode zu bauen zählt als Verwendung einer Quelle: trag `unleashed-src` in `sources`
ein und das passende GitHub-Quellverzeichnis in `original`.

So werden die `original`-URLs gebildet:

- **Flipper-Dokumentation** — `https://docs.flipper.net/zero/<path>` (also `zero_nfc_read.md` → `/zero/nfc/read`).
- **Unleashed-Dokumentation** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md`
  (Leerzeichen als `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — die `telegra.ph`-URL des Artikels und/oder `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Schreibstil

- Eine echte Anleitung, keine Kopie. Formuliere in eigenen Worten, führe sich überschneidende Quellen zusammen,
  strukturiere für den Lesenden um.
- Sei **Unleashed-first**: Wo Unleashed von der Stock-Firmware abweicht, sag es mit einem `::: tip Unleashed`-Kasten.
- Jede Funktionsseite: was es ist → wann man es braucht → nummerierte Schritte mit genauen Menüpfaden
  (`Main Menu → Sub-GHz → Read`), Tasten als `<kbd>OK</kbd>`, erwartete Ergebnisse, Fehlerbehebung, verwandte Links.
- Übernimm technische Fakten exakt: Frequenzen, Dateiformate, Pfade wie `/ext/subghz/`, CLI-Befehle, Protokollnamen,
  Versionsnummern. Erfinde keine Funktionen — wenn du unsicher bist, lass es weg.
- Nutze die VitePress-Container: `::: tip`, `::: warning`, `::: danger`, `::: details`. Das einzige erlaubte rohe
  HTML ist `<kbd>`; keine Vue-Komponenten.
- Interne Links sind absolut und ohne Dateiendung: `/nfc/mfkey` im Englischen, `/ru/nfc/mfkey` im Russischen.
  Verlinke nur auf Seiten, die existieren.

## Eine Seite hinzufügen

1. Lege `docs/<section>/<page>.md` mit Frontmatter und Inhalt an.
2. Lege das Gegenstück in **jeder** anderen Sprache unter demselben Pfad an (z. B. `docs/ru/<section>/<page>.md`).
3. Nimm die Seite in die Liste in der `index.md` des Abschnitts auf.
4. Führe `npm run check` aus, um zu bestätigen, dass die Seite in keiner Sprache fehlt, und dann
   `npx vitepress build docs`, um toten Links auf die Spur zu kommen (sie werden als Build-Fehler gemeldet).

Die Seitenleiste wird automatisch aus den Dateien und ihrem `order` erzeugt, es gibt also keine Sidebar-Liste zu
pflegen.

## Screenshots des Geräts

Die Flipper-Bildschirme unter `/screens/…` sind **generiert, nicht abgefilmt**. `npm run screens` kompiliert den
GUI-Code der Firmware selbst (das Canvas, `gui/modules/*` und die App-Views) und rendert jeden Screen nach
`docs/public/screens/<section>/<name>.png`. Das Ergebnis ist pixelgleich mit einem qFlipper-Screenshot: derselbe
128x64-Rahmen, dieselben zwei Farben, ×4 skaliert. Der Renderer liegt in `scripts/screens/` — seine `README.md`
erklärt die Voraussetzungen, woher der Firmware-Checkout kommt und wie sich das Ausgabeformat aus dem Code von
qFlipper ableitet.

So fügst du einen neuen Screen hinzu:

1. Schreibe einen `SCREEN(...)`-Block in `scripts/screens/specs/<section>.c`. Baue den View genau so auf, wie es die
   Szene der App tut (`submenu_add_item`, `widget_add_*`, `popup_set_*`, die eigenen Setter des Views), mit
   realistischen Platzhalterdaten.
2. Führe `npm run screens` aus (oder `bash scripts/screens/build.sh --only <section>/` für einen einzelnen
   Abschnitt).
3. Verweise von der Seite auf das PNG: `![alt text](/screens/<section>/<name>.png)`. Der Pfad ist **in jeder Sprache
   identisch**; übersetzt wird nur der Alt-Text.

Setze jeden Screenshot neben den Schritt oder Screen, den er zeigt, nicht in eine Galerie am Seitenanfang, und
beschränke dich auf einige wenige pro Seite. `docs/public/screens/manifest.json` listet jeden generierten Screen mit
Titel, Menüpfad und der Firmware-Szene, aus der der Platzhalterzustand stammt.

## Eine neue Sprache hinzufügen

Das Sprachregister liegt in `docs/.vitepress/i18n/`. So kommt die Sprache `xx` dazu:

1. **Die Strings kopieren.** Kopiere `docs/.vitepress/i18n/en.ts` nach `docs/.vitepress/i18n/xx.ts` und übersetze
   jeden String darin. Setze `prefix: 'xx'` (daraus wird das URL-Präfix `/xx/`).
2. **Registrieren.** Importiere deine Datei in `docs/.vitepress/i18n/index.ts` und häng sie an das Array `LOCALES`
   an.
3. **Die Seiten anlegen.** Lege `docs/xx/` als Spiegel von `docs/` an — dieselben Dateinamen und Pfade — und
   übersetze jede Seite. Lass das Frontmatter identisch (gleiches `author`, `original`, `sources`).
4. **Prüfen.** Führe `npm run check` aus, um die in der neuen Sprache fehlenden Seiten aufzulisten, füll die Lücken
   und baue dann.

::: tip Für Inhalte fasst du `.vitepress/` nicht an
Alles oben außer dem *Hinzufügen einer Sprache* ist reines Markdown unter `docs/`. Seitenleiste, Navigationsleiste
und Credits-Block werden alle generiert — lass `docs/.vitepress/` in Ruhe, solange du nicht ausdrücklich eine
Sprache oder einen Quellenschlüssel hinzufügst.
:::

::: tip Siehe auch
- [Credits & Danksagungen](/de/community/credits) — wie bestehende Seiten ihre Quellen nennen
- [Community-Überblick](/de/community/) — der Rest dieses Abschnitts
:::
