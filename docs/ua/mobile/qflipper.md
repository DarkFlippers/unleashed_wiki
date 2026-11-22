---
title: qFlipper
order: 10
original: [https://docs.flipper.net/zero/qflipper, https://docs.flipper.net/zero/qflipper/windows-debug, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [flipper-docs, unleashed-docs]
---
# qFlipper

**qFlipper** — офіційний настільний застосунок для Flipper Zero: оновлює прошивку й бази, керує файлами на картці
microSD, створює та відновлює резервні копії, ремонтує зламану прошивку й дублює екран. Працює на Windows, macOS і
Linux.

::: tip Unleashed
Канали оновлення qFlipper (Release / RC / Dev) встановлюють **офіційну** прошивку. Щоб встановити Unleashed,
скористайтеся **Install from file** з файлом `.tgz` Unleashed (qFlipper 1.2.0 або новіший) — див. нижче — або
[вебінсталятором](/ua/mobile/web-tools#unleashed-web-installer).
:::

## Встановлення qFlipper

Завантажте застосунок зі [flipperzero.one/update](https://flipperzero.one/update) і запустіть інсталятор.

- **Windows**: лише Windows 10 і 11. Інсталятор також установлює драйвери.
- **macOS**: 10.14 або новіша, оптимізовано під Apple Silicon.
- **Linux**: AppImage. Зробіть файл виконуваним і налаштуйте правила udev:

```bash
chmod +x qFlipper-x86_64.AppImage
./qFlipper-x86_64.AppImage                 # run it
./qFlipper-x86_64.AppImage rules install   # udev rules, to use it as a normal user
```

(У файловому менеджері: Властивості → Права → «Дозволити виконання файлу як програми» / «Є виконуваним».)

## Огляд

Підключіть Flipper зі вставленою SD-карткою через USB і запустіть qFlipper.

- **Device information**: дані про апаратну частину й прошивку, кнопка оновлення, дистанційне керування.
- **Advanced controls**: резервна копія, відновлення, скидання до заводських налаштувань, канал оновлення,
  **Install from file**.
- **File manager**: перегляд, завантаження на пристрій і з пристрою, перейменування й видалення файлів на
  SD-картці та у внутрішній пам'яті.

## Встановлення Unleashed через qFlipper

1. Переконайтеся, що **SD-картка** вставлена.
2. Завантажте `flipper-z-f7-update-(version).tgz` зі сторінки
   [релізів Unleashed](https://github.com/DarkFlippers/unleashed-firmware/releases/latest) (виберіть потрібну
   літеру збірки, див. [варіанти збірок](/ua/apps/catalog#build-variants)).
3. Запустіть qFlipper і підключіть Flipper.
4. Натисніть **Install from file** і виберіть файл `.tgz`.
5. Дочекайтеся завершення всіх етапів. Flipper перезавантажиться в Unleashed з усіма встановленими ресурсами.

Уже на Unleashed? Просто встановіть нову версію поверх — повертатися до офіційної прошивки не потрібно.
Інші варіанти: [Встановлення Unleashed](/ua/start/install), [Оновлення](/ua/start/updating).

## Завантаження файлів на пристрій і з нього

У **File manager** перетягніть файли в теку або клацніть теку правою кнопкою → **Upload here**. Клацніть файл чи
теку правою кнопкою → **Download**, щоб скопіювати їх на комп'ютер (простий спосіб зробити резервну копію всієї
SD-картки).

| Команда | Windows / Linux | macOS |
|---|---|---|
| Увійти в теку | Return | Return |
| Назад | Backspace | Backspace |
| Завантажити на пристрій | Ctrl+L | Cmd+L |
| Завантажити з пристрою | Ctrl+D | Cmd+D |
| Видалити | Delete | Fn+Backspace |
| Видалити негайно | Shift+Delete | Shift+Fn+Backspace |
| Нова тека | Ctrl+N | Cmd+N |
| Перейменувати | Ctrl+E | Cmd+E |
| Оновити | Ctrl+G | Cmd+G |

## Дистанційне керування та скриншоти

У **Device information** клацніть на зображенні Flipper, а далі натискайте кнопки на екрані або користуйтеся
клавіатурою (ℹ️ показує розкладку клавіш). **SAVE SCREENSHOT** зберігає поточний екран як зображення.

## Логи та повідомлення про помилки

- **LOGS → OPEN FULL LOG** показує лог поточної сесії; його можна зберегти як `.txt`.
- qFlipper зберігає логи останніх 100 сесій: у **LOGS** клацніть правою кнопкою в області логу →
  **Browse all logs**.
- Про проблеми саме з офіційним qFlipper повідомляйте на [forum.flipperzero.one](https://forum.flipperzero.one/)
  (розділ Firmware update / qFlipper). Проблеми з самим Unleashed — у чати Unleashed або в issues на GitHub.

## Якщо не працює

### qFlipper не бачить Flipper / Chrome не може підключитися

Послідовний порт може використовувати лише одна програма. Якщо qFlipper відкритий, Flipper Lab, вебінсталятор та
інші вебінструменти підключитися не зможуть — і навпаки. Закрийте qFlipper (і зайві вкладки Flipper Lab), перш ніж
користуватися вебінструментом.

### Драйвери Windows

1. Встановлюйте qFlipper лише з офіційних джерел; він ставить правильні драйвери. Наявність оновлень перевіряйте в
   **Advanced controls → CHECK APP UPDATES**.
2. **Звичайний режим** (Flipper працює): Flipper видно як **USB Serial Device** у
   `Device Manager → Ports (COM & LPT)`, апаратний ID — **VID 0483, PID 5740**, драйвер від **Microsoft**. Якщо
   встановлено інший драйвер, видаліть його й підключіть пристрій знову.
3. **Конфлікт COM-портів**: два послідовні пристрої з однаковим номером COM. Відкрийте один із них →
   **Port Settings → Advanced** і призначте невикористаний **COM Port Number**.
4. **Режим Recovery (DFU)**: затисніть <kbd>←</kbd> + <kbd>Back</kbd>, відпустіть <kbd>Back</kbd> і тримайте
   <kbd>←</kbd>, доки світлодіод не стане синім. Flipper має з'явитися як **DFU in FS Mode** в розділі
   `Universal Serial Bus devices`, **VID 0483, PID DF11**, драйвер **STMicroelectronics**.
5. Якщо ви бачите **STM Device in DFU mode** в розділі `Universal Serial Bus controllers`, встановлено хибний
   драйвер: видаліть qFlipper, перевстановіть його з офіційного сайту й перевірте знову.
6. Якщо **DFU in FS Mode** стоїть у `Other devices` зі знаком оклику: клацніть правою кнопкою →
   **Update driver → Browse my computer → Let me pick** → **Universal serial bus devices** → **WinUsb Device**.

Якщо Flipper взагалі не вмикається, див. [Відновлення](/ua/start/recovery).

## Пов'язані сторінки

- [Встановлення Unleashed](/ua/start/install)
- [Мобільний застосунок Flipper](/ua/mobile/mobile-app)
- [Вебінструменти](/ua/mobile/web-tools)
