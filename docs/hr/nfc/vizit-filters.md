---
title: Filtri čitača Vizit
order: 120
author: gromovyna
original: [https://telegra.ph/Filtry-schityvatelej-Vizit-dlya-zashchity-ot-klonov-metok-Vizit-RF-31-05-15]
sources: [gromovyna]
---
# Filtri čitača Vizit protiv klonova Vizit RF 3.1

Kako čitači Vizit pokušavaju prepoznati klonirane ključeve **Vizit RF 3.1** (MIFARE Ultralight EV1) i što svaki filtar traži. Temeljeno na članku autora @gromovyna (2025-05-15).

::: tip Opseg
Samo za vlastite pristupne ključeve i zakonito istraživanje.
:::

## Pozadina

Vizit je ruski proizvođač opreme za kontrolu pristupa (prema vlastitim navodima od 1996. godine). Stari čitači koristili su ključeve **Dallas**, zatim **EM Marine**; noviji koriste **Vizit RF 3.1** (= MIFARE Ultralight, UID počinje s `34`); najnoviji ključevi **Vizit RF 7.1** su **MIFARE Ultralight C** (3DES autentifikacija). Minimalni firmver za RF 7.1 naveden je na web-mjestu proizvođača. Autor napominje da je izvođenje ključeva za ključeve 7.1 poznato tvrtki iKey te da zapadni istraživači rade na oporavku 3DES ključeva (pojedinosti nisu objavljene).

## Kako se ovi sustavi brane od kloniranja

Za razliku od sustava Iron Logic, filtri Vizit koje autor poznaje su **softverski**, a ne hardverski, pa su vidljivi u prometu snimljenom pomoću uređaja Proxmark3. Pronađeni su u čitaču **RD-5F, firmver 212**; druge centrale ih također imaju, ali nije poznato u kojoj se verziji pojedini filtar pojavio.

### Filtar 1: Gen1 backdoor

Čitač šalje poznatu backdoor naredbu `40(7)` i čeka odgovor. Izvorna oznaka ne odgovara. Cilja najranije prazne kartice (UL-0116 / UL-0416), koje su se zapisivale putem backdoora uključujući UID.

### Filtar 2: EV1 VERSION

Čitač šalje `EV1 VERSION` i uspoređuje **drugi bajt rezultata** s **prvim bajtom UID-a oznake**. Oznake Vizit RF 3.1 prijavljuju proizvođača **Micron Russia** (bajt `34`), a njihovi UID-ovi počinju s `34`. Time se blokiraju varijante USCUID-UL (kineski „UL-21“, na ruskom tržištu „UL-2“). Odgovor tržišta bile su oznake „ULtra“, USCUID-UL s istom verzijom kao 3.1 (što se može ručno konfigurirati dvjema naredbama u Proxmark3 ako je konfiguracija otvorena). Nakon 2022. u Ukrajini oprema kompatibilna s Vizitom (čitači Grazhda, centrale Mriya) koristi izvorne NXP čipove s ispravnom verzijom, pa kopije ULtra tamo možda neće raditi.

### Filtar 3: OTP

Stranica 3 na Ultralightu je OTP: tvornički su nule, bitovi se mogu postaviti samo na 1, nikada natrag (pogledajte odjeljak 8.5.4 podatkovnog lista MF0ULX1). Na običnim oznakama USCUID-UL ona se može slobodno prepisivati. Čitač pokušava zapisati nule na tu stranicu i ponovno je čita; ako se promijenila, oznaka je kopija, čitač vraća „izvornu“ vrijednost i odbija je. Izvorna oznaka odgovara s **NACK** i prestaje odgovarati do sljedećeg SELECT-a, što je ispravan automat stanja.

Druge implementacije imale su istu grešku: Flipper Zero je ispravan nakon refaktoriranja NFC-a, a emulacija u Proxmark3 imala ju je dok je autor nije prijavio ([issue 2790](https://github.com/RfidResearchGroup/proxmark3/issues/2790)) nakon čega je ispravljena.

Odgovor tvrtke iKey bila je prazna oznaka **UL-5**, zapisiva jednom; nakon promjene stranice 0 zaključava se i ponaša poput izvorne. Iz Kine dolazi s verzijom koja nije Micron Russia. Autor pretpostavlja da se radi o posebno konfiguriranom USCUID-UL čipu. Isti se filtar može proći i na običnom USCUID-UL (primjerice u konfiguraciji ULtra) ispravnom izmjenom konfiguracijskog bloka, ako je otvoren.

## Zaključak za vlasnike

Vizit RF 7.1 (Ultralight C) zadovoljava suvremene sigurnosne standarde i okončava ovu igru mačke i miša.

## Povezano

- [Čitači Iron Logic](/hr/nfc/iron-logic) · [Magic kartice](/hr/nfc/magic-cards) · [Čitanje kartica](/hr/nfc/read)
