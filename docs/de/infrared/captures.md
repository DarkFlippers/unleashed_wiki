---
title: Aufnahmen beitragen
order: 40
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/InfraredCaptures.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-docs, flipper-docs, unleashed-readme, unleashed-src]
---
# IR-Aufnahmen zu den Universalfernbedienungen beitragen

Wenn eine [Universalfernbedienung](/de/infrared/universal-remotes) mit deinem Gerät nicht funktioniert, kannst du
deine Originalfernbedienung aufnehmen und zur Bibliothek beitragen, damit sie für alle funktioniert. Diese Seite
erklärt, wie man **saubere** Aufnahmen macht: kurz, möglichst dekodiert und genau so benannt, wie die
Universalfernbedienung es erwartet.

Die Methode ist die Unleashed-Anleitung von **@amec0e** (der die IR-Assets von Unleashed pflegt), aufbauend auf der
ursprünglichen *UniversalRemotes*-Dokumentation von @gsurkov, @skotopes, @knrn-ai, @DrZlo13 und @ahumeniy.

## Tastennamen je Bibliothek {#button-names-per-library}

Die Universalfernbedienung verwendet nur Signale, deren `name:` genau einer ihrer Tasten entspricht (Groß-/
Kleinschreibung zählt). Jede davon kann weggelassen werden, wenn dein Gerät sie nicht hat.

| Bibliothek | Datei | Signalnamen |
|---|---|---|
| TVs | `tv.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Ch_next`, `Ch_prev` |
| Audio | `audio.ir` | `Power`, `Mute`, `Play`, `Pause`, `Prev`, `Next`, `Vol_up`, `Vol_dn` |
| Projectors | `projectors.ir` | `Power`, `Mute`, `Vol_up`, `Vol_dn`, `Play`, `Pause` |
| LEDs | `leds.ir` | `Power_on`, `Power_off`, `Brightness_up`, `Brightness_dn`, `Red`, `Green`, `Blue`, `White` |
| Fans | `fans.ir` | `Power`, `Mode`, `Speed_up`, `Speed_dn`, `Rotate`, `Timer` |
| ACs | `ac.ir` | `Off`, `Dh`, `Cool_hi`, `Cool_lo`, `Heat_hi`, `Heat_lo` |

Auf vielen Audio-Fernbedienungen sind `Play` und `Pause` dieselbe Taste: nimm sie als `Play` auf und lass `Pause` weg.

## Fernseher, Audio, Projektoren, Ventilatoren, LEDs

1. Richte die Fernbedienung auf den IR-Empfänger des Flippers.
2. Starte für die erste Taste `Infrared → Learn New Remote`, für die weiteren wähle in der Fernbedienung `+`.
3. Drücke die Taste der Fernbedienung **kurz** und speichere sie unter dem passenden Namen aus der Tabelle oben.
4. Wiederhole die Schritte 2-3 für alle Tasten.
5. Teste jede gespeicherte Taste am echten Gerät: jede muss tun, was ihr Name sagt.

::: warning Halte die Taste nicht
Wenn du die Taste der Fernbedienung hältst, entstehen lange Aufnahmen mit vielen Wiederholungen. Sie brauchen länger
zum Senden und bremsen die ganze Universalfernbedienung — für alle.
:::

### Parsed oder RAW

**Parsed** ist das beste Ergebnis: das Protokoll wurde erkannt und es werden nur Protokoll, Adresse und Befehl
gespeichert.

```text
name: EXAMPLE
type: parsed
protocol: NEC
address: 07 00 00 00
command: 02 00 00 00
```

Störungen durch andere Geräte in der Umgebung (Lampen, TV-Hintergrundbeleuchtung, andere Fernbedienungen) können eine
Aufnahme in **RAW** kippen, selbst wenn das Protokoll bekannt ist. Hast du bei einer gewöhnlichen Fernbedienung RAW
bekommen, drücke am Flipper einige Male **Retry**, bis eine saubere geparste Aufnahme dabei ist.

**RAW** ist in Ordnung, wenn die Fernbedienung wirklich ein unbekanntes Protokoll benutzt. Ziel ist die *kleinste
Anzahl Samples*, die am Gerät noch funktioniert: ein kurzer Druck, typischerweise **rund 100 Samples**. Eine ideale
Aufnahme eines einzelnen Drucks sieht so aus:

