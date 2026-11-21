---
title: Fernbedienungen in der Mobile-App
order: 30
original: [https://docs.flipper.net/zero/infrared/remotes-mobile, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/infrared]
sources: [flipper-docs, unleashed-src]
---
# IR-Fernbedienungen in der Flipper Mobile App

Die Flipper Mobile App (iOS / Android) hat eine **Remotes Library**: eine Online-Datenbank mit IR-Fernbedienungen. Du
wählst Gerätetyp und Marke, die App findet über ein paar Testsignale die passende Fernbedienung, lädt sie auf den
Flipper und zeigt dir dann ein richtiges Bedienlayout auf dem Telefon. Gesendet wird vom Flipper.

Verglichen mit den [Universalfernbedienungen](/de/infrared/universal-remotes), die bei jedem Druck die ganze
Bibliothek abspielen, wird eine Fernbedienung aus der Remotes Library **einmal** gefunden und arbeitet danach sofort.
Sie hat außerdem mehr Tasten und deckt mehr Gerätetypen ab.

## Was du dort findest

Die Bibliothek enthält unter anderem Fernbedienungen für Fernseher, Projektoren, TV-Boxen, Ventilatoren,
Luftreiniger, DVD-Player, Kameras und AV-Receiver. Die Datenbank ist Open Source:
[flipperdevices/IRDB](https://github.com/flipperdevices/IRDB); du kannst deine Fernbedienung nach deren
[Contribution Guide](https://github.com/flipperdevices/IRDB/blob/dev/docs/adding_remote.md) beitragen.

::: tip Unleashed
Die Mobile-App arbeitet mit Unleashed genauso wie mit der Stock-Firmware: sie spricht per RPC mit der Infrared-App.
Während das Telefon die Kontrolle hat, zeigt der Flipper-Bildschirm **„Infrared – RPC mode"**. Aus der App geladene
Fernbedienungen sind gewöhnliche `.ir`-Dateien in `/ext/infrared/` und lassen sich am Flipper wie jede angelernte
Fernbedienung nutzen, bearbeiten und umbenennen. Mehr zur App selbst:
[Flipper Mobile App](/de/mobile/mobile-app).
:::

## Die Fernbedienung für dein Gerät finden

1. Verbinde den Flipper über Bluetooth mit der App.
2. Gehe in der App zu `Tools → Remotes Library`.
3. Wähle den **Gerätetyp**, dann die **Marke**.
4. Viele Marken haben mehrere Fernbedienungen, deshalb testet die App Signale eines nach dem anderen: richte den
   Flipper auf das Gerät, tippe auf die Taste, um das Signal zu senden, und beantworte, ob das Gerät reagiert hat.
5. Ist die richtige Fernbedienung gefunden, zeigt die App ihr Layout. Du kannst sie sofort benutzen.
6. Tippe auf **Save** (oben rechts) und gib der Fernbedienung einen Namen. Sie wird auf den Flipper geschrieben.
7. *(Optional)* Tippe **⋯ → Add to Favorites**, damit sie für den schnellen Zugriff im Archive-Tab liegt.

![Remotes Library](/img/remote/9c74a923d5c1aae5.jpg)

## Eine gespeicherte Fernbedienung benutzen

**Vom Telefon aus.** Öffne in der App `Archive → Infrared` (oder die Favoriten), wähle die Fernbedienung, richte den
Flipper auf das Gerät und tippe die Tasten auf dem Telefon an. Die App sagt dem Flipper, welches Signal er senden
soll.

![Bedienlayout in der App](/img/remote/7387cb59433e202d.jpg)

**Nur mit dem Flipper.** Gehe zu `Main Menu → Infrared → Saved Remotes`, öffne die Fernbedienung, wähle mit
<kbd>↑</kbd> / <kbd>↓</kbd> eine Taste und drücke <kbd>OK</kbd>. Siehe
[Signale anlernen und senden](/de/infrared/read#send-a-saved-button).

## Fehlersuche

| Problem | Was du versuchen kannst |
|---|---|
| Die App kann nicht senden / es passiert nichts | Stelle sicher, dass der Flipper verbunden und nicht in einer anderen App beschäftigt ist. Schließe eine laufende App am Flipper und versuche es erneut. |
| Für deine Marke wird keine Fernbedienung gefunden | Lerne die Originalfernbedienung am Flipper an ([wie](/de/infrared/read)) oder probiere die [Universalfernbedienungen](/de/infrared/universal-remotes). |
| Das Gerät reagiert nur auf sehr kurze Distanz | Nutze ein [externes IR-Modul](/de/infrared/external-ir); die App verwendet den in den Infrared GPIO Settings gewählten Sender. |

## Verwandte Seiten

- [Flipper Mobile App](/de/mobile/mobile-app)
- [Universalfernbedienungen](/de/infrared/universal-remotes)
- [IR-Dateiformat](/de/infrared/file-format)
