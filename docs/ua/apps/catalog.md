---
title: Застосунки у складі Unleashed
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system]
sources: [unleashed-readme, unleashed-src]
---
# Застосунки у складі Unleashed

Встановлений Unleashed має три шари застосунків:

1. **Системні (вбудовані) застосунки.** Вони збираються з репозиторію прошивки й встановлюються з кожним
   оновленням прошивки, яку збірку ви б не вибрали.
2. **Набір Base Apps.** Набір застосунків спільноти, попередньо встановлений у типовій збірці.
3. **Набір Extra Apps.** Значно більше застосунків спільноти, попередньо встановлені лише у збірці `e`.

На додачу ви можете встановити будь-що самостійно, див. [Застосунки на SD-карті](/ua/apps/sd-card-apps).

## Варіанти збірок {#build-variants}

Файли релізів називаються `flipper-z-f7-update-(version)(e / c).tgz`:

| Частина | Що означає |
|---|---|
| `flipper-z` | для Flipper Zero |
| `f7` | апаратна платформа, однакова для всіх Flipper Zero |
| `update` | пакет оновлення: оновлювач, ресурси (застосунки, ІЧ-бібліотеки тощо) і сама прошивка |
| `(version)` | версія прошивки |
| суфікс | які набори застосунків включено (див. нижче) |

| Суфікс | Base Apps | Extra Apps |
|---|:---:|:---:|
| немає (` `) | так | ні |
| `c` | ні | ні |
| `e` | так | так |

- **` ` (без літери)** — типовий варіант: прошивка, системні застосунки та набір Base.
- **`c`**: лише прошивка й системні застосунки, без набору застосунків. Виберіть цей варіант, якщо хочете скласти
  власний набір застосунків.
- **`e`**: прошивка, системні застосунки, набір Base і набір Extra.

Рекомендований спосіб встановити будь-який із них — [Web Installer](/ua/mobile/web-tools), див. також
[Встановлення Unleashed](/ua/start/install).

::: tip Unleashed
Вбудовані застосунки **не** входять до наборів Base чи Extra. Оновлення прошивки записує їх у папку `apps/` на
SD-карті, тому встановлення набору застосунків ніколи не перезапише системний застосунок і не відкотить його
до старішої версії.
:::

## Системні застосунки: у головному меню

| Застосунок | Що робить | Автор / походження |
|---|---|---|
| GPIO | керування пінами GPIO, міст USB-UART та інструменти 1-Wire/iButton | OFW |
| iButton | читання, збереження й емуляція ключів Dallas / Cyfral / Metakom | OFW |
| Infrared | навчання, збереження й надсилання ІЧ-сигналів, універсальні пульти | OFW |
| NFC | читання, збереження, емуляція та розбір NFC-карт | OFW |
| 125 kHz RFID | читання, збереження, емуляція та запис LF RFID-міток | OFW |
| Bad USB | пейлоади Ducky Script через USB і BadKB через Bluetooth | OFW + BadKB від Willy-JL, ClaraCrazy та контриб’юторів XFW |
| U2F | токен безпеки FIDO U2F через USB, див. [U2F](/ua/apps/u2f) | OFW |
| Clock | годинник із керуванням яскравістю екрана, будильником і простим таймером, див. [Clock](/ua/apps/clock) | @nymda, разом із @Willy-JL, @mishamyte та @xMasterX |
| Sub-GHz Remote | прив’язати до 5 збережених файлів `.sub` до кнопок і надсилати їх, див. [Sub-GHz Remote](/ua/subghz/remote) | @gid9798 та @xMasterX |

Sub-GHz, Archive, Settings і системні служби вкомпільовані в сам бінарник прошивки.

## Системні застосунки: у папці Apps

Це файли `.fap` у `Main Menu → Apps`, розкладені по папках-категоріях.

| Застосунок | Папка | Що робить | Автор / походження |
|---|---|---|---|
| MFKey | NFC | відновлює ключі MIFARE Classic з нонсів, зібраних через Detect Reader, див. [Застосунок MFKey](/ua/nfc/mfkey-app) | @noproto |
| T5577 | RFID | читання, редагування й запис блоків T5577, очищення або скидання пароля, перехоплення пароля, див. [Застосунок T5577](/ua/rfid/t5577-app) | @mishamyte |
| Nice O-Code | Sub-GHz | відновлює installer code пульта Nice O-Code і зберігає його як `.sub`, див. [Nice O-Code](/ua/subghz/nice-o-code) | @xMasterX |
| Security+ PIN | Sub-GHz | знаходить PIN клавіатури в перехопленому сигналі Security+ 2.0, див. [Security+ PIN](/ua/subghz/secplus-pin) | @xMasterX |
| Seed Capturer | Sub-GHz | збирає пари Fix + Hop з пультів FAAC SLH, Genius, Erreka та BFT Mitto для офлайн-відновлення Seed, див. [Seed Capturer](/ua/subghz/seed-capturer) | @xMasterX |
| Remote Analyzer | Sub-GHz | декодує по одному пульту на вбудованому CC1101, з вбудованим аналізатором частот, див. [Remote Analyzer](/ua/subghz/remote-analyzer) | @xMasterX |
| Sub-GHz RAW Edit | Sub-GHz | відкриває RAW-запис `.sub`, шукає сигнал, обрізає, об’єднує та декодує, див. [Редактор RAW](/ua/subghz/raw-editor) | Lechnio |
| SIM800 | GPIO | керує GSM-модулем SIM800C/SIM800L: дзвінки, SMS, телефонна книга, USSD, DTMF, AT-термінал, див. [SIM800](/ua/gpio/sim800) | @xMasterX |
| FindMy Flipper | Bluetooth | BLE-маячок місцезнаходження для Apple Find My / Google Find My Device та інших, див. [FindMy Flipper](/ua/apps/find-my-flipper) | @MatthewKuKanich |
| USB Keyboard & Mouse | USB | HID-пульт через USB, див. [HID-пульт](/ua/apps/hid-remote) | OFW |
| Bluetooth Remote | Bluetooth | HID-пульт через Bluetooth, див. [HID-пульт](/ua/apps/hid-remote) | OFW |
| Snake Game | Games | «Змійка», див. [Snake](/ua/apps/snake) | OFW |

