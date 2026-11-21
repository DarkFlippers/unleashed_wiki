import fs from 'node:fs'
import path from 'node:path'
import type { PageData, SiteConfig } from 'vitepress'
import { LOCALES } from './i18n'

/**
 * Site origin, no trailing slash. Canonical URLs, hreflang, Open Graph and the
 * sitemap all hang off it, and a wrong value is worse for SEO than none at all,
 * so when it is unset those tags are left out and only relative ones remain.
 */
export const SITE_URL = (process.env.UL_SITE_URL || '').replace(/\/+$/, '')

// `preview` and `dev` only load this config, they do not build, so warning
// there would wrongly suggest the built site is missing its tags.
const IS_BUILD = process.argv.includes('build')

if (!SITE_URL && IS_BUILD) {
  console.warn(
    '\n  UL_SITE_URL is not set: building without sitemap.xml, canonical links,\n' +
    '  hreflang or Open Graph tags. Set it to the public origin, e.g.\n' +
    '      UL_SITE_URL=https://wiki.example.com npm run build\n'
  )
}

const PREFIXES = LOCALES.map((l) => l.prefix).filter(Boolean)

/** 'ru/subghz/read.md' -> { prefix: 'ru', rest: 'subghz/read.md' } */
function splitLocale(relativePath: string) {
  const seg = relativePath.split('/')[0]
  return PREFIXES.includes(seg)
    ? { prefix: seg, rest: relativePath.slice(seg.length + 1) }
    : { prefix: '', rest: relativePath }
}

/** Site-relative clean URL of a page: 'subghz/read.md' in 'ru' -> '/ru/subghz/read' */
function urlOf(prefix: string, rest: string) {
  const clean = rest.replace(/(?:^|(?<=\/))index\.md$/, '').replace(/\.md$/, '')
  return '/' + (prefix ? prefix + '/' : '') + clean
}

/** BCP-47 language subtag for hreflang: 'uk-UA' -> 'uk'. */
const hreflangOf = (l: (typeof LOCALES)[number]) => l.lang.split('-')[0]

/**
 * First real paragraph of a page, flattened to plain text for the meta
 * description. Headings, containers, tables, lists, images and code are
 * skipped: the goal is the one sentence that says what the page is.
 */
function describe(file: string): string {
  let raw: string
  try {
    raw = fs.readFileSync(file, 'utf8')
  } catch {
    return ''
  }
  raw = raw.replace(/^---\r?\n[\s\S]*?\r?\n---\r?\n?/, '')
  const parts: string[] = []
  for (const line of raw.split(/\r?\n/)) {
    const t = line.trim()
    const skip =
      !t ||
      t.startsWith('#') ||
      t.startsWith(':::') ||
      t.startsWith('|') ||
      t.startsWith('>') ||
      t.startsWith('```') ||
      t.startsWith('<') ||
      t.startsWith('![') ||
      /^(?:[-*+]|\d+\.)\s/.test(t)
    if (skip) {
      if (parts.length) break // the paragraph ended
      continue
    }
    parts.push(t)
    if (parts.join(' ').length > 220) break
  }
  const text = parts
    .join(' ')
    .replace(/!\[[^\]]*\]\([^)]*\)/g, '')
    .replace(/\[([^\]]*)\]\([^)]*\)/g, '$1')
    .replace(/<\/?kbd>/g, '')
    .replace(/<[^>]+>/g, '')
    .replace(/[`*_]/g, '')
    .replace(/\{#[\w-]+\}/g, '')
    .replace(/\s+/g, ' ')
    .trim()
  // These land inside content="..." and VitePress does not escape head values,
  // so a straight quote would end the attribute and swallow the rest.
  const safe = text
    .replace(/"([^"]*)"/g, '\u201c$1\u201d')
    .replace(/"/g, '\u201d')
    .replace(/[<>]/g, '')
    .replace(/&/g, '&amp;')
    .replace(/\s+/g, ' ')
    .trim()
  if (safe.length <= 160) return safe
  return safe.slice(0, 157).replace(/[\s,;:.!?-]+\S*$/, '') + '…'
}

/**
 * Per-page SEO head tags: meta description, canonical, the hreflang set for
 * every language that actually has the page, and Open Graph / Twitter cards.
 */
export function seoHead(pageData: PageData, config: SiteConfig) {
  const srcDir = config.srcDir
  const { prefix, rest } = splitLocale(pageData.relativePath)
  const locale = LOCALES.find((l) => l.prefix === prefix) ?? LOCALES[0]

  // VitePress renders pageData.description as <meta name="description">.
  if (!pageData.description || pageData.description === config.site.description) {
    pageData.description =
      pageData.frontmatter.description ||
      describe(path.join(srcDir, pageData.relativePath)) ||
      locale.description
  }

  const head: NonNullable<PageData['frontmatter']['head']> = []
  if (!SITE_URL) return head

  const canonical = SITE_URL + urlOf(prefix, rest)
  head.push(['link', { rel: 'canonical', href: canonical }])

  // hreflang only for languages that really have this page, so a missing
  // translation is never advertised. x-default points at English.
  for (const l of LOCALES) {
    const file = path.join(srcDir, l.prefix ? `${l.prefix}/${rest}` : rest)
    if (fs.existsSync(file)) {
      head.push(['link', { rel: 'alternate', hreflang: hreflangOf(l), href: SITE_URL + urlOf(l.prefix, rest) }])
    }
  }
  head.push(['link', { rel: 'alternate', hreflang: 'x-default', href: SITE_URL + urlOf('', rest) }])

  const title = pageData.title ? `${pageData.title} · ${locale.title}` : locale.title
  head.push(
    ['meta', { property: 'og:type', content: 'article' }],
    ['meta', { property: 'og:site_name', content: locale.title }],
    ['meta', { property: 'og:title', content: title }],
    ['meta', { property: 'og:description', content: pageData.description }],
    ['meta', { property: 'og:url', content: canonical }],
    ['meta', { property: 'og:image', content: SITE_URL + '/og.png' }],
    ['meta', { property: 'og:image:width', content: '1200' }],
    ['meta', { property: 'og:image:height', content: '630' }],
    ['meta', { property: 'og:locale', content: locale.lang.replace('-', '_') }],
    ['meta', { name: 'twitter:card', content: 'summary_large_image' }],
    ['meta', { name: 'twitter:title', content: title }],
    ['meta', { name: 'twitter:description', content: pageData.description }],
    ['meta', { name: 'twitter:image', content: SITE_URL + '/og.png' }]
  )
  return head
}

/**
 * robots.txt, written at build time so it always names the configured host.
 * Without UL_SITE_URL there is no absolute sitemap URL to advertise, so the
 * file still allows everything but omits the Sitemap line.
 */
export function writeRobots(outDir: string) {
  const lines = ['User-agent: *', 'Allow: /', '']
  if (SITE_URL) lines.push(`Sitemap: ${SITE_URL}/sitemap.xml`, '')
  fs.writeFileSync(path.join(outDir, 'robots.txt'), lines.join('\n'))
}
