---
title: Skriptformat
order: 20
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/file_formats/BadUsbScriptFormat.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb/helpers, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://docs.flipper.net/zero/bad-usb]
sources: [unleashed-docs, unleashed-src, flipper-docs]
---
# Bad-USB-Skriptformat (DuckyScript)

Bad USB führt Klartextskripte in einer **erweiterten DuckyScript**-Syntax aus. Klassische Skripte für den USB Rubber
Ducky 1.0 laufen unverändert; darüber hinaus bietet der Flipper eine eigene USB-/BLE-Identität, `ALT`+Nummernblock-
Eingabe, `SYSRQ`, Medientasten, Maussteuerung, das Warten auf einen Tastendruck und mehr. Diese Referenz ist gegen
die Befehlstabelle in der Firmware abgeglichen (`helpers/ducky_script_commands.c`, `ducky_script_keycodes.c`).

## Regeln für die Datei

- Klartext, Endung **`.txt`**, keine Kompilierung. Zeilenenden `\n` oder `\r\n`.
- Ein Befehl pro Zeile. Leerzeilen werden übersprungen; Zeilen dürfen mit Leerzeichen oder Tabs eingerückt sein.
- Befehle stehen in **GROSSBUCHSTABEN und sind groß-/kleinschreibungsabhängig**: `STRING`, nicht `string`.
- Befehl und Argument werden durch ein einzelnes Leerzeichen getrennt.
- Kommentare sind ganze Zeilen, die mit `REM` beginnen. Kommentare am Zeilenende gibt es nicht.
- Getippter Text (`STRING`, `STRINGLN`) muss **ASCII** sein. Nicht-ASCII-Zeichen brechen das Skript mit
  *„Native .kl supports ASCII, not UTF-8"* ab.
- Bei einem Fehler stoppt das Skript und der Bildschirm zeigt *ERROR:*, die Zeilennummer und den Grund.

## Kurzreferenz

| Befehl | Argument | Wirkung |
|---|---|---|
| `REM` | Text | Kommentar, wird ignoriert. |
| `ID` | `VID:PID [Manufacturer:Product]` | USB-Identität, **nur in der ersten Zeile**. |
| `BLE_ID` / `BT_ID` | `MAC Name` | Bluetooth-Identität, **nur in der ersten Zeile**. |
| `DELAY` | ms | Einmal warten. |
| `DEFAULT_DELAY` / `DEFAULTDELAY` | ms | Vor jedem folgenden Befehl warten. |
| `STRING` | Text | Text tippen. |
| `STRINGLN` | Text | Text tippen und Enter drücken. |
| `STRING_DELAY` / `STRINGDELAY` | ms | Pause zwischen den Tastenanschlägen, nur für das **nächste** `STRING`. |
| `DEFAULT_STRING_DELAY` / `DEFAULTSTRINGDELAY` | ms | Pause zwischen den Tastenanschlägen für **jedes** `STRING`. |
| `REPEAT` | n | Den vorherigen Befehl n weitere Male ausführen. |
| `DUCKY_LANG` | Layout-Name | Tastaturlayout für den Rest des Skripts umschalten (Unleashed). |
| `HOLD` | Taste / Maustaste | Drücken und gedrückt halten. |
| `RELEASE` | dieselbe | Eine gehaltene Taste loslassen. |
| `ALTCHAR` | Code | Ein Zeichen per `ALT`+Nummernblock tippen. |
| `ALTSTRING` / `ALTCODE` | Text | Text per `ALT`+Nummernblock tippen. |
| `SYSRQ` | Zeichen | Magic-SysRq-Tastenkombination. |
| `MEDIA` | Medientaste | Consumer-Control-Taste (Lautstärke, Play …). |
| `GLOBE` | Taste | Fn/Globe + Taste (Mac/iPad). |
| `WAIT_FOR_BUTTON_PRESS` | keines | Pause, bis am Flipper <kbd>OK</kbd> gedrückt wird. |
| `LEFTCLICK`, `RIGHTCLICK`, `MIDDLECLICK`… | keines | Mausklicks. |
| `MOUSEMOVE` / `MOUSE_MOVE` | x y | Maus bewegen. |
| `MOUSESCROLL` / `MOUSE_SCROLL` | Delta | Mit dem Rad scrollen. |
| Tastenkombination | z. B. `CTRL-ALT DELETE` | Tasten gemeinsam drücken und loslassen. |

