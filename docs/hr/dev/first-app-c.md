---
title: Vaša prva aplikacija u jeziku C
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/app_dev/app_dev_your_first_app_in_c.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/BuildingFapsOnAndroid.md]
sources: [unleashed-docs]
---
# Vaša prva aplikacija u jeziku C

U ovim uputama postavit ćete razvojno okruženje pomoću alata **uFBT**, generirati predložak aplikacije, dodati jednostavan GUI
te izgraditi i pokrenuti aplikaciju na svom Flipper Zeru.

Aplikacije izgrađene na ovaj način su `.fap` datoteke (Flipper App Package) — nalaze se na microSD kartici i učitavaju se po potrebi,
tako da ne morate ponovno graditi cijeli firmver.

## 1. Postavljanje okruženja

Potrebni su vam Flipper Zero, USB kabel te na sustavima Windows / macOS / Linux:

- [**uFBT**](https://github.com/flipperdevices/flipperzero-ufbt) ("micro Flipper Build Tool") — inačica alata
  [fbt](/hr/dev/fbt) sa svime što je potrebno za razvoj aplikacija. Instalirajte ga naredbom `pip install ufbt` (detalje
  potražite u uFBT README-u).
- [**Visual Studio Code**](https://code.visualstudio.com/) — preporučeno razvojno okruženje (IDE). Rade i drugi uređivači,
  ali zahtijevaju ručnu konfiguraciju za integraciju s uFBT-om.

::: tip Unleashed
uFBT po zadanim postavkama preuzima **službeni** SDK. Da biste gradili za Unleashed, pokrenite jednom (i koristite iste
zastavice pri svakom budućem ažuriranju):

```sh
ufbt update --index-url=https://up.unleashedflip.com/directory.json --channel=dev
```

Koristite `--channel=release` ako vaš Flipper pokreće release izdanje. Verzija SDK-a mora odgovarati firmveru na
uređaju — pogledajte [korak 5](#_5-build-and-run-the-app).
:::

## 2. Generiranje predloška aplikacije

1. Stvorite mapu za aplikaciju, npr. `test_app`.
2. Otvorite terminal u toj mapi i pokrenite:

   ```sh
   ufbt create APPID=test_app
   ```

   uFBT generira strukturu datoteka.
3. Pokrenite:

   ```sh
   ufbt vscode_dist
   ```

   Time se VS Code konfigurira za izgradnju i otklanjanje pogrešaka izravno iz IDE-a.

::: warning
`APPID` smije sadržavati samo mala slova `a-z`, znamenke `0-9` i `_`.
:::

Dobivena struktura:

```
test_app/
├── application.fam
├── test_app.c
├── test_app.png
├── .github/
│   └── workflows/
|       └── build.yml
└── images/
    └── .gitkeep
```

| Datoteka | Namjena |
|---|---|
| `application.fam` | Manifest aplikacije koji uFBT čita kako bi znao kako je izgraditi — pogledajte [Manifesti aplikacija](/hr/dev/app-manifests) |
| `test_app.c` | Glavna izvorna datoteka s ulaznom točkom |
| `test_app.png` | Ikona aplikacije (10×10, 1-bit) |
| `.github/workflows/build.yml` | Konfiguracija za GitHub Actions — [više](https://github.com/marketplace/actions/build-flipper-application-package-fap) |
| `images/` | Vaše slikovne datoteke |
| `images/.gitkeep` | Rezervirana datoteka kako bi Git pratio praznu mapu `images/` |

## 3. Kôd predloška

```c
#include <furi.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    FURI_LOG_I("TEST", "Hello world");
    FURI_LOG_I("TEST", "I'm test_app!");

    return 0;
}
```

Što svaki dio radi:

- `#include <furi.h>` — glavno zaglavlje za **Furi**, jezgru Flipper firmvera ([Furi API](/hr/dev/furi-api)).
- `#include <test_app_icons.h>` — potrebno ako aplikacija koristi slike. uFBT pretvara PNG datoteke iz `images/` u
  interni format Flippera i automatski generira ovo zaglavlje.
- `int32_t` — uobičajeni povratni tip glavne funkcije aplikacije.
- `UNUSED(p);` — makro koji utišava upozorenje o neiskorištenom parametru.
- `FURI_LOG_I` — zapisuje poruku razine `info` u zapisnik (log) Flippera. Pratite ga putem `ufbt cli` → `log info`.
- `return 0;` — uspjeh, prema C konvenciji.

## 4. Dodavanje GUI-ja

Otvorite mapu aplikacije u VS Codeu (**File → Open Folder…**). Instalirajte predložene ekstenzije kada se to zatraži.

Prikažimo dva retka na zaslonu: `Hello world` i `I'm test_app!`. Zamijenite sadržaj datoteke `test_app.c` sljedećim:

```c
#include <furi.h>
#include <dialogs/dialogs.h>
#include <test_app_icons.h>

int32_t test_app_app(void* p) {
    UNUSED(p);
    DialogsApp* dialogs = furi_record_open(RECORD_DIALOGS);
    DialogMessage* message = dialog_message_alloc();
    dialog_message_set_header(message, "Hello world", 64, 20, AlignCenter, AlignTop);
    dialog_message_set_text(message, "I'm test_app!", 64, 32, AlignCenter, AlignTop);
    dialog_message_show(dialogs, message);
    dialog_message_free(message);
    furi_record_close(RECORD_DIALOGS);

    return 0;
}
```

Ovo koristi GUI servis **Dialogs**, najjednostavniji GUI API. Ostali pristupi opisani su na stranici
[GUI u aplikacijama](/hr/dev/gui).

## 5. Izgradnja i pokretanje aplikacije {#_5-build-and-run-the-app}

**Brzi način:**

1. Povežite Flipper s računalom putem USB kabela.
2. Zatvorite qFlipper i svaki drugi program koji koristi serijski priključak Flippera.
3. Pokrenite:

   ```sh
   ufbt launch
   ```

   Time se aplikacija gradi, prenosi i pokreće na Flipperu.

**Ručni način:**

1. Izgradite prečacem <kbd>Ctrl</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd> (Windows/Linux) ili <kbd>Cmd</kbd>+<kbd>Shift</kbd>+<kbd>B</kbd>
   (macOS), ili pokrenite `ufbt` u terminalu. Samostalna `.fap` datoteka (sa svim resursima) pojavljuje se u `dist/`.
2. U qFlipperu otvorite **File Manager → SD Card → apps → Examples** (stvorite mapu ako je potrebno) i povucite `.fap`
   datoteku tamo.
3. Na Flipperu: `Main Menu → Apps → Examples → vaša aplikacija`.

**Očekivani rezultat:** zaslon s naslovom "Hello world" i tekstom "I'm test_app!" ispod njega. Pritisnite bilo koju tipku
za zatvaranje.

::: warning Verzija SDK-a mora odgovarati
Verzija SDK-a (API-ja) firmvera na uređaju mora odgovarati SDK-u za koji je uFBT gradio. Ako dobijete pogrešku neusklađenosti
API-ja prilikom pokretanja aplikacije, ili ažurirajte uFBT SDK kako bi odgovarao vašem firmveru, ili instalirajte odgovarajući
firmver naredbom `ufbt flash_usb`. Na Unleashedu provjerite koristi li uFBT Unleashed indeks (pogledajte savjet u koraku 1) —
inače će `ufbt flash_usb` instalirati **službeni** firmver.
:::

Za pregled ispisa `FURI_LOG_I`: pokrenite `ufbt cli`, zatim `log` (ili `log info` ako ste promijenili zadanu razinu zapisnika).

## Rješavanje problema

| Problem | Rješenje |
|---|---|
| `ufbt create` odbija APPID | Koristite samo `a-z`, `0-9`, `_` |
| Neusklađenost API-ja / SDK-a pri pokretanju | Ažurirajte uFBT SDK za svoj firmver (Unleashed indeks!) i ponovno izgradite |
| `ufbt launch` ne može pronaći uređaj | Zatvorite qFlipper / Lab / bilo koji serijski terminal; ponovno spojite kabel |
| Aplikacije nema u izborniku | Mora biti u mapi kategorije pod `/ext/apps/`, npr. `/ext/apps/Examples/` |
| Ništa u `log` zapisu | Pokrenite `log` **prije** pokretanja aplikacije; provjerite razinu zapisnika |

## Što dalje?

- Ako vam je znanje jezika C zahrđalo, *The C Programming Language* autora B. Kernighana i D. Ritchieja klasična je referenca.
- [Otklanjanje pogrešaka u aplikacijama](/hr/dev/debugging) — koračajte kroz svoju aplikaciju pomoću debuggera.
- [GUI u aplikacijama](/hr/dev/gui) — ViewPort, prikazi (Views) i scene.
- [Manifesti aplikacija](/hr/dev/app-manifests) — sve opcije datoteke `application.fam`.
- Nemate računalo? [Izgradnja aplikacija na Androidu](/hr/dev/android-build).
- Više volite skriptiranje? [JavaScript na Flipperu](/hr/dev/js-about).
