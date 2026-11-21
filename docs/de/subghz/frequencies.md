---
title: Frequenzen und Bänder
order: 10
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/lib/subghz/subghz_setting.c, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/frequencies]
sources: [unleashed-src, unleashed-docs, flipper-docs]
---
# Frequenzen und Bänder

Flipper Zero redet mit der Welt unter 1 GHz über einen **TI CC1101**-Transceiver. Diese Seite beschreibt die Bänder,
die der Chip unterstützt, die Frequenzliste, die Unleashed mitbringt, wie die Sendebeschränkungen in Unleashed
funktionieren und wie du eigene Frequenzen hinzufügst.

## Bänder der Hardware

Das Datenblatt des CC1101 nennt drei Bänder:

| Band | Typische Nutzung |
|---|---|
| 300–348 MHz | US-Garagentore und -Tore (Familie 300, 310, 315, 318, 390 MHz), Autoschlüssel |
| 387–464 MHz | LPD433-Fernbedienungen auf 433.92 MHz, Schranken, Sensoren, Türklingeln (weite Teile Europas/der GUS) |
| 779–928 MHz | Geräte auf 868 MHz (EU SRD) und 915 MHz (US ISM) |

Unleashed weitet das Standard-Sendefenster leicht aus, damit die verbreiteten Frequenzen 350 MHz und 467.75 MHz
funktionieren.

## Sendebeschränkungen in Unleashed

::: tip Unleashed
Die Stock-Firmware sperrt das Senden auf die Frequenzen, die in der beim Update erkannten **Region** erlaubt sind
(z. B. nur 433.05–434.79 und 868.15–868.55 MHz in der EU/Russland). **Unleashed entfernt die Regionssperre
vollständig.** Du kannst auf jeder Frequenz senden, die der Chip unterstützt, ohne Zusatzschritte.
:::

Was weiterhin gilt, ist eine Sicherheitsgrenze der Hardware (aus `furi_hal_subghz.c`):

