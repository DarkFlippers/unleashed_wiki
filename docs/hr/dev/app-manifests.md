---
title: Manifesti aplikacija (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# Manifesti aplikacija (.fam)

Svaka komponenta firmvera — servisi, korisničke aplikacije, stranice postavki — razvija se neovisno i opisuje se
datotekom manifesta pod nazivom `application.fam`. Ona deklarira osnovna svojstva komponente i njezin odnos prema ostatku
sustava.

Prilikom prevođenja (builda) `fbt` prikuplja sve manifeste, rješava njihove ovisnosti i prevodi **samo** komponente koje
referencira trenutačna konfiguracija builda (vidi [fbt → skupovi aplikacija firmvera](/hr/dev/fbt#firmware-app-sets)).

## Definicija aplikacije

Manifest je isječak Python koda koji poziva `App()` s imenovanim argumentima. Obvezni su samo **`appid`** i **`apptype`**;
ostali su neobvezni, a neki imaju smisla samo za određene vrste aplikacija.

### Vrste aplikacija (`apptype`)

`apptype` je član nabrajanja `FlipperAppType`:

| Vrijednost | Vrsta komponente |
|---|---|
| `SERVICE` | Sistemski servis, stvara se pri ranom pokretanju sustava |
| `SYSTEM` | Ne prikazuje se u izbornicima; pokreću je druge aplikacije ili CLI |
| `APP` | Uobičajena aplikacija u glavnom izborniku |
| `PLUGIN` | Ugrađena u firmver i smještena u izbornik dodataka (Plugins) |
| `DEBUG` | Vidljiva samo u izborniku Debug, kada je uključen način otklanjanja pogrešaka |
| `ARCHIVE` | Jedna jedina aplikacija Archive |
| `SETTINGS` | Smještena u sustavni izbornik Settings |
| `STARTUP` | Povratni poziv (callback) koji se izvršava pri pokretanju sustava; ne definira zasebnu aplikaciju |
| `EXTERNAL` | Prevodi se kao vanjska `.fap` aplikacija |
| `METAPACKAGE` | Bez koda; služi za deklariranje ovisnosti i paketa aplikacija |

### Zajednički parametri

| Parametar | Značenje |
|---|---|
| `appid` | Tekstualni ID aplikacije unutar sustava prevođenja. Koristi se u konfiguracijama builda te za rješavanje ovisnosti i sukoba |
| `apptype` | Vidi tablicu iznad |
| `name` | Naziv koji se prikazuje u izbornicima |
| `entry_point` | C funkcija koja služi kao ulazna točka. C++ imena su izmijenjena (mangled) — omotajte funkciju u `extern "C"` |
| `flags` | Interne zastavice za sistemske aplikacije. **Ne koristiti** |
| `cdefines` | Globalne definicije C pretprocesora za druge aplikacije kada je ova aplikacija uključena u build. Za vanjske aplikacije — koristi se pri prevođenju same aplikacije |
| `requires` | ID-ovi aplikacija koje se dodaju u build kad god se prevodi ova aplikacija |
| `conflicts` | ID-ovi aplikacija s kojima se ova aplikacija sukobljava; ako je bilo koja prisutna, `fbt` prekida build |
| `provides` | Funkcionalno identično parametru `requires` |
| `stack_size` | Veličina stoga u bajtovima dodijeljena pri pokretanju aplikacije. Premala → rušenje zbog preljeva stoga; prevelika → manje hrpe (heap) za aplikaciju |
| `icon` | Animirana ikona iz ugrađenih resursa, koristi se kada je aplikacija ugrađena u firmver |
| `order` | Redoslijed sortiranja unutar grupe (manji broj = ranije). Koristi se za startup pozive i stavke izbornika |
| `sdk_headers` | C zaglavlja ove aplikacije koja se uključuju u API za vanjske aplikacije |
| `targets` | Kompatibilni [hardverski ciljevi](/hr/dev/hardware-targets). Zadano `["all"]` |
| `resources` | Mapa unutar izvornog koda aplikacije koja se pakira kao resursi na SD kartici (samo ako je aplikacija u buildu). Zadano `""` — ništa |

::: tip
Koristite [CLI naredbe](/hr/dev/cli) `top` i `free` za profiliranje potrošnje memorije vaše aplikacije pri odabiru vrijednosti `stack_size`.
:::

### Parametri za vanjske aplikacije (FAP)

| Parametar | Značenje |
|---|---|
| `sources` | Maske datoteka za prikupljanje izvornog koda u mapi aplikacije. Zadano `["*.c*"]` (C i C++). Mapa `lib` rezervirana je za `fap_private_libs`. Maske koje počinju s `!` isključuju datoteke; maske bez zamjenskih znakova (`*`, `?`) su doslovne putanje. Primjer: `["*.c*", "!plugins"]` |
| `fap_version` | Verzija aplikacije kao niz znakova, zadano `"0.1"`. Radi i tuple `(x, y)`. Dopušteni su dodatni dijelovi odvojeni točkom, ali se u `.fap` spremaju samo major i minor |
| `fap_icon` | `.png` datoteka, 1-bitna boja, 10×10 px, ugrađena u `.fap` |
| `fap_libs` | Dodatne biblioteke za povezivanje — daje pristup funkcijama koje firmver ne izvozi, uz cijenu većeg `.fap` paketa i veće potrošnje RAM-a |
| `fap_category` | Potkategorija aplikacije; ujedno određuje mapu unutar `apps/` na SD kartici |
| `fap_description` | Kratak opis (može biti prazan) |
| `fap_author` | Autor (može biti prazan) |
| `fap_weburl` | Početna web-stranica (može biti prazna) |
| `fap_icon_assets` | Mapa sa slikovnim resursima za predobradu i prevođenje zajedno s aplikacijom |
| `fap_extbuild` | Dijelovi izvora koje grade vanjski alati: popis `ExtFile(path="naziv datoteke", command="naredba ljuske")` |
| `fal_embedded` | Booleova vrijednost, zadano `False`. Samo za vrstu `PLUGIN`: ugrađuje dodatak u `.fap` glavne aplikacije kao resurs; raspakirava se u `apps_assets/APPID` pri pokretanju |
| `fap_private_libs` | Biblioteke isporučene kao izvorni kod uz aplikaciju — vidi dolje |

#### Vanjske naredbe prevođenja (`fap_extbuild`)

Naredbe se izvršavaju iz korijenske mape firmvera. Međudatoteke moraju ići u privremenu mapu builda aplikacije. `fbt`
proširuje ove varijable (i druge interne):

- `${FAP_WORK_DIR}` — privremena mapa builda aplikacije
- `${FAP_SRC_DIR}` — mapa izvornog koda aplikacije

Primjer — izgradnja aplikacije iz Rust izvornog koda:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Privatne biblioteke (`fap_private_libs`)

Izvorni kod biblioteka ide u podmapu unutar `lib/` u mapi aplikacije. Svaka biblioteka je poziv `Lib()`:

| Parametar `Lib()` | Značenje | Zadano |
|---|---|---|
| `name` | Naziv mape biblioteke (**obvezno**) | — |
| `fap_include_paths` | Putanje (relativne u odnosu na biblioteku) dodane u include putanju aplikacije | `["."]` |
| `sources` | Maske datoteka za izvorni kod biblioteke, relativne u odnosu na njezin korijen | `["*.c*"]` |
| `cflags` | Dodatne zastavice prevoditelja | `[]` |
| `cdefines` | Dodatne definicije pretprocesora | `[]` |
| `cincludes` | Dodatne include putanje, relativne u odnosu na korijen **aplikacije** (npr. za konfiguracijska zaglavlja) | `[]` |

Primjer:

```python
    fap_private_libs=[
            Lib(
                name="mbedtls",
                fap_include_paths=["include"],
                sources=[
                    "library/des.c",
                    "library/sha1.c",
                    "library/platform_util.c",
                ],
                cdefines=["MBEDTLS_ERROR_C"],
            ),
            Lib(
                name="loclass",
                cflags=["-Wno-error"],
            ),
        ],
```

Što `fbt` radi s tim:

- **mbedtls** — prevodi se iz `lib/mbedtls`; `lib/mbedtls/include` dodaje se u include putanju aplikacije; prevode se samo
  tri navedene datoteke; `MBEDTLS_ERROR_C` definiran je za njezin izvorni kod.
- **loclass** — prevodi se iz svog izvornog koda u `lib/loclass`; `lib/loclass` dodaje se u include putanju; upozorenja se
  **ne** tretiraju kao pogreške (`-Wno-error`), što je praktično za veliki kod trećih strana.

Obje se biblioteke povezuju u aplikaciju.

## Potpuna `.fam` datoteka

Jedna datoteka može definirati više aplikacija. Evo dijela datoteke `applications/services/bt/application.fam`:

```python
App(
    appid="bt_start",
    apptype=FlipperAppType.STARTUP,
    entry_point="bt_on_system_start",
    order=70,
)

App(
    appid="bt_settings",
    name="Bluetooth",
    apptype=FlipperAppType.SETTINGS,
    entry_point="bt_settings_app",
    stack_size=1 * 1024,
    requires=[
        "bt",
        "gui",
    ],
    order=10,
)
```

Manifest za vašu vlastitu vanjsku aplikaciju, kako ga generira `ufbt create APPID=test_app` (iz
`scripts/ufbt/project_template/app_template/application.fam`):

```python
# Za pojedinosti i više opcija pogledajte documentation/AppManifests.md u repozitoriju firmvera

App(
    appid="test_app",  # Mora biti jedinstveno
    name="App test_app",  # Prikazuje se u izbornicima
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Neobvezne vrijednosti
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bitni PNG
    # fap_description="Jednostavna aplikacija",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Slikovni resursi za prevođenje za ovu aplikaciju
)
```

Za više primjera pogledajte `.fam` datoteke diljem firmvera — npr. `applications/system/*/application.fam`
za dodatne Unleashed aplikacije.

## Povezane stranice

- [Vaša prva aplikacija u jeziku C](/hr/dev/first-app-c)
- [Flipper Build Tool (fbt)](/hr/dev/fbt)
- [Hardverski ciljevi](/hr/dev/hardware-targets)
