---
title: IR-Dateiformat
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/InfraredFileFormats.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/infrared]
sources: [unleashed-docs, unleashed-src]
---
# Infrarot-Dateiformat (`.ir`)

Alle IR-Daten auf dem Flipper liegen als Klartext im Flipper Format vor (Zeilen der Art `key: value`). Die Endung ist
immer `.ir`. Es gibt drei Varianten, die sich nur im `Filetype`-Kopf und im Einsatzzweck unterscheiden.

| Filetype | Verwendet für | Ort |
|---|---|---|
| `IR signals file` | Deine Fernbedienungen (angelernt, aus einer Universalfernbedienung gespeichert, aus der App geladen) | `/ext/infrared/` |
| `IR library file` | Bibliotheken der Universalfernbedienungen | `/ext/infrared/assets/` |
| Testdatei (`.irtest`) | Unit-Tests der Decoder/Encoder | nur im Firmware-Repo |

## Fernbedienungsdatei

### Beispiel

```text
Filetype: IR signals file
Version: 1
#
name: Button_1
type: parsed
protocol: NECext
address: EE 87 00 00
command: 5D A0 00 00
#
name: Button_2
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 504 3432 502 483 500 484 510 502 502 482 501 485 509 1452 504 1458 509 1452 504 481 501 474 509 3420 503
#
name: Button_3
type: parsed
protocol: SIRC
address: 01 00 00 00
command: 15 00 00 00
```

Die Datei enthält beliebig viele Tasten. Jede Taste beginnt mit `name:`; eine `#`-Kommentarzeile zwischen den Tasten
dient nur der Lesbarkeit.

### Felder

| Feld | Verwendet in | Typ | Beschreibung |
|---|---|---|---|
| `name` | beiden | String | Tastenname. Nur druckbares ASCII. Die Flipper-Oberfläche begrenzt Namen auf 23 Zeichen. |
| `type` | beiden | String | `parsed` oder `raw`. |
| `protocol` | parsed | String | Protokollname, genau wie in der [Protokollliste](/de/infrared/protocols) (der CLI-Befehl `ir` gibt ihn ebenfalls aus). |
| `address` | parsed | hex | Adresse, immer **4 Byte**, niederwertigstes Byte zuerst: `EE 87 00 00` = `0x87EE`. |
| `command` | parsed | hex | Befehl, immer **4 Byte**, niederwertigstes Byte zuerst. |
| `frequency` | raw | uint32 | Trägerfrequenz in Hz, meist `38000`. Gültiger Bereich 10000-1000000. |
| `duty_cycle` | raw | float | Duty-Cycle des Trägers, meist `0.33`. Muss > 0 und ≤ 1 sein. |
| `data` | raw | uint32-Liste | Zeiten in Mikrosekunden zwischen den Pegelwechseln (Mark, Space, Mark, …), durch Leerzeichen getrennt. **Max. 1024** Werte. |

### Gültige Werte für `protocol`

```text
NEC  NECext  NEC42  NEC42ext  Samsung32  RC6  RC5  RC5X  SIRC  SIRC15  SIRC20  Kaseikyo  RCA  Pioneer
```

::: tip Unleashed
`RCA` ist eine Ergänzung von Unleashed. `Pioneer` existiert in der Firmware, obwohl das offizielle Formatdokument es
noch nicht aufführt.
:::

### Von Hand bearbeiten

- Lass die beiden Kopfzeilen (`Filetype`, `Version`) oben stehen.
- Jede Taste braucht `name` und `type`, dann entweder `protocol`/`address`/`command` oder
  `frequency`/`duty_cycle`/`data`.
- Um zwei Fernbedienungen zusammenzuführen, kopiere die Tastenblöcke der einen Datei an das Ende der anderen.
- Adress- und Befehlsbytes müssen 4 Byte lang bleiben, auch wenn das Protokoll weniger Bits nutzt; unbenutzte Bytes
  sind `00`.
- Meldet der Flipper *„Failed to load …"*, ist eines der Felder fehlerhaft (zum Beispiel eine RAW-`data`-Zeile mit
  mehr als 1024 Werten oder eine Frequenz außerhalb des Bereichs).

## Bibliotheksdateien {#library-files}

Bibliotheksdateien nutzen genau dieselbe Struktur; nur der Kopf unterscheidet sich:

```text
Filetype: IR library file
Version: 1
# Last Updated 5th Oct, 2024
# Last Checked 5th Oct, 2024
#
# Model: Example TV 1234
name: Power
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Die Universalfernbedienung sucht Signale **über den Namen**, die Namen müssen also genau zu den Tasten der
Bibliothek passen (siehe die Tabelle unter [Aufnahmen beitragen](/de/infrared/captures#button-names-per-library)).
Neue Modelle werden am Ende angehängt, davor ein Kommentar `# Model: …`.

Eine Bibliotheksdatei lässt sich nicht über `Saved Remotes` öffnen: die App meldet *„Library file … can't be opened as
a remote"*.

## Testdateien (`.irtest`)

Werden nur von den Unit-Tests der Firmware benutzt (`applications/debug/unit_tests/resources/unit_tests/infrared` im
Repo). Sie sehen wie Fernbedienungsdateien aus, zusätzlich gibt es den Typ `parsed_array` für ganze Folgen
dekodierter Nachrichten:

| Feld | Verwendet in | Typ | Beschreibung |
|---|---|---|---|
| `name` | beiden | String | Signalname, siehe Benennung unten. |
| `type` | beiden | String | `parsed_array` oder `raw`. |
| `count` | parsed_array | uint32 | Anzahl der Nachrichten im Array, mindestens 1. |
| `protocol`, `address`, `command` | parsed_array | | Wie oben, einmal pro Nachricht. |
| `repeat` | parsed_array | bool | Ob die Nachricht eine Wiederholung ist (Taste gehalten). |
| `frequency`, `duty_cycle`, `data` | raw | | Wie oben. |

Die Namen folgen dem Muster `<name><test_number>`: `decoder_input1` (RAW-Eingabe für den Decoder, gleichzeitig
erwartete Encoder-Ausgabe), `decoder_expected1` (erwartete Decoder-Ausgabe, gleichzeitig Encoder-Eingabe),
`encoder_decoder_input1` (geparstes Array, das einen Durchlauf Encode → Decode unverändert überstehen muss). Jedes
Protokoll muss so eine Testdatei haben.

## Verwandte Seiten

- [Protokolle](/de/infrared/protocols)
- [Aufnahmen beitragen](/de/infrared/captures)
- [Signale anlernen und senden](/de/infrared/read)
