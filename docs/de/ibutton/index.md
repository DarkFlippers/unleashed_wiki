---
title: iButton
original: [https://docs.flipper.net/zero/ibutton, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton]
sources: [unleashed-src, flipper-docs, unleashed-readme]
---
# iButton

iButton („Touch Memory“, in der GUS oft *таблетка* genannt) ist ein Schlüssel in einem kleinen Stahlgehäuse, der
durch Antippen eines Lesegeräts ausgelesen wird. Die meisten sprechen Dallas **1-Wire**; Türsprechanlagen nutzen
außerdem **Cyfral**- und **Metakom**-Schlüssel. Flipper Zero kann solche Schlüssel lesen, speichern, emulieren und
schreiben.

## Hardware

Das iButton-Modul ist ein Kontaktfeld mit drei federgelagerten Pogo-Pins auf der iButton-Platine.

- Die beiden äußeren Pins sind Daten (verbunden mit **GPIO-Pin 17**), der mittlere Pin ist **Masse**.
- **Schlüssel lesen / schreiben**: Der Schlüssel berührt den **flachen Teil** des Kontaktfelds — linker Daten-Pin +
  mittlerer Masse-Pin.
- **Emulation gegenüber einem Lesegerät**: Der **hervorstehende Teil** des Kontaktfelds berührt das Lesegerät —
  rechter Daten-Pin + mittlere Masse.
- Erreicht die Masse den Rand des Lesegeräts nicht, nimm zwei Kabel: GPIO **17** (Daten) und GPIO **8, 11 oder 18**
  (Masse).

## Hauptmenü

`Main Menu → iButton`:

![Das iButton-Menü mit Read, Saved, Add Manually und Settings](/screens/ibutton/menu.png)

| Eintrag | Funktion | Seite |
|---|---|---|
| **Read** | Schlüsseltyp erkennen und ID lesen (bei DS1992/1996/1971 auch den Speicher) | [Lesen](/de/ibutton/read) |
| **Saved** | `/ext/ibutton/` durchsehen — emulieren, schreiben, bearbeiten, umbenennen, löschen | [Lesen](/de/ibutton/read), [Schreiben](/de/ibutton/write) |
| **Add Manually** | Schlüssel aus Protokoll + Hex-ID anlegen | [Manuell anlegen](/de/ibutton/add-manually) |
| **Settings** | **Write Blanks** — welche Rohling-Typen beim Schreiben verwendet werden dürfen | [Schreiben](/de/ibutton/write) |

::: tip Unleashed
Gegenüber der offiziellen Dokumentation hat Unleashed eine Seite **Settings → Write Blanks** (RW1990.1, RW1990.2,
TM2004, TM01x), zeigt beim Schreiben an, welcher Rohling gerade probiert wird und welcher den Schreibvorgang
angenommen hat, schreibt **Cyfral- und Metakom**-Schlüssel auf **TM01x**-Rohlinge und unterstützt **DS1420**. Die
ReadMe nennt außerdem ein iButton-Fuzzer-Plugin.
:::

## Seiten in diesem Abschnitt

- [Schlüssel lesen](/de/ibutton/read) — lesen, speichern, emulieren, CRC-Fehler.
- [Auf Rohlinge schreiben](/de/ibutton/write) — RW1990, TM2004, TM01x; Write ID gegenüber Full Write on Same Type.
- [Manuell anlegen](/de/ibutton/add-manually) — Schlüssel aus einer ID erzeugen.
- [Unterstützte Protokolle](/de/ibutton/protocols) — Dallas DS1990/1992/1996/1971/1420, generisches 1-Wire, Cyfral,
  Metakom.
- [Fuzzer](/de/ibutton/fuzzer) — was die Firmware für die iButton-Fuzzer-App mitbringt.
- [Dateiformat](/de/ibutton/file-format) — `.ibtn`-Dateien.

## Dateien

| Pfad | Inhalt |
|---|---|
| `/ext/ibutton/*.ibtn` | Gespeicherte Schlüssel (Standard-Namenspräfix `iBtn`) |
| `/ext/ibutton/.ibutton.settings` | Einstellung Write Blanks |

::: warning
Kopiere und emuliere nur Schlüssel, die dir gehören oder die du testen darfst.
:::
