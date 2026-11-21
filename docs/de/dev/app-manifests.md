---
title: App-Manifeste (.fam)
order: 30
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppManifests.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/scripts/ufbt/project_template/app_template]
sources: [unleashed-docs, unleashed-src]
---
# App-Manifeste (.fam)

Jede Firmware-Komponente — Dienste, Benutzer-Apps, Einstellungsseiten — wird eigenständig entwickelt und durch eine
Manifestdatei namens `application.fam` beschrieben. Sie deklariert die grundlegenden Eigenschaften der Komponente
und wie sie zum Rest des Systems in Beziehung steht.

Beim Bauen sammelt `fbt` alle Manifeste ein, löst deren Abhängigkeiten auf und baut **nur** die Komponenten, auf
die die aktuelle Build-Konfiguration verweist (siehe [fbt → Firmware-App-Sets](/de/dev/fbt#firmware-app-sets)).

## App-Definition

Ein Manifest ist ein Python-Schnipsel, das `App()` mit Schlüsselwortargumenten aufruft. Nur **`appid`** und
**`apptype`** sind zwingend; der Rest ist optional, und manches ist nur für bestimmte App-Typen sinnvoll.

### App-Typen (`apptype`)

`apptype` ist ein Element von `FlipperAppType`:

| Wert | Komponententyp |
|---|---|
| `SERVICE` | Systemdienst, wird früh beim Start erzeugt |
| `SYSTEM` | Erscheint nicht in Menüs; wird von anderen Apps oder über die CLI gestartet |
| `APP` | Gewöhnliche App im Hauptmenü |
| `PLUGIN` | Als Teil der Firmware gebaut und im Plugins-Menü abgelegt |
| `DEBUG` | Nur im Debug-Menü sichtbar, bei aktiviertem Debug-Modus |
| `ARCHIVE` | Die einzige Archive-App |
| `SETTINGS` | Im System-Menü Settings abgelegt |
| `STARTUP` | Callback, der beim Systemstart ausgeführt wird; definiert keine eigene App |
| `EXTERNAL` | Als `.fap`-App gebaut |
| `METAPACKAGE` | Kein Code; dient dazu, Abhängigkeiten und App-Bündel zu deklarieren |

### Gemeinsame Parameter

| Parameter | Bedeutung |
|---|---|
| `appid` | String-ID der App innerhalb des Build-Systems. Wird in Build-Konfigurationen und zum Auflösen von Abhängigkeiten und Konflikten verwendet |
| `apptype` | Siehe die Tabelle oben |
| `name` | In Menüs angezeigter Name |
| `entry_point` | C-Funktion, die als Einstiegspunkt dient. C++-Namen werden gemangelt — umschließe die Funktion mit `extern "C"` |
| `flags` | Interne Flags für System-Apps. **Nicht verwenden** |
| `cdefines` | C-Präprozessor-Definitionen, die global für andere Apps gelten, wenn diese App im Build ist. Bei externen Apps — werden beim Bauen der App selbst verwendet |
| `requires` | App-IDs, die dem Build hinzugefügt werden, sobald diese App gebaut wird |
| `conflicts` | App-IDs, mit denen diese App in Konflikt steht; ist eine davon vorhanden, bricht `fbt` den Build ab |
| `provides` | Funktional identisch zu `requires` |
| `stack_size` | Stackgröße in Bytes, die beim Start der App belegt wird. Zu klein → Absturz durch Stacküberlauf; zu groß → weniger Heap für die App |
| `icon` | Animiertes Icon aus den eingebauten Assets, wird verwendet, wenn die App in die Firmware gebaut wird |
| `order` | Sortierreihenfolge innerhalb der Gruppe (niedriger = früher). Wird für Startup-Hooks und Menüeinträge verwendet |
| `sdk_headers` | C-Header dieser App, die in die API für externe Apps aufgenommen werden |
| `targets` | Kompatible [Hardware-Targets](/de/dev/hardware-targets). Standard `["all"]` |
| `resources` | Ordner innerhalb der App-Quellen, der als SD-Karten-Ressourcen verpackt wird (nur wenn die App im Build ist). Standard `""` — keiner |

::: tip
Nutze die [CLI-Befehle](/de/dev/cli) `top` und `free`, um den Speicherverbrauch deiner App zu untersuchen, wenn du
`stack_size` festlegst.
:::

### Parameter für externe Apps (FAPs)

| Parameter | Bedeutung |
|---|---|
| `sources` | Dateimasken zum Einsammeln der Quellen im App-Ordner. Standard `["*.c*"]` (C und C++). Der Ordner `lib` ist für `fap_private_libs` reserviert. Masken, die mit `!` beginnen, schließen Dateien aus; Masken ohne Platzhalter (`*`, `?`) sind wörtliche Pfade. Beispiel: `["*.c*", "!plugins"]` |
| `fap_version` | Versionszeichenkette der App, Standard `"0.1"`. Ein Tupel `(x, y)` funktioniert ebenfalls. Weitere punktgetrennte Teile sind erlaubt, aber nur Major und Minor werden in der `.fap` gespeichert |
| `fap_icon` | `.png`-Datei, 1-Bit-Farbe, 10×10 px, wird in die `.fap` eingebettet |
| `fap_libs` | Zusätzliche Bibliotheken zum Linken — gibt Zugriff auf Funktionen, die die Firmware nicht exportiert, auf Kosten einer größeren `.fap` und mehr RAM |
| `fap_category` | Unterkategorie der App; bestimmt außerdem den Ordner unter `apps/` auf der SD-Karte |
| `fap_description` | Kurzbeschreibung (darf leer sein) |
| `fap_author` | Autor (darf leer sein) |
| `fap_weburl` | Homepage (darf leer sein) |
| `fap_icon_assets` | Ordner mit Bild-Assets, die vorverarbeitet und zusammen mit der App gebaut werden |
| `fap_extbuild` | Teile der Quellen, die von externen Werkzeugen gebaut werden: eine Liste von `ExtFile(path="file name", command="shell command")` |
| `fal_embedded` | Boolean, Standard `False`. Nur für den Typ `PLUGIN`: bettet das Plugin als Ressource in die `.fap` der Host-App ein; es wird beim Start nach `apps_assets/APPID` entpackt |
| `fap_private_libs` | Bibliotheken, die als Quellcode mit der App ausgeliefert werden — siehe unten |

#### Externe Build-Befehle (`fap_extbuild`)

Die Befehle laufen vom Firmware-Wurzelverzeichnis aus. Zwischendateien müssen in den temporären Build-Ordner der
App wandern. `fbt` ersetzt diese Variablen (und weitere interne):

- `${FAP_WORK_DIR}` — der temporäre Build-Ordner der App
- `${FAP_SRC_DIR}` — der Quellordner der App

Beispiel — eine App aus Rust-Quellen bauen:

```python
    sources=["target/thumbv7em-none-eabihf/release/libhello_rust.a"],
    fap_extbuild=(
        ExtFile(
            path="${FAP_WORK_DIR}/target/thumbv7em-none-eabihf/release/libhello_rust.a",
            command="cargo build --release --verbose --target thumbv7em-none-eabihf --target-dir ${FAP_WORK_DIR}/target --manifest-path ${FAP_SRC_DIR}/Cargo.toml",
        ),
    ),
```

#### Private Bibliotheken (`fap_private_libs`)

Die Bibliotheksquellen kommen in einen Unterordner von `lib/` innerhalb des App-Ordners. Jede Bibliothek ist ein
`Lib()`-Aufruf:

| `Lib()`-Parameter | Bedeutung | Standard |
|---|---|---|
| `name` | Name des Bibliotheksordners (**erforderlich**) | — |
| `fap_include_paths` | Pfade (relativ zur Bibliothek), die dem Include-Pfad der App hinzugefügt werden | `["."]` |
| `sources` | Dateimasken für die Quellen der Bibliothek, relativ zu ihrer Wurzel | `["*.c*"]` |
| `cflags` | Zusätzliche Compiler-Flags | `[]` |
| `cdefines` | Zusätzliche Präprozessor-Definitionen | `[]` |
| `cincludes` | Zusätzliche Include-Pfade, relativ zur Wurzel der **App** (z. B. für Konfigurations-Header) | `[]` |

Beispiel:

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

Was `fbt` damit macht:

- **mbedtls** — wird aus `lib/mbedtls` gebaut; `lib/mbedtls/include` wird dem Include-Pfad der App hinzugefügt;
  nur die drei genannten Dateien werden kompiliert; `MBEDTLS_ERROR_C` wird für deren Quellen definiert.
- **loclass** — wird aus allen Quellen in `lib/loclass` gebaut; `lib/loclass` wird dem Include-Pfad hinzugefügt;
  Warnungen werden **nicht** als Fehler behandelt (`-Wno-error`), was bei großem Fremdcode praktisch ist.

Beide Bibliotheken werden in die App gelinkt.

## Eine vollständige `.fam`-Datei

Eine Datei kann mehrere Apps definieren. Hier ein Teil von `applications/services/bt/application.fam`:

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

Ein Manifest für deine eigene externe App, wie es `ufbt create APPID=test_app` erzeugt (aus
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

Weitere Beispiele findest du in den `.fam`-Dateien überall in der Firmware — z. B.
`applications/system/*/application.fam` für die zusätzlichen Unleashed-Apps.

## Verwandte Seiten

- [Deine erste App in C](/de/dev/first-app-c)
- [Flipper Build Tool (fbt)](/de/dev/fbt)
- [Hardware-Targets](/de/dev/hardware-targets)
