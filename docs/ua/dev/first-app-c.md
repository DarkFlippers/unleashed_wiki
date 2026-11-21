---
title: Перший застосунок на C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Перший застосунок на C

У цьому посібнику ви налаштуєте середовище розробки з **uFBT**, згенеруєте шаблон застосунку, додасте простий
інтерфейс, а потім зберете та запустите застосунок на своєму Flipper Zero.

Застосунки, зібрані таким чином, — це файли `.fap` (Flipper App Package). Вони лежать на картці microSD і
завантажуються на вимогу, тому перезбирати прошивку не потрібно.

## 1. Налаштування середовища

Вам потрібні Flipper Zero, кабель USB і на Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) («micro Flipper Build Tool») — версія
  [fbt](/ua/dev/fbt) з усім необхідним для розробки застосунків. Встановлюється командою `pip install ufbt`
  (подробиці — у README uFBT).
- [**Visual Studio Code**](https://code.visualstudio.com/) — рекомендоване середовище розробки. Інші теж
  працюють, але їх доведеться налаштувати для роботи з uFBT вручну.

::: tip Unleashed
Типово uFBT завантажує **офіційний** SDK. Щоб збирати для Unleashed, один раз виконайте таку команду (і додавайте
ті самі прапорці під час кожного наступного оновлення):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Використовуйте `--channel=release`, якщо на вашому Flipper стоїть релізна збірка. Версія SDK має збігатися з
прошивкою на пристрої — див. [крок 5](#_5-build-and-run-the-app).
:::

## 2. Генерація шаблону застосунку

1. Створіть папку для застосунку, наприклад `test_app`.
2. Відкрийте термінал у цій папці та виконайте:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT згенерує структуру файлів.
3. Виконайте:

   ```sh
   ufbt vscode_dist
   ```

   Це налаштує VS Code так, щоб збирати й налагоджувати застосунок просто з редактора.

::: warning
`APPID` може містити лише малі латинські літери `a-z`, цифри `0-9` та `_`.
:::

Отримана структура:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| Файл | Призначення |
|---|---|
| `application.fam` | Маніфест застосунку, з якого uFBT дізнається, як його збирати — див. [Маніфести застосунків](/ua/dev/app-manifests) |
| `test_app.c` | Головний файл з точкою входу |
| `test_app.png` | Піктограма застосунку (10×10, 1 біт) |
| `.github/workflows/build.yml` | Конфігурація GitHub Actions — [докладніше](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Ваші зображення |
| `images/.gitkeep` | Заповнювач, щоб Git відслідковував порожню папку `images/` |

## 3. Код шаблону

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Що тут за що відповідає:

- `#include <furi.h>` — головний заголовний файл **Furi**, ядра прошивки Flipper ([Furi API](/ua/dev/furi-api)).
- `#include <test_app_icons.h>` — потрібен, якщо застосунок використовує зображення. uFBT перетворює файли PNG з
  `images/` у внутрішній формат Flipper і генерує цей заголовний файл автоматично.
- `int32_t` — звичний тип значення, яке повертає головна функція застосунку.
- `UNUSED(p);` — макрос, що прибирає попередження про невикористаний параметр.
- `FURI_LOG_I` — записує повідомлення рівня `info` до журналу Flipper. Дивитися його можна через `ufbt cli` →
  `log info`.
- `return 0;` — успіх, за традицією мови C.

## 4. Додавання інтерфейсу

Відкрийте папку застосунку у VS Code (**File → Open Folder…**). Коли редактор запропонує розширення, встановіть їх.

Виведемо на екран два рядки: `Hello world` і `I'm test_app!`. Замініть вміст `test_app.c` на такий:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Тут використано службу інтерфейсу **Dialogs** — найпростіший GUI API. Інші підходи описані в
[GUI у застосунках](/ua/dev/gui).

## 5. Збірка та запуск застосунку {#_5-build-and-run-the-app}

**Швидкий спосіб:**

1. Під’єднайте Flipper до комп’ютера кабелем USB.
2. Закрийте qFlipper і будь-яку іншу програму, яка займає послідовний порт Flipper.
3. Виконайте:

   ```sh
   ufbt launch
   ```

   Команда збере застосунок, завантажить його на пристрій і запустить.

**Спосіб вручну:**

1. Зберіть застосунок комбінацією <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) або
   <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (macOS) чи командою `ufbt` у терміналі. Самодостатній `.fap`
   (з усіма ресурсами) з’явиться в папці `dist/`.
2. У qFlipper відкрийте **File Manager → SD Card → apps → Examples** (створіть папку, якщо її немає) і перетягніть
   туди файл `.fap`.
3. На Flipper: `Main Menu → Apps → Examples → ваш застосунок`.

**Очікуваний результат:** екран із заголовком «Hello world» і рядком «I'm test_app!» під ним. Щоб закрити його,
натисніть будь-яку кнопку.

::: warning Версія SDK має збігатися
Версія SDK (API) прошивки на пристрої має збігатися з версією SDK, проти якої збирав uFBT. Якщо під час запуску
застосунку ви бачите помилку про невідповідність API, або оновіть SDK в uFBT до версії вашої прошивки, або
встановіть відповідну прошивку командою `ufbt flash_usb`. На Unleashed переконайтеся, що uFBT використовує індекс
Unleashed (див. підказку в кроці 1), — інакше `ufbt flash_usb` встановить **офіційну** прошивку.
:::

Щоб побачити вивід `FURI_LOG_I`, виконайте `ufbt cli`, а потім `log` (або `log info`, якщо ви змінювали типовий
рівень журналювання).

## Усунення проблем

| Проблема | Що робити |
|---|---|
| `ufbt create` не приймає APPID | Використовуйте лише `a-z`, `0-9`, `_` |
| Невідповідність API / SDK під час запуску | Оновіть SDK в uFBT під свою прошивку (індекс Unleashed!) і перезберіть застосунок |
| `ufbt launch` не знаходить пристрій | Закрийте qFlipper / Lab / будь-який термінал послідовного порту; перепідключіть кабель |
| Застосунку немає в меню | Він має лежати в папці категорії всередині `/ext/apps/`, наприклад `/ext/apps/Examples/` |
| У `log` нічого немає | Запустіть `log` **до** запуску застосунку; перевірте рівень журналювання |

## Що далі?

- Якщо ваш C трохи заріс, класичний довідник — «The C Programming Language» Б. Керніґана і Д. Рітчі.
- [Налагодження застосунків](/ua/dev/debugging) — покрокове проходження застосунку в налагоджувачі.
- [GUI у застосунках](/ua/dev/gui) — ViewPort, Views і Scenes.
- [Маніфести застосунків](/ua/dev/app-manifests) — усі параметри `application.fam`.
- Немає ПК? [Збирайте застосунки на Android](/ua/dev/android-build).
- Більше до душі скриптування? [JavaScript на Flipper](/ua/dev/js-about).
