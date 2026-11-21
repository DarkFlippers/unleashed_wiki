---
title: Contribuire e tradurre
order: 40
---
# Contribuire e tradurre

Questa wiki è un sito [VitePress](https://vitepress.dev). Le pagine sono semplice Markdown, ogni pagina esiste in
**tutte le lingue** e ogni pagina che usa una fonte la **cita**. Questa pagina spiega come aggiungere o modificare
una pagina, come funzionano i crediti e come aggiungere un'intera nuova lingua.

## Come è organizzata la wiki

I contenuti stanno sotto `docs/`, suddivisi per lingua e poi per sezione:

```
docs/              # English (the root locale)
  nfc/read.md
  community/credits.md
docs/ru/           # Russian — mirrors docs/ exactly
  nfc/read.md
  community/credits.md
```

La regola è semplice: **ogni pagina esiste allo stesso percorso in tutte le lingue.** Il file inglese
`docs/nfc/read.md` e quello russo `docs/ru/nfc/read.md` sono la stessa pagina in due lingue. Se una pagina esiste in
una lingua deve esistere in tutte: esegui `npm run check` per elencare quelle che mancano.

Le sezioni (le cartelle di primo livello) sono fissate in `docs/.vitepress/i18n/sections.ts`; ogni sezione ha un
`index.md` che funge da pagina di apertura.

## Frontmatter

Ogni pagina inizia con un blocco di frontmatter YAML:

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

- **`title`** — compare nella barra laterale e come titolo della pagina.
- **`order`** — posizione nella barra laterale della sezione. Usa multipli di 10 così da poter inserire pagine in
  seguito. Gli `index.md` di sezione sono pagine di apertura e non hanno `order`.
- **`author`** — impostalo su `gromovyna` (l'unica chiave autore registrata) ogni volta che viene usato **qualsiasi**
  suo materiale, anche in parte. Genera in fondo alla pagina una scheda di credito in evidenza.
- **`original`** — l'elenco delle URL **esatte** da cui la pagina è stata costruita. Obbligatorio ogni volta che è
  stata usata una fonte.
- **`sources`** — le chiavi di tutte le fonti usate (vedi sotto). Obbligatorio su ogni pagina di contenuto, comprese
  le pagine index di sezione.

Mantieni lo **stesso frontmatter in tutte le lingue**: tradurre una pagina non cambia a chi è attribuita.

## I crediti sono obbligatori

Se una pagina usa *una qualsiasi* fonte — un articolo, un post su un canale, della documentazione o del codice del
firmware — deve citarla. Il blocco dei crediti in fondo a ogni pagina viene generato dal frontmatter descritto sopra.
Le chiavi di fonte valide sono definite in `docs/.vitepress/sources.ts`; le chiavi attuali comprendono:

| Chiave | Fonte |
|---|---|
| `gromovyna` | Gli articoli e il canale di @gromovyna |
| `how2flipper` | Il canale @how2flipper_rus |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | La documentazione di Unleashed |
| `unleashed-readme` | Il ReadMe di Unleashed |
| `unleashed-src` | I sorgenti del firmware Unleashed |
| `li0ard` | Il blog di li0ard |

Costruire una pagina a partire dai sorgenti del firmware conta come uso di una fonte: aggiungi `unleashed-src` a
`sources` e indica in `original` la directory dei sorgenti su GitHub pertinente.

Come si formano le URL in `original`:

- **Documentazione Flipper** — `https://docs.flipper.net/zero/<path>` (quindi `zero_nfc_read.md` → `/zero/nfc/read`).
- **Documentazione Unleashed** —
  `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md` (gli spazi come `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — l'URL `telegra.ph` dell'articolo e/o `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Stile di scrittura

- Una vera guida pratica, non una copia. Riscrivi con parole tue, unisci le fonti che si sovrappongono, ristruttura
  pensando a chi legge.
- Adotta l'approccio **Unleashed-first**: quando Unleashed differisce dal firmware stock, dillo con un riquadro
  `::: tip Unleashed`.
- Ogni pagina su una funzione: cos'è → quando serve → passaggi numerati con i percorsi esatti dei menu
  (`Main Menu → Sub-GHz → Read`), i pulsanti come `<kbd>OK</kbd>`, i risultati attesi, la risoluzione dei problemi, i
  link correlati.
- Conserva esattamente i dati tecnici: frequenze, formati dei file, percorsi come `/ext/subghz/`, comandi CLI, nomi
  dei protocolli, numeri di versione. Non inventare funzioni: se non sei sicuro, lascia fuori.
- Usa i container di VitePress: `::: tip`, `::: warning`, `::: danger`, `::: details`. L'unico HTML grezzo ammesso è
  `<kbd>`; nessun componente Vue.
- I link interni sono assoluti e senza estensione: `/nfc/mfkey` in inglese, `/ru/nfc/mfkey` in russo. Collega solo
  pagine che esistono.

## Aggiungere una pagina

1. Crea `docs/<section>/<page>.md` con frontmatter e contenuto.
2. Crea il corrispondente in **tutte** le altre lingue allo stesso percorso (per esempio
   `docs/ru/<section>/<page>.md`).
3. Aggiungilo all'elenco nell'`index.md` della sezione.
4. Esegui `npm run check` per confermare che non manchi in nessuna lingua, poi `npx vitepress build docs` per
   individuare i link morti (vengono segnalati come errori di build).

La barra laterale è generata automaticamente dai file e dal loro `order`, quindi non c'è nessun elenco da modificare.

## Screenshot del dispositivo

Le schermate del Flipper sotto `/screens/…` sono **generate, non catturate**. `npm run screens` compila il codice
della GUI del firmware stesso (il canvas, `gui/modules/*` e le view delle app) e genera ogni schermata in
`docs/public/screens/<section>/<name>.png`. Il risultato è identico pixel per pixel a uno screenshot di qFlipper: lo
stesso frame 128x64, gli stessi due colori, scalato ×4. Il renderer si trova in `scripts/screens/`: il suo
`README.md` spiega i requisiti, da dove arriva il checkout del firmware e come viene derivato il formato di output dal
codice di qFlipper.

Per aggiungere una nuova schermata:

1. Scrivi un blocco `SCREEN(...)` in `scripts/screens/specs/<section>.c`. Costruisci la view esattamente come fa la
   scena dell'app (`submenu_add_item`, `widget_add_*`, `popup_set_*`, i setter della view stessa) con dati di esempio
   realistici.
2. Esegui `npm run screens` (oppure `bash scripts/screens/build.sh --only <section>/` per una singola sezione).
3. Richiama il PNG dalla pagina: `![alt text](/screens/<section>/<name>.png)`. Il percorso è **identico in tutte le
   lingue**; si traduce solo il testo alternativo.

Metti ogni screenshot accanto al passaggio o alla schermata che illustra, non in una galleria in cima alla pagina, e
limitati a pochi per pagina. `docs/public/screens/manifest.json` elenca ogni schermata generata con il suo titolo, il
percorso nei menu e la scena del firmware da cui proviene lo stato di esempio.

## Aggiungere una nuova lingua

Il registro delle lingue è `docs/.vitepress/i18n/`. Per aggiungere la lingua `xx`:

1. **Copia le stringhe.** Copia `docs/.vitepress/i18n/en.ts` in `docs/.vitepress/i18n/xx.ts` e traduci ogni stringa
   al suo interno. Imposta `prefix: 'xx'` (diventerà il prefisso dell'URL `/xx/`).
2. **Registrala.** In `docs/.vitepress/i18n/index.ts` importa il tuo file e aggiungilo all'array `LOCALES`.
3. **Crea le pagine.** Crea `docs/xx/` come specchio di `docs/` — gli stessi nomi di file e gli stessi percorsi — e
   traduci ogni pagina. Mantieni il frontmatter identico (stessi `author`, `original`, `sources`).
4. **Controlla.** Esegui `npm run check` per elencare le pagine che mancano nella nuova lingua, colma le lacune, poi
   compila.

::: tip Per i contenuti non si tocca `.vitepress/`
Tutto quanto sopra, tranne *aggiungere una lingua*, è puro Markdown sotto `docs/`. Barra laterale, barra di
navigazione e blocco dei crediti sono tutti generati: lascia `docs/.vitepress/` così com'è, a meno che non stia
aggiungendo proprio una lingua o una chiave di fonte.
:::

::: tip Vedi anche
- [Crediti e ringraziamenti](/it/community/credits) — come sono attribuite le pagine esistenti
- [Panoramica della comunità](/it/community/) — il resto di questa sezione
:::
