import type { LocaleStrings } from './types'
export default {
  code: 'ru', lang: 'ru-RU', label: 'Русский', prefix: 'ru',
  title: 'Unleashed Wiki',
  description: 'Самая полная вики по Flipper Zero и прошивке Unleashed',
  sections: {
    start: 'Начало работы', subghz: 'Sub-GHz', nfc: 'NFC', rfid: 'RFID 125 кГц',
    infrared: 'Инфракрасный порт', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO и модули',
    apps: 'Приложения', mobile: 'qFlipper и мобильное приложение', dev: 'Разработка', community: 'Сообщество'
  },
  nav: { home: 'Главная', guide: 'Вики', download: 'Скачать Unleashed' },
  ui: {
    outline: 'На этой странице', prev: 'Предыдущая страница', next: 'Следующая страница',
    lastUpdated: 'Обновлено', darkMode: 'Оформление', menu: 'Меню', toTop: 'Наверх',
    langMenu: 'Сменить язык', search: 'Поиск', editLink: 'Предложить правку',
    notFound: 'Страница не найдена', notFoundLink: 'На главную'
  },
  credits: {
    authorTitle: 'Автор оригинального материала',
    original: "Оригинальные источники",
    basedOn: 'Источники',
    channel: 'Telegram-канал',
    thanks: 'Огромное спасибо {name} за исследования и статьи, на которых основана эта страница.'
  },
  footer: 'Проект не связан с Flipper Devices. Только для образовательного и законного использования.'
} satisfies LocaleStrings
