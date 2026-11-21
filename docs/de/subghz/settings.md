---
title: Radio Settings (Funkeinstellungen)
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/radio_settings, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://docs.flipper.net/zero/sub-ghz]
sources: [unleashed-src, unleashed-docs, unleashed-readme, flipper-docs]
---
# Radio Settings

`Main Menu → Sub-GHz → Radio Settings` enthält die Einstellungen, die für die ganze Sub-GHz-App gelten: welches
Funkmodul genutzt wird, Sendeleistung, Dateibenennung und das Verhalten des rollierenden Zählers. Die Einstellungen
für den Empfang (Frequenz, Modulation, Hopping, Filter) liegen in `Read → Config` — siehe
[Read](/de/subghz/read#config).

::: tip Unleashed
In der Stock-Firmware schaltet dieses Menü nur zwischen internem und externem Modul um. Unleashed ergänzt
**TX Power**, **Protocol Names**, **Counter Incr.** und im Debug-Modus **Ext Amp & LEDs** sowie **Debug Pin**.
:::

## Menüpunkte

![Radio Settings: Module, TX Power, Protocol Names und Counter Incr.](/screens/subghz/radio_settings.png)

| Punkt | Werte | Funktion |
|---|---|---|
| `Module` | `Internal`, `External` | Funkmodul für Empfang und Senden. `External` wird nur angeboten, wenn am GPIO ein externes CC1101 erkannt wird; antwortet es nicht, fällt der Flipper auf `Internal` zurück |
| `TX Power` | `Preset`, `10dBm +`, `7dBm`, `5dBm`, `0dBm`, `-10dBm`, `-15dBm`, `-20dBm`, `-30dBm` | Sendeleistung. `Preset` = was das Modulations-Preset vorgibt (Standard). Niedrigere Werte sind praktisch für Tests auf kurze Distanz |
| `Protocol Names` | `OFF` / `ON` | Mit `ON` enthalten automatisch erzeugte Dateinamen den Protokollnamen + Zeitstempel statt nur einen Zeitstempel bzw. Zufallsnamen |
| `Counter Incr.` | `+1`, `+2`, `+3` (normal) | Um wie viel der rollierende Zähler bei dynamischen Protokollen pro Sendung erhöht wird. Standard `+1` |

Zusätzliche Punkte im **Debug-Modus** (`Settings → System → Debug → ON`):

| Punkt | Werte | Funktion |
|---|---|---|
| `Counter Incr.` | `+1` `+2` `+3` `+4` `+5` `+10` `+50` `OVFL` `OFEX` `No` `-1` `-2` `-3` `-4` `-5` `-10` `-50` | Vollständige Liste der Zählerschritte für Experimente: große Sprünge, `OVFL` (Schritt 65535), `OFEX` (Spezialmodus), `No` (Zähler bleibt unverändert) und negative Schritte |
| `Ext Amp & LEDs` | `ON` / `OFF` | Steuert den Verstärker- bzw. LED-Pin externer Module (GPIO PC3, wie bei E07-Modulen). Standard `ON`. Schalte es aus, wenn dein Modul diesen Pin anders nutzt |
| `Debug Pin` | `OFF` / `17(1W)` | Spiegelt das Datensignal des Funkmoduls auf GPIO-Pin 17 (1-Wire) — für die Protokollentwicklung mit einem Logikanalysator |

`TX Power`, `Protocol Names` und `Ext Amp & LEDs` werden sofort gespeichert (in
`/ext/subghz/assets/last_subghz.settings`). `Counter Incr.` wird nicht gespeichert: es bleibt bis zum nächsten
Neustart des Flippers erhalten und geht dann auf `+1` zurück.

::: warning Zählerschrittweite
Große oder negative Zählerschritte sind für Experimente **an deinen eigenen Empfängern** gedacht. Einen Zähler weit
nach vorn zu springen schiebt den im Empfänger gespeicherten Zähler dauerhaft über den deiner
Originalfernbedienung hinaus; zurückzugehen lässt den Empfänger dich ignorieren. Um neben der
Originalfernbedienung zu bestehen, nimm die [Zählermodi](/de/subghz/counter-mode) oder lege mit
[Add Manually](/de/subghz/add-manually) eine neue Fernbedienung an. Hintergrund:
[Rolling Codes](/de/subghz/rolling-codes).
:::

## Weitere Einstellungen, die auf der SD-Karte liegen

| Datei | Zweck | Details |
|---|---|---|
| `/ext/subghz/assets/setting_user` | Zusätzliche Frequenzen, Hopper-Liste, Standardfrequenz, eigene Modulations-Presets | [Frequenzen](/de/subghz/frequencies#adding-frequencies), [Dateiformate](/de/subghz/file-format#setting-user) |
| `/ext/subghz/assets/dangerous_settings` | Erweiterter Frequenzbereich (außerhalb der Spezifikation) | [Frequenzen](/de/subghz/frequencies#extended-range) |
| `/ext/subghz/assets/keeloq_mfcodes_user` | Eigene KeeLoq-Herstellerschlüssel | [Dateiformate](/de/subghz/file-format#keeloq-mfcodes-user), [KeeLoq](/de/subghz/keeloq) |
| `/ext/subghz/assets/last_subghz.settings` | Zuletzt genutzte Frequenz, Modulation, Filter, Analyzer-Trigger — von der App geschrieben | nicht von Hand bearbeiten |

Dateien, die auf `.example` enden, sind Vorlagen: zum Aktivieren in `…_user` umbenennen. `_user`-Dateien werden von
Firmware-Updates nicht überschrieben.

## Fehlersuche

- **`Module` zeigt nur `Internal`** — kein externes CC1101 erkannt. Prüfe Verkabelung und Stromversorgung, dann geh
  erneut ins Menü. Siehe [Externes CC1101](/de/subghz/external-cc1101).
- **Die Signale sind beim Senden schwach** — prüfe, ob `TX Power` nicht auf einem negativen Wert steht.
- **Dateinamen bestehen nur aus Datumsangaben** — aktiviere `Protocol Names`.
- **Die Punkte `Ext Amp & LEDs` / `Debug Pin` fehlen** — sie erscheinen nur im Debug-Modus.

## Verwandte Seiten

- [Read → Config](/de/subghz/read#config) · [Frequenzen](/de/subghz/frequencies) · [Externes CC1101](/de/subghz/external-cc1101)
- [Zählermodi](/de/subghz/counter-mode) · [Dateiformate](/de/subghz/file-format) · [Gefährliche Einstellungen](/de/start/dangerous-settings)
