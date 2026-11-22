---
title: Ručno dodavanje ključeva
order: 30
original: [https://docs.flipper.net/zero/rfid/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Ručno dodavanje 125 kHz ključeva

Ključ možete izraditi i bez fizičkog privjeska: odaberite protokol i upišite njegove podatke. Rezultat se sprema jednako kao očitan ključ te se može emulirati ili [zapisati na praznu karticu/privjesak](/hr/rfid/write).

## Koraci

1. Idite na `Main Menu → 125 kHz RFID → Add Manually`.
2. Odaberite protokol / format s popisa (pogledajte u nastavku).

   ![Popis vrsta privjesaka u Add Manually: EM-Micro EM4100, EM4100/32, EM4100/16 i Casi-Rusco C10106](/screens/lfrfid/add_manually.png)

3. Za formate koji imaju strukturu s kodom objekta (facility code) / brojem kartice dobivate izbor:
   - **Enter FC/ID** — upišite decimalna polja jedno po jedno. Zaglavlje prikazuje naziv polja i raspon, npr. `Facility Code (0-255)`. <kbd>Back</kbd> vraća na prethodno polje.
   - **Enter Hex Data** — upišite sirove bajtove.

   Ostali protokoli vode izravno u heksadecimalni uređivač *Enter the data in hex*.

   ![Uređivač "Enter the data in hex" s bajtovima privjeska iznad zaslonske heksadecimalne tipkovnice](/screens/lfrfid/add_manually_data.png)

4. Unesite naziv i spremite. Ključ se pohranjuje kao `/ext/lfrfid/<name>.rfid`.

Za kasniju izmjenu spremljenog ključa: `Saved` → ključ → **Edit** (heksadecimalni uređivač, isti naziv datoteke).

::: tip Unleashed
Unos **FC-a / broja kartice** umjesto heksadecimalnih podataka, dodatni **HID** formati i **Casi-Rusco** dodaci su specifični za Unleashed. Tvornički firmver prihvaća samo heksadecimalni unos. Kontrolni zbrojevi i Wiegand paritet izračunavaju se automatski.
:::

## Popis, redoslijedom na uređaju

| Oznaka u izborniku | Spremljeno kao (`Key type`) | Unos | Heksadecimalni bajtovi |
|---|---|---|---|
| EM-Micro EM4100 | EM4100 | FC/ID ili hex | 5 |
| EM-Micro EM4100/32 | EM4100/32 | FC/ID ili hex | 5 |
| EM-Micro EM4100/16 | EM4100/16 | FC/ID ili hex | 5 |
| Casi-Rusco C10106 | EM4100/32 | Credential + Card Number | — |
| Electra | Electra | hex | 8 |
| HID H10301 | H10301 | FC/ID ili hex | 3 |
| HID H10304 | HIDProx | FC + Card Number | — |
| HID H10302 | HIDProx | Card Number | — |
| HID S10401 | HIDProx | FC + Card Number | — |
| HID H10306 | HIDProx | FC + Card Number | — |
| HID Corp1000-35 | HIDProx | FC + Card Number | — |
| IDTECK Idteck | Idteck | hex | 8 |
| Motorola Indala26 | Indala26 | hex | 4 |
| Kantech IoProxXSF | IoProxXSF | FC/ID ili hex | 4 |
| AWID | AWID | FC/ID ili hex | 9 |
| FECAVA FDX-A | FDX-A | hex | 5 |
| ISO FDX-B | FDX-B | hex | 11 |
| Generic HIDProx | HIDProx | hex | 6 |
| Generic HIDExt | HIDExt | hex | 12 |
| Farpointe Pyramid | Pyramid | FC/ID ili hex | 4 |
| Viking | Viking | hex | 4 |
| Jablotron | Jablotron | hex | 5 |
| Paradox | Paradox | hex | 6 |
| PAC/Stanley | PAC/Stanley | hex | 4 |
| Keri | Keri | hex | 4 |
| Gallagher | Gallagher | FC/ID ili hex | 8 |
| Honeywell Nexwatch | Nexwatch | hex | 8 |
| Securakey Radio Key | Radio Key | hex | 6 |
| Guardall GProxII | GProxII | hex | 12 |
| Noralsy | Noralsy | hex | 12 |
| Motorola Indala224 | Indala224 | hex | 28 |

## Rasponi polja za "Enter FC/ID"

| Format | Polja (decimalno) |
|---|---|
| EM4100, EM4100/32, EM4100/16 | Facility Code 0–255, Card Number 0–65535 (pohranjeno u zadnja 3 bajta, prva 2 bajta nula) |
| HID H10301 (26-bit Wiegand) | Facility Code 0–255, Card Number 0–65535 |
| AWID | Facility Code 0–255, Card Number 0–65535 (26-bitni format, paritet dodan) |
| Farpointe Pyramid | Facility Code 0–255, Card Number 0–65535 (26-bitni, paritet i CRC dodani) |
| Kantech IoProxXSF | Facility Code 0–255, Card Number 0–65535, Version 0–255 (kontrolni zbroj dodan) |
| Gallagher | Facility Code 0–65535, Card Number 0–16777215, Region Code 0–15, Issue Level 0–15 |
| Casi-Rusco C10106 | Credential 150000–159999, Card Number 0–457681 (kako ga ispisuje sustav kontrole pristupa; sprema se kao EM4100/32) |
| HID H10304 (37-bit) | Facility Code 0–65535, Card Number 0–524287 |
| HID H10302 (37-bit) | Samo Card Number (35 bita) |
| HID S10401 (37-bit) | Facility Code 0–63, Card Number (29 bita) |
| HID H10306 (34-bit) | Facility Code 0–65535, Card Number 0–65535 |
| HID Corp1000-35 (35-bit) | Facility Code 0–4095, Card Number 0–1048575 |

::: info Veliki brojevi kartica
Unos broja drži predznačenu 32-bitnu vrijednost, pa se sam vrh polja šireg od 31 bita (npr. 35-bitni broj kartice u H10302) može unijeti samo putem **Enter Hex Data** / **Edit**.
:::

## Savjeti

- Broj otisnut na EM4100 kartici poput `0001234567` obično je u obliku **DEZ 10**; nakon spremanja usporedite ga na zaslonu **Info** (prikazuje FC/Card, DEZ 8 i DEZ 10) kako biste bili sigurni da ste unijeli točnu vrijednost.

  ![Zaslon Info spremljenog privjeska: naziv datoteke, EM-Micro EM4100, heksadecimalni podaci, FC/Card, DEZ 8 i DEZ 10](/screens/lfrfid/saved_info.png)

- EM4100/32 i EM4100/16 isti su okvir signala na brzinama prijenosa RF/32 i RF/16; odaberite onaj kao koji se očitava izvornik.
- Za protokole koji podržavaju samo heksadecimalni unos najjednostavniji način za dobivanje točnih bajtova jest jednom očitati pravi privjesak i prepisati vrijednost `Hex:`.

## Povezano

- [Protokoli](/hr/rfid/protocols) · [Format datoteke](/hr/rfid/file-format) · [Pisanje](/hr/rfid/write) · [Čitanje](/hr/rfid/read)
