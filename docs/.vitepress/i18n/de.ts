import type { LocaleStrings } from './types'
export default {
  code: 'de', lang: 'de-DE', label: 'Deutsch', prefix: 'de',
  title: 'Unleashed Wiki',
  description: 'Das umfassende Wiki zu Flipper Zero und der Unleashed-Firmware',
  sections: {
    start: 'Erste Schritte', subghz: 'Sub-GHz', nfc: 'NFC', rfid: '125-kHz-RFID',
    infrared: 'Infrarot', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO & Module',
    apps: 'Apps', mobile: 'qFlipper & Mobil', dev: 'Entwicklung', community: 'Community'
  },
  nav: { home: 'Start', guide: 'Wiki', download: 'Unleashed herunterladen' },
  ui: {
    outline: 'Auf dieser Seite', prev: 'Vorherige Seite', next: 'Nächste Seite',
    lastUpdated: 'Zuletzt aktualisiert', darkMode: 'Darstellung', menu: 'Menü', toTop: 'Nach oben',
    langMenu: 'Sprache wechseln', search: 'Suchen', editLink: 'Änderung vorschlagen',
    notFound: 'Seite nicht gefunden', notFoundLink: 'Zur Startseite'
  },
  credits: {
    authorTitle: 'Autor des Originalmaterials',
    original: 'Originalquellen',
    basedOn: 'Basiert auf',
    channel: 'Telegram-Kanal',
    thanks: 'Vielen Dank an {name} für die Recherche und die Artikel, auf denen diese Seite beruht.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Maschinelle Übersetzung',
    text: 'Diese Seite wurde automatisch aus dem Englischen übersetzt und kann Fehler oder technische Ungenauigkeiten enthalten. Im Zweifelsfall ziehe die englische oder russische Fassung heran.',
    help: 'Fehler gefunden? Korrekturen sind willkommen.'
  },
  footer: 'Nicht mit Flipper Devices verbunden. Nur für Bildungszwecke und rechtmäßige Nutzung.'
} satisfies LocaleStrings
