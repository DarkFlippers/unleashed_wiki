import type { LocaleStrings } from './types'
export default {
  code: 'fr', lang: 'fr-FR', label: 'Français', prefix: 'fr',
  title: 'Unleashed Wiki',
  description: 'Le wiki de référence sur le Flipper Zero et le firmware Unleashed',
  sections: {
    start: 'Démarrage', subghz: 'Sub-GHz', nfc: 'NFC', rfid: 'RFID 125 kHz',
    infrared: 'Infrarouge', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO et modules',
    apps: 'Applications', mobile: 'qFlipper et mobile', dev: 'Développement', community: 'Communauté'
  },
  nav: { home: 'Accueil', guide: 'Wiki', download: 'Télécharger Unleashed' },
  ui: {
    outline: 'Sur cette page', prev: 'Page précédente', next: 'Page suivante',
    lastUpdated: 'Dernière mise à jour', darkMode: 'Apparence', menu: 'Menu', toTop: 'Retour en haut',
    langMenu: 'Changer de langue', search: 'Rechercher', editLink: 'Proposer une modification',
    notFound: 'Page introuvable', notFoundLink: "Retour à l'accueil"
  },
  credits: {
    authorTitle: 'Auteur du contenu original',
    original: 'Sources originales',
    basedOn: 'Basé sur',
    channel: 'Chaîne Telegram',
    thanks: 'Un grand merci à {name} pour les recherches et les articles sur lesquels repose cette page.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Traduction automatique',
    text: "Cette page a été traduite automatiquement depuis l'anglais et peut contenir des erreurs ou des imprécisions techniques. En cas de doute, reportez-vous à la version anglaise ou russe.",
    help: 'Vous avez repéré une erreur ? Les corrections sont les bienvenues.'
  },
  footer: 'Sans lien avec Flipper Devices. Pour un usage pédagogique et légal uniquement.'
} satisfies LocaleStrings
