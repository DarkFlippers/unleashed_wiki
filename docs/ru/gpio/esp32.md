---
title: ESP32 и Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 и Wi-Fi

Своего Wi-Fi у Flipper Zero нет. Wi-Fi-инструменты появляются с платой на **ESP32** (или ESP8266) в GPIO-разъёме:
радиочасть работает на ней, а с приложением на Flipper она общается по UART.

## Какая плата

| Плата | Для чего обычно |
|---|---|
| **Официальная Wi-Fi Developer Board** (ESP32-S2) | Поставляется с прошивкой отладчика Black Magic для [отладки](/ru/gpio/devboard). Можно перепрошить на Marauder |
| **Платы под ESP32 Marauder** (разные ESP32 / ESP32-S2 / ESP32-S3, комбо-платы) | Сканирование Wi-Fi и BLE, захват пакетов, вардрайвинг |
| **Платы на ESP8266** | Прошивки Wi-Fi Scanner и Deauther |
| **ESP32-CAM** | Camera Suite (изображение с камеры на экране Flipper) |

## Приложения

Каждое из них — только половина пары: на плату сначала нужно прошить соответствующую прошивку.

| Приложение | Пак | Что делает |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Интерфейс для прошивки Marauder: сканирование Wi-Fi и BLE, захват пакетов, вардрайвинг |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Список Wi-Fi сетей рядом, для прошивки Scanner на ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Интерфейс для прошивки DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Картинка с ESP32-CAM на экране Flipper и съёмка фото |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Второе приложение для ESP32-CAM: живое видео и фото |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Интерфейс для прошивки Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Поднимает на ESP32 точку доступа с captive-порталом |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Для прошивки Deauther v2 от @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Прошивает плату ESP прямо с Flipper, по UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Запускает веб-хук IFTTT через ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Картирование Wi-Fi сетей с ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Показывает лицо и статус Pwnagotchi на экране Flipper, по UART |

Полный список приложений для модулей: [Модули и приложения для них](/ru/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) от justcallmekoko — прошивка для плат ESP32. На
Flipper с ней работают через приложение **WiFi Marauder** из дополнительных паков: оно отправляет команды плате и
показывает её вывод.

Обычный порядок:

1. **Прошейте Marauder** на плату ESP32 (см. прошивальщик ниже).
2. Выключите Flipper, вставьте плату в GPIO-разъём, включите.
3. Откройте приложение Marauder в `Apps → GPIO` и выберите команду (сканирование точек доступа, сниффинг, вардрайвинг и
   т. д.).
4. Результаты отображаются в приложении; захваты и логи вардрайвинга сохраняются согласно настройкам платы и
   приложения (см. документацию Marauder для вашей платы).

Полное руководство по Wi-Fi Devboard с Marauder (от UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Закон
Сканирование пассивно, но деаутентификация и другие активные атаки на Wi-Fi незаконны в отношении сетей, которые вам не
принадлежат или которые вам не разрешили тестировать.
:::

## ESP32 Web Flasher

::: tip Unleashed
Команда Unleashed поддерживает браузерный прошивальщик для популярных модулей ESP32:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Он работает полностью в браузере, esptool
ставить не нужно. Нужен браузер с поддержкой Web Serial (на базе Chromium).
:::

Общий порядок:

1. Отсоедините плату ESP32 от Flipper и подключите её к компьютеру по USB.
2. Если плата сама не входит в режим прошивки: зажмите **BOOT**, нажмите **RESET**, отпустите **BOOT**.
3. Откройте прошивальщик, выберите плату и прошивку, нажмите подключение и выберите последовательный порт платы.
4. Дождитесь окончания, перезагрузите плату и вставьте обратно во (выключенный) Flipper.

Другие способы прошить плату ESP:

- Приложение **ESP flasher** для Flipper — прошивает `.bin` с SD-карты Flipper через GPIO UART:
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Инструкция для Windows (esptool / Flash Download Tool):
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- [USB-UART Bridge в приложении GPIO](/ru/gpio/gpio-app) с `RTS/DTR Pins` может служить USB-адаптером для плат без
  своего USB-порта.

::: tip Как вернуть прошивку отладчика
Если вы прошили Marauder на официальную Wi-Fi Devboard и хотите вернуть Black Magic, перепрошейте её командой
`ufbt devboard_flash`, как описано в [Devboard: обновление прошивки](/ru/gpio/devboard-firmware).
:::

## Карта вардрайвинга Wi-Fi

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** объединяет и показывает на одной карте несколько
захватов вардрайвинга в формате WiGLE из ESP32 Marauder и других инструментов.
:::

1. Проведите вардрайвинг с Marauder (для вардрайвинга к плате ESP32 нужен GPS-модуль).
2. Скопируйте логи CSV в формате WiGLE на компьютер.
3. Откройте карту и загрузите один или несколько файлов — сети будут нанесены вместе.

Для Sub-GHz-записей и других файлов с координатами есть отдельная карта:
[map.unleashedflip.com](https://map.unleashedflip.com).

## Другие прошивки для ESP

| Прошивка | Плата | Ссылки |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Как пользоваться](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Как пользоваться](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Web Flasher](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Как пользоваться](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Соответствующие приложения для Flipper — в паках Base/Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Решение проблем

- **Приложение не получает ответа от платы:** на плате не та прошивка, которую ждёт приложение, TX/RX на другом UART
  или плата вставлена не до конца.
- **Странное поведение UART:** те же пины слушает что-то ещё. Проверьте `Settings → Expansion Modules → Listen UART`
  (см. [Expansion-модули](/ru/gpio/expansion-modules)) и `Settings → System → Log Device`.
- **Веб-прошивальщик не видит плату:** нужен кабель с передачей данных; войдите в загрузчик вручную, попробуйте другой
  USB-порт или браузер.

## См. также

- [Wi-Fi Devboard](/ru/gpio/devboard)
- [Внешние модули](/ru/gpio/external-modules)
- [GPS](/ru/gpio/gps)
