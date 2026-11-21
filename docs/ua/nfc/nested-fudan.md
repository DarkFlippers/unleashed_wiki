---
title: Nested-атаки та бекдори Fudan
order: 35
author: gromovyna
original: [https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://t.me/gromovyna/4, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [gromovyna, flipper-docs, unleashed-src]
---
# Nested-атаки та бекдори Fudan

Практичний гайд «що натискати» від **@gromovyna** до card-only атак на MIFARE Classic, вбудованих у `NFC → Read`.
Вони з'явилися в офіційній прошивці **1.1.2** (робота [@noproto](https://github.com/noproto)) і є частиною Unleashed.
Поки їх розробляли, дослідник зі спільноти зробив два важливі відкриття: атаку на **статичні шифровані nonce** та
**ключі-бекдори** в чипах виробництва **Fudan** (і не тільки), які дають змогу зчитати сектори мітки MIFARE Classic,
не знаючи її ключів. Обидва ввійшли і до прошивки, і до **MFKey 3** (тепер [MFKey 4.1](/ua/nfc/mfkey-app)).
Наукова робота: [eprint.iacr.org/2024/1275](https://eprint.iacr.org/2024/1275.pdf).

::: tip Швидший спосіб (оновлення, вересень 2026)
Якщо вам потрібно просто швидко відновити ключі MIFARE Classic, скористайтеся застосунком-компаньоном **qUnleashed**,
який виконує всі ці атаки, включно з HardNested, на телефоні або комп'ютері: див.
[Швидке відновлення ключів за допомогою qUnleashed](/ua/nfc/qunleashed).
:::

## Коротко про суть

**Nested-атаки** — це *card-only* атаки (зчитувач не потрібен): знаючи хоча б один ключ картки, вони відновлюють
невідомі. Концептуально мітки діляться на чотири групи (строго кажучи, є Nested і HardNested, але такий поділ
легше зрозуміти):

| Мітка вразлива до | Тип nonce | Де обчислюється ключ |
|---|---|---|
| **Nested** | слабкий PRNG | MFKey на Flipper, qUnleashed |
| **HardNested** | стійкий PRNG | qUnleashed або комп'ютер (не на Flipper) |
| **Static Nested** | статичний nonce | MFKey на Flipper, qUnleashed |
| **Static Encrypted Nested** (SEN) | статичний шифрований nonce | MFKey на Flipper (найповільніше), qUnleashed |

**Ключі-бекдори** — це ключі, які відкривають дані мітки **без** її справжніх ключів.

Для прикладів автор використав мітки кожного типу, у яких сектор 0 зашифровано згенерованою парою ключів:
ключ A `A3F92C8E7D3A`, ключ B `4F6D91C5BA7E` (біти доступу залишено стандартними). На Proxmark3 перевірка
стандартних ключів показала ці ключі як невідомі:

![Перевірка стандартних ключів на Proxmark3](/img/remote/86130b06142278a1.png)

## Крок 1. Зчитуємо мітку

Відкрийте `Main Menu → NFC → Read` і тримайте мітку нерухомо.

### 1.1 Мітка з бекдором

Ви побачите екран із **Backdoor Read**, а потім ще кілька з **(Backdoor)** у заголовку:

![Backdoor Read](/img/remote/1491507f521c09f5.png)

![Зчитування через бекдор](/img/remote/e9be977d84486794.png)

Це означає, що чип має бекдор: Flipper зчитує через нього дані секторів і паралельно збирає nonce, щоб потім
відновити ключі. Типовий результат — **усі сектори зчитано, але ключів менше, ніж потрібно**:

![Усі сектори, але лише 30 ключів](/img/remote/9e7db33e51594779.png)

### 1.2 Мітка без бекдора

Тоді запускається класичний пошук ключів: спершу **користувацький** словник, потім **системний**.

![Користувацький словник](/img/remote/fff8f5662df941b9.png)

![Системний словник](/img/remote/0da64f609fc2c770.png)

Якщо знайдено хоча б один ключ, Flipper переходить до **PRNG Analysis**, а далі — до **Nested Dictionary**:

![PRNG Analysis](/img/remote/3e0e493fe7fcbd5f.png)

потім **Calibration** і **Nonce Collection**:

![Calibration і збір nonce](/img/remote/f5b036a96f5a0869.png)

Якщо мітка вразлива **лише до HardNested**, збір nonce триває довше, а заголовок отримує суфікс **(Hard)**:

![Збір nonce для мітки зі стійким PRNG](/img/remote/fca9f1b2e4475631.png)

> У такому разі переходьте одразу до [пункту 2.2](#_2-2-the-tag-is-vulnerable-to-hardnested).

Тут результат виглядає звичніше: кількість знайдених ключів близька до кількості зчитаних секторів (залежно від
бітів доступу).

![Результат після nested-фази](/img/remote/d15656101dfafcc4.png)

Усі зібрані nonce дописуються до `/ext/nfc/.nested.log`.

## Крок 2. Відновлюємо ключі

Відкрийте `Main Menu → Apps → NFC → MFKey`.

::: warning Перевірте версію застосунку
Переконайтеся, що застосунок MFKey відповідає вашій прошивці й не був перезаписаний старою копією, якщо ви
встановлювали застосунки окремо. Unleashed постачається з **MFKey 4.1**.
:::

![Початковий екран MFKey](/img/remote/195a1b6a411e7bf3.png)

Натисніть <kbd>OK</kbd> **Start** і…

### 2.1 Мітка вразлива до Nested, Static Nested або Static Encrypted Nested

Починається процес зламування. Flipper можна залишити й зайнятися чимось іншим:

![Зламування триває](/img/remote/a514db67a986ae2c.png)

Залишається тільки чекати. На апаратній частині Flipper це небистро (вітання, SPI) і залежить від:

- типу атаки: Nested < Static Nested < Static Encrypted Nested (SEN найповільніша);
- кількості невідомих ключів (чим менше, тим швидше);
- того, наскільки унікальні ключі: ключ, що повторюється всюди, знаходиться швидше, ніж частково диверсифікована
  мітка (наприклад, Iron Logic), яка, у свою чергу, швидша за повністю диверсифіковану (наприклад, катушки з
  філаментом Bambu Lab).

Інтерфейс не завжди відповідає швидко й іноді «задумується». Часом Flipper може виглядати завислим — не спішіть
його перезавантажувати. Рядок **RAM** угорі змінюється, поки робота триває.

::: warning Статичні шифровані nonce
Зі статичними шифрованими nonce через особливості атаки nonce не позначаються як «розв'язані»; MFKey лише будує
**кандидатів** (ключі, які потім потрібно перевірити на мітці), і застосунок може виглядати застряглим на
останньому (або ранішому) кроці. Якщо часу пройшло достатньо, виходьте й перевіряйте результат (крок 3). Починаючи
з MFKey 4.x кандидати зберігаються до **CUID-словника** для цієї картки
`/ext/nfc/assets/mf_classic_dict_<UID>.nfc`, який `Read` пробує першим.
:::

Коли розшифрування завершено, ви отримаєте зведення з кількістю ключів, доданих до користувацького словника
(**Keys added to user dict: N**, а для міток SEN ще й **SEN key candidates: N**):

![MFKey завершив роботу](/img/remote/c9ef77139b74cc89.png)

Переходьте до кроку 3.

### 2.2 Мітка вразлива до HardNested {#_2-2-the-tag-is-vulnerable-to-hardnested}

Про це можна було дізнатися з екрана **(Hard)** під час збору nonce, або ж MFKey покаже помилку, що nonce не
знайдено:

![MFKey: nonce не знайдено](/img/remote/2519c7dce0b881c9.png)

HardNested — єдина атака, яку не можна виконати на Flipper. Варіанти:

- **qUnleashed** (рекомендовано, телефон або комп'ютер): `Tools → Recover MIFARE Keys`, див.
  [qUnleashed](/ua/nfc/qunleashed). Ключі одразу потрапляють до користувацького словника.
- **Комп'ютер із HardnestedRecovery**, як в оригінальному гайді:
  1. Скопіюйте `/ext/nfc/.nested.log` із microSD-картки Flipper на комп'ютер.
  2. Клонуйте та зберіть [github.com/noproto/HardnestedRecovery](https://github.com/noproto/HardnestedRecovery)
     командою `make build` (у Windows скористайтеся WSL або Docker).
  3. Запустіть програму, передавши лог аргументом:

     ```bash
     ./hardnested_main .nested.log
     ```

  4. Ключ з'явиться у виводі:

     ```text
     [=] Hardnested attack starting...
     [=]    0 |    0 | Start using 32 threads                 |                 |
     [=]    0 |    0 | Brute force benchmark: 589 million (2^29.1) keys/s   | 140737488355328 |  3d
     [=]   16 |  256 | Loading nonces from file                |     24286058496 |  41s
     [=]   46 | 1891 | Apply Sum property. Sum(a0) = 128            |      1262183296 |  2s
     [=]   78 | 1894 | Brute force phase completed. Key found: A3F92C8E7D3A  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: A: a3f92c8e7d3a
     ...
     [=]   70 | 1218 | Brute force phase completed. Key found: 4F6D91C5BA7E  |               0 |  0s
     Key found for UID: c66d2df2, Sector: 0, Key type: B: 4f6d91c5ba7e
     ```

::: danger Додайте ключі вручну
На відміну від 2.1, ключі, знайдені HardnestedRecovery на комп'ютері, **не** додаються автоматично. Додайте їх до
користувацького словника самостійно: `NFC → Extra Actions → MIFARE Classic Keys → Add` або дописавши їх у
`/ext/nfc/assets/mf_classic_dict_user.nfc`.
:::

## Крок 3. Перечитуємо мітку

Коли ключі відновлено, зчитайте мітку знову через `NFC → Read`.

::: tip Порада
Якщо ви зберегли мітку після першого зчитування, її можна розблокувати прямо з меню збереженої картки:
`Saved → <картка> → Unlock with Dictionary`.
:::

![Unlock with Dictionary з меню збереженої картки](/img/remote/8232d690446c70b6.png)

::: tip Порада
Щоб наступного разу все працювало швидше, очистьте `/ext/nfc/.nested.log` після того, як зламаєте ключі мітки.
:::

## Пов'язані сторінки

[MIFARE Classic](/ua/nfc/mifare-classic) · [Застосунок MFKey](/ua/nfc/mfkey-app) · [qUnleashed](/ua/nfc/qunleashed) ·
[MFKey32](/ua/nfc/mfkey) · [Зчитувачі Iron Logic](/ua/nfc/iron-logic) · більше статей у каналі автора
[@gromovyna](https://t.me/gromovyna)
