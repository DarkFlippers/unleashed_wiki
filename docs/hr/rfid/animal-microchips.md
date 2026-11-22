---
title: Mikročipovi za životinje
order: 50
original: [https://docs.flipper.net/zero/rfid/animal-microchips, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid/protocols]
sources: [unleashed-src, flipper-docs]
---
# Mikročipovi za životinje (FDX-B, FDX-A)

Mikročipovi za kućne ljubimce su RFID transponderi veličine zrna riže ugrađeni pod kožu. Kada ih čitač napoji, šalju
ID koji se može potražiti u bazama podataka za pronalazak kućnih ljubimaca. Flipper Zero čita dvije uobičajene LF vrste:

| Vrsta | Naziv na Flipperu | Opis |
|---|---|---|
| **FDX-B** | `FDX-B` (ISO) | ISO 11784/11785, 15-znamenkasti ID; najčešća vrsta; neki čipovi javljaju i tjelesnu temperaturu |
| **FDX-A** | `FDX-A` (FECAVA) | Stariji 10-znamenkasti čipovi koji nisu po ISO standardu |

Većina čipova za životinje radi na **134,2 kHz**, dok je antena Flippera ugođena na 125 kHz, pa je domet čitanja
kratak — oko **1 cm**. Mikročipovi u rasponu 110–140 kHz mogu se pročitati, ali iz veće blizine.

::: tip Unleashed
Službena dokumentacija upućuje vas na korištenje opcije *Read ASK*. Unleashed generira stvarno polje od **134,2 kHz** za ove čipove:
- **Read** sada pokreće treći prolaz, **134kHz**, nakon ASK i PSK;
- `Extra Actions → Read FDX-B (Animals)` ostaje na 134,2 kHz cijelo vrijeme — najbolji izbor za slabe čipove;
- naziv države za FDX-B traži se u `/ext/lfrfid/assets/iso3166.lfrfid`.
:::

## Čitanje čipa kućnog ljubimca

1. Idite na `Main Menu → 125 kHz RFID → Extra Actions → Read FDX-B (Animals)`. Zaslon prikazuje *Reading FDX-B*.
2. Pronađite čip:
   - psi i mačke: obično pod kožom **između lopatica**; u kontinentalnoj Europi često **na sredini
     lijeve strane vrata**. Čipovi se mogu malo pomaknuti;
   - lagano opipajte vršcima prstiju čvrst predmet veličine zrna riže, a zatim postavite sredinu poleđine Flippera izravno
     preko njega.
3. Držite Flipper mirno oko **3 sekunde** na svakom mjestu. Ako nema ništa, pomičite ga u malim koracima preko tog područja,
   zatim zakrenite Flipper za 90° i ponovite.
4. Pratite LED diodu: žuta/zelena znači da se signal hvata — ostanite tu.
5. Nakon dekodiranja dobit ćete zaslon s rezultatima. Pritisnite <kbd>→</kbd> **More → Save** da biste ga spremili.

## Što Flipper prikazuje za FDX-B

| Polje | Značenje |
|---|---|
| `ID: CCC-NNNNNNNNNNNN` | 3-znamenkasti kôd države (ISO 3166-1 numerički) ili proizvođača + 12-znamenkasti nacionalni ID — 15-znamenkasti broj za pretraživanje |
| Country Code / Country | Kôd i njegov naziv iz tablice ISO 3166 |
| Temperature | Za termo-čipove, u °C i °F; `---` ako nije prisutno |
| Animal | Oznaka primjene na životinji |
| Visual Start Digit, Replacement Number, User Info, RFU | Polja zaglavlja ISO okvira |
| Data Block | Present / Absent — dodatni blok podataka (npr. temperatura) |
| RUDI Bit | Yes / No |

FDX-A prikazuje 10-znamenkasti heksadecimalni `ID` i `Parity`.

::: warning
Temperatura s čipa nije zamjena za pravi toplomjer.
:::

## Pretraživanje ID-a

Unesite 15-znamenkasti ID u bazu podataka za pronalazak kućnih ljubimaca, primjerice:
- [AAHA Pet Microchip Lookup](https://www.aaha.org/petmicrochiplookup) — SAD i Kanada
- [Europetnet](https://www.europetnet.com/) — Europa
- [PETMAXX](http://www.petmaxx.com/) — diljem svijeta

Ili pitajte svog lokalnog veterinara / registar kućnih ljubimaca.

## Ako čip nije pronađen

- Izvan dometa — koristite manje korake i zadržite se dulje na svakoj točki.
- Čip se pomaknuo — skenirajte veće područje.
- Metal ili elektronika u blizini — odmaknite se od njih.
- Životinja možda ima čip od 13,56 MHz — pokušajte [NFC](/hr/nfc/read).
- Nepodržani čip — zamolite veterinara da ga očita.

FDX-B ključevi također se mogu [emulirati ili zapisati](/hr/rfid/write) (na prazne oznake T5577 i EM4305, koje postoje i kao staklene ampule),
npr. za testiranje vratašca za kućne ljubimce.

## Povezano

- [Čitanje](/hr/rfid/read) · [Protokoli](/hr/rfid/protocols) · [Pisanje](/hr/rfid/write)
