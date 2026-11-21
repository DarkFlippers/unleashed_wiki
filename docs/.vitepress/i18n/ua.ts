import type { LocaleStrings } from './types'
export default {
  code: 'ua', lang: 'uk-UA', label: 'Українська', prefix: 'ua',
  title: 'Unleashed Wiki',
  description: 'Найповніша вікі про Flipper Zero та прошивку Unleashed',
  sections: {
    start: 'Початок роботи', subghz: 'Sub-GHz', nfc: 'NFC', rfid: 'RFID 125 кГц',
    infrared: 'Інфрачервоний порт', ibutton: 'iButton', badusb: 'Bad USB', gpio: 'GPIO та модулі',
    apps: 'Застосунки', mobile: 'qFlipper і мобільний застосунок', dev: 'Розробка', community: 'Спільнота'
  },
  nav: { home: 'Головна', guide: 'Вікі', download: 'Завантажити Unleashed' },
  ui: {
    outline: 'На цій сторінці', prev: 'Попередня сторінка', next: 'Наступна сторінка',
    lastUpdated: 'Оновлено', darkMode: 'Оформлення', menu: 'Меню', toTop: 'Угору',
    langMenu: 'Змінити мову', search: 'Пошук', editLink: 'Запропонувати правку',
    notFound: 'Сторінку не знайдено', notFoundLink: 'На головну'
  },
  credits: {
    authorTitle: 'Автор оригінального матеріалу',
    original: 'Оригінальні джерела',
    basedOn: 'Джерела',
    channel: 'Telegram-канал',
    thanks: 'Величезна подяка {name} за дослідження та статті, на яких ґрунтується ця сторінка.'
  },
  machineTranslated: true,
  mtNotice: {
    title: 'Автоматичний переклад',
    text: 'Цю сторінку перекладено автоматично з англійської, тож вона може містити помилки або технічні неточності. Якщо сумніваєтесь — звіряйтеся з англійською чи російською версією.',
    help: 'Помітили помилку? Будемо вдячні за виправлення.'
  },
  footer: 'Проєкт не пов’язаний з Flipper Devices. Лише для освітнього та законного використання.'
} satisfies LocaleStrings