## Kommentare

```text
REM This line is ignored
```

## Verzögerungen

| Befehl | Parameter | Hinweise |
|---|---|---|
| `DELAY` | ms | Einzelne Pause. |
| `DEFAULT_DELAY` | ms | Wird vor jedem weiteren Befehl eingefügt. Gleichbedeutend mit `DEFAULTDELAY`. |

```text
DEFAULT_DELAY 50
DELAY 1000
```

Verzögerungen sind dein wichtigstes Mittel für Zuverlässigkeit: der Host braucht Zeit, um Fenster zu öffnen — setze
also ein `DELAY` nach `GUI r`, nach `ENTER` in einem Startdialog usw. Lange Verzögerungen zeigt der Bildschirm als
`Delay Ns` an.

## Text tippen

| Befehl | Parameter | Hinweise |
|---|---|---|
| `STRING` | Text | Tippt den Text genau so, über das aktive Tastaturlayout. |
| `STRINGLN` | Text | Dasselbe, drückt danach Enter. |
| `STRING_DELAY` | ms | Pause zwischen den Anschlägen, nur für das nächste `STRING`/`STRINGLN`. Gleichbedeutend mit `STRINGDELAY`. |
| `DEFAULT_STRING_DELAY` | ms | Pause zwischen den Anschlägen für alle folgenden Zeichenketten. Gleichbedeutend mit `DEFAULTSTRINGDELAY`. |

```text
DEFAULT_STRING_DELAY 10
STRINGLN Hello World!
```

Ohne String-Delay wird der Text so schnell wie möglich gesendet; manche Hosts und Anwendungen verlieren dabei
Zeichen. Die mitgelieferten Demo-Skripte benutzen `DEFAULT_STRING_DELAY 10`.

::: warning Das Layout entscheidet
`STRING` sendet *Tastenpositionen*, übersetzt über das gewählte [Tastaturlayout](/de/badusb/layouts). Nutzt der Host
ein anderes Layout als die App, bekommst du falsche Zeichen. Der Text muss ASCII sein.
:::

## Tasten und Kombinationen

Eine Zeile, die kein Befehl ist, wird als Tastendruck gelesen: null oder mehr **Modifier**, dann eine **Taste**.
Modifier werden mit Leerzeichen oder Bindestrichen verbunden. Die Taste ist ein Sondertastenname oder ein einzelnes
Zeichen.

```text
ENTER
GUI r
CTRL c
CTRL-SHIFT ESC
CTRL ALT DELETE
ALT F4
SHIFT TAB
```

### Modifier

| Name | Hinweise |
|---|---|
| `CTRL`, `CONTROL` | |
| `SHIFT` | |
| `ALT` | |
| `GUI`, `WINDOWS` | Windows- / Command- / Super-Taste |

### Sondertasten

| Name | Hinweise |
|---|---|
| `DOWNARROW` / `DOWN`, `LEFTARROW` / `LEFT`, `RIGHTARROW` / `RIGHT`, `UPARROW` / `UP` | Pfeiltasten |
| `ENTER` | |
| `DELETE` | Entf (vorwärts löschen) |
| `BACKSPACE` | |
| `END`, `HOME`, `INSERT`, `PAGEUP`, `PAGEDOWN` | |
| `ESCAPE` / `ESC` | |
| `CAPSLOCK`, `NUMLOCK`, `SCROLLLOCK` | |
| `PRINTSCREEN` | |
| `BREAK`, `PAUSE` | Pause/Break |
| `SPACE`, `TAB` | |
| `MENU`, `APP` | Kontextmenü-Taste |
| `F1` … `F24` | Funktionstasten (die Firmware kennt auch F13-F24) |

