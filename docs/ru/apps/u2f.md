---
title: U2F-ключ безопасности
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# U2F-ключ безопасности

Приложение **U2F** превращает Flipper Zero в USB-ключ безопасности
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). После ввода пароля на сайте
тот запрашивает ключ, и вы подтверждаете вход нажатием <kbd>OK</kbd> на Flipper. Ключи U2F поддерживают Google, GitHub,
Facebook, X и многие другие сайты; список ведёт [dongleauth.com](https://www.dongleauth.com/).

::: warning Программный ключ
U2F на Flipper реализован программно. Для банков и других важных аккаунтов используйте сертифицированный аппаратный
ключ безопасности. Всегда держите запасной второй фактор (коды восстановления или другой ключ).
:::

## Перед началом

- **Нужна microSD-карта.** Данные U2F хранятся в `/ext/u2f/`. Без карты приложение показывает
  `No SD card or app data found. This app will not work without required files.`
- Файлы сертификата `/ext/u2f/assets/cert.der` и `/ext/u2f/assets/cert_key.u2f` ставятся при обновлении прошивки.
  Если их нет, обновите прошивку ещё раз со вставленной картой.
- **Закройте qFlipper** (и Flipper Lab): Flipper переключает USB-порт в режим U2F, и порт должен быть свободен. Если
  активно соединение, приложение показывает `Connection Is Active! Disconnect from PC or phone to use this function.`

## Регистрация Flipper на сайте

1. Подключите Flipper к компьютеру USB-кабелем.
2. Откройте `Main Menu → U2F`. На экране `Connect me to computer`, затем `Connected!`, когда компьютер распознал ключ.

   ![U2F: Connect me to computer — Флиппер нарисован в виде USB-флешки](/screens/apps/u2f_not_connected.png)

3. На сайте откройте настройки двухфакторной аутентификации и выберите добавление **ключа безопасности** (security key;
   формулировка на разных сайтах отличается).
4. Flipper покажет `Press OK to register`. Нажмите <kbd>OK</kbd>.
5. Сайт подтвердит, что ключ добавлен.

## Вход

1. Подключите Flipper по USB и откройте `Main Menu → U2F` (`Connected!`).
2. Введите на сайте логин и пароль.
3. Когда сайт запросит ключ безопасности, Flipper покажет `Press OK to authenticate`. Нажмите <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate с подсказкой кнопки OK](/screens/apps/u2f.png)

4. Flipper покажет `Authentication successful!`, и сайт пустит вас в аккаунт.

## Берегите файлы U2F

| Файл | Назначение |
|---|---|
| `/ext/u2f/key.u2f` | U2F-ключ этого устройства, зашифрованный уникальным для этого Flipper ключом |
| `/ext/u2f/cnt.u2f` | счётчик аутентификаций |
| `/ext/u2f/assets/` | сертификат аттестации и его ключ (`cert.der`, `cert_key.u2f`) |

::: danger Не удаляйте, не редактируйте и не переносите файлы U2F
- У каждого Flipper есть уникальный встроенный ключ, которым шифруются файлы U2F. Карта с файлами U2F, перенесённая в
  **другой Flipper, там работать не будет**.
- Если удалить или изменить файлы либо вставить новую карту, Flipper создаст новый набор файлов U2F, и его придётся
  **заново зарегистрировать на всех сайтах**.
- Если удалить `u2f/assets` (или всю папку `u2f`), приложение перестанет работать (сообщит `No SD card or app
  data found`), пока вы не восстановите папку обновлением прошивки.
:::

## Проблемы

| Симптом | Решение |
|---|---|
| Висит на `Connect me to computer` | используйте кабель с передачей данных (не только для зарядки), закройте qFlipper, попробуйте другой USB-порт |
| `Connection Is Active!` | закройте qFlipper, Flipper Lab, CLI или сессию мобильного приложения, затем снова откройте U2F |
| `No SD card or app data found` | вставьте карту; если она вставлена, восстановите `/ext/u2f/assets` переустановкой прошивки |
| `Certificate error` | движок U2F не смог запуститься с файлами на карте: переустановите прошивку со вставленной картой |
| Сайт больше не принимает ключ | файлы U2F были пересозданы (новая карта, удалённые файлы): войдите с запасным фактором и зарегистрируйте Flipper заново |

Приложение также запускается с вкладки **U2F** в [Archive](/ru/apps/archive).

## Связанные страницы

- [Приложения в комплекте Unleashed](/ru/apps/catalog)
- [Bad USB](/ru/badusb/usage)
- [qFlipper](/ru/mobile/qflipper)
