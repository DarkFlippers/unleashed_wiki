---
title: MIFARE Classic
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols/mf_classic, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://telegra.ph/Gajd-po-novomu-Nested-i-Fudan-behkdoram-dlya-Flipper-11-13, https://telegra.ph/Vskryvaem-bystro-kriptoklyuchi-Mifare-Classic-s-pomoshchyu-qUnleashed-09-18]
sources: [flipper-docs, unleashed-src, unleashed-readme, gromovyna]
---
# MIFARE Classic

MIFARE Classic je najčešća kartica u sustavima kontrole pristupa, portafonima, hotelima i starijim sustavima javnog prijevoza. Ujedno je i „najzanimljivija” za Flipper: njezina šifra Crypto-1 je probijena, pa se uz dovoljno truda ključevi gotovo svake kartice mogu otkriti, a kartica se potom može emulirati ili zapisati na [magic karticu](/hr/nfc/magic-cards).

## Raspored memorije

| Vrsta | Sektori | Blokovi | Ključevi za pronalazak | Tipični SAK |
|---|---|---|---|---|
| MIFARE Mini | 5 | 20 | 10 | `09` |
| MIFARE Classic 1K | 16 | 64 | 32 | `08` |
| MIFARE Classic 4K | 40 (32 × 4 bloka + 8 × 16 blokova) | 256 | 80 | `18` |

- **Blok** ima 16 bajtova. **Blok 0** (proizvođački blok) sadrži UID i podatke proizvođača; na izvornim karticama dostupan je samo za čitanje, što je upravo razlog postojanja magic kartica.
- Posljednji blok svakog sektora je **trailer sektora** (*sector trailer*): `Key A (6 bajtova) | pristupni bitovi (4 bajta) | Key B (6 bajtova)`, npr. `FF FF FF FF FF FF FF 07 80 69 FF FF FF FF FF FF` na praznoj kartici.
- Pristupni bitovi određuju koji ključ smije čitati ili pisati koji blok. Često Key A čita, a Key B piše; ponekad je i sam Key B čitljiv te se tada ne može koristiti kao ključ.

## Rječnici ključeva

Flipper nikada ne „zna” ključeve unaprijed: isprobava kandidate ključeva iz rječnika. Svi su oni obične tekstualne datoteke s po jednim 12-znamenkastim heksadekadskim ključem po retku i znakom `#` za komentare (pogledajte [format datoteke](/hr/nfc/file-format)).

| Rječnik | Putanja | Tko ga piše |
|---|---|---|
| **System** | `/ext/nfc/assets/mf_classic_dict.nfc` | Dolazi s firmverom (prepisuje se pri ažuriranju). U firmveru Unleashed sadrži **4000+ ključeva**. |
| **User** | `/ext/nfc/assets/mf_classic_dict_user.nfc` | Vi, MFKey, qUnleashed, *Save Keys to Dictionary*. Preživljava ažuriranja. |
| **CUID** (po kartici) | `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` | MFKey / qUnleashed za kartice sa *static encrypted* jednokratnim brojevima (*nonces*): velik popis kandidata ključeva za jedan UID. |
| **Predmemorija ključeva** | `/ext/nfc/.cache/<UID>.keys` | Zapisuje se automatski kada **spremite** karticu; koristi se prva pri sljedećem čitanju istog UID-a. |

::: tip Unleashed
Sustavni rječnik firmvera Unleashed sadrži velik skup dodatnih ključeva koje je prikupila zajednica („Extra Mifare Classic keys in system dict” u ReadMe datoteci). Zaslon učitavanja CUID rječnika s trakom napretka (*"CUID dictionary is loading"*) pojavio se u dev izdanju 1437 / izdanju 094.
:::

### Upravljanje korisničkim rječnikom na uređaju

1. Idite na `Main Menu → NFC → Extra Actions → MIFARE Classic Keys`.

   ![Izbornik Extra Actions s opcijom MIFARE Classic Keys među stavkama rječnika](/screens/nfc/extra_actions.png)

2. Na zaslonu se prikazuju **System dict: N** i **User dict: N**.
3. <kbd>OK</kbd> **Add**: unesite 6-bajtni ključ u heksadekadskom zapisu i spremite. Duplikat ključa pokreće upozorenje.
4. <kbd>→</kbd> **List** (samo ako korisnički rječnik nije prazan): odaberite ključ za brisanje (*"Select key to delete:"*).

Datoteku `mf_classic_dict_user.nfc` možete uređivati i na računalu (qFlipper, qUnleashed ili izravno na SD kartici).

### Save Keys to Dictionary {#save-keys-to-dictionary}

