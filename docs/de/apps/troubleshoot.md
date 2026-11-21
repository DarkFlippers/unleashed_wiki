---
title: Probleme mit Apps
order: 140
original: [https://docs.flipper.net/zero/apps/troubleshoot, https://github.com/DarkFlippers/unleashed-firmware/tree/dev/applications/services/loader, https://github.com/DarkFlippers/unleashed-firmware/blob/dev/documentation/AppsOnSDCard.md]
sources: [flipper-docs, unleashed-src, unleashed-docs]
---
# Probleme mit Apps

Wenn eine App nicht starten kann, zeigt der Flipper `Error: <name>` mit einem kurzen Hinweis und dem Link
`r.flipper.net/err_0X`. Diese Seite erklärt jede Meldung so, wie sie in Unleashed erscheint.

::: tip Unleashed
Unleashed blockiert keine Apps, die für eine andere API-Version gebaut wurden. Anstelle der originalen Fehler
**Outdated App** / **Outdated Firmware** zeigt es eine Warnung und lässt dich entscheiden, siehe
[App Too Old / App Too New](#app-too-old-app-too-new).
:::

## App Too Old / App Too New

```
App Too Old
APP:86 < FW:88
This app might not work
Continue anyways?
```

Die **Major-API-Version** der App unterscheidet sich von der der Firmware: **App Too Old** bedeutet, dass die App
für eine ältere API gebaut wurde, **App Too New** für eine neuere.

- Drücke **Continue** (<kbd>→</kbd>), um es trotzdem zu versuchen. Viele Apps funktionieren, aber eine App, die eine
  geänderte Funktion aufruft, kann abstürzen.
- Drücke <kbd>Back</kbd> zum Abbrechen.
- Die echte Lösung: die App aktualisieren (nimm sie aus dem aktuellen Unleashed-Pack oder baue sie für das aktuelle
  SDK neu) oder, bei **App Too New**, die Firmware aktualisieren.

## Error: App Not Found (err_01)

`Update firmware or app`

| Ursache | Lösung |
|---|---|
| die Datei der App wurde von der SD-Karte gelöscht | die App neu installieren oder (bei System-Apps) die Firmware neu installieren |
| eine alte oder Beta-Version der Mobil-App hat eine Katalog-App geöffnet, die nicht auf der Karte liegt | die offizielle Flipper-Mobil-App aus dem App Store / von Google Play installieren und die App neu installieren |

Eine verwandte Meldung, **SD card needed** / `Install SD card to run this app`, bedeutet, dass eine Menü-App auf der
SD-Karte liegt und keine Karte eingesteckt ist. **Update needed** / `Update firmware to run this app` bedeutet, dass
die Karte da ist, die App-Datei aber fehlt: installiere die Firmware mit eingesteckter Karte neu.

## Error: Invalid File (err_02)

`Update the app`. Das `.fap` ist beschädigt: fehlerhafter ELF-Header, unvollständige Datei (abgebrochenes Kopieren)
oder Sektionen, die nicht geladen werden können. Kopiere oder installiere die App erneut.

## Error: Invalid Manifest (err_03)

`Update firmware or app`. Das Manifest (eine besondere ELF-Sektion mit der API-Version und den App-Informationen)
kann nicht gelesen werden. Die Datei ist beschädigt, oder App und Firmware liegen zu weit auseinander. Aktualisiere
die App; ist sie neuer als deine Firmware, aktualisiere die Firmware.

## Error: Missing Imports (err_04)

`Update firmware or app`. Die App ruft Funktionen auf, die deine Firmware nicht exportiert.

| Ursache | Lösung |
|---|---|
| die App wurde für eine neuere Firmware gebaut | Unleashed aktualisieren |
| die App wurde für einen anderen Fork gebaut (sie nutzt dessen eigene Funktionen) | einen Build der App für Unleashed suchen oder sie mit dem Unleashed-SDK neu bauen |

## Error: HW Target Mismatch (err_05)

`App not supported`. Die App wurde für ein anderes Flipper-Hardware-Target gebaut. Sie kann auf diesem Gerät nicht
laufen.

## Error: Out of Memory

`Not enough RAM to run the app. Please reboot the device`. Ein FAP wird ins RAM geladen; ist der Heap fragmentiert
oder läuft zu viel gleichzeitig (zum Beispiel ein BLE-Beacon im Hintergrund oder eine große App), passt es nicht
hinein. Drücke **Reboot** und starte die App direkt nach dem Hochfahren erneut.

## Es funktioniert weiterhin nicht

1. Aktualisiere auf das neueste Unleashed-Release, siehe [Aktualisieren](/de/start/updating).
2. Installiere die App aus dem aktuellen [App-Pack](/de/apps/catalog#base-and-extra-packs) oder aus dem Katalog neu
   ([Apps auf der SD-Karte](/de/apps/sd-card-apps)).
3. Wenn eine App den Flipper zum Abstürzen bringt, starte ihn mit <kbd>←</kbd> + <kbd>Back</kbd> neu; siehe
   [Wiederherstellung](/de/start/recovery), wenn er nicht mehr hochfährt.
4. Frag in den Community-Chats, siehe [FAQ](/de/start/faq).

## Verwandte Seiten

- [Apps auf der SD-Karte (.fap)](/de/apps/sd-card-apps)
- [Apps im Lieferumfang von Unleashed](/de/apps/catalog)
