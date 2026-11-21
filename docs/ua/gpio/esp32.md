---
title: ESP32 і Wi-Fi
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Get%20started%20with%20the%20Dev%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/devboard/Firmware%20update%20on%20Developer%20Board.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/system]
sources: [unleashed-readme, unleashed-docs, unleashed-src]
---
# ESP32 і Wi-Fi

Flipper Zero не має власного Wi-Fi. Інструменти для Wi-Fi з'являються разом із платою на **ESP32** (чи ESP8266) у
гребінці GPIO: вона виконує радіочастинну частину роботи й спілкується із застосунком на Flipper через UART. Ця сторінка —
огляд варіантів і вебінструментів Unleashed, які їх супроводжують.

## Яку плату вибрати

| Плата | Типове застосування |
|---|---|
| **Офіційна Wi-Fi Developer Board** (ESP32-S2) | Постачається з прошивкою відлагоджувального зонда Black Magic для [відлагодження](/ua/gpio/devboard). Можна перепрошити на Marauder |
| **Плати для ESP32 Marauder** (різні плати на ESP32 / ESP32-S2 / ESP32-S3, комбо-плати) | Сканування Wi-Fi і BLE, захоплення пакетів, вардрайвінг |
| **Плати на ESP8266** | Прошивки Wi-Fi Scanner і Deauther |
| **ESP32-CAM** | Camera Suite (зображення з камери на екрані Flipper) |

## Застосунки

