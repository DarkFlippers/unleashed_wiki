---
title: RFID fuzzer
order: 90
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/extra_resources/resources/rfidfuzzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md]
sources: [unleashed-readme, unleashed-src, unleashed-docs]
---
# RFID fuzzer

**Fuzzer** emulira dugi niz ID-jeva jedan za drugim kako bi testirao kako čitač reagira — npr. prihvaća li
zadani ID, ruši li se na neispravnim podatcima ili radi provjere raspona valjanih kartica u vašem vlastitom sustavu.

::: tip Unleashed
Unleashed ReadMe navodi **LFRFID and iButton Fuzzer plugins** među svojim NFC/RFID/iButton značajkama. Fuzzer je
vanjska aplikacija i nije dio izvornog kôda samog firmvera: unaprijed izgrađeni paketi aplikacija dodaju se u izdanja,
a **extra apps pack** objavljen sa svakim izdanjem sadrži sve poznate ispravne aplikacije. Njegovi izbornici ovise o
verziji aplikacije, pa ovdje nisu opisani.
:::

## Što firmver isporučuje: ogledni popisi UID-ova

Firmver instalira ogledne popise ID-jeva za fuzzer u **`/ext/rfidfuzzer/`**:

| Datoteka | Protokol | Duljina ID-ja (heks. znakova) |
|---|---|---|
| `example_uids_em4100.txt` | EM4100 | 10 (5 bajtova) |
| `example_uids_h10301.txt` | HID H10301 | 6 (3 bajta) |
| `example_uids_hidprox.txt` | HIDProx | 12 (6 bajtova) |
| `example_uids_pac.txt` | PAC/Stanley | 8 (4 bajta) |

Format — jedan heksadecimalni ID po retku, `#` za komentare i **prazan redak na kraju** datoteke:

```text
# Example file, P.S. keep empty line at the end!
0000000000
FE00000000
CAFE000000
00CAFE0000

```

Napravite vlastiti popis tako da kopirate jedan od primjera i zamijenite ID-jeve; duljina ID-ja mora odgovarati veličini
ključa protokola (pogledajte [protokole](/hr/rfid/protocols), stupac *Bytes*).

Unleashed FAQ povezuje gotove datoteke rječnika koje je podijelila zajednica:
[t.me/flipperzero_unofficial_ru/37058](https://t.me/flipperzero_unofficial_ru/37058) i
[t.me/flipperzero_unofficial_ru/37072](https://t.me/flipperzero_unofficial_ru/37072).

::: warning
Koristite fuzzer samo na čitačima koje posjedujete ili za čije testiranje imate ovlaštenje.
:::

## Povezano

- [Protokoli](/hr/rfid/protocols) · [Čitanje](/hr/rfid/read) · [iButton fuzzer](/hr/ibutton/fuzzer)
