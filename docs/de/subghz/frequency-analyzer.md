---
title: Frequency Analyzer
order: 20
original: [https://t.me/how2flipper_rus/3, https://t.me/how2flipper_rus/4, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz/plugins/frequency_analyzer, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://docs.flipper.net/zero/sub-ghz/read]
sources: [how2flipper, unleashed-src, unleashed-readme, unleashed-docs, flipper-docs]
---
# Frequency Analyzer

Der Frequency Analyzer sagt dir, **auf welcher Frequenz eine Fernbedienung sendet**. Er tastet die Frequenzen der
Sub-GHz-Liste ab, misst die Signalstärke (RSSI) und zeigt die stärkste an. Nimm ihn vor **Read** oder **Read RAW**,
wenn du die Frequenz einer Fernbedienung nicht kennst.

::: tip Unleashed
Unleashed bringt einen überarbeiteten Analyzer mit (ursprünglich von ClusterM): mit einer Historie von vier
Einträgen, einem einstellbaren Trigger, wählbarer Rückmeldung (Ton / Vibration / stumm) und einem **direkten Sprung
nach Read**: kurzes <kbd>OK</kbd> merkt die Frequenz für Read / Read RAW, langes <kbd>OK</kbd> merkt sie und öffnet
Read sofort.
:::

## Die goldene Regel

Der Analyzer ist dafür gedacht, **nur wenige Zentimeter von der Antenne des Flippers entfernt und mit dem internen
Funkmodul** zu arbeiten. Die Antenne sitzt an der linken Seite, neben dem schwarzen IR-Fenster. Seine Einstellungen
sind da, um Rauschen zu filtern, nicht um Signale aus der Ferne einzufangen. Mit einem sehr niedrigen Trigger meldet
der Analyzer nur zufällige Störungen und das Eigenrauschen des Flippers statt deiner Fernbedienung. Um Signale
tatsächlich zu *empfangen*, nimm [Read](/de/subghz/read) und [Read RAW](/de/subghz/read-raw).

::: warning
Der Analyzer mit einem externen Modul ist nicht empfehlenswert: externe Module sind empfindlicher und fangen viel
mehr Rauschen auf.
:::

## Der Bildschirm

![Frequency Analyzer zeigt 433.920 MHz, die Historieneinträge und den RSSI-Balken](/screens/subghz/frequency_analyzer.png)

| Element | Bedeutung |
|---|---|
| Symbol oben rechts | Rückmeldung, wenn ein Signal gefangen wird: Lautsprecher = Vibration + Ton, kleiner Lautsprecher = nur Vibration, durchgestrichen = stumm |
| Große Zahl in der Mitte | Aktuelle (Haupt-)Frequenz. Während ein Signal über dem Trigger empfangen wird, erscheint sie **invertiert in einem schwarzen Kasten** |
| Vier Einträge darunter | Historie: gerundete Frequenz und wie oft sie gefangen wurde (`x3`). Hilft bei schwachen oder driftenden Fernbedienungen |
| `RSSI`-Balken unten | Signalstärke in Echtzeit mit der Triggermarke |
| `T-` / `+T` | Schaltflächen für den Triggerpegel |

## Tasten

| Taste | Aktion |
|---|---|
| <kbd>←</kbd> / <kbd>→</kbd> | Trigger verschieben (von −97 dBm bis −60 dBm, Schrittweite 1 dBm). Links = empfindlicher, rechts = weniger empfindlich |
| <kbd>↑</kbd> | Rückmeldungsmodus durchschalten: Vibration + Ton → stumm → Vibration → … |
| <kbd>↓</kbd> | Einen Eintrag in der Historie auswählen (er wird umrahmt) |
| <kbd>OK</kbd> kurz | Die gewählte Frequenz für Read / Read RAW speichern |
| <kbd>OK</kbd> lang | Die Frequenz speichern und sofort **Read** öffnen |
| <kbd>Back</kbd> | Beenden (Trigger und Rückmeldungsmodus bleiben gespeichert) |

Welche Frequenz <kbd>OK</kbd> übernimmt:

- wird **gerade jetzt** ein Signal empfangen (schwarzer Kasten um die Hauptfrequenz) — diese Frequenz, selbst wenn
  ein Historieneintrag ausgewählt ist;
- wird nichts empfangen und ein Historieneintrag ist ausgewählt — der ausgewählte Eintrag;
- sonst — die letzte Frequenz, die den Trigger überschritten hat, damit du die Fernbedienung nicht gedrückt halten
  musst.

::: warning Rundung
Die gespeicherte Frequenz wird immer **auf die nächste Frequenz in der Liste gerundet**
([Frequenzen](/de/subghz/frequencies)). Liegt deine Fernbedienung weit von allen Standardwerten entfernt, füge ihre
Frequenz in `setting_user` ein. Die große Zahl zeigt dann die echte Frequenz, nach dem Sprung nach Read / Read RAW
musst du sie aber von Hand in `Config` setzen.
:::

Das Speichern einer Frequenz aus dem Analyzer **schaltet außerdem Hopping aus**, damit Read genau auf dieser
Frequenz startet.

## So findest du die Frequenz einer Fernbedienung

1. Geh weg von Schaltnetzteilen, Ladegeräten und anderer störender Elektronik.
2. Öffne `Main Menu → Sub-GHz → Frequency Analyzer`.
3. Halte die Fernbedienung direkt an die linke Seite des Flippers (neben das schwarze Fenster).
4. Drücke und halte eine Taste auf der Fernbedienung. Die Hauptfrequenz wird invertiert, solange das Signal
   empfangen wird.
5. Lass die Taste los und warte, bis die Frequenz in der Historie landet.
6. Drücke <kbd>OK</kbd>, um sie zu merken, oder halte <kbd>OK</kbd>, um direkt nach **Read** zu gehen.

Die meisten Fernbedienungen senden um 315, 433,92 oder 868,35 MHz. Probiere in Read trotzdem mehrere Modulationen
aus, wenn nichts dekodiert wird (zuerst `AM650`, dann `FM238`, `FM476`, `FM12K`).

## Den Trigger einstellen

Standardmäßig liegt der Trigger bei −93 dBm, eine Position, die in den meisten Fällen passt — normalerweise fasst
du sie also nicht an. Stelle ihn nur nach, wenn die Fernbedienung selbst auf Nulldistanz nicht erkannt wird oder
wenn es viel Rauschen gibt:

1. Verschiebe die Marke, ohne eine Taste der Fernbedienung zu drücken, mit <kbd>←</kbd> / <kbd>→</kbd>, bis der
   Flipper gar nichts mehr fängt (kein Rauschen, keine Zufallstreffer). Die Position ganz links ist die
   empfindlichste — sie fängt Signale *und* das Eigenrauschen des Flippers samt aller Störungen auf; die Position
   ganz rechts ist für beides am unempfindlichsten.
2. Halte die Fernbedienung an die linke Kante des Flippers und drücke ihre Taste.
3. Wird nichts gefangen, verschiebe den Trigger Schritt für Schritt nach **links**, bis das Signal erscheint.
4. Drücke die Taste der Fernbedienung beim Einstellen immer wieder und lass sie los — ein unterbrochenes Signal
   macht es leichter, die richtige Position zu finden, als ein durchgehendes.

## Fehlersuche

- **Es erscheinen ständig zufällige Frequenzen** — Trigger zu niedrig oder Rauschen in der Nähe. Verschiebe ihn
  nach rechts, geh weg von Netzteilen.
- **Die Fernbedienung wird nie gefangen** — halte sie näher, prüfe die Batterie, verschiebe den Trigger nach links.
  Manche Fernbedienungen senden sehr kurze Bursts: drücke mehrmals.
- **Read zeigt auf der gefundenen Frequenz nichts** — falsche Modulation. Ändere sie in `Read → Config`. Wird
  nichts dekodiert, nimm es mit [Read RAW](/de/subghz/read-raw) auf.
- **Die Frequenz weicht von der Aufschrift auf der Fernbedienung ab** — normal; billige Fernbedienungen driften.
  Nimm die Zähler in der Historie, um den häufigsten Wert zu wählen.

## Verwandte Seiten

- [Frequenzen](/de/subghz/frequencies) · [Read](/de/subghz/read) · [Read RAW](/de/subghz/read-raw)
- [Remote Analyzer](/de/subghz/remote-analyzer) — eine App mit eigenem Analyzer, die immer nur eine Fernbedienung dekodiert
