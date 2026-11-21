---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (автор @MatthewKuKanich) превращает Bluetooth Флиппера в маячок-трекер. Флиппер транслирует
такое же BLE-объявление, как метка, а телефоны сети поиска рядом сообщают его местоположение, так что потерянный
Флиппер можно найти в приложении владельца метки.

Поддерживаемые типы меток: **Apple AirTag** (Локатор / Find My), **Samsung SmartTag** (SmartThings Find),
**Tile SmartTag** и **Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper входит в прошивку, а Unleashed дополнительно ставит небольшой хук автозапуска: если маячок был активен
в момент выключения Флиппера, он **автоматически включается снова после перезагрузки**, без открытия приложения.
Маячок продолжает работать в фоне, пока вы пользуетесь другими приложениями.
:::

::: warning
Используйте только со своими метками и устройствами. Слежка за другими людьми может быть незаконной.
:::

## Что понадобится

Флипперу нужны **MAC-адрес** и **payload** (полезная нагрузка) метки, либо файл ключей. Получить их можно двумя
способами:

- **Клонировать существующую метку** (проще всего; местоположение будет видно в обычном приложении владельца метки).
- **Сгенерировать собственные ключи** методом OpenHaystack (физическая метка не нужна, только сеть Apple;
  местоположение смотрится в OpenHaystack или его аналоге без Mac).

### Вариант A: клонирование существующей метки

1. Привяжите AirTag или SmartTag к своему телефону как обычно.
2. Переведите её в режим «потеряна»: держите вдали от телефона, к которому она привязана, примерно 15 минут.
3. На Android-телефон установите **nRF Connect** (версия для iOS не показывает сырые данные).
4. В nRF Connect поставьте фильтр по бренду метки (Apple или Samsung), RSSI на минимальное значение и запустите
   сканирование.
5. Когда метка появится как устройство «FindMy», откройте **Raw** / **View Raw** и запишите **payload** и
   **MAC-адрес**. Можно также экспортировать данные в файл `.txt`.
6. **Сразу же выньте батарейку из метки**, иначе она сменит ключ и MAC, и ваша копия перестанет работать.

### Вариант B: ключи OpenHaystack

1. Скачайте `generate_keys.py` из [репозитория FindMyFlipper](https://github.com/MatthewKuKanich/FindMyFlipper)
   и запустите (нужна библиотека: `python3 -m pip install cryptography`).
2. Скрипт выдаст **Private Key**, **Public Key**, **Payload** и **MAC Address**, а также файл `.keys`.
3. Сохраните Private Key: он нужен для получения отчётов о местоположении.
4. Смотрите местоположение в [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS ниже 14) или без
   Mac через [macless-haystack](https://github.com/dchristl/macless-haystack) или
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Настройка на Флиппере

1. Скопируйте экспорт nRF Connect (`.txt`) или файл `.keys` в `/ext/apps_data/findmy/` на SD-карте (или пропустите
   этот шаг и введите данные вручную).
2. Откройте `Apps → Bluetooth → FindMy Flipper` и нажмите <kbd>→</kbd> (**Config**).
3. Выберите **Register Tag**, затем тип метки: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` или
   `Google Find My`.
4. Выберите способ импорта:
   - `nRF Connect (.txt)`: выберите экспортированный файл;
   - `OpenHaystack (.keys)`: выберите файл ключей;
   - `Register Tag Manually`: введите MAC-адрес, затем payload.
5. Вернитесь на главный экран и нажмите <kbd>OK</kbd>. Надпись сменится на `Broadcast Active`.

## Главный экран

| Кнопка | Действие |
|---|---|
| <kbd>OK</kbd> | включить / выключить маячок (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | изменить интервал трансляции |
| <kbd>→</kbd> | Config (настройки) |
| <kbd>←</kbd> | выйти из приложения, оставив маячок работать в фоне |
| <kbd>Back</kbd> | закрыть приложение |

## Меню Config

| Пункт | Значения | Примечания |
|---|---|---|
| Broadcast Interval | 1-10 с (Google: 1-2 с) | как часто отправляется маячок; Google требует не реже раза в 2 с |
| Transmit Power | 0-6 dBm | больше мощность = больше дальность и расход батареи |
| Register Tag | | тип метки и импорт (см. выше) |
| Show MAC | Yes / No | показывать MAC на главном экране |

Приложение хранит своё состояние в `/ext/apps_data/findmy/findmy_state.txt`; именно благодаря этому маячок
возобновляется после перезагрузки.

## Отслеживание

- **Клон AirTag**: Флиппер отображается как ваш AirTag в приложении «Локатор» (Find My).
- **Клон SmartTag**: в SmartThings (SmartThings Find), на телефоне или в браузере.
- **Ключи OpenHaystack**: в OpenHaystack или macless-haystack.

## Решение проблем

- **Местоположение не обновляется**: ключ/MAC метки сменился до того, как вы вынули батарейку; снимите данные заново.
- **Маячок не включается после перезагрузки**: проверьте, что SD-карта вставлена (файл состояния лежит на ней) и что
  перед выключением маячок был в состоянии `Broadcast Active`.
- **Батарея садится быстрее**: увеличьте интервал трансляции и уменьшите мощность передачи.

## Связанные страницы

- [Приложения в составе Unleashed](/ru/apps/catalog)
- [Настройки](/ru/start/settings)
