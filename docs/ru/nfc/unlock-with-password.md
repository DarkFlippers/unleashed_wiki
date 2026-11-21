---
title: Разблокировка паролем
order: 65
original: [https://docs.flipper.net/zero/nfc/unlock-with-password, https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc]
sources: [flipper-docs, unleashed-src]
---
# Разблокировка меток паролем и ключом

Метки со страничной памятью (MIFARE Ultralight, NTAG) могут защищать часть памяти. Если `Read` показывает
**«Some Pages Are Locked!»** / **«Password-protected pages!»** и `Pages Read: X/Y` при X < Y, метке нужен пароль или
ключ. В зависимости от метки:

| Метка | Защита | Как Флиппер её открывает |
|---|---|---|
| NTAG21x, Ultralight EV1 (11/21) | 4-байтный пароль (PWD) + 2-байтный PACK | перехват со считывателя, генерация по UID (amiibo, Xiaomi) или ручной ввод |
| Ultralight C | 16-байтный ключ 3DES | атака по словарю (автоматически) или ручной ввод ключа |
| Ultralight AES | 16-байтный ключ AES | атака по словарю (автоматически) или ручной ввод, см. [Ultralight AES](/ru/nfc/ultralight-aes) |
| ICODE SLIX-L | 4-байтный пароль | `Extra Actions → Unlock SLIX-L` |

::: danger Неверный пароль может заблокировать метку
Многие метки считают неудачные попытки (`AUTHLIM`) и навсегда блокируются после превышения. Перед попыткой Флиппер
предупреждает: **«Risky action! Wrong password can block your card.»** Не перебирайте пароли наугад.
:::

## Перехват пароля со считывателя

Если есть метка и считыватель, который её принимает: эмулируйте метку, дайте считывателю отправить пароль, перехватите
его и прочитайте метку с ним.

1. [Прочитайте и сохраните](/ru/nfc/read) метку.
2. Откройте `Main Menu → NFC → Saved → <метка> → Unlock`.
3. Выберите **Unlock With Reader**. На экране *«Touch the reader to get password...»* — приложите Флиппер к
   считывателю.
4. Когда пароль перехвачен, появится **Password Captured!** и его значение. Нажмите **Continue**.
5. Приложите метку к задней стороне Флиппера (*«Hold card next to Flipper's back»*, затем *«Don't move»*).
6. Когда страницы открыты (**«All Pages Are Unlocked!»**), **More → Save**, задайте имя и сохраните.

Если ничего не перехвачено (*«Password not captured.»*), считыватель может не использовать пароль, либо метка от
другого считывателя.

Для Ultralight C пункт `Unlock With Reader` не показывается: там взаимная аутентификация 3DES, пароль в открытом виде
не передаётся.

## Генерация пароля по UID

Для **игрушек toys-to-life** (amiibo-подобные NTAG215) и фильтров **Xiaomi Air Purifier** пароль вычисляется из UID
метки.

1. Откройте `Main Menu → NFC → Extra Actions → Unlock NTAG/Ultralight`
   (или для сохранённой метки — `Saved → <метка> → Unlock`).
2. Выберите **Auth As Ameebo** или **Auth As Xiaomi Air Purifier**.
3. Подтвердите предупреждение и приложите метку.
4. Когда страницы открыты, сохраните метку (**Save**).

## Ручной ввод пароля

1. `Main Menu → NFC → Saved → <метка> → Unlock` (или `Extra Actions → Unlock NTAG/Ultralight` до чтения).
2. Выберите **Enter Password Manually**.
3. **«Enter the password in hex»** — введите 4 байта, подтвердите.
4. Подтвердите предупреждение *«Try to unlock the card with password: …»* и приложите метку.
5. Сохраните разблокированную метку.

## Ultralight C: ключи 3DES

Ultralight C использует 16-байтный ключ 3DES. У Флиппера есть встроенный словарь известных ключей
(`/ext/nfc/assets/mf_ultralight_c_dict.nfc`, 50 ключей, включая тестовый ключ NXP `BREAKMEIFYOUCAN!`) и
пользовательский словарь (`mf_ultralight_c_dict_user.nfc`).

- При `Read`, если метка не читается полностью, атака по словарю запускается сама: заголовки
  **«MFUL C User Dictionary»**, затем **«MFUL C System Dictionary»**, с `Key found: Yes/No` и `Pages read: X/Y`.
- У сохранённой неполной метки: **Unlock with Dictionary** — повторить атаку; **Unlock** спросит **«Enter key in hex»**
  (16 байт), затем **«Risky Action! Unlock with key: … ?»** с кнопками **Unlock** / **Cancel**.
- Свои ключи: `Main Menu → NFC → Extra Actions → MIFARE Ultralight C Keys → Add`.

Полностью прочитанный дамп Ultralight C предлагает **Write (Keep Key)** (оставляет 3DES-ключ целевой метки) и
**Write (Copy Key)** (записывает и страницы ключа из дампа) — на метку того же типа.

::: tip Unleashed
Ручной ввод ключей 3DES/AES, запись Ultralight C/AES с Keep/Copy Key и словарь Ultralight AES
(`Extra Actions → MIFARE UL AES Keys`) — возможности Unleashed.
:::

## ICODE SLIX-L

1. Откройте `Main Menu → NFC → Extra Actions → Unlock SLIX-L`.
2. **Enter Password Manually** (4 байта в hex) или **Auth As TommyBox** (известный пароль меток TommyBox).
3. Приложите метку (*«Unlocking — Hold card next to Flipper's back»*).
4. На экране **SLIX Unlocked!** нажмите **More**, чтобы перейти к результату чтения и сохранить его, или **Retry**.

## Если разблокировать не удалось

- Метка может быть привязана к другому считывателю или использовать пароль, вычисляемый для каждой метки.
- Пароль верный, но часть страниц закрыта: lock-биты или настройки `AUTH0`/`PROT` могут делать страницы навсегда
  read-only или нечитаемыми без аутентификации.
- Для Ultralight AES смотрите замечание о порядке байтов ключа на странице [Ultralight AES](/ru/nfc/ultralight-aes).

## См. также

[Чтение меток](/ru/nfc/read) · [Ultralight AES](/ru/nfc/ultralight-aes) · [Фильтры Vizit](/ru/nfc/vizit-filters) ·
[Формат файлов NFC](/ru/nfc/file-format)
