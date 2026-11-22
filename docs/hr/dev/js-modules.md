---
title: "JavaScript: korištenje modula"
sidebarTitle: "JS: korištenje modula"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# Korištenje JavaScript modula

[Ugrađene funkcije](/hr/dev/js-builtin) namjerno su malobrojne. Hardverske i sustavne značajke nalaze se u **JS modulima**, primjerice:

- `serial` šalje i prima podatke putem UART-a;
- `badusb` emulira USB tipkovnicu;
- `math` pruža matematičke funkcije.

Moduli su napisani u jeziku C, pa su brzi. Isporučuju se s firmverom i pohranjeni su na SD kartici u prevedenom obliku kao **FAL (Flipper Application File)** dodaci. Izvorni kôd modula: [`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules). Popis modula nalazi se na stranici [Pregled JavaScripta](/hr/dev/js-about).

## Učitavanje modula

Modul **morate** učitati pomoću `require()` prije pozivanja njegovih metoda. Time se modul učitava u RAM.

- Učitajte samo ono što koristite kako biste uštedjeli RAM. (`math`, primjerice, zauzima oko 21 KB RAM-a nakon učitavanja.)
- Svi učitani moduli automatski se uklanjaju iz memorije kada skripta završi.
- Modul se može učitati samo jednom po skripti; drugi `require()` istog naziva ne uspijeva uz pogrešku `"... module is already installed"`.
- Neki moduli ovise o drugima i moraju se učitati nakon njih: `gpio` i `gui` trebaju `event_loop`, a svaki `gui/*` prikaz treba `gui`.

Proslijedite naziv modula u navodnicima:

```js
let notify = require("notification");
```

Zatim pozivajte njegove metode putem varijable:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Firmver prihvaća i naziv u SDK stilu `require("@flipperdevices/fz-sdk/notification")`: prefiks se automatski uklanja. Nazivi s kosom crtom, poput `gui/submenu`, preslikavaju se na datoteku dodatka `js_gui__submenu`.

## Što je sljedeće

- Pregledajte stranice modula u ovom odjeljku, počevši od [Petlja događaja (Event loop)](/hr/dev/js-event-loop) i [GUI](/hr/dev/js-gui).
- Proučite primjere skripti u `/ext/apps/Scripts/js_examples/`.
