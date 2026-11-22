---
title: Čitanje oznaka
order: 10
original: [https://docs.flipper.net/zero/rfid/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid]
sources: [unleashed-src, flipper-docs]
---
# Čitanje, spremanje i emulacija 125 kHz oznaka

125 kHz oznaka je transponder koji, kada ga napaja polje čitača, šalje fiksni ID. Ako oznaka koristi jedan od
[podržanih protokola](/hr/rfid/protocols), Flipper Zero dekodira ID, prikazuje ga i može ga spremiti na SD karticu, emulirati
prema čitaču ili [zapisati na praznu oznaku](/hr/rfid/write).

::: tip Umetnite SD karticu
Spremljeni ključevi, rječnici i postavke nalaze se na microSD kartici (`/ext/lfrfid/`). Instalirajte firmver s umetnutom
SD karticom kako bi resursi aplikacije bili dostupni.
:::

## Čitanje oznake

1. Idite u `Main Menu → 125 kHz RFID → Read`.
2. Prislonite oznaku na **stražnju stranu** Flippera, blizu sredine, i držite je mirno. Na zaslonu piše
   *Don't move card*.
3. Flipper prolazi kroz tri prolaza čitanja u trajanju od oko 2 sekunde svaki i prikazuje aktivni prolaz kao
   **Reading 1/3 … 3/3**: **ASK** (125 kHz), **PSK** (125 kHz) i **134kHz** (ASK na 134,2 kHz, za čipove životinja).

   ![Reading 1/3 s aktivnim ASK prolazom, PSK i 134 kHz ispod te porukom "Don't move card" na dnu](/screens/lfrfid/read.png)

4. Pratite LED diodu: treperi **cijan** tijekom čitanja, prelazi na **žutu** kada nešto čuje i **zelenu** kada se
   okviri signala oznake počnu dekodirati — korisno za pronalaženje najboljeg položaja.
5. Kada je oznaka dekodirana, Flipper se oglasi zvučnim signalom i prikazuje zaslon s rezultatom:
   - zaglavlje: proizvođač i protokol, npr. **EM-Micro EM4100**;
   - `Hex:` — sirovi podaci ključa (prvih 7 bajtova, dulji ključevi završavaju s `...`);
   - dekodirana polja (kod objekta, broj kartice itd. — pogledajte [protokole](/hr/rfid/protocols)).

   ![Rezultat čitanja: EM-Micro EM4100 s heksadecimalnim podacima, kodom objekta, brojem kartice, DEZ 8 i DEZ 10, Retry i More na dnu](/screens/lfrfid/read_success.png)

6. Tipke: <kbd>←</kbd> **Retry** (pita *Retry Reading? All unsaved data will be lost*), <kbd>→</kbd> **More**,
   <kbd>Back</kbd> pita želite li izaći i izgubiti nespremljeno očitanje.

::: tip Unleashed
Službena dokumentacija opisuje samo prebacivanje između ASK/PSK načina. Unleashed dodaje treći prolaz **134 kHz** (FDX-A/FDX-B
oznake ugođene su na 134,2 kHz i slabije se odazivaju samo tamo), a za EM4100 prikazuje i **DEZ 8** te **DEZ 10** — decimalne
oblike otisnute na mnogim privjescima. EM4100 koji se dekodira kao Casi-Rusco C10106 kartica dobiva dodatni redak `or C10106: …`,
a Generic HIDProx ključ uspoređuje se s poznatim HID formatima (H10304, H10302, S10401, H10306, Corp1000-35) i prikazuje
njihov FC/broj kartice.
:::

## Nakon čitanja: More

<kbd>→</kbd> **More** otvara:

| Stavka | Radnja |
|---|---|
| **Save** | Unesite naziv (zadani prefiks `RFID`), sprema se kao `/ext/lfrfid/<naziv>.rfid` |
| **Emulate** | Odmah emulirajte ključ, bez spremanja |
| **Write** | Zapišite ključ na praznu oznaku — pogledajte [Pisanje](/hr/rfid/write) |

## Čitanje s fiksnom modulacijom

Nekim je oznakama potrebno više od jednog prolaza od 2 sekunde za dekodiranje ili se pouzdano pronalaze samo određenim demodulatorom.
`Main Menu → 125 kHz RFID → Extra Actions` nudi:

| Stavka | Čita |
|---|---|
| **Read ASK (Regular)** | Samo ASK na 125 kHz, dok se oznaka ne pronađe: EM4100, HID, AWID, Viking, Paradox… |
| **Read PSK (Indala)** | Samo PSK: Indala, Keri, Nexwatch, Idteck… |
| **Read FDX-B (Animals)** | Samo ASK na 134,2 kHz — čipovi za životinje, pogledajte [Mikročipovi za životinje](/hr/rfid/animal-microchips) |

U Debug načinu rada isti izbornik također sadrži **Read RAW RFID data** i **Emulate RAW RFID data** — pogledajte [RAW](/hr/rfid/raw).

## Spremljeni ključevi

`Main Menu → 125 kHz RFID → Saved` otvara preglednik datoteka u `/ext/lfrfid/`. Odabirom `.rfid` ključa otvara se:

![Izbornik spremljene oznake s opcijama Emulate, Write, Write and set password i Edit](/screens/lfrfid/saved_menu.png)

| Stavka | Radnja |
|---|---|
| **Emulate** | Predstavljajte se kao ovaj ključ prema čitaču |
| **Write** | Zapišite ga na praznu oznaku ([Pisanje](/hr/rfid/write)) |
| **Write and set password** | Zapišite na T5577 i zaštitite lozinkom ([Pisanje](/hr/rfid/write#write-and-set-password)) |
| **Edit** | Promijenite podatke ključa u heksadecimalnom obliku; sprema se pod istim nazivom |
| **Rename** | Promijenite naziv datoteke |
| **Delete** | Izbrišite datoteku (uz potvrdu) |
| **Info** | Naziv, protokol, potpuni heksadecimalni podaci i sva dekodirana polja |

::: tip Unleashed
Preglednik također prikazuje **`.t5577`** ispise blokova (označene ikonom T5577). Odabirom jednog pokreće se
[aplikacija T5577](/hr/rfid/t5577-app) s tim ispisom. Ako aplikacija nedostaje, dobit ćete poruku *No T5577 app — It comes with the
firmware - install its resources to get it*.
:::

## Emulacija

1. Otvorite spremljeni ključ (ili svježe očitanje putem **More**) i odaberite **Emulate**.
2. Zaslon prikazuje *Emulating*, `[Protokol]` i naziv ključa (ili *Unsaved Tag*); LED dioda treperi magenta bojom.

   ![Zaslon emulacije s natpisom "Emulating", protokolom [EM4100] i nazivom ključa](/screens/lfrfid/emulate.png)

3. Držite stražnju stranu Flippera ravno uz čitač. Pritisnite <kbd>Back</kbd> za zaustavljanje.

## CLI

Putem USB/serijskog CLI-ja (naredba `rfid`):

```text
rfid read <optional: normal | indala | ask134>   - čitanje u ASK/PSK načinu rada
rfid <write | emulate> <key_type> <key_data>      - pisanje ili emulacija kartice
rfid raw_read <ask | ask134 | psk> <filename>     - čitanje i spremanje sirovih podataka u datoteku
rfid raw_emulate <filename>
rfid raw_analyze <filename>
```

`key_type` je naziv protokola kako je spremljen u `.rfid` datotekama (npr. `EM4100`, `H10301`), `key_data` je u heksadecimalnom obliku.

## Rješavanje problema

- **Ništa nije pronađeno.** Kartica možda radi na 13,56 MHz — pokušajte [NFC](/hr/nfc/read). Mnoge "dualne" kartice sadrže oba čipa.
- **Čitanje se neprestano ponavlja.** Pokušajte fiksni način rada u **Extra Actions** — prolaz od 2 s može biti prekratak za neke oznake.
- **Slabe oznake / mali privjesci.** Polako pomičite oznaku preko stražnje strane; pratite žutu/zelenu LED diodu. Nemojte je držati
  u ruci iznad metala.
- **Nepoznat protokol.** Snimite [RAW](/hr/rfid/raw) zapis i prijavite ga razvojnim programerima.
- **Emulacija nije prihvaćena.** Neki su čitači izbirljivi glede udaljenosti i položaja — držite Flipper ravno, isprobajte
  nekoliko položaja. Čitači koji provjeravaju nešto više od ID-a (npr. kripto kartice) ne mogu se zavarati emulacijom.

## Povezano

- [Pisanje na prazne oznake](/hr/rfid/write) · [Ručno dodavanje](/hr/rfid/add-manually) · [Protokoli](/hr/rfid/protocols) ·
  [Format datoteke](/hr/rfid/file-format)
