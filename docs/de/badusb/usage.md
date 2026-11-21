---
title: Bad USB verwenden
order: 10
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [flipper-docs, unleashed-src, unleashed-readme]
---
# Bad USB verwenden

Diese Seite führt dich durch das Ausführen eines Skripts über USB und über Bluetooth und erklärt jeden Punkt des
Menüs **Config**. Menübezeichnungen und Meldungen stehen genau so da, wie sie in der Firmware erscheinen.

::: warning
Führe Skripte nur auf Computern aus, die dir gehören oder die du testen darfst. Lies ein Skript, bevor du es
startest: es tut genau das, was darin steht — mit den Rechten deines Benutzers.
:::

## Bevor du anfängst

- Eine microSD-Karte mit den Firmware-Ressourcen ist Pflicht. Ohne sie zeigt die App *„No SD card or app data found.
  This app will not work without required files."*
- Lege dein Skript (`.txt`) nach `/ext/badusb/` (Unterordner sind erlaubt).
- **Der USB-Modus belegt den USB-Port des Flippers.** Ist qFlipper oder die [CLI](/de/dev/cli) über USB verbunden, zeigt
  die App *„Connection Is Active! Disconnect from PC or phone to use this function."* Beende qFlipper zuerst.

## Der Hauptbildschirm

1. Öffne `Main Menu → Bad USB`.
2. Wähle im Dateibrowser ein Skript. Der Skriptbildschirm öffnet sich.

Die obere Zeile zeigt den Skriptnamen, darunter das Tastaturlayout in Klammern — `(default)` oder z. B. `(de-DE)` —
und die vergangene Zeit, im BLE-Modus stattdessen die Pairing-PIN. Das Bild in der Mitte zeigt einen USB-Stecker oder
ein Bluetooth-Symbol.

![Bad USB Skriptbildschirm: demo_windows geladen, 0/34 Zeilen, Hinweise Config / Run / BLE](/screens/badusb/script_ready.png)

| Zustand | Bildschirmtext | <kbd>OK</kbd> | <kbd>←</kbd> | <kbd>→</kbd> |
|---|---|---|---|---|
| Idle / Done / nicht verbunden | Fortschritt oder *Connect to device* | **Run** | **Config** | umschalten auf **BLE** / **USB** |
| Warten auf Verbindung nach Run | *Will run on connect* | **Cancel** | | |
| Läuft oder in einem `DELAY` | `line/total`, Prozent, `Delay Ns` | **Stop** | | **Pause** |
| Pausiert | *Paused* | **End** | | **Resume** |
| Warten bei `WAIT_FOR_BUTTON_PRESS` | | **Press to continue** | | |
| Fehler | *ERROR:* + `line N` + Meldung | | | |

