---
title: Infrarot
original: [https://docs.flipper.net/zero/infrared, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Infrarot

Flipper Zero hat ein eingebautes Infrarot-Modul (IR). Es kann die Tasten fast jeder IR-Fernbedienung **anlernen**, sie
als virtuelle Fernbedienung auf der microSD-Karte **speichern**, sie wieder **senden** und als
**Universalfernbedienung** arbeiten, die eine Bibliothek bekannter Codes für Fernseher, Audioanlagen, Projektoren,
LED-Streifen, Ventilatoren und Klimaanlagen durchläuft.

![Infrarot am Flipper Zero](/img/remote/133011d2bd3dc44c.png)

## Hardware

- Ein IR-durchlässiges Kunststofffenster an der Oberkante des Flippers.
- **Drei IR-LEDs** zum Senden.
- Ein **IR-Empfänger**, der den Träger demoduliert (er ist auf den verbreiteten 38-kHz-Träger abgestimmt). Zum
  Anlernen wird immer dieser eingebaute Empfänger benutzt.
- Optional ein **externer IR-Sender** an GPIO-Pin 2 (A7) für mehr Reichweite, siehe
  [Externe IR-Module](/de/infrared/external-ir).

## Das Infrared-Menü

Öffne `Main Menu → Infrared`. Die Menüpunkte stammen direkt aus der Firmware:

![Das Infrared-Menü mit Universal Remotes, Learn New Remote, Saved Remotes und GPIO Settings](/screens/infrared/menu.png)

| Punkt | Funktion |
|---|---|
| **Universal Remotes** | Sendet für eine Taste (Power, Vol+ …) eine ganze Code-Bibliothek, bis dein Gerät reagiert. Siehe [Universalfernbedienungen](/de/infrared/universal-remotes). |
| **Learn New Remote** | Nimmt Tasten einer physischen Fernbedienung auf und speichert sie als neue Fernbedienung. Siehe [Signale anlernen und senden](/de/infrared/read). |
| **Saved Remotes** | Öffnet den Dateibrowser in `/ext/infrared/`, um deine Fernbedienungen zu senden, zu bearbeiten, umzubenennen oder zu löschen. |
| **GPIO Settings** | Wählt den Sender (eingebaut, Pin 2 (A7) oder automatische Erkennung) und 5 V am GPIO. Siehe [Externe IR-Module](/de/infrared/external-ir). |
| **Learn New Remote RAW** | Nur mit `Settings → System → Debug` ON. Wie Learn, aber mit abgeschaltetem Decoder: jedes Signal wird als RAW gespeichert. |
| **Debug RX** | Nur mit Debug ON. Ein Live-„INFRARED monitor" dessen, was der Empfänger bekommt. |

::: tip Unleashed
Die Infrared-App, ihre Protokoll-Dekoder und die Mechanik der Universalfernbedienungen stammen aus der
offiziellen Firmware. Unleashed ergänzt:
- das IR-Protokoll **RCA** (siehe [Protokolle](/de/infrared/protocols));
- zusätzliche Bibliotheken für Universalfernbedienungen (**LEDs**, **Fans**) und deutlich größere, regelmäßig
  nachgeprüfte Bibliotheken für Fernseher, Audio, Projektoren und Klimaanlagen, gepflegt vom Unleashed-Team
  (IR-Assets von @amec0e). Die TV-Bibliothek wird so neu kompiliert, dass **alle** ihre Tasten funktionieren;
- Unterstützung für externe IR-Module mit automatischer Erkennung (von der offiziellen Firmware übernommen).
:::

## Wo die Dateien liegen

| Pfad | Inhalt |
|---|---|
| `/ext/infrared/*.ir` | Deine gespeicherten Fernbedienungen (`Filetype: IR signals file`). |
| `/ext/infrared/assets/*.ir` | Bibliotheken der Universalfernbedienungen: `tv.ir`, `audio.ir`, `projectors.ir`, `leds.ir`, `fans.ir`, `ac.ir` (`Filetype: IR library file`). Sie werden zusammen mit der Firmware installiert und aktualisiert. |
| `/ext/infrared/.infrared.settings` | GPIO-Einstellungen (Ausgangspin, 5 V). |

Das Format der `.ir`-Dateien ist unter [IR-Dateiformat](/de/infrared/file-format) beschrieben.

## Kommandozeile

Der Befehl `ir` steht in der [CLI](/de/dev/cli) zur Verfügung (zum Beispiel über qFlipper oder ein serielles
Terminal):

```text
ir rx [raw]                                  receive and print signals (raw = no decoding)
ir tx <protocol> <address> <command>         send a parsed signal, address/command in hex
ir tx RAW F:<frequency> DC:<duty_cycle> <sample0> <sample1>...
                                             frequency 10000-1000000 Hz, duty cycle 0-100, max 512 samples
ir decode <input_file> [<output_file>]       try to decode RAW signals of a file into parsed ones
ir universal <remote_name> <signal_name>     run a universal library, e.g. ir universal tv Power
ir universal list <remote_name>              list the signal names of a library
```

## Seiten in diesem Abschnitt

| Seite | Was du lernst |
|---|---|
| [Signale anlernen und senden](/de/infrared/read) | Eine Fernbedienung anlernen, speichern, Tasten senden, Tasten bearbeiten / verschieben / umbenennen / löschen |
| [Universalfernbedienungen](/de/infrared/universal-remotes) | Alle Kategorien, Tasten, Bedienung, einen funktionierenden Code speichern |
| [Fernbedienungen in der Mobile-App](/de/infrared/mobile) | Die Remotes Library in der Flipper Mobile App |
| [Aufnahmen beitragen](/de/infrared/captures) | Wie du saubere Signale für die Universalbibliotheken aufnimmst |
| [Externe IR-Module](/de/infrared/external-ir) | GPIO-Ausgang, automatische Erkennung, 5-V-Versorgung |
| [Protokolle](/de/infrared/protocols) | Jedes Protokoll, das der Decoder kennt, inkl. RCA |
| [IR-Dateiformat](/de/infrared/file-format) | Die `.ir`-Formate für Fernbedienungen, Bibliotheken und Testdateien |
