---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** — официальное десктопное приложение для Flipper Zero: обновляет прошивку и базы, управляет файлами на
microSD, делает бэкап и восстановление, чинит слетевшую прошивку и транслирует экран. Работает на Windows, macOS и
Linux.

::: tip Unleashed
Каналы обновления qFlipper (Release / RC / Dev) ставят **официальную** прошивку. Чтобы установить Unleashed, используйте
**Install from file** с `.tgz` от Unleashed (qFlipper 1.2.0 и новее), см. ниже, или
[Web Installer](/ru/mobile/web-tools#unleashed-web-installer).
:::

## Установка qFlipper

Скачайте его с [flipperzero.one/update](https://flipperzero.one/update) и запустите установщик.

- **Windows**: только Windows 10 и 11. Вместе с программой ставятся драйверы.
- **macOS**: 10.14 и новее, оптимизирован под Apple Silicon.
- **Linux**: AppImage. Сделайте файл исполняемым и установите правила udev:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # запуск
./qFlipper-x86_64.AppImage rules install   # правила udev, чтобы работать от обычного пользователя
```

(Через файловый менеджер: Свойства → Права → «Разрешить выполнение файла как программы» / «Исполняемый».)

## Обзор

Подключите Флиппер с вставленной SD-картой по USB и запустите qFlipper.

- **Device information**: информация о железе и прошивке, кнопка обновления, удалённое управление.
- **Advanced controls**: бэкап, восстановление, сброс к заводским, канал обновления, **Install from file**.
- **File manager**: просмотр, загрузка, выгрузка, переименование и удаление файлов на SD-карте и во внутренней памяти.

## Установка Unleashed через qFlipper

1. Проверьте, что **SD-карта** вставлена.
2. Скачайте `flipper-z-f7-update-(version).tgz` со страницы
   [релизов Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (выберите нужную букву
   сборки, см. [варианты сборок](/ru/apps/catalog)).
3. Запустите qFlipper и подключите Флиппер.
4. Нажмите **Install from file** и выберите `.tgz`.
5. Дождитесь окончания всех этапов. Флиппер перезагрузится уже в Unleashed со всеми установленными ресурсами.

Уже стоит Unleashed? Просто ставьте новую версию поверх, возвращаться на официальную прошивку не нужно.
Другие способы: [Установка Unleashed](/ru/start/install), [Обновление](/ru/start/updating).

## Загрузка и выгрузка файлов

Во вкладке **File manager** перетащите файлы в нужную папку или нажмите правой кнопкой на папку → **Upload here**.
Правая кнопка на файле или папке → **Download** копирует её на компьютер (простой способ забэкапить всю SD-карту).

| Команда | Windows / Linux | macOS |
|---|---|---|
| Войти в папку | Return | Return |
| Назад | Backspace | Backspace |
| Загрузить (Upload) | Ctrl+L | Cmd+L |
| Скачать (Download) | Ctrl+D | Cmd+D |
| Удалить | Delete | Fn+Backspace |
| Удалить сразу | Shift+Delete | Shift+Fn+Backspace |
| Новая папка | Ctrl+N | Cmd+N |
| Переименовать | Ctrl+E | Cmd+E |
| Обновить | Ctrl+G | Cmd+G |

## Удалённое управление и скриншоты

Во вкладке **Device information** нажмите на изображение Флиппера, затем нажимайте кнопки на экране или используйте
клавиатуру (ℹ️ показывает раскладку клавиш). **SAVE SCREENSHOT** сохраняет текущий экран в картинку.

## Логи и баг-репорты

- **LOGS → OPEN FULL LOG** показывает лог текущей сессии; сохраните его как `.txt`.
- qFlipper хранит логи последних 100 сессий: в **LOGS** нажмите правой кнопкой по области лога → **Browse all logs**.
- О проблемах официального qFlipper сообщайте на [forum.flipperzero.one](https://forum.flipperzero.one/) (раздел
  Firmware update / qFlipper). Проблемы самого Unleashed — в чаты Unleashed или в GitHub issues.

## Решение проблем

### qFlipper не видит Флиппер / Chrome не подключается

Serial-порт может занять только одна программа. Пока открыт qFlipper, Flipper Lab, Web Installer и другие
веб-инструменты подключиться не смогут, и наоборот. Закройте qFlipper (и лишние вкладки Flipper Lab) перед работой с
браузерными инструментами.

### Драйверы в Windows

1. Ставьте qFlipper только из официальных источников — он сам установит правильные драйверы. Проверить обновления:
   **Advanced controls → CHECK APP UPDATES**.
2. **Обычный режим** (Флиппер работает): Флиппер виден как **USB Serial Device** в
   `Диспетчер устройств → Порты (COM и LPT)`, ID оборудования **VID 0483, PID 5740**, драйвер от **Microsoft**. Если
   стоит другой драйвер, удалите его и переподключите Флиппер.
3. **Конфликт COM-портов**: два serial-устройства на одном номере COM. Откройте одно из них →
   **Параметры порта → Дополнительно** и назначьте свободный **номер COM-порта**.
4. **Режим восстановления (DFU)**: зажмите <kbd>←</kbd> + <kbd>Back</kbd>, отпустите <kbd>Back</kbd> и держите
   <kbd>←</kbd>, пока светодиод не загорится синим. Флиппер должен появиться как **DFU in FS Mode** в разделе
   `Устройства USB` (Universal Serial Bus devices), **VID 0483, PID DF11**, драйвер **STMicroelectronics**.
5. Если вместо этого в `Контроллеры USB` видно **STM Device in DFU mode** — стоит неправильный драйвер: удалите
   qFlipper, переустановите его с официального сайта и проверьте снова.
6. Если **DFU in FS Mode** висит в `Другие устройства` с восклицательным знаком: правой кнопкой →
   **Обновить драйвер → Найти на этом компьютере → Выбрать из списка** → **Устройства USB** → **WinUsb Device**.

Если Флиппер вообще не запускается, см. [Восстановление](/ru/start/recovery).

## Связанные страницы

- [Установка Unleashed](/ru/start/install)
- [Мобильное приложение Flipper](/ru/mobile/mobile-app)
- [Веб-инструменты](/ru/mobile/web-tools)
