---
title: Обновление
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Обновление

Unleashed обновляется часто. Обновление ничем не отличается от установки: новая версия ставится **поверх** текущей.
Возвращаться на официальную прошивку или ставить что-то промежуточное не нужно.

## Как обновиться

**Рекомендуем [qUnleashed](/ru/mobile/qunleashed-app)** — приложение-компаньон Unleashed для **Android, iOS,
Windows, macOS и Linux** (по USB на всех, кроме iOS: там Bluetooth). Новую прошивку оно скачивает само.

1. Установите или обновите qUnleashed со [страницы релизов](https://github.com/DarkFlippers/qUnleashed/releases).
2. Подключите Флиппер по USB или Bluetooth.
3. Откройте **обновление прошивки**, выберите канал **Unleashed** (**Release** или **Dev**) и свою сборку —
   базовую, с дополнительными приложениями или компактную.
4. Запустите установку и дождитесь окончания всех этапов.

Если Флиппер перестал загружаться, **Repair from DFU mode** в том же приложении перепрошьёт его по USB
([Восстановление](/ru/start/recovery#firmware-recovery)).

Альтернативы — любой из остальных [способов установки](/ru/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → Release или Dev → Install.
2. **qFlipper**: **Install from file** с новым `flipper-z-f7-update-(version).tgz`.
3. **Мобильное приложение**: канал Custom с файлом `.tgz`.
4. **Офлайн**: скопировать `f7-update-(version)` в `/ext/update/` и открыть `update.fuf` в Archive.

::: warning Не нажимайте «Update» в qFlipper или официальном приложении
Кнопка **Update** в qFlipper и Flipper Mobile App берёт прошивку с **официального** сервера и заменяет Unleashed
стоковой прошивкой. Для Unleashed используйте обновление в qUnleashed, **Install from file**, канал Custom или
Web Installer.
:::

## Релиз или dev?

| | Release | Dev |
|---|---|---|
| Стабильность | Проверенная | Возможны баги |
| Новые функции | С каждым релизом | Сразу после слияния в ветку |
| Где взять | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Dev-сборки собираются автоматически из последних коммитов. Когда загружается новая сборка, предыдущая удаляется с сайта.
Баги — в [GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Что сохраняется после обновления

- **Ваши файлы на microSD**: сохранённые ключи, карты, пульты и скрипты не трогаются.
- **Своё имя**: хранится на карте в `/ext/dolphin/name.settings` ([Своё имя Флиппера](/ru/start/custom-name)).
- **Настройки**: обычно сохраняются. **Исключение:** если в релизе меняется структура файла настроек, этот файл один
  раз сбрасывается на значения по умолчанию. Так бывает только в отдельных релизах. Если после обновления сбросились
  настройки рабочего стола (PIN, избранное и т. п.), настройте их заново и загляните в changelog.
- **Встроенные приложения** в `/ext/apps/` заменяются версиями из новой прошивки. Наборы приложений никогда не
  перезапишут и не откатят их.

## Как узнать версию

- **Main Menu → Settings → About**: версия прошивки, дата сборки, ветка и коммит;
- или зажмите <kbd>↓</kbd> на рабочем столе — откроется информационный экран.

## Где читать, что изменилось

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases) — changelog каждого релиза;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) в ветке dev — что войдёт в
  следующий релиз;
- обновления приложений: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Сервер обновлений Unleashed

У Unleashed есть свой сервер обновлений в том же формате, что и официальный:
`https://up.unleashedflip.com/directory.json`. Официальные приложения нельзя переключить на него без пересборки.
**uFBT** принимает этот адрес как аргумент — так можно собирать приложения под SDK Unleashed
(см. [Сборка прошивки](/ru/dev/build)).

## Если обновление не проходит

1. Перезагрузите <kbd>←</kbd> + <kbd>BACK</kbd> и попробуйте снова.
2. Попробуйте другой способ (qUnleashed ↔ Web Installer ↔ qFlipper ↔ офлайн).
3. Проверьте SD-карту (**Settings → Storage → About SD Card**) или отформатируйте её, предварительно сделав копию.
4. Не помогло — [Восстановление](/ru/start/recovery).
