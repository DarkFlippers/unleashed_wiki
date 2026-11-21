---
title: Приложения в комплекте Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Приложения в комплекте Unleashed

Приложения в установленной Unleashed складываются из трёх слоёв:

1. **Системные (встроенные) приложения.** Собираются из репозитория прошивки и ставятся при каждом обновлении
   прошивки, какую бы сборку вы ни выбрали.
2. **Пак Base Apps.** Набор приложений сообщества, предустановленный в сборке по умолчанию.
3. **Пак Extra Apps.** Ещё множество приложений сообщества, предустановлен только в сборке `e`.

Поверх этого можно установить что угодно самостоятельно, см. [Приложения на SD-карте](/ru/apps/sd-card-apps).

## Варианты сборки {#build-variants}

Файлы релизов называются `flipper-z-f7-update-(version)(e / c).tgz`:

| Часть | Значение |
|---|---|
| `flipper-z` | для Flipper Zero |
| `f7` | аппаратная платформа (hardware target), одинаковая для всех Flipper Zero |
| `update` | пакет обновления: апдейтер, ассеты (приложения, ИК-библиотеки и т. д.) и сама прошивка |
| `(version)` | версия прошивки |
| суффикс | какие паки приложений включены (ниже) |

| Суффикс | Base Apps | Extra Apps |
|---|:---:|:---:|
| нет (` `) | да | нет |
| `c` | нет | нет |
| `e` | да | да |

- **` ` (без буквы)** — вариант по умолчанию: прошивка, системные приложения и пак Base.
- **`c`**: только прошивка и системные приложения, без паков. Выбирайте, если хотите собрать свой набор приложений.
- **`e`**: прошивка, системные приложения, пак Base и пак Extra.

Любой из вариантов рекомендуется ставить через [Web Installer](/ru/mobile/web-tools), см. также
[Установка Unleashed](/ru/start/install).

::: tip Unleashed
Встроенные приложения **не входят** в паки Base и Extra. Обновление прошивки записывает их в папку `apps/` на
SD-карте, поэтому установка пака никогда не перезапишет и не откатит системное приложение.
:::

## Системные приложения в главном меню

| Приложение | Что делает | Автор / происхождение |
|---|---|---|
| GPIO | управление пинами GPIO, мост USB-UART и инструменты 1-Wire/iButton | OFW |
| iButton | чтение, сохранение и эмуляция ключей Dallas / Cyfral / Metakom | OFW |
| Infrared | запись, сохранение и отправка ИК-сигналов, универсальные пульты | OFW |
| NFC | чтение, сохранение, эмуляция и разбор NFC-карт | OFW |
| 125 kHz RFID | чтение, сохранение, эмуляция и запись LF RFID-меток | OFW |
| Bad USB | Ducky Script по USB и BadKB по Bluetooth | OFW + BadKB от Willy-JL, ClaraCrazy и контрибьюторов XFW |
| U2F | токен безопасности FIDO U2F по USB, см. [U2F](/ru/apps/u2f) | OFW |
| Clock | часы с регулировкой яркости экрана, будильником и простым таймером, см. [Clock](/ru/apps/clock) | @nymda, при участии @Willy-JL, @mishamyte и @xMasterX |
| Sub-GHz Remote | привязка до 5 сохранённых `.sub`-файлов к кнопкам и их отправка, см. [Sub-GHz Remote](/ru/subghz/remote) | @gid9798 и @xMasterX |

Sub-GHz, Archive, Settings и системные сервисы вкомпилированы прямо в бинарник прошивки.

## Системные приложения в папке Apps

Это файлы `.fap` в `Main Menu → Apps`, разложенные по папкам-категориям.

