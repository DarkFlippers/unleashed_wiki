---
title: "JavaScript: deine erste App"
sidebarTitle: "JS: erste App"
order: 210
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_your_first_js_app.md]
sources: [unleashed-docs]
---
# Deine erste JavaScript-App

In dieser Anleitung schreibst du ein kleines Skript, das Zahlen mit einer Verzögerung ausgibt, und führst es dann auf
zwei Wegen auf dem Flipper Zero aus: über das Gerätemenü und von einem PC über die CLI. Du brauchst einen Flipper
Zero, einen PC und ein USB-Kabel.

## Schritt 1. Das Skript anlegen

Erstelle eine Textdatei mit dem Namen `first_app.js` und diesem Inhalt:

```js
print("start");
delay(1000);
print("1");
delay(500);
print("2");
delay(500);
print("3");
delay(500);
print("end");
```

Was es tut:

- gibt **start** aus und wartet 1 Sekunde;
- gibt **1**, **2** und **3** aus, mit jeweils 0,5 Sekunden Pause danach;
- gibt **end** aus.

`print()` gibt Text aus, und `delay()` pausiert für die angegebene Anzahl Millisekunden (1000 ms = 1 s). Beide sind
**eingebaute Funktionen**, es muss also vorher kein Modul geladen werden. Die vollständige Liste steht unter
[Eingebaute Funktionen](/de/dev/js-builtin).

## Schritt 2. Die Datei auf den Flipper Zero kopieren

1. Verbinde den Flipper Zero über USB mit deinem PC.
2. Öffne [qFlipper](/de/mobile/qflipper).
3. Gehe auf den Tab **File manager** und öffne `SD Card/apps/Scripts/`.
4. Zieh `first_app.js` per Drag & Drop in das qFlipper-Fenster.

Du kannst die Datei auch mit einem Kartenleser kopieren. Sie muss in `/ext/apps/Scripts/` landen.

## Schritt 3. Das Skript ausführen

### Über das Flipper-Menü

1. Öffne `Main Menu → Apps → Scripts`. Die Liste zeigt die Skripte in `SD Card/apps/Scripts/`.
2. Wähle `first_app`.
3. Drücke <kbd>OK</kbd>, um es auszuführen.

![Skript läuft auf dem Flipper Zero](/img/dev/js_first_app_on_fz.jpg)

Die Zeilen erscheinen mit den im Skript festgelegten Verzögerungen auf dem Display des Flipper.

### Über die CLI

Das Ausführen über die [CLI](/de/dev/cli) ist praktisch zum Debuggen: du bearbeitest und testest das Skript, ohne das
Gerät anzufassen.

1. Verbinde den Flipper Zero über USB.
2. Öffne die CLI (zum Beispiel über den CLI-Tab von qFlipper, ein serielles Terminal oder `./fbt cli`).
3. Führe `js` gefolgt vom Pfad zum Skript aus:

```sh
js /ext/apps/Scripts/first_app.js
```

![Skriptausgabe in der CLI](/img/dev/js_first_app_on_cli.jpg)

Wird ein Skript über die CLI gestartet, geht alles, was mit `print()` ausgegeben wird, an die CLI und nicht an das
Display des Flipper.

## Fehlerbehebung

- **Das Skript steht nicht in der Liste.** Prüfe, ob die Datei die Endung `.js` hat und in `/ext/apps/Scripts/`
  liegt (Unterordner sind in Ordnung; navigiere einfach hinein).
- **Das Skript bricht mit einem Fehler ab.** mJS unterstützt nur eine Teilmenge von JavaScript (keine Closures,
  keine Arrow Functions, keine Klassen). Führe es über die CLI aus, um die Fehlermeldung und die Zeile zu sehen.

**Als Nächstes:** [Apps mit dem JavaScript-SDK entwickeln](/de/dev/js-sdk)
