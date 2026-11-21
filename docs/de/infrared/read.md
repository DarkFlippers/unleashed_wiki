---
title: Signale anlernen und senden
order: 10
original: [https://docs.flipper.net/zero/infrared/read, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# IR-Signale anlernen und senden

Flipper Zero kann die Tasten einer IR-Fernbedienung eine nach der anderen kopieren und als **virtuelle
Fernbedienung** behalten: eine `.ir`-Datei in `/ext/infrared/`. Praktisch, wenn die Originalfernbedienung verloren,
kaputt oder einfach im anderen Zimmer ist — oder wenn eine Universalfernbedienung dein Gerät nicht findet.

Signale [bekannter Protokolle](/de/infrared/protocols) werden dekodiert und in einer kompakten *geparsten* Form
gespeichert (Protokoll + Adresse + Befehl). Alles andere landet als **RAW**-Zeitwerte, was zum Abspielen genauso
funktioniert.

## Eine neue Fernbedienung anlernen

1. Gehe zu `Main Menu → Infrared → Learn New Remote`.
2. Der Bildschirm sagt **„Point the remote at IR port and push the button"**. Halte die Fernbedienung ein paar
   Zentimeter von der Oberkante des Flippers entfernt, mit freier Sicht auf das IR-Fenster.

   ![Learn New Remote wartet auf ein Signal: „Point the remote at IR port and push the button"](/screens/infrared/learn.png)

3. Drücke die Taste auf der Fernbedienung **kurz**. Halte sie nicht: eine gehaltene Taste ergibt eine lange Aufnahme
   voller Wiederholungen.
4. Der Aufnahmebildschirm erscheint:
   - ein dekodiertes Signal zeigt den Protokollnamen und Adresse/Befehl, z. B. `NECext`, `A: 0x87EE`, `C: 0xA05D`;
   - ein unbekanntes Signal zeigt **Unknown** und die Anzahl der Samples, z. B. `150 samples`.

   ![Aufnahmebildschirm: das dekodierte Protokoll NEC mit Adresse und Befehl, unten Retry, Send und Save](/screens/infrared/learn_success.png)

5. Entscheide, was passieren soll:
   - <kbd>OK</kbd> **Send**: spielt das aufgenommene Signal, solange du die Taste hältst — zum sofortigen Test;
   - <kbd>←</kbd> **Retry**: fragt *„Retry Reading? All unsaved data will be lost!"*; dann verwirft <kbd>←</kbd> Exit
     die Aufnahme und hört erneut zu, <kbd>→</kbd> Stay kehrt zurück;
   - <kbd>→</kbd> **Save**: weiter zur Namensvergabe.
6. Gib unter **„Name the button"** einen Tastennamen ein (max. 23 Zeichen) und bestätige. Der Standardname wird aus
   dem Signal gebildet: die ersten 4 Buchstaben des Protokolls und der Befehl (z. B. `NECe_A05D`), bei RAW
   `RAW_<samples>`.
7. **„Success!"** erscheint und die neue Fernbedienung öffnet sich. Die erste wird als `/ext/infrared/Remote.ir`
   gespeichert; ist der Name belegt, folgen `Remote1.ir`, `Remote2.ir` und so weiter.

![Aufgenommenes Signal auf dem Bildschirm](/img/remote/a62fc8f9d738534b.png)

::: tip Benenne die Fernbedienung um
Eine frische Fernbedienung heißt immer `Remote`. Benenne sie gleich über `Edit → Rename Remote` um (siehe unten),
sonst hast du am Ende `Remote`, `Remote1`, `Remote2` …
:::

### Weitere Tasten hinzufügen

Scrolle in der Tastenliste der Fernbedienung nach unten und wähle **`+`**. Der Anlernbildschirm öffnet sich wieder.
Aufnehmen, **Save**, Taste benennen — und du bekommst **„Saved"**: die Taste wird an dieselbe Datei angehängt.

Ein <kbd>Back</kbd> auf dem Aufnahmebildschirm fragt *„Exit to Infrared Menu?"* (bzw. *„Exit to Remote Menu?"*, wenn
du zu einer bestehenden Fernbedienung hinzufügst): mit Exit sind nicht gespeicherte Daten verloren.

## Eine gespeicherte Taste senden {#send-a-saved-button}

1. Gehe zu `Main Menu → Infrared → Saved Remotes` und wähle eine `.ir`-Datei.
2. Richte die Oberkante des Flippers auf das Gerät.
3. Wähle mit <kbd>↑</kbd> / <kbd>↓</kbd> eine Taste und drücke <kbd>OK</kbd>.

Das Signal wird **so lange gesendet, wie du** <kbd>OK</kbd> **hältst**: ein Druck für einen einzelnen Befehl, halten
für „drücken und halten"-Aktionen wie das Hochlaufen der Lautstärke. Die LED blinkt während des Sendens.

![Ein gespeichertes Signal senden](/img/remote/d20ed673954c3711.png)

::: tip Favoriten und Archiv
Gespeicherte Fernbedienungen erscheinen auch im **Archive** (`Main Menu → Archive → Infrared`) und können dort zu den
Favoriten hinzugefügt werden. In der Flipper Mobile App stehen sie unter **Archive → Infrared**, siehe
[Fernbedienungen in der Mobile-App](/de/infrared/mobile).
:::

## Eine Fernbedienung bearbeiten

Öffne eine Fernbedienung und wähle ganz unten in der Tastenliste **Edit**. Das Edit-Menü enthält:

| Punkt | Funktion |
|---|---|
| **Add Button** | Eine weitere Taste anlernen (wie `+`). |
| **Rename Button** | Taste auswählen, neuen Namen eingeben. |
| **Move Button** | Bildschirm *„Select a Button to Move"*: Taste auswählen, mit <kbd>OK</kbd> aufnehmen (sie rückt nach rechts), mit <kbd>↑</kbd> / <kbd>↓</kbd> verschieben, mit erneutem <kbd>OK</kbd> ablegen. |
| **Delete Button** | Taste auswählen. Die Bestätigung *„Delete Button?"* zeigt Name und Protokoll / Adresse / Befehl (oder `RAW` und die Sample-Anzahl). <kbd>←</kbd> Cancel, <kbd>→</kbd> Delete. |
| **Rename Remote** | Benennt die Fernbedienung und die Datei um. Existiert der Name, wird eine Zahl angehängt. |
| **Delete Remote** | Die Bestätigung *„Delete Remote?"* nennt die Anzahl der Tasten. Löscht die `.ir`-Datei. |

Namen sind bei Tasten wie bei Fernbedienungen auf **23 Zeichen** begrenzt. Größere Umbauten (Dateien zusammenführen,
viele Tasten entfernen) gehen am PC leichter: lade die Datei mit [qFlipper](/de/mobile/qflipper) herunter und
bearbeite sie als Text, siehe [IR-Dateiformat](/de/infrared/file-format).

::: warning Bibliotheksdateien sind keine Fernbedienungen
Versuchst du, eine Datei aus `/ext/infrared/assets/` über Saved Remotes zu öffnen, erscheint *„Library file … can't be
opened as a remote"*. Bibliotheksdateien (`Filetype: IR library file`) werden nur von den
[Universalfernbedienungen](/de/infrared/universal-remotes) benutzt.
:::

## Zusätze im Debug-Modus {#debug-mode-extras}

Mit `Settings → System → Debug` ON zeigt das Infrared-Menü zwei weitere Punkte:

- **Learn New Remote RAW**: derselbe Ablauf wie Learn, aber der Decoder ist abgeschaltet und jedes Signal wird als
  RAW gespeichert. Nützlich, wenn der Decoder ein Protokoll erkennt, die dekodierte Wiedergabe an deinem Gerät aber
  nicht funktioniert.
- **Debug RX**: der Bildschirm *„INFRARED monitor"*, der in Echtzeit zeigt, was der Empfänger bekommt.

## Fehlersuche

| Problem | Was du versuchen kannst |
|---|---|
| Beim Drücken der Fernbedienung passiert nichts | Prüfe die Batterien der Fernbedienung (schau mit einer Handykamera auf ihre LED). Gehe näher heran und ziele direkt auf die Oberkante. Vermeide direktes Sonnenlicht und Leuchtstoff-/LED-Lampen in der Nähe. |
| Das Signal wird als **Unknown / RAW** aufgenommen, obwohl die Fernbedienung verbreitet ist | Störungen können RAW erzwingen. Nutze **Retry** einige Male, bis ein dekodiertes Signal kommt. Ist es wirklich ein unbekanntes Protokoll, ist RAW völlig in Ordnung. |
| Riesige RAW-Aufnahmen (hunderte Samples) | Du hast die Taste gehalten. Drücke kurz; rund 100 Samples sind für einen einzelnen Druck typisch. Sehr lange Aufnahmen spielen langsam ab. Ein RAW-Signal fasst höchstens 1024 Zeitwerte. |
| Das Gerät reagiert nicht auf die gespeicherte Taste | Gehe näher heran, ziele direkt auf das IR-Fenster des Geräts. Sende mehrmals oder halte <kbd>OK</kbd> länger. Für große Entfernungen nutze ein [externes IR-Modul](/de/infrared/external-ir). |
| Die Klimaanlage reagiert falsch | Klimaanlagen-Fernbedienungen senden bei jedem Druck den vollständigen Zustand (Modus, Temperatur, Lüfter). Nimm jeden Zustand, den du brauchst, als eigene Taste auf, siehe [Aufnahmen beitragen](/de/infrared/captures#air-conditioners). |
| „Failed to load …" beim Senden | Die `.ir`-Datei ist beschädigt oder wurde von Hand falsch bearbeitet. Prüfe sie gegen das [Dateiformat](/de/infrared/file-format). |

## Verwandte Seiten

- [Universalfernbedienungen](/de/infrared/universal-remotes)
- [Fernbedienungen in der Mobile-App](/de/infrared/mobile)
- [IR-Dateiformat](/de/infrared/file-format)
- [Externe IR-Module](/de/infrared/external-ir)
