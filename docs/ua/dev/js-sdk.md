---
title: "JavaScript: SDK і TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Розробка застосунків з JavaScript SDK

Копіювати скрипт на пристрій через qFlipper після кожної зміни швидко набридає. **Flipper Zero JavaScript SDK** — набір інструментів, який прибирає ці кроки:

- **одна команда** (`npm start`) збирає застосунок, надсилає його на пристрій і запускає;
- **автодоповнення коду** й перевірка типів (ви пишете на TypeScript);
- необов’язковий **мініфікатор JS**.

::: tip Unleashed
В Unleashed є власний форк SDK: **`@darkflippers/fz-sdk-ul`**, проєкт створюється через **`@darkflippers/create-fz-app-ul`**. Він додає типи для [модулів, які є лише в Unleashed](/ua/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`, `spi`, `vgm`), і для додаткових представлень GUI. Скрипти, написані під офіційний SDK (`@flipperdevices/fz-sdk`), в Unleashed також працюють. Якщо ви користуєтеся розширеннями Unleashed, захищайте їх перевіркою `doesSdkSupport([...])`, щоб застосунок працював і на інших прошивках, або викликайте `checkSdkFeatures([...])` на старті, якщо без цієї можливості застосунок не має сенсу.
:::

## Встановлення SDK

SDK постачається як NPM-пакет, тому потрібен **Node.js** із менеджером пакетів (npm, pnpm або yarn). У цьому посібнику використовується npm.

1. Встановіть **Node.js + npm** зі [офіційної сторінки завантаження](https://nodejs.org/en/download/package-manager).
2. Відкрийте термінал у папці, де хочете тримати проєкт.
3. Створіть проєкт із шаблону. Інтерактивний майстер запитає назву проєкту й менеджер пакетів:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

Тепер папка проєкту містить шаблонний застосунок, пакет SDK, залежності та конфіги. Ваш код пишеться в `index.ts`.

## Запуск застосунку {#run}

1. Підключіть Flipper Zero до комп’ютера через USB.
2. Відкрийте термінал у папці проєкту (`cd my-flip-app`).
3. Виконайте:

```sh
npm start
```

SDK компілює застосунок, копіює файл `.js` на Flipper Zero і запускає його. Вивід `print()` показується в терміналі.

![Вивід npm start](/img/dev/js_sdk_npm_start.jpg)

## Оновлення застосунку

Після зміни коду просто запустіть `npm start` знову. Поки Flipper підключений, старий файл `.js` на пристрої буде замінено й запуститься нова версія.

## Конфігурація: `fz-sdk.config.json5`

Шаблонний конфіг (Unleashed SDK) має такий вигляд:

```js
{
    build: {
        // Where to put the compiled file
        output: "dist/<app_name>.js",

        // Whether to reduce the final file size at the cost of readability and
        // clarity of error messages
        minify: false,

        // Set this to `false` if you've thoroughly read the documentation and
        // are sure that you can use manual version checks to your advantage
        enforceSdkVersion: true,
    },

    upload: {
        // Where to grab the file from. If you're not doing any extra processing
        // after the SDK, this should match `build.output`
        input: "dist/<app_name>.js",

        // Where to put the file on the device
        output: "/ext/apps/Scripts/<app_name>.js",
    },
}
```

### Автодоповнення коду

Редактори з підтримкою Language Server (наприклад, [VS Code](https://code.visualstudio.com/)) підказують функції модулів і їхні параметри прямо під час набору, тож зазирати в документацію доводиться рідко.

![Автодоповнення коду у VS Code](/img/dev/js_sdk_code_completion.jpg)

### Мініфікатор JS

Мініфікатор прибирає пробіли, табуляції та переноси рядків і скорочує назви змінних. Скрипт стає меншим і може працювати трохи швидше, але повідомлення про помилки читати стає значно важче. Тому він **типово вимкнений**. Щоб його увімкнути, вкажіть `minify: true` у `fz-sdk.config.json5`.

## Відмінності від звичайного Flipper JS

З SDK ви пишете на **TypeScript**: краще автодоповнення й попередження про типи, але код виглядає трохи інакше.

- **Імпорт модулів**
  - звичайний JS: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (в Unleashed SDK: `"@darkflippers/fz-sdk-ul/module"`)
- **Кілька файлів з кодом.** SDK поки що не підтримує кілька файлів `.ts`, які імпортують один одного. Можна користуватися `load()`, але вже без перевірки типів.
- **Приведення значень.** Деякі функції повертають узагальнені типи. Наприклад, `eventLoop.subscribe()` викликає ваш колбек з узагальненим `Item`. За потреби приведіть його до потрібного типу:
  - вбудовано: `<string>item`
  - через нову змінну: `let text = item as string;`

`npm start` транспілює ваш код у звичайний JavaScript (і мініфікує, якщо це увімкнено). Готовий файл `.js` у `dist/` — саме те, що ви передаєте іншим людям.

## Пов’язані сторінки

- [Ваш перший JS-застосунок](/ua/dev/js-first-app)
- [Використання JS-модулів](/ua/dev/js-modules)
- [Вбудовані функції: сумісність SDK](/ua/dev/js-builtin#sdk-compatibility)
