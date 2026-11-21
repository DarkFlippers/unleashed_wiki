---
title: "MFKey32: ключі зі зчитувача"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: відновлення ключів зі зчитувача

**MFKey32** — це атака на шифр Crypto-1 у MIFARE Classic. Flipper видає себе за картку; зчитувач намагається
аутентифікуватися своїм справжнім ключем, і двох пар nonce/відповідь, які він надсилає, достатньо, щоб обчислити цей
ключ офлайн. Тобто атаці потрібен **доступ до зчитувача**, а не до ключів.

Коли це доречно:

- картка зчитується лише частково, а бракує саме тих ключів, які використовує зчитувач (найчастіший випадок);
- картки у вас немає взагалі, але ви хочете дізнатися ключі зчитувача й додати їх до свого словника;
- у картки немає бекдора й жодного відомого ключа, тому [nested-атаки](/ua/nfc/nested-fudan) не можуть почати роботу.

## З карткою та зчитувачем (рекомендовано)

Якщо картка у вас є, то після відновлення ключів зчитувача ви зможете зчитати більше секторів — а саме їх зчитувач
зазвичай і перевіряє.

1. Зчитайте картку (`Main Menu → NFC → Read`). Вона зчитається частково.
2. У **More** виберіть **Extract MFC Keys**. Flipper запитає *"Save the Key?"*: **Save** (дамп знадобиться потім)
   або **Skip**.
   *Як альтернатива*, відкрийте вже збережену картку: `Main Menu → NFC → Saved → <картка> → Extract MFC Keys`.
3. На екрані з'явиться **"Emulating... MIFARE MFkey32"** з UID картки та підказкою *"Touch the reader"*.

   ![Емуляція MIFARE MFkey32 з UID картки та підказкою прикласти до зчитувача](/screens/nfc/mfkey_start.png)

4. Прикладіть Flipper задньою стінкою до зчитувача, відведіть його (*"Move the Flipper away"*), прикладіть знову
   (*"Touch the reader again"*). Лічильник **Nonce pairs: X/10** збільшується з кожною успішною спробою.

   ![Збір пар nonce: зібрано 4 з 10, підказка відвести Flipper](/screens/nfc/mfkey_collecting.png)

5. Коли зібрано 10 пар, на екрані з'явиться **Completed!**. Можна зупинитися раніше кнопкою <kbd>OK</kbd> **Done**.
6. Наступний екран показує **Nonce pairs saved: N** і **Authenticated sectors** (який сектор і тип ключа запитував
   зчитувач). Натисніть <kbd>OK</kbd>.

   ![Nonce pairs saved: 5 зі списком аутентифікованих секторів і типів ключів](/screens/nfc/mfkey_nonces_info.png)

7. Flipper запропонує відновити ключі: **"Now run Mfkey32 to extract keys"** з кнопкою **Run** (відкриває
   [застосунок MFKey](/ua/nfc/mfkey-app)). Якщо застосунку немає, показується QR-код на `r.flipper.net/nfc-tools`
   і кнопка **Finish**.
8. Відновіть ключі одним з інструментів, описаних нижче. Вони додаються до користувацького словника.
9. Зчитайте картку знову (або `Saved → <картка> → Unlock with Dictionary`). Тепер мають знайтися додаткові ключі
   та сектори.
10. Емулюйте картку або запишіть її на заготовку.

Nonce зберігаються в `/ext/nfc/.mfkey32.log`, по одному рядку на пару:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Лічильник не збільшується?
Зчитувач не намагається аутентифікувати емульовану картку. Деякі зчитувачі перевіряють лише UID або використовують
інший протокол; інші взагалі відкидають емуляцію. Спробуйте різні відстані та кути; іноді на одну пару потрібно
кілька прикладань.
:::

## Лише зчитувач

1. Перейдіть до `Main Menu → NFC → Extract MFC Keys`. Flipper емулює узагальнену картку MIFARE Classic.
2. Кроки 3–8 — як вище.
3. Відновлені ключі потрапляють до користувацького словника й надалі автоматично перевіряються, коли ви зчитуєте
   картки цієї системи.

## Відновлення ключів із nonce

| Інструмент | Де | Примітки |
|---|---|---|
| **Застосунок MFKey** на Flipper | `Main Menu → Apps → NFC → MFKey` | Телефон чи ПК не потрібні. Працює з `.mfkey32.log` і `.nested.log`. Повільніший. Див. [застосунок MFKey](/ua/nfc/mfkey-app). |
| **qUnleashed** (супутній застосунок Unleashed) | `Tools → Recover MIFARE Keys` | Обробляє `.mfkey32.log` і `.nested.log`, включно з hard- та static encrypted nonce. Швидко. Див. [qUnleashed](/ua/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Офіційний застосунок, лише nonce зі зчитувача. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | Через USB у браузері. |

::: tip Unleashed
В Unleashed пункт меню називається **Extract MFC Keys** (у стоку — *Extract MF Keys*), а супутній застосунок
**qUnleashed** уміє відновлювати ключі безпосередньо на телефоні або комп'ютері. Починаючи з **MFKey 4.x**
(dev-білд Unleashed 1251+) відновлення на самому Flipper стало в кілька разів швидшим — див.
[застосунок MFKey](/ua/nfc/mfkey-app).
:::

## Якщо відновлення не вдається

- **З nonce не знайдено жодного ключа**: зчитувач не прийняв емуляцію Flipper як слід. Зберіть nonce знову,
  спробуйте інший дамп картки (збережена справжня картка працює краще за узагальнену емуляцію).
- **MFKey показує "No nonces found"**: немає ні `.mfkey32.log`, ні `.nested.log`.
- **MFKey зависає або падає**: перезавантажте пристрій (утримуйте <kbd>←</kbd> + <kbd>Back</kbd> 5 секунд),
  видаліть `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log`, зберіть nonce знову.
- **Останній засіб**: зробіть резервну копію й видаліть `/ext/nfc/assets/mf_classic_dict_user.nfc` (це прибере
  **всі** ваші користувацькі ключі).

## Пов'язані сторінки

[MIFARE Classic](/ua/nfc/mifare-classic) · [Nested-атаки](/ua/nfc/nested-fudan) · [Застосунок MFKey](/ua/nfc/mfkey-app) ·
[qUnleashed](/ua/nfc/qunleashed)
