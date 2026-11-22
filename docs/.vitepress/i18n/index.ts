// ── LANGUAGE REGISTRY ───────────────────────────────────────────
// To add a language:
//   1. copy en.ts → xx.ts and translate the strings (set prefix: 'xx')
//   2. import it below and append to LOCALES
//   3. create docs/xx/ mirroring docs/ (same file names), translate pages
//   4. run `npm run check` to list missing pages
import en from './en'
import ru from './ru'
import it from './it'
import es from './es'
import de from './de'
import fr from './fr'
import ua from './ua'
import hr from './hr'
export const LOCALES = [en, ru, ua, de, fr, es, it, hr]
export type { LocaleStrings } from './types'
