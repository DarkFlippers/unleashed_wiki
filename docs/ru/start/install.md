---
title: Установка Unleashed
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-readme, unleashed-src, flipper-docs]
---
# Установка Unleashed

Установить Unleashed можно несколькими способами. Все они ставят один и тот же пакет обновления: прошивку, апдейтер и
все ресурсы (приложения, ИК-библиотеки, настройки Sub-GHz и т. д.).

::: tip Перед началом
- **Только при первой установке:** сначала обновитесь до **последнего официального релиза** ([Первый запуск](/ru/start/first-start)).
- **Уже стоит Unleashed:** ничего промежуточного ставить не нужно. Новую версию ставьте прямо поверх текущей.
- Убедитесь, что **вставлена microSD-карта**: обновление распаковывается на неё, и на ней же живут приложения.
- Зарядите аккумулятор. Полное обновление занимает несколько минут.
:::

## Какой файл скачивать {#which-file-to-download}

Файлы релиза называются `flipper-z-f7-update-(version)(e / c).tgz`:

| Часть | Значение |
|---|---|
| `flipper-z` | Для устройства Flipper Zero |
| `f7` | Аппаратная платформа. Одинакова для всех Flipper Zero |
| `update` | Пакет самообновления: апдейтер, прошивка и все ресурсы |
| `(version)` | Версия прошивки |
| суффикс | Вариант набора приложений (см. ниже) |

