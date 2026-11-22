---
title: "JavaScript: subghz"
sidebarTitle: "JS: subghz"
order: 400
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules/js_subghz]
sources: [unleashed-src]
---
# Sub-GHz modul

Dodatak u firmveru Unleashed koji nije prisutan u izvornom firmveru. Skripti daje pristup Sub-GHz radiju: prebacivanje između prijema i mirovanja, čitanje razine signala, promjena frekvencije i odašiljanje spremljene `.sub` datoteke.

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");
subghz.setup();
```

`setup()` najprije traži vanjski modul CC1101, a ako ga nema, koristi ugrađeni radio. Dok se ne pokrene, svaka druga metoda baca iznimku `Radio is not setup`.

Primjer skripte: `/ext/apps/Scripts/js_examples/subghz.js`.

## Metode

### setup()
Inicijalizira radio i odabire uređaj. Kreće na 433920000 Hz u stanju `IDLE`. Baca iznimku ako je radio već postavljen.

### end()
Stavlja radio u stanje mirovanja (sleep) i oslobađa uređaj. To se događa automatski kada skripta završi. Pozivanje `setup()` nakon toga ponovno traži vanjski modul.

### setRx()
Prebacuje radio u način prijema.

### setIdle()
Prebacuje radio u stanje mirovanja (`IDLE`). Frekvencija se može mijenjati samo u tom stanju.

### getRssi()
Razina signala na trenutačnoj frekvenciji, u dBm.

- **Vraća:** `number`, ili `undefined` ako radio nije u načinu RX.

### getState()
- **Vraća:** `"RX"`, `"TX"` ili `"IDLE"`.

### getFrequency()
- **Vraća:** trenutačnu frekvenciju u Hz, kao broj.

### setFrequency()
Ugađa radio na zadanu frekvenciju. Baca iznimku ako radio nije u stanju `IDLE` ili ako je frekvencija izvan pojaseva koje uređaj podržava.

- **Parametri:** `frequency`, broj u Hz — na primjer `433920000`.
- **Vraća:** frekvenciju na koju se radio stvarno ugodio. CC1101 ne može pogoditi svaku vrijednost točno, pa odabire najbližu moguću.

### isExternal()
- **Vraća:** boolean — `true` kada se koristi vanjski CC1101, `false` za ugrađeni radio.

### transmitFile()
Šalje `.sub` datoteku. Frekvencija i modulacija preuzimaju se iz datoteke, a ne iz `setFrequency()`. Vraća `true`; pri bilo kakvoj pogrešci (datoteka nedostaje, neispravno zaglavlje, nepodržana frekvencija, nepoznat preset) baca iznimku. Radio ostaje u stanju `IDLE`.

- **Parametri:**
  - `path`: puna putanja do datoteke, npr. `"/ext/subghz/0.sub"`;
  - `repeat` (neobvezno): koliko puta poslati signal.

Bez parametra `repeat`, RAW datoteke šalju se jednom, a datoteke protokola 10 puta, što oponaša držanje tipke na pravom daljinskom upravljaču. `CAME Atomo`, `CAME TWEE`, `Hormann HSM`, `Nice FloR-S` i `Power Smart` već šalju nekoliko okvira signala po ponavljanju, pa im je zadana vrijednost 1.

## Primjer

Slušanje na 433,92 MHz, zatim slanje spremljenog ključa:

```js
checkSdkFeatures(["subghz"]);
let subghz = require("subghz");

subghz.setup();
subghz.setIdle();
subghz.setFrequency(433920000);

subghz.setRx();
print("RSSI:", subghz.getRssi(), "dBm, external:", subghz.isExternal());
delay(1000);

print("Sending 0.sub");
subghz.transmitFile("/ext/subghz/0.sub");
print("Sent");

subghz.end();
```

## Povezano

- [Format Sub-GHz datoteka](/hr/subghz/file-format) — što se nalazi u `.sub` datoteci
- [Vanjski CC1101 moduli](/hr/subghz/external-cc1101)
- [Pregled JavaScripta](/hr/dev/js-about)
