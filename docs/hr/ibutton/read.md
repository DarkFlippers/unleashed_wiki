---
title: Čitanje ključeva
order: 10
original: [https://docs.flipper.net/zero/ibutton/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols]
sources: [unleashed-src, flipper-docs]
---
# Čitanje, spremanje i emulacija iButton ključeva

Flipper Zero čita ključeve Dallas 1-Wire (ID i, kod memorijskih ključeva, njihovu memoriju), Cyfral i Metakom ključeve te ih zatim može spremiti i emulirati.

| Ključ | Što se čita |
|---|---|
| Dallas **DS1990** / **DS1420** | Samo 8-bajtni ROM (ID) — ključ nema memoriju |
| Dallas **DS1992** | ROM + 128 bajtova SRAM-a |
| Dallas **DS1996** | ROM + 8192 bajta SRAM-a |
| Dallas **DS1971** | ROM + 32 bajta EEPROM-a |
| Ostali 1-Wire uređaji | Samo ROM, prikazan kao **Dallas (non-specific)** |
| **Cyfral** | 2-bajtni kôd |
| **Metakom** | 4-bajtni kôd |

## Čitanje ključa

1. Otvorite `Main Menu → iButton → Read`. Na zaslonu se prikazuje **Reading — Connect key with pogo pins**.

   ![Zaslon čitanja s porukom "Connect key with pogo pins"](/screens/ibutton/read.png)

2. Prislonite ključ na **ravni dio** iButton kontaktne pločice tako da njegovo središte dodiruje **lijevi podatkovni pin**, a rub **srednji pin mase**. Držite ga mirno.
3. Kada se ključ očita, Flipper se oglasi zvučnim signalom i prikaže protokol (npr. **Dallas DS1990**) i njegov ID.

   ![Rezultat čitanja: Dallas DS1990 s osmobajtnim ID-om i family kodom, Retry i More na dnu](/screens/ibutton/read_success.png)

4. Tipke: <kbd>←</kbd> **Retry**, <kbd>→</kbd> **More**. <kbd>Back</kbd> pita *Exit to iButton Menu? All unsaved data will be lost!*

**More** nudi (stavke ovise o protokolu):

| Stavka | Kada se prikazuje | Radnja |
|---|---|---|
| **Save** | uvijek | Imenujte ključ, sprema se u `/ext/ibutton/<name>.ibtn` |
| **Emulate** | uvijek | Odmah emulira |
| **Write ID** | protokoli s mogućnošću pisanja | Upisuje ID na prazan ključ — [Pisanje](/hr/ibutton/write) |
| **Full Write on Same Type** | DS1992, DS1996, DS1971 | Kopira memoriju na ključ iste vrste |
| **Data Info** | DS1992, DS1996, DS1971 | Prikazuje sadržaj memorije |

## Pogreške pri čitanju

Ako podaci ne prođu provjeru protokola, zaslon pogreške objašnjava razlog i dalje nudi **Retry** i **More**:

- **CRC Error** (Dallas) — 8. bajt ROM-a jest CRC nad prvih sedam; zaslon prikazuje ROM s označenim neispravnim bajtom i *Expected CRC*. Najčešće je uzrok loš kontakt: očistite ključ i ponovno ga očitajte. Ako se pogreška ponavlja, i dalje možete spremiti ključ i pokušati emulaciju — neki čitači zanemaruju CRC. Ako emulacija ne uspije, pogreška se ne može ispraviti.
- **Invalid Metakom key: odd parity in byte N** — bajt Metakom ključa nije prošao provjeru pariteta; ponovno ga očitajte.

## Spremljeni ključevi

`Main Menu → iButton → Saved` otvara `/ext/ibutton/`. Izbornik ključa:

| Stavka | Radnja |
|---|---|
| **Emulate** | Emulira prema čitaču |
| **Write ID** | Upisuje ID na prazan ključ |
| **Full Write on Same Type** | Samo DS1992/DS1996/DS1971 — kopira memoriju |
| **Edit** | Mijenja ID u heksadekadskom obliku, zatim sprema pod imenom |
| **Rename** / **Delete** | Upravljanje datotekom |
| **Info** | Naziv, protokol, ID; <kbd>→</kbd> **More** prikazuje podatke memorije za memorijske ključeve |

## Emulacija

1. Otvorite spremljeni ključ → **Emulate** (ili **More → Emulate** odmah nakon čitanja). Na zaslonu se prikazuju **Emulating**, `[Protocol]` i naziv ključa (ili *Unsaved Key*).

   ![Zaslon emulacije koji prikazuje "Emulating", protokol [DS1990] i naziv ključa](/screens/ibutton/emulate.png)

2. Prislonite **izbočeni dio** kontaktne pločice na čitač: **desni podatkovni pin** mora dodirivati središte čitača, a **srednji pin mase** njegov rub.
3. Ako pin mase ne može dosegnuti rub, spojite dvije žice: GPIO **17** → središte čitača, GPIO **8 / 11 / 18** (GND) → rub.

## CLI

```text
ikey read
ikey emulate <key_type> <key_data>
ikey write Dallas <key_data>
	<key_type>: Dallas (8 bytes), Cyfral (2 bytes), Metakom (4 bytes, must contain correct parity)
	<key_data> is hex
```

## Rješavanje problema

- **Ništa se ne događa.** Ključ ne dodiruje oba pina — nagnite ga tako da rub dodiruje pin mase.
- **Nepodržani ključ.** Možda koristi nepodržani protokol (ili je riječ o RFID privjesku — pokušajte [125 kHz RFID](/hr/rfid/read)).
- **Emulacija odbijena.** Provjerite kontakt pinova; neki čitači otkrivaju emulatore ili provjeravaju svojstva koja Flipper ne može lažirati. Ako ste ključ ručno uredili ili dodali, dvaput provjerite ID.

## Povezano

- [Pisanje](/hr/ibutton/write) · [Ručno dodavanje](/hr/ibutton/add-manually) · [Protokoli](/hr/ibutton/protocols) · [Format datoteke](/hr/ibutton/file-format)
