---
title: Sub-GHz-Remote-App
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz_remote, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemotePlugin.md, https://github.com/DarkFlippers/SubGHz_Remote]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Sub-GHz Remote

**Sub-GHz Remote** macht den Flipper zu einer Fernbedienung mit fünf Tasten. Du bindest bis zu fünf gespeicherte `.sub`-Dateien an <kbd>↑</kbd>, <kbd>↓</kbd>, <kbd>←</kbd>, <kbd>→</kbd> und <kbd>OK</kbd>, gibst jeder eine Bezeichnung und sendest sie dann mit einem Tastendruck, ohne dich durch `Sub-GHz → Saved` zu klicken.

::: tip Unleashed
Sub-GHz Remote ist in Unleashed eingebaut und steht im **Hauptmenü**: `Main Menu → Sub-GHz Remote`. Geschrieben haben sie @gid9798 und @xMasterX, ihr Quellcode liegt in einem eigenen Repository, [DarkFlippers/SubGHz_Remote](https://github.com/DarkFlippers/SubGHz_Remote), das als Submodul in der Firmware steckt. In der Stock-Firmware steht sie nicht im Menü; für die offizielle Firmware gibt es einen eigenen Build im App-Katalog.
:::

## Wann du sie brauchst

- Du nutzt ständig ein paar Signale, zum Beispiel ein Tor, ein Garagentor und eine Schranke, und willst sie einen Tastendruck weit entfernt haben.
- Du steuerst mehrere Geräte (Lüfter, Licht, Türklingel) und willst sie auf einem Bildschirm mit lesbaren Bezeichnungen haben.

Jede Taste sendet eine normale `.sub`-Datei, es funktioniert hier also alles, was auch aus `Sub-GHz → Saved → Emulate` funktioniert: statische Schlüssel, Rolling-Code-Fernbedienungen, die du mit [Add Manually](/de/subghz/add-manually) angelegt hast, RAW- und BinRAW-Aufnahmen. Protokolle, die der Flipper nur empfangen kann, lassen sich nicht binden.

## Das Menü

Die App öffnet sofort den Dateibrowser für Maps. Drücke <kbd>Back</kbd>, um ins Menü zu kommen:

| Eintrag | Was er tut |
|---|---|
| `Open Map File` | eine Map wählen und zum Fernbedienungsbildschirm gehen |
| `Edit Map File` | eine Map wählen und im Editor öffnen |
| `New Map File` | einen Namen eingeben und eine neue Map anlegen |
| `Set Default` | die Map wählen, die die App ab jetzt von selbst öffnet |
| `Clear Default` | diese Map wieder vergessen (nur sichtbar, wenn eine gesetzt ist) |

Maps sind `.txt`-Dateien im Ordner `subghz_remote` auf der SD-Karte. Der Dateiname ist beliebig, und du kannst so viele Maps behalten, wie du willst. Hast du noch einen alten `unirf`-Ordner aus früheren Versionen, verschiebt ihn die App beim ersten Start nach `subghz_remote`.

## Eine Map auf dem Flipper anlegen

Die App hat einen eingebauten Editor, du brauchst also keinen PC.

1. Speichere zuerst die Signale, die du willst, mit [Read](/de/subghz/read), [Read RAW](/de/subghz/read-raw) oder [Add Manually](/de/subghz/add-manually).
2. Öffne `Main Menu → Sub-GHz Remote`, drücke <kbd>Back</kbd> und wähle `New Map File`.
3. Gib einen Namen ein, bis zu 25 Zeichen. Die Map wird zu `/ext/subghz_remote/<name>.txt`.
4. Der Editor öffnet sich auf dem Slot `UP`.

| Taste im Editor | Was sie tut |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> | zwischen den fünf Slots wechseln: `UP`, `DOWN`, `LEFT`, `RIGHT`, `OK` |
| <kbd>OK</kbd> | `Edit` — das Menü des Slots öffnen |
| <kbd>→</kbd> | `Save` — zur Vorschau gehen |
| <kbd>←</kbd> oder <kbd>Back</kbd> | `Back` |

Die Leiste oben zeigt den Namen des Slots und seine Bezeichnung. Darunter steht der Pfad der Datei, die an diesem Slot hängt, oder `Button not set` bei einem leeren Slot, oder `ERR:` mit dem Grund: `File not found`, `Bad frequency`, `Bad modulation`, `Unsupported protocol`.

Das Slot-Menü hat vier Einträge:

- `Edit Label` — der Text, der für diese Taste angezeigt wird. Bis zu 25 Zeichen, davon passen etwa 16 auf den Fernbedienungsbildschirm. Eine leere Bezeichnung ist erlaubt, die App fragt vorher `Empty Label Name / Continue?`; ohne Bezeichnung zeigt sie stattdessen den Dateinamen.
- `Edit File` — ein Dateibrowser für `.sub`-Dateien, der in `/ext/subghz` startet. Lässt sich die Datei nicht verwenden, erscheint ein `ERROR`-Popup mit `Bad frequency`, `Bad modulation` oder `Unsupported protocol`, und der Slot behält, was er hatte.
- `Button` — welche Taste der Fernbedienung dieser Slot sendet: `Default`, `Up`, `Down`, `Left`, `Right`. Siehe [Eigene Tasten](#custom-buttons).
- `Clear Slot` — den Slot leeren.

Drücke <kbd>→</kbd>, wenn du fertig bist. Die Vorschau zeigt die fertige Fernbedienung, links `Back` und rechts `Save`; <kbd>→</kbd> oder <kbd>OK</kbd> schreibt die Datei, dann erscheint ein `Saved!`-Bildschirm. Verlässt du den Editor mit ungespeicherten Änderungen, fragt er vorher `Changes are not saved / do you want to exit?`.

Ein Slot darf leer bleiben. Eine Map mit einer einzigen Taste funktioniert.

## Senden

Wähle `Open Map File` und dann deine Map. Dieser Bildschirm ist quer gezeichnet, halte den Flipper also hochkant.

- **Halte** eine Taste, um zu senden. Die Zeile wird schwarz und die LED blinkt magenta.
- Lässt du los, sendet das Protokoll seine restlichen Wiederholungen und hört dann auf. Eine RAW-Datei läuft bis zum Ende der Aufnahme und beginnt von vorn, solange du die Taste hältst.
- Unter den fünf Zeilen zeigt die App, was sie sendet: Protokollname, Frequenz und Modulation, `Key:` (nur bei Schlüsseln bis 32 Bit), `Sn:` oder `Fix:`, `Cnt:`, `MF:`. Mehr als fünf Zeilen passen nicht.
- Das Symbol oben links sagt dir, ob das interne Funkmodul oder ein [externes Modul](/de/subghz/external-cc1101) genutzt wird.
- <kbd>Back</kbd> stoppt eine laufende Übertragung. Noch einmal drücken verlässt die App.

Ein Slot, dessen Datei nicht geladen werden konnte, zeigt statt seiner Bezeichnung `[X] Can't open file` oder `[X] Error in .sub file`. Leere Slots bleiben leer, und ein Druck darauf lässt die LED rot blinken.

## Eigene Tasten {#custom-buttons}

Eine Rolling-Code-Fernbedienung hat mehrere Tasten, und eine `.sub`-Datei speichert eine davon. `Button` im Slot-Menü wählt, welche dieser Slot sendet. `Default` behält die Taste aus der Datei; `Up`, `Down`, `Left` und `Right` senden die anderen Tasten derselben Fernbedienung, genau die, die du mit diesen Tasten auch aus `Sub-GHz → Saved → Emulate` bekommst. Der Editor hängt dann `(Btn. Up)` an den Pfad.

Der Zähler läuft pro Tastendruck einen Schritt weiter, und die App setzt die ursprüngliche Taste am Ende der Übertragung zurück.

So gibst du einer versteckten oder einer Programmiertaste einen eigenen Slot. Welche Pfeiltaste welche Taste ist, hängt vom Protokoll ab, siehe [Flipper als neue Fernbedienung](/de/subghz/remote-prog).

## Die Map-Datei

Der Editor schreibt eine reine Textdatei im Flipper-Format:

```text
Filetype: Flipper SubRem Map file
Version: 1
UP: /ext/subghz/Fan1.sub
DOWN: /ext/subghz/Fan2.sub
LEFT: /ext/subghz/Door.sub
RIGHT: /ext/subghz/Garage3.sub
OK: /ext/subghz/Garage3l.sub
ULABEL: Fan ON
DLABEL: Fan OFF
LLABEL: Doorbell
RLABEL: Garage OPEN
OKLABEL: Garage CLOSE
UBUTTON: 01
```

- `UP` / `DOWN` / `LEFT` / `RIGHT` / `OK` sind die vollständigen Pfade der `.sub`-Dateien, die an die jeweilige Richtung des Steuerkreuzes gebunden sind.
- `ULABEL` / `DLABEL` / `LLABEL` / `RLABEL` / `OKLABEL` sind die Texte, die für diese Tasten auf dem Bildschirm erscheinen.
- `UBUTTON` / `DBUTTON` / `LBUTTON` / `RBUTTON` / `OKBUTTON` sind die eigene Taste, in Hex: `00` Default, `01` oben, `02` unten, `03` links, `04` rechts. Nutzt der Slot `Default`, lässt der Editor die Zeile weg.

Du kannst eine Map auch am PC schreiben. Wenn du das tust:

- Trenne Schlüssel und Wert durch einen Doppelpunkt und **ein** Leerzeichen, genau wie oben.
- Die Reihenfolge der Zeilen ist egal, die App sucht jeden Schlüssel über seinen Namen. Ein weggelassener Schlüssel gilt als leer.
- Der **Dateiname** einer `.sub` muss aus druckbarem ASCII bestehen und darf `\ < > * | " : ?` nicht enthalten. Ein kyrillischer Name oder ein Emoji lässt diesen Slot scheitern.
- Halte Bezeichnungen bei etwa 16 Zeichen. Längere werden auf dem schmalen Fernbedienungsbildschirm abgeschnitten.

Der eingebaute Editor kann keine kaputte Map erzeugen, nimm also lieber ihn.

## Eine Map beim Start öffnen

`Set Default` legt die gewählte Map in `/ext/subghz_remote/.config` ab. Von da an springt die App beim Öffnen direkt auf den Fernbedienungsbildschirm, und <kbd>Back</kbd> bringt dich ins Menü. `Clear Default` löscht diese Datei.

Die App nimmt außerdem einen Map-Pfad als Startargument entgegen, eine andere App kann also eine bestimmte Fernbedienung direkt öffnen.

## Fehlersuche

- **`[X] Can't open file`**: die `.sub`-Datei, auf die der Slot zeigt, wurde verschoben, umbenannt oder gelöscht. Wähle sie mit `Edit File` neu aus oder korrigiere den Pfad in der Map.
- **`[X] Error in .sub file`**: die Datei lädt, lässt sich aber nicht senden. Der Editor sagt warum: `Bad frequency` (das gewählte Funkmodul unterstützt die Frequenz des Signals nicht, siehe [Frequenzen](/de/subghz/frequencies)), `Bad modulation` oder `Unsupported protocol` (das Protokoll kann nur empfangen).
- **Eine Taste tut nichts** und die LED blinkt rot: der Slot ist leer oder seine Datei ließ sich nicht laden.
- **Eine Rolling-Code-Fernbedienung funktioniert nicht mehr**, nachdem du Flipper und Original genutzt hast: das ist ein Zählerkonflikt, kein Fehler der App. Siehe [Rolling Codes](/de/subghz/rolling-codes) und lege mit [Flipper als neue Fernbedienung](/de/subghz/remote-prog) eine neue an.
- **Warnung `Not official FW` beim Start**: du hast den Build aus dem App-Katalog installiert, der für die offizielle Firmware gedacht ist. Nimm das Sub-GHz Remote, das in Unleashed schon im Hauptmenü steht.
- Ältere Anleitungen erwähnen einen Bildschirm `Config is incorrect. Please configure map.`. Die aktuelle App zeigt ihn nicht mehr; sie markiert die kaputten Tasten stattdessen auf dem Fernbedienungsbildschirm.

## Verwandte Seiten

- [Signale lesen](/de/subghz/read) · [Read RAW](/de/subghz/read-raw) · [Add Manually](/de/subghz/add-manually)
- [Flipper als neue Fernbedienung](/de/subghz/remote-prog)
- [Das `.sub`-Dateiformat](/de/subghz/file-format)