| Суффикс | [Base Apps](https://github.com/xMasterX/all-the-plugins#default-pack) | [Extra Apps](https://github.com/xMasterX/all-the-plugins#extra-pack) |
|---|:---:|:---:|
| `e` | ✅ | ✅ |
| *(нет)* | ✅ | — |
| `c` | — | — |

- **`e`** — всё сразу: базовый и дополнительный наборы приложений сообщества. Если сомневаетесь — берите его.
- **Без суффикса** — только базовый набор приложений сообщества.
- **`c`** («clean») — без приложений сообщества.

**Встроенные системные приложения** (MFKey, T5577, Nice O-Code, Security+ PIN, Seed Capturer, Remote Analyzer,
Sub-GHz RAW Edit, SIM800, FindMy Flipper, USB/BT-пульты, Snake…) поставляются **вместе с прошивкой** и есть в
**любом** варианте, включая `c`. Подробнее: [Возможности Unleashed](/ru/start/unleashed-features#built-in-apps).

Другие файлы релиза:
- `flipper-z-any-scripts-(version).tgz` — папка `scripts` для разработки прошивки и приложений;
- `flipper-z-f7-sdk-(version).zip` — SDK для разработки приложений и uFBT.

## Способ 1: qUnleashed (рекомендуется)

[qUnleashed](/ru/mobile/qunleashed-app) — собственное приложение-компаньон команды Unleashed. Оно само
скачивает и ставит прошивку, так что выбирать файл не нужно. Работает на **Android, iOS, Windows, macOS
и Linux** — по USB на всех, кроме iOS: там подключение только по Bluetooth.

1. Установите qUnleashed для своей системы со
   [страницы релизов](https://github.com/DarkFlippers/qUnleashed/releases).
2. Подключите Флиппер по USB или сопрягите по Bluetooth (на iOS — только Bluetooth).
3. Откройте в приложении **обновление прошивки**.
4. Выберите канал **Unleashed** — **Release** или **Dev**.
5. Выберите сборку: **базовую**, **с дополнительными приложениями** или **компактную**
   ([что в них входит](#which-file-to-download)).
6. Запустите установку и ждите. Флиппер перезагрузится в апдейтер и пройдёт все этапы.

Если Флиппер уже не загружается, тем же приложением его можно перепрошить по USB через
**Repair from DFU mode**. См. [Восстановление](/ru/start/recovery#firmware-recovery).

Способы ниже — альтернативные. Возьмите один из них, если qUnleashed вам не подходит.

## Способ 2: Unleashed Web Installer

Нужен **браузер на Chromium** (Chrome, Edge, Opera, Brave, Vivaldi) и USB-кабель.

1. Закройте **qFlipper** и другие веб-страницы Flipper — они занимают последовательный порт.
2. Подключите Флиппер по USB.
3. Откройте **[web.unleashedflip.com](https://web.unleashedflip.com)**.
4. Нажмите **Connect** и выберите Флиппер во всплывающем окне браузера.
5. Выберите ветку **Release** или **Dev**.
6. Нажмите **Install** и ждите. Флиппер перезагрузится в апдейтер и пройдёт все этапы.
7. Готово, все ресурсы установлены.

## Способ 3: веб-апдейтер Flipper Lab

1. Откройте [страницу последнего релиза](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
2. Подключите Флиппер и перейдите по ссылке **Install via Web Updater**.
3. На странице веб-апдейтера нажмите **Connect**, затем **Install**.
4. Дождитесь окончания обновления.

![Веб-апдейтер](/img/remote/b803c9d8ec0350d6.png)

## Способ 4: qFlipper (1.2.0 и новее)

1. Установите [qFlipper](https://flipperzero.one/update) версии 1.2.0+. Старые версии не умеют ставить `.tgz`.
2. Скачайте `flipper-z-f7-update-(version).tgz` со [страницы релизов](https://github.com/DarkFlippers/unleashed-firmware/releases/latest).
3. Запустите qFlipper и подключите Флиппер.
4. Нажмите **Install from file** и выберите скачанный `.tgz`.
5. Начнётся обновление — дождитесь окончания.

![qFlipper, установка из файла](/img/remote/f1a3ede83085d040.png)

::: warning
После установки Unleashed **не нажимайте** в qFlipper кнопку **Update** — она поставит **официальную** прошивку
поверх Unleashed. Используйте **Install from file**.
:::

## Способ 5: Flipper Mobile App

### Android, с файлом `.tgz`
1. Скачайте `flipper-z-f7-update-(version).tgz` на телефон.
2. В приложении Flipper нажмите **Update channel** и выберите **Custom**.
3. Выберите скачанный `.tgz` и нажмите **Update**.
4. Дождитесь окончания обновления.

### Android, по ссылке веб-апдейтера
1. На странице релиза нажмите **Install via Web Updater**.
2. На вопрос, чем открыть ссылку, выберите **Flipper App**.
3. Продолжите установку и дождитесь окончания.

### iOS
1. Скачайте `flipper-z-f7-update-(version).tgz`.
2. Откройте его в приложении **Файлы**, нажмите **Поделиться** и выберите **Flipper App**.
3. В приложении Flipper нажмите зелёную кнопку **Update**. В канале обновления должно быть
   `Custom flipper-z-f7-update...`.
4. Ждите. **В конце приложение на iOS может показать ошибку, но Флиппер при этом обновится успешно.**

## Способ 6: офлайн-обновление с microSD-карты

Без программ на компьютере, можно даже с телефона.

1. Распакуйте `flipper-z-f7-update-(version).tgz` (или `.zip`). Внутри — папка `f7-update-(version)` с файлами
   `update.fuf`, `resources.tar` и другими.
2. Вставьте карту в ПК или телефон (или загрузите файлы через qFlipper).
3. Создайте в **корне** карты папку `update` и переместите в неё `f7-update-(version)`:
   ```text
   /ext/update/f7-update-(version)/update.fuf
   /ext/update/f7-update-(version)/resources.tar
   ...
   ```
4. Проверьте, что на месте **все** файлы. Стандартное приложение «Файлы» на iOS может показать только 3 файла из 6.
   Используйте другое приложение для распаковки, ПК или Android.
5. Вставьте карту обратно во Флиппер.
6. Откройте **Archive** (<kbd>↓</kbd> на рабочем столе), вкладка **Browser**, перейдите в
   `update/f7-update-(version)/` и откройте `update.fuf`.
7. Начнётся обновление. Дождитесь окончания всех этапов.

![Офлайн-обновление](/img/remote/92717373349f3b7c.png)

## После установки

- В **Settings → About** отображаются сведения о прошивке Unleashed и её версия.
- При первой загрузке после обновления Флиппер распаковывает ресурсы на карту — это нормально.
- Прочитайте [Возможности Unleashed](/ru/start/unleashed-features) и настройте устройство в разделе [Настройки](/ru/start/settings).

## Проблемы

| Проблема | Решение |
|---|---|
| Браузер не подключается | Закройте qFlipper и другие вкладки Flipper Lab, используйте Chromium-браузер, попробуйте другой кабель или порт |
| Обновление падает или зависает | Перезагрузите <kbd>←</kbd> + <kbd>BACK</kbd>, проверьте SD-карту, попробуйте другой способ |
| После установки не подключается мобильное приложение | Забудьте Флиппер в приложении и в настройках Bluetooth телефона, затем на Флиппере **Settings → Bluetooth → Unpair All Devices** и сопрягите заново |
| После установки не работает подсветка | См. [FAQ](/ru/start/faq#backlight-does-not-work) (настройка RGB-мода) |
| Устройство не подаёт признаков жизни | [Восстановление](/ru/start/recovery) |