```text
name: EXAMPLE
type: raw
frequency: 38000
duty_cycle: 0.330000
data: 2410 597 1189 599 592 600 1186 602 589 603 1183 606 595 597 593 598 1208 605 596 596 594 597 593 599 592 25604 2403 604 1182 606 595 597 1189 599 591 601 1185 603 618 573 617 575 1211 602 588 603 588 605 596 596 594 25605 2402 604 1192 596 594 597 1189 599 592 601 1185 628 593 598 593 600 1186 602 589 603 588 604 597 595 596
```

## Klimaanlagen {#air-conditioners}

Klimaanlagen-Fernbedienungen sind anders: die Fernbedienung führt den Zustand (Modus, Temperatur, Lüfter, Lamellen)
auf ihrem Display selbst mit, und jeder Druck sendet **den ganzen Zustand** auf einmal. Jede AC-„Taste" ist also in
Wahrheit ein kompletter Zustand, der als Ganzes aufgenommen werden muss.

Für jedes Signal **außer `Off`**:

1. Drücke **Power** auf der Fernbedienung, sodass ihr Display die Klimaanlage als EIN anzeigt.
2. Stelle Modus und Temperatur nach der Tabelle unten ein. Lass alles andere (Lüfterstufe, Lamellen) möglichst auf
   **AUTO**.
3. Drücke **Power** auf der Fernbedienung, um sie auf AUS zu stellen.
4. Starte am Flipper das Anlernen (`Learn New Remote` beim ersten, `+` bei den weiteren).
5. Richte die Fernbedienung auf den Flipper und drücke noch einmal **Power** (das ist der Frame „in diesem Modus
   einschalten").
6. Speichere das Signal unter dem Namen aus der Tabelle.
7. Wiederhole das für jede Zeile.

| Signal | Modus | Temperatur | Hinweis |
|:---:|:---:|:---:|---|
| `Dh` | Entfeuchten | entfällt | |
| `Cool_hi` | Kühlen | niedrigste | niedrigste im Kühlmodus verfügbare Temperatur |
| `Cool_lo` | Kühlen | 23 °C | |
| `Heat_hi` | Heizen | höchste | höchste im Heizmodus verfügbare Temperatur |
| `Heat_lo` | Heizen | 23 °C | |

Danach nimm **`Off`** auf:

1. Achte darauf, dass das Display der Fernbedienung die Klimaanlage als EIN anzeigt.
2. Starte am Flipper das Anlernen und richte die Fernbedienung darauf.
3. Drücke **Power**, sodass die Fernbedienung AUS anzeigt.
4. Speichere das Signal als `Off`.

Am Ende hast du bis zu 6 Signale. Teste sie alle an der echten Klimaanlage.

## Die Datei vorbereiten und einreichen

1. Kopiere die `.ir`-Datei aus `/ext/infrared/` mit [qFlipper](/de/mobile/qflipper) (oder der Mobile-App) auf deinen
   Computer und öffne sie in einem Texteditor.
2. Setze vor deine Signale einen Modell-Kommentar, damit die Bibliothek geordnet bleibt:
   ```text
   # Model: <your brand and model>
   ```
   Die Reihenfolge der Signale innerhalb des Blocks ist egal.
3. Forke das [Unleashed-Repository](https://github.com/DarkFlippers/unleashed-firmware) und **hänge** deinen Block
   **an das Ende** der passenden Datei in `applications/main/infrared/resources/infrared/assets/` an.
4. Öffne einen Pull Request mit der geänderten Datei. Nach dem Review kommt sie im nächsten Build bei allen an.

Das Dateiformat ist unter [IR-Dateiformat](/de/infrared/file-format#library-files) beschrieben. Große
Community-Sammlungen fertiger Fernbedienungen: [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) und das
offizielle [flipperdevices/IRDB](https://github.com/flipperdevices/IRDB), das die
[Mobile-App](/de/infrared/mobile) nutzt.

## Verwandte Seiten

- [Universalfernbedienungen](/de/infrared/universal-remotes)
- [Signale anlernen und senden](/de/infrared/read)
- [IR-Dateiformat](/de/infrared/file-format)
