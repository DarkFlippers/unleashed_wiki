---
title: Підключення HID-пульта
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Підключення HID-пульта

Застосунок HID-пульта дозволяє керувати з Flipper презентаціями, вводити текст, рухати мишею й керувати
відтворенням медіа на комп’ютері чи телефоні. Ця сторінка — про **підключення**; що робить кожен режим, описано в
[Пульт USB / Bluetooth (HID)](/ua/apps/hid-remote).

Під’єднатися можна двома способами:

| | USB | Bluetooth LE |
|---|---|---|
| Застосунок | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Спарювання | не потрібне, просто під’єднайте | один раз на кожен хост |
| Працює з | комп’ютерами, телефонами з USB-C/OTG | комп’ютерами, Android, iPhone/iPad |

::: tip Unleashed
В Unleashed ці два варіанти називаються **USB Keyboard & Mouse** і **Bluetooth Remote** та лежать у папках
застосунків `USB` і `Bluetooth` (в офіційній документації обидва названі «Remote»).
:::

## Через USB

1. Під’єднайте Flipper до комп’ютера USB-кабелем із передачею даних. Спершу закрийте qFlipper — пульту потрібен
   USB-порт.
2. Відкрийте `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Виберіть режим (Keynote, Keyboard, Mouse…). Комп’ютер побачить нову клавіатуру/мишу, драйвер не потрібен.

Коли ви вийдете із застосунку, USB Flipper повернеться у звичайний (послідовний) режим.

## Через Bluetooth

1. Увімкніть Bluetooth на комп’ютері чи телефоні.
2. На Flipper: `Main Menu → Settings → Bluetooth` і переведіть **Bluetooth** у стан **ON**.
3. Відкрийте `Main Menu → Apps → Bluetooth → Bluetooth Remote` і виберіть режим.
4. На комп’ютері чи телефоні відкрийте налаштування Bluetooth і під’єднайтеся до
   **Control &lt;Flipper name&gt;** (на телефоні натисніть **Pair**).
5. Якщо Flipper покаже запит на підтвердження спарювання, натисніть <kbd>OK</kbd>.

Наступного разу хост перепід’єднається автоматично, коли ви відкриєте Bluetooth Remote.

::: tip Своя назва
`Bluetooth Remote → Bluetooth Remote Name` змінює назву, під якою пульт видно під час пошуку, — зручно, якщо у вас
кілька пультів Flipper або ви хочете, щоб він виглядав як звичайна клавіатура.
:::

### Якщо спарювання не вдається

- Переконайтеся, що Bluetooth увімкнено (ON) у `Settings → Bluetooth`.
- Видаліть старий запис «Control …» у налаштуваннях Bluetooth на хості, потім на Flipper виконайте
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` і спаруйте знову.
- Від’єднайте Flipper від інших пристроїв (наприклад, від мобільного застосунку).
- Перезавантажте Flipper: утримуйте <kbd>←</kbd> + <kbd>Back</kbd> близько 5 секунд.
- Оновіть прошивку.

Пульт тримає власні спарювання (`/ext/apps_data/hid_ble/.bt_hid.keys`) окремо від основного Bluetooth Flipper, яким
користується мобільний застосунок. **Bluetooth Unpairing** у самому пульті очищає лише хостів пульта. Глобальний
`Settings → Bluetooth → Unpair All Devices` очищає все: і спарювання з мобільним застосунком, і спарювання пульта
(та BadKB).

### iPhone / iPad: режим TikTok не реагує

1. На iPhone відкрийте `Settings → Accessibility → Touch → AssistiveTouch`.
2. Увімкніть **AssistiveTouch**.
3. У розділі **Pointer Devices** перейдіть до **Devices → Bluetooth Devices** і виберіть свій Flipper.

## Пов’язані сторінки

- [Пульт USB / Bluetooth (HID)](/ua/apps/hid-remote)
- [Налаштування](/ua/start/settings)
- [Мобільний застосунок Flipper](/ua/mobile/mobile-app)
