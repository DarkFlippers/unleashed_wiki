---
title: Auf Rohlinge schreiben
order: 20
original: [https://docs.flipper.net/zero/ibutton/write, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/ibutton/protocols/blanks]
sources: [unleashed-src, flipper-docs]
---
# iButton-Schlüssel auf Rohlinge schreiben

Original-iButton-Schlüssel haben eine ab Werk festgelegte ID, die sich nicht ändern lässt. Zum Kopieren brauchst du
einen **Rohling** — einen wiederbeschreibbaren Schlüssel, dessen ID programmierbar ist. Flipper Zero hat zwei
Schreibmodi:

- **Write ID** — schreibt die ID (ROM bzw. Code) auf einen Rohling. Das ist das übliche „ich will eine Kopie meines
  Türsprechanlagen-Schlüssels".
- **Full Write on Same Type** — nur für DS1992, DS1996 und DS1971: kopiert den **Speicherinhalt** auf einen anderen
  echten Schlüssel desselben Typs (DS1992 → DS1992). Der Zielschlüssel behält seine eigene ID.

## Unterstützte Rohlinge

| Rohling (wie in Settings) | Schreibt | Hinweise |
|---|---|---|
| **RW1990.1** | IDs von DS1990, DS1420 | Rohlinge vom Typ RW1990; diese Variante schreibt die Bits invertiert |
| **RW1990.2** | IDs von DS1990, DS1420 | Rohlinge vom Typ RW1990, nicht invertierte Variante |
| **TM2004** | IDs von DS1990, DS1420, DS1992, DS1996, DS1971 und generischem 1-Wire | RW2004/TM2004-Rohlinge; es wird nur die ID geschrieben, obwohl der Rohling Speicher hat |
| **TM01x** | DS1990-ID, **Cyfral**, **Metakom** | TM01/TM01x-Rohlinge |

Rohlinge, die als RW1990, TM1990 oder TM08v2 verkauft werden, deckt eine der RW1990-Varianten ab; der Flipper probiert
beide, du musst also nicht wissen, welche du vor dir hast.

::: tip Unleashed
- Unter **Settings → Write Blanks** kannst du Rohling-Typen ein- und ausschalten (standardmäßig sind alle ON).
- Der Schreibbildschirm zeigt, welcher Rohling gerade probiert wird, und die Erfolgsmeldung lautet z. B.
  *Written to TM2004!*
- **Cyfral und Metakom** lassen sich auf **TM01x**-Rohlinge schreiben.
:::

::: warning TM01x für Cyfral / Metakom ist einmalig
Für Cyfral und Metakom wird der TM01x-Rohling beschrieben, zurückgelesen, verglichen und dann in den Cyfral- bzw.
Metakom-Modus **finalisiert**. Das Finalisieren lässt sich nicht rückgängig machen: Der Rohling antwortet dann nicht
mehr als 1-Wire-Gerät und kann nicht erneut beschrieben werden — auch nicht als Dallas-Schlüssel. Schlägt die
Verifikation fehl, wird der Rohling nicht finalisiert und bleibt beschreibbar. Eine auf einen TM01x geschriebene
Dallas-ID wird nicht finalisiert.

Metakom-Schlüssel mit falscher Parität werden abgewiesen (*Refusing to write a key with odd parity*).
:::

## Write ID

1. Öffne den Schlüssel: `Saved` → Schlüssel → **Write ID** (oder nach dem Lesen **More → Write ID**).

   ![Menü eines gespeicherten Schlüssels mit Emulate, Write ID, Edit und Rename](/screens/ibutton/saved_menu.png)

2. Der Bildschirm zeigt **Writing ID**, `[Protocol]`, den Schlüsselnamen (oder *Unsaved Key*) und in Klammern den
   gerade probierten Rohling-Typ — etwa `(RW1990.1)`.

   ![Bildschirm Writing ID mit dem Protokoll [DS1990], dem Schlüsselnamen und dem probierten Rohling (RW1990.1)](/screens/ibutton/write.png)

3. Halte den Rohling wie beim Lesen an den **flachen Teil** des Kontaktfelds (linker Daten-Pin + mittlere Masse).
   Halte ihn still.
4. Der Flipper probiert jeden aktivierten Rohling, der dieses Protokoll tragen kann, und liest das Ergebnis zurück.
5. **Written to RW1990.2!** (oder *Successfully written!*) — fertig.

## Full Write on Same Type

1. `Saved` → DS1992-/DS1996-/DS1971-Schlüssel → **Full Write on Same Type**.
2. Der Bildschirm zeigt **Full Writing**. Halte einen echten Schlüssel **desselben** Typs an das Kontaktfeld.
3. Der Speicher wird geschrieben; die ID des Ziels bleibt erhalten. Dieser Modus nutzt die Einstellung Write Blanks
   nicht.

## Settings → Write Blanks

`Main Menu → iButton → Settings → Write Blanks` listet **RW1990.1**, **RW1990.2**, **TM2004** und **TM01x** mit
**ON**/**OFF**. Umschalten mit <kbd>OK</kbd>/<kbd>←</kbd>/<kbd>→</kbd>; gespeichert wird beim Verlassen, in
`/ext/ibutton/.ibutton.settings`. Das CLI-Kommando `ikey write` nutzt dieselbe Einstellung.

Meldet die Seite *Settings page missing. Update the SD resources*, installiere die Firmware mit eingesteckter
SD-Karte neu.

## Fehlermeldungen

| Bildschirm | Bedeutung |
|---|---|
| **Cannot Write** — *No blanks enabled. Enable one in Settings* | Alle Rohling-Typen sind OFF |
| **Cannot Write** — *No enabled blank can write this key* | z. B. nur RW1990 aktiviert bei einem Metakom-Schlüssel |
| **Cannot Write** — *This key cannot be written* (oder der Grund des Protokolls) | Die Daten des Schlüssels sind zum Schreiben ungültig |
| Schreibbildschirm bleibt stehen, LED blinkt | Noch kein Rohling erkannt — Kontakt prüfen, oder der Rohling-Typ wird nicht unterstützt |

## Fehlerbehebung

- **Kontakt.** Die Mitte des Rohlings muss den Daten-Pin, sein Rand den Masse-Pin berühren.
- **Unbekannter Rohling-Typ.** Aktiviere alle Typen. Manche billigen Rohlinge sind von Typen, die der Flipper nicht
  programmieren kann.
- **„Erfolg", aber das Lesegerät weist die Kopie ab.** Manche Lesegeräte filtern Rohlinge heraus (sie prüfen auf
  typisches Rohling-Verhalten) — dagegen kann der Flipper nichts machen.
- **Verbrauchter TM01x.** Ein als Cyfral/Metakom finalisierter TM01x lässt sich nicht wiederverwenden.

## Verwandte Seiten

- [Lesen](/de/ibutton/read) · [Protokolle](/de/ibutton/protocols) · [Manuell anlegen](/de/ibutton/add-manually)
