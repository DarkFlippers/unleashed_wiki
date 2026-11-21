---
title: Entwicklung
original: [https://docs.flipper.net/zero/development, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/documentation]
sources: [flipper-docs, unleashed-readme, unleashed-docs]
---
# Entwicklung

Dieser Abschnitt richtet sich an alle, die mehr wollen, als den Flipper nur zu benutzen: die Unleashed Firmware aus
dem Quellcode bauen, eigene Apps in C oder JavaScript schreiben, sie auf echter Hardware debuggen, über die
Kommandozeile mit dem Gerät sprechen oder verstehen, wie Updates und die Hardware intern funktionieren.

::: tip Unleashed
Unleashed ist ein Fork der offiziellen Firmware, der **vollständig kompatibel zur offiziellen API und zu den
offiziellen Apps** bleibt. Nahezu alles aus der offiziellen Entwicklerdokumentation gilt unverändert. Die
wichtigsten Punkte, die du dir merken solltest:

- klone `https://github.com/DarkFlippers/unleashed-firmware` statt des offiziellen Repositorys;
- wenn du Apps mit **uFBT** baust, richte es auf das Unleashed-SDK aus
  (`--index-url=https://up.unleashedflip.com/directory.json`), sonst wird deine App gegen das offizielle SDK gebaut
  und lädt möglicherweise nicht ([Details](/de/dev/build#build-apps-against-the-unleashed-sdk-with-ufbt));
- die Firmware-Herkunft wird als `Unleashed` gemeldet, die aktuelle API-Version auf `dev` ist **88.27**.
:::

## Die Firmware bauen

| Seite | Was du bekommst |
|---|---|
| [Die Firmware bauen](/de/dev/build) | Unleashed unter Linux, macOS und Windows klonen, bauen und flashen |
| [Flipper Build Tool (fbt)](/de/dev/fbt) | Jedes `fbt`-Target, jede Option und jede Umgebungsvariable |
| [Hardware-Targets](/de/dev/hardware-targets) | Wie `targets/` und `target.json` Hardwarevarianten beschreiben (f7, f18) |
| [Apps unter Android bauen](/de/dev/android-build) | `.fap`-Apps auf dem Smartphone mit Termux + uFBT kompilieren, ohne PC |

## Apps schreiben

| Seite | Was du bekommst |
|---|---|
| [Deine erste App in C](/de/dev/first-app-c) | uFBT, App-Vorlage, "Hello world" mit einem Dialog, bauen und ausführen |
| [App-Manifeste (.fam)](/de/dev/app-manifests) | Alle Felder von `application.fam`, Optionen für externe Apps, private Bibliotheken |
| [Furi-API](/de/dev/furi-api) | Hardware- und Softwarearchitektur, Furi-Kern, `furi_assert` / `furi_check` |
| [GUI in Apps](/de/dev/gui) | Dialoge, ViewPort, Views & Scenes, View-Module |
| [Apps debuggen](/de/dev/debugging) | SWD-Probes, Debugging in VS Code, Debug-Signale des Furi HAL |
| [FuriHalBus-API](/de/dev/furi-hal-bus) | MCU-Peripherie korrekt ein- und ausschalten, DMA-Kanalbelegung |
| [JavaScript auf dem Flipper](/de/dev/js-about) | Skripte in JavaScript statt in C schreiben (eigene Seitengruppe) |
| JS-Module nur in Unleashed | [subghz](/de/dev/js-subghz), [infrared](/de/dev/js-infrared), [blebeacon](/de/dev/js-blebeacon), [usbdisk](/de/dev/js-usbdisk), [i2c](/de/dev/js-i2c), [spi](/de/dev/js-spi), [vgm](/de/dev/js-vgm) — nicht in der Stock-Firmware, nicht in der offiziellen Dokumentation |

## Mit dem Gerät arbeiten

| Seite | Was du bekommst |
|---|---|
| [Kommandozeile (CLI)](/de/dev/cli) | Über USB-Serial verbinden; jeder CLI-Befehl mit seinen Argumenten |
| [OTA-Updates](/de/dev/ota) | Wie der Updater arbeitet, Manifestfelder, `[XX-YY]`-Fehlercodes, Pakete bauen |
| [Heatshrink-Tarball-Format](/de/dev/tar-heatshrink) | Der `.tar.hs`-Container für Ressourcen in Update-Paketen |
| [Hardware](/de/dev/hardware) | Technische Daten, Schaltpläne, 3D-Modelle, Zeichnungen von Modulen und Devboards |

## Testen

| Seite | Was du bekommst |
|---|---|
| [Unit-Tests](/de/dev/unit-tests) | Die App `unit_tests` auf dem Gerät bauen und ausführen, eigene Tests ergänzen |
| [Integrationstests](/de/dev/testing) | Der manuelle Testplan, der vor dem Mergen von PRs und vor Releases durchlaufen wird |

## Weitere nützliche Ressourcen

- Offizielle Entwicklerdokumentation (Doxygen): [developer.flipper.net](https://developer.flipper.net/flipperzero/doxygen/) — hier schlägst du Firmware-APIs nach, die dieses Wiki nicht abdeckt, mit Abschnitten zu Systemprogrammierung, App-Entwicklung, JavaScript, Erweiterungsmodulen und Dateiformaten
- Einrichtung eines CLion-Workspace — [Anleitung von Savely Krasovsky](https://krasovs.ky/2022/11/01/flipper-zero-clion.html)
- "Hello world!"-Plugin-Tutorials: [Englisch (DroomOne)](https://github.com/DroomOne/Flipper-Plugin-Tutorial),
  [Russisch (Pavel Yakovlev)](https://yakovlev.me/hello-flipper-zero)
- [Wie du deine eigene App schreibst](https://flipper.atmanos.com/docs/overview/intro)

### Projektstruktur des Firmware-Repositorys

| Ordner | Inhalt |
|---|---|
| `applications` | Anwendungen und Dienste, die in der Firmware verwendet werden |
| `assets` | Assets, die von Anwendungen und Diensten verwendet werden |
| `furi` | Furi Core: Primitive und Hilfsfunktionen auf Betriebssystemebene |
| `debug` | Debug-Werkzeuge: GDB-Plugins, SVD-Datei usw. |
| `documentation` | Dokumentationsquellen und Generator-Konfigurationen |
| `firmware` | Quellcode der Firmware |
| `lib` | Eigene und Drittanbieter-Bibliotheken, Treiber |
| `site_scons` | Build-Hilfsfunktionen |
| `scripts` | Ergänzende Skripte und Python-Bibliotheken |
| `targets` | Definitionen der Hardware-Targets (`f7`, `f18`) |

Viele dieser Ordner haben ihre eigene `ReadMe.md` — die Lektüre lohnt sich.
