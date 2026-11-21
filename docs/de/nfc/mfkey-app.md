---
title: Die MFKey-App
order: 40
author: gromovyna
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/mfkey, https://telegra.ph/MFKey-41---bystree-vyshe-silnee-03-03, https://t.me/gromovyna/27, https://docs.flipper.net/zero/nfc/mfkey32, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, gromovyna, flipper-docs, unleashed-readme]
---
# Die MFKey-App (MFKey 4.1)

**MFKey** (von [@noproto](https://github.com/noproto)) rechnet MIFARE-Classic-Schlüssel **auf dem Flipper selbst**
aus Nonces zurück, die die NFC-App gesammelt hat: Nonces vom Lesegerät (MFKey32) und Nonces von der Karte aus den
Nested-Angriffen. Es ist das Werkzeug für den Fall, dass du kein Telefon und keinen PC zur Hand hast; es ist
langsamer als [qUnleashed](/de/nfc/qunleashed), funktioniert aber überall, selbst in deiner Tasche.

| | |
|---|---|
| Ort | `Main Menu → Apps → NFC → MFKey` (`/ext/apps/NFC/mfkey.fap`) |
| Version in Unleashed | **4.1** |
| Eingaben | `/ext/nfc/.mfkey32.log` (Lesegerät-Nonces), `/ext/nfc/.nested.log` (Karten-Nonces) |
| Ausgabe | `/ext/nfc/assets/mf_classic_dict_user.nfc` (Schlüssel), `/ext/nfc/assets/mf_classic_dict_<UID>.nfc` (SEN-Kandidaten) |

## Benutzung

1. Sammle zuerst Nonces:
   - von einem Lesegerät: [MFKey32](/de/nfc/mfkey) (`Extract MFC Keys`);
   - von der Karte: [Nested-Angriffe](/de/nfc/nested-fudan) während `NFC → Read`.
2. Öffne `Main Menu → Apps → NFC → MFKey`, oder drücke **Run** auf dem Bildschirm *„Now run Mfkey32 to extract
   keys"* in der NFC-App (er erscheint nach `Extract MFC Keys` und nach `Crack nonces in MFKey32`).
3. Der Bildschirm zeigt **Ready**. <kbd>→</kbd> **Help** zeigt *„Collect nonces by reading tag or reader in NFC
   app"*. Drücke <kbd>OK</kbd> **Start**.
4. Zuerst prüft MFKey die Nonces gegen die bestehenden Wörterbücher: **Dict solves: N (in progress)**,
   **Keys in dict: N**. Nonces, deren Schlüssel schon bekannt ist, werden übersprungen.
5. Dann läuft der Angriff mit drei Fortschrittsbalken: **Cracking: X/Y**, **Round: X/Y – ETA NN Sec** und
   **Total ETA NNN Sec**. Die Zeile **RAM** oben zeigt den freien Heap.
6. Ist er fertig, hörst du einen Piepton und siehst **Complete**, **Keys added to user dict: N** und, bei static
   encrypted Nonces, **SEN key candidates: N**.
7. Geh zurück in die NFC-App und lies die Karte erneut (oder `Saved → <Karte> → Unlock with Dictionary`).

<kbd>←</kbd> stoppt die Arbeit und beendet die App (der Thread wird sauber beendet; bis dahin gefundene Schlüssel
werden trotzdem geschrieben).

### Fehler

| Bildschirm | Bedeutung |
|---|---|
| **No nonces found** | Es existiert weder `.mfkey32.log` noch `.nested.log`. Sammle zuerst Nonces. Erscheint auch bei Tags, die nur per HardNested angreifbar sind: deren Nonces lassen sich auf dem Flipper nicht knacken. |
| **Nonces already cracked** | Jede Nonce in den Protokollen ist bereits durch einen Schlüssel in deinen Wörterbüchern gelöst. |
| **No free RAM** | Zu wenig Speicher. Starte den Flipper neu und versuche es erneut; beende andere Apps. |

## Was MFKey 4.x geändert hat

Aus @gromovynas Artikel „MFKey 4.1 — schneller, höher, stärker": die neue Hauptversion kam recht leise, ist aber ein
großer Geschwindigkeitsschub. Verfügbar ist sie in **Unleashed-Dev-Builds ab 1251**. (Zum Zeitpunkt des Artikels
waren die Änderungen der App auch in der offiziellen Firmware eingepflegt, die dafür nötigen Änderungen auf
Firmware-Seite aber nicht.) Dank an @noproto und das Team.

Unten steht **SEN** für static encrypted nonce (siehe [Nested-Angriffe](/de/nfc/nested-fudan)).

**4.0**

- Unterstützung für das neue SEN-Wörterbuchformat: die Schlüsselrückrechnung ist **10× schneller**.
- Das alte SEN-Wörterbuchformat wird nicht mehr unterstützt.

**4.1**

- Die Schlüsselrückrechnung ist weitere **40 % schneller**; bessere Speichereffizienz.
- Das monolithische `mfkey.c` wurde in Module aufgeteilt: `mfkey_batch_prelude`, `mfkey_state_expansion`,
  `mfkey_bs_verify`, `mfkey_recovery`, `mfkey_dedup`.
- 32 Kandidaten werden per SWAR parallel geprüft (Bitoperationen statt einzelner Prüfungen).
- Eine vorberechnete 2 KB große „Super-LUT" für die Runden 0–3: ein indizierter Ladezugriff pro Runde statt einer
  Berechnung.
- Radix Sort in O(n) statt Quicksort; Deduplizierung per Fibonacci-Hashing statt eines naiven Durchlaufs.
- Die FPU-Register des M4 werden als zusätzlicher Zwischenspeicher genutzt (`vmov`), was den Registerdruck senkt.
- Eine 8-fach ausgerollte Duff's-Device-Schleife beim Suchen nach Duplikaten.

### Zeiten aus der Praxis

Der Autor hat den härtesten Fall getestet: einen Tag mit **static encrypted Nonces**. Bei solchen Tags werden die
berechneten Schlüssel nicht unterwegs geprüft und landen nicht direkt im Benutzerwörterbuch; stattdessen wird ein
Wörterbuch von **Kandidaten** aufgebaut, das später gegen den Tag geprüft werden muss. Es werden also **alle**
Schlüssel extrahiert, die eine Nonce erzeugen könnten — das größte Wörterbuch, das längste Szenario. Während der
Tests kam nicht ein einziges *Out Of Memory*.

| Test | Aufbau | Ergebnis |
|---|---|---|
| Iron-Logic-Schlüssel | Tag, verschlüsselt mit einer [Iron Logic](/de/nfc/iron-logic)-Objektkarte; kein Schlüssel im Wörterbuch, Angriff über die Backdoor; **18 einmalige Schlüssel über 32 Sektoren** | Voller Durchlauf **6 h 8 min**, mehr als **1,2 Millionen Kandidaten**; danach mehrere weitere Stunden, um die Kandidaten am Tag zu prüfen. |
| 1 Sektor, 2 Schlüssel | Derselbe Tag (gelöscht), Sektor 0 mit zufälligen, verschiedenen Schlüsseln A und B verschlüsselt | **17 Minuten**; die Kandidatenprüfung an einem Sektor war ebenfalls schnell. |

Zum Vergleich: den ersten Test auf einem Proxmark3 mit Rechner zurückzurechnen dauerte 24 Sekunden, der Flipper wird
damit also nie konkurrieren. Aber wenn du unterwegs bist oder einfach Zeit für Hintergrundarbeit hast, kann der
Flipper in deiner Tasche die Schlüssel zurückrechnen und den Tag emulieren. Und weil vor allem Systeme nach Art von
Iron Logic die Schlüsseldiversifizierung lieben, ist die Chance, in das längste Szenario zu laufen, relativ klein.

::: tip Unleashed
Unleashed enthält MFKey 4.1 mit den dafür nötigen Änderungen auf Firmware-Seite (das CUID-Wörterbuch in `Read`, mit
Fortschrittsbalken während des Ladens). Ist MFKey bei einem SEN-Tag fertig, nimm **Save Keys to Dictionary** am
vollständig gelesenen Dump, um die zurückgerechneten Schlüssel in dein Benutzerwörterbuch zu kopieren, siehe
[MIFARE Classic](/de/nfc/mifare-classic#save-keys-to-dictionary).
:::

## Tipps

- Räume `/ext/nfc/.nested.log` und `/ext/nfc/.mfkey32.log` nach erfolgreicher Rückrechnung auf: alte Nonces werden
  bei jedem Start erneut geprüft.
- Hast du Apps separat installiert, stelle sicher, dass eine alte `mfkey.fap` nicht die aus der Firmware
  überschrieben hat.
- Deutlich schnellere Alternativen: [qUnleashed](/de/nfc/qunleashed) auf Telefon oder PC, oder das Projekt
  [mfkey_desktop_cli](https://github.com/phntm-lab/mfkey_desktop_cli).

## Verwandte Seiten

[MFKey32](/de/nfc/mfkey) · [Nested-Angriffe](/de/nfc/nested-fudan) · [qUnleashed](/de/nfc/qunleashed) ·
[MIFARE Classic](/de/nfc/mifare-classic)
