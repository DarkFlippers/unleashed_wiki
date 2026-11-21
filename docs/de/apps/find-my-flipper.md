---
title: FindMy Flipper
order: 70
original: [https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/system/find_my_flipper, https://github.com/MatthewKuKanich/FindMyFlipper, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/ReadMe.md]
sources: [unleashed-src, unleashed-readme]
---
# FindMy Flipper

**FindMy Flipper** (von @MatthewKuKanich) verwandelt das Bluetooth des Flipper in ein Tracker-Beacon. Der Flipper
sendet dieselben BLE-Advertisements wie ein Tag, und Smartphones des Tracking-Netzwerks in der Nähe melden seinen
Standort – so lässt sich ein verlorener Flipper in der App des Tag-Besitzers wiederfinden.

Unterstützte Tag-Typen: **Apple AirTag** (Find My), **Samsung SmartTag** (SmartThings Find), **Tile SmartTag** und
**Google Find My** (Find My Device).

`Main Menu → Apps → Bluetooth → FindMy Flipper`

::: tip Unleashed
FindMy Flipper ist Teil der Firmware, und Unleashed installiert zusätzlich einen kleinen Startup-Hook: war das
Beacon aktiv, als der Flipper ausgeschaltet wurde, **startet es nach einem Neustart automatisch wieder**, ohne dass
du die App öffnen musst. Das Beacon läuft im Hintergrund weiter, während du andere Apps benutzt.
:::

::: warning
Verwende die App nur mit deinen eigenen Tags und Geräten. Das Verfolgen anderer Personen kann an deinem Wohnort
illegal sein.
:::

## Was du brauchst

Der Flipper benötigt die **MAC-Adresse** und die **Payload** des Tags (oder eine Key-Datei). Du bekommst sie auf
einem von zwei Wegen:

- **Ein vorhandenes Tag klonen** (am einfachsten; der Standort erscheint dann in der üblichen App des
  Tag-Besitzers).
- **Eigene Schlüssel erzeugen** mit der OpenHaystack-Methode (kein physisches Tag nötig, nur das Apple-Netzwerk;
  den Standort siehst du mit OpenHaystack oder einer Alternative ohne Mac).

### Variante A: ein vorhandenes Tag klonen

1. Koppele das AirTag oder SmartTag wie gewohnt mit deinem Smartphone.
2. Versetze es in den "verloren"-Modus: halte es etwa 15 Minuten vom registrierten Smartphone entfernt.
3. Installiere auf einem Android-Smartphone **nRF Connect** (die iOS-Version zeigt die Rohdaten nicht).
4. Setze in nRF Connect den Filter auf die Marke des Tags (Apple oder Samsung), stelle RSSI auf den niedrigsten Wert
   und starte den Scan.
5. Sobald das Tag als "FindMy"-Gerät auftaucht, öffne **Raw** / **View Raw** und notiere die **Payload** und die
   **MAC-Adresse**. Du kannst sie auch als `.txt`-Datei exportieren.
6. **Entferne sofort die Batterie des Tags**, sonst wechselt es Schlüssel und MAC und deine Kopie funktioniert nicht
   mehr.

### Variante B: OpenHaystack-Schlüssel

1. Lade `generate_keys.py` aus dem [FindMyFlipper-Repository](https://github.com/MatthewKuKanich/FindMyFlipper)
   herunter und führe es aus (es braucht `python3 -m pip install cryptography`).
2. Es liefert dir einen **Private Key**, einen **Public Key**, eine **Payload** und eine **MAC Address** sowie eine
   `.keys`-Datei.
3. Bewahre den Private Key auf: du brauchst ihn, um Standortmeldungen zu empfangen.
4. Standorte siehst du in [OpenHaystack](https://github.com/seemoo-lab/openhaystack) (Mac, macOS vor 14) oder ohne
   Mac mit [macless-haystack](https://github.com/dchristl/macless-haystack) oder
   [Chapoly1305/FindMy](https://github.com/Chapoly1305/FindMy).

## Den Flipper einrichten

1. Kopiere deinen nRF-Connect-`.txt`-Export oder die `.keys`-Datei nach `/ext/apps_data/findmy/` auf der SD-Karte
   (oder überspringe das und gib die Daten von Hand ein).
2. Öffne `Apps → Bluetooth → FindMy Flipper` und drücke <kbd>→</kbd> (**Config**).
3. Wähle **Register Tag** und dann den Tag-Typ: `Apple AirTag`, `Samsung SmartTag`, `Tile SmartTag` oder
   `Google Find My`.
4. Wähle die Importart:
   - `nRF Connect (.txt)`: die exportierte Datei auswählen;
   - `OpenHaystack (.keys)`: die Key-Datei auswählen;
   - `Register Tag Manually`: die MAC-Adresse und danach die Payload eintippen.
5. Gehe zurück zum Hauptbildschirm und drücke <kbd>OK</kbd>. Die Anzeige wechselt zu `Broadcast Active`.

## Hauptbildschirm

| Taste | Aktion |
|---|---|
| <kbd>OK</kbd> | Beacon starten / stoppen (`Broadcast Active` / `Broadcast Inactive`) |
| <kbd>↑</kbd> / <kbd>↓</kbd> | das Sendeintervall ändern |
| <kbd>→</kbd> | Config |
| <kbd>←</kbd> | die App verlassen, das Beacon läuft im Hintergrund weiter |
| <kbd>Back</kbd> | die App beenden |

## Config-Menü

| Eintrag | Werte | Hinweise |
|---|---|---|
| Broadcast Interval | 1–10 s (Google: 1–2 s) | wie oft das Beacon gesendet wird; Google verlangt mindestens alle 2 s |
| Transmit Power | 0–6 dBm | mehr Leistung = mehr Reichweite, höherer Akkuverbrauch |
| Register Tag | | Tag-Typ und Import (siehe oben) |
| Show MAC | Yes / No | die MAC auf dem Hauptbildschirm anzeigen |

Die App speichert ihren Zustand in `/ext/apps_data/findmy/findmy_state.txt`; genau das ermöglicht es dem Beacon, nach
einem Neustart weiterzulaufen.

## Tracking

- **AirTag-Klon**: der Flipper erscheint als dein AirTag in der Find-My-App.
- **SmartTag-Klon**: in SmartThings (SmartThings Find), auf dem Smartphone oder im Browser.
- **OpenHaystack-Schlüssel**: in OpenHaystack oder macless-haystack.

## Fehlerbehebung

- **Der Standort wird nie aktualisiert**: Schlüssel/MAC des Tags haben rotiert, bevor du die Batterie entfernt hast;
  erfasse es erneut.
- **Das Beacon stoppt nach einem Neustart**: prüfe, ob die SD-Karte eingesteckt ist (die Zustandsdatei liegt darauf)
  und ob das Beacon vor dem Ausschalten auf `Broadcast Active` stand.
- **Der Akku entleert sich schneller**: erhöhe das Sendeintervall und reduziere die Sendeleistung.

## Verwandte Seiten

- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
- [Einstellungen](/de/start/settings)
