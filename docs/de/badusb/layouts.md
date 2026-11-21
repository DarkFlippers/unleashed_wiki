---
title: Tastaturlayouts
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/resources/badusb/assets/layouts, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [unleashed-src, unleashed-readme]
---
# Bad-USB-Tastaturlayouts

Eine USB-Tastatur sendet keine Zeichen, sie sendet **Tastenpositionen**. Der Computer macht daraus Zeichen — nach
*seinem* Tastaturlayout. Um auf einem deutschen PC (QWERTZ) ein `z` zu tippen, muss der Flipper also die Taste
drücken, die auf einer US-Tastatur das `y` ist. Eine **Layout-Datei** (`.kl`) sagt Bad USB, welche Taste (und welcher
Modifier) im Ziellayout welches Zeichen erzeugt.

::: tip Unleashed
Die Tastaturlayouts für Bad USB stammen von [rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl)
und sind Teil von Unleashed. Der Befehl `DUCKY_LANG` für ein Layout pro Skript ist neu in Unleashed (PR #1224).
:::

## Verfügbare Layouts

Dateien in `/ext/badusb/assets/layouts/` (31 im aktuellen Build):

| Datei | Layout |
|---|---|
| `en-US.kl` | Englisch (USA), der **Standard** und der eingebaute Fallback |
| `en-UK.kl` | Englisch (Großbritannien) |
| `de-DE.kl`, `de-DE-mac.kl` | Deutsch (Deutschland), PC und Mac |
| `de-CH.kl` | Deutsch (Schweiz) |
| `fr-FR.kl`, `fr-FR-mac.kl` | Französisch (Frankreich), PC und Mac |
| `fr-BE.kl`, `fr-CA.kl`, `fr-CH.kl` | Französisch (Belgien, Kanada, Schweiz) |
| `es-ES.kl`, `es-LA.kl` | Spanisch (Spanien, Lateinamerika) |
| `it-IT.kl`, `it-IT-mac.kl` | Italienisch, PC und Mac |
| `pt-PT.kl`, `pt-BR.kl` | Portugiesisch (Portugal, Brasilien) |
| `nl-NL.kl` | Niederländisch |
| `da-DA.kl` | Dänisch |
| `nb-NO.kl` | Norwegisch |
| `sv-SE.kl` | Schwedisch |
| `fi-FI.kl` | Finnisch |
| `cz_CS.kl` | Tschechisch |
| `sk-SK.kl` | Slowakisch |
| `hu-HU.kl` | Ungarisch |
| `hr-HR.kl` | Kroatisch |
| `si-SI.kl` | Slowenisch |
| `ba-BA.kl` | Bosnisch |
| `tr-TR.kl` | Türkisch |
| `ja-JP.kl` | Japanisch |
| `dvorak.kl` | Dvorak (US) |
| `colemak.kl` | Colemak |

Ein russisches/kyrillisches Layout gibt es nicht: das Format kann nur ASCII-Zeichen beschreiben (siehe unten).

## Ein Layout wählen

**Global** (für alle Skripte): drücke auf dem Skriptbildschirm <kbd>←</kbd> **Config → Keyboard Layout (global)** und
wähle eine `.kl`-Datei. Die Wahl wird in `/ext/badusb/.badusb.settings` gespeichert und auf dem Skriptbildschirm in
Klammern angezeigt, z. B. `(de-DE)`. Fehlt die gespeicherte Datei oder ist sie defekt, wird `en-US` benutzt.

![Bad-USB-Menü Config, Keyboard Layout (global) ist der erste Punkt](/screens/badusb/config.png)

**Pro Skript**: setze `DUCKY_LANG <name>` an den Anfang des Skripts:

```text
DUCKY_LANG fr-FR
STRINGLN bonjour
```

- `<name>` ist der Dateiname ohne `.kl`. Kurzformen: `en` = `en-US`, `de` = `de-DE`, `fr` = `fr-FR`.
- Es gilt ab dieser Zeile und wird zu Beginn jedes Durchlaufs auf das globale Layout zurückgesetzt.
- Ein unbekannter oder ungültiger Name fällt auf das eingebaute `en-US` zurück, ohne das Skript abzubrechen.

## Was ein Layout NICHT ändert

- Nur der Text von `STRING` / `STRINGLN` und Einzelzeichen-Tasten (`CTRL c`, `HOLD a` …) laufen durch das Layout.
  Benannte Tasten (`ENTER`, `F5`, Pfeiltasten …) sind überall gleich.
- `ALTCHAR` / `ALTSTRING` nutzen das Layout überhaupt nicht; sie tippen Zeichen über ihren Code per `ALT`+Nummernblock
  — deshalb funktionieren sie unter Windows mit jedem Layout.
- Das Layout muss zur **aktuellen Eingabesprache des Hosts** passen. Hat ein PC mehrere Sprachen (z. B. Englisch und
  Russisch), stelle ihn vor dem Start auf die Sprache des Layouts um, sonst tippt `STRING` kyrillische Buchstaben.

## Dateiformat (`.kl`)

Eine `.kl`-Datei ist eine binäre Tabelle von genau **256 Byte**: 128 Einträge mit je 2 Byte (Little-Endian `uint16`),
einer für jeden ASCII-Code 0-127.

- **Low-Byte**: der HID-Usage-Code der zu drückenden Taste (z. B. `0x1F` = die Taste `2`).
- **High-Byte**: die Modifier-Bits, die dabei gehalten werden:

| Bit (High-Byte) | Modifier |
|---|---|
| `0x01` | Left Ctrl |
| `0x02` | Left Shift |
| `0x04` | Left Alt |
| `0x08` | Left GUI |
| `0x10` | Right Ctrl |
| `0x20` | Right Shift |
| `0x40` | Right Alt (AltGr) |
| `0x80` | Right GUI |

Beispiel aus `de-DE.kl`: der Eintrag für `"` (ASCII 34) ist `1F 02`, also Shift + `2` — dort sitzt das
Anführungszeichen auf einer deutschen Tastatur.

Weil die Tabelle nur 128 Einträge hat, **kann ausschließlich ASCII getippt werden**; ein `STRING` mit einem Byte
≥ 128 (UTF-8-Akzente, Umlaute, Kyrillisch, Emoji) bricht das Skript mit *„Native .kl supports ASCII, not UTF-8"* ab.
Dateinamen dürfen Buchstaben, Ziffern, `-` und `_` enthalten (max. 32 Zeichen vor `.kl`).

Ein eigenes Layout baust du nach der Anleitung in
[dummy-decoy/flipperzero_badusb_kl](https://github.com/dummy-decoy/flipperzero_badusb_kl); kopiere die fertige Datei
dann nach `/ext/badusb/assets/layouts/`.

## Verwandte Seiten

- [Skriptformat](/de/badusb/script-format#keyboard-layout-per-script-ducky-lang)
- [Bad USB verwenden](/de/badusb/usage)
- [Beispiele](/de/badusb/examples)