Svaki spremljeni ili tek pročitani sadržaj (*dump*) kartice MIFARE Classic s barem jednim poznatim ključem ima u svom izborniku stavku **Save Keys to Dictionary**. Ona kopira sve ključeve iz tog sadržaja u korisnički rječnik, preskačući duplikate, i javlja *"New keys: N, Already known: M"*. To je najvažnije za kartice čiji su ključevi otkriveni iz CUID rječnika: ti ključevi inače postoje samo u toj datoteci za pojedini UID i u samom sadržaju kartice, dok [NFC Magic](/hr/nfc/nfc-magic) gleda samo predmemoriju ključeva te korisnički i sustavni rječnik (to je „automatsko spremanje ključeva s provjerom duplikata” koje @gromovyna spominje u svom [članku o qUnleashedu](/hr/nfc/qunleashed)).

## Što se događa kada čitate karticu MIFARE Classic

`Main Menu → NFC → Read`, držite karticu mirno. Firmver prolazi kroz ove faze; zaglavlje zaslona napada prikazuje koja je trenutačno pokrenuta.

1. **Predmemorija ključeva.** Ako ste već spremili ovaj UID, koriste se predmemorirani ključevi i kartica se čita odmah.
2. **Napad rječnikom**, ovim redoslijedom:
   - **MF Classic CUID Dictionary**: samo ako postoji datoteka za taj UID (prije nje se prikazuje *"CUID dictionary is loading"* s trakom napretka; velika datoteka učitava se minutama).
   - **MF Classic User Dictionary**: ako korisnička datoteka postoji i nije prazna.
   - **MF Classic System Dictionary**.

   Zaslon prikazuje `Keys found: X/Y`, `Sectors Read: X/Y`, trenutačni broj ključa te *"Unlocking sector: N"* / *"Reuse key check for sector: N"*.

   ![Napad sustavnim rječnikom: otključavanje sektora 9, ključ 1244 od 2271, pronađeno 19 od 32 ključa](/screens/nfc/dict_attack.png)

3. **Čitanje stražnjim vratima (*backdoor*).** Ako čip ima poznati **backdoor ključ** (Fudan i neki drugi), zaglavlje prikazuje **Backdoor Read** / **(Backdoor)** i sektori se čitaju bez pravih ključeva. Istovremeno se prikupljaju jednokratni brojevi (*nonces*).
4. **Ugniježđeni napadi (*Nested*)** (nakon što je poznat barem jedan ključ): **PRNG Analysis**, **Nested Dictionary**, **Calibration**, **Nonce Collection** (*"Collecting from sector: N"*). Nastavak **(Hard)** znači da kartica ima tvrdi PRNG. Prikupljeni jednokratni brojevi dodaju se u `/ext/nfc/.nested.log`.
5. Otvara se zaslon rezultata. Zelena LED dioda / zvuk uspjeha znače da je kartica u potpunosti pročitana, a kratki „poluuspjeh” znači da neki sektori još nedostaju.

Pritisnite <kbd>OK</kbd> **Skip** za skok na sljedeću fazu (CUID → User → System → rezultat). <kbd>←</kbd> pita *"Exit to NFC Menu? All unsaved data will be lost"*. Ako odmaknete karticu, prikazuje se **"Lost the tag! Make sure the tag is positioned correctly."**; vratite je i napad se nastavlja.

Detaljan vodič sa snimkama zaslona svake faze nalazi se na stranici [Ugniježđeni napadi i Fudan stražnja vrata](/hr/nfc/nested-fudan).

### Nakon čitanja

Izbornik nakon čitanja (`More`) za karticu MIFARE Classic sadrži:

| Stavka | Kada | Što radi |
|---|---|---|
| **Save** | uvijek | Sprema sadržaj (*dump*) u `/ext/nfc/`. Također popunjava predmemoriju ključeva. |
| **Emulate** | uvijek | Potpuna emulacija sadržaja. |
| **Extract MFC Keys** | kartica nije u potpunosti pročitana | Pita *"Save the Key?"* (Save/Skip), zatim prikuplja jednokratne brojeve s čitača. Pogledajte [MFKey32](/hr/nfc/mfkey). |
| **Unlock with Dictionary** | kartica nije u potpunosti pročitana | Ponovno pokreće napad rječnikom/ugniježđeni napad (npr. nakon što ste dodali ključeve). |
| **Crack nonces in MFKey32** | kartica nije u potpunosti pročitana | Nudi spremanje kartice, zatim pokreće [aplikaciju MFKey](/hr/nfc/mfkey-app) (**Run**). |
| **Show Keys** | uvijek | *"Found MFC Keys"*: pristupni bitovi po sektoru, Key A, Key B i ukupni brojevi. |
| **Save Keys to Dictionary** | poznat barem jedan ključ | Pogledajte iznad. |
| **Info** | uvijek | UID, ATQA, SAK, sažetak ključeva/sektora; **More** prikazuje heksadekadski ispis (`??` = nepoznati bajtovi). |

