---
title: NFC
author: gromovyna
original: [https://docs.flipper.net/zero/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://t.me/gromovyna/3]
sources: [flipper-docs, unleashed-readme, unleashed-src, gromovyna]
---
# NFC

Flipper Zero ima ugrađen **13,56 MHz NFC modul** koji može **čitati**, **spremati**, **emulirati** i, za neke vrste kartica, **zapisivati** visokofrekventne kartice: pristupne kartice i privjeske, prijevozne kartice, hotelske ključeve, NFC naljepnice, igračke tipa amiibo te bankovne kartice (samo javne podatke). Podaci se pohranjuju na microSD karticu u `/ext/nfc/` kao tekstualne datoteke `.nfc`.

::: warning Umetnite microSD karticu
Aplikacija NFC čuva svoje rječnike, parsere i spremljene kartice na microSD kartici (`/ext/nfc/`). Ažurirajte firmver s umetnutom SD karticom kako bi se resursi (rječnici ključeva, `assets/*.nfc`, dodaci parsera) instalirali.
:::

## Hardver

- **ST25R3916** NFC front-end čip, zadužen za čitanje i emulaciju.
- **13,56 MHz antena** na dvopojasnoj RFID antenskoj ploči na stražnjoj strani uređaja, pored 125 kHz antene. Prislonite kartice uz **sredinu stražnje strane** Flippera.

## Izbornik NFC

`Main Menu → NFC` otvara ovaj izbornik (oznake točno onakve kakve su na uređaju u firmveru Unleashed):

![Glavni izbornik NFC: Read, Extract MFC Keys, Saved, Extra Actions](/screens/nfc/menu.png)

| Stavka | Što radi |
|---|---|
| **Read** | Prepoznaje vrstu kartice i čita sve što može, uključujući napade na ključeve MIFARE Classic. Pogledajte [Čitanje kartica](/hr/nfc/read). |
| **Extract MFC Keys** | Emulira karticu MIFARE Classic za prikupljanje nonce vrijednosti s čitača (MFKey32). Pogledajte [MFKey32](/hr/nfc/mfkey). |
| **Saved** | Vaše spremljene `.nfc` datoteke: emulacija, pisanje, otključavanje, preimenovanje, brisanje. |
| **Extra Actions** | Čitanje određene vrste kartice, upravljanje rječnicima ključeva, otključavanje kartica NTAG/Ultralight i SLIX-L. |
| **Add Manually** | Generira praznu virtualnu karticu ili NFC-A karticu iz poznatog UID/ATQA/SAK-a. Pogledajte [Ručno dodavanje kartica](/hr/nfc/add-manually). |
| **Debug** | Vidljivo samo kada je uključen Debug način rada (`Settings → System → Debug`). |

`Extra Actions` sadrži:

![Izbornik Extra Actions: Read Specific Card Type i rječnici ključeva](/screens/nfc/extra_actions.png)

- **Read Specific Card Type**: preskače automatsko prepoznavanje, korisno za hibridne kartice.
- **MIFARE Classic Keys**, **MIFARE Plus Keys**, **MIFARE Ultralight C Keys**, **MIFARE UL AES Keys**: pregled brojača sistemskog/korisničkog rječnika, **Add** za dodavanje ključa ili **List** (i brisanje) korisničkih ključeva.
- **Unlock NTAG/Ultralight**: generiranje ili unos lozinke prije čitanja. Pogledajte [Otključavanje kartica](/hr/nfc/unlock-with-password).
- **Unlock SLIX-L**: otključavanje lozinkom za oznake ICODE SLIX-L.

::: tip Unleashed
NFC je aplikacija iz službenog firmvera — njezin čitač, emulator i većina parsera kartica. Povrh toga, Unleashed dodaje, među ostalim: prošireni sistemski rječnik za MIFARE Classic (4000+ ključeva), čitanje **MIFARE Plus SL3** s rječnicima AES ključeva, podršku za **MIFARE Ultralight AES**, ključeve portafona **Texkom**, Add Manually za MIFARE Classic s prilagođenim UID-om i za MIFARE Plus, **Save Keys to Dictionary** iz ispisa (dumpa), CUID rječnik (po kartici) s trakom napretka učitavanja te mnogo dodatnih parsera kartica (Troika, Plantain, Umarsh, Zolotaya Korona, Kazan, Metromoney, Moscow Social Card, PPK karte i još mnogo toga).
:::

## Osnove

| Pojam | Značenje |
|---|---|
| **UID** | Serijski broj kartice, 4 ili 7 bajtova (10 na nekima). Tvornički zapisan na izvornim karticama. |
| **ATQA / SAK** | Bajtovi odgovora tijekom antikolizije koji upućuju na vrstu kartice (npr. SAK `08` = MIFARE Classic 1K). |
| **Sektor / blok** | Memorijska jedinica MIFARE Classic: 16 bajtova po bloku, 4 bloka po sektoru (sektori od 16 blokova na kraju 4K kartice). |
| **Stranica (Page)** | Memorijska jedinica Ultralight/NTAG, 4 bajta. |
| **Key A / Key B** | 6-bajtni Crypto-1 ključevi koji štite svaki sektor MIFARE Classic. |
| **Nonce** | Nasumični broj razmijenjen tijekom autentifikacije. Prikupljeni nonceovi omogućuju izračun ključeva izvan mreže. |
| **Magic kartica** | Prazna kartica sa zapisivim UID-om/blokom 0. Pogledajte [Magic kartice](/hr/nfc/magic-cards). |

## Stranice u ovom odjeljku

### Svakodnevna upotreba

- [Čitanje kartica](/hr/nfc/read): čitanje, spremanje, emulacija; koje su vrste kartica podržane i što dobivate od svake.
- [Ručno dodavanje kartica](/hr/nfc/add-manually): generiranje virtualnih kartica, izrada NFC-A kartice iz UID/ATQA/SAK-a.
- [Podržane kartice (parseri)](/hr/nfc/supported-cards): prijevozne, pristupne i igračke kartice koje Flipper može dekodirati.
- [Bankovne kartice (EMV)](/hr/nfc/emv): što se čita s bankovne kartice i zašto se ne može klonirati.
- [Otključavanje kartica lozinkama](/hr/nfc/unlock-with-password): NTAG/Ultralight lozinke, Ultralight C ključevi, SLIX-L.

### MIFARE Classic i oporavak ključeva

- [MIFARE Classic](/hr/nfc/mifare-classic): rječnici, sektori, cjeloviti tijek čitanja, emulacija i pisanje.
- [MFKey32: ključevi s čitača](/hr/nfc/mfkey): prikupljanje nonceova s čitača, oporavak ključeva.
- [Nested napadi i Fudan stražnja vrata](/hr/nfc/nested-fudan): napadi samo na karticu ugrađeni u `Read`.
- [Aplikacija MFKey](/hr/nfc/mfkey-app): oporavak ključeva na samom Flipperu (MFKey 4.1).
- [Brzi oporavak ključeva uz qUnleashed](/hr/nfc/qunleashed): svi napadi na vašem telefonu ili računalu.

### Prazne kartice i kloniranje

- [MIFARE Classic magic kartice](/hr/nfc/magic-cards): Gen1/Gen2/Gen3/Gen4, CUID, FUID, USCUID, UMC i lokalni nazivi.
- [NFC Magic 2.0](/hr/nfc/nfc-magic): pisanje i brisanje magic kartica MIFARE Classic i Ultralight/NTAG.

### Ostale obitelji kartica

- [MIFARE Ultralight AES](/hr/nfc/ultralight-aes): Ultralight zaštićen AES-om (MF0AES20), ključevi, ponovno pisanje, sigurna razmjena poruka.
- [MIFARE Plus](/hr/nfc/mifare-plus): kako se prepoznaju S/X/SE/EV1/EV2 i razine sigurnosti, SL3 AES ključevi.

### Pristupni sustavi (autor @gromovyna)

- [Čitači Iron Logic](/hr/nfc/iron-logic)
- [Dinamički upis na Iron Logic](/hr/nfc/iron-logic-enrollment)
- [Filtri čitača Vizit](/hr/nfc/vizit-filters)
- [Kartice Moskvyonok](/hr/nfc/moskvyonok)

### Referenca

- [Format NFC datoteka](/hr/nfc/file-format): struktura `.nfc` datoteke i formati rječnika.

::: tip Zakonska napomena
Radite samo s vlastitim karticama ili uz izričito dopuštenje. Kopiranje pristupnih ovlasti ili prijevoznih karata koje ne posjedujete može biti nezakonito.
:::

MIFARE, MIFARE Classic, MIFARE Ultralight, MIFARE Plus, MIFARE DESFire, NTAG i ICODE su zaštitni znakovi tvrtke NXP B.V.
FeliCa je zaštitni znak tvrtke Sony Corporation.
