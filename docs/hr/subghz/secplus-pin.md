---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (autor @xMasterX) radi s uhvaćenim signalom **tipkovnice Security+ 2.0** — 86-bitnim okvirom signala koji šalju bežične tipkovnice Chamberlain / LiftMaster. PIN tipkovnice nalazi se unutar tog okvira signala. Aplikacija vam omogućuje ručno postavljanje PIN-a ili pretraživanje raspona `0000`–`9999`, odašilje svaki kandidat i zapisuje PIN natrag u datoteku nakon što pronađete ispravni.

::: tip Unleashed
Security+ 2.0 Keypad (86 bitova, 315 / 390 / 868 MHz) dekodira aplikacija Sub-GHz u firmveru Unleashed, a ova ugrađena sustavna aplikacija uređuje njezin PIN. Obični 62-bitni daljinski upravljači Security+ 2.0 nisu okviri signala tipkovnice i bivaju odbijeni.
:::

::: warning
Samo za vlastiti otvarač garažnih vrata i tipkovnicu.
:::

## Prije početka

1. Uhvatite signal svoje tipkovnice pomoću `Sub-GHz → Read` na njezinoj frekvenciji (pogledajte [Čitanje](/hr/subghz/read)) i spremite ga. Spremljena datoteka mora prikazivati `Security+ 2.0` uz `Bit: 86`.
2. Datoteka se nalazi u `/ext/subghz/`.

## Korištenje aplikacije

1. Otvorite `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Odaberite `Open .sub file` i izaberite zapis tipkovnice. Kada se učita, status prikazuje frekvenciju i `ready` (npr. `315MHz  ready`). Ako datoteka već sadrži `Pin`, on se prikazuje.
3. Četiri znamenke PIN-a nalaze se na zaslonu, s okvirom oko aktivne znamenke:
   - <kbd>←</kbd> / <kbd>→</kbd> — pomicanje između znamenki
   - <kbd>↑</kbd> / <kbd>↓</kbd> — promjena PIN-a
   - <kbd>OK</kbd> (`Send`) — odašiljanje trenutačnog PIN-a (`Sending 1234...` → `Sent 1234`)
   - držanje <kbd>OK</kbd> — **pretraživanje (sweep)**: šalje svaki PIN od trenutačnog nadalje; traka napretka prikazuje `N of 9999`. Kratki pritisak <kbd>OK</kbd> ili <kbd>←</kbd> (Back) zaustavlja ga na `Stopped at NNNN`
   - držanje <kbd>←</kbd> — **spremanje** trenutačnog PIN-a u datoteku (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — povratak u izbornik

Redak s naznakom na zaslonu sažima to kao: `hold OK sweep   < save`.

Spremanje ažurira otvorenu datoteku na mjestu: zapisuje polja `Pin`, `Key` i `Secplus_packet_1`. Nakon toga datoteka se može normalno slati iz `Sub-GHz → Saved`.

## Poruke

| Poruka | Značenje |
|---|---|
| `Not Security+ 2.0: …` | datoteka je drugog protokola |
| `Not an 86-bit keypad` | daljinski upravljač Security+ 2.0, a ne okvir signala tipkovnice |
| `Missing packet 1` / `No Key value` | nepotpuno hvatanje — ponovno očitajte tipkovnicu |
| `Unsupported preset …` / `Bad custom preset` | postavka (preset) datoteke ne može se upotrijebiti |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | odašiljanje na ovoj frekvenciji nije dopušteno (pogledajte [Frekvencije](/hr/subghz/frequencies)) |
| `TX failed` | radio nije mogao odaslati signal |

## Rješavanje problema

- **Pretraživanje je sporo** — svaki PIN zasebno je odašiljanje s kratkom pauzom; potpuno pretraživanje traje dugo. Pokrenite ga od vjerojatne vrijednosti i zaustavite čim vrata reagiraju.
- **Vrata su reagirala, ali ste propustili PIN** — pretraživanje se zaustavlja na prikazanom broju; vratite se unatrag pomoću <kbd>↓</kbd> i šaljite pojedinačne PIN-ove tipkom <kbd>OK</kbd> za potvrdu, zatim držite <kbd>←</kbd> za spremanje.
- **Pogrešna datoteka je odbijena** — uhvatite signal same tipkovnice, a ne ručnog daljinskog upravljača.

## Povezane stranice

- [Čitanje](/hr/subghz/read) · [Podržani sustavi](/hr/subghz/supported-systems)
- [Promjenjivi kodovi](/hr/subghz/rolling-codes)
