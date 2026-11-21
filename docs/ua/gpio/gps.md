---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Є два способи дати Flipper координати:

| Варіант | Обладнання | Як працює |
|---|---|---|
| **Служба GPS (місцеположення від компаньйона)** | Жодного: смартфон або комп'ютер, підключений через USB чи Bluetooth | Застосунки запитують місцеположення в підключеного супутнього застосунку через RPC |
| **NMEA-GPS-модуль** | Послідовний GPS-приймач на UART гребінки GPIO | Плагін `[NMEA] GPS` читає з модуля NMEA-рядки |

## Служба GPS (місцеположення від компаньйона)

::: tip Unleashed
Прошивка Unleashed містить системну службу `gps` (запис `gps`, запускається під час завантаження). Вона не
використовує жодних пінів GPIO: вона переадресовує запити місцеположення через активну **RPC-сесію** (USB або
Bluetooth) супутньому застосунку, який відповідає позицією смартфона чи комп'ютера.
:::

Що застосунок отримує від неї:

| Поле | Одиниця |
|---|---|
| Широта, довгота | градуси × 10⁷ |
| Курс | градуси × 100 (0…36000) |
| Швидкість | мм/с |
| Висота | см |
| Точність | мм |
| Супутники | кількість |

Застосунки можуть запросити одноразову позицію (`gps_request_location()`), потік із частотою **1–10 Гц**
(`gps_request_stream()` / `gps_stop_stream()`), а також надіслати місцеположення назад компаньйону
(`gps_report_location()`). Компаньйон може відповісти помилкою: не підтримується, немає дозволу, геолокація
вимкнена, невідома помилка.

### Як це спробувати

У дереві початкового коду є два приклади застосунків від @apfxtech (категорія `Examples`, збираються як FAP):

- **`[RPC] GPS Click`** — одноразовий запит: натисніть <kbd>OK</kbd>, щоб отримати місцеположення; показує
  широту, довготу, курс, швидкість, висоту, супутники й точність. <kbd>BACK</kbd> виходить.
- **`[RPC] GPS Stream`** — безперервний потік тих самих даних.

Повідомлення, які можна побачити:

| Повідомлення | Що означає |
|---|---|
| `No USB/BLE connection` | Немає RPC-сесії: підключіть супутній застосунок через USB або Bluetooth |
| `GPS not available` | Компаньйон не підтримує геолокацію |
| `Permission denied` | Супутньому застосунку не надано дозвіл на геолокацію |
| `Location disabled` | Служби геолокації вимкнені на смартфоні чи комп'ютері |
| `No response` | Компаньйон не відповів у відведений час |
| `Waiting for data...` | Потік запущено, позиції ще немає |

Супутній застосунок мусить підтримувати ці RPC-запити GPS; перевірте свій компаньйон (див.
[Мобільні застосунки](/ua/mobile/)).

Розробникам застосунків: підключіть `<gps/gps.h>` і відкрийте запис через `furi_record_open(RECORD_GPS)`; у
заголовку також є допоміжні функції для форматування координат, курсу, швидкості, висоти й точності.

## NMEA-GPS-модуль на UART

Щоб отримати координати без смартфона, підключіть послідовний GPS-приймач (більшість модулів, що видають
NMEA-рядки з логікою 3,3 В).

Підключення (USART):

| Пін Flipper | GPS-модуль |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) або 1 (5V) | VCC (перевірте діапазон живлення модуля) |
| 8, 11 або 18 (GND) | GND |

Далі відкрийте плагін `[NMEA] GPS` із додаткових пакетів застосунків. Налаштування, швидкість передавання та
підтримувані модули описані в його
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
GPS-модуль та інші користувачі UART (Wi-Fi-плати, SIM800, модулі розширення, вивід логів) ділять піни 13/14. Якщо
плагін не отримує даних, перевірте `Settings → Expansion Modules → Listen UART` і
`Settings → System → Log Device`.
:::

## Застосунки

Застосунки, які працюють із GPS-модулем, усі з паків:

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Координати з будь-якого GPS-модуля NMEA на UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Показує та логує дані GPS-модулів u-blox через I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Трекер NMEA з навігацією за точками |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Файловий браузер, який сортує файли за відстанню від вас |

Повний список застосунків для модулів: [Модулі та застосунки для них](/ua/gpio/module-apps).

## Пов'язані сторінки

- [ESP32 і Wi-Fi](/ua/gpio/esp32) — карта вардрайвінгу
- [Зовнішні модулі](/ua/gpio/external-modules)
- [Розпіновка GPIO](/ua/gpio/pinout)
