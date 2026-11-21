---
title: Manifest delle app (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# Manifest delle app (.fam)

Ogni componente del firmware — servizi, app utente, pagine di impostazioni — è sviluppato in modo indipendente ed è
descritto da un file di manifest chiamato `application.fam`. Questo dichiara le proprietà di base del componente e le
sue relazioni con il resto del sistema.

In fase di compilazione `fbt` raccoglie tutti i manifest, risolve le loro dipendenze e compila **soltanto** i
componenti a cui la configurazione di build corrente fa riferimento (vedi
[fbt → insiemi di app del firmware](/it/dev/fbt#firmware-app-sets)).

## Definizione di un'app

Un manifest è un frammento di codice Python che chiama `App()` con argomenti con nome. Solo **`appid`** e
**`apptype`** sono obbligatori; gli altri sono facoltativi e alcuni hanno senso solo per certi tipi di app.

### Tipi di app (`apptype`)

`apptype` è un valore di `FlipperAppType`:

| Valore | Tipo di componente |
|---|---|
| `SERVICE` | Servizio di sistema, creato all'avvio iniziale |
| `SYSTEM` | Non mostrato nei menu; avviato da altre app o dalla CLI |
| `APP` | App normale nel menu principale |
| `PLUGIN` | Compilato come parte del firmware e inserito nel menu Plugins |
| `DEBUG` | Visibile solo nel menu Debug, con la modalità debug attiva |
| `ARCHIVE` | L'unica app Archive |
| `SETTINGS` | Inserito nel menu Settings di sistema |
| `STARTUP` | Callback eseguita all'avvio del sistema; non definisce un'app a sé |
| `EXTERNAL` | Compilato come app `.fap` |
| `METAPACKAGE` | Senza codice; serve a dichiarare dipendenze e insiemi di app |

### Parametri comuni

| Parametro | Significato |
|---|---|
| `appid` | ID testuale dell'app all'interno del sistema di build. Usato nelle configurazioni di build e per risolvere dipendenze e conflitti |
| `apptype` | Vedi la tabella sopra |
| `name` | Nome mostrato nei menu |
| `entry_point` | Funzione C usata come punto di ingresso. I nomi C++ vengono alterati dal mangling — racchiudi la funzione in `extern "C"` |
| `flags` | Flag interni per le app di sistema. **Da non usare** |
| `cdefines` | Definizioni del preprocessore C dichiarate globalmente per le altre app quando questa app è nella build. Per le app esterne — usate nella compilazione dell'app stessa |
| `requires` | ID di app da aggiungere alla build ogni volta che questa app viene compilata |
| `conflicts` | ID di app con cui questa app è in conflitto; se uno di essi è presente, `fbt` interrompe la compilazione |
| `provides` | Funzionalmente identico a `requires` |
| `stack_size` | Dimensione dello stack in byte allocata all'avvio dell'app. Troppo piccola → crash per stack overflow; troppo grande → meno heap per l'app |
| `icon` | Icona animata presa dagli asset integrati, usata quando l'app è compilata nel firmware |
| `order` | Ordine di ordinamento all'interno del proprio gruppo (più basso = prima). Usato per gli hook di avvio e le voci di menu |
| `sdk_headers` | Intestazioni C di questa app da includere nell'API per le app esterne |
| `targets` | [Target hardware](/it/dev/hardware-targets) compatibili. Predefinito `["all"]` |
| `resources` | Cartella all'interno dei sorgenti dell'app, impacchettata come risorse per la scheda SD (solo se l'app è nella build). Predefinito `""` — nessuna |

::: tip
Usa i comandi [CLI](/it/dev/cli) `top` e `free` per profilare l'uso di memoria della tua app quando scegli
`stack_size`.
:::

### Parametri per le app esterne (FAP)

| Parametro | Significato |
|---|---|
| `sources` | Maschere di file per raccogliere i sorgenti nella cartella dell'app. Predefinito `["*.c*"]` (C e C++). La cartella `lib` è riservata a `fap_private_libs`. Le maschere che iniziano con `!` escludono file; le maschere senza caratteri jolly (`*`, `?`) sono percorsi letterali. Esempio: `["*.c*", "!plugins"]` |
| `fap_version` | Stringa di versione dell'app, predefinita `"0.1"`. Funziona anche una tupla `(x, y)`. Sono ammesse parti aggiuntive separate da punti, ma nel `.fap` vengono memorizzate solo major e minor |
| `fap_icon` | File `.png`, colore a 1 bit, 10×10 px, incorporato nel `.fap` |
| `fap_libs` | Librerie aggiuntive con cui collegarsi — danno accesso a funzioni non esportate dal firmware, al prezzo di un `.fap` più grande e di più RAM |
| `fap_category` | Sottocategoria dell'app; determina anche la cartella sotto `apps/` sulla scheda SD |
| `fap_description` | Breve descrizione (può essere vuota) |
| `fap_author` | Autore (può essere vuoto) |
| `fap_weburl` | Pagina del progetto (può essere vuota) |
| `fap_icon_assets` | Cartella con gli asset grafici da preelaborare e compilare insieme all'app |
| `fap_extbuild` | Parti dei sorgenti compilate da strumenti esterni: un elenco di `ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Booleano, predefinito `False`. Solo per il tipo `PLUGIN`: incorpora il plugin nel `.fap` dell'app ospitante come risorsa; viene estratto in `apps_assets/APPID` all'avvio |
| `fap_private_libs` | Librerie distribuite come sorgenti insieme all'app — vedi sotto |

#### Comandi di build esterni (`fap_extbuild`)

I comandi vengono eseguiti dalla radice del firmware. I file intermedi devono finire nella cartella temporanea di
build dell'app. `fbt` espande queste variabili (e altre interne):

- `${FAP_WORK_DIR}` — la cartella temporanea di build dell'app
- `${FAP_SRC_DIR}` — la cartella dei sorgenti dell'app

Esempio — compilare un'app da sorgenti Rust:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Librerie private (`fap_private_libs`)

I sorgenti delle librerie vanno in una sottocartella di `lib/` all'interno della cartella dell'app. Ogni libreria è
una chiamata a `Lib()`:

| Parametro di `Lib()` | Significato | Predefinito |
|---|---|---|
| `name` | Nome della cartella della libreria (**obbligatorio**) | — |
| `fap_include_paths` | Percorsi (relativi alla libreria) aggiunti al percorso di include dell'app | `["."]` |
| `sources` | Maschere di file per i sorgenti della libreria, relative alla sua radice | `["*.c*"]` |
| `cflags` | Flag aggiuntivi per il compilatore | `[]` |
| `cdefines` | Definizioni aggiuntive del preprocessore | `[]` |
| `cincludes` | Percorsi di include aggiuntivi, relativi alla radice dell'**app** (per esempio per intestazioni di configurazione) | `[]` |

Esempio:

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

Che cosa ne fa `fbt`:

- **mbedtls** — compilata da `lib/mbedtls`; `lib/mbedtls/include` viene aggiunta al percorso di include dell'app;
  vengono compilati solo i tre file elencati; `MBEDTLS_ERROR_C` è definito per i suoi sorgenti.
- **loclass** — compilata da tutti i sorgenti in `lib/loclass`; `lib/loclass` viene aggiunta al percorso di include;
  gli avvisi **non** sono trattati come errori (`-Wno-error`), cosa comoda per codice di terze parti di grandi
  dimensioni.

Entrambe le librerie vengono collegate all'app.

## Un file `.fam` completo

Un unico file può definire più app. Ecco una parte di `applications/services/bt/application.fam`:

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

Un manifest per una tua app esterna, come generato da `ufbt create APPID=test_app` (da
`scripts/ufbt/project_template/app_template/application.fam`):

```python
# For details & more options, see documentation/AppManifests.md in firmware repo

App(
    appid="test_app",  # Must be unique
    name="App test_app",  # Displayed in menus
    apptype=FlipperAppType.EXTERNAL,
    entry_point="test_app_app",
    stack_size=2 * 1024,
    fap_category="Examples",
    # Optional values
    # fap_version="0.1",
    fap_icon="test_app.png",  # 10x10 1-bit PNG
    # fap_description="A simple app",
    # fap_author="J. Doe",
    # fap_weburl="https://github.com/user/test_app",
    fap_icon_assets="images",  # Image assets to compile for this application
)
```

Per altri esempi guarda i file `.fam` sparsi nel firmware — per esempio `applications/system/*/application.fam` per
le app aggiuntive di Unleashed.

## Pagine correlate

- [La tua prima app in C](/it/dev/first-app-c)
- [Flipper Build Tool (fbt)](/it/dev/fbt)
- [Target hardware](/it/dev/hardware-targets)
