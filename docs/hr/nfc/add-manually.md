---
title: Ručno dodavanje kartica
order: 60
original: [https://docs.flipper.net/zero/nfc/add-manually, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Ručno dodavanje NFC kartica

`Add Manually` stvara virtualnu karticu bez čitanja fizičke kartice. Dva su načina primjene:

- **Generiranje kartice standardne vrste** s nasumičnim UID-om i zadanim (praznim) sadržajem, kao da imate novu fizičku karticu. Zatim je emulirajte kako biste je „prijavili” u sustav kontrole pristupa ili dopustite telefonu da na nju upiše NDEF podatke (poveznicu, vCard).
- **Stvaranje NFC-A kartice iz poznatih vrijednosti**: UID, ATQA i SAK. Dovoljno za jednostavne sustave koji provjeravaju samo UID.

## Generiranje kartice standardne vrste

1. Otvorite `Main Menu → NFC → Add Manually`.
2. Odaberite vrstu kartice (popis u nastavku).

   ![Add Manually: popis vrsta kartica s odabranim NFC-A 7-bytes UID](/screens/nfc/add_manually.png)

3. Otvara se zaslon s generiranim **UID-om**. Pritisnite <kbd>→</kbd> **More**.
4. U izborniku odaberite **Save** (možete i najprije odabrati **Change UID**, ili odmah **Emulate**).
5. Unesite naziv i potvrdite. Kartica se sprema u `/ext/nfc/`.

Dostupne vrste (točni nazivi kao u izborniku):

| Skupina | Vrste |
|---|---|
| Ultralight | Mifare Ultralight, Mifare Ultralight EV1 11, Mifare Ultralight EV1 H11, Mifare Ultralight EV1 21, Mifare Ultralight EV1 H21, Mifare Ultralight C, Mifare Ultralight AES |
| NTAG | NTAG203, NTAG213, NTAG215, NTAG216, NTAG I2C 1k, NTAG I2C 2k, NTAG I2C Plus 1k, NTAG I2C Plus 2k |
| MIFARE Classic | Mifare Mini, Mifare Classic 1k 4byte UID, Mifare Classic 1k 7byte UID, Mifare Classic 4k 4byte UID, Mifare Classic 4k 7byte UID |
| MIFARE Plus | Mifare Plus SE 4byte / 7byte UID; Mifare Plus S 2K / 4K, 4byte / 7byte UID; Mifare Plus X 2K / 4K, 4byte / 7byte UID; Mifare Plus EV1 2K / 4K, 4b. / 7b. UID; Mifare Plus EV2 2K / 4K, 4b. / 7b. UID |
| Texkom | Texkom TK13, Texkom TK17, Texkom MMBIT |

::: tip Unleashed
Izvorni firmver generira samo Ultralight/NTAG i MIFARE Classic. Unleashed dodaje **Mifare Ultralight C** (sa zadanim 3DES ključem `BREAKMEIFYOUCAN!`), **Mifare Ultralight AES**, sve inačice **MIFARE Plus**, **Texkom** ključeve za portafone i **Change UID** odmah nakon generiranja, pa se može izraditi MIFARE Classic s prilagođenim UID-om („NFC Add manually → Mifare Classic with custom UID” u datoteci ReadMe).
:::

::: tip Koju vrstu odabrati za telefon?
Za upisivanje poveznice ili posjetnice s telefona, **NTAG216** radi u većini slučajeva. Provjerite što vaša aplikacija ili sustav očekuje.
:::

## Stvaranje NFC-A kartice iz UID-a, ATQA-a i SAK-a

Neki sustavi kontrole pristupa odobravaju pristup prema UID-u (ponekad uz ATQA/SAK). Ako znate te vrijednosti:

1. Otvorite `Main Menu → NFC → Add Manually`.
2. Odaberite **NFC-A 7-bytes UID** ili **NFC-A 4-bytes UID**.
3. **"Enter SAK in hex"**: upišite SAK (1 bajt), potvrdite.
4. **"Enter ATQA in hex"**: upišite ATQA (2 bajta), potvrdite.
5. **"Enter UID in hex"**: upišite UID, potvrdite.
6. Imenujte karticu i spremite je.

Uobičajene vrijednosti: MIFARE Classic 1K: ATQA `00 04` (4-bajtni UID) ili `00 44` (7-bajtni), SAK `08`; Ultralight/NTAG: ATQA `00 44`, SAK `00`. Savjet za unos bajtova: pritisnite <kbd>↑</kbd> više puta dok se ne pojavi uređivač po polubajtovima (Unleashed).

## Korištenje kartice

- **Emulacija**: `Main Menu → NFC → Saved → <card> → Emulate` (ili **Emulate UID** za NFC-A karticu) i prislonite Flipper uz čitač. Za „programiranje” virtualnog ključa u sustav kontrole pristupa, postavite sustav u način za prijavu kartica prema njegovim uputama i prislonite emuliranu karticu.
- **Kasnija izmjena UID-a**: `Saved → <card> → Edit UID` (NFC-A kartice).

::: warning
Različiti sustavi kontrole pristupa i aplikacije prijavljuju kartice na različite načine; provjerite u njihovoj dokumentaciji koje su vrste kartica podržane. Virtualna kartica ne može pomoći kod sustava koji provjeravaju kriptografiju kartice (DESFire, Plus SL3 s nepoznatim ključevima, EMV).
:::

## Povezano

[Čitanje kartica](/hr/nfc/read) · [Format NFC datoteke](/hr/nfc/file-format) · [Magic kartice](/hr/nfc/magic-cards)