| Modus | Erlaubte Sendebereiche |
|---|---|
| Standard | 300–350 MHz, 387–467.75 MHz, 779–928 MHz |
| Erweitert („dangerous") | 281–361 MHz, 378–481 MHz, 749–962 MHz |

Versuchst du außerhalb des erlaubten Bereichs zu senden, verweigert der Flipper das Senden.

### Den Bereich erweitern (gefährlich) {#extended-range}

::: danger
Senden außerhalb der CC1101-Spezifikationen kann **den Funkchip beschädigen**. Weder das Flipper-Team noch die
Unleashed-Entwickler haften für Schäden. Fast niemand braucht das — der Standardbereich deckt praktisch jede echte
Fernbedienung ab.
:::

1. Verbinde die SD-Karte mit einem PC (oder nutze qFlipper bzw. den Dateimanager der Mobile-App).
2. Öffne `/ext/subghz/assets/dangerous_settings`. Der Inhalt sieht so aus:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Ändere `false` in `true`, speichere die Datei und starte den Flipper neu (die Einstellung wird beim Start
   gelesen).

Siehe auch [Gefährliche Einstellungen](/de/start/dangerous-settings).

## Standard-Frequenzliste

Das sind die Frequenzen, die du in **Read**, **Read RAW** → `Config` mit <kbd>←</kbd> <kbd>→</kbd> durchschalten
kannst und auf die der Frequency Analyzer rundet. **433.92 MHz** ist der Standard.

| 300–350 MHz | 387–467.75 MHz | 779–928 MHz |
|---|---|---|
| 300.000, 302.757, 303.000, 303.875, 303.900, 304.250, 307.000, 307.500, 307.800, 309.000, 310.000, 312.000, 312.100, 312.200, 313.000, 313.850, 314.000, 314.350, 314.980, 315.000, 317.000, 318.000, 320.000, 320.150, 330.000, 336.100, 345.000, 348.000, 350.000 | 387.000, 390.000, 418.000, 430.000, 430.500, 431.000, 431.500, 433.075 (erster LPD433-Kanal), 433.220, 433.420, 433.657070, 433.889, **433.920** (Mitte von LPD433, Standard), 434.075, 434.176948, 434.190, 434.390, 434.420, 434.620, 434.775 (letzter LPD433-Kanal), 438.900, 440.175, 462.750, 464.000, 467.750 | 779.000, 868.000, 868.350, 868.400, 868.460, 868.800, 868.950, 906.400, 915.000, 925.000, 928.000 |

### Hopping-Liste

Ist **Hopping** aktiv, durchläuft der Empfänger nur eine kurze Liste (bei einer langen Liste gingen zu viele Signale
verloren):

`315.00`, `390.00`, `430.50`, `433.92`, `434.42`, `868.35` MHz.

## Modulationen (Presets)

Die Frequenz allein genügt nicht — der Flipper ist kein SDR, man muss ihm die Modulation vorher sagen.
Eingebaute Presets:

| Name im Menü | Preset in der `.sub`-Datei | Bedeutung |
|---|---|---|
| `AM270` | `FuriHalSubGhzPresetOok270Async` | OOK/ASK, 270 kHz Bandbreite |
| `AM650` | `FuriHalSubGhzPresetOok650Async` | OOK/ASK, 650 kHz Bandbreite — **Standard, von den meisten Fernbedienungen genutzt** |
| `FM238` | `FuriHalSubGhzPreset2FSKDev238Async` | 2-FSK, 2,38 kHz Hub |
| `FM476` | `FuriHalSubGhzPreset2FSKDev476Async` | 2-FSK, 47,6 kHz Hub |
| `FM12K` | `FuriHalSubGhzPreset2FSKDev12KAsync` | 2-FSK, 12 kHz Hub (z. B. Cardin S449, Sommer) |

Du kannst eigene Presets hinzufügen (zum Beispiel `FM15k`, `Pagers`) — siehe
[Dateiformate](/de/subghz/file-format#setting-user).

## Eigene Frequenzen hinzufügen {#adding-frequencies}

1. Geh auf der SD-Karte nach `/ext/subghz/assets/`.
2. Benenne `setting_user.example` in `setting_user` um (die `_user`-Dateien überleben Firmware-Updates).
3. Füge Zeilen in diesem Format hinzu — immer 9 Stellen, in Hz:
   ```text
   Frequency: 928000000
   Hopper_frequency: 345000000
   ```
4. Starte die Sub-GHz-App neu.

Regeln, die man kennen sollte:

- Eigene Frequenzen werden **hinter** die Standardliste **angehängt** — scrolle zum Ende der Liste, um sie zu
  finden.
- `Hopper_frequency` fügt eine Frequenz zum Hopping hinzu. Halte die Hopper-Liste kurz. Eine Frequenz mehrfach
  einzutragen lässt den Flipper häufiger auf sie hören.
- Um **nur** deine eigenen Frequenzen zu nutzen, ändere `#Add_standard_frequencies: true` in
  `Add_standard_frequencies: false`. Dann musst du **beide** Listen füllen (`Frequency:` und `Hopper_frequency:`) —
  sonst ist die Hauptliste leer.
- `Default_frequency: 433920000` legt die Frequenz fest, mit der Read und Read RAW starten.

## Fehlersuche

- **Es wird nichts empfangen** — Frequenz oder Modulation ist falsch. Finde die Frequenz mit dem
  [Frequency Analyzer](/de/subghz/frequency-analyzer), probiere dann `AM650`, danach die FM-Presets.
- **Meine Frequenz steht nicht in der Liste** — füge sie in `setting_user` ein (siehe oben). Der Analyzer rundet
  weiterhin auf den nächsten Listeneintrag, setze den genauen Wert also von Hand in `Config`.
- **Senden wird verweigert** — die Frequenz liegt außerhalb des Standard-Sendefensters; prüfe die Tabelle oben.
  Aktiviere den erweiterten Bereich nicht einfach, um ihn „auszuprobieren".

## Verwandte Seiten

- [Frequency Analyzer](/de/subghz/frequency-analyzer) · [Read](/de/subghz/read) · [Read RAW](/de/subghz/read-raw)
- [Radio Settings](/de/subghz/settings) · [Dateiformate](/de/subghz/file-format) · [Externes CC1101](/de/subghz/external-cc1101)
