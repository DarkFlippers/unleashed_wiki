---
title: Оновлення
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/basics/firmware-update]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Оновлення

Unleashed оновлюється часто. Оновлення працює так само, як і встановлення: нова версія ставиться **поверх** поточної.
Повертатися на офіційну прошивку чи ставити щось проміжне не потрібно.

## Як оновитися

**Рекомендовано: [qUnleashed](/ua/mobile/qunleashed-app)** — супутній застосунок Unleashed для **Android, iOS,
Windows, macOS і Linux** (по USB на всіх, окрім iOS, де працює Bluetooth). Нову прошивку він завантажує сам.

1. Встановіть або оновіть qUnleashed зі [сторінки релізів](https://github.com/DarkFlippers/qUnleashed/releases).
2. Під’єднайте Фліппер по USB або по Bluetooth.
3. Відкрийте **оновлення прошивки**, виберіть канал **Unleashed** (**Release** або **Dev**) і ту збірку, якою
   користуєтеся: **базову**, **з додатковими застосунками** або **компактну**.
4. Запустіть встановлення й дочекайтеся, доки Фліппер пройде всі етапи.

Якщо Фліппер перестав завантажуватися, **Repair from DFU mode** у тому самому застосунку перепрошиє його по USB
([Відновлення](/ua/start/recovery#firmware-recovery)).

Альтернативи, усі описані в [способах встановлення](/ua/start/install):

1. **[Web Installer](https://web.unleashedflip.com)**: Connect → вибір Release або Dev → Install.
2. **qFlipper**: **Install from file** з новим `flipper-z-f7-update-(version).tgz`.
3. **Мобільний застосунок**: власний канал оновлення з файлом `.tgz`.
4. **Офлайн**: скопіювати `f7-update-(version)` у `/ext/update/` і відкрити `update.fuf` в Archive.

::: warning Не натискайте «Update» у qFlipper чи офіційному застосунку
Вбудована кнопка **Update** у qFlipper і Flipper Mobile App звертається до **офіційного** сервера оновлень. Вона
заміняє Unleashed стоковою прошивкою. Для Unleashed використовуйте оновлювач qUnleashed, **Install from file**,
власний канал оновлення або Web Installer.
:::

## Реліз чи dev?

| | Release | Dev |
|---|---|---|
| Стабільність | Перевірена | Можливі баги |
| Нові можливості | З кожним релізом | Щойно їх влили в гілку |
| Де взяти | Web Installer → Release, [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases), [@unleashed_fw](https://t.me/unleashed_fw) | Web Installer → Dev, [dev.unleashedflip.com](https://dev.unleashedflip.com), [@kotnehleb](https://t.me/kotnehleb) |

Dev-збірки створюються автоматично з останніх комітів. Попередня dev-збірка видаляється із сайту, коли туди
завантажують нову. Про баги повідомляйте в
[GitHub issues](https://github.com/DarkFlippers/unleashed-firmware/issues).

## Що зберігається після оновлення

- **Ваші файли на картці microSD** — збережені ключі, карти, пульти та скрипти ніхто не чіпає.
- **Власне ім’я Фліппера** — лежить на картці у `/ext/dolphin/name.settings`
  ([Власне ім’я Фліппера](/ua/start/custom-name)).
- **Налаштування** — зазвичай зберігаються. **Виняток:** якщо в релізі змінилася структура файлу налаштувань, цей
  файл один раз скидається до типових значень. Таке трапляється лише в окремих релізах. Якщо після оновлення
  скинулися налаштування робочого стола (PIN-код, улюблені застосунки…), задайте їх знову й перегляньте список змін.
- **Вбудовані застосунки** в `/ext/apps/` заміняються версіями з нової прошивки. Набори застосунків ніколи не можуть
  перезаписати їх чи відкотити до старішої версії.

## Як перевірити свою версію

- **Main Menu → Settings → About** — версія прошивки, дата збірки, гілка й коміт;
- або утримуйте <kbd>↓</kbd> на робочому столі, щоб відкрити службовий інформаційний екран.

## Де почитати, що змінилося

- [GitHub Releases](https://github.com/DarkFlippers/unleashed-firmware/releases) — список змін кожного релізу;
- [CHANGELOG.md](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md) у гілці dev — що буде
  в наступному релізі;
- оновлення застосунків: [xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/commits/dev).

## Сервер оновлень Unleashed

В Unleashed є власний сервер оновлень у тому самому форматі, що й офіційний:
`https://up.unleashedflip.com/directory.json`. Офіційні застосунки не можна перевести на нього без перезбирання.
**uFBT** приймає цю URL-адресу як аргумент, щоб збирати застосунки проти SDK Unleashed
(див. [Збирання прошивки](/ua/dev/build)).

## Якщо оновлення не вдалося

1. Перезавантажте пристрій комбінацією <kbd>←</kbd> + <kbd>BACK</kbd> і спробуйте знову.
2. Спробуйте інший спосіб (qUnleashed ↔ Web Installer ↔ qFlipper ↔ офлайн).
3. Перевірте картку (**Settings → Storage → About SD Card**) або відформатуйте її, зробивши резервну копію.
4. Так і не виходить — [Відновлення](/ua/start/recovery).
