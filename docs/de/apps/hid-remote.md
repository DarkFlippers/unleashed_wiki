---
title: USB-/Bluetooth-Fernbedienung (HID)
order: 50
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app, https://docs.flipper.net/zero/apps/controllers]
sources: [unleashed-src, flipper-docs]
---
# USB-/Bluetooth-Fernbedienung (HID)

Die HID-App lässt den Flipper für einen Computer, ein Smartphone oder ein Tablet wie eine Tastatur, eine Maus oder
eine Medienfernbedienung aussehen (ein USB **H**uman **I**nterface **D**evice). Dieselbe App wird zweimal gebaut:

| App | Wo auf dem Flipper | Verbindung |
|---|---|---|
| **USB Keyboard & Mouse** | `Main Menu → Apps → USB → USB Keyboard & Mouse` | USB-Kabel |
| **Bluetooth Remote** | `Main Menu → Apps → Bluetooth → Bluetooth Remote` | Bluetooth LE |

Wie du sie verbindest, steht unter [HID-Fernbedienung verbinden](/de/apps/controllers). Diese Seite beschreibt jeden
Modus.

## Modi

Das Startmenü listet auf:

`Keynote` · `Keynote Vertical` · `Keyboard` · `Numpad` · `Media` · `Apple Music macOS` · `Movie` · `Mouse` ·
`TikTok / YT Shorts` · `Mouse Clicker` · `Mouse Jiggler` · `Mouse Jiggler Stealth` · `PushToTalk`

Die Bluetooth-Version hat zusätzlich `Bluetooth Remote Name` und `Bluetooth Unpairing`.

::: tip Unleashed
Die offizielle Dokumentation beschreibt Keynote, Keyboard, Media, Mouse, TikTok, Mouse Jiggler und Mouse Clicker.
Der Unleashed-Build der App hat außerdem **Numpad**, **Apple Music macOS**, **Movie**, **Mouse Jiggler Stealth**,
**PushToTalk** und **Bluetooth Remote Name**, um den angekündigten Namen der Fernbedienung zu ändern.
:::

In fast jedem Modus gilt: **<kbd>Back</kbd> gedrückt halten, um zu beenden** und zur Modusliste zurückzukehren;
beim Verlassen werden alle Tasten freigegeben.

### Keynote und Keynote Vertical

Ein Präsentations-Clicker. Keynote Vertical ist derselbe Modus, gedreht für das aufrechte Halten des Flipper.

| Taste | Sendet |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Pfeiltasten (nächste / vorherige Folie) |
| <kbd>OK</kbd> | Space |
| <kbd>Back</kbd> | Backspace + "AC Back" (verlässt in den meisten Programmen die Präsentationsansicht) |
| <kbd>Back</kbd> halten | beenden |

### Keyboard

Eine QWERTY-Tastatur auf dem Display mit Ziffern, Symbolen, F1–F12, Esc, Tab, Enter, Backspace, Delete und den
Modifikatoren Ctrl, Alt, Shift und Cmd (Win).

1. Mit den Pfeiltasten navigieren, mit <kbd>OK</kbd> die ausgewählte Taste senden.
2. Wähle die Taste ⬆ (Shift), um Großbuchstaben und die zweite Symbolreihe zu tippen.
3. Für ein Tastenkürzel zuerst den Modifikator (Ctrl, Alt oder Cmd) drücken, dann die Taste.
4. <kbd>Back</kbd> halten zum Beenden.

### Numpad

Ein Zahlenblock: `0`–`9`, `.`, `+`, `-`, `*`, `/`, `En` (Enter des Zahlenblocks), `NL` (Num Lock) und Backspace.
Pfeiltasten wählen aus, <kbd>OK</kbd> drückt die Taste, <kbd>Back</kbd> halten beendet.

### Media

| Taste | Sendet |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | vorheriger / nächster Titel |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Lautstärke höher / niedriger |
| <kbd>Back</kbd> halten | beenden |

Auf Smartphones funktionieren die Lautstärketasten auch als Kameraauslöser: Kamera öffnen und <kbd>↑</kbd> oder
<kbd>↓</kbd> drücken, um ein Foto zu machen oder ein Video zu starten bzw. zu stoppen.

### Apple Music macOS

| Taste | Sendet |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | vorheriger / nächster Titel |
| <kbd>↑</kbd> / <kbd>↓</kbd> | <kbd>Cmd</kbd>+<kbd>↑</kbd> / <kbd>Cmd</kbd>+<kbd>↓</kbd> (Lautstärke in Apple Music) |
| <kbd>Back</kbd> halten | beenden |

### Movie

| Taste | Sendet |
|---|---|
| <kbd>OK</kbd> | Play / Pause |
| <kbd>←</kbd> / <kbd>→</kbd> | Pfeil links / rechts (Spulen in den meisten Playern) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Lautstärke höher / niedriger |
| <kbd>Back</kbd> halten | beenden |

### Mouse

