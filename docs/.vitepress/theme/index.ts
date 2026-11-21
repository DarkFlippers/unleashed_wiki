import DefaultTheme from 'vitepress/theme'
import { h } from 'vue'
import type { EnhanceAppContext } from 'vitepress'
import Credits from './components/Credits.vue'
import MachineTranslated from './components/MachineTranslated.vue'
import NotFoundRedirect from './components/NotFoundRedirect.vue'
import { LOCALES } from '../i18n'
import './style.css'

const PREFIXES = LOCALES.map((l) => l.prefix).filter(Boolean) as string[]

/** Language of a path: the first segment when it is a known prefix, else 'en'. */
function langOf(path: string) {
  const seg = path.split('/')[1]
  return PREFIXES.includes(seg) ? seg : 'en'
}

/**
 * Remembers the language the visitor is actually reading, so the redirect in
 * `config.mts` respects a manual choice from the language menu and stops
 * guessing from the browser.
 */
function rememberLanguage() {
  if (typeof window === 'undefined') return
  try {
    localStorage.setItem('ul-lang', langOf(location.pathname))
  } catch {
    /* private mode: preference just isn't remembered */
  }
}

export default {
  extends: DefaultTheme,
  Layout() {
    return h(DefaultTheme.Layout, null, {
      'doc-before': () => h(MachineTranslated),
      'doc-after': () => h(Credits),
      'not-found': () => h(NotFoundRedirect)
    })
  },
  enhanceApp({ router }: EnhanceAppContext) {
    if (typeof window === 'undefined') return
    rememberLanguage()
    const onChange = router.onAfterRouteChanged
    router.onAfterRouteChanged = (to) => {
      rememberLanguage()
      onChange?.(to)
    }
  }
}
