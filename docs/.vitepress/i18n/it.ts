import type { LocaleStrings } from './types'
export default {
  code: 'it', lang: 'it-IT', label: 'Italiano', prefix: 'it',
  title: 'Unleashed Wiki',
  description: 'La wiki definitiva su Flipper Zero e il firmware Unleashed',
  sections: {
    start: 'Primi passi', subghz: 'Sub-GHz', nfc: 'NFC', rfid: 'RFID 125 kHz',
    infrared: 'Infrarossi', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO e moduli',
    apps: 'App', mobile: 'qFlipper e mobile', dev: 'Sviluppo', community: 'Comunità'
  },
  nav: { home: 'Home', guide: 'Wiki', download: 'Scarica Unleashed' },
  ui: {
    outline: 'In questa pagina', prev: 'Pagina precedente', next: 'Pagina successiva',
    lastUpdated: 'Ultimo aggiornamento', darkMode: 'Aspetto', menu: 'Menu', toTop: 'Torna su',
    langMenu: 'Cambia lingua', search: 'Cerca', editLink: 'Proponi una modifica',
    notFound: 'Pagina non trovata', notFoundLink: 'Torna alla home'
  },
  credits: {
    authorTitle: 'Autore del materiale originale',
    original: 'Fonti originali',
    basedOn: 'Basato su',
    channel: 'Canale Telegram',
    thanks: 'Un enorme grazie a {name} per le ricerche e gli articoli su cui si basa questa pagina.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Traduzione automatica',
    text: "Questa pagina è stata tradotta automaticamente dall'inglese e può contenere errori o imprecisioni tecniche. In caso di dubbio consulta la versione inglese o russa.",
    help: 'Hai trovato un errore? I contributi sono benvenuti.'
  },
  footer: 'Non affiliato a Flipper Devices. Solo per uso didattico e lecito.'
} satisfies LocaleStrings
