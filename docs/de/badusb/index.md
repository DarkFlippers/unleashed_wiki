---
title: Bad USB
original: [https://docs.flipper.net/zero/bad-usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/bad_usb, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/CHANGELOG.md]
sources: [flipper-docs, unleashed-readme, unleashed-src]
---
# Bad USB

Die App **Bad USB** verwandelt den Flipper in eine Tastatur (und Maus), die ein vorbereitetes Skript in einen Computer
tippt. Der Computer sieht ein ganz normales Human Interface Device (HID), es sind also keine Treiber nötig. Skripte
werden in einem erweiterten **DuckyScript** (der Sprache des USB Rubber Ducky) geschrieben und als einfache
`.txt`-Dateien auf der microSD-Karte abgelegt.

![Bad USB](/img/remote/2a3485aa02031f3f.png)

Typische legitime Einsätze: wiederkehrende Einrichtungsschritte auf eigenen Rechnern automatisieren, lange Passwörter
oder Konfigurationen eintippen, Software auf einem frischen PC installieren, Demos und Security-Awareness-Schulungen.

::: danger Rechtliches
Ein Gerät zur Tastatureingabe-Injektion kann alles, was auch ein Mensch an der Tastatur kann. Führe Skripte nur auf
Computern aus, die dir gehören oder die du ausdrücklich testen darfst.
:::

Die App arbeitet über **USB**-Kabel oder über **Bluetooth (BLE)**; im zweiten Fall erscheint sie beim Host als
Bluetooth-Tastatur.

::: tip Unleashed
Unleashed integriert **BadKB** (von Willy-JL, ClaraCrazy und den XFW-Mitwirkenden) direkt in die Bad-USB-App:
- **BLE-Modus** mit einstellbarem Gerätenamen, MAC-Adresse, Pairing-Modus und dauerhaftem Pairing, dazu die
  Skriptbefehle `BLE_ID` / `BT_ID`;
- Einstellungen zur **USB-Identität**: Hersteller- und Produktname, VID/PID, Zufallswerte;
- **Tastaturlayouts** für viele Sprachen ([von rien / dummy-decoy](https://github.com/dummy-decoy/flipperzero_badusb_kl));
- der Befehl **`DUCKY_LANG`**, mit dem ein Skript sein eigenes Tastaturlayout wählen kann (neu im aktuellen Release, PR #1224 von @ANTONiO-eagle).
:::

## Dateien

| Pfad | Inhalt |
|---|---|
| `/ext/badusb/` | Deine Skripte (`.txt`). Der Dateibrowser der App öffnet sich hier. |
| `/ext/badusb/examples/` | Demo-Skripte, die mit der Firmware mitkommen (Windows, macOS, GNOME, ChromeOS, Maustest, qFlipper-Installer). |
| `/ext/badusb/assets/layouts/` | Tastaturlayout-Dateien (`.kl`). Siehe [Tastaturlayouts](/de/badusb/layouts). |
| `/ext/badusb/.badusb.settings` | App-Einstellungen: globales Layout, USB-/BLE-Modus, USB- und BLE-Identität. |

Skripte überträgst du mit [qFlipper](/de/mobile/qflipper), der [Mobile-App](/de/mobile/mobile-app) oder indem du sie
direkt auf die SD-Karte kopierst. Eine Datei mit gleichem Namen wird ohne Rückfrage überschrieben.

## Seiten in diesem Abschnitt

| Seite | Was du lernst |
|---|---|
| [Bad USB verwenden](/de/badusb/usage) | Skripte über USB und BLE ausführen, das `Config`-Menü, alle Einstellungen |
| [Skriptformat](/de/badusb/script-format) | Vollständige Befehlsreferenz: STRING, DELAY, HOLD/RELEASE, ALTCHAR, MEDIA, Maus, ID, DUCKY_LANG… |
| [Beispiele](/de/badusb/examples) | Unbedenkliche Beispielskripte für den Anfang |
| [Tastaturlayouts](/de/badusb/layouts) | Welche Layouts es gibt, wie sie funktionieren, eines pro Skript wählen |
