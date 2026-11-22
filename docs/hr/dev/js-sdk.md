---
title: "JavaScript: SDK i TypeScript"
sidebarTitle: "JS: SDK"
order: 220
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_developing_apps_using_js_sdk.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/packages]
sources: [unleashed-docs, unleashed-src]
---
# Razvoj aplikacija pomoću JavaScript SDK-a

Kopiranje skripte na uređaj putem qFlippera nakon svake izmjene brzo postane naporno. **Flipper Zero JavaScript SDK** skup je alata koji uklanja te korake:

- **jedna naredba** (`npm start`) prevodi aplikaciju, prenosi je na uređaj i pokreće;
- **dovršavanje koda** i provjera tipova (pišete u TypeScriptu);
- opcijski **JS minifikator**.

::: tip Unleashed
Unleashed ima vlastiti fork SDK-a: **`@darkflippers/fz-sdk-ul`**, koji se stvara pomoću **`@darkflippers/create-fz-app-ul`**. On dodaje definicije tipova za [module specifične za Unleashed](/hr/dev/js-about#unleashed-extras) (`subghz`, `infrared`, `blebeacon`, `usbdisk`, `i2c`, `spi`, `vgm`) i dodatne GUI prikaze. Skripte napisane za službeni SDK (`@flipperdevices/fz-sdk`) također rade na firmveru Unleashed. Ako koristite Unleashed dodatke, zaštitite ih provjerom `doesSdkSupport([...])` kako bi aplikacija i dalje radila na drugim firmverima, ili pozovite `checkSdkFeatures([...])` na početku ako je značajka nužna.
:::

## Instalacija SDK-a

SDK se distribuira kao NPM paket, pa vam je potreban **Node.js** s upraviteljem paketa (npm, pnpm ili yarn). Ove upute koriste npm.

1. Instalirajte **Node.js + npm** sa [službene stranice za preuzimanje](https://nodejs.org/en/download/package-manager).
2. Otvorite terminal u mapi u kojoj želite držati svoj projekt.
3. Stvorite projekt iz predloška. Interaktivni čarobnjak zatražit će naziv projekta i upravitelja paketa:

```sh
# službeni SDK
npx @flipperdevices/create-fz-app@latest

# Unleashed SDK (preporučeno na firmveru Unleashed)
npx @darkflippers/create-fz-app-ul@latest
```

Mapa projekta sada sadrži predložak aplikacije, SDK paket, ovisnosti i konfiguracijske datoteke. Vaš kôd ide u `index.ts`.

## Pokretanje aplikacije {#run}

1. Povežite Flipper Zero s računalom putem USB-a.
2. Otvorite terminal u mapi projekta (`cd my-flip-app`).
3. Pokrenite:

```sh
npm start
```

SDK prevodi aplikaciju, kopira `.js` datoteku na Flipper Zero i pokreće je. Izlaz funkcije `print()` prikazuje se u terminalu.

![Izlaz naredbe npm start](/img/dev/js_sdk_npm_start.jpg)

## Ažuriranje aplikacije

Nakon izmjene koda ponovno pokrenite `npm start`. Dok je Flipper još povezan, stara `.js` datoteka na uređaju zamjenjuje se novom i pokreće se nova inačica.

## Konfiguracija: `fz-sdk.config.json5`

Konfiguracija predloška (Unleashed SDK) izgleda ovako:

```js
{
    build: {
        // Kamo spremiti prevedenu datoteku
        output: "dist/<app_name>.js",

        // Treba li smanjiti veličinu konačne datoteke nauštrb čitljivosti i
        // jasnoće poruka o pogreškama
        minify: false,

        // Postavite na `false` ako ste temeljito pročitali dokumentaciju i
        // sigurni ste da možete koristiti ručne provjere inačice u svoju korist
        enforceSdkVersion: true,
    },

    upload: {
        // Odakle preuzeti datoteku. Ako ne radite dodatnu obradu
        // nakon SDK-a, ovo treba odgovarati `build.output`
        input: "dist/<app_name>.js",

        // Kamo spremiti datoteku na uređaju
        output: "/ext/apps/Scripts/<app_name>.js",
    },
}
```

### Dovršavanje koda

Uređivači s podrškom za Language Server (na primjer [VS Code](https://code.visualstudio.com/)) predlažu funkcije modula i njihove parametre dok tipkate, pa rijetko morate naknadno pretraživati dokumentaciju.

![Dovršavanje koda u VS Codeu](/img/dev/js_sdk_code_completion.jpg)

### JS minifikator

Minifikator uklanja razmake, tabulatore i prijelome redaka te skraćuje nazive varijabli. Skripta postaje manja i može raditi nešto brže, ali poruke o pogreškama postaju znatno teže za čitanje. Zbog toga je **zadano isključen**. Da biste ga uključili, postavite `minify: true` u datoteci `fz-sdk.config.json5`.

## Razlike u odnosu na obični Flipper JS

Uz SDK pišete **TypeScript**: bolje dovršavanje koda i upozorenja o tipovima, ali kôd izgleda malo drukčije.

- **Uvoz modula**
  - obični JS: `let module = require("module");`
  - SDK: `import * as module from "@flipperdevices/fz-sdk/module";` (na Unleashed SDK-u: `"@darkflippers/fz-sdk-ul/module"`)
- **Više izvornih datoteka.** SDK još ne podržava međusobni uvoz više `.ts` datoteka. I dalje možete koristiti `load()`, ali bez provjere tipova.
- **Pretvorba tipova (casting).** Neke funkcije vraćaju generičke tipove. Na primjer, `eventLoop.subscribe()` poziva vašu povratnu funkciju s generičkim tipom `Item`. Pretvorite ga kada je potrebno:
  - u retku: `<string>item`
  - pomoću nove varijable: `let text = item as string;`

`npm start` transpilira vaš kôd u obični JavaScript (i minificira ga ako je to uključeno). Dobivena `.js` datoteka u mapi `dist/` jest ono što dijelite s drugim korisnicima.

## Povezano

- [Vaša prva JS aplikacija](/hr/dev/js-first-app)
- [Korištenje JS modula](/hr/dev/js-modules)
- [Ugrađene funkcije: kompatibilnost SDK-a](/hr/dev/js-builtin#sdk-compatibility)
