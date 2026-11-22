---
title: Moskvyonok kartice
order: 130
author: gromovyna
original: [https://telegra.ph/Karty-braslety-brelki-Moskvyonok-i-s-chem-ih-kushat-12-16]
sources: [gromovyna]
---
# Moskvyonok kartice, narukvice i privjesci

Kako su građene moskovske učeničke/dječje kartice "Moskvyonok" i kako kopirati **vlastitu** karticu u praktičniji oblik (narukvica, privjesak). Temeljeno na članku autora @gromovyna (2024-12-16), uz tehničku pomoć @Aleksei_Pashaev i anonimnog člana Unleashed zajednice.

::: warning
Tehnički članak; pravna regulativa se razlikuje. Koristite isključivo vlastite kartice, imajte na umu da podsjećaju na platni instrument i sami snosite posljedice.
:::

## Kako se ovi sustavi štite od kloniranja

Gotovo nikako. Sustav koristi **MIFARE Classic** sa standardnim ključevima, bez diverzifikacije, pa se ključevi mogu pronaći običnim rječnikom. Kopiranje je stoga uobičajeno [čitanje MIFARE Classic kartice](/hr/nfc/mifare-classic) uz pisanje na [čarobnu karticu (magic card)](/hr/nfc/magic-cards).

## Prepoznajte svoju karticu

| Tip | UID | Blok 0 | ATQA | SAK |
|---|---|---|---|---|
| 4-bajtni UID | 4 bajta | počinje s UID-om | `00 04` | `08` |
| 7-bajtni UID | 7 bajtova | počinje s UID-om | `00 44` | `08` |
| 7-bajtni, personaliziran na 4 | 4 bajta | ne počinje s UID-om, izgleda kao nasumični podaci | `00 44` | `08` |

### 4-bajtni UID

Standardne oznake, zapisuju se kakve jesu. Preporučuju se prazne kartice **Gen2 (CUID)**; rade i jeftinije **Gen1 (UID/Zero)**, iako neki izvještaji navode da su bile filtrirane.

### 7-bajtni UID

Novije oznake, zapisuju se kakve jesu na prazne kartice **Zero 7 bytes** poput običnih Gen1 oznaka, uključujući pomoću Flipper Zera; ili na oznake temeljene na USCUID-u pomoću kineskih duplikatora ili Proxmarka 3 (proučite strukturu memorije i konfiguracije jer u suprotnom možete trajno blokirati oznaku).

::: tip Unleashed
Pisanje praznih kartica Zero od 7 bajtova na Flipper Zeru dostupno je u Unleashedu od verzije 079, ili s aplikacijom NFC Magic izgrađenom prije NFC refaktoriranja.
:::

### 7-bajtni UID personaliziran na 4 bajta

Ovo je MIFARE Classic EV1 u **načinu personalizacije**: unatrag kompatibilan način rada u kojem kartica ima 7-bajtni ID, ali na svaki SELECT odgovara 4-bajtnim ID-om izračunatim iz njega (tehnička dokumentacija MF1S50YYX_V1 odjeljak 10.1.1; algoritam u NXP AN10927, stranica 14). Zapisivanje kakvo jest daje besmislene podatke. Tipičan blok 0 kartice Moskvyonok počinje s `34 00...`, ali to ovisi o seriji. Na Proxmarku 3 izračun se pokreće naredbom `analyse nuid`.

Kopiranje na 4-bajtnu (CUID) praznu karticu:

1. Napravite kopiju izvornog ispisa (dumpa).
2. Izračunajte novi UID (primjer: `3400060000DBDC` postaje `2FEDA2F1`).
3. Izračunajte BCC kontrolni bajt (`2FEDA2F1` daje `0x91`).
4. Prepišite blok 0 kopije ovako: izračunati 4-bajtni ID, BCC, `08`, `04`, `00`, ostatak nepromijenjen (`2F ED A2 F1 91 08 04 00 FF FF FF FF FF FF FF FF`).
5. Promijenite ATQA u zaglavlju `.nfc` datoteke na `00 04` (većina praznih kartica ima fiksni ATQA, ali učinite to radi ispravnosti).
6. Zapišite ispis na praznu karticu.

Oznake temeljene na USCUID-u mogu zapisati ispis kakav jest i emulirati ovo ponašanje, ali to zahtijeva poznavanje konfiguracije čipa i ovdje nije obrađeno.

## Što nije radilo

Tim je pokušao skratiti gornje, donje i srednje bajtove UID-a, obrnuti redoslijed bajtova te upotrijebiti NUID iz 7 bajtova na 7-bajtnim sustavima; ništa nije uspjelo.

## Povezano

- [MIFARE Classic](/hr/nfc/mifare-classic) · [Čarobne kartice](/hr/nfc/magic-cards) · [Čitanje kartica](/hr/nfc/read)
