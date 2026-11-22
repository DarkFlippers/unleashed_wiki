import type { LocaleStrings } from './types'
export default {
  code: 'hr', lang: 'hr-HR', label: 'Hrvatski', prefix: 'hr',
  title: 'Unleashed Wiki',
  description: 'Potpuni vodič za Flipper Zero i Unleashed Firmware',
  sections: {
    start: 'Početak rada', subghz: 'Sub-GHz', nfc: 'NFC', rfid: '125 kHz RFID',
    infrared: 'Infracrveno', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO i moduli',
    apps: 'Aplikacije', mobile: 'qFlipper i mobilno', dev: 'Razvoj', community: 'Zajednica'
  },
  nav: { home: 'Početna', guide: 'Wiki', download: 'Preuzmi Unleashed' },
  ui: {
    outline: 'Na ovoj stranici', prev: 'Prethodna stranica', next: 'Sljedeća stranica',
    lastUpdated: 'Zadnje ažurirano', darkMode: 'Izgled', menu: 'Izbornik', toTop: 'Natrag na vrh',
    langMenu: 'Promijeni jezik', search: 'Pretraži', editLink: 'Predloži izmjenu',
    notFound: 'Stranica nije pronađena', notFoundLink: 'Na početnu'
  },
  credits: {
    authorTitle: 'Autor izvornog materijala',
    original: 'Izvorni članci',
    basedOn: 'Temeljeno na',
    channel: 'Telegram kanal',
    thanks: 'Velika hvala {name} na istraživanju i člancima na kojima se temelji ova stranica.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Strojni prijevod',
    text: 'Ova je stranica automatski prevedena s engleskog i može sadržavati pogreške ili tehničke nepreciznosti. U slučaju nedoumice provjerite englesku ili rusku verziju.',
    help: 'Pronašli ste pogrešku? Ispravci su dobrodošli.'
  },
  footer: 'Nije povezano s Flipper Devices. Samo za edukativnu i zakonitu upotrebu.'
} satisfies LocaleStrings
