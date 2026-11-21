import type { LocaleStrings } from './types'
export default {
  code: 'en', lang: 'en-US', label: 'English', prefix: '',
  title: 'Unleashed Wiki',
  description: 'The ultimate Flipper Zero & Unleashed Firmware wiki',
  sections: {
    start: 'Getting Started', subghz: 'Sub-GHz', nfc: 'NFC', rfid: '125 kHz RFID',
    infrared: 'Infrared', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO & Modules',
    apps: 'Apps', mobile: 'qFlipper & Mobile', dev: 'Development', community: 'Community'
  },
  nav: { home: 'Home', guide: 'Wiki', download: 'Download Unleashed' },
  ui: {
    outline: 'On this page', prev: 'Previous page', next: 'Next page',
    lastUpdated: 'Last updated', darkMode: 'Appearance', menu: 'Menu', toTop: 'Return to top',
    langMenu: 'Change language', search: 'Search', editLink: 'Suggest an edit',
    notFound: 'Page not found', notFoundLink: 'Take me home'
  },
  credits: {
    authorTitle: 'Author of the original material',
    original: "Original sources",
    basedOn: 'Based on',
    channel: 'Telegram channel',
    thanks: 'Huge thanks to {name} for the research and articles this page is built on.'
  },
  footer: 'Not affiliated with Flipper Devices. For educational and lawful use only.'
} satisfies LocaleStrings
