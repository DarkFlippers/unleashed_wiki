---
title: Bankovne kartice (EMV)
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/emv, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/NfcFileFormats.md]
sources: [unleashed-src, unleashed-readme, unleashed-docs]
---
# Bankovne kartice (EMV)

Beskontaktne bankovne kartice i mobilni novčanici koriste **EMV** povrh standarda ISO14443-4. Flipper može pročitati **javne** podatke koje kartica daje svakom terminalu i prikazati ih u čitljivom obliku. Ne može pročitati tajne ključeve te **ne može emulirati niti klonirati** bankovnu karticu: svako plaćanje potpisuje se ključem koji nikada ne napušta čip.

::: tip Unleashed
EMV protokol i parser javnih podataka dolaze iz firmvera Unleashed (autori @Leptopt1los i @wosk).
:::

## Čitanje bankovne kartice

1. `Main Menu → NFC → Read`, prislonite karticu (ili otključani telefon s otvorenim novčanikom) na stražnju stranu Flippera.
2. Obradeni rezultat prikazuje što je kartica otkrila, primjerice:
   - oznaku ili naziv aplikacije (npr. platni sustav) ili samo `EMV`;
   - broj kartice (PAN), grupiran po 4 znamenke;
   - `Cardholder name:` (većina modernih kartica više ga ne šalje);
   - datume `Effective:` / `Expires:` (u formatu datuma vaših regionalnih postavki);
   - `Country:` i `Currency:` izdavatelja;
   - `PIN attempts left:`;
   - `Mobile: yes` za novčanike na telefonu/satu;
   - *„No data was parsed“* ako nije vraćeno ništa korisno.
3. <kbd>→</kbd> **More** otvara izbornik: **Save**, **Transactions** (samo ako je kartica vratila zapisnik transakcija), **Info**.

Zaslon **Info** prikazuje tehnički pregled: UID, `AID`, `Interchange profile`, `Currency code`, `Country code`, `Transactions count` i `Last Online ATC` ako su dostupni.

## Transakcije

Neke kartice čuvaju kratak zapisnik nedavnih transakcija i daju ga bez PIN-a. `More → Transactions` navodi svaki unos s njegovim brojačem (ATC), iznosom, valutom, državom te datumom/vremenom ako postoje (`???` / `UNK` za nepoznate vrijednosti).

## Nazivi država, valuta i aplikacija

EMV parser prevodi kodove koristeći tablice za pretraživanje na SD kartici:

- `/ext/nfc/assets/aid.nfc`: ID-ovi aplikacija → nazivi;
- `/ext/nfc/assets/country_code.nfc`: ISO kodovi država;
- `/ext/nfc/assets/currency_code.nfc`: ISO kodovi valuta.

Svaka datoteka ima zaglavlje `Filetype: Flipper EMV resources`, `Version: 1`, a zatim retke `<code>: <name>`, npr. `0985: PLN`. Pogledajte [format datoteke](/hr/nfc/file-format#emv-resources).

## Što ne radi i zašto

- **Emulacija / plaćanje**: nije moguće. Kartica izračunava kriptogram za svaku transakciju svojim privatnim ključevima.
- **Nedostaje broj kartice**: neke kartice i većina mobilnih novčanika daju tokenizirani broj ili ne daju ništa bez dijaloga s terminalom.
- **Hibridne kartice** (bankovna kartica + čip za javni prijevoz/pristup): koristite `Extra Actions → Read Specific Card Type` za čitanje drugog dijela.

::: warning Privatnost
Spremljeni EMV dump može sadržavati broj vaše kartice i datum isteka. Nemojte ga dijeliti.
:::

## Povezano

[Čitanje kartica](/hr/nfc/read) · [Podržane kartice](/hr/nfc/supported-cards) · [Format NFC datoteka](/hr/nfc/file-format)
