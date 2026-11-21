---
title: NRF24
order: 60
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/NRF24.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, unleashed-readme]
---
# NRF24 (2,4 ГГц)

**nRF24L01(+)** від Nordic Semiconductor — дешевий трансивер на 2,4 ГГц, який використовується в багатьох
бездротових мишах, клавіатурах і радіоаматорських проєктах. Підключається до Flipper через SPI.

## Застосунки

У Base pack є Sniffer і Mouse Jacker — їх використовує інструкція нижче. Extra pack додає ще шість:

| Застосунок | Пак | Що робить |
|---|---|---|
| [\[NRF24\] Sniffer](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/nrfsniff) | Base | Збирає адреси безпровідних клавіатур для Mouse Jacker |
| [\[NRF24\] Mouse Jacker](https://github.com/xMasterX/all-the-plugins/tree/dev/base_pack/mousejacker) | Base | Вставляє натискання клавіш у вразливий приймач безпровідної клавіатури або мишки |
| [\[NRF24\] Tool](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24tool) | Extra | Універсальна утиліта для nRF24L01 |
| [\[NRF24\] Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24scan) | Extra | Шукає та декодує пакети nRF24 |
| [\[NRF24\] Channel Scanner](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24channelscanner) | Extra | Показує, які канали 2,4 ГГц зайняті |
| [\[NRF24\] Batch](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrf24-batch) | Extra | Читає і пише іменовані поля пристрою nRF24 за файлом конфігурації |
| [\[NRF24\] Sniffer MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/nrfsniff_ms) | Extra | Інша збірка Sniffer вище |
| [\[NRF24\] Mouse Jacker MS](https://github.com/xMasterX/all-the-plugins/tree/dev/non_catalog_apps/mousejacker_ms) | Extra | Інша збірка Mouse Jacker вище |

Драйвер, Sniffer і Mouse Jacker — від [mothball187](https://github.com/mothball187/flipperzero-nrf24/tree/main/mousejacker). Усі ці застосунки є в
[паках застосунків](https://github.com/xMasterX/all-the-plugins/releases/latest) — див. [Модулі та застосунки для них](/ua/gpio/module-apps).

::: warning Правові аспекти
Лише для навчання й лише з власним обладнанням. Інжекція натискань клавіш у чужий комп'ютер — незаконна.
:::

## Підключення

| Пін Flipper | Пін nRF24L01 |
|---|---|
| 2 (A7) | MOSI (6) |
| 3 (A6) | MISO (7) |
| 4 (A4) | CSN (4) |
| 5 (B3) | SCK (5) |
| 6 (B2) | CE (3) |
| 8 (GND) | GND (1) |
| 9 (3V3) | VCC (2) |
| — | IRQ (8) — залишити непідключеним |

![Схема підключення nRF24L01 до Flipper Zero](/img/remote/511927f9f2d850ad.png)

*Розпіновка від UberGuidoZ.*

nRF24 використовує ті самі піни SPI (2–5), що й [зовнішній CC1101](/ua/subghz/external-cc1101). Підключайте лише
щось одне за раз, якщо ви не користуєтеся комбінованою платою, розрахованою на обидва модулі (тоді дотримуйтеся
її документації).

## Використання

1. Вимкніть Flipper, підключіть модуль, увімкніть пристрій.
2. Відкрийте **NRF24: Sniffer** (`Apps → GPIO`). Запустіть сканування; перемикайте режими й канали кнопками, як
   показано на екрані.
3. Дочекайтеся, доки сніфер знайде **адресу**.
4. Відкрийте **NRF24: Mouse Jacker**.
5. Виберіть адресу, а потім відкрийте скрипт Bad USB, який потрібно надіслати.
6. Натискання клавіш передаються цільовому донглу.

Демонстраційне відео: [YouTube](https://www.youtube.com/watch?v=C5hbyAjuU4k). Синтаксис скриптів такий самий, як
для [Bad USB](/ua/badusb/script-format).

## Якщо модуль працює нестабільно

nRF24 споживає струм короткими кидками. Якщо він працює лише інколи, поставте конденсатор між **VCC і GND**
просто біля модуля:

- електролітичний на 3,3 мкФ – 10 мкФ (слідкуйте за полярністю: мінус до GND). Одного конденсатора на 10 мкФ
  зазвичай достатньо.
- За бажанням паралельно — керамічний на 0,1 мкФ: великий конденсатор згладжує повільні зміни, малий — швидкі
  комутаційні викиди.

Версіям «plus» (nRF24L01+PA+LNA) із підсилювачем це потрібно навіть більше.

![Конденсатор на модулі nRF24](/img/remote/218b238eb91c9e38.jpg)

## Подяки

- Методика сніфінгу: Travis Goodspeed, [Promiscuity is the nRF24L01+'s duty](http://travisgoodspeed.blogspot.com/2011/02/promiscuity-is-nrf24l01s-duty.html).
- Уразливості MouseJack: Marc Newlin, [дослідження Bastille](https://www.bastille.net/research/vulnerabilities/mousejack/technical-details).
- Драйвер натхнений [RadioHead](https://www.airspayce.com/mikem/arduino/RadioHead/classRH__NRF24.html); код
  MouseJack — [JackIt](https://github.com/insecurityofthings/jackit).

## Пов'язані сторінки

- [Зовнішні модулі](/ua/gpio/external-modules)
- [Bad USB](/ua/badusb/usage)
- [Розпіновка GPIO](/ua/gpio/pinout)
