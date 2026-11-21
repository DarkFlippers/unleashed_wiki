---
title: Eigener Flipper-Name
order: 110
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/CustomFlipperName.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/namechanger, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/settings/desktop_settings]
sources: [unleashed-docs, unleashed-src]
---
# Eigener Flipper-Name

Jeder Flipper hat einen Namen aus dem Werk. Er erscheint im Passport, unter **About**, in Bluetooth-Gerätelisten und in
qFlipper. Unleashed erlaubt es, ihn durch einen eigenen Namen zu ersetzen.

::: tip Unleashed
Die Stock-Firmware hat kein Menü zum Umbenennen des Geräts. In Unleashed liegt es unter
**Settings → Desktop → Change Flipper Name**, und der Name **übersteht Firmware-Updates**, weil er auf der
microSD-Karte gespeichert wird.
:::

## Namen setzen

1. Öffne **Main Menu → Settings → Desktop → Change Flipper Name**.
2. Gib den neuen Namen ein. In der Kopfzeile der Tastatur steht `Leave empty for default` („leer lassen für den
   Standardnamen“).
   - **2 bis 8 Zeichen**;
   - **nur lateinische Buchstaben und Ziffern** (`A–Z`, `a–z`, `0–9`). Bei allem anderen erscheint *„Please only enter
     letters and numbers!“*.
3. Wähle **Save**.
4. Es erscheint die Meldung **`Name is set!`** / *„Your Flipper will be restarted on exit.“* („Der Flipper startet beim
   Verlassen neu“).
5. Verlasse die Einstellungen mit <kbd>BACK</kbd>. Der Flipper **startet automatisch neu**.
6. Nach dem Neustart steht der neue Name im Passport, unter **Settings → About** und über Bluetooth.

## Auf den Werksnamen zurücksetzen

1. Öffne **Settings → Desktop → Change Flipper Name**.
2. Lösche alle Zeichen und lass das Feld **leer**.
3. Wähle **Save** und verlasse die Einstellungen. Der Flipper startet mit seinem ursprünglichen Namen neu.

## Wie es funktioniert

- Der Name wird in **`/ext/dolphin/name.settings`** auf der SD-Karte gespeichert:
  ```text
  Filetype: Flipper Name File
  Version: 1
  Name: MyFlip
  ```
- Beim Start wartet der Dienst `namechanger` auf die SD-Karte, liest diese Datei und übernimmt den Namen, wenn er gültig
  ist: richtige Kopfzeile und Version, 2–8 Zeichen, nur Buchstaben und Ziffern. Danach startet er die serielle
  USB-Schnittstelle und die Bluetooth-Profile neu, damit sie den neuen Namen verwenden.
- Einen leeren Namen zu speichern löscht die Datei.
- Der Dienst läuft nur beim normalen Start, nicht im Updater und nicht im DFU-Modus.

Weil der Name auf der Karte liegt, bleibt er nach Updates erhalten. Verloren geht er, wenn du die Karte formatierst oder
ersetzt oder die Datei löschst.

## Fehlerbehebung

| Problem | Lösung |
|---|---|
| Der Name hat sich nicht geändert | Hast du die Einstellungen verlassen (erst der Neustart übernimmt ihn)? Ist die SD-Karte eingesteckt? Hat der Name 2–8 Buchstaben/Ziffern? Ein Name mit nur 1 Zeichen wird gespeichert, beim Start aber ignoriert |
| Die mobile App verbindet sich nicht mehr | Der Bluetooth-Name hat sich geändert. Entferne den Flipper in der App **und** in den Bluetooth-Einstellungen des Telefons, führe auf dem Flipper **Settings → Bluetooth → Unpair All Devices** aus und koppel ihn neu |
| Eine von anderswo kopierte Namensdatei wird ignoriert | Prüfe die Kopfzeile `Flipper Name File`, `Version: 1` und die Regeln für den Namen |
