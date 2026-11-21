---
title: Rolling Codes
order: 60
original: [https://t.me/how2flipper_rus/7, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/SubGHzRemoteProg.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/lib/subghz]
sources: [how2flipper, unleashed-docs, unleashed-readme, unleashed-src]
---
# Rolling Codes

Sub-GHz-Fernbedienungen gibt es in zwei Sorten:

- **Statischer (fester) Code** — jeder Tastendruck sendet genau dasselbe Paket (Princeton, CAME 12/24 Bit,
  Nice Flo, Marantec, Roger, Gate TX …). Eine Kopie ist mit dem Original identisch; beide funktionieren dauerhaft,
  in beliebiger Reihenfolge. Einfach [Read](/de/subghz/read) und speichern.
- **Rolling Code (dynamischer Code)** — jeder Tastendruck sendet ein neues Paket, gebildet aus einem **Zähler**,
  der mit jedem Druck um eins wächst (KeeLoq, FAAC SLH, Nice FloR-S, CAME Atomo, Somfy, Security+,
  Alutech AT-4N …). Der Zähler ist meist verschlüsselt, der nächste Code lässt sich also nur berechnen, wenn die
  Firmware den Schlüssel des Protokolls kennt.

::: tip Unleashed
Unleashed kann viele Rolling-Code-Protokolle dekodieren, speichern **und senden**, mit
[Add Manually](/de/subghz/add-manually) neue Fernbedienungen dafür anlegen, die anderen Tasten der Fernbedienung
über die Pfeiltasten senden ([eigene Tasten](#custom-buttons)) und einstellen, wie der Zähler hochgezählt wird
([Counter Incr.](#counter-increment), [Zählermodi](/de/subghz/counter-mode)). Die Stock-Firmware dekodiert die
meisten davon, sendet sie aber nicht.
:::

## Wie der Empfänger den Zähler prüft

Der Empfänger speichert den letzten Zähler, den er akzeptiert hat, **für jede Fernbedienung** (ein Wert pro
Fernbedienung, nicht pro Taste):

- Zähler **gleich dem erwarteten nächsten / innerhalb des Vorwärtsfensters** → akzeptiert, das Tor öffnet;
- Zähler **weit voraus** → viele Empfänger synchronisieren neu: der erste Druck wird gespeichert, der nächste
  darauffolgende funktioniert;
- Zähler **hinter** dem gespeicherten Wert → ignoriert. Manche Empfänger entkoppeln eine Fernbedienung nach
  wiederholten „alten" Codes.

## Der Zählerkonflikt

*Warum kann man die eigene Rolling-Code-Fernbedienung nicht einfach in Read einfangen und vom Flipper aus nutzen?*
(nach [@how2flipper_rus](https://t.me/how2flipper_rus/7))

Stell dir vor:

1. Du drückst die Originalfernbedienung — sie sendet Zähler `0002`.
2. Du hast dieses Signal auf dem Flipper gespeichert; wenn du es sendest, sendet der Flipper `0003`.
3. Der Empfänger denkt, du hättest einfach wieder das Original gedrückt, und öffnet.
4. Aber die Originalfernbedienung steht noch auf `0002`; ihr nächster Druck ist `0003` — ein Wert, den der
   Empfänger schon gesehen hat, also **öffnet er nicht**.

Keine Panik — die Fernbedienung ist nicht entkoppelt. Drücke sie noch einmal: `0004` überholt den Flipper und das
Original funktioniert wieder. Solche „Rennen" können die Zähler aber mehr als 100 Tastendrücke auseinandertreiben,
und dann lässt sich das Original nicht zurückholen, ohne es am Empfänger neu anzulernen.

Wege heraus:

- **Am besten: eine neue Fernbedienung anlegen** auf dem Flipper (`Sub-GHz → Add Manually`) und im Empfänger
  anlernen. Sie hat eine eigene Seriennummer und einen eigenen Zähler und kollidiert nie mit den Originalen. Siehe
  [Fernbedienung anlernen](/de/subghz/remote-prog).
- Entscheide dich, welche du nutzt — den Flipper **oder** das Original — und nutze nur diese eine.
- Nutze beide, lass die Zähler aber nie weit auseinanderlaufen (drücke diejenige mehrmals, die hinterherhinkt).
- Experimentell: spezielle [Zählermodi](/de/subghz/counter-mode) erlauben bei manchen Empfängern, dass Klon und
  Original nebeneinander bestehen.

::: danger Autos
Klone nicht den Funkschlüssel eines Autos. Ihn wieder abzuspielen (auch über Read RAW) kann den Schlüssel
desynchronisieren oder sperren, und das erneute Anlernen braucht oft Werkstattwerkzeug.
:::

## Eigene Tasten {#custom-buttons}

Wenn eine unterstützte Rolling-Code-Datei (oder manche statische) in `Emulate` geöffnet ist:

- <kbd>OK</kbd> (`Send`) sendet die Taste, die aufgenommen bzw. erzeugt wurde;
- <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> senden, solange sie gehalten werden, **andere Tastencodes**
  derselben Fernbedienung mit korrekt erhöhtem Zähler. Der ursprüngliche Tastencode steht als kleine Hex-Ziffer
  rechts auf dem Bildschirm, solange eine Pfeiltaste benutzt wird.

Welche Pfeiltaste welcher Taste entspricht, hängt vom Protokoll ab; versteckte bzw. Programmiertasten (z. B. `0xF`
bei BFT Mitto, `Prog` bei Somfy) sind auf diesem Weg ebenfalls erreichbar — die vollständige Tabelle steht unter
[Fernbedienung anlernen](/de/subghz/remote-prog) (Referenz der versteckten Tasten).

Protokolle mit eigenen Tasten in der aktuellen Firmware (Zahl = wie viele zusätzliche Codes die Pfeiltasten senden
können):

| Protokoll | Zusätzlich | Protokoll | Zusätzlich |
|---|---|---|---|
| KeeLoq (alle `KL:`-Hersteller) | 4 | Nice FloR-S / Nice One / O-Code | 4 |
| Alutech AT-4N | 4 | CAME Atomo | 4 |
| Security+ 2.0 | 4 | V2 Phoenix | 4 |
| Ditec GOL4 | 4 | Dooya | 4 |
| Princeton | 4 | Somfy Telis | 3 |
| Jarolift | 3 | KingGates Stylo 4k | 3 |
| Prastel | 3 | BelKorn | 3 |
| Roger | 3 | Nord ICE | 3 |
| Proteco | 3 | GangQi | 3 |
| Hollarm | 3 | Beninca ARC | 2 |
| Hay21 | 2 | FAAC SLH / Genius | 1 (Programmierung) |
| Somfy Keytis | 1 (`Prog`) | | |

## Zählerschrittweite {#counter-increment}

`Sub-GHz → Radio Settings → Counter Incr.` legt fest, um wie viel der Zähler pro Sendung wächst: `+1` (Standard),
`+2`, `+3`. Mit aktivem **Debug-Modus** (`Settings → System → Debug`) wächst die Liste auf `+4`, `+5`, `+10`,
`+50`, `OVFL`, `OFEX`, `No`, `-1` … `-50` — Werkzeuge für die Protokollentwicklung; nutze sie nicht an einer echten
Anlage. Siehe [Einstellungen](/de/subghz/settings).

## Eine neue Fernbedienung im Empfänger anlernen

Der normale, konfliktfreie Weg, den Flipper an einem Rolling-Code-Tor zu nutzen:

1. Lies deine Originalfernbedienung (`Sub-GHz → Read`), um Protokoll, Frequenz und Modulation zu erfahren.
2. `Sub-GHz → Add Manually` → dein System → dasselbe Band → speichern.
3. Versetze den Empfänger in den Anlernmodus (Taste auf der Platine oder von einer funktionierenden Fernbedienung
   aus — der Flipper sendet die versteckte „Programmier"-Taste mit einer Pfeiltaste).
4. Öffne die neue Datei und halte <kbd>OK</kbd>.

Vorgehen je Hersteller: **[Flipper als neue Fernbedienung](/de/subghz/remote-prog)**.

## Fehlersuche

- **Hat einmal funktioniert, dann nicht mehr** — du nutzt einen Klon. Drücke mehrmals hintereinander, um neu zu
  synchronisieren, oder lege stattdessen eine neue Fernbedienung an.
- **Die Originalfernbedienung funktioniert nicht mehr** — der Flipper ist vorausgelaufen. Drücke das Original
  mehrmals; ist der Abstand zu groß, lerne es am Empfänger neu an.
- **Die Pfeiltasten tun nichts** — das Protokoll hat keine eigenen Tasten, oder die Datei ist statisch ohne
  Tastenfeld.
- **`KL: Unknown` nach dem Read** — der Herstellerschlüssel ist unbekannt; das Signal kann nicht gesendet werden.
  Siehe [KeeLoq](/de/subghz/keeloq).

::: warning
Nutze diese Funktionen nur mit deiner eigenen Technik oder mit Erlaubnis des Eigentümers.
:::

## Verwandte Seiten

- [Add Manually](/de/subghz/add-manually) · [Fernbedienung anlernen](/de/subghz/remote-prog)
- [KeeLoq](/de/subghz/keeloq) · [Zählermodi](/de/subghz/counter-mode)
- [Unterstützte Systeme](/de/subghz/supported-systems)
