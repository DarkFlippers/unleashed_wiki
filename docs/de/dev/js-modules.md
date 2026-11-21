---
title: "JavaScript: Module verwenden"
sidebarTitle: "JS: Module verwenden"
order: 230
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/js/js_using_js_modules.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules]
sources: [unleashed-docs, unleashed-src]
---
# JavaScript-Module verwenden

Die [eingebauten Funktionen](/de/dev/js-builtin) sind absichtlich wenige. Hardware- und Systemfunktionen stecken in
**JS-Modulen**, zum Beispiel:

- `serial` sendet und empfängt Daten über UART;
- `badusb` emuliert eine USB-Tastatur;
- `math` stellt mathematische Funktionen bereit.

Module sind in C geschrieben und daher schnell. Sie werden mit der Firmware ausgeliefert und in kompilierter Form
als **FAL-Plugins (Flipper Application File)** auf der SD-Karte abgelegt. Modulquellen:
[`applications/system/js_app/modules`](https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/js_app/modules).
Die Liste der Module steht unter [JavaScript – Übersicht](/de/dev/js-about).

## Ein Modul laden

Du **musst** ein Modul mit `require()` laden, bevor du seine Methoden aufrufst. Dadurch wird das Modul ins RAM
geladen.

- Lade nur, was du verwendest, um RAM zu sparen. (`math` belegt zum Beispiel nach dem Laden etwa 21 KB RAM.)
- Alle geladenen Module werden automatisch entladen, wenn das Skript endet.
- Ein Modul kann pro Skript nur einmal geladen werden; ein zweites `require()` desselben Namens schlägt mit
  `"... module is already installed"` fehl.
- Manche Module hängen von anderen ab und müssen nach diesen geladen werden: `gpio` und `gui` brauchen
  `event_loop`, und jede `gui/*`-View braucht `gui`.

Übergib den Modulnamen in Anführungszeichen:

```js
let notify = require("notification");
```

Rufe dann seine Methoden über die Variable auf:

```js
let notify = require("notification");

notify.success();
print("success notification");
```

Die Firmware akzeptiert auch den SDK-Namensstil `require("@flipperdevices/fz-sdk/notification")`: das Präfix wird
automatisch entfernt. Namen mit einem Schrägstrich, etwa `gui/submenu`, werden auf die Plugin-Datei
`js_gui__submenu` abgebildet.

## Wie es weitergeht

- Sieh dir die Modulseiten in diesem Abschnitt an, beginnend mit [Event loop](/de/dev/js-event-loop) und
  [GUI](/de/dev/js-gui).
- Studiere die Beispielskripte in `/ext/apps/Scripts/js_examples/`.
