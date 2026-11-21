---
title: Universalfernbedienungen
order: 20
original: [https://docs.flipper.net/zero/infrared/universal-remotes, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UniversalRemotes.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-docs, unleashed-readme, unleashed-src]
---
# Universalfernbedienungen

Mit einer Universalfernbedienung steuerst du ein Gerät, **ohne vorher seine Fernbedienung anzulernen**. Drückst du
etwa *Power*, sendet der Flipper den Power-Code jedes Modells aus seiner Bibliothek, einen nach dem anderen. Trifft
er den Code, den dein Gerät versteht, reagiert es. Deshalb braucht eine Universaltaste ein paar Sekunden, statt
sofort zu wirken.

Öffne `Main Menu → Infrared → Universal Remotes`.

![Die Kategorieliste der Universal Remotes: TVs, Audio, Projectors, LEDs](/screens/infrared/universal_remotes.png)

::: tip Unleashed
Die offizielle Firmware liefert Bibliotheken für Fernseher, Audio, Projektoren und Klimaanlagen. Unleashed ergänzt
**LEDs** und **Fans** und hält alle Bibliotheken deutlich umfangreicher und regelmäßig vom Team nachgeprüft
(IR-Assets von @amec0e). Die TV-Bibliothek wird so neu kompiliert, dass **alle** ihre Tasten funktionieren, nicht nur
Power.
:::

## Kategorien

Die Menüpunkte und Tastennamen unten stammen aus der Firmware; die Signalzahlen aus den Bibliotheken des aktuellen
`dev`-Builds (`/ext/infrared/assets/`, letzter Stand Oktober 2024 / Februar 2024 für AC).

| Menüpunkt | Bibliotheksdatei | Tasten | Signale in der Bibliothek |
|---|---|---|---|
| **TVs** | `tv.ir` | Power, Mute, Vol_up, Vol_dn, Ch_next, Ch_prev | 613 (295 davon Power) |
| **Audio** | `audio.ir` | Power, Mute, Play, Pause, Prev, Next, Vol_dn, Vol_up | 851 |
| **Projectors** | `projectors.ir` | Power, Mute, Vol_up, Vol_dn, Play, Pause | 302 |
| **LEDs** | `leds.ir` | Power_on, Power_off, Brightness_up, Brightness_dn, Red, Green, Blue, White | 489 |
| **Fans** | `fans.ir` | Power, Mode, Speed_up, Speed_dn, Rotate, Timer | 421 |
| **ACs** | `ac.ir` | Off, Dh, Cool_hi, Cool_lo, Heat_hi, Heat_lo | 182 |

„Audio" umfasst Soundbars, AV-Receiver, Kompaktanlagen und Ähnliches. „LEDs" meint IR-gesteuerte LED-Streifen und
-Leuchtmittel.

### Klimaanlagen

Klimaanlagen-Fernbedienungen führen den Gerätezustand selbst mit und senden bei jedem Druck den vollständigen
Zustand. Die AC-Bibliothek enthält daher komplette „Szenen" statt einzelner Tasten:

| Taste | Bedeutung |
|---|---|
| **Off** | Die Klimaanlage ausschalten. Das ist die *einzige* Taste, die sie ausschaltet. |
| **Dh** | Entfeuchten (Trockenmodus). |
| **Cool_hi** | Kühlen bei der niedrigsten Temperatur, die die Fernbedienung zulässt (maximales Kühlen). |
| **Cool_lo** | Kühlen bei 23 °C. |
| **Heat_hi** | Heizen bei der höchsten Temperatur, die die Fernbedienung zulässt (maximales Heizen). |
| **Heat_lo** | Heizen bei 23 °C. |

Um eine Klimaanlage **einzuschalten**, drücke eine beliebige Taste außer Off. Die Temperaturtasten zeigen °C oder °F,
je nach `Settings → System → Units`.

## So wird's benutzt

1. Gehe zu `Main Menu → Infrared → Universal Remotes` und wähle eine Kategorie.
2. Richte die Oberkante des Flippers auf das Gerät. Bleibe nah dran und in Sichtlinie.
3. Wähle mit den Pfeiltasten eine Taste und drücke <kbd>OK</kbd>.

   ![Die universelle TV-Fernbedienung auf dem hochkant genutzten Bildschirm: oben Power und Mute, darunter Channel und Volume auf/ab](/screens/infrared/universal_tv.png)

4. Das Fenster **„Sending..."** zeigt den Fortschritt als `current/total` und einen Balken. Ziele weiter auf das Gerät.
5. Sobald das Gerät reagiert, drücke <kbd>OK</kbd> für **pause** — oder lass die Bibliothek bis zum Ende durchlaufen.

![Universalfernbedienung in Aktion](/img/remote/bdb3541a3f2e88fe.png)

### Bedienung während des Sendens

| Zustand | Taste | Aktion |
|---|---|---|
| Sendet | <kbd>OK</kbd> | **pause** |
| Sendet | <kbd>Back</kbd> | **stop** |
| Pausiert | <kbd>Back</kbd> | Senden dort **fortsetzen**, wo es angehalten wurde |
| Pausiert | <kbd>OK</kbd> | **send 1**: nur das gerade ausgewählte Signal senden |
| Pausiert | <kbd>←</kbd> / <kbd>→</kbd> (Pfeile) | das vorherige / nächste Signal der Bibliothek **auswählen** |
| Pausiert | <kbd>↓</kbd> | das ausgewählte Signal **speichern** |

## Den genauen Code finden und speichern

Die eigentliche Stärke des Pausenbildschirms: du kannst den einen funktionierenden Code finden und behalten, damit die
Taste beim nächsten Mal sofort wirkt.

1. Starte eine Universaltaste. Sobald das Gerät reagiert, drücke <kbd>OK</kbd> (pause). Der Zähler steht nun beim
   letzten gesendeten Signal.
2. Weil man nie perfekt schnell ist, gehe mit der linken Pfeiltaste zurück und probiere mit **send 1**
   (<kbd>OK</kbd>) jedes Signal, bis du das findest, das das Gerät auslöst. Mit der rechten Pfeiltaste geht es wieder
   vorwärts.
3. Drücke <kbd>↓</kbd> **save**. Die Menüzeile zeigt den Tastennamen (z. B. `Power`) — unter diesem Namen wird das
   Signal auch gespeichert:
   - **Save as New Remote**: gib unter **„Name the remote"** einen Namen ein; in `/ext/infrared/` entsteht eine neue
     `.ir`-Datei;
   - **Add to Existing Remote**: wähle eine bestehende `.ir`-Datei; das Signal wird daran angehängt.
4. **„Saved"** bestätigt es. Die Fernbedienung liegt jetzt in `Infrared → Saved Remotes`.

Wiederhole das für Vol_up, Mute und so weiter und hänge alles an dieselbe Fernbedienung: so entsteht aus der
Universalbibliothek eine eigene, sofort reagierende Fernbedienung.

![Eine gespeicherte Fernbedienung hochkant: die Tastenliste Power, Vol_up, Vol_dn, Mute, Ch_next, Ch_prev](/screens/infrared/remote.png)

## Von der Kommandozeile

Dieselben Bibliotheken lassen sich über die [CLI](/de/dev/cli) abspielen:

```text
ir universal list tv        # list the signal names in tv.ir
ir universal tv Power       # send every "Power" signal from tv.ir
```

`ir universal` ohne Argumente listet die verfügbaren Bibliotheken auf (alle `.ir`-Dateien in
`/ext/infrared/assets/`). <kbd>Ctrl</kbd>+<kbd>C</kbd> im Terminal bricht ab.

## Fehlersuche

| Problem | Was du versuchen kannst |
|---|---|
| *„Function requires SD card with fresh databases."* | Die Bibliotheksdateien fehlen. Lege die microSD-Karte ein und installiere bzw. aktualisiere die Firmware mit eingelegter Karte, siehe [Aktualisieren](/de/start/updating). |
| Nach der ganzen Bibliothek reagiert nichts | Dein Modell ist nicht in der Bibliothek. [Lerne](/de/infrared/read) stattdessen die Originalfernbedienung an, probiere die [Remotes Library der Mobile-App](/de/infrared/mobile) und denke über [einen Beitrag](/de/infrared/captures) nach. |
| Das Gerät reagiert, aber zu spät zum Pausieren | Gehe mit der linken Pfeiltaste + **send 1** zum richtigen Signal zurück, siehe oben. |
| Funktioniert nur auf sehr kurze Distanz | Die eingebauten LEDs sind für große Räume schwach. Nutze ein [externes IR-Modul](/de/infrared/external-ir). |
| Die Klimaanlage lässt sich mit Off nicht einschalten | Das ist so gewollt: Off schaltet nur aus. Nutze Cool/Heat/Dh zum Einschalten. |

## Verwandte Seiten

- [Aufnahmen beitragen](/de/infrared/captures): dein Gerät in die Bibliotheken bringen
- [IR-Dateiformat](/de/infrared/file-format): das Format der Bibliotheksdateien
- [Signale anlernen und senden](/de/infrared/read)
