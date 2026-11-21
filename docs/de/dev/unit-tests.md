---
title: Unit-Tests
order: 120
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/UnitTests.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/fbt_options.py, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests]
sources: [unleashed-docs, unleashed-src]
---
# Unit-Tests

Unit-Tests geben bekannte Eingaben an den Funktionscode und prüfen, ob die Ergebnisse korrekt sind. Sie sind
unverzichtbar für robusten, fehlerfreien Code.

Die Firmware enthält eine eigene App, **`unit_tests`** (`applications/debug/unit_tests`), die **auf dem Flipper
selbst** läuft — die Tests nutzen also die echte Hardware und schließen plattformbedingte Unterschiede aus.

Wenn du zur Firmware beiträgst, liefere nach Möglichkeit Unit-Tests mit neuen Funktionen mit und führe die
bestehenden aus, um sicherzustellen, dass deine Änderung keine Regressionen einführt.

## Die Tests ausführen

1. **Baue die Firmware mit dem Test-App-Set:**

   ```sh
   ./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests updater_package
   ```

   ::: warning `DEBUG=0` ist erforderlich
   Die `fbt_options.py` setzt standardmäßig `DEBUG=1`, und ein Debug-Image passt nicht mehr unter den
   Flash-Bereich des Radio-Stacks — das Packen bricht mit
   `Firmware image overlaps C2 region and is not programmable!` ab. Seit API 88.23 ist ein Debug-Image für dieses
   App-Set etwa 7 KB zu groß (10 KB beim Standard-Set), die Tests zu verkleinern hilft also nicht.
   (`COMPACT=1` ist schon der Standard; es ist nur ausgeschrieben, damit es zu den anderen Befehlen passt.)

   Denk daran, dass `DEBUG=0` `furi_assert()` herauskompiliert, Assertions im getesteten Code greifen also nicht.
   `furi_check()` und die minunit-Assertions sind davon nicht betroffen.
   :::

   Das App-Set `unit_tests` enthält: `basic_services`, `updater_app`, `radio_device_cc1101_ext`, `unit_tests`,
   `infrared`, `archive`.

2. **Flashe die Firmware einschließlich der SD-Karten-Ressourcen** (`build/latest/resources`) — installiere z. B.
   die erzeugte `.tgz` aus `dist/` mit qFlipper oder nutze
   `./fbt COMPACT=1 DEBUG=0 FIRMWARE_APP_SET=unit_tests flash_usb_full`. Die Test-Assets müssen auf der SD-Karte
   landen.
3. **Öffne eine [CLI](/de/dev/cli)-Sitzung** und führe aus:

   ```
   unit_tests
   ```

**Erwartetes Ergebnis:** die Suiten laufen eine nach der anderen, danach erscheint ein Bericht wie dieser:

```
Tests run: …, asserts: …
Failed tests: 0
Consumed: … ms
Leaked: …
```

Erscheint `Cannot open /ext/apps_data/unit_tests/plugins - are the SD card resources deployed?`, wurden die
SD-Karten-Ressourcen nicht installiert — wiederhole Schritt 2 mit Ressourcen.

Um **einen** Test auszuführen und die übrigen zu überspringen, gib seinen Namen an:

```
unit_tests test_infrared
```

Andere Suiten werden übersprungen (`Skipping …`); ein falscher Name ergibt `No suite named …`. Die Testnamen
entsprechen den App-IDs (`test_furi`, `test_storage`, `test_subghz`, `test_infrared`, `test_nfc`, `test_lfrfid`, …),
die in
[`applications/debug/unit_tests/application.fam`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/application.fam)
definiert sind.

::: info
Das ist ein besonderer Firmware-Build ohne die üblichen Apps. Installiere danach wieder einen normalen Build.
:::

## Unit-Tests ergänzen

### Einstiegspunkt

Alle Tests laufen aus der "Mutter"-App `unit_tests`. Der Testcode selbst wird als `PLUGIN`-App in einem
Unterverzeichnis von `tests/` innerhalb von `unit_tests` verpackt und in der gemeinsamen `application.fam`
referenziert. Übernimm die Struktur eines bestehenden Tests.

### Test-Assets

Manche Tests brauchen externe Daten ("Assets"). Sie liegen in
[`applications/debug/unit_tests/resources/unit_tests`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests),
jeweils in ihrem eigenen Unterverzeichnis. Assets können jeden Typ haben: einfachen Text, Flipper Format (FFF),
Binärdaten usw.

### Beispiel: Infrarotprotokolle

Jedes Infrarotprotokoll hat eine Reihe von Unit-Tests, ergänze also einen, wenn du ein neues Protokoll hinzufügst:

1. Erstelle `test_<your_protocol_name>.irtest` im
   [Asset-Verzeichnis für Infrarot](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/debug/unit_tests/resources/unit_tests/infrared).
2. Füll es mit Testdaten (siehe unten).
3. Ergänze den Testcode in
   [`infrared_test.c`](https://github.com/DarkFlippers/unleashed-firmware/blob/dev/applications/debug/unit_tests/tests/infrared/infrared_test.c).
4. Baue und installiere die Firmware mit Ressourcen, führe dann die Tests aus und prüfe, ob sie durchlaufen.

#### Format der Testdaten

Jeder Infrarot-Test hat drei Abschnitte:

| Abschnitt | Funktion |
|---|---|
| `decoder` | Nimmt ein Rohsignal, gibt dekodierte Nachrichten aus |
| `encoder` | Nimmt dekodierte Nachrichten, gibt ein Rohsignal aus |
| `encoder_decoder` | Kodiert dekodierte Nachrichten in ein Rohsignal und dekodiert sie wieder |

`.irtest`-Dateien sind gewöhnliche [`.ir`-Dateien](/de/infrared/file-format) mit ein paar Ergänzungen:

- Eingangssignale für den Decoder heißen `decoder_input_N` (N = Nummer in der Testreihe), die erwartete Ausgabe
  `decoder_expected_N`;
- bei Encoder-Tests sind die beiden getauscht;
- dekodierte Daten sind ein **Array**, weil ein Rohsignal in mehrere Nachrichten dekodiert werden kann — eine
  einzelne Nachricht ist ein Array der Größe 1.

Nimm bestehende `.irtest`-Dateien als Syntaxbeispiele.

#### Rohsignale aufzeichnen

Öffne eine CLI-Sitzung und führe aus:

```
ir rx raw
```

Richte die Fernbedienung auf den Flipper und drücke Tasten. Die Rohdaten werden in einem direkt verwendbaren Format
ausgegeben.

## Verwandte Seiten

- [Integrationstests](/de/dev/testing)
- [Flipper Build Tool (fbt)](/de/dev/fbt)
- [Kommandozeile](/de/dev/cli)
