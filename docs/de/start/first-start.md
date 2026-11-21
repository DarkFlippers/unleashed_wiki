---
title: Erster Start
order: 10
original: [https://docs.flipper.net/zero/basics/first-start, https://docs.flipper.net/zero/basics/sd-card, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/HowToInstall.md]
sources: [flipper-docs, unleashed-docs]
---
# Erster Start

Was in den ersten zehn Minuten mit einem neuen Flipper Zero zu tun ist, noch bevor du Unleashed installierst.

## 1. Einschalten

Halte <kbd>BACK</kbd> etwa 3 Sekunden gedrückt. Der Desktop erscheint, mit dem Delfin und der Statusleiste:

![Der Flipper-Desktop: die Ruheanimation des Delfins und die Statusleiste mit den Symbolen für SD-Karte und Akku](/screens/desktop/idle.png)

::: details Der Flipper lässt sich nicht einschalten
- Der Akku kann vollständig leer sein. Schließe das USB-C-Kabel an. Das Gerät schaltet sich nach kurzer Zeit von
  selbst ein.
- Bleibt das Display dunkel, halte <kbd>←</kbd> + <kbd>BACK</kbd> 5 Sekunden gedrückt (Neustart).
- Immer noch nichts: siehe [Tastenkombinationen](/de/start/key-combos) und [Wiederherstellung](/de/start/recovery).
:::

## 2. microSD-Karte einlegen

Eine microSD-Karte ist **zwingend erforderlich**. Auf der Karte liegen Schlüssel, Karten, Handsender, Datenbanken, die
mit der Firmware gelieferten Apps und sogar der „interne“ Speicher (siehe [microSD-Karte](/de/start/sd-card)). Die
Karte gehört nicht zum Lieferumfang.

1. Der Steckplatz befindet sich an der Unterseite des Flippers.
2. Halte die Karte **mit den Kontakten nach oben** und schiebe sie hinein, bis sie einrastet.
3. Ist die Karte eingebunden, zeigt die Statusleiste ein SD-Karten-Symbol.

Eine Markenkarte mit **16–32 GB** reicht völlig. Karten bis 256 GB funktionieren, brauchen zum Einbinden aber länger.
Billige No-Name-Karten können das Gerät langsam oder instabil machen.

## 3. Offizielle Firmware aktualisieren (nur bei der Erstinstallation)

Die Installationsanleitung von Unleashed verlangt, dass du bei der **Erstinstallation zuerst auf das aktuelle
offizielle Release aktualisierst**. Damit sind Bootloader, Radio Stack und interne Daten auf dem neuesten Stand.

- **qFlipper** (Windows/macOS/Linux): per USB verbinden, den Tab **Advanced controls** öffnen, **Update Channel** auf
  **Release** setzen und **Update** anklicken.
- **Flipper Mobile App** (iOS/Android): Bluetooth am Flipper aktivieren (**Main Menu → Settings → Bluetooth**), mit der
  App koppeln, dann auf **Update** tippen. Das dauert etwa 10 Minuten.

Mehr zu qFlipper und zur Mobil-App: [qFlipper](/de/mobile/qflipper), [Mobil-App](/de/mobile/mobile-app).

## 4. Unleashed installieren

Nutze den **[Unleashed Web Installer](https://web.unleashedflip.com)** — das ist der einfachste Weg. Alle Methoden
stehen unter [Unleashed installieren](/de/start/install).

## 5. Grundeinrichtung

Öffne nach der Installation **Main Menu → Settings** und prüfe:

- **Clock & Alarm**: Datum und Uhrzeit einstellen;
- **System → Hand Orient**: `Lefty`, wenn du das Gerät in der linken Hand hältst;
- **Desktop**: PIN, Uhr auf dem Desktop (`Show Clock`), Akkuanzeige (`Battery View`), Apps für den Schnellzugriff;
- **Desktop → Change Flipper Name**: gib deinem Flipper einen eigenen Namen
  ([Eigener Flipper-Name](/de/start/custom-name)).

Jeder einzelne Punkt ist unter [Einstellungen](/de/start/settings) beschrieben.

## Nächste Schritte

- Tasten und Tastenkürzel lernen: [Steuerung](/de/start/controls)
- Den Desktop erkunden: [Desktop](/de/start/desktop)
- Sehen, was Unleashed ergänzt: [Was Unleashed hinzufügt](/de/start/unleashed-features)
