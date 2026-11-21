---
title: Ключ безпеки U2F
order: 40
original: [https://docs.flipper.net/zero/u2f, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/u2f]
sources: [flipper-docs, unleashed-src]
---
# Ключ безпеки U2F

Застосунок **U2F** перетворює Flipper Zero на USB-ключ безпеки
[Universal 2nd Factor](https://en.wikipedia.org/wiki/Universal_2nd_Factor) (FIDO U2F). Після того як ви ввели пароль
на сайті, сайт запитує ключ, і ви підтверджуєте вхід натисканням <kbd>OK</kbd> на Flipper. Google, GitHub, Facebook,
X і багато інших сайтів підтримують ключі U2F; їхній перелік веде [dongleauth.com](https://www.dongleauth.com/).

::: warning Програмний ключ
U2F у Flipper реалізовано програмно. Для банків та інших важливих акаунтів використовуйте сертифікований апаратний
ключ безпеки. Завжди тримайте резервний другий фактор (коди відновлення або інший ключ).
:::

## Перед початком

- **Потрібна картка microSD.** Дані U2F лежать у `/ext/u2f/`. Без неї застосунок показує
  `No SD card or app data found. This app will not work without required files.`
- Файли сертифіката `/ext/u2f/assets/cert.der` і `/ext/u2f/assets/cert_key.u2f` встановлюються під час оновлення
  прошивки. Якщо їх немає, оновіть прошивку ще раз зі вставленою карткою.
- **Закрийте qFlipper** (і Flipper Lab): Flipper має бути вільним, щоб перевести свій USB-порт у режим U2F. Якщо
  з’єднання активне, застосунок показує `Connection Is Active! Disconnect from PC or phone to use this function.`

## Реєстрація Flipper на сайті

1. Під’єднайте Flipper до комп’ютера USB-кабелем.
2. Відкрийте `Main Menu → U2F`. На екрані з’явиться `Connect me to computer`, а потім `Connected!`, коли комп’ютер
   розпізнає ключ.

   ![U2F: Connect me to computer, Flipper намальований як USB-флешка](/screens/apps/u2f_not_connected.png)

3. На сайті відкрийте налаштування двофакторної автентифікації й виберіть додавання **ключа безпеки**
   (формулювання відрізняється від сайту до сайту).
4. Flipper покаже `Press OK to register`. Натисніть <kbd>OK</kbd>.
5. Сайт підтвердить, що ключ додано.

## Вхід

1. Під’єднайте Flipper через USB і відкрийте `Main Menu → U2F` (`Connected!`).
2. Введіть логін і пароль на сайті.
3. Коли сайт запитає ключ безпеки, Flipper покаже `Press OK to authenticate`. Натисніть <kbd>OK</kbd>.

   ![U2F: Press OK to authenticate з підказкою кнопки OK](/screens/apps/u2f.png)

4. Flipper покаже `Authentication successful!`, і сайт виконає вхід.

## Зберігайте файли U2F у безпеці

| Файл | Призначення |
|---|---|
| `/ext/u2f/key.u2f` | ключ U2F цього пристрою, зашифрований ключем, унікальним для цього Flipper |
| `/ext/u2f/cnt.u2f` | лічильник автентифікацій |
| `/ext/u2f/assets/` | сертифікат атестації та його ключ (`cert.der`, `cert_key.u2f`) |

::: danger Не видаляйте, не редагуйте й не переміщуйте файли U2F
- У кожного Flipper є унікальний вбудований ключ, яким шифруються файли U2F. Картка з файлами U2F, переставлена в
  **інший Flipper, там не працюватиме**.
- Якщо ви видалите або відредагуєте ці файли чи вставите нову картку, Flipper створить новий набір файлів U2F, і вам
  доведеться **заново зареєструвати його на кожному сайті**.
- Якщо ви видалите `u2f/assets` (або всю папку `u2f`), застосунок перестане працювати (повідомляючи `No SD card or
  app data found`), доки ви не відновите папку оновленням прошивки.
:::

## Усунення проблем

| Симптом | Що робити |
|---|---|
| Застрягло на `Connect me to computer` | візьміть кабель із передачею даних (не лише для заряджання), закрийте qFlipper, спробуйте інший USB-порт |
| `Connection Is Active!` | закрийте qFlipper, Flipper Lab, CLI або сеанс мобільного застосунку, після чого відкрийте U2F знову |
| `No SD card or app data found` | вставте картку; якщо вона на місці, відновіть `/ext/u2f/assets`, перевстановивши прошивку |
| `Certificate error` | рушій U2F не зміг запуститися з файлами, що є на картці: перевстановіть прошивку зі вставленою карткою |
| Сайт більше не приймає ключ | файли U2F були створені заново (нова картка, видалені файли): увійдіть резервним фактором і зареєструйте Flipper ще раз |

Вкладка **U2F** в [Archive](/ua/apps/archive) також запускає застосунок.

## Пов’язані сторінки

- [Застосунки у складі Unleashed](/ua/apps/catalog)
- [Bad USB](/ua/badusb/usage)
- [qFlipper](/ua/mobile/qflipper)
