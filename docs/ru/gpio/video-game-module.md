---
title: Video Game Module
order: 90
original: [https://docs.flipper.net/zero/video-game-module, https://docs.flipper.net/zero/video-game-module/quick-start, https://docs.flipper.net/zero/video-game-module/firmware-update, https://docs.flipper.net/zero/video-game-module/custom-firmware, https://docs.flipper.net/zero/video-game-module/gpio, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_vgm]
sources: [flipper-docs, unleashed-src]
---
# Video Game Module

**Video Game Module** (VGM) — официальный модуль на **Raspberry Pi RP2040**. Он вставляется в GPIO-разъём и
добавляет:

- **Video Out** — вывод экрана Flipper на телевизор или монитор (сигнал DVI-D, 640×480);
- **6-осевой датчик движения** (TDK ICM-42688-P: 3-осевой гироскоп + акселерометр) для управления наклоном;
- **порт USB-C**, подключённый к RP2040 (прошивка или собственные задачи кастомной прошивки);
- **14-контактную гребёнку GPIO** от RP2040;
- **кнопки BOOT / RESET** (нажимать скрепкой) для режима прошивки UF2 и сброса;
- RGB-светодиод сверху.

Модуль может работать и самостоятельно, как плата на RP2040, совместимая с проектами для Raspberry Pi Pico.

![Кнопки и разъёмы Video Game Module](/img/remote/b24db83aa0fa8a69.jpg)

## Установка и подключение к ТВ

1. **Наденьте модуль.** В комплекте силиконовый бампер, рассчитанный на Flipper *без* чехла. Если Flipper в
   силиконовом чехле, снимите бампер с модуля (или чехол с Flipper).
2. **Прошивка.** Модулю нужна прошивка Flipper 0.98.3 или новее; актуальные релизы Unleashed подходят.
3. **Проверьте настройку UART:** `Main Menu → Settings → Expansion Modules → Listen UART` должно быть **`USART`**. При
   любом другом значении модуль не определится. (См. [Expansion-модули](/ru/gpio/expansion-modules).)
4. Вставьте модуль (Flipper выключен), включите. Flipper определит модуль и подготовит его автоматически.
5. Подключите кабель ТВ к порту **Video Out** модуля и выберите этот вход на телевизоре.

### «Video Game Module not initialized»

Эта надпись на экране ТВ значит, что модуль не общается с Flipper: прошивка слишком старая, `Listen UART` не `USART`
или модуль запитан (например, по USB) без подключённого Flipper.

## Игры и приложения

Датчик движения используют приложения из каталога Flipper Apps, например
[Air Arkanoid](https://lab.flipper.net/apps/air_arkanoid) и [Air Mouse](https://lab.flipper.net/apps/vgm_air_mouse)
(гиромышь для компьютера).

::: tip Unleashed
В JavaScript-движке Unleashed есть модуль `vgm` (JS-фича `vgm`): `getPitch()`, `getRoll()`, `getYaw()` и
`deltaYaw(angle, timeout)` читают ориентацию модуля из скрипта и возвращают `undefined`, если VGM не подключён.
О JS-приложениях — в разделе [Разработка](/ru/dev/).
:::

## Обновление прошивки модуля

Обновления ставятся приложением **Video Game Module Tool** (из каталога Flipper Apps). Его меню:

- `Install Official Firmware` — последняя официальная прошивка модуля, встроенная в приложение;
- `Install Firmware from File` — кастомный `.uf2` с SD-карты.

Порядок:

1. Установите (или **сначала обновите**) Video Game Module Tool: в мобильном приложении Flipper откройте **Apps**,
   найдите *Video Game Module Tool*, нажмите **INSTALL** / **UPDATE**. Новая прошивка модуля приходит вместе с новой
   версией приложения, поэтому сначала всегда обновляйте приложение.
2. Подключите модуль к Flipper.
3. Откройте `Main Menu → Apps → Tools → Video Game Module Tool`.
4. Выберите `Install Official Firmware`, подтвердите `Install` (<kbd>→</kbd>).
5. Дождитесь сообщения **Video Game Module Updated**.

## Кастомная прошивка

Модуль может работать с вашей собственной прошивкой для RP2040.

### Через Flipper Zero

Можно хранить на SD-карте несколько прошивок модуля и переключаться без компьютера.

1. Скопируйте файл `.uf2` на SD-карту Flipper (например, через [qFlipper](/ru/mobile/qflipper): `File manager → SD Card`,
   создайте папку, загрузите файл).
2. Подключите модуль, откройте `Apps → Tools → Video Game Module Tool → Install Firmware from File`.
3. Выберите файл и подтвердите `Install` (<kbd>→</kbd>). Дождитесь **Video Game Module Updated**.

::: warning Ограничения UF2 при установке через Flipper
- Блоки не для flash не поддерживаются.
- Полезная нагрузка блока — ровно 256 байт.
- Адреса назначения выровнены по 256 байт, без пропусков.
- Контейнеры файлов и теги расширений не поддерживаются.
:::

### С компьютера

1. Отключите модуль от Flipper и от USB.
2. Зажмите скрепкой кнопку **BOOT** на модуле.
3. Подключите модуль к компьютеру по USB-C. Он появится как USB-диск **RPI-RP2**. Отпустите **BOOT**.
4. Перетащите файл `.uf2` на **RPI-RP2**. Модуль перезагрузится и сам отключится как диск.

## Аппаратные подробности (для самостоятельного использования)

### GPIO RP2040

- GPIO **8–15** и **18–20** заняты видеовыходом и на разъёмы не выведены.
- GPIO **0–7, 16, 17, 21, 22, 26–28** выведены на разъёмы (как у Raspberry Pi Pico). GPIO **2–7** также подключены к
  датчику движения.
- GPIO **23–25 и 29** (на Pico заняты внутри) на VGM свободны и выведены на 14-контактную гребёнку.

![Распиновка 14-контактной гребёнки Video Game Module](/img/remote/b030c6a0375c6254.png)

![Распиновка Video Game Module и Raspberry Pi Pico](/img/remote/9e55d40b6c557fa8.jpg)

### Периферия, доступная RP2040

- **Video Out:** видео и звук на ТВ/монитор, плюс обмен данными по
  [Display Data Channel](https://en.wikipedia.org/wiki/Display_Data_Channel).
- **USB-C:** USB-устройство или хост (без USB Power Delivery).
- **IMU:** TDK ICM-42688-P.
- **Гребёнка GPIO:** 11 пинов с защитой от ЭСР.
- **Разъём к Flipper Zero:** пины Flipper 13 и 14 — полноценно; пины 2–7 — с ограничениями (общие с IMU). Защита от
  ЭСР.
- **RGB-светодиод**, управляется с GPIO RP2040.

### Питание

- 5 В по USB-C при автономной работе;
- 3,3 В (пин 9) или 5 В (пин 1) от Flipper.

Одновременное питание от USB-C и от Flipper безопасно и для модуля, и для обоих источников.

Схемы, сборочные чертежи и PDF-распиновки — на официальной странице
[GPIO on Video Game Module](https://docs.flipper.net/zero/video-game-module/gpio).

## См. также

- [Expansion-модули](/ru/gpio/expansion-modules)
- [Распиновка GPIO](/ru/gpio/pinout)
- [Внешние модули](/ru/gpio/external-modules)
