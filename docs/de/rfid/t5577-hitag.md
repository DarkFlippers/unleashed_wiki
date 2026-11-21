---
title: T5577 und Hitag Micro (von @gromovyna)
order: 60
author: gromovyna
original: [https://telegra.ph/Prevyu-LF-RFID-fichej-kotorye-ya-prigotovil-dlya-Unleashed-06-08, https://t.me/gromovyna/29, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/lfrfid, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/t5577]
sources: [gromovyna, unleashed-src]
---
# Hitag Micro schreiben, Schreib-UX und T5577-Wipe

Nach dem Artikel von @gromovyna *„Vorschau auf die LF-(RFID-)Features, die ich für Unleashed vorbereitet habe"*
(Juni 2026), ergänzt um den heutigen Stand der Funktionen in der Firmware.

![](/img/remote/2e30c69f7eded901.png)

## Vorgeschichte

Nach einer langen Pause kehrte @gromovyna zur Forschung zurück und nahm sich die **H5.5**-Rohlinge vor, die *iKey*
verkauft. Aus Icemans Discord war bereits bekannt, dass H5.5 derselbe chinesische **Hitag-Micro**-Klon ist, auf dem
iKey ein eigenes Passwort gesetzt hat. Die Namenslage:

| Name | Was es ist |
|---|---|
| **8265 / H5** | der Chip mit dem Standardpasswort |
| **H5.5** | derselbe Chip mit dem **iKey**-Passwort |
| **8210** | derselbe Chip mit dem Passwort des chinesischen Cloners **FURUI** |

Er holte das iKey-Passwort heraus (am zweiten Tag des Versuchens), teilte es mit der Community und
[aktualisierte die Magic-Cards-Notizen von Proxmark3](https://github.com/RfidResearchGroup/proxmark3/blob/master/doc/magic_cards_notes.md#id8265).
Danach implementierte er die Funktionen für den Flipper — als Pull Requests an **Unleashed**, in der Hoffnung, sie
auch ins OFW zu bringen, sobald dort wieder aktiv entwickelt wird.

Die Passwörter, die die Firmware für die drei Varianten nutzt:

| Variante | Passwort |
|---|---|
| 8265 / H5 | `00000000` |
| 8210 | `9AC4999C` |
| H5.5 | `496B0E59` |

## Unterstützung für Hitag Micro

Der Flipper kann Hitag-Micro-Klone — **8265/H5**, **H5.5** und **8210** — jetzt als EM4100-Schlüssel **schreiben**
(der Chip wird so konfiguriert, dass er den EM4100-Frame von selbst sendet, „transponder talks first").

Grenzen der aktuellen Architektur:
- die LF-Hardware des Flippers **sendet** beim Schreiben nur, Erfolg lässt sich also allein durch **Zurücklesen des
  Tags** prüfen;
- viel Zeit floss in die Kalibrierung von Konstanten, trotzdem braucht das Schreiben dieser Chips eine **gute
  Positionierung**.

### Warum das Schreiben langsamer wurde

Die neue Unterstützung hat die UX zunächst verschlechtert, denn die Schreiblogik ist jetzt eine Schleife, die
nacheinander probiert:

- **T5577**
- **EM4305**
- **Hitag Micro** — und hier drei Varianten, eine pro bekanntem Werkspasswort; diese Operationen sind schon für sich
  langsamer

Bei Hitag Micro probiert der Flipper das Passwort jeder bekannten Variante der Reihe nach, damit er den Nutzer nicht
fragen muss — Fragen würde eine der Grundideen von Flipper Zero zerstören: Einfachheit. Der Preis ist die
Schreibgeschwindigkeit. Ein falsches Passwort wird vom Chip einfach abgewiesen und lässt das Tag unberührt; vorhanden
ist die Variante, die sich korrekt zurücklesen lässt.

Für den Nutzer sah das furchtbar aus — als würde nichts passieren — und es war unklar, mit welchem Protokoll das Tag
beschrieben wurde. Daher die nächste Funktion.

## UX: Womit schreiben wir gerade / was wurde geschrieben?

Während eines Schreibvorgangs zeigt der Bildschirm jetzt, **welcher Chip gerade probiert wird**:

![Laufender Schreibvorgang](/img/remote/34b72cbd8417d74e.png)

Technisch ist das kein Protokoll, sondern der Handelsname der Rohling-Variante — aber man versteht, was gemeint ist.
Nach dem Schreiben wird das Ergebnis genauso detailliert angezeigt:

![Schreibergebnis](/img/remote/3ca59457a78dad5b.png)

::: tip In der aktuellen Firmware
- Welche Chips probiert werden, ist einstellbar: `125 kHz RFID → Settings → Write Chips` — T5577, EM4305, 8265, 8210,
  H5.5 (alle ON) und **8268** (ID8268 / Hitag-S-Magic-Chip, standardmäßig OFF). Schalte ab, was du nicht brauchst,
  dann geht das Schreiben schneller.
- Das Ziel 8268 schreibt nur EM4100 mit RF/64 und muss man selbst einschalten, weil es auf einem echten Hitag S
  Nutzerdaten überschreiben würde.
- Das Format des Schreibbildschirms ist `[Protocol]`, Dateiname, `(chip)`; **Success!** zeigt den Chip, der die
  Daten angenommen hat. Details: [Auf Rohlinge schreiben](/de/rfid/write).
:::

## Einen T5577 in den Werkszustand wipen

Eine Funktion, die @gromovyna auf dem Flipper lange gefehlt hat: einen T5577 in den Leerzustand zurücksetzen. Ein
früherer Versuch, sie zu Unleashed hinzuzufügen, war blockiert worden; später wurden Funktionen wie *T5577-Passwort
löschen* mit denselben architektonischen Problemen gemerged, eine saubere Lösung müsste also global ansetzen.

Verhalten (wie bei Proxmark3):

- vor dem Start wirst du gewarnt, dass **alle Daten gelöscht werden** und das Tag von Read **nicht mehr lesbar** ist,
  bis du neue Daten darauf schreibst;
- der Wipe **entfernt kein Passwort** — ist das Tag geschützt, lösche das Passwort zuerst mit der dafür gedachten
  Funktion;
- es gibt einen Fortschrittsbalken. Die meiste Zeit geht nicht in den Wipe selbst, sondern in dessen
  **Verifikation**: Wegen der LF-API prüft der Flipper, ob das Tag leer ist, indem er es zu lesen versucht und
  erwartet, dass dieser Lesevorgang fehlschlägt;
- am Ende erscheint eine Erfolgs- oder Fehlermeldung.

![Warnung vor dem Wipe](/img/remote/f5ed0aa91bfcae98.png)

![Laufender Wipe](/img/remote/153b85d1fede96d9.png)

![Verifikation](/img/remote/0f2f4e240a35940d.png)

![Erfolg](/img/remote/312494f343dd8b21.png)

::: tip Unleashed — wo es jetzt steckt
Im Artikel lag der Wipe noch unter `125 kHz RFID → Extra Actions`. In der aktuellen Firmware sind er (und Clear
Password) in die mitgelieferte **T5577**-App gewandert: `Apps → RFID → T5577 → Wipe Tag`. Die Warnung lautet
*Wipe T5577 — Erases all data. The tag stops working as a key. Hold still while running*; das Ergebnis ist
**Wiped!** oder **Not wiped** (z. B. *No answer. Protected? Try Clear Password*). Der Wipe schreibt genullte
Datenblöcke und eine Standardkonfiguration, die T5577-App kann den Chip danach also weiterhin lesen. Siehe
[T5577-App](/de/rfid/t5577-app).
:::

## „Das ist doch nur vibe-coded!"

Nach den Worten des Autors war das ein Experiment: Kann man für solche Systeme mit einem LLM ordentlichen Code
schreiben? Der Prozess war penibel: Datenblätter, der Code der Unleashed-Firmware, um die Architektur zu verstehen,
der Proxmark3-Code. Jeder Schritt wurde validiert, auf echter Hardware getestet und feinjustiert. Die Funktionen sind
also *geschrieben von Claude Code*, aber *erschaffen von @gromovyna*.

## Pull Requests

- [[RFID]: Support of Hitag Micro chips (8265/8210/H5.5)](https://github.com/DarkFlippers/unleashed-firmware/pull/1002)
- [[RFID]: Wipe T5577 (reset to blank, with read-back verification)](https://github.com/DarkFlippers/unleashed-firmware/pull/1003)

Weitere Artikel und Forschung: [@gromovyna](https://t.me/gromovyna).

## Verwandte Seiten

- [Auf Rohlinge schreiben](/de/rfid/write) · [T5577-App](/de/rfid/t5577-app) · [Protokolle](/de/rfid/protocols)