Кожен із них — лише половина пари: на плату спершу потрібно прошити відповідну прошивку.

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[ESP32\] WiFi Marauder](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_marauder_companion) | Base | Інтерфейс для прошивки Marauder: сканування Wi-Fi і BLE, захоплення пакетів, вардрайвінг |
| [\[WiFi\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/wifi_scanner) | Base | Список Wi-Fi мереж поблизу, для прошивки Scanner на ESP8266 |
| [\[ESP8266\] Deauther](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/esp8266_deauth) | Base | Інтерфейс для прошивки DSTIKE Deauther |
| [\[ESP32\] Camera Suite](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/camera_suite) | Base | Картинка з ESP32-CAM на екрані Flipper і зйомка фото |
| [\[ESP32\] Camera](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipperzero-camera) | Extra | Другий застосунок для ESP32-CAM: живе відео та фото |
| [\[ESP32\] Ghost ESP](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ghost_esp_app) | Extra | Інтерфейс для прошивки Ghost ESP |
| [\[ESP32\] Evil Portal](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipper_evil_portal) | Extra | Піднімає на ESP32 точку доступу з captive-порталом |
| [\[ESP8266\] Deauther v2](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi_deauther) | Extra | Для прошивки Deauther v2 від @SpacehuhnTech |
| [ESP Flasher](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/esp_flasher) | Extra | Прошиває плату ESP просто з Flipper, через UART |
| [\[ESP8266\] IFTTT Btn](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/ifttt) | Extra | Запускає вебхук IFTTT через ESP8266 |
| [WIFI Mapping](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/wifi-map) | Extra | Картування Wi-Fi мереж з ESP32 |
| [Flipagotchi](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/flipagotchi) | Extra | Показує обличчя та статус Pwnagotchi на екрані Flipper, через UART |

Повний список застосунків для модулів: [Модулі та застосунки для них](/ua/gpio/module-apps).

## ESP32 Marauder

[ESP32 Marauder](https://github.com/justcallmekoko/ESP32Marauder) від justcallmekoko — прошивка для плат на ESP32.
На Flipper її використовують через застосунок **WiFi Marauder** із додаткових пакетів застосунків, який надсилає
платі команди й показує її вивід.

Типовий порядок дій:

1. **Прошийте Marauder** на плату ESP32 (див. прошивальник нижче).
2. Вимкніть Flipper, вставте плату в гребінку GPIO, увімкніть пристрій.
3. Відкрийте застосунок Marauder у `Apps → GPIO` і виберіть команду (сканування точок доступу, сніфінг,
   вардрайвінг тощо).
4. Результати показуються в застосунку; захоплені дані й логи вардрайвінгу зберігаються згідно з налаштуваннями
   плати й застосунку (див. документацію Marauder для вашої плати).

Повний посібник із використання Wi-Fi Devboard разом із Marauder (від UberGuidoZ):
[UberGuidoZ/Flipper → Wifi_DevBoard](https://github.com/UberGuidoZ/Flipper/tree/main/Wifi_DevBoard).

::: warning Правові аспекти
Сканування пасивне, але деавтентифікація та інші активні атаки на Wi-Fi незаконні щодо мереж, які вам не належать
і на тестування яких у вас немає дозволу.
:::

## Вебпрошивальник ESP32

::: tip Unleashed
Команда Unleashed підтримує браузерний прошивальник для популярних модулів ESP32:
**[espflasher.unleashedflip.com](https://espflasher.unleashedflip.com)**. Він працює повністю у браузері, тому
встановлювати esptool не потрібно. Користуйтеся браузером із підтримкою Web Serial (на Chromium).
:::

Загальні кроки:

1. Відключіть плату ESP32 від Flipper і підключіть її до комп'ютера через USB.
2. Якщо плата не входить у режим прошивання сама, затисніть **BOOT**, коротко натисніть **RESET**, відпустіть
   **BOOT**.
3. Відкрийте прошивальник, виберіть плату й прошивку, натисніть підключення та виберіть послідовний порт плати.
4. Дочекайтеся завершення прошивання, перезапустіть плату й вставте її назад у Flipper (із вимкненим Flipper).

Інші способи прошити плату на ESP:

- Застосунок **ESP flasher** для Flipper — прошиває файл `.bin` із SD-картки Flipper через UART на GPIO:
  [0xchocolate/flipperzero-esp-flasher](https://github.com/0xchocolate/flipperzero-esp-flasher).
- Посібник для Windows щодо esptool / Flash Download Tool:
  [SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32](https://github.com/SequoiaSan/Guide-How-To-Upload-bin-to-ESP8266-ESP32).
- [USB-UART Bridge із застосунку GPIO](/ua/gpio/gpio-app) з параметром `RTS/DTR Pins` може працювати як
  USB-перехідник для плат без власного USB-порту.

::: tip Повернення до відлагоджувальної прошивки
Якщо ви встановили Marauder на офіційну Wi-Fi Devboard і хочете повернути відлагоджувач Black Magic, перепрошийте
її через `ufbt devboard_flash`, як описано в [Devboard: оновлення прошивки](/ua/gpio/devboard-firmware).
:::

## Карта Wi-Fi-вардрайвінгу

::: tip Unleashed
**[wdmap.unleashedflip.com](https://wdmap.unleashedflip.com)** об'єднує й відображає на одній карті кілька
записів вардрайвінгу у форматі WiGLE з ESP32 Marauder та інших інструментів.
:::

1. Проведіть вардрайвінг із Marauder (для нього потрібен GPS-модуль, підключений до плати ESP32).
2. Скопіюйте CSV-логи у форматі WiGLE на комп'ютер.
3. Відкрийте карту й завантажте один або кілька файлів; мережі буде показано разом.

Для записів Sub-GHz та інших файлів із координатами є окрема карта —
[map.unleashedflip.com](https://map.unleashedflip.com).

## Інші прошивки для ESP

| Прошивка | Плата | Посилання |
|---|---|---|
| Wi-Fi Scanner | ESP8266 / ESP32 | [Як користуватися](https://github.com/SequoiaSan/FlipperZero-WiFi-Scanner_Module#readme) · [Вебпрошивальник](https://sequoiasan.github.io/FlipperZero-WiFi-Scanner_Module/) |
| ESP8266 Deauther | ESP8266 | [Як користуватися](https://github.com/SequoiaSan/FlipperZero-Wifi-ESP8266-Deauther-Module#readme) · [Вебпрошивальник](https://sequoiasan.github.io/FlipperZero-Wifi-ESP8266-Deauther-Module/) |
| Camera Suite | ESP32-CAM | [Як користуватися](https://github.com/CodyTolene/Flipper-Zero-Camera-Suite) |

Відповідні застосунки для Flipper є в пакетах Base/Extra:
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/releases/latest).

## Якщо не працює

- **Застосунок не отримує відповіді від плати:** на плату прошито не ту прошивку, яку очікує застосунок, TX/RX
  підключені до не того UART або плата вставлена не до кінця.
- **Дивна поведінка на UART:** ті самі піни слухає інша функція. Перевірте
  `Settings → Expansion Modules → Listen UART` (див. [Модулі розширення](/ua/gpio/expansion-modules)) і
  `Settings → System → Log Device`.
- **Вебпрошивальник не знаходить плату:** скористайтеся USB-кабелем із передаванням даних, увійдіть у режим
  завантажувача вручну, спробуйте інший USB-порт або інший браузер.

## Пов'язані сторінки

- [Wi-Fi Devboard](/ua/gpio/devboard)
- [Зовнішні модулі](/ua/gpio/external-modules)
- [GPS](/ua/gpio/gps)
