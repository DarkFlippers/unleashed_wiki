---
title: Gefährliche Einstellungen
order: 140
original: [https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/DangerousSettings.md, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/FAQ.md, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/main/subghz, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/targets/f7/furi_hal]
sources: [unleashed-docs, unleashed-src]
---
# Gefährliche Einstellungen: erweiterter Sub-GHz-Bereich

Unleashed kann das CC1101-Funkmodul **außerhalb seines offiziellen Frequenzbereichs** betreiben. Diese Seite erklärt,
was die Einstellung tut, warum du sie mit großer Wahrscheinlichkeit nicht brauchst, und wie du sie einschaltest, falls
doch.

::: danger Erst lesen
1. Lass das besser, wenn du nicht genau weißt, was du tust.
2. Für fast jeden Anwendungsfall brauchst du den erweiterten Bereich nicht.
3. Senden außerhalb der Hardware-Spezifikation **kann deine Hardware beschädigen**.
4. Weder das Team von Flipper Devices noch die Unleashed-Entwickler haften für Schäden durch Custom-Firmware oder
   durch das Erweitern des Frequenzbereichs.
:::

## Du brauchst es wahrscheinlich nicht: es gibt keine Regionssperre

::: tip Unleashed
In Unleashed sind **alle regionalen TX-Beschränkungen standardmäßig aufgehoben**. Jede Frequenz innerhalb des vom Chip
unterstützten Bereichs sendet ohne weitere Schritte. Benutze die gefährliche Einstellung nicht, um „deine Region zu
entsperren“. Dafür ist sie nicht nötig.
:::

Wird das Senden auf einer Frequenz blockiert, prüfe zuerst, ob die Frequenz im unten genannten normalen TX-Bereich
liegt. Außerhalb davon protokolliert die Firmware `Frequency blocked - outside default range`.

## Frequenzbereiche

| | Bereiche |
|---|---|
| CC1101-Datenblatt | 300–348 MHz, 386–464 MHz, 778–928 MHz |
| Standard-**TX**-Bereich von Unleashed | ≈ 300–350 MHz, 387–467,75 MHz, 779–928 MHz (erweitert, damit 350 MHz und 467 MHz enthalten sind) |
| TX mit aktivierten `dangerous_settings` | **281–361 MHz, 378–481 MHz, 749–962 MHz** |

Der erweiterte Bereich entspricht dem erweiterten Bereich des YARD Stick One (laut Firmware-Quellcode). Außerhalb der
Bereiche aus dem Datenblatt arbeitet der Chip außerhalb der Spezifikation, und Senden kann ihn dort beschädigen.

## Aktivieren

1. Nimm die microSD-Karte heraus oder verbinde dich per qFlipper bzw. mit einem Dateimanager deiner Wahl.
2. Öffne die Datei **`/ext/subghz/assets/dangerous_settings`**. Sie sieht so aus:
   ```text
   # Do you want to damage your flipper CC1101 radio chip by using Frequencies that outside HW specs?
   # CC1101 Frequency range specs: 300-348 MHz, 386-464 MHz, and 778-928 MHz
   # This setting will extend to: 281-361 MHz, 378-481 MHz, and 749-962 MHz
   yes_i_want_to_destroy_my_flipper: false
   ```
3. Lies die Kommentare und ändere dann `false` zu `true`:
   ```text
   yes_i_want_to_destroy_my_flipper: true
   ```
4. Speichere die Datei und starte den Flipper neu. Die Einstellung wird beim Start gelesen.

Zum Zurücknehmen setze den Wert auf `false` und starte neu.

::: warning Updates
Die Datei gehört zu den Firmware-Ressourcen. Ein Update kann sie mit dem Standardwert `false` überschreiben. Prüfe sie
nach einem Update, wenn du auf die Einstellung angewiesen bist.
:::

## Siehe auch

- Sub-GHz-Frequenzen und Presets, eigene Frequenzen hinzufügen: [Frequenzen](/de/subghz/frequencies)
- Sub-GHz-Einstellungen in der App: [Sub-GHz-Einstellungen](/de/subghz/settings)
- Externes CC1101-Modul: [Externes CC1101](/de/subghz/external-cc1101)

Nutze den Funk nur mit eigenen Geräten und im Rahmen der für dich gültigen Funkvorschriften.
