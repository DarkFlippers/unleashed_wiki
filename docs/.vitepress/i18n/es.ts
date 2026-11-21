import type { LocaleStrings } from './types'
export default {
  code: 'es', lang: 'es-ES', label: 'Español', prefix: 'es',
  title: 'Unleashed Wiki',
  description: 'La wiki definitiva sobre Flipper Zero y el firmware Unleashed',
  sections: {
    start: 'Primeros pasos', subghz: 'Sub-GHz', nfc: 'NFC', rfid: 'RFID 125 kHz',
    infrared: 'Infrarrojos', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO y módulos',
    apps: 'Aplicaciones', mobile: 'qFlipper y móvil', dev: 'Desarrollo', community: 'Comunidad'
  },
  nav: { home: 'Inicio', guide: 'Wiki', download: 'Descargar Unleashed' },
  ui: {
    outline: 'En esta página', prev: 'Página anterior', next: 'Página siguiente',
    lastUpdated: 'Última actualización', darkMode: 'Apariencia', menu: 'Menú', toTop: 'Volver arriba',
    langMenu: 'Cambiar idioma', search: 'Buscar', editLink: 'Sugerir un cambio',
    notFound: 'Página no encontrada', notFoundLink: 'Ir al inicio'
  },
  credits: {
    authorTitle: 'Autor del material original',
    original: 'Fuentes originales',
    basedOn: 'Basado en',
    channel: 'Canal de Telegram',
    thanks: 'Muchísimas gracias a {name} por la investigación y los artículos en los que se basa esta página.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Traducción automática',
    text: 'Esta página se ha traducido automáticamente del inglés y puede contener errores o imprecisiones técnicas. Ante la duda, consulta la versión en inglés o en ruso.',
    help: '¿Has encontrado un fallo? Las correcciones son bienvenidas.'
  },
  footer: 'Sin afiliación con Flipper Devices. Solo para uso educativo y lícito.'
} satisfies LocaleStrings
