---
title: Podržani protokoli
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://docs.flipper.net/zero/rfid/read]
sources: [unleashed-src, flipper-docs]
---
# Podržani protokoli na 125 kHz

Tablica je sastavljena iz mape `lib/lfrfid/protocols/` firmvera Unleashed. Svi protokoli mogu se **čitati**, **spremati**, **emulirati** i **dodavati ručno**; posljednji stupci pokazuju koji ih prazni čipovi mogu nositi (pogledajte [Pisanje](/hr/rfid/write)).

- **Naziv** — kako se prikazuje na zaslonu i sprema u `.rfid` datoteke kao `Key type`.
- **Čitanje** — koji prolaz čitanja ga dekodira: ASK, PSK ili oba.
- **Bajtovi** — duljina polja `Data:`.

| Naziv | Proizvođač | Čitanje | Bajtovi | Prikazana polja | T5577 | EM4305 | Hitag Micro¹ | 8268² |
|---|---|---|---|---|---|---|---|---|
| EM4100 | EM-Micro | ASK/PSK | 5 | FC, Card, CL, DEZ 8, DEZ 10 | ✓ | ✓ | ✓ | ✓ |
| EM4100/32 | EM-Micro | ASK/PSK | 5 | isto (brzina bita RF/32) | ✓ | ✓ | ✓ | — |
| EM4100/16 | EM-Micro | ASK/PSK | 5 | isto (brzina bita RF/16) | ✓ | ✓ | ✓ | — |
| Electra | Electra | ASK/PSK | 8 | Epilogue | ✓ | ✓ | — | — |
| H10301 | HID | ASK | 3 | FC, Card (26-bitni Wiegand) | ✓ | — | — | — |
| Idteck | IDTECK | PSK | 8 | FC, Card | ✓ | — | — | — |
| Indala26 | Motorola | PSK | 4 | FC, Card, Parity, Checksum | ✓ | — | — | — |
| Indala224 | Motorola | PSK | 28 | Raw | ✓ | — | — | — |
| IoProxXSF | Kantech | ASK | 4 | FC, Version, Card | ✓ | — | — | — |
| AWID | AWID | ASK | 9 | Format, FC, Card | ✓ | — | — | — |
| FDX-A | FECAVA | ASK | 5 | ID, Parity | ✓ | — | — | — |
| FDX-B | ISO | ASK | 11 | ID, country, temperature, animal flag… | ✓ | ✓ | — | — |
| HIDProx | Generički | ASK | 6 | duljina u bitovima; podudarajući HID formati | ✓ | — | — | — |
| HIDExt | Generički | ASK | 12 | — | ✓ | — | — | — |
| Pyramid | Farpointe | ASK | 4 | Format, FC, Card | ✓ | — | — | — |
| Viking | Viking | ASK | 4 | ID | ✓ | ✓ | — | — |
| Jablotron | Jablotron | ASK | 5 | Card | ✓ | ✓ | — | — |
| Paradox | Paradox | ASK | 6 | FC, Card, CRC provjera | ✓ | — | — | — |
| PAC/Stanley | — | ASK | 4 | CIN | ✓ | — | — | — |
| Keri | Keri | PSK | 4 | Internal ID, FC, Card | ✓ | — | — | — |
| Gallagher | Gallagher | ASK | 8 | FC, Card, Region, Issue Level | ✓ | ✓ | — | — |
| Nexwatch | Honeywell | PSK | 8 | ID, Mode, Type | ✓ | — | — | — |
| Radio Key | Securakey | ASK | 6 | RKKT n-bit (FC, Card) ili RKKTH otvoreni tekst (Card) | ✓ | ✓ | — | — |
| GProxII | Guardall | ASK | 12 | FC, Card, LEN, XOR, CRC | ✓ | ✓ | — | — |
| Noralsy | Noralsy | ASK | 12 | Card ID, Year | ✓ | — | — | — |

¹ Hitag Micro = ciljevi 8265/H5, 8210 i H5.5. ² 8268 (Hitag S) prihvaća samo EM4100 pri brzini RF/64 i zadano je isključen.

::: tip Unleashed
U usporedbi s popisom u službenoj dokumentaciji, ovaj firmver dodaje **Indala224** i prolaz čitanja na **134,2 kHz** za FDX-A/FDX-B. Službenoj dokumentaciji formata datoteke također nedostaju EM4100/32, EM4100/16, Electra, Nexwatch, Radio Key, Noralsy i Indala224 — ovdje su to valjane vrijednosti za `Key type`.
:::

## Napomene o pojedinim protokolima

- **EM4100 / EM-Marin** — najčešći tip privjeska u ZND-u („ЕМ-Марин”). 40-bitni ID; FC je 3. bajt, broj kartice posljednja dva. DEZ 8 / DEZ 10 su dekadski oblici otisnuti na privjescima.
- **Casi-Rusco C10106** — nije zaseban protokol; to je EM4100 okvir (obično RF/32). Kada podaci odgovaraju, zaslon s informacijama dodaje redak `or C10106: credential card`, a Add Manually nudi ga kao ulazni format.
- **HIDProx** — generički HID Prox spremnik od 26–37 bitova. Flipper isprobava poznate rasporede (H10304, H10302, S10401, H10306, Corp1000-35) i ispisuje FC/card za svako podudaranje.
- **Paradox** — zaslon s informacijama prikazuje CRC te *CRC Mismatch, Invalid Card!* ako se ne podudara.
- **Zastarjeli naziv za Indala26** — vrlo stare datoteke s `Key type: I40134` pretvaraju se u Indala26 pri učitavanju.

## Povezano

- [Čitanje](/hr/rfid/read) · [Ručno dodavanje](/hr/rfid/add-manually) · [Pisanje](/hr/rfid/write) ·
  [Životinjski mikročipovi](/hr/rfid/animal-microchips) · [Format datoteke](/hr/rfid/file-format)
