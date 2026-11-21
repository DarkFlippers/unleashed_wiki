---
title: FAQ
order: 150
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://t.me/how2flipper_rus/7]
sources: [unleashed-docs, unleashed-readme, unleashed-src, how2flipper]
---
# FAQ

## Allgemein

### Ich habe mir gerade einen Flipper Zero gekauft. Wo fange ich an?

Lies [Erster Start](/de/start/first-start) und danach [Unleashed installieren](/de/start/install). Die offizielle Seite
[flipperzero.one](https://flipperzero.one/) und [docs.flipper.net](https://docs.flipper.net/) behandeln die Grundlagen
der Stock-Firmware.

### Offizielle Firmware, Unleashed oder ein anderer Fork?

Wenn du unsicher bist, fang mit der offiziellen Firmware an. Brauchst du mehr Funktionen oder Sub-GHz ohne
Regionssperren, installiere **Unleashed**: einen Fork der offiziellen Firmware mit vielen neuen Funktionen und
vorinstallierten Apps (probier den `e`-Build). Es gibt weitere Forks auf Basis von Unleashed für alle, die mehr mit der
Oberfläche experimentieren wollen. Du kannst auch deinen eigenen Fork bauen.

**Prüfe vor einem Bugreport, welche Firmware du einsetzt.** Melde Probleme aus anderen Forks oder aus der
Stock-Firmware nicht im Unleashed-Repo oder in den Unleashed-Chats.

### Wo sehe ich die Unterschiede zur offiziellen Firmware?

Unter [Was Unleashed hinzufügt](/de/start/unleashed-features).

### Welchen Build soll ich installieren? Was bedeuten `e` und `c`?

`e` = Basis + zusätzliche Community-Apps, ohne Suffix = Basis-Apps, `c` = ohne Community-Apps. Die eingebauten
System-Apps sind in allen enthalten. Details: [Unleashed installieren](/de/start/install#which-file-to-download).

### Was sind Dev-Builds?

Automatische Builds der neuesten Commits im `dev`-Branch, die noch nicht veröffentlicht sind. Sie **können Bugs
enthalten**. Du bekommst sie im Web Installer (Dev), auf [dev.unleashedflip.com](https://dev.unleashedflip.com), in
Telegram bei [@kotnehleb](https://t.me/kotnehleb) oder im Discord-Kanal `unleashed-development`. Beim Hochladen eines
neuen Builds wird der vorherige gelöscht; alte bleiben nur als Dateien im Telegram-Kanal. Einen Bug gefunden?
[Melde ihn](https://github.com/DarkFlippers/unleashed-firmware/issues).

### Was ist der Update-Server von Unleashed?

`https://up.unleashedflip.com/directory.json`. Er nutzt dasselbe Format wie der offizielle, offizielle Apps lassen sich
aber nicht ohne Neubau darauf umstellen. Du kannst ihn an **uFBT** übergeben, um Apps für das Unleashed-SDK zu bauen. Er
bleibt online und aktualisiert sich automatisch.

### Welche Apps sind enthalten?

Die eingebauten System-Apps sowie das Basis-Pack (und für `e` zusätzlich das Extra-Pack) von
[xMasterX/all-the-plugins](https://github.com/xMasterX/all-the-plugins/tree/dev).
Siehe [Was Unleashed hinzufügt](/de/start/unleashed-features#built-in-apps).

### Wie kann ich das Projekt unterstützen?

Siehe den [Abschnitt zur Unterstützung](https://github.com/DarkFlippers/unleashed-firmware#please-support-development-of-the-project)
in der ReadMe. Schon ein einfaches „Danke“ hilft. Jeder Build ist und bleibt frei und Open Source.

## Nach der Installation

### Nach der Installation von Unleashed funktioniert die Beleuchtung nicht {#backlight-does-not-work}

Du hast die Einstellung für den **RGB-Backlight-Mod** aktiviert, die nur für Flipper mit dem RGB-Hardware-Mod gedacht
ist. Geh zu **Settings → LCD and Notifications → RGB Mod Settings** und setz **RGB backlight installed** auf `OFF`.
Wenn du den Mod *tatsächlich* hast, aktiviere ihn genau dort.

### Die mobile App verbindet sich nicht (nach der Installation von Unleashed oder einer Namensänderung)

1. Tippe in der mobilen App auf **Forget Flipper**.
2. Such den Flipper in den **Einstellungen → Bluetooth** des Telefons und wähle **Dieses Gerät ignorieren**.
3. Auf dem Flipper: **Settings → Bluetooth → Unpair All Devices**, dann bestätigen.
4. Stell sicher, dass Bluetooth auf dem Flipper `ON` ist, und koppel dann erneut aus der App.

### Meine Einstellungen (PIN, Favoriten, Desktop …) wurden nach einem Update zurückgesetzt

Setz sie neu. Eine Einstellungsdatei wird nur dann zurückgesetzt, wenn ein Release ihre Struktur ändert — das passiert
in bestimmten Releases, nicht jedes Mal. Schau in die Changelogs der Releases seit deiner vorherigen Version.

### Der Flipper verbindet sich nicht mit Chrome / dem Web Installer

Meist ist **qFlipper offen**, oder eine zweite Flipper-Lab- bzw. Webseite ist verbunden. Nur ein Programm kann den Port
belegen. Schließ die anderen und versuch es erneut. Verwende einen Chromium-basierten Browser.

## Probleme

### Der Flipper ist abgestürzt, eingefroren oder hängt

Halte <kbd>←</kbd> + <kbd>BACK</kbd> gedrückt, um neu zu starten. Mehr dazu:
[Tastenkombinationen](/de/start/key-combos).

### Der Flipper funktioniert überhaupt nicht. Wie stelle ich die Firmware wieder her?

[Wiederherstellung → Firmware-Wiederherstellung](/de/start/recovery#firmware-recovery).

### Ich habe meinen PIN vergessen

Zieh USB ab, schalte den Flipper aus, halte <kbd>↑</kbd> + <kbd>BACK</kbd> etwa 5 s gedrückt, bis der Reset-Bildschirm
erscheint, und halte dann <kbd>→</kbd>. Einstellungen und PIN werden zurückgesetzt, Dateien auf der SD-Karte bleiben
erhalten. Details: [Wiederherstellung → Vergessenen PIN zurücksetzen](/de/start/recovery#reset-pin).

### Der Flipper ist langsam und reagiert kaum

1. Nimm eine gute microSD-Karte eines Markenherstellers. Der Flipper arbeitet über SPI, und nicht jede Karte kommt
   damit gut zurecht.
2. Prüfe unter **Settings → System**:
   ```text
   Log Level = None
   Debug = OFF
   Heap Trace = None
   ```
3. Lad den Akku. Ein schwacher Akku beeinflusst die Leistung ebenfalls.

### Wie ändere ich den Namen des Flippers oder setze ihn zurück?

**Settings → Desktop → Change Flipper Name**: Namen eingeben, **Save**, die Einstellungen verlassen — und der Flipper
startet neu. Speicher einen leeren Namen, um zum Standard zurückzukehren. Siehe
[Eigener Flipper-Name](/de/start/custom-name).

## Sub-GHz

### Gibt es eine Regionssperre? Wie entsperre ich Sub-GHz?

In **Unleashed gibt es keine Regionssperre**: jede Frequenz, die der Chip unterstützt, funktioniert sofort. **Über die
Chip-Spezifikation hinauszugehen** ist möglich, kann aber die Hardware beschädigen:
[Gefährliche Einstellungen](/de/start/dangerous-settings).

### Welche Protokolle werden unterstützt, und mit welcher Frequenz und Modulation?

[Unterstützte Systeme](/de/subghz/supported-systems).

### Wie füge ich zusätzliche Frequenzen hinzu?

[Frequenzen und Presets](/de/subghz/frequencies).

### Kann ich meinen eigenen Autoschlüssel klonen und den Flipper als Schlüssel nutzen?

**Nein.** Autoschlüssel und die meisten Garagentor-Handsender nutzen **Rolling Codes**. Ein aufgezeichnetes Signal
erneut zu senden (etwa aus Read RAW) bringt den Zähler aus dem Takt. Im schlimmsten Fall wird der Originalschlüssel
abgemeldet oder gesperrt, und zum erneuten Anlernen sind Service-Werkzeuge nötig.

**Warum:** der Empfänger merkt sich den letzten Zählerstand, den er von einem Handsender bekommen hat (wie oft
irgendeine Taste gedrückt wurde). Angenommen, der Originalsender hat den Zählerstand `0002` gesendet und du sendest
dasselbe Signal vom Flipper mit `0003`. Der Empfänger akzeptiert es. Der Originalsender steht aber weiterhin bei
`0002`, sein nächster Tastendruck sendet also `0003` — das hat der Empfänger schon gesehen, und er reagiert nicht. Eine
Abmeldung ist das noch nicht: drück den Originalsender einige Male mehr, um den Flipper zu überholen (`0004`), und er
funktioniert wieder. Zieht sich dieses Wettrennen aber hin, kann der Abstand auf **über 100 Tastendrücke** anwachsen —
und dann lässt sich der Originalsender nicht mehr zurückholen, ohne ihn neu am Empfänger anzulernen.

**Was du stattdessen tun kannst:**
- nutze nur **einen** Sender: entweder den Flipper oder das Original;
- **am besten:** leg mit **Add manually** einen **neuen Sender** auf dem Flipper an und lerne ihn als eigenständigen
  Sender am Empfänger an ([Add manually](/de/subghz/add-manually),
  [Neuen Handsender anlernen](/de/subghz/remote-prog));
- wenn es beide sein müssen, nutze sie abwechselnd, damit die Zählerstände nie weit auseinanderlaufen.

Mehr dazu: [Rolling Codes](/de/subghz/rolling-codes), [Counter Mode](/de/subghz/counter-mode).

### Wie nutze ich den Flipper als neuen Handsender (Nice FlorS, BFT Mitto, Somfy Telis, Aprimatic, AN-Motors …)?

[Neuen Handsender anlernen](/de/subghz/remote-prog).

### Wie benutze ich die App Sub-GHz Remote?

1. Öffne die App, drücke <kbd>BACK</kbd> und wähle **New map file**.
2. Wähle für jede Taste eine Signaldatei und eine Bezeichnung. Tasten dürfen leer bleiben.
3. Speicher die Map.
4. Öffne die Map-Datei, die du erstellt hast.
5. Drücke die Tasten, um die zugewiesenen Signale zu senden.

Details: [Sub-GHz Remote](/de/subghz/remote).

### Mein Handsender wird nicht unterstützt (kein Autoschlüssel). Wie zeichne ich ihn für die Entwickler auf?

1. **Finde die Frequenz.** **Sub-GHz → Frequency Analyzer**: halte die Taste des Senders in die Nähe des Flippers (die
   Antenne sitzt links beim IR-Fenster). Lass sie los, und die Frequenz landet im Verlauf. Halte <kbd>OK</kbd>
   gedrückt, um zu **Read** zu springen, und drück den Sender ein paar Mal, jeden Druck mindestens 2 s lang. Probier
   `AM650`, `FM238`, `FM476`, `FM12K`.
2. **Es wird nichts dekodiert? Zeichne RAW auf.** Öffne **Read RAW**, setz die Frequenz in der Konfiguration und den
   **RSSI Threshold** auf `----`. Mach für **jede** Modulation eine eigene Aufnahme
   (`AM650`/`FM238`/`FM476`/`FM12K`). Drücke **REC**, dann eine Taste 5-mal für je 1–2 s und anschließend 5-mal für je
   ~5 s. Nimm jede Taste auf dieselbe Weise auf und benenne jede Datei nach der Taste.
3. **Meld es.** Pack die RAW-Dateien in ein ZIP und öffne ein Issue im Firmware-Repo. Leg gute Fotos des Senders bei
   (wenn möglich auch von innen), Modell und Hersteller sowie, falls machbar, ein Foto der Empfängerplatine.

Ist der Sender nicht verschlüsselt und ausreichend eigenständig, kann Unterstützung ergänzt werden. Zum eigenen
Analysieren von Signalen bietet sich [lab.flipper.net/pulse-plotter](https://lab.flipper.net/pulse-plotter) an.

### Wie schließe ich ein externes CC1101-Modul an?

[Externes CC1101](/de/subghz/external-cc1101).

## NFC und RFID

### MIFARE Ultralight

Lies die Karte, halte den Flipper an den Leser, um das Passwort mitzuschneiden, das die restlichen Pages freigibt, und
lies die Karte dann erneut: [Mit Passwort entsperren](/de/nfc/unlock-with-password).

### MIFARE DESFire / MIFARE Ultralight C

Für diese Karten gibt es auf dem Flipper derzeit keine Angriffe.

### Bankkarten

Bankkarten lassen sich nicht klonen, der Flipper kann sie nicht emulieren und nicht als Zahlungsterminal auftreten. Er
kann nur öffentliche Daten lesen: [Bankkarten (EMV)](/de/nfc/emv).

### Amiibo

Amiibo sind `NTAG215`. Sie passen nicht auf eine MIFARE Classic, und derzeit lassen sich Amiibo nicht auf neue
physische Tags schreiben.

### HID / iClass (Picopass)

- iClass liest du mit der App **Picopass**. Emulation wird in den aktuellen Unleashed-Builds mit Apps unterstützt.
- 26-Bit-Picopass lässt sich auf H10301-Credentials für LF-RFID herunterstufen. Das funktioniert nur, wenn der Leser
  für LF konfiguriert ist. Manche iClass-Leser arbeiten ausschließlich im HF-Bereich.
- Schreibunterstützung für Karten im Personalisierungsmodus ist mit der App möglich.
- Die App **Seader** mit einem SAM-Erweiterungsboard liest auch besser gesicherte HID-Karten.

### 125-kHz-RFID klonen

Um einen LF-Tag zu kopieren, schreibst du ihn auf einen **T5577**. Die Chips, die der Flipper liest, sind nur lesbar,
und „Rohlinge“ davon gibt es nicht. Der T5577 ist ein Multi-Emulator-Chip, der sich so programmieren lässt, dass er
andere Tags nachbildet: [RFID schreiben](/de/rfid/write), [T5577-App](/de/rfid/t5577-app).

### Unbekannte Karte oder unbekannter Schlüsselanhänger

Wenn NFC, RFID und Picopass alle scheitern, mach Fotos von Vorder- und Rückseite des Mediums und vom Leser. Bei einer
Karte hältst du sie vor eine helle Lampe und fotografierst die Antenne. Poste die Bilder in den Community-Chats, damit
sie bestimmt werden kann.

## Infrarot

### Gibt es einen richtigen Weg, IR-Signale aufzunehmen (gerade bei Klimaanlagen)?

Ja: [IR-Aufnahmen](/de/infrared/captures).

## Dateien und Computer

### Wo finde ich Dateien (Sub-GHz, IR, NFC …) für meinen Flipper?

- [UberGuidoZ/Flipper](https://github.com/UberGuidoZ/Flipper) und [Flipper-IRDB](https://github.com/Lucaslhm/Flipper-IRDB) decken die meisten Bedürfnisse ab.
- [Awesome Flipper Zero](https://github.com/djsime1/awesome-flipperzero): praktisch jeder Link, den du brauchen könntest.

### Wie kopiere ich Dateien von GitHub auf den Flipper?

Lad die Dateien am PC herunter und kopier sie auf die SD-Karte (Kartenleser oder der Dateimanager von qFlipper). Es gibt
außerdem eine ausführliche
[Anleitung aus der Community](https://github.com/wrenchathome/flipperfiles/blob/main/_Guides/How2Flipper.pdf).

### Wie entferne ich `.DS_Store` und Punkt-Dateien von macOS, oder sortiere Dateien?

Siehe [microSD-Karte → macOS](/de/start/sd-card#macos-hidden-files-and-sorting).

### Wie öffne ich die CLI oder sehe mir Logs an?

Schließ zuerst qFlipper. Nur ein Programm kann den seriellen Port belegen.

- **Browser (Chromium):** [lab.flipper.net/cli](https://lab.flipper.net/cli) → **CONNECT** → das
  USB-Serial-Gerät wählen → **CLI** in der Seitenleiste.
- **Windows:** den COM-Port in qFlipper ablesen, qFlipper schließen, dann in PuTTY **Serial** wählen, COM-Port und
  Geschwindigkeit `115200` eintragen und **Open** klicken. „Access Denied“ bedeutet, dass qFlipper noch läuft.
- **macOS/Linux:** den Gerätepfad in qFlipper ablesen (er beginnt mit `/dev/tty`) oder mit `ls /dev/tty.*` ermitteln,
  qFlipper schließen, dann ausführen (`PATH` ersetzen):
  ```bash
  screen PATH 115200
  ```
- **Android:** die App *Serial USB Terminal*, verbunden über USB OTG.
- **iPhone:** kein USB-Serial. Nimm einen anderen Weg.

Für Logs setz **Settings → System → Log Level** auf `Debug` und tippe `log` in der CLI. <kbd>Ctrl</kbd>+<kbd>C</kbd>
beendet die Ausgabe. Mehr dazu: [CLI](/de/dev/cli).

### Wie baue ich die Firmware selbst?

[Firmware bauen](/de/dev/build).

## Community

- Releases: Telegram [@unleashed_fw](https://t.me/unleashed_fw)
- Dev-Builds: Telegram [@kotnehleb](https://t.me/kotnehleb)
- Discord: [discord.unleashedflip.com](https://discord.unleashedflip.com)
- Weitere Links: [Links](/de/community/links)
