---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 ГГц)

**nRF24L01(+)** от Nordic Semiconductor — дешёвый трансивер на 2,4 ГГц, который стоит во многих беспроводных мышах,
клавиатурах и самоделках. Подключается к Flipper по SPI.

## Приложения

В Base pack есть Sniffer и Mouse Jacker — их использует инструкция ниже. Extra pack добавляет ещё шесть:

| Приложение | Пак | Что делает |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Собирает адреса беспроводных клавиатур для Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Вставляет нажатия клавиш в уязвимый приёмник беспроводной клавиатуры или мыши |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Универсальная утилита для nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Ищет и декодирует пакеты nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Показывает, какие каналы 2,4 ГГц заняты |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Читает и пишет именованные поля устройства nRF24 по файлу конфигурации |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Другая сборка Sniffer выше |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Другая сборка Mouse Jacker выше |

Драйвер, Sniffer и Mouse Jacker — [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Все эти приложения есть в
[паках приложений](https://github.com/xMasterX/all-the-plugins/releases/latest) — см. [Модули и приложения для них](/ru/gpio/module-apps).

::: warning Закон
Только в учебных целях и на собственном оборудовании. Ввод нажатий в чужой компьютер незаконен.
:::

## Подключение

| Пин Flipper | Пин nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — не подключать |

![Подключение nRF24L01 к Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Распиновка от UberGuidoZ.*

nRF24 использует те же SPI-пины (2–5), что и [внешний CC1101](/ru/subghz/external-cc1101). Подключайте их по одному,
если только у вас не комбо-плата, рассчитанная на оба модуля (тогда следуйте её документации).

## Использование

1. Выключите Flipper, подключите модуль, включите.
2. Откройте **NRF24: Sniffer** (`Apps → GPIO`). Запустите сканирование; режимы и каналы переключаются кнопками, как
   подсказано на экране.
3. Дождитесь, пока сниффер найдёт **адрес**.
4. Откройте **NRF24: Mouse Jacker**.
5. Выберите адрес, затем откройте скрипт Bad USB для отправки.
6. Нажатия передаются на целевой донгл.

Демонстрация: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). Синтаксис скриптов — как в
[Bad USB](/ru/badusb/script-format).

## Если модуль работает нестабильно

nRF24 потребляет ток короткими всплесками. Если он работает через раз, поставьте конденсатор между **VCC и GND**
прямо у модуля:

- электролит 3,3–10 мкФ (соблюдайте полярность: минус на GND). Обычно хватает одного на 10 мкФ;
- по желанию — керамика 0,1 мкФ параллельно: большой конденсатор сглаживает медленные изменения, маленький — быстрые
  импульсы при переключении.

Версиям «плюс» (nRF24L01+PA+LNA) с усилителем это нужно тем более.

![Конденсатор на модуле nRF24](/img/remote/218b238eb91c9e38.jpg)

## Благодарности

- Техника сниффинга: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Уязвимости MouseJack: Marc Newlin, [исследование Bastille](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Драйвер вдохновлён [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html), код MouseJack —
  проектом [JackIt](https://github.com/insecurityofthings/jackit).

## См. также

- [Внешние модули](/ru/gpio/external-modules)
- [Bad USB](/ru/badusb/usage)
- [Распиновка GPIO](/ru/gpio/pinout)