Na **spremljenoj** kartici dodatno dobivate **Write to Initial Card**, **Update from Initial Card**, **Restore to Original State** (ako postoji *shadow* datoteka), **Rename** i **Delete**.

## Pronalazak nedostajućih ključeva

Ako nisu pročitani svi sektori, odaberite metodu koja odgovara vašoj situaciji:

| Situacija | Metoda |
|---|---|
| Imate karticu **i** pristup čitaču | [MFKey32](/hr/nfc/mfkey): Flipper emulira karticu, čitač otkriva svoje ključeve. |
| Imate karticu, poznat je barem jedan ključ ili čip ima *backdoor* | Ugniježđeni napadi automatski se izvode u `Read`; zatim izračunajte ključeve pomoću [aplikacije MFKey](/hr/nfc/mfkey-app) ili, znatno brže, [qUnleasheda](/hr/nfc/qunleashed). |
| Kartica ima **tvrdi PRNG** | HardNested: izračunava se u qUnleashedu ili na računalu, pogledajte [Ugniježđeni napadi](/hr/nfc/nested-fudan). |
| Nema kartice, samo čitač | [MFKey32](/hr/nfc/mfkey) putem `Extract MFC Keys` iz glavnog NFC izbornika: ključevi idu u korisnički rječnik za kasniju upotrebu. |
| Ključevi su diversificirani po kartici (npr. [Iron Logic](/hr/nfc/iron-logic)) | Svaka kartica ima vlastite ključeve: otkrijte ih za svaku karticu pojedinačno. |

Nakon dodavanja novih ključeva ponovno pročitajte karticu (ili otvorite spremljenu datoteku → **Unlock with Dictionary**).

## Emulacija

1. `Main Menu → NFC → Saved → <card> → Emulate`.
2. Prislonite Flipper na čitač.

Sektori koji nikada nisu pročitani emuliraju se kao nepoznati: čitač koji ih treba odbit će karticu. Ako čitač zapisuje na karticu (stanje računa, brojači, „dinamički” sustavi), promjene idu u [shadow datoteku](/hr/nfc/read#shadow-files).

::: warning Dinamički sustavi
Neki sustavi pri svakom prolazu iznova zapisuju podatke na karticu (npr. [Iron Logic u dinamičkom načinu](/hr/nfc/iron-logic-enrollment)). Emulirana kopija i izvornik tada gube sinkronizaciju; korištenje obaju može blokirati izvornu karticu.
:::

## Pisanje

- **Write to Initial Card** zapisuje sadržaj natrag **na istu karticu** (UID se mora podudarati). Svaka druga kartica daje poruku *"Use source card! To write blanks use NFC Magic app"*. Ako se nije mogao zapisati svaki blok: *"Not all sectors were written correctly"*.
- Za kloniranje na praznu karticu koristite aplikaciju [NFC Magic](/hr/nfc/nfc-magic) i odgovarajuću [magic karticu](/hr/nfc/magic-cards). Pažljivo odaberite praznu karticu: mnogi čitači filtriraju Gen1 kartice.

## Rješavanje problema

- **Ključevi su pronađeni, ali neki sektori i dalje nisu pročitani**: pristupni bitovi možda zabranjuju čitanje pronađenom vrstom ključa; otkrijte drugi ključ (A ili B).
- **Čitanje započinje dugim "CUID dictionary is loading"**: postoji velik popis kandidata za pojedini UID ove kartice. To je očekivano nakon napada sa statičnim šifriranim jednokratnim brojevima. Izbrišite `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` nakon što je kartica u potpunosti pročitana i njezini su ključevi spremljeni u korisnički rječnik.
- **MFKey javlja "Nonces already cracked" / ništa novo**: očistite `/ext/nfc/.nested.log` i `/ext/nfc/.mfkey32.log` nakon uspješnog oporavka; stari jednokratni brojevi usporavaju sve.
- **Otkriveni ključevi kao da se ne koriste**: provjerite jesu li zaista završili u `mf_classic_dict_user.nfc` (`Extra Actions → MIFARE Classic Keys → List`). Ključevi pronađeni pomoću HardNested na računalu moraju se dodati ručno.

## Povezano

[Čitanje kartica](/hr/nfc/read) · [MFKey32](/hr/nfc/mfkey) · [Ugniježđeni napadi](/hr/nfc/nested-fudan) ·
[Aplikacija MFKey](/hr/nfc/mfkey-app) · [qUnleashed](/hr/nfc/qunleashed) · [Magic kartice](/hr/nfc/magic-cards) ·
[MIFARE Plus](/hr/nfc/mifare-plus)