| Приложение | Папка | Что делает | Автор / происхождение |
|---|---|---|---|
| MFKey | NFC | восстановление ключей MIFARE Classic из nonce, собранных через Detect Reader, см. [Приложение MFKey](/ru/nfc/mfkey-app) | @noproto |
| T5577 | RFID | чтение, редактирование и запись блоков T5577, очистка и сброс пароля, перехват пароля, см. [Приложение T5577](/ru/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | восстановление установочного кода пульта Nice O-Code и сохранение его в `.sub`, см. [Nice O-Code](/ru/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | поиск PIN-кода клавиатуры в записанном сигнале Security+ 2.0, см. [Security+ PIN](/ru/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | сбор пар Fix + Hop с пультов FAAC SLH, Genius, Erreka и BFT Mitto для офлайн-восстановления Seed, см. [Seed Capturer](/ru/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | декодирование одного пульта за раз на встроенном CC1101, со встроенным анализатором частот, см. [Remote Analyzer](/ru/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | открыть RAW-запись `.sub`, найти сигнал, обрезать, склеить и декодировать, см. [RAW-редактор](/ru/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | управление GSM-модулем SIM800C/SIM800L: звонки, SMS, телефонная книга, USSD, DTMF, AT-терминал, см. [SIM800](/ru/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | BLE-маячок местоположения для Apple Find My / Google Find My Device и других, см. [FindMy Flipper](/ru/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | HID-пульт по USB, см. [HID-пульт](/ru/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | HID-пульт по Bluetooth, см. [HID-пульт](/ru/apps/hid-remote) | OFW |
| Snake Game | Games | змейка, см. [Snake](/ru/apps/snake) | OFW |

Также в прошивке есть **стили главного меню** — небольшие плагины, которые переключаются в
`Settings → Desktop → Menu Style`, см. [Стили главного меню](/ru/apps/menu-styles), и JavaScript-раннер для скриптов
`.js` (см. [JavaScript](/ru/dev/js-about)).

::: info Последние изменения
Начиная со сборки от 20 ноября 2026, Sub-GHz RAW Edit поставляется вместе с прошивкой и больше не входит в пак Extra,
а SIM800 — новое встроенное приложение (`Apps → GPIO → SIM800`).
:::

## Паки Base и Extra

Приложения сообщества собирает @xMasterX в репозитории
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): там полный список и исходники, а на
странице [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) паки Base и Extra лежат отдельными
загрузками — на случай, если вы хотите добавить пак к сборке `c` или обновить приложения между релизами прошивки.

Чтобы поставить пак вручную: скачайте `.zip` со [страницы релизов](https://github.com/xMasterX/all-the-plugins/releases/latest), распакуйте и скопируйте папки приложений в
папку `apps` на SD-карте (`/ext/apps/`). Версия API пака должна совпадать с версией прошивки (`Current API:` в
начале каждого changelog).

Приложения, на которые ссылается ReadMe Unleashed (каждое входит в один из паков):

| Приложение | Где почитать подробнее |
|---|---|
| TOTP (Authenticator) | [описание файла конфигурации](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/ru/apps/barcode) |
| Multi Converter | [Multi Converter](/ru/apps/multi-converter) |
| WAV Player | [примеры файлов и как конвертировать](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [скрипт-генератор](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Брутфорс Sub-GHz](/ru/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [RFID fuzzer](/ru/rfid/fuzzer), [iButton fuzzer](/ru/ibutton/fuzzer) |
| Unitemp (датчики температуры) | [как пользоваться и поддерживаемые датчики](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [как пользоваться](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [как пользоваться](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| Приложения NRF24 | [NRF24](/ru/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 и Wi-Fi-модули](/ru/gpio/esp32) |
| ESP flasher | [FAP "ESP flasher"](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/ru/apps/sentry-safe) |

::: warning
Состав паков меняется от релиза к релизу. Тег сборки текущих паков указан в начале каждого changelog Unleashed
(например `Apps: Build tag (20nov2026)`) вместе со ссылкой на последние коммиты приложений.
:::

## Официальный каталог

Официальный каталог приложений Flipper Zero доступен во [Flipper Lab](https://lab.flipper.net/apps) и в
[мобильном приложении Flipper](/ru/mobile/mobile-app). Установка из него описана в разделе
[Приложения на SD-карте](/ru/apps/sd-card-apps).

## Связанные страницы

- [Приложения на SD-карте (.fap)](/ru/apps/sd-card-apps)
- [Проблемы с приложениями](/ru/apps/troubleshoot)
- [Установка Unleashed](/ru/start/install)