## Wiederholen

```text
DOWN
REPEAT 9
```

`REPEAT n` führt den **vorherigen Befehl** n weitere Male aus (im Beispiel wird Pfeil-ab zehnmal gedrückt). `n` muss
≥ 1 sein.

## Halten und loslassen

| Befehl | Parameter | Hinweise |
|---|---|---|
| `HOLD` | Sondertaste, Modifier, einzelnes Zeichen oder Maustaste | Drücken und halten, bis `RELEASE` kommt. |
| `RELEASE` | dieselben | Diese Taste loslassen. |

```text
HOLD SHIFT
DOWN
REPEAT 4
RELEASE SHIFT
```

Es können höchstens **6** Tasten/Knöpfe gleichzeitig gehalten werden (die Größe des HID-Key-Reports); mehr ergibt
*„Too many keys are held"*. Ein `RELEASE`, ohne dass etwas gehalten wird, ergibt *„No keys are held"*. Das offizielle
Dokument nennt 5; die Prüfung in der Firmware erlaubt 6.

## ALT + Nummernblock-Eingabe

Unter Windows (und bei manchen Linux-Konfigurationen) lässt sich jedes Zeichen tippen, indem man `ALT` hält und
seinen Code auf dem Nummernblock eingibt. Das **hängt nicht vom Tastaturlayout ab**, was es an unbekannten Rechnern
sehr praktisch macht.

| Befehl | Parameter | Hinweise |
|---|---|---|
| `ALTCHAR` | Zeichencode | Tippt ein Zeichen: hält ALT und gibt die Ziffern auf dem Nummernblock ein. |
| `ALTSTRING` | Text | Tippt jedes druckbare ASCII-Zeichen (32-126) des Textes über seinen ALT-Code. |
| `ALTCODE` | Text | Gleichbedeutend mit `ALTSTRING` (Name, den manche DuckyScript-Implementierungen verwenden). |

NumLock wird vor der ALT-Eingabe automatisch eingeschaltet.

```text
ALTCHAR 7
ALTSTRING This works with any keyboard layout
```

## SysRq

```text
SYSRQ b
```