Прошивка також містить **стилі головного меню** — невеликі плагіни, які перемикаються в
`Settings → Desktop → Menu Style`, див. [Стилі головного меню](/ua/apps/menu-styles), і рушій JavaScript для
скриптів `.js` (див. [JavaScript](/ua/dev/js-about)).

::: info Нещодавні зміни
Починаючи зі збірки від 20 листопада 2026 року Sub-GHz RAW Edit постачається разом із прошивкою і більше не входить
до набору Extra, а SIM800 став новим вбудованим застосунком (`Apps → GPIO → SIM800`).
:::

## Набори Base та Extra {#base-and-extra-packs}

Застосунки спільноти збирає @xMasterX у
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev): у цьому репозиторії є повний
перелік і вихідний код, а на сторінці [Releases](https://github.com/xMasterX/all-the-plugins/releases/latest) набори
Base та Extra лежать як окремі завантаження — на випадок, якщо ви хочете додати набір до збірки `c` або оновити
застосунки між релізами прошивки.

Щоб поставити набір вручну: завантажте `.zip` зі [сторінки релізів](https://github.com/xMasterX/all-the-plugins/releases/latest), розпакуйте й скопіюйте теки застосунків до
теки `apps` на SD-карті (`/ext/apps/`). Версія API набору має збігатися з версією прошивки (`Current API:` на
початку кожного changelog).

Застосунки, на які вказує ReadMe Unleashed (кожен із них є в одному з наборів):

| Застосунок | Де почитати докладніше |
|---|---|
| TOTP (Authenticator) | [опис файлу конфігурації](https://github.com/akopachov/flipper-zero_authenticator/blob/master/docs/conf-file_description.md) |
| Barcode Generator | [Barcode Generator](/ua/apps/barcode) |
| Multi Converter | [Multi Converter](/ua/apps/multi-converter) |
| WAV Player | [приклади файлів і як конвертувати](https://github.com/UberGuidoZ/Flipper/tree/main/Wav_Player#readme) |
| Sub-GHz Playlist | [скрипт-генератор](https://github.com/darmiel/flipper-scripts/blob/main/playlist/playlist_creator_by_chunk.py) |
| Sub-GHz Bruteforcer | [Брутфорс Sub-GHz](/ua/subghz/bruteforce) |
| LF RFID / iButton Fuzzer | [Фазер RFID](/ua/rfid/fuzzer), [Фазер iButton](/ua/ibutton/fuzzer) |
| Unitemp (датчики температури) | [як користуватися й підтримувані датчики](https://github.com/quen0n/unitemp-flipperzero#readme) |
| [NMEA] GPS | [як користуватися](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/gps_nmea_uart/README.md) |
| i2c Tools | [як користуватися](https://github.com/xMasterX/all-the-plugins/blob/dev/base_pack/flipper_i2ctools/README.md) |
| NRF24 apps | [NRF24](/ua/gpio/nrf24) |
| [WiFi] Scanner, [ESP8266] Deauther, [ESP32] WiFi Marauder, [ESP32-CAM] Camera Suite | [ESP32 і Wi-Fi модулі](/ua/gpio/esp32) |
| ESP flasher | [FAP «ESP flasher»](https://github.com/0xchocolate/flipperzero-esp-flasher) |
| Sentry Safe | [Sentry Safe](/ua/apps/sentry-safe) |

::: warning
Склад наборів змінюється від релізу до релізу. Тег збірки поточних наборів друкується на початку кожного
changelog Unleashed (наприклад, `Apps: Build tag (20nov2026)`) з посиланням на останні коміти застосунків.
:::

## Офіційний каталог

Офіційний каталог застосунків Flipper Zero доступний у [Flipper Lab](https://lab.flipper.net/apps) і в
[мобільному застосунку Flipper](/ua/mobile/mobile-app). Встановлення з нього описане в
[Застосунки на SD-карті](/ua/apps/sd-card-apps#installing-from-the-official-catalog).

## Пов’язані сторінки

- [Застосунки на SD-карті (.fap)](/ua/apps/sd-card-apps)
- [Усунення проблем із застосунками](/ua/apps/troubleshoot)
- [Встановлення Unleashed](/ua/start/install)
