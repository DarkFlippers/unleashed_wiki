---
title: Подключение HID-пульта
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# Подключение HID-пульта

HID-пульт превращает Flipper в клавиатуру, мышь или медиапульт для компьютера или телефона. Здесь —
**подключение**; что делает каждый режим, см. [USB / Bluetooth-пульт (HID)](/ru/apps/hid-remote).

Подключиться можно двумя способами:

| | USB | Bluetooth LE |
|---|---|---|
| Приложение | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Сопряжение | не нужно, просто подключите | один раз для каждого хоста |
| Работает с | компьютерами, телефонами с USB-C/OTG | компьютерами, Android, iPhone/iPad |

::: tip Unleashed
В Unleashed два варианта называются **USB Keyboard & Mouse** и **Bluetooth Remote** и лежат в папках приложений `USB`
и `Bluetooth` (в официальной документации оба называются "Remote").
:::

## По USB

1. Подключите Flipper к компьютеру USB-кабелем с передачей данных. Сначала закройте qFlipper — пульту нужен USB-порт.
2. Откройте `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Выберите режим (Keynote, Keyboard, Mouse...). Компьютер увидит новую клавиатуру/мышь, драйвер не нужен.

При выходе из приложения USB Flipper возвращается в обычный (serial) режим.

## По Bluetooth

1. Включите Bluetooth на компьютере или телефоне.
2. На Flipper: `Main Menu → Settings → Bluetooth`, переключите **Bluetooth** в **ON**.
3. Откройте `Main Menu → Apps → Bluetooth → Bluetooth Remote` и выберите режим.
4. На компьютере или телефоне откройте настройки Bluetooth и подключитесь к **Control &lt;имя Flipper&gt;** (на телефоне
   нажмите **Pair** / «Создать пару»).
5. Если Flipper покажет запрос подтверждения сопряжения, нажмите <kbd>OK</kbd>.

В следующий раз хост подключится автоматически, когда вы откроете Bluetooth Remote.

::: tip Своё имя
`Bluetooth Remote → Bluetooth Remote Name` меняет имя, под которым виден пульт, — удобно, если пультов-Flipper
несколько или нужно, чтобы он выглядел как обычная клавиатура.
:::

### Если сопряжение не удаётся

- Убедитесь, что Bluetooth включён (ON) в `Settings → Bluetooth`.
- Удалите старую запись "Control ..." в настройках Bluetooth хоста, затем на Flipper выполните
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` и выполните сопряжение заново.
- Отключите Flipper от других устройств (например, от мобильного приложения).
- Перезагрузите Flipper: удерживайте <kbd>←</kbd> + <kbd>Back</kbd> около 5 секунд.
- Обновите прошивку.

Пульт хранит свои сопряжения отдельно (`/ext/apps_data/hid_ble/.bt_hid.keys`) от основного Bluetooth Flipper,
которым пользуется мобильное приложение. **Bluetooth Unpairing** внутри пульта очищает только хосты пульта. Глобальный
`Settings → Bluetooth → Unpair All Devices` очищает всё: сопряжение с мобильным приложением, а также сопряжения пульта
(и BadKB).

### iPhone / iPad: режим TikTok не реагирует

1. На iPhone откройте `Settings → Accessibility → Touch → AssistiveTouch` («Настройки → Универсальный доступ →
   Касание → AssistiveTouch»).
2. Включите **AssistiveTouch**.
3. В разделе **Pointer Devices** («Указывающие устройства») перейдите в **Devices → Bluetooth Devices** и выберите
   свой Flipper.

## Связанные страницы

- [USB / Bluetooth-пульт (HID)](/ru/apps/hid-remote)
- [Настройки](/ru/start/settings)
- [Мобильное приложение Flipper](/ru/mobile/mobile-app)
