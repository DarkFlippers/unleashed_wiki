import { defineConfig, type DefaultTheme, type LocaleConfig } from 'vitepress'
import { LOCALES } from './i18n'
import { buildSidebar } from './sidebar'
import { SITE_URL, seoHead, writeRobots } from './seo'

const REPO = 'https://github.com/DarkFlippers/unleashed-firmware'

function themeFor(l: typeof LOCALES[number]): DefaultTheme.Config {
  const base = l.prefix ? `/${l.prefix}/` : '/'
  return {
    nav: [
      { text: l.nav.guide, link: `${base}start/` },
      { text: l.nav.download, link: 'https://github.com/DarkFlippers/unleashed-firmware/releases' }
    ],
    sidebar: { [base]: buildSidebar(l) },
    outline: { level: [2, 3], label: l.ui.outline },
    docFooter: { prev: l.ui.prev, next: l.ui.next },
    lastUpdated: { text: l.ui.lastUpdated },
    darkModeSwitchLabel: l.ui.darkMode,
    sidebarMenuLabel: l.ui.menu,
    returnToTopLabel: l.ui.toTop,
    langMenuLabel: l.ui.langMenu,
    notFound: { title: l.ui.notFound, linkText: l.ui.notFoundLink, linkLabel: l.ui.notFoundLink, quote: '' },
    footer: { message: l.footer, copyright: 'Unleashed Wiki · community project' }
  }
}

const locales: LocaleConfig<DefaultTheme.Config> = {}
for (const l of LOCALES) {
  locales[l.prefix || 'root'] = {
    label: l.label, lang: l.lang, title: l.title, description: l.description,
    ...(l.prefix ? { link: `/${l.prefix}/` } : {}),
    themeConfig: themeFor(l)
  }
}

// Runs before the page renders: sends a visitor to the version matching their
// browser language, unless they have already picked a language themselves.
// `en` lives at the root, so an English-speaking visitor is never redirected.
// A loop guard in sessionStorage stops it bouncing when a page is missing in
// that language (the 404 handler in the theme sends those back to English).
const PREFIXES = LOCALES.map((l) => l.prefix).filter(Boolean)
const LANG_REDIRECT = `(function(){try{
var P=${JSON.stringify(PREFIXES)},p=location.pathname,s=p.split('/')[1];
if(P.indexOf(s)!==-1)return;
var saved=null;try{saved=localStorage.getItem('ul-lang')}catch(e){}
if(saved==='en')return;
var t=saved&&P.indexOf(saved)!==-1?saved:null;
if(!t){var L=navigator.languages||[navigator.language||''];
for(var i=0;i<L.length;i++){var x=String(L[i]).toLowerCase(),b=x.split('-')[0],r=x.split('-')[1];
if(b==='en')return;
if(b==='uk'||(b==='ru'&&r==='ua')){t='ua';break}
if(P.indexOf(b)!==-1){t=b;break}}}
if(!t)return;
var d='/'+t+(p==='/'?'/':p),k='ul-rd:'+d;
try{if(sessionStorage.getItem(k))return;sessionStorage.setItem(k,'1')}catch(e){}
location.replace(d+location.search+location.hash)}catch(e){}})()`

export default defineConfig({
  cleanUrls: true,
  // Absolute URLs need the real origin: set UL_SITE_URL to enable the sitemap,
  // canonical links, hreflang and Open Graph tags.
  ...(SITE_URL ? { sitemap: { hostname: SITE_URL } } : {}),
  transformPageData(pageData, ctx) {
    const head = seoHead(pageData, ctx.siteConfig)
    if (head.length) pageData.frontmatter.head = [...(pageData.frontmatter.head ?? []), ...head]
  },
  buildEnd(siteConfig) {
    writeRobots(siteConfig.outDir)
  },
  // Set UL_SKIP_LINKCHECK=1 to build while a translation is still in progress.
  ignoreDeadLinks: !!process.env.UL_SKIP_LINKCHECK,
  lastUpdated: false,
  appearance: 'force-dark',
  head: [
    ['link', { rel: 'icon', href: '/favicon.ico', sizes: 'any' }],
    ['link', { rel: 'icon', href: '/favicon.png', type: 'image/png' }],
    ['link', { rel: 'apple-touch-icon', href: '/apple-touch-icon.png' }],
    ['meta', { name: 'theme-color', content: '#e0151b' }],
    ['meta', { name: 'robots', content: 'index, follow, max-image-preview:large' }],
    ['script', {}, LANG_REDIRECT]
  ],
  locales,
  markdown: { image: { lazyLoading: true } },
  themeConfig: {
    logo: '/logo.png',
    siteTitle: 'Unleashed Wiki',
    socialLinks: [
      { icon: 'github', link: REPO },
      { icon: 'discord', link: 'https://discord.unleashedflip.com' },
      { icon: { svg: '<svg viewBox="0 0 24 24"><path fill="currentColor" d="M9.78 18.65l.28-4.23 7.68-6.92c.34-.31-.07-.46-.52-.19L7.74 13.3 3.64 12c-.88-.25-.89-.86.2-1.3l15.97-6.16c.73-.33 1.43.18 1.15 1.3l-2.72 12.81c-.19.91-.74 1.13-1.5.71L12.6 16.3l-1.99 1.93c-.23.23-.42.42-.83.42z"/></svg>' }, link: 'https://t.me/unleashed_fw', ariaLabel: 'Telegram' }
    ],
    search: {
      provider: 'local',
      options: {
        locales: Object.fromEntries(LOCALES.map((l) => [l.prefix || 'root', {
          translations: { button: { buttonText: l.ui.search, buttonAriaLabel: l.ui.search } }
        }]))
      }
    }
  }
})
