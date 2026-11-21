---
title: Nice-O-Code-App
order: 170
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/nice_o_code, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzSupportedSystems.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-docs, unleashed-readme]
---
# Nice-O-Code-App

**Nice O-Code** (von @xMasterX) rechnet den 16-Bit-**Installationscode (IC)** einer Nice-O-Code-Fernbedienung zurück und speichert die Fernbedienung als `.sub`-Datei — entweder als einfachen Klon oder als **neue Fernbedienung** derselben Anlage, die du im Empfänger anlernen kannst.

## Hintergrund

Nice O-Code ist Nice FloR-S, verschlüsselt mit einem Installationscode — einem Wert, den alle Fernbedienungen einer Anlage teilen. Der Empfänger akzeptiert nur eine Fernbedienung, die seinen Installationscode trägt. Ein einzelner mitgeschnittener Tastendruck genügt nicht, um ihn zu finden, aber **vier oder mehr Tastendrücke** derselben Fernbedienung genügen: nur mit dem richtigen Code dekodiert jeder Druck zur gleichen Seriennummer. Die App sammelt Tastendrücke und probiert alle 65 536 Codes auf dem Flipper durch.

Manche O-Code-Fernbedienungen tragen außerdem das **Zertifikat** des Empfängers (ein längeres 112-Bit-Paket, das nur während der ersten zwanzig Nutzungen der Fernbedienung gesendet wird). Sieht die App eines, demaskiert sie es, sobald der IC bekannt ist, und zeigt es als `Cert`.

::: tip Unleashed
Nice O-Code ist eine eingebaute Systemapp von Unleashed, und die Sub-GHz-App kann O-Code-Fernbedienungen dekodieren und senden, sobald eine Datei den IC enthält. `Add Manually` hat die passenden Einträge `Nice O-Code`, `Nice O-Code One` und `Nice O-Code+Crt` — siehe [Add Manually](/de/subghz/add-manually) und [Neue Fernbedienung anlernen](/de/subghz/remote-prog).
:::

::: warning
Nutze es nur mit deiner eigenen Anlage. Ein Klon teilt den Zähler mit der Originalfernbedienung, und beide werden sich darum streiten (siehe [Rolling Codes](/de/subghz/rolling-codes)).
:::

## Voraussetzungen

- Die Nice-FloR-S-Schlüsseldatei `/ext/subghz/assets/nice_flor_s` auf der SD-Karte (sie wird mit der Firmware ausgeliefert). Ohne sie meldet die App `No rainbow table`.
- Eine funktionierende O-Code-Fernbedienung der Anlage. Die App hört auf **433,92 MHz AM650**, mit dem internen oder einem [externen](/de/subghz/external-cc1101) Funkmodul (`Int` / `Ext` in der Kopfzeile).

## Eine Fernbedienung mitschneiden

1. Öffne `Main Menu → Apps → Sub-GHz → Nice O-Code`.
2. Wähle `Capture remote`. Der Status zeigt `Listening 433.92`.
3. Drücke die Taste der Fernbedienung **4-mal oder öfter — kurze Drücke, nicht halten**. Jeder neue Druck zeigt `Press N: …`; die Zeile `Presses n/4  Xpkt` und der Fortschrittsbalken füllen sich. Hat die Fernbedienung ein Zertifikat, endet die Zeile mit `+Crt`.
4. Sind 4 Drücke gesammelt, erscheint `Solve` — drücke <kbd>OK</kbd>.
5. Der Bildschirm zeigt `Trying installer codes` mit einem Zähler bis 65536. <kbd>←</kbd> (`Cancel`) bricht ab.
6. Bei Erfolg siehst du `IC XXXX`, `Serial XXXXXXX` und, falls vorhanden, `Cert XXXXXX`.

Statusmeldungen, die beim Mitschneiden erscheinen können:

| Status | Bedeutung |
|---|---|
| `Not O-Code, ignored` | ein Paket, das kein O-Code ist (z. B. eine einfache FloR-S-Fernbedienung) |
| `Same press, ignored` | eine Wiederholung eines bereits gespeicherten Tastendrucks |
| `Need 4+ packets` | zu wenige Tastendrücke zum Lösen |
| `Ambiguous, capture more` | mehrere Codes passen — drücke die Fernbedienung noch ein paar Mal und löse erneut |
| `No code fits, not O-Code?` | kein Installationscode passt — wohl keine O-Code-Fernbedienung, oder es wurden Tastendrücke verschiedener Fernbedienungen gemischt |

## Speichern

Auf dem Ergebnisbildschirm:

- <kbd>OK</kbd> (`Save`) — ein **Klon** der mitgeschnittenen Fernbedienung (Standardname `NiceO`). Nützlich für Tests, streitet sich aber mit deinem Original um den Zähler.
- <kbd>→</kbd> (`New`) — eine **neue Fernbedienung**: derselbe Installationscode, dieselbe Taste und dasselbe Zertifikat, aber mit eigener Seriennummer und eigenem Zähler (Standardname `NiceO_new`). Diese lernst du im Empfänger an. Der Zähler wird nah an den Stand deiner funktionierenden Fernbedienung gesetzt, etwas darunter.

Beide werden nach der Namenseingabe (`Name the .sub file`) in `/ext/subghz/` geschrieben. Öffne sie unter `Sub-GHz → Saved`.

Um die neue Fernbedienung anzulernen, folge dem Vorgehen für Nice FloR-S unter [Neue Fernbedienung anlernen](/de/subghz/remote-prog). Eine Fernbedienung mit Zertifikat lernt sich selbst an: drücke ihre Taste etwa einmal pro Sekunde, **10–15 Mal in einem Durchgang** — das Tor öffnet um den zehnten Druck herum.

## Decode RAW file

`Decode RAW file` führt dieselbe Rückrechnung auf einer RAW-`.sub` durch, die du vorher mit
[Read RAW](/de/subghz/read-raw) aufgenommen hast (nimm 4 oder mehr einzelne Tastendrücke auf). Eine Schlüsseldatei wird mit `Not a RAW capture` abgewiesen. Der Fortschrittsbalken zeigt, wie weit sie in der Datei ist.

## Fehlersuche

- **`No rainbow table`** — `/ext/subghz/assets/nice_flor_s` fehlt; installiere die Firmware mit eingelegter SD-Karte neu oder stelle den `assets`-Ordner wieder her.
- **Die Tastendrücke werden nicht gezählt** — mache einzelne kurze Drücke; die Taste zu halten wiederholt denselben Druck.
- **Ein Empfänger im Werkszustand ignoriert die O-Code-Fernbedienung** — ein unangetasteter Empfänger hat keinen Installationscode; lerne dort an der Taste stattdessen eine einfache `Nice One`- / `Nice FloR-S`-Fernbedienung an (siehe [Neue Fernbedienung anlernen](/de/subghz/remote-prog)).
- **Der Empfänger weist die neue Fernbedienung ab** — halte den Zähler nah am Stand deiner funktionierenden Fernbedienung; setze ihn nicht auf null zurück.

## Verwandte Seiten

- [Neue Fernbedienung anlernen](/de/subghz/remote-prog) · [Add Manually](/de/subghz/add-manually)
- [Rolling Codes](/de/subghz/rolling-codes) · [Unterstützte Systeme](/de/subghz/supported-systems)
