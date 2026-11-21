---
title: Читання ключів
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Читання, збереження та емуляція ключів iButton

Flipper Zero читає ключі Dallas 1-Wire (ID, а для ключів із пам’яттю — і її вміст), а також ключі Cyfral і Metakom,
після чого може зберігати та емулювати їх.

| Ключ | Що зчитується |
|---|---|
| Dallas **DS1990** / **DS1420** | Лише 8-байтовий ROM (ID) — пам’яті в ключі немає |
| Dallas **DS1992** | ROM + 128 байт SRAM |
| Dallas **DS1996** | ROM + 8192 байти SRAM |
| Dallas **DS1971** | ROM + 32 байти EEPROM |
| Інші пристрої 1-Wire | Лише ROM, показується як **Dallas (non-specific)** |
| **Cyfral** | 2-байтовий код |
| **Metakom** | 4-байтовий код |

## Читання ключа

1. Відкрийте `Main Menu → iButton → Read`. На екрані з’явиться **Reading — Connect key with pogo pins**.

   ![Екран читання з підказкою «Connect key with pogo pins»](/screens/ibutton/read.png)

2. Прикладіть ключ до **плоскої частини** майданчика iButton так, щоб його центр торкався **лівого піна даних**, а
   обідок — **середнього піна землі**. Тримайте нерухомо.
3. Коли ключ прочитано, Flipper подає звуковий сигнал і показує протокол (наприклад, **Dallas DS1990**) та його ID.

   ![Результат читання: Dallas DS1990 з восьмибайтовим ID і family code, знизу Retry і More](/screens/ibutton/read_success.png)

4. Кнопки: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> запитує *Exit to iButton Menu? All unsaved data
   will be lost!*

**More** пропонує (пункти залежать від протоколу):

| Пункт | Коли показується | Дія |
|---|---|---|
| **Save** | завжди | Задати назву; ключ зберігається у `/ext/ibutton/<name>.ibtn` |
| **Emulate** | завжди | Одразу перейти до емуляції |
| **Write ID** | протоколи з підтримкою запису | Записати ID на заготовку — [Запис](/ua/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Скопіювати пам’ять на ключ того самого типу |
| **Data Info** | DS1992, DS1996, DS1971 | Показати дамп пам’яті |

## Помилки читання

Якщо дані не проходять перевірку протоколу, екран помилки пояснює причину й усе одно пропонує **Retry** і **More**:

- **CRC Error** (Dallas) — восьмий байт ROM є контрольною сумою перших семи; на екрані показано ROM із виділеним
  хибним байтом і *Expected CRC*. Зазвичай це поганий контакт: протріть ключ і прочитайте знову. Якщо помилка
  повторюється, ключ усе одно можна зберегти та спробувати емулювати — деякі зчитувачі не перевіряють CRC. Якщо
  емуляція не працює, виправити помилку не вдасться.
- **Invalid Metakom key: odd parity in byte N** — байт Metakom не пройшов перевірку парності; прочитайте ключ ще раз.

## Збережені ключі

`Main Menu → iButton → Saved` відкриває `/ext/ibutton/`. Меню ключа:

| Пункт | Дія |
|---|---|
| **Emulate** | Емулювати ключ для зчитувача |
| **Write ID** | Записати ID на заготовку |
| **Full Write on Same Type** | Лише DS1992/DS1996/DS1971 — копіювання пам’яті |
| **Edit** | Змінити ID у hex і зберегти під назвою |
| **Rename** / **Delete** | Операції з файлом |
| **Info** | Назва, протокол, ID; <kbd>→</kbd> **More** показує дані пам’яті для ключів із пам’яттю |

## Емуляція

1. Відкрийте збережений ключ → **Emulate** (або **More → Emulate** одразу після читання). На екрані буде
   **Emulating**, `[Protocol]` і назва ключа (або *Unsaved Key*).

   ![Екран емуляції: «Emulating», протокол [DS1990] і назва ключа](/screens/ibutton/emulate.png)

2. Притисніть **виступаючу частину** майданчика до зчитувача: **правий пін даних** має торкатися центру зчитувача, а
   **середній пін землі** — його обідка.
3. Якщо пін землі не дістає до обідка, під’єднайте два проводи: GPIO **17** → центр зчитувача, GPIO **8 / 11 / 18**
   (GND) → обідок.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Усунення проблем

- **Нічого не відбувається.** Ключ не торкається обох пінів — нахиліть його так, щоб обідок притискався до піна землі.
- **Ключ не підтримується.** Можливо, він використовує непідтримуваний протокол (або це RFID-брелок — спробуйте
  [RFID 125 кГц](/ua/rfid/read)).
- **Зчитувач не приймає емуляцію.** Перевірте контакт пінів; деякі зчитувачі виявляють емулятори або перевіряють те,
  що Flipper підробити не може. Якщо ви редагували чи додавали ключ вручну, ще раз перевірте ID.

## Пов’язані сторінки

- [Запис](/ua/ibutton/write) · [Додавання вручну](/ua/ibutton/add-manually) · [Протоколи](/ua/ibutton/protocols) ·
  [Формат файлів](/ua/ibutton/file-format)
