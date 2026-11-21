---
title: "JavaScript: SDK и TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Разработка с JavaScript SDK

Копировать скрипт через qFlipper после каждой правки быстро надоедает. **Flipper Zero JavaScript SDK** — набор инструментов, который убирает эту рутину:

- **одна команда** (`npm start`) собирает, загружает и запускает приложение;
- **автодополнение** и проверка типов (пишете на TypeScript);
- необязательный **минификатор JS**.

::: tip Unleashed
У Unleashed свой форк SDK: **`@darkflippers/fz-sdk-ul`**, проект создаётся через **`@darkflippers/create-fz-app-ul`**. В нём есть типы для [модулей, которые есть только в Unleashed](/ru/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`, `spi`, `vgm`), и дополнительных видов GUI. Скрипты для официального SDK (`@flipperdevices/fz-sdk`) тоже работают на Unleashed. Если используете возможности Unleashed, оборачивайте их в `doesSdkSupport([...])`, чтобы приложение работало и на других прошивках, или вызывайте `checkSdkFeatures([...])` в начале, если без фичи никак.
:::

## Установка SDK

SDK распространяется как NPM-пакет, поэтому нужен **Node.js** с менеджером пакетов (npm, pnpm или yarn). Здесь используем npm.

1. Установите **Node.js + npm** с [официальной страницы загрузки](https://nodejs.org/en/download/package-manager).
2. Откройте терминал в папке, где будет лежать проект.
3. Создайте проект из шаблона. Интерактивный мастер спросит имя проекта и менеджер пакетов:

```sh
# official SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (recommended on Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

В папке проекта появятся шаблон приложения, пакет SDK, зависимости и конфиги. Код пишется в `index.ts`.

## Запуск приложения {#run}

1. Подключите Flipper Zero к ПК по USB.
2. Откройте терминал в папке проекта (`cd my-flip-app`).
3. Выполните:

```sh
npm start
```

SDK скомпилирует приложение, скопирует `.js`-файл на Flipper Zero и запустит его. Вывод `print()` отображается в терминале.

![Вывод npm start](/img/dev/js_sdk_npm_start.jpg)

## Обновление приложения

После правок просто снова выполните `npm start`. Пока Flipper подключён, старый `.js`-файл на устройстве заменится и запустится новая версия.

## Настройки: `fz-sdk.config.json5`

Конфиг из шаблона (Unleashed SDK):

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

### Автодополнение

Редакторы с поддержкой Language Server (например, [VS Code](https://code.visualstudio.com/)) подсказывают функции модулей и их параметры прямо при наборе, так что в документацию заглядывать приходится реже.

![Автодополнение в VS Code](/img/dev/js_sdk_code_completion.jpg)

### Минификатор JS

Минификатор убирает пробелы, табуляции и переводы строк и сокращает имена переменных. Скрипт становится меньше и может работать чуть быстрее, но сообщения об ошибках читать гораздо сложнее. Поэтому по умолчанию он **выключен**. Чтобы включить, задайте `minify: true` в `fz-sdk.config.json5`.

## Отличия от обычного Flipper JS

С SDK вы пишете на **TypeScript**: автодополнение и предупреждения о типах лучше, но код выглядит немного иначе.

- **Подключение модулей**
  - обычный JS: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (в Unleashed SDK: `"@darkflippers/fz-sdk-ul/module"`)
- **Несколько файлов.** SDK пока не поддерживает несколько `.ts`-файлов, импортирующих друг друга. Можно использовать `load()`, но без проверки типов.
- **Приведение типов.** Некоторые функции возвращают обобщённые типы. Например, `eventLoop.subscribe()` передаёт в колбэк обобщённый `Item`. При необходимости приведите тип:
  - на месте: `<string>item`
  - через новую переменную: `let text = item as string;`

`npm start` транспилирует код в обычный JavaScript (и минифицирует, если включено). Получившийся `.js` из `dist/` и нужно отдавать другим людям.

## См. также

- [Первое JS-приложение](/ru/dev/js-first-app)
- [Использование модулей](/ru/dev/js-modules)
- [Встроенные функции: совместимость SDK](/ru/dev/js-builtin#sdk-compatibility)
