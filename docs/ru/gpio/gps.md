---
title: GPS
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/gps, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/examples/example_gps, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# GPS

Дать Flipper координаты можно двумя способами:

| Вариант | Железо | Как работает |
|---|---|---|
| **Сервис GPS (координаты компаньона)** | Никакого: телефон или компьютер, подключённый по USB или Bluetooth | Приложения запрашивают координаты у подключённого приложения-компаньона по RPC |
| **NMEA GPS-модуль** | GPS-приёмник с UART на GPIO | Плагин `[NMEA] GPS` читает NMEA-строки с модуля |

## Сервис GPS (координаты компаньона)

::: tip Unleashed
В прошивке Unleashed есть системный сервис `gps` (запись `gps`, стартует при загрузке). GPIO он не использует: запросы
координат уходят через активную **RPC-сессию** (USB или Bluetooth) приложению-компаньону, а оно отвечает положением
телефона / компьютера.
:::

Что получает приложение:

| Поле | Единицы |
|---|---|
| Широта, долгота | градусы × 10⁷ |
| Курс | градусы × 100 (0…36000) |
| Скорость | мм/с |
| Высота | см |
| Точность | мм |
| Спутники | количество |

Приложение может запросить одну точку (`gps_request_location()`), поток с частотой **1–10 Гц** (`gps_request_stream()` /
`gps_stop_stream()`), а также отправить координаты компаньону (`gps_report_location()`). Компаньон может ответить
ошибкой: не поддерживается, нет разрешения, геолокация выключена, неизвестная ошибка.

### Попробовать

В исходниках есть два примера от @apfxtech (категория `Examples`, собираются как FAP):

- **`[RPC] GPS Click`** — разовый запрос: <kbd>OK</kbd> — получить координаты; показывает широту, долготу, курс,
  скорость, высоту, число спутников и точность. <kbd>BACK</kbd> — выход.
- **`[RPC] GPS Stream`** — непрерывный поток тех же данных.

Возможные сообщения:

| Сообщение | Значение |
|---|---|
| `No USB/BLE connection` | Нет RPC-сессии: подключите приложение-компаньон по USB или Bluetooth |
| `GPS not available` | Компаньон не поддерживает геолокацию |
| `Permission denied` | Приложению-компаньону не выдано разрешение на геолокацию |
| `Location disabled` | Геолокация на телефоне / компьютере выключена |
| `No response` | Компаньон не ответил вовремя |
| `Waiting for data...` | Поток запущен, координат пока нет |

Приложение-компаньон должно поддерживать эти RPC-запросы GPS; уточните это для своего приложения (см. раздел
[Мобильные приложения](/ru/mobile/)).

Разработчикам: подключите `<gps/gps.h>` и откройте запись через `furi_record_open(RECORD_GPS)`; в заголовке есть
функции форматирования координат, курса, скорости, высоты и точности.

## NMEA GPS-модуль на UART

Чтобы получать координаты без телефона, подключите GPS-приёмник с UART (большинство модулей, выдающих NMEA-строки с
логикой 3,3 В).

Подключение (USART):

| Пин Flipper | GPS-модуль |
|---|---|
| 13 (TX) | RX |
| 14 (RX) | TX |
| 9 (3V3) или 1 (5V) | VCC (проверьте допустимое питание модуля) |
| 8, 11 или 18 (GND) | GND |

Затем откройте плагин `[NMEA] GPS` из дополнительных паков. Настройка, скорость и поддерживаемые модули — в его
[README](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md).

::: tip
GPS-модуль делит пины 13/14 с другими пользователями UART (Wi-Fi платы, SIM800, expansion-модули, вывод логов). Если
плагин не получает данных, проверьте `Settings → Expansion Modules → Listen UART` и `Settings → System → Log Device`.
:::

## Приложения

Приложения, которые работают с GPS-модулем, все из паков:

| Приложение | Пак | Что делает |
|---|---|---|
| [\[NMEA\] GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/gps_nmea_uart) | Base | Координаты с любого GPS-модуля NMEA на UART |
| [u-blox GPS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ublox) | Extra | Показывает и логирует данные GPS-модулей u-blox по I2C |
| [GPS Track](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/gps_track) | Extra | Трекер NMEA с навигацией по точкам |
| [Nearby Files](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nearby_files) | Base | Файловый браузер, который сортирует файлы по расстоянию от вас |

Полный список приложений для модулей: [Модули и приложения для них](/ru/gpio/module-apps).

## См. также

- [ESP32 и Wi-Fi](/ru/gpio/esp32) — карта вардрайвинга
- [Внешние модули](/ru/gpio/external-modules)
- [Распиновка GPIO](/ru/gpio/pinout)