Drückst du **Run**, bevor der Host den Flipper erkannt hat, wartet die App (*„Will run on connect"*) und startet das
Skript automatisch **1,5 s nach dem Verbindungsaufbau**, damit der Host Zeit hat, die Tastatur einzurichten.

Solange kein Host verbunden ist, ersetzen die Sanduhr und *Connect to device* die Fortschrittsanzeige:

![Bad USB wartet auf einen USB-Host, der Bildschirm zeigt Connect to device](/screens/badusb/not_connected.png)

<kbd>Back</kbd> verlässt den Skriptbildschirm und kehrt zum Dateibrowser zurück.

## Über USB ausführen

1. Beende qFlipper auf dem Computer.
2. `Main Menu → Bad USB` → Skript auswählen.
3. Achte darauf, dass der Bildschirm das **USB**-Bild zeigt; falls nicht, drücke <kbd>→</kbd> **USB**.
4. Optional: <kbd>←</kbd> **Config → Keyboard Layout (global)**, um das Layout des Computers zu treffen
   (Standard `en-US`).
5. Verbinde den Flipper per USB-Kabel mit dem Computer.
6. Drücke <kbd>OK</kbd> **Run**. Der Fortschritt `line/total` läuft bis 100 %.

![Bad USB führt ein Skript aus: 32 %, Zeile 12 von 34, Hinweise Stop und Pause](/screens/badusb/script_running.png)

![Bad USB im USB-Modus](/img/remote/d49323518c0b4b18.jpg)

## Über Bluetooth (BLE) ausführen

1. Stelle sicher, dass Bluetooth am Flipper eingeschaltet ist (`Settings → Bluetooth`).
2. `Main Menu → Bad USB` → Skript auswählen.
3. Drücke <kbd>→</kbd> **BLE**; das Bluetooth-Bild erscheint. Der Flipper beginnt, sich als Tastatur zu bewerben.
4. Öffne am Computer/Telefon die Bluetooth-Einstellungen und verbinde dich mit
   **`BadUSB <dein Flipper-Name>`** (der Standardname).
5. Bestätige das Pairing auf beiden Geräten. Im Standard-Pairing-Modus zeigen beide Bildschirme dieselbe PIN;
   bestätige, dass sie übereinstimmt. Die PIN steht auch auf dem Skriptbildschirm.
6. Drücke <kbd>OK</kbd> **Run**.
7. Pairing später entfernen: <kbd>←</kbd> **Config → Remove BLE Pairing**, danach das Gerät auch am Host vergessen.

![Bad USB im BLE-Modus](/img/remote/083420027c3f836c.jpg)

::: tip Eigene Identität und eigenes Pairing
Im BLE-Modus nutzt der Flipper seine **eigene MAC-Adresse** (abgeleitet von der MAC des Flippers) und einen eigenen
Pairing-Speicher, getrennt vom normalen Bluetooth-Profil. Wenn du einen Computer mit Bad USB koppelst, zerstörst du
also nicht das Pairing mit der Flipper Mobile App. Beim Verlassen der App wird das normale Bluetooth-Profil
wiederhergestellt.
:::

## Skripte, die den Modus selbst umschalten

Ist die **erste Zeile** eines Skripts ein `ID`-Befehl (USB) oder `BLE_ID` / `BT_ID` (Bluetooth), schaltet die App beim
Öffnen des Skripts automatisch in diesen Modus und übernimmt die angegebene Identität. Von Hand umschalten kannst du
weiterhin mit <kbd>→</kbd>. Siehe [Skriptformat → Device ID](/de/badusb/script-format#device-id).

## Config-Menü

<kbd>←</kbd> **Config** ist nur verfügbar, solange das Skript nicht läuft. Der Inhalt hängt vom aktuellen
Verbindungsmodus ab.

### Gemeinsam

| Punkt | Werte | Funktion |
|---|---|---|
| **Keyboard Layout (global)** | Dateibrowser | Wählt eine `.kl`-Datei aus `/ext/badusb/assets/layouts/`. Gilt für jedes Skript, das mit `DUCKY_LANG` kein eigenes setzt. Siehe [Tastaturlayouts](/de/badusb/layouts). |
| **Connection** | `USB` / `BLE` | Dasselbe wie <kbd>→</kbd> auf dem Hauptbildschirm. Die Liste darunter ändert sich entsprechend. |

### BLE-Modus

| Punkt | Werte | Funktion |
|---|---|---|
| **Persist Pairing** | `ON` / `OFF` | ON (Standard): Bond mit dem Host anlegen und merken, sodass er sich ohne erneutes Pairing verbindet. OFF: jedes Mal neu koppeln. |
| **Pairing Mode** | `YesNo`, `PIN Type`, `PIN Y/N` | `YesNo`: Pairing ohne PIN. `PIN Type`: der Flipper zeigt eine PIN, die du am Host eintippst. `PIN Y/N` (Standard): beide zeigen eine PIN, du bestätigst die Übereinstimmung. |
| **Set Device Name** | Text | Bluetooth-Name (*„Set BLE device name"*). Leer = `BadUSB <Flipper-Name>`. |
| **Set MAC Address** | 6 Bytes | *„Set BLE MAC address"*. |
| **Randomize MAC Address** | Aktion | Erzeugt eine zufällige statische MAC und zeigt **Done**. Praktisch, um als „neue" Tastatur zu erscheinen. |
| **Restore BLE Defaults** | Aktion | Löscht Name und MAC, Persist Pairing ON, Pairing Mode `PIN Y/N`. |
| **Remove BLE Pairing** | Aktion | *„Unpair the Device?"* → **Unpair** vergisst alle mit Bad USB gekoppelten Hosts. |

### USB-Modus

| Punkt | Werte | Funktion |
|---|---|---|
| **Set Manufacturer Name** | Text | USB-Hersteller-String (*„Set USB manufacturer name"*). |
| **Set Product Name** | Text | USB-Produkt-String (*„Set USB product name"*). |
| **Set VID and PID** | 4 Bytes | *„Set USB VID:PID"*. Lässt den Flipper sich mit einer bestimmten Vendor-/Product-ID ausgeben. |
| **Randomize VID and PID** | Aktion | Zufällige VID und PID, zeigt **Done**. |
| **Restore USB Defaults** | Aktion | Löscht VID/PID und Namen: es wird die Standard-Tastaturidentität des Flippers benutzt. |

All das wird zusammen mit dem gewählten Layout und Modus in `/ext/badusb/.badusb.settings` gespeichert. Eine Zeile
`ID` / `BLE_ID` in einem Skript überschreibt die Identität nur für dieses Skript.

## Fehlersuche

| Problem | Was du versuchen kannst |
|---|---|
| Der getippte Text ist Kauderwelsch (`z` und `y` vertauscht, falsche Sonderzeichen) | Das Tastaturlayout des Hosts passt nicht zu dem der App. Wähle in `Config` das richtige Layout oder ergänze `DUCKY_LANG` im Skript. Hat der PC mehrere Eingabesprachen, stelle ihn vor dem Start auf die Sprache des Layouts um (also z. B. Englisch, nicht Russisch). |
| Zeichen fehlen | Der Host ist zu langsam. Setze `DEFAULT_STRING_DELAY 10` (oder mehr) und längere `DELAY`s nach dem Öffnen von Fenstern. |
| Das Skript startet, bevor das Fenster offen ist | Erhöhe das `DELAY` nach `GUI r`, `ENTER` und Ähnlichem. |
| *ERROR: line N* | Die Zeile enthält einen unbekannten Befehl, einen Tippfehler, eine ungültige Zahl oder Nicht-ASCII-Text. Befehle sind **groß-/kleinschreibungsabhängig** (`STRING`, nicht `string`). Siehe [Skriptformat](/de/badusb/script-format). |
| *Native .kl supports ASCII, not UTF-8* | `STRING` enthält Nicht-ASCII-Zeichen (Umlaute, Akzente, Kyrillisch …). Nutze unter Windows `ALTSTRING`/`ALTCHAR` oder gib solchen Text anders ein. |
| *Connection Is Active!* | Trenne qFlipper / CLI vom USB-Port. |
| macOS öffnet den *Keyboard Setup Assistant* | Nutze eine `ID`-Zeile mit VID/PID einer Apple-Tastatur (siehe das Beispiel `demo_macos.txt`) oder schließe den Assistenten einfach. |
| Der BLE-Host findet den Flipper nicht | Bluetooth am Flipper einschalten, im BLE-Modus auf dem Skriptbildschirm bleiben, alte Pairings auf beiden Seiten entfernen (`Remove BLE Pairing`). |

## Verwandte Seiten

- [Skriptformat](/de/badusb/script-format)
- [Beispiele](/de/badusb/examples)
- [Tastaturlayouts](/de/badusb/layouts)
