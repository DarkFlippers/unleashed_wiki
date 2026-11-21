---
title: Seed Capturer
order: 190
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/seed_capturer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Seed Capturer

**FAAC SLH**, **Genius**, **Erreka** und **BFT Mitto** bauen ihren Rolling Code aus einem geheimen **Seed**. Ohne ihn kann der Flipper diese Fernbedienungen nicht dekodieren (sie werden als `KL: Unknown` oder gar nicht gelesen) und keine Fernbedienung bauen, die der Empfänger akzeptiert. **Seed Capturer** (von @xMasterX) sammelt das Rohmaterial, um den Seed zurückzurechnen: den `Fix` der Fernbedienung und eine Folge aufeinanderfolgender `Hop`-Werte.

Er rechnet den Seed **nicht** selbst zurück und **sendet nie** — er hört nur zu und schreibt eine Datei. Die Suche läuft in der Begleit-App [qUnleashed](/de/mobile/qunleashed-app).

::: tip Unleashed
Seed Capturer ist eine eingebaute Unleashed-Systemapp, und qUnleashed liest seine Aufnahmen direkt vom Flipper. Ist der Seed bekannt, kann Unleashed die Fernbedienung dekodieren und über `Add Manually [Advanced]` neue anlegen.
:::

## Wann du ihn brauchst

- Die Funkprogrammierung des Empfängers ist deaktiviert, der einzige Weg hinein ist also ein Klon einer bekannten Fernbedienung — und ein Klon braucht den Seed.
- Deine FAAC-/Genius-Fernbedienung ist ein **Slave** und kann den Programmiercode nicht senden.
- Du kommst nicht an den Empfänger heran.
- **Erreka**-Anlagen, in denen alle Fernbedienungen einen Seed teilen.
- **Ältere BFT-Mitto**-Fernbedienungen mit einmaligem Seed, wenn der Weg über die Programmiertaste nicht funktioniert (neuere BFT-Fernbedienungen leiten den Seed aus der Seriennummer ab und werden in einem normalen Read dekodiert).

Lässt sich die Fernbedienung in den Programmiermodus versetzen, wird der Seed oft im Klartext gesendet — dieser Weg ist schneller; siehe [Neue Fernbedienung anlernen](/de/subghz/remote-prog).

## Mitschneiden

1. Öffne `Main Menu → Apps → Sub-GHz → Seed Capturer`.
2. Wähle `New capture`.
3. **Fernbedienungstyp:** `FAAC SLH`, `Genius`, `Erreka` oder `BFT Mitto`.
4. **Frequenz:** `433.92 MHz  AM650` oder `868.35 MHz  AM650` (`BFT Mitto` bietet nur 433.92 MHz).
5. Drücke **dieselbe Taste derselben Fernbedienung** immer wieder, etwa einmal pro Sekunde, mit der Fernbedienung direkt neben dem Flipper.
6. Beobachte den Bildschirm:
   - `Fix XXXXXXXX` — der feste Teil der Fernbedienung; die App rastet auf den ersten ein, den sie hört;
   - `Hops n/10  Xpkt` — wie viele **verschiedene** Hops gesammelt sind und die Zahl der rohen Pakete;
   - Status `Hop n: XXXXXXXX` jedes Mal, wenn ein neuer landet.
7. Ab **2 Hops** erscheint `Save` auf <kbd>OK</kbd>. Drücke es; die App zeigt `Saved N hops` und den Dateinamen.

<kbd>←</kbd> (`Reset`) verwirft die Aufnahme, damit du auf eine andere Fernbedienung oder Taste einrasten kannst.

| Status | Bedeutung |
|---|---|
| `Hop n: XXXXXXXX` | neuer rollierender Teil gespeichert — drücke weiter |
| `Other remote XXXXXXXX` | eine andere Fernbedienung oder eine andere Taste — ignoriert |
| `Same hop, ignored` | eine Wiederholung des letzten Drucks |
| `Have 10, enough` | voll — drücke `Save` |

**Wie viele Tastendrücke:** 2 ist das Minimum, 5–10 sind besser. Genauso wichtig: die Drücke müssen **aufeinanderfolgen, ohne dass einer verloren geht** — prüfe, dass `Hops` bei jedem Druck steigt. Geht einer verloren, drücke `Reset` und fang neu an.

::: warning
Bei **FAAC SLH und Genius ist der Seed für jede Taste anders** — schneide die Taste mit, die du wirklich nutzen willst. Bei Erreka gilt der Seed pro Fernbedienung (manchmal pro Anlage), bei BFT Mitto pro Fernbedienung.
:::

## Weitere Menüpunkte

- `Decode RAW file` — Fix/Hops aus einer RAW-`.sub` (aus `/ext/subghz`) holen, die du vorher mit [Read RAW](/de/subghz/read-raw) aufgenommen hast; die Frequenz kommt aus der Datei. Eine Schlüsseldatei wird mit `Not a RAW capture` abgewiesen. Hier ist <kbd>←</kbd> `Back` statt `Reset`.
- `Delete all captures` — fragt `Delete every capture file in subghz_seed_captures?` und löscht sie dann.
- `Exit`.

## Die Aufnahmedatei

Die Dateien landen in `/ext/apps_data/subghz_seed_captures/` und heißen `<Typ>_<Fix>_<Datum-Uhrzeit>.txt`, z. B. `Erreka_F00F1C9B_261008-142233.txt`. Es ist eine Textdatei, **keine abspielbare `.sub`**:

```text
Filetype: Flipper SubGhz Seed Capture
Version: 1
# Fix + Hop set for offline seed recovery, not a playable .sub
Received: 2026-10-08 14:22:33
Manufacturer: Erreka
Protocol: KeeLoq
Frequency: 433920000
Preset: FuriHalSubGhzPresetOok650Async
Fix: F00F1C9B
Hops: 3
# Hops in the order they were received
Hop: ...
Hop: ...
Hop: ...
```

## Den Seed in qUnleashed zurückrechnen

1. Verbinde den Flipper mit **qUnleashed** und öffne dort das Werkzeug zur Seed-Rückrechnung. Es holt die Aufnahmen selbst aus `subghz_seed_captures` — kein Kopieren, kein Umbenennen.
2. Wähle die Aufnahme und starte die Suche (eine Brute-Force-Suche, weshalb sie nicht auf dem Flipper läuft).
3. Wird der Seed gefunden, kann qUnleashed die fertige Klon-`.sub` zusammenbauen (Seriennummer und Taste aus `Fix`, dazu Seed und Zähler) und auf den Flipper legen.
4. Wird nichts gefunden, hatte die Aufnahme höchstwahrscheinlich eine Lücke — schneide sie noch einmal sorgfältig mit.

Mit dem Seed kannst du Fernbedienungen auch von Hand in `Sub-GHz → Add Manually [Advanced]` bauen: eine eigene `SERIAL` + den `SEED` für eine neue Fernbedienung, oder `SERIAL`/`BUTTON` des Originals + `SEED` + einen leicht höheren `COUNTER` für einen Klon. Ein Klon streitet sich mit dem Original um den Zähler — siehe [Rolling Codes](/de/subghz/rolling-codes).

::: warning
Nur für Fernbedienungen und Empfänger, die dir gehören.
:::

## Verwandte Seiten

- [Neue Fernbedienung anlernen](/de/subghz/remote-prog) · [KeeLoq](/de/subghz/keeloq) · [Add Manually](/de/subghz/add-manually)
- [Die qUnleashed-App](/de/mobile/qunleashed-app)
