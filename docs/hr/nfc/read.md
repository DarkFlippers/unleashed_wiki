---
title: Čitanje kartica
order: 10
original: [https://docs.flipper.net/zero/nfc/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/nfc, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/nfc/protocols]
sources: [flipper-docs, unleashed-src]
---
# Čitanje, spremanje i emulacija NFC kartica

`Read` je glavna ulazna točka NFC aplikacije. Flipper sam prepoznaje protokol, čita sve podatke do kojih može doći,
pokreće napade za otkrivanje ključeva gdje su primjenjivi (MIFARE Classic, Ultralight C, Ultralight AES, MIFARE Plus SL3) i zatim vam omogućuje
spremanje, emulaciju ili pisanje rezultata.

## Čitanje kartice

1. Idite u `Main Menu → NFC → Read`.
2. Na zaslonu piše **"Reading — Hold card next to Flipper's back"**. Prislonite karticu ravno uz **sredinu stražnje strane**
   Flippera i držite je mirno.

   ![Zaslon čitanja: Hold card next to Flipper's back](/screens/nfc/reading.png)

3. Kada kartica bude pronađena, vidjet ćete **"Don't move"** dok se podatci učitavaju. Za zaštićene kartice može se pojaviti
   zaslon napada (napad rječnikom, ugniježđeni napad, pogledajte [MIFARE Classic](/hr/nfc/mifare-classic)).

   ![Sustavni napad rječnikom za MIFARE Classic: otključavanje sektora 9, pronađeno 19 od 32 ključa](/screens/nfc/dict_attack.png)

4. Zaslon rezultata prikazuje naziv kartice i sažetak. Ako je [raščlanjivač (parser)](/hr/nfc/supported-cards) prepoznao karticu,
   vidite dekodirane podatke (stanje računa, broj vožnji, broj kartice…).

   ![Rezultat čitanja: MIFARE Classic 1K s UID-om, 32/32 pronađena ključa i 16/16 pročitanih sektora](/screens/nfc/card_info.png)

   - <kbd>←</kbd> **Retry**: pita *"Retry Reading? All unsaved data will be lost"*.
   - <kbd>→</kbd> **More**: otvara izbornik kartice.
5. U izborniku **More** odaberite **Save**, upišite naziv pod **"Name the card"** i potvrdite. Datoteka se sprema u
   `/ext/nfc/<name>.nfc`.

Izbornik `More` nakon čitanja uvijek sadrži **Save** i **Info**; ovisno o vrsti kartice sadrži i
**Emulate** / **Emulate UID**, te stavke specifične za protokol (npr. **Unlock**, **Show Keys**, **Extract MFC Keys**,
**Transactions** za EMV).

### Višeprotokolne kartice

Neke kartice odgovaraju na više protokola (na primjer bankovna kartica koja sadrži i područje MIFARE Classic).
Flipper tada prikazuje izbornik **"Multi-protocol card"** sa stavkama poput **Read as MIFARE Classic**. Kako biste potpuno preskočili
automatsko prepoznavanje, koristite `Main Menu → NFC → Extra Actions → Read Specific Card Type`, odaberite vrstu i pritisnite
<kbd>OK</kbd>.

## Podržane vrste kartica

| Obitelj | Vrste kartica (prema nazivu u firmveru) | Čitanje | Emulacija | Pisanje |
|---|---|---|---|---|
| ISO14443-3A (NFC-A) | Bilo koja NFC-A kartica: UID, ATQA, SAK | da | samo UID | — |
| MIFARE Classic | Mini, 1K, 4K (4- i 7-bajtni UID) | sektori s poznatim ključevima | potpuno | samo na izvornu karticu |
| MIFARE Ultralight / NTAG | Ultralight, Ultralight 11/21 (EV1), Ultralight C, Ultralight AES, NTAG203/210/212/213/215/216, NTAG I2C 1K/2K, NTAG I2C Plus 1K/2K | otvorene stranice, više nakon otključavanja | potpuno | ista vrsta (vidi dolje) |
| MIFARE Plus | Plus, S, X, SE, EV1, EV2; SL0–SL3 | SL1 kao Classic, SL3 s AES ključevima | SL3 potpuno, ostali UID | SL3 na izvornu karticu |
| MIFARE DESFire | DESFire | nezaštićene aplikacije i datoteke | samo UID | — |
| ISO14443-4A | Nepoznate ISO-DEP kartice | UID, ATQA, SAK, ATS | samo UID | — |
| NTAG4xx, Type 4 Tag | NTAG 4xx DNA; NFC Forum Type 4 oznake (NDEF) | da | NTAG4xx: UID; T4T: potpuno | T4T: da |
| EMV | Bankovne kartice | javni podatci | — | — |
| ISO14443-3B / -4B | NFC-B kartice | UID, podatci aplikacije, informacije o protokolu | — | — |
| ST25TB | ST25TB512, ST25TB512-AC, SRIX512, ST25TB02K, ST25TB04K, SRIX4K | da | — | — |
| ISO15693-3 (NFC-V) | Nepoznate NFC-V oznake | UID + čitljivi blokovi | potpuno | da |
| SLIX | ICODE SLIX, SLIX-S, SLIX-L, SLIX2 | da, otključavanje lozinkom | potpuno | da |
| FeliCa | FeliCa (Lite-S i druge) | IDm, PMm, blokovi | potpuno | — |
| Texkom | Texkom TK13, TK15, TK17, MMBIT portafonski ključevi | da | potpuno | — |

::: tip Unleashed
Ključevi **Texkom** (13,56 MHz portafonski privjesci uobičajeni u Rusiji koji ne implementiraju nijedan ISO standard), izvadci **MIFARE Plus SL3**
s AES ključevima, **Ultralight AES** i proširena podrška za **Write** na Ultralightu dodaci su firmvera koje
nećete pronaći u tvorničkom firmveru. MIFARE Classic također dobiva CUID rječnik i **Save Keys to Dictionary**.
:::

### MIFARE Classic

Za čitanje sektora Flipper treba ključeve: do **10 ključeva za 5 sektora** (Mini), **32 ključa za 16 sektora** (1K) ili
**80 ključeva za 40 sektora** (4K). Prvo isprobava predmemoriju ključeva pojedine kartice, zatim CUID, korisnički i sustavni rječnik, a potom
ugniježđene napade. Pojedinosti su na stranici [MIFARE Classic](/hr/nfc/mifare-classic); ako ključevi i dalje nedostaju, pogledajte
[MFKey32](/hr/nfc/mfkey) i [Ugniježđeni napadi](/hr/nfc/nested-fudan).

### MIFARE Ultralight i NTAG

Otvorene stranice čitaju se izravno. Stranice zaštićene lozinkom (NTAG21x, Ultralight EV1), 3DES ključem (Ultralight C) ili
AES ključem (Ultralight AES) ostaju zaključane dok ih ne otključate; pogledajte [Otključavanje kartica](/hr/nfc/unlock-with-password) i
[Ultralight AES](/hr/nfc/ultralight-aes). Ultralight C i Ultralight AES automatski pokreću napad rječnikom.

**Write** je ponuđen za potpuno pročitane izvatke kartica **NTAG213, NTAG215, NTAG216, Ultralight, Ultralight 11, Ultralight 21,
Ultralight C** i **Ultralight AES**, na karticu iste vrste. Ultralight C i AES imaju dvije stavke:
**Write (Keep Key)** zadržava ključ ciljne kartice, a **Write (Copy Key)** također zapisuje ključ iz izvatka. Ako je
ciljna kartica zaštićena lozinkom, AUTH0 ili bitovima zaključavanja, dobivate poruku *"Card protected by password, AUTH0 or lock bits"*.

### Nepoznate kartice

Za nepoznatu NFC-A karticu spremaju se samo UID, ATQA i SAK; za nepoznatu NFC-V oznaku spremaju se UID i čitljivi
blokovi. Mnogi jednostavni čitači za kontrolu pristupa provjeravaju samo UID, pa **Emulate UID** i dalje može raditi.

## Spremljene kartice

`Main Menu → NFC → Saved` prikazuje vaše `.nfc` datoteke. Izbornik spremljene kartice sadrži (ovisno o vrsti):

- **Emulate** ili **Emulate UID**
- **Write** / **Write to Initial Card** (MIFARE Classic, MIFARE Plus SL3) / **Write (Keep Key)** + **Write (Copy Key)**
- **Edit UID** (NFC-A, ISO14443-4A, ISO15693)
- stavke protokola: **Unlock**, **Unlock with Dictionary**, **Extract MFC Keys**, **Update from Initial Card**,
  **Show Keys**, **Save Keys to Dictionary**, **Reveal Real UID**…
- **Restore to Original State** (samo kada postoji datoteka u sjeni, vidi dolje)
- **Rename**, **Delete**, **Info**

## Emulacija kartice

1. Idite u `Main Menu → NFC → Saved`, odaberite karticu.
2. Odaberite **Emulate** (potpuna emulacija) ili **Emulate UID** (šalju se samo UID/ATQA/SAK).
3. Zaslon prikazuje **Emulating** s nazivom kartice. Prislonite stražnju stranu Flippera uz čitač.
4. Ako je čitač komunicirao s emuliranom karticom, pojavljuje se gumb **Log** (<kbd>OK</kbd>) koji prikazuje razmjenu podataka.
5. Pritisnite <kbd>←</kbd> za zaustavljanje.

### Datoteke u sjeni (Shadow files) {#shadow-files}

Kada čitač zapisuje podatke na emuliranu karticu (na primjer ažurira stanje ili brojač), Flipper ne mijenja
vašu izvornu datoteku. Novo stanje zapisuje u **datoteku u sjeni** pokraj nje (`<name>.shd`). Izvorni izvadak ostaje
netaknut:

- **Restore to Original State** (`Saved → card`): pita *"Restore Card Data?"* i briše datoteku u sjeni.
- **Update from Initial Card** (MIFARE Classic, MIFARE Plus SL3): ponovno čita fizičku karticu sa spremljenim ključevima i
  osvježava izvadak. Prihvaća se samo izvorna kartica, inače javlja *"Wrong Card! Data management is only possible
  with source card"*.

## Ako čitanje ne uspije

- **Ništa se ne otkriva**: kartica je možda 125 kHz kartica. Pokušajte `Main Menu → 125 kHz RFID → Read`
  (pogledajte [odjeljak RFID](/hr/rfid/read)).
- **Otkrivena je pogrešna vrsta / hibridna kartica**: koristite `Extra Actions → Read Specific Card Type`.
- **"Lost the tag!"** tijekom dugog napada: vratite karticu na isto mjesto i držite je mirno. Debele maskice i
  metal iza kartice ometaju polje.
- **Nisu pročitani svi sektori / stranice**: kartica je zaštićena. Nastavite uz [MIFARE Classic](/hr/nfc/mifare-classic),
  [MFKey32](/hr/nfc/mfkey) ili [Otključavanje kartica](/hr/nfc/unlock-with-password).
- **"Plugin Not Loaded — Plugin file missing or outdated"**: datoteke raščlanjivača `.fal` na SD kartici ne odgovaraju
  firmveru. Ponovno instalirajte/ažurirajte firmver s umetnutom SD karticom.

## Povezano

- [MIFARE Classic](/hr/nfc/mifare-classic) · [Podržane kartice](/hr/nfc/supported-cards) · [Format NFC datoteke](/hr/nfc/file-format)
- [Magic kartice](/hr/nfc/magic-cards) · [NFC Magic 2.0](/hr/nfc/nfc-magic)
