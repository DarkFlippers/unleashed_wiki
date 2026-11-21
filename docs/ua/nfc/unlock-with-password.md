---
title: Розблокування карток паролем
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Розблокування карток паролями та ключами

Картки з посторінковою організацією пам'яті (**MIFARE Ultralight**, **NTAG**) можуть захищати частину своєї
пам'яті. Якщо `Read` показує **«Some Pages Are Locked!»** / **«Password-protected pages!»** і `Pages Read: X/Y`,
де X < Y, то картці потрібен пароль або ключ. Залежно від картки:

| Картка | Захист | Як Flipper її розблоковує |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | 4-байтовий пароль (PWD) + 2-байтовий PACK | перехоплення зі зчитувача, генерування з UID (amiibo, Xiaomi) або введення вручну |
| Ultralight C | 16-байтовий ключ 3DES | словникова атака (автоматично) або введення ключа вручну |
| Ultralight AES | 16-байтовий ключ AES | словникова атака (автоматично) або введення ключа вручну, див. [Ultralight AES](/ua/nfc/ultralight-aes) |
| ICODE SLIX-L | 4-байтовий пароль | `Extra Actions → Unlock SLIX-L` |

::: danger Хибні паролі можуть заблокувати картку
Багато карток рахують невдалі автентифікації (`AUTHLIM`) і після певної кількості блокуються назавжди. Flipper
попереджає **«Risky action! Wrong password can block your card.»** перед спробою пароля. Не робіть перебору.
:::

## Перехоплення пароля зі зчитувача

Якщо у вас є і картка, і зчитувач, який її приймає: емулюйте картку, дайте зчитувачу надіслати свій пароль,
перехопіть його, а потім прочитайте картку з цим паролем.

1. [Зчитайте й збережіть](/ua/nfc/read) картку.
2. Перейдіть до `Main Menu → NFC → Saved → <картка> → Unlock`.
3. Виберіть **Unlock With Reader**. На екрані з'явиться *«Touch the reader to get password...»*. Піднесіть Flipper
   до зчитувача.
4. Коли пароль перехоплено, ви побачите **Password Captured!** із його значенням. Натисніть **Continue**.
5. Піднесіть картку до задньої частини Flipper (*«Hold card next to Flipper's back»*, потім *«Don't move»*).
6. Коли сторінки розблоковано (**«All Pages Are Unlocked!»**), перейдіть до **More → Save**, назвіть картку й
   збережіть її.

Якщо нічого не перехоплено (*«Password not captured.»*), то зчитувач, можливо, не використовує пароль, або картка
належить іншому зчитувачу.

Для Ultralight C пункт `Unlock With Reader` не пропонується (там взаємна автентифікація 3DES, і пароль не
передається у відкритому вигляді).

## Генерування пароля з UID

Для фігурок **toys-to-life** (NTAG215 на кшталт amiibo) і фільтрів **Xiaomi Air Purifier** пароль виводиться з
UID картки.

1. Перейдіть до `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (або, для збереженої картки, `Saved → <картка> → Unlock`).
2. Виберіть **Auth As Ameebo** або **Auth As Xiaomi Air Purifier**.
3. Підтвердьте попередження й піднесіть картку до Flipper.
4. Коли сторінки розблоковано, збережіть картку через **Save**.

## Введення пароля вручну

1. `Main Menu → NFC → Saved → <картка> → Unlock` (або `Extra Actions → Unlock NTAG/Ultralight` ще до зчитування).
2. Виберіть **Enter Password Manually**.
3. **«Enter the password in hex»**: введіть 4 байти й підтвердьте.
4. Підтвердьте попередження *«Try to unlock the card with password: …»* і піднесіть картку до Flipper.
5. Збережіть розблоковану картку через **Save**.

## Ultralight C: ключі 3DES

Картки Ultralight C використовують 16-байтовий ключ 3DES. У Flipper є вбудований словник відомих ключів
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 ключів, включно з демонстраційним ключем NXP
`BREAKMEIFYOUCAN!`) і користувацький словник (`mf_ultralight_c_dict_user.nfc`).

- Під час `Read`, якщо картка читається не повністю, словникова атака запускається сама: заголовки
  **«MFUL C User Dictionary»**, потім **«MFUL C System Dictionary»**, із `Key found: Yes/No` і
  `Pages read: X/Y`.
- Для збереженої не до кінця зчитаної картки: **Unlock with Dictionary** запускає атаку повторно; **Unlock**
  запитує **«Enter key in hex»** (16 байтів), а потім **«Risky Action! Unlock with key: … ?»** з варіантами
  **Unlock** / **Cancel**.
- Додати власні ключі: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Повністю зчитаний дамп Ultralight C пропонує **Write (Keep Key)** (залишає ключ 3DES цільової картки) і
**Write (Copy Key)** (записує також сторінки ключа з дампа) на картку того самого типу.

::: tip Unleashed
Введення ключів 3DES/AES вручну, зворотний запис Ultralight C/AES із Keep/Copy Key і словник Ultralight AES
(`Extra Actions → MIFARE UL AES Keys`) — це можливості Unleashed.
:::

## ICODE SLIX-L

1. Перейдіть до `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. Виберіть **Enter Password Manually** (4 байти в шістнадцятковій формі) або **Auth As TommyBox** (відомий
   пароль міток TommyBox).
3. Піднесіть мітку до Flipper (*«Unlocking — Hold card next to Flipper's back»*).
4. Після **SLIX Unlocked!** натисніть **More**, щоб перейти до результату зчитування й зберегти його, або
   **Retry**.

## Якщо розблокувати не вдалося

- Картка може бути спарована з іншим зчитувачем або використовувати ключ, виведений окремо для кожної картки.
- Пароль правильний, але частина сторінок залишається заблокованою: біти блокування або налаштування
  `AUTH0`/`PROT` можуть робити сторінки назавжди доступними лише для читання чи взагалі нечитними без
  автентифікації.
- Щодо Ultralight AES див. примітку про порядок байтів на сторінці
  [Ultralight AES](/ua/nfc/ultralight-aes).

## Пов'язані сторінки

[Зчитування міток](/ua/nfc/read) · [Ultralight AES](/ua/nfc/ultralight-aes) ·
[Фільтри зчитувачів Vizit](/ua/nfc/vizit-filters) · [Формат файлів NFC](/ua/nfc/file-format)
