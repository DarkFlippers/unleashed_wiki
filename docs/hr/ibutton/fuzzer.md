---
title: iButton fuzzer
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/ibtnfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# iButton fuzzer

**Fuzzer** emulira niz ID-jeva ključeva jedan za drugim kako bi se vidjelo kako čitač reagira — primjerice radi provjere prihvaća li vaš vlastiti portafon zadane ili neispravno oblikovane ID-jeve.

::: tip Unleashed
Unleashed ReadMe navodi **LFRFID i iButton Fuzzer dodatke**. Fuzzer je vanjska aplikacija i nije dio stabla izvornog koda firmvera: unaprijed prevedeni paketi aplikacija dodaju se u izdanja, a **extra apps pack** koji se objavljuje uz svako izdanje sadrži sve poznate ispravne aplikacije. Njegovi izbornici ovise o verziji aplikacije, pa ovdje nisu opisani.
:::

## Što firmver isporučuje: pokazni popisi UID-ova

Firmver instalira pokazne popise ID-jeva u **`/ext/ibtnfuzzer/`**:

| Datoteka | Protokol | Duljina ID-ja (heks. znakovi) |
|---|---|---|
| `example_uids_ds1990.txt` | Dallas DS1990 | 16 (8 bajtova) |
| `example_uids_cyfral.txt` | Cyfral | 4 (2 bajta) |
| `example_uids_metakom.txt` | Metakom | 8 (4 bajta) |

Format — jedan heksadekadski ID po retku, `#` za komentare, zadržite **prazan redak na kraju**:

```text
# Example file, P.S. keep empty line at the end!
0000000000000000
FE00000000000000
CAFE000000000000
00CAFE0000000000

```

Za izradu vlastitog popisa kopirajte primjer i zamijenite ID-jeve; duljina mora odgovarati protokolu.

Rječnici zajednice povezani iz Unleashed FAQ-a:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058),
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Koristite fuzzer samo na čitačima koje posjedujete ili za čije testiranje imate ovlaštenje.
:::

## Povezano

- [Protokoli](/hr/ibutton/protocols) · [Emulacija ključeva](/hr/ibutton/read) · [RFID fuzzer](/hr/rfid/fuzzer)
