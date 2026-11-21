---
title: "MFKey32: ключи со считывателя"
order: 30
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, gromovyna]
---
# MFKey32: восстановление ключей со считывателя

**MFKey32** — атака на шифр Crypto-1 MIFARE Classic. Флиппер притворяется меткой; считыватель пытается
аутентифицироваться своим настоящим ключом, и двух пар нонс/ответ, которые он отправляет, хватает, чтобы вычислить
этот ключ офлайн. То есть атаке нужен **доступ к считывателю**, а не к ключам.

Когда использовать:

- метка прочитана частично, а недостающие ключи — именно те, что использует считыватель (самый частый случай);
- метки нет вообще, но хочется узнать ключи считывателя и добавить их в словарь;
- у метки нет бэкдора и ни одного известного ключа, поэтому [nested-атаки](/ru/nfc/nested-fudan) не стартуют.

## С меткой и считывателем (рекомендуется)

Если метка на руках, после восстановления ключей считывателя можно дочитать больше секторов — обычно именно их
считыватель и проверяет.

1. Прочитайте метку (`Main Menu → NFC → Read`). Она прочитается частично.
2. В **More** выберите **Extract MFC Keys**. Флиппер спросит *«Save the Key?»*: **Save** (дамп понадобится) или **Skip**.
   *Или* откройте уже сохранённую метку: `Main Menu → NFC → Saved → <метка> → Extract MFC Keys`.
3. На экране **«Emulating... MIFARE MFkey32»**, UID метки и *«Touch the reader»*.

   ![Эмуляция MIFARE MFkey32 с UID метки и просьбой приложить Флиппер к считывателю](/screens/nfc/mfkey_start.png)

4. Приложите Флиппер к считывателю задней стороной, уберите (*«Move the Flipper away»*), приложите снова
   (*«Touch the reader again»*). Счётчик **Nonce pairs: X/10** растёт с каждой удачной попыткой.

   ![Сбор нонсов: собрано 4 пары из 10, просьба убрать Флиппер](/screens/nfc/mfkey_collecting.png)

5. Когда собраны 10 пар — **Completed!**. Остановиться раньше можно кнопкой <kbd>OK</kbd> **Done**.
6. Следующий экран: **Nonce pairs saved: N** и **Authenticated sectors** (какой сектор и тип ключа спрашивал
   считыватель). Нажмите <kbd>OK</kbd>.

   ![Сохранено 5 пар нонсов и список аутентифицированных секторов с типами ключей](/screens/nfc/mfkey_nonces_info.png)

7. Флиппер предложит восстановить ключи: **«Now run Mfkey32 to extract keys»** и **Run** (откроет
   [MFKey](/ru/nfc/mfkey-app)). Если приложения нет — QR-код на `r.flipper.net/nfc-tools` и **Finish**.
8. Восстановите ключи одним из инструментов ниже. Они добавятся в пользовательский словарь.
9. Прочитайте метку снова (или `Saved → <метка> → Unlock with Dictionary`). Ключей и секторов должно стать больше.
10. Эмулируйте или запишите метку.

Нонсы хранятся в `/ext/nfc/.mfkey32.log`, по строке на пару:
`Sec 1 key A cuid 2a234f80 nt0 ... nr0 ... ar0 ... nt1 ... nr1 ... ar1 ...`.

::: tip Счётчик не растёт?
Считыватель не пытается аутентифицировать эмулируемую метку. Некоторые проверяют только UID или работают по другому
протоколу, другие вообще не принимают эмуляцию. Пробуйте другое расстояние и угол; иногда на одну пару нужно
несколько прикладываний.
:::

## Только считыватель

1. Откройте `Main Menu → NFC → Extract MFC Keys`. Флиппер эмулирует «обычную» метку MIFARE Classic.
2. Шаги 3–8, как выше.
3. Восстановленные ключи окажутся в пользовательском словаре и будут автоматически пробоваться при чтении меток этой
   системы.

## Восстановление ключей из нонсов

| Инструмент | Где | Примечание |
|---|---|---|
| **MFKey** на Флиппере | `Main Menu → Apps → NFC → MFKey` | Не нужны телефон/ПК. Обрабатывает `.mfkey32.log` и `.nested.log`. Медленнее. См. [MFKey](/ru/nfc/mfkey-app). |
| **qUnleashed** (приложение-компаньон Unleashed) | `Tools → Recover MIFARE Keys` | `.mfkey32.log` и `.nested.log`, включая hard и static encrypted нонсы. Быстро. См. [qUnleashed](/ru/nfc/qunleashed). |
| **Flipper Mobile App** | `Tools → Mfkey32 (Extract MF Keys)` | Официальное приложение, только нонсы считывателя. |
| **Flipper Lab** | lab.flipper.net → **NFC tools** → **GIVE ME THE KEYS** | По USB в браузере. |

::: tip Unleashed
В Unleashed пункт называется **Extract MFC Keys** (в стоке — *Extract MF Keys*), а приложение-компаньон
**qUnleashed** восстанавливает ключи прямо на телефоне или компьютере. Начиная с **MFKey 4.x** (дев-билды Unleashed
от 1251) восстановление на самом Флиппере в разы быстрее — см. [MFKey](/ru/nfc/mfkey-app).
:::

## Если не получилось

- **Из нонсов ключи не находятся** — считыватель неправильно воспринял эмуляцию Флиппера. Соберите заново,
  попробуйте другой дамп (сохранённая настоящая метка работает лучше «обычной» эмуляции).
- **MFKey пишет «No nonces found»** — нет ни `.mfkey32.log`, ни `.nested.log`.
- **MFKey зависает или падает** — перезагрузите Флиппер (зажать <kbd>←</kbd> + <kbd>Back</kbd> на 5 секунд), удалите
  `/ext/nfc/.mfkey32.log` / `/ext/nfc/.nested.log`, соберите заново.
- **Крайняя мера** — сделайте копию и удалите `/ext/nfc/assets/mf_classic_dict_user.nfc` (это удалит **все** ваши
  пользовательские ключи).

## См. также

[MIFARE Classic](/ru/nfc/mifare-classic) · [Nested-атаки](/ru/nfc/nested-fudan) · [MFKey](/ru/nfc/mfkey-app) ·
[qUnleashed](/ru/nfc/qunleashed)
