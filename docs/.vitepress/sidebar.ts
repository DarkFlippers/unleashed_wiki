// Auto-generates the sidebar from the file system.
// Page order inside a section = frontmatter `order` (then title).
// Section index page = <section>/index.md.
import fs from 'node:fs'
import path from 'node:path'
import { SECTIONS } from './i18n/sections'
import type { LocaleStrings } from './i18n'

const DOCS = path.resolve(__dirname, '..')

function front(file: string): Record<string, string> {
  const src = fs.readFileSync(file, 'utf8')
  const m = src.match(/^---\r?\n([\s\S]*?)\r?\n---/)
  const fm: Record<string, string> = {}
  if (m) for (const line of m[1].split(/\r?\n/)) {
    const kv = line.match(/^(\w+):\s*(.*)$/)
    if (kv) fm[kv[1]] = kv[2].replace(/^['"]|['"]$/g, '')
  }
  if (!fm.title) fm.title = (src.match(/^#\s+(.+)$/m) || [])[1] || path.basename(file, '.md')
  return fm
}

export function buildSidebar(loc: LocaleStrings) {
  const base = loc.prefix ? `/${loc.prefix}/` : '/'
  return SECTIONS.flatMap((sec) => {
    const dir = path.join(DOCS, loc.prefix, sec)
    if (!fs.existsSync(dir)) return []
    const pages = fs.readdirSync(dir)
      .filter((f) => f.endsWith('.md') && f !== 'index.md')
      .map((f) => ({ f, fm: front(path.join(dir, f)) }))
      .filter((p) => p.fm.sidebar !== 'false')
      .sort((a, b) => (+a.fm.order || 999) - (+b.fm.order || 999) || a.fm.title.localeCompare(b.fm.title))
      .map((p) => ({ text: p.fm.sidebarTitle || p.fm.title, link: `${base}${sec}/${p.f.replace(/\.md$/, '')}` }))
    const hasIndex = fs.existsSync(path.join(dir, 'index.md'))
    return [{
      text: loc.sections[sec], collapsed: false,
      ...(hasIndex ? { link: `${base}${sec}/` } : {}),
      items: pages
    }]
  })
}
