---
title: Snimanje u RAW načinu
order: 80
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/LFRFIDRaw.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/lfrfid_debug]
sources: [unleashed-docs, unleashed-src]
---
# Čitanje RAW 125 kHz podataka

RAW način bilježi signal oznake onakav kakav jest — trajanja impulsa i perioda — umjesto da ga dekodira, pomalo nalik
diktafonu. Namijenjen je **istraživanju protokola**: ako vaša oznaka nije prepoznata, snimite je i pošaljite datoteke (te
fotografiju kartice) razvojnim programerima u GitHub issueu.

## Uključivanje načina Debug

RAW stavke skrivene su dok Debug nije uključen:

1. `Main Menu → Settings → System`.
2. Postavite **Debug** na **ON**.

## Snimanje

1. Idite na `Main Menu → 125 kHz RFID → Extra Actions → Read RAW RFID data`.
2. Imenujte snimku (zadano `RfidRecord`).
3. Pročitajte upute (*RAW RFID Data Reader — 1. Hold card next to Flipper, 2. Press OK, 3. Wait until data is
   read*) i pritisnite <kbd>OK</kbd>.
4. Držite karticu na poleđini Flippera. Flipper snima tri prolaza od po **5 sekundi** — *Reading ASK*,
   *ASK 134kHz*, *Reading PSK* — i traži *Don't move for 5 sec.*
5. **RAW RFID Read Success** — *Now you can analyze files or send them to developers*. Pritisnite <kbd>OK</kbd>.

U `/ext/lfrfid/` stvaraju se tri datoteke:

| Datoteka | Prolaz |
|---|---|
| `<name>.ask.raw` | ASK, nositelj 125 kHz |
| `<name>.ask134.raw` | ASK, nositelj 134,2 kHz |
| `<name>.psk.raw` | PSK, nositelj 125 kHz |

::: tip Unleashed
Dokumentacija firmvera Unleashed i tvornički firmver spominju dvije datoteke (ASK i PSK). Trenutačni firmver snima i treći,
**ASK 134kHz**, prolaz za životinjske oznake.
:::

Ako vidite *RAW Reading error! This may be caused by SD card issues*, provjerite karticu (slobodan prostor, pogreške). Bez
microSD kartice aplikacija prikazuje *No SD Card!*.

## Reprodukcija

`Extra Actions → Emulate RAW RFID data` otvara preglednik datoteka za `.raw` datoteke i reproducira odabranu
(*Emulating RAW RFID*). To je ponajprije korisno za otklanjanje pogrešaka protokola, a ne kao zamjena za uobičajenu emulaciju.

## CLI

Isto je dostupno putem sučelja CLI i praktično je za razvoj:

```text
rfid raw_read <ask | ask134 | psk> <filename>   - čitanje i spremanje RAW podataka u datoteku
rfid raw_emulate <filename>                     - emuliranje RAW podataka
rfid raw_analyze <filename>                     - ispis RAW podataka i pokušaj dekodiranja
```

`raw_analyze` ispisuje svaki par impulsa i trajanja, označava gdje je protokol dekodiran te završava frekvencijom, faktorom ispune,
prosjecima i otkrivenim protokolom (ili `not found`).

## Aplikacija LF-RFID Debug

Izvorni kôd firmvera sadrži i razvojni alat **LF-RFID Debug** (`applications/debug/lfrfid_debug`), čiji
zaslon **Tune** uživo podešava tajmer nositelja (ARR/CCR — frekvenciju i faktor ispune). To je alat za razvoj protokola
i nije potreban za uobičajenu upotrebu.

## Povezano

- [Formati datoteka](/hr/rfid/file-format) · [Čitanje](/hr/rfid/read) · [Protokoli](/hr/rfid/protocols)
