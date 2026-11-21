---
title: Auf Rohlinge schreiben
order: 20
author: gromovyna
original: [https://docs.flipper.net/zero/rfid/write-data, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29]
sources: [unleashed-src, flipper-docs, gromovyna]
---
# 125-kHz-Schlüssel auf Rohlinge schreiben

Original-125-kHz-Karten und -Anhänger sind fast immer nur lesbar. Für eine physische Kopie brauchst du einen
**beschreibbaren Rohling** — einen „Magic"-Chip, der sich so programmieren lässt, dass er sich wie eine Karte eines
anderen Protokolls verhält. Flipper Zero kann jeden gespeicherten, gelesenen oder manuell angelegten Schlüssel auf
so einen Rohling schreiben.

## Welche Rohlinge beschreibbar sind

| Chip (wie auf dem Display) | Typische Handelsnamen | Schreibt | Standard |
|---|---|---|---|
| **T5577** | T5577, ATA5577, „5577"-Karten/-Anhänger/-Sticker | jedes Protokoll | ON |
| **EM4305** | EM4305-/EM4205-Rohlinge | EM4100-Familie, Electra, FDX-B, Gallagher, GProxII, Jablotron, Radio Key (Securakey), Viking | ON |
| **8265** | ID8265 / H5 (Hitag-Micro-Klon, Standardpasswort) | EM4100-Familie | ON |
| **8210** | ID8210 (derselbe Chip, Passwort des FURUI-Cloners) | EM4100-Familie | ON |
| **H5.5** | iKey H5.5 (derselbe Chip, iKey-Passwort) | EM4100-Familie | ON |
| **8268** | ID8268 (Hitag-S-Magic-Chip) | EM4100 nur mit RF/64 | **OFF** |

::: tip Unleashed
Die offizielle Dokumentation spricht nur über T5577. Die Unterstützung für Hitag Micro (**8265/H5, H5.5 und 8210**)
kam von **@gromovyna** zu Unleashed — die Chips unterscheiden sich nur im Login-Passwort, deshalb probiert der
Flipper jedes bekannte Passwort der Reihe nach, statt zu fragen. Hintergrund und Geschichte:
[T5577 und Hitag Micro](/de/rfid/t5577-hitag).
:::

::: warning 8268 muss man selbst einschalten
Das Ziel **8268** (Hitag S) ist standardmäßig aus. Anders als die übrigen Writer wählt es jedes Hitag-S-Tag, das
antwortet, und bei einem echten Hitag S enthalten die Seiten 4 und 5 Anwendungsdaten — der Flipper kann ein echtes
Tag nicht von einem Klon unterscheiden. Schalte es nur ein, wenn du weißt, dass ein 8268-Rohling auf der Spule liegt.
:::

## Einen Schlüssel schreiben

1. Lies ein Tag (`Read` → **More** → **Write**) oder öffne ein gespeichertes (`Saved` → Schlüssel → **Write**).
2. Halte den Rohling an die Rückseite des Flippers und **bewege ihn nicht**. Die LED blinkt magenta.
3. Der Bildschirm zeigt **Writing**, das Protokoll in Klammern, den Dateinamen (oder *Unsaved Tag*) und in Klammern
   den **gerade probierten Chip**, zum Beispiel:

   ```text
   Writing
   [EM4100]
   Office
   (T5577)
   ```

   ![Schreibbildschirm mit dem Protokoll [EM4100], dem Schlüsselnamen und dem probierten Chip (T5577) in Klammern](/screens/lfrfid/write.png)

4. Der Flipper schreibt jeden aktivierten Chiptyp der Reihe nach und **liest das Tag nach jedem Versuch zurück**.
   Sobald das Zurückgelesene passt, hört er auf.
5. Bei Erfolg erscheint **Success!** mit dem Namen des Chips, der die Daten tatsächlich angenommen hat (z. B.
   `T5577`, `EM4305`, `H5.5`), und die App kehrt ins Schlüsselmenü zurück.

![Laufender Schreibvorgang mit dem gerade probierten Chip](/img/remote/34b72cbd8417d74e.png)

![Schreibergebnis mit dem Chipnamen](/img/remote/3ca59457a78dad5b.png)

::: tip Warum der Chipname?
Bei mehreren zu probierenden Chiptypen (und drei Passwörtern für Hitag Micro) kann ein Schreibvorgang deutlich länger
dauern, und es war unklar, was eigentlich geschrieben wurde. Den probierten und den endgültigen Chip anzuzeigen, war
@gromovynas UX-Verbesserung: Technisch ist das der Handelsname der Rohling-Variante, nicht ein Protokoll.
:::

## Settings → Write Chips

`Main Menu → 125 kHz RFID → Settings → Write Chips` listet alle Ziele: **T5577**, **EM4305**, **8265**, **8210**,
**H5.5**, **8268**, jeweils **ON** / **OFF**.

- <kbd>OK</kbd>, <kbd>←</kbd> oder <kbd>→</kbd> schaltet den markierten Chip um.
- Die Auswahl wird beim Verlassen der Seite (<kbd>Back</kbd>) nach `/ext/lfrfid/.lfrfid.settings` gespeichert.
- Chips abzuschalten, die du nie brauchst, macht Schreibvorgänge schneller (jeder aktivierte, aber nicht passende
  Chip kostet einen Schreib- und einen Prüfvorgang).
- Das CLI-Kommando `rfid write` beachtet dieselbe Einstellung.

Lässt sich die Seite nicht öffnen, erscheint *Settings plugin failed to load* — aktualisiere die SD-Ressourcen (die
Seite ist eine eigene Plugin-Datei). Schreibvorgänge nutzen weiterhin das, was in der Einstellungsdatei steht.

## Write and set password

`Saved` → Schlüssel → **Write and set password** schreibt den Schlüssel auf einen **T5577** und aktiviert dessen
Passwortschutz, sodass niemand das Tag ohne Passwort überschreiben kann.

1. Gib das 4 Byte lange Passwort in Hex ein. War noch keines gesetzt, ist das Feld mit einem Zufallswort aus dem
   T5577-Wörterbuch vorbelegt.
2. Halte den Rohling still. Der Bildschirm zeigt **Writing with password**, `[Protocol]` und den aktuellen Schritt.
3. Zuerst wird der Schlüssel geschrieben und zurückgelesen, dann wandert das Passwort in Block 7 und wird
   zurückgelesen, und erst danach wird das Passwort-Bit in Block 0 gesetzt. **Notiere das Passwort** — ein T5577, der
   mit einem unbekannten Passwort gesperrt ist, lässt sich nicht wiederverwenden.

Mögliche Ergebnisse:

| Bildschirm | Bedeutung |
|---|---|
| **Success!** | Schlüssel geschrieben, Passwort gespeichert und Schutz aktiv |
| **Error** — *This protocol cannot be written with a password* | Das Protokoll braucht alle 7 Datenblöcke, Block 7 kann kein Passwort aufnehmen |
| **Has a password** — *Clear it first: the T5577 app, Clear Password* | Das Tag ist bereits geschützt |
| **Cannot read it** | Es liegt etwas auf der Spule, aber seine Blöcke lassen sich nicht lesen — erst wipen oder das Passwort löschen |
| **Not written** | Ein Block hat den Schlüssel abgewiesen; das Tag trägt einen Teil davon und kein Passwort |
| **Not protected** | Das Passwort ist nicht in Block 7 gelandet, oder das Tag hat das Aktivieren des Schutzes abgelehnt |
| **Not confirmed** | Das Passwort ist auf dem Tag, aber ob der Schutz aktiv ist, ließ sich nicht zurücklesen |
| **Still trying to write...** | Kein Tag antwortet — prüfe, ob es ein beschreibbarer T5577 ist |

## Fehlermeldungen beim normalen Schreiben

| Meldung | Was zu tun ist |
|---|---|
| *This protocol cannot be written* | Dafür existiert keine Chip-Kodierung |
| *No write chips enabled. Enable one in Settings* | Alle Ziele sind OFF |
| *No enabled chip can write this protocol* | z. B. nur EM4305 aktiviert bei einem HID-Schlüssel — aktiviere T5577 |
| **Still Trying to Write...** *Make sure this card is writable and not protected* | Erscheint nach etwa 10 s oder nach mehreren fehlgeschlagenen Prüfvorgängen. Das Tag ist nur lesbar, mit einem Passwort geschützt, ein nicht unterstützter Chip oder schlecht positioniert. Der Flipper versucht es weiter, bis du <kbd>Back</kbd> drückst. |

## Fehlerbehebung

- **Der Rohling hat ein Passwort.** Viele billige Cloner sperren T5577-Rohlinge. Nimm die
  [T5577-App](/de/rfid/t5577-app) → **Clear Password** (probiert dein Passwort, dann das Wörterbuch).
- **Ein T5577 hat eine kaputte Konfiguration bekommen** (wird als gar nichts erkannt). Nimm die T5577-App →
  **Wipe Tag**.
- **Hitag Micro (8265/8210/H5.5) braucht gute Positionierung.** Diese Chips zu schreiben dauert länger und ist
  empfindlich gegenüber der Lage; der Flipper hat auf LF nur TX, Erfolg bestätigt sich also nur durch Zurücklesen des
  Tags.
- **„Success" bei einer nur lesbaren Karte.** Trägt ein nicht beschreibbares Tag schon dieselbe ID, passt das
  Zurückgelesene und der Schreibvorgang wird als erfolgreich gemeldet.
- **Anhänger mit Metall / dickem Gehäuse.** Probiere verschiedene Stellen; bei Schlüsselanhängern sitzt die Spule
  oft außermittig.

## Verwandte Seiten

- [T5577 und Hitag Micro](/de/rfid/t5577-hitag) · [T5577-App](/de/rfid/t5577-app) ·
  [Protokolle](/de/rfid/protocols) · [Lesen](/de/rfid/read)