| Taste | Aktion |
|---|---|
| <kbd>↑</kbd> <kbd>↓</kbd> <kbd>←</kbd> <kbd>→</kbd> | Cursor bewegen; Halten beschleunigt |
| <kbd>OK</kbd> | Linksklick |
| <kbd>OK</kbd> halten | linke Taste gedrückt halten (Ziehen, "Selecting...") |
| <kbd>Back</kbd> | Rechtsklick |
| <kbd>Back</kbd> halten | beenden |

### TikTok / YT Shorts

Für Kurzvideo-Apps auf einem Smartphone oder Tablet.

| Taste | Aktion |
|---|---|
| <kbd>↑</kbd> / <kbd>↓</kbd> | zum vorherigen / nächsten Video scrollen |
| <kbd>OK</kbd> | Doppeltipp (Like) |
| <kbd>←</kbd> / <kbd>→</kbd> | Lautstärke niedriger / höher |
| <kbd>Back</kbd> | einfacher Tipp (Pause) |
| <kbd>Back</kbd> halten | beenden |

::: tip iPhone / iPad
Wenn der TikTok-Modus unter iOS nichts tut, aktiviere
`Settings → Accessibility → Touch → AssistiveTouch` und wähle dann unter
**Pointer Devices → Devices → Bluetooth Devices** deinen Flipper aus.
:::

### Mouse Clicker

Klickt automatisch mit einer eingestellten Rate.

| Taste | Aktion |
|---|---|
| <kbd>OK</kbd> | Start / Stop |
| <kbd>↑</kbd> / <kbd>↓</kbd> | Klicks pro Sekunde, bis 100 (Standard 1) |
| <kbd>←</kbd> / <kbd>→</kbd> | welche Taste: links, rechts oder Rad (Mitte) |
| <kbd>Back</kbd> | beenden |

### Mouse Jiggler

Bewegt den Cursor in einem festen Intervall ein wenig, damit der Computer nicht in den Ruhezustand geht oder dich
als "abwesend" anzeigt.

1. Wähle vor dem Start mit <kbd>←</kbd> / <kbd>→</kbd> das Intervall: 500, 2000, 5000, 10000, 30000 oder 60000 ms
   (Standard 5000 ms).
2. Drücke <kbd>OK</kbd> für **Start**, erneut für **Stop**. Bis der Host verbunden ist, zeigt das Display
   `Waiting for Connection...`.
3. <kbd>Back</kbd> beendet.

### Mouse Jiggler Stealth

Wie der Jiggler, bewegt sich aber in zufälligen Intervallen zwischen einem Minimum und einem Maximum, die du in
Minuten festlegst (1 bis 30) – das sieht weniger maschinell aus. Im gestoppten Zustand ändern <kbd>↑</kbd> /
<kbd>↓</kbd> das Minimum und <kbd>→</kbd> / <kbd>←</kbd> erhöhen / verringern das Maximum; <kbd>OK</kbd> startet
oder stoppt.

### PushToTalk

Eine Mute-/Push-to-Talk-Taste für Videokonferenzen.

1. Wähle die Liste für dein Betriebssystem (**macOS** oder **Win/Linux**) und dann die App: Google Meet, Google
   Meet Global, Google Hangouts, Discord, FaceTime, Gather, Jamulus, Signal, Skype, Slack Call, Slack Huddle,
   TeamSpeak, Teams, Webex, Zoom oder Zoom Global.
2. Halte <kbd>OK</kbd> auf einem Eintrag der Liste lange gedrückt, um dessen Hilfe zu lesen (manche Apps brauchen
   eine Einstellung oder eine Erweiterung, zum Beispiel ein globales Tastenkürzel für Google Meet oder das Belegen
   der Tasten in TeamSpeak).
3. Im Gespräch: <kbd>Back</kbd> schaltet das Mikrofon um, **<kbd>OK</kbd> halten** für Push-to-Talk (beim Loslassen
   geht das Mikrofon aus), <kbd>→</kbd> halten ändert den Mikrofonstatus des Flipper, falls er nicht mehr mit dem
   Computer übereinstimmt. Bei Zoom sendet ein langer Druck auf <kbd>←</kbd> Enter.
4. <kbd>Back</kbd> halten zum Beenden.

### Bluetooth Remote Name und Bluetooth Unpairing (nur Bluetooth)

- **Bluetooth Remote Name**: gib in `Bluetooth Name` einen Namen ein; die Fernbedienung kündigt sich darunter an.
  Standardmäßig erscheint sie als `Control <Flipper name>`.
- **Bluetooth Unpairing**: fragt `Unpair All Devices? All previous pairings will be lost!`; drücke **Unpair**, um
  jeden mit der Fernbedienung gekoppelten Host zu vergessen. Die Fernbedienung verwaltet ihre eigenen
  Kopplungsschlüssel (`/ext/apps_data/hid_ble/.bt_hid.keys`), getrennt von den Haupt-Bluetooth-Kopplungen des
  Flipper.

## Verwandte Seiten

- [HID-Fernbedienung verbinden](/de/apps/controllers)
- [Bad USB](/de/badusb/usage)
- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