Sendet `ALT`+`PRINTSCREEN`+Taste, die Linux-Kombination [Magic SysRq](https://en.wikipedia.org/wiki/Magic_SysRq_key).
Vorsicht: manche SysRq-Tasten starten das System sofort neu oder halten es an.

## Medientasten

`MEDIA <key>` drückt eine Consumer-Control-Taste:

| Taste | Hinweise |
|---|---|
| `POWER`, `REBOOT`, `SLEEP`, `LOGOFF` | System |
| `EXIT`, `HOME`, `BACK`, `FORWARD`, `REFRESH` | Browser- / App-Navigation |
| `SNAPSHOT` | In einer Kamera-App ein Foto aufnehmen |
| `PLAY`, `PAUSE`, `PLAY_PAUSE`, `NEXT_TRACK`, `PREV_TRACK`, `STOP`, `EJECT` | Wiedergabe |
| `MUTE`, `VOLUME_UP`, `VOLUME_DOWN` | Lautstärke |
| `FN` | Fn/Globe-Taste auf Mac-Tastaturen |
| `BRIGHT_UP`, `BRIGHT_DOWN` | Bildschirmhelligkeit |

```text
MEDIA VOLUME_UP
REPEAT 5
```

## Fn- / Globe-Taste (Mac, iPad)

```text
GLOBE e
```

`GLOBE <key>` hält Fn/Globe, drückt die Taste und lässt beide los (Sondertaste oder einzelnes Zeichen).

## Auf einen Tastendruck warten

```text
WAIT_FOR_BUTTON_PRESS
```

Das Skript hält unbegrenzt an; der Flipper zeigt **Press to continue**. Drücke <kbd>OK</kbd>, um weiterzumachen.
Nützlich, um sich mit etwas zu synchronisieren, das du von Hand tust (anmelden, Bildschirm entsperren …).

## Maus

| Befehl | Parameter | Hinweise |
|---|---|---|
| `LEFTCLICK` / `LEFT_CLICK` | keines | Linksklick |
| `RIGHTCLICK` / `RIGHT_CLICK` | keines | Rechtsklick |
| `MIDDLECLICK` / `MIDDLE_CLICK` / `WHEELCLICK` / `WHEEL_CLICK` | keines | Mittlere (Rad-)Taste |
| `MOUSEMOVE` / `MOUSE_MOVE` | `x y` (ganze Zahlen) | Relative Bewegung; negativ = links / oben |
| `MOUSESCROLL` / `MOUSE_SCROLL` | `delta` (ganze Zahl) | Scrollrad; das Vorzeichen gibt die Richtung |

Maustasten funktionieren mit `HOLD`/`RELEASE`, z. B. für Drag-and-drop:

```text
HOLD LEFTCLICK
MOUSEMOVE 100 0
RELEASE LEFTCLICK
```

## Device ID {#device-id}

Du kannst festlegen, mit welcher Identität sich der Flipper beim Host meldet. Der Befehl muss in der **allerersten
Zeile** stehen; er wird beim Öffnen des Skripts angewandt, noch vor dem Start, und die App **wechselt in den
passenden Verbindungsmodus** (von Hand kannst du weiterhin zurückschalten). In anderen Zeilen werden diese Befehle
ignoriert.

| Befehl | Parameter | Beispiel | Modus |
|---|---|---|---|
| `ID` | `VID:PID Manufacturer:Product` | `ID 1234:abcd Flipper Devices:Flipper Zero` | USB |
| `BLE_ID` | `MAC Device name` | `BLE_ID AA:BB:CC:DD:EE:FF Smart Fridge` | Bluetooth |
| `BT_ID` | `MAC Device name` | `BT_ID AA:BB:CC:DD:EE:FF Smart Fridge` | wie `BLE_ID` |

- `ID`: VID und PID (hex) sind Pflicht; Hersteller- und Produkt-String sind optional (je max. 31 Zeichen).
- `BLE_ID` / `BT_ID`: die 6-Byte-MAC und der Gerätename sind beide Pflicht.

## Tastaturlayout pro Skript: `DUCKY_LANG` {#keyboard-layout-per-script-ducky-lang}

::: tip Unleashed
`DUCKY_LANG` ist neu in Unleashed (PR #1224 von @ANTONiO-eagle).
:::

```text
DUCKY_LANG de-DE
STRING Hallo Welt
```

- Lädt `/ext/badusb/assets/layouts/<name>.kl` und benutzt es ab dieser Zeile anstelle des globalen Layouts aus
  `Config`. Kurzformen: `en` → `en-US`, `de` → `de-DE`, `fr` → `fr-FR`.
- Der Name darf Buchstaben, Ziffern, `-` und `_` enthalten, und nach ihm darf in der Zeile nichts mehr folgen.
- Eine fehlende Datei oder ein ungültiger Name **bricht das Skript nicht ab**: es fällt still auf das eingebaute
  `en-US` zurück.
- Jeder neue Durchlauf beginnt wieder mit dem globalen Layout — setze `DUCKY_LANG` also möglichst weit oben.

Die Liste der Layout-Namen steht unter [Tastaturlayouts](/de/badusb/layouts).

## Verwandte Seiten

- [Beispiele](/de/badusb/examples)
- [Tastaturlayouts](/de/badusb/layouts)
- [Bad USB verwenden](/de/badusb/usage)
