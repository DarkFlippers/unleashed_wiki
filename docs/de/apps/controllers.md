---
title: HID-Fernbedienung verbinden
order: 60
original: [https://docs.flipper.net/zero/apps/controllers, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/hid_app]
sources: [flipper-docs, unleashed-src]
---
# HID-Fernbedienung verbinden

Mit der HID-Fernbedienungs-App steuert der Flipper Präsentationen, tippt Text, bewegt die Maus und steuert
Medienwiedergabe auf einem Computer oder Smartphone. Diese Seite behandelt das **Verbinden**; was die einzelnen Modi
tun, steht unter [USB-/Bluetooth-Fernbedienung (HID)](/de/apps/hid-remote).

Es gibt zwei Verbindungswege:

| | USB | Bluetooth LE |
|---|---|---|
| App | `Apps → USB → USB Keyboard & Mouse` | `Apps → Bluetooth → Bluetooth Remote` |
| Kopplung | keine, einfach einstecken | einmal pro Host |
| Funktioniert mit | Computern, Smartphones mit USB-C/OTG | Computern, Android, iPhone/iPad |

::: tip Unleashed
In Unleashed heißen die beiden Varianten **USB Keyboard & Mouse** und **Bluetooth Remote** und liegen in den
App-Ordnern `USB` und `Bluetooth` (die offizielle Dokumentation nennt beide "Remote").
:::

## Über USB

1. Verbinde den Flipper mit einem USB-Datenkabel mit dem Computer. Schließe zuerst qFlipper, die Fernbedienung
   braucht den USB-Port.
2. Öffne `Main Menu → Apps → USB → USB Keyboard & Mouse`.
3. Wähle einen Modus (Keynote, Keyboard, Mouse ...). Der Computer erkennt eine neue Tastatur bzw. Maus, ein Treiber
   ist nicht nötig.

Beim Verlassen der App kehrt der USB-Anschluss des Flipper in den normalen (seriellen) Modus zurück.

## Über Bluetooth

1. Schalte Bluetooth am Computer oder Smartphone ein.
2. Auf dem Flipper: `Main Menu → Settings → Bluetooth` und **Bluetooth** auf **ON** stellen.
3. Öffne `Main Menu → Apps → Bluetooth → Bluetooth Remote` und wähle einen Modus.
4. Öffne am Computer oder Smartphone die Bluetooth-Einstellungen und verbinde dich mit
   **Control &lt;Flipper name&gt;** (auf dem Smartphone auf **Pair** tippen).
5. Wenn der Flipper eine Kopplungsbestätigung anzeigt, drücke <kbd>OK</kbd>.

Beim nächsten Mal verbindet sich der Host automatisch, sobald du Bluetooth Remote öffnest.

::: tip Eigener Name
`Bluetooth Remote → Bluetooth Remote Name` ändert den angekündigten Namen – praktisch, wenn du mehrere
Flipper-Fernbedienungen hast oder sie wie eine gewöhnliche Tastatur aussehen soll.
:::

### Wenn die Kopplung fehlschlägt

- Vergewissere dich, dass Bluetooth unter `Settings → Bluetooth` auf ON steht.
- Entferne den alten "Control ..."-Eintrag in den Bluetooth-Einstellungen des Hosts, führe dann auf dem Flipper
  `Bluetooth Remote → Bluetooth Unpairing → Unpair` aus und koppele erneut.
- Trenne den Flipper von anderen Geräten (zum Beispiel der Mobil-App).
- Starte den Flipper neu: <kbd>←</kbd> + <kbd>Back</kbd> etwa 5 Sekunden halten.
- Aktualisiere die Firmware.

Die Fernbedienung verwaltet ihre eigenen Kopplungen (`/ext/apps_data/hid_ble/.bt_hid.keys`), getrennt vom
Haupt-Bluetooth des Flipper, das die Mobil-App nutzt. **Bluetooth Unpairing** innerhalb der Fernbedienung löscht nur
deren Hosts. Das globale `Settings → Bluetooth → Unpair All Devices` löscht alles: die Kopplung der Mobil-App und
auch die der Fernbedienung (und von BadKB).

### iPhone / iPad: der TikTok-Modus reagiert nicht

1. Öffne auf dem iPhone `Settings → Accessibility → Touch → AssistiveTouch`.
2. Schalte **AssistiveTouch** ein.
3. Gehe unter **Pointer Devices** zu **Devices → Bluetooth Devices** und wähle deinen Flipper aus.

## Verwandte Seiten

- [USB-/Bluetooth-Fernbedienung (HID)](/de/apps/hid-remote)
- [Einstellungen](/de/start/settings)
- [Flipper-Mobil-App](/de/mobile/mobile-app)
