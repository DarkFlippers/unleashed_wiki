---
title: Security+ PIN
order: 180
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/secplus_pin, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Security+ PIN

**Security+ PIN** (von @xMasterX) arbeitet mit einem mitgeschnittenen Signal eines **Security+ 2.0 Keypads** — dem 86-Bit-Paket, das Funktastaturen von Chamberlain / LiftMaster senden. Der PIN der Tastatur steckt in diesem Paket. Die App lässt dich einen PIN von Hand setzen oder `0000`–`9999` durchlaufen, sendet jeden Kandidaten und schreibt den PIN in die Datei zurück, sobald du den richtigen gefunden hast.

::: tip Unleashed
Security+ 2.0 Keypad (86 Bit, 315 / 390 / 868 MHz) wird von der Sub-GHz-App von Unleashed dekodiert, und diese eingebaute Systemapp bearbeitet dessen PIN. Normale 62-Bit-Fernbedienungen für Security+ 2.0 sind keine Keypad-Pakete und werden abgewiesen.
:::

::: warning
Nur für deinen eigenen Garagentorantrieb und dein eigenes Keypad.
:::

## Bevor du anfängst

1. Schneide dein Keypad mit `Sub-GHz → Read` auf seiner Frequenz mit (siehe [Read](/de/subghz/read)) und speichere es. Die gespeicherte Datei muss `Security+ 2.0` mit `Bit: 86` zeigen.
2. Die Datei liegt in `/ext/subghz/`.

## Die App benutzen

1. Öffne `Main Menu → Apps → Sub-GHz → Security+ PIN`.
2. Wähle `Open .sub file` und nimm die Keypad-Aufnahme. Ist sie geladen, zeigt der Status die Frequenz und `ready` (z. B. `315MHz  ready`). Enthält die Datei schon einen `Pin`, wird er angezeigt.
3. Die vier PIN-Stellen stehen auf dem Bildschirm, mit einem Rahmen um die aktive Stelle:
   - <kbd>←</kbd> / <kbd>→</kbd> — zwischen den Stellen wechseln
   - <kbd>↑</kbd> / <kbd>↓</kbd> — den PIN ändern
   - <kbd>OK</kbd> (`Send`) — den aktuellen PIN senden (`Sending 1234...` → `Sent 1234`)
   - <kbd>OK</kbd> halten — **Durchlauf**: jeden PIN ab dem aktuellen senden; ein Fortschrittsbalken zeigt `N of 9999`. Kurzes <kbd>OK</kbd> oder <kbd>←</kbd> (Back) hält ihn bei `Stopped at NNNN` an
   - <kbd>←</kbd> halten — den aktuellen PIN in die Datei **speichern** (`Saved PIN NNNN`)
   - <kbd>Back</kbd> — zurück ins Menü

Die Hinweiszeile auf dem Bildschirm fasst es zusammen: `hold OK sweep   < save`.

Das Speichern aktualisiert die geöffnete Datei an ihrem Platz: es schreibt die Felder `Pin`, `Key` und `Secplus_packet_1`. Danach lässt sich die Datei normal aus `Sub-GHz → Saved` senden.

## Meldungen

| Meldung | Bedeutung |
|---|---|
| `Not Security+ 2.0: …` | die Datei ist ein anderes Protokoll |
| `Not an 86-bit keypad` | eine Security+-2.0-Fernbedienung, kein Keypad-Paket |
| `Missing packet 1` / `No Key value` | unvollständige Aufnahme — lies das Keypad erneut |
| `Unsupported preset …` / `Bad custom preset` | das Preset der Datei lässt sich nicht nutzen |
| `NNNMHz TX blocked` / `TX blocked, sweep stopped` | das Senden auf dieser Frequenz ist nicht erlaubt (siehe [Frequenzen](/de/subghz/frequencies)) |
| `TX failed` | das Funkmodul konnte nicht senden |

## Fehlersuche

- **Der Durchlauf ist langsam** — jeder PIN ist eine eigene Sendung mit einer kurzen Pause; ein vollständiger Durchlauf dauert lange. Starte ihn bei einem wahrscheinlichen Wert und stoppe ihn, sobald das Tor reagiert.
- **Das Tor hat reagiert, aber du hast den PIN verpasst** — der Durchlauf stoppt bei der angezeigten Zahl; geh mit <kbd>↓</kbd> zurück und sende einzelne PINs mit <kbd>OK</kbd>, um zu bestätigen, dann halte <kbd>←</kbd> zum Speichern.
- **Die falsche Datei wird abgewiesen** — schneide das Keypad selbst mit, nicht eine Handfernbedienung.

## Verwandte Seiten

- [Read](/de/subghz/read) · [Unterstützte Systeme](/de/subghz/supported-systems)
- [Rolling Codes](/de/subghz/rolling-codes)
