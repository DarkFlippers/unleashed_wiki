import type { Section } from './sections'
export interface LocaleStrings {
  code: string; lang: string; label: string
  /** URL/folder prefix: '' for the root (English), otherwise e.g. 'ru' */
  prefix: string
  title: string; description: string
  sections: Record<Section, string>
  nav: { home: string; guide: string; download: string }
  ui: Record<'outline'|'prev'|'next'|'lastUpdated'|'darkMode'|'menu'|'toTop'|'langMenu'|'search'|'editLink'|'notFound'|'notFoundLink', string>
  credits: { authorTitle: string; original: string; basedOn: string; channel: string; thanks: string }
  footer: string
  /** Set on locales produced by machine translation: shows a notice banner on every page. */
  machineTranslated?: boolean
  /** Text of that banner. Required when machineTranslated is true. */
  mtNotice?: { title: string; text: string; help: string }
}
