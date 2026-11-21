---
title: Contribuir y traducir
order: 40
---
# Contribuir y traducir

Esta wiki es un sitio hecho con [VitePress](https://vitepress.dev). Las páginas son Markdown normal, cada página
existe en **todos los idiomas** y toda página que usa una fuente la **acredita**. Esta página explica cómo añadir o
editar una página, cómo funcionan los créditos y cómo añadir un idioma completo.

## Cómo está organizada la wiki

El contenido vive en `docs/`, separado por idioma y después por sección:

```
docs/              # English (the root locale)
  nfc/read.md
  community/credits.md
docs/ru/           # Russian — mirrors docs/ exactly
  nfc/read.md
  community/credits.md
```

La regla es sencilla: **cada página existe en la misma ruta en todos los idiomas.** El `docs/nfc/read.md` inglés y
el `docs/ru/nfc/read.md` ruso son la misma página en dos idiomas. Si una página existe en un idioma, debe existir
en todos: ejecuta `npm run check` para ver las que falten.

Las secciones (las carpetas de primer nivel) están fijadas en `docs/.vitepress/i18n/sections.ts`; cada sección
tiene un `index.md` que hace de página de entrada.

## Frontmatter

Toda página empieza con un bloque de frontmatter en YAML:

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

- **`title`** — se muestra en la barra lateral y como título de la página.
- **`order`** — la posición en la barra lateral de la sección. Usa múltiplos de 10 para poder insertar páginas más
  adelante. Los `index.md` de sección son páginas de entrada y no llevan `order`.
- **`author`** — ponlo en `gromovyna` (la única clave de autor registrada) siempre que se use **algo** de su
  material, aunque sea parcialmente. Genera una tarjeta de crédito destacada al final de la página.
- **`original`** — la lista de URL **exactas** a partir de las que se elaboró la página. Obligatorio siempre que se
  haya usado una fuente.
- **`sources`** — las claves de todas las fuentes usadas (véase más abajo). Obligatorio en toda página de
  contenido, incluidas las páginas índice de sección.

Mantén el **mismo frontmatter en todos los idiomas**: traducir una página no cambia a quién se acredita.

## Los créditos son obligatorios

Si una página usa *cualquier* fuente —un artículo, una publicación de un canal, documentación o código del
firmware—, debe acreditarla. El bloque de créditos del final de cada página se genera a partir del frontmatter
anterior. Las claves de fuente válidas están definidas en `docs/.vitepress/sources.ts`; las claves actuales son:

| Clave | Fuente |
|---|---|
| `gromovyna` | Artículos y canal de @gromovyna |
| `how2flipper` | Canal @how2flipper_rus |
| `flipper-docs` | docs.flipper.net |
| `unleashed-docs` | Documentación de Unleashed |
| `unleashed-readme` | ReadMe de Unleashed |
| `unleashed-src` | Código fuente del firmware Unleashed |
| `li0ard` | Blog de li0ard |

Elaborar una página a partir del código del firmware cuenta como usar una fuente: añade `unleashed-src` a
`sources` y pon el directorio de GitHub correspondiente en `original`.

Cómo se forman las URL de `original`:

- **Documentación de Flipper** — `https://docs.flipper.net/zero/<path>` (así, `zero_nfc_read.md` → `/zero/nfc/read`).
- **Documentación de Unleashed** —
  `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/<File>.md` (los espacios como `%20`).
- **ReadMe** — `https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md`.
- **gromovyna** — la URL de `telegra.ph` del artículo y/o `https://t.me/gromovyna/<id>`.
- **how2flipper** — `https://t.me/how2flipper_rus/<id>`.

## Estilo de redacción

- Una guía de verdad, no una copia. Reescribe con tus palabras, fusiona las fuentes que se solapen, reestructura
  pensando en quien lee.
- Sé **Unleashed-first**: cuando Unleashed se comporte de forma distinta al firmware de serie, dilo con un cuadro
  `::: tip Unleashed`.
- Cada página de función: qué es → cuándo usarlo → pasos numerados con las rutas de menú exactas
  (`Main Menu → Sub-GHz → Read`), los botones como `<kbd>OK</kbd>`, resultados esperados, resolución de problemas,
  enlaces relacionados.
- Conserva los datos técnicos exactos: frecuencias, formatos de archivo, rutas como `/ext/subghz/`, comandos de la
  CLI, nombres de protocolos, números de versión. No inventes funciones: si no estás seguro, déjalo fuera.
- Usa los contenedores de VitePress: `::: tip`, `::: warning`, `::: danger`, `::: details`. El único HTML en bruto
  permitido es `<kbd>`; nada de componentes de Vue.
- Los enlaces internos son absolutos y sin extensión: `/nfc/mfkey` en inglés, `/ru/nfc/mfkey` en ruso. Enlaza solo
  a páginas que existan.

## Añadir una página

1. Crea `docs/<section>/<page>.md` con su frontmatter y su contenido.
2. Crea el equivalente en **todos** los demás idiomas en la misma ruta (por ejemplo, `docs/ru/<section>/<page>.md`).
3. Añádela a la lista del `index.md` de la sección.
4. Ejecuta `npm run check` para confirmar que no falta en ningún idioma y después `npx vitepress build docs` para
   detectar enlaces rotos (se informan como errores de compilación).

La barra lateral se genera automáticamente a partir de los archivos y su `order`, así que no hay ninguna lista de
barra lateral que editar.

## Capturas de la pantalla del dispositivo

Las pantallas del Flipper que hay en `/screens/…` están **generadas, no capturadas**. `npm run screens` compila el
propio código de la GUI del firmware (el canvas, `gui/modules/*` y las vistas de las aplicaciones) y renderiza cada
pantalla en `docs/public/screens/<section>/<name>.png`. El resultado es idéntico píxel a píxel a una captura de
qFlipper: el mismo marco de 128x64, los mismos dos colores, escalado ×4. El renderizador está en
`scripts/screens/`; su `README.md` explica los requisitos, de dónde sale el checkout del firmware y cómo se deriva
el formato de salida del código de qFlipper.

Para añadir una pantalla nueva:

1. Escribe un bloque `SCREEN(...)` en `scripts/screens/specs/<section>.c`. Construye la vista exactamente como lo
   hace la escena de la aplicación (`submenu_add_item`, `widget_add_*`, `popup_set_*`, los setters propios de la
   vista) con datos de ejemplo realistas.
2. Ejecuta `npm run screens` (o `bash scripts/screens/build.sh --only <section>/` para una sola sección).
3. Referencia el PNG desde la página: `![alt text](/screens/<section>/<name>.png)`. La ruta es **idéntica en todos
   los idiomas**; solo se traduce el texto alternativo.

Coloca cada captura junto al paso o la pantalla que ilustra, no en una galería al principio de la página, y no
pongas más de unas pocas por página. `docs/public/screens/manifest.json` lista todas las pantallas generadas con su
título, su ruta de menú y la escena del firmware de la que proviene el estado de ejemplo.

## Añadir un idioma nuevo

El registro de idiomas está en `docs/.vitepress/i18n/`. Para añadir el idioma `xx`:

1. **Copia las cadenas.** Copia `docs/.vitepress/i18n/en.ts` a `docs/.vitepress/i18n/xx.ts` y traduce todas las
   cadenas. Pon `prefix: 'xx'` (ese será el prefijo de URL `/xx/`).
2. **Regístralo.** En `docs/.vitepress/i18n/index.ts`, importa tu archivo y añádelo al array `LOCALES`.
3. **Crea las páginas.** Crea `docs/xx/` como espejo de `docs/` —los mismos nombres y rutas de archivo— y traduce
   cada página. Mantén el frontmatter idéntico (el mismo `author`, `original`, `sources`).
4. **Comprueba.** Ejecuta `npm run check` para ver qué páginas faltan en el idioma nuevo, rellena los huecos y
   compila.

::: tip No hace falta tocar `.vitepress/` para el contenido
Todo lo anterior, salvo *añadir un idioma*, es Markdown puro dentro de `docs/`. La barra lateral, la barra de
navegación y el bloque de créditos se generan solos: no toques `docs/.vitepress/` a menos que vayas a añadir
específicamente un idioma o una clave de fuente.
:::

::: tip Véase también
- [Créditos y agradecimientos](/es/community/credits) — cómo se acreditan las páginas existentes
- [Resumen de la comunidad](/es/community/) — el resto de esta sección
:::
